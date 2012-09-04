/******************************************************************************


******************************************************************************/

#include "softWareup.h"

LOCAL SDWORD SoftWareCheck(BYTE* pbyBuffer, DWORD dwLen, BYTE *byFileType,BYTE *byFileNo);
LOCAL SDWORD SoftWareWrite();
LOCAL SDWORD SoftWriteCheck();
LOCAL SDWORD SoftWareBKWrite();

LOCAL struct sSoftWareUp s_sSoftWarePara;

/*
 * 软件升级
-----------------------------------
    input:
        byBuffer            : 数据指针
        dwLen               : 数据长度
        dwType             : 类型 01主机/单板，02FPGA
        dwNo                :dwType 为01 时忽略，02是表示FPGA 的编号
        softUpCallback   : 回调函数，
                                    返回SYS_OK 表示继续升级，
                                    SYS_ERR表示终止升级.
                                    BYTE* 要写入的数据长度，已经写入的数据长度
    output:
        VIOD
    return:
        SYS_OK
        SYS_ERROR
*/

SDWORD  BSP_SoftUpgrade(BYTE* pbyBuffer, DWORD dwLen, DWORD dwType, 
            DWORD dwNo, SDWORD (*softUpCallback) (DWORD*, DWORD*))
{
		BYTE byFileType=0;
		BYTE byFileNo=0;
        SDWORD result=0;
		DWORD  dwLEDState=0;
        BYTE bordType = -1;
        
		dwLEDState=BSP_SysRunLedFlic(BSP_LED_FAST);

		if(dwLen>FILE_LENGTH)
		{
			
			BSP_SysRunLedFlic(dwLEDState);
			return FILE_TOOLARGE_ERROR;
		}
		if(NULL != softUpCallback)
		{
			s_sSoftWarePara.softUpCallback = softUpCallback;
		}

        if(OK!=semTake(s_sSoftWarePara.semRecBuffInit, WAIT_FOREVER))
       	{
			logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
       	}

		result=SoftWareCheck(pbyBuffer,dwLen,&byFileType,&byFileNo);
		
		if (OK!=result)
		{
			if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
			{
			   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
			}

			
			BSP_SysRunLedFlic(dwLEDState);
			return result;
		}


		switch(byFileType)
		{
			/* 主控软件升级*/
			case 1:
				s_sSoftWarePara.pbyDAdd =(BYTE *) BSP_MAINSOFT;
				s_sSoftWarePara.pbyBkDAdd =(BYTE *) BSP_BACKSOFT; 
				if(dwLen>SOFT_LENGTH)
				{
					
					BSP_SysRunLedFlic(dwLEDState);
					if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
					{
					   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
					}
					return FILE_TOOLARGE_ERROR;
				}
				break;
			/* FPGA 升级*/
			case 2:	
				switch (byFileNo)
					{
						case 1:
							s_sSoftWarePara.pbyDAdd =(BYTE *) BSP_MAINLOGSOFT1;
							s_sSoftWarePara.pbyBkDAdd =(BYTE *)BSP_BACKLOGSOFT1;
							if(dwLen>LOGSOFT__LA_LENGTH)
							{
								
								BSP_SysRunLedFlic(dwLEDState);
								if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
								{
								   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
								}
								return FILE_TOOLARGE_ERROR;
							}
							break;
						case 2:
							
							s_sSoftWarePara.pbyDAdd =(BYTE *) BSP_MAINLOGSOFT2;
							s_sSoftWarePara.pbyBkDAdd =(BYTE *)BSP_BACKLOGSOFT2;
							if(dwLen>LOGSOFT__LA_LENGTH)
							{
								
								BSP_SysRunLedFlic(dwLEDState);
								if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
								{
								   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
								}
								return FILE_TOOLARGE_ERROR;
							}							
							break;
						case 3:
							
							s_sSoftWarePara.pbyDAdd =(BYTE *) BSP_MAINLOGSOFT3;
							s_sSoftWarePara.pbyBkDAdd =(BYTE *)BSP_BACKLOGSOFT3; 
							if(dwLen>LOGSOFT__AL_LENGTH)
							{
								
								BSP_SysRunLedFlic(dwLEDState);
								if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
								{
								   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
								}
								return FILE_TOOLARGE_ERROR;
							}							
							break;
						case 4:
							
							s_sSoftWarePara.pbyDAdd =(BYTE *) BSP_MAINLOGSOFT4;
							s_sSoftWarePara.pbyBkDAdd =(BYTE *)BSP_BACKLOGSOFT4; 
							if(dwLen>LOGSOFT__AL_LENGTH)
							{
								
								BSP_SysRunLedFlic(dwLEDState);
								if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
								{
								   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
								}
								return FILE_TOOLARGE_ERROR;
							}							
							break;
						case 5:
					#if defined(BOARD_OP) || defined(BOARD_MC)
							bordType = BSP_GetBoardTypeId();                            

							if (BSP_BOARD_TYPE_OP == bordType)
							{
									DWORD dwDataLength=0;
									BYTE * pFpgaFile=NULL;
									DWORD dwToNo=100;
									DWORD dwCrNo=100;
									pFpgaFile = (BYTE *)malloc(0x200000);
									if(NULL == pFpgaFile)
									{
										BSP_SysRunLedFlic(dwLEDState);
										if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
										{
										   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
										}                                        
										return ERROR;
									}
									
									if (OK!=BSPGetSoft(pbyBuffer,pFpgaFile,&dwDataLength))
									{
										BSP_SysRunLedFlic(dwLEDState);
										if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
										{
										   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
										}
                                        free(pFpgaFile);
										return ERROR;
									}
									BSP_SPI_Init();
									BSP_SPI_FlashEnable();
									if (OK!=BSP_SPIWrite_Data(pFpgaFile,dwDataLength,softUpCallback))
									{
										BSP_SPI_FlashDisable();
										BSP_SysRunLedFlic(dwLEDState);
										if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
										{
										   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
										}
                                        free(pFpgaFile);
										return ERROR;
									}
									BSP_SPI_FlashDisable();
									
									if(s_sSoftWarePara.softUpCallback !=NULL)
									{
										if (OK!=s_sSoftWarePara.softUpCallback(&dwToNo,&dwCrNo))
										{
											
										}
									
									}
									
									if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
									{
									   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
									}
									BSP_Debug(0);
									BSP_SysRunLedFlic(dwLEDState);
                                    free(pFpgaFile);
									return OK;
								}
							break;
					#endif

							
						
						default:
							break;
							
					}
				
				break;
				
			/* FPGA 背景图片*/
			case 3:
				{
				
					DWORD	dwFileLength = FILE_LEN_VALUE(pbyBuffer);
					BYTE *	dwFileStart = *((BYTE *)(pbyBuffer+FILE_OFF))+pbyBuffer;
					result=BSP_NandFlashFileWrite(byFileNo,dwFileStart,dwFileLength,softUpCallback);
					
					if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
					{
					   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
					}
					
					BSP_SysRunLedFlic(dwLEDState);
					return result;
				}

				break;
				
			default:
				break;

		}

		s_sSoftWarePara.pbySAdd = pbyBuffer;
		s_sSoftWarePara.dwlength = dwLen;

		
		result=SoftWareWrite();
		if (OK!=result)
		{
			
			if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
			{
			   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
			}

			
			BSP_SysRunLedFlic(dwLEDState);
			return result;
		}

		result=SoftWriteCheck();

		
		if (OK!=result)
		{
			
			if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
			{
			   logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
			}

			
			BSP_SysRunLedFlic(dwLEDState);
			return result;
		}
		SoftWareBKWrite();
        if(OK!=semGive(s_sSoftWarePara.semRecBuffInit))
        {
           logMsg("s_sSoftWarePara.semRecBuffInit\n",0,0,0,0,0,0);
        }
		BSP_Debug(0);

		


		BSP_SysRunLedFlic(dwLEDState);
		return OK;

        
}

