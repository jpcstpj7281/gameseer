/**********************************************************

* ����ժҪ�� ��ƵԤ���ӿ�ͷ�ļ�
*
**********************************************************/

#ifndef _VPAPI_H_
#define _VPAPI_H_

#include "sys_types.h"

typedef DWORD  ERROR_CODE;

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

/* ��ʼ��ƵԤ��
 *
 * BYTE byChannel     ͨ����
 * BYTE byResolution  �ֱ���
 * 
 * ����ֵ:�ɹ�/ʧ��
 */
ERROR_CODE PF_StartPreview(BYTE byChannel, BYTE byResolution);

/* ������ƵԤ��
 *
 * BYTE byChannel     ͨ����
 * 
 * ����ֵ:�ɹ�/ʧ��
 */
ERROR_CODE PF_EndPreview(BYTE byChannel);


/* �����ṩ�Ļ�ȡ��ƵԤ�����ݽӿ�
 *
 *
 */
DWORD GetPreviewData(BYTE byChannels,  BYTE *bypDataAddr, BYTE *bypSign);


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef _VPAPI_H_ */

