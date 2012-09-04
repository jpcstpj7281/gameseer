/******************************************************************************

    
  ��������   : ���ļ�ͳһ�������ذ����ӿ�
  

******************************************************************************/


#ifndef __CSINTERFACE_H__
#define __CSINTERFACE_H__

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#ifndef BYTE
#define BYTE unsigned char  
#endif


#ifndef WORD
#define WORD unsigned short int
#endif

#ifndef DWORD
#define DWORD unsigned long  
#endif

#ifndef SDWORD
#define SDWORD signed long  
#endif

/* IIC driver*/
/*
VOID I2cInit(VOID);
DWORD I2cRead(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData);
DWORD I2cReadSeq(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData, DWORD dwCount);
DWORD I2cWrite(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE byData);
DWORD I2cWritePage(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData, DWORD dwCount);
*/
/* SPI driver*/
VOID   CS_SpiCreate(VOID);
SDWORD CS_SpiOpen(BYTE bySpiPortNum);
SDWORD CS_SpiClose(BYTE bySpiPortNum);
SDWORD CS_SpiCmd(BYTE bySpiPortNum, BYTE *pbyCmd, BYTE byCmdSize, BYTE *pbyData, WORD wDataSize);

/* LCD driver*/
DWORD CS_GetFanStatus(BYTE *pbyStatus);            /*����ɹ�����SYS_OK, ʧ�ܷ���SYS_ERROR, *pbyStatus
                                                    ÿ������λ��ʾ��Ӧ�ķ���״̬��0��ʾ������1��ʾ������
                                                    �����֧��5������*/

DWORD CS_GetPowStatus(BYTE *pbyStatus);            /*����ɹ�����SYS_OK, ʧ�ܷ���SYS_ERROR, *pbyStatus
                                                    ÿ������λ��ʾ��Ӧ�ĵ�Դ״̬��0��ʾ������1��ʾ������
                                                    �����֧��3����Դ*/
                                                    
DWORD CS_GetTempStatus(BYTE *pbyStatus);           /*����ɹ�����SYS_OK, ʧ�ܷ���SYS_ERROR, *pbyStatus
                                                    ÿ������λ��ʾ��Ӧ���¶ȵ�״̬��0��ʾ������1��ʾ����
                                                    �������֧��6���¶ȵ�*/

DWORD CS_SetBuzzer(BYTE byStatus);                  /*����ɹ�����SYS_OK, ʧ�ܷ���SYS_ERROR��byStatusΪ1
                                                    ��ʾ������������0��ʾ�ر�*/

DWORD CS_GetBuzzer(BYTE *pbyStatus);                /**/


DWORD CS_CrossTemperature(DWORD *pdwTemp);          /*����Ƭ�¶Ȳ�ѯ*/

DWORD CS_GetFpgaVsSync(BYTE *pbySync, BYTE *pbySyncStat);

DWORD CS_SetFpgaVsSync(BYTE bySyncSel);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
