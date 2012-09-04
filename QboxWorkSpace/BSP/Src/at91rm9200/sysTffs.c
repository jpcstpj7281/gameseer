/* sysTffsStub.c - BSP stub for TrueFFS Socket Component Driver */

/* Copyright 1984-2000 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01e,22may02,nrv  Adding INCLUDE_MTD_CFIAMD
01d,13nov01,nrv  made use of PRJ_BUILD
01c,09nov01,nrv  merging in T3 version with some cleanup
01b,14dec00,yp   Documentation cleanup
01a,29nov00,yp   derived from ads860 sysTffs.c 01j.
*/

/*
This stub file provides the user with the means to create a TrueFFS compliant 
socket component driver for use with any BSP. This is sample code and it is
expected, even required, to be modified after it is added to a BSP by the 
project facility when the component INCLUDE_TFFS is added to a kernel project.
Look for #error and TODO statements in the sample code.

This stub does not provides code, just some procedural macros that the
generic driver code will use.

DESCRIPTION
This library must provide board-specific hardware access routines for TrueFFS.
In effect, these routines comprise the socket component driver (or drivers)
for your flash device.  At socket registration time, TrueFFS stores
the functions provided by this socket component driver in an 'FLSocket'
structure.  When TrueFFS needs to access the flash device, it uses these
functions. 
 
Because this file is, for the most part, a device driver that exports its
functionality by registering function pointers with TrueFFS, very few of the
functions defined here are externally callable.  For the record, the only
external functions are flFitInSocketWindow() and flDelayLoop(), and you should
never have to call them.
 
However, one of the most important functions defined in this file is neither
referenced in an 'FLSocket' structure, nor is it externally callable.  This
function is sysTffsInit() and it should only be called by TrueFFS.  TrueFFS 
calls this function at initialization time to register socket component 
drivers for all the flash devices attached to your target.  It is this call 
to sysTffs() that results in assigning drive numbers to the flash devices on 
your target hardware.  Drive numbers are assigned by the order in which the 
socket component drivers are registered. The first to be registered is drive 
0, the second is drive 1, and so on up to 4.  As shipped, TrueFFS supports up 
to five flash drives.
 
After registering socket component drivers for a flash device, you may
format the flash medium even though there is not yet a block device driver
associated with the flash (see the reference entry for the tffsDevCreate()
routine).  To format the flash medium for use with TrueFFS,
call tffsDevFormat() or, for some BSPs, sysTffsFormat().
 
The sysTffsFormat() routine is an optional,BSP-specific helper routine that
can be called externally. Internally, sysTffsFormat() calls tffsDevFormat() 
with a pointer to a 'FormatParams' structure that is initialized to values 
that leave a space on the flash device for a boot image. This space is outside 
the region managed by TrueFFS.  This special region is necessary for boot
images because the normal translation and wear-leveling services of TrueFFS
are incompatible with the needs of the boot program and the boot image it
relies upon.  To write a boot image (or any other data) into this area,
use tffsBootImagePut(). 
 
The function sysTffsFormat() is only provided when a Flash SIMM has to have 
the TrueFFS file system in some desired fraction of it. It is provided only 
for the purpose of simplifying the process of formatting a Flash part that 
that should be subdivided.

The Flash SIMM might also be referred to as RFA (Resident Flash Array) in the 
following text.

Example implentations of sysTffs.c can be found in the directory

    $(WIND_BASE)/target/src/drv/tffs/sockets

The files sds860-sysTffs.c and pc386-sysTffs.c have support for single and dual 
socketed PCMCIA devices as well if that might be useful to you. They both 
support multiple sockets.


Finally, this file also contains define statements for symbolic constants
that determine which MTDs, translation layer modules, and other utilities
are ultimately included in TrueFFS.  These defines are as follows:

.IP "INCLUDE_TL_FTL"
To include the NOR-based translation layer module.
.IP "INCLUDE_TL_SSFDC"
To include the SSFDC-appropriate translation layer module.
.IP "INCLUDE_MTD_I28F016"
For Intel 28f016 flash devices.
.IP "INCLUDE_MTD_I28F008"
For Intel 28f008 flash devices.
.IP "INCLUDE_MTD_I28F008_BAJA"
For Intel 28f008 flash devices on the Heurikon Baja 4700.
.IP "INCLUDE_MTD_AMD"
For AMD, Fujitsu: 29F0{40,80,16} 8-bit flash devices.
.IP "INCLUDE_MTD_CFIAMD"
For CFI compliant AMD, Fujitsu flash devices.
.IP "INCLUDE_MTD_CFISCS"
For CFI/SCS flash devices.
.IP "INCLUDE_MTD_WAMD"
For AMD, Fujitsu 29F0{40,80,16} 16-bit flash devices.
.IP "INCLUDE_TFFS_BOOT_IMAGE"
To include tffsBootImagePut() in TrueFFS for Tornado.
.LP
To exclude any of the modules mentioned above, edit sysTffs.c and undefine
its associated symbolic constant.


INCLUDE FILES: flsocket.h, tffsDrv.h
*/

