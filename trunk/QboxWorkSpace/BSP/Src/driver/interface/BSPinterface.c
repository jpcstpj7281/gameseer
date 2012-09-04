/******************************************************************************


******************************************************************************/

#include "BSPinterface.h"
#include "BSPinclude.h"
#include "end.h"
#include "timers.h "
#include "mmapi.h"
//#include "eventid.h"
#include "ramDrv.h"
#include "cbioLib.h"
#include "dosFsLib.h"

#include "driver_interface.h"

void I2C_Driver()
{
    printf("This is I2C driver for Qbox! \n");
}


/**************************************接口*****************************************/

LOCAL BOOT_PARAM_DATA *sGlobaSysData=(BOOT_PARAM_DATA *)0x2000;

void ReadReg(unsigned int paddr)
{
    volatile unsigned int *addr = (unsigned int *)paddr;
	printf("\r\n addr: 0x%x, value: 0x%x\n",addr,*addr);
}

void WriteReg(unsigned int paddr, unsigned int value)
{
    volatile unsigned int *addr = (unsigned int *)paddr;
	*(addr) = value;
	ReadReg(paddr);
}

void FlashTest()
{
	/* Here is an example of Autoselect mode (getting manufacturer ID) */
	/* Define UINT16 example: typedef unsigned short UINT16; */
	unsigned short manuf_id = 0;
	BSP_FlashWriteEnable(1);
	/* Auto Select Entry */
	*( (unsigned short *)0x30000000 + 0x555 ) = 0x00AA; /* write unlock cycle 1 */
	*( (unsigned short *)0x30000000 + 0x2AA ) = 0x0055; /* write unlock cycle 2 */
	*( (unsigned short *)0x30000000 + 0x555 ) = 0x0090; /* write autoselect command */
	/* multiple reads can be performed after entry */
	manuf_id = *( (unsigned short *)0x30000000 + 0x000 ); /* read manuf. id */
	/* unsigned int exit */
	*( (unsigned short *)0x30000000 + 0x000 ) = 0x00F0; /* exit autoselect (write reset command) */
	BSP_FlashWriteEnable(0);
	printf(" manuf_id:0x%x\n",manuf_id);
}

void setSMC2(unsigned int value)
{
   *((volatile unsigned int *)0xffffff78) = value;
   printf("\r\n addr: 0xffffff78, value: 0x%x\n",*((volatile unsigned int *)0xffffff78));
}

/* 广播设置
128  高清采集板
129  标清采集板
130  全体采集板
131  信号处理板
132  交叉板（目前和主控为同一板）
133  主控板（目前未定义）
*/

/*软件入口
-----------------------------------
	input:
		VOID
	output:
    		VOID
	return:
		VOID
*/
extern void Qbox_app_entry();
 
extern void C753_Reset( unsigned char dwEnable );
extern void C722_Reset( unsigned char dwEnable );

VOID BSP_SoftStart(VOID)
{
    SDWORD sdwResult=OK;
    SDWORD sdwResultbksoft=OK;

	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
    /*BSP_DrvInit();*/

	/* initialize the SPI interface */
	dev_SpiInit();
	printf ("\r\n======= Finished the SPI initialize =========\n");
	
	C753_Reset(1);
	C772_Reset(1);

	/* Initialize the I2C interface */	
	dev_I2cInit();
	printf ("\r\n======= Finished the I2C initialize =========\n");


	C753_Reset(0);
	C772_Reset(0);

#if 0
    Qbox_app_entry();
#endif
	printf("\n@@@@@line:%d, function:%s, file:%s",__LINE__,__FUNCTION__,__FILE__);
#if 0    
    /* 如果运行单板软件就要加载FPGA*/
    if(BSP_SOFT_MAINSOFT==sGlobaSysData->dwSoftState)
    {
        sdwResult=BSP_LoadFpga();
        
        if(OK != sdwResult)
        {
            printf("\n LOAD FPGA ERROR ! \n");
        }
        if(OK == sdwResult)         
        {
            OpenBus();
        }
        sdwResultbksoft=BSP_SoftBackUP();
    
        if(OK != sdwResultbksoft)
        {
            printf("\n SoftWare BackUP ERROR ! \n");
        }
    }
    xcopy("/tffs0","/ram0");
	/*mkdir("home");*/
	/*VOS_InitVOS();
    start485();
    starttimer();
    starttcp();
	startmm();*/

//	PF_RegisterModule(1, MAILBOX_CFG_BS, 0, 0, 0, 0);
/*    PF_RegisterSystemMessage(1, PF_SYS_MSG_REBOOT   | PF_SYS_MSG_STANDING_BY | \
		                        PF_SYS_MSG_START_UP | PF_SYS_MSG_OFFLINE);
	PF_LoadModule(1);

	taskMainCtrlAll(sdwResult);*/

/* CS板特殊定义*/	
#ifdef BOARD_CS
/*	TaskMainCtlBdAll();*/
#endif
/* HD板特殊定义*/	
#ifdef BOARD_HD
	TaskHD();
#endif
/* SD板特殊定义*/	
#ifdef BOARD_SD
	TaskSD();
#endif
/* OP板特殊定义*/	
#ifdef BOARD_OP
	SPCTask();
#endif
/* MS板特殊定义*/
#ifdef BOARD_MS

#endif
/* MC板特殊定义*/	
#ifdef BOARD_MC

#endif

/*    PF_ModuleLoaded(1); */
#endif
}












