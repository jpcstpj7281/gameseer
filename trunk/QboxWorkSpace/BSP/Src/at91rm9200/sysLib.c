/* sysLib.c - AT91RM9200 system-dependent routines */

/* Copyright 1999-2001 ARM Limited */
/* Copyright 1999-2001 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
01q,28may02,m_h  windML not UGL
01p,31oct01,rec  use generic driver for amba timer
01o,09oct01,m_h  configure keyboard if windML is configured
01n,09oct01,jpd  correct sysPhysMemDesc entres for 946es.
01m,03oct01,jpd  tidied slightly
01l,28sep01,pr   added support for ARM946E.
01k,12sep01,m_h  WindML support
01j,27aug01,jb   Adding USB support
01i,21feb01,h_k  added support for ARM966ES and ARM966ES_T.
01h,01dec00,rec  fix typo in INCLUDE_FEI82557END
01g,20nov00,jpd  added support for Intel Ethernet driver.
01f,14jun00,pr   fixed Flash enable/disable with recent versions of FPGA.
01e,18feb00,jpd  minor tidying. Added Core Module Header sysPhysMemDesc entry.
01d,07feb00,jpd  added support for ARM720T, ARM920T.
01c,13jan00,pr	 added support for ARM740T.
01b,07dec99,pr	 added support for PCI.
01a,15nov99,ajb  copied from pid7t version 01o.
*/

/*
DESCRIPTION
This library provides board-specific routines for the ARM Integrator
Development Board BSP.

It #includes the following chip drivers:
    nullVme.c -         dummy VMEbus routines
    ambaTimer.c -       AMBA timer driver
    ambaIntrCtl.c -     AMBA interrupt controller driver
    primeCellSio.c -	PrimeCell UART driver
    pciIomapLib.c -	PCI I/O mapping support
if INCLUDE_FLASH is defined, it #includes:
    flashMem.c -        Flash memory driver
    nvRamToFlash.c -    driver to use some Flash like NVRAM
else it #includes:
    nullNvRam.c -	dummy NVRAM routines

It #includes the following BSP files:
    sysSerial.c -	serial device initialisation routines
    sysEnd.c -		END network driver support routines.
    pciIomapShow.c -	PCI Show routines

INCLUDE FILES: sysLib.h string.h intLib.h taskLib.h vxLib.h muxLib.h
	       pciIomapLib.h

SEE ALSO:
.pG "Configuration"
.I "ARM Architecture Reference Manual,"
.I "ARM 7TDMI Data Sheet,"
.I "ARM 720T Data Sheet,"
.I "ARM 740T Data Sheet,"
.I "ARM 920T Technical Reference Manual",
.I "ARM 940T Technical Reference Manual",
.I "ARM 946E-S Technical Reference Manual",
.I "ARM 966E-S Technical Reference Manual",
.I "ARM Reference Peripherals Specification,"
.I "ARM Integrator/AP User Guide",
.I "ARM Integrator/CM7TDMI User Guide",
.I "ARM Integrator/CM720T User Guide",
.I "ARM Integrator/CM740T User Guide",
.I "ARM Integrator/CM920T User Guide",
.I "ARM Integrator/CM940T User Guide",
.I "ARM Integrator/CM946E User Guide",
.I "ARM Integrator/CM9x6ES Datasheet".
*/

/* includes */

#include "vxWorks.h"
#include "config.h"

#include "sysLib.h"
#include "string.h"
#include "intLib.h"
#include "taskLib.h"
#include "vxLib.h"
#include "muxLib.h"
#include "cacheLib.h"
#if defined(CPU_720T)  || defined(CPU_720T_T) || \
    defined(CPU_740T)  || defined(CPU_740T_T) || \
    defined(CPU_920T)  || defined(CPU_920T_T) || \
    defined(CPU_940T)  || defined(CPU_940T_T) || \
    defined(CPU_946ES) || defined(CPU_946ES_T)
