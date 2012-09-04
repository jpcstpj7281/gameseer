/* dataflashDrv.c - dataflash disk device driver */

/* Copyright 1989-1999 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01p,30jul99,jkf  fixed SPR 9729, retryRW condition loses data.
01o,11jan99,aeg  removed redundant semBInit () in dataflashInit ().
01n,03mar97,dat  fixed SPR 8084, previous edit needed tweeking.
01m,28feb97,dat  fixed SPR 8084, incorrect block number check
01l,17dec96,dat  fixed SPR 3273, incorrect block count
01k,14jun95,hdn  removed function declarations defined in sysLib.h.
01j,24jan95,jdi  doc cleanup.
01i,07dec94,rhp  man page cleanups to dataflashDrvCreate(), dataflashRawio() (SPR3734).
01h,25oct94,hdn  cleaned up dataflashRawio().
		 changed dataflashSemSec and dataflashWdSec back to 5.
01g,06oct94,hdn  changed dataflashSemSec to 10, dataflashWdSec to 10.
		 added dataflashRawio() to provdataflash physical IO.
01f,03jun94,hdn  changed DESCRIPTION, 386 to 386/486.
		 added an explanation of parameters for dataflashDevCreate().
01e,18nov93,hdn  added watchdog to check dataflashInit() in dataflashDrv().
01d,11nov93,hdn  added dataflashWait() in end of each primitive functions.
		 implemented semaphore timeout and watchdog.
01c,10nov93,hdn  separated dataflashDiagnose() from dataflashInit().
01b,04nov93,hdn  cleaned up.
01a,18oct93,hdn  written.
*/

/*
DESCRIPTION
This is the driver for the dataflash used on the PC 386/486.

USER-CALLABLE ROUTINES
Most of the routines in this driver are accessible only through the I/O
system.  However, two routines must be called directly:  dataflashDrv() to
initialize the driver, and dataflashDevCreate() to create devices.

Before the driver can be used, it must be initialized by calling dataflashDrv().
This routine should be called exactly once, before any reads, writes, or
calls to dataflashDevCreate().  Normally, it is called from usrRoot() in
usrConfig.c.

The routine dataflashRawio() provdataflashs physical I/O access.  Its first
argument is a drive number, 0 or 1; the second argument is a pointer
to an DATAFLASH_RAW structure.

NOTE
Format is not supported, because dataflash disks are already formatted, and bad
sectors are mapped.

SEE ALSO:
.pG "I/O System"
*/

#include "vxWorks.h"
#include "taskLib.h"
#include "ioLib.h"
#include "iosLib.h"
#include "memLib.h"
#include "stdlib.h"
#include "errnoLib.h"
#include "stdio.h"
#include "string.h"
#include "private/semLibP.h"
#include "intLib.h"
#include "iv.h"
#include "wdLib.h"
#include "sysLib.h"
#include "sys/fcntlcom.h"
#include "drv/dataflash/dataflashdrv.h"
#include "at91c_spi_dataflash.h"

#define AT91C_DATAFLASH_TIMEOUT				10000   /* For AT91F_DataFlashWaitReady */
//#define BUFFER_SIZE_DATAFLASH				1056
//#define MASTER_CLOCK						60000000

/* imports */

#define CFG_MAX_DATAFLASH_BANKS 2
/* global */

BOOL dataflashDebug	 = FALSE;	/* debug flag */
BOOL dataflashDebugErr = FALSE;	/* debug flag */
int  dataflashIntCount = 0;		/* interrupt count */
int  dataflashStatus	 = 0;		/* status register in interrupt level */
int  dataflashDrives	 = 0;		/* number of dataflash drives */
int  dataflashRetry	 = 3;		/* max retry count */
int  dataflashSemSec	 = 5;		/* timeout seconds for semaphore */
int  dataflashWdSec	 = 5;		/* timeout seconds for watchdog */
BOOL dataflashWaitForever = TRUE;	/* watchdog: wait forever in dataflashInit() */

//SEMAPHORE dataflashSyncSem;		/* binary semaphore for syncronization */
SEMAPHORE dataflashMuteSem;		/* mutex  semaphore for mutual-exclusion */
int cs[CFG_MAX_DATAFLASH_BANKS] = {
	AT91C_SPI_PCS0_SERIAL_DATAFLASH,	/* Logical adress, CS */
	AT91C_SPI_PCS3_DATAFLASH_CARD
};

/* local */

LOCAL BOOL dataflashDrvInstalled = FALSE;   /* TRUE = facility installed */


