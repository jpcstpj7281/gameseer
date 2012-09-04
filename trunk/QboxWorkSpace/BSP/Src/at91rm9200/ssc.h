/*-------------------------------------------------------------------------
* Copyright (c) 2006,�㶫�������µ������޹�˾


* All rights reserved.
*
*
* �ļ����ƣ�PethEnd.c
*
* ժ Ҫ��
*        AT91RM9200��ͬ�����п����� SSC ��Serial Synchronous Controller��
*�ṩ��һ�ִ���ͬ��ͨ�ŵĻ��ƣ�����֧�ֺܶ���ͨ
*ѶЭ��ͨ��������Ƶ�͵������ã����� I2SͨѶ����֡
*ͬ������֡ͬ������2501����Ŀ������ģ��RS422��ʵ��
*һ�Զ�� �㲥ʽ���ͨ�š�
*
*
* ��ǰ�汾��1.0
* �� �ߣ�����
* ������ڣ�2007��8��20��
*
*
* �޶���¼
* --------------------
* 2006-1-23     ���������
* 2006��8��20�� ϸ�ڲ������
* 2006-9-6      ��ƻ������
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


/*ͨ���жϺ�*/
#define SSC_IRQ_CHANNLE		(14)	/*  SHAC Ring Full */

 /*�������*/
 
#define SSC_DRIVERTASKPRI		(100)


/**/
#define SSC_PL_RBUF_SIZE			(0x4)
#define SSC_NULL_INT              (0x0)
#define SSC_PACKAGE_SIZE         (1024)









#ifdef SSC_LOOP_DEBUG

/* ���Բ���
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

/* ���Բ���
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



/*SSC2 ʱ������*/
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

	UINT32 		ulSSCSend;	   	      /*ͨ�� �հ��� */
	UINT32 		ulSSCRec;			  /*ͨ�� ������*/
	UINT32 		ulInterruptCtl;     /*ͨ�� �ж���*/

}SSC_DEBUG_DATA;


typedef struct SSC_Private_Resource
{
	SEM_ID			semRecBuffInit;    	/* Scc ͬ��ͨѶ */
	SEM_ID			semLinkprotect;    	/* Scc ��·���� */
	UINT32			uluint;				    /*�豸��             */
	UINT32          ulvector;				/*�жϺ�             */
	INT32 			ultSCCRec;	   		    /*�������� ID   */
	SSC_DEBUG_DATA 	stDebugInf;			/*������Ϣ       */
	INT32 			ulIntSSCState;		    /*SSC ͨ��״̬*/
	AT91PS_SSC      stAT91SSCSCR;
    void        *   pvSSCSendData;
    void        *   pvSSCReceiveData;
    UINT32          ulSSCInterruptState;
    UINT32          ulSSCPackageSize;
    UINT32          ulTaskPRI;
    char *          pcTaskName;
	MSG_Q_ID  	    msgPlatformR; 		/*��Ϣ���У��ϲ���Ϣ���գ�*/
    SSC_CONFIGURE   stSSCcongigure; 
}SSC_PRIVATE_RESOURCE;





typedef struct SSC_Private_Data
{
	SSC_PRIVATE_RESOURCE *  pstSSCResource[3];
	SEM_ID  		        semSccSend;    	/* Scc �����������ź���*/
	MSG_Q_ID  		        msgPlatformR; 		/*��Ϣ���У��ϲ���Ϣ���գ�*/
	INT32 			        ulIntSSCState;		/*SSC ͨ��״̬*/

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

