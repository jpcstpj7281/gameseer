/* mmcDrv.c - MMC disk device driver */

/* Copyright 1989-1999 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01p,30jul99,jkf  fixed SPR 9729, retryRW condition loses data.
01o,11jan99,aeg  removed redundant semBInit () in mmcInit ().
01n,03mar97,dat  fixed SPR 8084, previous edit needed tweeking.
01m,28feb97,dat  fixed SPR 8084, incorrect block number check
01l,17dec96,dat  fixed SPR 3273, incorrect block count
01k,14jun95,hdn  removed function declarations defined in sysLib.h.
01j,24jan95,jdi  doc cleanup.
01i,07dec94,rhp  man page cleanups to mmcDrvCreate(), mmcRawio() (SPR3734).
01h,25oct94,hdn  cleaned up mmcRawio().
		 changed mmcSemSec and mmcWdSec back to 5.
01g,06oct94,hdn  changed mmcSemSec to 10, mmcWdSec to 10.
		 added mmcRawio() to provmmc physical IO.
01f,03jun94,hdn  changed DESCRIPTION, 386 to 386/486.
		 added an explanation of parameters for mmcDevCreate().
01e,18nov93,hdn  added watchdog to check mmcInit() in mmcDrv().
01d,11nov93,hdn  added mmcWait() in end of each primitive functions.
		 implemented semaphore timeout and watchdog.
01c,10nov93,hdn  separated mmcDiagnose() from mmcInit().
01b,04nov93,hdn  cleaned up.
01a,18oct93,hdn  written.
*/

/*
DESCRIPTION
This is the driver for the mmc used on the PC 386/486.

USER-CALLABLE ROUTINES
Most of the routines in this driver are accessible only through the I/O
system.  However, two routines must be called directly:  mmcDrv() to
initialize the driver, and mmcDevCreate() to create devices.

Before the driver can be used, it must be initialized by calling mmcDrv().
This routine should be called exactly once, before any reads, writes, or
calls to mmcDevCreate().  Normally, it is called from usrRoot() in
usrConfig.c.

The routine mmcRawio() provmmcs physical I/O access.  Its first
argument is a drive number, 0 or 1; the second argument is a pointer
to an MMC_RAW structure.

NOTE
Format is not supported, because mmc disks are already formatted, and bad
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
#include "drv/mmc/mmcdrv.h"

#define AT91C_MCI_TIMEOUT			1000000   /* For AT91F_MCmmcviceWaitReady */
//#define BUFFER_SIZE_MCI_DEVICE		512
//#define MASTER_CLOCK				60000000
	

/* imports */


/* global */

BOOL mmcDebug	 = FALSE;	/* debug flag */
BOOL mmcDebugErr = FALSE;	/* debug flag */
int  mmcIntCount = 0;		/* interrupt count */
int  mmcStatus	 = 0;		/* status register in interrupt level */
int  mmcDrives	 = 0;		/* number of mmc drives */
int  mmcRetry	 = 3;		/* max retry count */
int  mmcSemSec	 = 5;		/* timeout seconds for semaphore */
int  mmcWdSec	 = 5;		/* timeout seconds for watchdog */
BOOL mmcWaitForever = TRUE;	/* watchdog: wait forever in mmcInit() */

SEMAPHORE mmcSyncSem;		/* binary semaphore for syncronization */
SEMAPHORE mmcMuteSem;		/* mutex  semaphore for mutual-exclusion */


/* local */

LOCAL BOOL mmcDrvInstalled = FALSE;   /* TRUE = facility installed */

#include "mci_device.c"
/* function prototypes */

      void   mmcShow	(int drive);
LOCAL STATUS mmcBlkRd	(AT91PS_MciDevice pmmcDev, int startBlk, int nBlks, char *pBuf);
LOCAL STATUS mmcBlkWrt	(AT91PS_MciDevice pmmcDev, int startBlk, int nBlks, char *pBuf);
LOCAL STATUS mmcReset	(AT91PS_MciDevice pmmcDev);
LOCAL STATUS mmcIoctl	(AT91PS_MciDevice pmmcDev, int function, int arg);
LOCAL STATUS mmcBlkRW	(AT91PS_MciDevice pmmcDev, int startBlk, int nBlks, char *pBuf,
			 int direction);
