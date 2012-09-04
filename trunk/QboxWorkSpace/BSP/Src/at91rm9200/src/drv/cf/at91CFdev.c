/* cfcDrv.c - AT91RM9200DK compact flash card disk device driver */

/* Copyright 1989-1999 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01p,30jul99,jkf  fixed SPR 9729, retryRW condition loses data.
01o,11jan99,aeg  removed redundant semBInit () in cfcInit ().
01n,03mar97,dat  fixed SPR 8084, previous edit needed tweeking.
01m,28feb97,dat  fixed SPR 8084, incorrect block number check
01l,17dec96,dat  fixed SPR 3273, incorrect block count
01k,14jun95,hdn  removed function declarations defined in sysLib.h.
01j,24jan95,jdi  doc cleanup.
01i,07dec94,rhp  man page cleanups to cfcDrvCreate(), cfcRawio() (SPR3734).
01h,25oct94,hdn  cleaned up cfcRawio().
		 changed cfcSemSec and cfcWdSec back to 5.
01g,06oct94,hdn  changed cfcSemSec to 10, cfcWdSec to 10.
		 added cfcRawio() to provcfc physical IO.
01f,03jun94,hdn  changed DESCRIPTION, 386 to 386/486.
		 added an explanation of parameters for cfcDevCreate().
01e,18nov93,hdn  added watchdog to check cfcInit() in cfcDrv().
01d,11nov93,hdn  added cfcWait() in end of each primitive functions.
		 implemented semaphore timeout and watchdog.
01c,10nov93,hdn  separated cfcDiagnose() from cfcInit().
01b,04nov93,hdn  cleaned up.
01a,18oct93,hdn  written.
*/

/*
DESCRIPTION
This is the driver for the cfc used on the PC 386/486.

USER-CALLABLE ROUTINES
Most of the routines in this driver are accessible only through the I/O
system.  However, two routines must be called directly:  cfcDrv() to
initialize the driver, and cfcDevCreate() to create devices.

Before the driver can be used, it must be initialized by calling cfcDrv().
This routine should be called exactly once, before any reads, writes, or
calls to cfcDevCreate().  Normally, it is called from usrRoot() in
usrConfig.c.

The routine cfcRawio() provcfcs physical I/O access.  Its first
argument is a drive number, 0 or 1; the second argument is a pointer
to an DATAFLASH_RAW structure.

NOTE
Format is not supported, because cfc disks are already formatted, and bad
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
//#include "drv/h/pccardLib.h"
//#include "drv/cf/cfcdrv.h"


#define AT91C_CFC_TIMEOUT				10000   /* For AT91F_DataFlashWaitReady */
#define CF_BUFFER_SIZE						512
//#define MASTER_CLOCK						60000000

/* imports */


/* global */

BOOL cfcDebug	 = FALSE;	/* debug flag */
BOOL cfcDebugErr = FALSE;	/* debug flag */
int  cfcIntCount = 0;		/* interrupt count */
int  cfcStatus	 = 0;		/* status register in interrupt level */
int  cfcDrives	 = 0;		/* number of cfc drives */
int  cfcRetry	 = 3;		/* max retry count */
int  cfcSemSec	 = 5;		/* timeout seconds for semaphore */
int  cfcWdSec	 = 5;		/* timeout seconds for watchdog */
BOOL cfcWaitForever = TRUE;	/* watchdog: wait forever in cfcInit() */

SEMAPHORE cfcSyncSem;		/* binary semaphore for syncronization */
SEMAPHORE cfcMuteSem;		/* mutex  semaphore for mutual-exclusion */


/* local */

LOCAL BOOL cfcDrvInstalled = FALSE;   /* TRUE = facility installed */

typedef struct __at91s_cf_card_device
{
	BLK_DEV blkDev; 
	int drive;
    	int blkOffset;
    	int blknum;
    	int pagesize;
} AT91S_CF_Card_Device,*AT91PS_CF_Card_Device;


