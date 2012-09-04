/* pccardLib.c - PC CARD enabler library */

/* Copyright 1984-1996 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01k,21jun00,rsh  upgrade to dosFs 2.0
01o,31aug99,jkf  changed from cbio.h to cbioLib.h
01n,03nov98,lrn  cleanup warnings
01m,06oct98,lrn  merge DosFs 2.0 changes into T2.0, DosFs 2.0 API for TFFS
01l,17sep98,lrn  reworked DosFs 2.0 support and memory leak issues
01k,13jul98,lrn  DosFs 2.0 - can not delete a DOS device
01j,19jan98,hdn  added a check to see if the socket is registered.
01i,11dec97,hdn  added TFFS support for flash PC card.
01h,19mar97,hdn  deleted a line that writes 0 to the ELT's address config reg.
01g,16jan97,hdn  initialized pcmciaCtrl.
01f,17nov96,jdi  doc: tweaks.
01e,08nov96,dgp  doc: final formatting
01d,28mar96,jdi  doc: cleaned up language and format.
01c,08mar96,hdn  added more descriptions.
01b,22feb96,hdn  cleaned up
01a,19oct95,hdn  written.
*/

/*
DESCRIPTION
This library provides generic facilities for enabling PC CARD.
Each PC card device driver needs to provide an enabler routine and
a CSC interrupt handler.  The enabler routine must be in the
`pccardEnabler' structure.
Each PC card driver has its own resource structure, `xxResources'.  The
ATA PC card driver resource structure is `ataResources' in
sysLib, which also supports a local IDE disk.
The resource structure has a PC card common resource structure in
the first member.  Other members are device-driver dependent resources.

The PCMCIA chip initialization routines tcicInit() and pcicInit() are
included in the PCMCIA chip table `pcmciaAdapter'.
This table is scanned when the PCMCIA library is initialized.  If the
initialization routine finds the PCMCIA chip, it registers all function
pointers of the PCMCIA_CHIP structure.

A memory window defined in `pcmciaMemwin' is used to access
the CIS of a PC card through the routines in cisLib.

SEE ALSO
pcmciaLib, cisLib, tcic, pcic

*/

/* LINTLIBRARY */

#include "private/funcBindP.h"
#include "drv/pcmcia/pcmciaLib.h"
#include "drv/pcmcia/cisLib.h"
#include "drv/pcmcia/pcic.h"
#include "drv/pcmcia/tcic.h"
//#include "drv/pcmcia/sramDrv.h"
//#include "drv/hdisk/ataDrv.h"
#include "cbioLib.h"
#include "dcacheCbio.h"
#include "dpartCbio.h"


#define INCLUDE_AT91_CF 1
#ifdef INCLUDE_AT91_CF
STATUS at91CFEnabler
    (
    int		  sock,		  /* socket no. */
    TFFS_RESOURCE *pTffsResource, /* pointer to TFFS resources */
    int		  numEnt,	  /* number of SRAM resource entries */
    FUNCPTR	  showRtn 	  /* TFFS show routine */
    );
LOCAL STATUS at91CFIntr
    (
    int sock,			/* socket no. */
    int csc			/* CSC bits */
    );
#endif
/*#include "at91_pcmcia.h"*/
#include "pcic.c"


/* externs */
IMPORT BOOL pcmciaDebug;
/* dont use partition table decoder unless ATA is included */
#define	USE_PARTITIONS	FALSE



#ifdef	INCLUDE_ATA
IMPORT ATA_CTRL		ataCtrl [ATA_MAX_CTRLS];
LOCAL STATUS	pccardAtaCscIntr  (int sock, int csc);
#undef	USE_PARTITIONS
#define	USE_PARTITIONS	TRUE
#endif	/* INCLUDE_ATA */

#ifdef	INCLUDE_SRAM
IMPORT SRAM_CTRL	sramCtrl;
IMPORT int		sramResourceNumEnt;
LOCAL STATUS	pccardSramCscIntr (int sock, int csc);
#endif	/* INCLUDE_SRAM */




/* globals */

PCMCIA_CTRL pcmciaCtrl = {PCMCIA_SOCKS, PCMCIA_MEMBASE} ;

