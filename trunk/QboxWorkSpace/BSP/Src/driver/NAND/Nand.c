/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/


#include "nand.h"



SDWORD PhyGetStatus(void);
SDWORD PhyBlockErase(UINT32 ulBlockAddr);
SDWORD PhyBlockCheck(UINT32 ulBlockAddr);
SDWORD PhyBlockRead(UINT32 ulBlockAddr,UINT8 * pbDataBuffer);
SDWORD PhyBlockRead_L(UINT32 ulBlockAddr,UINT8 * pbDataBuffer);
SDWORD PhyPageRead(UINT32 ulPageAddr,UINT8 * pbDataBuffer);
SDWORD PhyPageWrite(UINT32 ulPageAddr,UINT8 * pbDataBuffer);
SDWORD PhyBlockWrite(UINT32 ulBlockAddr,UINT8 * pbDataBuffer);
SDWORD PhyBlockWrite_L(UINT32 ulBlockAddr,UINT8 * pbDataBuffer);
void   PhyDelay(void);
SDWORD NandFlashBlockCmp(DWORD * pdwStr ,DWORD * pdwDtr,DWORD dwLength);
SDWORD FLASH_CalBackTest(DWORD *dwtoNo,DWORD *dwcrNo);
SDWORD BSP_NandFlashFileRead_L(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength);
SDWORD BSP_NandFlashFileWrite_L(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength,SDWORD (*softUpCallback) (DWORD*, DWORD*));

LOCAL   NAND_FLASH_FILE_TABLE sNandFlashTable;
LOCAL   BYTE abyTempBuffer[NAND_BLOCK_SIZE];

static SEM_ID		semNandFlsh=NULL; 			 /*FLASh 保护*/



/********************************************************************************
	Function:  	PhyBlockRead
	Description:		读取一块物理层数据
	Calls:  			略
	Called By:  		略
	Input:  			ulBlockAddr 物理块的地址
	Output:  			pbDataBuffer 读取到的数据
	Return:  			OK 读取成功，NAND_NOINBUFFER 没有给传人参数
	                        分配内存。
	Others:  			无
    											
********************************************************************************/
SDWORD PhyBlockRead(UINT32 ulBlockAddr,UINT8 * pbDataBuffer)
{
    UINT32 ultempCount;
   
    NAND_FLASH_ADD stTempPageAdd;
    stTempPageAdd.ulPageAddr32=ulBlockAddr<<7;
   
    /*校正块地址*/
    stTempPageAdd.pbPageAddr8[0]&=NAND_BLOCK_ADDR_MASK2;
    stTempPageAdd.pbPageAddr8[1]&=NAND_BLOCK_ADDR_MASK3;
    stTempPageAdd.pbPageAddr8[2]&=NAND_BLOCK_ADDR_MASK4;


    if(NULL==pbDataBuffer)
    {
        printf("block read.\n");
        return NAND_NOINBUFFER;
    }
    for (ultempCount=0;ultempCount<NAND_TOTAL_PAGE_BLOCK_NO;ultempCount++)
    {
        PhyPageRead(stTempPageAdd.ulPageAddr32,pbDataBuffer);
        stTempPageAdd.pbPageAddr8[0]+=1;
        pbDataBuffer+=NAND_PAGE_SIZE;
    }
    return OK;
}




void EnableCe(DWORD dwIsEnable)
{
  	
    if (0 ==dwIsEnable )
    {
        
        BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_FLASH_CE);
    }
    else if(1 == dwIsEnable)
    {
        
        BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_FLASH_CE);
    }
   return;
}


SDWORD PhyBlockWrite(UINT32 ulBlockAddr,UINT8 * pbDataBuffer)
{
    UINT32 ultempCount;
    UINT32 bResult;
    NAND_FLASH_ADD stTempPageAdd;
    BYTE * pbyTempAdd = pbDataBuffer;
    stTempPageAdd.ulPageAddr32=ulBlockAddr<<7;

    /*校正块地址*/
    stTempPageAdd.pbPageAddr8[0]&=NAND_BLOCK_ADDR_MASK2;
    stTempPageAdd.pbPageAddr8[1]&=NAND_BLOCK_ADDR_MASK3;
    stTempPageAdd.pbPageAddr8[2]&=NAND_BLOCK_ADDR_MASK4;


    if(NULL==pbDataBuffer)
    {
		printf("Buffer NULL.\n");
        return NAND_NOINBUFFER;
    }
	if (OK!=PhyBlockErase(stTempPageAdd.ulPageAddr32))
	{
	    printf("PhyBlockErase failed!\n");
		return ERROR;
	}
    for (ultempCount=0;ultempCount<NAND_TOTAL_PAGE_BLOCK_NO;ultempCount++)
    {
        bResult=PhyPageWrite(stTempPageAdd.ulPageAddr32,pbDataBuffer);
        if(ERROR==bResult)
        {
			printf("pagewrite error.\n");
            return ERROR;
        }
        stTempPageAdd.pbPageAddr8[0]+=1;
        pbDataBuffer+=NAND_PAGE_SIZE;
    }
	if(OK== PhyBlockRead(ulBlockAddr,abyTempBuffer))
	{
		if (OK==NandFlashBlockCmp((DWORD *)pbyTempAdd,(DWORD *)abyTempBuffer,(DWORD)NAND_BLOCK_SIZE))
		{
		    printf("sucess!\n");
			return OK;
		}
	}
    return ERROR;
}



