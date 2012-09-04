/******************************************************************************


******************************************************************************/

#include <semLib.h>
#include <logLib.h>
#include <cacheLib.h>

#include "sys_types.h"
#include "SpiDev_t.h"
#include "BSPinclude.h"

#define WREN 		0x06 /*дʹ��*/
#define WRDI 		0x04 /*д��ʹ��*/
#define RDID 		0x9f /*��ID ��*/
#define RDSR 		0x05 /*��״̬�Ĵ���*/
#define WRSR 		0x01 /*д״̬�Ĵ���*/
#define READPAGE 	0x03 /*������*/
#define FASR_READ 	0x0b /*���ٶ�*/
#define PP			0x02 /*���һҳ����*/
#define SE			0xd8 /*��������*/
#define BE			0xc7 /*Bulk ����*/
#define DP			0xb9 /*���˯��*/
#define RES			0xab /*��˯��״̬����*/

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

/*SPI��������*/
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
//����SPI��
//input :  bySpiPortNum  SPI�˿ں�Ϊ 1 ~ 4
//output:  VOID
//return:  OK            ��ȷ
//         ERROR         ����
*/
SDWORD CS_SpiOpen(BYTE bySpiPortNum)
{
    volatile DWORD dwSpiSr;
    volatile DWORD dwSpiCsr0;
    volatile DWORD dwSpiMr;

    SDWORD semStatus;
    
    /*�ж϶˿ںź�����*/
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
    
    /*��Ƕ˿��Ѿ���*/
    sSpiDev.byIsSpiPortOpen[bySpiPortNum - 1] = OPEN;

    semGive(sSpiDev.semIsSpiUsing);
    
    /*��������ͬ���ź�*/
    sSpiDev.semIsCmdComplete = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY); 

    if(NULL == sSpiDev.semIsCmdComplete)
    {
        logMsg("semBCreate ERROR", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }
    
    //logMsg("SpiOpen OK\n", 0, 0, 0, 0, 0, 0);
    
    /*����IO�˿�*/
    SpiPioConfig(bySpiPortNum);
    
    dwSpiSr = SPI_SR;
	//logMsg("SPI_SR = %d\n", dwSpiSr, 0, 0, 0, 0, 0);

    /*��������ʱ��*/
    PMC_PCER = (DWORD)(0x1 << SPI_ID);
    /*��λSPI*/
    SPI_CR = SPI_SWRST;

    /*�趨SPIģʽ*/
    SPI_MR = SPI_MSTR | SPI_MODFDIS | SPI_PCS;

    dwSpiMr = SPI_MR;
    //logMsg("spiMr = %d\n", dwSpiMr, 0, 0, 0, 0, 0);

    /*�رս���,����*/
    SPI_PTCR = PDC_RXTDIS | PDC_TXTDIS;

    /*ʹ��SPI*/
    SPI_CR = SPI_SPIEN;
    
    /*�ر�����ʱ��*/
    PMC_PCDR = (DWORD)(1 << SPI_ID);
    /*�ر�SPI���ж�*/
    SPI_IDR = 0xFF;
    
    /*����ѡ��˿ڲ�����*/    
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
����IO��
*/
LOCAL SDWORD SpiPioConfig(BYTE bySpiPortNum)
{
    DWORD dwPinMask = 0;

    /*�ж϶˿ںź�����*/
    if(bySpiPortNum > SPI_MAX_NUM)
    {
        logMsg("SpiPortNum error", 0, 0, 0, 0, 0, 0);
        return ERROR;
    }

    dwPinMask = PIN_SPI_MASK | (1 << (bySpiPortNum + 2));       /*��ӦIO��*/
    
    PIOA_IDR = PIN_SPI_MASK | dwPinMask;                      /*�رն�ӦIO���ж�*/

    /*PIOA_PPUER = PIN_SPI_MASK | dwPinMask;*/

    PIOA_ASR = PIN_SPI_MASK | dwPinMask;                      /*IO�ڶ�Ӧ��Χ�豸A*/

    PIOA_PDR = PIN_SPI_MASK | dwPinMask;                      /*ʹ��IO��*/

    return OK;
}

/*
//�ر�SPI��
//input :  bySpiPortNum  SPI�˿ں�Ϊ 1 ~ 4
//output:  VOID
//return:  OK            ��ȷ
//         ERROR         ����
*/
SDWORD CS_SpiClose(BYTE bySpiPortNum)
{
    SDWORD semStatus;
    
    /*�ж��������*/
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
    
    /*ɾ���˿ڴ򿪱�־*/
    sSpiDev.byIsSpiPortOpen[bySpiPortNum - 1] = CLOSE;

    semGive(sSpiDev.semIsSpiUsing);

    /*ɾ������ͬ���ź�*/
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

/*SPI�����
//input :  bySpiPortNum  SPI�˿ں�Ϊ 0 ~ 3
//         pbyCmd        ������
//         byCmdSize     �����
//         pbyData       ����
//         wDataSize     ���ݳ���
//
//return:  OK            ��ȷ
//         ERROR         ����
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

    /*��������ʱ��*/
    PMC_PCER = (1 << SPI_ID);
    
    /*�رս��գ�����*/
    SPI_PTCR = PDC_RXTDIS | PDC_TXTDIS;
    
    /*Ƭѡѡ��˿�*/
    dwSpiMr = SPI_MR;
    dwSpiMr |= SPI_PCS;
    dwSpiMr &= ~((1 << (bySpiPortNum-1)) << 16);

    SPI_MR = dwSpiMr;
    
    /*��ʼ��DMA������*/
    SPI_RPR = (DWORD)sSpiCmd.pbyCmd;
    SPI_RCR = sSpiCmd.byCmdSize;
    SPI_TPR = (DWORD)sSpiCmd.pbyCmd;
    SPI_TCR = sSpiCmd.byCmdSize;

    SPI_RNPR = (DWORD)sSpiCmd.pbyData;
    SPI_RNCR = sSpiCmd.wDataSize;
    SPI_TNPR = (DWORD)sSpiCmd.pbyData;
    SPI_TNCR = sSpiCmd.wDataSize;
    
    /*��������,����*/
    SPI_PTCR = PDC_RXTEN | PDC_TXTEN;
	
    SPI_IDR = 0xFF;

    sSpiDev.byCurSpiPortOpen = OPEN;
    
    /*���������ж�*/
    SPI_IER = SPI_RXBUFF;/*SPI_ENDRX;//SPI_RXBUFF;*/
    
    /*�ж������Ƿ�ɹ�*/
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

/*�жϷ������*/
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
    
    /*�ж��Ƿ�Ϊ�����ж�*/
    if(dwSpiSr & SPI_RXBUFF)/*SPI_ENDRX)//SPI_RXBUFF)*/
    {
        /*�رս���,����*/
        SPI_PTCR = PDC_RXTDIS |PDC_TXTDIS;
        /*�ر�ʱ�ӿ�����*/
        
        PMC_PCDR = 1 << SPI_ID;
        /*�رս����ж�*/
        SPI_IDR = SPI_RXBUFF;/*SPI_ENDRX;//SPI_RXBUFF;*/

        //logMsg("semGive\n", 0, 0, 0, 0, 0, 0);
        //logMsg("semIsCmdComplete = 0x%x\n", sSpiDev.semIsCmdComplete, 0, 0, 0, 0, 0);

        /*������������ź���*/
        semGive(sSpiDev.semIsCmdComplete);
    }
}

/*ע���ж�*/
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
    intEnable(byIrqNum);                  /*�����ж�*/
    return OK;
}

