/******************************************************************************

     
  ��������   : ϵͳ��ģ����������䶨��
  
******************************************************************************/
#ifndef __SYS_ERRCODE_H__
#define __SYS_ERRCODE_H__
    
    

		/*��������������*/
#define COMMON_ERR_CODE_REGION_BASE     0x5001
		/*ƽ̨ģ�����������*/
#define PF_ERR_CODE_REGION_BASE         0x8001
		/*BSPģ�����������*/
#define BSP_ERR_CODE_REGION_BASE         0xA001
		/*SD�ɼ�ҵ�����������*/
#define SD_ERR_CODE_REGION_BASE 0xB001
		/*HD�ɼ�ҵ�����������*/
#define HD_ERR_CODE_REGION_BASE   0xC001
		/*�źŴ���ҵ�����������*/
#define OP_ERR_CODE_REGION_BASE    0xE001
		/*����ģ�����������*/
#define CS_ERR_CODE_REGION_BASE         0xF001



/*�ļ�ϵͳ��Ϣ*/

#define NO_MEM                  (BSP_ERR_CODE_REGION_BASE)
#define ERR_PARAM               (BSP_ERR_CODE_REGION_BASE+(0x2))
#define MALLOC_ERROR            (BSP_ERR_CODE_REGION_BASE+(0x3))
#define INTCONNECT_ERROR        (BSP_ERR_CODE_REGION_BASE+(0x4))
#define SEM_CREATE_ERROR        (BSP_ERR_CODE_REGION_BASE+(0x5))
#define TASK_CREATE_ERROR       (BSP_ERR_CODE_REGION_BASE+(0x6)) /* ���񴴽�����*/
#define MSG_CREATE_ERROR        (BSP_ERR_CODE_REGION_BASE+(0x7)) /* ��Ϣ���д�������*/
#define CHECK_SUM_ERROR         (BSP_ERR_CODE_REGION_BASE+(0x8)) /* �ļ�У��ʹ���*/ 
#define INFLATE_ERROR           (BSP_ERR_CODE_REGION_BASE+(0x9)) /* ��ѹ������*/
#define FILE_TYPE_ERROR			(BSP_ERR_CODE_REGION_BASE+(0xa)) /* �ļ����ʹ���*/
#define FILE_USE_CANCLE			(BSP_ERR_CODE_REGION_BASE+(0xb)) /* �û�ȡ������*/
#define FILE_WRITE_ERROR		(BSP_ERR_CODE_REGION_BASE+(0xc)) /* FLASH д����*/
#define FILE_TOOLARGE_ERROR		(BSP_ERR_CODE_REGION_BASE+(0xd)) /* �ļ�̫��*/


#define NAND_BASE               (BSP_ERR_CODE_REGION_BASE+(0x20))
#define NAND_NO_BLOCK          (NAND_BASE+(0x1))
#define NAND_NOINBUFFER        (NAND_BASE+(0x9))
#define NAND_NO_INIT           (NAND_BASE+(0x9))



#endif /* __SYS_ERRCODE_H__ */



