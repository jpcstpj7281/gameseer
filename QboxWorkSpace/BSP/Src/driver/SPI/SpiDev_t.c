/******************************************************************************


******************************************************************************/

#include <semLib.h>
#include <logLib.h>
#include <cacheLib.h>

#include "sys_types.h"
#include "SpiDev_t.h"
#include "BSPinclude.h"

#define WREN 		0x06 /*写使能*/
#define WRDI 		0x04 /*写不使能*/
#define RDID 		0x9f /*读ID 号*/
#define RDSR 		0x05 /*读状态寄存器*/
#define WRSR 		0x01 /*写状态寄存器*/
#define READPAGE 	0x03 /*读数据*/
#define FASR_READ 	0x0b /*快速读*/
#define PP			0x02 /*编程一页数据*/
#define SE			0xd8 /*扇区擦除*/
#define BE			0xc7 /*Bulk 擦除*/
#define DP			0xb9 /*深度睡眠*/
#define RES			0xab /*从睡眠状态醒来*/

#define M25P16PORT  0x1


#define STATUS_OK   (BYTE)(~STATUS_WIP&STATUS_WEL)
#define STATUS_WIP  (BYTE)0x1
#define STATUS_WEL  (BYTE)0x2

static STATUS BSP_SPI_GetFlashStatus(BYTE * pbyStatus);
static STATUS BSP_SPI_SetFlashPage(BYTE byadd1,BYTE byadd2,BYTE byadd3,BYTE * pbyData);
static STATUS BSP_SPI_SetFlashReady(void);
static STATUS BSP_SPI_GetFlashPage(BYTE * pbyData, DWORD dwlength);
static STATUS BSP_SPI_SetFlashCmp(BYTE *pbyCmp,BYTE * pbyDataAdd,DWORD dwlength);

LOCAL SPIDEV sSpiDev;

/*SPI驱动创建*/
VOID CS_SpiCreate(VOID)
{
    //logMsg("SpiCreate\n", 0, 0, 0, 0, 0, 0);
    
    sSpiDev.byCurSpiPortOpen    = 0;
    memset(&sSpiDev.byIsSpiPortOpen, SPI_MAX_NUM, 0);
    sSpiDev.psSpiCmd             = NULL;
    sSpiDev.semIsCmdComplete    = NULL;

    sSpiDev.semIsSpiUsing = semBCreate( SEM_Q_PRIORITY, SEM_FULL);
    if(NULL == sSpiDev.semIsSpiUsing)
    {
        logMsg("semBCreate(sSpiDev.semIsSpiUsing)error\n", 0, 0, 0, 0, 0, 0);
        return;
    }

    sSpiDev.semCmdSending = semBCreate( SEM_Q_PRIORITY, SEM_FULL); 
    if(NULL == sSpiDev.semCmdSending)
    {
        logMsg("semBCreate(sSpiDev.semCmdSending)error\n", 0, 0, 0, 0, 0, 0);
        return;
    }
    
    SpiIsrInstall();
}

