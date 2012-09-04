/******************************************************************************

  
  ��������     : ����ģ��ͷ�ļ������ⲿ���õĽӿڶ��ڴ��ļ�����
  

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
  *�澯��Դö�٣�ÿ���澯����Ӧ��ֵ���ܹ�����޸ģ�����
  *�澯��ö�ٵײ���������
  */
 enum 
 {
     upgrade_software_failed = 0x0001, /*�������ʧ�� */
     upgrade_file_failed        = 0x0002, /*�����ļ�ʧ�� */
     fpga_file_error                = 0x0003, /*FPGA�ļ����� */
     fpga_file_lost                = 0x0004, /*FPGA�ļ���ʧ */
     file_lost                          = 0x0005, /*�ļ���ʧ */
     file_overflow                  = 0x0006, /*�ļ�������� */
     file_destroyed                 = 0x0007, /*�ļ����ƻ� */
     file_alarm_overflow    = 0x0008, /*�澯�ļ�����澯 */
     flash_bad_block         = 0x0009, /*FLASH������� */
     flash_error                = 0x000A, /*FLASH���� */
     cpu_alarm                   = 0x000B, /*CPUʹ���ʹ��� */
     memory_alarm            = 0x000C, /*�ڴ�ʹ���ʹ��� */
     standby_scc_error   = 0x000D, /*����SCC��·�澯 */
     main_scc_error      = 0x000E, /*��SCC��·�澯 */
     bdsoft_lost            = 0x000F, /*���������ʧ */
     bdsoft_error       = 0x0010, /*����������� */
     i2c_error               = 0x0011, /*I2Cͨ�Ŵ��� */
     spi_error                  = 0x0012, /*SPIͨ�Ŵ��� */
     eth_link_error  = 0x0013, /*��̫�����Ӵ��� */
     FAT_error = 0x0014, /*�ļ��������� */
     /*desktop_sign_change	   = 0x0015, //�����ź�Դ�����ı� */
     fan_abnormal= 0x0016, /*�����쳣 */
     fan_invalid= 0x0017, /*����ʧЧ */
     clock_error= 0x0018, /*ʱ�Ӵ��� */
     fpga_error = 0x0019, /*FPGA ���� */
     fpga_fifo_error= 0x001A, /*FPGA FIFO���� */
     sign_format_error= 0x001B, /*�źŸ�ʽ���� */
     sign_format_change = 0x001C, /*�źŸ�ʽ�ı� */
     /*sign_source_change	   = 0x001D, //�ź�Դ�����仯 */
     chip_AD9888_alarm= 0x001E, /*AD9888оƬ���� */
     chip_TVP5160_alarm= 0x001F, /*TVP5160оƬ���� */
     chip_SII1161_alarm = 0x0020, /*SII1161оƬ���� */
     chip_IP00C751_alarm= 0x0021, /*IP00C751оƬ���� */
     logic_alarm = 0x0022, /*Ӳ���߼����� */
     chip_VSC3108_alarm= 0x0023, /*VSC3108оƬ���� */
     double_synclk_invalid= 0x0024, /*˫·ͬ��ʱ����Ч */
     single_synclk_invalid= 0x0025, /*��·ͬ��ʱ����Ч */
     synclk_lost= 0x0026, /*ͬ��ʱ�Ӷ�ʧ */
     unit_A_decode_abnormal  = 0x0027, /*��ԪA�⴮FPGA�߼��쳣 */
     unit_B_decode_abnormal  = 0x0028, /*��ԪB�⴮FPGA�߼��쳣 */
     unit_C_decode_abnormal  = 0x0029, /*��ԪC�⴮FPGA�߼��쳣 */
     unit_D_decode_abnormal  = 0x002a, /*��ԪD�⴮FPGA�߼��쳣 */
     unit_A_overlap_abnormal = 0x002b, /*��ԪA����FPGA�߼��쳣 */
     unit_B_overlap_abnormal = 0x002c, /*��ԪB����FPGA�߼��쳣 */
     unit_C_overlap_abnormal = 0x002d, /*��ԪC����FPGA�߼��쳣 */
     unit_D_overlap_abnormal = 0x002e, /*��ԪD����FPGA�߼��쳣 */
     scaler_1_ctrl_abnormal  = 0x002f, /*Scaler 1�����쳣 */
     scaler_2_ctrl_abnormal  = 0x0030, /*Scaler 2�����쳣 */
     scaler_3_ctrl_abnormal  = 0x0031, /*Scaler 3�����쳣 */
     scaler_4_ctrl_abnormal  = 0x0032, /*Scaler 4�����쳣 */
     scaler_5_ctrl_abnormal  = 0x0033, /*Scaler 5�����쳣 */
     scaler_6_ctrl_abnormal  = 0x0034, /*Scaler 6�����쳣 */
     scaler_7_ctrl_abnormal  = 0x0035, /*Scaler 7�����쳣 */
     scaler_8_ctrl_abnormal  = 0x0036, /*Scaler 8�����쳣 */
     scaler_9_ctrl_abnormal  = 0x0037, /*Scaler 9�����쳣 */
     scaler_10_ctrl_abnormal = 0x0038, /*Scaler 10�����쳣 */
     scaler_11_ctrl_abnormal = 0x0039, /*Scaler 11�����쳣 */
     scaler_12_ctrl_abnormal = 0x003a, /*Scaler 12�����쳣 */
     scaler_13_ctrl_abnormal = 0x003b, /*Scaler 13�����쳣 */
     scaler_14_ctrl_abnormal = 0x003c, /*Scaler 14�����쳣 */
     scaler_15_ctrl_abnormal = 0x003d, /*Scaler 15�����쳣 */
     scaler_16_ctrl_abnormal = 0x003e, /*Scaler 16�����쳣 */
     scaler_17_ctrl_abnormal = 0x003f, /*Scaler 17�����쳣 */
     scaler_18_ctrl_abnormal = 0x0040, /*Scaler 18�����쳣 */
     scaler_19_ctrl_abnormal = 0x0041, /*Scaler 19�����쳣 */
     scaler_20_ctrl_abnormal = 0x0042, /*Scaler 20�����쳣 */
     desktop_sign_lost	= 0x0043, /*�����źŶ�ʧ */			 
     decode_crc_clock_lost	 = 0x0044, /*�⴮CRCʱ�Ӷ�ʧ	 */						 
     closk_27M_lost = 0x0045, /*ϵͳ27MHzʱ�Ӷ�ʧ */
     card_1_loosen= 0x0046, /*�忨λ��1δ��� */		  
     card_2_loosen= 0x0047, /*�忨λ��2δ��� */  
     card_3_loosen = 0x0048, /*�忨λ��3δ���  */ 
     temp_inport_high   = 0x0049, /*������¶ȹ��� */
     temp_inport_low= 0x004a, /*������¶ȹ��� */
     temp_outport_high = 0x004b, /*������¶ȹ��� */
     temp_outport_low	= 0x004c, /*������¶ȹ��� */
     unit_A_decode_high= 0x004d, /*��ԪA�⴮FPGA�¶ȹ��� */
     unit_B_decode_high= 0x004e, /*��ԪB�⴮FPGA�¶ȹ��� */
     unit_C_decode_high= 0x004f, /*��ԪC�⴮FPGA�¶ȹ��� */
     unit_D_decode_high= 0x0050, /*��ԪD�⴮FPGA�¶ȹ��� */
     voltage_0_9V_high = 0x0051, /*0.9V��ѹ���� */
     voltage_0_9V_low	= 0x0052, /*0.9V��ѹ���� */
     voltage_1_0V_high = 0x0053, /*1.0V��ѹ���� */
     voltage_1_0V_low	= 0x0054, /*1.0V��ѹ���� */
     voltage_1_2V_high = 0x0055, /*1.2V��ѹ���� */
     voltage_1_2V_low= 0x0056, /*1.2V��ѹ���� */
     voltage_1_25V_high = 0x0057, /*1.25V��ѹ���� */
     voltage_1_25V_low = 0x0058, /*1.25V��ѹ����        */ 
     voltage_1_5V_high= 0x0059, /*1.5V��ѹ����          */
     voltage_1_5V_low	= 0x005a, /*1.5V��ѹ����          */
     voltage_1_8V_high = 0x005b, /*1.8V��ѹ����         */
     voltage_1_8V_low	= 0x005c, /*1.8V��ѹ����          */
     voltage_2_5V_high = 0x005d, /*2.5V��ѹ����         */
     voltage_2_5V_low= 0x005e, /*2.5V��ѹ����           */
     voltage_3_3V_high = 0x005f, /*3.3V��ѹ����         */
     voltage_3_3V_low	= 0x0060, /*3.3V��ѹ����          */
     voltage_5_0V_high = 0x0061, /*5.0V��ѹ����         */
     voltage_5_0V_low	= 0x0062, /*5.0V��ѹ����          */
     voltage_24_0V_high= 0x0063, /*24.0V��ѹ����        */
     voltage_24_0V_low= 0x0064, /*24.0V��ѹ����         */
     voltage_48_0V_high = 0x0065, /*48.0V��ѹ����       */
     voltage_48_0V_low = 0x0066, /*48.0V��ѹ����        */
     temp_difference_large= 0x0067, /*�²����          */
     serdes_0_abnormal = 0x0068, /*serdesͨ��0�쳣      */
     serdes_1_abnormal = 0x0069, /*serdesͨ��1�쳣      */
     serdes_2_abnormal = 0x0070, /*serdesͨ��2�쳣      */
     serdes_3_abnormal = 0x0071, /*serdesͨ��3�쳣      */
     serdes_4_abnormal = 0x0072, /*serdesͨ��4�쳣      */
     serdes_5_abnormal = 0x0073, /*serdesͨ��5�쳣      */
     serdes_6_abnormal = 0x0074, /*serdesͨ��6�쳣      */
     serdes_7_abnormal = 0x0075, /*serdesͨ��7�쳣      */
     serdes_8_abnormal = 0x0076, /*serdesͨ��8�쳣      */
     serdes_9_abnormal = 0x0077, /*serdesͨ��9�쳣      */
     serdes_10_abnormal = 0x0078, /*serdesͨ��10�쳣    */
     serdes_11_abnormal = 0x0079, /*serdesͨ��11�쳣    */
     serdes_12_abnormal = 0x007a, /*serdesͨ��12�쳣    */
     serdes_13_abnormal = 0x007b, /*serdesͨ��13�쳣    */
     serdes_14_abnormal = 0x007c, /*serdesͨ��14�쳣    */
     serdes_15_abnormal = 0x007d, /*serdesͨ��15�쳣    */
     serdes_16_abnormal = 0x007e, /*serdesͨ��16�쳣    */
     ddr_0_abnormal = 0x007f, /*ddr0�����쳣            */
     ddr_1_abnormal = 0x0080, /*ddr1�����쳣            */
     ddr_2_abnormal = 0x0081, /*ddr2�����쳣            */
     ddr_3_abnormal = 0x0082, /*ddr3�����쳣            */
     ddr_4_abnormal = 0x0083, /*ddr4�����쳣            */

     /*---------------------------------------------*/
     tmp_vsc3172             = 0x0084, /*����Ƭ�¶��쳣  */ 
     clk_sys_lost            = 0x0085, /*ϵͳʱ��        */
     fans_sys                = 0x0086, /*����            */
     pwrs_sys                = 0x0087, /*��Դ            */
     /*---------------------------------------------*/
     fpga_load_error         = 0x0090, /*fpga���س���    */
     chip_IP00C751_alarm_a   = 0x0091, /*c751 Ƭ1����    */
     chip_IP00C751_alarm_b   = 0x0092, /*c751 Ƭ2����    */
     chip_IP00C751_alarm_c   = 0x0093, /*c751 Ƭ3����    */
     chip_IP00C751_alarm_d   = 0x0094, /*c751 Ƭ4����    */
    
     background_file_inexistent = 0x0095, /*����ͼ���ļ�������                                 */ 
     background_file_format_err = 0x0096, /*��֧�ָ�ͼ���ļ���ʽ                               */

     env_tmp_abnormal=0x0097,/*�����¶��쳣                                                    */
     bd_tmp_abnormal=0x0098,/*���¶��쳣                                                       */
     chip_cross_tmp_abnormal=0x0099,/*����Ƭ�¶��쳣                                           */
     voltage_unite_abnormal=0x009a,/*���ϵ�ѹ�쳣                                              */

     chip_SI5326_alarm=0x009b,/*2800����оƬSI5326оƬ����chip SI5326 error                    */
     chip_POWER1014_alarm=0x009c,/*2800����оƬPOWER1014оƬ���� chip POWER1014 error          */
     chip_LM73_alarm=0x009d,/*2800����оƬLM73оƬ����chip LM73 error                          */
     mainkel_backupfs_alarm=0x009e,/*ϵͳ�������ں˱��ļ�ϵͳ    mainkel_backupfs_2800ip       */
     backupkel_mainfs_alarm=0x009f,/*ϵͳ���뱸�ں����ļ�ϵͳ     backupkel_mainfs_2800ip      */
     backupkel_backupfs_alarm=0x00a0,/*ϵͳ���뱸�ں˱��ļ�ϵͳ    backupkel_backupfs_2800ip   */
     minisys_alarm = 0x00a1,/*ϵͳ������Сϵͳ                                                 */
     board_unlock  = 0x00a2, /*�����δ����                                                    */
     pcie_abnormal = 0x00a3, /* PCIE �쳣                                                       */
};
 
 enum 
 {
    sys_login= 0x0001, /*ϵͳ��½                                 */ 
    sys_upgrade= 0x0002, /*ϵͳ����                               */
    board_online= 0x0003, /*��������                              */
    board_offline= 0x0004, /*��������                             */
    desktop_sign_change= 0x0005, /*�����ź�Դ�ı�                 */
    channel_start= 0x0006, /*ͨ������                             */
    channel_stop= 0x0007, /*ͨ���ر�                              */
    desktop_sign_format_change = 0x0008, /*�����źŸ�ʽ�ı�       */
    loopshow_prepared= 0x0009, /*������ʾ���ݱ�׼��               */
    data_sign_format_change= 0x000a, /*���ݲɼ����źŸ�ʽ�ı�     */
    sign_source_change= 0x000b, /*�ź�Դ�����仯                  */
    clk_sys_exchange = 0x000c,  /*ϵͳʱ���л�                    */
    back_clk_sys_abnormal = 0x000d,  /*ϵͳʱ���쳣               */
    lcd_poweron           = 0x000e,  /*lcd����                    */
 };

 enum AlarmState
 {
    ALARM_START= 1,/*�澯��ʼ     */ 
    ALARM_CONTINUE = 2,/*�澯���� */
    ALARM_END= 3,/*�澯����       */
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

