/* usrConfig.c - user-defined system configuration library */

/* Copyright 1984-2005 Wind River Systems, Inc. */
#include "copyright_wrs.h"

/*
modification history
--------------------
20d,15feb06,spw  Add protection to loginUserAdd
20c,16dec05,bpn  Fixed build warning when shell and security are included 
                 (SPR#77071).
19z,13oct05,elp  ntpassfs allways uses slash as separator default (SPR# 112560).
20b,28oct04,pch  add excIntNestLogInit (LOG_FRAMELESS and LOG_DISPATCH support)
20b,14apr04,pch  SPR 95355: enable interrupts in root task after MMU is set up.
		 Fix warnings re constant conditionals involving NUM_TTY.
20a,20jun03,t_m  added pccardlib
19z,09jun03,mil  Merged from CP1 to e500.
19y,12nov02,dbt  Reworked symbol table synchronization initialization code
		 (SPR #25509).
19x,17oct02,dtr  Adding in usrSpeInit.
19w,15may02,sbs  changing default sys clock rate to a macro (SPR #1918)
19v,24apr02,j_s  make WDB Banner the same as in
		 target/config/comps/src/usrWdbBanner.c (SPR #76099)
		 updated 2001 to 2002
19u,19apr02,pch  SPR 74348: Enable PPC Machine Check exception ASAP
19t,05apr02,hbh  Fixed SPR# 30368 and improved ntPassFs initialization.
19s,04mar02,pch  SPR 73609
19r,11feb02,jkf  SPR#73173, adding INCLUDE_DOSFS_MAIN init section.
19q,21jan02,sn   added INCLUDE_CTORS_DTORS
19p,10dec01,jlb  Change UGL to WindML product
19o,07dec01,wef  add USB initialization code.
19n,07dec01,sn   added INCLUDE_CPLUS_DEMANGLER
19m,08nov01,jmp  removed useless routeAdd() for SIMNT.
19l,31oct01,gls  added pthread code
19k,27oct01,dat  Adding trap for misaligned data section SPR 9006
19j,21sep01,aeg  updated initialization sequence of selectLib (SPR #31319).
19i,17sep01,pcm  added excShowInit() (SPR 7333), and lstLibInit () (SPR 20698)
19h,15may01,pch  Move call of usrAltivecInit() from sysLib.c to usrConfig.c,
		 to fix an undefined reference when building bootrom.
19g,20jan99,dbs  change VXCOM to COM
19f,18dec98,dbs  add VXCOM as separate item
19e,06nov98,dbs  add DCOM init when INCLUDE_DCOM is set
19g,22feb01,scm  add fast dram support capabilities for XScale...
19f,16mar99,jpd  changed copyright yearfrom 1998 to 1999.
19e,13nov98,jpd  call usrMmuInit if INCLUDE_MMU_MPU defined; conditionally
		 add sysHwInit0() call before cacheLibInit(); added
		 INCLUDE_INITIAL_MEM_ALLOCATION
	    cdp	 make Thumb support for ARM CPUs dependent on ARM_THUMB.
19j,27feb01,hk   update INCLUDE_WDB_BANNER copyright notice to cover 2001.
19i,08jun00,csi  Merginf usrConfig.c for vxfusion
19h,19apr00,zl   updated copyright year to 2000.
19g,02mar00,zl   merged SH support into T2.
01g,07mar01,sn   simplify job of host val by using creationDate (which
		 is overridable) rather than __DATE__
19g,14oct99,jk   added conditional init code for sound driver support.
19i,30jul99,jkf  fixed SPR#4429. ideDrv, ataDrv, fdDrv, warn on ERROR.
19h,16mar99,jpd  changed copyright yearfrom 1998 to 1999.
19g,10mar99,drm  Changing WINDMP to VXFUSION to reflect new product name.
19f,13nov98,jpd  call usrMmuInit if INCLUDE_MMU_MPU defined; conditionally
		 add sysHwInit0() call before cacheLibInit(); added
		 INCLUDE_INITIAL_MEM_ALLOCATION
	    cdp	 make Thumb support for ARM CPUs dependent on ARM_THUMB.
19e,08oct98,rlp  added support for UGL and HTML.
19d,17sep98,ms   call cplusDemanglerInit if INCLUDE_CPLUS and INCLUDE_LOADER
19c,17sep98,cym  added code to calculate proper IP address for PCSIM.
19b,01sep98,drm  added code to initialize WindMP
19a,10aug98,cym  added code to inform tornado when the NT simulator is up.
18z,23apr98,yp   merged in TrueFFS support
18y,22apr98,elp  created group 1 module when standalone (fixed SPR# 20301).
18w,22apr98,hdn  added comment for tffsDrv().
18t,17apr98,nps  added support for rBuffShow.
18s,09mar98,sjw  merge in HTTP and JAVA changes for conflict resolution
18r,18dec97,cth  replaced windview, timestamp initialization with windviewConfig
18q,13nov97,cth  changed WV evtInstInit to wvLibInit2; removed connRtnSet,
		 evtTaskInit; added include wvLib.h, rBuffLib.h
18p,18aug97,nps  changed WV buffer initialization with the rBuff API.
18x,06mar98,ms   changed copyright year from 1996 to 1998.
18v,04feb98,jpd  fix unsigned/signed warning (usrRoot); updated copyright date.
18u,25feb98,jgn  removed call to excShowInit(), it is called by excInit()
		 if needed (SPR #20625)
18t,19jan98,hdn  changed a condition macro to include tffsDrv().
18p,06jan98,cym  added SIMNT as processor not to clear bss.
18s,23sep97,yp   added support for TFFS.
18r,13aug97,cdp  add Thumb (ARM7TDMI_T) support;
		 'fix' unsigned/signed comparison in usrRoot.
18q,26feb97,dat  added INCLUDE_USER_APPL and USER_APPL_INIT, spr 8071.
18p,05feb97,cdp  remove ARM test hook (_func_armStartup).
18o,12dec96,cdp  added _func_armStartup for ARM platforms.
18n,13dec96,elp	 changed syncLibInit() into symSyncLibInit().
18m,18nov96,dds  SPR 2529: return status for sysScsiInit is now checked.
18l,06nov96,ms   removed 17n hack to usrClock.
18k,01nov96,hdn  added support for PCMCIA.
18j,21oct96,hdn  changed paramerters for new LPT driver.
18i,04oct96,elp  added INCLUDE_SYM_TBL_SYNC (SPR# 6775).
18h,11jul96,tam  changed copyright year from 1995 to 1996.
18l,19jul96,hdn  added support for ATA driver.
18k,25jun96,jmb  Eliminated alternative WDB macro names (SPR #5707).
18j,25jun96,dbt  Initialized _func_selWakeupListInit before tyLib (SPR #3314).
18i,21jun96,jmb  update copyright. SPR #6364
18h,21jun96,jmb  long modhist -- deleted entries prior to 1994.  SPR #6528
18g,12mar96,tam  removed all #if (CPU == PPC403).
18p,06jun96,ism  bumped copyright to 1996.
18o,26jan96,ism  cleaned up vxsim/solaris version
18f,02oct95,kvk  added sysHwInit2() for PPC603.
18e,27sep95,tpr  removed #if (CPU_FAMILY != PPC) staff.
18n,07nov95,srh  fixed C++ support comments.
18m,29oct95,dat  fixed warnings about printf arguments
18l,11oct95,jdi  doc: changed .pG to .tG.
18k,10oct95,dat	 new BSP revision id. Added WDB Banner printing
18j,15jun95,ms	 updated for new serial drivers.
18i,09jun95,ms	 cleaned up console initialization
18h,30may95,p_m  added initialization of formatted I/O library.
		 replaced spyStop() by spyLibInit().
18g,22may95,p_m  no longer initialize object format specific libraries if
		 loader is not included.
18f,22may95,myz  modified new serial device initialization for x86 support
18e,22may95,ms   added some WDB agent support
18e,30oct95,ism  updated for SIMSPARCSOLARIS
18d,28mar95,kkk  added scalability support, changed edata and end to arrays
		 (SPR #3917), changed baud rate to be a macro in configAll.h
18g,25may95,yao  changed to bzero bss segment for PPC.
18f,04apr95,caf  added PPC cache support.
18e,03mar95,yao  added shsHwInit2 () for PPC403.
18d,24feb95,caf  added PPC support.
18c,20nov94,kdl  added hashLibInit() when using dosFs.
18b,09nov94,jds  additions for scsi backward compatability ; scsi[12]IfInit()
18a,04nov94,kdl	 merge cleanup.
17l,02aug94,tpr  added cacheEnable (BRANCH_CACHE) for the MC68060.
17m,15oct94,hdn  added LPT driver.
17o,20jul94,ms   changed INCLUDE_AOUT_HPPA to INCLUDE_SOM_COFF
17n,02may94,ms   added VxSim HP hack to usrClock().
17q,15mar94,smb  renamed tEvtTask parameters.
17p,15feb94,smb  defined WV_MODE, EVTBUFFER_ADDRESS for wvInstInit().
17o,12jan94,kdl  modified posix initialization; added queued signal init.
*/

