/* ambaMse.c - ARM AMBA mouse driver routines */

/* Copyright 1993-2001 Wind River System, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01b,12sep01,m_h  fix delays
01a,10aug01,m_h  created
*/

/*
DESCRIPTION
This is the driver for ARM's AMBA PrimeCell mouse controller chip.  This driver
supports a PS2 type of pointing  device.


NOTES
The following macros must be defined in ambakmi.h file: COMMAND_AMBA_MS,
DATA_AMBA_MS, STATUS_AMBA_MS. These refer to the I/O base addresses of the various 
key board controller registers. In addition, the macro MSE_INT_LVL and 
MSE_INT_VIC must be defined that identifies the interrupt level and vector 
that is to be used for the mouse interrupts.  Also the I/O access method 
requires that the macros MS_IN and MS_OUT be defined.

*/

/* includes */

#include "vxWorks.h"
#include "iv.h"
#include "ioLib.h"
#include "iosLib.h"
#include "memLib.h"
#include "tyLib.h"
#include "errnoLib.h"
#include "wdLib.h"
#include "sysLib.h"
#include "intLib.h"
#include "taskLib.h"
#include "ambakmi.h"
#include "ugl/bspExt/bspUtil.h"

#ifndef COMMAND_AMBA_MS
#warning "Mouse driver is not initialized for processor"
#else

/* forward declarations */

LOCAL void  mseHwInit();
LOCAL int   mseOpen();
LOCAL int   mseClose();
LOCAL void  mseTxStart();
LOCAL void  ambaMseIntr (MSE_DEVICE  *pDev);
LOCAL void  mseDelay(void);

#ifdef USE_BSP_API
#include <ugl/sysWindML.h>
int ambaMseRegBase, ambaMseRegDelta;
#endif


/*******************************************************************************
*
* ambaPs2DevCreate - PS/2 mouse driver initialization routine
*
* This routine creates a device for a PS/2 mouse.  The AMBA hardware is
* initialized when the keyboard interface is initialized.
*
* RETURNS: device number, if sucessful; otherwise ERROR.
*
* SEE ALSO: 
*/

int ambaPs2DevCreate
    (
    char         *name            /* name to be associated with device   */
    )
    {

    int            mseDrvNum;    /* device number for this driver */
    DEV_HDR     *  pHdr;
    MSE_DEVICE  *  pMseDevice;    /* device descriptors */
    char        *  pName;
#ifdef USE_BSP_API
    WINDML_DEVICE *pDev;
#endif

    /* if device is already present, do not create again */
    pHdr = iosDevFind (name, &pName);
    if ((pHdr != NULL) && (strcmp (name, pHdr->name) == 0))
        return (OK);

    pMseDevice = (MSE_DEVICE *)malloc (sizeof (MSE_DEVICE));

    /* enable the mouse interrupt */
    
#ifdef USE_BSP_API
    pDev = sysWindMLDevGet (WINDML_POINTER_DEVICE, 0, 0, 0);

    ambaMseRegBase = (int)(pDev->pRegBase);
    ambaMseRegDelta = pDev->regDelta;
    sysWindMLIntConnect (pDev, ambaMseIntr, (int)pMseDevice);
#else /* USE_BSP_API */
    (void) intConnect (INT_LVL_MOUSE, ambaMseIntr, (int)pMseDevice);
#endif /* USE_BSP_API */

    /* Install the driver and return installation status */
    mseDrvNum = iosDrvInstall(mseOpen, (FUNCPTR) NULL, mseOpen,
                             (FUNCPTR) mseClose, tyRead, tyWrite, tyIoctl);

    /* Create the channels for this device */
    if (tyDevInit(&pMseDevice->ty_dev, 512, 512, (FUNCPTR)mseTxStart) != OK)
        return (ERROR);

    /* initialize the interface */
    mseHwInit ();

    /* enable the pointer interrupt */
#ifdef USE_BSP_API
    sysWindMLIntEnable (pDev);
#else /* USE_BSP_API */
    intEnable ((int) INT_VEC_MOUSE);
#endif /* USE_BSP_API */

    /* add the device to the I/O system */
    if (iosDevAdd(&pMseDevice->ty_dev.devHdr,name,mseDrvNum) == ERROR)
        return (ERROR);

    return (mseDrvNum);
    }


/*******************************************************************************
*
* mseHwInit - initialize AMBA hardware for mouse support
*
* This routine initializes the AMBA hardware for a PS/2 mouse.
*
* RETURNS N/A
*
* SEE ALSO: 
*/

LOCAL void mseHwInit (void)
    {

    /* disable everything */
    *KMI_CR(KMI1_BASE) = 0;

    /* Clock divisor */
    *KMI_CR(MOUSE_CLK) = KMI_DIVISOR;
        
    /* Enable mouse and interrupts */
    *KMI_CR(MOUSE_CR) = KMI_CR_RXIEN | KMI_CR_KMIEN;

    /* send reset */
    *KMI_CR(MOUSE_DATA) = 0xFF;

    mseDelay();

    /* send enable */
    *KMI_CR(MOUSE_DATA) = 0xF4;

    return;
    }

/*******************************************************************************
*
* mseOpen - open file
*
* This routine opens the PS2 device.
* 
* RETURNS device structure
*
* SEE ALSO: 
*/

LOCAL int mseOpen
    (
    MSE_DEVICE  *dev,
    char        *name,
    int         mode
    )
    {
    return ((int)dev);
    }


/*****************************************************************************
*
*  mseTxStart - send data to mouse
*
* This routine transmits data to the PS2 device
*
* RETURNS  N/A
*
* SEE ALSO: 
*/

LOCAL void mseTxStart
    (
    MSE_DEVICE  *dev
    )
    {
    char          out_char;

    while (tyITx(&dev->ty_dev,&out_char) == OK);
    }

/*****************************************************************************
*
* mseClose - close file
*
*  This routine closes the PS2 device
*
* RETURNS N/A
*
* SEE ALSO: 
*/

LOCAL int mseClose
    (
    MSE_DEVICE  *dev
    )
    {
    return((int)dev);
    }

/*****************************************************************************
*
* ambaMseIntr - handle interrupts
*
* This routine is the PS2 interrupt handler
*
* RETURNS  NA
*
* SEE ALSO: 
*/

LOCAL void ambaMseIntr 
    (
    MSE_DEVICE  *pDev          /* device control structure */
    )
    {
    unsigned char   in_char;

    if (MS_IN(STATUS_AMBA_MS) & KMI_RXFULL)
        {
        in_char = MS_IN(DATA_AMBA_MS);

        tyIRd (&pDev->ty_dev,in_char);
        }
    }

/******************************************************************************
*
* ambaMsCommand - write command to the mouse.
*
* Write command to the mouse.
*
* RETURNS: OK or ERROR if timed out
*/

STATUS ambaMsCommand
    (
    UCHAR command
    )
    {
    MS_OUT (COMMAND_AMBA_MS, command);

    return (OK);
    }

/*******************************************************************************
*
* mseDelay - pause
* 
* This routine is called to introduce some delay
*
* RETURNS: N/A
*
* NOMANUAL
*/
LOCAL void mseDelay(void)
    {
        taskDelay (sysClkRateGet () >> 3);
    }

#endif /* COMMAND_AMBA_MS */