PCMCIA_MEMWIN pcmciaMemwin [] =
    {
    {0, 0, 0, CIS_MEM_START, CIS_MEM_STOP, 0},	/* CIS extraction */
    {0, 0, 0, CIS_REG_START, CIS_REG_STOP, 0},	/* config registers */
    };

PCMCIA_ADAPTER pcmciaAdapter [] =
    {
    {PCMCIA_PCIC, PCIC_BASE_ADR, PCIC_INT_VEC, PCIC_INT_LVL,pcicInit, NULL}
 /*   {PCMCIA_TCIC, TCIC_BASE_ADR, TCIC_INT_VEC, TCIC_INT_LVL, tcicInit, NULL}*/
    };



#ifdef	INCLUDE_SRAM
SRAM_RESOURCE sramResources[] =
    {
    {
     {
     5, 0,
     {0, 0}, {0, 0}, 0,
     SRAM0_MEM_START, SRAM0_MEM_STOP, 1, 0x0, SRAM0_MEM_LENGTH
     }
    },
    {
     {
     5, 0,
     {0, 0}, {0, 0}, 0,
     SRAM1_MEM_START, SRAM1_MEM_STOP, 1, 0x0, SRAM1_MEM_LENGTH
     }
    },
    {
     {
     5, 0,
     {0, 0}, {0, 0}, 0,
     SRAM2_MEM_START, SRAM2_MEM_STOP, 1, 0x0, SRAM2_MEM_LENGTH
     }
    },
    {
     {
     5, 0,
     {0, 0}, {0, 0}, 0,
     SRAM3_MEM_START, SRAM3_MEM_STOP, 1, 0x0, SRAM3_MEM_LENGTH
     }
    }
    };
#endif	/* INCLUDE_SRAM */


#ifdef	INCLUDE_AT91_CF
TFFS_RESOURCE at91CFResources[] =
    {
    {
     {
     3 /* vcc */, 0 /* vpp */,
     {0, 0}, {0, 0}, 0,
     0x400, 0x7ff, 2 /* extra wait state */,
     0x0 /* offset card address */, 0x0 /* size of the memory */
     }
    }
    };
#endif	/* INCLUDE_TFFS */



PCCARD_ENABLER pccardEnabler [] =
    {


#ifdef	INCLUDE_ATA
    {
     PCCARD_ATA, (void *)ataResources, NELEMENTS(ataResources),
     (FUNCPTR)pccardAtaEnabler, NULL
    },
#endif	/* INCLUDE_ATA */



#ifdef	INCLUDE_AT91_CF
    {
     PCCARD_FLASH, (void *)at91CFResources, NELEMENTS(at91CFResources),
     (FUNCPTR)at91CFEnabler, NULL
    },
#endif	/* INCLUDE_TFFS */


#ifdef	INCLUDE_SRAM
    {
     PCCARD_SRAM, (void *)sramResources, NELEMENTS(sramResources),
     (FUNCPTR)pccardSramEnabler, NULL
    }
#endif	/* INCLUDE_SRAM */
    };

int pcmciaAdapterNumEnt = NELEMENTS (pcmciaAdapter);
int pccardEnablerNumEnt = NELEMENTS (pccardEnabler);


/* locals */

#ifdef	INCLUDE_SRAM
LOCAL int sramSizeTable [] = {512, 2000, 8000, 32000,
			      128000, 512000, 2000000, 0};
#endif	/* INCLUDE_SRAM */

#ifdef INCLUDE_DOSFS
#define ATA_CACHE_SIZE	(128*1024)
#define SRAM_CACHE_SIZE	(2*1024)
#define TFFS_CACHE_SIZE	(32*1024)

CBIO_DEV_ID sockCbioDevs[ PCIC_MAX_SOCKS * NELEMENTS (pcmciaAdapter) ];
char * sockDevNames[ PCIC_MAX_SOCKS * NELEMENTS (pcmciaAdapter) ] =
		 { "/card0", "/card1", "/card2", "/card3", NULL };
#endif /* INCLUDE_DOSFS */
#ifdef INCLUDE_ATA

#endif

#ifdef INCLUDE_SRAM
#endif

