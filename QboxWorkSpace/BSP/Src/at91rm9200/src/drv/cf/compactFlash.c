//*----------------------------------------------------------------------------
//*         ATMEL Microcontroller Software Support  -  ROUSSET  -
//*----------------------------------------------------------------------------
//* The software is delivered "AS IS" without warranty or condition of any
//* kind, either express, implied or statutory. This includes without
//* limitation any warranty or condition with respect to merchantability or
//* fitness for any particular purpose, or against the infringements of
//* intellectual property rights of others.
//*----------------------------------------------------------------------------
//* File Name           : CompactFlash.c
//* Object              : main application written in C
//* Creation            : GGi   12/11/2002
//*
//*----------------------------------------------------------------------------
#include "CompactFlash.h"


//WARNING value changed for access trought PCMCIA card
volatile char *CompactFlash_BASE = (volatile char *)(AT91_PCMCIA_CM_BASE(0)+0x400);
volatile char *CompactFlash_CIS_BASE = (volatile char *)(AT91_PCMCIA_AT_BASE(0));
volatile char *CompactFlash_Attribute = (volatile char *)(AT91_PCMCIA_AT_BASE(0)+0x200);
volatile short *CompactFlash_BASE_16 = (volatile short *)(AT91_PCMCIA_CM_BASE(0));
volatile char *CompactFlash_COMMAND_BASE = (volatile char *)(AT91_PCMCIA_CM_BASE(0));


