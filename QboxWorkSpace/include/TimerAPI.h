#ifndef _TIMERAPI_H_
#define _TIMERAPI_H_

#include "sys_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* #ifndef __cplusplus */

typedef DWORD TIMER_ID;
typedef SDWORD TASK_ID;

/* 无效定时器ID */
#define    INVALID_TIMER_ID      0xFFFFFFFF

/* 循环定时器 */
#define    PERIODIC_TIMER        0
/* 相对定时器 */
#define    RELATIVE_TIMER        1


/*
 *	功能描述:创建消息定时器
 *
 *  参数说明:
 *  DWORD       dwInterval       间隔时间(毫秒)
 *  BYTE        byintervalType   消息类型:循环定时器/相对定时器
 *  DWORD       dwEvent          事件ID
 *  TASK_ID     iTask            接收定时事件的任务
 *
 *  返回:
 *  TIMER_ID*   pdwTimerID       定时器ID
 */
TIMER_ID PF_SetTimer(DWORD      dwInterval,
                     BYTE       byintervalType,
                     DWORD      dwEvent,
                     TASK_ID    iTask);

/*
 *  删除定时器
 *  参数说明:
 *  DWORD     dwTimerID    要删除的定时器ID
 *
 *  返回:
 *  删除结果(成功/失败)
 */
int PF_KillTimer(TIMER_ID dwTimerID);

#ifdef __cplusplus
}
#endif /* #ifndef __cplusplus */

#endif /* #ifndef _TIMERAPI_H_ */