/*
 * 读取FPGA 版本，版本格式：V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    input:
        VOID
    output:
        pbyVer:版本号
        pbyNum:FPGA数量
    return:
        VOID
*/
VOID BSP_GetFpgaVer( BYTE *pbyNum,BYTE *pbyVer )
	{
		SDWORD dwResult=OK;
		DWORD  dwFileNum=0;
		BYTE 	bordType=0;
		
	    	DWORD dwTempVer=0;
		
		bordType=BSP_GetBoardTypeId();

		if(NULL==pbyVer)
		{
			return ;
		}

		switch (bordType)
		{
			case BSP_BOARD_TYPE_CS: 	/* SC */
				dwFileNum=1;
				if(OK==dwResult)
				{
					dwResult=BSP_GetFPGAStatus(3);
					
				}

			    dwTempVer = FILE_VER_VALUE(BSP_MAINLOGSOFT3);
			    pbyVer[2] = ( (dwTempVer & 0x000000FF) >> 0 );
			    pbyVer[1] = ( (dwTempVer & 0x0000FF00) >> 8 );
			    pbyVer[0] = ( (dwTempVer & 0x00FF0000) >> 16);
				break;
			case BSP_BOARD_TYPE_HD: 	/* HD */
				dwFileNum=2;
				if(OK==dwResult)
				{
					dwResult=BSP_GetFPGAStatus(1);
				}

				if(OK==dwResult)
				{
					dwResult=BSP_GetFPGAStatus(2);
				}
			    dwTempVer = FILE_VER_VALUE(BSP_MAINLOGSOFT1);
			    pbyVer[2] = ( (dwTempVer & 0x000000FF) >> 0 );
			    pbyVer[1] = ( (dwTempVer & 0x0000FF00) >> 8 );
			    pbyVer[0] = ( (dwTempVer & 0x00FF0000) >> 16);
			    dwTempVer = FILE_VER_VALUE(BSP_MAINLOGSOFT2);
			    pbyVer[5] = ( (dwTempVer & 0x000000FF) >> 0 );
			    pbyVer[4] = ( (dwTempVer & 0x0000FF00) >> 8 );
			    pbyVer[3] = ( (dwTempVer & 0x00FF0000) >> 16);

				break;
			case BSP_BOARD_TYPE_SD: 	/* SD */	
				dwFileNum=2;
				if(OK==dwResult)
				{
					dwResult=BSP_GetFPGAStatus(1);
				}

				if(OK==dwResult)
				{
					dwResult=BSP_GetFPGAStatus(2);
				}
			    dwTempVer = FILE_VER_VALUE(BSP_MAINLOGSOFT1);
			    pbyVer[2] = ( (dwTempVer & 0x000000FF) >> 0 );
			    pbyVer[1] = ( (dwTempVer & 0x0000FF00) >> 8 );
			    pbyVer[0] = ( (dwTempVer & 0x00FF0000) >> 16);
			    dwTempVer = FILE_VER_VALUE(BSP_MAINLOGSOFT2);
			    pbyVer[5] = ( (dwTempVer & 0x000000FF) >> 0 );
			    pbyVer[4] = ( (dwTempVer & 0x0000FF00) >> 8 );
			    pbyVer[3] = ( (dwTempVer & 0x00FF0000) >> 16);

				break;
			case BSP_BOARD_TYPE_OP: 	/* OP */	
				dwFileNum=3;
				if(OK==dwResult)
				{
					dwResult=BSP_GetFPGAStatus(1);
				}

				if(OK==dwResult)
				{
					dwResult=BSP_GetFPGAStatus(2);
				}

				if(OK==dwResult)
				{
					dwResult=BSP_GetFPGAStatus(3);
				}
			    dwTempVer = FILE_VER_VALUE(BSP_MAINLOGSOFT1);
			    pbyVer[2] = ( (dwTempVer & 0x000000FF) >> 0 );
			    pbyVer[1] = ( (dwTempVer & 0x0000FF00) >> 8 );
			    pbyVer[0] = ( (dwTempVer & 0x00FF0000) >> 16);
			    dwTempVer = FILE_VER_VALUE(BSP_MAINLOGSOFT2);
			    pbyVer[5] = ( (dwTempVer & 0x000000FF) >> 0 );
			    pbyVer[4] = ( (dwTempVer & 0x0000FF00) >> 8 );
			    pbyVer[3] = ( (dwTempVer & 0x00FF0000) >> 16);
			    dwTempVer = FILE_VER_VALUE(BSP_MAINLOGSOFT3);
			    pbyVer[8] = ( (dwTempVer & 0x000000FF) >> 0 );
			    pbyVer[7] = ( (dwTempVer & 0x0000FF00) >> 8 );
			    pbyVer[6] = ( (dwTempVer & 0x00FF0000) >> 16);

				break;
		}					
				
		*pbyNum=dwFileNum;

		return ;

	
	
	}




/*
 * 读取BootRom 版本，版本格式：V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:版本号
    return:
        VOID
*/
VOID BSP_GetBootromVer( BYTE *pbyVer )
{
    UINT8 s[6] ;
    if(NULL==pbyVer)
    {
        return ;
    }
    bcopy((UINT8*)BOOTROM_VERSION_ADDR, s, 6 ) ;
    pbyVer[2] = ( s[0] - '0' ) * 10 + s[1] - '0' ;
    pbyVer[1] = ( s[2] - '0' ) * 10 + s[3] - '0' ;
    pbyVer[0] = ( s[4] - '0' ) * 10 + s[5] - '0' ;

}



/*
 * 读取最小系统 版本，版本格式：V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:版本号
    return:
        VOID
*/
VOID BSP_GetMiniSysVer( BYTE *pbyVer )
{
    DWORD dwTempVer;

    if(NULL==pbyVer)
    {
        return ;
    }

	if (OK != BSP_GetMiniSystemStatus())
	{

		pbyVer[2] = 0xff;
		pbyVer[1] = 0xff;
		pbyVer[0] = 0xff;

		return ;
	}

    dwTempVer = FILE_VER_VALUE(BSP_MINSOFT);
    pbyVer[2] = ( (dwTempVer & 0x000000FF) >> 0 );
    pbyVer[1] = ( (dwTempVer & 0x0000FF00) >> 8 );
    pbyVer[0] = ( (dwTempVer & 0x00FF0000) >> 16);
}



/*
 * 读取系统软件 版本，版本格式：V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:版本号
    return:
        VOID
*/
VOID BSP_GetSysSoftVer( BYTE *pbyVer )
{
    DWORD dwTempVer;
    if(NULL==pbyVer)
    {
        return ;
    }
	if (OK!=BSP_GetMainSoftStatus(1))
	{
		pbyVer[2]=0xff;
		pbyVer[1]=0xff;
		pbyVer[0]=0xff;
		return;
	}
	
    dwTempVer=FILE_VER_VALUE(BSP_MAINSOFT);
    pbyVer[2]=( (dwTempVer & 0x000000FF) >> 0 );
    pbyVer[1]=( (dwTempVer & 0x0000FF00) >> 8 );
    pbyVer[0]=( (dwTempVer & 0x00FF0000) >> 16);

}