/* 软件合法性校验

软件标志划分共４字节
0 : 软件类型　１主控，２FPGA
1 : FPGA 编号　主控忽略次参数
2-3 : 软件标志固定为'S','F'

*/

LOCAL SDWORD SoftWareCheck(BYTE* pbyBuffer, DWORD dwLen, BYTE *byFileType,BYTE *byFileNo)
{
    DWORD   dwSum1 = 0;
    DWORD   dwSum2 = FILE_SUM_VALUE(pbyBuffer);
    DWORD   dwFileLength = FILE_LEN_VALUE(pbyBuffer);
    DWORD   dwFileType = FILE_FLG_VALUE(pbyBuffer);
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
		return FILE_TYPE_ERROR;
	}

	if(dwFileFlg!=0x4600)
	{
		return FILE_TYPE_ERROR;
	}

	*byFileType = (dwFileType&0x000000FF);
	*byFileNo = (dwFileType&0x0000FF00)>>8;

    /* 数据校验长度*/
    dwSum1=BSPCheckSum(FILE_CHECKSUM_START(pbyBuffer),dwLen-4);
    if(dwSum1 != dwSum2)
    {
        return CHECK_SUM_ERROR;
    }

	return OK;

}


LOCAL SDWORD SoftWriteCheck()
{

	

    WORD   *pdwSadd 	= (WORD   *)s_sSoftWarePara.pbySAdd;
    WORD   *pdwDadd 	= (WORD   *)s_sSoftWarePara.pbyDAdd; 
    DWORD   dwlengeth	= s_sSoftWarePara.dwlength/2;
	DWORD   dwcounter    = 0;
	for (dwcounter=0;dwcounter<dwlengeth;dwcounter++)
	{
		if (*pdwSadd !=  *pdwDadd)
		{
			return FILE_WRITE_ERROR;
			
		}
		pdwSadd++;
		pdwDadd++;

	}
	
	return OK;


}