/*�ж������Ƿ�ִ��*/
LOCAL SDWORD IsCmdSend(VOID)
{
	SDWORD semStatus;
    //logMsg("wait for inturrupt\n",0, 0, 0, 0, 0, 0);
    //logMsg("semIsCmdComplete = 0x%x\n", sSpiDev.semIsCmdComplete, 0, 0, 0, 0, 0);

    /*�ȴ���������ź�*/
    semStatus = semTake(sSpiDev.semIsCmdComplete, WAIT_FOREVER);//SPICMDINTTIMEOUT);

    //logMsg("inturrupt finish\n",0, 0, 0, 0, 0, 0);

    if(semStatus == ERROR)
    {
        logMsg("semTake error\n", 0, 0, 0, 0, 0, 0);
    }
    
    return semStatus;
}


/*********************************************/
/* ���Ժ��� */

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
	  logMsg("SPI_MR = 0x%x\n", dwStatus, 0, 0, 0, 0, 0);//��Ҫ�鿴PS
	  
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
	/*����Ƭѡ����*/
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	/* ��Ƭѡ*/
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	return;
}

void BSP_SPI_FlashDisable(void)
{
	/*����Ƭѡ����*/
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	/*�ر�Ƭѡ*/
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
	
	/*����Ƭѡ����*/
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	/* ��Ƭѡ*/
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
	/*�ر�Ƭѡ*/
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
	
	/*����Ƭѡ����*/
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
	/* ��Ƭѡ*/
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,BSP_SPI_FLASH_CS);
    if(NULL == pbyId)
    {
        pbyId = (BYTE *)malloc(0x10);
    }
    byData[0] =RDID;
    CS_SpiCmd(M25P16PORT, &byData[0], 1, &byData[1], 3);
	memcpy(pbyId,&byData[1],10);
	/*�ر�Ƭѡ*/
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
	/* ҳ��ַ*/
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
	
	/* ��дʼ��*/
	byData[0] =WREN;
	CS_SpiCmd(M25P16PORT, &byData[0], 1, pbyId, 0);
	/* ��ȡ״̬�Ĵ���*/
	BSP_SPI_GetFlashStatus(&byFlashStatus);
	/* �ж�״̬*/
	if(byFlashStatus == STATUS_OK)
	{
		/* ����FLASH*/
		byData[0] =BE;
		CS_SpiCmd(M25P16PORT, &byData[0], 1, pbyId, 0);
		do
		{
			BSP_SPI_GetFlashStatus(&byFlashStatus);
		}while(byFlashStatus & STATUS_WIP);
		/*дFLASH*/
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
								return FILE_USE_CANCLE;/* �û�ȡ��*/
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
			/* ��������*/
			if (OK!=softUpCallback(&dwpages1,&dwpages1))
			{
				return FILE_USE_CANCLE;/* �û�ȡ��*/
			}
		}
		
		/* �����Ƚ�*/
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
	
	/*�ر�Ƭѡ*/
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
	/* ��������*/
	byData[0] =PP;
	byData[1] =byadd1;
	byData[2] =byadd2;
	byData[3] =byadd3;
	memcpy(pbyId,pbyData,256);

	/* д����*/				
	CS_SpiCmd(M25P16PORT, &byData[0], 4, pbyId, 256);
	
	/*�ر�Ƭѡ*/
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
	/* ��������*/
	byData[0] =READPAGE;
	byData[1] =0;
	byData[2] =0;
	byData[3] =0;



	for(byadd1=0;byadd1<32;byadd1++)
	{
		do
		{
			/* д����*/ 	
			
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
	/*�ر�Ƭѡ*/
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
	
	/*�ر�Ƭѡ*/
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