#include "compactFlash.c"
/* function prototypes */

      void   cfcShow	(int drive);
LOCAL STATUS cfcBlkRd	(AT91PS_CF_Card_Device pcfcDev, int startBlk, int nBlks, char *pBuf);
LOCAL STATUS cfcBlkWrt	(AT91PS_CF_Card_Device pcfcDev, int startBlk, int nBlks, char *pBuf);
LOCAL STATUS cfcReset	(AT91PS_CF_Card_Device pcfcDev);
LOCAL STATUS cfcIoctl	(AT91PS_CF_Card_Device pcfcDev, int function, int arg);
LOCAL STATUS cfcBlkRW	(AT91PS_CF_Card_Device pcfcDev, int startBlk, int nBlks, char *pBuf,
			 int direction);
LOCAL void   cfcIntr	(int ctrl);
LOCAL void   cfcWdog	(int ctrl);
LOCAL void   cfcWait	(int request);
LOCAL void   cfcInit	(void);
LOCAL STATUS cfcDiagnose(void);
LOCAL STATUS cfcPinit	(AT91PS_CF_Card_Device pcfcDev);
LOCAL STATUS cfcPread	(int drive, void *buffer);
LOCAL STATUS cfcRecalib	(int drive);
LOCAL STATUS cfcSeek	(int drive, int cylinder, int head);
LOCAL STATUS cfcRW	(int drive, int cylinder, int head, int sector, 
	 		 void *pBuf, int nSecs, int direction);
LOCAL STATUS cfcFormat	(int drive, int cylinder, int head, int interleave);
LOCAL STATUS cfcStatusChk(AT91PS_CF_Card_Device pcfcDev);


AT91PS_CF_Card_Device gpCFCDev=0;

LOCAL int  cfcWaitReady(unsigned int timeout)
{
	return 0;//return semTake (&cfcSyncSem, timeout);
	
	
}


/*******************************************************************************
*
* cfcDrv - initialize the cfc driver
*
* This routine initializes the cfc driver, sets up interrupt vectors,
* and performs hardware initialization of the cfc chip.
*
* This routine should be called exactly once, before any reads, writes,
* or calls to cfcDevCreate().  Normally, it is called by usrRoot()
* in usrConfig.c.
*
* The cfcDrv() call requires a configuration type, <manualConfig>.  If
* this argument is 1, the driver will initialize drive parameters; if
* the argument is 0, the driver will not initialize drive parameters.
*
* The drive parameters are the number of sectors per track, the number of
* heads, and the number of cylinders.  They are stored in the structure
* table `cfcTypes[]' in sysLib.c.  The table has two entries:  the first is
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
* SEE ALSO: cfcDevCreate()
*/

STATUS cfcDrv
    (
    )
    {
    int drive;


    if (!cfcDrvInstalled)
    {
        semBInit (&cfcSyncSem, SEM_Q_FIFO, SEM_EMPTY);

        semMInit (&cfcMuteSem, SEM_Q_PRIORITY | SEM_DELETE_SAFE |
		SEM_INVERSION_SAFE);


	
        //cfcInit ();
	        

	cfcDrvInstalled = TRUE;
    }

    return (OK);
    }

