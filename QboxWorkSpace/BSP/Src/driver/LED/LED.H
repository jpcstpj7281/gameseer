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




/*����ͨ������*/
typedef struct sLEDPara
{
    DWORD dwRunLEDFlg;		    /*1.���� 2. ����3.��˸ */
    DWORD dwRunLEDDiv;		    /*��˸�������λ100ms */
    DWORD dwAlarmLEDFlg;	    /*1.���� 2. ����3.��˸ */
    DWORD dwAlarmLEDDiv;	    /*��˸�������λ100ms */
    DWORD dwTimeCounter;	    /*��ʱʱ�� */
    DWORD dwRunLEDState;	    /*���е�״̬����������*/
    DWORD dwAlarmLEDState;	    /*�澯��״̬����������*/
} LED_PARA;


VOID LedStateChg(DWORD dwRunLEDFlg,DWORD dwRunLEDDiv,DWORD dwAlarmLEDFlg,DWORD dwAlarmLEDDiv);
SDWORD LedDrvInit(void);



#ifdef __cplusplus
#if __cplusplus
}
#endif

#endif /* __cplusplus */
#endif /* __BSP_LED_H__ */

