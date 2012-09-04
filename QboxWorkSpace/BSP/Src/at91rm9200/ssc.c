/*-------------------------------------------------------------------------
* Copyright (c) 2006,�㶫�������µ������޹�˾
* All rights reserved.
*
*
* �ļ����ƣ�ssc.c
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


#include "ssc.h"



LOCAL void SSCInt(int lSSCResource);
LOCAL void tSSCRec(int lSSCResource);
LOCAL SSCPmcPio(SSC_PRIVATE_RESOURCE * pstSSCResource);



/*-----------------------------------------------------------------------------
��������: SSCDriverinit
����ʱ��: 2007��9��5��
��������: SSC ������ʼ�����������������

��ڲ���: ��
���ڲ���: ��
����ֵ:     MALLOC_ERROR-------�ڴ����ʧ��
            		    INTCONNECT_ERROR---�ж�����ʧ��
              	    SEM_CREATE_ERROR---�źŴ���ʧ��
              	    TASK_CREATE_ERROR--���񴴽�ʧ��
            		    MSG_CREATE_ERROR---��Ϣ����ʧ��

-----------------------------------------------------------------------------*/
STATUS SSCDriverinit(SSC_PRIVATE_RESOURCE * pstSSCResource)
{


    if (NULL == pstSSCResource)
    {
        return MALLOC_ERROR;
    }



    /*�ر�SSC����ж�*/

    intDisable(pstSSCResource->ulvector);

    /*SSC �жϵ�����*/
    if (intConnect((VOIDFUNCPTR *)(pstSSCResource->ulvector), SSCInt, (INT32)pstSSCResource) == ERROR)
    {

        DRV_LOG(DRV_DEBUG_START,"\rintConnect SSCInt0   error.....!!!!\n",0,0,0,0,0,0);
        FreeSSCResource(pstSSCResource);
        return INTCONNECT_ERROR;
    }





    /*����SSC �������ź���ͬ��*/
    pstSSCResource->semRecBuffInit= semBCreate(SEM_Q_FIFO,SEM_EMPTY) ;
    if (NULL == pstSSCResource->semRecBuffInit)
    {
        FreeSSCResource(pstSSCResource);
        return SEM_CREATE_ERROR;
    }

    /*����SSC ��·����*/
    pstSSCResource->semLinkprotect = semBCreate(SEM_Q_FIFO,SEM_FULL) ;
    
    if (NULL ==  pstSSCResource->semLinkprotect)
    {
        FreeSSCResource(pstSSCResource);
        return SEM_CREATE_ERROR;
    }

    /*ΪSSC ���ݽ��շ����ڴ�*/
    pstSSCResource->pvSSCReceiveData=(void *)cacheDmaMalloc(pstSSCResource->ulSSCPackageSize);

    if (NULL ==  pstSSCResource->pvSSCReceiveData)
    {
        FreeSSCResource(pstSSCResource);
        return MALLOC_ERROR;
    }

    /*������ѯ��������*/
    pstSSCResource->ultSCCRec=taskSpawn(
                            pstSSCResource->pcTaskName,pstSSCResource->ulTaskPRI, 0, 
                            0x5000, (FUNCPTR)tSSCRec, (INT32)pstSSCResource, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0);
    if (ERROR == pstSSCResource->ultSCCRec)
    {
        FreeSSCResource(pstSSCResource);
        return TASK_CREATE_ERROR;
    }
    /*����SSC */
    if (SSC_OK!=SSCPmcPio(pstSSCResource))
    {
        FreeSSCResource(pstSSCResource);
        return SSC_HARDWARE;
    }
    pstSSCResource->ulIntSSCState|=SSC_STATE_MEMORY;

    return SSC_OK;
}


void SSCStart(SSC_PRIVATE_RESOURCE * pstSSCResource)
{
	pstSSCResource->ulIntSSCState|=SSC_STATE_INITAL;
	 /*���ж�*/
	 intEnable(pstSSCResource->ulvector);
     /*SSC �жϿ���*/
	AT91F_SSC_EnableRx(pstSSCResource->stAT91SSCSCR);
    AT91F_SSC_EnableTx(pstSSCResource->stAT91SSCSCR);
	DRV_LOG(DRV_DEBUG_START,"\rSSC Driver start OK !\n",0,0,0,0,0,0);
}