/*******************************************************************************
*
* cfcDevCreate - create a device for a cfc disk
*
* This routine creates a device for a specified cfc disk.
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
int __get_block_size__(int size)
{
	int n=0;
	while(( size=(size>>1)))n++;
	return (1<<n);
}
#undef __TEST__
#ifdef __TEST__
LOCAL char* gpCache=0;
#endif
BLK_DEV *cfcDevCreate
    (
    int drive,		/* drive number for hard drive (0 or 1) */
    int nBlocks,	/* device size in blocks (0 = whole disk) */
    int blkOffset	/* offset from start of device */
    )
    {
    AT91PS_CF_Card_Device pcfcDev;
    BLK_DEV *pBlkDev;
	unsigned short buf[CF_BUFFER_SIZE/2];

    if (!cfcDrvInstalled)
	return (NULL);

    if ((UINT)drive > cfcDrives)
	return (NULL);


	/*
	 * CD1/2 are active low; so are the VSS pins; Ready is active high
	 */
	if ((AT91_SYS->PIOB_PDSR & (AT91C_CF_PB0_CD1 | AT91C_CF_PB1_CD2))) {
		printf("No Compact Flash Card Inserted\n");
		return 0;
//		state_array->state[0].iois16 = (AT91_SYS->PIOB_PDSR & AT91C_CF_PB2_IOIS16) ? 1 : 0;
	}

    if ((pcfcDev = (AT91PS_CF_Card_Device )calloc(sizeof (AT91S_CF_Card_Device), 1)) == NULL)
	return (NULL);

   
    pBlkDev = &pcfcDev->blkDev;
    gpCFCDev = pcfcDev;


    //AT91F_CfgDataFlash(pcfcDev);
    //cfcPinit (pcfcDev);
	pcfcDev->blknum = 0x2000;
	pcfcDev->pagesize = CF_BUFFER_SIZE;
    //if (nBlocks == 0)
    //	nBlocks = (pcfcDev->blknum)  - blkOffset;

    pBlkDev->bd_nBlocks		= nBlocks;
    if (nBlocks == 0) pBlkDev->bd_nBlocks =(pcfcDev->blknum)  - blkOffset;		

    pBlkDev->bd_blksPerTrack	= 1;
    pBlkDev->bd_nHeads		= 1;
    pBlkDev->bd_removable	= FALSE;
    pBlkDev->bd_retry		= 1;
    pBlkDev->bd_mode		= O_RDWR;
    pBlkDev->bd_readyChanged	= FALSE;
    pBlkDev->bd_blkRd		= cfcBlkRd;
    pBlkDev->bd_blkWrt		= cfcBlkWrt;
    pBlkDev->bd_ioctl		= cfcIoctl;
    pBlkDev->bd_reset		= cfcReset;
    pBlkDev->bd_statusChk	= cfcStatusChk;

    pcfcDev->drive		= drive;
    pcfcDev->blkOffset		= blkOffset;
    
    if(0==AT91F_CF_READ16_ID ( buf))
    {
    	char szModel [LENGTH_MODEL*2+1]; 
    	char* p = szModel;
    	int i;
    	pcfcDev->blknum = (buf[OFFSET_SECTORS]<<16)|buf[OFFSET_SECTORS+1];
    	for(i=0;i<OFFSET_MODEL;i++)
    	{
    		*p++= (buf[OFFSET_SECTORS+i]>>8);
    		*p++= (buf[OFFSET_SECTORS+i]&0xff);
    	}
    	*p=0;
    	printf ("Device %s is ready!\n",szModel);
    	printf ("Capacity is %x bytes!\n",pcfcDev->blknum*CF_BUFFER_SIZE);
    }else 
    {
    	free(pcfcDev);gpCFCDev=0;
    	return 0;
    }
    
    pBlkDev->bd_bytesPerBlk	= __get_block_size__(pcfcDev->pagesize);
    if(nBlocks==0)
    	pBlkDev->bd_nBlocks	= (pcfcDev->blknum)  - blkOffset;
    
#ifdef __TEST__    
    gpCache = malloc(0x210*nBlocks);
#endif    
    return (&pcfcDev->blkDev);
    }

/*******************************************************************************
*
* cfcShow - show cfc disk parameters
*
* Show cfc disk parameters
*
* RETURNS: N/A
*
* NOMANUAL
*/

void cfcShow
    (
    int drive
    )
    {

    }

/*******************************************************************************
*
* cfcRawio - provide raw I/O access
*
* This routine is called when the raw I/O access is necessary.
*
* <drive> is a drive number for the hard drive: it must be 0 or 1.
*
* The <pcfcRaw> is a pointer to the structure DATAFLASH_RAW which is defined in 
* cfcDrv.h
*
* RETURNS: OK or ERROR.
*
*/