/*
DESCRIPTION
This library is the WRS-supplied configuration module for VxWorks.  It
contains the root task, the primary system initialization routine, the
network initialization routine, and the clock interrupt routine.

The include file config.h includes a number of system-dependent parameters used
in this file.

In an effort to simplify the presentation of the configuration of vxWorks,
this file has been split into smaller files.  These additional configuration
source files are located in ../../src/config/usr[xxx].c and are #included into
this file below.  This file contains the bulk of the code a customer is
likely to customize.

The module usrDepend.c contains checks that guard against unsupported
configurations such as INCLUDE_NFS without INCLUDE_RPC.  The module
usrKernel.c contains the core initialization of the kernel which is rarely
customized, but provided for information.  The module usrNetwork.c now
contains all network initialization code.  Finally, the module usrExtra.c
contains the conditional inclusion of the optional packages selected in
configAll.h.

The source code necessary for the configuration selected is entirely
included in this file during compilation as part of a standard build in
the board support package.  No other make is necessary.

INCLUDE FILES:
config.h

SEE ALSO:
.tG "Getting Started, Cross-Development"
*/

#include "vxWorks.h"			/* always first */
#include "config.h"			/* board support configuration header */
#include "usrConfig.h"			/* general configuration header */
#include "usrDepend.c"			/* include dependency rules */
#include "usrKernel.c"			/* kernel configuration */
#include "usrExtra.c"			/* conditionally included packages */

#if CPU==SIMNT
extern int simUpMutex;
extern int win_ReleaseMutex(int hMutex);
#endif

#ifdef INCLUDE_HTTP
#include "http/httpLib.h"		/* Wind Web Server interfaces */
#endif

#ifdef INCLUDE_COM
extern int comLibInit ();
#endif

#ifdef INCLUDE_DCOM
extern int dcomLibInit ();
#endif

/* defines - must be after include of usrDepend.c */

#ifdef	INCLUDE_WDB
#define FREE_MEM_START_ADRS (FREE_RAM_ADRS + WDB_POOL_SIZE)
#else
#define FREE_MEM_START_ADRS FREE_RAM_ADRS
#endif

#ifdef	INCLUDE_INITIAL_MEM_ALLOCATION
#define MEM_POOL_START_ADRS \
	    (ROUND_UP(FREE_MEM_START_ADRS, (INITIAL_MEM_ALIGNMENT)) + \
	    (INITIAL_MEM_SIZE))
#else	/* INCLUDE_INITIAL_MEM_ALLOCATION */
#define MEM_POOL_START_ADRS FREE_MEM_START_ADRS
#endif	/* INCLUDE_INITIAL_MEM_ALLOCATION */

#if	(CPU_FAMILY == PPC)
void excIntNestLogInit(void);
#endif	/* (CPU_FAMILY == PPC) */

/* global variables */

int		consoleFd;		/* fd of initial console device */
char		consoleName[20];	/* console device name, eg. "/tyCo/0" */
SYMTAB_ID	statSymTbl;		/* system error status symbol table id*/
SYMTAB_ID	standAloneSymTbl;	/* STANDALONE version symbol table id */
SYMTAB_ID	sysSymTbl;		/* system symbol table id */
BOOT_PARAMS	sysBootParams;		/* parameters from boot line */
int		sysStartType;		/* type of boot (WARM, COLD, etc) */

#if	(CPU_FAMILY == PPC)
IMPORT _RType taskMsrDefault;   /* from taskArchLib.c */
#endif	/* (CPU_FAMILY == PPC) */

/* Two magic cookies used to detect data section misalignment */

#define TRAP_VALUE_1	0x12348765
#define TRAP_VALUE_2	0x5a5ac3c3
LOCAL volatile UINT32	trapValue1	= TRAP_VALUE_1;
LOCAL volatile UINT32	trapValue2	= TRAP_VALUE_2;


/*******************************************************************************
*
* usrInit - user-defined system initialization routine
*
* This is the first C code executed after the system boots.  This routine is
* called by the assembly language start-up routine sysInit() which is in the
* sysALib module of the target-specific directory.  It is called with
* interrupts locked out.  The kernel is not multitasking at this point.
*
* This routine starts by clearing BSS; thus all variables are initialized to 0,
* as per the C specification.  It then initializes the hardware by calling
* sysHwInit(), sets up the interrupt/exception vectors, and starts kernel
* multitasking with usrRoot() as the root task.
*
* RETURNS: N/A
*
* SEE ALSO: kernelLib
*
* ARGSUSED0
*/

