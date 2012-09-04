'\" t
.so wrs.an
.\" at91rm9200/target.nr - Ateml AT91RM9200DK/EK board's target-specific documentation
.\"

.\"
.\" modification history
.\" --------------------
.\" 01a,1aug05,ajb  created, derived from pid920t
.\"
.TH AT91RM9200 T "Atmel AT91rm9200DK/EK" "Rev: 21 Feb 00" "TORNADO REFERENCE: VXWORKS"

.SH "NAME"
.aX "Atmel AT91rm9200DK/EK "

.SH "INTRODUCTION"
This reference entry provides board-specific information necessary to run
VxWorks for the Atmel AT91rm9200DK/EK evaluation board.  Before using a board with VxWorks, 
verify that the board runs in the factory configuration using vendor-supplied 
ROMs and jumper settings and checking the RS-232 connection.

.SS "ARM 920Tsupport"
The ARM 920T cache/MMMU support is used to create five memory regions:

RAM, from 0  to LOCAL_MEM_SIZE, is cached.  
Note that if auto-sizing is added, this should adjust the size of this
region correspondingly.

The peripheral registers area, 0x10000000 (INTEGRATOR_PERIPHERAL_BASE) to
0x20000000 (+INTEGRATOR_PERIPHERAL_SIZE), is uncached.

Flash memory, starting at 0x24000000 (FLASH_ADRS) to 0x28000000
(+INTEGRATOR_FLASH_SIZE), is uncached.

The PCI address space region starting at 0x40000000 (INTEGRATOR_PCI_BASE) 
and finishing at 0x60000000.

PCI IO area, config area and V360EPC registers, starting at 0x60000000 
(CPU_PCI_IO_ADRS) with CPU_PCI_IO_SIZE. 

All other regions are marked as invalid.

.SS "ARM 946es support"

NOTE: Cache and MMU support for the 946e is not included in the architecture
archives for the 946e.  In order to obtain support for this core, it is 
necessary to apply a patch (SPR-68958).  Consult WindSurf for this update.

In addition to the memory regions defined for the 940T/740T, a sixth
region was created for the I-SSRAM memory region.  SSRAM is not enabled 
in this implementation.  The address region is defined for compatibility 
with systems that make use of SSRAM.  When not enabled, I-SSRAM address 
space is supported by system RAM.  This region is not used by either
the bootrom image or vxWorks.  The arm architecture requires that the
exception vectors be located at address zero.  These vectors are placed
at the bottom of this region.  This region is not cached.

If D-SSRAM is used, a separate region will need to be defined in 
sysLib.c.

.SS "ARM Firmware Suite Flash library conformance"

The AFS Flash library defines a mechanism for storing multiple images
in Flash.  Each image can be identified by a record ('footer') which is
stored at the end of the last Flash page used by the image.  A special
type of image is used to store System Information Blocks ('SIB').  The
standard Integrator boot-switcher uses a SIB to store system settings,
such as core and bus clock speeds.

The current BSP implementation doesn't use this information.  Instead,
default values are chosen based on the CPU type.

Flash is used to store the boot line parameters.  The location in Flash
is defined by FLASH_ADRS.  This location in Flash can be changed by
modifying the block number in the definition of FLASH_ADRS (cf.
integrator.h).  If INCLUDE_FLASH_SIB_FOOTER is defined, a footer is
written at the end of this block to mark it as a Wind River Systems
type (TYPE_WRS_SIB).  This complies with the footer format used with
AFS.

.SS "ROM Init code"

Most of the code in romInit.s has been copied from uHAL's start-up
macros for the Integrator.  The board-specific code starts at HiPosn,
where the Core Module remap flag is set.

The code to calculate the size of SDRAM/SSRAM is copied directly from
uHAL's target.s.  As described in the comments, this leaves r1
containing the size of RAM available.  This value is stored in the
variable integratorMemSize, but is not currently used.


.SS "Boot ROMs"

