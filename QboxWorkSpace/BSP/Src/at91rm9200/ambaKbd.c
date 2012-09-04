/* ambaKbd.c - ARM AMBA keyboard driver routines */

/* Copyright 1993-2001 Wind River System, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01a,06jul01,m_h  created.
*/

/*
DESCRIPTION
This is the driver for ARM's AMBA PrimeCell keyboard controller chip. This driver
handles the standard 101 keyboard.

NOTES
The following macros must be defined in ambakmi.h file: COMMAND_AMBA_KB,
DATA_AMBA_KB, STATUS_AMBA_KB. These refer to the I/O base addresses of the various 
keyboard controller registers. In addition, the macro KBD_INT_LVL and 
KBD_INT_VEC must be defined that identifies the interrupt level and vector 
that is to be used for the mouse interrupts.  Also the I/O access method 
requires that the macros KBD_IN and KBD_OUT be defined.

Warning: Use kbdIntDisable() to disable interrupts while sending commands to the
keyboard.  Otherwise the KMI keyboard interface chip will no longer produce rx
interrupts.  Use kbdIntEnable() to reenable the interrupts.

*/

/* includes */

#include "vxWorks.h"
#include "iv.h"
#include "ioLib.h"
#include "iosLib.h"
#include "memLib.h"
#include "errnoLib.h"
#include "wdLib.h"
#include "sysLib.h"
#include "intLib.h"
#include "taskLib.h"
#include "ambakmi.h"
#include "ugl/bspExt/bspUtil.h"

#ifdef USE_BSP_API
#include "ugl/sysWindML.h"
#endif

#ifndef COMMAND_AMBA_KB
#warning "Keyboard driver is not initialized for processor"
#else

LOCAL KBD_DEVICE   *  pKbdDevice;    /* device descriptors */
LOCAL int       kbdIntCnt = 0;
LOCAL int       kbdTimeoutCnt = 0;
LOCAL BOOL      kbdTimeout = FALSE;
LOCAL WDOG_ID   kbdWdid;
LOCAL int       kbdWdsec = 2;
LOCAL UCHAR     oldLedStat = 0;
LOCAL BOOL      kbdAcknowledge = FALSE;

/* forward declarations */

LOCAL void      kbdStatInit (void);
LOCAL void      kbdLedSet (void);
LOCAL void      kbdWdog (void);
LOCAL int       kbdWriteData (KBD_DEVICE * pKbdDv);
LOCAL void      kbdIntr (void);
LOCAL int       kbdDrvOpen ();
LOCAL STATUS    kbdDrvIoctl (KBD_DEVICE * pKbdDv, int request, int arg);
LOCAL void      kbdDrvHwInit (void);
LOCAL void      kbdHwInit (void);
LOCAL void      kbdDelay (void);
LOCAL void      kbdIntDisable (void);
LOCAL void      kbdIntEnable (void);

#ifdef USE_BSP_API
int ambaKbdRegBase, ambaKbdRegDelta;
#endif

/* scan code->key number conversion table for
 *  an extended AT keyboard in mode 2
 */