#include "dataflash.c"
/* function prototypes */

      void   dataflashShow	(int drive);
LOCAL STATUS dataflashBlkRd	(AT91PS_DataFlash_Device pdataflashDev, int startBlk, int nBlks, char *pBuf);
LOCAL STATUS dataflashBlkWrt	(AT91PS_DataFlash_Device pdataflashDev, int startBlk, int nBlks, char *pBuf);
LOCAL STATUS dataflashReset	(AT91PS_DataFlash_Device pdataflashDev);
LOCAL STATUS dataflashIoctl	(AT91PS_DataFlash_Device pdataflashDev, int function, int arg);
LOCAL STATUS dataflashBlkRW	(AT91PS_DataFlash_Device pdataflashDev, int startBlk, int nBlks, char *pBuf,
			 int direction);
LOCAL void   dataflashIntr	(int ctrl);
LOCAL void   dataflashWdog	(int ctrl);
LOCAL void   dataflashWait	(int request);
//LOCAL void   dataflashInit	(void);
LOCAL STATUS dataflashDiagnose(void);
LOCAL STATUS dataflashPinit	(AT91PS_DataFlash_Device pdataflashDev);
LOCAL STATUS dataflashPread	(int drive, void *buffer);
LOCAL STATUS dataflashRecalib	(int drive);
LOCAL STATUS dataflashSeek	(int drive, int cylinder, int head);
LOCAL STATUS dataflashRW	(int drive, int cylinder, int head, int sector, 
	 		 void *pBuf, int nSecs, int direction);
LOCAL STATUS dataflashFormat	(int drive, int cylinder, int head, int interleave);
LOCAL STATUS dataflashStatusChk(AT91PS_DataFlash_Device pdataflashDev);
LOCAL void AT91F_CfgDataFlash (AT91PS_DataFlash_Device pdataflashDev);
LOCAL AT91S_DataflashFeatures			DeviceAT45DCB;
LOCAL AT91S_DataflashFeatures			DeviceAT45DB;
LOCAL AT91S_DataflashDesc			DataflashDesc;
/*AT91S_DataFlash				DataFlash;*/
LOCAL AT91PS_DataFlash_Device			pDataFlash_Device=0;



LOCAL void  AT91F_SPI_CfgSPI(void)
{
    /* Reset the SPI*/
	AT91F_SPI_Reset(AT91C_BASE_SPI);

    /* Configure SPI in Master Mode with No CS selected !!! */ 
	AT91F_SPI_CfgMode(AT91C_BASE_SPI, AT91C_SPI_MSTR | AT91C_SPI_MODFDIS | AT91C_SPI_PCS);
#if 1
    /* Configure SPI CS0 for Serial DataFlash AT45DBxx*/
	AT91F_SPI_CfgCs(0, AT91C_SPI_CPOL | (AT91C_SPI_DLYBS & 0x100000) | ((MASTER_CLOCK / (2*DATAFLASH_CLK)) << 8));

    /* Configure SPI CS3 for DataFlash Card AT45DCBxx*/
	AT91F_SPI_CfgCs(3, AT91C_SPI_CPOL | (AT91C_SPI_DLYBS & 0x100000) | ((MASTER_CLOCK / (2*DATAFLASH_CLK)) << 8));
#else
	/* Configure CS0 and CS3 */
	*(AT91C_SPI_CSR + 0) = AT91C_SPI_CPOL | (AT91C_SPI_DLYBS & DATAFLASH_TCSS) | (AT91C_SPI_DLYBCT &
	DATAFLASH_TCHS) | ((MASTER_CLOCK / (2*DATAFLASH_CLK)) << 8);

	*(AT91C_SPI_CSR + 3) = AT91C_SPI_CPOL | (AT91C_SPI_DLYBS & DATAFLASH_TCSS) | (AT91C_SPI_DLYBCT &
	DATAFLASH_TCHS) | ((MASTER_CLOCK / (2*DATAFLASH_CLK)) << 8);
#endif

    /* Enable the SPI */
    
       AT91F_SPI_Enable(AT91C_BASE_SPI);
}