The boot ROM image has been tested running from Flash.  The Makefile
options are set to run the image from the start of Flash, 0x24000000.
Two methods are available for loading the boot ROM image into target 
flash.  The image may be loaded via the target serial port using the 
supplied onboard boot Monitor program (ref: ARM Firmware Suite 
Reference Guide Chapt 4).  To load the target flash using this method,
first build bootrom.hex using the Tornado.  Connect a null serial cable
from the host serial port to the target Comm-1 port (closest to the 
dip-switches).  Open a terminal emulator program and configure it for 
38400 baud.  Power on the Integrator board and observe the ARM boot ROM 
banner.  Download the flash image by typing "L <enter>" for
load image.  Observe that the firmware deletes image zero.  Select
Transfer->SendTextFile, then browse to find the above hex file.  After the
download initiates, type "<control-C>".  The terminal window will remain
silent for approximately two minutes, after which it will acknowledge that 
the download has completed and return a boot monitor prompt.
  
Note: Some serial communication programs do not work properly if they
do not delay (approx 5ms) between sending characters.  Other
serial communication programs (such as Hyperterminal) may take an
extraordinary amount of time (1 hour) to program the flash because
they continuously time out from being unable to handle the
communication protocol used by the ARM boot loader.

The ARM Flash Utility (AFU) can be used to program the image into
Flash.  For this the bootrom needs to be generated and converted to 
binary format:
.bS
   make bootrom.hex
.bE
The 4-pole DIL switch (S1) is used to control the boot settings.  Turn
S1-1 off to boot from the start of Flash (0x24000000).  With S1-1 on,
the boot switcher will run, in which case S1-4 determines whether to
enter the boot monitor console (s1-4 on), or boot from a defined Flash
image (s1-4 off).

The ARM debugger can be used to load this binary image onto Flash.
For this choose a backend to connect to the target and start the ARM 
debugger and set S1-1 on.  Load and run the semihosted AFU.AXF until 
there are some messages printed in the ARM debugger console window 
with a AFU> prompt. 

To see a listing of the images present in the Flash enter the 
following command:
.bS
    AFU> list
.bE
Assuming there is already an image with number 1 in Flash, the new 
binary image can replace it with the following sequence of commands:
.bS
  AFU> Delete 1
  AFU> Program 1 VxBoot c:\Tornado\target\config\integrator940t\bootrom.bin b0
.bE

The board can use this new image to boot from by setting S1-1 off.

The boot monitor's BI command determines which Flash image to boot from.

.SS "Libraries"

Included within this BSP release are two directories containing object 
files:
.bS
     - objARMARCH4gnuvx 
     - objARMARCH4_Tgnuvx
.bE

These must be used to add and replace the versions of these files contained 
within the architecture libraries:
.bS
    target/lib/libARMARCH4gnuvx.a
    target/lib/libARMARCH4_Tgnuvx.a
.bE

If this is not done, kernels will be built which may fail to start, or in the 
case of ARM720T, kernels will fail to build.

