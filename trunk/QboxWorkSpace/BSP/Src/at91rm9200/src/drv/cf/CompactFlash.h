//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : CompactFlash.h
//* Object              : main application written in C
//* Creation            : GGi   12/11/2002
//*
//*----------------------------------------------------------------------------

#ifndef COMPACTFLASH_H
#define COMPACTFLASH_H

/*
#include "PRODUCT/AT91RM9200/AT91RM9200.h"
#include "PRODUCT/AT91RM9200/lib_AT91RM9200.h"

#define SANDISK8M

#ifdef FUJI16M
#include "Fuji16M.h"
#endif
#ifdef SANDISK8M
#include "Sandisk8M.h"
#endif
#ifdef HITACHI8M
#include "Hitachi8M.h"
#endif
*/

/*---------------------------  Constants definition -------------------------*/



/*---------------------------  Structure definition -------------------------*/



//Configuration Option Register

#define	CF_COR_MEMMAP	(0)
#define	CF_COR_IO16		(1)
#define	CF_COR_IO_1		(2) 		//I/O mapped 1F0h-1F7h/3F6h-3F7h
#define	CF_COR_IO_2		(3) 		//I/O mapped 170h-177h/376h-377h
#define	CF_COR_LEVIRQ	(1 << 6) 	//IRQ level mode
#define	CF_COR_PULIRQ	(0 << 6) 	//IRQ pulse mode
#define	CF_COR_SRESET	(1 << 7)	//Soft reset
#define	CF_COR_HRESET	(0 << 7)	//Hard reset
//to be defined for CF+


//Card Configuration and Status Register

#define	CF_CCSR_INT		(1 << 1)	//internal state of interrupt request
#define	CF_CCSR_PWRDWN	(1 << 2)	//power down
#define	CF_CCSR_AUDIO	(1 << 3)	//Audio, only for CF+
#define	CF_CCSR_WE		(1 << 4)	//Power Level 1 feature, only for CF+
#define	CF_CCSR_IO8		(1 << 5)	//I/O on 8 bits
#define	CF_CCSR_SIGCHG	(1 << 6)	//State change signal
#define	CF_CCSR_CH		(1 << 7)	//changed

//Pin Replacement Register
#define	CF_PRR_WPROT	(0)			//always zero
#define	CF_PRR_MWPROT	(1)			//acts as a mask for writing CWPROT
#define	CF_PRR_RDY_BSY	(1 << 1)	//Ready/-Busy signal
#define	CF_PRR_MRDY_BSY	(1 << 1)	//acts as a mask for writing CRDY_BSY
#define	CF_PRR_CWPROT	(1 << 4)	//set to one when RWprot state changes
#define	CF_PRR_CRDY_BSY	(1 << 5)	//set to one when RRDY_BSY state changes

//Socket and Copy Register
#define	CF_SCR_DRIVE(x)	(x&1 << 4)	//drive number
#define	CF_SCR_RESERVED	(0 << 7)	//must be 0 when the register is written



#define CF_ATA_DATA_OFFSET		0
#define CF_ATA_ERROR_OFFSET		1

#define CF_ATA_ALT_TRUE_IDE_STATUS_OFFSET	6

#define CF_ATA_STATUS_OFFSET	7
#define CF_ATA_EVEN_DATA_OFFSET	8
#define CF_ATA_ODD_DATA_OFFSET	9

#define CF_ATA_ST_ERR			(1)
#define CF_ATA_ST_CORR			(1 << 2)
#define CF_ATA_ST_DRQ			(1 << 3)
#define CF_ATA_ST_DSC			(1 << 4)
#define CF_ATA_ST_DWF			(1 << 5)
#define CF_ATA_ST_RDY			(1 << 6)
#define CF_ATA_ST_BUSY			(1 << 7)
//to complete with bit values for each reg

/*-------------------  CompactFlash command set  -------------------------*/