void usrInit
    (
    int startType
    )
    {
    /*
     * This trap will catch improper loading of the data section.
     * We check the magic cookie values to make sure the data section is
     * in the expected memory location. We do not want
     * to proceed further if the data segment is not correct.
     *
     * It should be easy to detect entry into the trap using an ICE, JTAG,
     * or logic analyzer. Without the trap, the processor is likely to run
     * away out of control.
     *
     * Data section misalignment can occur when there is a change in tool
     * chain, build rules, compiler, host utilites,  etc. 
     */

    while (trapValue1 != TRAP_VALUE_1 || trapValue2 != TRAP_VALUE_2)
	{
	/* infinite loop */;
	}
    
#if	(CPU_FAMILY == SPARC)
    excWindowInit ();				/* SPARC window management */
#endif

#ifdef INCLUDE_SYS_HW_INIT_0
    /*
     * Perform any BSP-specific initialisation that must be done before
     * cacheLibInit() is called and/or BSS is cleared.
     */

    SYS_HW_INIT_0 ();
#endif /* INCLUDE_SYS_HW_INIT_0 */

    /* configure data and instruction cache if available and leave disabled */

#ifdef  INCLUDE_CACHE_SUPPORT
    /*
     * SPR 73609:  If a cache is not to be enabled, don't require
     * its mode to be defined.  Instead, default it to disabled.
     */
# if (!defined(USER_D_CACHE_ENABLE) && !defined(USER_D_CACHE_MODE))
#  define USER_D_CACHE_MODE CACHE_DISABLED
# endif	/* !USER_D_CACHE_ENABLE && !USER_D_CACHE_MODE */
# if (!defined(USER_I_CACHE_ENABLE) && !defined(USER_I_CACHE_MODE))
#  define USER_I_CACHE_MODE CACHE_DISABLED
# endif	/* !USER_I_CACHE_ENABLE && !USER_I_CACHE_MODE */

    cacheLibInit (USER_I_CACHE_MODE, USER_D_CACHE_MODE);
#endif  /* INCLUDE_CACHE_SUPPORT */

#if	CPU_FAMILY!=SIMNT && CPU_FAMILY!=SIMSPARCSUNOS && CPU_FAMILY!=SIMHPPA && CPU_FAMILY!=SIMSPARCSOLARIS
    /* don't assume bss variables are zero before this call */

    bzero (edata, end - edata);		/* zero out bss variables */
#endif	/* CPU_FAMILY!=SIMNT && CPU_FAMILY!=SIMSPARCSUNOS && CPU_FAMILY!=SIMHPPA && CPU_FAMILY!=SIMSPARCSOLARIS */

#if (CPU_FAMILY == PPC)
    /*
     * Immediately after clearing the bss, ensure global stdin
     * etc. are ERROR until set to real values.  This is used in
     * target/src/arch/ppc/excArchLib.c to improve diagnosis of
     * exceptions which occur before I/O is set up.
     */
    ioGlobalStdSet (STD_IN,  ERROR);
    ioGlobalStdSet (STD_OUT, ERROR);
    ioGlobalStdSet (STD_ERR, ERROR);
#endif  /* CPU_FAMILY == PPC */

    sysStartType = startType;			/* save type of system start */

    intVecBaseSet ((FUNCPTR *) VEC_BASE_ADRS);	/* set vector base table */

#if (CPU_FAMILY == AM29XXX)
    excSpillFillInit ();			/* am29k stack cache managemt */
#endif

#ifdef  INCLUDE_EXC_HANDLING
# if (CPU_FAMILY == PPC) && defined(INCLUDE_EXC_SHOW)
    /*
     * Do this ahead of excVecInit() to set up _func_excPanicHook, in case
     * the enabling of Machine Check there allows a pending one to occur.
     * excShowInit() will be called again later, harmlessly.
     */
    excShowInit ();
# endif  /* CPU_FAMILY == PPC && defined(INCLUDE_EXC_SHOW) */
    excVecInit ();				/* install exception vectors */
#endif  /* INCLUDE_EXC_HANDLING */

    sysHwInit ();				/* initialize system hardware */

    usrKernelInit ();				/* configure the Wind kernel */

#ifdef INCLUDE_USB 
#   ifdef INCLUDE_OHCI_PCI_INIT
	sysUsbPciOhciInit ();
#   endif
#endif

#ifdef  INCLUDE_CACHE_SUPPORT
#ifdef 	USER_I_CACHE_ENABLE
    cacheEnable (INSTRUCTION_CACHE);		/* enable instruction cache */
#endif	/* USER_I_CACHE_ENABLE */

#ifdef	USER_D_CACHE_ENABLE
    cacheEnable (DATA_CACHE);			/* enable data cache */
#endif 	/* USER_D_CACHE_ENABLE */

#if (CPU == MC68060)
#ifdef 	USER_B_CACHE_ENABLE
    cacheEnable (BRANCH_CACHE);			/* enable branch cache */
#endif	/* USER_B_CACHE_ENABLE */
#endif	/* (CPU == MC68060) */
#endif  /* INCLUDE_CACHE_SUPPORT */

    /* start the kernel specifying usrRoot as the root task */

    kernelInit ((FUNCPTR) usrRoot, ROOT_STACK_SIZE,
		(char *) MEM_POOL_START_ADRS,
		sysMemTop (), ISR_STACK_SIZE, INT_LOCK_LEVEL);
    }

