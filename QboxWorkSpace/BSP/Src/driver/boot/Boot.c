/******************************************************************************


******************************************************************************/
#include "BSPinclude.h"
#include "config.h"


#define ICS307_OTHER_VAL(x)	((unsigned long)(x & 0x001F) << 19)		/*C1 C0 TTL F1 F0*/
#define ICS307_OD_VAL(x)	((unsigned long)(x & 0x0007) << 16)		/*S2-S0*/
#define	ICS307_VDW_VAL(x)	((unsigned long)(x & 0x01FF) << 7)		/*V8-V0*/
#define ICS307_RDW_VAL(x)	((unsigned long)(x & 0x007F))			/*R6-R0*/




/*
 * У��ͼ���
 -----------------------------------
    input:
        dwAddr:Ҫ�������ʼ��ַ
        dwLen:Ҫ����ĳ���
    output:
        VOID
    return:
        У���
*/

LOCAL SDWORD s_dwFeedDogCnt = 0;
LOCAL SDWORD s_dwFeedDogCntDis = 0;
LOCAL SDWORD s_dwSoftBackCnt = 0;
LOCAL BOOT_PARAM_DATA *sGlobaSysData=(BOOT_PARAM_DATA *)0x2000;
LOCAL SDWORD BootSoftWareCheck(BYTE* pbyBuffer, BYTE *byFileType,BYTE *byFileNo);
VOID initDog (void);


/*��λ����
-----------------------------------
	input:
		resetType:��λ����01:�临λ��02:�ȸ�λ
	output:
    		NA
	return:
		VOID
*/
VOID BSP_Reset(BYTE byResetType)
{
    /*��λǰ��Ҫ����*/
    /*�ر���̫��,�Լ�����ʹ��DMA���籣�Ա��ⲻ�ص��鷳*/
    /*����BSP ��λ�ӿ�*/

	sGlobaSysData->dwHWReset = RESET_SW;
	BSP_DisableHardDog();
	reboot((SDWORD) 0);
	#if 0
	if(2==byResetType)
		{
			sGlobaSysData->dwHWReset = RESET_SW;
			BSP_DisableHardDog();
			reboot((SDWORD) 0);
		}
	else if(1==byResetType)
		{
			sGlobaSysData->dwHWReset = RESET_HW;
			reboot((SDWORD) 0);
		}
	#endif

}

/*�������״̬
-----------------------------------
	input:
		byDebug:01:�������״̬��00:�˳�����״̬
	output:
    		NA
	return:
		VOID
*/
VOID BSP_Debug(BYTE byDebug)
{
	if(1==byDebug)
		{
			sGlobaSysData->dwVxworksDebuger=BSP_VXWORKS_DEBUG;
		}
	else
		{
			sGlobaSysData->dwVxworksDebuger=0;
		}
}

