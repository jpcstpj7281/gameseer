#ifndef _DEBUGAPI_H_
#define _DEBUGAPI_H_

#ifdef __cplusplus
extern "C" {
#endif

/*#include "debug.h"*/

/* 声明模块及调试变量 */
#define DECLARE_DEBUG_SWITCH       _DECLARE_DEBUG_SWITCH_
    
/* 声明模块内部的子模块级调试变量 */
#define DECLARE_SUB_DEBUG_SWITCH   _DECLARE_SUB_DEBUG_SWITCH_

/* 调试输出 */
#define DEBUG_OUT _DEBUG_OUT_

/* 设置调试开关 */
void SetDebugSwitch(int*, int);

void simple_va_fun(int start, ...);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _DEBUGAPI_H_ */

