
/************************************************************************/
/*                                                                      */
/*		FAT-FTL Lite Software Development Kit			*/
/*		Copyright (C) M-Systems Ltd. 1995-1996			*/
/*									*/
/************************************************************************/
/*                                                                      */
/*                    16-bit AMD MTD                                    */
/*                                                                      */
/* This MTD is for flash media which is accessible in 16-bit mode only. */
/* The following Flash technologies are supported:                      */
/*                                                                      */
/* - AMD     Am29F080   8-mbit devices                                  */
/* - AMD     Am29LV080  8-mbit devices                                  */
/* - AMD     Am29F016  16-mbit devices                                  */
/* - Fujitsu MBM29F080  8-mbit devices                                  */
/*									*/
/************************************************************************/

/*
 * $Log:   V:/wamdmtd.c_v  $
 * 
 *    Rev 1.1   07 Oct 1997 14:58:32   ANDRY
 * get rid of generic names, registration routine returns status
 *
 *    Rev 1.0   25 Aug 1997 12:00:00   ANDRY
 * Initial revision.
 */


#include "tffs/flflash.h"
#include "tffs/backgrnd.h"


/* JEDEC ids for this MTD */
#define Am29F040_FLASH       0x01a4
#define Am29F080_FLASH       0x01d5
#define Am29LV080_FLASH      0x0137
#define Am29LV008_FLASH      0x0137
#define Am29F016_FLASH       0x007E
#define Am29F016C_FLASH      0x013d
#define Am29LV017_FLASH      0x01c8

#define Fuj29F040_FLASH      0x04a4
#define Fuj29F080_FLASH      0x04d5
#define Fuj29LV080_FLASH     0x0438
#define Fuj29LV008_FLASH     0x0437
#define Fuj29F016_FLASH      0x04ad
#define Fuj29F016C_FLASH     0x043d
#define Fuj29LV017_FLASH     0x04c8

/* commands for AMD flash */
#define SETUP_ERASE          0x80
#define SETUP_WRITE          0xa0
#define READ_ID              0x90
#define SUSPEND_ERASE        0xb0
#define SECTOR_ERASE         0x30
#define RESUME_ERASE         0x30
#define READ_ARRAY           0xf0
#define INTEL_READ_ARRAY     0xff

/* AMD unlocking sequence */
#define UNLOCK_1             0xaaaa
#define UNLOCK_2             0x5555
#define UNLOCK_ADDR1         0x5555
#define UNLOCK_ADDR2         0x2aaa

/* AMD flash status bits */
#define D2                   0x04    /* Toggles when erase suspended */
#define D5                   0x20    /* Set when programming timeout */
#define D6                   0x40    /* Toggles when programming     */
#define Q7(ix)		((ix & 0x80) >> 7)	/* DQ7 bit */
#define Q5(ix)		((ix & 0x20) >> 5)	/* DQ5 bit */
#define Q6(ix)		((ix & 0x40) >> 6)	/* DQ6 bit */
#define Q2(ix)		((ix & 0x02) >> 2)	/* DQ2 bit */

#ifdef __cplusplus
  #define wFlashPtr    ((FlashWPTR &) flashPtr)
  #define wBuffer      ((const unsigned short FAR1 * &) buffer)
  #define wUnlockAddr1 ((FlashWPTR &) unlockAddr1)
  #define wUnlockAddr2 ((FlashWPTR &) unlockAddr2)
#else
  #define wFlashPtr    ((FlashWPTR) flashPtr)
  #define wBuffer      ((const unsigned short FAR1 *) buffer)
  #define wUnlockAddr1 ((FlashWPTR) unlockAddr1)
  #define wUnlockAddr2 ((FlashWPTR) unlockAddr2)
#endif

LOCAL STATUS BSP_sysFlashDataPoll16(volatile UINT16 * pFA,UINT16 value,UINT16 oper);


/* -------------------------------------------------------------------- */
/* AMD Flash specific data. Pointed by FLFlash.mtdVars                  */
/* -------------------------------------------------------------------- */

typedef struct
        {
          FlashWPTR  unlockAddr1;
          FlashWPTR  unlockAddr2;
        } Vars;

static Vars  mtdVars[DRIVES];

#define thisVars   ((Vars *) vol.mtdVars)

LOCAL void mydelay();



