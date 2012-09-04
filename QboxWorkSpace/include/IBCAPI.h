/**********************************************************

* 内容摘要： 板间通信通信用户接口

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
    /* 发送消息的单板  (1..64)-->(0..63)                    */
    /* 485中的0..5bits保存板位号, 6..7bits保存优先级        */
    BYTE        bySourceBoard;

    /* 接收消息的单板                                       */
    /* 单播:槽位号(1..64)  组播:组ID(65..128)  广播:0xFF    */
    BYTE        byDestinationBoard;

    WORD        wSourceMailBox;      /* 发送消息的信箱ID    */
    WORD        wDestinationMailBox; /* 接收消息的信箱ID    */

    /* 该域只体现给应用层                                   */
    /* 485中,优先级被压缩到源单板域中保存                   */
    BYTE        byPrivilege;         /* 优先级(普通,紧急)   */

    /* 消息数据                                             */
    WORD        wDataLength;         /* 数据长度            */
    BYTE*       pbyDataAddress;      /* 数据地址            */
} S_MESSAGE;

/* 消息优先级定义 */
#define PF_MSG_PRI_NORMAL (0)
#define PF_MSG_PRI_URGENT (1)
#define PF_MSG_PRI_ERROR  (0xFF)

/* 广播地址 0     */
#define PF_BROAD_CAST            (0)

/* 板位号的无效值 */
#define PF_INVALID_BOARD_ID      (0xFF)

/* 无效的信箱ID   */
#define PF_INVALID_MAIL_BOX_ID   (0xFFFF)

/* 无效的任务ID   */
#define PF_INVALID_TASK_ID   (0xFFFFFFFF)

/* 创建信箱，并注册驱动该信箱的事件接收事件的任务
 *
 * WORD      wMailBoxID     信箱ID
 * DWORD     dwMailBoxSize  信箱大小
 * WORD      wMessageSize   信箱中消息的大小
 * TASK_ID   dwTaskID       信箱对应的任务
 * DWORD     dwEvent        驱动任务接收消息的事件
 * BYTE      byOptions      信箱选项
 *                          MSG_Q_FIFO (0x00)
 *                          queue pended tasks in FIFO order. 
 *                          MSG_Q_PRIORITY
 *                          queue pended tasks in priority order
 *
 * 备注:如果不注册信箱驱动事件,任务ID参数必须填写PT_INVALID_TASK_ID
 * 
 * 返回值:成功/失败
 */
ERROR_CODE PF_CreateMailBox(WORD     wMailBoxID,
                            DWORD    dwMailBoxSize,
                            WORD     wMessageSize,
                            TASK_ID  dwTaskID,
                            DWORD    dwEvent,
                            int      iOptions);


/* 任务以信箱ID向通信模块注销之前创建的信箱
 *
 * WORD     wMailBoxID     信箱ID
 *
 * 返回值:成功/失败
 */
ERROR_CODE PF_DeleteMailBox(WORD wMailBoxID);


/* 应用层在使用CPU通信功能向目的信箱发送消息之前,需要通过这个接口申请消息
 * 空间,并正确填写该空间的各域之后,才能调用发送消息接口发送消息.
 *
 * WORD        wDataSize          消息附带数据大小
 * S_MESSAGE**  ppsMessage        输出申请的消息空间指针
 *
 * 返回值:成功/失败
 */            
ERROR_CODE PF_AllocateMessage(WORD wDataSize, S_MESSAGE**  ppsMessage);


/* 应用层在调用发送消息接口向网络传输层发送消息之前,如果不想发送该消息,或
 * 发送消息失败的情况下,想释放消息,可以调用该接口释放之前申请的消息块;应用层
 * 在接收消息之后,负责释放消息,否则该消息占用的内存会一直不会被释放
 *
 * S_MESSAGE* psMessage消息块地址
 *
 * 返回值:成功/失败
 */
ERROR_CODE PF_FreeMessage(S_MESSAGE* psMessage);


/* 向目的信箱发送消息
 *
 * S_MESSAGE* psMessage消息块地址
 *
 * 返回值:成功/失败
 */
ERROR_CODE PF_SendMessage(S_MESSAGE* psMessage);


/* 该接口以阻塞方式从指定信箱中取消息队列的队首返回给应用层
 *
 * WORD       wMailBoxID      信箱ID
 * S_MESSAGE* psMessage       消息块地址
 * int        iTimeOut        等待时间,单位为毫秒,按10向上取整,两个特殊值:
 *                            NO_WAIT (0)       无论是否有消息,立即返回
 *                            WAIT_FOREVER (-1) 永远等待
 *
 * 返回值:成功/失败
 */
ERROR_CODE PF_ReceiveMessage(WORD       wMailBoxID, \
                             S_MESSAGE* psMessage,  \
                             int        iTimeOut);


/* 查询指定信箱中的消息数
 *
 * WORD       wMailBoxID      信箱ID
 *
 * 返回值:消息数,失败返回-1
 */
int PF_GetMessageNumber(WORD wMailBoxID);


/* 查询本板ID
 *
 * 返回值:正确/错误
 */
BYTE PF_GetLocalBoardID();


/* 查询本板类型
 *
 * 返回值:板类型
 */
BYTE PF_GetLocalBoardType();


/*
 *	驱动上报紧急消息的接口
 *
 *  DWORD dwBufferSize : 报文大小
 *  BYTE* pbyBuffer    : 报文地址
 *
 *  返回值: 正确/错误
 */
ERROR_CODE PF_ReceiveUrgentFrame(DWORD dwBufferSize, BYTE* pbyBuffer);


#ifdef __cplusplus
}
#endif /* #ifdef __cplusplus */

#endif /* #ifndef _IBCAPI_H_ */

