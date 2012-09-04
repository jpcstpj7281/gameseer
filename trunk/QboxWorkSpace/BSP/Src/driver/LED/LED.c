/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/




/*


一）．启动系统自检阶段。

１．内存检查不通过，内存坏。运行灯常亮，单板不启动。

２．其它错误无任何表示
３．软件解压缩 运行灯，告警同时亮。


二）ＢＯＯＴＲＯＭ阶段　，告警灯，运行灯同时慢闪

三）最小系统状态，运行灯灭，告警灯慢闪

四）正常状态，告警灯灭，运行灯慢闪

五）FPGA 加载，软件升级，运行灯快闪

六)    告警时告警灯快闪

快闪:100毫秒亮，100毫秒灭
慢闪:500毫秒亮，500毫秒灭





*/
#include "Led.h"
static struct sLEDPara s_sLEDPara;
LOCAL VOID RunLedOn(VOID);
LOCAL VOID RunLedOFF(VOID);
LOCAL VOID AlarmLedON(VOID);
LOCAL VOID AlarmLedOFF(VOID);
LOCAL VOID RunLedDeal(void);
LOCAL VOID AlarmLedDeal(void);
LOCAL VOID LedTask(VOID);
 
#define BSP_AT91C_PMC       (0xFFFFFC00) 
#define BSP_PCK0 (0x40)
#define BSP_PCK1 (0x44)
#define BSP_PCK2 (0x48)
#define BSP_PCK3 (0x4C)

#define VAL_BSP_PCK0  (*((volatile DWORD *)(BSP_AT91C_PMC+BSP_PCK0)))
#define VAL_BSP_PCK0E (*((volatile DWORD *)(BSP_AT91C_PMC)))



#define PCK0_CSS   2
#define PCK0_DIV   2
#define PCK0_VAL   ((PCK0_CSS)|(PCK0_DIV<<2))
#define PCK0_EN	   (1<<8)


SDWORD LedDrvInit(void)
{
    /* 管脚初始化*/
    
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOC,BSP_ALARMLED_CIO);
    BSP_AT91F_OR_PIO_CfgOutput(BSP_PIOA,BSP_RUNLED_CIO);
	BSP_AT91F_OR_PIO_CfgPeriphA(BSP_PIOB,BSP_CLOCK_CIO);

    
    /* 设置默认参数*/
    LedStateChg(LED_ON,LED_DIV_DEF,LED_ON,LED_DIV_DEF);
	VAL_BSP_PCK0=PCK0_VAL;
	VAL_BSP_PCK0E=PCK0_EN;

    /*启动电灯任务 */
    
    taskSpawn("LED", BSP_LED_TASK, 0,1024, (FUNCPTR)LedTask, 0, 0,0, 0, 0, 0, 0, 0, 0, 0);


}

VOID LedStateChg(DWORD dwRunLEDFlg,DWORD dwRunLEDDiv,DWORD dwAlarmLEDFlg,DWORD dwAlarmLEDDiv)
{
    
    bzero((void *)&s_sLEDPara,sizeof(struct sLEDPara));
    s_sLEDPara.dwAlarmLEDDiv=dwAlarmLEDDiv;
    s_sLEDPara.dwAlarmLEDFlg=dwAlarmLEDFlg;
    s_sLEDPara.dwRunLEDDiv=dwRunLEDDiv;
    s_sLEDPara.dwRunLEDFlg=dwRunLEDFlg;
	s_sLEDPara.dwRunLEDState=LED_OFF;
	s_sLEDPara.dwAlarmLEDState=LED_OFF;
	RunLedOFF();
	AlarmLedOFF();
    return ;
}


VOID LedRunStateChg(DWORD dwRunLEDFlg,DWORD dwRunLEDDiv)
{
    s_sLEDPara.dwRunLEDDiv=dwRunLEDDiv;
    s_sLEDPara.dwRunLEDFlg=dwRunLEDFlg;
	RunLedOFF();
    return ;
}

