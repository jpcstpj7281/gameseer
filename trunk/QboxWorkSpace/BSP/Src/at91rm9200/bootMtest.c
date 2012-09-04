#include "vxWorks.h"
#include "sysLib.h"
#include "asm.h"
#include "regs.h"	
#include "config.h"
#include "arch/arm/mmuArmLib.h"

typedef  unsigned char    	     BYTE;    		/*前缀 by        */
typedef  char             	     CHAR;    		/*前缀 c          */
typedef  signed short     	     SWORD;   		/*前缀 ssw      */
typedef  signed long      	     SDWORD;  		/*前缀 i          */
typedef  float                  FLOAT;    		/*前缀 f          */
typedef  double	                 DOUBLE;	 	/*前缀 d         */
typedef  unsigned long long     DDWORD; 		/*前缀 ddw	   */




typedef  void                    VOID;          /*前缀 v         */
typedef  unsigned short   	     WORD;    		/*前缀 w         */
typedef  unsigned long    	     DWORD;   		/*前缀 dw       */

#define LED_ON   (1)
#define LED_OFF  (2)
#define LED_SIK  (3)

#define LED_DIV_DEF  (0x5)
#define LED_SIK_SLOW (0x5)
#define LED_SIK_FAST (0x1)
/* WATCH DOG 部分*/


/* IO 相关定义*/
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
            /*点告警灯*/
			
			BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_ALARMLED_CIO);
        }
        
        if(0==i%(1024*1024*2-4))
        {
            /*灭告警灯*/

			
			BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_ALARMLED_CIO);
        }
	}
	for(i=LOCAL_MEM_LOCAL_ADRS; i<(LOCAL_MEM_LOCAL_ADRS+LOCAL_MEM_SIZE);i+=128)
	{
   		if(*((unsigned int *)i)!=i)
    		{
            /*内存错误点运行灯，死循环*/
    	            while(1)
     		       {
						BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_RUNLED_CIO);
         	       }
            
     		}
        
        if(0==i%(1024*1024*1-4))
        {
            /*点灯*/
			
			BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_ALARMLED_CIO);
        }
        
        if(0==i%(1024*1024*2-4))
        {
            /*灭灯*/
			
			BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_ALARMLED_CIO);
        }
	 }

	 BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_ALARMLED_CIO);
	 
	 /*清零系统参数*/	 

	 if (  *((unsigned int *)0x2000) !=  0x55AA5414)
	 	{
		     for(i=0x00200000; i<(0x00200000+0x3000);i+=4)
		     {
		         *((unsigned int *)i)=0;
		     }
	 	}
	/*	FLASH 片选配置*/	
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