First, make a copy of the existing library files in case something goes wrong. 
Replace the object file in the libraries using commands like:
.bS
    cp objARMARCH4gnuvx/* $(WIND_BASE)/target/lib/objARMARCH4gnuvx
    ararm crus $(WIND_BASE)/target/lib/libARMARCH4gnuvx.a \
	       $(WIND_BASE)/target/lib/objARMARCH4gnuvx/*
and
    cp objARMARCH4_Tgnuvx/* $(WIND_BASE)/target/lib/objARMARCH4_Tgnuvx
    ararm crus $(WIND_BASE)/target/lib/libARMARCH4_Tgnuvx.a \
	       $(WIND_BASE)/target/lib/objARMARCH_T4gnuvx/*
.bE

.SS "Jumpers"
The following jumpers and switches are relevant to VxWorks configuration.

.TS E
expand;
cf3 s s
lf3 lf3 lf3
l l lw(3i) .
.ne 5
Integrator 940T
.sp .25
Jumper	Function	Description
_
S1	Various	T{
Four-pole DIL switches, S1-1 to S1-4
T}
S1-1	Boot ROM select	T{
This switch determines which device is mapped to low memory at startup
(before the header card maps its own RAM to address 0).  When the
switch is turned ON, the boot ROM is selected, causing the AFS Boot
Monitor to execute.  Otherwise, Flash is selected.
T}
S1-4	Boot switcher 	T{
The boot monitor reads this switch at startup to determine whether to
continue execution or jump to Flash.  If the switch is ON, the boot
monitor prompt is generated; otherwise it reads the SIB to determine
which Flash block to jump to.
T}
.TE

For details of jumper configuration, see the board diagram at the end
of this entry and in the hardware manual.

.SH "FEATURES"

The Integrator/AP is a platform for code development for embedded ARM
processors.  It supports up to four processors for which it provides clocks, 
bus arbitration and interrupt handling.  It also provides Flash memory, 
boot ROM, 2 serial ports, readable switches and controllable LEDS.

The Integrator/AP supports flexible expansion:

 - system bus expansion allowing core modules and logic modules to be added.
 - PCI bus bridge allowing PCI expansion cards to be mounted.
 - extension to the PCI bus allowing the Integrator/AP to be installed in a 
   CompactPCI card rack.

The ARM720T, ARM740T and ARM940T daughter cards can be used with
this BSP.

.SS "Supported Features"

The BSP supports and has been tested with PCI Ethernet cards containing
the Digital 21x4x Ethernet controller chip.

.SS "RAM size"

By default, the RAM size is set to 8 Mbytes (see LOCAL_MEM_SIZE).  This
requires an SDRAM DIMM of at least that size to be fitted to the core
module header card.  The RAM size is configured by changing
LOCAL_MEM_SIZE in config.h.  If this is reduced below 8 MBytes, other
values may need changing, such as RAM_HIGH_ADRS.  The boot ROM
initialization code automatically reads the SPD data from the SDRAM to
configure CM_SDRAM correctly (see CM940T User Guide, p. 4-14).
However, this data is not currently used to derive a correct value for
the memory size.

.SS "Timestamp support"

The two AMBA timers are used by the system and auxiliary clock
facilities.  The system clock provides the timestamp timer as well.


.SS "Unsupported Features"

No explicit support is provided for use of the JTAG port, EmbeddedICE, 
reading the switches, or any other PCI cards.  However, nothing is done
to prevent these features from being used (e.g. by the Multi-ICE
backend for Tornado).

.SS "Flash memory as NVRAM"

If the BSP is configured with INCLUDE_FLASH defined, the standard VxWorks
Flash support is included.  
  
.SS "WindML Support"

WindML 2.0 is supported on the integrator7tdmi.  Other integrator
versions have not been tested with WindML and no WindML support is
included for those BSPs.

If the BSP is configured with INCLUDE_WINDML defined, support for
WindML 2.0 is included.  Otherwise, WindML will not be
enabled.  Additionally, the WindML drivers need to be configured
properly as described in the "WindML Programmer's Guide",  Part#
DOC-13632-ND-02.

Modify the file target/src/ugl/config/uglInit.h as follows:

.bS
 #define INCLUDE_IGS_GRAPHICS
 #define INCLUDE_CUSTOM_KEYBOARD
 #define INCLUDE_CUSTOM_POINTER
 #define JP3_ON
.bE

Because this configuration uses custom keyboard and mouse drivers, the
file target/h/ugl/config/uglCustom.h must be created from the template
in the same directory.  An excerpt from this file is shown below:

.bS
  /* Custom keyboard */
  #ifdef INCLUDE_CUSTOM_KEYBOARD
  #define INCLUDE_UGL_INPUT
  #define SYS_KEYBOARD_NAME     "/keyboard/0"
  
  /* Name of the function to create the keyboard device */
  extern STATUS                      ambaKbdDevCreate(char *name);
  #define SYS_KEYBOARD_CREATE        ambaKbdDevCreate
  
  /* Name of the function to initialize the keyboard device */
  
  extern UGL_INPUT_DEVICE_ID uglAmbaKbdInit (char * name,
                                     UGL_EVENT_SERVICE_ID eventServiceId);
  #define UGL_KEYBOARD_INIT	   uglPcKbdInit
  #endif /* INCLUDE_CUSTOM_KEYBOARD */
  
  /* Custom pointer */
  #ifdef INCLUDE_CUSTOM_POINTER
  #ifndef INCLUDE_UGL_INPUT
  #define INCLUDE_UGL_INPUT
  #endif /* INCLUDE_UGL_INPUT */
  
  #define SYS_POINTER_NAME     "/ambaPtr/0"
  
  /* Name of the function to create the pointer device */
  extern STATUS                      ambaPs2DevCreate(char *name);
  #define SYS_POINTER_CREATE	   ambaPs2DevCreate
  
  /* Name of the function to initialize the pointer device */
  
  extern UGL_INPUT_DEVICE_ID uglPs2PtrInit (char * name,
                                     UGL_EVENT_SERVICE_ID eventServiceId);
  #define UGL_POINTER_INIT	   uglPs2PtrInit
  #endif /* INCLUDE_CUSTOM_POINTER */

