/******************************************************************************

  
  ��������   : ϵͳ�ж����õ��Ľṹ/��Ķ���
  

******************************************************************************/

/*��������ö��*/
typedef	enum {
	SYS_MASTER_BOARD = 1000,
		SYS_SD_GATHER_BOARD,
		SYS_HD_GATHER_BOARD,
		SYS_SD_CROSS_BOARD,
		SYS_HD_CROSS_BOARD,
		SYS_DIGIT_PROCESS_BOARD,
		SYS_FAN_POWER_BOARD,
		SYS_BACK_BOARD,
		SYS_BOARD_END
}BOARDTYPE_E;


/*����ṹ*/
typedef	struct {
	DWORD		ulSlotId;
	BOARDTYPE_E	eBrdType;
}Sys_Board_S;


/*����IP���ýṹ*/
typedef	struct {
	DWORD		ulIpAddr;
	DWORD		ulGateAddr;
	DWORD		ulNetMask;
}BoardIpConfig_S;


/*����״̬*/
typedef	struct {
	BYTE		ucMac[6];
	DWORD		ulLinkStatus;
	DWORD		ulSpeed;	/*10M/100M*/
	DWORD		ulMode;		/*ȫ˫��/��˫��*/
	DWORD		ulSndStatistics;	/*����ͳ��*/
	DWORD		ulRcvStatistics;	/*�հ�ͳ��*/
}EtherStatus_S;



/*�߼��汾*/
typedef	struct {
	BYTE		ucMainVer;	/*��汾*/
	BYTE		ucRevVer;	/*�޶��汾*/
}LogicVersion_S;


/*Ӳ���汾*/
typedef	struct {
	BYTE		ucPcb;
	BYTE		ucPcba;
	union {
		struct {
			LogicVersion_S	stLogicA;
		} stGatherLogic;
		struct {
			LogicVersion_S	stLogicA;
			LogicVersion_S	stLogicB;
			LogicVersion_S	stLogicC;
		} stDigitLogic;
		struct {
			LogicVersion_S	stLogicA;
		} stMasterLogic;
	} uLogic;
}HwVersion_S;



/*����汾*/
typedef	struct {
	BYTE		ucMainVer;	/*��汾*/
	BYTE		ucRevVer;	/*�޶��汾*/
}SwVersion_S;



/*BOM�汾*/
typedef	struct {
	BYTE		ucMainVer;	/*��汾*/
	BYTE		ucRevVer;	/*�޶��汾*/
}BOMVersion_S;



/*�¶ȼ���ö��*/
typedef	enum {
	TEMP_Master_Point = 1008,
		TEMP_SD_POINTA,
		TEMP_SD_POINTB,
		TEMP_HD_POINTA,
		TEMP_HD_POINTB
}TEMPPOINT_E;



/*�澯��Դö��*/
typedef	enum {
	TEMPERATURE_ALARM_SRC = 100,
		FAN_ALARM_SRC,
		VOLTAGE_ALARM_SRC,
		POWER_ALARM_SRC,
		SYN_CLOCK_ALARM_SRC,
		MASTER_SERIAL_ALARM_SRC,
		SLAVE_SERIAL_ALARM_SRC,
		PERFORMANCE_ALARM_SRC,
		SYS_LOAD_ALARM_SRC
}ALARMSOURCE_E;




/*�澯�ȼ�ö��*/
typedef	enum {
	DEBUG_INFO_LEVEL = 200,
		SYS_INFO_LEVEL,
		PERFORMANCE_ALARM_LEVEL,
		DEVICE_ALARM_LEVEL,
		LINK_ALARM_LEVEL,
		SYS_ERROR_LEVEL
}ALARMGRADE_E;




/*�澯�쳣����*/
typedef	enum {
	OVER_TEMPERATURE_ALARM = 100,
		FAN_TOO_SLOW_ALARM,
		FAN_SHUTDOWN_ALARM,
		OVER_VOLTAGE_ALARM,
		UNDER_VOLTAGE_ALARM,
		POWER_SHUTDOWN_ALARM,
		SYN_CLOCK_ERROR_ALARM,
		MASTER_LINK_FAILED_ALARM,
		SLAVE_LINK_FAILED_ALARM,
		MEM_ALLOC_FAILED_ALARM,		
		COMM_OVERFLOW_ALARM,	/*ͨ�Ź���*/
		LOG_FILE_FULL,
		SYS_LOAD_FAILED,		/*bootrom load system over 3 times*/
		
}ALARMTYPES_E;



typedef struct DATE_STRU
{
    WORD  uwYear;    /* year  */
    BYTE   ucMonth;   /* month */
    BYTE   ucDate;    /* day   */
} DATE_T;


typedef struct TIME_STRU
{
    BYTE   ucHour;    /* hour   */
    BYTE   ucMinute;  /* minute */
    BYTE   ucSecond;  /* second */
    BYTE   ucPadding;
} TIME_T;


typedef struct tagSysTime
{
    WORD  uwYear;
    BYTE   ucMonth;   /* scope is 1 - 12 */
    BYTE   ucDate;    /* scope is 1 - 31 */
    BYTE   ucHour;    /* scope is 0 - 23 */
    BYTE   ucMinute;  /* scope is 0 - 59 */
    BYTE   ucSecond;  /* scope is 0 - 59 */
    BYTE   ucWeek;    /* scope is 1 - 7  */
} SYS_T;


typedef	struct tagImageResolution
{
	DWORD	ulHorizontal;
	DWORD	ulVertical;
}ImageResolution_S;



typedef	struct
{
	DWORD		ulX;
	DWORD		ulY;
}ImageCoordinate_S;


typedef	struct
{
	DWORD				ulLogicWinNo;	/*�߼����ڱ��*/
	ImageCoordinate_S	stStart;
	DWORD				ulHeight;
	DWORD				ulWidth;
	DWORD				ulSuperposeNo;	/*���Ӳ���*/
}LogicWindow_S;




typedef	union
{
/*
*	struct {} sd;
*     struct {} hd;
*     ��ɫ\����\��ʽ\�ֱ��ʵ�,����
*/
}InputSrcAttributes_U;


typedef	struct
{
	Sys_Board_S				stBrd;
	WORD					usStartNo;
	WORD					usEndNo;
	InputSrcAttributes_U	uProperties[16];
}InputSourceInfo_S;



typedef	struct
{
	Sys_Board_S			stBrd;
	WORD				usPortNum;
	InputSrcAttributes_U	uAttr;
}VideoInputSource_S;


typedef	struct
{
	DWORD				ulScreenNo;		/*��Ļ���*/
	ImageCoordinate_S	stStartLoc;		/*��������*/
	ImageCoordinate_S	stEndLoc;		/*��������*/
	ImageResolution_S	stResolution;	/*��Ļ�ֱ���*/
}VideoScreenInfo_S;




typedef	struct
{
	BYTE		ucRead;
	BYTE		ucGreen;
	BYTE		ucBlue;
}ImageColorKey_S;



typedef	struct
{
	BOMVersion_S	stBOM;
	HwVersion_S		stHwVer;
	SwVersion_S		stSwVer;
}SDVideoInBoard_S;


typedef	struct
{
	BOMVersion_S	stBOM;
	HwVersion_S		stHwVer;
	SwVersion_S		stSwVer;
}HDVideoInBoard_S;



typedef	struct
{
	BOMVersion_S	stBOM;
	HwVersion_S		stHwVer;
	SwVersion_S		stSwVer;
}SDSwBoard_S;



typedef	struct
{
	BOMVersion_S	stBOM;
	HwVersion_S		stHwVer;
	SwVersion_S		stSwVer;
}HDSwBoard_S;


typedef	struct
{
	BOMVersion_S	stBOM;
	HwVersion_S		stHwVer;
	SwVersion_S		stSwVer;
}SignalProcessBoard_S;



typedef	struct
{
	BOMVersion_S	stBOM;
	HwVersion_S		stHwVer;
	SwVersion_S		stSwVer;
}MainCtrlBoard_S;




/*��Ʒ���ױ�*/
typedef	struct
{
	BYTE				aucModel[32];	/*�ͺ�,��"sp1000"*/
	BOOL				bMaster;		/*���ӱ�־*/
	BYTE				ucPowerNum;		/*AC-DC��Դ��*/
	BYTE				ucFanNum;		/*���ȸ���*/
	BYTE				ucSDVideoInNum;	/*SD�ɼ������*/
	SDVideoInBoard_S	stSDVideoInBrd[17];
	BYTE				ucHDVideoInNum;	/*HD�ɼ������*/
	HDVideoInBoard_S	stHDVideoInBrd[9];
	BYTE				ucSDSwNum;		/*SD��������*/
	SDSwBoard_S			stSDSwBrd[2];	/*SD���������*/
	BYTE				ucHDSwNum;
	HDSwBoard_S			stHDSwBrd[2];
	BYTE				ucSPNum;		/*�źŴ�������*/
	SignalProcessBoard_S stSPBrd[12];
	MainCtrlBoard_S		stMainBrd;		/*���ذ�����*/
}SP1000_Spec_S;




/*�ɱ�̱�����Ϣ*/
typedef	struct
{
	BOOL				bEnabled;		/*�Ƿ�ѡ��*/
	DWORD				ulPicNum;		/*ͼƬ����,���16��*/
	DWORD				ulInterval;		/*���ʱ��*/
	BYTE				aucSort[8][16];	/*����,��0��15 ��,���Ե���,��1ά���ļ���*/
}ProgrammbleBg_S;





/*���������(�߼�������˿ڵĶ�Ӧ)*/
typedef	struct
{
	struct {
		BYTE			ucSlotId;		/*��Ӧ�ɼ���Ĳۺ�*/
		DWORD			ulPhyInputNo;	/*��Ӧ�ɼ�������Դ������*/
		DWORD			ulLogInputNo;	/*��Ӧ�ɼ���ϵͳ����ʱ���߼����*/
	} SDSignalInput[216];
	struct {
		BYTE			ucSlotId;		/*��Ӧ���ݴ����Ĳۺ�*/
		DWORD			ulLogicWinNo;		/*��Ӧ���߼�����*/
		DWORD			ulLogicChannel;	/*��Ӧ�����ݴ�����߼�ͨ��,��1--144����Ļ��һһ��Ӧ*/
		DWORD			ulLogicPort;	/*��Ӧÿ��ͨ������ĸ���(3+7, 2+8, 1+9), �����źŹ̶���ǰ������*/		
	} SDSignalOutput[216];
}SDSwBrd_Map_S;



typedef	struct
{
	struct {
		BYTE			ucSlotId;		/*��Ӧ�ɼ���Ĳۺ�*/
		DWORD			ulPhyInputNo;	/*��Ӧ�ɼ�������Դ������*/
		DWORD			ulLogInputNo;	/*��Ӧ�ɼ���ϵͳ����ʱ���߼����*/
	} HDSignalInput[144];
	struct {
		BYTE			ucSlotId;		/*��Ӧ���ݴ����Ĳۺ�*/
		DWORD			ulLogicWinNo;		/*��Ӧ���߼�����*/
		DWORD			ulLogicChannel;	/*��Ӧ�����ݴ�����߼�ͨ��,��1--144����Ļ��һһ��Ӧ*/
		DWORD			ulLogicPort;	/*��Ӧÿ��ͨ������ĸ���(3+7, 2+8, 1+9), �����źŹ̶���ǰ������*/		
	} HDSignalOutput[144];
}HDSwBrd_Map_S;