int scanmap_mode2[256] =
    {
    0,    /*  0   */
    120,  /*  1   */           
    0,    /*  2   */           
    116,  /*  3   */           
    114,  /*  4   */           
    112,  /*  5   */           
    113,  /*  6   */           
    123,  /*  7   */           
    0,    /*  8   */           
    121,  /*  9   */           
    119,  /*  A   */           
    117,  /*  B   */           
    115,  /*  C   */           
    16,   /*  D   */           
    1,    /*  E   */           
    0,    /*  F   */           
    0,    /*  10  */           
    60,   /*  11  */           
    44,   /*  12  */           
    0,    /*  13  */           
    58,   /*  14  */           
    17,   /*  15  */           
    2,    /*  16  */           
    0,    /*  17  */           
    0,    /*  18  */           
    0,    /*  19  */           
    46,   /*  1A  */           
    32,   /*  1B  */           
    31,   /*  1C  */           
    18,   /*  1D  */           
    3,    /*  1E  */           
    128,  /*  1F  */           
    0,    /*  20  */           
    48,   /*  21  */           
    47,   /*  22  */           
    33,   /*  23  */           
    19,   /*  24  */           
    5,    /*  25  */           
    4,    /*  26  */           
    129,  /*  27  */           
    0,    /*  28  */           
    61,   /*  29  */           
    49,   /*  2A  */           
    34,   /*  2B  */           
    21,   /*  2C  */           
    20,   /*  2D  */           
    6,    /*  2E  */           
    130,  /*  2F  */           
    0,    /*  30  */           
    51,   /*  31  */           
    50,   /*  32  */           
    36,   /*  33  */           
    35,   /*  34  */           
    22,   /*  35  */           
    7,    /*  36  */           
    0,    /*  37  */           
    0,    /*  38  */           
    0,    /*  39  */           
    52,   /*  3A  */           
    37,   /*  3B  */           
    23,   /*  3C  */           
    8,    /*  3D  */           
    9,    /*  3E  */           
    0,    /*  3F  */           
    0,    /*  40  */           
    53,   /*  41  */           
    38,   /*  42  */           
    24,   /*  43  */           
    25,   /*  44  */           
    11,   /*  45  */           
    10,   /*  46  */           
    0,    /*  47  */           
    0,    /*  48  */           
    54,   /*  49  */           
    55,   /*  4A  */           
    39,   /*  4B  */           
    40,   /*  4C  */           
    26,   /*  4D  */           
    12,   /*  4E  */           
    0,    /*  4F  */           
    0,    /*  50  */           
    0,    /*  51  */           
    41,   /*  52  */           
    0,    /*  53  */           
    27,   /*  54  */           
    13,   /*  55  */           
    0,    /*  56  */           
    0,    /*  57  */           
    30,   /*  58  */           
    57,   /*  59  */           
    43,   /*  5A  */           
    28,   /*  5B  */           
    0,    /*  5C  */           
    29,   /*  5D  */           
    0,    /*  5E  */           
    0,    /*  5F  */           
    0,    /*  60  */           
    45,   /*  61  */           
    0,    /*  62  */           
    0,    /*  63  */           
    0,    /*  64  */           
    0,    /*  65  */           
    15,   /*  66  */           
    0,    /*  67  */           
    0,    /*  68  */           
    93,   /*  69  */           
    0,    /*  6A  */           
    92,   /*  6B  */           
    91,   /*  6C  */           
    0,    /*  6D  */           
    0,    /*  6E  */           
    0,    /*  6F  */           
    99,   /*  70  */           
    104,  /*  71  */           
    98,   /*  72  */           
    97,   /*  73  */           
    102,  /*  74  */           
    96,   /*  75  */           
    110,  /*  76  */           
    90,   /*  77  */           
    122,  /*  78  */           
    106,  /*  79  */           
    103,  /*  7A  */           
    105,  /*  7B  */           
    100,  /*  7C  */           
    101,  /*  7D  */           
    125,  /*  7E  */           
    0,    /*  7F  */           
    0,    /*  80  */           
    0,    /*  81  */           
    0,    /*  82  */           
    118,  /*  83  */           
    0,    /*  84  */           
    0,    /*  85  */
    0,    /*  86  */
    0,    /*  87  */
    0,    /*  88  */
    0,    /*  89  */
    0,    /*  8A  */
    0,    /*  8B  */
    0,    /*  8C  */
    0,    /*  8D  */
    0,    /*  8E  */
    0,    /*  8F  */
    /* no keys with codes > 0x8F */
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    };

/******************************************************************************
*
* ambaKbdDevCreate - create a device for the on-board ports
*
* This routine creates a device on the AMBA keyboard port.  Each port
* to be used should have only one device associated with it, by calling
* this routine.
*
* RETURNS: OK, or ERROR if there is no driver or one already exists for the
* specified port.
*/