/********************************************************************************
	Function:  	PhyPageRead
	Description:		从物理块读取一页数据
	Calls:  			略
	Called By:  		略
	Input:  			无
	Output:  			无
	Return:  			无
	Others:  			无
    											
********************************************************************************/
SDWORD PhyPageRead(UINT32 ulPageAddr,UINT8 * pbDataBuffer)
{
    UINT32 ultempCount;
    NAND_FLASH_ADD stTempPageAdd;
    stTempPageAdd.ulPageAddr32=ulPageAddr;
    if(NULL==pbDataBuffer)
    {
        printf("page read.\n");
        return NAND_NOINBUFFER;
    }
	//EnableCe(1);
    NAND_CMD_REGISTER=NAND_READ1ST;
    NAND_ADD_REGISTER=0x0&NAND_PAGE_ADDR_MASK0;
    NAND_ADD_REGISTER=0x0&NAND_PAGE_ADDR_MASK1;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[0]&NAND_PAGE_ADDR_MASK2;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[1]&NAND_PAGE_ADDR_MASK3;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[2]&NAND_PAGE_ADDR_MASK4;
    NAND_CMD_REGISTER=NAND_READ2ND;
    PhyDelay();
    for (ultempCount=0;ultempCount<NAND_PAGE_SIZE;ultempCount++)
    {
        *pbDataBuffer=NAND_DAT_REGISTER;
/*		if(ultempCount < 0x10)
		{
			printf("src:0x%x ",*((unsigned char *)(0x10000000+ultempCount)));
			printf("dst:0x%x \n",*pbDataBuffer);
		}
*/      pbDataBuffer++;
    }
	//EnableCe(0);
	return OK;
}





SDWORD PhyBlockErase(UINT32 ulBlockAddr)
{
    SDWORD status;
    NAND_FLASH_ADD stTempPageAdd;
    stTempPageAdd.ulPageAddr32=ulBlockAddr;
	//EnableCe(1);
    NAND_CMD_REGISTER=NAND_ERASE1ST;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[0]&NAND_BLOCK_ADDR_MASK2;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[1]&NAND_BLOCK_ADDR_MASK3;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[2]&NAND_BLOCK_ADDR_MASK4;
    NAND_CMD_REGISTER=NAND_ERASE2ND;
	//EnableCe(0);
	status = PhyGetStatus();
	if (ERROR == status)
		printf("erase status: 0x%x\n",status);
    return status;
    
}

/**
 * @brief 读NandFlash地址的值
 * @param uiBlockAddr [in] 块地址
 * @param uiPageAddr [in] 页地址
 * @param uiInnerAddr [in] 页内地址
 * @return 该地址的值
 */
UINT8 NandAddrRead(UINT32 uiBlockAddr,UINT32 uiPageAddr,UINT32 uiInnerAddr)
{
	unsigned char ucData = 0;
	unsigned int uiAddr = 0;

	uiAddr = (0x0fff&uiInnerAddr);
	uiAddr |=((uiPageAddr&0x7f)<<12);
	uiAddr |= (uiBlockAddr<<19);
	
//    NAND_CMD_REGISTER=0x05; //RANDOM DATA OUTPUT
	NAND_CMD_REGISTER=NAND_READ1ST;
	PhyDelay();
	
    NAND_ADD_REGISTER=(UINT8)(0xff&uiAddr);
    NAND_ADD_REGISTER=(UINT8)(0x0f&(uiAddr>>8));
    NAND_ADD_REGISTER=(UINT8)(0xff&(uiAddr>>12));
    NAND_ADD_REGISTER=(UINT8)(0xff&(uiAddr>>20));
    NAND_ADD_REGISTER=(UINT8)(0x03&(uiAddr>>28));
	
//    NAND_CMD_REGISTER=0xE0; //RANDOM DATA OUTPUT
	NAND_CMD_REGISTER=NAND_READ2ND;
    PhyDelay();
	
    ucData=NAND_DAT_REGISTER;	
	return ucData;	
}

/**
 * @brief NandFlash 块好坏标志
 * @param uiBlockAddr [in] 块地址
 * @return OK 好块,ERROR 坏块
 */
SDWORD NandBlockStateRead(UINT32 uiBlockAddr)
{
	unsigned char ucData[2] = {0};

	/*判断块好坏的标志是第一页和第二页的保留区域第一个字节(也就是页内第2049个字节)必须为0xff*/
	ucData[0] = NandAddrRead(uiBlockAddr,0,2048);  
	ucData[1] = NandAddrRead(uiBlockAddr,1,2048);
	
//	printf("NandStateRead ucData 0x%02x,0x%02x\n",ucData[0],ucData[1]);
	
	if((ucData[0]==0xff) && (ucData[1]==0xff))
	{
//		printf("Block(%d) is  good \n",uiBlockAddr);
		return OK;
	}
	else
	{
		printf("Block(%d) is bad,ucData 0x%02x,0x%02x\n",uiBlockAddr,ucData[0],ucData[1]);
		return ERROR;
	}
}



/********************************************************************************
	Function:  	PhyGetStatus
	Description:		获取NAND 物理层状态
	Calls:  			略
	Called By:  		略
	Input:  			无
	Output:  			无
	Return:  			无
	Others:  			无
    											
********************************************************************************/
SDWORD PhyGetStatus(void)
{
    UINT8 bResult=0;
	PhyDelay();
	//EnableCe(1);
    NAND_CMD_REGISTER=NAND_STATUS1ST;
    bResult=NAND_DAT_REGISTER;
	//EnableCe(0);
    if (bResult&0x1)
    {
        return ERROR;
    }
    else
    {
        return OK;
    }
}



void PhyDelay(void)
{
	DWORD result=BSP_AT91F_OR_PIO_GetInput(BSP_PIOC,BSP_FLASH_BUSY);
   while(result==0)
   	{
   		result=BSP_AT91F_OR_PIO_GetInput(BSP_PIOC,BSP_FLASH_BUSY);
   	}
   return;
}





SDWORD PhyPageWrite(UINT32 ulPageAddr,UINT8 * pbDataBuffer)
{
    SDWORD status;
    UINT32 ultempCount;
    NAND_FLASH_ADD stTempPageAdd;
    stTempPageAdd.ulPageAddr32=ulPageAddr;
    if(NULL==pbDataBuffer)
    {
        printf("write null\n");
        return NAND_NOINBUFFER;
    }
	//EnableCe(1);
    NAND_CMD_REGISTER=NAND_WRITE1ST;
    NAND_ADD_REGISTER=0x0&NAND_PAGE_ADDR_MASK0;
    NAND_ADD_REGISTER=0x0&NAND_PAGE_ADDR_MASK1;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[0]&NAND_PAGE_ADDR_MASK2;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[1]&NAND_PAGE_ADDR_MASK3;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[2]&NAND_PAGE_ADDR_MASK4;
    
    PhyDelay();
    for (ultempCount=0;ultempCount<NAND_PAGE_SIZE;ultempCount++)
    {
        NAND_DAT_REGISTER=*pbDataBuffer;
        pbDataBuffer++;
		    PhyDelay();
    }
	NAND_CMD_REGISTER=NAND_WRITE2ND;
	//EnableCe(0);
	status = PhyGetStatus();
	if (ERROR == status)
		printf("page write status: 0x%x\n",status);
    return status;
}





