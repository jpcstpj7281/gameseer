/*****************************************************************************/
/*                                                                           */
/* PROJECT : SAMSUNG ECC                                                     */
/* FILE    : SAMSUNG_ECC.c                                                   */
/* PURPOSE : This file implements core ECC algorithms adopted				 */
/*           Hamming Error Correction and Detection Algorithm                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        COPYRIGHT 2000-2004, SAMSUNG ELECTRONICS CO., LTD.                 */
/*                      ALL RIGHTS RESERVED                                  */
/*                                                                           */
/*   Permission is hereby granted to licensees of Samsung Electronics        */
/*   Co., Ltd. products to use or abstract this computer program for the     */
/*   sole purpose of implementing a product based on Samsung                 */
/*   Electronics Co., Ltd. products. No other rights to reproduce, use,      */
/*   or disseminate this computer program, whether in part or in whole,      */
/*   are granted.                                                            */
/*                                                                           */
/*   Samsung Electronics Co., Ltd. makes no representation or warranties     */
/*   with respect to the performance of this computer program, and           */
/*   specifically disclaims any responsibility for any damages,              */
/*   special or consequential, connected with the use of this program.       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* REVISION HISTORY                                                          */
/*                                                                           */
/*  13-NOV-2003 [Chang JongBaek] : 	first writing                            */
/*  03-MAR-2004 [ Kim YoungGon ] :  Second writing                           */
/*  03-MAR-2004 [  Lee JaeBum  ] :  Third writing                            */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* NOTES                                                                     */
/*                                                                           */
/* - Make ECC parity code of 512bytes(256words) and 3 bytes are represented  */
/*   And ECC compare & Correction code is also represented                   */
/*                                                                           */
/*****************************************************************************/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "ecc.h"

#define	XMODE	8

/*****************************************************************************/
/* Address Types                                                             */
/*****************************************************************************/

typedef unsigned char *		address_t;			/* address (pointer) */
typedef unsigned long		address_value_t;	/* address (for calculation) */

/*****************************************************************************/
/* Integer Types                                                             */
/*****************************************************************************/



typedef enum {
	ECC_NO_ERROR			= 0,		/* no error */
	ECC_CORRECTABLE_ERROR	= 1,		/* one bit data error */
	ECC_ECC_ERROR			= 2,		/* one bit ECC error */
	ECC_UNCORRECTABLE_ERROR	= 3			/* uncorrectable error */
} eccdiff_t;

