/*-------------------------------------------------------------------------
* Copyright (c) 2006,�㶫�������µ������޹�˾


* All rights reserved.
*
*
* �ļ����ƣ�sysssc.c
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

LOCAL SSC_TASK_DATA task_Data=
{
    {"SSCTSK0","SSCTSK1","SSCTSK2"},
    {SSC_DRIVERTASKPRI,SSC_DRIVERTASKPRI,SSC_DRIVERTASKPRI}

};


/*ȫ�ֱ���*/
LOCAL SSC_PRIVATE_DATA * mdl_sysSSCData=NULL;
LOCAL void sysSSCFree(void);

STATUS sysSSCinit(UINT32 ulSSCNo)
{
	UINT32 ulILoop;
	ulSSCNo-=1;
	/*SSC ͨ����������С��3*/
	if(3<ulSSCNo)
	{
		DRV_LOG(DRV_DEBUG_INIT,"ulSSCNo error !\n",0,0,0,0,0,0);

		return SSC_NO_ERROR;
		
	}
	/*����ȫ�ֱ����ڴ�*/
	mdl_sysSSCData=(SSC_PRIVATE_DATA *)malloc(sizeof(SSC_PRIVATE_DATA));
	if (NULL == mdl_sysSSCData)
	{
	
		  DRV_LOG(DRV_DEBUG_INIT,"we have no enough memory !\n",0,0,0,0,0,0);
		  return MALLOC_ERROR;
	}


	/*�����豸��Դ*/
	bzero(((char *)mdl_sysSSCData), sizeof(SSC_PRIVATE_DATA));

	/*��Ϣ���У�ƽ̨��Ϣ���գ�*/
	mdl_sysSSCData->msgPlatformR= msgQCreate(10, SSC_PL_RBUF_SIZE, MSG_Q_FIFO);
	if (NULL == mdl_sysSSCData->msgPlatformR)
	  {
		sysSSCFree();
		return MSG_CREATE_ERROR;
	  }
	
	
	
	/*����ringBuffer �������ź�������*/
	mdl_sysSSCData->semSccSend=semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	if (NULL == mdl_sysSSCData->semSccSend)
	{
	  sysSSCFree();
	  return SEM_CREATE_ERROR;
	}


	/*����SSC ͨ����������*/
	for(ulILoop=0;ulILoop<ulSSCNo+1;ulILoop++)
	{
		
		mdl_sysSSCData->pstSSCResource[ulILoop]=(SSC_PRIVATE_RESOURCE *)malloc(sizeof(SSC_PRIVATE_RESOURCE));
		if (NULL == mdl_sysSSCData->pstSSCResource[ulILoop])
		{
		
			  DRV_LOG(DRV_DEBUG_INIT,"we have no enough memory !\n",0,0,0,0,0,0);
			  sysSSCFree();
			  return MALLOC_ERROR;
		}


		/*�����豸��Դ*/
		bzero(((char *)mdl_sysSSCData->pstSSCResource[ulILoop]), sizeof(SSC_PRIVATE_RESOURCE));

		/*���ݳ�ʼ�� */
		mdl_sysSSCData->pstSSCResource[ulILoop]->uluint=ulILoop;
		mdl_sysSSCData->pstSSCResource[ulILoop]->ulvector=SSC_IRQ_CHANNLE+ulILoop;
        mdl_sysSSCData->pstSSCResource[ulILoop]->ulSSCPackageSize=SSC_PACKAGE_SIZE;
        mdl_sysSSCData->pstSSCResource[ulILoop]->pcTaskName=task_Data.pcTaskName[ulILoop];
        mdl_sysSSCData->pstSSCResource[ulILoop]->ulTaskPRI=task_Data.ulTaskPRI[ulILoop];
        mdl_sysSSCData->pstSSCResource[ulILoop]->stAT91SSCSCR=(AT91PS_SSC)((int)AT91C_BASE_SSC0+(ulILoop*0x4000));
        mdl_sysSSCData->pstSSCResource[ulILoop]->msgPlatformR=mdl_sysSSCData->msgPlatformR;
        mdl_sysSSCData->pstSSCResource[ulILoop]->stSSCcongigure.ulBaudRate=SSC_BAUD_RATE;
        mdl_sysSSCData->pstSSCResource[ulILoop]->stSSCcongigure.ulSystClock=SSC_SYST_CLOCK;
        mdl_sysSSCData->pstSSCResource[ulILoop]->stSSCcongigure.ulClockRx=SSC_CLOCK_RX;
        mdl_sysSSCData->pstSSCResource[ulILoop]->stSSCcongigure.ulClockTx=SSC_CLOCK_TX;
        mdl_sysSSCData->pstSSCResource[ulILoop]->stSSCcongigure.ulModeRx=SSC_MODE_RX;
        mdl_sysSSCData->pstSSCResource[ulILoop]->stSSCcongigure.ulModeTx=SSC_MODE_TX;


		if(SSC_OK!=SSCDriverinit(mdl_sysSSCData->pstSSCResource[ulILoop]))
			{
			sysSSCFree();
			return MALLOC_ERROR;
			}
		
	

	}

	mdl_sysSSCData->ulIntSSCState|=SSC_STATE_MEMORY;
	
	/*����SSC ͨ��*/
	for(ulILoop=0;ulILoop<ulSSCNo;ulILoop++)
	{

		SSCStart(mdl_sysSSCData->pstSSCResource[ulILoop]);
	
	}

	/*������������*/

	semGive(mdl_sysSSCData->semSccSend);

	mdl_sysSSCData->ulIntSSCState|=SSC_STATE_INITAL;

	return SSC_OK;



}

