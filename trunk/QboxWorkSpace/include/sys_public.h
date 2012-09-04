/******************************************************************************

  
  功能描述   : 系统中都会用到的结构/宏的定义
  

******************************************************************************/

/*单板类型枚举*/
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


/*单板结构*/
typedef	struct {
	DWORD		ulSlotId;
	BOARDTYPE_E	eBrdType;
}Sys_Board_S;


/*网口IP配置结构*/
typedef	struct {
	DWORD		ulIpAddr;
	DWORD		ulGateAddr;
	DWORD		ulNetMask;
}BoardIpConfig_S;


/*网口状态*/
typedef	struct {
	BYTE		ucMac[6];
	DWORD		ulLinkStatus;
	DWORD		ulSpeed;	/*10M/100M*/
	DWORD		ulMode;		/*全双工/半双工*/
	DWORD		ulSndStatistics;	/*发包统计*/
	DWORD		ulRcvStatistics;	/*收包统计*/
}EtherStatus_S;



/*逻辑版本*/
typedef	struct {
	BYTE		ucMainVer;	/*大版本*/
	BYTE		ucRevVer;	/*修订版本*/
}LogicVersion_S;


/*硬件版本*/
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



/*软件版本*/
typedef	struct {
	BYTE		ucMainVer;	/*大版本*/
	BYTE		ucRevVer;	/*修订版本*/
}SwVersion_S;



/*BOM版本*/
typedef	struct {
	BYTE		ucMainVer;	/*大版本*/
	BYTE		ucRevVer;	/*修订版本*/
}BOMVersion_S;



/*温度检测点枚举*/
typedef	enum {
	TEMP_Master_Point = 1008,
		TEMP_SD_POINTA,
		TEMP_SD_POINTB,
		TEMP_HD_POINTA,
		TEMP_HD_POINTB
}TEMPPOINT_E;



/*告警来源枚举*/
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




/*告警等级枚举*/
typedef	enum {
	DEBUG_INFO_LEVEL = 200,
		SYS_INFO_LEVEL,
		PERFORMANCE_ALARM_LEVEL,
		DEVICE_ALARM_LEVEL,
		LINK_ALARM_LEVEL,
		SYS_ERROR_LEVEL
}ALARMGRADE_E;




/*告警异常类型*/
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
		COMM_OVERFLOW_ALARM,	/*通信过载*/
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
	DWORD				ulLogicWinNo;	/*逻辑窗口编号*/
	ImageCoordinate_S	stStart;
	DWORD				ulHeight;
	DWORD				ulWidth;
	DWORD				ulSuperposeNo;	/*叠加层数*/
}LogicWindow_S;




typedef	union
{
/*
*	struct {} sd;
*     struct {} hd;
*     颜色\亮度\制式\分辨率等,待定
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
	DWORD				ulScreenNo;		/*屏幕编号*/
	ImageCoordinate_S	stStartLoc;		/*左上坐标*/
	ImageCoordinate_S	stEndLoc;		/*右下坐标*/
	ImageResolution_S	stResolution;	/*屏幕分辨率*/
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




/*产品配套表*/
typedef	struct
{
	BYTE				aucModel[32];	/*型号,如"sp1000"*/
	BOOL				bMaster;		/*主从标志*/
	BYTE				ucPowerNum;		/*AC-DC电源数*/
	BYTE				ucFanNum;		/*风扇个数*/
	BYTE				ucSDVideoInNum;	/*SD采集板个数*/
	SDVideoInBoard_S	stSDVideoInBrd[17];
	BYTE				ucHDVideoInNum;	/*HD采集板个数*/
	HDVideoInBoard_S	stHDVideoInBrd[9];
	BYTE				ucSDSwNum;		/*SD交叉板个数*/
	SDSwBoard_S			stSDSwBrd[2];	/*SD交叉板配置*/
	BYTE				ucHDSwNum;
	HDSwBoard_S			stHDSwBrd[2];
	BYTE				ucSPNum;		/*信号处理板个数*/
	SignalProcessBoard_S stSPBrd[12];
	MainCtrlBoard_S		stMainBrd;		/*主控板配置*/
}SP1000_Spec_S;




/*可编程背景信息*/
typedef	struct
{
	BOOL				bEnabled;		/*是否选择*/
	DWORD				ulPicNum;		/*图片张数,最多16张*/
	DWORD				ulInterval;		/*间隔时间*/
	BYTE				aucSort[8][16];	/*排序,由0到15 排,可以调整,第1维是文件名*/
}ProgrammbleBg_S;





/*交叉板配置(逻辑与物理端口的对应)*/
typedef	struct
{
	struct {
		BYTE			ucSlotId;		/*对应采集板的槽号*/
		DWORD			ulPhyInputNo;	/*对应采集板输入源物理编号*/
		DWORD			ulLogInputNo;	/*对应采集板系统起来时的逻辑编号*/
	} SDSignalInput[216];
	struct {
		BYTE			ucSlotId;		/*对应数据处理板的槽号*/
		DWORD			ulLogicWinNo;		/*对应的逻辑窗口*/
		DWORD			ulLogicChannel;	/*对应的数据处理板逻辑通道,与1--144的屏幕数一一对应*/
		DWORD			ulLogicPort;	/*对应每个通道里的哪个口(3+7, 2+8, 1+9), 高清信号固定是前三个口*/		
	} SDSignalOutput[216];
}SDSwBrd_Map_S;



typedef	struct
{
	struct {
		BYTE			ucSlotId;		/*对应采集板的槽号*/
		DWORD			ulPhyInputNo;	/*对应采集板输入源物理编号*/
		DWORD			ulLogInputNo;	/*对应采集板系统起来时的逻辑编号*/
	} HDSignalInput[144];
	struct {
		BYTE			ucSlotId;		/*对应数据处理板的槽号*/
		DWORD			ulLogicWinNo;		/*对应的逻辑窗口*/
		DWORD			ulLogicChannel;	/*对应的数据处理板逻辑通道,与1--144的屏幕数一一对应*/
		DWORD			ulLogicPort;	/*对应每个通道里的哪个口(3+7, 2+8, 1+9), 高清信号固定是前三个口*/		
	} HDSignalOutput[144];
}HDSwBrd_Map_S;









