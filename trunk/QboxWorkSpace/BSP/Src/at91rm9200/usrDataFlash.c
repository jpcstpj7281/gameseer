/* usrDataFlash.c - IDE initialization */

/* Copyright 1992-1996 Wind River Systems, Inc. */

/*
modification history
--------------------
01f,18jul96,hdn  changed doc: DESCRIPTION
01e,18jun96,hdn  fixed a bug in "offset" calculation.
01d,24jan95,jdi  doc cleanup.
01c,12oct94,hdn  used dataflashRawio() instead of using raw file system.
01b,25oct93,hdn  tuned for IDE driver.
01a,07oct93,sst  part of this program was written by S.Stern
*/

/*
DESCRIPTION
This file is used to configure and initialize the VxWorks IDE support.
This file is included by bootConfig.c and usrConfig.c.

SEE ALSO: usrExtra.c

NOMANUAL
*/

#ifndef  __INCusrDataFlash
#define  __INCusrDataFlash

/* defines */

#include "drv/DataFlash/DataFlashdrv.h"
 
#define VXDOS                           "VXDOS"
#define VXEXT                           "VXEXT"
/* forward declaration */

LOCAL int usrDataFlashPartition (int drive, DOS_PART_TBL *pPart);


/*******************************************************************************
*
* usrDataFlashConfig - mount a DOS file system from an DataFlash disk
*
* This routine mounts a DOS file system from an DataFlash disk.
*
* The <drive> parameter is the drive number of the DataFlash disk;
* 0 is `C:' and 1 is `D:'.
*
* The <fileName> parameter is the mount point, e.g., `/df0/'.
*
* NOTE: Because VxWorks does not support partitioning, hard disks formatted
* and initialized on VxWorks are not compatible with DOS machines.  This
* routine does not refuse to mount a hard disk that was initialized on
* VxWorks.  The hard disk is assumed to have only one partition with a
* partition record in sector 0.
*
* RETURNS: OK or ERROR.
*
* SEE ALSO:
* .pG "I/O System, Local File Systems, Intel i386/i486 Appendix"
*/
STATUS usrDataFlashInit ()
{
	return OK;
}
LOCAL char df_mountpoint[32]="";
STATUS usrDataFlashConfig
    (
    int     drive,	/* drive number of hard disk (0 or 1) */
    char *  fileName	/* mount point */
    )
    {
    BLK_DEV *pBlkDev;
//    char bootDir [BOOT_FILE_LEN];
//    char buffer [1024];
    int offset = 0;

#if 0
    DATAFLASH_RAW dataflashRaw;
    char *pSys;
    DOS_PART_TBL *pPart;


    if ((UINT)drive >= DATAFLASH_MAX_DRIVES)
	{
	printErr ("drive is out of range (0-%d).\n", DATAFLASH_MAX_DRIVES - 1);
	return (ERROR);
	}

    /* split off boot device from boot file */

    devSplit (fileName, bootDir);
    strcpy(df_mountpoint,bootDir);
    /* read the boot sector */

    dataflashRaw.cylinder	= 0;
    dataflashRaw.head		= 0;
    dataflashRaw.sector	= 1;
    dataflashRaw.pBuf		= buffer;
    dataflashRaw.nSecs	= 1;
    dataflashRaw.direction	= 0;

    dataflashRawio (drive, &dataflashRaw);

    /* get an offset if it is formated by MSDOS */

    pSys  = &buffer[DOS_BOOT_SYS_ID];
    pPart = (DOS_PART_TBL *)&buffer[DOS_BOOT_PART_TBL];
    if ((strncmp(pSys, VXDOS, strlen(VXDOS)) != 0) &&
        (strncmp(pSys, VXEXT, strlen(VXEXT)) != 0))
        {
        offset = usrDataFlashPartition (drive, pPart);
        }
#endif
    if ((pBlkDev = dataflashDevCreate(drive, 0, offset)) == (BLK_DEV *)NULL)
        {
        printErr ("Error during dataflashDevCreate: %x\n", errno);
        return (ERROR);
        }

    /* Make DOS file system */
#if 1	
    if (dosFsDevInit(fileName, pBlkDev, NULL) == (DOS_VOL_DESC *)NULL)
        {
	printErr ("Error during dosFsDevInit: %x\n", errno);
        return (ERROR);
        }
#else
    if (dosFsDevCreate(fileName, pBlkDev, 20,0) == (DOS_VOL_DESC *)NULL)
    {
		printErr ("Error during dosFsDevInit: %x\n", errno);
	    return (ERROR);
    }
#endif    
    return (OK);
}

/*******************************************************************************
*
* usrDataFlashPartition - get an offset to the first partition of the drive.
*
* This routine gets an offset to the first partition of the drive.
*
* RETURNS: offset to the partition
*
*/

LOCAL int usrDataFlashPartition
    (
    int     drive,	/* drive number of hard disk (0 or 1) */
    DOS_PART_TBL *pPart	/* pointer to the partition table */
    )
    {
    DOS_PART_TBL *pTemp	= pPart;
    int offset		= 0;
    int ix;
    char buffer[1024];
    DATAFLASH_RAW dataflashRaw;

    for (ix = 0; ix < 4; ix++)		/* active primary DOS partition */
	{
	if (pPart->dospt_status == 0x80)
	    if ((pPart->dospt_type == 0x01) ||
	        (pPart->dospt_type == 0x04) ||
	        (pPart->dospt_type == 0x06))
		{
	        offset = pPart->dospt_absSec;
		return (offset);
		}
	pPart++;
	}
	
    pPart = pTemp;
    for (ix = 0; ix < 4; ix++)		/* primary DOS partition */
	{
	if ((pPart->dospt_type == 0x01) ||
	    (pPart->dospt_type == 0x04) ||
	    (pPart->dospt_type == 0x06))
	    {
	    offset = pPart->dospt_absSec;
	    return (offset);
	    }
	pPart++;
	}

    pPart = pTemp;
    for (ix = 0; ix < 4; ix++)		/* extended DOS partition */
	{
	if (pPart->dospt_type == 0x05)
	    {
	    dataflashRaw.cylinder	= (pPart->dospt_startSec & 0xf0) >> 4;
	    dataflashRaw.head		= pPart->dospt_startHead;
	    dataflashRaw.sector	= pPart->dospt_startSec & 0x0f;
	    dataflashRaw.pBuf		= buffer;
	    dataflashRaw.nSecs	= 1;
	    dataflashRaw.direction	= 0;

	    dataflashRawio (drive, &dataflashRaw);

	    pPart = (DOS_PART_TBL *)&buffer[DOS_BOOT_PART_TBL];
	    offset = usrDataFlashPartition (drive, pPart);
	    return (offset);
	    }
	pPart++;
	}

    return (offset);
    }

	



void dataflashFormatPrompt( DOS_VOL_CONFIG *pConfig )
{
	pConfig->fatType = 12 ;     /* M- Fat format Type */
    pConfig-> volSerial =0x12345678;     /* M- disk serial number */
	pConfig->sysId = "VXDOS12";
    strcpy(pConfig->volLabel,"DataFlash");
   
}

int dataflashFormat(char * mount)
{
	if(mount==0) mount = df_mountpoint;
	if(mount[0]==0 ) strcpy(df_mountpoint,"/df");
	return dosFsVolFormat(mount,2,dataflashFormatPrompt);
}
#endif /* __INCusrDataFlash */

	



