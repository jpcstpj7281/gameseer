# Makefile generated by the project manager
#


## core information

PRJ_FILE       = application.wpj
ifeq ($(wildcard Makefile),)
PRJ_DIR        = ..
else
PRJ_DIR        = .
endif
PRJ_TYPE       = vxApp
PRJ_OBJS       = app_demo.o
BUILD_SPEC     = ARMARCH4gnu
TGT_DIR        = $(WIND_BASE)/target




## build-configuration info

ifeq ($(BUILD_SPEC),ARMARCH4gnu)
CPU              = ARMARCH4
TOOL             = gnu
TOOL_FAMILY      = gnu
DEFAULT_RULE     = application.pl
endif

include $(TGT_DIR)/h/make/defs.project

## build-configuration info

ifeq ($(BUILD_SPEC),ARMARCH4gnu)
AR               = ararm
AS               = ccarm
CC               = ccarm
CC_ARCH_SPEC     = -mapcs-32 -mlittle-endian -march=armv4
CFLAGS           = -g -mapcs-32 -mlittle-endian -march=armv4 -ansi -fno-builtin -DARMEL -I. -I$(WIND_BASE)/target/h/ -DCPU=ARMARCH4 -DTOOL_FAMILY=gnu -DTOOL=gnu
CFLAGS_AS        = -g -mapcs-32 -mlittle-endian -march=armv4 -ansi -fno-builtin -P -xassembler-with-cpp -I. -I$(WIND_BASE)/target/h/ -DCPU=ARMARCH4 -DTOOL_FAMILY=gnu -DTOOL=gnu
CPP              = ccarm -E -P
LD               = ldarm
LDFLAGS          = -X -EL -N
LD_PARTIAL       = ccarm -r -nostdlib -Wl,-X -Wl,-EL
LD_PARTIAL_FLAGS = -X -EL -r
NM               = nmarm -g
OPTION_DEFINE_MACRO = -D
OPTION_DEPEND    = -M -w
OPTION_GENERATE_DEPENDENCY_FILE = -MD
OPTION_INCLUDE_DIR = -I
OPTION_LANG_C    = -xc
OPTION_UNDEFINE_MACRO = -U
POST_BUILD_RULE  = 
PRJ_LIBS         = 
SIZE             = sizearm
TOOL_FAMILY      = gnu
endif

# override make definitions only below this line


# override make definitions only above this line
include $(TGT_DIR)/h/make/rules.project



## build-configuration info

ifeq ($(BUILD_SPEC),ARMARCH4gnu)
app_demo.o:
	$(CC) -g -mapcs-32 -mlittle-endian -march=armv4 -ansi -fno-builtin -DARMEL -I. -I$(WIND_BASE)/target/h/ -DCPU=ARMARCH4 -DTOOL_FAMILY=gnu -DTOOL=gnu -c $(PRJ_DIR)/app_demo.c
endif


## dependencies

app_demo.o: $(PRJ_DIR)/app_demo.c \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/arm-wrs-vxworks/2.9-010413/include/stddef.h \
	$(WIND_BASE)/host/$(WIND_HOST_TYPE)/lib/gcc-lib/arm-wrs-vxworks/2.9-010413/include/stdarg.h


## user defined rules

