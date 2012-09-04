#ifndef _TIMERAPI_H_
#define _TIMERAPI_H_

#include "sys_types.h"

#ifdef __cplusplus
extern "C" {
#endif /* #ifndef __cplusplus */

typedef DWORD TIMER_ID;
typedef SDWORD TASK_ID;

/* ��Ч��ʱ��ID */
#define    INVALID_TIMER_ID      0xFFFFFFFF

/* ѭ����ʱ�� */
#define    PERIODIC_TIMER        0
/* ��Զ�ʱ�� */
#define    RELATIVE_TIMER        1


/*
 *	��������:������Ϣ��ʱ��
 *
 *  ����˵��:
 *  DWORD       dwInterval       ���ʱ��(����)
 *  BYTE        byintervalType   ��Ϣ����:ѭ����ʱ��/��Զ�ʱ��
 *  DWORD       dwEvent          �¼�ID
 *  TASK_ID     iTask            ���ն�ʱ�¼�������
 *
 *  ����:
 *  TIMER_ID*   pdwTimerID       ��ʱ��ID
 */
TIMER_ID PF_SetTimer(DWORD      dwInterval,
                     BYTE       byintervalType,
                     DWORD      dwEvent,
                     TASK_ID    iTask);

/*
 *  ɾ����ʱ��
 *  ����˵��:
 *  DWORD     dwTimerID    Ҫɾ���Ķ�ʱ��ID
 *
 *  ����:
 *  ɾ�����(�ɹ�/ʧ��)
 */
int PF_KillTimer(TIMER_ID dwTimerID);

#ifdef __cplusplus
}
#endif /* #ifndef __cplusplus */

#endif /* #ifndef _TIMERAPI_H_ */