SDWORD PhyBlockCheck(UINT32 ulBlockAddr)
{
    
   if (OK==PhyBlockWrite(ulBlockAddr,(BYTE *)BSP_BOOTROM_BASE))
   	{
   		if(OK== PhyBlockRead(ulBlockAddr,abyTempBuffer))
   			{
			if (OK==NandFlashBlockCmp((DWORD *)BSP_BOOTROM_BASE,(DWORD *)abyTempBuffer,(DWORD)NAND_BLOCK_SIZE))
				{
					return OK;
				}
   			}
   	}


    
    return    ERROR;
}

/********************************************************************************
	Function:  	NandLowFormat
	Description:		低级格式化NAND FLASH
	Calls:  			略
	Called By:  		略
	Input:  			VOID
	Output:  			VOID
	Return:  			OK 成功，ERROR 失败
	Others:  			无
    											
********************************************************************************/

SDWORD NandLowFormat()
{
    DWORD dwTempLoop=0;
    SDWORD dwTempResult=0;
    memset((void *)&sNandFlashTable,0,sizeof(NAND_FLASH_FILE_TABLE));
	
    for (dwTempLoop=0; dwTempLoop<NAND_TOTAL_BLOCK_NO; dwTempLoop++)
    {
        dwTempResult = OK;
		/*dwTempResult = PhyBlockCheck(dwTempLoop);*/
        if(OK==dwTempResult)
        {
            sNandFlashTable.sGoodBlock.dwBlock[sNandFlashTable.sGoodBlock.dwBlockNumber]=dwTempLoop;
            sNandFlashTable.sGoodBlock.dwBlockNumber += 1;
        }
        else
        {
            sNandFlashTable.sBadBlock.dwBlock[sNandFlashTable.sBadBlock.dwBlockNumber]=dwTempLoop;
            sNandFlashTable.sBadBlock.dwBlockNumber += 1;
        }
        
	printf("NAND Flash LowFormat Block %d total 2048 \n",dwTempLoop);
	}
	
	printf(" Good Block %d \n",sNandFlashTable.sGoodBlock.dwBlockNumber);
	printf(" Bad Block %d \n",sNandFlashTable.sBadBlock.dwBlockNumber);
    sNandFlashTable.dwNandFlashFormatFlg = NAND_FILE_TABLE_INIT;
    return OK;

}




/********************************************************************************
	Function:  	NandFileTableWrite
	Description:		写文件分区表函数
	Calls:  			略
	Called By:  		略
	Input:  			VOID
	Output:  			VOID
	Return:  			OK 成功，ERROR 失败
	Others:  			无
    											
********************************************************************************/

SDWORD NandFileTableWrite()
{
    SDWORD dwTempResult=0;
	dwTempResult=writeFlash16((void *)&sNandFlashTable,(void *)BSP_SYS_FTAB,sizeof(NAND_FLASH_FILE_TABLE));
	if(OK!=dwTempResult)
	{
	return ERROR;
	}
	return OK;
}


/********************************************************************************
	Function:  	NandFileTableRead
	Description:		读文件分区表函数
	Calls:  			略
	Called By:  		略
	Input:  			VOID
	Output:  			VOID
	Return:  			OK 成功，ERROR 失败
	Others:  			无
    											
********************************************************************************/
SDWORD NandFileTableRead()
{
        memcpy((void *)&sNandFlashTable,(void *)BSP_SYS_FTAB,sizeof(NAND_FLASH_FILE_TABLE));
}

/**/
SDWORD NandFlashBlockCmp(DWORD * pdwStr ,DWORD * pdwDtr,DWORD dwLength)
{
	DWORD DwCounter =0;
	for(DwCounter=0; DwCounter<dwLength/4;DwCounter+=1)
	{
   		if(*((DWORD *)(pdwStr+DwCounter))!=*((DWORD *)(pdwDtr+DwCounter)))
		{
		    printf("cmp error. source: 0x%x dst: 0x%x\n",*((DWORD *)(pdwStr+DwCounter)),*((DWORD *)(pdwDtr+DwCounter)));
      		return ERROR;
 		}
     
	 }
	 return OK;
}

/* 初始化NAND 文件系统
---------------------------------------
    input:
        Void
    return:
        OK ----------成功
        ERROR-------失败
*/
SDWORD BSP_NandFlashFileInit(DWORD dwtype)
{
	if(semNandFlsh==NULL)
	{
	  semNandFlsh = semBCreate(SEM_Q_FIFO, SEM_EMPTY);
	  if(OK!=semGive(semNandFlsh))
	  {
		 printf("semNandFlsh give !\n");
		 return(ERROR);
	  }
	}

	if(0==dwtype)
	{
		NandFileTableRead();
	}
	else
	{
		sNandFlashTable.dwNandFlashFormatFlg  =0;
	}
    BSP_AT91F_OR_PIO_CfgInput(BSP_PIOC,BSP_FLASH_BUSY);
	BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,BSP_FLASH_WP);
	//BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,BSP_FLASH_CE);
	BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_FLASH_WP);
	//BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_FLASH_CE);
	BSP_AT91F_PIO_Disable(BSP_PIOC,1);
	BSP_AT91F_PIO_Disable(BSP_PIOC,3);

	printf("Nand flag = 0x%x!\n",sNandFlashTable.dwNandFlashFormatFlg);
    if( NAND_FILE_TABLE_INIT!= sNandFlashTable.dwNandFlashFormatFlg  )
    {
        if ( OK!=NandLowFormat() )
        {
            printf("Nand Low Format fail!\n");
            return ERROR;
        }

        if ( OK!=NandFileTableWrite() )
        {
            printf("Nand information restored!\n");
            return ERROR;
        }
    }
    return OK;
}


/*
 * 获取NAND 文件系统内文件长度
 -----------------------------------
    input:
        pbyNandFlashId:用于存放FLASH ID的地址
    output:
        VOID
    return:
    	VOID

*/

