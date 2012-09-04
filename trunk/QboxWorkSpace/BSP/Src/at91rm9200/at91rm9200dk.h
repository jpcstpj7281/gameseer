/*
 * linux/include/asm-arm/arch-at91rm9200/at91rm9200dk.h
 *
 *  Copyright (c) 2003 SAN People
 *  Copyright (c) 2003 ATMEL
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 */

#ifndef __AT91RM9200DK_H
#define __AT91RM9200DK_H


#define MASTER_CLOCK		60000000

/* AT91RM92000 clocks */
#define AT91C_MAIN_CLOCK	179712000	/* from 18.432 MHz crystal (18432000 / 4 * 39) */
#define AT91C_MASTER_CLOCK	59904000	/* peripheral clock (AT91C_MAIN_CLOCK / 3) */
#define AT91C_SLOW_CLOCK	32768		/* slow clock */
#define AT91_PLLB_INIT		0x1048be0e      /* (18.432 / 14 * 73) /2 = 47.9714  */


#define CPLL_FREQ                       180                 /* 166 Mhz */



#ifndef CONFIG_SKIP_LOWLEVEL_INIT
#define CFG_USE_MAIN_OSCILLATOR		1
/* flash */
#define MC_PUIA_VAL	0x00000000
#define MC_PUP_VAL	0x00000000
#define MC_PUER_VAL	0x00000000
#define MC_ASR_VAL	0x00000000
#define MC_AASR_VAL	0x00000000
#define EBI_CFGR_VAL	0x00000000
#define SMC0_CSR_VAL	0x00003284 /* 16bit, 2 TDF, 4 WS */
#define SMC2_CSR_VAL	0xff0032ff /* 16bit, 2 TDF, 4 WS */

/* clocks */
#define PLLAR_VAL	0x20263E04 /* 179.712000 MHz for PCK */
#define PLLBR_VAL	0x10483E0E /* 48.054857 MHz (divider by 2 for USB) */
#define MCKR_VAL	0x00000202 /* PCK/3 = MCK Master Clock = 59.904000MHz from PLLA */

/* sdram */
#define PIOC_ASR_VAL	0xFFFF0000 /* Configure PIOC as peripheral (D16/D31) */
#define PIOC_BSR_VAL	0x00000000
#define PIOC_PDR_VAL	0xFFFF0000
#define EBI_CSA_VAL	0x0000000a /* CS1=SDRAM */
#define SDRC_CR_VAL	0x2188c159 /* set up the SDRAM */
#define SDRAM		0x20000000 /* address of the SDRAM */
#define SDRAM1		0x20000080 /* address of the SDRAM */
#define SDRAM_VAL	0x00000000 /* value written to SDRAM */
#define SDRC_MR_VAL	0x00000002 /* Precharge All */
#define SDRC_MR_VAL1	0x00000004 /* refresh */
#define SDRC_MR_VAL2	0x00000003 /* Load Mode Register */
#define SDRC_MR_VAL3	0x00000000 /* Normal Mode */
#define SDRC_TR_VAL	0x000002E0 /* Write refresh rate */
#endif	/* CONFIG_SKIP_LOWLEVEL_INIT */




/* Clock rates */

#define SYS_CLK_RATE_MIN                1                   /* minimum system clock rate */
#define SYS_CLK_RATE_MAX                1000000             /* maximum system clock rate */
#define AUX_CLK_RATE_MIN                1                   /* minimum auxiliary clock rate */
#define AUX_CLK_RATE_MAX                1000000             /* maximum auxiliary clock rate */

#define SYS_TIMER_CLK	(AT91C_MAIN_CLOCK/16)
#define AUX_TIMER_CLK	SYS_TIMER_CLK

/* FLASH */
#define AT91_FLASH_BASE		0x10000000	/* NCS0: Flash physical base address*/

/* SDRAM */
#define AT91_SDRAM_BASE		0x20000000	/* NCS1: SDRAM physical base address*/

/* SmartMedia */
#define AT91_SMARTMEDIA_BASE	0x40000000	/* NCS3: Smartmedia physical base address*/

/* Multi-Master Memory controller */
#define AT91_UHP_BASE		0x00300000	/* USB Host controller*/
#define INT_LVL_MOUSE		INT_LVL_SPI	
#define INT_LVL_KEYBOARD	INT_LVL_IRQ0
#define INT_VEC_MOUSE		INT_VEC_SPI
#define INT_VEC_KEYBOARD	INT_VEC_IRQ0