/*
获取本板在位信息
 -----------------------------------
     input:
         VOID:
     output:
         VOID:
     return:
         SYS_OK
         SYS_ERROR
         1      :本板在线
         0      :本板不在线
 */
SDWORD BSP_BoardIsOnline(VOID)

{
    BYTE byTempBT[3];

	if (OK ==	 I2cReadCpld(byTempBT,3))
        {
            return byTempBT[2]&(0x80);
        }
    else
        {
            return SYS_ERROR;
        }
    
    
}













/*
获取本板槽位号
 -----------------------------------
     input:
         VOID:
     output:
         VOID:pbyBNo 槽位号
     return:
         SYS_OK
         SYS_ERROR
 */
 SDWORD BSP_GetBoardslotNo( BYTE * pbyBNo )

{
    END_OBJ * pstemEnd = NULL;
    pstemEnd = (END_OBJ *)endFindByName(BSP_ETH_NAME,BSP_ETH_UNIT);
    
    if((NULL == pstemEnd)||(NULL == pbyBNo))
    {
        return SYS_ERROR;
    }

    *pbyBNo = (pstemEnd->mib2Tbl.ifPhysAddress.phyAddress[pstemEnd->mib2Tbl.ifPhysAddress.addrLength - 1]);
    return SYS_OK;
}





/*
 * 获取所有FPGA 状态
-----------------------------------
    input:
        VOID
    output:
        DWORD AllFPGAStatus 
        FPGA 状态. bit 1 －4 分别代表了4个主FPGA ;bit 5-8 代表4个备用FPGA 
                             0 : 正常 1:FPGA 丢失
    return:
        SYS_OK
        SYS_ERROR
*/
SDWORD BSP_GetAllFPGAStatus(DWORD *AllFPGAStatus)
{
	SDWORD dwResult=OK;
	DWORD  bordType=0;
	DWORD  dwLedState=0;
	if(NULL==AllFPGAStatus)
	{
     return SYS_ERROR;
	}
	*AllFPGAStatus =0 ;
	bordType=BSP_GetBoardTypeId();
	
	dwLedState=BSP_SysRunLedFlic(BSP_LED_FAST);
	switch (bordType)
	{
		case BSP_BOARD_TYPE_CS:		/* SC */
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(3);
				if(OK!=dwResult)
				{
				*AllFPGAStatus |= 1<<3;
				}
				dwResult=BSP_GetFPGAStatus(7);
				if(OK != dwResult)
				{
				*AllFPGAStatus |= 1<<7;
				}
			}
			break;
		case BSP_BOARD_TYPE_HD:		/* HD */
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(1);
				if(OK!=dwResult)
				{
				*AllFPGAStatus |= 1<<1;
				}
				dwResult=BSP_GetFPGAStatus(5);
				if(OK != dwResult)
				{
				*AllFPGAStatus |= 1<<5;
				}
				dwResult=BSP_GetFPGAStatus(2);
				if(OK!=dwResult)
				{
				*AllFPGAStatus |= 1<<2;
				}
				dwResult=BSP_GetFPGAStatus(6);
				if(OK != dwResult)
				{
				*AllFPGAStatus |= 1<<6;
				}
			}
			break;
		case BSP_BOARD_TYPE_SD:		/* SD */
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(1);
				if(OK!=dwResult)
				{
				*AllFPGAStatus |= 1<<1;
				}
				dwResult=BSP_GetFPGAStatus(5);
				if(OK != dwResult)
				{
				*AllFPGAStatus |= 1<<5;
				}
				dwResult=BSP_GetFPGAStatus(2);
				if(OK!=dwResult)
				{
				*AllFPGAStatus |= 1<<2;
				}
				dwResult=BSP_GetFPGAStatus(6);
				if(OK != dwResult)
				{
				*AllFPGAStatus |= 1<<6;
				}
			}
			break;
		case BSP_BOARD_TYPE_OP:		/* OP */
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(1);
				if(OK!=dwResult)
				{
				*AllFPGAStatus |= 1<<1;
				}
				dwResult=BSP_GetFPGAStatus(5);
				if(OK != dwResult)
				{
				*AllFPGAStatus |= 1<<5;
				}
				dwResult=BSP_GetFPGAStatus(2);
				if(OK!=dwResult)
				{
				*AllFPGAStatus |= 1<<2;
				}
				dwResult=BSP_GetFPGAStatus(6);
				if(OK != dwResult)
				{
				*AllFPGAStatus |= 1<<6;
				}
				dwResult=BSP_GetFPGAStatus(3);
				if(OK!=dwResult)
				{
				*AllFPGAStatus |= 1<<3;
				}
				dwResult=BSP_GetFPGAStatus(7);
				if(OK != dwResult)
				{
				*AllFPGAStatus |= 1<<7;
				}
			}
			break;
		default:
			dwResult=ERROR;
			break;
	}
	BSP_SysRunLedFlic(dwLedState);
	return dwResult;
}