/*#error "sysTffs : Verify system macros and function before first use"*/

/* includes */

#include "vxWorks.h"
#include "config.h"
#include "tffs/flsocket.h"
#include "tffs/tffsDrv.h"


/* defines */

#undef	INCLUDE_MTD_I28F016		/* Intel: 28f016 */
#undef	INCLUDE_MTD_I28F008		/* Intel: 28f008 */                             /*modified by zys      060714*/
#undef	INCLUDE_MTD_AMD			/* AMD, Fujitsu: 29f0{40,80,16} 8bit */
#undef	INCLUDE_MTD_CDSN		/* Toshiba, Samsung: NAND, CDSN */
#undef	INCLUDE_MTD_DOC2		/* Toshiba, Samsung: NAND, DOC */
#undef	INCLUDE_MTD_CFISCS		/* CFI/SCS */
#define	INCLUDE_MTD_WAMD		/* AMD, Fujitsu: 29f0{40,80,16} 16bit */
#undef	INCLUDE_TL_NFTL			/* NFTL translation layer */
#define	INCLUDE_TL_FTL			/* FTL translation layer */
#undef	INCLUDE_TL_SSFDC		/* SSFDC translation layer */
#undef   INCLUDE_TFFS_BOOT_IMAGE		/* include tffsBootImagePut() */
#define	FLASH_BASE_ADRS		0x30C00000	/* Flash memory base address */
#define	FLASH_SIZE		0x00400000	/* Flash memory size */


/* locals */


/* forward declarations */

LOCAL void		rfaWriteProtect (void);
LOCAL void		rfaWriteEnable (void);
LOCAL FLBoolean		rfaCardDetected (FLSocket vol);
LOCAL void		rfaVccOn (FLSocket vol);
LOCAL void		rfaVccOff (FLSocket vol);
#ifdef	SOCKET_12_VOLTS
LOCAL FLStatus		rfaVppOn (FLSocket vol);
LOCAL void		rfaVppOff (FLSocket vol);
#endif	/* SOCKET_12_VOLTS */
LOCAL FLBoolean		rfaGetAndClearCardChangeIndicator (FLSocket vol);
LOCAL FLBoolean		rfaWriteProtected (FLSocket vol);
LOCAL void		rfaSetWindow (FLSocket vol);
LOCAL void		rfaSetMappingContext (FLSocket vol, unsigned page);
LOCAL FLStatus		rfaSocketInit (FLSocket vol);
LOCAL FLStatus		rfaRegister (void);

#ifndef DOC
#include "tffs/tffsConfig.c"
#endif /* DOC */

/*******************************************************************************
*
* sysTffsInit - board level initialization for TFFS
*
* This routine calls the socket registration routines for the socket component
* drivers that will be used with this BSP. The order of registration signifies
* the logical drive number assigned to the drive associated with the socket.
*
* RETURNS: N/A
*/

