/* config.h - ARM Integrator configuration header */

/* Copyright 1999-2001 ARM Limited */
/* Copyright 1999-2001 Wind River Systems, Inc. */

/*
modification history
--------------------
01o,15jul02,m_h  WindML support, C++ protection
01n,22may02,m_h  Reduce ROM_SIZE for boards with 32 meg RAM (77901)
01m,15may02,m_h  INCLUDE_SHELL, etc are for BSP validation (75760, 75904)
01l,09oct01,jpd  corrected RAM_HIGH_ADRS and LOCAL_MEM_SIZE for integrator946.
                 bump revision number to /5
01k,03oct01,jpd  added support for Integrator 946es/946es_t.
01j,02may01,rec  bump revision number, fix 559 initialization problem
01m,01nov01,t_m  merge in 946 updates
01l,22oct01,jb  Setting MMU_BASIC as default for builds of cpus with MMU
01k,15oct01,jb  New assembly macros are in h/arch/arm/arm.h
01l,09oct01,jpd  corrected RAM_HIGH_ADRS and LOCAL_MEM_SIZE for integrator946.
01k,03oct01,jpd  added support for Integrator 946es/946es_t.
01j,02may01,rec  bump revision number, fix 559 initialization problem
01i,27apr01,rec  add support for 966
01h,25jan01,jmb  remove INCLUDE_MIILIB
01g,15dec00,rec  change RAM_HIGH_ADRS
01f,21nov00,jpd  added support for Intel Ethernet driver.
01e,17feb00,jpd  added define of INCLUDE_FLASH_SIB_FOOTER; raised RAM_HIGH_ADRS.
01d,07feb00,jpd  added support for ARM720T and ARM920T.
01c,13jan00,pr	 add support for Integrator 740T/740T_T.
01b,07dec99,pr	 add DEC and PCI support.
01a,05nov99,ajb  copied from PID BSP version 01p.
*/

/*
This module contains the configuration parameters for the ARM Integrator BSP.
*/

#ifndef	INCconfigh
#define	INCconfigh

