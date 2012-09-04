/******************************************************************************

    
  功能描述   : 消息类型枚举定义
  

******************************************************************************/


typedef enum {
		/*主控收到 vwas的消息的消息类型*/
		VWAS_MSG_REGION_BASE = 0x00006001,
		VWAS_CMD_PROTOCOL_VER,
		VWAS_CMD_NETWORK_OPER,
		VWAS_CMD_BOARD_STATUS,
		VWAS_CMD_VERSION_QUERY,
		VWAS_CMD_POWER_FAN_STATUS,
		VWAS_ALARM_MSG,
		VWAS_CMD_DEV_DATE_OPER,
		VWAS_PREVIEW_OPER,
		VWAS_DIGIT_DESKTOP_OPER,
		VWAS_WINDOW_LOGIC_WIN_SWITCH,
		VWAS_BACKGROUND_OPER,
		VWAS_CAPTURE_OPER,
		VWAS_WINDOW_LOGIC_WIN_MOVE,
		VWAS_CMD_SYS_INITIAL_CONFIG,
		VWAS_WINDOW_LOGIC_WIN_RESIZING,
		VWAS_LOGIC_WIN_ATTR_OPER,
		VWAS_WINDOW_CHOOSE,
		VWAS_SYS_FILE_UPGRADE,
		VWAS_DESKTOP_COLOR_KEY_OPER,

		/*维护管理的消息类型*/
		MCTRL_MSG_REGION_BASE = 0x00007001,

		/*平台模块的消息类型*/
		PLAT_MSG_REGION_BASE = 0x00008001,

		/*BSP的消息类型*/
		BSP_MSG_REGION_BASE = 0x0000A001,

		/*SD采集业务的消息类型*/
		OPER_VIDEO_MSG_REGION_BASE = 0x0000B001,

		/*HD采集业务的消息类型*/
		OPER_RGB_MSG_REGION_BASE = 0x0000C001,

		/*交叉业务的消息类型*/
		OPER_SW_MSG_REGION_BASE = 0x0000D001,

		/*数据信号处理板的消息类型*/
		OPER_SP_MSG_REGION_BASE = 0x0000E001,

		/*调试模块的消息类型*/
		DBG_MSG_REGION_BASE = 0x0000F001,
		
}MSG_ID_E;