STATUS cfcRawio
    (
    int        drive,	/* drive number for hard drive (0 or 1) */
    DATAFLASH_RAW *  pcfcRaw	/* pointer to DATAFLASH_RAW structure */
    )
    {
    AT91S_CF_Card_Device cfcDev;
    BLK_DEV *pBlkDev	= &cfcDev.blkDev;
    int nBlocks = 0;
    UINT startBlk;

    if (!cfcDrvInstalled)
	return (ERROR);

    if ((UINT)drive > cfcDrives)
	return (ERROR);
 
    //AT91F_CfgDataFlash(&cfcDev);

    //cfcPinit(&cfcDev);/*memcpy(&cfcDev,pDataFlash_Device,sizeof(cfcDev));*/
   	if(!gpCFCDev)
   	{
   		cfcDevCreate(0,0,0);
   	   	if(gpCFCDev) 
   	   	{
   	   		memcpy(&cfcDev,gpCFCDev,sizeof(cfcDev));
   	   		free(gpCFCDev);gpCFCDev = 0;
   	   	}
   	   	
   	}else memcpy(&cfcDev,gpCFCDev,sizeof(cfcDev));
    nBlocks = (cfcDev.blknum)
	  - 0;

    pBlkDev->bd_nBlocks		= nBlocks;


    pBlkDev->bd_bytesPerBlk	= __get_block_size__(cfcDev.pagesize);
    pBlkDev->bd_blksPerTrack	= 1;
    pBlkDev->bd_nHeads		= 1;
    pBlkDev->bd_removable	= FALSE;
    pBlkDev->bd_retry		= 1;
    pBlkDev->bd_mode		= O_RDWR;
    pBlkDev->bd_readyChanged	= TRUE;
    pBlkDev->bd_blkRd		= cfcBlkRd;
    pBlkDev->bd_blkWrt		= cfcBlkWrt;
    pBlkDev->bd_ioctl		= cfcIoctl;
    pBlkDev->bd_reset		= cfcReset;
    pBlkDev->bd_statusChk	= NULL;

    cfcDev.drive		= drive;
    cfcDev.blkOffset		= 0;

    startBlk = 0;
	AT91F_CF_RDY();       
    return (cfcBlkRW (&cfcDev, startBlk, pcfcRaw->nSecs, pcfcRaw->pBuf,
		     pcfcRaw->direction));
   
     return ERROR;
    }

/*******************************************************************************
*
* cfcBlkRd - read one or more blocks from a cfc disk
*
* This routine reads one or more blocks from the specified device,
* starting with the specified block number.
*
* If any block offset was specified during cfcDevCreate(), it is added
* to <startBlk> before the transfer takes place.
*
* RETURNS: OK, ERROR if the read command didn't succeed.
*/

LOCAL STATUS cfcBlkRd
    (
    AT91PS_CF_Card_Device pcfcDev,
    int startBlk,
    int nBlks,
    char *pBuf
    )
    {
    return (cfcBlkRW (pcfcDev, startBlk, nBlks, pBuf, O_RDONLY));
    }

/*******************************************************************************
*
* cfcBlkWrt - write one or more blocks to a cfc disk
*
* This routine writes one or more blocks to the specified device,
* starting with the specified block number.
*
* If any block offset was specified during cfcDevCreate(), it is added
* to <startBlk> before the transfer takes place.
*
* RETURNS: OK, ERROR if the write command didn't succeed.
*/

LOCAL STATUS cfcBlkWrt
    (
    AT91PS_CF_Card_Device pcfcDev,
    int startBlk,
    int nBlks,
    char *pBuf
    )
    {
    return (cfcBlkRW (pcfcDev, startBlk, nBlks, pBuf, O_WRONLY));
    }

/*******************************************************************************
*
* cfcReset - reset a cfc disk controller
*
* This routine resets a cfc disk controller.
*
* RETURNS: OK, always.
*/