LOCAL void sysTffsInit (void)
    {

    (void)rfaRegister ();
    }

/*******************************************************************************
*
* rfaRegister - install routines for the Flash RFA
*
* This routine installs necessary functions for the Resident Flash Array(RFA).
*
* RETURNS: N/A
*/

LOCAL FLStatus rfaRegister (void)
    {
    FLSocket vol = flSocketOf (noOfDrives);

    if (noOfDrives >= DRIVES)
        return (flTooManyComponents);

    tffsSocket[noOfDrives] = "RFA";
    noOfDrives++;

    vol.serialNo = 0;
    vol.window.baseAddress = FLASH_BASE_ADRS >> 12;

    /* fill in function pointers */

    vol.cardDetected      = rfaCardDetected;
    vol.VccOn             = rfaVccOn;
    vol.VccOff            = rfaVccOff;
#ifdef SOCKET_12_VOLTS
    vol.VppOn =			rfaVppOn;
    vol.VppOff =		rfaVppOff;
#endif
    vol.initSocket        = rfaSocketInit;
    vol.setWindow         = rfaSetWindow;
    vol.setMappingContext = rfaSetMappingContext;
    vol.getAndClearCardChangeIndicator =
                          rfaGetAndClearCardChangeIndicator;
    vol.writeProtected    = rfaWriteProtected;

    return (flOK);
    }

/*******************************************************************************
*
* rfaCardDetected - detect if a card is present (inserted)
*
* This routine detects if a card is present (inserted).
* Always return TRUE in RFA environments since device is not removable.
*
* RETURNS: TRUE, or FALSE if the card is not present.
*/

LOCAL FLBoolean rfaCardDetected
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    return (TRUE);
    }

/*******************************************************************************
*
* rfaVccOn - turn on Vcc (3.3/5 Volts)
*
* This routine turns on Vcc (3.3/5 Volts).  Vcc must be known to be good
* on exit. Assumed to be ON constantly in RFA environment.
*
* RETURNS: N/A
*/

LOCAL void rfaVccOn
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    rfaWriteEnable ();
    }

/*******************************************************************************
*
* rfaVccOff - turn off Vcc (3.3/5 Volts)
*
* This routine turns off Vcc (3.3/5 Volts) (PCMCIA). Assumed to be ON 
* constantly in RFA environment.
*
* RETURNS: N/A
*/

LOCAL void rfaVccOff
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    rfaWriteProtect ();
    }

#ifdef SOCKET_12_VOLTS

/*******************************************************************************
*
* rfaVppOn - turns on Vpp (12 Volts)
*
* This routine turns on Vpp (12 Volts). Vpp must be known to be good on exit.
* Assumed to be ON constantly in RFA environment. This is not optional and 
* must always be implemented. 
*
* RETURNS: flOK always.
*/

LOCAL FLStatus rfaVppOn
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    return (flOK);
    }

/*******************************************************************************
*
* rfaVppOff - turns off Vpp (12 Volts)
*
* This routine turns off Vpp (12 Volts). Assumed to be ON constantly 
* in RFA environment.This is not optional and must always be implemented.
*
* RETURNS: N/A
*/

LOCAL void rfaVppOff
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    }

#endif	/* SOCKET_12_VOLTS */

/*******************************************************************************
*
* rfaInitSocket - perform all necessary initializations of the socket
*
* This routine performs all necessary initializations of the socket.
*
* RETURNS: flOK always.
*/

LOCAL FLStatus rfaSocketInit
    (
    FLSocket vol		/* pointer identifying drive */
    ) 
    {
    rfaWriteEnable ();

    vol.cardChanged = FALSE;

    /* enable memory window and map it at address 0 */
    rfaSetWindow (&vol);

    return (flOK);
    }

