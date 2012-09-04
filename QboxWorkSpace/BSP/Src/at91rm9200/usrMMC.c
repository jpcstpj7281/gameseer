/* usrMmc.c - IDE initialization */

/* Copyright 1992-1996 Wind River Systems, Inc. */

/*
modification history
--------------------
01f,18jul96,hdn  changed doc: DESCRIPTION
01e,18jun96,hdn  fixed a bug in "offset" calculation.
01d,24jan95,jdi  doc cleanup.
01c,12oct94,hdn  used mmcRawio() instead of using raw file system.
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

#ifndef  __INCusrMmc
#define  __INCusrMmc

/* defines */

#include "drv/mmc/mmcdrv.h"
 
#define VXDOS                           "VXDOS"
#define VXEXT                           "VXEXT"
/* forward declaration */

LOCAL int usrMmcPartition (int drive, DOS_PART_TBL *pPart);


/*******************************************************************************
*
* usrMmcConfig - mount a DOS file system from an MMC disk
*
* This routine mounts a DOS file system from an MMC disk.
*
* The <drive> parameter is the drive number of the MMC disk;
* 0 is `C:' and 1 is `D:'.
*
* The <fileName> parameter is the mount point, e.g., `/mmc0/'.
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
STATUS usrMmcInit ()
{
	return OK;
}
LOCAL char mountpoint[32]="";
STATUS usrMmcConfig
    (
    int     drive,	/* drive number of hard disk (0 or 1) */
    char *  fileName	/* mount point */
    )
    {
    BLK_DEV *pBlkDev;
    char bootDir [BOOT_FILE_LEN];
    char buffer [1024];
    int offset = 0;
    MMC_RAW mmcRaw;
    char *pSys;
    DOS_PART_TBL *pPart;


    if ((UINT)drive >= MMC_MAX_DRIVES)
	{
	printErr ("drive is out of range (0-%d).\n", MMC_MAX_DRIVES - 1);
	return (ERROR);
	}

    /* split off boot device from boot file */

    devSplit (fileName, bootDir);
	strcpy(mountpoint,bootDir);
    /* read the boot sector */

    mmcRaw.cylinder	= 0;
    mmcRaw.head		= 0;
    mmcRaw.sector	= 1;
    mmcRaw.pBuf		= buffer;
    mmcRaw.nSecs	= 1;
    mmcRaw.direction	= 0;

    mmcRawio (drive, &mmcRaw);

    /* get an offset if it is formated by MSDOS */

    pSys  = &buffer[DOS_BOOT_SYS_ID];
    pPart = (DOS_PART_TBL *)&buffer[DOS_BOOT_PART_TBL];
    if ((strncmp(pSys, VXDOS, strlen(VXDOS)) != 0) &&
        (strncmp(pSys, VXEXT, strlen(VXEXT)) != 0))
        {
        offset = usrMmcPartition (drive, pPart);
        }

    if ((pBlkDev = mmcDevCreate(drive, 0, offset)) == (BLK_DEV *)NULL)
        {
        printErr ("Error during mmcDevCreate: %x\n", errno);
        return (ERROR);
        }

    /* Make DOS file system */
#if 0
    if (dosFsDevInit(bootDir, pBlkDev, NULL) == (DOS_VOL_DESC *)NULL)
        {
	printErr ("Error during dosFsDevInit: %x\n", errno);
        return (ERROR);
        }
#endif
    if (dosFsDevCreate(bootDir, pBlkDev, 20,0) == (DOS_VOL_DESC *)NULL)
    {
		printErr ("Error during dosFsDevInit: %x\n", errno);
	    return (ERROR);
    }
    return (OK);
    }

/*******************************************************************************
*
* usrMmcPartition - get an offset to the first partition of the drive.
*
* This routine gets an offset to the first partition of the drive.
*
* RETURNS: offset to the partition
*
*/

LOCAL int usrMmcPartition
    (
    int     drive,	/* drive number of hard disk (0 or 1) */
    DOS_PART_TBL *pPart	/* pointer to the partition table */
    )
    {
    DOS_PART_TBL *pTemp	= pPart;
    int offset		= 0;
    int ix;
    char buffer[1024];
    MMC_RAW mmcRaw;

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
	    mmcRaw.cylinder	= (pPart->dospt_startSec & 0xf0) >> 4;
	    mmcRaw.head		= pPart->dospt_startHead;
	    mmcRaw.sector	= pPart->dospt_startSec & 0x0f;
	    mmcRaw.pBuf		= buffer;
	    mmcRaw.nSecs	= 1;
	    mmcRaw.direction	= 0;

	    mmcRawio (drive, &mmcRaw);

	    pPart = (DOS_PART_TBL *)&buffer[DOS_BOOT_PART_TBL];
	    offset = usrMmcPartition (drive, pPart);
	    return (offset);
	    }
	pPart++;
	}

    return (offset);
    }

void mmcFormatPrompt( DOS_VOL_CONFIG *pConfig )
{
	pConfig->fatType = 16 ;     /* M- Fat format Type */
    pConfig-> volSerial =0x87654321;     /* M- disk serial number */
	pConfig->sysId = "VXDOS16";
    strcpy(pConfig->volLabel,"MMC");
   
}

int mmcFormat(char * mount)
{
	if(mount==0) mount = mountpoint;
	if(mount[0]==0 ) strcpy(mountpoint,"/mmc");
	return dosFsVolFormat(mountpoint,2,mmcFormatPrompt);
}

#endif /* __INCusrMmc */
