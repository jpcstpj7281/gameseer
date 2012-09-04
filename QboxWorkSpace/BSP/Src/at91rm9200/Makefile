# Makefile - make rules for target/config/integrator920t
#
# Copyright 1999-2001 Wind River Systems, Inc.
# Copyright 1999-2001 ARM Limited
#
# modification history
# --------------------
# 01h,23may02,m_h  Reduce ROM_SIZE for boards with 32 meg RAM (77901)
# 01g,20mar02,rec  Increase ROM size, SPR 74146
# 01f,14nov01,dat  RELEASE update
# 01e,30oct01,tpw  Standardize kernel links and bootrom conversions.
# 01d,25sep01,dat  Update for T2.2
# 01c,11jul01,rec  fix passed arguments to objcopy
# 01b,15dec00,rec  change RAM_HIGH_ADRS
# 01a,16nov00,jmb  created from 01c of integrator720t.
#
# DESCRIPTION
# This file contains rules for building VxWorks for the ARM INTEGRATOR AP
# fitted with an ARM920T core module.
#
# INCLUDES
#     makeTarget
#*/

CPU		= ARMARCH4
TOOL		= gnu
EXTRA_DEFINE	= -Wcomment -DCPU_920T \
		  -DARMMMU=ARMMMU_920T -DARMCACHE=ARMCACHE_920T \
			-I./ \
			-I./src/drv \
			-I./h \
			-IC:/Tornado2.2/target/h \
			-IC:/Tornado2.2/target/config/comps/src \
			-IC:/Tornado2.2/target/src/drv \
			-I./../driver\driver \
			-I./../driver/boot \
			-I./../driver/led \
			-I./../driver/gpio \
			-I./../driver/include \
			-I./../../../include

TGT_DIR = $(WIND_BASE)/target
MACH_EXTRA=bootled.o bootsoft.o BootIIc.o
BOOT_EXTRA=bootMtest.o
include $(TGT_DIR)/h/make/defs.bsp
#include $(TGT_DIR)/h/make/make.$(CPU)$(TOOL)
#include $(TGT_DIR)/h/make/defs.$(WIND_HOST_TYPE)

## Only redefine make definitions below this point, or your definitions will
## be overwritten by the makefile stubs above.

TARGET_DIR	= at91rm9200
VENDOR		= ARM Limited
BOARD		= at91rm9200dk

RELEASE		+= bootrom.bin
CONFIG_ALL= ./all
#
# The constants ROM_TEXT_ADRS, ROM_SIZE, and RAM_HIGH_ADRS are defined
# in config.h and Makefile.
# All definitions for these constants must be identical.
#

ROM_TEXT_ADRS	= 10000000 # ROM entry address
ROM_SIZE	= 00100000 # number of bytes of ROM space

RAM_LOW_ADRS	= 20001000 # RAM text/data address
RAM_HIGH_ADRS	= 21000000  # RAM text/data address

VMA_START	= 0x$(ROM_TEXT_ADRS)


 
# Binary version of VxWorks ROM images, suitable for programming
# into Flash using tools provided by ARM.  If other ROM images need to
# be put into Flash, add similar rules here.

bootrom.bin: bootrom
	- @ $(RM) $@
	$(EXTRACT_BIN) -O binary bootrom $@

bootrom_res.bin: bootrom_res
	- @ $(RM) $@
	$(EXTRACT_BIN) -O binary bootrom_res $@

bootrom_uncmp.bin: bootrom_uncmp
	- @ $(RM) $@
	$(EXTRACT_BIN) -O binary bootrom_uncmp $@

vxWorks_rom.bin: vxWorks_rom
	- @ $(RM) $@
	$(EXTRACT_BIN) -O binary vxWorks_rom $@

vxWorks.st_rom.bin: vxWorks.st_rom
	- @ $(RM) $@
	$(EXTRACT_BIN) -O binary vxWorks.st_rom $@

vxWorks.res_rom.bin: vxWorks.res_rom
	- @ $(RM) $@
	$(EXTRACT_BIN) -O binary vxWorks.res_rom $@

vxWorks.res_rom_nosym.bin: vxWorks.res_rom_nosym
	- @ $(RM) $@
	$(EXTRACT_BIN) -O binary vxWorks.res_rom_nosym $@

## Only redefine make definitions above this point, or the expansion of
## makefile target dependencies may be incorrect.

include $(TGT_DIR)/h/make/rules.bsp
#include $(TGT_DIR)/h/make/rules.$(WIND_HOST_TYPE)