LOCAL SDWORD SoftWareBKWrite()
{

	
    DWORD   dwToNo = (s_sSoftWarePara.dwlength / 0x20000);
    DWORD   dwCrNo = 0;
    DWORD   *pdwSadd 	= (DWORD   *)s_sSoftWarePara.pbySAdd;
    DWORD   *pdwDadd 	= (DWORD   *)s_sSoftWarePara.pbyBkDAdd; 
    DWORD   dwlengeth	= s_sSoftWarePara.dwlength;
	DWORD 	retVal = OK;

	if ((s_sSoftWarePara.dwlength % 0x20000)!=0)
	{
		++dwToNo;
	}
	while(dwlengeth>0x20000)
		{
			retVal=writeFlash16(pdwSadd,pdwDadd,0x20000);
			if(retVal==ERROR)
			{
				return 	FILE_WRITE_ERROR;
			}
			dwlengeth-=0x20000;
			pdwSadd += (0x20000/4);
			pdwDadd += (0x20000/4);
			dwCrNo++;

			if(s_sSoftWarePara.softUpCallback !=NULL)
			{
				if (OK!=s_sSoftWarePara.softUpCallback(&dwToNo,&dwCrNo))
				{
					
				}
			
			}

			
		}
	if(dwlengeth>0)
		{
		
			dwCrNo++;

			retVal=writeFlash16(pdwSadd,pdwDadd,0x20000);
			
			if(retVal==ERROR)
			{
				return 	FILE_WRITE_ERROR;
			}
			
			if(s_sSoftWarePara.softUpCallback !=NULL)
			{
				if (OK!=s_sSoftWarePara.softUpCallback(&dwToNo,&dwCrNo))
				{
					
				}
			
			}
			
		}
	return OK;
}


LOCAL SDWORD SoftWareWrite()
{

	
    DWORD   dwToNo = (s_sSoftWarePara.dwlength / 0x20000);
    DWORD   dwCrNo = 0;
    DWORD   *pdwSadd 	= (DWORD   *)s_sSoftWarePara.pbySAdd;
    DWORD   *pdwDadd 	= (DWORD   *)s_sSoftWarePara.pbyDAdd; 
    DWORD   dwlengeth	= s_sSoftWarePara.dwlength;
	DWORD 	retVal = OK;

	if ((s_sSoftWarePara.dwlength % 0x20000)!=0)
	{
		++dwToNo;
	}
	while(dwlengeth>0x20000)
		{
			retVal=writeFlash16(pdwSadd,pdwDadd,0x20000);
			if(retVal==ERROR)
			{
				return 	FILE_WRITE_ERROR;
			}
			dwlengeth-=0x20000;
			pdwSadd += (0x20000/4);
			pdwDadd += (0x20000/4);
			dwCrNo++;

		if(s_sSoftWarePara.softUpCallback !=NULL)
		{
			if (OK!=s_sSoftWarePara.softUpCallback(&dwToNo,&dwCrNo))
			{
				return FILE_USE_CANCLE;/* 用户取消*/
			}
		}

			
		}
	if(dwlengeth>0)
		{
		
			dwCrNo++;

			retVal=writeFlash16(pdwSadd,pdwDadd,0x20000);
			
			if(retVal==ERROR)
			{
				return 	FILE_WRITE_ERROR;
			}
			if(NULL!=s_sSoftWarePara.softUpCallback)
			{
				s_sSoftWarePara.softUpCallback(&dwToNo,&dwCrNo);
			}
			
		}
	return OK;
}



/* 软件升级驱动初始化*/
SDWORD BSP_SoftWareUPinit()
{
    
    bzero((void *)&s_sSoftWarePara,sizeof( s_sSoftWarePara));

   s_sSoftWarePara.semRecBuffInit = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
    if (NULL == s_sSoftWarePara.semRecBuffInit)
    {
      return SEM_CREATE_ERROR;
    }
    
	semGive(s_sSoftWarePara.semRecBuffInit);
}
DWORD BSP_UP=0;

SDWORD BSP_CalBackTest(DWORD *dwtoNo,DWORD *dwcrNo)
{
	printf("\n Total NO: %d  CurNo %d",*dwtoNo,*dwcrNo);
	if(BSP_UP==1)
	{
	return ERROR;
	}
	return OK;

}

/* 软件升级驱动初始化*/
SDWORD BSP_SoftWareUPTest()
{
    
	 UINT8 *data  = NULL;
	 UINT32 bytes ;
	 UINT8 *bootrom_p1 ;
	 FILE *bootrom_fd ;
	 UINT8	*pFpgaFile = NULL;
	 UINT8	dataTemp;
	 UINT32  i = 0;
	 UINT32  j = 0;
	 UINT32  count = 0 ;
	 UINT32  ulFileLength = 0;
	 SDWORD result=0;
	 /*从CF卡获得FPGA文件，并对文件
	 的合法性和文件长度进行判断*/
	
	 
	 pFpgaFile = (UINT8*)malloc(0x300000);
	 
	 if(NULL == pFpgaFile)
	 {
		 printf( "\nERROR: no memory!\n" ) ;
		 return (1);
	 }
	
	bootrom_p1 = pFpgaFile ;
	
	 if((bootrom_fd = fopen( "host:./nsp2000.bin", "rb" )) == NULL )
	 {
		 printf( "\nERROR: can not open nsp2000.bin\n" ) ;
		 free( pFpgaFile ) ;
		 return (1);
	 }
	
	 bytes = 0 ;
	 printf( "read FPGA file\n" ) ;
	 taskDelay(1);
	 while( fscanf( bootrom_fd, "%c", &dataTemp ) != EOF )
	 {
		 *bootrom_p1++ = dataTemp ;
		 bytes = bytes + 1 ;
		 if( bytes >= 0x300000 )
		 break ;
	 } 
	 fclose( bootrom_fd ) ;
	
	 if( bytes > 0x300000 )
	 {
		 printf( "ERROR: bootrom file is too long!\n" ) ;
		 return (1);
	 }
	 result=BSP_SoftUpgrade(pFpgaFile,bytes,1,1,BSP_CalBackTest);
	 free(pFpgaFile);
	 return result;

}

/* 删除软件
---------------------------------------
    input:
    	 dwFileNo: 软件编号
    	 1: 主系统软件
    	 2: 备系统软件
    	 3: 主逻辑软件1
    	 4: 主逻辑软件2
    	 5: 主逻辑软件3
    	 6: 主逻辑软件4
    	 7: 备逻辑软件1
    	 8: 备逻辑软件2
    	 9: 备逻辑软件3
    	10: 备逻辑软件4
    	 
    return:
        OK ---------- 正确
        ERROR-------- 错误
*/

SDWORD BSP_DeleteSoft(DWORD dwFileNo)
{
	SDWORD sdwResult=OK;
	switch(dwFileNo)
	{
		case BSP_MAINSOFT_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_MAINSOFT,BSP_DEL_LENGTH);
			break;
		case BSP_BACKSOFT_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_BACKSOFT,BSP_DEL_LENGTH);
			break;
		case BSP_MAINLOGSOFT1_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_MAINLOGSOFT1,BSP_DEL_LENGTH);
			break;
		case BSP_MAINLOGSOFT2_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_MAINLOGSOFT2,BSP_DEL_LENGTH);
			break;
		case BSP_MAINLOGSOFT3_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_MAINLOGSOFT3,BSP_DEL_LENGTH);
			break;
		case BSP_MAINLOGSOFT4_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_MAINLOGSOFT4,BSP_DEL_LENGTH);
			break;
		case BSP_BACKLOGSOFT1_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_BACKLOGSOFT1,BSP_DEL_LENGTH);
			break;
		case BSP_BACKLOGSOFT2_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_BACKLOGSOFT2,BSP_DEL_LENGTH);
			break;
		case BSP_BACKLOGSOFT3_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_BACKLOGSOFT3,BSP_DEL_LENGTH);
			break;
		case BSP_BACKLOGSOFT4_INDEX:
			sdwResult=writeFlash16(LOCAL_MEM_LOCAL_ADRS,BSP_BACKLOGSOFT4,BSP_DEL_LENGTH);
			break;
		default:
			sdwResult=ERROR;
			break;
	}
	return sdwResult;
}



