/******************************************************************************

  
  功能描述     : 主机模块头文件，供外部调用的接口都在此文件定义
  

******************************************************************************/

#ifndef __MC_IF_H__
#define __MC_IF_H__

#ifdef __cplusplus
extern "C" {
#endif


#define ALARM_PARA_SIZE 5
#define EVENT_PARA_SIZE 5
#define ALARM_DESC_SIZE 128
#define EVENT_DESC_SIZE 128

 struct ALARM_NODE
 {
	 DWORD dwAlarmID;
	 DWORD dwCount;
/* 
	// ALARM_NODE()
	// {
	//	 this->dwAlarmID = 0;
	//	 this->dwCount	 = 0;
	// }
*/
 };

 /*
  *告警来源枚举，每个告警所对应的值不能够随便修改，新增
  *告警在枚举底部依次增加
  */
 enum 
 {
     upgrade_software_failed = 0x0001, /*升级软件失败 */
     upgrade_file_failed        = 0x0002, /*升级文件失败 */
     fpga_file_error                = 0x0003, /*FPGA文件错误 */
     fpga_file_lost                = 0x0004, /*FPGA文件丢失 */
     file_lost                          = 0x0005, /*文件丢失 */
     file_overflow                  = 0x0006, /*文件超大溢出 */
     file_destroyed                 = 0x0007, /*文件被破坏 */
     file_alarm_overflow    = 0x0008, /*告警文件超大告警 */
     flash_bad_block         = 0x0009, /*FLASH坏块过多 */
     flash_error                = 0x000A, /*FLASH出错 */
     cpu_alarm                   = 0x000B, /*CPU使用率过高 */
     memory_alarm            = 0x000C, /*内存使用率过高 */
     standby_scc_error   = 0x000D, /*辅助SCC链路告警 */
     main_scc_error      = 0x000E, /*主SCC链路告警 */
     bdsoft_lost            = 0x000F, /*单板软件丢失 */
     bdsoft_error       = 0x0010, /*单板软件出错 */
     i2c_error               = 0x0011, /*I2C通信错误 */
     spi_error                  = 0x0012, /*SPI通信错误 */
     eth_link_error  = 0x0013, /*以太网连接错误 */
     FAT_error = 0x0014, /*文件分配表错误 */
     /*desktop_sign_change	   = 0x0015, //桌面信号源发生改变 */
     fan_abnormal= 0x0016, /*风扇异常 */
     fan_invalid= 0x0017, /*风扇失效 */
     clock_error= 0x0018, /*时钟错误 */
     fpga_error = 0x0019, /*FPGA 错误 */
     fpga_fifo_error= 0x001A, /*FPGA FIFO错误 */
     sign_format_error= 0x001B, /*信号格式错误 */
     sign_format_change = 0x001C, /*信号格式改变 */
     /*sign_source_change	   = 0x001D, //信号源发生变化 */
     chip_AD9888_alarm= 0x001E, /*AD9888芯片出错 */
     chip_TVP5160_alarm= 0x001F, /*TVP5160芯片出错 */
     chip_SII1161_alarm = 0x0020, /*SII1161芯片出错 */
     chip_IP00C751_alarm= 0x0021, /*IP00C751芯片出错 */
     logic_alarm = 0x0022, /*硬件逻辑出错 */
     chip_VSC3108_alarm= 0x0023, /*VSC3108芯片错误 */
     double_synclk_invalid= 0x0024, /*双路同步时钟无效 */
     single_synclk_invalid= 0x0025, /*单路同步时钟无效 */
     synclk_lost= 0x0026, /*同步时钟丢失 */
     unit_A_decode_abnormal  = 0x0027, /*单元A解串FPGA逻辑异常 */
     unit_B_decode_abnormal  = 0x0028, /*单元B解串FPGA逻辑异常 */
     unit_C_decode_abnormal  = 0x0029, /*单元C解串FPGA逻辑异常 */
     unit_D_decode_abnormal  = 0x002a, /*单元D解串FPGA逻辑异常 */
     unit_A_overlap_abnormal = 0x002b, /*单元A叠加FPGA逻辑异常 */
     unit_B_overlap_abnormal = 0x002c, /*单元B叠加FPGA逻辑异常 */
     unit_C_overlap_abnormal = 0x002d, /*单元C叠加FPGA逻辑异常 */
     unit_D_overlap_abnormal = 0x002e, /*单元D叠加FPGA逻辑异常 */
     scaler_1_ctrl_abnormal  = 0x002f, /*Scaler 1控制异常 */
     scaler_2_ctrl_abnormal  = 0x0030, /*Scaler 2控制异常 */
     scaler_3_ctrl_abnormal  = 0x0031, /*Scaler 3控制异常 */
     scaler_4_ctrl_abnormal  = 0x0032, /*Scaler 4控制异常 */
     scaler_5_ctrl_abnormal  = 0x0033, /*Scaler 5控制异常 */
     scaler_6_ctrl_abnormal  = 0x0034, /*Scaler 6控制异常 */
     scaler_7_ctrl_abnormal  = 0x0035, /*Scaler 7控制异常 */
     scaler_8_ctrl_abnormal  = 0x0036, /*Scaler 8控制异常 */
     scaler_9_ctrl_abnormal  = 0x0037, /*Scaler 9控制异常 */
     scaler_10_ctrl_abnormal = 0x0038, /*Scaler 10控制异常 */
     scaler_11_ctrl_abnormal = 0x0039, /*Scaler 11控制异常 */
     scaler_12_ctrl_abnormal = 0x003a, /*Scaler 12控制异常 */
     scaler_13_ctrl_abnormal = 0x003b, /*Scaler 13控制异常 */
     scaler_14_ctrl_abnormal = 0x003c, /*Scaler 14控制异常 */
     scaler_15_ctrl_abnormal = 0x003d, /*Scaler 15控制异常 */
     scaler_16_ctrl_abnormal = 0x003e, /*Scaler 16控制异常 */
     scaler_17_ctrl_abnormal = 0x003f, /*Scaler 17控制异常 */
     scaler_18_ctrl_abnormal = 0x0040, /*Scaler 18控制异常 */
     scaler_19_ctrl_abnormal = 0x0041, /*Scaler 19控制异常 */
     scaler_20_ctrl_abnormal = 0x0042, /*Scaler 20控制异常 */
     desktop_sign_lost	= 0x0043, /*桌面信号丢失 */			 
     decode_crc_clock_lost	 = 0x0044, /*解串CRC时钟丢失	 */						 
     closk_27M_lost = 0x0045, /*系统27MHz时钟丢失 */
     card_1_loosen= 0x0046, /*板卡位置1未插紧 */		  
     card_2_loosen= 0x0047, /*板卡位置2未插紧 */  
     card_3_loosen = 0x0048, /*板卡位置3未插紧  */ 
     temp_inport_high   = 0x0049, /*进风口温度过高 */
     temp_inport_low= 0x004a, /*进风口温度过低 */
     temp_outport_high = 0x004b, /*出风口温度过高 */
     temp_outport_low	= 0x004c, /*出风口温度过低 */
     unit_A_decode_high= 0x004d, /*单元A解串FPGA温度过高 */
     unit_B_decode_high= 0x004e, /*单元B解串FPGA温度过高 */
     unit_C_decode_high= 0x004f, /*单元C解串FPGA温度过高 */
     unit_D_decode_high= 0x0050, /*单元D解串FPGA温度过高 */
     voltage_0_9V_high = 0x0051, /*0.9V电压过高 */
     voltage_0_9V_low	= 0x0052, /*0.9V电压过低 */
     voltage_1_0V_high = 0x0053, /*1.0V电压过高 */
     voltage_1_0V_low	= 0x0054, /*1.0V电压过低 */
     voltage_1_2V_high = 0x0055, /*1.2V电压过高 */
     voltage_1_2V_low= 0x0056, /*1.2V电压过低 */
     voltage_1_25V_high = 0x0057, /*1.25V电压过高 */
     voltage_1_25V_low = 0x0058, /*1.25V电压过低        */ 
     voltage_1_5V_high= 0x0059, /*1.5V电压过高          */
     voltage_1_5V_low	= 0x005a, /*1.5V电压过低          */
     voltage_1_8V_high = 0x005b, /*1.8V电压过高         */
     voltage_1_8V_low	= 0x005c, /*1.8V电压过低          */
     voltage_2_5V_high = 0x005d, /*2.5V电压过高         */
     voltage_2_5V_low= 0x005e, /*2.5V电压过低           */
     voltage_3_3V_high = 0x005f, /*3.3V电压过高         */
     voltage_3_3V_low	= 0x0060, /*3.3V电压过低          */
     voltage_5_0V_high = 0x0061, /*5.0V电压过高         */
     voltage_5_0V_low	= 0x0062, /*5.0V电压过低          */
     voltage_24_0V_high= 0x0063, /*24.0V电压过高        */
     voltage_24_0V_low= 0x0064, /*24.0V电压过低         */
     voltage_48_0V_high = 0x0065, /*48.0V电压过高       */
     voltage_48_0V_low = 0x0066, /*48.0V电压过低        */
     temp_difference_large= 0x0067, /*温差过大          */
     serdes_0_abnormal = 0x0068, /*serdes通道0异常      */
     serdes_1_abnormal = 0x0069, /*serdes通道1异常      */
     serdes_2_abnormal = 0x0070, /*serdes通道2异常      */
     serdes_3_abnormal = 0x0071, /*serdes通道3异常      */
     serdes_4_abnormal = 0x0072, /*serdes通道4异常      */
     serdes_5_abnormal = 0x0073, /*serdes通道5异常      */
     serdes_6_abnormal = 0x0074, /*serdes通道6异常      */
     serdes_7_abnormal = 0x0075, /*serdes通道7异常      */
     serdes_8_abnormal = 0x0076, /*serdes通道8异常      */
     serdes_9_abnormal = 0x0077, /*serdes通道9异常      */
     serdes_10_abnormal = 0x0078, /*serdes通道10异常    */
     serdes_11_abnormal = 0x0079, /*serdes通道11异常    */
     serdes_12_abnormal = 0x007a, /*serdes通道12异常    */
     serdes_13_abnormal = 0x007b, /*serdes通道13异常    */
     serdes_14_abnormal = 0x007c, /*serdes通道14异常    */
     serdes_15_abnormal = 0x007d, /*serdes通道15异常    */
     serdes_16_abnormal = 0x007e, /*serdes通道16异常    */
     ddr_0_abnormal = 0x007f, /*ddr0工作异常            */
     ddr_1_abnormal = 0x0080, /*ddr1工作异常            */
     ddr_2_abnormal = 0x0081, /*ddr2工作异常            */
     ddr_3_abnormal = 0x0082, /*ddr3工作异常            */
     ddr_4_abnormal = 0x0083, /*ddr4工作异常            */

     /*---------------------------------------------*/
     tmp_vsc3172             = 0x0084, /*交叉片温度异常  */ 
     clk_sys_lost            = 0x0085, /*系统时钟        */
     fans_sys                = 0x0086, /*风扇            */
     pwrs_sys                = 0x0087, /*电源            */
     /*---------------------------------------------*/
     fpga_load_error         = 0x0090, /*fpga加载出错    */
     chip_IP00C751_alarm_a   = 0x0091, /*c751 片1出错    */
     chip_IP00C751_alarm_b   = 0x0092, /*c751 片2出错    */
     chip_IP00C751_alarm_c   = 0x0093, /*c751 片3出错    */
     chip_IP00C751_alarm_d   = 0x0094, /*c751 片4出错    */
    
     background_file_inexistent = 0x0095, /*背景图像文件不存在                                 */ 
     background_file_format_err = 0x0096, /*不支持该图像文件格式                               */

     env_tmp_abnormal=0x0097,/*环境温度异常                                                    */
     bd_tmp_abnormal=0x0098,/*板温度异常                                                       */
     chip_cross_tmp_abnormal=0x0099,/*交叉片温度异常                                           */
     voltage_unite_abnormal=0x009a,/*板上电压异常                                              */

     chip_SI5326_alarm=0x009b,/*2800板上芯片SI5326芯片出错chip SI5326 error                    */
     chip_POWER1014_alarm=0x009c,/*2800板上芯片POWER1014芯片出错 chip POWER1014 error          */
     chip_LM73_alarm=0x009d,/*2800板上芯片LM73芯片出错chip LM73 error                          */
     mainkel_backupfs_alarm=0x009e,/*系统进入主内核备文件系统    mainkel_backupfs_2800ip       */
     backupkel_mainfs_alarm=0x009f,/*系统进入备内核主文件系统     backupkel_mainfs_2800ip      */
     backupkel_backupfs_alarm=0x00a0,/*系统进入备内核备文件系统    backupkel_backupfs_2800ip   */
     minisys_alarm = 0x00a1,/*系统进入最小系统                                                 */
     board_unlock  = 0x00a2, /*处理板未上锁                                                    */
     pcie_abnormal = 0x00a3, /* PCIE 异常                                                       */
};
 
 enum 
 {
    sys_login= 0x0001, /*系统登陆                                 */ 
    sys_upgrade= 0x0002, /*系统升级                               */
    board_online= 0x0003, /*单板上线                              */
    board_offline= 0x0004, /*单板离线                             */
    desktop_sign_change= 0x0005, /*桌面信号源改变                 */
    channel_start= 0x0006, /*通道开启                             */
    channel_stop= 0x0007, /*通道关闭                              */
    desktop_sign_format_change = 0x0008, /*桌面信号格式改变       */
    loopshow_prepared= 0x0009, /*环回显示数据被准备               */
    data_sign_format_change= 0x000a, /*数据采集板信号格式改变     */
    sign_source_change= 0x000b, /*信号源发生变化                  */
    clk_sys_exchange = 0x000c,  /*系统时钟切换                    */
    back_clk_sys_abnormal = 0x000d,  /*系统时钟异常               */
    lcd_poweron           = 0x000e,  /*lcd上线                    */
 };

 enum AlarmState
 {
    ALARM_START= 1,/*告警开始     */ 
    ALARM_CONTINUE = 2,/*告警持续 */
    ALARM_END= 3,/*告警结束       */
 };

 DWORD MC_AlarmReport(DWORD dwAlarmID, BYTE byState, BYTE abyPara[ALARM_PARA_SIZE], DWORD dwSrcMailBox);

 DWORD MC_EventReport(DWORD dwEventID, BYTE abyPara[EVENT_PARA_SIZE], DWORD dwSrcMailBox);

 extern void W2BY(WORD wSrc, BYTE* byDst);
 extern void BY2W(BYTE* bySrc, WORD* wDst);
 extern void BY2DW(BYTE* bySrc, DWORD* dwDst);
 extern void DW2BY(DWORD dwSrc, BYTE* byDst);
 extern void DW2W(DWORD dwSrc, WORD* wDst);
 extern void W2DW(WORD* wSrc, DWORD* dwDst);



#ifdef __cplusplus
}
#endif

#endif __MC_IF_H__