#define BUF_SIZE 512
/*delay fct*/
void delay(int nb){
	while(nb--);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_GetStatus
//* \brief wait the RDY status
//*----------------------------------------------------------------------------
 char AT91F_GetStatus (void){


			return ( *(CompactFlash_COMMAND_BASE + CF_ATA_STATUS_OFFSET));

}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_RDY
//* \brief wait the RDY status
//*----------------------------------------------------------------------------
 int AT91F_CF_RDY (void){

   char status = 1;
   int cpt = 0;
   
    while (status && cpt++ < 100000){
			status = (AT91F_GetStatus()) & CF_ATA_ST_BUSY;
	}
	
	if (cpt == 100000) return -1;
	return 1;
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_ERR
//* \brief wait the ERR status
//*----------------------------------------------------------------------------
 int AT91F_CF_ERR (void){

   char status = 1;
   int cpt = 0;
   
    while (status && cpt++ < 100000){
			status = (AT91F_GetStatus()) & CF_ATA_ST_ERR;
	}
	
	if (cpt == 100000) return -1;
	return 1;
}
int AT91F_CF_Card_OK (void)
{
	int count =1000;
    while ( count>0 && ( ((AT91F_GetStatus()) & CF_ATA_ST_ERR) || !((AT91F_GetStatus()) & CF_ATA_ST_RDY) ) )
	{
		count--;
	}
	if(count>0)    return (1);
	else return 0;
}
//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_DRQ
//* \brief wait the DRQ status
//*----------------------------------------------------------------------------
int AT91F_CF_DRQ (void){

   char status = 0;
   int cpt = 0;
    while (!status && cpt++ < 100000){
			status = (AT91F_GetStatus()) & CF_ATA_ST_DRQ;
	}

	if (cpt == 100000) return -1;
	return 1;

}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_Read
//* \brief Read from CompactFlash
//*----------------------------------------------------------------------------
int AT91F_CF_Read(unsigned char *buffer,int size){
	int cpt = 0;
	if (AT91F_CF_DRQ() < 0) return -1;

	while ((cpt < size) && (cpt < BUF_SIZE)){
		*buffer++ =*(CompactFlash_BASE);
		cpt ++;
	}

	return cpt;
}
//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_Write
//* \brief Write to CompactFlash
//*----------------------------------------------------------------------------
int AT91F_CF_Write(unsigned char *buffer,int size){
	int cpt = 0;
	if (AT91F_CF_DRQ() < 0) return -1;


	while ((cpt < size) && (cpt < BUF_SIZE)){
		*(CompactFlash_BASE ) = *buffer++;
		cpt++;
	}

	return cpt;
}


//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_Read16
//* \brief Read from CompactFlash in 16 bitwidth databus mode
//*----------------------------------------------------------------------------
int AT91F_CF_Read16(unsigned short *buffer,int size){
	int cpt = 0,status = 1;
	if (AT91F_CF_DRQ() < 0) return -1;

	//while ((cpt < size) && (cpt < BUF_SIZE)){
	while (status) {
		*buffer++ =*(CompactFlash_BASE_16);
		delay(100);
		status = (AT91F_GetStatus()) & CF_ATA_ST_DRQ;
	cpt ++;
	}
//	memcpy(buffer,(char*)CompactFlash_BASE_16,size*2);
	return size;
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_Write16
//* \brief Write to CompactFlash
//*----------------------------------------------------------------------------
int AT91F_CF_Write16(unsigned short *buffer,int size){
	int cpt = 0, status = 1;
	if (AT91F_CF_DRQ() < 0) return -1;

	//while ((cpt < size) && (cpt < BUF_SIZE)){
	while (status) {
		*(CompactFlash_BASE_16 ) = *buffer++;
		delay(1000);
		status = (AT91F_GetStatus()) & CF_ATA_ST_DRQ;
		cpt++;
	}

//	memcpy((char*)CompactFlash_BASE_16,buffer,size*2);

	return size;

}


//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_WriteReg
//* \brief Write into CompactFlash configuration registers
//*----------------------------------------------------------------------------
void AT91F_CF_WriteReg(int offset, char data){

 	*(CompactFlash_Attribute + offset) = data;

}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_WriteCommand
//* \brief Write a command to the CompactFlash
//*----------------------------------------------------------------------------
int AT91F_CF_WriteCommand(char * buffer, int size, int offset){
	int i, status = 1, cpt = 0;
	if (AT91F_CF_RDY() < 0) return -1;


	for (i=0;i<size;i++){
		delay(10000);
		*(CompactFlash_COMMAND_BASE + i + offset) = *buffer++;
	}

	return 0;
}


//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_READ_ID
//* \brief Read the CF ID
//*----------------------------------------------------------------------------
 int AT91F_CF_READ_ID (unsigned char * buf){
 	char cmd[6] = {1,0,0,0,0,DRIVE_ID};

    if (AT91F_CF_WriteCommand(cmd,6,2) < 0) return -1;
    if (AT91F_CF_Read(buf,BUF_SIZE) != BUF_SIZE) return -1;
	if (AT91F_CF_ERR() < 0) return -1;

   	return 0;

}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_READ16_ID
//* \brief Read the CF ID in 16 bitwidth databus
//*----------------------------------------------------------------------------
 int AT91F_CF_READ16_ID (unsigned short * buf){
/* 	char cmd[2] = {0,DRIVE_ID};

    if (AT91F_CF_WriteCommand(cmd,2,6) < 0) return -1;
*/ 	char cmd[6] = {1,0,0,0,0,DRIVE_ID};

    if (AT91F_CF_WriteCommand(cmd,6,2) < 0) return -1;

	delay(1000000);

    if (AT91F_CF_Read16(buf,BUF_SIZE/2) != BUF_SIZE/2) return -1;
	if (AT91F_CF_ERR() < 0) return -1;

   	return 0;

}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_READ_CIS
//* \brief Read the CF CIS
//*----------------------------------------------------------------------------
void AT91F_CF_READ_CIS (unsigned char * buf, int size){
    int i;

    for(i=0;i<size/2;i++) *buf++ = *(CompactFlash_CIS_BASE + 2*i);
}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_WRITE_SECTOR
//* \brief fill in the sector with the buffer content
//*----------------------------------------------------------------------------
/*__inline*/ int AT91F_CF_WRITE_SECTOR (unsigned char * buf, char head, char cyl_high, char cyl_low, char sector){
 	char cmd[6];

 	cmd[5] = WRITE_SECTOR;
 	cmd[4] = (1 << 7) | (1 << 5) | (head & 0xff); //LBA = 0
 	cmd[3] = cyl_high;
 	cmd[2] = cyl_low;
 	cmd[1] = sector;
 	cmd[0] = 1;
    if (AT91F_CF_WriteCommand(cmd,6,2) <0) return -1;
    if (AT91F_CF_Write(buf,BUF_SIZE) != BUF_SIZE) return -1;
	if (AT91F_CF_ERR() < 0) return -1;

   	return 0;

}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_WRITE16_SECTOR
//* \brief fill in the sector with the buffer content
//*----------------------------------------------------------------------------
int AT91F_CF_WRITE16_SECTOR (unsigned short * buf, char head, char cyl_high, char cyl_low, char sector){
 	char cmd[6];

 	cmd[5] = WRITE_SECTOR;
 	cmd[4] = (1 << 7) | (1 << 6) | (1 << 5) | (head & 0xff); //LBA = 1
 	cmd[3] = cyl_high;
 	cmd[2] = cyl_low;
 	cmd[1] = sector;
 	cmd[0] = 1;
    if (AT91F_CF_WriteCommand(cmd,6,2) < 0) return -1;
    if (AT91F_CF_Write16(buf,BUF_SIZE/2) != BUF_SIZE/2) return -1;
	if (AT91F_CF_ERR() < 0) return -1;

   	return 0;

}
//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_Read_SECTOR
//* \brief fill in the buffer with the sector content
//*----------------------------------------------------------------------------
 int AT91F_CF_FORMAT_SECTOR (unsigned short * buf, char drive, char cyl, char head){
 	char cmd[4];

 	cmd[3] = FORMAT_TRACK;
 	cmd[2] = (1 << 7) | (1 << 5) | (drive & 0xff); //LBA = 0
 	cmd[1] = cyl;
 	cmd[0] = head;
    if (AT91F_CF_WriteCommand(cmd,4,4) < 0) return -1;
    if (AT91F_CF_Write16(buf,BUF_SIZE/2) < 0) return -1;
	if (AT91F_CF_ERR() < 0) return -1;

   	return 0;

}
//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_Read_SECTOR
//* \brief fill in the buffer with the sector content
//*----------------------------------------------------------------------------
 int AT91F_CF_READ_SECTOR (unsigned char * buf, char head, char cyl_high, char cyl_low, char sector){
 	char cmd[6];

 	cmd[5] = READ_SECTOR;
 	cmd[4] = (1 << 7) | (1 << 5) | (head & 0xff); //LBA = 0
 	cmd[3] = cyl_high;
 	cmd[2] = cyl_low;
 	cmd[1] = sector;
 	cmd[0] = 255;	//for test purpose
    if (AT91F_CF_WriteCommand(cmd,6,2) < 0) return -1;
    if (AT91F_CF_Read(buf,BUF_SIZE) != BUF_SIZE) return -1;
	if (AT91F_CF_ERR() < 0) return -1;

   	return 0;

}
//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_Read16_SECTOR
//* \brief fill in the buffer with the sector content
//*----------------------------------------------------------------------------
/*__inline*/ int AT91F_CF_READ16_SECTOR (unsigned short * buf, char head, char cyl_high, char cyl_low, char sector)
{
 	char cmd[6];

 	cmd[5] = READ_SECTOR;
 	cmd[4] = (1 << 7) | (1 << 6) | (1 << 5) | (head & 0xff); //LBA = 1
 	cmd[3] = cyl_high;
 	cmd[2] = cyl_low;
 	cmd[1] = sector;
 	cmd[0] = 1;
    AT91F_CF_WriteCommand(cmd,6,2);
    if (AT91F_CF_Read16(buf,BUF_SIZE/2) != BUF_SIZE/2) return -1;
	if (AT91F_CF_ERR() < 0) return -1;

   	return 0;

}


//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_WRITE_BUF
//* \brief fill in the sector buffer
//*----------------------------------------------------------------------------
/*__inline*/ int AT91F_CF_WRITE_BUF (unsigned char * buf, char head, char cyl_high, char cyl_low, char sector){
 	char cmd[6];

 	cmd[5] = WRITE_BUF;
 	cmd[4] = (1 << 7) | (1 << 5) | (head & 0xff); //LBA = 0
 	cmd[3] = cyl_high;
 	cmd[2] = cyl_low;
 	cmd[1] = sector;
 	cmd[0] = 1;
    if (AT91F_CF_WriteCommand(cmd,6,2) < 0) return -1;
    if (AT91F_CF_Write(buf,BUF_SIZE) < 0) return -1;
	if (AT91F_CF_ERR() < 0) return -1;
   	return 0;

}


//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_READ_BUF
//* \brief returns the sector buffer content
//*----------------------------------------------------------------------------
/*__inline*/ int AT91F_CF_READ_BUF (unsigned char * buf, char head, char cyl_high, char cyl_low, char sector){
 	char cmd[6];

 	cmd[5] = READ_BUF;
 	cmd[4] = (1 << 7) | (1 << 5) | (head & 0xff); //LBA = 0
 	cmd[3] = cyl_high;
 	cmd[2] = cyl_low;
 	cmd[1] = sector;
 	cmd[0] = 1;
    if (AT91F_CF_WriteCommand(cmd,6,2) <0) return -1;
    if (AT91F_CF_Read(buf,BUF_SIZE) < 0) return -1;
	if (AT91F_CF_ERR() < 0) return -1;
   	return 0;

}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_READ_BUF
//* \brief returns the sector buffer content
//*----------------------------------------------------------------------------
/*__inline*/ int AT91F_CF_READ16_BUF (unsigned short * buf, char head, char cyl_high, char cyl_low, char sector){
 	char cmd[6];

 	cmd[5] = READ_BUF;
 	cmd[4] = (1 << 7) | (1 << 6) | (1 << 5) | (head & 0xff); //LBA = 1
 	cmd[3] = cyl_high;
 	cmd[2] = cyl_low;
 	cmd[1] = sector;
 	cmd[0] = 1;
    if (AT91F_CF_WriteCommand(cmd,6,2) <0) return -1;
    if (AT91F_CF_Read16(buf,BUF_SIZE/2) < 0) return -1;
	if (AT91F_CF_ERR() < 0) return -1;
   	return 0;

}

//*----------------------------------------------------------------------------
//* \fn    AT91F_CF_WRITE_BUF
//* \brief fill in the sector buffer
//*----------------------------------------------------------------------------
/*__inline*/ int AT91F_CF_ERASE_SECTOR (char head, char cyl_high, char cyl_low, char sector){
 	char cmd[6];

 	cmd[5] = ERASE_SECTOR;
 	cmd[4] = (1 << 7) | (1 << 5) | (head & 0xff); //LBA = 0
 	cmd[3] = cyl_high;
 	cmd[2] = cyl_low;
 	cmd[1] = sector;
 	cmd[0] = 1;
    if(AT91F_CF_WriteCommand(cmd,6,2) < 0) return -1;
	if (AT91F_CF_ERR() < 0) return -1;

   	return 0;

}



