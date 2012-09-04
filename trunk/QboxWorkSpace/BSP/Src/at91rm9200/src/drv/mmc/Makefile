#
# Makefile for the kernel mmc device drivers.
#

O_TARGET := mmc.o

export-objs := mmc_common.o at91rm9200_mmc.o
#export-objs := mmc_base.o

obj-$(CONFIG_BLK_MMC) += mmc_base.o

# Declare multi-part drivers.
list-multi := mmc_base.o
mmc_base-objs := mmc_common.o

ifeq ($(CONFIG_ARCH_AT91RM9200),y)
  mmc_base-objs += at91rm9200_mmc.o
endif
ifeq ($(CONFIG_IA_CPU_9200_MMC),y)
  mmc_base-objs += ia_cpu_9200_mmc.o
else
  mmc_base-objs += at91rm9200_board_generic_mmc.o
endif

include $(TOPDIR)/Rules.make

# Link rules for multi-part drivers.

mmc_base.o: $(mmc_base-objs)
	$(LD) -r -o $@ $(mmc_base-objs)