#ifdef __cplusplus
extern "C" {
#endif

/* BSP version/revision identification, before configAll.h */

#define BSP_VER_1_1     1       /* 1.2 is backwards compatible with 1.1 */
#define BSP_VER_1_2     1
#define BSP_VERSION	"1.2"
#define BSP_REV		"/5"	/* 0 for first revision */

#include "configAll.h"

#if	defined(CPU_7TDMI)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator7t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_7TDMI_T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator7t_t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_720T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator720t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_720T_T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator720t_t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_740T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator740t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_740T_T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator740t_t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_920T)
#  define DEFAULT_BOOT_LINE \
    "eth(0,0) host:vxWorks " \
    "h=192.168.67.111 e=192.168.67.102:ffffff00 u=target pw=target"
#elif defined(CPU_920T_T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator920t_t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_940T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator940t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_940T_T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator940t_t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_966ES)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator966es/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_966ES_T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator966es_t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_946ES)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator946es/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#elif defined(CPU_946ES_T)
#  define DEFAULT_BOOT_LINE \
    "fei(0,0) host:/tor2/target/config/integrator946es_t/vxWorks " \
    "h=90.0.0.3 e=90.0.0.50:ffffff00 u=target tn=targetname"
#else
#  error CPU type not supported
#endif  /* defined(CPU_7TDMI) */


/* Memory configuration */

#undef	LOCAL_MEM_AUTOSIZE			/* run-time memory sizing */
#define USER_RESERVED_MEM	0		/* see sysMemTop() */

/*
 * Local-to-Bus memory address constants:
 * the local memory address always appears at 0 locally;
 * it is not dual ported.
 */

#if defined(CPU_946ES) || defined(CPU_946ES_T)
#define LOCAL_MEM_LOCAL_ADRS	0x00100000	/* fixed at 1Mbyte after TCM */
#define LOCAL_MEM_BUS_ADRS	0x00100000	/* fixed at 1Mbyte after TCM */
#define LOCAL_MEM_SIZE		0x00700000	/* 7 Mbytes after TCM */
#elif defined(CPU_966ES) || defined(CPU_966ES_T)
#  define LOCAL_MEM_LOCAL_ADRS	0x08000000	/* fixed at 0x08000000 */
#  define LOCAL_MEM_BUS_ADRS	0x08000000	/* fixed at 0x08000000 */
#define LOCAL_MEM_SIZE		0x00800000	/* 8 Mbytes */
#else
#define LOCAL_MEM_LOCAL_ADRS	0x20000000	/* fixed at zero */
#define LOCAL_MEM_BUS_ADRS	0x20000000	/* fixed at zero */
#define LOCAL_MEM_SIZE		0x04000000	/* 64 Mbytes */
#endif
#define LOCAL_MEM_END_ADRS	(LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE)


/*
 * Boot ROM is an image written into Flash. Part of the Flash can be
 * reserved for boot parameters etc. (see the Flash section below).
 *
 * The following parameters are defined here and in the Makefile.
 * They must be kept synchronized; effectively config.h depends on Makefile.
 * Any changes made here must be made in the Makefile and vice versa.
 *
 * ROM_BASE_ADRS is the base of the Flash ROM/EPROM.
 * ROM_TEXT_ADRS is the entry point of the VxWorks image
 * ROM_SIZE is the size of the part of the Flash ROM/EPROM allocated to
 *		the VxWorks image (block size - size of headers)
 *
 * Two other constants are used:
 * ROM_COPY_SIZE is the size of the part of the ROM to be copied into RAM
 * 		 (e.g. in uncompressed boot ROM)
 * ROM_SIZE_TOTAL is the size of the entire Flash ROM (used in sysPhysMemDesc)
 *
 * The values are given as literals here to make it easier to ensure
 * that they are the same as those in the Makefile.
 */

#define ROM_BASE_ADRS       0x10000000 /*AT91_FLASH_BASE  base of Flash/EPROM */
#define ROM_TEXT_ADRS       ROM_BASE_ADRS  /* code start addr in ROM */
#define ROM_SIZE            0x00100000     /* size of ROM holding VxWorks*/

#define ROM_COPY_SIZE       ROM_SIZE
#define ROM_SIZE_TOTAL      0x01000000	/* total size of ROM */

 
#define RAM_LOW_ADRS		0x20001000	/* VxWorks image entry point */
#define RAM_HIGH_ADRS		0x21000000	/* RAM address for ROM boot */
 

/*
 * Count for a CPU delay loop at the beginning of romInit. There have been
 * reports of problems with certain boards and certain power supplies, and
 * adding a delay at the start of romInit appears to help with this. This
 * value may need tuning for different board/PSU combinations.
 */

#define AT91_DELAY_VALUE	0x1000


/*
 * Flash/NVRAM memory configuration
 *
 * A block of the Flash memory (FLASH_SIZE bytes at FLASH_ADRS) is
 * reserved for non-volatile storage of data.
 *
 * See also integrator.h
 */

#undef	CONSOLE_BAUD_RATE
#define CONSOLE_BAUD_RATE 115200


#undef  INCLUDE_FLASH

#ifdef INCLUDE_FLASH
#define FLASH_SIZE		0x00020000	/* one 128kbyte block of Flash*/
#define NV_RAM_SIZE		0x100		/* how much we use as NVRAM */
#undef	NV_BOOT_OFFSET
#define NV_BOOT_OFFSET		0		/* bootline at start of NVRAM */
#define FLASH_NO_OVERLAY			/* do not read-modify-write all
						 * of Flash */
#define INCLUDE_FLASH_SIB_FOOTER		/* add a SIB footer to block */
#else	/* INCLUDE_FLASH */
#define NV_RAM_SIZE		NONE

#endif	/* INCLUDE_FLASH */


/* Serial port configuration */

#define INCLUDE_SERIAL
#undef	NUM_TTY
#define NUM_TTY			N_SIO_CHANNELS


/*
 * Cache/MMU configuration
 *
 * Note that when MMU is enabled, cache modes are controlled by
 * the MMU table entries in sysPhysMemDesc[], not the cache mode
 * macros defined here.
 */

#if defined(CPU_720T)  || defined(CPU_720T_T) || \
    defined(CPU_740T)  || defined(CPU_740T_T) || \
    defined(CPU_920T)  || defined(CPU_920T_T) || \
    defined(CPU_940T)  || defined(CPU_940T_T) || \
    defined(CPU_946ES) || defined(CPU_946ES_T)

/*
 * We use the generic architecture libraries, with caches/MMUs present. A
 * call to sysHwInit0() is needed from within usrInit before
 * cacheLibInit() is called.
 */

#ifndef _ASMLANGUAGE
IMPORT void sysHwInit0 (void);
#endif
#define INCLUDE_SYS_HW_INIT_0
#define SYS_HW_INIT_0()         sysHwInit0 ()

#endif /* defined(720T/740T/920T/940T/946ES) */

#if defined(CPU_720T) || defined(CPU_720T_T) || \
    defined(CPU_740T) || defined(CPU_740T_T)
/*
 * 720T and 740T can be either write-through or copyback (defines whether
 * write-buffer is enabled); cache itself is write-through.
 */

#undef  USER_I_CACHE_MODE
#define USER_I_CACHE_MODE	CACHE_COPYBACK

/*
 * 720T and 740T have a combined Instruction/Data cache, so the modes must
 * be identical.
 */

#undef  USER_D_CACHE_MODE
#define USER_D_CACHE_MODE	(USER_I_CACHE_MODE)

#endif /* defined(720T/720T_T/740T/740T_T) */

#if defined(CPU_920T)  || defined(CPU_920T_T) || \
    defined(CPU_940T)  || defined(CPU_940T_T) || \
    defined(CPU_946ES) || defined(CPU_946ES_T)
/*
 * 920T/940T/946ES I-cache mode is a bit of an inappropriate concept,
 * but use this.
 * */

#undef  USER_I_CACHE_MODE
#define USER_I_CACHE_MODE       CACHE_WRITETHROUGH

/* 920T/940T/946ES has to be this. */

#undef  USER_D_CACHE_MODE
#define USER_D_CACHE_MODE       CACHE_COPYBACK

#endif /* defined(CPU_920T/940T/946ES) */

#if defined(CPU_940T) || defined(CPU_940T_T)
/*
 * All ARM 940T BSPs must define a variable sysCacheUncachedAdrs: a
 * pointer to a word that is uncached and is safe to read (i.e. has no
 * side effects).  This is used by the cacheLib code to perform a read
 * (only) to drain the write-buffer. Clearly this address must be present
 * within one of the regions created within sysPhysMemDesc, where it must
 * be marked as non-cacheable. There are many such addresses we could use
 * on the board, but we choose to use an address here that will be
 * mapped in on just about all configurations: a safe address within the
 * interrupt controller: the IRQ Enabled status register. This saves us
 * from having to define a region just for this pointer. This constant
 * defined here is used to initialise sysCacheUncachedAdrs in sysLib.c
 * and is also used by the startup code in sysALib.s and romInit.s in
 * draining the write-buffer.
 */

#define SYS_CACHE_UNCACHED_ADRS               AMBA_INT_CSR_ENB
#endif /* defined(CPU_940T/940T_T) */

#if defined(CPU_740T)  || defined(CPU_740T_T) || \
    defined(CPU_940T)  || defined(CPU_940T_T) || \
    defined(CPU_946ES) || defined(CPU_946ES_T)

/*
 * 740T/940T/946E have an MPU and not a full MMU, so only INCLUDE_MMU_MPU can be
 * supported, and not full page-table-style MMU. Include support for
 * the MPU by default (this can be overridden, if desired).
 */

#undef	INCLUDE_MMU_FULL
#undef	INCLUDE_MMU_BASIC
#define INCLUDE_MMU_MPU

#endif /* defined(740T/940T/946ES) */


#if defined(CPU_720T) || defined(CPU_720T_T) || \
    defined(CPU_920T) || defined(CPU_920T_T)

/*
 * Include MMU BASIC and CACHE support for command line and project builds
 */
#define	INCLUDE_MMU_BASIC
#define INCLUDE_CACHE_SUPPORT

#endif /* defined(720T/720T_T/920T/920T_T) */

/*
 * Network driver configuration.
 *
 * De-select unused (default) network drivers selected in configAll.h.
 */

#undef	INCLUDE_ENP		/* include CMC Ethernet interface*/
#undef	INCLUDE_EX		/* include Excelan Ethernet interface */
#undef	INCLUDE_SM_NET		/* include backplane net interface */
#undef	INCLUDE_SM_SEQ_ADDR	/* shared memory network auto address setup */

/* Enhanced Network Driver (END) Support */

#define INCLUDE_END

#ifdef	INCLUDE_END
#define INCLUDE_SEC_END
#undef  WDB_COMM_TYPE		/* WDB agent communication path is END */
#define WDB_COMM_TYPE	WDB_COMM_END


#define INCLUDE_MIILIB


#endif  /* INCLUDE_END */


/* PCI configuration */

#undef INCLUDE_PCI


/*
 * Interrupt mode - interrupts can be in either preemptive or non-preemptive
 * mode.  For non-preemptive mode, change INT_MODE to INT_NON_PREEMPT_MODEL
 */

#define INT_MODE	INT_PREEMPT_MODEL

/*
 * Enable BSP-configurable interrupt priorities: order of servicing and
 * masking of interrupts will be determined by ambaIntLvlPriMap[] in
 * sysLib.c.  If AMBA_INT_PRIORITY_MAP is not defined, priority of
 * interrupts will be least-significant bit first.
 */

#define	AMBA_INT_PRIORITY_MAP	/* BSP-configurable interrupt priorities */


/*
 * miscellaneous definitions
 * Note: ISR_STACK_SIZE is defined here rather than in ../all/configAll.h
 * (as is more usual) because the stack size depends on the interrupt
 * structure of the BSP.
 */

#define ISR_STACK_SIZE	0x800	/* size of ISR stack, in bytes */


/* Optional timestamp support */

#undef	INCLUDE_TIMESTAMP	/* define to include timestamp driver */



/* Optional TrueFFS support */

#undef	INCLUDE_TFFS		/* define to include TrueFFS driver */

#ifdef  INCLUDE_TFFS
#define INCLUDE_SHOW_ROUTINES
#define INCLUDE_DOSFS
#endif /* INCLUDE_TFFS */

#include "at91rm9200dk.h"

#undef BSP_VTS
#ifdef BSP_VTS
/***************************************************
 * Add these defines for the Validation Test Suite *
 ***************************************************/
#define INCLUDE_SHELL
#define INCLUDE_RLOGIN
#define INCLUDE_SHOW_ROUTINES
#define INCLUDE_NET_SYM_TBL
#define INCLUDE_LOADER

#define INCLUDE_PING
#define INCLUDE_NET_SHOW
#endif /*BSP_VTS*/

#undef INCLUDE_WINDML          /* define to include windML support */

#ifdef __cplusplus
}
#endif
#endif  /* INCconfigh */

#if defined(PRJ_BUILD)
#include "prjParams.h"
#endif
