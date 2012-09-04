/******************************************************************************


******************************************************************************/

#ifndef __BSP_URGENCYCHANNELDRV_H__
#define __BSP_URGENCYCHANNELDRV_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "muxLib.h"
#include "vxWorks.h"
#include "netinet/in.h"
#include "netinet/ip.h"
#include "netinet/if_ether.h"
#include "netinet/udp.h"
#include "sys_include.h"
#include "BSPinclude.h"








/*����ͨ������*/
typedef struct sUrgencyPara
{
    VOID        *vmonitorRecvBindCookie;      /*���ݽ��վ��                     */
    VOID        *vmonitorSendBindCookie;      /*���ݷ��;��                     */
    END_OBJ     *pEnd;    			             /*END �����ṹָ��              */
    DWORD       dwChannelType;                 /*��·��Э��ѡ��                */			
    DWORD       dwReceiveCount;  		         /*����ͨ���հ�����          */	
    DWORD       dwSendCount;                    /*����ͨ����������          */
    SEM_ID	    semRecBuffInit;    	         /*����ͨ���ź�������     */
    DWORD       dwUrgencyStartflag;            /*��ʼ�����                          */
    BYTE        abyEthName[8];                  /*��̫������                           */
    DWORD       dwEthUnit;                      /*��̫�����*/
} URGENCY_PARA;





#ifdef __cplusplus
#if __cplusplus
}
#endif

#endif /* __cplusplus */
#endif /* __BSP_URGENCYCHANNELDRV_H__ */

