#ifndef _MMAPI_H_
#define _MMAPI_H_

#ifdef __cplusplus
extern "C" {
#endif /* #ifndef __cplusplus */

#include "sys_types.h"

typedef WORD PF_MODULE_ID;

typedef SDWORD (* PF_MODULE_ENTRY)(DWORD); /* 模块加载回调类型 */
typedef SDWORD (* PF_MODULE_EXIT)(DWORD);  /* 模块卸载回调类型 */

/* 无效模块ID */
#define INVALID_MODULE_ID 0xFFFF


/*
 *	系统消息数据区格式(兼容当前的BS协议格式,今后的BS协议更改不影响系统消息协议)
 *
 *
 *     0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 0 1 2 3 4 5 6 7 
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |                  reserved (0xFFFFFFFF)                        |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |       reserved (0xFFFF)       |   module manager mail box ID  |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *    |                  reserved (0xFFFFFFFF)                        |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+    +---------------------+
 *    | 0x0000 (compliante to cmd id) |          Data length          | -->| this length includs |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+    | systemmessage id,   |
 *    |           Data length         |        reserved (0xFFFF)      |    | system sub message  |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+    | id and data         |
 *    |     system message id         |     system sub message id     |    +---------------------+
 *    +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=|
 *    |                             Data                              |
 *    |                           .... ...                            |
 *    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 *
 */


/* 系统消息定义       */
/* 系统消息为2的n次方 */

/* 系统复位消息,无子消息ID,无消息参数,系统复位之前发送该消息 */
#define PF_SYS_MSG_REBOOT       1

/* 低功耗消息,子消息ID: 0 进入低功耗, 1 退出低功耗,无消息参数 */
#define PF_SYS_MSG_STANDING_BY  2

#define PF_SYS_MSG_STANDING_BY_START 0
#define PF_SYS_MSG_STANDING_BY_END   1

/* 单板开工消息,无子消息ID,消息参数为板位号和板类型 */
#define PF_SYS_MSG_START_UP     4

/* 单板下线消息,无子消息ID,消息参数为板位号和板类型 */
#define PF_SYS_MSG_OFFLINE      8

/* 无效的子系统消息ID,用于无子消息ID的系统消息 */
#define PF_INVALID_SYS_SUB_MSG       0xFFFF


/* 模块ID分配 */














/* 功能描述: 注册模块
 *
 * 输入参数:
 * WORD      		wMailBox     		模块对外信箱ID(用来接收系统消息,如果不关心系统消息,该信箱写入0xFFFF)
 * MODULE_ID 		wModuleID    		模块ID(该ID由平台统一分配)
 * PF_MODULE_ENTRY 	pfModuleEntry		模块加载入口函数指针
 * DWORD 			dwModuleEntryPara	模块加载入口函数参数
 * PF_MODULE_EXIT   pfModuleExit        模块卸载入口函数指针
 * DWORD 			dwModuleExitPara    模块卸载入口函数参数
 * 返回: 成功/失败
 */
int PF_RegisterModule(PF_MODULE_ID 		wModuleID, 			\
                      WORD 				wMailBox, 			\
                      PF_MODULE_ENTRY 	pfModuleEntry, 		\
                      DWORD 			dwModuleEntryPara, 	\
                      PF_MODULE_EXIT    pfModuleExit,      	\
                      DWORD 			dwModuleExitPara);



/* 功能描述: 注销模块
 *
 * 输入参数:
 * MODULE_ID wModuleID  模块ID
 *
 * 返回: 成功/失败
 */
int PF_UnregisterModule(PF_MODULE_ID wModuleID);



/* 功能描述: 加载模块
 *
 * 输入参数:
 * MODULE_ID wModuleID  模块ID
 *
 * 返回: 成功/失败
 */
int PF_LoadModule(PF_MODULE_ID wModuleID);



/* 功能描述: 卸载模块
 *
 * 输入参数:
 * MODULE_ID wModuleID  模块ID
 *
 * 返回: 成功/失败
 */
int PF_UnloadModule(PF_MODULE_ID wModuleID);



/* 功能描述: 模块加载完成
 *           模块加载完成后,要调用此接口通知平台,平台在所有
 *           注册过的模块都加载完成后,才会上报开工消息
 *
 * 输入参数:
 * MODULE_ID wModuleID  模块ID
 *
 * 返回: 成功/失败
 */
int PF_ModuleLoaded(PF_MODULE_ID wModuleID);



/* 功能描述: 注册系统消息通知
 *           关注系统消息的模块通过这个接口向平台注册相应的消息
 *           在某个系统消息发生后,平台会向注册过该消息的模块发送通知
 *
 * 输入参数: 
 * MODULE_ID wModuleID       模块ID
 * WORD      wMessageSet     系统消息集
 *           系统消息集wMessageSet是该模块需要得到通知的所有系统消息的位或的结果
 *
 * 返回: 成功/失败
 */
int PF_RegisterSystemMessage(PF_MODULE_ID wModuleID, WORD wMessageSet);



/* 功能描述: 注销系统消息通知,对应于注册系统消息通知接口
 *
 * 输入参数: 
 * MODULE_ID wModuleID       模块ID
 * WORD      wMessageSet     系统消息集
 *
 * 返回: 成功/失败
 */
int PF_UnregisterSystemMessage(PF_MODULE_ID wModuleID, WORD wMessageSet);



/* 功能描述: 该函数提供给BSP和主控模块.进入低功耗之前,BSP通过此接口通知模块管理
 *           退出低功耗之前,主控模块通过此接口通知模块管理
 *
 * 输入参数: 
 * BYTE      byStandbyStatus  低功耗状态(0 : 进入低功耗, 1 : 退出低功耗)
 *
 * 返回: 成功/失败
 */
int PF_Standby(BYTE byStandbyStatus);




/* 低功耗状态宏定义 */
/* 进入低功耗 */
#define PF_MM_STANDBY   (0)
/* 退出低功耗 */
#define PF_MM_WAKEON    (1)


/* 功能描述: 该函数提供给BSP,复位之前,BSP通过此接口通知模块管理
 *
 * 输入参数: 
 * BYTE      byRebootType(复位类型)
 *
 * 返回: 成功/失败
 */
int PF_Reboot(BYTE byRebootType);

/* 复位类型宏定义 */
/* 软复位 */
#define PF_MM_SOFT_REBOOT  (0)
/* 硬复位 */
#define PF_MM_HARD_REBOOT  (1)

#ifdef __cplusplus
}
#endif /* #ifndef __cplusplus */

#endif /* #ifndef _MMAPI_H_ */