/*��� FPGA
---------------------------------------
    input:
    	 no: FPGA ���01��04 ��FPGA,05-08 ����FPGA
    return:
        OK ---------- ��ȡ
        ERROR-------- ����
*/
SDWORD BSP_GetFPGAStatus(DWORD dwNo)
{
	BYTE   byFileType = 0;
	BYTE   byFileNo = 0;
	SWORD  swResult =0 ;
	if(dwNo>8)
	{
		return ERROR;
	}
	switch(dwNo)
	{
		case 1:
			swResult=BootSoftWareCheck((BYTE*)BSP_MAINLOGSOFT1,&byFileType,&byFileNo);
			if(byFileType!=2 || byFileNo !=1)
				{
				return ERROR;
				}
			break;
			
		case 2:
			swResult=BootSoftWareCheck((BYTE*)BSP_MAINLOGSOFT2,&byFileType,&byFileNo);
			if(byFileType!=2 || byFileNo !=2)
				{
				return ERROR;
				}
			
			break;

		case 3:
			swResult=BootSoftWareCheck((BYTE*)BSP_MAINLOGSOFT3,&byFileType,&byFileNo);
			if(byFileType!=2 || byFileNo !=3)
				{
				return ERROR;
				}
			
			break;

		case 4:
			swResult=BootSoftWareCheck((BYTE*)BSP_MAINLOGSOFT4,&byFileType,&byFileNo);
			if(byFileType!=2 || byFileNo !=4)
				{
				return ERROR;
				}
			
			break;

		case 5:
			swResult=BootSoftWareCheck((BYTE*)BSP_BACKLOGSOFT1,&byFileType,&byFileNo);
			if(byFileType!=2 || byFileNo !=1)
				{
				return ERROR;
				}
			
			break;

		case 6:
			swResult=BootSoftWareCheck((BYTE*)BSP_BACKLOGSOFT2,&byFileType,&byFileNo);
			if(byFileType!=2 || byFileNo !=2)
				{
				return ERROR;
				}
			
			break;

		case 7:
			swResult=BootSoftWareCheck((BYTE*)BSP_BACKLOGSOFT3,&byFileType,&byFileNo);
			if(byFileType!=2 || byFileNo !=3)
				{
				return ERROR;
				}
			
			break;

		case 8:
			swResult=BootSoftWareCheck((BYTE*)BSP_BACKLOGSOFT4,&byFileType,&byFileNo);
			if(byFileType!=2 || byFileNo !=4)
				{
				return ERROR;
				}
			
			break;
			
		default:
			swResult=ERROR;
			break;

	}
 	
	return swResult;
}




/*��� �������/�������
---------------------------------------
    input:
    	 no: 0 �������1����
    return:
        OK ---------- ��ȷ
        ERROR-------- ����
*/
SDWORD BSP_GetMainSoftStatus(DWORD dwNo)
{
	BYTE   byFileType = 0;
	BYTE   byFileNo = 0;
	SWORD  swResult = OK ;
	if(1 == dwNo)
	{
 		swResult=BootSoftWareCheck((BYTE *)BSP_MAINSOFT,&byFileType,&byFileNo);
	}
	else if(2 == dwNo)
	{
		swResult=BootSoftWareCheck((BYTE *)BSP_BACKSOFT,&byFileType,&byFileNo);
	}
	else
	{
		swResult = ERROR;
	}
	return swResult;
}


/*��ȡ��ǰ״̬
---------------------------------------
    input:
    	 VIOD
    return:
        OK ---------- ��ȷ
        ERROR-------- ����
*/
VOID BSP_GetCurStatus(VOID)
{
	printf("\n");
	printf( "sGlobaSysData->dwBKResult: 		%08x \n",sGlobaSysData->dwBKResult);
	printf( "sGlobaSysData->dwBoardSlot;		%08x \n",sGlobaSysData->dwBoardSlot);	  
	printf( "sGlobaSysData->dwBoardType;		%08x \n",sGlobaSysData->dwBoardType);	  
	printf( "sGlobaSysData->dwMinResult;		%08x \n",sGlobaSysData->dwMinResult);	  
	printf( "sGlobaSysData->dwResetCont;		%08x \n",sGlobaSysData->dwResetCont);	  
	printf( "sGlobaSysData->dwRsetType; 		%08x \n",sGlobaSysData->dwRsetType);	  
	printf( "sGlobaSysData->dwSoftState;		%08x \n",sGlobaSysData->dwSoftState);	  
	printf( "sGlobaSysData->dwVxworksDebuger;	%08x \n",sGlobaSysData->dwVxworksDebuger);
	printf("\n");
}




/*��� ��Сϵͳ
---------------------------------------
    return:
        OK ---------- ��ȷ
        ERROR-------- ����
*/

SDWORD BSP_GetMiniSystemStatus(VOID)
{
		BYTE   byFileType = 0;
		BYTE   byFileNo = 0;
		SWORD  swResult =0 ;
		swResult=BootSoftWareCheck((BYTE*)BSP_MINSOFT,&byFileType,&byFileNo);
		return swResult;
}


