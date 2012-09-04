/* ----------------------------------------------------------------------------*/
/*          ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/* ----------------------------------------------------------------------------*/
/*  The software is delivered "AS IS" without warranty or condition of any*/
/*  kind, either express, implied or statutory. This includes without*/
/*  limitation any warranty or condition with respect to merchantability or*/
/*  fitness for any particular purpose, or against the infringements of*/
/*  intellectual property rights of others.*/
/* ----------------------------------------------------------------------------*/
/* File Name           : AT91RM9200.h*/
/* Object              : AT91RM9200 / SMC2 definitions*/
/* Generated           : AT91 SW Application Group  01/17/2003 (13:41:22)*/
/* */
/* ----------------------------------------------------------------------------*/

#ifndef AT91RM9200_SMC2_H
#define AT91RM9200_SMC2_H

#include "AT91RM9200.h"

/* ******************************************************************************/
/*              SOFTWARE API DEFINITION  FOR Static Memory Controller 2 Interface*/
/* ******************************************************************************/

/*
typedef struct _AT91S_SMC2 {
	AT91_REG	 SMC2_CSR[8]; 	// SMC2 Chip Select Register
} AT91S_SMC2, *AT91PS_SMC2;
*/

/* -------- SMC2_CSR : (SMC2 Offset: 0x0) SMC2 Chip Select Register -------- */
#define AT91C_SMC2_NWS        ((unsigned int) 0x7F <<  0) /* (SMC2) Number of Wait States*/
#define AT91C_SMC2_WSEN       ((unsigned int) 0x1 <<  7) /* (SMC2) Wait State Enable*/
#define AT91C_SMC2_TDF        ((unsigned int) 0xF <<  8) /* (SMC2) Data Float Time*/
#define AT91C_SMC2_BAT        ((unsigned int) 0x1 << 12) /* (SMC2) Byte Access Type*/
#define AT91C_SMC2_DBW        ((unsigned int) 0x1 << 13) /* (SMC2) Data Bus Width*/
#define 	AT91C_SMC2_DBW_16                   ((unsigned int) 0x1 << 13) /* (SMC2) 16-bit.*/
#define 	AT91C_SMC2_DBW_8                    ((unsigned int) 0x2 << 13) /* (SMC2) 8-bit.*/
#define AT91C_SMC2_DRP        ((unsigned int) 0x1 << 15) /* (SMC2) Data Read Protocol*/
#define AT91C_SMC2_ACSS       ((unsigned int) 0x3 << 16) /* (SMC2) Address to Chip Select Setup*/
#define 	AT91C_SMC2_ACSS_STANDARD             ((unsigned int) 0x0 << 16) /* (SMC2) Standard, asserted at the beginning of the access and deasserted at the end.*/
#define 	AT91C_SMC2_ACSS_1_CYCLE              ((unsigned int) 0x1 << 16) /* (SMC2) One cycle less at the beginning and the end of the access.*/
#define 	AT91C_SMC2_ACSS_2_CYCLES             ((unsigned int) 0x2 << 16) /* (SMC2) Two cycles less at the beginning and the end of the access.*/
#define 	AT91C_SMC2_ACSS_3_CYCLES             ((unsigned int) 0x3 << 16) /* (SMC2) Three cycles less at the beginning and the end of the access.*/
#define AT91C_SMC2_RWSETUP    ((unsigned int) 0x7 << 24) /* (SMC2) Read and Write Signal Setup Time*/
#define AT91C_SMC2_RWHOLD     ((unsigned int) 0x7 << 29) /* (SMC2) Read and Write Signal Hold Time*/
/* ******************************************************************************/
/*               REGISTER ADDRESS DEFINITION FOR AT91RM9200 / SMC2*/
/* ******************************************************************************/
/* ========== Register definition for SMC2 peripheral ========== */
/*#define AT91C_SMC2_CSR  ((AT91_REG *) 	0xFFFFFF70) // (SMC2) SMC2 Chip Select Register*/

/* ******************************************************************************/
/*               PIO DEFINITIONS FOR AT91RM9200 / SMC2*/
/* ******************************************************************************/
#define AT91C_PC9_A25_CFRNW ((unsigned int) 1 <<  9) /*  Address Bus[25] /  Compact Flash Read Not Write*/
#define AT91C_PC6_NWAIT     ((unsigned int) 1 << 6) /*  Compact Flash Chip Select*/
#define AT91C_PC10_NCS4_CFCS ((unsigned int) 1 << 10) /*  Compact Flash Chip Select*/
#define AT91C_PC11_NCS5_CFCE1 ((unsigned int) 1 << 11) /*  Chip Select 5 / Compact Flash Chip Enable 1*/
#define AT91C_PC12_NCS6_CFCE2 ((unsigned int) 1 << 12) /*  Chip Select 6 / Compact Flash Chip Enable 2*/

/* ******************************************************************************/
/*               BASE ADDRESS DEFINITIONS FOR AT91RM9200 / SMC2*/
/* ******************************************************************************/
/*#define AT91C_BASE_SMC2      ((AT91PS_SMC2) 	0xFFFFFF70) // (SMC2) Base Address*/

#endif