/*
 * 加载fpga
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        SYS_OK
        SYS_ERROR
*/
SDWORD BSP_LoadFpga()
{
	SDWORD dwResult=OK;
	DWORD  bordType=0;
	DWORD  dwLedState=0;
	bordType=BSP_GetBoardTypeId();
	
	dwLedState=BSP_SysRunLedFlic(BSP_LED_FAST);
	switch (bordType)
	{
		case BSP_BOARD_TYPE_CS:		/* SC */
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(3);
				if(OK != dwResult)
				{
					dwResult=BSP_GetFPGAStatus(7);
				}
			}
			if(OK==dwResult)
			{
				dwResult=BSP_LoadFpga_ALTERA(1);
			}
			break;
		case BSP_BOARD_TYPE_HD:		/* HD */
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(1);
				if(OK != dwResult)
				{
					dwResult=BSP_GetFPGAStatus(5);
				}
			}
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(2);
				if(OK != dwResult)
				{
					dwResult=BSP_GetFPGAStatus(6);
				}

			}
			
			if(OK==dwResult)
			{
				dwResult=BSP_LoadFpga_LATTICE(2);
			}
			break;
		case BSP_BOARD_TYPE_SD:		/* SD */
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(1);
				if(OK != dwResult)
				{
					dwResult=BSP_GetFPGAStatus(5);
				}
				
			}
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(2);
				if(OK != dwResult)
				{
					dwResult=BSP_GetFPGAStatus(6);
				}
				
			}
			
			if(OK==dwResult)
			{
				dwResult=BSP_LoadFpga_LATTICE(2);
			}
			break;
		case BSP_BOARD_TYPE_OP:		/* OP */
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(1);
				
				if(OK != dwResult)
				{
					dwResult=BSP_GetFPGAStatus(5);
				}
			}
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(2);
				
				if(OK != dwResult)
				{
					dwResult=BSP_GetFPGAStatus(6);
				}
			}
			
			if(OK==dwResult)
			{
				dwResult=BSP_GetFPGAStatus(3);
				if(OK != dwResult)
				{
					dwResult=BSP_GetFPGAStatus(7);
				}
				
			}
			
			if(OK==dwResult)
			{
				dwResult=BSP_LoadFpga_ALTERA(1);
			}
			
			if(OK==dwResult)
			{
				dwResult=BSP_LoadFpga_LATTICE(2);
			}
			break;
		default:
			dwResult=ERROR;
			break;
	}
	BSP_SysRunLedFlic(dwLedState);



	return dwResult;



}







/*
 * RUN 灯闪烁
-----------------------------------
    input:
        dwFlickerType:闪烁类型 1:快闪2:慢闪3:常灭4:常亮
    output:
        VOID
    return:
        LastLedSta:LED 灯的设置前状态
*/
DWORD BSP_SysRunLedFlic( DWORD dwFlickerType )
{
	static DWORD sdwLEDState=0;
	DWORD dwtempLEDState=sdwLEDState;
	sdwLEDState=dwFlickerType;
    switch(dwFlickerType)
    {
        case 1:
            LedRunStateChg(LED_SIK,LED_SIK_FAST);
            break;

        case 2:
            LedRunStateChg(LED_SIK,LED_SIK_SLOW);
            break;

        case 3:
            LedRunStateChg(LED_OFF,LED_DIV_DEF);
            break;

        case 4:
            LedRunStateChg(LED_ON,LED_DIV_DEF);
            break;

        default:
            break;
            

    }
    return dwtempLEDState;

}



/*
 * Alarm 灯闪烁
-----------------------------------
    input:
        dwFlickerType:闪烁类型 1:快闪2:慢闪3:常灭4:常亮
    output:
        VOID
    return:
        LastLedSta:LED 灯的设置前状态
*/

DWORD BSP_SysAlarmLedFlic( DWORD dwFlickerType )
{
	static DWORD sdwLEDState=0;
	DWORD dwtempLEDState=sdwLEDState;
	sdwLEDState=dwFlickerType;

    switch(dwFlickerType)
    {
        case 1:
            LedAlarmStateChg(LED_SIK,LED_SIK_FAST);
            break;

        case 2:
            LedAlarmStateChg(LED_SIK,LED_SIK_SLOW);
            break;

        case 3:
            LedAlarmStateChg(LED_OFF,LED_DIV_DEF);
            break;

        case 4:
            LedAlarmStateChg(LED_ON,LED_DIV_DEF);
            break;

        default:
            break;
            

    }
    return dwtempLEDState;

}





/*
 * *设置MAC 地址
 Mac[0]=a,  Mac[1]=b, Mac[2]=c,Mac[3]=d,  Mac[4]=e, Mac[5]=f
-----------------------------------
    input:
        pbyMac:MAC 地址
    output:
        VOID
    return:
        SYS_OK
        SYS_ERROR


SDWORD BSP_DrvSetMac(BYTE *pbyMac)
{
    return OK;
}
*/





/*
 * *获取MAC 地址
 Mac[0]=a,  Mac[1]=b, Mac[2]=c,Mac[3]=d,  Mac[4]=e, Mac[5]=f
-----------------------------------
    input:
        VOID
    output:
        pbyMac:MAC 地址
    return:
        SYS_OK
        SYS_ERROR
*/

SDWORD BSP_DrvGetMac(BYTE *pbyMac)
{
    END_OBJ * pstemEnd = NULL;

    pstemEnd = (END_OBJ *)endFindByName(BSP_ETH_NAME,BSP_ETH_UNIT);
    if((NULL == pstemEnd)||(NULL == pbyMac))
    {
        return SYS_ERROR;
    }
    memcpy((VOID * )pbyMac, (const void *)(pstemEnd->mib2Tbl.ifPhysAddress.phyAddress),
        (size_t)(pstemEnd->mib2Tbl.ifPhysAddress.addrLength));
    return SYS_OK;
}






