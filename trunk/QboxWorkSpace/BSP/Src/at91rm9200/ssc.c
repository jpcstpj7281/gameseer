/*-------------------------------------------------------------------------
* Copyright (c) 2006,广东威创日新电子有限公司
* All rights reserved.
*
*
* 文件名称：ssc.c
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



LOCAL void SSCInt(int lSSCResource);
LOCAL void tSSCRec(int lSSCResource);
LOCAL SSCPmcPio(SSC_PRIVATE_RESOURCE * pstSSCResource);



/*-----------------------------------------------------------------------------
函数名称: SSCDriverinit
创建时间: 2007年9月5日
功能描述: SSC 驱动初始化，本驱动程序入口

入口参数: 无
出口参数: 无
返回值:     MALLOC_ERROR-------内存分配失败
            		    INTCONNECT_ERROR---中断连接失败
              	    SEM_CREATE_ERROR---信号创建失败
              	    TASK_CREATE_ERROR--任务创建失败
            		    MSG_CREATE_ERROR---消息创建失败

-----------------------------------------------------------------------------*/
STATUS SSCDriverinit(SSC_PRIVATE_RESOURCE * pstSSCResource)
{


    if (NULL == pstSSCResource)
    {
        return MALLOC_ERROR;
    }



    /*关闭SSC相关中断*/

    intDisable(pstSSCResource->ulvector);

    /*SSC 中断的连接*/
    if (intConnect((VOIDFUNCPTR *)(pstSSCResource->ulvector), SSCInt, (INT32)pstSSCResource) == ERROR)
    {

        DRV_LOG(DRV_DEBUG_START,"\rintConnect SSCInt0   error.....!!!!\n",0,0,0,0,0,0);
        FreeSSCResource(pstSSCResource);
        return INTCONNECT_ERROR;
    }





    /*创建SSC 二进制信号量同步*/
    pstSSCResource->semRecBuffInit= semBCreate(SEM_Q_FIFO,SEM_EMPTY) ;
    if (NULL == pstSSCResource->semRecBuffInit)
    {
        FreeSSCResource(pstSSCResource);
        return SEM_CREATE_ERROR;
    }

    /*创建SSC 链路保护*/
    pstSSCResource->semLinkprotect = semBCreate(SEM_Q_FIFO,SEM_FULL) ;
    
    if (NULL ==  pstSSCResource->semLinkprotect)
    {
        FreeSSCResource(pstSSCResource);
        return SEM_CREATE_ERROR;
    }

    /*为SSC 数据接收分配内存*/
    pstSSCResource->pvSSCReceiveData=(void *)cacheDmaMalloc(pstSSCResource->ulSSCPackageSize);

    if (NULL ==  pstSSCResource->pvSSCReceiveData)
    {
        FreeSSCResource(pstSSCResource);
        return MALLOC_ERROR;
    }

    /*启动轮询接收任务*/
    pstSSCResource->ultSCCRec=taskSpawn(
                            pstSSCResource->pcTaskName,pstSSCResource->ulTaskPRI, 0, 
                            0x5000, (FUNCPTR)tSSCRec, (INT32)pstSSCResource, 0, 
                            0, 0, 0, 0, 0, 0, 0, 0);
    if (ERROR == pstSSCResource->ultSCCRec)
    {
        FreeSSCResource(pstSSCResource);
        return TASK_CREATE_ERROR;
    }
    /*配置SSC */
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
	 /*开中断*/
	 intEnable(pstSSCResource->ulvector);
     /*SSC 中断开启*/
	AT91F_SSC_EnableRx(pstSSCResource->stAT91SSCSCR);
    AT91F_SSC_EnableTx(pstSSCResource->stAT91SSCSCR);
	DRV_LOG(DRV_DEBUG_START,"\rSSC Driver start OK !\n",0,0,0,0,0,0);
}



/*-----------------------------------------------------------------------------
函数名称: SSCInt0
创建时间: 2006年9月5日
功能描述: 通道 0 中断处理函数
 
入口参数: 无
出口参数: 无
返回值  : 无
-----------------------------------------------------------------------------*/
LOCAL void SSCInt(int lSSCResource)
{

    SSC_PRIVATE_RESOURCE * pstSSCResource = (SSC_PRIVATE_RESOURCE * )lSSCResource;

    /*关中断*/
    intDisable(pstSSCResource->ulvector);
    /*清楚中断*/
    /*发送信号,使能接收任务*/
    pstSSCResource->stDebugInf.ulInterruptCtl++;
    if(OK!=semGive(pstSSCResource->semRecBuffInit))
    {
       DRV_LOG(DRV_DEBUG_INT,"\nIn the interrupt\n",0,0,0,0,0,0);
    }
}



/*-----------------------------------------------------------------------------
函数名称: FreeSSCResource
创建时间: 2006年9月5日
功能描述: SRAM 驱动资源释放函数 ,用于释放驱动分配的资源
 
入口参数: 无
出口参数: 无
返回值  : 无
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
函数名称: tSSCRec
创建时间: 2006年9月5日
功能描述: 接收任务，该函数用于接收管理任务，永远不返回
 
入口参数: 无
出口参数: 无
返回值  : 无
-----------------------------------------------------------------------------*/
LOCAL void tSSCRec(int lSSCResource)
{

  SSC_PRIVATE_RESOURCE * pstSSCResource = (SSC_PRIVATE_RESOURCE * )lSSCResource;

  while (1)
  {
    /*等待中断到来的信号*/
    semTake(pstSSCResource->semRecBuffInit, WAIT_FOREVER);
	/*收取一定数量的包 */
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
	/*开中断*/
    
    AT91F_SSC_ReceiveFrame(pstSSCResource->stAT91SSCSCR,pstSSCResource->pvSSCReceiveData,pstSSCResource->ulSSCPackageSize);
  }
}



/*SSC 管脚初始化,时钟和配置空间*/
/*IO管脚的配置不正确，需要纠正*/
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
    /* 关闭链路*/
    semGive(pstSSCResource->semLinkprotect);
    return SSC_OK;


}