/*******************************************************************************
*
* usrRoot - the root task
*
* This is the first task to run under the multitasking kernel.  It performs
* all final initialization and then starts other tasks.
*
* It initializes the I/O system, installs drivers, creates devices, and sets
* up the network, etc., as necessary for a particular configuration.  It
* may also create and load the system symbol table, if one is to be included.
* It may then load and spawn additional tasks as needed.  In the default
* configuration, it simply initializes the VxWorks shell.
*
* RETURNS: N/A
*/
extern 	VOID BSP_SoftStart(VOID);
void usrRoot
    (
    char *	pMemPoolStart,		/* start of system memory partition */
    unsigned	memPoolSize		/* initial size of mem pool */
    )
    {
    char tyName [20];
    int  ix;

    /* Initialize the memory pool before initializing any other package.
     * The memory associated with the root task will be reclaimed at the
     * completion of its activities.
     */

#ifdef INCLUDE_MEM_MGR_FULL
    memInit (pMemPoolStart, memPoolSize);	/* initialize memory pool */
#else
    memPartLibInit (pMemPoolStart, memPoolSize);/* initialize memory pool */
#endif /* INCLUDE_MEM_MGR_FULL */

#ifdef	INCLUDE_SHOW_ROUTINES
    memShowInit ();				/* initialize memShow routine */
#endif	/* INCLUDE_SHOW_ROUTINES */

#if	defined(INCLUDE_MMU_BASIC) || defined(INCLUDE_MMU_FULL) || \
	defined(INCLUDE_MMU_MPU)
    usrMmuInit ();				/* initialize the mmu */
#endif	/* defined(INCLUDE_MMU_BASIC, INCLUDE_MMU_FULL, INCLUDE_MMU_MPU) */

#if	(CPU_FAMILY == PPC)
    excIntNestLogInit();			/* frameless nesting logger */
    /* Enable interrupts immediately after MMU */
    vxMsrSet(vxMsrGet() | taskMsrDefault);
#endif	/* (CPU_FAMILY == PPC) */

    /* set up system timer */

    sysClkConnect ((FUNCPTR) usrClock, 0);	/* connect clock ISR */
    sysClkRateSet (SYS_CLK_RATE);	/* set system clock rate */
    sysClkEnable ();				/* start it */

#ifdef INCLUDE_FAST_DRAM
/*
 * make use of data cache as fast DRAM,
 * establish parameters in config.h, MMU
 * must be initialed before data cache is
 * initialized as data ram...
 */
  cacheCreateInternalDataRAM((UINT32 *)FD_ORIGIN, FD_NUMLINES);
#endif

    /*
     * The select library needs to be initialized before the tyLib module
     * since the _func_selWakeupListInit FUNCPTR is required (SPR #3314).
     * The installation of the select task delete hooks is performed
     * later in usrRoot() after NFS and RPC have been initialized.
     */

#ifdef  INCLUDE_SELECT
    selectInit (NUM_FILES);
#endif	/* INCLUDE_SELECT */


    /* initialize I/O system */

#ifdef  INCLUDE_IO_SYSTEM
    iosInit (NUM_DRIVERS, NUM_FILES, "/null");

    consoleFd = NONE;                           /* assume no console device */

#ifdef  INCLUDE_TYCODRV_5_2
#ifdef  INCLUDE_TTY_DEV
    if ((NUM_TTY > 0))
	{
	tyCoDrv ();				/* install console driver */

	for (ix = 0; ix < NUM_TTY; ix++)	/* create serial devices */
	    {
	    sprintf (tyName, "%s%d", "/tyCo/", ix);

	    (void) tyCoDevCreate (tyName, ix, 512, 512);

	    if (ix == CONSOLE_TTY)
		strcpy (consoleName, tyName);	/* store console name */
	    }

	consoleFd = open (consoleName, O_RDWR, 0);

	/* set baud rate */

	(void) ioctl (consoleFd, FIOBAUDRATE, CONSOLE_BAUD_RATE);
	(void) ioctl (consoleFd, FIOSETOPTIONS, OPT_TERMINAL);
	}
#endif	/* INCLUDE_TTY_DEV */

#else   /* !INCLUDE_TYCODRV_5_2 */
#ifdef  INCLUDE_TTY_DEV
    if ((NUM_TTY > 0))
	{
	ttyDrv();				/* install console driver */

	for (ix = 0; ix < NUM_TTY; ix++)	/* create serial devices */
	    {
#if     (defined(INCLUDE_WDB) && (WDB_COMM_TYPE == WDB_COMM_SERIAL))
	    if (ix == WDB_TTY_CHANNEL)		/* don't use WDBs channel */
		continue;
#endif
	    sprintf (tyName, "%s%d", "/tyCo/", ix);
	    (void) ttyDevCreate (tyName, sysSerialChanGet(ix), 512, 512);

	    if (ix == CONSOLE_TTY)		/* init the tty console */
		{
		strcpy (consoleName, tyName);
		consoleFd = open (consoleName, O_RDWR, 0);
		(void) ioctl (consoleFd, FIOBAUDRATE, CONSOLE_BAUD_RATE);
		(void) ioctl (consoleFd, FIOSETOPTIONS, OPT_TERMINAL);
		}
	    }
	}
#endif  /* INCLUDE_TTY_DEV */

#ifdef INCLUDE_PC_CONSOLE
    pcConDrv ();
    for (ix = 0; ix < N_VIRTUAL_CONSOLES; ix++)
	{
	sprintf (tyName, "%s%d", "/pcConsole/", ix);
	(void) pcConDevCreate (tyName,ix, 512, 512);
	if (ix == PC_CONSOLE)		/* init the console device */
	    {
	    strcpy (consoleName, tyName);
	    consoleFd = open (consoleName, O_RDWR, 0);
	    (void) ioctl (consoleFd, FIOBAUDRATE, CONSOLE_BAUD_RATE);
	    (void) ioctl (consoleFd, FIOSETOPTIONS, OPT_TERMINAL);
	    }
	}
#endif	/* INCLUDE_PC_CONSOLE */

#endif  /* !INCLUDE_TYCODRV_5_2 */

    ioGlobalStdSet (STD_IN,  consoleFd);
    ioGlobalStdSet (STD_OUT, consoleFd);
    ioGlobalStdSet (STD_ERR, consoleFd);
#endif  /* INCLUDE_IO_SYSTEM */

    /* initialize symbol table facilities */

#ifdef	INCLUDE_SYM_TBL
    hashLibInit ();			/* initialize hash table package */
    symLibInit ();			/* initialize symbol table package */
#ifdef 	INCLUDE_SHOW_ROUTINES
    symShowInit ();			/* initialize symbol table show */
#endif	/* INCLUDE_SHOW_ROUTINES */
#endif	/* INCLUDE_SYM_TBL */

    /* initialize exception handling */

#if     defined(INCLUDE_EXC_HANDLING) && defined(INCLUDE_EXC_TASK)
#ifdef	INCLUDE_EXC_SHOW
    excShowInit ();
#endif
    excInit ();				/* initialize exception handling */
#endif  /* defined(INCLUDE_EXC_HANDLING) && defined(INCLUDE_EXC_TASK) */

#ifdef	INCLUDE_LSTLIB
    lstLibInit ();
#endif

#ifdef	INCLUDE_LOGGING
    logInit (consoleFd, MAX_LOG_MSGS);	/* initialize logging */
# ifdef	INCLUDE_LOG_STARTUP
    logMsg ("logging started to %s [%d], queue size %d\n",
		consoleName, consoleFd, MAX_LOG_MSGS, 4,5,6);
    taskDelay (2);	/* allow time for message to be displayed */
# endif	/* INCLUDE_LOG_STARTUP */
#endif	/* INCLUDE_LOGGING */

#ifdef	INCLUDE_SIGNALS
    sigInit ();				/* initialize signals */
#endif	/* INCLUDE_SIGNALS */

    /* initialize debugging */

#ifdef	INCLUDE_DEBUG
    dbgInit ();				/* initialize debugging */
#endif	/* INCLUDE_DEBUG */


    /* initialize pipe driver */

#ifdef	INCLUDE_PIPES
    pipeDrv ();				/* install pipe driver */
#endif	/* INCLUDE_PIPES */


    /* initialize standard I/O package */

#ifdef	INCLUDE_STDIO
    stdioInit ();			/* initialize standard I/O library */
#ifdef  INCLUDE_SHOW_ROUTINES
    stdioShowInit ();
#endif  /* INCLUDE_SHOW_ROUTINES */
#endif	/* INCLUDE_STDIO */

    /* initialize POSIX queued signals */

#if defined(INCLUDE_POSIX_SIGNALS) && defined(INCLUDE_SIGNALS)
    sigqueueInit (NUM_SIGNAL_QUEUES); /* initialize queued signals */
#endif

    /* initialize POSIX semaphores */

#ifdef  INCLUDE_POSIX_SEM
    semPxLibInit ();
#ifdef INCLUDE_SHOW_ROUTINES
    semPxShowInit ();
#endif  /* INCLUDE_SHOW_POUTINES */
#endif  /* INCLUDE_POSIX_SEM */

    /* initialize POSIX threads */

#ifdef INCLUDE_POSIX_PTHREADS
    pthreadLibInit ();
#endif  /* INCLUDE_POSIX_PTHREADS */

    /* initialize POSIX message queues */

#ifdef INCLUDE_POSIX_MQ
    mqPxLibInit (MQ_HASH_SIZE);
#ifdef INCLUDE_SHOW_ROUTINES
    mqPxShowInit ();
#endif  /* INCLUDE_SHOW_ROUTINES */
#endif  /* INCLUDE_POSIX_MQ */

    /* initialize POSIX async I/O support */

#ifdef INCLUDE_POSIX_AIO
    aioPxLibInit (MAX_LIO_CALLS);
#ifdef INCLUDE_POSIX_AIO_SYSDRV
    aioSysInit (MAX_AIO_SYS_TASKS, AIO_TASK_PRIORITY, AIO_TASK_STACK_SIZE);
#endif  /* INCLUDE_POSIX_AIO_SYSDRV */
#endif  /* INCLUDE_POSIX_AIO */

#ifdef INCLUDE_CBIO /* init main CBIO module, cbioLib() */
    cbioLibInit();
#endif INCLUDE_CBIO

    /* initialize filesystems and disk drivers */

#ifdef INCLUDE_DOSFS_MAIN  /* dosFs2 file system initialization */

    hashLibInit ();			/* initialize hash table package */

    /* First initialize the main dosFs module */

    dosFsLibInit( 0 );

    /* Initialize sub-modules */

    /* ensure that at least one directory handler is defined */

#   if ((!defined INCLUDE_DOSFS_DIR_VFAT) && \
	(!defined INCLUDE_DOSFS_DIR_FIXED))