LOCAL void AT91F_CfgSPIForDataFlash()
{


    /* Set up PIO SDC_TYPE to switch on DataFlash Card and not MMC/SDCard*/
#if __DK__
	AT91F_PIO_CfgOutput(AT91C_BASE_PIOB,AT91C_PIO_PB7);
	AT91F_PIO_ClearOutput(AT91C_BASE_PIOB,AT91C_PIO_PB7);
#else
	AT91F_PIO_CfgOutput(AT91C_BASE_PIOB,AT91C_PIO_PB22);
	AT91F_PIO_ClearOutput(AT91C_BASE_PIOB,AT91C_PIO_PB22);
#endif	
	/* Init SPI for DataFlash interface*/
	AT91F_SPI_CfgPIO();	
	AT91F_SPI_CfgPMC();
	AT91F_SPI_CfgSPI();
	AT91F_PDC_Open(AT91C_BASE_PDC_SPI);
	
 	AT91F_CfgDataFlash(pDataFlash_Device);
	
	/* Configure SPI interrupt */
/*	AT91F_AIC_ConfigureIt(AT91C_BASE_AIC,
						 AT91C_ID_SPI,
						 AT91C_AIC_PRIOR_HIGHEST,
						 AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE,
						 AT91F_ASM_SPI_Handler);
  */
    intConnect ((VOIDFUNCPTR *)INUM_TO_IVEC (AT91C_ID_SPI),
		       (VOIDFUNCPTR)dataflashIntr, 0);

	
	/* Enable SPI interrupt*/
	//AT91F_AIC_EnableIt(AT91C_BASE_AIC,AT91C_ID_SPI);
    sysIntEnablePIC (AT91C_ID_SPI);	/* unmask the interrupt level */	
}

LOCAL AT91S_DataFlashStatus AT91F_DataFlashWaitReady(AT91PS_DataflashDesc pDataFlashDesc, unsigned int timeout);
LOCAL int  dataflashWaitReady(unsigned int timeout)
{
//return semTake (&dataflashSyncSem, timeout);
	return AT91F_DataFlashWaitReady(pDataFlash_Device->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT); 	
	
}


/*******************************************************************************
*
* dataFlashDrv - initialize the dataflash driver
*
* This routine initializes the dataflash driver, sets up interrupt vectors,
* and performs hardware initialization of the dataflash chip.
*
* This routine should be called exactly once, before any reads, writes,
* or calls to dataflashDevCreate().  Normally, it is called by usrRoot()
* in usrConfig.c.
*
* The dataflashDrv() call requires a configuration type, <manualConfig>.  If
* this argument is 1, the driver will initialize drive parameters; if
* the argument is 0, the driver will not initialize drive parameters.
*
* The drive parameters are the number of sectors per track, the number of
* heads, and the number of cylinders.  They are stored in the structure
* table `dataflashTypes[]' in sysLib.c.  The table has two entries:  the first is
* for drive 0; the second is for drive 1.  The table has two other members
* which are used by the driver: the number of bytes per sector and
* the precompensation cylinder.  These two members should be set properly.
* Definitions of the structure members are:
* .CS
*     int cylinders;              /@ number of cylinders @/
*     int heads;                  /@ number of heads @/
*     int sectorsTrack;           /@ number of sectors per track @/
*     int bytesSector;            /@ number of bytes per sector @/
*     int precomp;                /@ precompensation cylinder @/
* .CE
*
* RETURNS: OK, or ERROR if initialization fails.
*
* SEE ALSO: dataflashDevCreate()
*/

STATUS dataflashDrv
    (
    )
    {
    int drive;


    if (!dataflashDrvInstalled)
    {
//        semBInit (&dataflashSyncSem, SEM_Q_FIFO, SEM_EMPTY);

        semMInit (&dataflashMuteSem, SEM_Q_PRIORITY | SEM_DELETE_SAFE |
		SEM_INVERSION_SAFE);



	
     //   dataflashInit ();
	/*dataflashPinit (drive);*/

        

	dataflashDrvInstalled = TRUE;
    }

    return (OK);
    }

/*******************************************************************************
*
* dataflashDevCreate - create a device for a dataflash disk
*
* This routine creates a device for a specified dataflash disk.
*
* <drive> is a drive number for the hard drive: it must be 0 or 1.
*
* The <nBlocks> parameter specifies the size of the device, in blocks.
* If <nBlocks> is zero, the whole disk is used.
*
* The <blkOffset> parameter specifies an offset, in blocks, from the start
* of the device to be used when writing or reading the hard disk.  This
* offset is added to the block numbers passed by the file system during
* disk accesses.  (VxWorks file systems always use block numbers beginning
* at zero for the start of a device.)
*
*
* RETURNS:
* A pointer to a block device structure (BLK_DEV), or NULL if memory cannot
* be allocated for the device structure.
*
* SEE ALSO: dosFsMkfs(), dosFsDevInit(), rt11FsDevInit(), rt11FsMkfs(),
* rawFsDevInit()
*/
extern int __get_block_size__(int size);