/* 单板驱动初始化
---------------------------------------
    return:
        OK 
        ERROR
*/
SDWORD BSP_DrvInit()
{
		
		DWORD dwTmpYear; 
		DWORD dwTmpMonth; 
		DWORD dwTmpDay;
		DWORD dwTmpHours; 
		DWORD dwTmpMinutes; 
		DWORD dwTmpSecond;
		struct tm psCurTime;
		CBIO_DEV_ID cbio ; 	
		DWORD  bordType=0;
		DWORD  dwLedState=0;
		SDWORD sdwResult=OK;

        DWORD dwIndex = 0;

		/* 开启软件狗*/
		initDog();
		dev_I2cInit();
		bordType=BSP_GetBoardTypeId();
		/*为主控设置当前时间*/
		if( BSP_BOARD_TYPE_CS == bordType)
		{
	
			if(OK != GetRtc(&dwTmpYear,&dwTmpMonth,&dwTmpDay,&dwTmpHours,&dwTmpMinutes,&dwTmpSecond))
			{
			   /* return;*/
			}
	
			dwTmpYear+=2000;
			psCurTime.tm_sec   = dwTmpSecond  ;
			psCurTime.tm_min   = dwTmpMinutes  ;
			psCurTime.tm_hour  = dwTmpHours ;
			psCurTime.tm_mday  = dwTmpDay ;
			psCurTime.tm_mon   = dwTmpMonth  ;
			psCurTime.tm_year  = dwTmpYear ;
	
			if(OK != (BSP_SetCurSysDateTime(&psCurTime)))
			{
			   /* return;*/
			}
	
	
		}
	   /* 安装文件系统*/
#if 0	    
		cbio=ramDiskDevCreate((void *)0x23800000,512,17,0x400000/512,0);
		if(cbio!=NULL)
		{	
			dosFsDevCreate("/ram0",cbio,20,NONE);
			if(ERROR==chkdsk("/ram0",2,0))
				{
					printf(" \n Format filesystem 0 !!!\n");
					dosFsVolFormat(cbio,DOS_OPT_BLANK | DOS_OPT_QUIET, NULL);
				}
		}
		/* 安装文件系统2*/

		cbio=ramDiskDevCreate(0x23C00000,512,17,0x400000/512,0);
		if(cbio!=NULL)
		{	
			dosFsDevCreate("/ram1",cbio,20,NONE);
			if(ERROR==chkdsk("/ram1",2,0))
				{
					printf(" \n Format filesystem 1 !!!\n");
					dosFsVolFormat(cbio,DOS_OPT_BLANK | DOS_OPT_QUIET, NULL);
				}
		}
		
#endif
		/*485接口初始化*/
		/*ioDefPathSet("/tffs0");*/
		LedDrvInit();
		/*关闭指示灯 */
		BSP_SysRunLedFlic(BSP_LED_OFF);
		BSP_SysAlarmLedFlic(BSP_LED_OFF);

		/*安装文件系统*/
		
		if (tffsDrv () != OK)
		{
			printf("Could not initialize tffsDrv.\n");
		   /* return ;*/
		}
	
		printf ("Attaching to TFFS... ");
	
		if (usrTffsConfig (0, 0, "/tffs0") == ERROR)
		{
			printf ("usrTffsConfig failed.	 format tffs now\n");
			/**/
			
			dwLedState=BSP_SysRunLedFlic(BSP_LED_FAST);
			if( sysTffsFormat( 0,0 ) == ERROR )
			{
				printf( "tffsDevFormat ERROR!\n" );
			   /* return ;*/
			}
	
			BSP_SysRunLedFlic(dwLedState);
					
			/**/		
			printf ("Attaching to TFFS... ");
			usrTffsConfig (0, 0, "/tffs0") ;
			ioDefPathSet("/ram0") ;
			printf ("done.\n");
		}
		else
		{
			ioDefPathSet("/ram0") ;
			printf ("done.\n");
		}  

	/* 点灯 加载FPGA*/
	
		if(BSP_SOFT_MINSYS==sGlobaSysData->dwSoftState)
			{
			BSP_SysRunLedFlic(BSP_LED_OFF);
			BSP_SysAlarmLedFlic(BSP_LED_SLOW);
			}
		else if(BSP_SOFT_MAINSOFT==sGlobaSysData->dwSoftState)
			{
			BSP_SysRunLedFlic(BSP_LED_SLOW);
			BSP_SysAlarmLedFlic(BSP_LED_OFF);
			}
		else if(BSP_VXWORKS_DEBUG==sGlobaSysData->dwVxworksDebuger)
			{
			
			BSP_SysRunLedFlic(BSP_LED_SLOW);
			BSP_SysAlarmLedFlic(BSP_LED_OFF);
	
			}

		urgencyInit();
		UrgencyStart(BSP_CHANNEL_ETH,BSP_485_MIRR);
		BSP_SoftWareUPinit();
		BSP_TimeInit();
		InitSi5326();

        for(dwIndex = 0; dwIndex < 10; dwIndex ++)
        {
            BSP_GetVoltageStatus(dwIndex); 
        }
        
		if( BSP_BOARD_TYPE_CS == bordType || BSP_BOARD_TYPE_OP== bordType )
		{
			BSP_NandFlashFileInit(0);
		}
		if(BSP_BOARD_TYPE_OP == bordType)
		{
			BSP_MulAdd(BSP_OP_PKG);
		}
		sGlobaSysData->dwResetCont = 0;

}






/*获取RTC的日期(年月日周)
---------------------------------------
    output:
        psCurTime : 系统当前时间
    return:
        SYS_OK ---------- 成功获取
        SYS_ERROR-------- 错误
*/

SDWORD BSP_GetCurSysDateTime(struct tm *psCurTime)
{

    struct timespec stemptime;
    
    if(NULL==psCurTime)
    {
        return SYS_ERROR;
    }


    if(SYS_OK==clock_gettime(CLOCK_REALTIME,&stemptime))
    {
        
        localtime_r(&(stemptime.tv_sec),psCurTime);
		psCurTime->tm_year +=1900;
        psCurTime->tm_mon  += 1;     /*tm_mon [0-11]*/
        return SYS_OK;

    }

    return SYS_ERROR;

}







/* 设置RTC的日期(年月日周)
---------------------------------------
    input:
        psCurTime :当前时间
    return:
        OK ---------- 设置正确
        ERROR-------- 错误
*/

SDWORD BSP_SetCurSysDateTime(struct tm *psCurTime)
{
        struct timespec stemptime;

        if(NULL==psCurTime)
        {
            return SYS_ERROR;
        }

        psCurTime->tm_year -=1900;
        psCurTime->tm_mon  -= 1;     /*tm_mon [0-11]*/
        
        stemptime.tv_nsec=0;
        stemptime.tv_sec=mktime(psCurTime);

        if(OK!=clock_settime(CLOCK_REALTIME, &stemptime))
            {
                return SYS_ERROR;
            }
  
		/*psCurTime->tm_year -=100; */
		psCurTime->tm_mon  += 1;     /*RTC tm_mon [1-12]*/         
        if(
		
        OK != SetRtc(psCurTime->tm_year,psCurTime->tm_mon,
                          psCurTime->tm_mday,psCurTime->tm_hour,
                          psCurTime->tm_min,psCurTime->tm_sec)
           )
        {
            return ERROR;
        }
            
}





/* 获取从1970 年开始到现在，已经走过的秒数
---------------------------------------
    output:
        pdwCurTime　: 从1970 年开始到现在，已经走过的秒数
    return:
        OK ---------- 正确获取
        ERROR--------错误
*/