#       define INCLUDE_DOSFS_DIR_VFAT  

#   endif 

    /* init VFAT (MS long file names) module */

#   ifdef INCLUDE_DOSFS_DIR_VFAT

    /* Sub-module: VFAT Directory Handler */

    dosVDirLibInit();

#   endif /* INCLUDE_DOSFS_DIR_VFAT */

    /* init strict 8.3 and vxLongNames handler */

#   ifdef INCLUDE_DOSFS_DIR_FIXED

    /* Sub-module: Vintage 8.3 and VxLong Directory Handler */

    dosDirOldLibInit();

#   endif /* INCLUDE_DOSFS_DIR_FIXED */

    /* Sub-module: FAT12/FAT16/FAT32 FAT Handler */

    dosFsFatInit();

#   ifdef INCLUDE_DOSFS_CHKDSK 

    /* Sub-module: Consistency check handler */

    dosChkLibInit();

#   endif /* INCLUDE_DOSFS_CHKDSK */

#   ifdef INCLUDE_DOSFS_FMT

    /* Sub-module: Formatter */

    dosFsFmtLibInit();           /* init dosFs scalable formatter */

#   endif /* INCLUDE_DOSFS_FMT */

#endif /* INCLUDE_DOSFS_MAIN */

    /* dosFs1 legacy code, dosFsInit(), usrDosFsOld.c */

#ifdef	INCLUDE_DOSFS
    hashLibInit ();			/* initialize hash table package */
    dosFsInit (NUM_DOSFS_FILES); 	/* init dosFs filesystem */
#endif	/* INCLUDE_DOSFS */

#ifdef	INCLUDE_RAWFS
    rawFsInit (NUM_RAWFS_FILES); 	/* init rawFs filesystem */
#endif	/* INCLUDE_RAWFS */

#ifdef	INCLUDE_RT11FS
    rt11FsInit (NUM_RT11FS_FILES); 	/* init rt11Fs filesystem */
#endif	/* INCLUDE_RT11FS */

#ifdef	INCLUDE_RAMDRV
    ramDrv ();				/* initialize ram disk driver */
#endif	/* INCLUDE_RAMDRV */

    /* Initialize PCCARD services */

#ifdef INCLUDE_PCCARD
    csInit (CS_PCCARD_STACK);
#ifdef INCLUDE_PCCARD_SHOW
    csShowInit ();
#endif /* INCLUDE_PCCARD_SHOW */
#endif /* INCLUDE_PCCARD */


    /* initialize USB components */

#ifdef INCLUDE_USB_INIT
    usbInit (); 		/* USB Host Stack Initialization */
#endif

#ifdef INCLUDE_UHCI_INIT
    usrUsbHcdUhciAttach (); 	/* UHCI Initialization */
#endif

#ifdef INCLUDE_OHCI_INIT
    usrUsbHcdOhciAttach (); 	/* OHCI Initialization */
#endif

#ifdef INCLUDE_USB_MOUSE_INIT
    usrUsbMseInit (); 		/* Mouse Driver Initialization */
#endif

#ifdef INCLUDE_USB_KEYBOARD_INIT
    usrUsbKbdInit (); 		/* Keyboard Driver Initialization */
#endif

#ifdef INCLUDE_USB_PRINTER_INIT
    usrUsbPrnInit (); 		/* Printer Driver Initialization */
#endif

#ifdef INCLUDE_USB_SPEAKER_INIT
    usrUsbSpkrInit (); 		/* Speaker Driver Initialization */
#endif

#ifdef INCDLUE_USB_AUDIO_DEMO
    usrUsbAudioDemo (); 	/* USB Audio Demo */
#endif

#ifdef INCLUDE_USB_MS_BULKONLY_INIT
    usrUsbBulkDevInit(); 	/* Bulk Driver Initialization */
#endif

#ifdef INCLUDE_USB_MS_CBI_INIT
    usrUsbCbiUfiDevInit (); 	/* CBI Driver Initialization */
#endif

#ifdef INCLUDE_USB_PEGASUS_END_INIT
    usrUsbPegasusEndInit (); 	/* Pegasus Driver Initialization */
#endif


#ifdef	INCLUDE_SCSI

    /*
     * initialize either the SCSI1 or SCSI2 interface; initialize SCSI2 when
     * the SCSI2 interface is available.
     */

#ifndef INCLUDE_SCSI2
    scsi1IfInit ();
#else
    scsi2IfInit ();
#endif

    /* initialize SCSI controller */
    if (sysScsiInit () == OK)
	{
	usrScsiConfig ();			/* configure SCSI peripherals */
	}
    else
	{
#ifdef INCLUDE_STDIO
	printf ("sysScsiInit() Failed, SCSI system not initialized\n");
#endif  /* INCLUDE_STDIO */
	}

#endif	/* INCLUDE_SCSI */

#ifdef  INCLUDE_FD     /* initialize floppy disk driver */
    if ((fdDrv (FD_INT_VEC, FD_INT_LVL)) == ERROR)
    	{
#ifdef INCLUDE_STDIO
	printf ("fdDrv returned ERROR from usrRoot.\n");
#endif /* INCLUDE_STDIO */
	}
#endif /* INCLUDE_FD */

#ifdef  INCLUDE_IDE
    /* init IDE disk driver */
    if ((ideDrv (IDE_INT_VEC, IDE_INT_LVL, IDE_CONFIG)) == ERROR)
	{
#ifdef INCLUDE_STDIO
	printf ("ideDrv returned ERROR from usrRoot.\n");
#endif /* INCLUDE_STDIO */
	}

#endif  /* INCLUDE_IDE */

#ifdef  INCLUDE_ATA
    {                                   /* initialize hard disk driver */
    IMPORT ATA_RESOURCE ataResources[];
    ATA_RESOURCE *pAtaResource;
    for (ix = 0; ix < ATA_MAX_CTRLS; ix++)
	{
	pAtaResource = &ataResources[ix];
	if (pAtaResource->ctrlType == IDE_LOCAL)
	    if ((ataDrv (ix, pAtaResource->drives, pAtaResource->intVector,
		   pAtaResource->intLevel, pAtaResource->configType,
		   pAtaResource->semTimeout, pAtaResource->wdgTimeout))
		== ERROR)
		{
#ifdef INCLUDE_STDIO
		printf ("ataDrv returned ERROR from usrRoot.\n");
#endif /* INCLUDE_STDIO */
		}
	}
    }

#ifdef  INCLUDE_SHOW_ROUTINES
    ataShowInit ();                     /* install ATA/IDE show routine */
#endif  /* INCLUDE_SHOW_ROUTINES */
#endif  /* INCLUDE_ATA */

#ifdef INCLUDE_PCCARD
    csClientLoad (CS_ATA_ENABLER);
#endif /* INCLUDE_PCCARD */

#ifdef  INCLUDE_LPT
    {
    IMPORT LPT_RESOURCE lptResources[];
    lptDrv (LPT_CHANNELS, &lptResources[0]); /* init LPT parallel driver */
    }
#endif  /* INCLUDE_LPT */