/* -------------------------------------------------------------------- */
/*               f l U p d a t e U n l o c k A d d r s                  */
/*									*/
/* Updates unlock addresses for AMD flash media.                        */
/*									*/
/*									*/
/* Parameters:                                                          */
/*	vol		: Pointer identifying drive			*/
/*      basePtr         : flash pointer, could point anywhere in the    */
/*                        memory window                                 */
/*									*/
/* -------------------------------------------------------------------- */

static void flUpdateUnlockAddrs (FLFlash    vol,
                                 FlashWPTR  basePtr)
{
  if ((vol.type == Am29F016C_FLASH) || (vol.type == Fuj29F016C_FLASH))
    thisVars->unlockAddr1 = thisVars->unlockAddr2 = basePtr;
  else
  {
    thisVars->unlockAddr1 = (FlashWPTR)(((long)basePtr & -0x10000l)) + 0x555;
    thisVars->unlockAddr2 = (FlashWPTR)(((long)basePtr & -0x10000l)) + 0x2aa;
  }
}


/*----------------------------------------------------------------------*/
/*                   f l w A m d C o m m a n d                          */
/*									*/
/* Writes an AMD command with the required unlock sequence		*/
/*									*/
/* Parameters:                                                          */
/*	vol		: Pointer identifying drive			*/
/*      address		: Card address at which to write command	*/
/*	command		: command to write				*/
/*                                                                      */
/*----------------------------------------------------------------------*/

static void flwAmdCommand (FLFlash         vol,
                           CardAddress     address,
                           unsigned short  command)
{
  if (thisVars->unlockAddr1)
  {
    thisVars->unlockAddr1[0] = UNLOCK_1;
    thisVars->unlockAddr2[0] = UNLOCK_2;
    thisVars->unlockAddr1[0] = command;
  }
  else
  {
    CardAddress  baseAddress  = address & (-0x10000l);

    /* write AMD unlock sequence */
    *(FlashWPTR) vol.map (&vol,
                          baseAddress + 2 * UNLOCK_ADDR1,
                          vol.interleaving) = UNLOCK_1;
    *(FlashWPTR) vol.map (&vol,
                          baseAddress + 2 * UNLOCK_ADDR2,
                          vol.interleaving) = UNLOCK_2;

    /* write flash command */
    *(FlashWPTR) vol.map (&vol,
                          baseAddress + 2 * UNLOCK_ADDR1,
                          vol.interleaving) = command;

    vol.map (&vol, address, vol.interleaving);
  }
}


/*----------------------------------------------------------------------*/
/*                f l w A m d M T D W r i t e                           */
/*									*/
/* Write a block of bytes to Flash					*/
/*									*/
/* This routine will be registered as FLFlash.write routine             */
/*									*/
/* Parameters:                                                          */
/*	vol		: Pointer identifying drive			*/
/*      address		: Card address to write to			*/
/*      buffer		: Address of data to write			*/
/*	length		: Number of bytes to write			*/
/*	overwrite	: TRUE if overwriting old Flash contents	*/
/*			  FALSE if old contents are known to be erased	*/
/*                                                                      */
/* Returns:                                                             */
/*      FLStatus        : 0 on success, failed otherwise                */
/*----------------------------------------------------------------------*/

static FLStatus flwAmdMTDWrite (FLFlash           vol,
                                CardAddress       address,
                                const void FAR1  *buffer,
                                int               length,
                                FLBoolean         overwrite)
{
  unsigned long writeTimeout;
  int           cLength;
  FlashWPTR     flashPtr,

                unlockAddr1 = thisVars->unlockAddr1,
                unlockAddr2 = thisVars->unlockAddr2;
  STATUS retVal = OK;
  if ( flWriteProtected(vol.socket) )
    return flWriteProtect;

  flashPtr = (FlashWPTR) vol.map (&vol, address, length);

  /* set addresses for AMD unlock sequence */
  flUpdateUnlockAddrs (&vol, flashPtr);
  unlockAddr1 = thisVars->unlockAddr1;
  unlockAddr2 = thisVars->unlockAddr2;

  /* Set timeout to 5 seconds from now */
  writeTimeout = flMsecCounter + 5000;

  /* write the data */
  cLength = length;
  while (cLength >= 2)
  {
    /* AMD unlock sequence */
    *wUnlockAddr1 = UNLOCK_1;
    *wUnlockAddr2 = UNLOCK_2;

    /* flash command */
    *wUnlockAddr1 = SETUP_WRITE;

    /* write user data word */
    *wFlashPtr    = *wBuffer;
    /* wait for ready */

	retVal=BSP_sysFlashDataPoll16(wFlashPtr,*wBuffer,2);
	
	if(ERROR==retVal)
	{
		resetflash();
		 return flWriteFault;
	}
	
    

    cLength -= 2;
    /* replaced wBuffer++; wFlashPtr++; */
    buffer = (unsigned char *)buffer + sizeof(unsigned short);
    flashPtr = (FlashWPTR)flashPtr + 1;
  }

  /* verify the written data */
  /* replaced: wFlashPtr -= length/2; wBuffer -= length/2; */
  flashPtr -= length / 2;
  buffer = (unsigned short *)buffer - (length/2);

  if (tffscmp((void FAR0 *)flashPtr, buffer, length))
  	{
    return flWriteFault;
/*			  resetflash();*/

  	}
		  resetflash();

  return flOK;
}