LOCAL	char *databuf =0 ;
#undef __TEST__
#ifdef __TEST__
LOCAL char* gpCache=0;
#endif
BLK_DEV *dataflashDevCreate
    (
    int drive,		/* drive number for hard drive (0 or 1) */
    int nBlocks,	/* device size in blocks (0 = whole disk) */
    int blkOffset	/* offset from start of device */
    )
    {
    AT91PS_DataFlash_Device pdataflashDev;
    BLK_DEV *pBlkDev;


    if (!dataflashDrvInstalled)
	return (NULL);

    if(pDataFlash_Device)
    {
 	 if (nBlocks == 0)
	nBlocks = (pDataFlash_Device->pDevice->pages_number)
		  - blkOffset;

    	pDataFlash_Device->blkDev.bd_nBlocks = nBlocks;
   	 pDataFlash_Device->drive		= drive;
   	 pDataFlash_Device->blkOffset		= blkOffset;
	return (&pDataFlash_Device->blkDev);
    }
    if ((UINT)drive > dataflashDrives)
	return (NULL);

    if ((pdataflashDev = (AT91PS_DataFlash_Device )calloc(sizeof (AT91S_DataFlash_Device), 1)) == NULL)
	return (NULL);

    DataflashDesc.command = (char *) cacheDmaMalloc (8);
    pBlkDev = &pdataflashDev->blkDev;
    pDataFlash_Device = pdataflashDev;

    AT91F_CfgSPIForDataFlash();
 
    dataflashPinit (pdataflashDev);

    if (nBlocks == 0)
	nBlocks = (pdataflashDev->pDevice->pages_number)
		  - blkOffset;

    pBlkDev->bd_nBlocks		= nBlocks;
    pBlkDev->bd_bytesPerBlk	= __get_block_size__(pdataflashDev->pDevice->pages_size);
    pBlkDev->bd_blksPerTrack	= 1;
    pBlkDev->bd_nHeads		= 1;
    pBlkDev->bd_removable	= FALSE;
    pBlkDev->bd_retry		= 1;
    pBlkDev->bd_mode		= O_RDWR;
    pBlkDev->bd_readyChanged	= FALSE;
    pBlkDev->bd_blkRd		= dataflashBlkRd;
    pBlkDev->bd_blkWrt		= dataflashBlkWrt;
    pBlkDev->bd_ioctl		= dataflashIoctl;
    pBlkDev->bd_reset		= dataflashReset;
    pBlkDev->bd_statusChk	= dataflashStatusChk;

    pdataflashDev->drive		= drive;
    pdataflashDev->blkOffset		= blkOffset;
#ifdef __TEST__    
    gpCache = malloc(0x210*nBlocks);
#endif    
databuf =(char *) cacheDmaMalloc (1200);
    return (&pdataflashDev->blkDev);
    }

/*******************************************************************************
*
* dataflashShow - show dataflash disk parameters
*
* Show dataflash disk parameters
*
* RETURNS: N/A
*
* NOMANUAL
*/

void dataflashShow
    (
    int drive
    )
    {

    }

/*******************************************************************************
*
* dataflashRawio - provide raw I/O access
*
* This routine is called when the raw I/O access is necessary.
*
* <drive> is a drive number for the hard drive: it must be 0 or 1.
*
* The <pdataflashRaw> is a pointer to the structure DATAFLASH_RAW which is defined in 
* dataflashDrv.h
*
* RETURNS: OK or ERROR.
*
*/

