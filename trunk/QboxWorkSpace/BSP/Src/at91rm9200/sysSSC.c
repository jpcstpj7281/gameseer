/*-------------------------------------------------------------------------
* Copyright (c) 2006,广东威创日新电子有限公司


* All rights reserved.
*
*
* 文件名称：sysssc.c
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


#include "ssc.h"

LOCAL SSC_TASK_DATA task_Data=
{
    {"SSCTSK0","SSCTSK1","SSCTSK2"},
    {SSC_DRIVERTASKPRI,SSC_DRIVERTASKPRI,SSC_DRIVERTASKPRI}

};


/*全局变量*/
LOCAL SSC_PRIVATE_DATA * mdl_sysSSCData=NULL;
LOCAL void sysSSCFree(void);

STATUS sysSSCinit(UINT32 ulSSCNo)
{
	UINT32 ulILoop;
	ulSSCNo-=1;
	/*SSC 通道个数必须小于3*/
	if(3<ulSSCNo)
	{
		DRV_LOG(DRV_DEBUG_INIT,"ulSSCNo error !\n",0,0,0,0,0,0);

		return SSC_NO_ERROR;
		
	}
	/*分配全局变量内存*/
	mdl_sysSSCData=(SSC_PRIVATE_DATA *)malloc(sizeof(SSC_PRIVATE_DATA));
	if (NULL == mdl_sysSSCData)
	{
	
		  DRV_LOG(DRV_DEBUG_INIT,"we have no enough memory !\n",0,0,0,0,0,0);
		  return MALLOC_ERROR;
	}


	/*清零设备资源*/
	bzero(((char *)mdl_sysSSCData), sizeof(SSC_PRIVATE_DATA));

	/*消息队列（平台消息接收）*/
	mdl_sysSSCData->msgPlatformR= msgQCreate(10, SSC_PL_RBUF_SIZE, MSG_Q_FIFO);
	if (NULL == mdl_sysSSCData->msgPlatformR)
	  {
		sysSSCFree();
		return MSG_CREATE_ERROR;
	  }
	
	
	
	/*创建ringBuffer 二进制信号量互斥*/
	mdl_sysSSCData->semSccSend=semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	if (NULL == mdl_sysSSCData->semSccSend)
	{
	  sysSSCFree();
	  return SEM_CREATE_ERROR;
	}


	/*分配SSC 通道独立数据*/
	for(ulILoop=0;ulILoop<ulSSCNo+1;ulILoop++)
	{
		
		mdl_sysSSCData->pstSSCResource[ulILoop]=(SSC_PRIVATE_RESOURCE *)malloc(sizeof(SSC_PRIVATE_RESOURCE));
		if (NULL == mdl_sysSSCData->pstSSCResource[ulILoop])
		{
		
			  DRV_LOG(DRV_DEBUG_INIT,"we have no enough memory !\n",0,0,0,0,0,0);
			  sysSSCFree();
			  return MALLOC_ERROR;
		}


		/*清零设备资源*/
		bzero(((char *)mdl_sysSSCData->pstSSCResource[ulILoop]), sizeof(SSC_PRIVATE_RESOURCE));

		/*数据初始化 */
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
	
	/*启动SSC 通道*/
	for(ulILoop=0;ulILoop<ulSSCNo;ulILoop++)
	{

		SSCStart(mdl_sysSSCData->pstSSCResource[ulILoop]);
	
	}

	/*开启发送允许*/

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



/*测试代码 */


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