#ifdef  INCLUDE_PCMCIA
#ifdef  INCLUDE_SHOW_ROUTINES
    pcmciaShowInit ();			/* install PCMCIA show routines */
#endif  /* INCLUDE_SHOW_ROUTINES */
    pcmciaInit ();			/* init PCMCIA Lib */
#endif  /* INCLUDE_PCMCIA */

#ifdef	INCLUDE_TFFS
    tffsDrv ();				/* it should be after pcmciaInit() */
#endif	/* INCLUDE_TFFS */

#ifdef  INCLUDE_FORMATTED_IO
    fioLibInit ();			/* initialize formatted I/O */
#endif  /* INCLUDE_FORMATTED_IO */

    /* initialize floating point facilities */

#ifdef	INCLUDE_FLOATING_POINT
    floatInit ();			/* initialize floating point I/O */
#endif	/* INCLUDE_FLOATING_POINT */

    /* install software floating point emulation (if applicable) */

#ifdef	INCLUDE_SW_FP
    mathSoftInit ();		/* use software emulation for fp math */
#endif	/* INCLUDE_SW_FP */

    /* install hardware floating point support (if applicable) */

#ifdef	INCLUDE_HW_FP
    mathHardInit (); 		/* do fppInit() & install hw fp math */

#ifdef	INCLUDE_SHOW_ROUTINES
    fppShowInit ();			/* install hardware fp show routine */
#endif	/* INCLUDE_SHOW_ROUTINES */
#endif	/* INCLUDE_HW_FP */

    /* install dsp support (if applicable) */

#ifdef	INCLUDE_DSP
    usrDspInit (); 			/* do dspInit() */
#endif	/* INCLUDE_DSP */

    /* initialize AltiVec library (if applicable) */

#ifdef	INCLUDE_ALTIVEC
    usrAltivecInit ();
#endif	/* INCLUDE_ALTIVEC */

    /* initialize Spe library (if applicable) */

#ifdef	INCLUDE_SPE
    usrSpeInit ();
#endif	/* INCLUDE_SPE */

    /* initialize performance monitoring tools */

#ifdef	INCLUDE_SPY
    spyLibInit ();			/* install task cpu utilization tool */
#endif	/* INCLUDE_SPY */

#ifdef	INCLUDE_TIMEX
    timexInit ();			/* install function timing tool */
#endif	/* INCLUDE_TIMEX */

#ifdef  INCLUDE_ENV_VARS
    envLibInit (ENV_VAR_USE_HOOKS);	/* initialize environment variable */
#endif	/* INCLUDE_ENV_VARS */

#ifdef INCLUDE_NTPASSFS
    {
    IMPORT int	    ntPassFsInit();
    IMPORT void *   ntPassFsDevInit();
    IMPORT char	    fullExePath[];
    char	    passName [MAX_FILENAME_LENGTH];
    char *	    defPathEnd;
    
    if (ntPassFsInit(1) == OK)
    	{	
    	if (ntPassFsDevInit("host:") == NULL)
    	    {
#ifdef INCLUDE_STDIO
	    printf ("ntPassFsDevInit failed for host: \n");
#endif /* INCLUDE_STDIO */
	    }
	else
	    {
    	    sprintf (passName, "host:%s", fullExePath);

	    /* Remove bootFile name at the end of the string */

    	    defPathEnd = strrchr (passName, '/');
    	    if (defPathEnd != NULL)
    		*defPathEnd = '\0';

    	    ioDefPathSet (passName);
	    }
	}
    else	
    	{
#ifdef INCLUDE_STDIO
	printf ("ntPassFsInit failed\n");
#endif /* INCLUDE_STDIO */
	}
    }
#endif /* INCLUDE_NTPASSFS */

    /* initialize object module loader */

#ifdef	INCLUDE_LOADER
    moduleLibInit ();			/* initialize module manager */

#if	defined(INCLUDE_AOUT)
    loadAoutInit ();				/* use a.out format */
#else	/* coff or ecoff */
#if	defined(INCLUDE_ECOFF)
    loadEcoffInit ();				/* use ecoff format */
#else	/* ecoff */
#if	defined(INCLUDE_COFF)
    loadCoffInit ();				/* use coff format */
#else   /* coff */
#if	defined(INCLUDE_ELF)
    loadElfInit ();				/* use elf format */
#else
#if	defined(INCLUDE_SOM_COFF)
    loadSomCoffInit ();
#else
#if	defined(INCLUDE_PECOFF)
    {
    extern int loadPecoffInit();

    loadPecoffInit ();
    }
#endif
#endif
#endif
#endif
#endif
#endif

#endif	/* INCLUDE_LOADER */

    /* initialize network */

#ifdef  INCLUDE_NET_INIT
    usrBootLineInit (sysStartType);	/* crack the bootline */
# if defined(INCLUDE_LOGGING) && defined(INCLUDE_LOG_STARTUP)
    logMsg ("before usrNetInit()\n", 1,2,3,4,5,6);
    taskDelay (2);	/* allow time for message to be displayed */
# endif	/* INCLUDE_LOGGING && INCLUDE_LOG_STARTUP */
    usrNetInit (BOOT_LINE_ADRS);	/* initialize network support */
# if defined(INCLUDE_LOGGING) && defined(INCLUDE_LOG_STARTUP)
    logMsg ("after usrNetInit()\n", 1,2,3,4,5,6);
    taskDelay (2);	/* allow time for message to be displayed */
# endif	/* INCLUDE_LOGGING && INCLUDE_LOG_STARTUP */
#endif	/* INCLUDE_NET_INIT */

#ifdef	INCLUDE_PASSFS
    {
    extern STATUS passFsInit ();
    extern void *passFsDevInit ();
    char passName [256];

    if (passFsInit (1) == OK)
	{
	extern char vxsim_hostname[];
	extern char vxsim_cwd[];

	sprintf (passName, "%s:", vxsim_hostname);
	if (passFsDevInit (passName) == NULL)
	    {
#ifdef INCLUDE_STDIO
	    printf ("passFsDevInit failed for <%s>\n", passName);
#endif /* INCLUDE_STDIO */
	    }
	else
	    {
	    sprintf (passName, "%s:%s", vxsim_hostname, vxsim_cwd);
	    ioDefPathSet (passName);
	    }
	}
    else
#ifdef INCLUDE_STDIO
	printf ("passFsInit failed\n");
#endif /* INCLUDE_STDIO */
    }
#endif	/* INCLUDE_PASSFS */

#ifdef	INCLUDE_DOS_DISK
    {
    char unixName [80];
    extern void unixDrv ();
    extern void unixDiskInit ();
    extern char *u_progname;  /* home of executable */
    char *pLastSlash;

    unixDrv ();

    pLastSlash = strrchr (u_progname, '/');
    pLastSlash = (pLastSlash == NULL) ? u_progname : (pLastSlash + 1);
    sprintf (unixName, "/tmp/%s%d.dos", pLastSlash, sysProcNumGet());
    unixDiskInit (unixName, "A:", 0);
    }
#endif	/* INCLUDE_DOS_DISK */

    /* initialize shared memory objects */

#ifdef INCLUDE_SM_OBJ			/* unbundled shared memory objects */
    usrSmObjInit (BOOT_LINE_ADRS);
#endif /* INCLUDE_SM_OBJ */

   /* initialize WindMP */