DWORD BSPCheckSum(DWORD *dwAddr,DWORD dwLen)
{

    DWORD   dwNleft = dwLen;
    DWORD   dwSum = 0;
    DWORD   *dwW = dwAddr;

    while ( dwNleft > 3 ) 
    {
        dwSum += *dwW++;
        dwNleft -= 4;
    }

    return(dwSum);


}
/* ����ָ����ַ�����*/
SDWORD BSPLoadSoft(DWORD dwBaseAdd)
{
    DWORD   dwSum1 = 0;

    DWORD   dwFileLength = FILE_LEN_VALUE(dwBaseAdd);
    DWORD   dwFileStart = *((DWORD *)(dwBaseAdd+FILE_OFF))+dwBaseAdd;


	/*if(OK==inflate((BYTE*)dwFileStart, (BYTE*)RAM_LOW_ADRS, dwFileLength))*/
	
	LedRunStateChg(1,1);
	LedAlarmStateChg(1,1);
	if(OK == inflate((BYTE*)dwFileStart, (BYTE*)RAM_LOW_ADRS, dwFileLength))
    {
        intLock(); 
        ((FUNCPTR)RAM_LOW_ADRS)();
        
    }
    else
    {
        return INFLATE_ERROR;
    }

}


void CpLDDogClose()
{
	/* ��λCPLD*/
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,BSP_CPLD_RESET);
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_CPLD_RESET);
	/* CPLD ���ر�*/
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_CPLD_DOG_OPEN);
	BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_CPLD_DOG_OPEN);


}


void CpLDDogOpen()
{
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_CPLD_DOG_OPEN);
	BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,BSP_CPLD_DOG_OPEN);
}


/* BSP �Զ�����*/
void BSPBooter()
{
    SDWORD dwBootRseult = 0;
	BYTE   byFileType = 0;
	BYTE   byFileNo = 0;
	SWORD  swResult =0 ;
        

	/* �ȹر�CPLD ��*/
	CpLDDogClose();
		
	/*���õ����ʶ*/
	sGlobaSysData->dwHWReset = BSP_HW_RESET;
				


	/* �������״̬*/
	if(BSP_VXWORKS_DEBUG == sGlobaSysData->dwVxworksDebuger )
	{
		
		sGlobaSysData->dwSoftState = 0;
		return ;
	}
    
	printf ("\nsGlobaSysData->dwResetCont = %d\n",sGlobaSysData->dwResetCont);
    if(sGlobaSysData->dwResetCont<=3)
    {
		swResult = BootSoftWareCheck((BYTE *)BSP_MAINSOFT,&byFileType,&byFileNo);
		
		printf ("\n 1 swResult:%08x\n",swResult);
		if(OK == swResult)
        {
                sGlobaSysData->dwResetCont+=1;
				sGlobaSysData->dwSoftState = BSP_SOFT_MAINSOFT;
				/* CPLD ��OPEN*/
				CpLDDogOpen();
				printf ("\n Start Load soft !\n");
                sGlobaSysData->dwMinResult=BSPLoadSoft(BSP_MAINSOFT);
        }

		swResult = BootSoftWareCheck((BYTE *)BSP_BACKSOFT,&byFileType,&byFileNo);

		printf ("\n 2 swResult:%08x\n",swResult);
        if(OK == swResult)
        {
                sGlobaSysData->dwResetCont+=1;
				sGlobaSysData->dwSoftState = BSP_SOFT_MAINSOFT;	
				/* CPLD ��OPEN*/
				CpLDDogOpen();
				printf ("\n Start Load soft !\n");
                sGlobaSysData->dwBKResult=BSPLoadSoft(BSP_BACKSOFT);
                
        }
    }
    
    sGlobaSysData->dwResetCont=0;
    
    /* ������Сϵͳ*/
	
	swResult = BootSoftWareCheck((BYTE *)BSP_MINSOFT,&byFileType,&byFileNo);

    if(OK == swResult)
    {
			sGlobaSysData->dwSoftState = BSP_SOFT_MINSYS;
			dwBootRseult=BSPLoadSoft(BSP_MINSOFT);
    }
		sGlobaSysData->dwSoftState = 0;
		sGlobaSysData->dwVxworksDebuger=BSP_VXWORKS_DEBUG;

}

/*
 * ιӲ���� ����
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/
VOID BSP_FeedHardDog( VOID )
{
    
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,BSP_DOG_FEED_BIO);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,BSP_DOG_FEED_BIO);
}

/*
 * ʹ�� Ӳ�����Ź�
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/

VOID BSP_EnableHardDog( VOID )
{
    s_dwFeedDogCntDis = 0;
    /*�͵�ƽʹ��Ӳ����*/
	
	s_dwFeedDogCnt = BSP_SOFT_FEED_TIME ;
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,BSP_DOG_EN_BIO);
}


VOID BSP_ShowDog()
{
	printf("\ns_dwFeedDogCntDis %08x \n",s_dwFeedDogCntDis);
	printf("\ns_dwFeedDogCnt %08x \n",s_dwFeedDogCnt);	

}

/*
 * ��ֹ Ӳ�����Ź�
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/
VOID BSP_DisableHardDog( VOID )
{
    s_dwFeedDogCntDis = 1;
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_CPLD_DOG_OPEN);
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,BSP_DOG_EN_BIO);
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_CPLD_DOG_OPEN);
	
}



LOCAL VOID DogHTask(VOID)
{
    while(1)
    {
        if( --s_dwFeedDogCnt >0  || s_dwFeedDogCntDis)
        {
        BSP_FeedHardDog();
        }
        taskDelay(BSP_HARD_FEED_TIME);
    }

}

LOCAL VOID DogLTask(VOID)
{
    SDWORD asdwTaskId[BSP_TASK_CUNT];
    DWORD dwTaskNum;
    DWORD dwTempLoop;
    DWORD i = 0;
    bzero((void*)asdwTaskId, sizeof(asdwTaskId));

    /* һ����ѭ�� */
    while(1)
    {
        dwTaskNum=taskIdListGet(asdwTaskId,BSP_TASK_CUNT);
        for(dwTempLoop=0;dwTempLoop<dwTaskNum;dwTempLoop++)
        {
            if(taskIsSuspended(asdwTaskId[dwTempLoop]))
            {
                dwTempLoop=BSP_TASK_CUNT;
                break;
            }
        }
        if(dwTempLoop != BSP_TASK_CUNT)
        {
        s_dwFeedDogCnt = BSP_SOFT_FEED_TIME ;
        }
		else
		{
		s_dwFeedDogCnt = BSP_SOFT_FEED_TIME ;
		BSP_Reset(2);
		}

        for(i = 0; i < 60; i++)
        {
    		taskDelay(100);
    		s_dwSoftBackCnt++;
    		if(1800 <= s_dwSoftBackCnt)
    		{
    			s_dwSoftBackCnt=0;
                #ifndef BOOTROM
                    /*BSP_SoftBackUP();*/
                #ifdef BOARD_CS
                    printf("\n Start copy file !!\n");
    				taskLock();
                    cp("/ram0/*.log","/ram1");
    				taskUnlock();
    				taskLock();				
                    cp("/ram0/*.bin","/ram1");				
    				taskUnlock();
    				xcopy("/ram1","/tffs0");
                    printf("\n End copy file !!\n");
                #endif
                #endif
                
    		}
        }
    }

}

void BSP_SaveFile(void)
{
    s_dwSoftBackCnt = 1800;
}

void testCopy()
{
    s_dwSoftBackCnt=30;
}

void testShow()
{
    printf("\n s_dwSoftBackCnt : %d !!\n",s_dwSoftBackCnt);
}

VOID initDog (void)
{
    DWORD dwTempState=0;
    /*IO ���ܳ�ʼ��*/

    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,BSP_DOG_EN_BIO);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,BSP_DOG_FEED_BIO);
	/*

	*/


    CpLDDogOpen();
    /*���������*/
    BSP_EnableHardDog();
    taskSpawn("DogH", BSP_DOG_TASKLEV_H, 0,1024, (FUNCPTR)DogHTask, 0, 0,0, 0, 0, 0, 0, 0, 0, 0);
    taskSpawn("DogL", BSP_DOG_TASKLEV_L, 0,1024*8, (FUNCPTR)DogLTask, 0, 0,0, 0, 0, 0, 0, 0, 0, 0);

}


VOID BSP_Reset_PCIE (void)
{

    /*IO ���ܳ�ʼ��*/

    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,BSP_R_PCIE);

    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_R_PCIE);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_R_PCIE);
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_R_PCIE);
}

VOID BSP_Reset_FPGA (void)
{

    /*IO ���ܳ�ʼ��*/
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,BSP_R_FPGA);



    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_R_FPGA);
    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_R_FPGA);
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_R_FPGA);

}



/*
 * FLASH д���� PC14 �Ϳ�д
-----------------------------------
    input:
        dwWriteEnable: 1: ����FLASH д��0 ������FLASH д
    output:
        VOID
    return:
        VOID
*/

VOID BSP_FlashWriteEnable( DWORD dwWriteEnable )
{


	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,14);

	if(1==dwWriteEnable)
	{
	    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,14);

	}
	if(0==dwWriteEnable)
	{
		

	    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,14);	
	}


		
    return ;

}

/*
 * ��ȡpcb �汾���汾��ʽ��V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:�汾��
    return:
        VOID
*/
VOID BSP_GetPcbVer( BYTE *pbyVer )
{
    BYTE byTempBT[3] = {0,0,0};

    if(NULL==pbyVer)
    {
        return ;
    }
    if (OK == I2cReadCpld(byTempBT,3))
	{

	 pbyVer[0]=byTempBT[1]&0x0F;
	 pbyVer[1]=byTempBT[1]&0xF0>>4;
	 pbyVer[2]='\0';
	 return ;

	}
	 else
	{
	 pbyVer[0]=0xff;
	 pbyVer[1]='\0';
	 pbyVer[2]='\0';
	 return ;
	}

}

/*
��ȡ�����λ��Ϣ
 -----------------------------------
     input:
         VOID:
     output:
         VOID:
     return:
         SYS_OK
         SYS_ERROR
         ����: �����λ��Ϣ
 */
SDWORD BSP_BoardSolt(VOID)

{
    BYTE byTempBT[3] = {0,0,0};
   /* if (OK == I2cRead(0,BSP_EPM3064,BSP_CPLD_ONLINE,&byTempBT))*/
/*
	if(sGlobaSysData->dwBoardSlot !=0)
		{
		return sGlobaSysData->dwBoardSlot;
		}
	*/	
   
   if (OK == I2cReadCpld(byTempBT,3))

        {
			if(0==(byTempBT[2]&(0x7F)))
			{

			sGlobaSysData->dwBoardSlot=9;
			return 9;
			
			}
			else
			{
			byTempBT[2]= (byTempBT[2]&(0x7F));
			
			sGlobaSysData->dwBoardSlot=byTempBT[2];
			return byTempBT[2];
			}
        }
    else
        {
            return SYS_ERROR;
        }
    
    
}


/*
 * ��ȡ������ID��
 * ���ذ�����id��2:SD��3:SP��1:HD��
 *  0:SSC FF:����
 -----------------------------------
	 return:
		 ������ID
 */
BYTE BSP_GetBoardTypeId( VOID )
{
	 BYTE byTempBT[3];
	/* if (OK == I2cRead(0,BSP_EPM3064,BSP_CPLD_ONLINE,&byTempBT))*/
	if (OK ==	 I2cReadCpld(byTempBT,3))
	
		 {
			 sGlobaSysData->dwBoardType=byTempBT[0];
			 return byTempBT[0];
		 }
	 else
		 {
			 return 0xFF;
		 }

}


/*
�������ĺϷ��ԣ�
�������: �����ַ
�������: ������ͣ������š�

*/