LOCAL void   mmcIntr	(int ctrl);
LOCAL void   mmcWdog	(int ctrl);
LOCAL void   mmcWait	(int request);
LOCAL void   mmcInit	(void);
LOCAL STATUS mmcDiagnose(void);
LOCAL STATUS mmcPinit	(AT91PS_MciDevice pmmcDev);
LOCAL STATUS mmcPread	(int drive, void *buffer);
LOCAL STATUS mmcRecalib	(int drive);
LOCAL STATUS mmcSeek	(int drive, int cylinder, int head);
LOCAL STATUS mmcRW	(int drive, int cylinder, int head, int sector, 
	 		 void *pBuf, int nSecs, int direction);
LOCAL STATUS mmcFormat	(int drive, int cylinder, int head, int interleave);
LOCAL STATUS mmcStatusChk(AT91PS_MciDevice pmmcDev);

LOCAL AT91S_MciDeviceFeatures			MCI_Device_Features;
LOCAL  AT91S_MciDeviceDesc			MCI_Device_Desc;
LOCAL AT91S_MciDevice *				pMCI_Device=0;
LOCAL int  AT91F_MCmmcviceWaitReady(unsigned int timeout)
{
	return semTake (&mmcSyncSem, timeout);
	
	
}


/*******************************************************************************
*
* mmcDrv - initialize the mmc driver
*
* This routine initializes the mmc driver, sets up interrupt vectors,
* and performs hardware initialization of the mmc chip.
*
* This routine should be called exactly once, before any reads, writes,
* or calls to mmcDevCreate().  Normally, it is called by usrRoot()
* in usrConfig.c.
*
* The mmcDrv() call requires a configuration type, <manualConfig>.  If
* this argument is 1, the driver will initialize drive parameters; if
* the argument is 0, the driver will not initialize drive parameters.
*
* The drive parameters are the number of sectors per track, the number of
* heads, and the number of cylinders.  They are stored in the structure
* table `mmcTypes[]' in sysLib.c.  The table has two entries:  the first is
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
* SEE ALSO: mmcDevCreate()
*/

STATUS mmcDrv
    (
    )
    {
    int drive;


    if (!mmcDrvInstalled)
    {
        semBInit (&mmcSyncSem, SEM_Q_FIFO, SEM_EMPTY);

        semMInit (&mmcMuteSem, SEM_Q_PRIORITY | SEM_DELETE_SAFE |
		SEM_INVERSION_SAFE);

        (void) intConnect ((VOIDFUNCPTR *)INUM_TO_IVEC (AT91C_ID_MCI),
		       (VOIDFUNCPTR)mmcIntr, 0);

	

        sysIntEnablePIC (AT91C_ID_MCI);	/* unmask the interrupt level */

	
        mmcInit ();
	/*mmcPinit (drive);*/

        

	mmcDrvInstalled = TRUE;
    }

    return (OK);
    }

