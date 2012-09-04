/******************************************************************************

******************************************************************************/

#ifndef __BSP_SOFTWAREUP_H__
#define __BSP_SOFTWAREUP_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "muxLib.h"
#include "vxWorks.h"
#include "vxWorks.h"
#include "stdio.h"
#include "taskLib.h"
#include <bootLib.h>
#include <ftpLib.h>
#include <config.h>
#include "muxLib.h"
#include "sys_include.h"
#include "BSPinclude.h"




/*软件升级参数*/
typedef struct sSoftWareUp
{
    SDWORD (*softUpCallback) (DWORD*, DWORD*);
    BYTE * pbySAdd;
    BYTE * pbyDAdd;
    BYTE * pbyBkDAdd;
    DWORD dwlength;
    DWORD dwToNo;
    DWORD dwCrNo;
    SEM_ID	    semRecBuffInit;    	         /*紧急通道信号量保护     */
} SOFT_WARE_UP;


#ifdef __cplusplus
#if __cplusplus
}
#endif

#endif /* __cplusplus */
#endif /* __BSP_LED_H__ */

