#include "vxWorks.h"
#include "sysLib.h"
#include "asm.h"
#include "regs.h"	
#include "config.h"
#include "arch/arm/mmuArmLib.h"

typedef  unsigned char    	     BYTE;    		/*ǰ׺ by        */
typedef  char             	     CHAR;    		/*ǰ׺ c          */
typedef  signed short     	     SWORD;   		/*ǰ׺ ssw      */
typedef  signed long      	     SDWORD;  		/*ǰ׺ i          */
typedef  float                  FLOAT;    		/*ǰ׺ f          */
typedef  double	                 DOUBLE;	 	/*ǰ׺ d         */
typedef  unsigned long long     DDWORD; 		/*ǰ׺ ddw	   */




typedef  void                    VOID;          /*ǰ׺ v         */
typedef  unsigned short   	     WORD;    		/*ǰ׺ w         */
typedef  unsigned long    	     DWORD;   		/*ǰ׺ dw       */

#define LED_ON   (1)
#define LED_OFF  (2)
#define LED_SIK  (3)

#define LED_DIV_DEF  (0x5)
#define LED_SIK_SLOW (0x5)
#define LED_SIK_FAST (0x1)
/* WATCH DOG ����*/


/* IO ��ض���*/
#define BSP_DOG_EN_BIO              (2)
#define BSP_DOG_FEED_BIO            (1)
#define BSP_ALARMLED_CIO            (0)	  /**/
#define BSP_RUNLED_CIO              (27)   /* PA27*/
#define BSP_R_FPGA					(15) /*PC15*/
#define BSP_R_PCIE					(2)  /*PC2*/

#define BSP_PIOD      (0xFFFFFA00) /* (PIOD) Base Address*/
#define BSP_PIOC      (0xFFFFF800) /* (PIOC) Base Address*/
#define BSP_PIOB      (0xFFFFF600) /* (PIOB) Base Address*/
#define BSP_PIOA      (0xFFFFF400) /* (PIOA) Base Address*/

void BootTest(void)
{
	unsigned int i;
	
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,BSP_ALARMLED_CIO);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_RUNLED_CIO);

	for(i=LOCAL_MEM_LOCAL_ADRS; i<(LOCAL_MEM_LOCAL_ADRS+LOCAL_MEM_SIZE);i+=128)
 	{
        *((unsigned int *)i)=i;
        if(0==i%(1024*1024*1-4))
        {
            /*��澯��*/
			
			BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_ALARMLED_CIO);
        }
        
        if(0==i%(1024*1024*2-4))
        {
            /*��澯��*/

			
			BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_ALARMLED_CIO);
        }
	}
	for(i=LOCAL_MEM_LOCAL_ADRS; i<(LOCAL_MEM_LOCAL_ADRS+LOCAL_MEM_SIZE);i+=128)
	{
   		if(*((unsigned int *)i)!=i)
    		{
            /*�ڴ��������еƣ���ѭ��*/
    	            while(1)
     		       {
						BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_RUNLED_CIO);
         	       }
            
     		}
        
        if(0==i%(1024*1024*1-4))
        {
            /*���*/
			
			BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_ALARMLED_CIO);
        }
        
        if(0==i%(1024*1024*2-4))
        {
            /*���*/
			
			BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_ALARMLED_CIO);
        }
	 }

	 BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_ALARMLED_CIO);
	 
	 /*����ϵͳ����*/	 

	 if (  *((unsigned int *)0x2000) !=  0x55AA5414)
	 	{
		     for(i=0x00200000; i<(0x00200000+0x3000);i+=4)
		     {
		         *((unsigned int *)i)=0;
		     }
	 	}
	/*	FLASH Ƭѡ����*/	
	 *((volatile unsigned int *)0xffffff78) = 0x00003284;
	/*	*/
	 BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_RUNLED_CIO);
	 BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_ALARMLED_CIO);

 
}


/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_SetOutput*/
/** \brief Set to 1 output PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_OR_PIO_SetOutput(
    AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
    DWORD dwFlag) /* \arg  output to be set*/
{
    
    DWORD dwTempValue;
    dwTempValue = spPio ->PIO_ODSR;
    dwTempValue = dwTempValue | (1 << dwFlag );
    spPio->PIO_SODR = dwTempValue;
}



/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_ClearOutput*/
/** \brief Set to 0 output PIO*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_OR_PIO_ClearOutput(
    AT91PS_PIO spPio,   /* \arg  pointer to a PIO controller*/
    DWORD dwFlag) /* \arg  output to be cleared*/
{
    DWORD dwTempValue;
    dwTempValue = spPio ->PIO_ODSR;
    dwTempValue = ~dwTempValue | (1 << dwFlag );
    spPio->PIO_CODR = dwTempValue;
}


/**----------------------------------------------------------------------------*/
/** \fn    BSP_AT91F_PIO_CfgOutput*/
/** \brief Enable PIO in output mode*/
/**----------------------------------------------------------------------------*/
 VOID BSP_AT91F_OR_PIO_CfgOutput(
    AT91PS_PIO spPio,             /* \arg pointer to a PIO controller*/
    DWORD dwPioEnable)      /* \arg PIO to be enabled*/
{
    DWORD dwTempValue;
    dwTempValue = spPio->PIO_PSR;
    dwTempValue = dwTempValue | (1<<dwPioEnable);
    spPio->PIO_PER = dwTempValue; /* Set in PIO mode*/
    dwTempValue = spPio->PIO_OSR;
    dwTempValue = dwTempValue | (1<<dwPioEnable);
    spPio->PIO_OER = dwTempValue; /* Configure in Output*/
}