/*******************************************************************************
*
* mmcDevCreate - create a device for a mmc disk
*
* This routine creates a device for a specified mmc disk.
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


BLK_DEV *mmcDevCreate
    (
    int drive,		/* drive number for hard drive (0 or 1) */
    int nBlocks,	/* device size in blocks (0 = whole disk) */
    int blkOffset	/* offset from start of device */
    )
    {
    AT91PS_MciDevice pmmcDev;
    BLK_DEV *pBlkDev;


    if (!mmcDrvInstalled)
	return (NULL);

    if ((UINT)drive > mmcDrives)
	return (NULL);

    if ((pmmcDev = (AT91PS_MciDevice )calloc(sizeof (AT91PS_MciDevice), 1)) == NULL)
	return (NULL);

   
    pBlkDev = &pmmcDev->blkDev;
    mmcPinit (pmmcDev);
    pMCI_Device = pmmcDev;
    if (nBlocks == 0)
	nBlocks = (pmmcDev->pMCI_DeviceFeatures->Memory_Capacity/pmmcDev->pMCI_DeviceFeatures[0].Max_Read_DataBlock_Length)
		  - blkOffset;

    pBlkDev->bd_nBlocks		= nBlocks;
    pBlkDev->bd_bytesPerBlk	= pmmcDev->pMCI_DeviceFeatures[0].Max_Read_DataBlock_Length;
    pBlkDev->bd_blksPerTrack	= 1;
    pBlkDev->bd_nHeads		= 1;
    pBlkDev->bd_removable	= FALSE;
    pBlkDev->bd_retry		= 1;
    pBlkDev->bd_mode		= O_RDWR;
    pBlkDev->bd_readyChanged	= FALSE;
    pBlkDev->bd_blkRd		= mmcBlkRd;
    pBlkDev->bd_blkWrt		= mmcBlkWrt;
    pBlkDev->bd_ioctl		= mmcIoctl;
    pBlkDev->bd_reset		= mmcReset;
    pBlkDev->bd_statusChk	= NULL;

    pmmcDev->drive		= drive;
    pmmcDev->blkOffset		= blkOffset;

    return (&pmmcDev->blkDev);
    }

/*******************************************************************************
*
* mmcShow - show mmc disk parameters
*
* Show mmc disk parameters
*
* RETURNS: N/A
*
* NOMANUAL
*/

void mmcShow
    (
    int drive
    )
    {

    }

/*******************************************************************************
*
* mmcRawio - provide raw I/O access
*
* This routine is called when the raw I/O access is necessary.
*
* <drive> is a drive number for the hard drive: it must be 0 or 1.
*
* The <pmmcRaw> is a pointer to the structure MMC_RAW which is defined in 
* mmcDrv.h
*
* RETURNS: OK or ERROR.
*
*/

STATUS mmcRawio
    (
    int        drive,	/* drive number for hard drive (0 or 1) */
    MMC_RAW *  pmmcRaw	/* pointer to MMC_RAW structure */
    )
    {
    AT91S_MciDevice mmcDev;
    BLK_DEV *pBlkDev	= &mmcDev.blkDev;
    int nBlocks = 0;
    UINT startBlk;

    if (!mmcDrvInstalled)
	return (ERROR);

    if ((UINT)drive > mmcDrives)
	return (ERROR);

    memcpy(&mmcDev,pMCI_Device,sizeof(mmcDev));
    
    nBlocks = (mmcDev.pMCI_DeviceFeatures->Memory_Capacity/mmcDev.pMCI_DeviceFeatures[0].Max_Read_DataBlock_Length)
	  - 0;

    pBlkDev->bd_nBlocks		= nBlocks;


    pBlkDev->bd_bytesPerBlk	= mmcDev.pMCI_DeviceFeatures[0].Max_Read_DataBlock_Length;
    pBlkDev->bd_blksPerTrack	= 1;
    pBlkDev->bd_nHeads		= 1;
    pBlkDev->bd_removable	= FALSE;
    pBlkDev->bd_retry		= 1;
    pBlkDev->bd_mode		= O_RDWR;
    pBlkDev->bd_readyChanged	= TRUE;
    pBlkDev->bd_blkRd		= mmcBlkRd;
    pBlkDev->bd_blkWrt		= mmcBlkWrt;
    pBlkDev->bd_ioctl		= mmcIoctl;
    pBlkDev->bd_reset		= mmcReset;
    pBlkDev->bd_statusChk	= NULL;

    mmcDev.drive		= drive;
    mmcDev.blkOffset		= 0;

    startBlk = 0;

    return (mmcBlkRW (&mmcDev, startBlk, pmmcRaw->nSecs, pmmcRaw->pBuf,
		     pmmcRaw->direction));
   
     return ERROR;
    }