#include "arch/arm/mmuArmLib.h"
#include "private/vmLibP.h"
#include "dllLib.h"
/*#include "pciIomapLib.h"*/
#endif /* defined(720T/740T/920T/940T/946ES) */

/* imports */

IMPORT char end [];			    /* end of system, created by ld */
IMPORT VOIDFUNCPTR _func_armIntStackSplit;  /* ptr to fn to split stack */



#if !defined(INCLUDE_MMU) && \
    (defined(INCLUDE_CACHE_SUPPORT) || defined(INCLUDE_MMU_BASIC) || \
     defined(INCLUDE_MMU_FULL) || defined(INCLUDE_MMU_MPU))
#define INCLUDE_MMU
#endif

#if defined(INCLUDE_CACHE_SUPPORT)
#if defined(CPU_7TDMI) || defined(CPU_7TDMI_T) || \
    defined(CPU_966ES) || defined(CPU_966ES_T)
       FUNCPTR sysCacheLibInit = NULL;
#endif /* defined(CPU_7TDMI/7TDMI_T) */

#if	defined(CPU_940T) || defined(CPU_940T_T)
UINT32 * sysCacheUncachedAdrs = (UINT32 *)SYS_CACHE_UNCACHED_ADRS;
#endif /* defined(CPU_940T/940T_T) */
#endif /* defined(INCLUDE_CACHE_SUPPORT) */


/* globals */

#if defined(INCLUDE_MMU)
#if defined(CPU_720T)  || defined(CPU_720T_T) || \
    defined(CPU_740T)  || defined(CPU_740T_T) || \
    defined(CPU_920T)  || defined(CPU_920T_T) || \
    defined(CPU_940T)  || defined(CPU_940T_T) || \
    defined(CPU_946ES) || defined(CPU_946ES_T)

#if defined(CPU_720T) || defined(CPU_720T_T) || \
    defined(CPU_920T) || defined(CPU_920T_T)
/*
 * The following structure describes the various different parts of the
 * memory map to be used only during initialisation by
 * vm(Base)GlobalMapInit() when INCLUDE_MMU_BASIC/FULL are
 * defined.
 *
 * Clearly, this structure is only needed if the CPU has an MMU!
 *
 * The following are not the smallest areas that could be allocated for a
 * working system. If the amount of memory used by the page tables is
 * critical, they could be reduced.
 */

