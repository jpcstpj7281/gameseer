/******************************************************************************

  

******************************************************************************/

#include "UrgencyChannelDrv.h"

LOCAL BYTE dataa[2000];
LOCAL BYTE UrgencyMACAdd[6]= {0x00,0x0c,0x29,0xed,0x7f};
LOCAL BYTE MulMACAdd[6]= {0x01,0x00,0x5e,0xed,0x7f};


static struct sUrgencyPara s_sUrgencyPara;

void UrgencyShow()
{
    logMsg("Receive pCookie   :%08x!\n", s_sUrgencyPara.vmonitorRecvBindCookie);
    logMsg("Send    pCookie   :%08x!\n", s_sUrgencyPara.vmonitorSendBindCookie);
    logMsg("End OBJ ADDR      :%08x!\n", s_sUrgencyPara.pEnd);
    logMsg("ChannelType       :%08x!\n", s_sUrgencyPara.dwChannelType);
    logMsg("Receive Count     :%08x!\n", s_sUrgencyPara.dwReceiveCount);
    logMsg("Send Count        :%08x!\n", s_sUrgencyPara.dwSendCount);
    logMsg("Sem_ID            :%08x!\n", s_sUrgencyPara.semRecBuffInit);
    logMsg("ETH name:%s Unit:%08x\n", s_sUrgencyPara.abyEthName, s_sUrgencyPara.dwEthUnit);

    return ;
}


void  BSP_UrgencySetMulAdd(BYTE byNo)
{
	if(NULL==s_sUrgencyPara.vmonitorRecvBindCookie)
	{
		return;
	}
	MulMACAdd[5]=byNo;
	muxMCastAddrAdd(s_sUrgencyPara.vmonitorRecvBindCookie,MulMACAdd);
}


void  BSP_MulAdd(BYTE HashIndex)
{
	DWORD MulticastTable[2];
    
	volatile DWORD * HASHL=(volatile DWORD *)(0x90+0xFFFBC000);
	volatile DWORD * HASHH=(volatile DWORD *)(0x94+0xFFFBC000);
	
	volatile DWORD * EMAC_CFG=(volatile DWORD *)(0x04+0xFFFBC000);

	MulticastTable[0]=MulticastTable[1]=0;
	MulticastTable[ HashIndex/32]  |=  1 << (HashIndex%32);
	*HASHH |= MulticastTable[1];
	*HASHL |= MulticastTable[0];
	*EMAC_CFG |= 1<<6;
}

void BSP_MULTest(BYTE bydelay)
{
	DWORD dwloop=0;
	for(dwloop=0;dwloop<64;dwloop++)
	{
		BSP_MulAdd(dwloop);
		taskDelay(bydelay);
		printf("\ndwloop: %d \n",dwloop);
	}


}

/*紧急通道数据 接收*/

LOCAL BOOL UrgencyRecvProcess
(void * pCookie, long type, M_BLK_ID pMblk, LL_HDR_INFO *pLinkHdrInfo, void *pSpare)
{

	if( (2000>pMblk->mBlkHdr.mLen) && (pLinkHdrInfo->pktType==0x8888) )
	{
        s_sUrgencyPara.dwReceiveCount++;
       // PF_ReceiveUrgentFrame((pMblk->mBlkHdr.mLen-14),(BYTE* )(pMblk->mBlkHdr.mData+14));

		netMblkClChainFree(pMblk);
		return TRUE;

	}


    return FALSE;
}


/*紧急数据发送监测*/
LOCAL BOOL UrgencySendProcess
(void *pCookie, long type, M_BLK_ID pMblk, LL_HDR_INFO *pLinkHdrInfo, void *pSpare)
{
    int i;
    printf("DataMonitorByMux>Sended data(len=%d):\n", pMblk->mBlkHdr.mLen);
    for(i=0; i<pMblk->mBlkHdr.mLen; i++)
    printf("%3x", *((unsigned char *)pMblk->mBlkHdr.mData+i));
    printf("\n");

    return FALSE;
}

STATUS urgencyInit()
{
    bzero((void*)(&s_sUrgencyPara), sizeof(s_sUrgencyPara));




}