STATUS ambaKbdDevCreate
    (
    char *  name       /* name to use for this device */
    )
    {
    int        kbdDrvNum;      /* driver number assigned to this driver */
    DEV_HDR   *pHdr;
    char      *pName;
#ifdef USE_BSP_API
    WINDML_DEVICE *pDev;
#endif

    /* if device is already present, do not create again */
    pHdr = iosDevFind (name, &pName);
    if ((pHdr != NULL) && (strcmp (name, pHdr->name) == 0))
        {
        pKbdDevice = (KBD_DEVICE *)pHdr;
        return (OK);
        }
    
    pKbdDevice = (KBD_DEVICE *)malloc (sizeof (KBD_DEVICE));
    pKbdDevice->kbdFlags = 0;

    /* enable the keybord interrupt */
    
#ifdef USE_BSP_API
    pDev = sysWindMLDevGet (WINDML_KEYBOARD_DEVICE, 0, 0, 0);

    ambaKbdRegBase = (int)(pDev->pRegBase);
    ambaKbdRegDelta = pDev->regDelta;
    sysWindMLIntConnect (pDev, kbdIntr, (int)pKbdDevice);
#else /* USE_BSP_API */
    (void) intConnect (INT_LVL_KEYBOARD, kbdIntr, (int)pKbdDevice);
#endif /* USE_BSP_API */

    kbdDrvHwInit ();
    kbdDrvNum = iosDrvInstall (kbdDrvOpen, (FUNCPTR) NULL, kbdDrvOpen,
                    (FUNCPTR) NULL, tyRead, tyWrite, kbdDrvIoctl);

    if (kbdDrvNum == ERROR)
        {
        return (ERROR);
        }

    if (tyDevInit (&pKbdDevice->tyDev, 20, 10, kbdWriteData)
        != OK)
        {
        return (ERROR);
        }

#ifdef USE_BSP_API
    sysWindMLIntEnable (pDev);
#else /* USE_BSP_API */
    intEnable ((int) INT_VEC_KEYBOARD);
#endif /* USE_BSP_API */

    /* add the device to the I/O system */
    return (iosDevAdd (&pKbdDevice->tyDev.devHdr, name, kbdDrvNum));
    }

/******************************************************************************
*
* kbdDrvHwInit - initialize the Keyboard
*/

LOCAL void kbdDrvHwInit (void)
    {
    FAST int    oldlevel;   /* to hold the oldlevel of interrupt */

    oldlevel= intLock ();

    /* Keyboard initialization */

    kbdHwInit ();

    /* interrupt is masked out: the keyboard interrupt will be enabled
     * in the kbdDevCreate 
     */

    intUnlock (oldlevel);

    }

/*******************************************************************************
*
* kbdDrvOpen - open file to Console
*
*/

LOCAL int kbdDrvOpen 
    (
    KBD_DEVICE *    pKbdDv,
    char *          name,
    int             mode
    )
    {
    return ((int) pKbdDv);
    }

/*******************************************************************************
*
* kbdDrvIoctl - special device control
*
* This routine handles FIOGETOPT requests and passes all others to tyIoctl.
*
* RETURNS: OK or ERROR if invalid baud rate, or whatever tyIoctl returns.
*/

LOCAL STATUS kbdDrvIoctl 
    (
    KBD_DEVICE *    pKbdDv,    /* device to control */
    int             request,    /* request code */
    int             arg         /* some argument */
    )
    {
    int     status = OK;

    switch (request)
        {    
        case CONIOCURCONSOLE:   /* change current console */
            break;

        case CONIOCONVERTSCAN:      /* send scan codes vs. ASCII */
            break;

        case CONIOLEDS:         /* change LEDs */
            pKbdDv->kbdFlags = arg;
            kbdLedSet ();
            break;

        default:
            status = tyIoctl (&pKbdDv->tyDev, request, arg);
            break;
        }

    return (status);
    }

/*******************************************************************************
*
* kbdWriteData - write data to device
*
* This routine the write function from the I/O subsystem.
*
* RETURNS: 
*/

LOCAL int kbdWriteData 
    (
    KBD_DEVICE *    pKbdDv    /* device to control */
    )
    {

        return (0);
    }


/*******************************************************************************
*
* kbdHwInit - initialize the Keyboard
* 
* This routine is called to do the keyboard initialization from an external
* routine
*
* RETURNS: N/A
*
* NOMANUAL
*/


