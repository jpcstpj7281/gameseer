/* mmcDrv.h - IDE disk controller header */

/* Copyright 1984-2001 Wind River Systems, Inc. */
/*
modification history
--------------------
01d,30oct01,dat  Adding warning about driver being obsolete
01c,25oct94,hdn  added mmcRawio() function prototype.
01b,10oct94,hdn  added IDE_RAW structure for mmcRawio().
01a,19oct93,hdn  written.
*/

#ifndef __INCmmcDrvh
#define __INCmmcDrvh

#ifdef __cplusplus
extern "C" {
#endif



#ifndef _ASMLANGUAGE

#include "blkIo.h"
#define	STAT_ERR	0x01		/* error detect */
typedef struct mmcRaw
    {				/* this is for IDERAWACCESS ioctl */
    UINT cylinder;		/* cylinder (0 -> (cylindres-1)) */
    UINT head;			/* head (0 -> (heads-1)) */
    UINT sector;			/* sector (1 -> sectorsTrack) */
    char *pBuf;			/* pointer to buffer (bytesSector * nSecs) */
    UINT nSecs;			/* number of sectors (1 -> sectorsTrack) */
    UINT direction;		/* read=0, write=1 */
    } MMC_RAW;


/* max number of MMC drives */

#define MMC_MAX_DRIVES	1



/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

STATUS	mmcDrv ();
BLK_DEV	*mmcDevCreate (int drive, int nBlks, int offset);
STATUS	mmcRawio (int drive,MMC_RAW *pIdeRaw);

#else

STATUS	mmcDrv ();
BLK_DEV	*mmcDevCreate ();
STATUS	mmcRawio ();

#endif  /* __STDC__ */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCmmcDrvh */
