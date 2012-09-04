/******************************************************************************

 
  ��������   : ���ƽ�����Ϣ��ģ���ͨ����Ϣ�ṹ����
 

******************************************************************************/


/*vwas��2501�������ڲ����Ľṹ*/
typedef struct {
	DWORD			ulOperType;		/*0--��IP��Ϣ,1--����IP,2--������״̬,3--��������ģʽ*/
	Sys_Board_S			stBrd;			/*which board*/
	BoardIpConfig_S	stIpCfg;		/*ip information*/
	EtherStatus_S	stEthStatus;	/*ethernet status*/
	DWORD			ulResult;		/*����ִ�н��*/
}VwasNetWorkOper_S;


/*vwas��ѯ������λ״̬*/
typedef	struct {
	DWORD		ulInSlotStatus;		/*0--����λ,1--��λ,F--�����쳣*/
	Sys_Board_S		stBrd;
}VwasBrdInSlotQuery_S;



/*vwas��ѯ������Ӳ���汾*/
typedef	struct {
	Sys_Board_S		stBrd;
	DWORD		ulVerType;		/*0--hardware;1--software*/
	union {
		HwVersion_S		stHwVer;
		SwVersion_S		stSwVer;
	} uVersion;
	DWORD		ulResult;
}VwasQueryVersion_S;


/*vwas��ѯ�����¶�*/
typedef	struct {
	TEMPPOINT_E		eTemp;
	DWORD			ulResult;
	FLOAT			fValue;
}VwasQueryTemp_S;




/*vwas��ѯ��Դ����״̬*/
typedef	struct {
	DWORD		ulDevType;		/*0--fan;1--power*/
	union {
		DWORD	ulFanStatus;
		DWORD	ulPowerStatus;
	} uDevStatus;
	DWORD		ulResult;
}VwasQueryFanPower_S;



/*vwas��ѯ/�ϱ��澯��Ϣ*/
typedef	struct {
	DWORD			ulSerialNo;		/*alarm statistics*/
	SYS_T			stTime;
	Sys_Board_S		stBrd;
	ALARMGRADE_E	eGrade;
	ALARMSOURCE_E	eSrc;
	ALARMTYPES_E	eType;
	BYTE			aucDescr[256];
}VwasAlarmInfo_S;



/*vwas��ѯ/�����豸ϵͳʱ��*/
typedef	struct {
	DWORD		ulOperType;		/*0--query;1--config*/
	SYS_T		stDate;
	DWORD		ulResult;
}VwasDevSysDate_S;



/*vwas����Ƶ����ԴԤ���Ĳ���*/
typedef	struct {
	Sys_Board_S			stBrd;
	BYTE				ucVideoInChannel;	/*0~15,video input of eache gather board*/	
	BYTE				ucResult;
	ImageResolution_S 	stResolution;
}VwasVideoInPreview_S;




/*vwas���߼����ڵĿ��ز���*/
typedef	struct {
	DWORD			ulLogicWinNo;
	VideoInputSource_S	stPhyInput;		/*��Ӧ������Դ*/
	DWORD			ulSuperpositionNo;	/*�������,0--���ϲ㣬9--����*/
	DWORD			ulResult;
}VwasLogicWinSwitch_S;



/*vwasѡ�񱳾�����Ĳ���*/
typedef	struct {
	DWORD		ulBackgroundNo;
	DWORD		ulResult;
}VwasBackGroundSelect_S;



/*vwas���ƽ���/��֡����*/
typedef	struct {
	DWORD				ulEnable;
	ImageResolution_S	stResolution;
	DWORD				ulFrameRate;	/*֡��,ÿ���֡��*/
	DWORD				ulResult;
}VwasCaptureOper_S;




/*vwas���߼����ڵ��ƶ�*/
typedef	struct {
	DWORD				ulLogicWinNo;
	ImageCoordinate_S	stRelocate;
	DWORD				ulResult;
}VwasMoveLogicWin_S;




/*vwas��ϵͳ��ʼ������*/
typedef	struct {
	DWORD				ulInputNum;
	InputSourceInfo_S	stInput[17];
	DWORD				ulOutputNum;
	VideoScreenInfo_S	stOutput[48];
	DWORD				ulResult;
}VwasInitialConfig_S;





/*vwas�Ķ��߼����ڴ�С*/
typedef	struct {
	DWORD				ulLogicWinNo;
	ImageResolution_S	stOldWin;
	ImageResolution_S	stNewWin;
	DWORD				ulResult;
}VwasResizeLogicWin_S;






/*vwas�߼��������Բ���*/
typedef	struct {
	DWORD				ulLogicWinNo;
	VideoInputSource_S	stPhyInput;		/*��Ӧ������Դ*/
	DWORD				ulResult;
}VwasLogicWinAttrOper_S;





/*vwas�߼�����ѡ�в���*/
typedef struct
{
	DWORD			ulOldLogicWin;		/*֮ǰ�ĵ�ǰ����*/
	DWORD			ulNewLogicWin;		/*�µĵ�ǰ����*/
	DWORD			ulResult;
}VwasLogicWinSelect_S;




/*vwas�����������������*/
typedef	enum
{
	VWAS_BOARD_BOOTROM = 300,
		VWAS_BOARD_MINISYS,
		VWAS_BOARD_APPSYS,
		VWAS_BOARD_LOGICA,
		VWAS_BOARD_LOGICB,
		VWAS_BOARD_LOGICC
}VWAS_SOFTWARE_LIST_E;



/*vwas�����������*/
typedef struct
{
	Sys_Board_S				stBrd;
	VWAS_SOFTWARE_LIST_E	eSoftType;
	DWORD					ulTotalLen;
	DWORD					ulCurrPktLen;
	DWORD					ulPktSequence;
	DWORD					ulRcvPktAck;		/*���յ������л�Ӧ*/
	BYTE					aucData[1];			/*below is data*/
}VwasSoftwareUpgrade_S;




/*vwas����Color-Key*/
typedef struct
{
	ImageColorKey_S		stColorKey;
}VwasColorKeyConfig_S;