/*----------------------------------------------------------------------*/
/*               f l w A m d M T D E r a s e                            */
/*									*/
/* Erase one or more contiguous Flash erasable blocks			*/
/*									*/
/* This routine will be registered as FLFlash.erase routine             */
/*									*/
/* Parameters:                                                          */
/*      vol                : Pointer identifying drive                  */
/*      firstBlock         : Number of first block to erase             */
/*      numOfBlocks        : Number of blocks to erase                  */
/*                                                                      */
/* Returns:                                                             */
/*      FLStatus           : 0 on success, failed otherwise             */
/*----------------------------------------------------------------------*/

static FLStatus flwAmdMTDErase (FLFlash  vol,
                                int      firstBlock,
                                int      numOfBlocks)
{
  FlashWPTR  flashPtr;
  FLBoolean  finished;
  int        iBlock;
  STATUS retVal = OK;

  if ( flWriteProtected(vol.socket) )
    return flWriteProtect;

  for (iBlock = 0;  iBlock < numOfBlocks;  iBlock++)
  {
    flashPtr = (FlashWPTR) vol.map( &vol,
                                   (firstBlock + iBlock) * vol.erasableBlockSize,
                                    vol.interleaving);

    flUpdateUnlockAddrs (&vol, flashPtr);

    flwAmdCommand (&vol, 0, SETUP_ERASE);
    flwAmdCommand (&vol, 0, SECTOR_ERASE);

   
   retVal=BSP_sysFlashDataPoll16(wFlashPtr,0xFFFF,1);
   
   if(ERROR==retVal)
   {
	   resetflash();
	   return flWriteFault;
   }
   
  }

  return flOK;
}


/*----------------------------------------------------------------------*/
/*                     f l w A m d I d e n t i f y                      */
/*									*/
/* Identify the AMD Flash media.                                        */
/* Sets the value of flash.type (JEDEC id) & FLFlash.interleaving.	*/
/*									*/
/* Parameters:                                                          */
/*      vol             : Pointer identifying drive                     */
/*	amdCmdRoutine	: Routine to read-id AMD/Fujitsu style at	*/
/*			  a specific location. If null, Intel procedure	*/
/*			  is used.                                      */
/*      idOffset	: Chip offset to use for identification		*/
/*                                                                      */
/*----------------------------------------------------------------------*/

void flwAmdIdentify (FLFlash      vol,
                            void (*amdCmdRoutine)(FLFlash vol, CardAddress, unsigned short),
                            CardAddress  idOffset)
{
  unsigned short  resetCmd  = amdCmdRoutine ? READ_ARRAY : INTEL_READ_ARRAY;
  FlashWPTR       flashPtr  = (FlashWPTR) flMap (vol.socket, idOffset);

  vol.noOfChips = 0;

  flashPtr[0] = resetCmd;          /* Reset chips             */
  taskDelay(1);


  if (amdCmdRoutine)               /* use AMD unlock sequence */
  {
    flUpdateUnlockAddrs (&vol, flashPtr);
    amdCmdRoutine (&vol, idOffset, READ_ID);
  }
  else
    flashPtr[0] = READ_ID;         /* use Intel-style         */


  vol.type = (FlashType) ((flashPtr[0] & 0xff00) | (flashPtr[1] & 0xff));

  flashPtr[0] = resetCmd;
}


