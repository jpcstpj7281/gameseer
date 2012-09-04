/******************************************************************************

 
  ��������   : ��ϵͳͳһ�������Ͷ���
 

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





/*���Ͷ���
g_      �� ȫ�ֱ���
s_      �� ģ���ھ�̬����
��    �� �ֲ��������ӷ�Χǰ׺
p      	�� pointer
a      	�� ���飬array of TYPE
str    	�� �ַ���
s		�� �ṹ����
*/



typedef  unsigned char    	     BYTE;    		/*ǰ׺ by        */
typedef  char             	     CHAR;    		/*ǰ׺ c          */
typedef  signed short     	     SWORD;   		/*ǰ׺ ssw      */
typedef  signed long      	     SDWORD;  		/*ǰ׺ i          */
typedef  float                  FLOAT;    		/*ǰ׺ f          */
typedef  double	                 DOUBLE;	 	/*ǰ׺ d         */
typedef  unsigned long long     DDWORD; 		/*ǰ׺ ddw	   */




typedef  void                    VOID;          /*ǰ׺ v         */
typedef  unsigned short   	     WORD;    		/*ǰ׺ w         */
typedef  unsigned long    	     DWORD;   		/*ǰ׺ dw       */




#define DEBUG_CMD_BASE_ADDR   0x7000  /*�����������ַ*/

#define DEBUG_CMD_GATHER      (DEBUG_CMD_BASE_ADDR + 0x1) /*�ɼ�������������ַ��0x7001��ʼ*/
                                                          /*��0x7050��ֹ*/

#define DEBUG_CMD_PROC        (DEBUG_CMD_BASE_ADDR + 0x51) /*��Ƶ���������������ַ��0x7051��ʼ*/
                                                           /*��0x70a0����*/
                                                           
#define DEBUG_CMD_CROSS       (DEBUG_CMD_BASE_ADDR + 0xa1) /*��������������ַ��0x70a1��ʼ*/
                                                           /*��0x70f0����    */
                                                           
#define DEBUG_CMD_OVER        (DEBUG_CMD_BASE_ADDR + 0xf1) /*�������������ַ�ռ�           */                                                                                                      

#endif /* __SYS_TYPEDEF_H__ */

