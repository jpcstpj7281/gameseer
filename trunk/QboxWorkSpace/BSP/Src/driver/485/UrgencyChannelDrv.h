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








/*紧急通道参数*/
typedef struct sUrgencyPara
{
    VOID        *vmonitorRecvBindCookie;      /*数据接收句柄                     */
    VOID        *vmonitorSendBindCookie;      /*数据发送句柄                     */
    END_OBJ     *pEnd;    			             /*END 驱动结构指针              */
    DWORD       dwChannelType;                 /*链路层协议选择                */			
    DWORD       dwReceiveCount;  		         /*紧急通道收包计数          */	
    DWORD       dwSendCount;                    /*紧急通道发包计数          */
    SEM_ID	    semRecBuffInit;    	         /*紧急通道信号量保护     */
    DWORD       dwUrgencyStartflag;            /*初始化标记                          */
    BYTE        abyEthName[8];                  /*以太网名字                           */
    DWORD       dwEthUnit;                      /*以太网编号*/
} URGENCY_PARA;





#ifdef __cplusplus
#if __cplusplus
}
#endif

#endif /* __cplusplus */
#endif /* __BSP_URGENCYCHANNELDRV_H__ */