/*----------------------------------------------------------------------*/
/*                       f l w A m d S i z e                            */
/*									*/
/* Identify the card size for AMD Flash.                                */
/* Sets the value of flash.noOfChips.					*/
/*									*/
/* Parameters:                                                          */
/*	vol		: Pointer identifying drive			*/
/*	amdCmdRoutine	: Routine to read-id AMD/Fujitsu style at	*/
/*			  a specific location. If null, Intel procedure	*/
/*			  is used.                                      */
/*      idOffset	: Chip offset to use for identification		*/
/*                                                                      */
/* Returns:                                                             */
/*      FLStatus        : 0 = OK, otherwise failed (invalid Flash array)*/
/*----------------------------------------------------------------------*/

FLStatus flwAmdSize (FLFlash      vol,
                   void (*amdCmdRoutine)(FLFlash vol, CardAddress, unsigned short),
                   CardAddress  idOffset)
{
  unsigned short  resetCmd = amdCmdRoutine ? READ_ARRAY : INTEL_READ_ARRAY;
  FlashWPTR       flashPtr = (FlashWPTR) vol.map (&vol, idOffset, 0);

  if (amdCmdRoutine)             /* use AMD unlock sequence      */
  {
    flUpdateUnlockAddrs(&vol, flashPtr);
    amdCmdRoutine (&vol, idOffset, READ_ID);
  }
  else
    flashPtr[0] = READ_ID;       /* use Intel-style              */

  /* We left the first chip in Read ID mode, so that we can      */
  /* discover an address wraparound.                             */
  for (vol.noOfChips = 1;  vol.noOfChips < 2000;  vol.noOfChips++)
  {
    flashPtr = (FlashWPTR)
                vol.map (&vol, vol.noOfChips * vol.chipSize + idOffset, 0);

    /* Read ID from the chips without issuing a READ_ID command. */
    /* Check for address wraparound to the first chip.           */
    if ((FlashType)((flashPtr[0] & 0xff00) | (flashPtr[1] & 0xff)) == vol.type)
      break;                     /* wraparound to the first chip */

    /* Check if chip displays the same JEDEC id and interleaving */
    if (amdCmdRoutine)           /* AMD: use unlock sequence     */
    {
      flUpdateUnlockAddrs (&vol, flashPtr);
      amdCmdRoutine (&vol,
                     vol.noOfChips * vol.chipSize + idOffset,
                     READ_ID);
    }
    else
      flashPtr[0] = READ_ID;     /* use Intel-style              */

    if ((FlashType) ((flashPtr[0] & 0xff00) | (flashPtr[1] & 0xff)) != vol.type)
    {
      /* This "chip" doesn't respond correctly, so we're done */
      break;
    }

    flashPtr[0] = resetCmd;
  }

  flashPtr = (FlashWPTR) vol.map (&vol, idOffset, 0);
  flashPtr[0] = resetCmd;        /* reset the original chip      */

  return (vol.noOfChips == 0) ? flUnknownMedia : flOK;
}



/*----------------------------------------------------------------------*/
/*              f l w A m d M T D I d e n t i f y                       */
/*									*/
/* Identifies AMD flash media accessible in 16-bit mode only.           */
/*									*/
/* This routine will be placed on the MTD list in CUSTOM.C. It must be  */
/* an extern routine.							*/
/*									*/
/* On successful identification, the Flash structure is filled out and	*/
/* the write and erase routines registered.				*/
/*									*/
/* Parameters:                                                          */
/*	vol		: Pointer identifying drive			*/
/*                                                                      */
/* Returns:                                                             */
/*      FLStatus        : 0 = OK, otherwise failed (invalid Flash array)*/
/*----------------------------------------------------------------------*/