PHYS_MEM_DESC sysPhysMemDesc [] =
    {
    /* adrs and length parameters must be page-aligned (multiples of 0x1000) */
   /* Internal RAM */
    {
    (void *) 0,	/* virtual address */
    (void *) 0,	/* physical address */
    ROUND_UP (AT91C_SRAM_SIZE, PAGE_SIZE), /* length, then initial state: */
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE
    },

    /* DRAM */
    {
    (void *) LOCAL_MEM_LOCAL_ADRS,	/* virtual address */
    (void *) LOCAL_MEM_LOCAL_ADRS,	/* physical address */
    ROUND_UP (0x4000000, PAGE_SIZE),/*ROUND_UP (LOCAL_MEM_SIZE, PAGE_SIZE),  length, then initial state: */
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE
    },

	{
    (void *) 0x70000000,	/* virtual address */
    (void *) 0x70000000,	/* physical address */
	ROUND_UP (0x1000000, PAGE_SIZE),
	VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
	VM_STATE_VALID	| VM_STATE_WRITABLE  | VM_STATE_CACHEABLE_NOT
	},
	
	{
    (void *) 0x50000000,	/* virtual address */
    (void *) 0x50000000,	/* physical address */
	ROUND_UP (0x1000000, PAGE_SIZE),
	VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
	VM_STATE_VALID	| VM_STATE_WRITABLE  | VM_STATE_CACHEABLE_NOT
	},
		

#if     (USER_RESERVED_MEM > 0)
    /* Reserved RAM on system bus - Used for Buffer Descriptor and Buffer */
    {
    (void*)SYS_MEM_TOP,
    (void*)SYS_MEM_TOP,
    USER_RESERVED_MEM,
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID      | VM_STATE_WRITABLE      | VM_STATE_CACHEABLE_NOT
    },
#endif  /* (USER_RESERVED_MEM > 0) */

    /*
     * ROM is normally marked as uncacheable by VxWorks. We leave it like that
     * for the time being, even though this has a severe impact on execution
     * speed from ROM.
     */
    {
    (void *) ROM_BASE_ADRS,
    (void *) ROM_BASE_ADRS,
    ROUND_UP (ROM_SIZE_TOTAL, PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
#ifdef INCLUDE_FLASH
    /* needs to be writable */

    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
#else
    VM_STATE_VALID	| VM_STATE_WRITABLE_NOT  | VM_STATE_CACHEABLE_NOT
#endif
    },
    {
    (void *) 0x30000000,
    (void *) 0x30000000,
    ROUND_UP (0x1000000, PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,

    /* needs to be writable */

    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },
	{
    (void *) 0x40000000,
    (void *) 0x40000000,
    ROUND_UP (0x1000000, PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,

    /* needs to be writable */

    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },

#ifdef INCLUDE_DISPLAY
    {
    (void *) S1D13806_BASE,	/* Core Module Header regs */
    (void *) S1D13806_BASE,
    ROUND_UP (0x200000, PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },

    {
    (void *) (S1D13806_BASE+ 0x200000),	/* Core Module Header regs */
    (void *) (S1D13806_BASE+ 0x200000),
    ROUND_UP (0x140000, PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },

#endif


/* for usb host  */  
#ifdef INCLUDE_USB 
    {
    (void *) AT91C_BASE_UHP,	/* Core Module Header regs */
    (void *) AT91C_BASE_UHP,
    PAGE_SIZE,
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },
#endif

#ifdef INCLUDE_PCMCIA
    {
    (void *) 0x50000000,	/* Core Module Header regs */
    (void *) 0x50000000,
    ROUND_UP ((1<<24), PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },
#endif
    /* Interal Register */
    /*
     * I/O space:
     * Do not map in all I/O space, only that which has something there.
     * Otherwise we will use all of RAM allocating page tables!
     */
    {
    (void *) AT91C_IO_PHYS_BASE,	/* Core Module Header regs */
    (void *) AT91C_IO_VIRT_BASE,
    ROUND_UP (AT91C_IO_SIZE, PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },


    };
#endif /* defined(CPU_720T/720T_T/920T/920T_T) */
#if defined(CPU_740T)  || defined(CPU_740T_T) || \
    defined(CPU_940T)  || defined(CPU_940T_T) || \
    defined(CPU_946ES) || defined(CPU_946ES_T)

/*
 * The following structure describes the various different regions of the
 * memory map to be used only during initialisation by
 * vmMpuGlobalMapInit() when INCLUDE_MMU_MPU is defined.
 *
 * On the MPUs, the virtual and physical addresses must be
 * the same.  In addition, the regions must have an alignment equal to
 * their size, with a minimum size of 4K.  This restriction is very
 * important in understanding the region definitions.  Regions cannot be
 * arbitrarily moved or their size changed without considering
 * alignment.  There is no page-table RAM overhead to mapping in large
 * areas of the memory map, but we can only define 8 memory regions in
 * total. Regions cannot be marked as read-only in VxWorks.
 *
 * Here, we (arbitrarily) choose to leave as many regions in the MPU
 * unused as possible, so that they are available for later use (e.g. to
 * mark areas of RAM as non-cacheable).  This means that large areas are
 * mapped in as valid where no memory or I/O devices are actually
 * present.  If this is not desired, larger numbers of smaller regions
 * could be defined which more closely match what is actually present in
 * the memory map (paying close attention to the alignment requirements
 * mentioned above).  Spurious accesses outside those defined regions
 * would then cause access violation exceptions when the MPU is switched
 * on.
 *
 * Note that potentially important areas of memory space are currently
 * unmapped.  Core module alias areas, and the EBI space
 * (Boot ROM and SSRAM) are not defined, and will therefore cause
 * access violations.
 */
PHYS_MEM_DESC sysPhysMemDesc [] =
    {
    /*
     * Map the peripheral register area as writable but not cached or
     * buffered.
     */
    {
    (void *) INTEGRATOR_PERIPHERAL_BASE,	/* virtual address */
    (void *) INTEGRATOR_PERIPHERAL_BASE,	/* physical address */

    /* Region must have alignment equal to size, minimum of PAGE_SIZE */

    ROUND_UP(INTEGRATOR_PERIPHERAL_SIZE, PAGE_SIZE),	/* length */

    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },

    /*
     * Main RAM region from 0 to max(SSRAM,SDRAM), marked cacheable and
     * bufferable.
     */
    {
    (void *) 0,	/* virtual address */
    (void *) 0,	/* physical address */

    /* Region must have alignment equal to size, minimum of PAGE_SIZE */

    ROUND_UP ((LOCAL_MEM_SIZE + LOCAL_MEM_LOCAL_ADRS), PAGE_SIZE), /* length */

    /* initial state: */

    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE
    },

#if (LOCAL_MEM_LOCAL_ADRS != 0)
    /* If (e.g. on 946ES) we have image starting above where the
     * tightly-coupled memory is, then put another entry (higher priority than
     * the one before), which marks the area taken up by the tightly-coupled
     * memory as non-cacheable.
     */

    /* on-header SSRAM, or tightly-coupled memory */
    {
    (void *) 0,			/* virtual address */
    (void *) 0,			/* physical address */
    ROUND_UP (LOCAL_MEM_LOCAL_ADRS, PAGE_SIZE), /* length, then initial state */
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },
#endif /* (LOCAL_MEM_LOCAL_ADRS != 0) */

    /*
     * Flash memory: marked valid and writeable but not cached -
     * we need to be able to poll words in the Flash when updating
     * contents.
     */
    {
    (void *) ROM_BASE_ADRS,	/* virtual address */
    (void *) ROM_BASE_ADRS,	/* physical address */

    ROUND_UP (ROM_SIZE_TOTAL, PAGE_SIZE),	/* length */

    /* initial state: */

    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID      | VM_STATE_WRITABLE      | VM_STATE_CACHEABLE_NOT
    },

    /* I/O space: */

#ifdef INCLUDE_PCI
    {
    (void *) INTEGRATOR_PCI_BASE,
    (void *) INTEGRATOR_PCI_BASE,
    ROUND_UP (0x20000000, PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    },
    {
    (void *) CPU_PCI_IO_ADRS,
    (void *) CPU_PCI_IO_ADRS,
    ROUND_UP (0x4000000, PAGE_SIZE),
    VM_STATE_MASK_VALID | VM_STATE_MASK_WRITABLE | VM_STATE_MASK_CACHEABLE,
    VM_STATE_VALID	| VM_STATE_WRITABLE	 | VM_STATE_CACHEABLE_NOT
    }
#endif
    };
#endif /* defined(740T/940T/946ES) */

int sysPhysMemDescNumEnt = NELEMENTS (sysPhysMemDesc);
#endif /* defined(CPU_720T/740T/920T/940T/946ES) */

#endif /* defined(INCLUDE_MMU) */

int	sysBus	    = BUS;		/* system bus type (VME_BUS, etc) */
int	sysCpu	    = CPU;		/* system CPU type (e.g. ARMARCH4/4_T)*/
char *	sysBootLine = BOOT_LINE_ADRS; 	/* address of boot line */
char *	sysExcMsg   = EXC_MSG_ADRS;	/* catastrophic message area */
int	sysProcNum;			/* processor number of this CPU */
int	sysFlags;			/* boot flags */
char	sysBootHost [BOOT_FIELD_LEN];	/* name of host from which we booted */
char	sysBootFile [BOOT_FIELD_LEN];	/* name of file from which we booted */


/* locals */


/* defines */


/* externals */

IMPORT int  at91IntDevInit (void);
IMPORT void sysIntStackSplit (char *, long);


/* globals */


/* forward LOCAL functions declarations */


/* forward declarations */

char *	sysPhysMemTop (void);


#if defined (INCLUDE_USB)
void sysUsbPciInit(void);
#endif

/* included source files */

#ifdef INCLUDE_FLASH



#include "mem/nvRamToFlash.c"
#include "flashMem.c"
#else 

#endif
#include "vme/nullVme.c"
#include "sysSerial.c"

#include "timer/at91Timer.c"
#include "sio/at91Sio.c"
#include "intrCtl/at91Intr.c"

/*
#include "pciIomapLib.c"
#include "pciIomapShow.c"
#include "sysEnd.c"
*/
#ifdef INCLUDE_WINDML
//#include "ambaKbd.c"
//#include "ambaMse.c"
//#include "sysWindML.c"
#endif /* INCLUDE_WINDML */

#include "end/at91eth.c"

#ifdef INCLUDE_MMC
#include "mmc/mmcDev.c"
#endif

#ifdef INCLUDE_SPI_DATAFLASH_CARD
#include "dataflash/dataflashdev.c"
#endif

#ifdef INCLUDE_DISPLAY
#include "display/at91display.c"
#endif

#ifdef INCLUDE_USB_SLAVE_BULK
#include "usbslave/at91UsbSlave.c"
#endif

#ifdef INCLUDE_SOUND_CODEC
#include "audio/dac3550drv.c"
#endif


#ifdef INCLUDE_PCMCIA
#include "cf/pccardLib.c"
#endif
/*******************************************************************************
*
* sysModel - return the model name of the CPU board
*
* This routine returns the model name of the CPU board.
*
* NOTE
* This routine does not include all of the possible variants, and the
* inclusion of a variant in here does not mean that it is supported.
*
* RETURNS: A pointer to a string identifying the board and CPU.
*/

char *sysModel (void)
    {

    return	"ARM AT91RM9200";
    }

/*******************************************************************************
*
* sysBspRev - return the BSP version with the revision eg 1.2/<x>
*
* This function returns a pointer to a BSP version with the revision.
* e.g. 1.2/<x>. BSP_REV is concatenated to BSP_VERSION to form the
* BSP identification string.
*
* RETURNS: A pointer to the BSP version/revision string.
*/

char * sysBspRev (void)
    {
    return (BSP_VERSION BSP_REV);
    }

#if defined(CPU_720T)  || defined(CPU_720T_T) || \
    defined(CPU_740T)  || defined(CPU_740T_T) || \
    defined(CPU_920T)  || defined(CPU_920T_T) || \
    defined(CPU_940T)  || defined(CPU_940T_T) || \
    defined(CPU_946ES) || defined(CPU_946ES_T)
/*******************************************************************************
*
* sysHwInit0 - perform early BSP-specific initialisation
*
* This routine performs such BSP-specific initialisation as is necessary before
* the architecture-independent cacheLibInit can be called. It is called
* from usrInit() before cacheLibInit(), before sysHwInit() and before BSS
* has been cleared.
*
* RETURNS: N/A
*/

void sysHwInit0 (void)
    {

#ifdef INCLUDE_CACHE_SUPPORT
    /*
     * Install the appropriate cache library, no address translation
     * routines are required for this BSP, as the default memory map has
     * virtual and physical addresses the same.
     */

#if	defined(CPU_720T) || defined(CPU_720T_T)
    cacheArm720tLibInstall (NULL, NULL);
#elif   defined(CPU_740T) || defined(CPU_740T_T)
    cacheArm740tLibInstall (NULL, NULL);
#elif   defined(CPU_920T) || defined(CPU_920T_T)
    cacheArm920tLibInstall (NULL, NULL);
#elif   defined(CPU_940T) || defined(CPU_940T_T)
    cacheArm940tLibInstall (NULL, NULL);
#elif   defined(CPU_946ES) || defined(CPU_946ES_T)
    cacheArm946eLibInstall (NULL, NULL);
#endif
#endif /* INCLUDE_CACHE_SUPPORT */


#if defined(INCLUDE_MMU)
    /* Install the appropriate MMU library and translation routines */

#if	defined(CPU_720T) || defined(CPU_720T_T)
    mmuArm720tLibInstall (NULL, NULL);
#elif   defined(CPU_740T) || defined(CPU_740T_T)
    mmuArm740tLibInstall (NULL, NULL);
#elif   defined(CPU_920T) || defined(CPU_920T_T)
    mmuArm920tLibInstall (NULL, NULL);
#elif   defined(CPU_940T) || defined(CPU_940T_T)
    mmuArm940tLibInstall (NULL, NULL);
#elif   defined(CPU_946ES) || defined(CPU_946ES_T)
    mmuArm946eLibInstall (NULL, NULL);
#endif

#endif /* defined(INCLUDE_MMU) */

    return;
    }
#endif /* defined(720T/740T/920T/940T/946ES) */


/*******************************************************************************
*
* sysHwInit - initialize the CPU board hardware
*
* This routine initializes various features of the hardware.
* Normally, it is called from usrInit() in usrConfig.c.
*
* NOTE: This routine should not be called directly by the user.
*
* RETURNS: N/A
*/
void sysHwInit (void)
    {
    /* install the IRQ/SVC interrupt stack splitting routine */

    _func_armIntStackSplit = sysIntStackSplit;

#if defined(INCLUDE_PCI)

    /* Initialise the V3 PCI bridge controller */

    sysV3Init();

    /*  Initialise PCI driver library. */

    if (pciIomapLibInit (PCI_MECHANISM_3, CPU_PCI_CNFG_ADRS,
    			 CPU_PCI_CNFG_ADRS, 0) != OK)
	sysToMonitor (BOOT_NO_AUTOBOOT);

#endif  /* INCLUDE_PCI */

#ifdef INCLUDE_SERIAL
    /* initialise the serial devices */
	
    sysSerialHwInit ();      /* initialise serial data structure */
#endif /* INCLUDE_SERIAL */

	}

/*******************************************************************************
*
* sysHwInit2 - additional system configuration and initialization
*
* This routine connects system interrupts and does any additional
* configuration necessary.  Note that this is called from
* sysClkConnect() in the timer driver.
*
* RETURNS: N/A
*
*/

void sysHwInit2 (void)
    {
    static BOOL initialised = FALSE;

    if (initialised)
    	return;

    /* initialise the interrupt library and interrupt driver */

    intLibInit (AT91_INT_NUM_LEVELS, AT91_INT_NUM_LEVELS, INT_MODE);
    at91IntDevInit();

    /* connect sys clock interrupt and auxiliary clock interrupt */

    (void)intConnect (INT_VEC_SYS, sysClkInt, 0);
#ifdef INCLUDE_AUX_CLK
    (void)intConnect (INT_VEC_TC0, sysAuxClkInt, 0);
#endif
#ifdef INCLUDE_SERIAL
    /* connect serial interrupt */

    sysSerialHwInit2();
#endif /* INCLUDE_SERIAL */
	BSP_FlashWriteEnable(1);
    initialised = TRUE;

    }

/*******************************************************************************
*
* sysPhysMemTop - get the address of the top of physical memory
*
* This routine returns the address of the first missing byte of memory,
* which indicates the top of memory.
*
* Normally, the user specifies the amount of physical memory with the
* macro LOCAL_MEM_SIZE in config.h.  BSPs that support run-time
* memory sizing do so only if the macro LOCAL_MEM_AUTOSIZE is defined.
* If not defined, then LOCAL_MEM_SIZE is assumed to be, and must be, the
* true size of physical memory.
*
* NOTE: Do no adjust LOCAL_MEM_SIZE to reserve memory for application
* use.  See sysMemTop() for more information on reserving memory.
*
* RETURNS: The address of the top of physical memory.
*
* SEE ALSO: sysMemTop()
*/

char * sysPhysMemTop (void)
    {
    static char * physTop = NULL;

    if (physTop == NULL)
	{
#ifdef LOCAL_MEM_AUTOSIZE

	/* If auto-sizing is possible, this would be the spot.  */

#error   "Dynamic memory sizing not supported"

#else
	/* Don't do autosizing, if size is given */

	physTop = (char *)(LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE);

#endif /* LOCAL_MEM_AUTOSIZE */
	}

    return physTop;
    }

/*******************************************************************************
*
* sysMemTop - get the address of the top of VxWorks memory
*
* This routine returns a pointer to the first byte of memory not
* controlled or used by VxWorks.
*
* The user can reserve memory space by defining the macro USER_RESERVED_MEM
* in config.h.  This routine returns the address of the reserved memory
* area.  The value of USER_RESERVED_MEM is in bytes.
*
* RETURNS: The address of the top of VxWorks memory.
*/

char * sysMemTop (void)
    {
    static char * memTop = NULL;

    if (memTop == NULL)
	{
	memTop = sysPhysMemTop () - USER_RESERVED_MEM;
	}

    return memTop;
    }

/*******************************************************************************
*
* sysToMonitor - transfer control to the ROM monitor
*
* This routine transfers control to the ROM monitor.  It is usually called
* only by reboot() -- which services ^X -- and bus errors at interrupt
* level.  However, in some circumstances, the user may wish to introduce a
* new <startType> to enable special boot ROM facilities.
*
* RETURNS: Does not return.
*/

STATUS sysToMonitor
    (
    int startType	/* passed to ROM to tell it how to boot */
    )
    {
    FUNCPTR	pRom;
    UINT32 *	p = (UINT32 *)ROM_TEXT_ADRS;

#ifdef INCLUDE_SERIAL
    sysSerialReset ();	/* put serial devices into quiet state */
#endif

	pRom = (FUNCPTR)(ROM_TEXT_ADRS + 4);	/* warm boot address */

#if defined(CPU_720T)  || defined(CPU_720T_T) || \
    defined(CPU_740T)  || defined(CPU_740T_T) || \
    defined(CPU_920T)  || defined(CPU_920T_T) || \
    defined(CPU_940T)  || defined(CPU_940T_T) || \
    defined(CPU_946ES) || defined(CPU_946ES_T)

    VM_ENABLE(FALSE);	/* disable the MMU, cache(s) and write-buffer */
#endif

#if defined(CPU_920T) || defined(CPU_920T_T)
    /*
     * On 920T, can have the I-cache enabled once the MMU has been
     * disabled, so, unlike the other processors, disabling the MMU does
     * not disable the I-cache.  This would not be a problem, as the
     * 920T boot ROM initialisation code disables and flushes both caches.
     * However, in case we are, in fact, using a 7TDMI boot ROM,
     * disable and flush the I-cache here, or else the boot process may
     * fail.
     */

    cacheDisable (INSTRUCTION_CACHE);
#endif /* defined(CPU_920T/920T_T) */

    (*pRom)(startType);	/* jump to boot ROM */

    return OK;		/* in case we ever continue from ROM monitor */
    }

/****************************************************************************
*
* sysProcNumGet - get the processor number
*
* This routine returns the processor number for the CPU board, which is
* set with sysProcNumSet().
*
* RETURNS: The processor number for the CPU board.
*
* SEE ALSO: sysProcNumSet()
*/

int sysProcNumGet(void)
{
    return (sysProcNum);
}

/****************************************************************************
*
* sysProcNumSet - set the processor number
*
* Set the processor number for the CPU board.  Processor numbers should be
* unique on a single backplane.
*
* NOTE
* By convention, only processor 0 should dual-port its memory.
*
* RETURNS: N/A
*
* SEE ALSO: sysProcNumGet()
*/

void sysProcNumSet
    (
    int procNum		/* processor number */
    )
    {
    sysProcNum = procNum;
    }

/******************************************************************************
*
* sysLedsReadWrite - read/write the state of the LEDs on the board
*
* This routine can be used to read and write the state of the four LEDs
* on the board. The current state is ANDed and EORed with the supplied
* parameters. Bits 0..3 control LEDs 0..3. A 1 switches the LED on; a 0 off.
*
* RETURNS: previous state of LEDs.
*/

int sysLedsReadWrite
    (
    int and,
    int eor
    )
    {
    UINT32 previous=0;

    return previous;
    }

#ifdef INCLUDE_FLASH
/******************************************************************************
*
* sysFlashWriteEnable - enable write access to the Flash memory
*
* This routine is used by flashMem.c to enable write access to the
* Flash memory.
*
* RETURNS: N/A
*/

void sysFlashWriteEnable (void)
     {
     volatile UINT32 * ebiCsr = (volatile UINT32 *)INTEGRATOR_EBI_CSR1;

     /* allow write access to EBI_CSR1 area (Flash ) */

     *ebiCsr |= INTEGRATOR_EBI_WRITE_ENABLE;

     if (!(*ebiCsr & INTEGRATOR_EBI_WRITE_ENABLE))
	 {
	 *(volatile UINT32 *)INTEGRATOR_EBI_LOCK = 0xA05F;
	 *ebiCsr |= INTEGRATOR_EBI_WRITE_ENABLE;
	 *(volatile UINT32 *)INTEGRATOR_EBI_LOCK = 0;
	 }

     /* Enable Vpp and allow write access to Flash in system controller */

     *(volatile UINT32 *)INTEGRATOR_SC_CTRLS = FL_SC_CONTROL;
     }

/******************************************************************************
*
* sysFlashWriteDisable - disable write access to the Flash memory
*
* This routine is used by flashMem.c to disable write access to the
* Flash memory.
*
* RETURNS: N/A
*/

void sysFlashWriteDisable (void)
     {
     volatile UINT32 * ebiCsr = (volatile UINT32 *)INTEGRATOR_EBI_CSR1;

     /* disable write access to EBI_CSR1 area (Flash ) */

     *ebiCsr &= ~INTEGRATOR_EBI_WRITE_ENABLE;

     if (*ebiCsr & INTEGRATOR_EBI_WRITE_ENABLE)
	 {
	 *(volatile UINT32 *)INTEGRATOR_EBI_LOCK = 0xA05F;
	 *ebiCsr &= ~INTEGRATOR_EBI_WRITE_ENABLE;
	 *(volatile UINT32 *)INTEGRATOR_EBI_LOCK = 0;
	 }

     /* Disable Vpp and disable write access to Flash in system controller */

     *(volatile UINT32 *)INTEGRATOR_SC_CTRLS = 0;
     }
#else
void sysFlashWriteEnable (void)
{

}
#endif /* INCLUDE_FLASH */

STATUS sysIntEnablePIC(int level)
{
	return at91IntLvlEnable(level);
}


STATUS sysIntDisablePIC(int level)
{
	return at91IntLvlDisable(level);
}

UCHAR	sysInByte(ULONG port)
{
	return *(UCHAR*)port;
}

void	sysOutByte(ULONG port, UCHAR data)
{
	*(UCHAR*)port = data;
}




