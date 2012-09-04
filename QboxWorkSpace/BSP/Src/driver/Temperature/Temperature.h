/******************************************************************************


******************************************************************************/

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



typedef enum _LM73_INTTERRUPT_TYPE
{
    LM73_T_CRIT_A_LOW,
    LM73_INT_PIN_LOW
} LM73_INTTERRUPT_TYPE ;


typedef enum _LM73_REG
{
    LM73_TEMPERATURE_REG,            /*�¶�ֵ�Ĵ�����ֻ��*/
    LM73_CONFIGURATION_REG,          /*���üĴ���*/
    LM73_Thyst_POINT_REG,            /*Thystֵ���üĴ���*/
    LM73_Tcrit_POINT_REG,            /*Tcritֵ���üĴ���*/
    LM73_Tlow_POINT_REG,             /*Tlowֵ���üĴ���*/
    LM73_Thigh_POINT_REG,            /*Thighֵ���üĴ���*/
}LM73_REG ;


#define LM73_CONFIGURATION_REG_VALUE  0x00 
#define LM73_Thyst_POINT_VALUE  0x00a     /*5��*/
#define LM73_Tcrit_POINT_VALUE  0x0a0     /*80��*/
#define LM73_Tlow_POINT_VALUE  0x000      /*0��*/
#define LM73_Thigh_POINT_VALUE  0x06e     /*55��*/

#ifdef __cplusplus
#if __cplusplus
}
#endif

#endif /* __cplusplus */
#endif /* __BSP_LED_H__ */