LOCAL void kbdHwInit (void)
    {

    UCHAR reply;
    int  timeout = 3;
    kbdWdid = wdCreate ();

    /* disable everything */
    KBD_OUT (COMMAND_AMBA_KB, 0);

    do 
        {
        /* Clock divisor */
        KBD_OUT (KEYB_CLK, KMI_DIVISOR);
        
        /* Enable keyboard but not interrupts */
        KBD_OUT (COMMAND_AMBA_KB, KMI_CR_KMIEN);

        KBD_OUT (DATA_AMBA_KB, 0xFF);
        if (ambaKBRead(&reply) != OK)
            continue;
        if (reply != 0xfa && reply != 0xaa)
            continue;
        if (ambaKBRead(&reply) != OK)
            continue;
        if (reply != 0xfa && reply != 0xaa)
            continue;

        /* mode 1 produces XT scan codes */
        KBD_OUT (DATA_AMBA_KB, 0xF0);
        if (ambaKBRead(&reply) != OK)
            continue;
        KBD_OUT (DATA_AMBA_KB, 0x01);
        if (ambaKBRead(&reply) != OK)
            continue;

        /* enable */
        KBD_OUT (DATA_AMBA_KB, 0xF4);
        if (ambaKBRead(&reply) != OK)
            continue;

        /* repeat rate */
        KBD_OUT (DATA_AMBA_KB, 0xf3);
        if (ambaKBRead(&reply) != OK)
            continue;
        /* .25 sec delay, 30/sec */
        KBD_OUT (DATA_AMBA_KB, 0x00);
        if (ambaKBRead(&reply) != OK)
            continue;
        
        /* Enable interrupts */
        KBD_OUT (COMMAND_AMBA_KB, KMI_CR_RXIEN | KMI_CR_KMIEN);

        break;

        } while (timeout--);

    kbdStatInit ();

    } 

/*******************************************************************************
*
* kbdStatInit - initialize the Keyboard state
*
* This routine initializes the keyboard descriptor in the virtual consoles.
* The same keyboard descriptor is used for all the virtual consoles.
*
* RETURNS: N/A
*/


LOCAL void kbdStatInit (void)
    {
    UCHAR   stat, reply;
    int     timeout = 3;
    
    pKbdDevice->kbdFlags = NUM; /* Numeric mode on */

    stat = (UCHAR) (pKbdDevice->kbdFlags & 0x07);

    if (oldLedStat == stat)
        return;
    oldLedStat = stat;

    do 
        {

        if (ambaKBWrite (0xed) == ERROR)
            continue;
        if (ambaKBRead(&reply) == ERROR)
            continue;

        if (ambaKBWrite (stat) == ERROR)
            continue;
        if (ambaKBRead(&reply) == ERROR)
            continue;

        break;

        } while (--timeout);
    }

/*******************************************************************************
*
* kbdIntr - interrupt level processing
*
* This routine handles the keyboard interrupts
*
* RETURNS: N/A
*
* NOMANUAL
*/

LOCAL void kbdIntr (void)
    {
    FAST UCHAR  scanCode;   /* to hold the scanCode */
    UCHAR stat = KBD_IN (STATUS_AMBA_KB); 

    kbdIntCnt++;
    
    if (stat & KMI_RXFULL)
        {
        int par, temp, n;

        temp = scanCode = KBD_IN (DATA_AMBA_KB);

        /* check parity */
        par = (KBD_IN (STATUS_AMBA_KB) & KMI_PARITY) ? 1 : 0;
        for (n = 8; n > 0; n--)
            {
            par ^= (temp & 0x01);
            temp = temp >> 1;
            }
        if (!par)
            {
            /* parity failed - request retransmission */
            if (!(KBD_IN (STATUS_AMBA_KB) & KMI_TXBUSY))
                {
                /* send a retransmit command if we can */
                KBD_OUT (DATA_AMBA_KB, 0xFE);
                }
            return;
            }

        /* keyboard acknowledge to any valid input, so just return */
        if (scanCode == 0xfa) 
            {
            kbdAcknowledge = TRUE;
            return;
            }
        tyIRd (&(pKbdDevice->tyDev), scanCode);
        }
    }


/******************************************************************************
*
* kbdLedSet - Keybord LED Set
*
* This routine Keyboad LED control on kbdConDv.kbdFlags numeric, caps and
* stps
*
* RETURNS: N/A
*/

