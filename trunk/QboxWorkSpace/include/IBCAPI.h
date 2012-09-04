/**********************************************************

* ����ժҪ�� ���ͨ��ͨ���û��ӿ�

**********************************************************/

#ifndef _IBCAPI_H_
#define _IBCAPI_H_

#include "sys_types.h"


#ifdef __cplusplus
/*
#include <new>
void* operator new(size_t dwSize);
void operator delete(void * p);
*/
#endif /* #ifdef __cplusplus */


typedef SDWORD TASK_ID;
typedef DWORD  ERROR_CODE;

#ifdef __cplusplus
extern "C" {
#endif /* #ifdef __cplusplus */

typedef struct
{
    /* ������Ϣ�ĵ���  (1..64)-->(0..63)                    */
    /* 485�е�0..5bits�����λ��, 6..7bits�������ȼ�        */
    BYTE        bySourceBoard;

    /* ������Ϣ�ĵ���                                       */
    /* ����:��λ��(1..64)  �鲥:��ID(65..128)  �㲥:0xFF    */
    BYTE        byDestinationBoard;

    WORD        wSourceMailBox;      /* ������Ϣ������ID    */
    WORD        wDestinationMailBox; /* ������Ϣ������ID    */

    /* ����ֻ���ָ�Ӧ�ò�                                   */
    /* 485��,���ȼ���ѹ����Դ�������б���                   */
    BYTE        byPrivilege;         /* ���ȼ�(��ͨ,����)   */

    /* ��Ϣ����                                             */
    WORD        wDataLength;         /* ���ݳ���            */
    BYTE*       pbyDataAddress;      /* ���ݵ�ַ            */
} S_MESSAGE;

/* ��Ϣ���ȼ����� */
#define PF_MSG_PRI_NORMAL (0)
#define PF_MSG_PRI_URGENT (1)
#define PF_MSG_PRI_ERROR  (0xFF)

/* �㲥��ַ 0     */
#define PF_BROAD_CAST            (0)

/* ��λ�ŵ���Чֵ */
#define PF_INVALID_BOARD_ID      (0xFF)

/* ��Ч������ID   */
#define PF_INVALID_MAIL_BOX_ID   (0xFFFF)

/* ��Ч������ID   */
#define PF_INVALID_TASK_ID   (0xFFFFFFFF)

/* �������䣬��ע��������������¼������¼�������
 *
 * WORD      wMailBoxID     ����ID
 * DWORD     dwMailBoxSize  �����С
 * WORD      wMessageSize   ��������Ϣ�Ĵ�С
 * TASK_ID   dwTaskID       �����Ӧ������
 * DWORD     dwEvent        �������������Ϣ���¼�
 * BYTE      byOptions      ����ѡ��
 *                          MSG_Q_FIFO (0x00)
 *                          queue pended tasks in FIFO order. 
 *                          MSG_Q_PRIORITY
 *                          queue pended tasks in priority order
 *
 * ��ע:�����ע�����������¼�,����ID����������дPT_INVALID_TASK_ID
 * 
 * ����ֵ:�ɹ�/ʧ��
 */
ERROR_CODE PF_CreateMailBox(WORD     wMailBoxID,
                            DWORD    dwMailBoxSize,
                            WORD     wMessageSize,
                            TASK_ID  dwTaskID,
                            DWORD    dwEvent,
                            int      iOptions);


/* ����������ID��ͨ��ģ��ע��֮ǰ����������
 *
 * WORD     wMailBoxID     ����ID
 *
 * ����ֵ:�ɹ�/ʧ��
 */
ERROR_CODE PF_DeleteMailBox(WORD wMailBoxID);


/* Ӧ�ò���ʹ��CPUͨ�Ź�����Ŀ�����䷢����Ϣ֮ǰ,��Ҫͨ������ӿ�������Ϣ
 * �ռ�,����ȷ��д�ÿռ�ĸ���֮��,���ܵ��÷�����Ϣ�ӿڷ�����Ϣ.
 *
 * WORD        wDataSize          ��Ϣ�������ݴ�С
 * S_MESSAGE**  ppsMessage        ����������Ϣ�ռ�ָ��
 *
 * ����ֵ:�ɹ�/ʧ��
 */            
ERROR_CODE PF_AllocateMessage(WORD wDataSize, S_MESSAGE**  ppsMessage);


/* Ӧ�ò��ڵ��÷�����Ϣ�ӿ������紫��㷢����Ϣ֮ǰ,������뷢�͸���Ϣ,��
 * ������Ϣʧ�ܵ������,���ͷ���Ϣ,���Ե��øýӿ��ͷ�֮ǰ�������Ϣ��;Ӧ�ò�
 * �ڽ�����Ϣ֮��,�����ͷ���Ϣ,�������Ϣռ�õ��ڴ��һֱ���ᱻ�ͷ�
 *
 * S_MESSAGE* psMessage��Ϣ���ַ
 *
 * ����ֵ:�ɹ�/ʧ��
 */
ERROR_CODE PF_FreeMessage(S_MESSAGE* psMessage);


/* ��Ŀ�����䷢����Ϣ
 *
 * S_MESSAGE* psMessage��Ϣ���ַ
 *
 * ����ֵ:�ɹ�/ʧ��
 */
ERROR_CODE PF_SendMessage(S_MESSAGE* psMessage);


/* �ýӿ���������ʽ��ָ��������ȡ��Ϣ���еĶ��׷��ظ�Ӧ�ò�
 *
 * WORD       wMailBoxID      ����ID
 * S_MESSAGE* psMessage       ��Ϣ���ַ
 * int        iTimeOut        �ȴ�ʱ��,��λΪ����,��10����ȡ��,��������ֵ:
 *                            NO_WAIT (0)       �����Ƿ�����Ϣ,��������
 *                            WAIT_FOREVER (-1) ��Զ�ȴ�
 *
 * ����ֵ:�ɹ�/ʧ��
 */
ERROR_CODE PF_ReceiveMessage(WORD       wMailBoxID, \
                             S_MESSAGE* psMessage,  \
                             int        iTimeOut);


/* ��ѯָ�������е���Ϣ��
 *
 * WORD       wMailBoxID      ����ID
 *
 * ����ֵ:��Ϣ��,ʧ�ܷ���-1
 */
int PF_GetMessageNumber(WORD wMailBoxID);


/* ��ѯ����ID
 *
 * ����ֵ:��ȷ/����
 */
BYTE PF_GetLocalBoardID();


/* ��ѯ��������
 *
 * ����ֵ:������
 */
BYTE PF_GetLocalBoardType();


/*
 *	�����ϱ�������Ϣ�Ľӿ�
 *
 *  DWORD dwBufferSize : ���Ĵ�С
 *  BYTE* pbyBuffer    : ���ĵ�ַ
 *
 *  ����ֵ: ��ȷ/����
 */
ERROR_CODE PF_ReceiveUrgentFrame(DWORD dwBufferSize, BYTE* pbyBuffer);


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef _IBCAPI_H_ */