STATUS dataflashRawio
    (
    int        drive,	/* drive number for hard drive (0 or 1) */
    DATAFLASH_RAW *  pdataflashRaw	/* pointer to DATAFLASH_RAW structure */
    )
    {
     BLK_DEV *pBlkDev = 0 ;//	= &dataflashDev.blkDev;
    int nBlocks = 0;
    UINT startBlk;
    STATUS err;

    if (!dataflashDrvInstalled)
	return (ERROR);

    if ((UINT)drive > dataflashDrives)
	return (ERROR);
    if(pDataFlash_Device==0 ) 
    {
	pBlkDev=dataflashDevCreate(0,0,0);
    }
    
    AT91F_CfgDataFlash(pDataFlash_Device);

    dataflashPinit(pDataFlash_Device);/*memcpy(&dataflashDev,pDataFlash_Device,sizeof(dataflashDev));*/
    
 /*   nBlocks = (pDataFlash_Device->pDevice->pages_number)
	  - 0;

    pBlkDev->bd_nBlocks		= nBlocks;


    pBlkDev->bd_bytesPerBlk	= __get_block_size__(pDataFlash_Device->pDevice->pages_size);
    pBlkDev->bd_blksPerTrack	= 1;
    pBlkDev->bd_nHeads		= 1;
    pBlkDev->bd_removable	= FALSE;
    pBlkDev->bd_retry		= 1;
    pBlkDev->bd_mode		= O_RDWR;
    pBlkDev->bd_readyChanged	= TRUE;
    pBlkDev->bd_blkRd		= dataflashBlkRd;
    pBlkDev->bd_blkWrt		= dataflashBlkWrt;
    pBlkDev->bd_ioctl		= dataflashIoctl;
    pBlkDev->bd_reset		= dataflashReset;
    pBlkDev->bd_statusChk	= NULL;

    pDataFlash_Device->drive		= drive;
    pDataFlash_Device->blkOffset	= 0;
*/
    startBlk = 0;
	AT91F_DataFlashWaitReady(pDataFlash_Device->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);
    err= (dataflashBlkRW (pDataFlash_Device, startBlk, pdataflashRaw->nSecs, pdataflashRaw->pBuf,
		     pdataflashRaw->direction));
   
     return err;
    }

/*******************************************************************************
*
* dataflashBlkRd - read one or more blocks from a dataflash disk
*
* This routine reads one or more blocks from the specified device,
* starting with the specified block number.
*
* If any block offset was specified during dataflashDevCreate(), it is added
* to <startBlk> before the transfer takes place.
*
* RETURNS: OK, ERROR if the read command didn't succeed.
*/

LOCAL STATUS dataflashBlkRd
    (
    AT91PS_DataFlash_Device pdataflashDev,
    int startBlk,
    int nBlks,
    char *pBuf
    )
    {
    return (dataflashBlkRW (pdataflashDev, startBlk, nBlks, pBuf, O_RDONLY));
    }

/*******************************************************************************
*
* dataflashBlkWrt - write one or more blocks to a dataflash disk
*
* This routine writes one or more blocks to the specified device,
* starting with the specified block number.
*
* If any block offset was specified during dataflashDevCreate(), it is added
* to <startBlk> before the transfer takes place.
*
* RETURNS: OK, ERROR if the write command didn't succeed.
*/

LOCAL STATUS dataflashBlkWrt
    (
    AT91PS_DataFlash_Device pdataflashDev,
    int startBlk,
    int nBlks,
    char *pBuf
    )
    {
    return (dataflashBlkRW (pdataflashDev, startBlk, nBlks, pBuf, O_WRONLY));
    }

/*******************************************************************************
*
* dataflashReset - reset a dataflash disk controller
*
* This routine resets a dataflash disk controller.
*
* RETURNS: OK, always.
*/

LOCAL STATUS dataflashReset
    (
    AT91PS_DataFlash_Device pdataflashDev
    )
    {
    
    semTake (&dataflashMuteSem, WAIT_FOREVER);

 /*  dataflashInit ();*/

    semGive (&dataflashMuteSem);

    return (OK);
    }

/*******************************************************************************
*
* dataflashIoctl - do device specific control function
*
* This routine is called when the file system cannot handle an ioctl()
* function.
*
* RETURNS:  OK or ERROR.
*/

LOCAL STATUS dataflashIoctl
    (
    AT91PS_DataFlash_Device pdataflashDev,
    int function,
    int arg
    )
    {
    FAST int status = ERROR;

    semTake (&dataflashMuteSem, WAIT_FOREVER);

    switch (function)
	{
	case FIODISKFORMAT:

	    status = OK;
	    break;

	default:
	    (void) errnoSet (S_ioLib_UNKNOWN_REQUEST);
	}

doneIoctl:
    semGive (&dataflashMuteSem);
    return (status);
    }

