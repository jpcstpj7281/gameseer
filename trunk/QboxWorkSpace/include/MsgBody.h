/******************************************************************************

 
  功能描述   : 控制交互消息或模块间通信消息结构定义
 

******************************************************************************/


/*vwas与2501进行网口操作的结构*/
typedef struct {
	DWORD			ulOperType;		/*0--读IP信息,1--配置IP,2--读网口状态,3--配置网口模式*/
	Sys_Board_S			stBrd;			/*which board*/
	BoardIpConfig_S	stIpCfg;		/*ip information*/
	EtherStatus_S	stEthStatus;	/*ethernet status*/
	DWORD			ulResult;		/*命令执行结果*/
}VwasNetWorkOper_S;


/*vwas查询单板在位状态*/
typedef	struct {
	DWORD		ulInSlotStatus;		/*0--不在位,1--在位,F--其他异常*/
	Sys_Board_S		stBrd;
}VwasBrdInSlotQuery_S;



/*vwas查询单板软硬件版本*/
typedef	struct {
	Sys_Board_S		stBrd;
	DWORD		ulVerType;		/*0--hardware;1--software*/
	union {
		HwVersion_S		stHwVer;
		SwVersion_S		stSwVer;
	} uVersion;
	DWORD		ulResult;
}VwasQueryVersion_S;


/*vwas查询检测点温度*/
typedef	struct {
	TEMPPOINT_E		eTemp;
	DWORD			ulResult;
	FLOAT			fValue;
}VwasQueryTemp_S;




/*vwas查询电源风扇状态*/
typedef	struct {
	DWORD		ulDevType;		/*0--fan;1--power*/
	union {
		DWORD	ulFanStatus;
		DWORD	ulPowerStatus;
	} uDevStatus;
	DWORD		ulResult;
}VwasQueryFanPower_S;



/*vwas查询/上报告警信息*/
typedef	struct {
	DWORD			ulSerialNo;		/*alarm statistics*/
	SYS_T			stTime;
	Sys_Board_S		stBrd;
	ALARMGRADE_E	eGrade;
	ALARMSOURCE_E	eSrc;
	ALARMTYPES_E	eType;
	BYTE			aucDescr[256];
}VwasAlarmInfo_S;



/*vwas查询/设置设备系统时间*/
typedef	struct {
	DWORD		ulOperType;		/*0--query;1--config*/
	SYS_T		stDate;
	DWORD		ulResult;
}VwasDevSysDate_S;



/*vwas对视频输入源预览的操作*/
typedef	struct {
	Sys_Board_S			stBrd;
	BYTE				ucVideoInChannel;	/*0~15,video input of eache gather board*/	
	BYTE				ucResult;
	ImageResolution_S 	stResolution;
}VwasVideoInPreview_S;




/*vwas对逻辑窗口的开关操作*/
typedef	struct {
	DWORD			ulLogicWinNo;
	VideoInputSource_S	stPhyInput;		/*对应的输入源*/
	DWORD			ulSuperpositionNo;	/*叠加序号,0--最上层，9--最下*/
	DWORD			ulResult;
}VwasLogicWinSwitch_S;



/*vwas选择背景输出的操作*/
typedef	struct {
	DWORD		ulBackgroundNo;
	DWORD		ulResult;
}VwasBackGroundSelect_S;



/*vwas控制截屏/低帧捕获*/
typedef	struct {
	DWORD				ulEnable;
	ImageResolution_S	stResolution;
	DWORD				ulFrameRate;	/*帧率,每秒的帧数*/
	DWORD				ulResult;
}VwasCaptureOper_S;




/*vwas对逻辑窗口的移动*/
typedef	struct {
	DWORD				ulLogicWinNo;
	ImageCoordinate_S	stRelocate;
	DWORD				ulResult;
}VwasMoveLogicWin_S;




/*vwas对系统初始化配置*/
typedef	struct {
	DWORD				ulInputNum;
	InputSourceInfo_S	stInput[17];
	DWORD				ulOutputNum;
	VideoScreenInfo_S	stOutput[48];
	DWORD				ulResult;
}VwasInitialConfig_S;





/*vwas改动逻辑窗口大小*/
typedef	struct {
	DWORD				ulLogicWinNo;
	ImageResolution_S	stOldWin;
	ImageResolution_S	stNewWin;
	DWORD				ulResult;
}VwasResizeLogicWin_S;






/*vwas逻辑窗口属性操作*/
typedef	struct {
	DWORD				ulLogicWinNo;
	VideoInputSource_S	stPhyInput;		/*对应的输入源*/
	DWORD				ulResult;
}VwasLogicWinAttrOper_S;





/*vwas逻辑窗口选中操作*/
typedef struct
{
	DWORD			ulOldLogicWin;		/*之前的当前窗口*/
	DWORD			ulNewLogicWin;		/*新的当前窗口*/
	DWORD			ulResult;
}VwasLogicWinSelect_S;




/*vwas可以升级的软件类型*/
typedef	enum
{
	VWAS_BOARD_BOOTROM = 300,
		VWAS_BOARD_MINISYS,
		VWAS_BOARD_APPSYS,
		VWAS_BOARD_LOGICA,
		VWAS_BOARD_LOGICB,
		VWAS_BOARD_LOGICC
}VWAS_SOFTWARE_LIST_E;



/*vwas软件升级操作*/
typedef struct
{
	Sys_Board_S				stBrd;
	VWAS_SOFTWARE_LIST_E	eSoftType;
	DWORD					ulTotalLen;
	DWORD					ulCurrPktLen;
	DWORD					ulPktSequence;
	DWORD					ulRcvPktAck;		/*接收到的序列回应*/
	BYTE					aucData[1];			/*below is data*/
}VwasSoftwareUpgrade_S;




/*vwas设置Color-Key*/
typedef struct
{
	ImageColorKey_S		stColorKey;
}VwasColorKeyConfig_S;