#ifdef INCLUDE_VXFUSION			/* unbundled VxFusion (distributed objects) */
    usrVxFusionInit (BOOT_LINE_ADRS);
#ifdef INCLUDE_SHOW_ROUTINES
    {
    extern void msgQDistShowInit();
    extern void distNameShowInit ();
    extern void distIfShowInit ();
    extern void msgQDistGrpShowInit ();

    msgQDistShowInit();
    distNameShowInit ();
    distIfShowInit ();
    msgQDistGrpShowInit ();
    }
#endif /* INCLUDE_SHOW_ROUTINES */
#endif /* INCLUDE_WINDMP */

    /* write protect text segment & vector table only after bpattach () */

#ifdef	INCLUDE_MMU_FULL		/* unbundled mmu product */
#ifdef	INCLUDE_PROTECT_TEXT
    if (vmTextProtect () != OK)
	printf ("\nError protecting text segment. errno = %x\n", errno);
#endif	/* INCLUDE_PROTECT_TEXT */

#ifdef	INCLUDE_PROTECT_VEC_TABLE
    if (intVecTableWriteProtect () != OK)
	printf ("\nError protecting vector table. errno = %x\n", errno);
#endif	/* INCLUDE_PROTECT_VEC_TABLE */
#endif	/* INCLUDE_MMU_FULL */

    /* install select hook only after NFS/RPC for proper delete hook order */

#ifdef	INCLUDE_SELECT
    selTaskDeleteHookAdd ();
#endif	/* INCLUDE_SELECT */

    /* create system and status symbol tables */

#ifdef  INCLUDE_STANDALONE_SYM_TBL
# if defined(INCLUDE_LOGGING) && defined(INCLUDE_LOG_STARTUP)
    logMsg ("before symTblCreate()\n", 1,2,3,4,5,6);
    taskDelay (2);	/* allow time for message to be displayed */
# endif	/* INCLUDE_LOGGING && INCLUDE_LOG_STARTUP */
    sysSymTbl = symTblCreate (SYM_TBL_HASH_SIZE_LOG2, TRUE, memSysPartId);

    printf ("\nAdding %ld symbols for standalone.\n", standTblSize);

    /* fill in from built in table*/

    for (ix = 0; (ULONG) ix < standTblSize; ix++)
#if	((CPU_FAMILY == ARM) && ARM_THUMB)
	thumbSymTblAdd (sysSymTbl, &(standTbl[ix]));
#else
	symTblAdd (sysSymTbl, &(standTbl[ix]));
#endif	/* CPU_FAMILY == ARM */
# if defined(INCLUDE_LOGGING) && defined(INCLUDE_LOG_STARTUP)
    logMsg ("sysSymTbl complete.\n", 1,2,3,4,5,6);
    taskDelay (2);	/* allow time for message to be displayed */
# endif	/* INCLUDE_LOGGING && INCLUDE_LOG_STARTUP */
#endif	/* INCLUDE_STANDALONE_SYM_TBL */

#ifdef  INCLUDE_NET_SYM_TBL
    sysSymTbl = symTblCreate (SYM_TBL_HASH_SIZE_LOG2, TRUE, memSysPartId);

    netLoadSymTbl ();				/* fill in table from host */
#endif	/* INCLUDE_NET_SYM_TBL */

#ifdef  INCLUDE_STAT_SYM_TBL
    statSymTbl = symTblCreate (STAT_TBL_HASH_SIZE_LOG2, FALSE, memSysPartId);

    for (ix = 0; (ULONG)ix < statTblSize; ix ++) /* fill in from builtin table*/
	symTblAdd (statSymTbl, &(statTbl [ix]));
#endif	/* INCLUDE_STAT_SYM_TBL */

#ifdef	INCLUDE_SYM_TBL_SYNC
    /* initialize wtx client to synchronize host and target symbol tables */

    symSyncLibInit ();
#endif /* INCLUDE_SYM_TBL_SYNC */

    /* initialize C++ support library */

#if	defined (INCLUDE_CPLUS) && defined (INCLUDE_CPLUS_MIN)
#error	Define only one of INCLUDE_CPLUS or INCLUDE_CPLUS_MIN, not both
#endif

#if	defined (INCLUDE_CPLUS) || defined (INCLUDE_CPLUS_MIN)
#ifndef INCLUDE_CTORS_DTORS
#define INCLUDE_CTORS_DTORS
#endif
#endif

#ifdef  INCLUDE_CTORS_DTORS 
  /* 
   * call compiler generated init functions (usually - but not necessarily -
   * C++ related)
   */
   cplusCtorsLink ();
#endif

#ifdef	INCLUDE_CPLUS			/* all standard C++ runtime support */
    cplusLibInit ();
#endif

#ifdef	INCLUDE_CPLUS_MIN		/* minimal C++ runtime support */
    cplusLibMinInit ();
#endif

#ifdef INCLUDE_CPLUS_DEMANGLER
    cplusDemanglerInit ();
#endif

    /* initialize COM/DCOM runtime support */
#ifdef INCLUDE_COM
    comLibInit ();
#endif
#ifdef INCLUDE_DCOM
    dcomLibInit ();
#endif

    /* initialize Wind Web Server */

#ifdef INCLUDE_HTTP
    httpd ();
#endif /* INCLUDE_HTTP */

#ifdef   INCLUDE_RBUFF                  /* install rBuff support */
    rBuffLibInit();
#ifdef  INCLUDE_SHOW_ROUTINES
    rBuffShowInit ();                   /* install rBuff show routine */
#endif  /* INCLUDE_SHOW_ROUTINES */
#endif /* INCLUDE_RBUFF */

#ifdef INCLUDE_WINDVIEW
    windviewConfig ();
#endif /* INCLUDE_WINDVIEW */


    /* initialize the WDB debug agent */

#ifdef  INCLUDE_WDB
# if defined(INCLUDE_LOGGING) && defined(INCLUDE_LOG_STARTUP)
    logMsg ("before wdbConfig()\n", 1,2,3,4,5,6);
    taskDelay (2);	/* allow time for message to be displayed */
# endif	/* INCLUDE_LOGGING && INCLUDE_LOG_STARTUP */
    wdbConfig();
# if defined(INCLUDE_LOGGING) && defined(INCLUDE_LOG_STARTUP)
    logMsg ("after wdbConfig()\n", 1,2,3,4,5,6);
    taskDelay (2);	/* allow time for message to be displayed */
# endif	/* INCLUDE_LOGGING && INCLUDE_LOG_STARTUP */

#ifdef	INCLUDE_WDB_BANNER

#if (WDB_COMM_TYPE == WDB_COMM_NETWORK)
#define WDB_COMM_TYPE_STR "WDB_COMM_NETWORK"
#endif /* WDB_COMM_TYPE == WDB_COMM_NETWORK */

#if (WDB_COMM_TYPE == WDB_COMM_SERIAL)
#define WDB_COMM_TYPE_STR "WDB_COMM_SERIAL"
#endif /* WDB_COMM_TYPE == WDB_COMM_SERIAL */

#if (WDB_COMM_TYPE == WDB_COMM_TYCODRV_5_2)
#define WDB_COMM_TYPE_STR "WDB_COMM_TYCODRV_5_2"
#endif /* WDB_COMM_TYPE == WDB_COMM_TYCODRV_5_2 */