/* Peripheral interrupt configuration */
#define AT91_SMR_FIQ	(AT91C_AIC_PRIOR_HIGHEST | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Advanced Interrupt Controller (FIQ)*/
#define AT91_SMR_SYS	(AT91C_AIC_PRIOR_HIGHEST | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* System Peripheral*/
#define AT91_SMR_PIOA	(AT91C_AIC_PRIOR_LOWEST	 | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Parallel IO Controller A*/
#define AT91_SMR_PIOB	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Parallel IO Controller B*/
#define AT91_SMR_PIOC	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Parallel IO Controller C*/
#define AT91_SMR_PIOD	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Parallel IO Controller D*/
#define AT91_SMR_US0	(AT91C_AIC_PRIOR_6       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* USART 0*/
#define AT91_SMR_US1	(AT91C_AIC_PRIOR_6       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* USART 1*/
#define AT91_SMR_US2	(AT91C_AIC_PRIOR_6       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* USART 2*/
#define AT91_SMR_US3	(AT91C_AIC_PRIOR_6       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* USART 3*/
#define AT91_SMR_MCI	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Multimedia Card Interface*/
#define AT91_SMR_UDP	(AT91C_AIC_PRIOR_4       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* USB Device Port*/
#define AT91_SMR_TWI	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Two-Wire Interface*/
#define AT91_SMR_SPI	(AT91C_AIC_PRIOR_6       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Serial Peripheral Interface*/
#define AT91_SMR_SSC0	(AT91C_AIC_PRIOR_5       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Serial Synchronous Controller 0*/
#define AT91_SMR_SSC1	(AT91C_AIC_PRIOR_5       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Serial Synchronous Controller 1*/
#define AT91_SMR_SSC2	(AT91C_AIC_PRIOR_5       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Serial Synchronous Controller 2*/
#define AT91_SMR_TC0	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Timer Counter 0*/
#define AT91_SMR_TC1	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Timer Counter 1*/
#define AT91_SMR_TC2	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Timer Counter 2*/
#define AT91_SMR_TC3	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Timer Counter 3*/
#define AT91_SMR_TC4	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Timer Counter 4*/
#define AT91_SMR_TC5	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Timer Counter 5*/
#define AT91_SMR_UHP	(AT91C_AIC_PRIOR_3       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* USB Host port*/
#define AT91_SMR_EMAC	(AT91C_AIC_PRIOR_3       | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Ethernet MAC*/
#define AT91_SMR_IRQ0	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Advanced Interrupt Controller (IRQ0)*/
#define AT91_SMR_IRQ1	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Advanced Interrupt Controller (IRQ1)*/
#define AT91_SMR_IRQ2	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Advanced Interrupt Controller (IRQ2)*/
#define AT91_SMR_IRQ3	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Advanced Interrupt Controller (IRQ3)*/
#define AT91_SMR_IRQ4	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Advanced Interrupt Controller (IRQ4)*/
#define AT91_SMR_IRQ5	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Advanced Interrupt Controller (IRQ5)*/
#define AT91_SMR_IRQ6	(AT91C_AIC_PRIOR_LOWEST  | AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE)	/* Advanced Interrupt Controller (IRQ6)*/

#define AT91C_CONSOLE_DEFAULT_BAUDRATE 115200	/* default serial console baud-rate */

/*
 * Serial port configuration.
 *    0 .. 3 = USART0 .. USART3
 *    4      = DBGU
 */
#define AT91C_UART_MAP		{ 4, 1, -1, -1, -1 }	/* ttyS0, ..., ttyS4 */
#define AT91C_CONSOLE		0			/* ttyS0 */






/* System BUS Type */

#define BUS                             BUS_TYPE_NONE

/* Console definitions */

#define N_SIO_CHANNELS                  2                   /* No. serial I/O channels */

#undef  CONSOLE_TTY
#define CONSOLE_TTY                     0                   /* 0:CUART, 1: HUART0, 2:HUART1 */

/* FLASH definitions */


#if 0
/* LCD definitions */

#define INCLUDE_LCD                                         /* Include LCD support */

#define LCD_BASE_ADRS                   0x82000000          /* SRAM Base Address */
#define LCD_SIZE                        0x00100000          /* SRAM Size, 1M Bytes */


/* LED definitions */

#define INCLUDE_LED                                         /* Include LED support */

#define IOPMOD_LED                      S3C2510_IOPMOD1     /* 0:OUT, 1:IN */
#define IOPDATA_LED                     S3C2510_IOPDATA1    /* 0:ON,  1:OFF */

#define LED8_MASK                       0x00000080          /* LED 8 */
#define LED7_MASK                       0x00000040          /* LED 7 */
#define LED6_MASK                       0x00000020          /* LED 6 */
#define LED5_MASK                       0x00000010          /* LED 5 */
#define LED4_MASK                       0x00000008          /* LED 4 */
#define LED3_MASK                       0x00000004          /* LED 3 */
#define LED2_MASK                       0x00000002          /* LED 2 */
#define LED1_MASK                       0x00000001          /* LED 1 */

