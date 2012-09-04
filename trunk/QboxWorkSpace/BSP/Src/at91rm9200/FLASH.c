
#include "vxWorks.h"
#include "stdio.h"
#include "semLib.h"


#define SYS_FLASH_WRITE_ENABLE_RTN()	/*sysFlashWriteEnable ()*/
#define SYS_FLASH_WRITE_DISABLE_RTN() /*sysFlashWriteDisable ()*/



#define FLASH29_REG_FIRST_CYCLE		 (FLASH_BASE16+0x5555*2)
#define FLASH29_REG_SECOND_CYCLE	 (FLASH_BASE16+0x2aaa*2)

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
 



#define FLASH_BASE16            (0x50000000)
#define BLOCK_SIZE_16           (0x20000)

#define ADVANCED_BOOTROM_ADRS   (0x50000000)
#define MAX_BOOTROM_FILE_LENGTH (0x100000)




/* Operation status bits for Flash 29Fxxx devices */

#define Q7(ix)		((ix & 0x80) >> 7)	/* DQ7 bit */
#define Q5(ix)		((ix & 0x20) >> 5)	/* DQ5 bit */

/* globals */

/*
IMPORT	void sysFlashWriteEnable (void);
IMPORT	void sysFlashWriteDisable (void);
*/

/* forward declarations */


void	sysFlashDelay16 (int delayCount);
STATUS	sysFlashDataPoll16 (volatile UINT16 * pFA, UINT16 value);
STATUS  sysFlashWrite16(UINT16 *	pFB,UINT16 * offset,int size);
STATUS 	sysFlashErase16(void);




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
    {
        retVal = ERROR;
    }


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
	UINT16 *pFA= (UINT16 *)FA;
	UINT32 erasetime=1;
	UINT32 LoopTime =0;
	if(FLASH_BASE16==FA)
	{
	    erasetime=8;
	}
	SYS_FLASH_WRITE_ENABLE_RTN ();		  /* enable write */
	for(LoopTime=0;LoopTime<erasetime;LoopTime++)
	{

	  pFA= (UINT16 *)FA;
	  *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
	  *((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
	  *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_CHIP_ERASE;
	  *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FOURTH;
	  *((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_FIFTH;
	  *pFA = FLASH29_CMD_SECTOR;
	   do 
        {
    	     retVal = sysFlashDataPoll16 (pFA, (UINT16) 0xffffffff);
	    } while ((*pFA != (UINT16) 0xffffffff) && (retVal == OK));
	   
    	FA+=0x2000 ;
	}
	SYS_FLASH_WRITE_DISABLE_RTN (); 	 /* disable write */

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

    do 
    {
        retVal = sysFlashDataPoll16 (pFA, (UINT16) 0xffffffff);
    } while ((*pFA != (UINT16) 0xffffffff) && (retVal == OK));

    *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
    *((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
    *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;

    SYS_FLASH_WRITE_DISABLE_RTN ();		/* disable enable */



    return (retVal);
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

    for (pFA = offset; pFA < (UINT16 *)( size + offset) && (retVal == OK); pFA++)
    {
        *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
        *((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
        *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_PROGRAM;
        value = *pFB++;

        *pFA = value;                    	/* data to write */
        do 
        {
            retVal = sysFlashDataPoll16 (pFA, (UINT16) value);
        } while ((*pFA != value) && (retVal == OK));
    }

    *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_FIRST;
    *((UINT16 *) FLASH29_REG_SECOND_CYCLE) = FLASH29_CMD_SECOND;
    *((UINT16 *) FLASH29_REG_FIRST_CYCLE)  = FLASH29_CMD_READ_RESET;

    SYS_FLASH_WRITE_DISABLE_RTN ();		/* disable write */


            


    return (retVal);
    }

	void sysFlashDelay16(int delayCount)
	{
		taskDelay(delayCount);
	}
	
	
	
	
	/***************************************************************/
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
			   
				if(sysFlashWrite16((UINT16*)sourceBak,(UINT16*)destBak,
									 ((startBlock+1)*BLOCK_SIZE_16-offset))==ERROR)
					return(ERROR);
				temp=(startBlock+1)*BLOCK_SIZE_16-offset;
				dataLen-=temp;
				offset+=temp;
				sourceBak=sourceBak+temp;
				destBak=destBak+temp;
				startBlock++;
				sysSectorErase16(destBak);
			}
			else
			{
				if(sysFlashWrite16((UINT16*)sourceBak,(UINT16*)destBak,dataLen)==ERROR)
					return(ERROR);
				else
					return(OK);
			} 
		}/*while*/	   
		return(OK);
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