SDWORD BSP_GetCurSysDateTimeBySecond(DWORD * pdwCurTime)
{
    

    struct timespec stemptime;
    if(NULL==pdwCurTime)
    {
        return SYS_ERROR;
    }
    if(SYS_OK==clock_gettime(CLOCK_REALTIME,&stemptime))
    {
        *pdwCurTime=stemptime.tv_sec;
        return SYS_OK;
    }

    return SYS_ERROR;

}





/*得到目前温度状态
	小数位数 5 
---------------------------------------
    inPut:
         byChipNo:温度芯片号:0,1,2...
	output:
		VOID
    	return:
        	电压0xFFFFFFFF 无法读取
*/

SDWORD BSP_GetTemperatureVal(BYTE byChipNo )
{
    return getTemperatureValue(0);
}




/*得到目前电压状态
---------------------------------------
    inPut:
         byChipNo:电压通道号:0,1,2...
	output:
		VOID
    	return:
        	电压值 单位毫伏
        	0xFFFFFFFF 无法读取

通道号	监控电压值	SC			OP			SD				HD
0	1.0V				
1	1.2V			√			√			√				√
2	1.25V						√			√				√
3	1.25V						√			√				√
4	1.5V				
5	1.8V			√			√			√				√
6	2.5V			√			√			√				√
7	3.3V			√			√			√				√
8	5.0V			√			√			√				√
9	3.3V			√			√			√				√



*/

SDWORD BSP_GetVoltageStatus(BYTE byChipNo)
{
	SDWORD dwtemVol=getVoltage(byChipNo);
	if(0xffffffff==dwtemVol)
	{
		return 0xffffffff;
	}
	else
	{
		return dwtemVol*2;
	}
}







/*检查 Bootrom
---------------------------------------
    return:
        OK ---------- 读取
        ERROR-------- 错误
永远返回OK
*/
SDWORD BSP_GetBootromStatus()
{
    return OK;
}












/*
* 查询单板制造信息
* 输出:
*        pDateTime: 生产日期
*        abyArea  : 产地
*        abyVender: OEM厂商
*        abySeq   : 序列号
* 返回值:
*        成功/失败
生产信息:
36字节生产日期:
4:秒
4:分
4:小时
4:日
4:月
4:年
4:保留
4:保留
4:保留
产地  :30字节
厂商  :30字节
序列号:30字节

*/
WORD BSP_GetManInfo(struct tm* pDateTime, BYTE abyArea[128], BYTE abyVender[128], BYTE abySeq[32])
{
	BYTE byTempInfo[128];
	BYTE * pbyTempInfo =byTempInfo;
	struct tm *pstTempData = (struct tm *)byTempInfo;
	if (OK==eepromRead(0,&byTempInfo,128))
		{
			/* tm 共用掉36 字节*/
			pDateTime->tm_sec  = pstTempData->tm_sec ; 
			pDateTime->tm_min  = pstTempData->tm_min ; 
			pDateTime->tm_hour = pstTempData->tm_hour;
			pDateTime->tm_mday = pstTempData->tm_mday;
			pDateTime->tm_mon  = pstTempData->tm_mon ; 
			pDateTime->tm_year = pstTempData->tm_year;
			pDateTime->tm_wday = pstTempData->tm_wday;
			pDateTime->tm_yday = pstTempData->tm_yday;
			pDateTime->tm_isdst= pstTempData->tm_isdst;
			pbyTempInfo+=BSP_TM_LENGTH;
			memcpy((void *)abyArea,(const void * )(pbyTempInfo),(size_t)BSP_AREA_LENGTH);
			pbyTempInfo+=BSP_AREA_LENGTH;
			memcpy((void *)abyVender,(const void * )(pbyTempInfo),(size_t)BSP_VENDER_LENGTH);
			pbyTempInfo+=BSP_VENDER_LENGTH;
			memcpy((void *)abySeq,(const void * )(pbyTempInfo),(size_t)BSP_SEQ_LENGTH);
			return OK;
		}
	return ERROR;

}



/*CPU 占有率查询
---------------------------------------
    return:
	返回CPU 占有率，如50表示50%
*/

SDWORD BSP_CpuUsage(VOID)
{
    return 50;
}



/*内存使用率
---------------------------------------
    return:
	返回内存 占有率，如50表示50%
*/

SDWORD BSP_MemUsage(VOID)
{
   SDWORD   dwSum1 = 0;
   BSP_memPartShow(&dwSum1);
   return dwSum1;
}

/*复位FPGA 
---------------------------------------
    inPut:
         byChipNo:0 全体FPGA 1 LATTICE 2 ALTERA
	output:
		VOID
    	return:
            OK ---------- 正确
            ERROR-------- 错误
*/

SDWORD BSP_ResetFpga(BYTE byChipNo)
{
    if(0==byChipNo)
    {
        ResetFpga_LATTICE();
        ResetFpga_ALTERA();
        return OK;
    }
    if(1==byChipNo)
    {
        ResetFpga_LATTICE();
        return OK;
    }
    if(2==byChipNo)
    {
        ResetFpga_ALTERA();
        return OK;
    }

    
    return ERROR;
}




/* 加载指定地址的软件*/
SDWORD BSPGetSoft(DWORD dwBaseAdd,BYTE * pbyBuffer ,DWORD *dwBufferLength)
{
    DWORD   dwSum1 = 0;

    DWORD   dwFileLength = FILE_LEN_VALUE(dwBaseAdd);
    DWORD   dwFileStart = *((DWORD *)(dwBaseAdd+FILE_OFF))+dwBaseAdd;
	
	if(OK == inflate((BYTE*)dwFileStart, (BYTE*)pbyBuffer, dwFileLength,dwBufferLength))
    {
  		return OK;
    }
    else
    {
        return INFLATE_ERROR;
    }

}


/* 软件获取测试*/


SDWORD BSPGetSoft_TEST()
{
	DWORD   dwSum1 = 0;
	BYTE * pbyBuffer=(BYTE *)malloc(0x600000);
	DWORD dwBufferLength=0x600000;
	DWORD dwBaseAdd =BSP_MAINSOFT;
	dwSum1=BSPGetSoft(dwBaseAdd,pbyBuffer,&dwBufferLength);
	free(pbyBuffer);
	return dwSum1;
	
}