VOID BSP_NandFlashIDGet()
{
	BYTE * pbyNandFlashId = NULL;
	pbyNandFlashId = (BYTE *)malloc(4);
	if (pbyNandFlashId == NULL)
	{
		printf ("\r\n failed \n");
		return;
	}

	NAND_CMD_REGISTER=NAND_FLASHID;
/*	NAND_ADD_REGISTER=0x0; */
	PhyDelay();
	pbyNandFlashId[0]   = NAND_DAT_REGISTER;
	pbyNandFlashId[1]   = NAND_DAT_REGISTER;
	pbyNandFlashId[2]   = NAND_DAT_REGISTER;
	pbyNandFlashId[3]   = NAND_DAT_REGISTER;

	printf ("\r\n nand flash id 0x%0x 0x%0x 0x%0x 0x%0x\n", pbyNandFlashId[0],pbyNandFlashId[1],
					pbyNandFlashId[2],pbyNandFlashId[3]);

	free(pbyNandFlashId);
	return ;
}

VOID BSP_NandFlashReset()
{

	NAND_CMD_REGISTER=NAND_RESET1ST;
	PhyDelay();
	return ;

}




/*
 * 获取NAND 文件系统内文件长度
 -----------------------------------
    input:
        dwFileNo:要获取长度的文件的文件编号0-199
    output:
        pdwFileLength:返回的文件长度
    return:
        OK ----------成功
        ERROR-------失败
        NO_MEM------没有内存
        ERR_PARAM----参数错误
*/

SDWORD BSP_NandFlashFileGetLength(DWORD dwFileNo,DWORD * pdwFileLength)
{
    if(NULL == pdwFileLength)
    {
        return  NO_MEM;
    }
    if(dwFileNo>200)
    {
        return ERR_PARAM;
    }
    *pdwFileLength=sNandFlashTable.sFlashFile[dwFileNo].dwFileLength;
    return OK;
}

/*
 * 读取NAND 文件系统内的一个文件
 -----------------------------------
    input:
        dwFileNo:要读取的文件编号　0-199
        dwBufferLength:分配的内存长度
    output:
        pbyBuffer:返回的文件内容
    return:
        OK ----------成功
        ERROR-------失败
        NO_MEM------没有内存
        ERR_PARAM----参数错误
*/
SDWORD BSP_NandFlashFileRead(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength)
{
	SDWORD result=0;
	
	if(OK!=semTake(semNandFlsh, WAIT_FOREVER))
	{
		printf("semNandFlsh take !\n",0,0,0,0,0,0);
		return(ERROR);
	}

	 result=BSP_NandFlashFileRead_L(dwFileNo,pbyBuffer,dwBufferLength);

	if(OK!=semGive(semNandFlsh))
	{
	   printf("semNandFlsh give !\n",0,0,0,0,0,0);
	}

	return result;
}

SDWORD BSP_NandFlashFileRead_L(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength)
{
    DWORD dwTmpFileLength = 0;
    

    DWORD dwTempNU=0;

        
    if(NULL == pbyBuffer)
    {
        return  NO_MEM;
    }
    if(dwFileNo>200)
    {
        return ERR_PARAM;
    }
    if(OK != BSP_NandFlashFileGetLength(dwFileNo,&dwTmpFileLength))
    {
        return ERROR;
    }
    if(dwBufferLength<dwTmpFileLength)
    {
        return NO_MEM;
    }

    dwTmpFileLength = dwBufferLength;
    while(dwTmpFileLength>NAND_BLOCK_SIZE)
    {
        if(OK != PhyBlockRead(sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU],pbyBuffer))
        {
            return ERROR;
        }
        dwTempNU++;
        dwTmpFileLength-=NAND_BLOCK_SIZE;
        pbyBuffer+=NAND_BLOCK_SIZE;
    }
    if(dwTmpFileLength>0)
    {
    	if (OK !=PhyBlockRead(sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU],abyTempBuffer))
    	{
       	 	return ERROR;
    	}
    	memcpy(pbyBuffer,abyTempBuffer,dwTmpFileLength);
    }
    return OK;
    
}

/*
 * 写入NAND 文件系统内的一个文件
 -----------------------------------
    input:
        dwFileNo:要读取的文件编号　0-199
        dwBufferLength:分配的内存长度
        pbyBuffer:要写入的文件内容
    return:
        OK ----------成功
        ERROR-------失败
        NO_MEM------没有内存
        ERR_PARAM----参数错误
*/
SDWORD BSP_NandFlashFileWrite(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength,SDWORD (*softUpCallback) (DWORD*, DWORD*))
	{
		SDWORD result=0;
		
		if(OK!=semTake(semNandFlsh, WAIT_FOREVER))
		{
			printf("semNandFlsh take !\n",0,0,0,0,0,0);
			return(ERROR);
		}
	
		 result=BSP_NandFlashFileWrite_L(dwFileNo,pbyBuffer,dwBufferLength,softUpCallback);
	
		if(OK!=semGive(semNandFlsh))
		{
		   printf("semNandFlsh give !\n",0,0,0,0,0,0);
		}
	
		return result;
	}