.bE

Also, make sure, IGS is compiled into the ARM libraries.
The 'igs' directory may need to be added to the Makefile
'target/src/ugl/driver/graphics/Makefile' as follows:

.bS
  ifeq ($(CPU), ARMARCH4)
      CPU_SUBDIRS = arm igs
  endif
  ifeq ($(CPU), ARMARCH5)
      CPU_SUBDIRS = arm igs
  endif
.bE

The macro USE_BSP_API must be defined.  This can be done by inserting
'CPU==ARMARCH4' in the file target/h/ugl/driver/graphics/igs/udigs.h as
follows:


.bS
  #if ((CPU == MIPS32) || (CPU == MIPS64) || (CPU == ARMARCH4) \
    || (CPU == ARMARCH5))
  #define USE_BSP_API
  #endif
.bE

.SH "HARDWARE DETAILS"

.SS "Devices"
The device drivers included are:

    primeCellSio.c - PrimeCell UART driver.

If Flash support is configured then the following drivers are included:

   nvRamToFlash.c - NVRAM-to-Flash memory library

.SS "Shared memory"
This BSP has not been tested with shared memory, and there is no
BSP-specific support for test-and-set primitives.  The vxTas()
primitive is provided in the architecture-specific code to allow access
to the ARM SWPB instruction.  For further information, see the vxTas()
reference entry.

.SS "Interrupts"