/*
//开启SPI口
//input :  bySpiPortNum  SPI端口号为 1 ~ 4
//output:  VOID
//return:  OK            正确
//         ERROR         错误
*/
SDWORD CS_SpiOpen(BYTE bySpiPortNum)
{
    volatile DWORD dwSpiSr;
    volatile DWORD dwSpiCsr0;
    volatile DWORD dwSpiMr;

    SDWORD semStatus;
    
    /*判断端口号合理性*/
    if((bySpiPortNum > SPI_MAX_NUM) || (bySpiPortNum < 1))
    {
        logMsg("SpiPortNum error", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }

    semStatus = semTake(sSpiDev.semIsSpiUsing, NO_WAIT);

    if(ERROR == semStatus)
    {
        logMsg("SpiPort %d busy", bySpiPortNum, 0, 0, 0, 0, 0);
        return ERROR;
    }
  
    if(OPEN == sSpiDev.byIsSpiPortOpen[bySpiPortNum - 1])
    {
        semGive(sSpiDev.semIsSpiUsing);
        return OK;
    }    
    
    /*标记端口已经打开*/
    sSpiDev.byIsSpiPortOpen[bySpiPortNum - 1] = OPEN;

    semGive(sSpiDev.semIsSpiUsing);
    
    /*创建接收同步信号*/
    sSpiDev.semIsCmdComplete = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY); 

    if(NULL == sSpiDev.semIsCmdComplete)
    {
        logMsg("semBCreate ERROR", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }
    
    //logMsg("SpiOpen OK\n", 0, 0, 0, 0, 0, 0);
    
    /*配置IO端口*/
    SpiPioConfig(bySpiPortNum);
    
    dwSpiSr = SPI_SR;
	//logMsg("SPI_SR = %d\n", dwSpiSr, 0, 0, 0, 0, 0);

    /*开启外设时钟*/
    PMC_PCER = (DWORD)(0x1 << SPI_ID);
    /*复位SPI*/
    SPI_CR = SPI_SWRST;

    /*设定SPI模式*/
    SPI_MR = SPI_MSTR | SPI_MODFDIS | SPI_PCS;

    dwSpiMr = SPI_MR;
    //logMsg("spiMr = %d\n", dwSpiMr, 0, 0, 0, 0, 0);

    /*关闭接收,发送*/
    SPI_PTCR = PDC_RXTDIS | PDC_TXTDIS;

    /*使能SPI*/
    SPI_CR = SPI_SPIEN;
    
    /*关闭外设时钟*/
    PMC_PCDR = (DWORD)(1 << SPI_ID);
    /*关闭SPI口中断*/
    SPI_IDR = 0xFF;
    
    /*设置选择端口波特率*/    
    switch(bySpiPortNum - 1)
    {
        case 0:
            SPI_CSR0 = (DWORD)CALCULATE_CSR(BOARD_MCK, (5000000));
            break;
        case 1:
            SPI_CSR1 = (DWORD)CALCULATE_CSR(BOARD_MCK, AT45_SPI_CLK);
            break;
        case 2:
            SPI_CSR2 = (DWORD)CALCULATE_CSR(BOARD_MCK, AT45_SPI_CLK);
            break;
        case 3:
            SPI_CSR3 = (DWORD)CALCULATE_CSR(BOARD_MCK, AT45_SPI_CLK);
            break;
        default:
            break;
    }

    dwSpiCsr0 = SPI_CSR0;
    //logMsg("SPI_CS0 = %d\n", dwSpiCsr0, 0, 0, 0, 0, 0);
    
    return OK;
}

/*
配置IO口
*/
LOCAL SDWORD SpiPioConfig(BYTE bySpiPortNum)
{
    DWORD dwPinMask = 0;

    /*判断端口号合理性*/
    if(bySpiPortNum > SPI_MAX_NUM)
    {
        logMsg("SpiPortNum error", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }

    dwPinMask = PIN_SPI_MASK | (1 << (bySpiPortNum + 2));       /*对应IO口*/
    
    PIOA_IDR = PIN_SPI_MASK | dwPinMask;                      /*关闭对应IO口中断*/

    /*PIOA_PPUER = PIN_SPI_MASK | dwPinMask;*/

    PIOA_ASR = PIN_SPI_MASK | dwPinMask;                      /*IO口对应外围设备A*/

    PIOA_PDR = PIN_SPI_MASK | dwPinMask;                      /*使能IO口*/

    return OK;
}

/*
//关闭SPI口
//input :  bySpiPortNum  SPI端口号为 1 ~ 4
//output:  VOID
//return:  OK            正确
//         ERROR         错误
*/
SDWORD CS_SpiClose(BYTE bySpiPortNum)
{
    SDWORD semStatus;
    
    /*判断输入参数*/
    if((bySpiPortNum > SPI_MAX_NUM) || (bySpiPortNum < 1))
    {
        return ERROR;
    }

    semStatus = semTake(sSpiDev.semIsSpiUsing, NO_WAIT);
    
    if(ERROR == semStatus)
    {
        logMsg("SpiPort %d busy", bySpiPortNum, 0, 0, 0, 0, 0);
        return ERROR;
    }

    if(CLOSE == sSpiDev.byIsSpiPortOpen[bySpiPortNum - 1])
    {
        semGive(sSpiDev.semIsSpiUsing);
        return ERROR;
    }
    
    /*删除端口打开标志*/
    sSpiDev.byIsSpiPortOpen[bySpiPortNum - 1] = CLOSE;

    semGive(sSpiDev.semIsSpiUsing);

    /*删除接收同步信号*/
    if(ERROR == semDelete(sSpiDev.semIsCmdComplete))
    {
        logMsg("semDelete error", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }
    
    //logMsg("semDelete Ok\n", 0, 0, 0, 0, 0, 0);
/*
    if(ERROR == semGive(sSpiDev.semIsSpiUsing))
    {
        logMsg("semGive error\n", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }
*/    
    return OK;
}

/*SPI命令发送
//input :  bySpiPortNum  SPI端口号为 0 ~ 3
//         pbyCmd        命令字
//         byCmdSize     命令长度
//         pbyData       数据
//         wDataSize     数据长度
//
//return:  OK            正确
//         ERROR         错误
*/
SDWORD CS_SpiCmd(BYTE bySpiPortNum, BYTE *pbyCmd, BYTE byCmdSize, 
    BYTE *pbyData, WORD wDataSize)
{
    volatile DWORD dwSpiMr;
    volatile DWORD dwSpiSr;
    
    SPICMD sSpiCmd;
    
    assert(NULL != pbyCmd);

    if(OPEN != sSpiDev.byIsSpiPortOpen[bySpiPortNum - 1])
    {
		logMsg("SpiPortOpen error\n", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }

    if(ERROR == semTake(sSpiDev.semCmdSending, SPICMDTIMEOUT))
    {
        logMsg("semTake error\n", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }    
 
    sSpiCmd.pbyCmd    = pbyCmd;
    sSpiCmd.byCmdSize = byCmdSize;
    sSpiCmd.pbyData   = pbyData;
    sSpiCmd.wDataSize = wDataSize;

    /*开启外设时钟*/
    PMC_PCER = (1 << SPI_ID);
    
    /*关闭接收，发送*/
    SPI_PTCR = PDC_RXTDIS | PDC_TXTDIS;
    
    /*片选选择端口*/
    dwSpiMr = SPI_MR;
    dwSpiMr |= SPI_PCS;
    dwSpiMr &= ~((1 << (bySpiPortNum-1)) << 16);

    SPI_MR = dwSpiMr;
    
    /*初始化DMA控制器*/
    SPI_RPR = (DWORD)sSpiCmd.pbyCmd;
    SPI_RCR = sSpiCmd.byCmdSize;
    SPI_TPR = (DWORD)sSpiCmd.pbyCmd;
    SPI_TCR = sSpiCmd.byCmdSize;

    SPI_RNPR = (DWORD)sSpiCmd.pbyData;
    SPI_RNCR = sSpiCmd.wDataSize;
    SPI_TNPR = (DWORD)sSpiCmd.pbyData;
    SPI_TNCR = sSpiCmd.wDataSize;
    
    /*开启接收,发送*/
    SPI_PTCR = PDC_RXTEN | PDC_TXTEN;
	
    SPI_IDR = 0xFF;

    sSpiDev.byCurSpiPortOpen = OPEN;
    
    /*开启接收中断*/
    SPI_IER = SPI_RXBUFF;/*SPI_ENDRX;//SPI_RXBUFF;*/
    
    /*判断命令是否成功*/
    if(ERROR == IsCmdSend())
    {
        logMsg("SpiCmd can't receive", 0, 0, 0, 0, 0, 0);        
    }

    if(ERROR == semGive(sSpiDev.semCmdSending))
    {
        logMsg("semGive sSpiDev.semCmdSending error\n", 0, 0, 0, 0, 0, 0);
    }
    return OK;
}

/*中断服务程序*/
VOID SpiHandler(VOID)
{
    volatile DWORD dwSpiSr;
       
    dwSpiSr = SPI_SR;
	
    //logMsg("SPI interrupe, SPI_SR = 0x%x\n", dwSpiSr, 0, 0, 0, 0, 0);

    //dwSpiSr = SPI_PTSR;    
    //logMsg("SPI interrupe, SPI_PTSR = %d\n", dwSpiSr, 0, 0, 0, 0, 0);

    if(CLOSE == sSpiDev.byCurSpiPortOpen)
    {
        return;
    }
    
    /*判断是否为接收中断*/
    if(dwSpiSr & SPI_RXBUFF)/*SPI_ENDRX)//SPI_RXBUFF)*/
    {
        /*关闭接收,发送*/
        SPI_PTCR = PDC_RXTDIS |PDC_TXTDIS;
        /*关闭时钟控制器*/
        
        PMC_PCDR = 1 << SPI_ID;
        /*关闭接收中断*/
        SPI_IDR = SPI_RXBUFF;/*SPI_ENDRX;//SPI_RXBUFF;*/

        //logMsg("semGive\n", 0, 0, 0, 0, 0, 0);
        //logMsg("semIsCmdComplete = 0x%x\n", sSpiDev.semIsCmdComplete, 0, 0, 0, 0, 0);

        /*发送命令完成信号量*/
        semGive(sSpiDev.semIsCmdComplete);
    }
}

/*注册中断*/
LOCAL SDWORD SpiIsrInstall(VOID)
{
/*    DWORD IntVector;*/
    BYTE   byIrqNum = SPI_ID;
/*    IntVector = INUM2IVEC(irqNum);*/

    if(ERROR == intConnect(byIrqNum, (VOIDFUNCPTR)SpiHandler, 0))
    {
        logMsg("intConnect error", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }
    intEnable(byIrqNum);                  /*开启中断*/
    return OK;
}

/*判断命令是否执行*/
LOCAL SDWORD IsCmdSend(VOID)
{
	SDWORD semStatus;
    //logMsg("wait for inturrupt\n",0, 0, 0, 0, 0, 0);
    //logMsg("semIsCmdComplete = 0x%x\n", sSpiDev.semIsCmdComplete, 0, 0, 0, 0, 0);

    /*等待命令完成信号*/
    semStatus = semTake(sSpiDev.semIsCmdComplete, WAIT_FOREVER);//SPICMDINTTIMEOUT);

    //logMsg("inturrupt finish\n",0, 0, 0, 0, 0, 0);

    if(semStatus == ERROR)
    {
        logMsg("semTake error\n", 0, 0, 0, 0, 0, 0);
    }
    
    return semStatus;
}


/*********************************************/
/* 测试函数 */

#define AT45_PAGE_WRITE_BUF1 4
#define PAGESIZE             264
#define PAGESIZEOFFET        9






void GetSpiStatus(void)
{
	  DWORD dwStatus = 0;
	  
	  dwStatus = PIOA_PSR;
	  logMsg("PIOA_PSR = 0x%x\n", dwStatus, 0, 0, 0, 0, 0);
	  dwStatus = PIOA_OSR;
	  logMsg("PIOA_OSR = 0x%x\n", dwStatus, 0, 0, 0, 0, 0);
	  dwStatus = PIOA_ABSR;
	  logMsg("PIOA_ABSR = 0x%x\n", dwStatus, 0, 0, 0, 0, 0);
	  dwStatus = PMC_PCSR;
	  logMsg("PMC_PCSR = 0x%x\n", dwStatus, 0, 0, 0, 0, 0);
	  dwStatus = PMC_SR;
	  logMsg("PMC_SR = 0x%x\n", dwStatus, 0, 0, 0, 0, 0);
	  dwStatus = SPI_SR;
	  logMsg("SPI_SR = 0x%x\n", dwStatus, 0, 0, 0, 0, 0);
	  dwStatus = SPI_MR;
	  logMsg("SPI_MR = 0x%x\n", dwStatus, 0, 0, 0, 0, 0);//主要查看PS
	  
}

static SEM_ID semSpiLock = 0;
static sdwSPIinit = 0;
/*SPI FLASH*/
void BSP_SPI_Init(void)
{
	if(0==sdwSPIinit)
	{
	CS_SpiCreate();
    CS_SpiOpen(1);
    semSpiLock = semBCreate( SEM_Q_PRIORITY, SEM_FULL);
	sdwSPIinit=1;
	}
}
/**/

void BSP_SPI_FlashEnable(void)
{
	/*调节片选方向*/
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	/* 打开片选*/
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	return;
}

void BSP_SPI_FlashDisable(void)
{
	/*调节片选方向*/
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	/*关闭片选*/
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	return ;
}

void BSP_SPIRead_ID(BYTE *pbyId)
{
    BYTE * byData=NULL;
    BYTE i=0;
    DWORD semStatus = 0;
    DWORD memuse = 0;
    semStatus = semTake(semSpiLock, WAIT_FOREVER);
	
	/*调节片选方向*/
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	/* 打开片选*/
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	byData=cacheDmaMalloc(100);
	
	if(NULL == byData)
    {
		return ;
    }
	
    if(NULL == pbyId)
    {
        pbyId = (BYTE *)cacheDmaMalloc(10);
		printf ("No mem just see id !\n");
		memuse=1;
		if(NULL == pbyId)
			{
				cacheDmaFree(byData);
				return ;
			}
    }
    byData[0] =RDID;
    CS_SpiCmd(M25P16PORT, &byData[0], 1, pbyId, 3);
	cacheInvalidate (DATA_CACHE, pbyId, 3);   
	d(pbyId,10,1);
	d(byData,11,1);
	/*关闭片选*/
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	if(memuse==1)
	{
		cacheDmaFree(pbyId);
	}
	
	cacheDmaFree(byData);
    semGive(semSpiLock);
}

void BSP_SPIRead_Data(BYTE *pbyId)
{
    BYTE byData[100];
    BYTE i;
    DWORD semStatus = 0;
    semStatus = semTake(semSpiLock, WAIT_FOREVER);
	
	/*调节片选方向*/
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	/* 打开片选*/
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
    if(NULL == pbyId)
    {
        pbyId = (BYTE *)malloc(0x10);
    }
    byData[0] =RDID;
    CS_SpiCmd(M25P16PORT, &byData[0], 1, &byData[1], 3);
	memcpy(pbyId,&byData[1],10);
	/*关闭片选*/
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
    semGive(semSpiLock);
}

STATUS BSP_SPIWrite_Data(BYTE *pbyFlashData,DWORD dwlength,SDWORD (*softUpCallback) (DWORD*, DWORD*))
{
	BYTE * byData=NULL;
	BYTE * pbyId=NULL;
	
	BYTE * pbyCmp=NULL;

	BYTE  byFlashStatus=0;
	DWORD semStatus = 0;
	DWORD dwpages = dwlength/256;
	DWORD dwpages1 = 0;
	DWORD dwtemp1 = 0;
	DWORD dwtemp2 = 0;
	SWORD swCmpStatus=0;
	/**/
	BYTE * pbyDataAdd=pbyFlashData;
	/* 页地址*/
	BYTE byadd1=0;
	BYTE byadd2=0;
	if(0 != dwlength%256 )
	{
		dwpages++;	
	}
	dwpages1=dwpages-1;
	semStatus = semTake(semSpiLock, WAIT_FOREVER);
	
	byData=cacheDmaMalloc(10);
	if(NULL == byData)
	{
		
		semGive(semSpiLock);
		return ERROR;
	}
	
	pbyId = (BYTE *)cacheDmaMalloc(10);
	if(NULL == pbyId)
	{
		
		semGive(semSpiLock);
		cacheDmaFree(byData);
		return ERROR;
	
	}
	
	/* 打开写始能*/
	byData[0] =WREN;
	CS_SpiCmd(M25P16PORT, &byData[0], 1, pbyId, 0);
	/* 读取状态寄存器*/
	BSP_SPI_GetFlashStatus(&byFlashStatus);
	/* 判断状态*/
	if(byFlashStatus == STATUS_OK)
	{
		/* 擦除FLASH*/
		byData[0] =BE;
		CS_SpiCmd(M25P16PORT, &byData[0], 1, pbyId, 0);
		do
		{
			BSP_SPI_GetFlashStatus(&byFlashStatus);
		}while(byFlashStatus & STATUS_WIP);
		/*写FLASH*/
		pbyDataAdd = pbyFlashData;
		for(dwtemp1=0;dwtemp1<dwpages;dwtemp1++)
			{
				
				BSP_SPI_SetFlashReady();
				BSP_SPI_SetFlashPage(byadd1,byadd2,0,pbyDataAdd);
				pbyDataAdd+=256;
				byadd2++;
				if(0==byadd2)
				{
						byadd1++;
 						if(softUpCallback != NULL)
						{
							if (OK!=softUpCallback(&dwpages1,&dwtemp1))
							{
								return FILE_USE_CANCLE;/* 用户取消*/
							}
						}
				}
				do
				{
					BSP_SPI_GetFlashStatus(&byFlashStatus);
				}while(byFlashStatus & STATUS_WIP);
				
			}
		
		if(softUpCallback != NULL)
		{
			/* 修正数据*/
			if (OK!=softUpCallback(&dwpages1,&dwpages1))
			{
				return FILE_USE_CANCLE;/* 用户取消*/
			}
		}
		
		/* 读出比较*/
		pbyDataAdd = pbyFlashData;
		pbyCmp=(BYTE *)malloc(dwlength);
		if(NULL==pbyCmp)
		{
			cacheDmaFree(pbyId);
    		cacheDmaFree(byData);
	    	semGive(semSpiLock);
		    return ERROR;

		}

		BSP_SPI_GetFlashPage(pbyCmp,dwlength);
		swCmpStatus=BSP_SPI_SetFlashCmp(pbyCmp,pbyDataAdd,dwlength);
		
	
		if(0 != swCmpStatus)
		{
		cacheDmaFree(pbyId);
		cacheDmaFree(byData);
		free(pbyCmp);
		semGive(semSpiLock);
		return ERROR;
	
		}

		
		
	}

	cacheDmaFree(pbyId);
	cacheDmaFree(byData);
	semGive(semSpiLock);
	return OK;
}



static STATUS BSP_SPI_GetFlashStatus(BYTE * pbyStatus)
{
	BYTE * byData=NULL;
	BYTE * pbyId=NULL;

	byData=cacheDmaMalloc(10);
	if(NULL == byData)
	{
		return ERROR;
	}
	
	pbyId = (BYTE *)cacheDmaMalloc(10);
	if(NULL == pbyId)
	{
		cacheDmaFree(byData);
		return ERROR;
	
	}

	byData[0] =RDSR;
	CS_SpiCmd(M25P16PORT, &byData[0], 1, pbyId, 1);
	if(NULL==pbyStatus)
	{
		printf("the Status %02x \n",pbyId[0]);
	}
	else
	{
	*pbyStatus	=	*pbyId;
	}
	
	/*关闭片选*/
	cacheDmaFree(pbyId);
	cacheDmaFree(byData);
	return OK;
}


static STATUS BSP_SPI_SetFlashPage(BYTE byadd1,BYTE byadd2,BYTE byadd3,BYTE * pbyData)
{
	BYTE * byData=NULL;
	BYTE * pbyId=NULL;

	byData=cacheDmaMalloc(10);
	if(NULL == byData)
	{
		return ERROR;
	}
	
	pbyId = (BYTE *)cacheDmaMalloc(256);
	if(NULL == pbyId)
	{
		cacheDmaFree(byData);
		return ERROR;
	
	}
	/* 复制数据*/
	byData[0] =PP;
	byData[1] =byadd1;
	byData[2] =byadd2;
	byData[3] =byadd3;
	memcpy(pbyId,pbyData,256);

	/* 写数据*/				
	CS_SpiCmd(M25P16PORT, &byData[0], 4, pbyId, 256);
	
	/*关闭片选*/
	cacheDmaFree(pbyId);
	cacheDmaFree(byData);
	return OK;
}

static STATUS BSP_SPI_GetFlashPage(BYTE * pbyData, DWORD dwlength)
{
	BYTE * byData=NULL;
	BYTE * pbyId=NULL;
	
	BYTE * pbtemp=NULL;
	BYTE * pbtemp1=NULL;

	
	BYTE  byadd1=0;
	BYTE  byadd2=0;
	
	DWORD dwpages = dwlength/256;

	if(0 != dwlength%256 )
	{
		dwpages++;	
	}


	byData=cacheDmaMalloc(10);
	if(NULL == byData)
	{
		return ERROR;
	}
	
	pbyId = (BYTE *)cacheDmaMalloc(256);
	if(NULL == pbyId)
	{
		cacheDmaFree(byData);
		return ERROR;
	
	}
	pbtemp = (BYTE *)malloc(0x200000);
	if(NULL == pbtemp)
	{
		cacheDmaFree(byData);
		cacheDmaFree(pbyId);
		return ERROR;
	
	}
	pbtemp1=pbtemp;
	/* 复制数据*/
	byData[0] =READPAGE;
	byData[1] =0;
	byData[2] =0;
	byData[3] =0;



	for(byadd1=0;byadd1<32;byadd1++)
	{
		do
		{
			/* 写数据*/ 	
			
			byData[0] =READPAGE;
			byData[1] =byadd1;
			byData[2] =byadd2;
			byData[3] =0;
			CS_SpiCmd(M25P16PORT, &byData[0], 4, pbyId, 256);
			memcpy(pbtemp,pbyId,256);
			pbtemp+=256;
			byadd2++;
			dwpages--;
		}while( (0!=byadd2)&&(0!=dwpages));
		if(0==dwpages)
		{
		break ;
		}
	}
	memcpy(pbyData,pbtemp1,dwlength);
	/*关闭片选*/
	free(pbtemp1);
	cacheDmaFree(pbyId);
	cacheDmaFree(byData);
	return OK;
}

static STATUS BSP_SPI_SetFlashReady(void)
{
	BYTE * byData=NULL;
	BYTE * pbyId=NULL;

	byData=cacheDmaMalloc(10);
	if(NULL == byData)
	{
		return ERROR;
	}
	
	pbyId = (BYTE *)cacheDmaMalloc(10);
	if(NULL == pbyId)
	{
		cacheDmaFree(byData);
		return ERROR;
	
	}

	byData[0] =WREN;
	CS_SpiCmd(M25P16PORT, &byData[0], 1, pbyId, 0);
	do 
	{
		byData[0] =RDSR;
		CS_SpiCmd(M25P16PORT, &byData[0], 1, pbyId, 1);
	}while(STATUS_OK != pbyId[0]);
	
	/*关闭片选*/
	cacheDmaFree(pbyId);
	cacheDmaFree(byData);
	return OK;
}

static STATUS BSP_SPI_SetFlashCmp(BYTE *pbyCmp,BYTE * pbyDataAdd,DWORD dwlength)
{
	while(dwlength)
	{
		if (*pbyCmp != * pbyDataAdd)
			{
				return ERROR ;
			}
		dwlength--;
		pbyCmp++;
		pbyDataAdd++;
	}

	return OK;
}