/*******************************************************************************
*
* dataflashBlkRW - read or write sectors to a dataflash disk.
*
* Read or write sectors to a dataflash disk.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS dataflashBlkRW
    (
    AT91PS_DataFlash_Device pDev,
    int startBlk,
    int nBlks,
    char *pBuf,
    int direction
    )
    {
    BLK_DEV *pBlkDev = &pDev->blkDev;
    int src,ix ; 
    int status = ERROR;
    int semStatus = 0;

    int Max_Read_DataBlock_Length = pDev->pDevice->pages_size;
    startBlk+=pDev->blkOffset;
    src = startBlk* Max_Read_DataBlock_Length;
    semTake (&dataflashMuteSem, WAIT_FOREVER);
	memset(databuf,0,1200);
if(direction==O_RDONLY)
{
    for (ix = 0; ix < nBlks; ix ++)
    {
	AT91F_DataFlashWaitReady(pDev->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);
	AT91F_DataFlashPageRead(pDev,src,databuf,Max_Read_DataBlock_Length);
	semStatus = dataflashWaitReady(AT91C_DATAFLASH_TIMEOUT*1000);
	if ((dataflashStatus & STAT_ERR) || (semStatus == ERROR))
        goto errorRW;
/*	AT91F_DataFlashRead(pDev,src,Max_Read_DataBlock_Length,databuf);
	semStatus = OK;
*/
	memcpy(pBuf,databuf, pBlkDev->bd_bytesPerBlk);        

#ifdef __TEST__
	if(memcmp(pBuf,gpCache+src, pBlkDev->bd_bytesPerBlk)!=0)
	{
		fprintf(stderr,"not the same \n");
	}
#endif	
        src += Max_Read_DataBlock_Length ;
        pBuf += pBlkDev->bd_bytesPerBlk;/*Max_Read_DataBlock_Length;*/
    }
}else
{
    for (ix = 0; ix < nBlks; ix ++)
    {
#ifdef __TEST__
		memcpy(gpCache+src,pBuf,pBlkDev->bd_bytesPerBlk);		        
#endif	
	    memcpy(databuf,pBuf,pBlkDev->bd_bytesPerBlk);
	    if(AT91F_DataFlashWaitReady(pDev->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT)==DATAFLASH_OK)    
		{
		AT91F_DataFlashPagePgmBuf(pDev,(unsigned char*)databuf,(src),(Max_Read_DataBlock_Length) );
		semStatus = dataflashWaitReady(AT91C_DATAFLASH_TIMEOUT*1000);
		if ((dataflashStatus & STAT_ERR) || (semStatus == ERROR))
	        goto errorRW; 
	    }else goto errorRW; 
/*		AT91F_DataFlashWrite(pDev , (unsigned int*) databuf ,src,Max_Read_DataBlock_Length);
		semStatus =OK;
*/
	        
#ifdef __TEST__	 
		AT91F_DataFlashWaitReady(pDev->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);       
		AT91F_DataFlashPageRead(pDev,src,databuf,Max_Read_DataBlock_Length);
		semStatus = dataflashWaitReady(AT91C_DATAFLASH_TIMEOUT*1000);
		if ((dataflashStatus & STAT_ERR) || (semStatus == ERROR))
        	goto errorRW;
		//AT91F_DataFlashWaitReady(pDev->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);               	
		/*AT91F_DataFlashRead(pDev,src,Max_Read_DataBlock_Length,databuf);*/
		if(0!=memcmp(databuf,pBuf,pBlkDev->bd_bytesPerBlk))
		{
			fprintf(stderr,"write dataflash error \n");	
		}        
        
#endif        
        src += Max_Read_DataBlock_Length ;
        pBuf += pBlkDev->bd_bytesPerBlk; /*Max_Read_DataBlock_Length;*/
     }
}
    status = OK;

errorRW:
    if (status == ERROR)
        (void)errnoSet (S_ioLib_DEVICE_ERROR);
    semGive (&dataflashMuteSem);
    return (status);
    }

/*******************************************************************************
*
* dataflashIntr - dataflash controller interrupt handler.
*
* RETURNS: N/A
*/

LOCAL void dataflashIntr
    (
    int ctrl
    )
    {

dataflashStatus = ( AT91C_BASE_SPI->SPI_SR & AT91C_BASE_SPI->SPI_IMR );

AT91F_DataFlashHandler(pDataFlash_Device->pDataFlashDesc,dataflashStatus);
//semGive (&dataflashSyncSem);

  }

/*******************************************************************************
*
* dataflashIntr - dataflash controller watchdog handler.
*
* RETURNS: N/A
*/

LOCAL void dataflashWdog
    (
    int ctrl
    )
    {
    dataflashWaitForever = FALSE;
    }

/*******************************************************************************
*
* dataflashWait - wait the drive ready
*
* Wait the drive ready
*
* RETURNS: OK, ERROR if the drive didn't become ready in certain period of time.
*/

LOCAL void dataflashWait
    (
    int request
    )
    {
	dataflashWaitReady(AT91C_DATAFLASH_TIMEOUT);
	

    if (dataflashDebug)
	printErr ("dataflashWait end: \n");
    }


