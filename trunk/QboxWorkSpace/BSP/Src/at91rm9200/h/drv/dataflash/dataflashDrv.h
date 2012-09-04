/* dataflashDrv.h - IDE disk controller header */

/* Copyright 1984-2001 Wind River Systems, Inc. */
/*
modification history
--------------------
01d,30oct01,dat  Adding warning about driver being obsolete
01c,25oct94,hdn  added dataflashRawio() function prototype.
01b,10oct94,hdn  added IDE_RAW structure for dataflashRawio().
01a,19oct93,hdn  written.
*/

#ifndef __INCdataflashDrvh
#define __INCdataflashDrvh

#ifdef __cplusplus
extern "C" {
#endif



#ifndef _ASMLANGUAGE

#include "blkIo.h"
#define	STAT_ERR	0x01		/* error detect */
typedef struct dataflashRaw
    {				/* this is for IDERAWACCESS ioctl */
    UINT cylinder;		/* cylinder (0 -> (cylindres-1)) */
    UINT head;			/* head (0 -> (heads-1)) */
    UINT sector;			/* sector (1 -> sectorsTrack) */
    char *pBuf;			/* pointer to buffer (bytesSector * nSecs) */
    UINT nSecs;			/* number of sectors (1 -> sectorsTrack) */
    UINT direction;		/* read=0, write=1 */
    } DATAFLASH_RAW;


/* max number of MMC drives */

#define DATAFLASH_MAX_DRIVES	1

#define AT45DB161	0x2c
#define AT45DB321	0x34
#define AT45DB642	0x3c
#define AT45DB128	0x10

/* function declarations */

#if defined(__STDC__) || defined(__cplusplus)

STATUS	dataflashDrv ();
BLK_DEV	*dataflashDevCreate (int drive, int nBlks, int offset);
STATUS	dataflashRawio (int drive,DATAFLASH_RAW *pIdeRaw);

#else

STATUS	dataflashDrv ();
BLK_DEV	*dataflashDevCreate ();
STATUS	dataflashRawio ();

#endif  /* __STDC__ */

#endif  /* _ASMLANGUAGE */

#ifdef __cplusplus
}
#endif

#endif /* __INCdataflashDrvh */