FLStatus flwAmdMTDIdentify (FLFlash vol)
{
  unsigned int tempID;
  FlashWPTR  baseFlashPtr;

  flSetWindowBusWidth (vol.socket,16);      /* use 16-bits */
  flSetWindowSpeed (vol.socket,120);        /* 120 nsec.   */

  /* place to store all the AMD-specific flash parametes */
  vol.mtdVars = &mtdVars[flSocketNoOf(vol.socket)];

  thisVars->unlockAddr1 = NULL;

  vol.interleaving = 1;

  flwAmdIdentify (&vol, flwAmdCommand, 0);
	tempID=vol.type;
  if (vol.type == Am29F016_FLASH   || vol.type == Fuj29F016_FLASH  ||
      vol.type == Am29F016C_FLASH  || vol.type == Fuj29F016C_FLASH ||
      vol.type == Am29LV017_FLASH  || vol.type == Fuj29LV017_FLASH)
    vol.chipSize = 0x400000l * vol.interleaving;
  else
  if (vol.type == Fuj29F080_FLASH  || vol.type == Am29F080_FLASH   ||
      vol.type == Fuj29LV080_FLASH || vol.type == Am29LV080_FLASH  ||
      vol.type == Fuj29LV008_FLASH || vol.type == Am29LV008_FLASH)
{
    vol.chipSize = 0x100000l * vol.interleaving;
  	tempID= vol.chipSize;
}
  else
  if (vol.type == Fuj29F040_FLASH  ||  vol.type == Am29F040_FLASH)
    vol.chipSize = 0x80000l * vol.interleaving;
  else
    return flUnknownMedia;

  /* find where the window is */
  baseFlashPtr = (FlashWPTR)
                  vol.map (&vol, (CardAddress)0, vol.interleaving);

  flUpdateUnlockAddrs (&vol, baseFlashPtr);

  checkStatus( flwAmdSize(&vol, flwAmdCommand, 0) );

  vol.erasableBlockSize = 0x20000l * vol.interleaving;
  vol.flags            |= SUSPEND_FOR_WRITE;

  /* Register our flash handlers */
  vol.write = flwAmdMTDWrite;
  vol.erase = flwAmdMTDErase;
/*printf("vol.type	             %08x\n",vol.type	              );*/
/*printf("vol.erasableBlockSize  %08x\n",vol.erasableBlockSize  );*/
/*printf("vol.chipSize           %08x\n",vol.chipSize           );*/
/*printf("vol.noOfChips          %08x\n",vol.noOfChips          );*/
/*printf("vol.interleaving       %08x\n",vol.interleaving       );*/
/*printf("vol.flags              %08x\n",vol.flags              );*/

  return flOK;
}

LOCAL void mydelay(UINT32 val)
{
	volatile UINT32 x=0;
	for(x=0;x<val;x++);
 		
}

LOCAL STATUS BSP_sysFlashDataPoll16
    (
    volatile UINT16 * pFA,	/* programmed address to poll */
    UINT16 value,	/* data programmed to poll address */
    UINT16 oper		/* 1 erase or  2 program */
    )
{
	STATUS retVal = OK;
	volatile UINT16 * pTest = (UINT16 *) pFA;
	volatile UINT16 * pVal  = (UINT16 *) &value;
	UINT16 ix2;			/* byte counter */
	UINT16 ix3;			/* byte counter */

	int vBit;			/* programmed value of DQ7 */

	vBit = Q7(*pVal);

	while (Q7(*pTest) != vBit)
	{
		if (Q5(*pTest) == 1)	
		{
			ix2=Q6(*pTest);
			ix3=Q6(*pTest);
			if(ix2 != ix3)
			{
				retVal= ERROR;	/* timeout ? */
				
				return (retVal);
			}

		}
	}


	
	ix2 = *pTest;
	ix3 = *pTest;

	if(2 == oper) /*programme opreation*/
	{
		if(ix3 == value)
		{
			retVal = OK;
		}
		else
		{
			retVal= ERROR; 	/* programme Failed */
		}
	}

	
	if(1 == oper) /*erase opreation*/
	{
	
		if(Q6(ix2)	!=	Q6(ix3))
		{
			
			retVal= ERROR;	/* Device Error ? */
		}
		if(Q2(ix2)	==	Q2(ix3))
		{
			retVal= OK;	/* Device Error ? */

		}
		else
		{
			retVal= ERROR;	/* Device Error ? */
	
		}
	}




	return (retVal);
}
 

#if	FALSE
/*----------------------------------------------------------------------*/
/*                 f l R e g i s t e r W A M D M T D                    */
/*									*/
/* Registers this MTD for use						*/
/*									*/
/* Parameters:                                                          */
/*	None								*/
/*                                                                      */
/*----------------------------------------------------------------------*/

FLStatus  flRegisterWAMDMTD (void)
{
  if (noOfMTDs >= MTDS)
    return flTooManyComponents;

  mtdTable[noOfMTDs++] = flwAmdMTDIdentify;

  return flOK;
}
#endif	/* FALSE */