/*****************************************************************************/
/*                                                                           */
/* NAME                                                                      */
/*		make_ecc_512                                                         */
/* DESCRIPTION                                                               */
/*		This function generates 3 byte ECC for 512 byte data.                */
/*      (Software ECC)                                                       */
/* PARAMETERS                                                                */
/*		ecc_buf			the location where ECC should be stored              */
/*		data_buf		given data                                           */
/* RETURN VALUES                                                             */
/*		none                                                                 */
/*                                                                           */
/*****************************************************************************/
void make_ecc_512(uint8_t * ecc_buf, uint8_t * data_buf)
{
	
    uint32_t	i, ALIGN_FACTOR; 
	uint32_t	tmp;
	uint32_t	uiparity = 0;
	uint32_t	parityCol, ecc = 0;
	uint32_t	parityCol4321 = 0, parityCol4343 = 0, parityCol4242 = 0, parityColTot = 0;
	uint32_t	*Data;
	uint32_t	Xorbit=0;

	ALIGN_FACTOR = (uint32_t)data_buf % 4 ;
	Data = (uint32_t *)(data_buf + ALIGN_FACTOR);

	for( i = 0; i < 16; i++)
	{
		parityCol = *Data++; 
		tmp = *Data++; parityCol ^= tmp; parityCol4242 ^= tmp;
		tmp = *Data++; parityCol ^= tmp; parityCol4343 ^= tmp;
		tmp = *Data++; parityCol ^= tmp; parityCol4343 ^= tmp; parityCol4242 ^= tmp;
		tmp = *Data++; parityCol ^= tmp; parityCol4321 ^= tmp;
		tmp = *Data++; parityCol ^= tmp; parityCol4242 ^= tmp; parityCol4321 ^= tmp;
		tmp = *Data++; parityCol ^= tmp; parityCol4343 ^= tmp; parityCol4321 ^= tmp;
		tmp = *Data++; parityCol ^= tmp; parityCol4242 ^= tmp; parityCol4343 ^= tmp; parityCol4321 ^= tmp;

		parityColTot ^= parityCol;

		tmp = (parityCol >> 16) ^ parityCol;
		tmp = (tmp >> 8) ^ tmp;
		tmp = (tmp >> 4) ^ tmp;
		tmp = ((tmp >> 2) ^ tmp) & 0x03;
		if ((tmp == 0x01) || (tmp == 0x02))
		{
			uiparity ^= i;
			Xorbit ^= 0x01;
		}
	}

	tmp = (parityCol4321 >> 16) ^ parityCol4321;
	tmp = (tmp << 8) ^ tmp;
	tmp = (tmp >> 4) ^ tmp;
	tmp = (tmp >> 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x200;	// p128
	tmp = (parityCol4343 >> 16) ^ parityCol4343;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp << 4) ^ tmp;
	tmp = (tmp << 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x80;	// p64
	tmp = (parityCol4242 >> 16) ^ parityCol4242;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp << 4) ^ tmp;
	tmp = (tmp >> 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x20;	// p32
	tmp = parityColTot & 0xFFFF0000;
	tmp = tmp >> 16;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp >> 4) ^ tmp;
	tmp = (tmp << 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x08;	// p16
	tmp = parityColTot & 0xFF00FF00;
	tmp = (tmp >> 16) ^ tmp;
	tmp = (tmp >> 8);
	tmp = (tmp >> 4) ^ tmp;
	tmp = (tmp >> 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x02;	// p8
	tmp = parityColTot & 0xF0F0F0F0 ;
	tmp = (tmp << 16) ^ tmp;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp << 2) ^ tmp;
	ecc |= ((tmp << 1) ^ tmp) & 0x800000;	// p4
	tmp = parityColTot & 0xCCCCCCCC ;
	tmp = (tmp << 16) ^ tmp;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp << 4) ^ tmp;
	tmp = (tmp >> 2);
	ecc |= ((tmp << 1) ^ tmp) & 0x200000;	// p2
	tmp = parityColTot & 0xAAAAAAAA ;
	tmp = (tmp << 16) ^ tmp;
	tmp = (tmp >> 8) ^ tmp;
	tmp = (tmp >> 4) ^ tmp;
	tmp = (tmp << 2) ^ tmp;
	ecc |= (tmp & 0x80000);	// p1
	ecc |= (uiparity & 0x01) <<11;	
	ecc |= (uiparity & 0x02) <<12;	
	ecc |= (uiparity & 0x04) <<13;
	ecc |= (uiparity & 0x08) <<14;

	if (Xorbit)
	{
		ecc |= (ecc ^ 0x00AAAAAA)>>1;
	}
	else
	{
		ecc |= (ecc >> 1);
	}
	ecc = ~ecc;
	*(ecc_buf + 2) = (uint8_t) (ecc >> 16);
	*(ecc_buf + 1) = (uint8_t) (ecc >> 8);
	*(ecc_buf + 0) = (uint8_t) (ecc);
}

