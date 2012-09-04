/******************************************************************************

    
  ��������   : ��Ϣ����ö�ٶ���
  

******************************************************************************/


typedef enum {
		/*�����յ� vwas����Ϣ����Ϣ����*/
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

		/*ά���������Ϣ����*/
		MCTRL_MSG_REGION_BASE = 0x00007001,

		/*ƽ̨ģ�����Ϣ����*/
		PLAT_MSG_REGION_BASE = 0x00008001,

		/*BSP����Ϣ����*/
		BSP_MSG_REGION_BASE = 0x0000A001,

		/*SD�ɼ�ҵ�����Ϣ����*/
		OPER_VIDEO_MSG_REGION_BASE = 0x0000B001,

		/*HD�ɼ�ҵ�����Ϣ����*/
		OPER_RGB_MSG_REGION_BASE = 0x0000C001,

		/*����ҵ�����Ϣ����*/
		OPER_SW_MSG_REGION_BASE = 0x0000D001,

		/*�����źŴ�������Ϣ����*/
		OPER_SP_MSG_REGION_BASE = 0x0000E001,

		/*����ģ�����Ϣ����*/
		DBG_MSG_REGION_BASE = 0x0000F001,
		
}MSG_ID_E;

