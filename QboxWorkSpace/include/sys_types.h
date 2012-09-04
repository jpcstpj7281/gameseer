/******************************************************************************

 
  功能描述   : 本系统统一数据类型定义
 

******************************************************************************/

#ifndef __SYS_TYPEDEF_H__
#define __SYS_TYPEDEF_H__





#define SYS_NULL               (0)
#define SYS_NULL_PTR           (0L)
#define SYS_NULL_BYTE          (0XFF)
#define SYS_NULL_WORD          (0xFFFF)
#define SYS_NULL_DWORD         (0xFFFFFFFF)
#define SYS_NULL_LONG          (SYS_NULL_DWORD)
#define SYS_NULL_OBJ           (-1)
#define SYS_NULL_PARA          (-1)

#define SYS_OK                 (OK)
#define SYS_ERROR              (ERROR)
#ifndef LOCAL
#define LOCAL static
#endif





/*类型定义
g_      ： 全局变量
s_      ： 模块内静态变量
空    ： 局部变量不加范围前缀
p      	： pointer
a      	： 数组，array of TYPE
str    	： 字符串
s		： 结构类型
*/



typedef  unsigned char    	     BYTE;    		/*前缀 by        */
typedef  char             	     CHAR;    		/*前缀 c          */
typedef  signed short     	     SWORD;   		/*前缀 ssw      */
typedef  signed long      	     SDWORD;  		/*前缀 i          */
typedef  float                  FLOAT;    		/*前缀 f          */
typedef  double	                 DOUBLE;	 	/*前缀 d         */
typedef  unsigned long long     DDWORD; 		/*前缀 ddw	   */




typedef  void                    VOID;          /*前缀 v         */
typedef  unsigned short   	     WORD;    		/*前缀 w         */
typedef  unsigned long    	     DWORD;   		/*前缀 dw       */




#define DEBUG_CMD_BASE_ADDR   0x7000  /*调试命令基地址*/

#define DEBUG_CMD_GATHER      (DEBUG_CMD_BASE_ADDR + 0x1) /*采集板调试命令基地址从0x7001开始*/
                                                          /*到0x7050终止*/

#define DEBUG_CMD_PROC        (DEBUG_CMD_BASE_ADDR + 0x51) /*视频处理板调试命令基地址从0x7051开始*/
                                                           /*到0x70a0结束*/
                                                           
#define DEBUG_CMD_CROSS       (DEBUG_CMD_BASE_ADDR + 0xa1) /*交叉调试命令基地址从0x70a1开始*/
                                                           /*到0x70f0结束    */
                                                           
#define DEBUG_CMD_OVER        (DEBUG_CMD_BASE_ADDR + 0xf1) /*调试命令结束地址空间           */                                                                                                      

#endif /* __SYS_TYPEDEF_H__ */