/*-----------------------------------------------------------------------------
��������: SSCInt0
����ʱ��: 2006��9��5��
��������: ͨ�� 0 �жϴ�����
 
��ڲ���: ��
���ڲ���: ��
����ֵ  : ��
-----------------------------------------------------------------------------*/
LOCAL void SSCInt(int lSSCResource)
{

    SSC_PRIVATE_RESOURCE * pstSSCResource = (SSC_PRIVATE_RESOURCE * )lSSCResource;

    /*���ж�*/
    intDisable(pstSSCResource->ulvector);
    /*����ж�*/
    /*�����ź�,ʹ�ܽ�������*/
    pstSSCResource->stDebugInf.ulInterruptCtl++;
    if(OK!=semGive(pstSSCResource->semRecBuffInit))
    {
       DRV_LOG(DRV_DEBUG_INT,"\nIn the interrupt\n",0,0,0,0,0,0);
    }
}



/*-----------------------------------------------------------------------------
��������: FreeSSCResource
����ʱ��: 2006��9��5��
��������: SRAM ������Դ�ͷź��� ,�����ͷ������������Դ
 
��ڲ���: ��
���ڲ���: ��
����ֵ  : ��
-----------------------------------------------------------------------------*/
 void FreeSSCResource(SSC_PRIVATE_RESOURCE * pstSSCResource)
{

	if(NULL==pstSSCResource)
	{
		return ;
	}
	
    if(NULL!=pstSSCResource->pvSSCReceiveData)
    {
        cacheDmaFree(pstSSCResource->pvSSCReceiveData);
        pstSSCResource->pvSSCReceiveData=NULL; 
    }
    
    if (SSC_NULL_INT != pstSSCResource->semRecBuffInit)
   {
       semDelete(pstSSCResource->semRecBuffInit);
   }

    
    
    if (SSC_NULL_INT != pstSSCResource->ultSCCRec)
   {
       taskDelete(pstSSCResource->ultSCCRec);
   }

    pstSSCResource->ulIntSSCState=SSC_STATE_NOTREADY;
    free(pstSSCResource);
    pstSSCResource = NULL;
}










/*-----------------------------------------------------------------------------
��������: tSSCRec
����ʱ��: 2006��9��5��
��������: �������񣬸ú������ڽ��չ���������Զ������
 
��ڲ���: ��
���ڲ���: ��
����ֵ  : ��
-----------------------------------------------------------------------------*/
LOCAL void tSSCRec(int lSSCResource)
{

  SSC_PRIVATE_RESOURCE * pstSSCResource = (SSC_PRIVATE_RESOURCE * )lSSCResource;

  while (1)
  {
    /*�ȴ��жϵ������ź�*/
    semTake(pstSSCResource->semRecBuffInit, WAIT_FOREVER);
	/*��ȡһ�������İ� */
    msgQSend(pstSSCResource->msgPlatformR,
            (char *)(&(pstSSCResource->pvSSCReceiveData)),
            SSC_PL_RBUF_SIZE,
            WAIT_FOREVER ,    
            MSG_PRI_NORMAL   
            );
    pstSSCResource->stDebugInf.ulSSCRec++;
    pstSSCResource->pvSSCReceiveData=(void *)cacheDmaMalloc(pstSSCResource->ulSSCPackageSize);
    while(NULL==pstSSCResource->pvSSCReceiveData)
    {
        DRV_LOG(DRV_DEBUG_RX,"\n No memory for receive data!! task: %s \n",pstSSCResource->pcTaskName,0,0,0,0,0);
        pstSSCResource->pvSSCReceiveData=(void *)cacheDmaMalloc(pstSSCResource->ulSSCPackageSize);
    }
	/*���ж�*/
    
    AT91F_SSC_ReceiveFrame(pstSSCResource->stAT91SSCSCR,pstSSCResource->pvSSCReceiveData,pstSSCResource->ulSSCPackageSize);
  }
}