/*******************************************************************************
*
* dataflashDiagnose - diagnose the drive
*
* Diagnose the drive
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS dataflashDiagnose (void)
    {

    return (OK);
    }

/*******************************************************************************
*
* dataflashPinit - Initialize drive parameters
*
* Initialize drive parameters.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/
void AT91F_CfgDataFlash (AT91PS_DataFlash_Device pdataflashDev)
{
	/* Init AT91S_DataflashFeatures Structure for AT45DB642*/
	DeviceAT45DB.pages_number = 8192;
	DeviceAT45DB.pages_size   = 1056;
	DeviceAT45DB.page_offset  = 11;
	DeviceAT45DB.byte_mask    = 0x700;	

	/* Init AT91S_DataflashFeatures Structure for AT45DCB004 <=> AT45DB321B*/
	DeviceAT45DCB.pages_number = 8192;
	DeviceAT45DCB.pages_size   = 528;
	DeviceAT45DCB.page_offset  = 11; /*10*/
	DeviceAT45DCB.byte_mask    = 0x300;
	
	/* Init AT91S_DataflashFeatures Structure for AT45DCB002 <=> AT45DB161B*/
/*	DeviceAT45DCB.pages_number = 4096;
	DeviceAT45DCB.pages_size   = 528;
	DeviceAT45DCB.page_offset  = 10;
	DeviceAT45DCB.byte_mask    = 0x300;	*/
	
	/* Init AT91S_DataflashDesc Structure*/
	DataflashDesc.state             = IDLE;
	DataflashDesc.DataFlash_state   = IDLE;

	/* Init AT91S_DataFlash Global Structure, by default AT45DB choosen !!!*/
	pdataflashDev->pDataFlashDesc = &DataflashDesc;
	pdataflashDev->pDevice 		= &DeviceAT45DB ;//&DeviceAT45DCB;
}


/*----------------------------------------------------------------------------	*/
/* \fn    AT91F_DataFlashWaitReady						*/
/* \brief wait for dataflash ready (bit7 of the status register == 1)		*/	
/*----------------------------------------------------------------------------  */
AT91S_DataFlashStatus AT91F_DataFlashWaitReady(AT91PS_DataflashDesc pDataFlashDesc, unsigned int timeout)
{
	unsigned int i;

	pDataFlashDesc->DataFlash_state = IDLE;	

	do
	{
		AT91F_DataFlashGetStatus(pDataFlashDesc);
		timeout--;
		/* dummy waiting time*/
		for(i=0;i<10;i++);
	}
	while( ((pDataFlashDesc->DataFlash_state & 0x80) != 0x80) && (timeout>0) );

	if((pDataFlashDesc->DataFlash_state & 0x80) != 0x80)
		return DATAFLASH_ERROR;
		
	return DATAFLASH_OK;
}

#define BUFFER_SIZE_DATAFLASH  1200
void AT91F_Test(AT91PS_DataFlash_Device pDF)
{
	int i;
	int sect=0;
	char Buffer_Dataflash[BUFFER_SIZE_DATAFLASH];
	//* Wait DataFlash Ready
	AT91F_DataFlashWaitReady(pDF->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);
	
	

	//* Read Page 1
	for(i=0;i<BUFFER_SIZE_DATAFLASH;i++) 	Buffer_Dataflash[i] = 0x00;	
	AT91F_DataFlashPageRead(pDF,(sect*pDF->pDevice->pages_size),(unsigned char*)Buffer_Dataflash,(pDF->pDevice->pages_size) );

	//* Wait end of Read
	AT91F_DataFlashWaitReady(pDF->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);

	//* Write Page 1
        sprintf(Buffer_Dataflash,"\n\rI am Snow, I want to write to dataflash\n");
	AT91F_DataFlashPagePgmBuf(pDF,(unsigned char*)Buffer_Dataflash,(sect*pDF->pDevice->pages_size),(pDF->pDevice->pages_size) );

	//* Wait end of Write
	AT91F_DataFlashWaitReady(pDF->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);

	//* Read Page 1
	for(i=0;i<BUFFER_SIZE_DATAFLASH;i++) 	Buffer_Dataflash[i] = 0x00;	
	AT91F_DataFlashPageRead(pDF,(sect*pDF->pDevice->pages_size),(unsigned char*)Buffer_Dataflash,(pDF->pDevice->pages_size) );

	//* Wait end of Read
	AT91F_DataFlashWaitReady(pDF->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);


}