LOCAL STATUS cfcReset
    (
    AT91PS_CF_Card_Device pcfcDev
    )
    {
    
    semTake (&cfcMuteSem, WAIT_FOREVER);

 /*  cfcInit ();*/

    semGive (&cfcMuteSem);

    return (OK);
    }

/*******************************************************************************
*
* cfcIoctl - do device specific control function
*
* This routine is called when the file system cannot handle an ioctl()
* function.
*
* RETURNS:  OK or ERROR.
*/

LOCAL STATUS cfcIoctl
    (
    AT91PS_CF_Card_Device pcfcDev,
    int function,
    int arg
    )
    {
    FAST int status = ERROR;

    semTake (&cfcMuteSem, WAIT_FOREVER);

    switch (function)
	{
	case FIODISKFORMAT:

	    status = OK;
	    break;

	default:
	    (void) errnoSet (S_ioLib_UNKNOWN_REQUEST);
	}

doneIoctl:
    semGive (&cfcMuteSem);
    return (status);
    }



/*******************************************************************************
*
* cfcBlkRW - read or write sectors to a cfc disk.
*
* Read or write sectors to a cfc disk.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS cfcBlkRW
    (
    AT91PS_CF_Card_Device pCFC,
    int startBlk,
    int nBlks,
    char *pBuf,
    int direction
    )
    {
    BLK_DEV *pBlkDev = &pCFC->blkDev;
    int src,ix,i ; 
    int status = ERROR;
    int semStatus = 0;
    char databuf[1200];
    int Max_Read_DataBlock_Length = pCFC->pagesize;
    startBlk+=pCFC->blkOffset;
    src = startBlk;//* Max_Read_DataBlock_Length;
    semTake (&cfcMuteSem, WAIT_FOREVER);
    memset(databuf,0,1200);
if(direction==O_RDONLY)
{
    for (ix = 0; ix < nBlks; ix ++)
    {

	//AT91F_CF_READ16_SECTOR(pCFC,src,databuf,Max_Read_DataBlock_Length);
	AT91F_CF_READ16_SECTOR((short*)databuf,(src&0xff000000)>>24,(src&0xff0000)>>16,(src&0xff00)>>8,src&0xff);
	semStatus = cfcWaitReady(AT91C_CFC_TIMEOUT);
	if ((cfcStatus & STAT_ERR) || (semStatus == ERROR))
        goto errorRW;

	AT91F_CF_RDY();       
	memcpy(pBuf,databuf, pBlkDev->bd_bytesPerBlk);        

#ifdef __TEST__
	if(memcmp(pBuf,gpCache+src, pBlkDev->bd_bytesPerBlk)!=0)
	{
		fprintf(stderr,"not the same \n");
	}
#endif	
        src ++;//= Max_Read_DataBlock_Length ;
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
		AT91F_CF_WRITE16_SECTOR((unsigned short*)databuf,(src&0xff000000)>>24,(src&0xff0000)>>16,(src)>>8,src&0xff);
		AT91F_CF_RDY();
		semStatus = cfcWaitReady(AT91C_CFC_TIMEOUT);
		if ((cfcStatus & STAT_ERR) || (semStatus == ERROR))
	        goto errorRW; 
/*		AT91F_DataFlashWrite(pCFC , (unsigned int*) databuf ,src,Max_Read_DataBlock_Length);
		semStatus =OK;
*/
	        
#ifdef __TEST__	 
		
		AT91F_CF_RDY();

		AT91F_CF_READ16_SECTOR((short*)databuf,(src&0xff000000)>>24,(src&0xff0000)>>16,(src&0xff00)>>8,src&0xff);
		semStatus = cfcWaitReady(AT91C_CFC_TIMEOUT);
		if ((cfcStatus & STAT_ERR) || (semStatus == ERROR))
        	goto errorRW;
		AT91F_CF_RDY();
		/*AT91F_DataFlashRead(pCFC,src,Max_Read_DataBlock_Length,databuf);*/
		if(0!=memcmp(databuf,pBuf,pBlkDev->bd_bytesPerBlk))
		{
			fprintf(stderr,"write cfc error \n");	
		}        
        