SDWORD BSP_NandFlashFileWrite_L(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength,SDWORD (*softUpCallback) (DWORD*, DWORD*))
{
    
    DWORD dwTempNU=0;
	DWORD dwBlkNo = dwBufferLength/NAND_BLOCK_SIZE;
	DWORD dwtempcBlkNo = dwBufferLength/NAND_BLOCK_SIZE;

	DWORD dwtempBlkNo = dwBufferLength/NAND_BLOCK_SIZE;

	if(0 != dwBufferLength%NAND_BLOCK_SIZE )
	{
	dwBlkNo ++;
	dwtempBlkNo++;
	}


	if(dwBlkNo > 89 )
	{
		return FILE_TOOLARGE_ERROR;
	}

        
    if(NULL == pbyBuffer)
    {
        return  NO_MEM;
    }
    if(dwFileNo>200)
    {
        return ERR_PARAM;
    }
    


    while(dwBlkNo)
    {
        if(SYS_NULL==sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU])
        {
            if(sNandFlashTable.sGoodBlock.dwBlockNumber > 0)
            {

                sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU]=
                    sNandFlashTable.sGoodBlock.dwBlock[sNandFlashTable.sGoodBlock.dwBlockNumber-1];
                sNandFlashTable.sGoodBlock.dwBlock[sNandFlashTable.sGoodBlock.dwBlockNumber-1]=SYS_NULL;
                sNandFlashTable.sGoodBlock.dwBlockNumber -= 1;
            }
            
        }
        if(OK != PhyBlockWrite(sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU],pbyBuffer))
        {
            
            if(sNandFlashTable.sGoodBlock.dwBlockNumber > 0)
            {
                sNandFlashTable.sBadBlock.dwBlockNumber += 1;
                sNandFlashTable.sBadBlock.dwBlock[sNandFlashTable.sBadBlock.dwBlockNumber-1]=
                                  sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU];


                sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU]=
                    sNandFlashTable.sGoodBlock.dwBlock[sNandFlashTable.sGoodBlock.dwBlockNumber-1];
                sNandFlashTable.sGoodBlock.dwBlock[sNandFlashTable.sGoodBlock.dwBlockNumber-1]=SYS_NULL;
                sNandFlashTable.sGoodBlock.dwBlockNumber -= 1;
				continue ;
            }
            else
            {
                        return ERROR;
            }


        }
        dwTempNU++;
        dwBlkNo --;
        pbyBuffer+=NAND_BLOCK_SIZE;
		if(NULL!=softUpCallback)
		{
			dwtempcBlkNo=dwtempBlkNo-dwBlkNo;
			if (OK!=softUpCallback(&dwtempBlkNo,&dwtempcBlkNo))
			{
				return FILE_USE_CANCLE;/* 用户取消*/
			}
		}
    }


	/* 欺骗VTP  备份已经完成，根据问题单260 修改*/	
	if(NULL!=softUpCallback)
	{
		softUpCallback(&dwtempBlkNo,&dwtempBlkNo);
	}
	

	while(dwTempNU < 89)
		{
		 if(SYS_NULL!=sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU])
		 	{
		 	
			sNandFlashTable.sGoodBlock.dwBlock[sNandFlashTable.sGoodBlock.dwBlockNumber-1]=
				 sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU];
			sNandFlashTable.sFlashFile[dwFileNo].dwFileBlock[dwTempNU]=SYS_NULL;
			sNandFlashTable.sGoodBlock.dwBlockNumber += 1;
		 	}
		 dwTempNU++;
		}
  	sNandFlashTable.sFlashFile[dwFileNo].dwFileLength=dwBufferLength;
    /* 将修改过后的数据写入文件分区表*/
    if ( OK!=NandFileTableWrite() )
    {
        NandFileTableRead();
        return ERROR;
    }

    return OK;
}

/* 文件系统测试代码*/

SDWORD FLASH_CalBackTest(DWORD *dwtoNo,DWORD *dwcrNo)
{
	printf("\n Total NO: %d  CurNo %d",*dwtoNo,*dwcrNo);
	return OK;

}