LOCAL STATUS dataflashPinit
    (
AT91PS_DataFlash_Device pDF
    )
    {
	/******************************/
	/** For dataflash Init*/
	/******************************/
	
	volatile int status;
	int i;
	int timeout = AT91C_DATAFLASH_TIMEOUT ; 
	unsigned char dfcode=0;
	AT91PS_DataflashDesc pDesc= pDF->pDataFlashDesc;
	for (i = 0; i < CFG_MAX_DATAFLASH_BANKS; i++) {
		AT91F_SPI_CfgPCS(AT91C_BASE_SPI,cs[i]);	
//		AT91F_DataFlashGetStatus(pDesc);
		AT91F_DataFlashWaitReady(pDesc,AT91C_DATAFLASH_TIMEOUT);
		dfcode = ((pDesc->command[1] == 0xFF)? 0: pDesc->command[1] & 0x3C);
		switch (dfcode) {
		case AT45DB161:
			pDF->pDevice = &DeviceAT45DCB;
			break;

		case AT45DB321:
			pDF->pDevice = &DeviceAT45DCB;
			break;

		case AT45DB642:
			pDF->pDevice = &DeviceAT45DB;
			break;
		case AT45DB128:
			pDF->pDevice = &DeviceAT45DB;
			break;

		default:
			break;
		}
	}	

//	AT91F_SPI_CfgPCS(AT91C_BASE_SPI,AT91C_SPI_PCS3_DATAFLASH_CARD);
//	pDF->pDevice = &DeviceAT45DCB;

	/* Wait DataFlash Ready*/
//	AT91F_DataFlashWaitReady(pDF->pDataFlashDesc,AT91C_DATAFLASH_TIMEOUT);
	
//AT91F_Test(pDF);
    return (OK);
    }

/*******************************************************************************
*
* dataflashPread - Read drive parameters
*
* Read drive parameters.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS dataflashPread
    (
    int drive,
    void *buffer
    )
    {
 

    return (OK);
    }
/*******************************************************************************
*
* dataflashRecalib - recalibrate the drive
*
* Recalibrate the drive
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS dataflashRecalib
    (
    int drive
    )
    {
 
    return (OK);
    }

/*******************************************************************************
*
* dataflashSeek - seek the drive heads to the specified cylinder
*
* Seek the drive heads to the specified cylinder
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS dataflashSeek(int drive, int cylinder, int head)
{

 
    return (OK);
    }

/*******************************************************************************
*
* dataflashRW - read/write a number of sectors on the current track
*
* Read/write a number of sectors on the current track
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/



/*******************************************************************************
*
* dataflashFormat - format the current track
*
* format the current track; not supported.
*
* RETURNS: ERROR always.
*/

LOCAL STATUS dataflashFormat
    (
    int drive,
    int cylinder,
    int head,
    int interleave
    )
    {
    return (ERROR);
    }


/*******************************************************************************
*
* fdStatusChk - check a status of a floppy disk
*
* This routine checks for a disk change on devices.
*
* RETURNS: OK.
*/

LOCAL STATUS dataflashStatusChk
    (
    AT91PS_DataFlash_Device pdataflashDev
    )
    {
/* pdataflashDev->blkDev.bd_readyChanged	= TRUE;*/
 pdataflashDev->blkDev.bd_mode = O_RDWR;
 #if 0
    FD_TYPE *pType = &fdTypes[pFdDev->fdType];

    wdCancel (fdWid);
    semTake (&fdMuteSem, WAIT_FOREVER);

    sysOutByte (FD_REG_OUTPUT, fdDORvalues[pFdDev->drive]); 
    sysDelay ();

    /* 
     * Bit 7 is set when a diskette is changed.
     * To clear the bit, we need to perform a seek.  
     */

    if (sysInByte (FD_REG_INPUT) & 0x80)
	{
	pFdDev->blkDev.bd_readyChanged	= TRUE;

	/* do seek to clear DCHG bit in FD_REG_INPUT */

	if (++fdCylinder >= pType->cylinders)
	    fdCylinder = 1;

        fdDriveSelect (pFdDev->fdType, pFdDev->drive);
	(void) fdSeek(pFdDev->drive, fdCylinder, 0);

        /* set the bd_mode per the WP tab */

        pFdDev->blkDev.bd_mode =
			(fdDriveIsWP(pFdDev->drive))? O_RDONLY : O_RDWR;
	}
    
    semGive (&fdMuteSem);
    wdStart (fdWid, (sysClkRateGet() * fdWdSec), 
		(FUNCPTR)fdDriveRelease, 0);
#endif		
    return (OK);
    }