#define LED_ALL_MASK                    0x000000FF

#define LED_ON(_mask)                   (*IOPDATA_LED &= ~(_mask))
#define LED_OFF(_mask)                  (*IOPDATA_LED |=  (_mask))
#endif

/* Memory Map for Buffer Descriptor and Buffer */

#define ETH_MAX_UNITS                   1

#if     (USER_RESERVED_MEM > 0)
#define USER_BASE_ADRS                  (LOCAL_MEM_LOCAL_ADRS + LOCAL_MEM_SIZE - USER_RESERVED_MEM)
#define USER_SIZE                       (USER_RESERVED_MEM)
#else   /* (USER_RESERVED_MEM > 0) */


#endif  /* (USER_RESERVED_MEM > 0) */



/* Loopback Modes */

#define LOOP_NONE                       0                                       /* Normal */
#define LOOP_L2                         1                                       /* Layer 2 Loopback */
#define LOOP_TDM                        2                                       /* TDM Loopback (in SAR Mode) */
#define LOOP_L1                         3                                       /* Layer 1 Loopback */
#define LOOP_ECHO_L1                    4                                       /* Layer 1 Echo */
#define LOOP_ECHO_TDM                   5                                       /* TDM Echo (in SAR Mode) */
#define LOOP_ECHO_L2                    6                                       /* Layer 2 Echo */


#include "at91rm9200.h"

#ifdef __EK__
#define S1D13806_BASE       ( (unsigned char *) 0x40000000 )
#else
#define S1D13806_BASE		( (unsigned char *) 0x30000000 )
#endif

#define PCMCIA_SOCKS AT91_PCMCIA_MAX_SOCK
#define PCMCIA_MEMBASE AT91_PCMCIA_BASE(0)


#define PCIC_BASE_ADR AT91_PCMCIA_BASE(0)
#define PCIC_INT_VEC  INUM_TO_IVEC(PCIC_INT_LVL)
#define PCIC_INT_LVL  AT91C_ID_PIOB


#define CIS_RANGE_SIZE 0x400
#define CIS_MEM_START 0 /*AT91_PCMCIA_AT_BASE(0)*/
#define CIS_REG_START 0x400000  /*AT91_PCMCIA_CM_BASE(0)*/
#define CIS_MEM_STOP  CIS_MEM_START+(AT91_PCMCIA_REG-1)
#define CIS_REG_STOP  CIS_REG_START+(AT91_PCMCIA_REG-1)


#ifndef __ASSEMBLER__

static __inline__ void AT91_CfgPIO_USART0(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA17_TXD0 | AT91C_PA18_RXD0
		| AT91C_PA20_CTS0;

	/*
	 * Errata #39 - RTS0 is not internally connected to PA21.  We need to drive
	 *  the pin manually.  Default is off (RTS is active low).
	 */
	AT91_SYS->PIOA_PER = AT91C_PA21_RTS0;
	AT91_SYS->PIOA_OER = AT91C_PA21_RTS0;
	AT91_SYS->PIOA_SODR = AT91C_PA21_RTS0;
}

static __inline__ void AT91_CfgPIO_USART1(void) {
	AT91_SYS->PIOB_PDR = AT91C_PB18_RI1 | AT91C_PB19_DTR1
		| AT91C_PB20_TXD1 | AT91C_PB21_RXD1 | AT91C_PB23_DCD1
		| AT91C_PB24_CTS1 | AT91C_PB25_DSR1 | AT91C_PB26_RTS1;
}

static __inline__ void AT91_CfgPIO_USART2(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA22_RXD2 | AT91C_PA23_TXD2;
}

static __inline__ void AT91_CfgPIO_USART3(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA5_TXD3 | AT91C_PA6_RXD3;
	AT91_SYS->PIOA_BSR = AT91C_PA5_TXD3 | AT91C_PA6_RXD3;
}

static __inline__ void AT91_CfgPIO_DBGU(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA31_DTXD | AT91C_PA30_DRXD;
}

/*
 * Configure Ethernet for RMII mode.
 */
static __inline__ void AT91_CfgPIO_EMAC_RMII(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA16_EMDIO | AT91C_PA15_EMDC | AT91C_PA14_ERXER | AT91C_PA13_ERX1
		| AT91C_PA12_ERX0 | AT91C_PA11_ECRS_ECRSDV | AT91C_PA10_ETX1
		| AT91C_PA9_ETX0 | AT91C_PA8_ETXEN | AT91C_PA7_ETXCK_EREFCK;
	AT91_SYS->PIOB_PDR = AT91C_PB19_ERXCK;
	AT91_SYS->PIOB_BSR = AT91C_PB19_ERXCK;
}

/*
 * Configure Ethernet for MII mode.
 */
