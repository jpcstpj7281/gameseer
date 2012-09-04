
#include "vxWorks.h"
#include "stdio.h"
#include "semLib.h"


#define SYS_FLASH_WRITE_ENABLE_RTN()	BSP_FlashWriteEnable(1)
#define SYS_FLASH_WRITE_DISABLE_RTN() BSP_FlashWriteEnable(0)



#define FLASH29_REG_FIRST_CYCLE		 (FLASH_BASE16+0x555*2)
#define FLASH29_REG_SECOND_CYCLE	 (FLASH_BASE16+0x2aa*2)

/* FLASH29 command definitions */

#define	FLASH29_CMD_FIRST		(UINT16) 0xaa
#define	FLASH29_CMD_SECOND		(UINT16) 0x55
#define	FLASH29_CMD_FOURTH		(UINT16) 0xaa
#define	FLASH29_CMD_FIFTH		(UINT16) 0x55
#define	FLASH29_CMD_SIXTH		(UINT16) 0x10
#define	FLASH29_CMD_SECTOR		(UINT16) 0x30

#define	FLASH29_CMD_PROGRAM		(UINT16) 0xa0
#define	FLASH29_CMD_CHIP_ERASE	(UINT16) 0x80
#define	FLASH29_CMD_READ_RESET	(UINT16) 0xf0
#define	FLASH29_CMD_AUTOSELECT	(UINT16) 0x90
  



#define FLASH_BASE16            (0x30000000)
#define BLOCK_SIZE_16           (0x20000)
#define ADVANCED_BOOTROM_ADRS   (0x30000000)
#define MAX_BOOTROM_FILE_LENGTH (0x400000)

#define SYSTEMINFO_AREA      ((FLASH_BASE16)+(0x2F0000))

#define SYSTEMINFO_MAC		((FLASH_BASE16))


/* Operation status bits for Flash 29Fxxx devices */

#define Q7(ix)		((ix & 0x80) >> 7)	/* DQ7 bit */
#define Q5(ix)		((ix & 0x20) >> 5)	/* DQ5 bit */
#define Q6(ix)		((ix & 0x40) >> 6)	/* DQ6 bit */
#define Q2(ix)		((ix & 0x02) >> 2)	/* DQ2 bit */

/* globals */

/*
IMPORT	void sysFlashWriteEnable (void);
IMPORT	void sysFlashWriteDisable (void);
*/

/* forward declarations */

static SEM_ID		semFlsh=NULL; 			 /*FLASh 保护*/





STATUS	sysFlashDataPoll16 (volatile UINT16 * pFA, UINT16 value);
STATUS  sysFlashWrite16(UINT16 *	pFB,UINT16 * offset,int size);
STATUS 	sysFlashErase16(void);
UINT32 WriteFlash(UINT32 *source,UINT32 length);
LOCAL STATUS BSP_sysFlashDataPoll16(volatile UINT16 * pFA,UINT16 value,UINT16 oper);


STATUS sysFlashDataPoll16
    (
    volatile UINT16 * pFA,	/* programmed address to poll */
    UINT16 value		/* data programmed to poll address */
    )
{
	STATUS retVal = OK;
	volatile UINT16 * pTest = (UINT16 *) pFA;
	volatile UINT16 * pVal  = (UINT16 *) &value;
	int ix;			/* byte counter */
	int vBit;			/* programmed value of DQ7 */

	vBit = Q7(*pVal);

	while (Q7(*pTest) != vBit)
	{
		if (Q5(*pTest) == 1)	/* timeout ? */
		{
			break;
		}
	}

	if (Q7(*pTest) != vBit)		/* check Q7 & Q5 race */
		retVal = ERROR;


	return (retVal);
}

/******************************************************************************
*
* sysSectorErase - erase the contents of a sector
*
* This routine clears the contents of one sector in the flash memory.
*
* Flash 29F\f2xxx\f1 devices are erased by writing the six-byte erase code
* into specific address locations, which sets all byte locations to a high
* value (0xFF).
*
* RETURNS: OK, or ERROR if the contents of sector cannot be erased.
*/