SDWORD FileSysTest(BYTE fileno)
{
		
		 UINT8 *data  = NULL;
		 UINT32 bytes ;
		 UINT8 *bootrom_p1 ;
		 FILE *bootrom_fd ;
		 UINT8	*pFpgaFile = NULL;
 		 UINT8	*pFpgaFile2 = NULL;
		 UINT8	dataTemp;
		 UINT32  i = 0;
		 UINT32  j = 0;
		 UINT32  count = 0 ;
		 UINT32  ulFileLength = 0;
		 SDWORD result=0;
		 /*从CF卡获得FPGA文件，并对文件
		 的合法性和文件长度进行判断*/
		
		 
		 pFpgaFile = (UINT8*)malloc(0x300000);
		 pFpgaFile2 = (UINT8*)malloc(0x300000);
		 
		 if(NULL == pFpgaFile)
		 {
			 printf( "\nERROR: no memory!\n" ) ;
			 return (1);
		 }

		 
		 if(NULL == pFpgaFile2)
		 {
			 printf( "\nERROR: no memory!\n" ) ;
			 return (1);
		 }
		
		bootrom_p1 = pFpgaFile ;
		
		 if((bootrom_fd = fopen( "nsp2000.bin", "rb" )) == NULL )
		 {
			 printf( "\nERROR: can not open nsp2000.bin\n" ) ;
			 free( pFpgaFile ) ;
			 free( pFpgaFile2 ) ;
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
		 BSP_NandFlashFileInit(0);
		 do
		 {
			 fileno--;
			 BSP_NandFlashFileWrite(fileno,pFpgaFile,bytes,FLASH_CalBackTest);
			 BSP_NandFlashFileRead(fileno,pFpgaFile2,bytes);
			 result=memcmp(pFpgaFile,pFpgaFile2,bytes);
			 printf ("result :%d file %d \n",result,fileno);
		 }while(fileno);
		 free(pFpgaFile);
 		 free(pFpgaFile2);
		 return result;
	
}


DWORD FlashWriteTest(DWORD blkno)
{
	BSP_NandFlashFileInit(0);
	PhyBlockWrite(blkno,(BYTE *)0x10000000);

}

DWORD FlashReadTest(DWORD blkno)
{
	UINT8  *pFpgaFile = NULL;
	BSP_NandFlashFileInit(0);
	PhyBlockRead(blkno,abyTempBuffer);
	d(abyTempBuffer);
	return (DWORD)abyTempBuffer;
	
	

}

DWORD FlashPageWTest(DWORD blkno)
{
	BSP_NandFlashFileInit(0);
	PhyPageWrite(blkno,(BYTE *)0x10000000);

}

DWORD FlashPageRTest(DWORD blkno)
{
	BSP_NandFlashFileInit(0);
	PhyPageRead(blkno,abyTempBuffer);
	d(abyTempBuffer);
	return (DWORD)abyTempBuffer;
	

}



SDWORD PhyPageWriteTest(UINT32 ulPageAddr)
{
    UINT32 ultempCount;
    NAND_FLASH_ADD stTempPageAdd;
    stTempPageAdd.ulPageAddr32=ulPageAddr;
    NAND_CMD_REGISTER=NAND_WRITE1ST;
    NAND_ADD_REGISTER=0x0&NAND_PAGE_ADDR_MASK0;
    NAND_ADD_REGISTER=0x0&NAND_PAGE_ADDR_MASK1;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[0]&NAND_PAGE_ADDR_MASK2;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[1]&NAND_PAGE_ADDR_MASK3;
    NAND_ADD_REGISTER=stTempPageAdd.pbPageAddr8[2]&NAND_PAGE_ADDR_MASK4;
    
    PhyDelay();
    for (ultempCount=0;ultempCount<NAND_PAGE_SIZE;ultempCount++)
    {
        NAND_DAT_REGISTER=0x55;
		    PhyDelay();
    }
	NAND_CMD_REGISTER=NAND_WRITE2ND;
	//EnableCe(0);
    return PhyGetStatus();
}


/*kangbozhi add*******/
static BYTE *pNandFlashBuf = NULL;
static SEM_ID SemNandBuf = 0;
#define NAND_FILE_LENGTH 0xA00000


BYTE * GetNandFlashBuffer()
{
	if(!SemNandBuf)
	{
//		SemNandBuf = semBCreate(SEM_Q_PRIORITY,SEM_FULL);	
		SemNandBuf = semBCreate(SEM_Q_FIFO,SEM_FULL);	
	}
	if(pNandFlashBuf==NULL)
	{
		pNandFlashBuf = malloc(NAND_FILE_LENGTH);
		if(pNandFlashBuf==NULL)
		{
			printf("No Memory!\n",0,0,0,0,0,0);
			return NULL;			
		}
	}
	
	if(SemNandBuf)
	{
		if(OK == semTake(SemNandBuf,sysClkRateGet()/10))
		{
			memset(pNandFlashBuf,0,NAND_FILE_LENGTH);
			return pNandFlashBuf;
		}
		else
		{
			printf("semTake SemNandBuf failed\n",0,0,0,0,0,0);
		}
	}
	return NULL;
}

SDWORD ReleaseNandFlashBuffer()
{
	int ret = ERROR;
	if(SemNandBuf)
	{
		ret = semGive(SemNandBuf);
		if(ret!=OK)
		{
			printf("SemNandBuf semGive Failed\n",0,0,0,0,0,0);
		}
	}
	return ret;
}

SDWORD GetNandBufLength()
{	
	return 
NAND_FILE_LENGTH;
}

SDWORD FreeNandFlashBuffer()
{
	if(pNandFlashBuf)
	{
		free(pNandFlashBuf);
		pNandFlashBuf = NULL;
	}
	return OK;
}

SDWORD BSPFileUncompress(BYTE *pbySrc,DWORD dwSrcLen,BYTE *pbyDest,DWORD *pdwDestLen)
{
	DWORD dwBaseAdd = 0;
	DWORD dwSrcStart = 0;
	DWORD dwSrcLength = 0;

	int ret = 0;

	if(pbySrc==NULL || pbyDest==NULL || pdwDestLen==NULL || *pdwDestLen<dwSrcLen)
	{
		printf("BSPFileUncompress No Memory!\n",0,0,0,0,0,0);
		return ERROR;
	}

//	logTMsg(" BSPFileUncompress begin to Uncompress...\n"); //kangbozhi test
	
	/*去掉文件头，获得文件起始地址和文件长度*/
	dwBaseAdd = (DWORD)pbySrc;
    dwSrcLength = FILE_LEN_VALUE(dwBaseAdd);
    dwSrcStart = *((DWORD *)(dwBaseAdd+FILE_OFF))+dwBaseAdd;

	ret = uncompress(pbyDest,pdwDestLen,(BYTE*)dwSrcStart,dwSrcLength);//文件解压

//	logTMsg(" BSPFileUncompress Uncompress end,result = %d ...\n",ret); //kangbozhi test	

	return ret;
}

SWORD NandFileUpgrade(BYTE byFileNo,BYTE * buf,DWORD dwLen,SDWORD (*softUpCallback) (DWORD*, DWORD*))
{
	SWORD result=ERROR;
	BYTE *pNandBuf = NULL;

	if(dwLen>NAND_FILE_LENGTH)	//判断文件长度是否溢出
	{
		return ERROR;
	}

	pNandBuf = GetNandFlashBuffer();
	if(pNandBuf == NULL)
	{
		printf("get memory failed\n",0,0,0,0,0,0);
		return ERROR;
	}
	
	memcpy(pNandBuf,buf,dwLen);
	result = BSP_NandFlashFileWrite(byFileNo,pNandBuf,dwLen,softUpCallback); //write data to flash

	ReleaseNandFlashBuffer();

	return OK;
}

SWORD BSPGetNandFileVerDevice(BYTE byFileNo,BYTE * pbyVer)
{
	BYTE *pNandBuf = NULL;
	DWORD dwFileSize = 0;
	
	pNandBuf = GetNandFlashBuffer();
	if(pNandBuf == NULL)
	{
		printf("get memory failed\n",0,0,0,0,0,0);
		return ERROR;
	}

		
	if(OK!=BSP_NandFlashFileGetLength(byFileNo,&dwFileSize))//获取文件长度
	{
		printf("BSP_NandFlashFileGetLength failed, FileNo = %d \n",(int)byFileNo,0,0,0,0,0);
		ReleaseNandFlashBuffer();
		return ERROR;
	}
	
	if(GetNandBufLength()<dwFileSize)
	{
		printf("No enough memory ! \n",0,0,0,0,0,0);
		ReleaseNandFlashBuffer();
		return ERROR;
	}

	if(OK!=BSP_NandFlashFileRead(byFileNo,pNandBuf,dwFileSize))//读取NandFlash文件到内存
	{
		printf("BSP_NandFlashFileRead file %d failed\n",byFileNo,0,0,0,0,0);
		ReleaseNandFlashBuffer();
		return ERROR;
	}
	
	pbyVer[2] = *(pNandBuf+FILE_VER);
	pbyVer[1] = *(pNandBuf+FILE_VER+1);
	pbyVer[0] = *(pNandBuf+FILE_VER+2);

	ReleaseNandFlashBuffer();

	return OK;
	
}



/* kangbozhi add test */
/***临时添加为logo图测试***/
#define BSP_LOGO_BACKUP 1000
SDWORD BSPGetFileFromNorFlash(DWORD dwFileNo,BYTE *pbyBuffer,DWORD *pdwLength)
{
	int ret = ERROR;

	DWORD dwBaseAdd = BSP_LOGO_BACKUP;
    DWORD dwFileLength = FILE_LEN_VALUE(dwBaseAdd);
    DWORD dwFileStart = *((DWORD *)(dwBaseAdd+FILE_OFF))+dwBaseAdd;

	printf("BSPGetFileFromNorFlash enter\n",0,0,0,0,0,0);
	
	if(1 != dwFileNo)
	{
		printf("BSPGetFileFromNorFlash include error file No(%d).\n",dwFileNo,0,0,0,0,0);
		return ERROR;
	}

	ret = uncompress(pbyBuffer,pdwLength,(BYTE*)dwFileStart,dwFileLength);//文件解压

	if(ret != OK)
	{
		printf("BSPGetFileFromNorFlash ret = %d\n",ret,0,0,0,0,0);
	}
	
	return ret;
	
}


int NandFlashTest(int FileNo)
{
//	UINT8 *src = (UINT8 *)malloc(0x300000);
//	UINT8 *dest = (UINT8 *)malloc(0x300000);
	char *src = (UINT8 *)malloc(384*1024);
	char *dest = (UINT8 *)malloc(384*1024);
	
	UINT32 fileSize = 288*1024;
	int result = 0;

	memset(src,0,384*1024);
	memcpy(src, "hahahahahaha", 16);

	printf("write data into nand flash\n");
#if 0	
	BSP_NandFlashFileWrite(1, pTempFile1, fileSize, NandCalBackTest);
	printf("read data from nand flash\n");
	BSP_NandFlashFileRead(1, pTempFile2, fileSize);
	result = memcmp(pTempFile1, pTempFile2, fileSize);
	printf("result:%d\n", result);
	free(pTempFile1);
	free(pTempFile2);

	
    char src[16] = "123456789abcdef";
	char dest[16] = {0};
#endif	
	if(OK!=BSP_NandFlashFileWrite(FileNo,src,fileSize,NULL))
	{
		printf("BSP_NandFlashFileWrite failed\n",0,0,0,0,0,0);
		return ERROR;
	}
	if(OK!=BSP_NandFlashFileRead(FileNo,dest,fileSize))
	{
		printf("BSP_NandFlashFileRead failed\n",0,0,0,0,0,0);
		return ERROR;
	}

	printf("NandFlashTest src: %s \n",(int)src,0,0,0,0,0);
	printf("NandFlashTest dest: %s \n",(int)dest,0,0,0,0,0);

	result = memcmp(src, dest, fileSize);
	printf("result:%d\n", result);
	
	free(src);
	free(dest);
	
	return OK;

}


int NandTestCheck()
{
	DWORD dwTempLoop = 0;
	int dwTempResult = 0;
    for (dwTempLoop=0; dwTempLoop<NAND_TOTAL_BLOCK_NO; dwTempLoop++)
    {        
		dwTempResult = PhyBlockCheck(dwTempLoop);
		printf("NandTestCheck %d result %d\n",dwTempLoop,dwTempResult,0,0,0,0);
    }
	return 0;
}

void inflateTask(char *pStr)
{
	CHAR fileName[128];
	FILE *fp;	
	UINT32 fileSize;
	UINT32 inflateSize;
	int ctrlSock;
	UINT8 *pTempFile1 = NULL;
	UINT8 *pTempFile2 = NULL;
	int result;

	pTempFile1 = (UINT8 *)malloc(0xa00000);
	pTempFile2 = (UINT8 *)malloc(0xa00000);

	if((pTempFile1 == NULL) || (pTempFile2 == NULL))
	{
		printf("ERROR: no enough memory\n");
		free(pTempFile1);
		free(pTempFile2);
		return;
	}
	else
	{
		printf("pTempFile1: 0x%x,pTempFile2:0x%x,\n",pTempFile1,pTempFile2);
	}

	ctrlSock = ftpHookup("host");
	if(ctrlSock == ERROR)
	{
		printf("can not open the FTP server\n", 0, 0, 0, 0);
		free(pTempFile1);
		free(pTempFile2);
		return;
	}	
	close(ctrlSock);
	
	memset(fileName, 0, sizeof(fileName));
	strcpy(fileName, "host:./");
	strcat(fileName, pStr);
	fp = fopen(fileName, "rb");
	if(fp == NULL)
	{
		printf("can not open the file %s\n", (int)pStr, 0, 0, 0);
		free(pTempFile1);
		free(pTempFile2);
		return;
	}

	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if(fileSize > 0xa00000)
	{
		printf("fileSize > 0x300000\n");
		fileSize = 0xa00000;
	}
	fread(pTempFile1, 1, fileSize, fp);
	fclose(fp);
#if 0
	printf("write data into nand flash\n");
	BSP_NandFlashFileWrite(1, pTempFile1, fileSize, NandCalBackTest);
	printf("read data from nand flash\n");
	BSP_NandFlashFileRead(1, pTempFile2, fileSize);
	result = memcmp(pTempFile1, pTempFile2, fileSize);
	printf("result:%d\n", result);
#endif

	if(OK!=inflate(pTempFile1,pTempFile2,fileSize,&inflateSize))
	{
		printf("inflate failed,fileSize=%d,inflateSize=%d\n",fileSize,inflateSize);
	}
	else
	{
		printf("inflate success,fileSize=%d,inflateSize=%d\n",fileSize,inflateSize);
	}

	free(pTempFile1);
	free(pTempFile2);
}


void InflateTest(char *pStr)
{
	sp(inflateTask, pStr, 0, 0, 0, 0, 0, 0, 0, 0);
}

extern int compress (BYTE *dest, unsigned int *destLen, const BYTE *source, unsigned int sourceLen); 

int NandBlockCompTask(UINT32 uiBlockAddr)
{
	unsigned char ucData1[NAND_BLOCK_SIZE] = {0};
	unsigned char ucData2[NAND_BLOCK_SIZE] = {0};
	UINT32 uiPageAddr = 0;
	UINT32 uiInnerAddr = 0;

	int i = 0;
	if(OK != PhyBlockRead(uiBlockAddr,ucData1))
	{
		printf("PhyBlockRead failed\n");
		return ERROR;
	}
	for(i=0;i<NAND_BLOCK_SIZE;i++)
	{
		uiPageAddr = i/NAND_PAGE_SIZE;
		uiInnerAddr = i%NAND_PAGE_SIZE; 
		ucData2[i] = NandAddrRead(uiBlockAddr,uiPageAddr,uiInnerAddr);
	}

	if(0==memcmp(ucData1,ucData2,NAND_BLOCK_SIZE))
	{
		printf("Nand read OK\n");
	}
	else
	{
		printf("Nand read ERROR \n");
	}

	printf("page:");
	for(i=0;i<16;i++) printf("0x%2x,",ucData1[i]);
	printf("\n");
	printf("data:");
	for(i=0;i<16;i++) printf("0x%2x,",ucData2[i]);
	printf("\n");
	
	return 0;
}

int NandBlockComp(UINT32 uiBlockAddr)
{
	taskSpawn(
		"BlockCompT",             /* name of new task (stored at pStackBase) */
	    140,         /* priority of new task */
	    0,          /* task option word */
	    378*1024,        /* size (bytes) of stack needed plus name */
	    (FUNCPTR)NandBlockCompTask,          /* entry point of new task */
	    uiBlockAddr,             /* 1st of 10 req'd task args to pass to func */
	    0,0,0,0,0,0,0,0,0);
}

int NandAllStateRead()
{
	unsigned int i = 0;
	unsigned int uiGood = 0;
	unsigned int uiBad = 0;	
	for(i= 0;i<4096;i++)
	{
		if(0==NandBlockStateRead(i))
		{
			uiGood++;
		}
		else
		{
			uiBad++;
		}		
	}
	printf("NandAllStateRead Good block %d,bad block %d\n",uiGood,uiBad);
	return 0;
}

int PrintTableBlock()
{
	int i = 0;
	printf("Block table has %d good blocks,%d bad blocks\n",sNandFlashTable.sGoodBlock.dwBlockNumber,
		sNandFlashTable.sBadBlock.dwBlockNumber);

	printf("\ngood block is:\n");
	for(i=0;i<sNandFlashTable.sGoodBlock.dwBlockNumber;i++)
	{
		printf("%4d,",sNandFlashTable.sGoodBlock.dwBlock[i]);
		if(((i+1)%16) == 0)
			printf("\n");
	}

	printf("\n\nbad block is:\n");
	for(i=0;i<sNandFlashTable.sBadBlock.dwBlockNumber;i++)
	{
		printf("%4d,",sNandFlashTable.sBadBlock.dwBlock[i]);
		if(((i+1)%16) == 0)
			printf("\n");
	}
	return 0;
}

int IniBlockWriteTask(UINT32 uiBlockAddr)
{
	char src[NAND_BLOCK_SIZE] = {
		0x78,0x9C,0x4D,0x4E,0x41,0x8E,0xC2,0x30,0x0C,0xBC,0xFB,0x31,0x55,0xD2,0x55,0x0B,
		0x1C,0x7C,0xA0,0x05,0x01,0x02,0xA4,0xAA,0xA0,0xBD,0xA0,0x1E,0x02,0x35,0x10,0xA0,
		0x31,0x4A,0x53,0x2A,0x7E,0x4F,0x22,0x2D,0x0B,0x07,0x5B,0x33,0x1E,0xCF,0xD8,0xBB,
		0x45,0x91,0xB3,0x39,0xEA,0x53,0x05,0xFB,0xC9,0xF9,0x70,0x47,0x01,0x8B,0x02,0xE5,
		0x28,0x8E,0x64,0x3A,0x8C,0xD2,0x41,0x34,0x82,0xB5,0x6A,0xAF,0x18,0x27,0x49,0xF4,
		0x2E,0x01,0xBF,0xBD,0x6A,0xBF,0x97,0xA4,0x94,0x00,0xBB,0xCD,0xB3,0xAD,0x60,0xA3,
		0x6B,0x94,0x90,0xFB,0x2E,0xA0,0xE4,0x3E,0x60,0xBE,0x61,0x90,0x83,0xA9,0x24,0x7F,
		0xA8,0x60,0xEB,0x30,0x15,0x22,0x86,0x39,0x29,0xEB,0x32,0x52,0x6E,0xA2,0x9C,0xC2,
		0xF9,0x87,0x6F,0x75,0x43,0xDC,0x39,0x4C,0xBC,0xDB,0x18,0x3A,0xFC,0x0F,0xA4,0xF0,
		0x49,0x2B,0x7D,0x3A,0xBB,0x71,0x7D,0xE9,0x5A,0x57,0xC1,0x9A,0x6B,0xF2,0xF9,0xCB,
		0x92,0x6A,0xFC,0x89,0x07,0xE9,0x10,0x96,0x33,0x4B,0x64,0xDE,0x24,0xBB,0x75,0xF4,
		0x87,0xA7,0xE6,0xA1,0x57,0x5D,0x93,0x73,0x73,0xF7,0x7A,0x48,0x2A,0xB8,0x27,0x5B,
		0x41,0x66,0x59,0x85,0x87,0x5F,0x68,0x81,0x4F,0x1C,0x00,0x00
		};
	
	if(OK==PhyBlockWrite(uiBlockAddr,src))
	{
		printf("IniBlockWrite success,block = %d\n",uiBlockAddr);
	}
	else
	{
		printf("IniBlockWrite failed,block = %d\n",uiBlockAddr);
		return ERROR;
	}
	return OK;	
}

int IniBlockWrite(UINT32 uiBlockAddr)
{
	taskSpawn(
		"IniWriteTk",             /* name of new task (stored at pStackBase) */
	    140,         /* priority of new task */
	    0,          /* task option word */
	    200*1024,        /* size (bytes) of stack needed plus name */
	    (FUNCPTR)IniBlockWriteTask,          /* entry point of new task */
	    uiBlockAddr,             /* 1st of 10 req'd task args to pass to func */
	    0,0,0,0,0,0,0,0,0);
}


/* kangbozhi test end */