/* 软件恢复*/
SDWORD BSP_SoftBackUP(VOID)
{

	SWORD  swResultS = OK;
	DWORD  dwLedState = 0;
	/*software */
	SWORD  swResultS1 = BSP_GetMainSoftStatus(1);
	SWORD  swResultS2 = BSP_GetMainSoftStatus(2);
	DWORD	dwFileLength=0;
	DWORD	dwLen=0;
	/*FPGA*/
	SWORD  swResultF1 = OK; 
	SWORD  swResultF2 = OK; 
	SWORD  swResultF3 = OK; 
	SWORD  swResultF4 = OK; 
	SWORD  swResultF5 = OK; 
	SWORD  swResultF6 = OK; 
	SWORD  swResultF7 = OK; 
	SWORD  swResultF8 = OK; 

	printf("\n Soft BackUp\n");
	dwLedState=BSP_SysRunLedFlic(BSP_LED_FAST);
	

	swResultF1 = BSP_GetFPGAStatus(1);
	swResultF2 = BSP_GetFPGAStatus(2);
	swResultF3 = BSP_GetFPGAStatus(3);
	swResultF4 = BSP_GetFPGAStatus(4);
	swResultF5 = BSP_GetFPGAStatus(5);
	swResultF6 = BSP_GetFPGAStatus(6);
	swResultF7 = BSP_GetFPGAStatus(7);
	swResultF8 = BSP_GetFPGAStatus(8);
	

					
	if((OK!=swResultS1) && (OK==swResultS2))/* software 2 to 1*/
	{
		
		dwFileLength = FILE_LEN_VALUE(BSP_BACKSOFT);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_BACKSOFT);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_BACKSOFT,BSP_MAINSOFT,dwLen);
	}

	
	if((OK!=swResultS2) && (OK==swResultS1))/* software 1 to 2*/
	{
	
		dwFileLength = FILE_LEN_VALUE(BSP_MAINSOFT);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_MAINSOFT);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_MAINSOFT,BSP_BACKSOFT,dwLen);
	}


	if((OK!=swResultF1) && (OK==swResultF5))/* FPGA  5 to 1*/
	{
		dwFileLength = FILE_LEN_VALUE(BSP_BACKLOGSOFT1);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_BACKLOGSOFT1);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_BACKLOGSOFT1,BSP_MAINLOGSOFT1,dwLen);

	}

	if((OK!=swResultF5) && (OK==swResultF1))/* FPGA  1 to 5*/
	{
		dwFileLength = FILE_LEN_VALUE(BSP_MAINLOGSOFT1);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_MAINLOGSOFT1);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_MAINLOGSOFT1,BSP_BACKLOGSOFT1,dwLen);
	}

	if((OK!=swResultF2) && (OK==swResultF6))/* FPGA  6 to 2*/
	{
		dwFileLength = FILE_LEN_VALUE(BSP_BACKLOGSOFT2);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_BACKLOGSOFT2);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_BACKLOGSOFT2,BSP_MAINLOGSOFT2,dwLen);
	}

	if((OK!=swResultF6) && (OK==swResultF2))/* FPGA  2 to 6*/
	{
		dwFileLength = FILE_LEN_VALUE(BSP_MAINLOGSOFT2);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_MAINLOGSOFT2);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_MAINLOGSOFT2,BSP_BACKLOGSOFT2,dwLen);
	}
	if((OK!=swResultF3) && (OK==swResultF7))/* FPGA  7 to 3*/
	{
		dwFileLength = FILE_LEN_VALUE(BSP_BACKLOGSOFT3);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_BACKLOGSOFT3);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_BACKLOGSOFT3,BSP_MAINLOGSOFT3,dwLen);
	}
	if((OK!=swResultF7) && (OK==swResultF3))/* FPGA  3 to 7*/
	{
		dwFileLength = FILE_LEN_VALUE(BSP_MAINLOGSOFT3);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_MAINLOGSOFT3);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_MAINLOGSOFT3,BSP_BACKLOGSOFT3,dwLen);
	}
	if((OK!=swResultF4) && (OK==swResultF8))/* FPGA  8 to 4*/
	{
		dwFileLength = FILE_LEN_VALUE(BSP_BACKLOGSOFT4);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_BACKLOGSOFT4);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_BACKLOGSOFT4,BSP_MAINLOGSOFT4,dwLen);
	}
	if((OK!=swResultF8) && (OK==swResultF4))/* FPGA  4 to 8*/
	{
		dwFileLength = FILE_LEN_VALUE(BSP_MAINLOGSOFT4);
		dwLen = dwFileLength + FILE_OFF_VALUE(BSP_MAINLOGSOFT4);
		while(dwLen%4)
		{
			dwLen ++;
		}
		swResultS=writeFlash16(BSP_MAINLOGSOFT4,BSP_BACKLOGSOFT4,dwLen);
	}
	
	BSP_SysRunLedFlic(dwLedState);
	printf("\n Soft BackUp Done .\n");
	return swResultS;
}