/*SSC �ܽų�ʼ��,ʱ�Ӻ����ÿռ�*/
/*IO�ܽŵ����ò���ȷ����Ҫ����*/
LOCAL SSCPmcPio(SSC_PRIVATE_RESOURCE * pstSSCResource)
{

	if(0==pstSSCResource->uluint)
	{
    	AT91F_SSC0_CfgPMC();
    	AT91F_SSC0_CfgPIO();
        AT91F_SSC_Configure(pstSSCResource->stAT91SSCSCR,
                               pstSSCResource->stSSCcongigure.ulSystClock,
                               pstSSCResource->stSSCcongigure.ulBaudRate,
                               pstSSCResource->stSSCcongigure.ulClockRx,
                               pstSSCResource->stSSCcongigure.ulModeRx,
                               pstSSCResource->stSSCcongigure.ulClockTx,
                               pstSSCResource->stSSCcongigure.ulModeTx
                                );

        
        AT91F_SSC_ReceiveFrame(pstSSCResource->stAT91SSCSCR,
                                    pstSSCResource->pvSSCReceiveData,
                                    pstSSCResource->ulSSCPackageSize
                                 );
    	return SSC_OK;
	};
	if(1==pstSSCResource->uluint)
	{
    	AT91F_SSC1_CfgPMC();
    	AT91F_SSC1_CfgPIO();
        
        AT91F_SSC_Configure(pstSSCResource->stAT91SSCSCR,
                               pstSSCResource->stSSCcongigure.ulSystClock,
                               pstSSCResource->stSSCcongigure.ulBaudRate,
                               pstSSCResource->stSSCcongigure.ulClockRx,
                               pstSSCResource->stSSCcongigure.ulModeRx,
                               pstSSCResource->stSSCcongigure.ulClockTx,
                               pstSSCResource->stSSCcongigure.ulModeTx
                                );

        
        AT91F_SSC_ReceiveFrame(pstSSCResource->stAT91SSCSCR,
                                    pstSSCResource->pvSSCReceiveData,
                                    pstSSCResource->ulSSCPackageSize
                                 );
    	return SSC_OK;
	};
	if(2==pstSSCResource->uluint)
	{
    	AT91F_SSC2_CfgPMC();
    	AT91F_SSC2_CfgPIO();
        AT91F_SSC_Configure(pstSSCResource->stAT91SSCSCR,
                               pstSSCResource->stSSCcongigure.ulSystClock,
                               pstSSCResource->stSSCcongigure.ulBaudRate,
                               pstSSCResource->stSSCcongigure.ulClockRx,
                               pstSSCResource->stSSCcongigure.ulModeRx,
                               pstSSCResource->stSSCcongigure.ulClockTx,
                               pstSSCResource->stSSCcongigure.ulModeTx
                                );

        
        AT91F_SSC_ReceiveFrame(pstSSCResource->stAT91SSCSCR,
                                    pstSSCResource->pvSSCReceiveData,
                                    pstSSCResource->ulSSCPackageSize
                                 );
    	return SSC_OK;
	};

	return SSC_NO_ERROR;


}


LOCAL void SSCInterruptEnable(SSC_PRIVATE_RESOURCE * pstSSCResource,UINT32 ulIntNo)
{
    UINT32 linterrupt=0x1;
    if(32<ulIntNo)
    {
        return;
    }
    linterrupt<<=ulIntNo;
    AT91F_SSC_EnableIt(pstSSCResource->stAT91SSCSCR,linterrupt);
    return;

}



LOCAL void SSCInterruptDisable(SSC_PRIVATE_RESOURCE * pstSSCResource,UINT32 ulIntNo)
{
    UINT32 linterrupt=0x1;
    if(32<ulIntNo)
    {
        return;
    }
    linterrupt<<=ulIntNo;
    AT91F_SSC_DisableIt(pstSSCResource->stAT91SSCSCR,linterrupt);
    return ;

}


STATUS SSCSend(SSC_PRIVATE_RESOURCE * pstSSCResource, void * SSCBuffer,	UINT32 szBuffer)
{

    semTake(pstSSCResource->semLinkprotect, WAIT_FOREVER);
    AT91F_SSC_SendFrame(pstSSCResource->stAT91SSCSCR,SSCBuffer,pstSSCResource->ulSSCPackageSize);
    pstSSCResource->stDebugInf.ulSSCSend++;
    /* �ر���·*/
    semGive(pstSSCResource->semLinkprotect);
    return SSC_OK;


}