VOID LedAlarmStateChg(DWORD dwAlarmLEDFlg,DWORD dwAlarmLEDDiv)
{
    
    s_sLEDPara.dwAlarmLEDDiv=dwAlarmLEDDiv;
    s_sLEDPara.dwAlarmLEDFlg=dwAlarmLEDFlg;
	AlarmLedOFF();
    return ;
}


LOCAL VOID LedTask(VOID)
{
    while(1)
    {
        taskDelay(10);
        s_sLEDPara.dwTimeCounter+=1;
        if(0==s_sLEDPara.dwTimeCounter%s_sLEDPara.dwRunLEDDiv)
        {
            RunLedDeal();
        }
        if(0==s_sLEDPara.dwTimeCounter%s_sLEDPara.dwAlarmLEDDiv)
        {
            AlarmLedDeal();
        }
    }

}

LOCAL VOID RunLedDeal(void)
{
    if( LED_ON ==s_sLEDPara.dwRunLEDFlg)
    {
        
        if( LED_ON ==s_sLEDPara.dwRunLEDState)
        {
            return;  
        }
        if(LED_OFF==s_sLEDPara.dwRunLEDState)
        {
            RunLedOn();
        }
    }
    else if(LED_OFF==s_sLEDPara.dwRunLEDFlg)
    {
        
        if( LED_ON ==s_sLEDPara.dwRunLEDState)
        {
            RunLedOFF();
        }
        if(LED_OFF==s_sLEDPara.dwRunLEDState)
        {
            return;  
        }
    }
    else if(LED_SIK==s_sLEDPara.dwRunLEDFlg)
    {
        if( LED_ON ==s_sLEDPara.dwRunLEDState)
        {
            RunLedOFF();  

        }
        else if(LED_OFF==s_sLEDPara.dwRunLEDState)
        {
            RunLedOn();
        }
    }

}


LOCAL VOID AlarmLedDeal(void)
{
    /* 灯设置为常开状态*/
    if( LED_ON ==s_sLEDPara.dwAlarmLEDFlg)
    {
        
        if( LED_ON ==s_sLEDPara.dwAlarmLEDState)
        {
          return;  
        }
        if(LED_OFF==s_sLEDPara.dwAlarmLEDState)
        {
            AlarmLedON();
            return ;
        }
    }
    
    /* 灯设置为常关状态*/
    else if(LED_OFF==s_sLEDPara.dwAlarmLEDFlg)
    {
        
        if( LED_ON ==s_sLEDPara.dwAlarmLEDState)
        {
            AlarmLedOFF();
            return ;
        }
        if(LED_OFF==s_sLEDPara.dwAlarmLEDState)
        {
            return;  
        }
    }
    /*灯设置为闪烁状态*/
    else if(LED_SIK==s_sLEDPara.dwAlarmLEDFlg)
    {
        if( LED_ON ==s_sLEDPara.dwAlarmLEDState)
        {
            AlarmLedOFF();
        }
        else if(LED_OFF==s_sLEDPara.dwAlarmLEDState)
        {
            AlarmLedON();  
        }
    }

}

LOCAL VOID RunLedOn(VOID)
{
    
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOA,BSP_RUNLED_CIO);
    s_sLEDPara.dwRunLEDState=LED_ON;
}

LOCAL VOID RunLedOFF(VOID)
{
    


    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOA,BSP_RUNLED_CIO);
    s_sLEDPara.dwRunLEDState=LED_OFF;
}

LOCAL VOID AlarmLedON(VOID)
{
    BSP_AT91F_OR_PIO_SetOutput(BSP_PIOC,BSP_ALARMLED_CIO);
    s_sLEDPara.dwAlarmLEDState=LED_ON;
}


LOCAL VOID AlarmLedOFF(VOID)
{

    BSP_AT91F_OR_PIO_ClearOutput(BSP_PIOC,BSP_ALARMLED_CIO);
    s_sLEDPara.dwAlarmLEDState=LED_OFF;
}

 