/*******************************************************************************
*
* rfaSetWindow - set current window attributes, base address, size, etc
*
* This routine sets current window hardware attributes: Base address, size,
* speed and bus width.  The requested settings are given in the 'vol.window' 
* structure.  If it is not possible to set the window size requested in
* 'vol.window.size', the window size should be set to a larger value, 
* if possible. In any case, 'vol.window.size' should contain the 
* actual window size (in 4 KB units) on exit.
*
* RETURNS: N/A
*/

    /* TODO: set this to your specific needs */

LOCAL void rfaSetWindow
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    /* Physical base as a 4K page */

    vol.window.baseAddress = FLASH_BASE_ADRS >> 12;

    flSetWindowSize (&vol, FLASH_SIZE >> 12);
    }

/*******************************************************************************
*
* rfaSetMappingContext - sets the window mapping register to a card address
*
* This routine sets the window mapping register to a card address.
* The window should be set to the value of 'vol.window.currentPage',
* which is the card address divided by 4 KB. An address over 128MB,
* (page over 32K) specifies an attribute-space address. On entry to this 
* routine vol.window.currentPage is the page already mapped into the window.
* (In otherwords the page that was mapped by the last call to this routine.)
* The page to map is guaranteed to be on a full window-size boundary.
* This is meaningful only in environments that use sliding window mechanism
* to view flash memory, like in PCMCIA. Not common in RFA environments. 
*
* RETURNS: N/A
*/

LOCAL void rfaSetMappingContext
    (
    FLSocket vol,		/* pointer identifying drive */
    unsigned page		/* page to be mapped */
    )
    {
    }

/*******************************************************************************
*
* rfaGetAndClearCardChangeIndicator - return the hardware card-change indicator
*
* This routine returns TRUE if the card has been changed and FALSE if not. It
* also clears the "card-changed" indicator if it has been set.
* Always return FALSE in RFA environments since device is not removable.
*
* RETURNS: FALSE, or TRUE if the card has been changed
*/

LOCAL FLBoolean rfaGetAndClearCardChangeIndicator
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    return (FALSE);
    }

/*******************************************************************************
*
* rfaWriteProtected - return the write-protect state of the media
*
* This routine returns the write-protect state of the media
*
* RETURNS: FALSE, or TRUE if the card is write-protected
*/

LOCAL FLBoolean rfaWriteProtected
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    return (FALSE);
    }

/*******************************************************************************
*
* rfaWriteProtect - disable write access to the RFA
*
* This routine disables write access to the RFA.
*
* RETURNS: N/A
*/

LOCAL void rfaWriteProtect (void)
    {
    /* clear GPOEN1 bit (#17), make sure GPIO1 bit (#13) is clear  */
    /**VMECHIP2_IOCR = (*VMECHIP2_IOCR) & ((~IOCR_GPOEN1) & (~IOCR_GPIOO1_HIGH));*/
    }

/*******************************************************************************
*
* rfaWriteEnable - enable write access to the RFA
*
* This routine enables write access to the RFA.
*
* RETURNS: N/A
*/

LOCAL void  rfaWriteEnable (void)
    {
    /* set GPOEN1 bit (#17), make sure GPIO1 bit (#13) is clear */
    /**VMECHIP2_IOCR = ((*VMECHIP2_IOCR) | IOCR_GPOEN1) & (~IOCR_GPIOO1_HIGH);*/
    }

/*******************************************************************************
*
* flFitInSocketWindow - check whether the flash array fits in the socket window
*
* This routine checks whether the flash array fits in the socket window.
*
* RETURNS: A chip size guaranteed to fit in the socket window.
*/

long int flFitInSocketWindow 
    (
    long int chipSize,		/* size of single physical chip in bytes */
    int      interleaving,	/* flash chip interleaving (1,2,4 etc) */
    long int windowSize		/* socket window size in bytes */
    )
    {
    if (chipSize*interleaving > windowSize) /* doesn't fit in socket window */
        {
        int  roundedSizeBits;

        /* fit chip in the socket window */
        chipSize = windowSize / interleaving;

        /* round chip size at powers of 2 */
        for (roundedSizeBits = 0; (0x1L << roundedSizeBits) <= chipSize;
             roundedSizeBits++)
	    ;

        chipSize = (0x1L << (roundedSizeBits - 1));
        }

    return (chipSize);
    }

