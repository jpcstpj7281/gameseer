/**********************************************************

* 内容摘要： 视频预览接口头文件
*
**********************************************************/

#ifndef _VPAPI_H_
#define _VPAPI_H_

#include "sys_types.h"

typedef DWORD  ERROR_CODE;

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* 开始视频预览
 *
 * BYTE byChannel     通道号
 * BYTE byResolution  分辨率
 * 
 * 返回值:成功/失败
 */
ERROR_CODE PF_StartPreview(BYTE byChannel, BYTE byResolution);

/* 结束视频预览
 *
 * BYTE byChannel     通道号
 * 
 * 返回值:成功/失败
 */
ERROR_CODE PF_EndPreview(BYTE byChannel);


/* 驱动提供的获取视频预览数据接口
 *
 *
 */
DWORD GetPreviewData(BYTE byChannels,  BYTE *bypDataAddr, BYTE *bypSign);


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef _VPAPI_H_ */

