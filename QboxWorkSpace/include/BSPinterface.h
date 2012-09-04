/******************************************************************************


  功能描述   : 本文件统一描述BSP 对上接口


******************************************************************************/


#ifndef __BSP_BSPINTERFACE_H__
#define __BSP_BSPINTERFACE_H__


#ifdef __cplusplus
extern "C" {
#endif /* #ifndef __cplusplus */


#include "sys_include.h"
#include "Time.h"






/**************************************接口*****************************************/





/*复位单板
-----------------------------------
	input:
		resetType:复位类型01:冷复位，02:热复位
	output:
    		NA
	return:
		VOID
*/
VOID BSP_Reset(BYTE byResetType);

/*高精度时钟获取函数
---------------------------------------------------
input:
	
output:
		DaubleSecond 从BSP 初始化完成后的时间 单位 2秒
		munit DaubleSecond的下计数器  单位 1／32768 秒
return:
	VOID

如: 读出 DaubleSecond 3，munit 100 实际时间为 3*2+100*(1／32768)秒


*/
DWORD BSP_TimeGet(DWORD *DaubleSecond ,DWORD *munit);



/*
 * 读取pcb 版本，版本格式：V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:版本号
    return:
        VOID
*/
VOID BSP_GetPcbVer( BYTE *pbyVer );




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
VOID BSP_GetFpgaVer( BYTE *pbyNum,BYTE *pbyVer );



/*
 * 读取BootRom 版本，版本格式：V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:版本号
    return:
        VOID
*/
VOID BSP_GetBootromVer( BYTE *pbyVer );



/*
 * 读取最小系统 版本，版本格式：V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:版本号
    return:
        VOID
*/
VOID BSP_GetMiniSysVer( BYTE *pbyVer );



/*
 * 读取系统软件 版本，版本格式：V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:版本号
    return:
        VOID
*/
VOID BSP_GetSysSoftVer( BYTE *pbyVer );




/*
 * 读取板类型ID号
 * 返回板类型id，0:HD，1:SD，2:HDSW，
 * 3:SDSW， 4:SSC
 -----------------------------------
	 return:
		 板类型ID
 */
BYTE BSP_GetBoardTypeId( VOID );








/*
获取本板槽位号
 -----------------------------------
     input:
         VOID:
     output:
         VOID:pbyBNo 槽位号
     return:
         SYS_OK
         SYS_ERR
 */
    SDWORD BSP_GetBoardslotNo( BYTE * pbyBNo );








/*
 * 使能 硬件看门狗
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/

VOID BSP_EnableHardDog( VOID );




/*
 * 禁止 硬件看门狗
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/
VOID BSP_DisableHardDog( VOID );




/*
 * 喂硬件狗 函数
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/
VOID BSP_FeedHardDog( VOID );

/*
 * 保存文件 函数
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/
VOID BSP_SaveFile(VOID);


/*
 * 加载fpga
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        SYS_OK
        SYS_ERR
*/
SDWORD BSP_LoadFpga(VOID);





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
        SYS_ERR
*/

SDWORD  BSP_SoftUpgrade(BYTE* pbyBuffer, DWORD dwLen, DWORD dwType, 
                            DWORD dwNo, SDWORD (*softUpCallback) (DWORD*, DWORD*));




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
DWORD BSP_SysRunLedFlic( DWORD dwFlickerType );



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

DWORD BSP_SysAlarmLedFlic( DWORD dwFlickerType );







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
        SYS_ERR


SDWORD BSP_DrvSetMac(BYTE *pbyMac);


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
        SYS_ERR
*/

SDWORD BSP_DrvGetMac(BYTE *pbyMac);






/* 单板驱动初始化
---------------------------------------
    return:
        OK 
        ERROR
*/
SDWORD BSP_DrvInit();







/* 设置RTC的日期(年月日周)
---------------------------------------
    input:
        RTC_DATE_STRUCT
    return:
        OK ---------- 设置正确
        ERROR-------- 错误
SDWORD setRtcDate(tm *psValue );
*/





/*得到目前温度状态
---------------------------------------
    inPut:
         byChipNo:温度芯片号:0,1,2...
	output:
		VOID
    	return:
        	电压0xFFFFFFFF 无法读取
*/

SDWORD BSP_GetTemperatureVal(BYTE byChipNo );




/*得到目前电压状态
---------------------------------------
    inPut:
         byChipNo:电压芯片号:0,1,2...
	output:
		VOID
    	return:
        	电压0xFFFFFFFF 无法读取
*/

SDWORD BSP_GetVoltageStatus(BYTE byChipNo);



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

SDWORD BSP_DeleteSoft(DWORD dwFileNo);

SDWORD BSP_SoftBackUP(VOID);


/*检查 Bootrom
---------------------------------------
    return:
        OK ---------- 读取
        ERROR-------- 错误
*/
SDWORD BSP_GetBootromStatus();




/*检查 FPGA
---------------------------------------
    input:
    	 no: FPGA 编号01－04 主FPGA,05-08 备用FPGA
    return:
        OK ---------- 读取
        ERROR-------- 错误
*/
SDWORD BSP_GetFPGAStatus(DWORD dwNo);






/*检查 单板软件/主机软件
---------------------------------------
    input:
    	 no: 0 主软件，1备用
    return:
        OK ---------- 正确
        ERROR-------- 错误
*/
SDWORD BSP_GetMainSoftStatus(DWORD dwNo);





/*检查 最小系统
---------------------------------------
    return:
        OK ---------- 正确
        ERROR-------- 错误
*/

SDWORD BSP_GetMiniSystemStatus(VOID);







/*CPU 占有率查询
---------------------------------------
    return:
	返回CPU 占有率，如50表示50%
*/

SDWORD BSP_CpuUsage(VOID);




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
        SYS_ERR
*/

SDWORD BSP_UrgencySend(BYTE *pbyDataBuffer,DWORD dwLength);



/*获取RTC的日期(年月日周)
---------------------------------------
    output:
        psCurTime : 系统当前时间
    return:
        SYS_OK ---------- 成功获取
        SYS_ERR-------- 错误
*/


SDWORD BSP_GetCurSysDateTime(struct tm *psCurTime);


/* 设置RTC的日期(年月日周)
---------------------------------------
    input:
        psCurTime :当前时间
    return:
        OK ---------- 设置正确
        ERROR-------- 错误
*/

SDWORD BSP_SetCurSysDateTime(struct tm *psCurTime);

/* 获取从1970 年开始到现在，已经走过的秒数
---------------------------------------
    output:
        pdwCurTime　: 从1970 年开始到现在，已经走过的秒数
    return:
        OK ---------- 正确获取
        ERROR--------错误
*/

SDWORD BSP_GetCurSysDateTimeBySecond(DWORD * pdwCurTime);









/* 初始化NAND 文件系统
---------------------------------------
    input:
        Void
    return:
        OK ----------成功
        ERROR-------失败
*/
SDWORD BSP_NandFlashFileInit(DWORD dwtype);


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
SDWORD BSP_NandFlashFileGetLength(DWORD dwFileNo,DWORD * pdwFileLength);


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
SDWORD BSP_NandFlashFileWrite(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength,SDWORD (*softUpCallback) (DWORD*, DWORD*));



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
SDWORD BSP_NandFlashFileRead(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength);




/*
* 查询单板制造信息
* 输出:
*        pDateTime: 生产日期
*        abyArea  : 产地
*        abyVender: OEM厂商
*        abySeq   : 序列号
* 返回值:
*        成功/失败
*/
WORD BSP_GetManInfo(struct tm* pDateTime, BYTE abyArea[128], BYTE abyVender[128], BYTE abySeq[32]);




/*文件系统接口
标准DOS 文件接口


*/

/*LCD 串口接口
标准IO 接口


*/

/*
* 初始化系统时钟
*/
WORD BSP_InitPll(VOID);

#ifdef __cplusplus
}
#endif /* #ifndef __cplusplus */
#endif /* __BSP_BSPINTERFACE_H__ */