LOCAL void kbdLedSet (void)
    {
    UCHAR   stat = 0;
    int     timeout;
    UCHAR   reply;

    /* bits 0 1 2 for scroll numlock & capslock */
    stat = (UCHAR) (pKbdDevice->kbdFlags & 0x07);

    if (oldLedStat == stat)
        return;
    oldLedStat = stat;

    timeout = 3;

    do
        {

        kbdDelay();

        kbdIntDisable();

        ambaKBWrite(0xed);       /* SET LEDS command */
        if (ambaKBRead(&reply) != OK)
            continue;

        ambaKBWrite(stat);       /* set LEDs */
        if (ambaKBRead(&reply) == OK)
            break;

        } while (--timeout >= 0);
        
        kbdIntEnable();

    }

/******************************************************************************
*
* ambaKBRead - read data from the keyboard.
*
* Read data from the keyboard.
*
* RETURNS: OK or ERROR if timed out
*/

STATUS ambaKBRead
    (
    UCHAR *pData
    )
    {

    kbdTimeout = FALSE;
    wdStart (kbdWdid, (sysClkRateGet() * kbdWdsec), (FUNCPTR)kbdWdog, 0);

    while (((KBD_IN (STATUS_AMBA_KB) & KMI_RXFULL) == 0) && !kbdTimeout)
        ;

    wdCancel (kbdWdid);

    kbdDelay();

    *pData = KBD_IN (DATA_AMBA_KB);

    return (kbdTimeout ? ERROR : OK);
    }

/******************************************************************************
*
* ambaKBWrite - write data to the keyboard.
*
* Write data to the keyboard.
*
* RETURNS: OK or ERROR if timed out
*/

STATUS ambaKBWrite
    (
    UCHAR data
    )
    {

    kbdTimeout = FALSE;

    wdStart (kbdWdid, (sysClkRateGet() * kbdWdsec), (FUNCPTR)kbdWdog, 0);

    while ((KBD_IN (STATUS_AMBA_KB) & KMI_TXBUSY) && !kbdTimeout)
        ;

    wdCancel (kbdWdid);

    KBD_OUT (DATA_AMBA_KB, data);

    return (kbdTimeout ? ERROR : OK);
    }

/******************************************************************************
*
* ambaKBCommand - write command to the keyboard.
*
* Write command to the keyboard.
*
* RETURNS: OK or ERROR if timed out
*/

STATUS ambaKBCommand
    (
    UCHAR command
    )
    {

    KBD_OUT (COMMAND_AMBA_KB, command);

    return (OK);
    }

/******************************************************************************
*
* kbdWdog - KBD driver watchdog handler.
*
* KBD driver watchdog handler.
*
* RETURNS: N/A
*/

LOCAL void kbdWdog
    (
    void
    )
    {
    kbdTimeout = TRUE;
    kbdTimeoutCnt++;
    }

/*******************************************************************************
*
* kbdDelay - pause
* 
* This routine is called to introduce some delay
*
* RETURNS: N/A
*
* NOMANUAL
*/
LOCAL void kbdDelay(void)
    {
        taskDelay (sysClkRateGet () >> 3);
    }

/*******************************************************************************
*
* kbdIntDisable - disable keyboard interrupts 
* 
* This routine disables interrupts from being generated by the keyboard controller
*
* RETURNS: N/A
*
* NOMANUAL
*/
LOCAL void kbdIntDisable (void)
    {

    /* Disable interrupts */
    KBD_OUT (COMMAND_AMBA_KB, KMI_CR_KMIEN);

    }

/*******************************************************************************
*
* kbdIntEable - enable keyboard interrupts 
* 
* This routine re-enables Rx interrupts to be generated by the keyboard controller
*
* RETURNS: N/A
*
* NOMANUAL
*/
LOCAL void kbdIntEnable (void)
    {
    
    /* Enable interrupts */
    KBD_OUT (COMMAND_AMBA_KB, KMI_CR_RXIEN | KMI_CR_KMIEN);
    
    }

#endif /* COMMAND_AMBA_KB */