/* 生产测试代码*/
/*
1、PCB硬件版本信息
2、板卡类型
3、槽位号
4、在位信息
5、读写EEPROM AT24C01
6、读写1014A
7、读写Si5326
*/
SDWORD BSP_TEST(VOID)
{
	SWORD  swResultS = OK;
	struct tm pDateTime;
	BYTE abyArea[128];
	BYTE abyVender[128];
	BYTE abySeq[32];
	BYTE byVer[3];
	printf("\n soft Test Start :\n");
	BSP_GetPcbVer(byVer);
	printf(" PCB ver: %d .%d.%d\n",byVer[0],byVer[1],byVer[2]);
	byVer[0]=BSP_GetBoardTypeId();
	printf(" Board type %d \n ",byVer[0]);
	swResultS=BSP_GetBoardslotNo(&byVer[0]);
	if(SYS_OK == swResultS)
	{
		printf(" Board slotNo %d \n ",byVer[0]);
	}
	else
	{
		printf(" Board slotNo TEST Error !!!\n ");
	}
	swResultS=BSP_BoardIsOnline();
	if(1==swResultS)
	{
		printf(" Board ON line !!!\n ");
	}
	if(0==swResultS)
	{
		printf(" Board off line !!!\n ");
	}

	if ( OK==BSP_GetManInfo(&pDateTime, abyArea, abyVender, abySeq) )
	{
		printf(" \n tm_sec  :  %d   ", pDateTime.tm_sec  ); 
		printf(" \n tm_min  :  %d   ", pDateTime.tm_min  ); 
		printf(" \n tm_hour :  %d   ", pDateTime.tm_hour );
		printf(" \n tm_mday :  %d   ", pDateTime.tm_mday );
		printf(" \n tm_mon  :  %d   ", pDateTime.tm_mon  ); 
		printf(" \n tm_year :  %d   ", pDateTime.tm_year );
		printf(" \n tm_wday :  %d   ", pDateTime.tm_wday );
		printf(" \n tm_yday :  %d   ", pDateTime.tm_yday );
		printf(" \n tm_isdst:  %d \n", pDateTime.tm_isdst);
		printf(" \n abyArea !!!\n ");
		d(abyArea,BSP_AREA_LENGTH,1);
		printf(" \n abyVender !!!\n ");
		d(abyVender,BSP_VENDER_LENGTH,1);
		printf(" \n abySeq !!!\n ");
		d(abySeq,BSP_SEQ_LENGTH,1);
	}
/*
    for (i = 0; i < 10; i++)
    {
        sdwVol[i] = BSP_GetVoltageStatus(i);
        printf(" \n Voltage %d:  %d \n",i, sdwVol[i]);
    }
*/
	printf(" \n Voltage 0:  %d \n",BSP_GetVoltageStatus(0));
	printf(" \n Voltage 1:  %d \n",BSP_GetVoltageStatus(1));
	printf(" \n Voltage 2:  %d \n",BSP_GetVoltageStatus(2));
	printf(" \n Voltage 3:  %d \n",BSP_GetVoltageStatus(3));
	printf(" \n Voltage 4:  %d \n",BSP_GetVoltageStatus(4));
	printf(" \n Voltage 5:  %d \n",BSP_GetVoltageStatus(5));
	printf(" \n Voltage 6:	%d \n",BSP_GetVoltageStatus(6));
	printf(" \n Voltage 7:  %d \n",BSP_GetVoltageStatus(7));
	printf(" \n Voltage 8:  %d \n",BSP_GetVoltageStatus(8));
	printf(" \n Voltage 9:  %d \n",BSP_GetVoltageStatus(9));
    

	printf(" \n InitSi5326 \n");

	InitSi5326();
	printf(" \n the board temperature : %d \n",getTemperatureValue(0));

	/* CS板特殊定义*/	
#ifdef BOARD_CS
	if(OK==BSP_SetCurTimeTest(0,0,0,1,5,2008))
	{
		printf(" \n RTC time set to 2008-5-1 00:00:00 OK !\n");
	}
	else
	{
		printf(" \n RTC time set ERROR !!!\n");	
	}

#endif
	/* HD板特殊定义*/	
#ifdef BOARD_HD

#endif
	/* SD板特殊定义*/	
#ifdef BOARD_SD

#endif
	/* OP板特殊定义*/	
#ifdef BOARD_OP

#endif

	return swResultS;
}

/*文件系统接口
标准DOS 文件接口


*/

/*LCD 串口接口
标准IO 接口


*/

/* 接口测试函数 以下函数BSP 测试接口用，不对外提供*/

/*
struct tm
	{
	int tm_sec;	 //seconds after the minute	- [0, 59] 
	int tm_min; 	 //minutes after the hour	- [0, 59] 
	int tm_hour;	 //hours after midnight		- [0, 23] 
	int tm_mday; //day of the month		- [1, 31] 
	int tm_mon;	 //months since January		- [0, 11] 
	int tm_year;	 //years since 1900	
	int tm_wday; //days since Sunday		- [0, 6] 
	int tm_yday;	 //days since January 1		- [0, 365]
	int tm_isdst;	 //Daylight Saving Time flag 
	};

struct timespec
    {
                            //interval = tv_sec*10**9 + tv_nsec 
    time_t tv_sec;	//seconds 
    long tv_nsec;		// nanoseconds (0 - 1,000,000,000) 
    };


*/

SDWORD BSP_SetCurTimeTest(DWORD tm_sec, DWORD tm_min, DWORD tm_hour, DWORD tm_mday, 
                                    DWORD tm_mon, DWORD tm_year)
{

    struct tm stemptm;
    
    bzero((void *)&stemptm,sizeof(struct tm));

    stemptm.tm_sec   = tm_sec  ;
    stemptm.tm_min   = tm_min  ;
    stemptm.tm_hour  = tm_hour ;
    stemptm.tm_mday  = tm_mday ;
    stemptm.tm_mon   = tm_mon  ;
    stemptm.tm_year  = tm_year ;
    stemptm.tm_wday  = 0 ;
    stemptm.tm_yday  = 0  ;
    stemptm.tm_isdst = 0 ;
    
    return BSP_SetCurSysDateTime( &stemptm );
}