/*******************************************************************************
*
* mmcBlkRd - read one or more blocks from a mmc disk
*
* This routine reads one or more blocks from the specified device,
* starting with the specified block number.
*
* If any block offset was specified during mmcDevCreate(), it is added
* to <startBlk> before the transfer takes place.
*
* RETURNS: OK, ERROR if the read command didn't succeed.
*/

LOCAL STATUS mmcBlkRd
    (
    AT91PS_MciDevice pmmcDev,
    int startBlk,
    int nBlks,
    char *pBuf
    )
    {
    return (mmcBlkRW (pmmcDev, startBlk, nBlks, pBuf, O_RDONLY));
    }

/*******************************************************************************
*
* mmcBlkWrt - write one or more blocks to a mmc disk
*
* This routine writes one or more blocks to the specified device,
* starting with the specified block number.
*
* If any block offset was specified during mmcDevCreate(), it is added
* to <startBlk> before the transfer takes place.
*
* RETURNS: OK, ERROR if the write command didn't succeed.
*/

LOCAL STATUS mmcBlkWrt
    (
    AT91PS_MciDevice pmmcDev,
    int startBlk,
    int nBlks,
    char *pBuf
    )
    {
    return (mmcBlkRW (pmmcDev, startBlk, nBlks, pBuf, O_WRONLY));
    }

/*******************************************************************************
*
* mmcReset - reset a mmc disk controller
*
* This routine resets a mmc disk controller.
*
* RETURNS: OK, always.
*/

LOCAL STATUS mmcReset
    (
    AT91PS_MciDevice pmmcDev
    )
    {
    
    semTake (&mmcMuteSem, WAIT_FOREVER);

   /*   mmcInit ();*/

    semGive (&mmcMuteSem);

    return (OK);
    }

/*******************************************************************************
*
* mmcIoctl - do device specific control function
*
* This routine is called when the file system cannot handle an ioctl()
* function.
*
* RETURNS:  OK or ERROR.
*/

LOCAL STATUS mmcIoctl
    (
    AT91PS_MciDevice pmmcDev,
    int function,
    int arg
    )
    {
    FAST int status = ERROR;

    semTake (&mmcMuteSem, WAIT_FOREVER);

    switch (function)
	{
	case FIODISKFORMAT:

	    status = OK;
	    break;

	default:
	    (void) errnoSet (S_ioLib_UNKNOWN_REQUEST);
	}

doneIoctl:
    semGive (&mmcMuteSem);
    return (status);
    }

/*******************************************************************************
*
* mmcBlkRW - read or write sectors to a mmc disk.
*
* Read or write sectors to a mmc disk.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS mmcBlkRW
    (
    AT91PS_MciDevice pMCI_Device,
    int startBlk,
    int nBlks,
    char *pBuf,
    int direction
    )
    {
    BLK_DEV *pBlkDev = &pMCI_Device->blkDev;
    int src,ix ; 
    int status = ERROR;
    int semStatus = 0;
    char databuf[1200];
    int Max_Read_DataBlock_Length = pMCI_Device->pMCI_DeviceFeatures->Max_Read_DataBlock_Length;
    startBlk+=pMCI_Device->blkOffset;

    src = startBlk* Max_Read_DataBlock_Length;
    semTake (&mmcMuteSem, WAIT_FOREVER);
	memset(databuf,0,1200);
if(direction==O_RDONLY)
{
    for (ix = 0; ix < nBlks; ix ++)
    {

	
	/* ReadBlock & WriteBlock Test -> Entire Block
	 Wait MCI Device Ready */
	
	
	AT91F_MCI_ReadBlock(pMCI_Device,src,(unsigned int*)pBuf,Max_Read_DataBlock_Length);
	semStatus = AT91F_MCmmcviceWaitReady(AT91C_MCI_TIMEOUT);
	if ((mmcStatus & STAT_ERR) || (semStatus == ERROR))
	        goto errorRW;
        src += Max_Read_DataBlock_Length ;
        pBuf += pBlkDev->bd_bytesPerBlk;
    }
}else
{
    for (ix = 0; ix < nBlks; ix ++)
    {
    memcpy(databuf,pBuf,pBlkDev->bd_bytesPerBlk);	
	AT91F_MCI_WriteBlock(pMCI_Device,(src),(unsigned int*) pBuf,Max_Read_DataBlock_Length);
	semStatus = AT91F_MCmmcviceWaitReady(AT91C_MCI_TIMEOUT);
	if ((mmcStatus & STAT_ERR) || (semStatus == ERROR))
	        goto errorRW;

        src += Max_Read_DataBlock_Length ;
        pBuf += pBlkDev->bd_bytesPerBlk;
     }
}
    status = OK;