#endif        
        src ++; //= Max_Read_DataBlock_Length ;
        pBuf += pBlkDev->bd_bytesPerBlk; /*Max_Read_DataBlock_Length;*/
     }
}
    status = OK;

errorRW:
    if (status == ERROR)
        (void)errnoSet (S_ioLib_DEVICE_ERROR);
    semGive (&cfcMuteSem);
    return (status);
    }

/*******************************************************************************
*
* cfcIntr - cfc controller interrupt handler.
*
* RETURNS: N/A
*/

LOCAL void cfcIntr
    (
    int ctrl
    )
    {

//cfcStatus = ( AT91C_BASE_SPI->SPI_SR & AT91C_BASE_SPI->SPI_IMR );

//AT91F_DataFlashHandler(pDataFlash_Device->pDataFlashDesc,cfcStatus);
semGive (&cfcSyncSem);

  }

/*******************************************************************************
*
* cfcIntr - cfc controller watchdog handler.
*
* RETURNS: N/A
*/

LOCAL void cfcWdog
    (
    int ctrl
    )
    {
    cfcWaitForever = FALSE;
    }

/*******************************************************************************
*
* cfcWait - wait the drive ready
*
* Wait the drive ready
*
* RETURNS: OK, ERROR if the drive didn't become ready in certain period of time.
*/

LOCAL void cfcWait
    (
    int request
    )
    {
	cfcWaitReady(AT91C_CFC_TIMEOUT);
	

    if (cfcDebug)
	printErr ("cfcWait end: \n");
    }

/*******************************************************************************
*
* cfcInit - init a cfc disk controller
*
* This routine initializes a cfc disk controller.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL void cfcInit (void)
    {
 //   AT91F_CfgSPIForDataFlash();
 
 	
    if (cfcDebug)
	printErr ("cfcInit end: \n");
    }

/*******************************************************************************
*
* cfcDiagnose - diagnose the drive
*
* Diagnose the drive
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS cfcDiagnose (void)
    {

    return (OK);
    }









/*******************************************************************************
*
* cfcPread - Read drive parameters
*
* Read drive parameters.
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS cfcPread
    (
    int drive,
    void *buffer
    )
    {
 

    return (OK);
    }
/*******************************************************************************
*
* cfcRecalib - recalibrate the drive
*
* Recalibrate the drive
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS cfcRecalib
    (
    int drive
    )
    {
 
    return (OK);
    }

/*******************************************************************************
*
* cfcSeek - seek the drive heads to the specified cylinder
*
* Seek the drive heads to the specified cylinder
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/

LOCAL STATUS cfcSeek(int drive, int cylinder, int head)
{

 
    return (OK);
    }

/*******************************************************************************
*
* cfcRW - read/write a number of sectors on the current track
*
* Read/write a number of sectors on the current track
*
* RETURNS: OK, ERROR if the command didn't succeed.
*/



/*******************************************************************************
*
* cfcFormat - format the current track
*
* format the current track; not supported.
*
* RETURNS: ERROR always.
*/

LOCAL STATUS cfcFormat
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

LOCAL STATUS cfcStatusChk
    (
    AT91PS_CF_Card_Device pcfcDev
    )
    {
/* pcfcDev->blkDev.bd_readyChanged	= TRUE;*/
 pcfcDev->blkDev.bd_mode = O_RDWR;
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





void cfPrompt( DOS_VOL_CONFIG *pConfig )
{
	pConfig->fatType = 12 ;     /* M- Fat format Type */
    pConfig-> volSerial =0x12345678;     /* M- disk serial number */
	pConfig->sysId = "VXDOS12";
    strcpy(pConfig->volLabel,"CF Card");
   
}