SDWORD BSP_GetCurTimeTest()
{
        BYTE abyTmpData[100];
        size_t datalentth =sizeof(abyTmpData);
        struct tm stemptm;
        bzero(abyTmpData, datalentth);
        BSP_GetCurSysDateTime(&stemptm);
        
        asctime_r(&stemptm, abyTmpData, &datalentth);
        printf(abyTmpData);
}

DWORD BSP_GetCurSecondTest()
{
    DWORD dwtemp=0;
    BSP_GetCurSysDateTimeBySecond(&dwtemp);
    return dwtemp;
}

/* 5324 调试用相关接口*/
/* 5324 读取函数*/
SDWORD BSP_Read5324(DWORD dwPage,DWORD dwAdd,DWORD *pdwData0,DWORD *pdwData1, DWORD *pdwData2,DWORD *pdwData3)
{
	
	DWORD dwTempData0 ;
	DWORD dwTempReg0 ;
	DWORD dwTempReg1 ;
	DWORD dwTempReg2 ;
	DWORD dwTempReg3 ;

	/*BSP_enable_mdi(BSP_MACADD);*/
	/* 设置页寄存器*/
	dwTempData0 = 0;
	dwTempData0 = dwPage<<8;
	dwTempData0 |= 1;
	/*BSP_write_phy(BSP_MACADD,15,16,dwTempData0);*/

	/* 设置寄存器地址*/
	dwTempData0 = 0;
	dwTempData0 = dwAdd<<8;
	dwTempData0 |=2;
	/*BSP_write_phy(BSP_MACADD,15,17,dwTempData0);*/
	/*查询操作是否完成 */
	do
	{
		/*BSP_read_phy(BSP_MACADD,15,17,&dwTempData0);*/
		dwTempData0 &= 0x00000003;
		
	}while(dwTempData0);

	/* 判断数据正确性*/
	/*BSP_read_phy(BSP_MACADD,15,18,&dwTempData0);*/
	dwTempData0 &= 0x00000003;
	if(dwTempData0)
	{
		return ERROR;
	}
	/* 读取数据*/
	/*BSP_read_phy(BSP_MACADD,15,24,&dwTempReg0);
	BSP_read_phy(BSP_MACADD,15,25,&dwTempReg1);
	BSP_read_phy(BSP_MACADD,15,26,&dwTempReg2);
	BSP_read_phy(BSP_MACADD,15,27,&dwTempReg3);*/



	if	(
		(pdwData0 == NULL)
		||(pdwData1 == NULL)
		||(pdwData2 == NULL)
		||(pdwData3 == NULL)
		)
	{
		printf("\n");
		printf("5324 reg page: %d,add %d,value %08x\n",dwPage,dwAdd,dwTempReg0);
		printf("5324 reg page: %d,add %d,value %08x\n",dwPage,dwAdd,dwTempReg1);
		printf("5324 reg page: %d,add %d,value %08x\n",dwPage,dwAdd,dwTempReg2);
		printf("5324 reg page: %d,add %d,value %08x\n",dwPage,dwAdd,dwTempReg3);		
	}
	else
		{
		*pdwData0 = dwTempReg0;
		*pdwData1 = dwTempReg1;
		*pdwData2 = dwTempReg2;
		*pdwData3 = dwTempReg3;
		}
	/*BSP_disable_mdi(BSP_MACADD);*/
	return OK;
		
		
}



/* 5324 写入函数*/
SDWORD BSP_Write5324(DWORD dwPage,DWORD dwAdd,DWORD dwData0,DWORD dwData1, DWORD dwData2,DWORD dwData3)
{
	
	DWORD dwTempData0 ;
	DWORD dwTempReg0 ;
	DWORD dwTempReg1 ;
	DWORD dwTempReg2 ;
	DWORD dwTempReg3 ;

	/*BSP_enable_mdi(BSP_MACADD);*/
	/* 设置页寄存器*/
	dwTempData0 = 0;
	dwTempData0 = dwPage<<8;
	dwTempData0 |= 1;
	/*BSP_write_phy(BSP_MACADD,15,16,dwTempData0);*/


	/*写入数据*/
	/*BSP_write_phy(BSP_MACADD,15,24,dwData0);
	BSP_write_phy(BSP_MACADD,15,25,dwData1);
	BSP_write_phy(BSP_MACADD,15,26,dwData2);
	BSP_write_phy(BSP_MACADD,15,27,dwData3);*/


	

	/* 设置寄存器地址*/
	dwTempData0 = 0;
	dwTempData0 = dwAdd<<8;
	dwTempData0 |=1;
	/*BSP_write_phy(BSP_MACADD,15,17,dwTempData0);*/


	/*查询操作是否完成 */
	do
	{
		/*BSP_read_phy(BSP_MACADD,15,17,&dwTempData0);*/
		dwTempData0 &= 0x00000003;
		
	}while(dwTempData0);


	/* 判断数据正确性*/
	/*BSP_read_phy(BSP_MACADD,15,18,&dwTempData0);*/
	dwTempData0 &= 0x00000003;
	if(dwTempData0)
	{
		return ERROR;
	}
	/*BSP_disable_mdi(BSP_MACADD);*/
	return OK;
		
		
}

void BSP_PHYRead(DWORD dwUnit)
{
	DWORD dwTempData;
	DWORD dwTempData1;
	/*BSP_enable_mdi(BSP_MACADD);*/
	for(dwTempData=0;dwTempData<32;dwTempData++)
		{
			/*BSP_read_phy(BSP_MACADD,dwUnit,dwTempData,&dwTempData1);*/
			printf("5324 Phy reg unit : %d,add %d,value %08x\n",dwUnit,dwTempData,dwTempData1);		
		}
	/*BSP_disable_mdi(BSP_MACADD);*/
	return;
}

void BSP_PHYScan()
{
	DWORD dwTempData;
	for(dwTempData=0;dwTempData<32;dwTempData++)
		{
		BSP_PHYRead(dwTempData);
		}
	return;

}

WORD BSP_InitPll(void)
{
    WORD wRet;
    wRet = InitSi5326();
}

