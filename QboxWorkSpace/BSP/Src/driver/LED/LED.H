/*-------------------------------------------------------------------------

-------------------------------------------------------------------------*/


#ifndef __BSP_LED_H__
#define __BSP_LED_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "muxLib.h"
#include "vxWorks.h"
#include "sys_include.h"
#include "BSPinclude.h"




/*紧急通道参数*/
typedef struct sLEDPara
{
    DWORD dwRunLEDFlg;		    /*1.常亮 2. 常灭3.闪烁 */
    DWORD dwRunLEDDiv;		    /*闪烁间隔，单位100ms */
    DWORD dwAlarmLEDFlg;	    /*1.常亮 2. 常灭3.闪烁 */
    DWORD dwAlarmLEDDiv;	    /*闪烁间隔，单位100ms */
    DWORD dwTimeCounter;	    /*计时时间 */
    DWORD dwRunLEDState;	    /*运行灯状态１亮，２灭*/
    DWORD dwAlarmLEDState;	    /*告警灯状态１亮，２灭*/
} LED_PARA;


VOID LedStateChg(DWORD dwRunLEDFlg,DWORD dwRunLEDDiv,DWORD dwAlarmLEDFlg,DWORD dwAlarmLEDDiv);
SDWORD LedDrvInit(void);



#ifdef __cplusplus
#if __cplusplus
}
#endif

#endif /* __cplusplus */
#endif /* __BSP_LED_H__ */