22 interrupt levels are provided:
    0 Soft interrupt
    1 UART 0
    2 UART 1
    3 Keyboard
    4 Mouse
    5 Timer 0
    6 Timer 1
    7 Timer 2
    8 Real time clock
    9 Logic module 0
   10 Logic module 1
   11 Logic module 2
   12 Logic module 3
   13 PCI bus (INTA#)
   14 PCI bus (INTB#)
   15 PCI bus (INTC#)
   16 PCI bus (INTD#)
   17 V3 PCI bridge
   18 CompactPCI auxiliary interrupt (DEG#)
   19 CompactPCI auxiliary interrupt (ENUM#)
   20 PCI local bus fault
   21 External AutoPC

Only interrupt levels 1, 2, 5, 6, 13, 14, 15 and 16 are used by default
in this BSP.  Interrupt connection, enabling and disabling are
performed using the standard intArchLib routines.  The interrupt
controller driver is provided in ambaIntrCtl.c.

.SS "Serial Configuration"

There are two serial ports on the board, provided by two PrimeCell UARTs.
The default configuration is 9600 baud, 8 data bits, no parity, 1 stop
bit.

The driver code in primecellSio.c/.h is a modified version of the
standard VxWorks ambaSio driver.  Documentation for the PrimeCell UART
is on the ARM web site.

The two main differences are as follows:

The PrimeCell SIO has five separate interrupt signal lines.  Four of
these correspond to different types of interrupt; the fifth is a
combined signal, which is used on the Integrator to provide a single
interrupt source for each UART.

There are two separate interrupt signals for received data: one is
generated when the received buffer is more than half full; the other
when no data is received for 32 UART clocks.

.SS "SCSI Configuration"
This BSP does not support SCSI.

.SS "Network Configuration"
This BSP provides network support for PCI Dec 21x4x network cards.

.SS "VME Access"
The board is a standalone board: VME is not supported.

.SS "PCI Access"
This BSP supports the PCI bus and has been tested with network
expansion cards.  PCI to PCI bridge functionality is not implemented.

.SS "Boot Devices"
The default boot image provided with this BSP does not provide a
mechanism for loading a VxWorks kernel.


.SH "SPECIAL CONSIDERATIONS"
.SS "CPU Speed/Timers"

All clocks are derived from various VCOs and dividers, which can be
modified under software control.  Clock values are read throuh the 
coprocessor are set according to the header fitted (cf. romInit.s).

.SS "Special routines"
The routine sysLedsReadWrite() is used to control the LEDs on the
board.  Use of the LEDs is mutually exclusive with use of the parallel
port due to a restriction in the hardware.  For further information,
see the reference entry for this routine.

.SS "Divide by Zero Exception"
The ARM architecture does not provide for an integer divide by zero
exception.  Consequently, no exception is generated when an integer
divide by zero operation is performed programmatically.

.SS "Multiple core module support"
Support is provided for only one core module.

.SH "BOARD LAYOUT"
The diagrams below show the relevant jumpers for VxWorks
configuration.
.bS

______________________________________________________________________________
|               +---+ +---+ +---+ +---+    J15                               |
|         LOGIC | U | | U | | U | | U |    +-+                             +-+
|          +-+  |11 | |12 | |13 | |14 |    | |                          J21| |
|+-------+ | |  +---+ +---+ +---+ +---+    | |                             | |
|| J12   + | |  +---+ +---+ +---+ +---+    | |                             +-+
|+-------+ | |  | U | | U | | U | | U |    | |                       S3   S2 |
|          +-+  |15 | |16 | |17 | |18 |    | |                               |
|               +---+ +---+ +---+ +---+    | |                               |
|               +-----+                    | |                               |
|           U34 |SRAM |   ----EXPM----     +-+                               |
|               +-----+             +---+                                    |
|--+            +-----+             |U19|                                    |
|  |ALPHA   U35 |SRAM |             +---+                                    |
|  |DISPLAY     +-----+           +-----+                                    |
|--+                              | V3  |                                    |
|                                 +-----+                                    |
|    +----------------------------+       +-+ +-+ +-+                        |
|    |                            |       | | | | | |                       +--+
|    |                            |       |P| |P| |P|                       |C |
|    |               +-------+    |       |C| |C| |C|                       |O |
|    |               |  FPGA |    |       |I| |I| |I|                       |M |
+-+  | +------+      |       |    |       | | | | | |                       |P |
|A|  | |  CPU |      +-------+    |       |S| |S| |S|                       |A |
|T|  | |      |                   |       |L| |L| |L|                       |C |
|X|  | +----- +                   |       |O| |O| |O|                       |T |
+-+  |                            |       |T| |T| |T|            +--------+ |  |
|    +----------------------------+       | | | | | |            | PCI/PCI| |P |
|KBD                                      +-+ +-+ +-+            | Bridge | |C |
+--+      SERIAL SERIAL                   J9  J10 J11            +--------+ |I |
|  |  S1  +----+ +----+                                                     +--+
|__|______|    |_|    |_____________________    ______________________________|
.bE
    Key:
    S1    4 pole DIL switch
    S2    Reset button
    S3    Standby button

    U11.. Flash memory
    U19   Boot ROM
    J15   Logic module connector (EXPA) 
    EXPM  External bus interface connector
    V3    System bus - PCI bridge

.SH SEE ALSO
.tG "Getting Started,"
.pG "Configuration."

.SH BIBLIOGRAPHY
.I "ARM Integrator/AP User Guide",
.I "ARM Integrator/CM7TDMI User Guide",
.I "ARM Integrator/CM720T User Guide",
.I "ARM Integrator/CM740T User Guide",
.I "ARM Integrator/CM920T User Guide",
.I "ARM Integrator/CM940T User Guide",
.I "ARM Integrator/CM9x6ES Datasheet",
.I "ARM Architecture Reference Manual",
.I "ARM 7TDMI Data Sheet",
.I "ARM 720T Data Sheet",
.I "ARM 740T Data Sheet",
.I "ARM 920T Technical Reference Manual",
.I "ARM 940T Technical Reference Manual",
.I "ARM 966ES Technical Reference Manual",
.I "ARM Reference Peripherals Specification".
