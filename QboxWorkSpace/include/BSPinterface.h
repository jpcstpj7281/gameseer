/******************************************************************************


  ��������   : ���ļ�ͳһ����BSP ���Ͻӿ�


******************************************************************************/


#ifndef __BSP_BSPINTERFACE_H__
#define __BSP_BSPINTERFACE_H__


#ifdef __cplusplus
extern "C" {
#endif /* #ifndef __cplusplus */


#include "sys_include.h"
#include "Time.h"






/**************************************�ӿ�*****************************************/





/*��λ����
-----------------------------------
	input:
		resetType:��λ����01:�临λ��02:�ȸ�λ
	output:
    		NA
	return:
		VOID
*/
VOID BSP_Reset(BYTE byResetType);

/*�߾���ʱ�ӻ�ȡ����
---------------------------------------------------
input:
	
output:
		DaubleSecond ��BSP ��ʼ����ɺ��ʱ�� ��λ 2��
		munit DaubleSecond���¼�����  ��λ 1��32768 ��
return:
	VOID

��: ���� DaubleSecond 3��munit 100 ʵ��ʱ��Ϊ 3*2+100*(1��32768)��


*/
DWORD BSP_TimeGet(DWORD *DaubleSecond ,DWORD *munit);



/*
 * ��ȡpcb �汾���汾��ʽ��V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:�汾��
    return:
        VOID
*/
VOID BSP_GetPcbVer( BYTE *pbyVer );




/*
 * ��ȡFPGA �汾���汾��ʽ��V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    input:
        VOID
    output:
        pbyVer:�汾��
        pbyNum:FPGA����
    return:
        VOID
*/
VOID BSP_GetFpgaVer( BYTE *pbyNum,BYTE *pbyVer );



/*
 * ��ȡBootRom �汾���汾��ʽ��V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:�汾��
    return:
        VOID
*/
VOID BSP_GetBootromVer( BYTE *pbyVer );



/*
 * ��ȡ��Сϵͳ �汾���汾��ʽ��V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:�汾��
    return:
        VOID
*/
VOID BSP_GetMiniSysVer( BYTE *pbyVer );



/*
 * ��ȡϵͳ��� �汾���汾��ʽ��V a.b.c
 * ver[0]=a,  ver[1]=b, ver[2]=c
-----------------------------------
    output:
        ver:�汾��
    return:
        VOID
*/
VOID BSP_GetSysSoftVer( BYTE *pbyVer );




/*
 * ��ȡ������ID��
 * ���ذ�����id��0:HD��1:SD��2:HDSW��
 * 3:SDSW�� 4:SSC
 -----------------------------------
	 return:
		 ������ID
 */
BYTE BSP_GetBoardTypeId( VOID );








/*
��ȡ�����λ��
 -----------------------------------
     input:
         VOID:
     output:
         VOID:pbyBNo ��λ��
     return:
         SYS_OK
         SYS_ERR
 */
    SDWORD BSP_GetBoardslotNo( BYTE * pbyBNo );








/*
 * ʹ�� Ӳ�����Ź�
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/

VOID BSP_EnableHardDog( VOID );




/*
 * ��ֹ Ӳ�����Ź�
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/
VOID BSP_DisableHardDog( VOID );




/*
 * ιӲ���� ����
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/
VOID BSP_FeedHardDog( VOID );

/*
 * �����ļ� ����
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        VOID
*/
VOID BSP_SaveFile(VOID);


/*
 * ����fpga
-----------------------------------
    input:
        VOID
    output:
        VOID
    return:
        SYS_OK
        SYS_ERR
*/
SDWORD BSP_LoadFpga(VOID);





/*
 * �������
-----------------------------------
    input:
        byBuffer            : ����ָ��
        dwLen               : ���ݳ���
        dwType             : ���� 01����/���壬02FPGA
        dwNo                :dwType Ϊ01 ʱ���ԣ�02�Ǳ�ʾFPGA �ı��
        softUpCallback   : �ص�������
                                    ����SYS_OK ��ʾ����������
                                    SYS_ERR��ʾ��ֹ����.
                                    BYTE* Ҫд������ݳ��ȣ��Ѿ�д������ݳ���
    output:
        VIOD
    return:
        SYS_OK
        SYS_ERR
*/

SDWORD  BSP_SoftUpgrade(BYTE* pbyBuffer, DWORD dwLen, DWORD dwType, 
                            DWORD dwNo, SDWORD (*softUpCallback) (DWORD*, DWORD*));




/*
 * RUN ����˸
-----------------------------------
    input:
        dwFlickerType:��˸���� 1:����2:����3:����4:����
    output:
        VOID
    return:
        LastLedSta:LED �Ƶ�����ǰ״̬
*/
DWORD BSP_SysRunLedFlic( DWORD dwFlickerType );



/*
 * Alarm ����˸
-----------------------------------
    input:
        dwFlickerType:��˸���� 1:����2:����3:����4:����
    output:
        VOID
    return:
        LastLedSta:LED �Ƶ�����ǰ״̬
*/

DWORD BSP_SysAlarmLedFlic( DWORD dwFlickerType );







/*
 * *����MAC ��ַ
 Mac[0]=a,  Mac[1]=b, Mac[2]=c,Mac[3]=d,  Mac[4]=e, Mac[5]=f
-----------------------------------
    input:
        pbyMac:MAC ��ַ
    output:
        VOID
    return:
        SYS_OK
        SYS_ERR


SDWORD BSP_DrvSetMac(BYTE *pbyMac);


*/



/*
 * *��ȡMAC ��ַ
 Mac[0]=a,  Mac[1]=b, Mac[2]=c,Mac[3]=d,  Mac[4]=e, Mac[5]=f
-----------------------------------
    input:
        VOID
    output:
        pbyMac:MAC ��ַ
    return:
        SYS_OK
        SYS_ERR
*/

SDWORD BSP_DrvGetMac(BYTE *pbyMac);






/* ����������ʼ��
---------------------------------------
    return:
        OK 
        ERROR
*/
SDWORD BSP_DrvInit();







/* ����RTC������(��������)
---------------------------------------
    input:
        RTC_DATE_STRUCT
    return:
        OK ---------- ������ȷ
        ERROR-------- ����
SDWORD setRtcDate(tm *psValue );
*/





/*�õ�Ŀǰ�¶�״̬
---------------------------------------
    inPut:
         byChipNo:�¶�оƬ��:0,1,2...
	output:
		VOID
    	return:
        	��ѹ0xFFFFFFFF �޷���ȡ
*/

SDWORD BSP_GetTemperatureVal(BYTE byChipNo );




/*�õ�Ŀǰ��ѹ״̬
---------------------------------------
    inPut:
         byChipNo:��ѹоƬ��:0,1,2...
	output:
		VOID
    	return:
        	��ѹ0xFFFFFFFF �޷���ȡ
*/

SDWORD BSP_GetVoltageStatus(BYTE byChipNo);



/* ɾ�����
---------------------------------------
    input:
    	 dwFileNo: ������
    	 1: ��ϵͳ���
    	 2: ��ϵͳ���
    	 3: ���߼����1
    	 4: ���߼����2
    	 5: ���߼����3
    	 6: ���߼����4
    	 7: ���߼����1
    	 8: ���߼����2
    	 9: ���߼����3
    	10: ���߼����4
    	 
    return:
        OK ---------- ��ȷ
        ERROR-------- ����
*/

SDWORD BSP_DeleteSoft(DWORD dwFileNo);

SDWORD BSP_SoftBackUP(VOID);


/*��� Bootrom
---------------------------------------
    return:
        OK ---------- ��ȡ
        ERROR-------- ����
*/
SDWORD BSP_GetBootromStatus();




/*��� FPGA
---------------------------------------
    input:
    	 no: FPGA ���01��04 ��FPGA,05-08 ����FPGA
    return:
        OK ---------- ��ȡ
        ERROR-------- ����
*/
SDWORD BSP_GetFPGAStatus(DWORD dwNo);






/*��� �������/�������
---------------------------------------
    input:
    	 no: 0 �������1����
    return:
        OK ---------- ��ȷ
        ERROR-------- ����
*/
SDWORD BSP_GetMainSoftStatus(DWORD dwNo);





/*��� ��Сϵͳ
---------------------------------------
    return:
        OK ---------- ��ȷ
        ERROR-------- ����
*/

SDWORD BSP_GetMiniSystemStatus(VOID);







/*CPU ռ���ʲ�ѯ
---------------------------------------
    return:
	����CPU ռ���ʣ���50��ʾ50%
*/

SDWORD BSP_CpuUsage(VOID);




/*
 * 82525 ��������
 -----------------------------------
    input:
        pbyDataBuffer:Ҫ���͵����ݰ�
        DWORD:����
    output:
        VOID
    return:
        SYS_OK
        SYS_ERR
*/

SDWORD BSP_UrgencySend(BYTE *pbyDataBuffer,DWORD dwLength);



/*��ȡRTC������(��������)
---------------------------------------
    output:
        psCurTime : ϵͳ��ǰʱ��
    return:
        SYS_OK ---------- �ɹ���ȡ
        SYS_ERR-------- ����
*/


SDWORD BSP_GetCurSysDateTime(struct tm *psCurTime);


/* ����RTC������(��������)
---------------------------------------
    input:
        psCurTime :��ǰʱ��
    return:
        OK ---------- ������ȷ
        ERROR-------- ����
*/

SDWORD BSP_SetCurSysDateTime(struct tm *psCurTime);

/* ��ȡ��1970 �꿪ʼ�����ڣ��Ѿ��߹�������
---------------------------------------
    output:
        pdwCurTime��: ��1970 �꿪ʼ�����ڣ��Ѿ��߹�������
    return:
        OK ---------- ��ȷ��ȡ
        ERROR--------����
*/

SDWORD BSP_GetCurSysDateTimeBySecond(DWORD * pdwCurTime);









/* ��ʼ��NAND �ļ�ϵͳ
---------------------------------------
    input:
        Void
    return:
        OK ----------�ɹ�
        ERROR-------ʧ��
*/
SDWORD BSP_NandFlashFileInit(DWORD dwtype);


/*
 * ��ȡNAND �ļ�ϵͳ���ļ�����
 -----------------------------------
    input:
        dwFileNo:Ҫ��ȡ���ȵ��ļ����ļ����0-199
    output:
        pdwFileLength:���ص��ļ�����
    return:
        OK ----------�ɹ�
        ERROR-------ʧ��
        NO_MEM------û���ڴ�
        ERR_PARAM----��������
*/
SDWORD BSP_NandFlashFileGetLength(DWORD dwFileNo,DWORD * pdwFileLength);


/*
 * д��NAND �ļ�ϵͳ�ڵ�һ���ļ�
 -----------------------------------
    input:
        dwFileNo:Ҫ��ȡ���ļ���š�0-199
        dwBufferLength:������ڴ泤��
        pbyBuffer:Ҫд����ļ�����
    return:
        OK ----------�ɹ�
        ERROR-------ʧ��
        NO_MEM------û���ڴ�
        ERR_PARAM----��������
*/
SDWORD BSP_NandFlashFileWrite(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength,SDWORD (*softUpCallback) (DWORD*, DWORD*));



/*
 * ��ȡNAND �ļ�ϵͳ�ڵ�һ���ļ�
 -----------------------------------
    input:
        dwFileNo:Ҫ��ȡ���ļ���š�0-199
        dwBufferLength:������ڴ泤��
    output:
        pbyBuffer:���ص��ļ�����
    return:
        OK ----------�ɹ�
        ERROR-------ʧ��
        NO_MEM------û���ڴ�
        ERR_PARAM----��������
*/
SDWORD BSP_NandFlashFileRead(DWORD dwFileNo,BYTE * pbyBuffer,DWORD dwBufferLength);




/*
* ��ѯ����������Ϣ
* ���:
*        pDateTime: ��������
*        abyArea  : ����
*        abyVender: OEM����
*        abySeq   : ���к�
* ����ֵ:
*        �ɹ�/ʧ��
*/
WORD BSP_GetManInfo(struct tm* pDateTime, BYTE abyArea[128], BYTE abyVender[128], BYTE abySeq[32]);




/*�ļ�ϵͳ�ӿ�
��׼DOS �ļ��ӿ�


*/

/*LCD ���ڽӿ�
��׼IO �ӿ�


*/

/*
* ��ʼ��ϵͳʱ��
*/
WORD BSP_InitPll(VOID);

#ifdef __cplusplus
}
#endif /* #ifndef __cplusplus */
#endif /* __BSP_BSPINTERFACE_H__ */