#ifdef INCLUDE_ELT
#endif


#ifdef INCLUDE_AT91_CF
#include "at91CFdev.c"
#endif
/*******************************************************************************
*
* pccardMount - mount a DOS file system
*
* This routine mounts a DOS file system.
*
* RETURNS: OK or ERROR.
*/
STATUS pccardMount
    (
    int	 sock,			/* socket number */
    char *pName			/* name of a device */
    )

    {

    printErr( "This function is discontinued\n" );
    return ERROR;

#if FALSE
    PCMCIA_CTRL *pCtrl		= &pcmciaCtrl;
    PCMCIA_CHIP *pChip		= &pCtrl->chip;
    PCMCIA_CARD *pCard		= &pCtrl->card[sock];
    DOS_VOL_DESC *pDos		= pCard->pDos;

    if ((!pChip->installed) || (!pCard->installed) || (sock >= pChip->socks))
        return (ERROR);

    if (pDos != NULL)
	{
	iosDevDelete (&pDos->dosvd_devHdr);
	free ((char *)pDos);
	return (ERROR);
	}

    pCard->pDos = dosFsDevInit (pName, pCard->pBlkDev, NULL);
    if (pCard->pDos == NULL)
	return (ERROR);

    return (OK);
#endif /* FALSE */
    }

/*******************************************************************************
*
* pccardMkfs - initialize a device and mount a DOS file system
*
* This routine initializes a device and mounts a DOS file system.
*
* RETURNS: OK or ERROR.
*/
STATUS pccardMkfs
    (
    int	 sock,			/* socket number */
    char *pName			/* name of a device */
    )

    {

    printErr( "This function is discontinued. Use dosFsVolFormat()\n" );
    return ERROR;

#if FALSE
    PCMCIA_CTRL *pCtrl		= &pcmciaCtrl;
    PCMCIA_CHIP *pChip		= &pCtrl->chip;
    PCMCIA_CARD *pCard		= &pCtrl->card[sock];
    DOS_VOL_DESC *pDos		= pCard->pDos;

    if ((!pChip->installed) || (!pCard->installed) || (sock >= pChip->socks))
        return (ERROR);

    if (pDos != NULL)
	{
	iosDevDelete (&pDos->dosvd_devHdr);
	free ((char *)pDos);
	return (ERROR);
	}

    pCard->pDos = dosFsMkfs (pName, pCard->pBlkDev);
    if (pCard->pDos == NULL)
	return (ERROR);

    return (OK);
#endif /* FALSE */
    }



#ifdef INCLUDE_AT91_CF

/*******************************************************************************
*
* pccardTffsEnabler - enable the PCMCIA-TFFS driver
*
* This routine enables the PCMCIA-TFFS driver.
*
* RETURNS:
* OK, ERROR_FIND if there is no TFFS(Flash) card, or ERROR if another error occurs.
*/
STATUS at91CFMount()
{
	int sock=0;
    PCMCIA_CTRL *pCtrl		= &pcmciaCtrl;
    PCMCIA_CHIP *pChip		= &pCtrl->chip;
    PCMCIA_CARD *pCard		= &pCtrl->card[sock];
    int deviceType		= 0;
    PCCARD_RESOURCE *pResource;
    DL_NODE *pNode;
    CIS_TUPLE *pTuple;
    int flag;
    char *pChar;

    if ((!pChip->installed))
	return (ERROR);
	if(!pCard->installed)
	{
	    return cisGet(sock);
	}
    return (OK);
}