/*紧急通道开始*/
STATUS UrgencyStart(DWORD dwChannelType, DWORD dwMirrEnable) /*程序启动*/
{


/* 判断是否已经进行初始化，如果已经初始化则不
再进行初始化*/
    if(0 == s_sUrgencyPara.dwUrgencyStartflag)
    {
            
        s_sUrgencyPara.dwChannelType=dwChannelType;
        if( BSP_CHANNEL_ETH ==s_sUrgencyPara.dwChannelType)
        {
            s_sUrgencyPara.pEnd=endFindByName(BSP_ETH_NAME,BSP_ETH_NAME_UNIT);
            if(NULL ==s_sUrgencyPara.pEnd)
            {
                logMsg("UrgencyStart cant find ethernet eth\n");
                UrgencyStop();
                return ERROR;
            }
          memcpy( (void*)s_sUrgencyPara.abyEthName,BSP_ETH_NAME,BSP_ETH_NAME_LENGTH);
          s_sUrgencyPara.dwEthUnit=BSP_ETH_NAME_UNIT;
        }
        else if( BSP_CHANNEL_485 ==s_sUrgencyPara.dwChannelType)
        {
            s_sUrgencyPara.pEnd=endFindByName("Peth",0);
            if(NULL ==s_sUrgencyPara.pEnd)
            {
                logMsg("UrgencyStart cant find ethernet Peth\n");
                UrgencyStop();
                return ERROR;
            }
            
        memcpy( (void*)s_sUrgencyPara.abyEthName,"Peth",5);
        s_sUrgencyPara.dwEthUnit=0;
        }
        else
        {
            
            logMsg("UrgencyStart started with a invalid dwChannelType %08x\n",dwChannelType);
            UrgencyStop();
            return ERROR;
        }

        s_sUrgencyPara.semRecBuffInit = semBCreate(SEM_Q_PRIORITY, SEM_FULL);
        if(NULL == s_sUrgencyPara.semRecBuffInit)
        {
            
            logMsg("UrgencyStart cant Create  sem\n");
            UrgencyStop();
            return ERROR;

        }


        s_sUrgencyPara.vmonitorRecvBindCookie = muxBind (s_sUrgencyPara.abyEthName, 
            s_sUrgencyPara.dwEthUnit, (FUNCPTR)UrgencyRecvProcess, NULL, NULL, 
            NULL, MUX_PROTO_SNARF, "Urg", NULL);
        if(NULL ==s_sUrgencyPara.vmonitorRecvBindCookie)
            {
                
                logMsg("Cant bind Urg protocol !\n");
                UrgencyStop();
                return ERROR;
            }
        if(1 == dwMirrEnable)
        {
            
            s_sUrgencyPara.vmonitorRecvBindCookie = muxBind (s_sUrgencyPara.abyEthName, 
                s_sUrgencyPara.dwEthUnit, 
                (FUNCPTR)UrgencySendProcess,NULL, NULL, NULL, MUX_PROTO_SNARF, "Urg", NULL);
            if(NULL ==s_sUrgencyPara.vmonitorRecvBindCookie)
                {
                    
                    logMsg("Cant bind Urg protocol !\n");
                    UrgencyStop();
                    return ERROR;
                }
        }
            s_sUrgencyPara.dwUrgencyStartflag = 1;
    }
    return (OK); 
}

/*紧急通道停止*/
STATUS UrgencyStop(char *ifname, int unit) /*停止监测*/
{
    if(NULL!=s_sUrgencyPara.vmonitorRecvBindCookie)
    {
        if(muxUnbind(s_sUrgencyPara.vmonitorRecvBindCookie, MUX_PROTO_SNARF, (FUNCPTR)UrgencyRecvProcess) != OK)
            {
                logMsg("monitorRecvProcess unBind err!\n");
                return ERROR;
            }
        
    }
    if(NULL != s_sUrgencyPara.vmonitorSendBindCookie)
    {
        
        if(muxUnbind(s_sUrgencyPara.vmonitorSendBindCookie, MUX_PROTO_OUTPUT, (FUNCPTR)UrgencySendProcess)!=OK)
            {
                logMsg("monitorSendBindCookie unBind err!\n");
                return ERROR;
            }
    }
    if(NULL !=s_sUrgencyPara.semRecBuffInit)
    {
            semDelete(s_sUrgencyPara.semRecBuffInit);
    }

    s_sUrgencyPara.dwUrgencyStartflag=0;


    urgencyInit();




    return (OK);
}


/*
 * 82525 发包函数
 -----------------------------------
    input:
        pbyDataBuffer:要发送的数据包
        DWORD:包长
    output:
        VOID
    return:
        SYS_OK
        SYS_ERROR
*/


SDWORD BSP_UrgencySend(BYTE *pbyDataBuffer,DWORD dwLength)
{
    M_BLK_ID pMblk;
	BYTE * dataa=NULL;

    if ( (pMblk = netTupleGet(s_sUrgencyPara.pEnd->pNetPool, 1514, M_DONTWAIT, MT_DATA, FALSE)) == NULL)
    {
        perror("pMblk");
        return(ERROR);
    }

	dataa=(BYTE *)(pMblk->mBlkHdr.mData);

	if(128 > *pbyDataBuffer)
	{
        UrgencyMACAdd[5]= *pbyDataBuffer;
        memcpy((void *)(&dataa[0]), (void *)UrgencyMACAdd, 6);
        memcpy((void *)(&dataa[6]), (void *)UrgencyMACAdd, 6);
	}
	else
	{
		MulMACAdd[5]= (*pbyDataBuffer - 127);
	    memcpy((void *)(&dataa[0]), (void *)MulMACAdd, 6);
	    memcpy((void *)(&dataa[6]), (void *)MulMACAdd, 6);
	}

    memcpy((void *)(&dataa[14]), (void *)pbyDataBuffer, dwLength);
    dataa[11]=pbyDataBuffer[5];
    dataa[12]=0x88;
    dataa[13]=0x88;
    dwLength+=14;
    
    pMblk->mBlkHdr.mLen = dwLength;
    pMblk->mBlkPktHdr.len = pMblk->mBlkHdr.mLen;
    /*pMblk->mBlkHdr.mData;*/
    /*memcpy((void *)(pMblk->mBlkHdr.mData+14), (void *)pbyDataBuffer, (dwLength-14));*/
    if(muxSend(s_sUrgencyPara.vmonitorRecvBindCookie, pMblk) != OK)
    {
       perror("muxSend"); 
       netMblkClChainFree(pMblk);
       return (ERROR);
    }
    s_sUrgencyPara.dwSendCount++;

    return OK;
}
 


STATUS urgencySendTest(DWORD dwNo, BYTE Dest)
{
  BYTE * testData=(DWORD *)malloc(0x2000);
  int i;
  for (i = 200; i < 256; i ++)
  {
    testData[0]=Dest;
    dwNo = 1;
    while(dwNo)
    {
        BSP_UrgencySend( (unsigned char *)(testData),1400);
        dwNo--;
    }
  }
  free(testData);
}

BSP_ReceiveUrgentFrame(DWORD dwLength,BYTE* byBuffer)
{
	byBuffer[0]=9;
	byBuffer[5]=10;
	BSP_UrgencySend( (unsigned char *)(byBuffer),1400);
}