static __inline__ void AT91_CfgPIO_EMAC_MII(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA16_EMDIO | AT91C_PA15_EMDC | AT91C_PA14_ERXER | AT91C_PA13_ERX1
		| AT91C_PA12_ERX0 | AT91C_PA11_ECRS_ECRSDV | AT91C_PA10_ETX1
		| AT91C_PA9_ETX0 | AT91C_PA8_ETXEN | AT91C_PA7_ETXCK_EREFCK;
	AT91_SYS->PIOB_PDR = AT91C_PB19_ERXCK | AT91C_PB18_ECOL | AT91C_PB17_ERXDV
		| AT91C_PB16_ERX3 | AT91C_PB15_ERX2 | AT91C_PB14_ETXER | AT91C_PB13_ETX3
		| AT91C_PB12_ETX2;
	AT91_SYS->PIOB_BSR = AT91C_PB19_ERXCK | AT91C_PB18_ECOL | AT91C_PB17_ERXDV
		| AT91C_PB16_ERX3 | AT91C_PB15_ERX2 | AT91C_PB14_ETXER | AT91C_PB13_ETX3
		| AT91C_PB12_ETX2;
}

/*
 * Configure interrupt from Ethernet PHY.
 */
static __inline__ void AT91_CfgPIO_EMAC_PHY(void) {
	AT91_SYS->PMC_PCER = 1 << AT91C_ID_PIOC;	/* enable peripheral clock */
#ifdef CONFIG_MACH_CSB337
	AT91_SYS->PIOC_ODR = AT91C_PIO_PC2;
#else
	AT91_SYS->PIOC_ODR = AT91C_PIO_PC4;
#endif
}

/*
 * Enable the Two-Wire interface.
 */
static __inline__ void AT91_CfgPIO_TWI(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA25_TWD | AT91C_PA26_TWCK;
	AT91_SYS->PIOA_ASR = AT91C_PA25_TWD | AT91C_PA26_TWCK;
	AT91_SYS->PIOA_MDER = AT91C_PA25_TWD | AT91C_PA26_TWCK;		/* open drain */
}

/*
 * Enable the Serial Peripheral Interface.
 */
static __inline__ void AT91_CfgPIO_SPI(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA0_MISO | AT91C_PA1_MOSI | AT91C_PA2_SPCK;
}

static __inline__ void AT91_CfgPIO_SPI_CS0(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA3_NPCS0;
}

static __inline__ void AT91_CfgPIO_SPI_CS1(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA4_NPCS1;
}

static __inline__ void AT91_CfgPIO_SPI_CS2(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA5_NPCS2;
}

static __inline__ void AT91_CfgPIO_SPI_CS3(void) {
	AT91_SYS->PIOA_PDR = AT91C_PA6_NPCS3;
}

/*
 * Select the DataFlash card.
 */
static __inline__ void AT91_CfgPIO_DataFlashCard(void) {
	AT91_SYS->PIOB_PER = AT91C_PIO_PB7;
	AT91_SYS->PIOB_OER = AT91C_PIO_PB7;
	AT91_SYS->PIOB_CODR = AT91C_PIO_PB7;
}

/*
 * Enable NAND Flash (SmartMedia) interface.
 */
static __inline__ void AT91_CfgPIO_SmartMedia(void) {
	/* enable PC0=SMCE, PC1=SMOE, PC3=SMWE, A21=CLE, A22=ALE */
	AT91_SYS->PIOC_ASR = AT91C_PC0_BFCK | AT91C_PC1_BFRDY_SMOE | AT91C_PC3_BFBAA_SMWE;
	AT91_SYS->PIOC_PDR = AT91C_PC0_BFCK | AT91C_PC1_BFRDY_SMOE | AT91C_PC3_BFBAA_SMWE;

	/* Configure PC2 as input (signal READY of the SmartMedia) */
	AT91_SYS->PIOC_PER = AT91C_PC2_BFAVD;	/* enable direct output enable */
	AT91_SYS->PIOC_ODR = AT91C_PC2_BFAVD;	/* disable output */

	/* Configure PB1 as input (signal Card Detect of the SmartMedia) */
	AT91_SYS->PIOB_PER = AT91C_PIO_PB1;	/* enable direct output enable */
	AT91_SYS->PIOB_ODR = AT91C_PIO_PB1;	/* disable output */
}

static __inline__ int AT91_PIO_SmartMedia_RDY(void) {
	return (AT91_SYS->PIOC_PDSR & AT91C_PIO_PC2) ? 1 : 0;
}

static __inline__ int AT91_PIO_SmartMedia_CardDetect(void) {
	return (AT91_SYS->PIOB_PDSR & AT91C_PIO_PB1) ? 1 : 0;
}


#endif


#include "port.h"
#endif


