/******************************************************************************

     
  功能描述   : 系统各模块错误码区间定义
  
******************************************************************************/
#ifndef __SYS_ERRCODE_H__
#define __SYS_ERRCODE_H__
    
    

		/*公共错误码区间*/
#define COMMON_ERR_CODE_REGION_BASE     0x5001
		/*平台模块错误码区间*/
#define PF_ERR_CODE_REGION_BASE         0x8001
		/*BSP模块错误码区间*/
#define BSP_ERR_CODE_REGION_BASE         0xA001
		/*SD采集业务错误码区间*/
#define SD_ERR_CODE_REGION_BASE 0xB001
		/*HD采集业务错误码区间*/
#define HD_ERR_CODE_REGION_BASE   0xC001
		/*信号处理业务错误码区间*/
#define OP_ERR_CODE_REGION_BASE    0xE001
		/*交叉模块错误码区间*/
#define CS_ERR_CODE_REGION_BASE         0xF001



/*文件系统信息*/

#define NO_MEM                  (BSP_ERR_CODE_REGION_BASE)
#define ERR_PARAM               (BSP_ERR_CODE_REGION_BASE+(0x2))
#define MALLOC_ERROR            (BSP_ERR_CODE_REGION_BASE+(0x3))
#define INTCONNECT_ERROR        (BSP_ERR_CODE_REGION_BASE+(0x4))
#define SEM_CREATE_ERROR        (BSP_ERR_CODE_REGION_BASE+(0x5))
#define TASK_CREATE_ERROR       (BSP_ERR_CODE_REGION_BASE+(0x6)) /* 任务创建错误*/
#define MSG_CREATE_ERROR        (BSP_ERR_CODE_REGION_BASE+(0x7)) /* 消息队列创建错误*/
#define CHECK_SUM_ERROR         (BSP_ERR_CODE_REGION_BASE+(0x8)) /* 文件校验和错误*/ 
#define INFLATE_ERROR           (BSP_ERR_CODE_REGION_BASE+(0x9)) /* 解压缩错误*/
#define FILE_TYPE_ERROR			(BSP_ERR_CODE_REGION_BASE+(0xa)) /* 文件类型错误*/
#define FILE_USE_CANCLE			(BSP_ERR_CODE_REGION_BASE+(0xb)) /* 用户取消升级*/
#define FILE_WRITE_ERROR		(BSP_ERR_CODE_REGION_BASE+(0xc)) /* FLASH 写错误*/
#define FILE_TOOLARGE_ERROR		(BSP_ERR_CODE_REGION_BASE+(0xd)) /* 文件太大*/


#define NAND_BASE               (BSP_ERR_CODE_REGION_BASE+(0x20))
#define NAND_NO_BLOCK          (NAND_BASE+(0x1))
#define NAND_NOINBUFFER        (NAND_BASE+(0x9))
#define NAND_NO_INIT           (NAND_BASE+(0x9))



#endif /* __SYS_ERRCODE_H__ */