LOCAL void sysSSCFree(void)
{
    if (SSC_NULL_INT != mdl_sysSSCData->semSccSend)          
       {
           semDelete(mdl_sysSSCData->semSccSend);
       }

	if (SSC_NULL_INT != mdl_sysSSCData->msgPlatformR) 
       {
           msgQDelete(mdl_sysSSCData->msgPlatformR);
       }
		FreeSSCResource(mdl_sysSSCData->pstSSCResource[0]);
		FreeSSCResource(mdl_sysSSCData->pstSSCResource[1]);
		FreeSSCResource(mdl_sysSSCData->pstSSCResource[2]);


}

STATUS getMainSCCMsgQID(MSG_Q_ID * msgSSCQID)
{
    if(NULL==mdl_sysSSCData)
    {
        return SSC_INIT_ERROR;
    }
    *msgSSCQID = mdl_sysSSCData->msgPlatformR;

}

STATUS mainSCCSend(UINT8 bMainSCCNo, UINT32 ulbufferSize, INT8 *pbBuffer)
{
    if(NULL==mdl_sysSSCData)
    {
        return SSC_INIT_ERROR;
    }
    if(3<bMainSCCNo)
    {
        return SSC_NO_ERROR;
    }
    if(1024!=ulbufferSize)
    {
        return SSC_PACKSIZE_ERROR;
    }
    return SSCSend(mdl_sysSSCData->pstSSCResource[bMainSCCNo],(void *)pbBuffer,ulbufferSize);
}



/*���Դ��� */


void SSC_TEST(void)
{
    MSG_Q_ID msgReceiveTest;
    UINT32 ulFreeData;
    sysSSCinit(1);
    getMainSCCMsgQID(&msgReceiveTest);
    while(1)
    {
    msgQReceive(msgReceiveTest,(void *)&ulFreeData,4,WAIT_FOREVER);
    DRV_LOG(DRV_DEBUG_TEST,"we have to Free memory %08x !\n",ulFreeData,0,0,0,0,0);
    cacheDmaFree((void *)ulFreeData);
    }

}

void SSC_SEND_TEST(void)
{
    void * pvTestData=NULL;

    pvTestData=(void *)cacheDmaMalloc(SSC_PACKAGE_SIZE);
    
    mainSCCSend(0,SSC_PACKAGE_SIZE,pvTestData);
    
    cacheDmaFree((void *)pvTestData);

}
