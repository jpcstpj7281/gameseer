#ifndef _DEBUGAPI_H_
#define _DEBUGAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/*#include "debug.h"*/

/* ����ģ�鼰���Ա��� */
#define DECLARE_DEBUG_SWITCH       _DECLARE_DEBUG_SWITCH_
    
/* ����ģ���ڲ�����ģ�鼶���Ա��� */
#define DECLARE_SUB_DEBUG_SWITCH   _DECLARE_SUB_DEBUG_SWITCH_

/* ������� */
#define DEBUG_OUT _DEBUG_OUT_

/* ���õ��Կ��� */
void SetDebugSwitch(int*, int);

void simple_va_fun(int start, ...);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _DEBUGAPI_H_ */

