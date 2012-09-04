/*-------------------------------------------------------------------------
* Copyright (c) 2006,广东威创日新电子有限公司


* All rights reserved.
*
*
* 文件名称：PethEnd.c
*
* 摘 要：
*        AT91RM9200的同步串行控制器 SSC （Serial Synchronous Controller）
*提供了一种串行同步通信的机制，可以支持很多种通
*讯协议通常用于音频和电信运用，例如 I2S通讯，短帧
*同步，长帧同步。在2501的项目中用于模拟RS422，实现
*一对多的 广播式板间通信。
*
*
* 当前版本：1.0
* 作 者：邱文
* 完成日期：2007年8月20日
*
*
* 修订记录
* --------------------
* 2006-1-23     定义大体框架
* 2006年8月20日 细节部分完成
* 2006-9-6      设计基本完成
-------------------------------------------------------------------------*/




#ifndef __INSCCDRIVER
#define __INSCCDRIVER


#ifdef __cplusplus
extern "C" {
#endif

#include "vxWorks.h"
#include "intLib.h"
#include "errno.h"
#include "semLib.h" 
#include "msgQLib.h"
#include "logLib.h"
#include "drivererr.h"
#include "driverdebug.h"



#include "config.h"






#define LOCAL  static


#define SSC_STATE_INITAL  	(0x1)
#define SSC_STATE_LOOP		    (0x2)
#define SSC_STATE_MEMORY	    (0x4)
#define SSC_STATE_NOTREADY	(0x0)





#define SSC_AT91C_SSCBASE          (0xFFFD0000)
#define SSC_LOOP_DEBUG


/*通道中断号*/
#define SSC_IRQ_CHANNLE		(14)	/*  SHAC Ring Full */

 /*任务相关*/
 
#define SSC_DRIVERTASKPRI		(100)


/**/
#define SSC_PL_RBUF_SIZE			(0x4)
#define SSC_NULL_INT              (0x0)
#define SSC_PACKAGE_SIZE         (1024)









#ifdef SSC_LOOP_DEBUG

/* 调试参数
SSC_RCMR
11111111 		00000000 			0000 0010 			00 0 001 00
SSC_RFMR
00000001		0011 0000			0000 1111			101 11111
SSC_TCMR
11111111 		00000000 			0000 0010 			00 0 001 00
SSC_TFMR
00000001		0011 0000			0000 1111			101 11111
*/

#define    SSC_SYST_CLOCK   (60*1000000)
#define    SSC_BAUD_RATE    (10*1000000)
#define    SSC_CLOCK_RX     (0xFF000204)
#define    SSC_MODE_RX      (0x1300FBF)
#define    SSC_CLOCK_TX     (0XFF000204)
#define    SSC_MODE_TX      (0x1300FBF)
#elif

/* 调试参数
SSC_RCMR
11111111 		00000000 			0000 0010 			00 0 001 00
SSC_RFMR
00000001		0011 0000			0000 1111			100 11111
SSC_TCMR
11111111 		00000000 			0000 0010 			00 0 001 00
SSC_TFMR
00000001		0011 0000			0000 1111			101 11111
*/


#define    SSC_SYST_CLOCK   (60*1000000)
#define    SSC_BAUD_RATE    (10*1000000)
#define    SSC_CLOCK_RX     (0xFF000204)
#define    SSC_MODE_RX      (0x1300F9F)
#define    SSC_CLOCK_TX     (0XFF000204)
#define    SSC_MODE_TX      (0x1300FBF)

#endif



/*SSC2 时钟允许*/
/*
AT91F_SSC2_CfgPMC();
AT91F_SSC2_CfgPIO();

AT91F_SSC0_CfgPMC();

AT91F_SSC1_CfgPMC();
AT91F_SSC1_CfgPIO();


AT91F_SSC_EnableRx();
AT91F_SSC_DisableRx();
AT91F_SSC_EnableTx();
AT91F_SSC_DisableTx();
AT91F_SSC_EnableIt();
AT91F_SSC_DisableIt();


AT91F_SSC_ReceiveFrame();
AT91F_SSC_SetBaudrate();
AT91F_SSC_Configure();
AT91F_SSC_SendFrame();

AT91F_SSC_GetInterruptMaskStatus();
AT91F_SSC_IsInterruptMasked();

*/


/*
AT91F_PDC_SetNextRx();
AT91F_PDC_SetNextTx();
AT91F_PDC_SetRx();
AT91F_PDC_SetTx();
AT91F_PDC_EnableTx();
AT91F_PDC_EnableRx();
AT91F_PDC_DisableTx();
AT91F_PDC_DisableRx();
AT91F_PDC_IsTxEmpty();
AT91F_PDC_IsNextTxEmpty();
AT91F_PDC_IsRxEmpty();
AT91F_PDC_IsNextRxEmpty();
AT91F_PDC_Open();
AT91F_PDC_Close();
AT91F_PDC_SendFrame();
AT91F_PDC_ReceiveFrame();

*/


/*
AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SSC1);
*/
typedef struct SSC_Configure
{
    UINT32  ulSystClock;  /* \arg System Clock Frequency*/
    UINT32  ulBaudRate;   /* \arg Expected Baud Rate Frequency*/
    UINT32  ulClockRx;    /* \arg Receiver Clock Parameters*/
    UINT32  ulModeRx;     /* \arg mode Register to be programmed*/
    UINT32  ulClockTx;    /* \arg Transmitter Clock Parameters*/
    UINT32  ulModeTx;     /* \arg mode Register to be programmed*/
}SSC_CONFIGURE;

typedef struct SSC_Debug_Data
{

	UINT32 		ulSSCSend;	   	      /*通道 收包数 */
	UINT32 		ulSSCRec;			  /*通道 发包数*/
	UINT32 		ulInterruptCtl;     /*通道 中断数*/

}SSC_DEBUG_DATA;


typedef struct SSC_Private_Resource
{
	SEM_ID			semRecBuffInit;    	/* Scc 同步通讯 */
	SEM_ID			semLinkprotect;    	/* Scc 链路保护 */
	UINT32			uluint;				    /*设备号             */
	UINT32          ulvector;				/*中断号             */
	INT32 			ultSCCRec;	   		    /*接收任务 ID   */
	SSC_DEBUG_DATA 	stDebugInf;			/*调试信息       */
	INT32 			ulIntSSCState;		    /*SSC 通道状态*/
	AT91PS_SSC      stAT91SSCSCR;
    void        *   pvSSCSendData;
    void        *   pvSSCReceiveData;
    UINT32          ulSSCInterruptState;
    UINT32          ulSSCPackageSize;
    UINT32          ulTaskPRI;
    char *          pcTaskName;
	MSG_Q_ID  	    msgPlatformR; 		/*消息队列（上层消息接收）*/
    SSC_CONFIGURE   stSSCcongigure; 
}SSC_PRIVATE_RESOURCE;





typedef struct SSC_Private_Data
{
	SSC_PRIVATE_RESOURCE *  pstSSCResource[3];
	SEM_ID  		        semSccSend;    	/* Scc 发包二进制信号量*/
	MSG_Q_ID  		        msgPlatformR; 		/*消息队列（上层消息接收）*/
	INT32 			        ulIntSSCState;		/*SSC 通道状态*/

}SSC_PRIVATE_DATA;




 typedef struct SSC_Task_Data
 {
     char           pcTaskName[3][8];
     UINT32         ulTaskPRI[3];
 }SSC_TASK_DATA;







 void FreeSSCResource(SSC_PRIVATE_RESOURCE * pstSSCResource);
 STATUS SSCDriverinit(SSC_PRIVATE_RESOURCE * pstSSCResource);


#ifdef __cplusplus
}
#endif

#endif /*__INSCCDRIVER*/