#if (WDB_COMM_TYPE ==  WDB_COMM_NETROM)
#define WDB_COMM_TYPE_STR "WDB_COMM_NETROM"
#endif /* WDB_COMM_TYPE == WDB_COMM_NETROM */

#if (WDB_COMM_TYPE ==  WDB_COMM_VTMD)
#define WDB_COMM_TYPE_STR "WDB_COMM_VTMD"
#endif /* WDB_COMM_TYPE == WDB_COMM_VTMD */

#if (WDB_COMM_TYPE ==  WDB_COMM_END)
#define WDB_COMM_TYPE_STR "WDB_COMM_END"
#endif /* WDB_COMM_TYPE == WDB_COMM_END */

#if (WDB_COMM_TYPE ==  WDB_COMM_CUSTOM)
#define WDB_COMM_TYPE_STR "WDB_COMM_CUSTOM"
#endif /* WDB_COMM_TYPE == WDB_COMM_CUSTOM */

#if (WDB_COMM_TYPE ==  WDB_COMM_PIPE)
#define WDB_COMM_TYPE_STR "WDB_COMM_PIPE"
#endif /* WDB_COMM_TYPE == WDB_COMM_PIPE */

#ifndef WDB_COMM_TYPE_STR
#define WDB_COMM_TYPE_STR "Unknown"
#endif /* WDB_COMM_TYPE_STR */

#ifndef INCLUDE_SHELL
    /* WDB banner same as printed by usrWdbBanner */
    printf ("\n\n");
    printf ("%23s\n\n", runtimeName);
    printf ("Copyright 1984-2002  Wind River Systems, Inc.\n\n");
    printf ("            CPU: %s\n", sysModel ());
    printf ("   Runtime Name: %s\n", runtimeName);
    printf ("Runtime Version: %s\n", runtimeVersion);
    printf ("    BSP version: " BSP_VERSION BSP_REV "\n");
    printf ("        Created: %s\n", creationDate);
    printf ("  WDB Comm Type: %s\n", WDB_COMM_TYPE_STR);
    printf ("            WDB: %s.\n\n",
	    ((wdbRunsExternal () || wdbRunsTasking ()) ?
		 "Ready" : "Agent configuration failed") );
	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
#endif /*INCLUDE_SHELL*/

#endif /*INCLUDE_WDB_BANNER*/

#endif  /* INCLUDE_WDB */

    /* initialize interactive shell */

#ifdef  INCLUDE_SHELL
#ifdef	INCLUDE_SECURITY			/* include shell security */
	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
    if ((sysFlags & SYSFLG_NO_SECURITY) == 0)
	{
		printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
	loginInit ();				/* initialize login table */
	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
	shellLoginInstall (loginPrompt, 0);	/* install security program */

	/* add additional users here as required */

#if defined(LOGIN_USER_NAME) && defined(LOGIN_PASSWORD)
	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
	loginUserAdd (LOGIN_USER_NAME, LOGIN_PASSWORD);
#endif	
	}
#endif	/* INCLUDE_SECURITY */

	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
    printLogo ();				/* print out the banner page */

	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
    printf ("                               ");
    printf ("CPU: %s.  Processor #%d.\n", sysModel (), sysProcNumGet ());
    printf ("                              ");
#ifdef	HITACHI_SH_KERNEL_ON_SDRAM
    printf ("Memory Size: 0x%x.", (UINT)(sysMemTop () - (char *)FREE_RAM_ADRS));
#else	/* HITACHI_SH_KERNEL_ON_SDRAM */
    printf ("Memory Size: 0x%x.", (UINT)(sysMemTop () - (char *)LOCAL_MEM_LOCAL_ADRS));
#endif	/* HITACHI_SH_KERNEL_ON_SDRAM */
    printf ("  BSP version " BSP_VERSION BSP_REV ".");
#if defined(INCLUDE_WDB) && defined(INCLUDE_WDB_BANNER)
    printf ("\n                             ");
    printf ("WDB Comm Type: %s", WDB_COMM_TYPE_STR);
    printf ("\n                            ");
    printf ("WDB: %s.",
	    ((wdbRunsExternal () || wdbRunsTasking ()) ?
		 "Ready" : "Agent configuration failed") );
	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
#endif /*INCLUDE_WDB && INCLUDE_WDB_BANNER*/
    printf ("\n\n");

#ifdef	INCLUDE_STARTUP_SCRIPT			/* run a startup script */
    if (sysBootParams.startupScript [0] != EOS)
	usrStartupScript (sysBootParams.startupScript);
#endif	/* INCLUDE_STARTUP_SCRIPT */

    shellInit (SHELL_STACK_SIZE, TRUE);		/* create the shell */


    /* only include the simple demo if the shell is NOT included */

#else
#if defined(INCLUDE_DEMO)			/* create demo w/o shell */
    taskSpawn ("demo", 20, 0, 2000, (FUNCPTR)usrDemo, 0,0,0,0,0,0,0,0,0,0);
#endif						/* mips cpp no elif */

#endif	/* INCLUDE_SHELL */

#ifdef  INCLUDE_WINDML
    usrWindMlInit ();
#endif  /* INCLUDE_WINDML */

#if defined (INCLUDE_SOUND) && defined(INCLUDE_SB16)
    sb16Drv ();            /* install sound driver SB16 */

    sb16DevCreate ("/sound", 0x220, 5, 1, 5);
#endif /* INCLUDE_SOUND && INCLUDE_SB16 */

#if defined(INCLUDE_JAVA)
    javaConfig ();
#endif	/* INCLUDE_JAVA */

#ifdef INCLUDE_HTML
    usrHtmlInit ();
#endif /* INCLUDE_HTML */

#if CPU==SIMNT
    win_ReleaseMutex(simUpMutex);
#endif

#ifdef INCLUDE_USER_APPL
    /* Startup the user's application */

    USER_APPL_INIT;	/* must be a valid C statement or block */
#endif
	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
	BSP_SoftStart();
}

/*******************************************************************************
*
* usrClock - user-defined system clock interrupt routine
*
* This routine is called at interrupt level on each clock interrupt.
* It is installed by usrRoot() with a sysClkConnect() call.
* It calls all the other packages that need to know about clock ticks,
* including the kernel itself.
*
* If the application needs anything to happen at the system clock interrupt
* level, it can be added to this routine.
*
* RETURNS: N/A
*/

void usrClock ()

    {
    tickAnnounce ();	/* announce system tick to kernel */
    }

#ifdef	INCLUDE_DEMO

/********************************************************************************
* usrDemo - example application without shell
*
* This routine is spawned as a task at the end of usrRoot(), if INCLUDE_DEMO
* is defined, and INCLUDE_SHELL is NOT defined in configAll.h or config.h.
* It is intended to indicate how a shell-less application can be linked,
* loaded, and ROMed.
*
* NOMANUAL
*/

void usrDemo (void)

    {
    char string [40];

    printf ("VxWorks (for %s) version %s.\n", sysModel (), vxWorksVersion);
    printf ("Kernel: %s.\n", kernelVersion ());
    printf ("Made on %s.\n", creationDate);

    FOREVER
	{
	printf ("\nThis is a test.  Type something: ");
	fioRdString (STD_IN, string, sizeof (string));
	printf ("\nYou typed \"%s\".\n", string);

	if (strcmp (string, "0") == 0)
	    memShow (0);

	if (strcmp (string, "1") == 0)
	    memShow (1);
	}
    }

#endif	/* INCLUDE_DEMO */