#define CHK_POWMOD			0xe5 //or 0x98
#define DRIVE_DIAG			0x90
#define ERASE_SECTOR		0xc0
#define FORMAT_TRACK		0x50
#define DRIVE_ID			0xec
#define CF_IDLE				0xe3 //or 0x97
#define IDLE_IMM			0xe1 //or 0x95
#define INIT_DRIVE_PARAM	0x91
#define READ_BUF			0xe4
#define READ_LONG_SECTOR	0x22 //or 0x23
#define READ_MULT			0xc4
#define READ_SECTOR			0x20 //or 0x21
#define READ_VERIF_SECTOR	0x40 //or 0x41
#define RECALIBRATE			0x10 //in fact 1xh
#define REQ_SENSE			0x03
#define SECU_DIS_PASS		0xf6
#define SECU_ERASE_PREP		0xf3
#define SECU_ERASE_UNIT		0xf4
#define SECU_FREEZE_LOCK	0xf5
#define SECU_SET_PASS		0xf1
#define SECU_UNLOCK			0xf2
#define SEEK				0x70 //in fact 7xh
#define SET_FEATURES		0xef
#define SET_MULT_MODE		0xc6
#define SET_SLEEP_MODE		0xe6 //or 0x99
#define STAND_BY			0xe2 //or 0x96
#define STAND_BY_IMM		0xe0 //or 0x94
#define TRANS_SECTOR		0x87
#define WEAR_LEVEL			0xf5
#define WRITE_BUF			0xe8
#define WRITE_LONG_SECTOR	0x32 //or 0x33
#define WRITE_MULT			0xc5
#define WRITE_MULT_WO_ER	0xcd
#define WRITE_SECTOR		0x30 //or 0x31
#define WRITE_SECTOR_WO_ER	0x38
#define WRITE_VERIFY		0x3c

//memory mapping structures

#define CF_NORMAL_RWH		(2 << 28)
#define CF_NORMAL_RWS		(2 << 24)
#define CF_NORMAL_TDF		(6 << 8)
#define CF_NORMAL_NWS		(16)
#define CF_IO_RWH			(3 << 28)//2
#define CF_IO_RWS			(5 << 24)//4
#define CF_IO_TDF			(0 << 8) //0
#define CF_IO_NWS			(10)//10

#define ATTRIBUTE	0
#define	IO_1		1
#define	IO_2		2
#define	IO_16		3
#define	MEMORY		4
#define	MEMORY16	5
#define	IO_IDE		6
#define	MEM_BY_IO	7
#define	IO_BY_MEM	8
#define	IDE			9
#define	NB_MEM_CFG	10

typedef struct{
	int type;
	int cor;
	int base;
	int smc_cfg;
}AT91S_CF_MemMap;



/*---------------------------  Function Prototyping -------------------------*/
extern volatile char *CompactFlash_BASE;
extern volatile short *CompactFlash_BASE_16;

extern int space_type ;

extern int AT91F_CF_Read(unsigned char *,int);
extern int AT91F_CF_Write(unsigned char *,int);
extern void AT91F_CF_Open(void);
extern int AT91F_CF_READ_ID (unsigned char *);
extern int AT91F_CF_READ_IDE_ID (unsigned short *);
extern void AT91F_CF_READ_CIS (unsigned char *,int);
extern int AT91F_CF_WRITE_SECTOR (unsigned char *, char, char, char, char);
extern int AT91F_CF_READ_SECTOR (unsigned char *, char, char, char, char);
extern int AT91F_CF_WRITE_BUF (unsigned char *, char, char, char, char);
extern int AT91F_CF_READ_BUF (unsigned char *, char, char, char, char);
extern int AT91F_CF_ERASE_SECTOR (char, char, char, char);

extern int AT91F_CF_SetMemType (int);
extern char AT91F_GetStatus (void);

//16 bitwitdh databus functions
extern int AT91F_CF_READ16_ID (unsigned short *);
extern int AT91F_CF_WRITE16_SECTOR (unsigned short *, char, char, char, char);
extern int AT91F_CF_READ16_SECTOR (unsigned short *, char, char, char, char);

extern int AT91F_CF_Read16(unsigned short *,int);
extern int AT91F_CF_Write16(unsigned short *,int);

/* MACROS */
extern void AT91F_CF_WriteReg(int, char);
extern int AT91F_CF_WriteCommand(char *, int , int);
extern int AT91F_CF_Write16Command(short *, int , int);

extern int AT91F_CF_Card_OK (void);

#define OFFSET_SECTORS 7
#define OFFSET_MODEL 27
#define LENGTH_MODEL 20




#endif // COMPACTFLASH_H