errorRW:
    if (status == ERROR)
        (void)errnoSet (S_ioLib_DEVICE_ERROR);
    semGive (&mmcMuteSem);
    return (status);
    }

/*******************************************************************************
*
* mmcIntr - mmc controller interrupt handler.
*
* RETURNS: N/A
*/

LOCAL void mmcIntr
    (
    int ctrl
    )
    {


mmcStatus = ( AT91C_BASE_MCI->MCI_SR & AT91C_BASE_MCI->MCI_IMR );

AT91F_MCI_Device_Handler(pMCI_Device,mmcStatus);
semGive (&mmcSyncSem);

  }

/*******************************************************************************
*
* mmcIntr - mmc controller watchdog handler.
*
* RETURNS: N/A
*/

LOCAL void mmcWdog
    (
    int ctrl
    )
    {
    mmcWaitForever = FALSE;
    }

/*******************************************************************************
*
* mmcWait - wait the drive ready
*
* Wait the drive ready
*
* RETURNS: OK, ERROR if the drive didn't become ready in certain period of time.
*/

LOCAL void mmcWait
    (
    int request
    )
    {
	AT91F_MCmmcviceWaitReady(AT91C_MCI_TIMEOUT);
	

    if (mmcDebug)
	printErr ("mmcWait end: \n");
    }

/*******************************************************************************
*
* mmcInit - init a mmc disk controller
*
* This routine initializes a mmc disk controller.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL void mmcInit (void)
    {
    /* Set up PIO SDC_TYPE to switch on MMC/SDCard and not DataFlash Card*/
#ifdef __DK__    
	AT91F_PIO_CfgOutput(AT91C_BASE_PIOB,AT91C_PIO_PB7);
	AT91F_PIO_SetOutput(AT91C_BASE_PIOB,AT91C_PIO_PB7);
#else
	AT91F_PIO_CfgOutput(AT91C_BASE_PIOB,AT91C_PIO_PB22);
	AT91F_PIO_SetOutput(AT91C_BASE_PIOB,AT91C_PIO_PB22);
#endif	
	/* Init MCI for MMC and SDCard interface*/
	AT91F_MCI_CfgPIO();	
	AT91F_MCI_CfgPMC();
	AT91F_PDC_Open(AT91C_BASE_PDC_MCI);

    /* Disable all the interrupts*/
    AT91C_BASE_MCI->MCI_IDR = 0xFFFFFFFF;

	/* Init MCI Device Structures*/
	/*AT91F_CfgDevice();*/

	/* Configure MCI interrupt */
/*	AT91F_AIC_ConfigureIt(AT91C_BASE_AIC,
						 AT91C_ID_MCI,
						 AT91C_AIC_PRIOR_HIGHEST,
						 AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE,
						 AT91F_ASM_MCI_Handler);
*/
	/* Enable MCI interrupt*/
	AT91F_AIC_EnableIt(AT91C_BASE_AIC,AT91C_ID_MCI);
    if (mmcDebug)
	printErr ("mmcInit end: \n");
    }