LOCAL SDWORD BootSoftWareCheck(BYTE* pbyBuffer, BYTE *byFileType,BYTE *byFileNo)
{
	DWORD	dwSum1 = 0;
	DWORD	dwSum2 = FILE_SUM_VALUE(pbyBuffer);
	DWORD	dwFileLength = FILE_LEN_VALUE(pbyBuffer);
	DWORD	dwFileType = FILE_FLG_VALUE(pbyBuffer);
	DWORD 	dwLen = dwFileLength + FILE_OFF_VALUE(pbyBuffer);
    DWORD   dwFileFlg =0;
    BYTE    byBordType =0;

	while(dwLen%4)
	{
		dwLen ++;
	}
	dwFileFlg = (dwFileType&0xFF000000) >>16;
	byBordType = (dwFileType&0x00FF0000) >>16;

	if( (byBordType != BSP_GetBoardTypeId()) &&( byBordType != 0xFF))
	{
		
		/*printf ("\n BootSoftWareCheck byBordType:%08x BSP_GetBoardTypeId 08x\n",byBordType,BSP_GetBoardTypeId());*/
		return FILE_TYPE_ERROR;
	}

	if(dwFileFlg!=0x4600)
	{

		return FILE_TYPE_ERROR;
	}


	*byFileType = (dwFileType&0x000000FF);
	*byFileNo = (dwFileType&0x0000FF00)>>8;

	/* ���У�鳤��*/
	dwSum1=BSPCheckSum((DWORD *) (FILE_CHECKSUM_START(pbyBuffer)),dwLen-4);
	if(dwSum1 != dwSum2)
	{

		/*printf ("\n BootSoftWareCheck dwSum1 %08x dwSum2 %08x \n",dwSum1,dwSum2);*/
		return CHECK_SUM_ERROR;
	}

	return OK;

}




VOID BSP_StopAllTask(DWORD dwStopRange)
{
    SDWORD asdwTaskId[BSP_TASK_CUNT];
    DWORD dwTaskNum;
    DWORD dwTempLoop;
    SDWORD Priority;

    bzero((void*)asdwTaskId, sizeof(asdwTaskId));

		if(dwStopRange==0||dwStopRange > 255)
		{
			dwStopRange=99;
		}

	BSP_DisableHardDog();
        dwTaskNum=taskIdListGet(asdwTaskId,BSP_TASK_CUNT);
		
        for(dwTempLoop=0;dwTempLoop<dwTaskNum;dwTempLoop++)
        {
			taskPriorityGet(asdwTaskId[dwTempLoop],&Priority);
			if(Priority > dwStopRange)
				{
					taskSuspend(asdwTaskId[dwTempLoop]);
				}
			
        }
       

}


VOID BSP_RunAllTask()
{
    SDWORD asdwTaskId[BSP_TASK_CUNT];
    DWORD dwTaskNum;
    DWORD dwTempLoop;
    SDWORD Priority;

    bzero((void*)asdwTaskId, sizeof(asdwTaskId));
    BSP_EnableHardDog();
    dwTaskNum=taskIdListGet(asdwTaskId,BSP_TASK_CUNT);

    for(dwTempLoop=0;dwTempLoop<dwTaskNum;dwTempLoop++)
    {
	taskResume(asdwTaskId[dwTempLoop]);
    }
       

}

/******************************************************************************
*
* sysNvRamGet - get the contents of non-volatile RAM
*
* This routine copies the contents of non-volatile memory into a specified
* string.  The string is terminated with an EOS.
*
* NOTE: This routine has no effect, since there is no non-volatile RAM.
*
* RETURNS: ERROR, always.
*
* SEE ALSO: sysNvRamSet()
*/

STATUS sysNvRamGet
    (
    char *string,    /* where to copy non-volatile RAM    */
    int strLen,      /* maximum number of bytes to copy   */
    int offset       /* byte offset into non-volatile RAM */
    )
    {
    return (ERROR);
    }

/*******************************************************************************
*
* sysNvRamSet - write to non-volatile RAM
*
* This routine copies a specified string into non-volatile RAM.
*
* NOTE: This routine has no effect, since there is no non-volatile RAM.
*
* RETURNS: ERROR, always.
*
* SEE ALSO: sysNvRamGet()
*/

