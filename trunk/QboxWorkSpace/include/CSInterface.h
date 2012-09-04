/******************************************************************************

    
  功能描述   : 本文件统一描述主控板对外接口
  

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
DWORD CS_GetFanStatus(BYTE *pbyStatus);            /*命令成功返回SYS_OK, 失败返回SYS_ERROR, *pbyStatus
                                                    每个比特位表示对应的风扇状态，0表示正常，1表示不正常
                                                    。最多支持5个风扇*/

DWORD CS_GetPowStatus(BYTE *pbyStatus);            /*命令成功返回SYS_OK, 失败返回SYS_ERROR, *pbyStatus
                                                    每个比特位表示对应的电源状态，0表示正常，1表示不正常
                                                    。最多支持3个电源*/
                                                    
DWORD CS_GetTempStatus(BYTE *pbyStatus);           /*命令成功返回SYS_OK, 失败返回SYS_ERROR, *pbyStatus
                                                    每个比特位表示对应的温度点状态，0表示正常，1表示不正
                                                    常。最多支持6个温度点*/

DWORD CS_SetBuzzer(BYTE byStatus);                  /*命令成功返回SYS_OK, 失败返回SYS_ERROR，byStatus为1
                                                    表示开启蜂鸣器，0表示关闭*/

DWORD CS_GetBuzzer(BYTE *pbyStatus);                /**/


DWORD CS_CrossTemperature(DWORD *pdwTemp);          /*交叉片温度查询*/

DWORD CS_GetFpgaVsSync(BYTE *pbySync, BYTE *pbySyncStat);

DWORD CS_SetFpgaVsSync(BYTE bySyncSel);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