/*******************************************************************************
*
* mmcDiagnose - diagnose the drive
*
* Diagnose the drive
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS mmcDiagnose (void)
    {

    return (OK);
    }

/*******************************************************************************
*
* mmcPinit - Initialize drive parameters
*
* Initialize drive parameters.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/
void AT91F_CfgDevice(AT91PS_MciDevice pmmcDev)
{
	/* Init Device Structure*/

	MCI_Device_Features.Relative_Card_Address 		= 0;
	MCI_Device_Features.Card_Inserted 				= AT91C_CARD_REMOVED;
	MCI_Device_Features.Max_Read_DataBlock_Length	= 0;
	MCI_Device_Features.Max_Write_DataBlock_Length 	= 0;
	MCI_Device_Features.Read_Partial 				= 0;
	MCI_Device_Features.Write_Partial 				= 0;
	MCI_Device_Features.Erase_Block_Enable 			= 0;
	MCI_Device_Features.Sector_Size 				= 0;
	MCI_Device_Features.Memory_Capacity 			= 0;
	
	MCI_Device_Desc.state							= AT91C_MCI_IDLE;
	MCI_Device_Desc.SDCard_bus_width				= AT91C_MCI_SCDBUS;
	
	/* Init AT91S_DataFlash Global Structure, by default AT45DB choosen !!!*/
	pmmcDev->pMCI_DeviceDesc 		= &MCI_Device_Desc;
	pmmcDev->pMCI_DeviceFeatures 	= &MCI_Device_Features;

}
LOCAL STATUS mmcPinit
    (
AT91PS_MciDevice pmmcDev
    )
    {
	/******************************/
	/** For MMC Init*/
	/******************************/
	
	volatile int status;
	int timeout = AT91C_MCI_TIMEOUT ; 
	AT91F_CfgDevice(pmmcDev);
	
	AT91F_MCI_Configure(AT91C_BASE_MCI,
				AT91C_MCI_DTOR_1MEGA_CYCLES,
				0x834A,						/* 400kHz for MCK = 60MHz*/
				AT91C_MCI_MMC_SLOTA);
	
	/** Wait MCI Device Ready*/
	do
	{
		status = AT91C_BASE_MCI->MCI_SR;
		timeout--;
	}
	while( !(status & AT91C_MCI_NOTBUSY)  && (timeout>0) );	
	
	if(AT91F_MCI_MMC_Init(pmmcDev) != AT91C_INIT_OK)
		return FALSE;
	
	/* Select MMC Card n°1*/
	if(AT91F_MCI_MMC_SelectCard(pmmcDev,AT91C_FIRST_RCA) != AT91C_CARD_SELECTED_OK)
		return ERROR;
	
	/* Set Block Length*/
	if (AT91F_MCI_SetBlocklength(pmmcDev,pmmcDev->pMCI_DeviceFeatures[0].Max_Read_DataBlock_Length) != AT91C_CMD_SEND_OK)
		return ERROR;

    return (OK);
    }

/*******************************************************************************
*
* mmcPread - Read drive parameters
*
* Read drive parameters.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS mmcPread
    (
    int drive,
    void *buffer
    )
    {
 

    return (OK);
    }
/*******************************************************************************
*
* mmcRecalib - recalibrate the drive
*
* Recalibrate the drive
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS mmcRecalib
    (
    int drive
    )
    {
 
    return (OK);
    }

/*******************************************************************************
*
* mmcSeek - seek the drive heads to the specified cylinder
*
* Seek the drive heads to the specified cylinder
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS mmcSeek(int drive, int cylinder, int head)
{

 
    return (OK);
    }

/*******************************************************************************
*
* mmcRW - read/write a number of sectors on the current track
*
* Read/write a number of sectors on the current track
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/



/*******************************************************************************
*
* mmcFormat - format the current track
*
* format the current track; not supported.
*
* RETURNS: ERROR always.
*/

LOCAL STATUS mmcFormat
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

LOCAL STATUS mmcStatusChk
    (
    AT91PS_MciDevice pmmcDev
    )
    {
/* pdataflashDev->blkDev.bd_readyChanged	= TRUE;*/
 pmmcDev->blkDev.bd_mode = O_RDWR;
 	
    return (OK);
    }