/*****************************************************************************/
/*                                                                           */
/* NAME                                                                      */
/*		compare_ecc_512                                                      */
/* DESCRIPTION                                                               */
/*		This function compares two ECCs and indicates if there is an error.  */
/* PARAMETERS                                                                */
/*		ecc_data1		one ECC to be compared                               */
/*		ecc_data2		the other ECC to be compared                         */
/*		page_data		content of data page                                 */
/*		offset			where the error occurred                             */
/*		corrected		correct data                                         */
/* RETURN VALUES                                                             */
/*		Upon successful completion, compare_ecc returns SSR_SUCCESS.         */
/*      Otherwise, corresponding error code is returned.                     */
/*                                                                           */
/*****************************************************************************/
eccdiff_t compare_ecc_512(uint8_t *iEccdata1, uint8_t *iEccdata2, 
          uint8_t *pPagedata, int32_t *pOffset, uint8_t *pCorrected)
{

	uint32_t  iCompecc = 0, iEccsum = 0;
    uint32_t  iFindbyte   = 0;
    uint32_t  iIndex;
    uint32_t  nT1 = 0, nT2 =0;

	uint8_t   iNewvalue;
    uint8_t   iFindbit    = 0;

    uint8_t   *pEcc1 = (uint8_t *)iEccdata1;
    uint8_t   *pEcc2 = (uint8_t *)iEccdata2;

	for ( iIndex = 0; iIndex <2; iIndex++)
    {
        nT1 ^= (((*pEcc1) >> iIndex) & 0x01);
        nT2 ^= (((*pEcc2) >> iIndex) & 0x01);
    }

    for (iIndex = 0; iIndex < 3; iIndex++)
        iCompecc |= ((~(*pEcc1++) ^ ~(*pEcc2++)) << iIndex * 8);
    
    for(iIndex = 0; iIndex < 24; iIndex++) {
        iEccsum += ((iCompecc >> iIndex) & 0x01);
    }

    
    switch (iEccsum) {
    case 0 :
		printf("RESULT : no error\n");
        return ECC_NO_ERROR;

	case 1 :
		printf("RESULT : ECC code 1 bit fail\n");
        return ECC_ECC_ERROR;

    case 12 :
        if (nT1 != nT2)
        {
            iFindbyte = ((iCompecc >> 17 & 1) << 8) + ((iCompecc >> 15 & 1) << 7) + ((iCompecc >> 13 & 1) << 6)
                      + ((iCompecc >> 11 & 1) << 5) + ((iCompecc >> 9 & 1) << 4) + ((iCompecc >> 7 & 1) << 3)
                      + ((iCompecc >> 5 & 1) << 2) + ((iCompecc >> 3 & 1) << 1) + (iCompecc >> 1 & 1);
            iFindbit =  (uint8_t)(((iCompecc >> 23 & 1) << 2) + ((iCompecc >> 21 & 1) << 1) + (iCompecc >> 19 & 1));
            iNewvalue = (uint8_t)(pPagedata[iFindbyte] ^ (1 << iFindbit));
			printf("iCompecc = %d\n",iCompecc);
            printf("RESULT : one bit error\r\n");
            printf("byte = %d, bit = %d\r\n", iFindbyte, iFindbit);
            printf("corrupted = %x, corrected = %x\r\n", pPagedata[iFindbyte], iNewvalue);

            if (pOffset != NULL) {
                *pOffset = iFindbyte;
            }
            if (pCorrected != NULL) {
                *pCorrected = iNewvalue;
            }
            
            return ECC_CORRECTABLE_ERROR;
        }
        else
            return ECC_UNCORRECTABLE_ERROR;

    default :
		printf("RESULT : unrecoverable error\n");
        return ECC_UNCORRECTABLE_ERROR;
    }   
}

text_ecc()
{
  int32_t i;
  char    Ecc[128];
  int32_t iEccdata1[128];
  int32_t pOffset;
  uint8_t pCorrected;
  for(i=0;i<128;i++)
  	{
  	iEccdata1[i]=i;
	Ecc[i]=0;
  	}
  make_ecc_512((uint8_t *)iEccdata1,(uint8_t *)Ecc);
  compare_ecc_512((uint8_t *)Ecc,(uint8_t *)Ecc,(uint8_t *)iEccdata1,&pOffset,&pCorrected);

}


















/**************��������******************/
#include <stdio.h>
#include <stddef.h>

int main_test(void)
{
    int keys[] = { 5, 8, 9, 15, -18, 150, 0, 0, -5, -108, 100 };
    int i;
    const int keys_size = (sizeof keys) / (sizeof *keys);
    /* prototype */
    void my_qsort(int v[], int left, int right);
    
    my_qsort( keys, 0, keys_size - 1 );
    for ( i = 0; i < keys_size; ++i ) {
        printf("%d ", keys[i]);
    }
    
    printf("\nPress ENTER to quit...");    
    getchar();
    return 0;
}

/* my_qsort:  sort v[left]...v[right] into increasing order */
void my_qsort(int v[], int left, int right)
{
   int i, last;
   /* prototype */
   void my_swap(int v[], int i, int j);

   if (left >= right) /* do nothing if array contains */
       return;        /* fewer than two elements */
   my_swap(v, left, (left + right)/2); /* move partition elem */
   last = left;                        /* to v[0] */
   for (i = left + 1; i <= right; i++) /* partition */
       if (v[i] < v[left])
           my_swap(v, ++last, i);
   my_swap(v, left, last);            /* restore partition elem */
   my_qsort(v, left, last-1);
   my_qsort(v, last+1, right);
}

/* my_swap:  interchange v[i] and v[j] */
void my_swap(int v[], int i, int j)
{
   int temp;

   temp = v[i];
   v[i] = v[j];
   v[j] = temp;
}