STATUS sysSectorErase16
    (
    UINT32  FA		/* Sector start address */
    )
{
	STATUS retVal = OK;
	UINT16 * pFA= (UINT16 *)FA;
	SYS_FLASH_WRITE_ENABLE_RTN ();		/* enable write */
	pFA= (UINT16 *)FA;
	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
	*((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_CHIP_ERASE;
	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FOURTH;
	*((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_FIFTH;
	*pFA = FLASH29_CMD_SECTOR;
	
		retVal = BSP_sysFlashDataPoll16 (pFA, (UINT16) 0xffffffff,1);
	
	if(ERROR==retVal)
	{
		*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;
	}

	SYS_FLASH_WRITE_DISABLE_RTN ();		/* disable write */

	return (retVal);
}


STATUS sysFlashErase16
    (
    )
{
	volatile UINT16 * pFA = (UINT16 *) (FLASH_BASE16);
	STATUS retVal = OK;
	int ix;



	SYS_FLASH_WRITE_ENABLE_RTN ();		/* enable write */

	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
	*((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_CHIP_ERASE;
	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FOURTH;
	*((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_FIFTH;
	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_SIXTH;

/*	
	retVal = BSP_sysFlashDataPoll16 (pFA, (UINT16) 0xffffffff,1);
*/	
	retVal = sysFlashDataPoll16(pFA,(UINT16)0xffffffff);


	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;

	SYS_FLASH_WRITE_DISABLE_RTN ();		/* disable enable */

	return (retVal);
}

void resetflash(void)
{
	*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;
}

STATUS sysFlashWrite16
    (
    UINT16 *	pFB,		/* string to be copied; use <value> if NULL */
    UINT16 *	offset,		/* byte offset into flash memory */
    int		size		/* size to program in bytes */
    )
{
	volatile UINT16 * pFA;		/* flash address */
	STATUS retVal = OK;
	int ix;
	int sectorSize = 128;
	int twc = 2;	/* time for write completion */
	UINT16 value =0;
	SYS_FLASH_WRITE_ENABLE_RTN ();		/* enable write */

	for (pFA = offset; pFA < (UINT16 *)( size +(int) offset) && (retVal == OK); pFA++)
	{
		value = *pFB++;
		if(value == 0xffff) 
		{
			continue;
		}
		*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
		*((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
		*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_PROGRAM;

		*pFA = value;                    	/* data to write */
/*		retVal = BSP_sysFlashDataPoll16 (pFA, (UINT16) value,2);
*/
		retVal = sysFlashDataPoll16(pFA, (UINT16)value);

		if(ERROR==retVal)
		{
			*((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;
		}
	}

	SYS_FLASH_WRITE_DISABLE_RTN ();		/* disable write */

	return (retVal);
}

	
	
int writeFlash16
		(
		  UINT16 *source,
		  UINT16 *dest,
		  int	 dataLength
		)
{
	UINT32 offset,temp;
	int    startBlock;
	int    endBlock;
	int    dataLen;
	UINT32 sourceBak;
	UINT32 destBak;

	if(semFlsh==NULL)
	{
	  semFlsh = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	  if(OK!=semGive(semFlsh))
	  {
		 logMsg("semFlsh give !\n",0,0,0,0,0,0);
		 return(ERROR);
	  }
	}

	if(OK!=semTake(semFlsh, WAIT_FOREVER))
	{
		logMsg("semFlsh take !\n",0,0,0,0,0,0);
		return(ERROR);
	}

	dataLen=dataLength;
	sourceBak=(UINT32)source;
	destBak=(UINT32)dest;  
	offset=destBak-FLASH_BASE16; 
	startBlock=(int)(offset/BLOCK_SIZE_16);   
	endBlock=(int)((offset+dataLength)/BLOCK_SIZE_16);
	while(startBlock<=endBlock)
	{
		if(startBlock<endBlock)
		{  
			if( sysSectorErase16( destBak ) != OK )
			{
				if(OK!=semGive(semFlsh))
				{
				   logMsg("semFlsh give !\n",0,0,0,0,0,0);
				}

				printf("\nERROR: erase flash block failure, Address:%08x!!\n",destBak);
				resetflash();
				return(ERROR);
			}


			if(sysFlashWrite16((UINT16*)sourceBak,(UINT16*)destBak,
			((startBlock+1)*BLOCK_SIZE_16-offset))==ERROR)
			{
			
				if(OK!=semGive(semFlsh))
				{
				   logMsg("semFlsh give !\n",0,0,0,0,0,0);
				}
				resetflash();
				return(ERROR);
			}
			temp=(startBlock+1)*BLOCK_SIZE_16-offset;
			dataLen-=temp;
			offset+=temp;
			sourceBak=sourceBak+temp;
			destBak=destBak+temp;
			startBlock++;
		}
		else
		{

			if(dataLen == 0)
			{

				if(OK!=semGive(semFlsh))
				{
				   logMsg("semFlsh give !\n",0,0,0,0,0,0);
				}
				return(OK);


			}			
			if( sysSectorErase16( destBak ) != OK )
			{
				printf("\nERROR: erase flash block failure, Address:%08x!!\n",destBak);
				
				if(OK!=semGive(semFlsh))
				{
				   logMsg("semFlsh give !\n",0,0,0,0,0,0);
				}
				resetflash();
				return(ERROR);
			}
			if(sysFlashWrite16((UINT16*)sourceBak,(UINT16*)destBak,dataLen)==ERROR)
			{
			
				if(OK!=semGive(semFlsh))
				{
				   logMsg("\nERROR: write flash block failure!!\n",0,0,0,0,0,0);
				}
				resetflash();
				return(ERROR);
			}
			else
			{
			
				if(OK!=semGive(semFlsh))
				{
				  logMsg("semFlsh give !\n",0,0,0,0,0,0);
				}
				return(OK);
			}
		} 
		
	}/*while*/	 
	
	if(OK!=semGive(semFlsh))
	{
	   logMsg("semFlsh give !\n",0,0,0,0,0,0);
	}
	return(OK);
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
	UINT16 ix2=0;			/* byte counter */
	UINT16 ix3=0;			/* byte counter */
    UINT32 delay=0;
	int vBit=0;			/* programmed value of DQ7 */
	vBit = Q7(*pVal);
    delay=tickGet();
	while (Q7(*pTest) != vBit)
	{
        if(tickGet()<delay)
        {
           delay=tickGet();
        }
        if (tickGet()>(delay+1000))
        {
            retVal= ERROR;  /* timeout ? */
            return (retVal);
        }
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

/*根据 2008 最新版本DATASHEET 描述修改写轮询流程*/
LOCAL STATUS BSP_sysFlashDataPoll16_NEW
    (
    volatile UINT16 * pFA,	/* programmed address to poll */
    UINT16 value,	/* data programmed to poll address */
    UINT16 oper		/* 1 erase or  2 program */
    )
{
	STATUS retVal = ERROR;
	volatile UINT16 * pTest = (UINT16 *) pFA;
	volatile UINT16 * pVal  = (UINT16 *) &value;
	UINT16 ix1=0;			/* Read_1 */
	UINT16 ix2=0;			/* Read_2 */
	UINT16 ix3=0;			/* Read_3 */
    UINT32 delay=0;
	int vBit=0;			/* programmed value of DQ7 */

	ix1=*pTest;
	ix2=*pTest;
	ix3=*pTest;	
    printf("ix1/2/3:0x%x,0x%x,0x%x\n",ix1,ix2,ix3);
	 /*DQ6 Toggles between Read_1 & Read_2  and Read_2 & Read_3*/

	  while((Q6(ix1) !=	Q6(ix2))&&(Q6(ix2) !=	Q6(ix3)))
	  {
		/*yes*/
		if(Q5(ix1))
		{
			printf("\nERROR: write flash block failure!! timeout!\n",0,0,0,0,0,0);
			retVal= ERROR;
			return retVal;
		}
		
		ix1=*pTest;
		ix2=*pTest;
		ix3=*pTest; 

	  }


	ix1=*pTest;
	ix2=*pTest;

	if((Q2(ix1) !=	Q2(ix2)))
	{
		retVal = OK;
		return retVal;
	}

	return (retVal);
}

void downloadBootrom( void )
{
	UINT8 data ;
	UINT32 bytes ;
	UINT8 *bootrom_buf, *bootrom_p1 ;
	FILE *bootrom_fd ;

	 *((UINT32 *) 0xc4000000)=0xbcd23c42;
	printf( "start download advancedBootrom, address is 0x%x\n", ADVANCED_BOOTROM_ADRS ) ;
	bootrom_buf = (UINT8*)malloc( 0x108000 ) ;
	if( bootrom_buf == NULL )
	{
		printf( "\nERROR: can not malloc buf!!\n" ) ;
		return ;
	}

	bootrom_p1 = bootrom_buf ;

	if((bootrom_fd = fopen( "bootrom.bin", "rb" )) == NULL )
	{
		printf( "\nERROR: can not open advancedBootrom.bin\n" ) ;
		free( bootrom_buf ) ;
		return ;
	}

	bytes = 0 ;
	printf( "read file\n" ) ;
	taskDelay(1);
	while( fscanf( bootrom_fd, "%c", &data ) != EOF )
	{
		*bootrom_p1++ = data ;
		bytes = bytes + 1 ;
		if( bytes >= 0x108000 )
			break ;
	} 
	fclose( bootrom_fd ) ;
	
	if( bytes > MAX_BOOTROM_FILE_LENGTH )
	{
		printf( "ERROR: bootrom file is too long!\n" ) ;
		free( bootrom_buf ) ;
		return ;
	}
	
	printf( "file size is %d bytes\n", bytes ) ;
	taskDelay(1);

	printf( "bootrom2 erase..." ) ;
	if( sysSectorErase16( ADVANCED_BOOTROM_ADRS ) != OK )
	{
		printf( "\nERROR: erase flash block failure!!\n" ) ;
		free( bootrom_buf ) ;
		return ;
	}
	printf( "down\nStart write..." ) ;
	if( writeFlash16((UINT16*)bootrom_buf, (UINT16*)ADVANCED_BOOTROM_ADRS, bytes ) == OK )
		printf( "write bootrom2 success\n" ) ;
	else
		printf( "ERROR: write bootrom2 failure!!\n" ) ;
	free( bootrom_buf ) ;
}

void flashtest()
{
	/* Here is an example of Autoselect mode (getting manufacturer ID) */
	/* Define UINT16 example: typedef unsigned short UINT16; */
	unsigned short manuf_id;
	unsigned short devid1;
	unsigned short devid2;
	unsigned short devid3;
	unsigned short secure_device;
	unsigned short sector_protect;
	
	/* Auto Select Entry */
	*( (unsigned short *)0x30000000 + 0x555 ) = 0x00AA; /* write unlock cycle 1 */
	*( (unsigned short *)0x30000000 + 0x2AA ) = 0x0055; /* write unlock cycle 2 */
	*( (unsigned short *)0x30000000 + 0x555 ) = 0x0090; /* write autoselect command */
	/* multiple reads can be performed after entry */
	manuf_id = *( (unsigned short *)0x30000000 + 0x000 ); /* read manuf. id */
	devid1 = *( (unsigned short *)0x30000000 + 0x001 ); /* read manuf. id */
	devid2 = *( (unsigned short *)0x30000000 + 0x00e ); /* read manuf. id */
	devid3 = *( (unsigned short *)0x30000000 + 0x00f ); /* read manuf. id */
	secure_device = *( (unsigned short *)0x30000000 + 0x003 ); /* read manuf. id */
	sector_protect = *( (unsigned short *)0x30000000 + 0x002 ); /* read manuf. id */
	/* Autoselect exit */
	*( (unsigned short *)0x30000000 + 0x000 ) = 0x00F0; /* exit autoselect (write reset command) */
	printf("manuf_id:%x \n",manuf_id);
	printf("devid1:%x \n",devid1);
	printf("devid2:%x \n",devid2);
	printf("devid3:%x \n",devid3);
	printf("secure_device:%x \n",secure_device);
	printf("sector_protect:%x \n",sector_protect);
}

void flashwrite(unsigned short addr, unsigned short data)
{
	SYS_FLASH_WRITE_ENABLE_RTN ();		/* enable write */
	*( (unsigned short *)0x30000000 + 0x555 ) = 0x00AA; /* write unlock cycle 1 */
	*( (unsigned short *)0x30000000 + 0x2AA ) = 0x0055; /* write unlock cycle 2 */
	*( (unsigned short *)0x30000000 + 0x555 ) = 0x00A0; /* write program setup command */
	*( (unsigned short *)(0x30000000 + addr)) = data; /* write data to be programmed */
	SYS_FLASH_WRITE_DISABLE_RTN ();		/* disable write */
}

void setFlashConfig(unsigned int value)
{
	*((volatile unsigned int *)0xffffff78) = value;
}

void flashreset(unsigned int value)
{
	*((volatile unsigned int *)0x30000000) = 0x00f0;
}