STATUS sysNvRamSet
    (
    char *string,     /* string to be copied into non-volatile RAM */
    int strLen,       /* maximum number of bytes to copy           */
    int offset        /* byte offset into non-volatile RAM         */
    )
    {
    return (ERROR);
    }

VOID SPIFlashEnable( DWORD dwWriteEnable )
{
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOB,10);
	if(1==dwWriteEnable)
	{
		BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOB,10);

	}
	if(0==dwWriteEnable)
	{
		BSP_AT91F_OR_PIO_SetOutput(BSP_PIOB,10);	
	}
	return ;
}

void C753_Reset( unsigned char dwEnable )
{
	BSP_AT91F_OR_PIO_CfgOutput(0xFFFFF800,2);
	if(1==dwEnable)
	{
		BSP_AT91F_OR_PIO_ClearOutput(0xFFFFF800,2);

	}
	if(0==dwEnable)
	{
		BSP_AT91F_OR_PIO_SetOutput(0xFFFFF800,2); 
	}
	return ;
}

void C772_Reset( unsigned char dwEnable )
{
	BSP_AT91F_OR_PIO_CfgOutput(0xFFFFF800,15);
	if(1==dwEnable)
	{
		BSP_AT91F_OR_PIO_ClearOutput(0xFFFFF800,15);

	}
	if(0==dwEnable)
	{
		BSP_AT91F_OR_PIO_SetOutput(0xFFFFF800,15); 
	}
	return ;
}

void ICS307_SS_OP( unsigned char dwEnable )
{
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,19);
	if(1==dwEnable)
	{
		BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,19);

	}
	if(0==dwEnable)
	{
		BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,19); 
	}
	return ;
}
void ICS307_CLK_OP( unsigned char dwEnable )
{
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,20);
	if(1==dwEnable)
	{
		BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,20);

	}
	if(0==dwEnable)
	{
		BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,20); 
	}
	return ;
}

void ICS307_Data_OP( unsigned char dwEnable )
{
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,21);
	if(1==dwEnable)
	{
		BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,21);

	}
	if(0==dwEnable)
	{
		BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,21); 
	}
	return ;
}

void ICS307_delay(int iN)
{
    BYTE byBase;             /*��ʱѭ������*/
        while(byBase --);
}

void ICS307_WriteBit(BYTE x)
{
	ICS307_CLK_OP(0x1);
	ICS307_delay(1);

	if (x & 0x80) /* the MSB is sent out first*/
		ICS307_Data_OP(0x0);
	else
		ICS307_Data_OP(0x1);

	ICS307_delay(1);
	ICS307_CLK_OP(0x0);
	ICS307_delay(1*15);
	ICS307_CLK_OP(0x1);
	ICS307_delay(1);
}

void ICS307_SendDWORD(DWORD dwData)
{
	BYTE val=0;
	int i;

	val = (BYTE)(dwData >> 16);
	for(i = 0; i < 8; i++)
	{
		ICS307_WriteBit(val);
		val <<= 1;
	}
	/*Byte 2*/
	val = (BYTE)(dwData >> 8);
	for(i = 0; i < 8; i++)
	{
		ICS307_WriteBit(val);
		val <<= 1;
	}
	/*Byte 1*/
	val = (BYTE)dwData;
	for(i = 0; i < 8; i++)
	{
		ICS307_WriteBit(val);
		val <<= 1;
	}

	ICS307_Data_OP(0x0);/*release SDA*/
}

void ICS307_SendByte(BYTE data)
{
	int i;

	for(i=0;i<8;i++)
    {
		ICS307_WriteBit(data);
		data<<=1;
    }

	ICS307_Data_OP(0x0);/*release SDA*/
}




void ICS307_config(unsigned long val)
{

	if(val==0)
	{
 		val = ICS307_OTHER_VAL(0x06) | ICS307_OD_VAL(0x04) | ICS307_VDW_VAL(0x39) | ICS307_RDW_VAL(0x02);
	}


	

	/*0x234808*/
	ICS307_SS_OP(0x1);
	ICS307_SendDWORD(val);
	ICS307_SS_OP(0x0);
}







	