STATUS at91CFEnabler
    (
    int		  sock,		  /* socket no. */
    TFFS_RESOURCE *pTffsResource, /* pointer to TFFS resources */
    int		  numEnt,	  /* number of SRAM resource entries */
    FUNCPTR	  showRtn 	  /* TFFS show routine */
    )

    {
    PCMCIA_CTRL *pCtrl		= &pcmciaCtrl;
    PCMCIA_CHIP *pChip		= &pCtrl->chip;
    PCMCIA_CARD *pCard		= &pCtrl->card[sock];
    int deviceType		= 0;
    PCCARD_RESOURCE *pResource;
    DL_NODE *pNode;
    CIS_TUPLE *pTuple;
    int flag;
    char *pChar;

    if ((!pChip->installed) || (sock >= numEnt))
	return (ERROR);

    for (pNode = DLL_FIRST (&pCard->cisTupleList);
	 pNode != NULL;
	 pNode = DLL_NEXT(pNode))
	{
	pTuple	= (CIS_TUPLE *)((char *)pNode + sizeof (DL_NODE));
	pChar	= (char *)pTuple + sizeof (CIS_TUPLE);

	switch (pTuple->code)
	    {
	    case CISTPL_DEVICE:
		deviceType = *pChar & 0xf0;
		break;
	    }
	}

    /* configure the card with a resource which is assigned for the socket */

    if( !(deviceType == DTYPE_FLASH || deviceType == DTYPE_FUNCSPEC ))
    	return (ERROR_FIND);
    	
	{
        pTffsResource		+= sock;
        pResource		= &pTffsResource->resource;
        pCard->type		= PCCARD_FLASH;
        pCard->sock		= sock;
        pCard->detected		= TRUE;
        pCard->pResource	= pResource;
        pCard->cardStatus	= (* pChip->status)(sock);
        pCard->cscIntr		= (FUNCPTR)at91CFIntr;
        pCard->showRtn		= (FUNCPTR)showRtn;
        pResource->memStart	&= 0xfffff000;
        pResource->memStop	|= 0x00000fff;

        flag = PC_PWR_AUTO;
        if (pResource->vcc == PCCARD_5V)
	    flag |= PC_VCC_5V;
        else if (pResource->vcc == PCCARD_3V)
	    flag |= PC_VCC_3V;
        if ((* pChip->flagSet)(sock, flag) != OK)
	    return (ERROR);

        if ((pCard->initStatus = cfcDrv ()) != OK)	/* just in case */
	    return (ERROR);

        pCard->installed = TRUE;
	}
    
	

    /* return if we didn't recognize the card or didn't install the driver */

    if (!pCard->installed)
	return (ERROR);



    if (pCard->pBlkDev != NULL)
	free ((char *)pCard->pBlkDev);

    pCard->pBlkDev = cfcDevCreate (0, 0,0);
    if (pCard->pBlkDev == (BLK_DEV *)NULL)
	    {
	    printErr ("Error during tffsDevCreate: %x\n", errno);
	    return (ERROR);
	    }
    if ((pcmciaDebug) && (_func_logMsg != NULL))
	(* _func_logMsg) ("TFFS sock=%d blkDev=%x\n",
			      sock,pCard->pBlkDev , 0, 0, 0, 0);

#ifdef INCLUDE_DOSFS
    /*
     * init DOS device with new block device driver and
     * valid disk cache size
     */
    return dosFsDevCreate(sockDevNames[ sock ], pCard->pBlkDev, 20,0);
    
//    return pccardDosDevCreate( sock, pCard->pBlkDev,
//	TFFS_CACHE_SIZE, USE_PARTITIONS );
#else
    printErr ("DosFs not included, card in socket %d ignored\n", sock);
#endif /* INCLUDE_DOSFS */
    return (OK);
    }

/*******************************************************************************
*
* pccardTffsCscIntr - PCMCIA flash card status change interrupt handler
*
* RETURNS: OK, or ERROR if the CSC event is Ready.
*/

LOCAL STATUS at91CFIntr
    (
    int sock,			/* socket no. */
    int csc			/* CSC bits */
    )

    {
    PCMCIA_CTRL *pCtrl		= &pcmciaCtrl;
    PCMCIA_CARD *pCard		= &pCtrl->card[sock];


    /* hot insertion */


    /* hot removal */

    if ((csc & PC_DETECT) && ((pCard->cardStatus & PC_DETECT) == 0x0))
	{
	}

    /* card is ready */

    if (csc & PC_READY)
	{
	return (ERROR);
	}

    /* other card status changes */

    if ((csc & PC_WRPROT) && (_func_logMsg != NULL))
	(* _func_logMsg) ("TFFS: socket=%d Write protect\n",
			  sock, 0, 0, 0, 0, 0);

    return (OK);
    }

#endif

#include "cisShow.c"