#if	FALSE
/*******************************************************************************
*
* flDelayMsecs - wait for specified number of milliseconds
*
* This routine waits for the specified number of milliseconds.
*
* RETURNS: N/A
*
* NOMANUAL
*/

void * sysTffsCpy
    (
    void *       destination,   /* destination of copy */
    const void * source,        /* source of copy */
    size_t       size           /* size of memory to copy */
    )
    {
    bcopy ((char *) source, (char *) destination, (size_t) size);
    return (destination);
    }

/*******************************************************************************
*
* sysTffsSet - set a block of memory
*
* This routine stores <c> converted to an `unsigned char' in each of the
* elements of the array of `unsigned char' beginning at <m>, with size <size>.
*
* INCLUDE FILES: string.h
*
* RETURNS: A pointer to <m>.
*
* NOMANUAL
*/

void * sysTffsSet
    (
    void * m,                   /* block of memory */
    int    c,                   /* character to store */
    size_t size                 /* size of memory */
    )
    {
    bfill ((char *) m, (int) size, c);
    return (m);
    }
#endif	/* FALSE */

/*******************************************************************************
*
* flDelayLoop - consume the specified time
*
* This routine delays for the specified time.
*
* RETURNS: N/A
*/

void flDelayLoop 
    (
    int  cycles
    )
    {
    while (--cycles)
	;
    }


/*******************************************************************************
*
* sysTffsFormat - format the flash memory above an offset
*
* This routine formats the flash memory.  Because this function defines 
* the symbolic constant, HALF_FORMAT, the lower half of the specified flash 
* memory is left unformatted.  If the lower half of the flash memory was
* previously formated by TrueFFS, and you are trying to format the upper half,
* you need to erase the lower half of the flash memory before you format the
* upper half.  To do this, you could use:
* .CS
* tffsRawio(0, 3, 0, 8)  
* .CE
* The first argument in the tffsRawio() command shown above is the TrueFFS 
* drive number, 0.  The second argument, 3, is the function number (also 
* known as TFFS_PHYSICAL_ERASE).  The third argument, 0, specifies the unit 
* number of the first erase unit you want to erase.  The fourth argument, 8,
* specifies how many erase units you want to erase.  
*
* RETURNS: OK, or ERROR if it fails.
*/
#if 0
STATUS sysTffsFormat (void)
    {
    STATUS status;
    tffsDevFormatParams params = 
	{
	{0x000000l, 99, 1, 0x10000l, NULL, {0,0,0,0}, NULL, 2, 0, NULL},
	FTL_FORMAT_IF_NEEDED
	};

    /* we assume that the drive number 0 is RFA */

    status = tffsDevFormat (0, (int)&params);
    return (status);
    }
#endif
STATUS sysTffsFormat (void)
    {
    STATUS status; 
    tffsDevFormatParams params = 
	{
	{0x000000l, 99, 1, 0x10000l, NULL, {0,0,0,0}, NULL, 2, 0, NULL},
	FTL_FORMAT_IF_NEEDED
	};

    /* we assume that the drive number 0 is SIMM */

    printf( "\nformatFlags=0x%x\n", params.formatFlags ) ;
    printf( "params->formatParams.bootImageLen=0x%x\n", params.formatParams.bootImageLen ) ;
    printf( "params->formatParams.percentUse=0x%x\n", params.formatParams.percentUse ) ;
    printf( "params->formatParams.noOfSpareUnits=0x%x\n", params.formatParams.noOfSpareUnits ) ;
    printf( "params->formatParams.vmAddressingLimit=0x%x\n", params.formatParams.vmAddressingLimit ) ;

    status = tffsDevFormat (0, (int)&params);
    return (status);
    }

