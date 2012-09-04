/* symTbl.c - standalone symbol tables wrapper */

/* CREATED BY C:\Tornado2.2/host/src/hutils/makeSymTbl.tcl
 *  WITH ARGS arm tmp.o symTbl.c
 *         ON Mon Jun 04 17:28:40 China Standard Time 2012
 */

#include "vxWorks.h"
#include "symbol.h"

IMPORT int AT91F_AIC_AcknowledgeIt ();
IMPORT int AT91F_AIC_CfgPMC ();
IMPORT int AT91F_AIC_ClearIt ();
IMPORT int AT91F_AIC_ConfigureIt ();
IMPORT int AT91F_AIC_DisableIt ();
IMPORT int AT91F_AIC_EnableIt ();
IMPORT int AT91F_AIC_IsActive ();
IMPORT int AT91F_AIC_IsPending ();
IMPORT int AT91F_AIC_Open ();
IMPORT int AT91F_AIC_SetExceptionVector ();
IMPORT int AT91F_AIC_Trig ();
IMPORT int AT91F_CKGR_GetMainClock ();
IMPORT int AT91F_DBGU_CfgPIO ();
IMPORT int AT91F_DBGU_CfgPMC ();
IMPORT int AT91F_DBGU_GetInterruptMaskStatus ();
IMPORT int AT91F_DBGU_InterruptDisable ();
IMPORT int AT91F_DBGU_InterruptEnable ();
IMPORT int AT91F_DBGU_IsInterruptMasked ();
IMPORT int AT91F_EBI_CfgPIO ();
IMPORT int AT91F_EMAC_CfgPIO ();
IMPORT int AT91F_EMAC_CfgPMC ();
IMPORT int AT91F_MCI_CfgPIO ();
IMPORT int AT91F_MCI_CfgPMC ();
IMPORT int AT91F_MCI_Cfg_ModeRegister ();
IMPORT int AT91F_MCI_Configure ();
IMPORT int AT91F_MCI_DisableIt ();
IMPORT int AT91F_MCI_Disable_Interface ();
IMPORT int AT91F_MCI_EnableIt ();
IMPORT int AT91F_MCI_Enable_Interface ();
IMPORT int AT91F_PDC_Close ();
IMPORT int AT91F_PDC_DisableRx ();
IMPORT int AT91F_PDC_DisableTx ();
IMPORT int AT91F_PDC_EnableRx ();
IMPORT int AT91F_PDC_EnableTx ();
IMPORT int AT91F_PDC_IsNextRxEmpty ();
IMPORT int AT91F_PDC_IsNextTxEmpty ();
IMPORT int AT91F_PDC_IsRxEmpty ();
IMPORT int AT91F_PDC_IsTxEmpty ();
IMPORT int AT91F_PDC_Open ();
IMPORT int AT91F_PDC_ReceiveFrame ();
IMPORT int AT91F_PDC_SendFrame ();
IMPORT int AT91F_PDC_SetNextRx ();
IMPORT int AT91F_PDC_SetNextTx ();
IMPORT int AT91F_PDC_SetRx ();
IMPORT int AT91F_PDC_SetTx ();
IMPORT int AT91F_PIOA_CfgPMC ();
IMPORT int AT91F_PIOB_CfgPMC ();
IMPORT int AT91F_PIOC_CfgPMC ();
IMPORT int AT91F_PIOD_CfgPMC ();
IMPORT int AT91F_PIO_A_RegisterSelection ();
IMPORT int AT91F_PIO_B_RegisterSelection ();
IMPORT int AT91F_PIO_CfgDirectDrive ();
IMPORT int AT91F_PIO_CfgInput ();
IMPORT int AT91F_PIO_CfgInputFilter ();
IMPORT int AT91F_PIO_CfgOpendrain ();
IMPORT int AT91F_PIO_CfgOutput ();
IMPORT int AT91F_PIO_CfgPeriph ();
IMPORT int AT91F_PIO_CfgPullup ();
IMPORT int AT91F_PIO_ClearOutput ();
IMPORT int AT91F_PIO_Disable ();
IMPORT int AT91F_PIO_Enable ();
IMPORT int AT91F_PIO_ForceOutput ();
IMPORT int AT91F_PIO_GetCfgPullup ();
IMPORT int AT91F_PIO_GetInput ();
IMPORT int AT91F_PIO_GetInputFilterStatus ();
IMPORT int AT91F_PIO_GetInterruptMaskStatus ();
IMPORT int AT91F_PIO_GetInterruptStatus ();
IMPORT int AT91F_PIO_GetMultiDriverStatus ();
IMPORT int AT91F_PIO_GetOutputDataStatus ();
IMPORT int AT91F_PIO_GetOutputStatus ();
IMPORT int AT91F_PIO_GetOutputWriteStatus ();
IMPORT int AT91F_PIO_GetStatus ();
IMPORT int AT91F_PIO_Get_AB_RegisterStatus ();
IMPORT int AT91F_PIO_InputFilterDisable ();
IMPORT int AT91F_PIO_InputFilterEnable ();
IMPORT int AT91F_PIO_InterruptDisable ();
IMPORT int AT91F_PIO_InterruptEnable ();
IMPORT int AT91F_PIO_IsAB_RegisterSet ();
IMPORT int AT91F_PIO_IsCfgPullupStatusSet ();
IMPORT int AT91F_PIO_IsInputFilterSet ();
IMPORT int AT91F_PIO_IsInputSet ();
IMPORT int AT91F_PIO_IsInterruptMasked ();
IMPORT int AT91F_PIO_IsInterruptSet ();
IMPORT int AT91F_PIO_IsMultiDriverSet ();
IMPORT int AT91F_PIO_IsOutputDataStatusSet ();
IMPORT int AT91F_PIO_IsOutputSet ();
IMPORT int AT91F_PIO_IsOutputWriteSet ();
IMPORT int AT91F_PIO_IsSet ();
IMPORT int AT91F_PIO_MultiDriverDisable ();
IMPORT int AT91F_PIO_MultiDriverEnable ();
IMPORT int AT91F_PIO_OutputDisable ();
IMPORT int AT91F_PIO_OutputEnable ();
IMPORT int AT91F_PIO_OutputWriteDisable ();
IMPORT int AT91F_PIO_OutputWriteEnable ();
IMPORT int AT91F_PIO_SetOutput ();
IMPORT int AT91F_PMC_CfgPIO ();
IMPORT int AT91F_PMC_CfgPMC ();
IMPORT int AT91F_PMC_DisablePCK ();
IMPORT int AT91F_PMC_DisablePeriphClock ();
IMPORT int AT91F_PMC_EnablePCK ();
IMPORT int AT91F_PMC_EnablePeriphClock ();
IMPORT int AT91F_PMC_GetMasterClock ();
IMPORT int AT91F_PMC_GetProcessorClock ();
IMPORT int AT91F_RTC_CfgPMC ();
IMPORT int AT91F_RTC_GetInterruptMaskStatus ();
IMPORT int AT91F_RTC_InterruptDisable ();
IMPORT int AT91F_RTC_InterruptEnable ();
IMPORT int AT91F_RTC_IsInterruptMasked ();
IMPORT int AT91F_SDRC_CfgPIO ();
IMPORT int AT91F_SMC2_CfgPIO ();
IMPORT int AT91F_SPI_CfgCs ();
IMPORT int AT91F_SPI_CfgMode ();
IMPORT int AT91F_SPI_CfgPCS ();
IMPORT int AT91F_SPI_CfgPIO ();
IMPORT int AT91F_SPI_CfgPMC ();
IMPORT int AT91F_SPI_Close ();
IMPORT int AT91F_SPI_Disable ();
IMPORT int AT91F_SPI_DisableIt ();
IMPORT int AT91F_SPI_Enable ();
IMPORT int AT91F_SPI_EnableIt ();
IMPORT int AT91F_SPI_GetChar ();
IMPORT int AT91F_SPI_GetInterruptMaskStatus ();
IMPORT int AT91F_SPI_IsInterruptMasked ();
IMPORT int AT91F_SPI_Open ();
IMPORT int AT91F_SPI_PutChar ();
IMPORT int AT91F_SPI_ReceiveFrame ();
IMPORT int AT91F_SPI_Reset ();
IMPORT int AT91F_SPI_SendFrame ();
IMPORT int AT91F_SSC0_CfgPIO ();
IMPORT int AT91F_SSC0_CfgPMC ();
IMPORT int AT91F_SSC1_CfgPIO ();
IMPORT int AT91F_SSC1_CfgPMC ();
IMPORT int AT91F_SSC2_CfgPIO ();
IMPORT int AT91F_SSC2_CfgPMC ();
IMPORT int AT91F_SSC_Configure ();
IMPORT int AT91F_SSC_DisableIt ();
IMPORT int AT91F_SSC_DisableRx ();
IMPORT int AT91F_SSC_DisableTx ();
IMPORT int AT91F_SSC_EnableIt ();
IMPORT int AT91F_SSC_EnableRx ();
IMPORT int AT91F_SSC_EnableTx ();
IMPORT int AT91F_SSC_GetInterruptMaskStatus ();
IMPORT int AT91F_SSC_GetStatus ();
IMPORT int AT91F_SSC_IsInterruptMasked ();
IMPORT int AT91F_SSC_ReceiveFrame ();
IMPORT int AT91F_SSC_SendFrame ();
IMPORT int AT91F_SSC_SetBaudrate ();
IMPORT int AT91F_ST_CfgPMC ();
IMPORT int AT91F_ST_DisableIt ();
IMPORT int AT91F_ST_EnableIt ();
IMPORT int AT91F_ST_GetInterruptMaskStatus ();
IMPORT int AT91F_ST_IsInterruptMasked ();
IMPORT int AT91F_SYS_CfgPMC ();
IMPORT int AT91F_TC0_CfgPMC ();
IMPORT int AT91F_TC1_CfgPMC ();
IMPORT int AT91F_TC2_CfgPMC ();
IMPORT int AT91F_TC3_CfgPMC ();
IMPORT int AT91F_TC4_CfgPMC ();
IMPORT int AT91F_TC5_CfgPMC ();
IMPORT int AT91F_TC_GetInterruptMaskStatus ();
IMPORT int AT91F_TC_InterruptDisable ();
IMPORT int AT91F_TC_InterruptEnable ();
IMPORT int AT91F_TC_IsInterruptMasked ();
IMPORT int AT91F_TWI_CfgPIO ();
IMPORT int AT91F_TWI_CfgPMC ();
IMPORT int AT91F_TWI_Configure ();
IMPORT int AT91F_TWI_DisableIt ();
IMPORT int AT91F_TWI_EnableIt ();
IMPORT int AT91F_TWI_GetInterruptMaskStatus ();
IMPORT int AT91F_TWI_IsInterruptMasked ();
IMPORT int AT91F_UDP_CfgPMC ();
IMPORT int AT91F_UDP_DisableEp ();
IMPORT int AT91F_UDP_DisableIt ();
IMPORT int AT91F_UDP_EnableEp ();
IMPORT int AT91F_UDP_EnableIt ();
IMPORT int AT91F_UDP_EpClear ();
IMPORT int AT91F_UDP_EpEndOfWr ();
IMPORT int AT91F_UDP_EpRead ();
IMPORT int AT91F_UDP_EpSet ();
IMPORT int AT91F_UDP_EpStall ();
IMPORT int AT91F_UDP_EpStatus ();
IMPORT int AT91F_UDP_EpWrite ();
IMPORT int AT91F_UDP_GetInterruptMaskStatus ();
IMPORT int AT91F_UDP_GetState ();
IMPORT int AT91F_UDP_IsInterruptMasked ();
IMPORT int AT91F_UDP_ResetEp ();
IMPORT int AT91F_UDP_SetAddress ();
IMPORT int AT91F_UDP_SetState ();
IMPORT int AT91F_UHP_CfgPMC ();
IMPORT int AT91F_US0_CfgPIO ();
IMPORT int AT91F_US0_CfgPMC ();
IMPORT int AT91F_US1_CfgPIO ();
IMPORT int AT91F_US1_CfgPMC ();
IMPORT int AT91F_US2_CfgPIO ();
IMPORT int AT91F_US2_CfgPMC ();
IMPORT int AT91F_US3_CfgPMC ();
IMPORT int AT91F_US_Baudrate ();
IMPORT int AT91F_US_Close ();
IMPORT int AT91F_US_Configure ();
IMPORT int AT91F_US_DisableIt ();
IMPORT int AT91F_US_DisableRx ();
IMPORT int AT91F_US_DisableTx ();
IMPORT int AT91F_US_EnableIt ();
IMPORT int AT91F_US_EnableRx ();
IMPORT int AT91F_US_EnableTx ();
IMPORT int AT91F_US_Error ();
IMPORT int AT91F_US_GetChar ();
IMPORT int AT91F_US_PutChar ();
IMPORT int AT91F_US_ReceiveFrame ();
IMPORT int AT91F_US_ResetRx ();
IMPORT int AT91F_US_ResetTx ();
IMPORT int AT91F_US_RxReady ();
IMPORT int AT91F_US_SendFrame ();
IMPORT int AT91F_US_SetBaudrate ();
IMPORT int AT91F_US_SetIrdaFilter ();
IMPORT int AT91F_US_SetTimeguard ();
IMPORT int AT91F_US_TxReady ();
IMPORT int Add485Node__12C485NodePoolUcUc ();
IMPORT int AddAlarmNode__10CAlarmInfoRC13st_Alarm_InfoUc ();
IMPORT int AddDumbTimes__11CSocketNode ();
IMPORT int AddDumbTimes__11CSocketPoolRCl ();
IMPORT int AddDumbTimes__12C485NodePoolUc ();
IMPORT int AddDumbTimes__9CLinkNode ();
IMPORT int AddErrorTimes__11CSocketNode ();
IMPORT int AddErrorTimes__11CSocketPoolRCl ();
IMPORT int AddErrorTimes__12C485NodePoolUc ();
IMPORT int AddErrorTimes__9CLinkNode ();
IMPORT int AddFunction__6CBoardP5CRoot ();
IMPORT int AddMessages__7CModuleUs ();
IMPORT int AddRcvCtrlPackages__15CPackageCounter ();
IMPORT int AddRcvDataPackages__15CPackageCounter ();
IMPORT int AddRcvNormalPackages__15CPackageCounter ();
IMPORT int AddReceiveOKTimes__15CPackageCounter ();
IMPORT int AddReceiveTimes__15CPackageCounter ();
IMPORT int AddRecvCounter__C12CCtrlPackageR15CPackageCounter ();
IMPORT int AddRecvCounter__C12CDataPackageR15CPackageCounter ();
IMPORT int AddRecvCounter__C8CPackageR15CPackageCounter ();
IMPORT int AddSendCounter__C12CCtrlPackageR15CPackageCounter ();
IMPORT int AddSendCounter__C12CDataPackageR15CPackageCounter ();
IMPORT int AddSendCounter__C8CPackageR15CPackageCounter ();
IMPORT int AddSendCtrlPackages__15CPackageCounter ();
IMPORT int AddSendDataPackages__15CPackageCounter ();
IMPORT int AddSendOKTimes__15CPackageCounter ();
IMPORT int AddSendTimes__15CPackageCounter ();
IMPORT int AddSocketNode__11CSocketPoollUlUcUc ();
IMPORT int AlarmRspCmdToNs__FP10VWAS_CMD_SUlUl ();
IMPORT int AllocateBlock__11CMemoryPool ();
IMPORT int AllocateInputChannel__6CCrossUc ();
IMPORT int AllocateMessage__13CAppInterfaceUsPP9S_MESSAGE ();
IMPORT int AllocateOutputChannel__6CCrossPUcUc ();
IMPORT int AllocateTimerID__12CTimerIDPool ();
IMPORT int AutoReportAlarm__10CAlarmInfoP10VWAS_CMD_SUcUl ();
IMPORT int AutoReportEvent__10CAlarmInfoP10VWAS_CMD_SUcUl ();
IMPORT int AutoWhiteBalance__8CChannelP10VWAS_CMD_SUl ();
IMPORT int BSPBooter ();
IMPORT int BSPCheckSum ();
IMPORT int BSPGetSoft ();
IMPORT int BSPGetSoft_TEST ();
IMPORT int BSPLoadSoft ();
IMPORT int BSP_AT91F_OR_PIO_CfgInput ();
IMPORT int BSP_AT91F_OR_PIO_CfgOutput ();
IMPORT int BSP_AT91F_OR_PIO_CfgPeriphA ();
IMPORT int BSP_AT91F_OR_PIO_CfgPeriphB ();
IMPORT int BSP_AT91F_OR_PIO_ClearOutput ();
IMPORT int BSP_AT91F_OR_PIO_GetInput ();
IMPORT int BSP_AT91F_OR_PIO_SetOutput ();
IMPORT int BSP_AT91F_PIO_A_RegisterSelection ();
IMPORT int BSP_AT91F_PIO_B_RegisterSelection ();
IMPORT int BSP_AT91F_PIO_CfgInputFilter ();
IMPORT int BSP_AT91F_PIO_CfgOpendrain ();
IMPORT int BSP_AT91F_PIO_CfgPullup ();
IMPORT int BSP_AT91F_PIO_CfgPullupDisable ();
IMPORT int BSP_AT91F_PIO_CfgdwDirectDrive ();
IMPORT int BSP_AT91F_PIO_Disable ();
IMPORT int BSP_AT91F_PIO_Enable ();
IMPORT int BSP_AT91F_PIO_ForceOutput ();
IMPORT int BSP_AT91F_PIO_GetCfgPullup ();
IMPORT int BSP_AT91F_PIO_GetInput ();
IMPORT int BSP_AT91F_PIO_GetInputFilterStatus ();
IMPORT int BSP_AT91F_PIO_GetInterruptMaskStatus ();
IMPORT int BSP_AT91F_PIO_GetInterruptStatus ();
IMPORT int BSP_AT91F_PIO_GetMultiDriverStatus ();
IMPORT int BSP_AT91F_PIO_GetOutputDataStatus ();
IMPORT int BSP_AT91F_PIO_GetOutputStatus ();
IMPORT int BSP_AT91F_PIO_GetOutputWriteStatus ();
IMPORT int BSP_AT91F_PIO_GetStatus ();
IMPORT int BSP_AT91F_PIO_Get_AB_RegisterStatus ();
IMPORT int BSP_AT91F_PIO_InputFilterDisable ();
IMPORT int BSP_AT91F_PIO_InputFilterEnable ();
IMPORT int BSP_AT91F_PIO_InterruptDisable ();
IMPORT int BSP_AT91F_PIO_InterruptEnable ();
IMPORT int BSP_AT91F_PIO_IsAB_RegisterSet ();
IMPORT int BSP_AT91F_PIO_IsCfgPullupStatusSet ();
IMPORT int BSP_AT91F_PIO_IsInputFilterSet ();
IMPORT int BSP_AT91F_PIO_IsInputSet ();
IMPORT int BSP_AT91F_PIO_IsInterruptMasked ();
IMPORT int BSP_AT91F_PIO_IsInterruptSet ();
IMPORT int BSP_AT91F_PIO_IsMultiDriverSet ();
IMPORT int BSP_AT91F_PIO_IsOutputDataStatusSet ();
IMPORT int BSP_AT91F_PIO_IsOutputSet ();
IMPORT int BSP_AT91F_PIO_IsOutputWriteSet ();
IMPORT int BSP_AT91F_PIO_IsSet ();
IMPORT int BSP_AT91F_PIO_MultiDriverDisable ();
IMPORT int BSP_AT91F_PIO_MultiDriverEnable ();
IMPORT int BSP_AT91F_PIO_OutputDisable ();
IMPORT int BSP_AT91F_PIO_OutputEnable ();
IMPORT int BSP_AT91F_PIO_OutputWriteDisable ();
IMPORT int BSP_AT91F_PIO_OutputWriteEnable ();
IMPORT int BSP_BoardIsOnline ();
IMPORT int BSP_BoardSolt ();
IMPORT int BSP_CalBackTest ();
IMPORT int BSP_CpuUsage ();
IMPORT int BSP_Debug ();
IMPORT int BSP_DeleteSoft ();
IMPORT int BSP_DisableHardDog ();
IMPORT int BSP_DrvGetMac ();
IMPORT int BSP_DrvInit ();
IMPORT int BSP_EnableHardDog ();
IMPORT int BSP_FeedHardDog ();
IMPORT int BSP_FlashWriteEnable ();
IMPORT int BSP_GetAllFPGAStatus ();
IMPORT int BSP_GetBoardTypeId ();
IMPORT int BSP_GetBoardslotNo ();
IMPORT int BSP_GetBootromStatus ();
IMPORT int BSP_GetBootromVer ();
IMPORT int BSP_GetCurSecondTest ();
IMPORT int BSP_GetCurStatus ();
IMPORT int BSP_GetCurSysDateTime ();
IMPORT int BSP_GetCurSysDateTimeBySecond ();
IMPORT int BSP_GetCurTimeTest ();
IMPORT int BSP_GetFPGAStatus ();
IMPORT int BSP_GetFpgaVer ();
IMPORT int BSP_GetMainSoftStatus ();
IMPORT int BSP_GetManInfo ();
IMPORT int BSP_GetMiniSysVer ();
IMPORT int BSP_GetMiniSystemStatus ();
IMPORT int BSP_GetPcbVer ();
IMPORT int BSP_GetSysSoftVer ();
IMPORT int BSP_GetTemperatureVal ();
IMPORT int BSP_GetVoltageStatus ();
IMPORT int BSP_InitPll ();
IMPORT int BSP_LoadFpga ();
IMPORT int BSP_LoadFpga_ALTERA ();
IMPORT int BSP_LoadFpga_LATTICE ();
IMPORT int BSP_MULTest ();
IMPORT int BSP_MemUsage ();
IMPORT int BSP_MulAdd ();
IMPORT int BSP_NandFlashFileGetLength ();
IMPORT int BSP_NandFlashFileInit ();
IMPORT int BSP_NandFlashFileRead ();
IMPORT int BSP_NandFlashFileRead_L ();
IMPORT int BSP_NandFlashFileWrite ();
IMPORT int BSP_NandFlashFileWrite_L ();
IMPORT int BSP_NandFlashIDGet ();
IMPORT int BSP_NandFlashReset ();
IMPORT int BSP_PHYRead ();
IMPORT int BSP_PHYScan ();
IMPORT int BSP_RTCTEST ();
IMPORT int BSP_Read5324 ();
IMPORT int BSP_ReceiveUrgentFrame ();
IMPORT int BSP_Reset ();
IMPORT int BSP_ResetFpga ();
IMPORT int BSP_Reset_FPGA ();
IMPORT int BSP_Reset_PCIE ();
IMPORT int BSP_RunAllTask ();
IMPORT int BSP_SaveFile ();
IMPORT int BSP_SetCurSysDateTime ();
IMPORT int BSP_SetCurTimeTest ();
IMPORT int BSP_ShowDog ();
IMPORT int BSP_SoftBackUP ();
IMPORT int BSP_SoftStart ();
IMPORT int BSP_SoftUpgrade ();
IMPORT int BSP_SoftWareUPTest ();
IMPORT int BSP_SoftWareUPinit ();
IMPORT int BSP_StopAllTask ();
IMPORT int BSP_SysAlarmLedFlic ();
IMPORT int BSP_SysRunLedFlic ();
IMPORT int BSP_TEST ();
IMPORT int BSP_TimeGet ();
IMPORT int BSP_TimeInit ();
IMPORT int BSP_UP;
IMPORT int BSP_UrgencySend ();
IMPORT int BSP_UrgencySetMulAdd ();
IMPORT int BSP_Write5324 ();
IMPORT int BSP_disable_mdi ();
IMPORT int BSP_enable_mdi ();
IMPORT int BSP_memPartShow ();
IMPORT int BSP_read_phy ();
IMPORT int BSP_write_phy ();
IMPORT int BY2DW ();
IMPORT int BY2W ();
IMPORT int Bbase__9streambuf ();
IMPORT int BdGetTestTime ();
IMPORT int BeginUpgrade__12CSoftUpGradeP10VWAS_CMD_SUl ();
IMPORT int BinarySearchLeft__5CFileUlUlR5SYS_T ();
IMPORT int BinarySearchRight__5CFileUlUlR5SYS_T ();
IMPORT int BoardID2Socket__11CSocketPoolUcRl ();
IMPORT int BoardOfflineTest__FUcUc ();
IMPORT int BoardOffline__14CModuleManagerUlUc ();
IMPORT int BoardOnlineTest__FUcUc ();
IMPORT int BoardOnline__14CModuleManagerUlUc ();
IMPORT int Bptr__9streambuf ();
IMPORT int CRC;
IMPORT int CRC_Poly;
IMPORT int CancelUpgrade__12CSoftUpGradeP10VWAS_CMD_SUl ();
IMPORT int CfgRspCmdToNs__FP10VWAS_CMD_SUlUl ();
IMPORT int CfgSendCmdToBsWaitReturn__FUcP10VWAS_CMD_SUlUlT1 ();
IMPORT int CfgSendCmdToBs__FUcP10VWAS_CMD_SUlUl ();
IMPORT int ChannelMap__10COperationUcUc ();
IMPORT int CheckDateTimeIsCorrect__FR5SYS_T ();
IMPORT int CheckDayIsCorrect__FUsUcUc ();
IMPORT int CheckFpgaSupport__FUl ();
IMPORT int CheckVoltageUniteSupport__FUl ();
IMPORT int ClearAlarmLog__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int ClearEventLog__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int ClearFlashLed__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int Clear__5CFilePCc ();
IMPORT int CloseBus ();
IMPORT int CloseWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int Close__5CFile ();
IMPORT int ClrLed__12CFunctionLedP10VWAS_CMD_SUl ();
IMPORT int CpLDDogClose ();
IMPORT int CpLDDogOpen ();
IMPORT int CreateBoard__3CNeUcUs ();
IMPORT int CreateMailBox__13CAppInterfaceUsUlUsiUli ();
IMPORT int CtrlBuzzer__10CAlarmInfoRC13st_Alarm_InfoUc ();
IMPORT int CtrlLcdAlarm__10CAlarmInfoUc ();
IMPORT int DCACHE_CTRL;
IMPORT int DW2BY ();
IMPORT int DW2W ();
IMPORT int DebugOut ();
IMPORT int DecreaseNode__10CTcpSocketi ();
IMPORT int DelFunction__6CBoardUs ();
IMPORT int DeleteMailBox__13CAppInterfaceUs ();
IMPORT int DeleteMessages__7CModuleUs ();
IMPORT int DeleteSoft__12CSoftUpGradeP10VWAS_CMD_SUl ();
IMPORT int Delete__11CMailBoxMapRCUs ();
IMPORT int Disable_mac_address ();
IMPORT int Dispatch__18CProtocolInterfaceR8CPackage ();
IMPORT int Dispatch__C13CAppInterfaceR9S_MESSAGE ();
IMPORT int Display485PingResult ();
IMPORT int Display485TestResult ();
IMPORT int Enable_mac_address ();
IMPORT int EnumWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int EventRspCmdToNs__FP10VWAS_CMD_SUlUl ();
IMPORT int EventSignSourceChange__10CAlarmProcUcUc ();
IMPORT int EventSystemClockChange__10CAlarmProc ();
IMPORT int FileSysTest ();
IMPORT int FillAlarmInfo__10CAlarmInfoR13st_Alarm_InfoP12ALARM_REPORTUc ();
IMPORT int FillEventInfo__10CAlarmInfoR13st_Event_InfoP12EVENT_REPORTUc ();
IMPORT int FindFunction__6CBoardUs ();
IMPORT int FlashPageRTest ();
IMPORT int FlashPageWTest ();
IMPORT int FlashReadTest ();
IMPORT int FlashWriteTest ();
IMPORT int FreeBlock__11CMemoryPoolPv ();
IMPORT int FreeCross__6CCrossUcUcPUcUc ();
IMPORT int FreeInputChannel__6CCrossUc ();
IMPORT int FreeListMemory__12CSoftUpGrade ();
IMPORT int FreeMessage__13CAppInterfaceP9S_MESSAGE ();
IMPORT int FreeOutputChannel__6CCrossPUcUc ();
IMPORT int FreeTimerID__12CTimerIDPoolUl ();
IMPORT int FreezeChannel__8CChannelP10VWAS_CMD_SUl ();
IMPORT int Gbase__9streambuf ();
IMPORT int GenerateHwnd__4CWnd ();
IMPORT int GetAlarmAutoReport__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int GetAlarmState__10CAlarmInfoUcUc ();
IMPORT int GetAlarm__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int GetAllFileRecord__5CFilePUc ();
IMPORT int GetAllMailBoxes__C11CMailBoxMap ();
IMPORT int GetAllModules__14CModuleManager ();
IMPORT int GetAllRecordCount__5CFileRUlT1 ();
IMPORT int GetBoardID__C11CSocketNode ();
IMPORT int GetBoardID__C9CLinkNode ();
IMPORT int GetBoardSet__C12C485NodePoolRUcPUc ();
IMPORT int GetBoardType__C11CSocketNode ();
IMPORT int GetBoardType__C9CLinkNode ();
IMPORT int GetBoardslotNo__9CFunction ();
IMPORT int GetBuzzer__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetChannelOffset__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetColorKey__9CColorKeyP10VWAS_CMD_SUl ();
IMPORT int GetColorKiller__8CChannelP10VWAS_CMD_SUl ();
IMPORT int GetCross__6CCrossP10VWAS_CMD_SUl ();
IMPORT int GetCurRecNo__5CFileRUl ();
IMPORT int GetCutArea__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetCutWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int GetDataAddress__C12CCtrlPackageRPUc ();
IMPORT int GetDataAddress__C12CDataPackageRPUc ();
IMPORT int GetDataAddress__C8CPackageRPUc ();
IMPORT int GetDataLength__C12CCtrlPackageRUs ();
IMPORT int GetDataLength__C12CDataPackageRUs ();
IMPORT int GetDataLength__C20CRebootSystemMessage ();
IMPORT int GetDataLength__C21COfflineSystemMessage ();
IMPORT int GetDataLength__C21CStandbySystemMessage ();
IMPORT int GetDataLength__C21CStartupSystemMessage ();
IMPORT int GetDataLength__C8CPackageRUs ();
IMPORT int GetDateTime__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetDateTime__C10CAlarmFilePUc ();
IMPORT int GetDateTime__C10CEventFilePUc ();
IMPORT int GetDateTime__C5CFilePUc ();
IMPORT int GetDestinationBD__C12CCtrlPackageRUc ();
IMPORT int GetDestinationBD__C12CDataPackageRUc ();
IMPORT int GetDestinationBD__C8CPackageRUc ();
IMPORT int GetDestinationMailBox__C12CDataPackageRUs ();
IMPORT int GetDestinationMailBox__C8CPackageRUs ();
IMPORT int GetDeviceType__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetDumbTimes__11CSocketPoollRUc ();
IMPORT int GetDumbTimes__12C485NodePoolUcRUc ();
IMPORT int GetDumbTimes__C11CSocketNode ();
IMPORT int GetDumbTimes__C9CLinkNode ();
IMPORT int GetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetErrorTimes__11CSocketPoollRUc ();
IMPORT int GetErrorTimes__12C485NodePoolUcRUc ();
IMPORT int GetErrorTimes__C11CSocketNode ();
IMPORT int GetErrorTimes__C9CLinkNode ();
IMPORT int GetEventAutoReport__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int GetEvent__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int GetEvent__C11CMailBoxMapUsRUl ();
IMPORT int GetFanStatus__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetFileCurSize__5CFile ();
IMPORT int GetFileNo__12CSoftUpGradeUcUcUcRUc ();
IMPORT int GetFileSize__5CFile ();
IMPORT int GetGatherChannelStat__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetGatherOffset__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetGatherSignFormat__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetHardVer__12CFunctionVerP10VWAS_CMD_SUl ();
IMPORT int GetHeadPointer__C8CPackage ();
IMPORT int GetIPAddress__C11CSocketNode ();
IMPORT int GetIP__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int GetInSlotStatus__15CFunctionInSlotP10VWAS_CMD_SUl ();
IMPORT int GetInfo__C11CMemoryPoolRUcRUlT2 ();
IMPORT int GetInputChannelByDataBoardInfo__6CCrossUcUcRUcT3 ();
IMPORT int GetInslotProcBdNum__3CNe ();
IMPORT int GetInstance__10CProcAlarm ();
IMPORT int GetInstance__11COperAndCfg ();
IMPORT int GetInstance__12CSoftUpGrade ();
IMPORT int GetInstance__13CCfgTcpSocket ();
IMPORT int GetInstance__14CSoftTcpSocket ();
IMPORT int GetInstance__15CAlarmTcpSocket ();
IMPORT int GetInstance__15CDebugTcpSocket ();
IMPORT int GetLocalBoardID__13CAppInterface ();
IMPORT int GetLocalBoardType__13CAppInterface ();
IMPORT int GetLogFileLength__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetMailBox__C7CModule ();
IMPORT int GetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl ();
IMPORT int GetMaxSocket__C11CSocketPool ();
IMPORT int GetMessageID__C20CRebootSystemMessage ();
IMPORT int GetMessageID__C21COfflineSystemMessage ();
IMPORT int GetMessageID__C21CStandbySystemMessage ();
IMPORT int GetMessageID__C21CStartupSystemMessage ();
IMPORT int GetMessageNumber__13CAppInterfaceUs ();
IMPORT int GetMessageSet__C7CModule ();
IMPORT int GetMilliseconds__6CTimer ();
IMPORT int GetModuleID__C7CModule ();
IMPORT int GetModule__14CModuleManagerUs ();
IMPORT int GetMsgPara__10CAlarmInfoPUcR10VWAS_CMD_SRUl ();
IMPORT int GetMsgPara__11COperAndCfgPUcR10VWAS_CMD_SRUl ();
IMPORT int GetMsgQID__C11CMailBoxMapUsRP5msg_q ();
IMPORT int GetNetStatus__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int GetOutputChannelBySignBoardInfo__6CCrossUcUcUcRUcT4 ();
IMPORT int GetPackageLength__C12CCtrlPackageRUs ();
IMPORT int GetPackageLength__C12CDataPackageRUs ();
IMPORT int GetPackageLength__C8CPackageRUs ();
IMPORT int GetPortInfo__17CFunctionPortInfoP10VWAS_CMD_SUl ();
IMPORT int GetPowerStatus__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetPrivilege__C12CDataPackageRUc ();
IMPORT int GetPrivilege__C8CPackageRUc ();
IMPORT int GetProcBdInfoByWallUnitNo__4CWndP10VWAS_CMD_SUl ();
IMPORT int GetProtocalVer__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetQueryResult__5CFilePUc ();
IMPORT int GetQuerySize__5CFileR5SYS_TT1RUlT3 ();
IMPORT int GetRcvCtrlPackages__C15CPackageCounter ();
IMPORT int GetRcvDataPackages__C15CPackageCounter ();
IMPORT int GetRcvNormalPackages__C15CPackageCounter ();
IMPORT int GetRecNum__5CFileRUl ();
IMPORT int GetReceiveOKTimes__C15CPackageCounter ();
IMPORT int GetReceiveTimes__C15CPackageCounter ();
IMPORT int GetRtc ();
IMPORT int GetSendCtrlPackages__C15CPackageCounter ();
IMPORT int GetSendDataPackages__C15CPackageCounter ();
IMPORT int GetSendOKTimes__C15CPackageCounter ();
IMPORT int GetSendTimes__C15CPackageCounter ();
IMPORT int GetSequenceNumber__11CSocketNode ();
IMPORT int GetSequenceNumber__11CSocketPoolRClRUs ();
IMPORT int GetSequenceNumber__12C485NodePoolUcRUs ();
IMPORT int GetSequenceNumber__9CLinkNode ();
IMPORT int GetSequenceNumber__C8CPackageRUl ();
IMPORT int GetSi5326Reg ();
IMPORT int GetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int GetSlotNumber__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetSocketSet__C11CSocketPoolRUcPl ();
IMPORT int GetSocket__C11CSocketNode ();
IMPORT int GetSoftFromList__12CSoftUpGrade ();
IMPORT int GetSoftPara__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetSoftStatus__12CFunctionVerP10VWAS_CMD_SUl ();
IMPORT int GetSoftVer__12CFunctionVerP10VWAS_CMD_SUl ();
IMPORT int GetSourceBD__C12CCtrlPackageRUc ();
IMPORT int GetSourceBD__C12CDataPackageRUc ();
IMPORT int GetSourceBD__C8CPackageRUc ();
IMPORT int GetSourceMailBox__C12CDataPackageRUs ();
IMPORT int GetSourceMailBox__C8CPackageRUs ();
IMPORT int GetStatus__C7CModule ();
IMPORT int GetSteps__6CTimerUc ();
IMPORT int GetSubMessageID__C14CSystemMessage ();
IMPORT int GetSubMessageID__C20CRebootSystemMessage ();
IMPORT int GetSubMessageID__C21CStandbySystemMessage ();
IMPORT int GetSubType__C12CCtrlPackageRUc ();
IMPORT int GetSubType__C8CPackageRUc ();
IMPORT int GetSysInitInfo__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int GetSysSync__8CChannelP10VWAS_CMD_SUl ();
IMPORT int GetTaskID__6CTimer ();
IMPORT int GetTaskID__C11CMailBoxMapUsRi ();
IMPORT int GetTempTh__13CFunctionTempP10VWAS_CMD_SUl ();
IMPORT int GetTemp__13CFunctionTempP10VWAS_CMD_SUl ();
IMPORT int GetTime__12CSoftUpGradeRUl ();
IMPORT int GetTimerID__6CTimer ();
IMPORT int GetTimers__13CTimerManager ();
IMPORT int GetType__C12CCtrlPackageRUc ();
IMPORT int GetType__C12CDataPackageRUc ();
IMPORT int GetType__C8CPackageRUc ();
IMPORT int GetVersion__C12CCtrlPackageRUc ();
IMPORT int GetVersion__C12CDataPackageRUc ();
IMPORT int GetVersion__C8CPackageRUc ();
IMPORT int GetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl ();
IMPORT int GetVoltageValue__16CFunctionVoltageP10VWAS_CMD_SUl ();
IMPORT int GetVsSync__8CChannelP10VWAS_CMD_SUl ();
IMPORT int GetWallUnitNoByCoordinate__4CWndRC11st_PositionRUcP18st_Sign_Board_Info ();
IMPORT int GetWhiteBalance__8CChannelP10VWAS_CMD_SUl ();
IMPORT int GetWindowAdj__8CDesktopP10VWAS_CMD_SUl ();
IMPORT int GetWndSignChannel__4CWndRCUcPC18st_Sign_Board_InfoPUc ();
IMPORT int I2cClk ();
IMPORT int I2cClkCycles ();
IMPORT int I2cCpldReset ();
IMPORT int I2cData ();
IMPORT int I2cDeviceBusy ();
IMPORT int I2cInit ();
IMPORT int I2cRead ();
IMPORT int I2cRead1014 ();
IMPORT int I2cReadBit ();
IMPORT int I2cReadByte ();
IMPORT int I2cReadCpld ();
IMPORT int I2cReadSeq ();
IMPORT int I2cStop ();
IMPORT int I2cWrite ();
IMPORT int I2cWriteBit ();
IMPORT int I2cWriteByte ();
IMPORT int I2cWritePage ();
IMPORT int IfBoardInstall__3CNeUc ();
IMPORT int IncreaseNode__10CTcpSocketi ();
IMPORT int InitFirstRecord__5CFile ();
IMPORT int InitFunction__10CMainBoard ();
IMPORT int InitFunction__6CBoard ();
IMPORT int InitLcd__10CMainBoard ();
IMPORT int InitSi5326 ();
IMPORT int InitSocket__9CListener ();
IMPORT int Init__11COperAndCfg ();
IMPORT int Init__12CSoftUpGrade ();
IMPORT int Insert__11CMailBoxMapUsUlUsiUli ();
IMPORT int Instance__10C485Client ();
IMPORT int Instance__11CEthnClient ();
IMPORT int Instance__11CMailBoxMap ();
IMPORT int Instance__11CSocketPool ();
IMPORT int Instance__12C485NodePool ();
IMPORT int Instance__12CTimerIDPool ();
IMPORT int Instance__13CAppInterface ();
IMPORT int Instance__13CTimerManager ();
IMPORT int Instance__14CModuleManager ();
IMPORT int Instance__18CProtocolInterface ();
IMPORT int Instance__9CListener ();
IMPORT int IsBoardExist__C12C485NodePoolUc ();
IMPORT int IsBoardOnline__10C485ClientUc ();
IMPORT int IsBoardOnline__11CEthnClientUc ();
IMPORT int IsBoardOnline__9CProtocolUc ();
IMPORT int IsTimeOut__12CSoftUpGrade ();
IMPORT int KeepAlive__10COperationP10VWAS_CMD_SUl ();
IMPORT int KillTimer__13CTimerManagerUl ();
IMPORT int LedAlarmStateChg ();
IMPORT int LedDrvInit ();
IMPORT int LedRunStateChg ();
IMPORT int LedStateChg ();
IMPORT int ListLastMsg ();
IMPORT int LoadFpga_ALTERA ();
IMPORT int LoadFpga_LATTICE ();
IMPORT int LoadModule__14CModuleManagerUs ();
IMPORT int LoadModule__7CModule ();
IMPORT int MAX_FAN_COUNT ();
IMPORT int MAX_POWER_COUNT ();
IMPORT int MC_AlarmReport ();
IMPORT int MC_EventReport ();
IMPORT int MailBoxEventHandler__14CModuleManager ();
IMPORT int MainCtrlMsgPrintf ();
IMPORT int MainCtrlTace ();
IMPORT int ModuleChecker__14CModuleManager ();
IMPORT int ModuleLoaded__14CModuleManagerUs ();
IMPORT int ModuleLoaded__7CModule ();
IMPORT int Nbase__9streambuf ();
IMPORT int OfflineAll__Fv ();
IMPORT int OfflineNotify__9CProtocolUc ();
IMPORT int OnlineAll__Fv ();
IMPORT int OpenBus ();
IMPORT int OpenWindow__4CWndP10VWAS_CMD_SUlUcUl ();
IMPORT int Open__5CFilePCcT1 ();
IMPORT int OperRspCmdToNs__FP10VWAS_CMD_SUlUl ();
IMPORT int OperSendCmdToBsWaitReturn__FUcP10VWAS_CMD_SUlUlT1 ();
IMPORT int OperSendCmdToBs__FUcP10VWAS_CMD_SUlUl ();
IMPORT int PF_AllocateMessage ();
IMPORT int PF_CreateMailBox ();
IMPORT int PF_DeleteMailBox ();
IMPORT int PF_FreeMessage ();
IMPORT int PF_GetLocalBoardID ();
IMPORT int PF_GetLocalBoardType ();
IMPORT int PF_GetMessageNumber ();
IMPORT int PF_KillTimer ();
IMPORT int PF_LoadModule ();
IMPORT int PF_ModuleLoaded ();
IMPORT int PF_Reboot ();
IMPORT int PF_ReceiveMessage ();
IMPORT int PF_ReceiveUrgentFrame ();
IMPORT int PF_RegisterModule ();
IMPORT int PF_RegisterSystemMessage ();
IMPORT int PF_SendMessage ();
IMPORT int PF_SetTimer ();
IMPORT int PF_Standby ();
IMPORT int PF_UnloadModule ();
IMPORT int PF_UnregisterModule ();
IMPORT int PF_UnregisterSystemMessage ();
IMPORT int PinAClk ();
IMPORT int PinACs ();
IMPORT int PinADo ();
IMPORT int Ping ();
IMPORT int PostSend__12CCtrlPackage ();
IMPORT int PostSend__12CDataPackage ();
IMPORT int PostSend__8CPackage ();
IMPORT int Proc15Timer__12CSoftUpGrade ();
IMPORT int ProcAlarmBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl ();
IMPORT int ProcAlarmNsCmd__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int ProcAlarm__10CAlarmInfoRC13st_Alarm_Info ();
IMPORT int ProcAlarm__10CProcAlarm ();
IMPORT int ProcAlarm__3CNe ();
IMPORT int ProcBdOffline__3CNeUcUs ();
IMPORT int ProcBdOnline__3CNeUcUs ();
IMPORT int ProcBdSoftAlarm__10CProcAlarm ();
IMPORT int ProcBdTempAlarm__10CProcAlarm ();
IMPORT int ProcBdVoltageAlarm__10CProcAlarm ();
IMPORT int ProcBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl ();
IMPORT int ProcBsCmd__10CDataBoardP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__10COperationP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__10CSignBoardP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__11CCrossBoardP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__11COperAndCfgUcP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__12CFunctionLedP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__12CFunctionVerP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__12CHDDataBoardP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__12CSDDataBoardP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__13CFunctionTempP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__14C2800DataBoardP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__15CFunctionInSlotP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__16CFunctionRestartP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__16CFunctionVoltageP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__17CFunctionPortInfoP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__20CFunctionManufactureP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__3CNeUcP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__4CWndP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__5CRootP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__6CBoardP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__6CCrossP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__8CChannelP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__8CDesktopP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__9CColorKeyP10VWAS_CMD_SUl ();
IMPORT int ProcBsCmd__9CFunctionP10VWAS_CMD_SUl ();
IMPORT int ProcCpuUsage__10CProcAlarm ();
IMPORT int ProcEnvTmp__10CProcAlarm ();
IMPORT int ProcEventBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl ();
IMPORT int ProcEventNsCmd__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int ProcEvent__10CAlarmInfoR13st_Event_Info ();
IMPORT int ProcFpgaStatus__10CProcAlarm ();
IMPORT int ProcNsCmd__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__10CDataBoardP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__10COperationP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__10CSignBoardP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__11CBackGroundP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__11CCrossBoardP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__11COperAndCfgP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__12CFunctionLedP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__12CFunctionVerP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__12CHDDataBoardP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__12CSDDataBoardP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__12CSoftUpGradeP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__13CFunctionTempP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__14C2800DataBoardP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__15CFunctionInSlotP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__16CFunctionRestartP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__16CFunctionVoltageP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__17CFunctionPortInfoP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__20CFunctionManufactureP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__3CNeP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__4CWndP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__5CRootP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__6CBoardP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__6CCrossP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__8CChannelP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__8CDesktopP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__9CColorKeyP10VWAS_CMD_SUl ();
IMPORT int ProcNsCmd__9CFunctionP10VWAS_CMD_SUl ();
IMPORT int ProcProtocalVer1__10CAlarmInfoPUc ();
IMPORT int ProcProtocalVer1__11COperAndCfgPUc ();
IMPORT int ProcProtocalVer1__12CSoftUpGradePUc ();
IMPORT int ProcProtocalVer2__10CAlarmInfoPUc ();
IMPORT int ProcProtocalVer2__11COperAndCfgPUc ();
IMPORT int ProcProtocalVer2__12CSoftUpGradePUc ();
IMPORT int ProcTimer__10CAlarmInfo ();
IMPORT int ProcTimer__10CMainBoard ();
IMPORT int ProcTimer__10COperation ();
IMPORT int ProcTimer__10CTcpSocket ();
IMPORT int ProcTimer__11COperAndCfg ();
IMPORT int ProcTimer__12CSoftUpGrade ();
IMPORT int ProcTimer__3CNe ();
IMPORT int ProcTimer__6CBoard ();
IMPORT int ReadFirstRecord__5CFileR19st_File_Config_Info ();
IMPORT int ReadLM73 ();
IMPORT int Read__5CFileUlUlPUc ();
IMPORT int Reboot__14CModuleManagerUc ();
IMPORT int ReceiveAction__12CCtrlPackageP9CProtocoll ();
IMPORT int ReceiveAction__12CDataPackageP9CProtocoll ();
IMPORT int ReceiveAction__14COnLinePackageP9CProtocoll ();
IMPORT int ReceiveAction__17CKeepAlivePackageP9CProtocoll ();
IMPORT int ReceiveAction__8CPackageP9CProtocoll ();
IMPORT int ReceiveBsBlockMsg__11COperAndCfg ();
IMPORT int ReceiveBsMsg__10CAlarmInfo ();
IMPORT int ReceiveBsMsg__11COperAndCfg ();
IMPORT int ReceiveFrameCallBack__10C485ClientUlPUc ();
IMPORT int ReceiveMessage__13CAppInterfaceUsP9S_MESSAGEi ();
IMPORT int ReceiveNsCancelMsg__12CSoftUpGrade ();
IMPORT int ReceiveNsMsg__10CAlarmInfo ();
IMPORT int ReceiveNsMsg__11COperAndCfg ();
IMPORT int ReceiveNsMsg__12CSoftUpGrade ();
IMPORT int ReceivePackage__11CEthnClientRCl ();
IMPORT int RegisterModule__14CModuleManagerUsUsPFUl_lUlT3Ul ();
IMPORT int RegisterNotify__9CProtocolUcPFUlUc_v ();
IMPORT int RegisterSystemMessage__14CModuleManagerUsUs ();
IMPORT int Remove485Node__12C485NodePoolUc ();
IMPORT int RemoveSocketNode__11CSocketPoolRCl ();
IMPORT int RemoveWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int ReportWriteFlashProgress__12CSoftUpGradePUlT1 ();
IMPORT int ResetDumbTimes__11CSocketNode ();
IMPORT int ResetDumbTimes__9CLinkNode ();
IMPORT int ResetErrorTimes__11CSocketNode ();
IMPORT int ResetErrorTimes__11CSocketPoolRCl ();
IMPORT int ResetErrorTimes__12C485NodePoolUc ();
IMPORT int ResetErrorTimes__9CLinkNode ();
IMPORT int ResetFpga_ALTERA ();
IMPORT int ResetFpga_LATTICE ();
IMPORT int ResetKeepAliveTimer__10C485Clientl ();
IMPORT int ResetKeepAliveTimer__11CEthnClientl ();
IMPORT int ResetKeepAliveTimer__11CSocketPoolRCl ();
IMPORT int ResetKeepAliveTimer__12C485NodePoolUc ();
IMPORT int ResetKeepAliveTimer__9CProtocoll ();
IMPORT int ResetKeepAlive__10C485Client ();
IMPORT int ResetWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int Reset__6CTimer ();
IMPORT int RestartBoard__16CFunctionRestartP10VWAS_CMD_SUl ();
IMPORT int ResumeInitInfo__10CSignBoardUc ();
IMPORT int ResumeInitInfo__6CBoardUc ();
IMPORT int ResumeWindow__4CWndUc ();
IMPORT int RspAutoWhiteBalance__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspClrLed__12CFunctionLedP10VWAS_CMD_SUl ();
IMPORT int RspCmdToNs__10CTcpSocketP10VWAS_CMD_SUlUl ();
IMPORT int RspErrToNs__11CBackGroundUsP10VWAS_CMD_SUl ();
IMPORT int RspErrToNs__4CWndUsP10VWAS_CMD_SUl ();
IMPORT int RspFreezeChannel__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspGetChannelOffset__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetColorKey__9CColorKeyP10VWAS_CMD_SUl ();
IMPORT int RspGetColorKiller__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspGetCutArea__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetGatherChannelStat__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetGatherOffset__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetGatherSignFormat__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetIP__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int RspGetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl ();
IMPORT int RspGetNetStatus__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int RspGetPortInfo__17CFunctionPortInfoP10VWAS_CMD_SUl ();
IMPORT int RspGetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspGetSysSync__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspGetTempTh__13CFunctionTempP10VWAS_CMD_SUl ();
IMPORT int RspGetTemp__13CFunctionTempP10VWAS_CMD_SUl ();
IMPORT int RspGetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl ();
IMPORT int RspGetWhiteBalance__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspGetWindowAdj__8CDesktopP10VWAS_CMD_SUl ();
IMPORT int RspHardVer__12CFunctionVerP10VWAS_CMD_SUl ();
IMPORT int RspRestartBoard__16CFunctionRestartP10VWAS_CMD_SUl ();
IMPORT int RspSetChannelOffset__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspSetChannelsOff__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspSetChannelsOn__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspSetColorKey__9CColorKeyP10VWAS_CMD_SUl ();
IMPORT int RspSetColorKiller__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspSetCutArea__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspSetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspSetGatherOffset__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspSetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspSetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspSetIP__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int RspSetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl ();
IMPORT int RspSetNetStatus__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int RspSetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int RspSetSysSync__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspSetTempTh__13CFunctionTempP10VWAS_CMD_SUl ();
IMPORT int RspSetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl ();
IMPORT int RspSetWhiteBalance__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspSetWindowAdj__8CDesktopP10VWAS_CMD_SUl ();
IMPORT int RspSoftStatus__12CFunctionVerP10VWAS_CMD_SUl ();
IMPORT int RspSoftVer__12CFunctionVerP10VWAS_CMD_SUl ();
IMPORT int RspTopWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int RspViewLoopOff__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspViewLoopOn__8CChannelP10VWAS_CMD_SUl ();
IMPORT int RspVoltageValue__16CFunctionVoltageP10VWAS_CMD_SUl ();
IMPORT int SendCmdToBsWaitReturn__11COperAndCfgUcPP10VWAS_CMD_SUlUlUlUlUlP10VWAS_CMD_S ();
IMPORT int SendCmdToBs__11COperAndCfgUcPP10VWAS_CMD_SUlUlUlUlUl ();
IMPORT int SendMessage__13CAppInterfaceP9S_MESSAGE ();
IMPORT int SendMessage__18CProtocolInterfaceR9S_MESSAGE ();
IMPORT int SendMsg2Lcd ();
IMPORT int SendMsgToMailBox__10CTcpSocketPUcUliUl ();
IMPORT int SendMsgToMailBox__15CDebugTcpSocketPUcUliUl ();
IMPORT int SendPackage__9CProtocolR8CPackage ();
IMPORT int SendStartupMessageToServer__14CModuleManagerUc ();
IMPORT int Send__10C485ClientP8CPackage ();
IMPORT int Send__11CEthnClientP8CPackage ();
IMPORT int SerializePackage__9CProtocolPUcRP8CPackage ();
IMPORT int SetAlarmAutoReport__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int SetBackGround__11CBackGroundP10VWAS_CMD_SUl ();
IMPORT int SetBoardID__11CSocketNodeUc ();
IMPORT int SetBoardID__11CSocketPoollUc ();
IMPORT int SetBoardID__9CLinkNodeUc ();
IMPORT int SetBoardInfo__10C485ClientlUcUc ();
IMPORT int SetBoardInfo__11CEthnClientlUcUc ();
IMPORT int SetBoardInfo__9CProtocollUcUc ();
IMPORT int SetBoardType__11CSocketNodeUc ();
IMPORT int SetBoardType__11CSocketPoollUc ();
IMPORT int SetBoardType__12C485NodePoolUcUc ();
IMPORT int SetBoardType__9CLinkNodeUc ();
IMPORT int SetBuzzer__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int SetChannelOffset__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int SetChannelsOff__8CChannelP10VWAS_CMD_SUl ();
IMPORT int SetChannelsOn__8CChannelP10VWAS_CMD_SUl ();
IMPORT int SetColorKey__9CColorKeyP10VWAS_CMD_SUl ();
IMPORT int SetColorKiller__8CChannelP10VWAS_CMD_SUl ();
IMPORT int SetCross__6CCrossUcUcPUcUc ();
IMPORT int SetCutArea__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int SetCutWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int SetDateTime__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int SetDebugSwitch ();
IMPORT int SetDestTop__11CBackGroundP10VWAS_CMD_SUl ();
IMPORT int SetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int SetEventAutoReport__10CAlarmInfoP10VWAS_CMD_SUl ();
IMPORT int SetGatherOffset__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int SetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int SetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int SetHeadPointer__8CPackagePCUc ();
IMPORT int SetIPAddress__11CSocketNodeUl ();
IMPORT int SetIP__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int SetInfoDisplay__11CBackGroundP10VWAS_CMD_SUl ();
IMPORT int SetMainCtrlOnLine__3CNe ();
IMPORT int SetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl ();
IMPORT int SetNetStatus__11CFunctionIPP10VWAS_CMD_SUl ();
IMPORT int SetRcvCtrlPackages__15CPackageCounterUl ();
IMPORT int SetRcvDataPackages__15CPackageCounterUl ();
IMPORT int SetRcvNormalPackages__15CPackageCounterUl ();
IMPORT int SetReceiveOKTimes__15CPackageCounterUl ();
IMPORT int SetReceiveTimes__15CPackageCounterUl ();
IMPORT int SetRtc ();
IMPORT int SetSendCtrlPackages__15CPackageCounterUl ();
IMPORT int SetSendDataPackages__15CPackageCounterUl ();
IMPORT int SetSendOKTimes__15CPackageCounterUl ();
IMPORT int SetSendTimes__15CPackageCounterUl ();
IMPORT int SetSequenceNumber__12CCtrlPackageUs ();
IMPORT int SetSequenceNumber__12CDataPackageUs ();
IMPORT int SetSequenceNumber__8CPackageUs ();
IMPORT int SetSi5326Reg ();
IMPORT int SetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl ();
IMPORT int SetSocketOption__9CListenerl ();
IMPORT int SetSocket__11CSocketNodel ();
IMPORT int SetSoftPara__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int SetSysInitInfo__10CMainBoardP10VWAS_CMD_SUl ();
IMPORT int SetSysSync__8CChannelP10VWAS_CMD_SUl ();
IMPORT int SetTempTh__13CFunctionTempP10VWAS_CMD_SUl ();
IMPORT int SetTestMap__11CBackGroundP10VWAS_CMD_SUl ();
IMPORT int SetTimer__13CTimerManagerP6CTimer ();
IMPORT int SetTimer__13CTimerManagerRPt12PF_list_node1ZP6CTimer ();
IMPORT int SetTimer__13CTimerManagerlUlUcUl ();
IMPORT int SetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl ();
IMPORT int SetVsSync__8CChannelP10VWAS_CMD_SUl ();
IMPORT int SetWhiteBalance__8CChannelP10VWAS_CMD_SUl ();
IMPORT int SetWindowAdj__8CDesktopP10VWAS_CMD_SUl ();
IMPORT int ShowWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int Socket2BoardID__11CSocketPoollRUc ();
IMPORT int SoftRspCmdToNs__FP10VWAS_CMD_SUlUl ();
IMPORT int SoftwareIsCorrect__12CSoftUpGrade ();
IMPORT int Spi0Test ();
IMPORT int SpiInit ();
IMPORT int SpiRead ();
IMPORT int SpiReadBit ();
IMPORT int SpiReadByte ();
IMPORT int SpiWrite ();
IMPORT int SpiWriteBit ();
IMPORT int SpiWriteByte ();
IMPORT int Standby__14CModuleManagerUc ();
IMPORT int StartAccept__10CTcpSocket ();
IMPORT int StartRecv__10CTcpSocketUl ();
IMPORT int Startup__14CModuleManagerUcUc ();
IMPORT int SystemMessage__14CModuleManagerR14CSystemMessage ();
IMPORT int SystemMessage__7CModuleR14CSystemMessage ();
IMPORT int TASKID_ALARMEVENT;
IMPORT int TASKID_CFGOPER;
IMPORT int TASKID_UPGRADE;
IMPORT int TAlarmEvent_ReceiveTask__10CAlarmInfoPv ();
IMPORT int TCFGOPER_ReceiveBsTaskBlock__11COperAndCfgPv ();
IMPORT int TCFGOPER_ReceiveTask__11COperAndCfgPv ();
IMPORT int TUpgrade_CancelTask__12CSoftUpGradePv ();
IMPORT int TUpgrade_ReceiveTask__12CSoftUpGradePv ();
IMPORT int TempTest ();
IMPORT int TestBoardInstalled__3CNe ();
IMPORT int TestBspTimer ();
IMPORT int TestCpld ();
IMPORT int TestLm73 ();
IMPORT int Tick__14CPeriodicTimer ();
IMPORT int Tick__6CTimer ();
IMPORT int TopWindow__4CWndP10VWAS_CMD_SUl ();
IMPORT int TransFileBegin__12CSoftUpGradeP10VWAS_CMD_SUl ();
IMPORT int TransFileEnd__12CSoftUpGradeP10VWAS_CMD_SUl ();
IMPORT int Uninstance__10C485Client ();
IMPORT int Uninstance__11CEthnClient ();
IMPORT int UnloadModule__14CModuleManagerUs ();
IMPORT int UnloadModule__7CModule ();
IMPORT int UnregisterModule__14CModuleManagerUs ();
IMPORT int UnregisterSystemMessage__14CModuleManagerUsUs ();
IMPORT int UpdateConfigureInfo__5CFileR19st_File_Config_Info ();
IMPORT int UrgencyJobAdd ();
IMPORT int UrgencyJobAlloc ();
IMPORT int UrgencyLibInit ();
IMPORT int UrgencyShow ();
IMPORT int UrgencyStart ();
IMPORT int UrgencyStop ();
IMPORT int UrgencyTask ();
IMPORT int VOS_AddExcHook ();
IMPORT int VOS_CloseSocket ();
IMPORT int VOS_ConnectClk ();
IMPORT int VOS_CreateBSem ();
IMPORT int VOS_CreateCSem ();
IMPORT int VOS_CreateMSem ();
IMPORT int VOS_CreateMsgQue ();
IMPORT int VOS_CreateTask ();
IMPORT int VOS_DelayTask ();
IMPORT int VOS_DeleteMsgQue ();
IMPORT int VOS_DeleteSem ();
IMPORT int VOS_DeleteTask ();
IMPORT int VOS_Display ();
IMPORT int VOS_GetBoardID ();
IMPORT int VOS_GetBoardType ();
IMPORT int VOS_GetErrno ();
IMPORT int VOS_GetMsgNum ();
IMPORT int VOS_GetPriority ();
IMPORT int VOS_GetSelfTaskID ();
IMPORT int VOS_GetSysClkRate ();
IMPORT int VOS_GetTick ();
IMPORT int VOS_GiveSem ();
IMPORT int VOS_InitVOS ();
IMPORT int VOS_ReceiveEvent ();
IMPORT int VOS_ReceiveMsg ();
IMPORT int VOS_ResumeTask ();
IMPORT int VOS_SendEvent ();
IMPORT int VOS_SendMsg ();
IMPORT int VOS_SetIOControl ();
IMPORT int VOS_SetPriority ();
IMPORT int VOS_SetSysClkRate ();
IMPORT int VOS_SuspendSelf ();
IMPORT int VOS_SuspendTask ();
IMPORT int VOS_TakeSem ();
IMPORT int ViewLoopOff__8CChannelP10VWAS_CMD_SUl ();
IMPORT int ViewLoopOn__8CChannelP10VWAS_CMD_SUl ();
IMPORT int W2BY ();
IMPORT int W2DW ();
IMPORT int WDCallBack__13CTimerManagerl ();
IMPORT int WndHandleIsExist__4CWndUl ();
IMPORT int WriteLM73 ();
IMPORT int WriteMessage__14CSystemMessagePUc ();
IMPORT int WriteMessage__21COfflineSystemMessagePUc ();
IMPORT int WriteMessage__21CStartupSystemMessagePUc ();
IMPORT int WriteSoftwareToFlash__12CSoftUpGrade ();
IMPORT int Write__5CFilePCUc ();
IMPORT int _$_10C485Client ();
IMPORT int _$_10CAlarmFile ();
IMPORT int _$_10CAlarmInfo ();
IMPORT int _$_10CAlarmProc ();
IMPORT int _$_10CDataBoard ();
IMPORT int _$_10CEventFile ();
IMPORT int _$_10CMainBoard ();
IMPORT int _$_10COperation ();
IMPORT int _$_10CProcAlarm ();
IMPORT int _$_10CSignBoard ();
IMPORT int _$_10CTcpSocket ();
IMPORT int _$_10bad_typeid ();
IMPORT int _$_11CBackGround ();
IMPORT int _$_11CCrossBoard ();
IMPORT int _$_11CEthnClient ();
IMPORT int _$_11CFunctionIP ();
IMPORT int _$_11CMailBoxMap ();
IMPORT int _$_11CMemoryPool ();
IMPORT int _$_11COperAndCfg ();
IMPORT int _$_11CSocketNode ();
IMPORT int _$_11CSocketPool ();
IMPORT int _$_12C485NodePool ();
IMPORT int _$_12CCtrlPackage ();
IMPORT int _$_12CDataPackage ();
IMPORT int _$_12CFunctionLed ();
IMPORT int _$_12CFunctionVer ();
IMPORT int _$_12CHDDataBoard ();
IMPORT int _$_12CSDDataBoard ();
IMPORT int _$_12CSoftUpGrade ();
IMPORT int _$_12CTimerIDPool ();
IMPORT int _$_12streammarker ();
IMPORT int _$_13CAppInterface ();
IMPORT int _$_13CFunctionTemp ();
IMPORT int _$_13CTimerManager ();
IMPORT int _$_13bad_exception ();
IMPORT int _$_14C2800DataBoard ();
IMPORT int _$_14CModuleManager ();
IMPORT int _$_14COnLinePackage ();
IMPORT int _$_14COperAttribute ();
IMPORT int _$_14CSystemMessage ();
IMPORT int _$_14__si_type_info ();
IMPORT int _$_15CDebugTcpSocket ();
IMPORT int _$_15CFunctionInSlot ();
IMPORT int _$_15CPackageCounter ();
IMPORT int _$_16CFunctionRestart ();
IMPORT int _$_16CFunctionVoltage ();
IMPORT int _$_16__user_type_info ();
IMPORT int _$_17CFunctionPortInfo ();
IMPORT int _$_17CKeepAlivePackage ();
IMPORT int _$_17__class_type_info ();
IMPORT int _$_18CProtocolInterface ();
IMPORT int _$_20CFunctionManufacture ();
IMPORT int _$_20CRebootSystemMessage ();
IMPORT int _$_21COfflineSystemMessage ();
IMPORT int _$_21CStandbySystemMessage ();
IMPORT int _$_21CStartupSystemMessage ();
IMPORT int _$_22_IO_istream_withassign ();
IMPORT int _$_22_IO_ostream_withassign ();
IMPORT int _$_3CNe ();
IMPORT int _$_3ios ();
IMPORT int _$_4CWnd ();
IMPORT int _$_5CFile ();
IMPORT int _$_5CRoot ();
IMPORT int _$_6CBoard ();
IMPORT int _$_6CCross ();
IMPORT int _$_6CTimer ();
IMPORT int _$_7CModule ();
IMPORT int _$_7filebuf ();
IMPORT int _$_7istream ();
IMPORT int _$_7ostream ();
IMPORT int _$_8CChannel ();
IMPORT int _$_8CDesktop ();
IMPORT int _$_8CPackage ();
IMPORT int _$_8bad_cast ();
IMPORT int _$_8iostream ();
IMPORT int _$_9CColorKey ();
IMPORT int _$_9CFunction ();
IMPORT int _$_9CLinkNode ();
IMPORT int _$_9CListener ();
IMPORT int _$_9CProtocol ();
IMPORT int _$_9bad_alloc ();
IMPORT int _$_9exception ();
IMPORT int _$_9streambuf ();
IMPORT int _$_9type_info ();
IMPORT int _$_Q2t24__default_alloc_template2b1i05_Lock ();
IMPORT int _10C485Client$m_spInstance;
IMPORT int _10CAlarmInfo$m_pAlarmFile;
IMPORT int _10CAlarmInfo$m_pEventFile;
IMPORT int _10CProcAlarm$m_pInstance;
IMPORT int _11CEthnClient$m_spInstance;
IMPORT int _11CMailBoxMap$m_spInstance;
IMPORT int _11COperAndCfg$m_pInstance;
IMPORT int _11CSocketPool$m_spInstance;
IMPORT int _12C485NodePool$m_spInstance;
IMPORT int _12CSoftUpGrade$m_pUpgrade;
IMPORT int _12CSoftUpGrade$m_slRspWriteFlashResult;
IMPORT int _12CTimerIDPool$m_pclaInstance;
IMPORT int _13CAppInterface$m_spInstance;
IMPORT int _13CCfgTcpSocket$m_pCfgTcpSocket;
IMPORT int _13CTimerManager$m_pclaInstance;
IMPORT int _14CModuleManager$m_spInstance;
IMPORT int _14CSoftTcpSocket$m_pSoftTcpSocket;
IMPORT int _15CAlarmTcpSocket$m_pAlarmTcpSocket;
IMPORT int _15CDebugTcpSocket$m_pDebugTcpSocket;
IMPORT int _18CProtocolInterface$m_spInstance;
IMPORT int _4CWnd$m_dwWndHwnd;
IMPORT int _7filebuf$openprot ();
IMPORT int _9CListener$m_spInstance;
IMPORT int _GLOBAL_$D$MAX_POWER_COUNT ();
IMPORT int _GLOBAL_$D$MC_AlarmReport ();
IMPORT int _GLOBAL_$D$_11CMailBoxMap$m_spInstance ();
IMPORT int _GLOBAL_$D$_11CSocketPool$m_spInstance ();
IMPORT int _GLOBAL_$D$_12C485NodePool$m_spInstance ();
IMPORT int _GLOBAL_$D$_12CSoftUpGrade$m_pUpgrade ();
IMPORT int _GLOBAL_$D$_4CWnd$m_dwWndHwnd ();
IMPORT int _GLOBAL_$D$_IO_stdin_ ();
IMPORT int _GLOBAL_$D$__11CMemoryPoolUlUlUc ();
IMPORT int _GLOBAL_$D$_t24__default_alloc_template2b1i0$_S_end_free ();
IMPORT int _GLOBAL_$D$_un_link__9streambuf ();
IMPORT int _GLOBAL_$D$g_AlarmInfo ();
IMPORT int _GLOBAL_$D$g_dwStartTimeSec ();
IMPORT int _GLOBAL_$I$MAX_POWER_COUNT ();
IMPORT int _GLOBAL_$I$MC_AlarmReport ();
IMPORT int _GLOBAL_$I$_11CMailBoxMap$m_spInstance ();
IMPORT int _GLOBAL_$I$_11CSocketPool$m_spInstance ();
IMPORT int _GLOBAL_$I$_12C485NodePool$m_spInstance ();
IMPORT int _GLOBAL_$I$_12CSoftUpGrade$m_pUpgrade ();
IMPORT int _GLOBAL_$I$_4CWnd$m_dwWndHwnd ();
IMPORT int _GLOBAL_$I$_IO_stdin_ ();
IMPORT int _GLOBAL_$I$__11CMemoryPoolUlUlUc ();
IMPORT int _GLOBAL_$I$_t24__default_alloc_template2b1i0$_S_end_free ();
IMPORT int _GLOBAL_$I$_un_link__9streambuf ();
IMPORT int _GLOBAL_$I$g_AlarmInfo ();
IMPORT int _GLOBAL_$I$g_CommVer1 ();
IMPORT int _GLOBAL_$I$g_dwStartTimeSec ();
IMPORT int _IO_adjust_column ();
IMPORT int _IO_cleanup ();
IMPORT int _IO_cleanup_registration_needed;
IMPORT int _IO_default_doallocate ();
IMPORT int _IO_default_finish ();
IMPORT int _IO_default_pbackfail ();
IMPORT int _IO_default_read ();
IMPORT int _IO_default_seek ();
IMPORT int _IO_default_seekoff ();
IMPORT int _IO_default_seekpos ();
IMPORT int _IO_default_setbuf ();
IMPORT int _IO_default_stat ();
IMPORT int _IO_default_sync ();
IMPORT int _IO_default_uflow ();
IMPORT int _IO_default_underflow ();
IMPORT int _IO_default_write ();
IMPORT int _IO_default_xsgetn ();
IMPORT int _IO_default_xsputn ();
IMPORT int _IO_do_write ();
IMPORT int _IO_doallocbuf ();
IMPORT int _IO_dtoa ();
IMPORT int _IO_file_attach ();
IMPORT int _IO_file_close ();
IMPORT int _IO_file_close_it ();
IMPORT int _IO_file_doallocate ();
IMPORT int _IO_file_finish ();
IMPORT int _IO_file_fopen ();
IMPORT int _IO_file_init ();
IMPORT int _IO_file_jumps;
IMPORT int _IO_file_overflow ();
IMPORT int _IO_file_read ();
IMPORT int _IO_file_seek ();
IMPORT int _IO_file_seekoff ();
IMPORT int _IO_file_setbuf ();
IMPORT int _IO_file_stat ();
IMPORT int _IO_file_sync ();
IMPORT int _IO_file_underflow ();
IMPORT int _IO_file_write ();
IMPORT int _IO_file_xsputn ();
IMPORT int _IO_flush_all ();
IMPORT int _IO_flush_all_linebuffered ();
IMPORT int _IO_free_backup_area ();
IMPORT int _IO_getc ();
IMPORT int _IO_getline ();
IMPORT int _IO_getline_info ();
IMPORT int _IO_init ();
IMPORT int _IO_init_marker ();
IMPORT int _IO_link_in ();
IMPORT int _IO_list_all;
IMPORT int _IO_marker_delta ();
IMPORT int _IO_marker_difference ();
IMPORT int _IO_outfloat ();
IMPORT int _IO_padn ();
IMPORT int _IO_peekc_locked ();
IMPORT int _IO_putc ();
IMPORT int _IO_remove_marker ();
IMPORT int _IO_seekmark ();
IMPORT int _IO_seekoff ();
IMPORT int _IO_seekpos ();
IMPORT int _IO_setb ();
IMPORT int _IO_sgetn ();
IMPORT int _IO_sputbackc ();
IMPORT int _IO_stderr_;
IMPORT int _IO_stdin_;
IMPORT int _IO_stdout_;
IMPORT int _IO_strtod ();
IMPORT int _IO_sungetc ();
IMPORT int _IO_switch_to_backup_area ();
IMPORT int _IO_switch_to_get_mode ();
IMPORT int _IO_switch_to_main_get_area ();
IMPORT int _IO_un_link ();
IMPORT int _IO_ungetc ();
IMPORT int _IO_unsave_markers ();
IMPORT int _IO_vfscanf ();
IMPORT int _Randseed;
IMPORT int _S_chunk_alloc__t24__default_alloc_template2b1i0UlRi ();
IMPORT int _S_freelist_index__t24__default_alloc_template2b1i0Ul ();
IMPORT int _S_oom_malloc__t23__malloc_alloc_template1i0Ul ();
IMPORT int _S_oom_realloc__t23__malloc_alloc_template1i0PvUl ();
IMPORT int _S_refill__t24__default_alloc_template2b1i0Ul ();
IMPORT int _S_round_up__t24__default_alloc_template2b1i0Ul ();
IMPORT int __10C485Client ();
IMPORT int __10CAlarmFilePcT1 ();
IMPORT int __10CAlarmInfo ();
IMPORT int __10CAlarmProc ();
IMPORT int __10CDataBoardUc ();
IMPORT int __10CEventFilePcT1 ();
IMPORT int __10CMainBoardUc ();
IMPORT int __10COperation ();
IMPORT int __10CProcAlarm ();
IMPORT int __10CSignBoardUc ();
IMPORT int __10CTcpSocketUlUl ();
IMPORT int __10bad_typeid ();
IMPORT int __11CBackGround ();
IMPORT int __11CCrossBoardUc ();
IMPORT int __11CEthnClient ();
IMPORT int __11CFunctionIP ();
IMPORT int __11CMailBoxMap ();
IMPORT int __11CMemoryPoolUlUlUc ();
IMPORT int __11COperAndCfg ();
IMPORT int __11CSocketNodelUlUcUc ();
IMPORT int __11CSocketPool ();
IMPORT int __12C485NodePool ();
IMPORT int __12CCtrlPackagePUc ();
IMPORT int __12CCtrlPackageR9S_MESSAGE ();
IMPORT int __12CCtrlPackageUcUcUsPUc ();
IMPORT int __12CDataPackagePUc ();
IMPORT int __12CDataPackageR9S_MESSAGE ();
IMPORT int __12CFunctionLed ();
IMPORT int __12CFunctionVer ();
IMPORT int __12CHDDataBoardUc ();
IMPORT int __12CSDDataBoardUc ();
IMPORT int __12CSoftUpGrade ();
IMPORT int __12CTimerIDPool ();
IMPORT int __12streammarkerP9streambuf ();
IMPORT int __13CAppInterface ();
IMPORT int __13CAppInterfaceRC13CAppInterface ();
IMPORT int __13CCfgTcpSocket ();
IMPORT int __13CFunctionTemp ();
IMPORT int __13CTimerManager ();
IMPORT int __13bad_exception ();
IMPORT int __14C2800DataBoardUc ();
IMPORT int __14CModuleManager ();
IMPORT int __14COnLinePackage ();
IMPORT int __14COnLinePackagePUc ();
IMPORT int __14COperAttribute ();
IMPORT int __14CPeriodicTimerUllUlUl ();
IMPORT int __14CRelativeTimerUllUlUl ();
IMPORT int __14CSoftTcpSocket ();
IMPORT int __14CSystemMessage ();
IMPORT int __14__si_type_infoPCcRC16__user_type_info ();
IMPORT int __14tagMailBoxNodeUsP5msg_qiUl ();
IMPORT int __15CAlarmTcpSocket ();
IMPORT int __15CDebugTcpSocket ();
IMPORT int __15CFunctionInSlot ();
IMPORT int __15CPackageCounter ();
IMPORT int __16CFunctionRestart ();
IMPORT int __16CFunctionVoltage ();
IMPORT int __16__user_type_infoPCc ();
IMPORT int __17CFunctionPortInfo ();
IMPORT int __17CKeepAlivePackagePUc ();
IMPORT int __17CKeepAlivePackageUcUcUsPUc ();
IMPORT int __17__class_type_infoPCcPCQ217__class_type_info9base_infoUl ();
IMPORT int __18CProtocolInterface ();
IMPORT int __20CFunctionManufacture ();
IMPORT int __20CRebootSystemMessageUc ();
IMPORT int __21COfflineSystemMessageUc ();
IMPORT int __21CStandbySystemMessageUs ();
IMPORT int __21CStartupSystemMessageUcUc ();
IMPORT int __3CNe ();
IMPORT int __3iosP9streambufP7ostream ();
IMPORT int __4CWnd ();
IMPORT int __5CFilePcT1UlUl ();
IMPORT int __5CRoot ();
IMPORT int __5CRootUc ();
IMPORT int __6CBoardUc ();
IMPORT int __6CCross ();
IMPORT int __6CTimerUllUlUl ();
IMPORT int __7CModuleUsUsPFUl_lUlT3UlUs ();
IMPORT int __7filebuf ();
IMPORT int __7filebufi ();
IMPORT int __7filebufiPci ();
IMPORT int __7istreami ();
IMPORT int __7istreamiP9streambufP7ostream ();
IMPORT int __7ostreami ();
IMPORT int __7ostreamiP9streambufP7ostream ();
IMPORT int __8CChannel ();
IMPORT int __8CDesktop ();
IMPORT int __8CPackagePUc ();
IMPORT int __8CPackageR9S_MESSAGE ();
IMPORT int __8bad_cast ();
IMPORT int __8iostreami ();
IMPORT int __8iostreamiP9streambufP7ostream ();
IMPORT int __9CColorKey ();
IMPORT int __9CFunction ();
IMPORT int __9CLinkNodeUcUc ();
IMPORT int __9CListener ();
IMPORT int __9CProtocol ();
IMPORT int __9exception ();
IMPORT int __9streambufi ();
IMPORT int __9type_infoPCc ();
IMPORT int __DIAB_rd_pk_db ();
IMPORT int __DIAB_rd_pk_fl ();
IMPORT int __DIAB_rd_pk_ld ();
IMPORT int __DIAB_rd_sw_db ();
IMPORT int __DIAB_rd_sw_fl ();
IMPORT int __DIAB_rd_sw_ld ();
IMPORT int __DIAB_wr_pk_db ();
IMPORT int __DIAB_wr_pk_fl ();
IMPORT int __DIAB_wr_pk_ld ();
IMPORT int __DIAB_wr_sw_db ();
IMPORT int __DIAB_wr_sw_fl ();
IMPORT int __DIAB_wr_sw_ld ();
IMPORT int __POL ();
IMPORT int __Q23ios4Init ();
IMPORT int __Q2t24__default_alloc_template2b1i05_Lock ();
IMPORT int ___x_diab_arm_div_o;
IMPORT int ___x_diab_comljmp_o;
IMPORT int ___x_diab_ff1_o;
IMPORT int ___x_diab_libg_o;
IMPORT int ___x_diab_rd_pk_db_o;
IMPORT int ___x_diab_rd_pk_fl_o;
IMPORT int ___x_diab_rd_pk_ld_o;
IMPORT int ___x_diab_rd_sw_db_o;
IMPORT int ___x_diab_rd_sw_fl_o;
IMPORT int ___x_diab_rd_sw_ld_o;
IMPORT int ___x_diab_rtahooks_o;
IMPORT int ___x_diab_sfpdcmp_o;
IMPORT int ___x_diab_sfpdcmpe_o;
IMPORT int ___x_diab_sfpdnorm_o;
IMPORT int ___x_diab_sfpdpol_o;
IMPORT int ___x_diab_sfpdsetup_o;
IMPORT int ___x_diab_sfpfcmp_o;
IMPORT int ___x_diab_sfpfcmpe_o;
IMPORT int ___x_diab_sfpfnorm_o;
IMPORT int ___x_diab_sfpfsetup_o;
IMPORT int ___x_diab_sfpround_o;
IMPORT int ___x_diab_sxpadd64_o;
IMPORT int ___x_diab_sxpasr64_o;
IMPORT int ___x_diab_sxpcmp64_o;
IMPORT int ___x_diab_sxpdiv64_o;
IMPORT int ___x_diab_sxplsl64_o;
IMPORT int ___x_diab_sxplsr64_o;
IMPORT int ___x_diab_sxpm6432_o;
IMPORT int ___x_diab_sxpmul64_o;
IMPORT int ___x_diab_sxprem32_o;
IMPORT int ___x_diab_sxprem64_o;
IMPORT int ___x_diab_torn_syncatomic_o;
IMPORT int ___x_diab_torn_syncmutex_o;
IMPORT int ___x_diab_torn_syncsem_o;
IMPORT int ___x_diab_wr_pk_db_o;
IMPORT int ___x_diab_wr_pk_fl_o;
IMPORT int ___x_diab_wr_pk_ld_o;
IMPORT int ___x_diab_wr_sw_db_o;
IMPORT int ___x_diab_wr_sw_fl_o;
IMPORT int ___x_diab_wr_sw_ld_o;
IMPORT int ___x_gnu___gcc_bcmp_o;
IMPORT int ___x_gnu__ashldi3_o;
IMPORT int ___x_gnu__ashrdi3_o;
IMPORT int ___x_gnu__bb_init_func_o;
IMPORT int ___x_gnu__bb_o;
IMPORT int ___x_gnu__clear_cache_o;
IMPORT int ___x_gnu__cmpdi2_o;
IMPORT int ___x_gnu__df_to_usi_o;
IMPORT int ___x_gnu__divdi3_o;
IMPORT int ___x_gnu__divsi3_o;
IMPORT int ___x_gnu__dp_df_to_usi_o;
IMPORT int ___x_gnu__dp_fpcmp_parts_df_o;
IMPORT int ___x_gnu__dp_make_df_o;
IMPORT int ___x_gnu__dp_pack_df_o;
IMPORT int ___x_gnu__dp_sf_to_usi_o;
IMPORT int ___x_gnu__dp_thenan_df_o;
IMPORT int ___x_gnu__dp_unpack_df_o;
IMPORT int ___x_gnu__dvmd_tls_o;
IMPORT int ___x_gnu__eh_o;
IMPORT int ___x_gnu__eprintf_o;
IMPORT int ___x_gnu__fixtfdi_o;
IMPORT int ___x_gnu__fixunstfdi_o;
IMPORT int ___x_gnu__fixunsxfdi_o;
IMPORT int ___x_gnu__fixunsxfsi_o;
IMPORT int ___x_gnu__fixxfdi_o;
IMPORT int ___x_gnu__floatditf_o;
IMPORT int ___x_gnu__floatdixf_o;
IMPORT int ___x_gnu__fpcmp_parts_sf_o;
IMPORT int ___x_gnu__interwork_call_via_rX_o;
IMPORT int ___x_gnu__lshrdi3_o;
IMPORT int ___x_gnu__make_sf_o;
IMPORT int ___x_gnu__moddi3_o;
IMPORT int ___x_gnu__modsi3_o;
IMPORT int ___x_gnu__muldi3_o;
IMPORT int ___x_gnu__negdi2_o;
IMPORT int ___x_gnu__pack_sf_o;
IMPORT int ___x_gnu__sf_to_usi_o;
IMPORT int ___x_gnu__shtab_o;
IMPORT int ___x_gnu__thenan_sf_o;
IMPORT int ___x_gnu__trampoline_o;
IMPORT int ___x_gnu__ucmpdi2_o;
IMPORT int ___x_gnu__udiv_w_sdiv_o;
IMPORT int ___x_gnu__udivdi3_o;
IMPORT int ___x_gnu__udivmoddi4_o;
IMPORT int ___x_gnu__udivsi3_o;
IMPORT int ___x_gnu__umoddi3_o;
IMPORT int ___x_gnu__umodsi3_o;
IMPORT int ___x_gnu__unpack_sf_o;
IMPORT int ___x_gnu_cleanup_o;
IMPORT int ___x_gnu_exception_o;
IMPORT int ___x_gnu_filebuf_o;
IMPORT int ___x_gnu_filedoalloc_o;
IMPORT int ___x_gnu_fileops_o;
IMPORT int ___x_gnu_floatconv_o;
IMPORT int ___x_gnu_frame_o;
IMPORT int ___x_gnu_genops_o;
IMPORT int ___x_gnu_ioassign_o;
IMPORT int ___x_gnu_iogetc_o;
IMPORT int ___x_gnu_iogetline_o;
IMPORT int ___x_gnu_iopadn_o;
IMPORT int ___x_gnu_ioputc_o;
IMPORT int ___x_gnu_ioseekoff_o;
IMPORT int ___x_gnu_ioseekpos_o;
IMPORT int ___x_gnu_iostream_o;
IMPORT int ___x_gnu_ioungetc_o;
IMPORT int ___x_gnu_iovfscanf_o;
IMPORT int ___x_gnu_isgetline_o;
IMPORT int ___x_gnu_isscan_o;
IMPORT int ___x_gnu_new_o;
IMPORT int ___x_gnu_outfloat_o;
IMPORT int ___x_gnu_peekc_o;
IMPORT int ___x_gnu_sbscan_o;
IMPORT int ___x_gnu_stdstrbufs_o;
IMPORT int ___x_gnu_stdstreams_o;
IMPORT int ___x_gnu_stlinst_o;
IMPORT int ___x_gnu_streambuf_o;
IMPORT int ___x_gnu_tinfo2_o;
IMPORT int ___x_gnu_tinfo_o;
IMPORT int __add64 ();
IMPORT int __adddf3 ();
IMPORT int __addsf3 ();
IMPORT int __arm_call_via_o;
IMPORT int __as__13CAppInterfaceR13CAppInterface ();
IMPORT int __as__22_IO_istream_withassignR22_IO_istream_withassign ();
IMPORT int __as__22_IO_istream_withassignR7istream ();
IMPORT int __as__22_IO_ostream_withassignR22_IO_ostream_withassign ();
IMPORT int __as__22_IO_ostream_withassignR7ostream ();
IMPORT int __ashldi3 ();
IMPORT int __ashrdi3 ();
IMPORT int __asr64 ();
IMPORT int __assert ();
IMPORT int __builtin_delete ();
IMPORT int __builtin_new ();
IMPORT int __builtin_vec_delete ();
IMPORT int __builtin_vec_new ();
IMPORT int __check_eh_spec ();
IMPORT int __clear_cache ();
IMPORT int __clocale;
IMPORT int __cmpdf2 ();
IMPORT int __cmpdi2 ();
IMPORT int __cmpsf2 ();
IMPORT int __common_intrinsicsInit ();
IMPORT int __common_long_jmp ();
IMPORT int __costate;
IMPORT int __cp_eh_info ();
IMPORT int __cp_exception_info ();
IMPORT int __cp_pop_exception ();
IMPORT int __cp_push_exception ();
IMPORT int __cplusCore_o;
IMPORT int __cplusDem_o;
IMPORT int __cplusLoadObjFiles;
IMPORT int __cplusLoad_o;
IMPORT int __cplusUsr_o;
IMPORT int __cplusXtors_o;
IMPORT int __cplus_type_matcher ();
IMPORT int __ctype;
IMPORT int __daysSinceEpoch ();
IMPORT int __default_terminate ();
IMPORT int __default_unexpected__Fv ();
IMPORT int __dflt_normalise ();
IMPORT int __diab_alloc_mutex ();
IMPORT int __diab_alloc_semaphore ();
IMPORT int __diab_atomic_enter ();
IMPORT int __diab_atomic_restore ();
IMPORT int __diab_free_mutex ();
IMPORT int __diab_free_semaphore ();
IMPORT int __diab_intrinsics_impfpInit ();
IMPORT int __diab_intrinsics_implInit ();
IMPORT int __diab_intrinsics_tornInit ();
IMPORT int __diab_lock_mutex ();
IMPORT int __diab_lock_semaphore ();
IMPORT int __diab_trylock_mutex ();
IMPORT int __diab_trylock_semaphore ();
IMPORT int __diab_unlock_mutex ();
IMPORT int __diab_unlock_semaphore ();
IMPORT int __div0 ();
IMPORT int __div32 ();
IMPORT int __div64 ();
IMPORT int __divdf3 ();
IMPORT int __divdi3 ();
IMPORT int __divsf3 ();
IMPORT int __divsi3 ();
IMPORT int __dunder ();
IMPORT int __dunder_d ();
IMPORT int __dynamic_cast ();
IMPORT int __dynamic_cast_2 ();
IMPORT int __eh_alloc ();
IMPORT int __eh_free ();
IMPORT int __eh_rtime_match ();
IMPORT int __empty ();
IMPORT int __eq64 ();
IMPORT int __eq__C11CSocketNodeRCUc ();
IMPORT int __eq__C11CSocketNodeRCl ();
IMPORT int __eq__C9CLinkNodeRCUc ();
IMPORT int __eq__C9type_infoRC9type_info ();
IMPORT int __eqdf2 ();
IMPORT int __eqsf2 ();
IMPORT int __errno ();
IMPORT int __exp10 ();
IMPORT int __extendsfdf2 ();
IMPORT int __ff1 ();
IMPORT int __ff1l ();
IMPORT int __ff1ll ();
IMPORT int __fflt_normalise ();
IMPORT int __fixdfdi ();
IMPORT int __fixdfsi ();
IMPORT int __fixsfdi ();
IMPORT int __fixsfsi ();
IMPORT int __fixunsdfdi ();
IMPORT int __fixunsdfsi ();
IMPORT int __fixunssfdi ();
IMPORT int __fixunssfsi ();
IMPORT int __floatdidf ();
IMPORT int __floatdisf ();
IMPORT int __floatsidf ();
IMPORT int __floatsisf ();
IMPORT int __fpcmp_parts_d ();
IMPORT int __fpcmp_parts_f ();
IMPORT int __fpl_cmpreturn ();
IMPORT int __fpl_dcheck_NaN2 ();
IMPORT int __fpl_dcmp_InfNaN ();
IMPORT int __fpl_exception ();
IMPORT int __fpl_fcheck_NaN2 ();
IMPORT int __fpl_normalise2 ();
IMPORT int __fpl_return_NaN ();
IMPORT int __funder ();
IMPORT int __funder_d ();
IMPORT int __gcc_bcmp ();
IMPORT int __gcc_intrinsicsInit ();
IMPORT int __ge64 ();
IMPORT int __gedf2 ();
IMPORT int __gesf2 ();
IMPORT int __getDstInfo ();
IMPORT int __getTime ();
IMPORT int __getZoneInfo ();
IMPORT int __get_dynamic_handler_chain ();
IMPORT int __get_eh_context ();
IMPORT int __get_eh_info ();
IMPORT int __gt64 ();
IMPORT int __gtdf2 ();
IMPORT int __gtsf2 ();
IMPORT int __ieee754_rem_pio2 ();
IMPORT int __includeDiabIntrinsics;
IMPORT int __includeGnuIntrinsics;
IMPORT int __is_pointer__FPv ();
IMPORT int __julday ();
IMPORT int __kernel_cos ();
IMPORT int __kernel_poly ();
IMPORT int __kernel_rem_pio2 ();
IMPORT int __kernel_sin ();
IMPORT int __kernel_tan ();
IMPORT int __le64 ();
IMPORT int __ledf2 ();
IMPORT int __lesf2 ();
IMPORT int __locale;
IMPORT int __loctime;
IMPORT int __ls__7ostreamP9streambuf ();
IMPORT int __ls__7ostreamPCSc ();
IMPORT int __ls__7ostreamPCUc ();
IMPORT int __ls__7ostreamPCc ();
IMPORT int __ls__7ostreamPFR3ios_R3ios ();
IMPORT int __ls__7ostreamPFR7ostream_R7ostream ();
IMPORT int __ls__7ostreamSc ();
IMPORT int __ls__7ostreamUc ();
IMPORT int __ls__7ostreamUi ();
IMPORT int __ls__7ostreamUl ();
IMPORT int __ls__7ostreamUs ();
IMPORT int __ls__7ostreamUx ();
IMPORT int __ls__7ostreamb ();
IMPORT int __ls__7ostreamc ();
IMPORT int __ls__7ostreamd ();
IMPORT int __ls__7ostreamf ();
IMPORT int __ls__7ostreami ();
IMPORT int __ls__7ostreaml ();
IMPORT int __ls__7ostreamr ();
IMPORT int __ls__7ostreams ();
IMPORT int __ls__7ostreamx ();
IMPORT int __lshrdi3 ();
IMPORT int __lsl64 ();
IMPORT int __lsr64 ();
IMPORT int __lt64 ();
IMPORT int __lt__C14tagMailBoxNodeUs ();
IMPORT int __lt__FRC14tagMailBoxNodeT0 ();
IMPORT int __ltdf2 ();
IMPORT int __ltsf2 ();
IMPORT int __make_dp ();
IMPORT int __make_fp ();
IMPORT int __moddi3 ();
IMPORT int __modsi3 ();
IMPORT int __mul64 ();
IMPORT int __mul6432 ();
IMPORT int __muldf3 ();
IMPORT int __muldi3 ();
IMPORT int __mulsf3 ();
IMPORT int __ne64 ();
IMPORT int __ne__C11CSocketNodeRCUc ();
IMPORT int __ne__C11CSocketNodeRCl ();
IMPORT int __ne__C9CLinkNodeRCUc ();
IMPORT int __ne__C9type_infoRC9type_info ();
IMPORT int __nedf2 ();
IMPORT int __negdf2 ();
IMPORT int __negdi2 ();
IMPORT int __negsf2 ();
IMPORT int __nesf2 ();
IMPORT int __new_handler;
IMPORT int __nt__C3ios ();
IMPORT int __nw__FUlPv ();
IMPORT int __opPv__C3ios ();
IMPORT int __overflow ();
IMPORT int __overflow__FP9streambufi ();
IMPORT int __pack_d ();
IMPORT int __pack_f ();
IMPORT int __pure_virtual ();
IMPORT int __pure_virtual_called ();
IMPORT int __rem32 ();
IMPORT int __rem64 ();
IMPORT int __rs__7istreamP9streambuf ();
IMPORT int __rs__7istreamPFR3ios_R3ios ();
IMPORT int __rs__7istreamPFR7istream_R7istream ();
IMPORT int __rs__7istreamPSc ();
IMPORT int __rs__7istreamPUc ();
IMPORT int __rs__7istreamPc ();
IMPORT int __rs__7istreamRSc ();
IMPORT int __rs__7istreamRUc ();
IMPORT int __rs__7istreamRUi ();
IMPORT int __rs__7istreamRUl ();
IMPORT int __rs__7istreamRUs ();
IMPORT int __rs__7istreamRUx ();
IMPORT int __rs__7istreamRb ();
IMPORT int __rs__7istreamRc ();
IMPORT int __rs__7istreamRd ();
IMPORT int __rs__7istreamRf ();
IMPORT int __rs__7istreamRi ();
IMPORT int __rs__7istreamRl ();
IMPORT int __rs__7istreamRr ();
IMPORT int __rs__7istreamRs ();
IMPORT int __rs__7istreamRx ();
IMPORT int __rs__FRC8CPackageR9S_MESSAGE ();
IMPORT int __rs__FRC9S_MESSAGEPUc ();
IMPORT int __rt_fp_status_addr ();
IMPORT int __rta_longjmp;
IMPORT int __rtc_alloc_ptr;
IMPORT int __rtc_blkinfo_ptr;
IMPORT int __rtc_free_ptr;
IMPORT int __rtti_array ();
IMPORT int __rtti_attr ();
IMPORT int __rtti_class ();
IMPORT int __rtti_func ();
IMPORT int __rtti_ptmd ();
IMPORT int __rtti_ptmf ();
IMPORT int __rtti_ptr ();
IMPORT int __rtti_si ();
IMPORT int __rtti_user ();
IMPORT int __sclose ();
IMPORT int __set_malloc_handler__t23__malloc_alloc_template1i0PFv_v ();
IMPORT int __sflags ();
IMPORT int __sflush ();
IMPORT int __sfpRoundMode;
IMPORT int __sfvwrite ();
IMPORT int __shtab;
IMPORT int __sjpopnthrow ();
IMPORT int __sjthrow ();
IMPORT int __smakebuf ();
IMPORT int __sn_t24__default_alloc_template2b1i0$_S_node_allocator_lock;
IMPORT int __sread ();
IMPORT int __srefill ();
IMPORT int __srget ();
IMPORT int __sseek ();
IMPORT int __start_cp_handler ();
IMPORT int __stderr ();
IMPORT int __stdin ();
IMPORT int __stdout ();
IMPORT int __strxfrm ();
IMPORT int __sub64 ();
IMPORT int __subdf3 ();
IMPORT int __subsf3 ();
IMPORT int __swbuf ();
IMPORT int __swrite ();
IMPORT int __swsetup ();
IMPORT int __terminate ();
IMPORT int __terminate_func;
IMPORT int __tf10C485Client ();
IMPORT int __tf10CAlarmFile ();
IMPORT int __tf10CAlarmInfo ();
IMPORT int __tf10CAlarmProc ();
IMPORT int __tf10CDataBoard ();
IMPORT int __tf10CEventFile ();
IMPORT int __tf10CMainBoard ();
IMPORT int __tf10COperation ();
IMPORT int __tf10CProcAlarm ();
IMPORT int __tf10CSignBoard ();
IMPORT int __tf10CTcpSocket ();
IMPORT int __tf10bad_typeid ();
IMPORT int __tf11CBackGround ();
IMPORT int __tf11CCrossBoard ();
IMPORT int __tf11CEthnClient ();
IMPORT int __tf11CFunctionIP ();
IMPORT int __tf11COperAndCfg ();
IMPORT int __tf11CSocketNode ();
IMPORT int __tf12CCtrlPackage ();
IMPORT int __tf12CDataPackage ();
IMPORT int __tf12CFunctionLed ();
IMPORT int __tf12CFunctionVer ();
IMPORT int __tf12CHDDataBoard ();
IMPORT int __tf12CSDDataBoard ();
IMPORT int __tf12CSoftUpGrade ();
IMPORT int __tf13CFunctionTemp ();
IMPORT int __tf13bad_exception ();
IMPORT int __tf14C2800DataBoard ();
IMPORT int __tf14COnLinePackage ();
IMPORT int __tf14COperAttribute ();
IMPORT int __tf14CPeriodicTimer ();
IMPORT int __tf14CSystemMessage ();
IMPORT int __tf14__si_type_info ();
IMPORT int __tf15CDebugTcpSocket ();
IMPORT int __tf15CFunctionInSlot ();
IMPORT int __tf16CFunctionRestart ();
IMPORT int __tf16CFunctionVoltage ();
IMPORT int __tf16__user_type_info ();
IMPORT int __tf17CFunctionPortInfo ();
IMPORT int __tf17CKeepAlivePackage ();
IMPORT int __tf17__class_type_info ();
IMPORT int __tf18CProtocolInterface ();
IMPORT int __tf20CFunctionManufacture ();
IMPORT int __tf20CRebootSystemMessage ();
IMPORT int __tf21COfflineSystemMessage ();
IMPORT int __tf21CStandbySystemMessage ();
IMPORT int __tf21CStartupSystemMessage ();
IMPORT int __tf22_IO_istream_withassign ();
IMPORT int __tf22_IO_ostream_withassign ();
IMPORT int __tf3CNe ();
IMPORT int __tf3ios ();
IMPORT int __tf4CWnd ();
IMPORT int __tf5CFile ();
IMPORT int __tf5CRoot ();
IMPORT int __tf6CBoard ();
IMPORT int __tf6CCross ();
IMPORT int __tf6CTimer ();
IMPORT int __tf7CModule ();
IMPORT int __tf7filebuf ();
IMPORT int __tf7istream ();
IMPORT int __tf7ostream ();
IMPORT int __tf8CChannel ();
IMPORT int __tf8CDesktop ();
IMPORT int __tf8CPackage ();
IMPORT int __tf8bad_cast ();
IMPORT int __tf8iostream ();
IMPORT int __tf9CColorKey ();
IMPORT int __tf9CFunction ();
IMPORT int __tf9CLinkNode ();
IMPORT int __tf9CListener ();
IMPORT int __tf9CProtocol ();
IMPORT int __tf9bad_alloc ();
IMPORT int __tf9exception ();
IMPORT int __tf9streambuf ();
IMPORT int __tf9type_info ();
IMPORT int __tfSc ();
IMPORT int __tfUc ();
IMPORT int __tfUi ();
IMPORT int __tfUl ();
IMPORT int __tfUs ();
IMPORT int __tfUx ();
IMPORT int __tfb ();
IMPORT int __tfc ();
IMPORT int __tfd ();
IMPORT int __tff ();
IMPORT int __tfi ();
IMPORT int __tfl ();
IMPORT int __tfr ();
IMPORT int __tfs ();
IMPORT int __tfv ();
IMPORT int __tfw ();
IMPORT int __tfx ();
IMPORT int __thenan_df ();
IMPORT int __thenan_sf ();
IMPORT int __throw_bad_cast ();
IMPORT int __throw_bad_typeid ();
IMPORT int __throw_type_match ();
IMPORT int __throw_type_match_rtti ();
IMPORT int __throw_type_match_rtti_2 ();
IMPORT int __ti10C485Client;
IMPORT int __ti10CAlarmFile;
IMPORT int __ti10CAlarmInfo;
IMPORT int __ti10CAlarmProc;
IMPORT int __ti10CDataBoard;
IMPORT int __ti10CEventFile;
IMPORT int __ti10CMainBoard;
IMPORT int __ti10COperation;
IMPORT int __ti10CProcAlarm;
IMPORT int __ti10CSignBoard;
IMPORT int __ti10CTcpSocket;
IMPORT int __ti10bad_typeid;
IMPORT int __ti11CBackGround;
IMPORT int __ti11CCrossBoard;
IMPORT int __ti11CEthnClient;
IMPORT int __ti11CFunctionIP;
IMPORT int __ti11COperAndCfg;
IMPORT int __ti11CSocketNode;
IMPORT int __ti11_ios_fields;
IMPORT int __ti12CCtrlPackage;
IMPORT int __ti12CDataPackage;
IMPORT int __ti12CFunctionLed;
IMPORT int __ti12CFunctionVer;
IMPORT int __ti12CHDDataBoard;
IMPORT int __ti12CSDDataBoard;
IMPORT int __ti12CSoftUpGrade;
IMPORT int __ti13CCfgTcpSocket;
IMPORT int __ti13CFunctionTemp;
IMPORT int __ti13bad_exception;
IMPORT int __ti14C2800DataBoard;
IMPORT int __ti14COnLinePackage;
IMPORT int __ti14COperAttribute;
IMPORT int __ti14CPeriodicTimer;
IMPORT int __ti14CRelativeTimer;
IMPORT int __ti14CSoftTcpSocket;
IMPORT int __ti14CSystemMessage;
IMPORT int __ti14__si_type_info;
IMPORT int __ti15CAlarmTcpSocket;
IMPORT int __ti15CDebugTcpSocket;
IMPORT int __ti15CFunctionInSlot;
IMPORT int __ti16CFunctionRestart;
IMPORT int __ti16CFunctionVoltage;
IMPORT int __ti16__attr_type_info;
IMPORT int __ti16__func_type_info;
IMPORT int __ti16__ptmd_type_info;
IMPORT int __ti16__ptmf_type_info;
IMPORT int __ti16__user_type_info;
IMPORT int __ti17CFunctionPortInfo;
IMPORT int __ti17CKeepAlivePackage;
IMPORT int __ti17__array_type_info;
IMPORT int __ti17__class_type_info;
IMPORT int __ti18CProtocolInterface;
IMPORT int __ti19__builtin_type_info;
IMPORT int __ti19__pointer_type_info;
IMPORT int __ti20CFunctionManufacture;
IMPORT int __ti20CRebootSystemMessage;
IMPORT int __ti21COfflineSystemMessage;
IMPORT int __ti21CStandbySystemMessage;
IMPORT int __ti21CStartupSystemMessage;
IMPORT int __ti22_IO_istream_withassign;
IMPORT int __ti22_IO_ostream_withassign;
IMPORT int __ti3CNe;
IMPORT int __ti3ios;
IMPORT int __ti4CWnd;
IMPORT int __ti5CFile;
IMPORT int __ti5CRoot;
IMPORT int __ti6CBoard;
IMPORT int __ti6CCross;
IMPORT int __ti6CTimer;
IMPORT int __ti7CModule;
IMPORT int __ti7filebuf;
IMPORT int __ti7istream;
IMPORT int __ti7ostream;
IMPORT int __ti8CChannel;
IMPORT int __ti8CDesktop;
IMPORT int __ti8CPackage;
IMPORT int __ti8_IO_FILE;
IMPORT int __ti8bad_cast;
IMPORT int __ti8iostream;
IMPORT int __ti9CColorKey;
IMPORT int __ti9CFunction;
IMPORT int __ti9CLinkNode;
IMPORT int __ti9CListener;
IMPORT int __ti9CProtocol;
IMPORT int __ti9bad_alloc;
IMPORT int __ti9exception;
IMPORT int __ti9streambuf;
IMPORT int __ti9type_info;
IMPORT int __tiSc;
IMPORT int __tiUc;
IMPORT int __tiUi;
IMPORT int __tiUl;
IMPORT int __tiUs;
IMPORT int __tiUx;
IMPORT int __tib;
IMPORT int __tic;
IMPORT int __tid;
IMPORT int __tif;
IMPORT int __tii;
IMPORT int __til;
IMPORT int __tir;
IMPORT int __tis;
IMPORT int __tiv;
IMPORT int __tiw;
IMPORT int __tix;
IMPORT int __truncdfsf2 ();
IMPORT int __ucmpdi2 ();
IMPORT int __udiv32 ();
IMPORT int __udiv64 ();
IMPORT int __udiv_w_sdiv ();
IMPORT int __udivdi3 ();
IMPORT int __udivmoddi4 ();
IMPORT int __udivsi3 ();
IMPORT int __uflow ();
IMPORT int __uge64 ();
IMPORT int __ugt64 ();
IMPORT int __ule64 ();
IMPORT int __ult64 ();
IMPORT int __umoddi3 ();
IMPORT int __umodsi3 ();
IMPORT int __uncatch_exception ();
IMPORT int __underflow ();
IMPORT int __unpack_d ();
IMPORT int __unpack_f ();
IMPORT int __urem32 ();
IMPORT int __urem64 ();
IMPORT int __vn__FUlPv ();
IMPORT int __wdbEventListIsEmpty;
IMPORT int __wdbEvtptDeleteAll;
IMPORT int _archHelp_msg;
IMPORT int _arpCmd ();
IMPORT int _clockRealtime;
IMPORT int _cplusDemangle ();
IMPORT int _d2f ();
IMPORT int _d_add ();
IMPORT int _d_cmp ();
IMPORT int _d_cmpe ();
IMPORT int _d_div ();
IMPORT int _d_dtof ();
IMPORT int _d_dtoi ();
IMPORT int _d_dtoll ();
IMPORT int _d_dtou ();
IMPORT int _d_dtoull ();
IMPORT int _d_feq ();
IMPORT int _d_fge ();
IMPORT int _d_fgt ();
IMPORT int _d_fle ();
IMPORT int _d_flt ();
IMPORT int _d_fne ();
IMPORT int _d_itod ();
IMPORT int _d_lltod ();
IMPORT int _d_mul ();
IMPORT int _d_sub ();
IMPORT int _d_ulltod ();
IMPORT int _d_utod ();
IMPORT int _dabs ();
IMPORT int _dadd ();
IMPORT int _db_show_arptab ();
IMPORT int _dbgArchInit ();
IMPORT int _dbgDsmInstRtn;
IMPORT int _dbgFuncCallCheck ();
IMPORT int _dbgInstSizeGet ();
IMPORT int _dbgRetAdrsGet ();
IMPORT int _dbgTaskPCGet ();
IMPORT int _dbgTaskPCSet ();
IMPORT int _dcmpeq ();
IMPORT int _dcmpge ();
IMPORT int _dcmple ();
IMPORT int _ddiv ();
IMPORT int _deq ();
IMPORT int _dfix ();
IMPORT int _dfix_r ();
IMPORT int _dfixu ();
IMPORT int _dfixu_r ();
IMPORT int _dflt ();
IMPORT int _dfltu ();
IMPORT int _dgeq ();
IMPORT int _dgr ();
IMPORT int _dleq ();
IMPORT int _dls ();
IMPORT int _dmul ();
IMPORT int _dneg ();
IMPORT int _dneq ();
IMPORT int _drdiv ();
IMPORT int _drem ();
IMPORT int _drsb ();
IMPORT int _dsqrt ();
IMPORT int _dsub ();
IMPORT int _f2d ();
IMPORT int _f_add ();
IMPORT int _f_cmp ();
IMPORT int _f_cmpe ();
IMPORT int _f_div ();
IMPORT int _f_feq ();
IMPORT int _f_fge ();
IMPORT int _f_fgt ();
IMPORT int _f_fle ();
IMPORT int _f_flt ();
IMPORT int _f_fne ();
IMPORT int _f_ftod ();
IMPORT int _f_ftoi ();
IMPORT int _f_ftoll ();
IMPORT int _f_ftou ();
IMPORT int _f_ftoull ();
IMPORT int _f_itof ();
IMPORT int _f_lltof ();
IMPORT int _f_mul ();
IMPORT int _f_sub ();
IMPORT int _f_ulltof ();
IMPORT int _f_utof ();
IMPORT int _fabs ();
IMPORT int _fadd ();
IMPORT int _fcmpeq ();
IMPORT int _fcmpge ();
IMPORT int _fcmple ();
IMPORT int _fdiv ();
IMPORT int _feq ();
IMPORT int _ffix ();
IMPORT int _ffix_r ();
IMPORT int _ffixu ();
IMPORT int _ffixu_r ();
IMPORT int _fflt ();
IMPORT int _ffltu ();
IMPORT int _fgeq ();
IMPORT int _fgr ();
IMPORT int _fleq ();
IMPORT int _fls ();
IMPORT int _fmul ();
IMPORT int _fneg ();
IMPORT int _fneq ();
IMPORT int _fpStatus;
IMPORT int _fp_round ();
IMPORT int _fp_trap ();
IMPORT int _fp_trapveneer ();
IMPORT int _frdiv ();
IMPORT int _frsb ();
IMPORT int _fsub ();
IMPORT int _func_armIntStackSplit;
IMPORT int _func_armIrqHandler;
IMPORT int _func_armPageSource;
IMPORT int _func_bdall;
IMPORT int _func_dbgHostNotify;
IMPORT int _func_dbgTargetNotify;
IMPORT int _func_dspMregsHook;
IMPORT int _func_dspRegsListHook;
IMPORT int _func_dspTaskRegsShow;
IMPORT int _func_evtLogM0;
IMPORT int _func_evtLogM1;
IMPORT int _func_evtLogM2;
IMPORT int _func_evtLogM3;
IMPORT int _func_evtLogO;
IMPORT int _func_evtLogOIntLock;
IMPORT int _func_evtLogPoint;
IMPORT int _func_evtLogReserveTaskName;
IMPORT int _func_evtLogString;
IMPORT int _func_evtLogT0;
IMPORT int _func_evtLogT0_noInt;
IMPORT int _func_evtLogT1;
IMPORT int _func_evtLogT1_noTS;
IMPORT int _func_evtLogTSched;
IMPORT int _func_excBaseHook;
IMPORT int _func_excBreakpoint;
IMPORT int _func_excInfoShow;
IMPORT int _func_excIntHook;
IMPORT int _func_excJobAdd;
IMPORT int _func_excPanicHook;
IMPORT int _func_fclose;
IMPORT int _func_fileDoesNotExist;
IMPORT int _func_fppTaskRegsShow;
IMPORT int _func_ftpLs;
IMPORT int _func_ftpTransientFatal;
IMPORT int _func_ioTaskStdSet;
IMPORT int _func_ipsecFilterHook;
IMPORT int _func_ipsecInput;
IMPORT int _func_ipsecOutput;
IMPORT int _func_logMsg;
IMPORT int _func_memalign;
IMPORT int _func_netLsByName;
IMPORT int _func_printErr;
IMPORT int _func_pthread_setcanceltype;
IMPORT int _func_remCurIdGet;
IMPORT int _func_remCurIdSet;
IMPORT int _func_selPtyAdd;
IMPORT int _func_selPtyDelete;
IMPORT int _func_selTyAdd;
IMPORT int _func_selTyDelete;
IMPORT int _func_selWakeupAll;
IMPORT int _func_selWakeupListInit;
IMPORT int _func_selWakeupListTerm;
IMPORT int _func_sigExcKill;
IMPORT int _func_sigTimeoutRecalc;
IMPORT int _func_sigprocmask;
IMPORT int _func_smObjObjShow;
IMPORT int _func_spy;
IMPORT int _func_spyClkStart;
IMPORT int _func_spyClkStop;
IMPORT int _func_spyReport;
IMPORT int _func_spyStop;
IMPORT int _func_spyTask;
IMPORT int _func_sseTaskRegsShow;
IMPORT int _func_symFindByValue;
IMPORT int _func_symFindByValueAndType;
IMPORT int _func_symFindSymbol;
IMPORT int _func_symNameGet;
IMPORT int _func_symTypeGet;
IMPORT int _func_symValueGet;
IMPORT int _func_taskCreateHookAdd;
IMPORT int _func_taskDeleteHookAdd;
IMPORT int _func_taskRegsShowRtn;
IMPORT int _func_tmrConnect;
IMPORT int _func_tmrDisable;
IMPORT int _func_tmrEnable;
IMPORT int _func_tmrFreq;
IMPORT int _func_tmrPeriod;
IMPORT int _func_tmrStamp;
IMPORT int _func_tmrStampLock;
IMPORT int _func_trap;
IMPORT int _func_trgCheck;
IMPORT int _func_valloc;
IMPORT int _func_vxMemProbeHook;
IMPORT int _func_wdbIsNowExternal;
IMPORT int _func_wvNetAddressFilterTest;
IMPORT int _func_wvNetPortFilterTest;
IMPORT int _icmpErrorHook;
IMPORT int _igmpJoinAlertHook;
IMPORT int _igmpJoinGrpHook;
IMPORT int _igmpLeaveAlertHook;
IMPORT int _igmpLeaveGrpHook;
IMPORT int _igmpMessageHook;
IMPORT int _igmpQuerierTimeUpdateHook;
IMPORT int _insque ();
IMPORT int _ipCfgFlags;
IMPORT int _ipFilterHook;
IMPORT int _landAttackSafe;
IMPORT int _link_in__9streambuf ();
IMPORT int _ll_sfrom_d ();
IMPORT int _ll_sfrom_d_r ();
IMPORT int _ll_sfrom_f ();
IMPORT int _ll_sfrom_f_r ();
IMPORT int _ll_sto_d ();
IMPORT int _ll_sto_f ();
IMPORT int _ll_ufrom_d ();
IMPORT int _ll_ufrom_d_r ();
IMPORT int _ll_ufrom_f ();
IMPORT int _ll_ufrom_f_r ();
IMPORT int _ll_uto_d ();
IMPORT int _ll_uto_f ();
IMPORT int _m2IfTableUpdate;
IMPORT int _m2SetIfLastChange;
IMPORT int _mCastRouteCmdHook;
IMPORT int _mCastRouteFwdHook;
IMPORT int _mmuCrValue;
IMPORT int _netFree ();
IMPORT int _netMalloc ();
IMPORT int _pNetBufCollect;
IMPORT int _pNetDpool;
IMPORT int _pNetPoolFuncTbl;
IMPORT int _pNetSysPool;
IMPORT int _pSigQueueFreeHead;
IMPORT int _pTcpPcbHead;
IMPORT int _pTcpPcbPrint;
IMPORT int _pUdpPcbHead;
IMPORT int _panicHook;
IMPORT int _pingTxInterval;
IMPORT int _pingTxLen;
IMPORT int _pingTxTmo;
IMPORT int _presolvHostLibGetByAddr;
IMPORT int _presolvHostLibGetByName;
IMPORT int _procNumWasSet;
IMPORT int _protoSwIndex;
IMPORT int _remque ();
IMPORT int _sb_readline__FP9streambufRlc ();
IMPORT int _sch_istable ();
IMPORT int _sch_tolower ();
IMPORT int _sch_toupper ();
IMPORT int _setjmpSetup ();
IMPORT int _sigCtxLoad ();
IMPORT int _sigCtxRtnValSet ();
IMPORT int _sigCtxSave ();
IMPORT int _sigCtxSetup ();
IMPORT int _sigCtxStackEnd ();
IMPORT int _sigfaulttable;
IMPORT int _skip_ws__7istream ();
IMPORT int _t23__malloc_alloc_template1i0$__malloc_alloc_oom_handler;
IMPORT int _t24__default_alloc_template2b1i0$_S_end_free;
IMPORT int _t24__default_alloc_template2b1i0$_S_free_list;
IMPORT int _t24__default_alloc_template2b1i0$_S_heap_size;
IMPORT int _t24__default_alloc_template2b1i0$_S_node_allocator_lock;
IMPORT int _t24__default_alloc_template2b1i0$_S_start_free;
IMPORT int _throw_failure__C3ios ();
IMPORT int _un_link__9streambuf ();
IMPORT int _vt$10C485Client ();
IMPORT int _vt$10CAlarmFile ();
IMPORT int _vt$10CAlarmInfo ();
IMPORT int _vt$10CAlarmProc ();
IMPORT int _vt$10CDataBoard ();
IMPORT int _vt$10CEventFile ();
IMPORT int _vt$10CMainBoard ();
IMPORT int _vt$10COperation ();
IMPORT int _vt$10CProcAlarm ();
IMPORT int _vt$10CSignBoard ();
IMPORT int _vt$10CTcpSocket ();
IMPORT int _vt$10bad_typeid ();
IMPORT int _vt$11CBackGround ();
IMPORT int _vt$11CCrossBoard ();
IMPORT int _vt$11CEthnClient ();
IMPORT int _vt$11CFunctionIP ();
IMPORT int _vt$11COperAndCfg ();
IMPORT int _vt$11CSocketNode ();
IMPORT int _vt$12CCtrlPackage ();
IMPORT int _vt$12CDataPackage ();
IMPORT int _vt$12CFunctionLed ();
IMPORT int _vt$12CFunctionVer ();
IMPORT int _vt$12CHDDataBoard ();
IMPORT int _vt$12CSDDataBoard ();
IMPORT int _vt$12CSoftUpGrade ();
IMPORT int _vt$13CFunctionTemp ();
IMPORT int _vt$13bad_exception ();
IMPORT int _vt$14C2800DataBoard ();
IMPORT int _vt$14COnLinePackage ();
IMPORT int _vt$14COperAttribute ();
IMPORT int _vt$14CPeriodicTimer ();
IMPORT int _vt$14CSystemMessage ();
IMPORT int _vt$14__si_type_info ();
IMPORT int _vt$15CDebugTcpSocket ();
IMPORT int _vt$15CFunctionInSlot ();
IMPORT int _vt$16CFunctionRestart ();
IMPORT int _vt$16CFunctionVoltage ();
IMPORT int _vt$16__user_type_info ();
IMPORT int _vt$17CFunctionPortInfo ();
IMPORT int _vt$17CKeepAlivePackage ();
IMPORT int _vt$17__class_type_info ();
IMPORT int _vt$18CProtocolInterface ();
IMPORT int _vt$20CFunctionManufacture ();
IMPORT int _vt$20CRebootSystemMessage ();
IMPORT int _vt$21COfflineSystemMessage ();
IMPORT int _vt$21CStandbySystemMessage ();
IMPORT int _vt$21CStartupSystemMessage ();
IMPORT int _vt$22_IO_istream_withassign$3ios ();
IMPORT int _vt$22_IO_ostream_withassign$3ios ();
IMPORT int _vt$3CNe ();
IMPORT int _vt$3ios ();
IMPORT int _vt$4CWnd ();
IMPORT int _vt$5CFile ();
IMPORT int _vt$5CRoot ();
IMPORT int _vt$6CBoard ();
IMPORT int _vt$6CCross ();
IMPORT int _vt$6CTimer ();
IMPORT int _vt$7CModule ();
IMPORT int _vt$7filebuf ();
IMPORT int _vt$7istream$3ios ();
IMPORT int _vt$7ostream$3ios ();
IMPORT int _vt$8CChannel ();
IMPORT int _vt$8CDesktop ();
IMPORT int _vt$8CPackage ();
IMPORT int _vt$8bad_cast ();
IMPORT int _vt$8iostream$3ios ();
IMPORT int _vt$9CColorKey ();
IMPORT int _vt$9CFunction ();
IMPORT int _vt$9CLinkNode ();
IMPORT int _vt$9CListener ();
IMPORT int _vt$9CProtocol ();
IMPORT int _vt$9bad_alloc ();
IMPORT int _vt$9exception ();
IMPORT int _vt$9streambuf ();
IMPORT int _vt$9type_info ();
IMPORT int _vtable__9streambuf ();
IMPORT int _wdbTaskBpAdd;
IMPORT int _wdbTaskBpTrap;
IMPORT int _wdbTaskCont;
IMPORT int _wdbTaskStep;
IMPORT int _wdbTgtHasAltivec;
IMPORT int _wdbTgtHasDsp;
IMPORT int _wdbTgtHasFpp;
IMPORT int abort ();
IMPORT int abs ();
IMPORT int accept ();
IMPORT int ack1;
IMPORT int ack2;
IMPORT int acos ();
IMPORT int activeQHead;
IMPORT int addDomain ();
IMPORT int addSegNames ();
IMPORT int alarmDebug ();
IMPORT int allocate__9streambuf ();
IMPORT int allocate__t23__malloc_alloc_template1i0Ul ();
IMPORT int allocate__t24__default_alloc_template2b1i0Ul ();
IMPORT int allocbuf__9streambuf ();
IMPORT int armGetNpc ();
IMPORT int armInitExceptionModes ();
IMPORT int armInstrChangesPc ();
IMPORT int arpAdd ();
IMPORT int arpCmd ();
IMPORT int arpDelete ();
IMPORT int arpFlush ();
IMPORT int arpLibInit ();
IMPORT int arpMaxEntries;
IMPORT int arpResolve ();
IMPORT int arpRxmitTicks;
IMPORT int arpShow ();
IMPORT int arp_allocated;
IMPORT int arp_intimer;
IMPORT int arp_inuse;
IMPORT int arp_maxtries;
IMPORT int arp_rtrequest ();
IMPORT int arpinit_done;
IMPORT int arpintr ();
IMPORT int arpintrq;
IMPORT int arpioctl ();
IMPORT int arpresolve ();
IMPORT int arpt_down;
IMPORT int arpt_keep;
IMPORT int arpt_prune;
IMPORT int arptabShow ();
IMPORT int arptfree ();
IMPORT int arpwhohas ();
IMPORT int asctime ();
IMPORT int asctime_r ();
IMPORT int asin ();
IMPORT int at91EthFlagsSet ();
IMPORT int at91EthInit ();
IMPORT int at91EthLoopSet ();
IMPORT int at91EthMCastAdd ();
IMPORT int at91EthMCastDel ();
IMPORT int at91EthMiiShow ();
IMPORT int at91EthMulTest ();
IMPORT int at91EthPollReceive ();
IMPORT int at91EthPollSend ();
IMPORT int at91EthPollStart ();
IMPORT int at91EthPollStop ();
IMPORT int at91EthRbdCheck ();
IMPORT int at91EthRbdFree ();
IMPORT int at91EthRbdProcess ();
IMPORT int at91EthSend ();
IMPORT int at91EthSend2 ();
IMPORT int at91EthShow ();
IMPORT int at91EthStart ();
IMPORT int at91EthStop ();
IMPORT int at91EthTbdCheck ();
IMPORT int at91EthTbdFree ();
IMPORT int at91EthTbdGet ();
IMPORT int at91EthTbdProcess ();
IMPORT int at91EthTbdStart ();
IMPORT int at91EthURbdProcess ();
IMPORT int at91IntDevInit ();
IMPORT int at91SioDevInit ();
IMPORT int at91SioDevInit2 ();
IMPORT int at91SioInt ();
IMPORT int atan ();
IMPORT int atan2 ();
IMPORT int atexit ();
IMPORT int atof ();
IMPORT int atoi ();
IMPORT int atol ();
IMPORT int attach__7filebufi ();
IMPORT int attrib ();
IMPORT int b ();
IMPORT int bad__C3ios ();
IMPORT int base__C9streambuf ();
IMPORT int bcmp ();
IMPORT int bcopy ();
IMPORT int bcopyBytes ();
IMPORT int bcopyLongs ();
IMPORT int bcopyWords ();
IMPORT int bcopy_to_mbufs ();
IMPORT int bd ();
IMPORT int bdall ();
IMPORT int before__C9type_infoRC9type_info ();
IMPORT int bfill ();
IMPORT int bfillBytes ();
IMPORT int bind ();
IMPORT int bindresvport ();
IMPORT int binvert ();
IMPORT int bitreverse ();
IMPORT int blen__C9streambuf ();
IMPORT int bootBpAnchorExtract ();
IMPORT int bootChange ();
IMPORT int bootLeaseExtract ();
IMPORT int bootNetmaskExtract ();
IMPORT int bootParamsErrorPrint ();
IMPORT int bootParamsPrompt ();
IMPORT int bootParamsShow ();
IMPORT int bootScanNum ();
IMPORT int bootStringToStruct ();
IMPORT int bootStructToString ();
IMPORT int bpFreeList;
IMPORT int bpList;
IMPORT int bsdAccept ();
IMPORT int bsdBind ();
IMPORT int bsdConnect ();
IMPORT int bsdConnectWithTimeout ();
IMPORT int bsdGetpeername ();
IMPORT int bsdGetsockname ();
IMPORT int bsdGetsockopt ();
IMPORT int bsdListen ();
IMPORT int bsdRecv ();
IMPORT int bsdRecvfrom ();
IMPORT int bsdRecvmsg ();
IMPORT int bsdSend ();
IMPORT int bsdSendmsg ();
IMPORT int bsdSendto ();
IMPORT int bsdSetsockopt ();
IMPORT int bsdShutdown ();
IMPORT int bsdSock43ApiFlag;
IMPORT int bsdSockFunc;
IMPORT int bsdSockLibInit ();
IMPORT int bsdSocket ();
IMPORT int bsdZbufSockRtn ();
IMPORT int bsearch ();
IMPORT int bswap ();
IMPORT int bufAlloc ();
IMPORT int bufFree ();
IMPORT int bufPoolInit ();
IMPORT int bufferedRtShow ();
IMPORT int build_cluster ();
IMPORT int bzero ();
IMPORT int c ();
IMPORT int cacheArchAlignSize;
IMPORT int cacheArchIntLock ();
IMPORT int cacheArchIntMask;
IMPORT int cacheArchState;
IMPORT int cacheArm920tArchPipeFlush ();
IMPORT int cacheArm920tDClear ();
IMPORT int cacheArm920tDClearAll ();
IMPORT int cacheArm920tDClearDisable ();
IMPORT int cacheArm920tDFlush ();
IMPORT int cacheArm920tDFlushAll ();
IMPORT int cacheArm920tDInvalidate ();
IMPORT int cacheArm920tDInvalidateAll ();
IMPORT int cacheArm920tIClearDisable ();
IMPORT int cacheArm920tIInvalidate ();
IMPORT int cacheArm920tIInvalidateAll ();
IMPORT int cacheArm920tLibInstall ();
IMPORT int cacheClear ();
IMPORT int cacheDataEnabled;
IMPORT int cacheDataMode;
IMPORT int cacheDisable ();
IMPORT int cacheDmaFree ();
IMPORT int cacheDmaFreeRtn;
IMPORT int cacheDmaFuncs;
IMPORT int cacheDmaMalloc ();
IMPORT int cacheDmaMallocRtn;
IMPORT int cacheDrvFlush ();
IMPORT int cacheDrvInvalidate ();
IMPORT int cacheDrvPhysToVirt ();
IMPORT int cacheDrvVirtToPhys ();
IMPORT int cacheEnable ();
IMPORT int cacheFlush ();
IMPORT int cacheFuncsSet ();
IMPORT int cacheInvalidate ();
IMPORT int cacheLib;
IMPORT int cacheLibInit ();
IMPORT int cacheLock ();
IMPORT int cacheMmuAvailable;
IMPORT int cacheNullFuncs;
IMPORT int cachePipeFlush ();
IMPORT int cacheTextUpdate ();
IMPORT int cacheUnlock ();
IMPORT int cacheUserFuncs;
IMPORT int calloc ();
IMPORT int cbioBlkCopy ();
IMPORT int cbioBlkRW ();
IMPORT int cbioBytesRW ();
IMPORT int cbioClass;
IMPORT int cbioClassId;
IMPORT int cbioDevCreate ();
IMPORT int cbioDevVerify ();
IMPORT int cbioIoctl ();
IMPORT int cbioLibInit ();
IMPORT int cbioLock ();
IMPORT int cbioModeGet ();
IMPORT int cbioModeSet ();
IMPORT int cbioMutexSemOptions;
IMPORT int cbioParamsGet ();
IMPORT int cbioRdyChgdGet ();
IMPORT int cbioRdyChgdSet ();
IMPORT int cbioRdyChk ();
IMPORT int cbioShow ();
IMPORT int cbioUnlock ();
IMPORT int cbioWrapBlkDev ();
IMPORT int cd ();
IMPORT int ceil ();
IMPORT int cerr;
IMPORT int cfree ();
IMPORT int changeReg ();
IMPORT int chdir ();
IMPORT int checkInetAddrField ();
IMPORT int checkStack ();
IMPORT int check_trailer ();
IMPORT int checksum ();
IMPORT int chkdsk ();
IMPORT int cin;
IMPORT int cksum ();
IMPORT int clDescTbl;
IMPORT int clDescTblNumEnt;
IMPORT int classClassId;
IMPORT int classCreate ();
IMPORT int classDestroy ();
IMPORT int classInit ();
IMPORT int classInstConnect ();
IMPORT int classInstrument ();
IMPORT int classLibInit ();
IMPORT int classMemPartIdSet ();
IMPORT int classShowConnect ();
IMPORT int clear__3iosi ();
IMPORT int clearerr ();
IMPORT int clock ();
IMPORT int clockLibInit ();
IMPORT int clock_getres ();
IMPORT int clock_gettime ();
IMPORT int clock_setres ();
IMPORT int clock_settime ();
IMPORT int clock_show ();
IMPORT int clog;
IMPORT int close ();
IMPORT int close__3ios ();
IMPORT int close__7filebuf ();
IMPORT int closedir ();
IMPORT int commtest ();
IMPORT int connect ();
IMPORT int connectWithTimeout ();
IMPORT int consoleFd;
IMPORT int contained_nonpublic_p__16__user_type_infoQ216__user_type_info8sub_kind ();
IMPORT int contained_nonvirtual_p__16__user_type_infoQ216__user_type_info8sub_kind ();
IMPORT int contained_p__16__user_type_infoQ216__user_type_info8sub_kind ();
IMPORT int contained_public_p__16__user_type_infoQ216__user_type_info8sub_kind ();
IMPORT int copy ();
IMPORT int copyFromMbufs ();
IMPORT int copyStreams ();
IMPORT int copyright_wind_river;
IMPORT int copysign ();
IMPORT int cos ();
IMPORT int cosh ();
IMPORT int cout;
IMPORT int cp ();
IMPORT int cplusArraysInit ();
IMPORT int cplusCallCtors ();
IMPORT int cplusCallDtors ();
IMPORT int cplusCallNewHandler__Fv ();
IMPORT int cplusCtors ();
IMPORT int cplusCtorsLink ();
IMPORT int cplusDemangle ();
IMPORT int cplusDemangleFunc;
IMPORT int cplusDemanglerInit ();
IMPORT int cplusDemanglerMode;
IMPORT int cplusDemanglerSet ();
IMPORT int cplusDemanglerStyle;
IMPORT int cplusDemanglerStyleSet ();
IMPORT int cplusDtors ();
IMPORT int cplusDtorsLink ();
IMPORT int cplusLibMinInit ();
IMPORT int cplusLoadFixup ();
IMPORT int cplusMatchMangled ();
IMPORT int cplusNewHandlerExists__Fv ();
IMPORT int cplusNewHdlMutex;
IMPORT int cplusTerminate__Fv ();
IMPORT int cplusUnloadFixup ();
IMPORT int cplusXtorSet ();
IMPORT int cplusXtorStrategy;
IMPORT int cplus_demangle ();
IMPORT int cplus_demangle_name_to_style ();
IMPORT int cplus_demangle_opname ();
IMPORT int cplus_demangle_set_style ();
IMPORT int cplus_demangle_v3 ();
IMPORT int cplus_mangle_opname ();
IMPORT int cpsr ();
IMPORT int crc32_le ();
IMPORT int creat ();
IMPORT int creationDate;
IMPORT int cret ();
IMPORT int ctime ();
IMPORT int ctime_r ();
IMPORT int cur_ptr__7filebuf ();
IMPORT int currentContext;
IMPORT int current_demangling_style;
IMPORT int d ();
IMPORT int db_print_sa ();
IMPORT int db_show_arptab ();
IMPORT int dbgHelp ();
IMPORT int dbgInit ();
IMPORT int dbgLockUnbreakable;
IMPORT int dbgPrintCall ();
IMPORT int dbgPrintDsp;
IMPORT int dbgPrintFpp;
IMPORT int dbgPrintSimd;
IMPORT int dbgSafeUnbreakable;
IMPORT int dbgTaskBpBreakpoint ();
IMPORT int dbgTaskBpHooksInstall ();
IMPORT int dbgTaskBpTrace ();
IMPORT int dbgTaskBpTrap ();
IMPORT int dbgTaskCont ();
IMPORT int dbgTaskStep ();
IMPORT int dbgUnbreakableOld;
IMPORT int dcacheCtrl;
IMPORT int dcacheDevCreate ();
IMPORT int dcacheDevDisable ();
IMPORT int dcacheDevEnable ();
IMPORT int dcacheDevMemResize ();
IMPORT int dcacheDevTune ();
IMPORT int dcacheShow ();
IMPORT int dcacheUpd ();
IMPORT int dcacheUpdTaskId;
IMPORT int dcacheUpdTaskOptions;
IMPORT int dcacheUpdTaskPriority;
IMPORT int dcacheUpdTaskStack;
IMPORT int ddiv_mantissas ();
IMPORT int deallocate__t23__malloc_alloc_template1i0PvUl ();
IMPORT int deallocate__t24__default_alloc_template2b1i0PvUl ();
IMPORT int dec__FR3ios ();
IMPORT int decode_identifier ();
IMPORT int decode_identifier_styled ();
IMPORT int delayNSec ();
IMPORT int delayUSec ();
IMPORT int delta__12streammarker ();
IMPORT int delta__12streammarkerR12streammarker ();
IMPORT int devSplit ();
IMPORT int devs ();
IMPORT int difftime ();
IMPORT int dirList ();
IMPORT int diskFormat ();
IMPORT int diskInit ();
IMPORT int dispLM73reg ();
IMPORT int div ();
IMPORT int div_r ();
IMPORT int dllAdd ();
IMPORT int dllCount ();
IMPORT int dllCreate ();
IMPORT int dllDelete ();
IMPORT int dllEach ();
IMPORT int dllGet ();
IMPORT int dllInit ();
IMPORT int dllInsert ();
IMPORT int dllRemove ();
IMPORT int dllTerminate ();
IMPORT int do_dyncast__C14__si_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result ();
IMPORT int do_dyncast__C16__user_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result ();
IMPORT int do_dyncast__C17__class_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result ();
IMPORT int do_find_public_subobj__C14__si_type_infoiRC9type_infoPvT3 ();
IMPORT int do_find_public_subobj__C16__user_type_infoiRC9type_infoPvT3 ();
IMPORT int do_find_public_subobj__C17__class_type_infoiRC9type_infoPvT3 ();
IMPORT int do_osfx__7ostream ();
IMPORT int do_protocol_with_type ();
IMPORT int do_upcast__C14__si_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result ();
IMPORT int do_upcast__C16__user_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result ();
IMPORT int do_upcast__C17__class_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result ();
IMPORT int doallocate__7filebuf ();
IMPORT int doallocate__9streambuf ();
IMPORT int doallocbuf__9streambuf ();
IMPORT int domaininit ();
IMPORT int domains;
IMPORT int dosChkDebug;
IMPORT int dosChkDsk ();
IMPORT int dosChkEntryMark ();
IMPORT int dosChkLibInit ();
IMPORT int dosChkMinDate;
IMPORT int dosDirHdlrsList;
IMPORT int dosDirOldDebug;
IMPORT int dosDirOldLibInit ();
IMPORT int dosFatHdlrsList;
IMPORT int dosFsCacheSizeDefault;
IMPORT int dosFsChkDsk ();
IMPORT int dosFsChkRtn;
IMPORT int dosFsChkTree ();
IMPORT int dosFsConfigGet ();
IMPORT int dosFsConfigInit ();
IMPORT int dosFsConfigShow ();
IMPORT int dosFsDateTimeInstall ();
IMPORT int dosFsDebug;
IMPORT int dosFsDevCreate ();
IMPORT int dosFsDevInit ();
IMPORT int dosFsDevInitOptionsSet ();
IMPORT int dosFsDrvNum;
IMPORT int dosFsFatInit ();
IMPORT int dosFsFmtLibInit ();
IMPORT int dosFsHdlrInstall ();
IMPORT int dosFsInit ();
IMPORT int dosFsLastAccessDateEnable ();
IMPORT int dosFsLibInit ();
IMPORT int dosFsMkfs ();
IMPORT int dosFsMkfsOptionsSet ();
IMPORT int dosFsModeChange ();
IMPORT int dosFsReadyChange ();
IMPORT int dosFsShow ();
IMPORT int dosFsVolDescGet ();
IMPORT int dosFsVolFormat ();
IMPORT int dosFsVolFormatRtn;
IMPORT int dosFsVolIsFat12 ();
IMPORT int dosFsVolOptionsGet ();
IMPORT int dosFsVolOptionsSet ();
IMPORT int dosFsVolUnmount ();
IMPORT int dosSetVolCaseSens ();
IMPORT int dosVDirDebug;
IMPORT int dosVDirLibInit ();
IMPORT int drvTable;
IMPORT int dsmInst ();
IMPORT int dsmNbytes ();
IMPORT int dyncast__C16__user_type_infoiRC9type_infoPvT2T3 ();
IMPORT int e ();
IMPORT int eBptr__9streambuf ();
IMPORT int eGptr__9streambuf ();
IMPORT int eNptr__9streambuf ();
IMPORT int eback__C9streambuf ();
IMPORT int ebuf__C9streambuf ();
IMPORT int eepromRead ();
IMPORT int egptr__C9streambuf ();
IMPORT int elfArmInit ();
IMPORT int elfRelocRelEntryRd ();
IMPORT int elfRelocRelaEntryRd ();
IMPORT int end8023AddressForm ();
IMPORT int endDevName ();
IMPORT int endDevTbl;
IMPORT int endEtherAddressForm ();
IMPORT int endEtherPacketAddrGet ();
IMPORT int endEtherPacketDataGet ();
IMPORT int endFindByName ();
IMPORT int endFlagsClr ();
IMPORT int endFlagsGet ();
IMPORT int endFlagsSet ();
IMPORT int endMibIfInit ();
IMPORT int endMultiLstCnt ();
IMPORT int endMultiLstFirst ();
IMPORT int endMultiLstNext ();
IMPORT int endObjFlagSet ();
IMPORT int endObjInit ();
IMPORT int endObjectUnload ();
IMPORT int endRcvRtnCall ();
IMPORT int endTxSemGive ();
IMPORT int endTxSemTake ();
IMPORT int endl__FR7ostream ();
IMPORT int ends__FR7ostream ();
IMPORT int envLibInit ();
IMPORT int envPrivateCreate ();
IMPORT int envPrivateDestroy ();
IMPORT int envShow ();
IMPORT int eof__C3ios ();
IMPORT int epptr__C9streambuf ();
IMPORT int errno;
IMPORT int errnoGet ();
IMPORT int errnoOfTaskGet ();
IMPORT int errnoOfTaskSet ();
IMPORT int errnoSet ();
IMPORT int etherMultiAdd ();
IMPORT int etherMultiDebug;
IMPORT int etherMultiDel ();
IMPORT int etherMultiGet ();
IMPORT int ether_addmulti ();
IMPORT int ether_attach ();
IMPORT int ether_delmulti ();
IMPORT int ether_ifattach ();
IMPORT int ether_input ();
IMPORT int ether_ipmulticast_max;
IMPORT int ether_ipmulticast_min;
IMPORT int ether_output ();
IMPORT int ether_sprintf ();
IMPORT int etherbroadcastaddr;
IMPORT int eventClear ();
IMPORT int eventEvtRtn;
IMPORT int eventInit ();
IMPORT int eventLibInit ();
IMPORT int eventReceive ();
IMPORT int eventRsrcSend ();
IMPORT int eventRsrcShow ();
IMPORT int eventSend ();
IMPORT int eventStart ();
IMPORT int eventTaskShow ();
IMPORT int eventTerminate ();
IMPORT int evtAction;
IMPORT int excEnterDataAbort ();
IMPORT int excEnterPrefetchAbort ();
IMPORT int excEnterSwi ();
IMPORT int excEnterUndef ();
IMPORT int excExcContinue ();
IMPORT int excExcHandle ();
IMPORT int excExcepHook;
IMPORT int excHookAdd ();
IMPORT int excInit ();
IMPORT int excIntConnect ();
IMPORT int excIntHandle ();
IMPORT int excJobAdd ();
IMPORT int excMsgQId;
IMPORT int excShowInit ();
IMPORT int excTask ();
IMPORT int excTaskId;
IMPORT int excTaskOptions;
IMPORT int excTaskPriority;
IMPORT int excTaskStackSize;
IMPORT int excVecGet ();
IMPORT int excVecInit ();
IMPORT int excVecSet ();
IMPORT int exceptions__3iosi ();
IMPORT int exceptions__C3ios ();
IMPORT int execute ();
IMPORT int exit ();
IMPORT int exp ();
IMPORT int expm1 ();
IMPORT int fabs ();
IMPORT int fail__C3ios ();
IMPORT int fat16ClustValueGet ();
IMPORT int fat16ClustValueSet ();
IMPORT int fat16Debug;
IMPORT int fat16VolMount ();
IMPORT int fatClugFac;
IMPORT int fclose ();
IMPORT int fd;
IMPORT int fdTable;
IMPORT int fd__C7filebuf ();
IMPORT int fdopen ();
IMPORT int fdprintf ();
IMPORT int feof ();
IMPORT int ferror ();
IMPORT int fflush ();
IMPORT int ffsLsb ();
IMPORT int ffsLsbTbl;
IMPORT int ffsMsb ();
IMPORT int ffsMsbTbl;
IMPORT int fgetc ();
IMPORT int fgetpos ();
IMPORT int fgets ();
IMPORT int fieldSzIncludeSign;
IMPORT int file_ptr__7filebuf ();
IMPORT int fileno ();
IMPORT int fill__3ioss ();
IMPORT int fill__C3ios ();
IMPORT int find_public_subobj__C16__user_type_infoiRC9type_infoPvT3 ();
IMPORT int fioFltInstall ();
IMPORT int fioFormatV ();
IMPORT int fioLibInit ();
IMPORT int fioRdString ();
IMPORT int fioRead ();
IMPORT int fioScanV ();
IMPORT int flAddLongToFarPointer ();
IMPORT int flBufferOf ();
IMPORT int flCall ();
IMPORT int flCreateMutex ();
IMPORT int flCurrentDate ();
IMPORT int flCurrentTime ();
IMPORT int flDelayLoop ();
IMPORT int flDontNeedVcc ();
IMPORT int flDontNeedVpp ();
IMPORT int flDosFormat ();
IMPORT int flFitInSocketWindow ();
IMPORT int flFormat ();
IMPORT int flFreeMutex ();
IMPORT int flGetMappingContext ();
IMPORT int flIdentifyFlash ();
IMPORT int flInit ();
IMPORT int flInitSockets ();
IMPORT int flInstallTimer ();
IMPORT int flIntelIdentify ();
IMPORT int flIntelSize ();
IMPORT int flIntervalRoutine ();
IMPORT int flMap ();
IMPORT int flMediaCheck ();
IMPORT int flMinClusterSize;
IMPORT int flMount ();
IMPORT int flMsecCounter;
IMPORT int flNeedVcc ();
IMPORT int flNeedVpp ();
IMPORT int flPollSemId;
IMPORT int flPollTask ();
IMPORT int flRandByte ();
IMPORT int flRegisterComponents ();
IMPORT int flResetCardChanged ();
IMPORT int flSetPowerOnCallback ();
IMPORT int flSetWindowBusWidth ();
IMPORT int flSetWindowSize ();
IMPORT int flSetWindowSpeed ();
IMPORT int flSocketNoOf ();
IMPORT int flSocketOf ();
IMPORT int flSocketSetBusy ();
IMPORT int flSysfunInit ();
IMPORT int flTakeMutex ();
IMPORT int flWriteProtected ();
IMPORT int flags__3iosUl ();
IMPORT int flags__C3ios ();
IMPORT int floatInit ();
IMPORT int floor ();
IMPORT int flush__7ostream ();
IMPORT int flush__FR7ostream ();
IMPORT int flush_all__9streambuf ();
IMPORT int flush_all_linebuffered__9streambuf ();
IMPORT int flwAmdIdentify ();
IMPORT int flwAmdMTDIdentify ();
IMPORT int flwAmdSize ();
IMPORT int fmod ();
IMPORT int fopen ();
IMPORT int formatFTL ();
IMPORT int fpArmModules;
IMPORT int fpClassId;
IMPORT int fpCtlRegName;
IMPORT int fpRegName;
IMPORT int fpTypeGet ();
IMPORT int fppArchInit ();
IMPORT int fppArchTaskCreateInit ();
IMPORT int fppCreateHookRtn;
IMPORT int fppDisplayHookRtn;
IMPORT int fppInit ();
IMPORT int fppProbe ();
IMPORT int fppRestore ();
IMPORT int fppSave ();
IMPORT int fppShowInit ();
IMPORT int fppTaskRegsCFmt;
IMPORT int fppTaskRegsDFmt;
IMPORT int fppTaskRegsGet ();
IMPORT int fppTaskRegsSet ();
IMPORT int fppTaskRegsShow ();
IMPORT int fprintf ();
IMPORT int fputc ();
IMPORT int fputs ();
IMPORT int fread ();
IMPORT int free ();
IMPORT int free_backup_area__9streambuf ();
IMPORT int freopen ();
IMPORT int frexp ();
IMPORT int fromBCD ();
IMPORT int fromUNAL ();
IMPORT int fromUNALLONG ();
IMPORT int fscanf ();
IMPORT int fseek ();
IMPORT int fsetpos ();
IMPORT int fstat ();
IMPORT int fstatfs ();
IMPORT int ftell ();
IMPORT int ftpCommand ();
IMPORT int ftpCommandEnhanced ();
IMPORT int ftpDataConnGet ();
IMPORT int ftpDataConnInit ();
IMPORT int ftpDataConnInitPassiveMode ();
IMPORT int ftpHookup ();
IMPORT int ftpLibDebugOptionsSet ();
IMPORT int ftpLogin ();
IMPORT int ftpLs ();
IMPORT int ftpReplyGet ();
IMPORT int ftpReplyGetEnhanced ();
IMPORT int ftpTransientConfigGet ();
IMPORT int ftpTransientConfigSet ();
IMPORT int ftpTransientFatalInstall ();
IMPORT int ftpXfer ();
IMPORT int ftpdDebug;
IMPORT int ftpdDelete ();
IMPORT int ftpdInit ();
IMPORT int ftpdTaskOptions;
IMPORT int ftpdTaskPriority;
IMPORT int ftpdWindowSize;
IMPORT int ftpdWorkTaskOptions;
IMPORT int ftpdWorkTaskPriority;
IMPORT int ftpdWorkTaskStackSize;
IMPORT int ftplDebug;
IMPORT int ftplPasvModeDisable;
IMPORT int ftplTransientMaxRetryCount;
IMPORT int ftplTransientRetryInterval;
IMPORT int ftpsCurrentClients;
IMPORT int ftpsMaxClients;
IMPORT int fwrite ();
IMPORT int g_AlarmInfo;
IMPORT int g_CommVer1;
IMPORT int g_CommVer2;
IMPORT int g_EventInfo;
IMPORT int g_SysInitInfo;
IMPORT int g_UpgradeFlage;
IMPORT int g_as485TestResult;
IMPORT int g_asPingResult;
IMPORT int g_by485Test;
IMPORT int g_byBuzzer;
IMPORT int g_dwAlarmPrint;
IMPORT int g_dwBdInterPrint;
IMPORT int g_dwCommTestPri;
IMPORT int g_dwEndTimeMSec;
IMPORT int g_dwEndTimeSec;
IMPORT int g_dwInterPrint;
IMPORT int g_dwPingSerialNumber;
IMPORT int g_dwPrintTrace;
IMPORT int g_dwPrintfAllLog;
IMPORT int g_dwPrintfDugLog;
IMPORT int g_dwPrintfEntryLog;
IMPORT int g_dwPrintfErrLog;
IMPORT int g_dwPrintfExitLog;
IMPORT int g_dwPrintfTimeLog;
IMPORT int g_dwRecvNormalPkg;
IMPORT int g_dwRecvUrgentPkg;
IMPORT int g_dwSend;
IMPORT int g_dwSendNormalPkg;
IMPORT int g_dwSendUrgentPkg;
IMPORT int g_dwSerialNumber;
IMPORT int g_dwSockPrint;
IMPORT int g_dwSoftPara;
IMPORT int g_dwStartTimeMSec;
IMPORT int g_dwStartTimeSec;
IMPORT int g_iDebugSwitch;
IMPORT int g_iVoltageUniteVal;
IMPORT int g_pObject;
IMPORT int g_pclaDataPackage;
IMPORT int g_psMessage;
IMPORT int g_semFileOper;
IMPORT int g_stLastSocketBuf;
IMPORT int gbump__9streambufi ();
IMPORT int gcount__7istream ();
IMPORT int get485clients ();
IMPORT int getTemperatureValue ();
IMPORT int getVoltage ();
IMPORT int get__7istream ();
IMPORT int get__7istreamPScic ();
IMPORT int get__7istreamPUcic ();
IMPORT int get__7istreamPcic ();
IMPORT int get__7istreamRSc ();
IMPORT int get__7istreamRUc ();
IMPORT int get__7istreamRc ();
IMPORT int get_column__9streambuf ();
IMPORT int getc ();
IMPORT int getchar ();
IMPORT int getcwd ();
IMPORT int getenv ();
IMPORT int gethostname ();
IMPORT int getline__7istreamPScic ();
IMPORT int getline__7istreamPUcic ();
IMPORT int getline__7istreamPcic ();
IMPORT int getmailboxes ();
IMPORT int getmodules ();
IMPORT int getpeername ();
IMPORT int gets ();
IMPORT int gets__7istreamPPcc ();
IMPORT int getsockname ();
IMPORT int getsockopt ();
IMPORT int gettcpclients ();
IMPORT int gettimers ();
IMPORT int getw ();
IMPORT int getwd ();
IMPORT int gmtime ();
IMPORT int gmtime_r ();
IMPORT int good__C3ios ();
IMPORT int gptr__C9streambuf ();
IMPORT int h ();
IMPORT int hashClassId;
IMPORT int hashFuncIterScale ();
IMPORT int hashFuncModulo ();
IMPORT int hashFuncMultiply ();
IMPORT int hashKeyCmp ();
IMPORT int hashKeyStrCmp ();
IMPORT int hashLibInit ();
IMPORT int hashTblCreate ();
IMPORT int hashTblDelete ();
IMPORT int hashTblDestroy ();
IMPORT int hashTblEach ();
IMPORT int hashTblFind ();
IMPORT int hashTblInit ();
IMPORT int hashTblPut ();
IMPORT int hashTblRemove ();
IMPORT int hashTblTerminate ();
IMPORT int hashinit ();
IMPORT int have_backup__9streambuf ();
IMPORT int have_markers__9streambuf ();
IMPORT int help ();
IMPORT int hex__FR3ios ();
IMPORT int hostAdd ();
IMPORT int hostDelete ();
IMPORT int hostGetByAddr ();
IMPORT int hostGetByName ();
IMPORT int hostInitFlag;
IMPORT int hostList;
IMPORT int hostListSem;
IMPORT int hostShow ();
IMPORT int hostTblInit ();
IMPORT int hostTblSearchByAddr ();
IMPORT int hostTblSearchByName ();
IMPORT int i ();
IMPORT int i2cReadWrite ();
IMPORT int i2cStart ();
IMPORT int i2c_ack_stat;
IMPORT int iam ();
IMPORT int icmpCfgParams;
IMPORT int icmpLibInit ();
IMPORT int icmpMaskGet ();
IMPORT int icmp_ctloutput ();
IMPORT int icmp_init ();
IMPORT int icmp_input ();
IMPORT int icmpmask;
IMPORT int icmpmaskrepl;
IMPORT int icmpstat;
IMPORT int ifAddrAdd ();
IMPORT int ifAddrDelete ();
IMPORT int ifAddrGet ();
IMPORT int ifAddrSet ();
IMPORT int ifAllRoutesDelete ();
IMPORT int ifBroadcastGet ();
IMPORT int ifBroadcastSet ();
IMPORT int ifDstAddrGet ();
IMPORT int ifDstAddrSet ();
IMPORT int ifFlagChange ();
IMPORT int ifFlagGet ();
IMPORT int ifFlagSet ();
IMPORT int ifIndexAlloc ();
IMPORT int ifIndexLibInit ();
IMPORT int ifIndexLibShutdown ();
IMPORT int ifIndexTest ();
IMPORT int ifIndexToIfName ();
IMPORT int ifIndexToIfp ();
IMPORT int ifMaskGet ();
IMPORT int ifMaskSet ();
IMPORT int ifMetricGet ();
IMPORT int ifMetricSet ();
IMPORT int ifNameToIfIndex ();
IMPORT int ifRouteDelete ();
IMPORT int ifShow ();
IMPORT int if_attach ();
IMPORT int if_dettach ();
IMPORT int if_down ();
IMPORT int if_qflush ();
IMPORT int if_slowtimo ();
IMPORT int if_slowtimoRestart ();
IMPORT int if_up ();
IMPORT int ifa_ifwithaddr ();
IMPORT int ifa_ifwithaf ();
IMPORT int ifa_ifwithdstaddr ();
IMPORT int ifa_ifwithnet ();
IMPORT int ifa_ifwithroute ();
IMPORT int ifafree ();
IMPORT int ifaof_ifpforaddr ();
IMPORT int ifconf ();
IMPORT int ifinit ();
IMPORT int ifioctl ();
IMPORT int ifnet;
IMPORT int ifpromisc ();
IMPORT int ifreset ();
IMPORT int ifreset2 ();
IMPORT int ifresetImmediate ();
IMPORT int ifunit ();
IMPORT int igmpLibInit ();
IMPORT int igmp_fasttimo ();
IMPORT int igmp_init ();
IMPORT int igmp_input ();
IMPORT int igmp_slowtimo ();
IMPORT int igmpstat;
IMPORT int ignore__7istreamii ();
IMPORT int ignore__9streambufi ();
IMPORT int in_addmulti ();
IMPORT int in_avail__9streambuf ();
IMPORT int in_backup__9streambuf ();
IMPORT int in_broadcast ();
IMPORT int in_canforward ();
IMPORT int in_cksum ();
IMPORT int in_control ();
IMPORT int in_delmulti ();
IMPORT int in_iaonnetof ();
IMPORT int in_ifaddr;
IMPORT int in_ifaddr_remove ();
IMPORT int in_ifinit ();
IMPORT int in_ifscrub ();
IMPORT int in_interfaces;
IMPORT int in_lnaof ();
IMPORT int in_localaddr ();
IMPORT int in_losing ();
IMPORT int in_netof ();
IMPORT int in_pcballoc ();
IMPORT int in_pcbbind ();
IMPORT int in_pcbconnect ();
IMPORT int in_pcbdetach ();
IMPORT int in_pcbdisconnect ();
IMPORT int in_pcbinshash ();
IMPORT int in_pcbladdr ();
IMPORT int in_pcblookup ();
IMPORT int in_pcblookuphash ();
IMPORT int in_pcbnotify ();
IMPORT int in_pcbrehash ();
IMPORT int in_rtchange ();
IMPORT int in_setpeeraddr ();
IMPORT int in_setsockaddr ();
IMPORT int in_socktrim ();
IMPORT int index ();
IMPORT int inet_addr ();
IMPORT int inet_aton ();
IMPORT int inet_lnaof ();
IMPORT int inet_makeaddr ();
IMPORT int inet_makeaddr_b ();
IMPORT int inet_netmatch ();
IMPORT int inet_netof ();
IMPORT int inet_netof_string ();
IMPORT int inet_network ();
IMPORT int inet_ntoa ();
IMPORT int inet_ntoa_b ();
IMPORT int inetctlerrmap;
IMPORT int inetdomain;
IMPORT int inetstatShow ();
IMPORT int inetsw;
IMPORT int inflate ();
IMPORT int inflateCksum;
IMPORT int initDog ();
IMPORT int init__3iosP9streambufP7ostream ();
IMPORT int init__7filebuf ();
IMPORT int initstate ();
IMPORT int input_ipaddr;
IMPORT int intCnt;
IMPORT int intConnect ();
IMPORT int intContext ();
IMPORT int intCount ();
IMPORT int intDemuxErrorCount;
IMPORT int intDisable ();
IMPORT int intEnable ();
IMPORT int intEnt ();
IMPORT int intExit ();
IMPORT int intIFLock ();
IMPORT int intIFUnlock ();
IMPORT int intIntRtnNonPreempt ();
IMPORT int intIntRtnPreempt ();
IMPORT int intLevelSet ();
IMPORT int intLibInit ();
IMPORT int intLock ();
IMPORT int intLockLevelGet ();
IMPORT int intLockLevelSet ();
IMPORT int intRegsLock ();
IMPORT int intRegsUnlock ();
IMPORT int intRestrict ();
IMPORT int intUninitVecSet ();
IMPORT int intUnlock ();
IMPORT int intVBRSet ();
IMPORT int intVecBaseGet ();
IMPORT int intVecBaseSet ();
IMPORT int intVecTableWriteProtect ();
IMPORT int ioDefDevGet ();
IMPORT int ioDefDirGet ();
IMPORT int ioDefPath;
IMPORT int ioDefPathCat ();
IMPORT int ioDefPathGet ();
IMPORT int ioDefPathSet ();
IMPORT int ioFullFileNameGet ();
IMPORT int ioGlobalStdGet ();
IMPORT int ioGlobalStdSet ();
IMPORT int ioHelp ();
IMPORT int ioMaxLinkLevels;
IMPORT int ioTaskStdGet ();
IMPORT int ioTaskStdSet ();
IMPORT int io_defs__;
IMPORT int ioctl ();
IMPORT int iosClose ();
IMPORT int iosCreate ();
IMPORT int iosDelete ();
IMPORT int iosDevAdd ();
IMPORT int iosDevDelete ();
IMPORT int iosDevFind ();
IMPORT int iosDevShow ();
IMPORT int iosDrvInstall ();
IMPORT int iosDrvRemove ();
IMPORT int iosDrvShow ();
IMPORT int iosDvList;
IMPORT int iosFdDevFind ();
IMPORT int iosFdFree ();
IMPORT int iosFdFreeHookRtn;
IMPORT int iosFdNew ();
IMPORT int iosFdNewHookRtn;
IMPORT int iosFdSet ();
IMPORT int iosFdShow ();
IMPORT int iosFdValue ();
IMPORT int iosInit ();
IMPORT int iosIoctl ();
IMPORT int iosLibInitialized;
IMPORT int iosNextDevGet ();
IMPORT int iosOpen ();
IMPORT int iosRead ();
IMPORT int iosShowInit ();
IMPORT int iosWrite ();
IMPORT int ipAttach ();
IMPORT int ipCfgParams;
IMPORT int ipDetach ();
IMPORT int ipDrvCtrl;
IMPORT int ipEtherResolvRtn ();
IMPORT int ipHeaderCreate ();
IMPORT int ipHeaderVerify ();
IMPORT int ipLibInit ();
IMPORT int ipMaxUnits;
IMPORT int ipMuxCookieGet ();
IMPORT int ipStrongEnded;
IMPORT int ipTkError ();
IMPORT int ipToEtherMCastMap ();
IMPORT int ip_ctloutput ();
IMPORT int ip_defttl;
IMPORT int ip_dooptions ();
IMPORT int ip_drain ();
IMPORT int ip_forward ();
IMPORT int ip_freef ();
IMPORT int ip_freemoptions ();
IMPORT int ip_getmoptions ();
IMPORT int ip_id;
IMPORT int ip_init ();
IMPORT int ip_mloopback ();
IMPORT int ip_nhops;
IMPORT int ip_optcopy ();
IMPORT int ip_output ();
IMPORT int ip_pcbopts ();
IMPORT int ip_protox;
IMPORT int ip_rtaddr ();
IMPORT int ip_slowtimo ();
IMPORT int ip_stripoptions ();
IMPORT int ipforward_rt;
IMPORT int ipfragttl;
IMPORT int ipfx0__7istream ();
IMPORT int ipfx1__7istream ();
IMPORT int ipfx__7istreami ();
IMPORT int ipintr ();
IMPORT int ipintrq;
IMPORT int ipq;
IMPORT int ipqmaxlen;
IMPORT int ipstat;
IMPORT int ipstatShow ();
IMPORT int iptime ();
IMPORT int is_open__3ios ();
IMPORT int is_open__C7filebuf ();
IMPORT int is_reading__7filebuf ();
IMPORT int isalnum ();
IMPORT int isalpha ();
IMPORT int isatty ();
IMPORT int iscntrl ();
IMPORT int isdigit ();
IMPORT int isfx__7istream ();
IMPORT int isgraph ();
IMPORT int islower ();
IMPORT int isprint ();
IMPORT int ispunct ();
IMPORT int isspace ();
IMPORT int istreambuf__C7istream ();
IMPORT int isupper ();
IMPORT int isxdigit ();
IMPORT int ixdr_get_long ();
IMPORT int kernelInit ();
IMPORT int kernelIsIdle;
IMPORT int kernelState;
IMPORT int kernelTimeSlice ();
IMPORT int kernelVersion ();
IMPORT int kill ();
IMPORT int ksleep ();
IMPORT int l ();
IMPORT int labs ();
IMPORT int ld ();
IMPORT int ldCommonMatchAll;
IMPORT int ldexp ();
IMPORT int ldiv ();
IMPORT int ldiv_r ();
IMPORT int ledClose ();
IMPORT int ledControl ();
IMPORT int ledId;
IMPORT int ledOpen ();
IMPORT int ledRead ();
IMPORT int lexActions ();
IMPORT int lexClass;
IMPORT int lexNclasses;
IMPORT int lexStateTable;
IMPORT int libiberty_demanglers;
IMPORT int linebuffered__9streambuf ();
IMPORT int linebuffered__9streambufi ();
IMPORT int linkDataSyms;
IMPORT int linkSyms;
IMPORT int link_rtrequest ();
IMPORT int linkedCtorsInitialized;
IMPORT int listen ();
IMPORT int lkAddr ();
IMPORT int lkup ();
IMPORT int ll ();
IMPORT int llinfo_arp;
IMPORT int llr ();
IMPORT int loadCommonManage ();
IMPORT int loadCommonMatch ();
IMPORT int loadElfInit ();
IMPORT int loadModule ();
IMPORT int loadModuleAt ();
IMPORT int loadModuleAtSym ();
IMPORT int loadModuleGet ();
IMPORT int loadRoutine;
IMPORT int loadSegmentsAllocate ();
IMPORT int load_fpga_ALTERA ();
IMPORT int load_fpga_LATTICE ();
IMPORT int loattach ();
IMPORT int localToGlobalOffset;
IMPORT int localeconv ();
IMPORT int localtime ();
IMPORT int localtime_r ();
IMPORT int lock__FR7istream ();
IMPORT int lock__FR7ostream ();
IMPORT int log ();
IMPORT int log10 ();
IMPORT int logFdAdd ();
IMPORT int logFdDelete ();
IMPORT int logFdFromRlogin;
IMPORT int logFdSet ();
IMPORT int logInit ();
IMPORT int logMsg ();
IMPORT int logShow ();
IMPORT int logTask ();
IMPORT int logTaskId;
IMPORT int logTaskOptions;
IMPORT int logTaskPriority;
IMPORT int logTaskStackSize;
IMPORT int loginDefaultEncrypt ();
IMPORT int loginEncryptInstall ();
IMPORT int loginInit ();
IMPORT int loginPrompt ();
IMPORT int loginStringSet ();
IMPORT int loginTimeOutInSecond;
IMPORT int loginUserAdd ();
IMPORT int loginUserDelete ();
IMPORT int loginUserShow ();
IMPORT int loginUserVerify ();
IMPORT int loginVerifyRtn;
IMPORT int logout ();
IMPORT int loif;
IMPORT int longjmp ();
IMPORT int looutput ();
IMPORT int ls ();
IMPORT int lseek ();
IMPORT int lsr ();
IMPORT int lstAdd ();
IMPORT int lstConcat ();
IMPORT int lstCount ();
IMPORT int lstDelete ();
IMPORT int lstExtract ();
IMPORT int lstFind ();
IMPORT int lstFirst ();
IMPORT int lstFree ();
IMPORT int lstGet ();
IMPORT int lstInit ();
IMPORT int lstInsert ();
IMPORT int lstLast ();
IMPORT int lstLibInit ();
IMPORT int lstNStep ();
IMPORT int lstNext ();
IMPORT int lstNth ();
IMPORT int lstPrevious ();
IMPORT int m ();
IMPORT int mBufClGet ();
IMPORT int mCastHashInfo;
IMPORT int mCastHashTblSize;
IMPORT int mClBlkConfig;
IMPORT int mHdrClGet ();
IMPORT int mPrivRouteEntryAdd ();
IMPORT int mPrivRouteEntryDelete ();
IMPORT int mRegs ();
IMPORT int mRouteAdd ();
IMPORT int mRouteDelete ();
IMPORT int mRouteEntryAdd ();
IMPORT int mRouteEntryDelete ();
IMPORT int mRouteShow ();
IMPORT int m_adj ();
IMPORT int m_cat ();
IMPORT int m_devget ();
IMPORT int m_getclr ();
IMPORT int m_prepend ();
IMPORT int m_pullup ();
IMPORT int malloc ();
IMPORT int mask_rnhead;
IMPORT int mathSoftInit ();
IMPORT int maxDrivers;
IMPORT int maxFiles;
IMPORT int max_hdr;
IMPORT int max_keylen;
IMPORT int max_linkhdr;
IMPORT int max_protohdr;
IMPORT int mbinit ();
IMPORT int mblen ();
IMPORT int mbstowcs ();
IMPORT int mbtowc ();
IMPORT int mbufShow ();
IMPORT int mcastHashInit ();
IMPORT int mcastHashTblDelete ();
IMPORT int mcastHashTblInsert ();
IMPORT int mcastHashTblLookup ();
IMPORT int memAddToPool ();
IMPORT int memDefaultAlignment;
IMPORT int memFindMax ();
IMPORT int memInit ();
IMPORT int memLibInit ();
IMPORT int memOptionsSet ();
IMPORT int memPartAddToPool ();
IMPORT int memPartAlignedAlloc ();
IMPORT int memPartAlloc ();
IMPORT int memPartAllocErrorRtn;
IMPORT int memPartBlockErrorRtn;
IMPORT int memPartBlockIsValid ();
IMPORT int memPartClassId;
IMPORT int memPartCreate ();
IMPORT int memPartFindMax ();
IMPORT int memPartFree ();
IMPORT int memPartInfoGet ();
IMPORT int memPartInit ();
IMPORT int memPartInstClassId;
IMPORT int memPartLibInit ();
IMPORT int memPartOptionsDefault;
IMPORT int memPartOptionsSet ();
IMPORT int memPartRealloc ();
IMPORT int memPartSemInitRtn;
IMPORT int memPartShow ();
IMPORT int memShow ();
IMPORT int memShowInit ();
IMPORT int memSysPartId;
IMPORT int memTest ();
IMPORT int memalign ();
IMPORT int memchr ();
IMPORT int memcmp ();
IMPORT int memcpy ();
IMPORT int memdebug ();
IMPORT int memmove ();
IMPORT int memset ();
IMPORT int memshow ();
IMPORT int mib2ErrorAdd ();
IMPORT int mib2Init ();
IMPORT int mkdir ();
IMPORT int mktime ();
IMPORT int mmtest ();
IMPORT int mmuArm920tADisable ();
IMPORT int mmuArm920tAEnable ();
IMPORT int mmuArm920tDacrSet ();
IMPORT int mmuArm920tLibInstall ();
IMPORT int mmuArm920tTLBIDFlushAll ();
IMPORT int mmuArm920tTLBIDFlushEntry ();
IMPORT int mmuArm920tTtbrSet ();
IMPORT int mmuCrGet;
IMPORT int mmuHardCrGet ();
IMPORT int mmuLibFuncs;
IMPORT int mmuModifyCr;
IMPORT int mmuModifyHardCr ();
IMPORT int mmuModifySoftCr ();
IMPORT int mmuPageBlockSize;
IMPORT int mmuPhysAddrShift;
IMPORT int mmuReadId ();
IMPORT int mmuSoftCrGet ();
IMPORT int mmuStateTransArray;
IMPORT int mmuStateTransArraySize;
IMPORT int modf ();
IMPORT int moduleCheck ();
IMPORT int moduleClassId;
IMPORT int moduleCreate ();
IMPORT int moduleCreateHookAdd ();
IMPORT int moduleCreateHookDelete ();
IMPORT int moduleDelete ();
IMPORT int moduleEach ();
IMPORT int moduleFindByGroup ();
IMPORT int moduleFindByName ();
IMPORT int moduleFindByNameAndPath ();
IMPORT int moduleFlagsGet ();
IMPORT int moduleIdFigure ();
IMPORT int moduleIdListGet ();
IMPORT int moduleInfoGet ();
IMPORT int moduleInit ();
IMPORT int moduleLibInit ();
IMPORT int moduleNameGet ();
IMPORT int moduleSegAdd ();
IMPORT int moduleSegEach ();
IMPORT int moduleSegFirst ();
IMPORT int moduleSegGet ();
IMPORT int moduleSegNext ();
IMPORT int moduleShow ();
IMPORT int moduleTerminate ();
IMPORT int mountFTL ();
IMPORT int msgQClassId;
IMPORT int msgQCreate ();
IMPORT int msgQDelete ();
IMPORT int msgQDistInfoGetRtn;
IMPORT int msgQDistNumMsgsRtn;
IMPORT int msgQDistReceiveRtn;
IMPORT int msgQDistSendRtn;
IMPORT int msgQDistShowRtn;
IMPORT int msgQEvLibInit ();
IMPORT int msgQEvStart ();
IMPORT int msgQEvStop ();
IMPORT int msgQInfoGet ();
IMPORT int msgQInit ();
IMPORT int msgQInstClassId;
IMPORT int msgQLibInit ();
IMPORT int msgQNumMsgs ();
IMPORT int msgQReceive ();
IMPORT int msgQSend ();
IMPORT int msgQShow ();
IMPORT int msgQShowInit ();
IMPORT int msgQSmInfoGetRtn;
IMPORT int msgQSmNumMsgsRtn;
IMPORT int msgQSmReceiveRtn;
IMPORT int msgQSmSendRtn;
IMPORT int msgQSmShowRtn;
IMPORT int msgQTerminate ();
IMPORT int mtdTable;
IMPORT int mutexOptionsHostLib;
IMPORT int mutexOptionsIosLib;
IMPORT int mutexOptionsLogLib;
IMPORT int mutexOptionsMemLib;
IMPORT int mutexOptionsNetDrv;
IMPORT int mutexOptionsSelectLib;
IMPORT int mutexOptionsSymLib;
IMPORT int mutexOptionsTyLib;
IMPORT int mutexOptionsUnixLib;
IMPORT int mutexOptionsVmBaseLib;
IMPORT int muxAddrResFuncAdd ();
IMPORT int muxAddrResFuncDel ();
IMPORT int muxAddrResFuncGet ();
IMPORT int muxAddressForm ();
IMPORT int muxBibLock;
IMPORT int muxBind ();
IMPORT int muxDevExists ();
IMPORT int muxDevLoad ();
IMPORT int muxDevStart ();
IMPORT int muxDevStartAll ();
IMPORT int muxDevStop ();
IMPORT int muxDevStopAll ();
IMPORT int muxDevUnload ();
IMPORT int muxError ();
IMPORT int muxIoctl ();
IMPORT int muxLibInit ();
IMPORT int muxLinkHeaderCreate ();
IMPORT int muxMCastAddrAdd ();
IMPORT int muxMCastAddrDel ();
IMPORT int muxMCastAddrGet ();
IMPORT int muxMaxBinds;
IMPORT int muxPacketAddrGet ();
IMPORT int muxPacketDataGet ();
IMPORT int muxPollDevAdd ();
IMPORT int muxPollDevDel ();
IMPORT int muxPollDevStat ();
IMPORT int muxPollEnd ();
IMPORT int muxPollReceive ();
IMPORT int muxPollSend ();
IMPORT int muxPollStart ();
IMPORT int muxPollTask ();
IMPORT int muxReceive ();
IMPORT int muxSend ();
IMPORT int muxShow ();
IMPORT int muxTaskDelayGet ();
IMPORT int muxTaskDelaySet ();
IMPORT int muxTaskPriorityGet ();
IMPORT int muxTaskPrioritySet ();
IMPORT int muxTkBibInit ();
IMPORT int muxTkBibShow ();
IMPORT int muxTkBind ();
IMPORT int muxTkBindUpdate ();
IMPORT int muxTkCookieGet ();
IMPORT int muxTkDebug;
IMPORT int muxTkDevLoadUpdate ();
IMPORT int muxTkDrvCheck ();
IMPORT int muxTkPollReceive ();
IMPORT int muxTkPollReceive2 ();
IMPORT int muxTkPollSend ();
IMPORT int muxTkReceive ();
IMPORT int muxTkSend ();
IMPORT int muxTkUnbindUpdate ();
IMPORT int muxTkUnloadUpdate ();
IMPORT int muxTxRestart ();
IMPORT int muxUnbind ();
IMPORT int mv ();
IMPORT int name__C9type_info ();
IMPORT int namelessPrefix;
IMPORT int netBufLibInit ();
IMPORT int netClBlkFree ();
IMPORT int netClBlkGet ();
IMPORT int netClBlkJoin ();
IMPORT int netClFree ();
IMPORT int netClPoolIdGet ();
IMPORT int netClusterGet ();
IMPORT int netDevCreate ();
IMPORT int netDevCreate2 ();
IMPORT int netDrv ();
IMPORT int netDrvDebugLevelSet ();
IMPORT int netDrvFileDoesNotExist ();
IMPORT int netDrvFileDoesNotExistInstall ();
IMPORT int netErrnoSet ();
IMPORT int netHelp ();
IMPORT int netJobAdd ();
IMPORT int netLibGeneralInit ();
IMPORT int netLibInit ();
IMPORT int netLibInitialized;
IMPORT int netLsByName ();
IMPORT int netMblkChainDup ();
IMPORT int netMblkClChainFree ();
IMPORT int netMblkClFree ();
IMPORT int netMblkClGet ();
IMPORT int netMblkClJoin ();
IMPORT int netMblkDup ();
IMPORT int netMblkFree ();
IMPORT int netMblkGet ();
IMPORT int netMblkOffsetToBufCopy ();
IMPORT int netMblkToBufCopy ();
IMPORT int netPoolDelete ();
IMPORT int netPoolInit ();
IMPORT int netPoolKheapInit ();
IMPORT int netPoolShow ();
IMPORT int netShowInit ();
IMPORT int netStackDataPoolShow ();
IMPORT int netStackSysPoolShow ();
IMPORT int netTask ();
IMPORT int netTaskId;
IMPORT int netTaskOptions;
IMPORT int netTaskPriority;
IMPORT int netTaskSemId;
IMPORT int netTaskStackSize;
IMPORT int netTupleGet ();
IMPORT int netTupleGet2 ();
IMPORT int netTypeAdd ();
IMPORT int netTypeDelete ();
IMPORT int netTypeInit ();
IMPORT int net_sysctl ();
IMPORT int noOfDrives;
IMPORT int noOfMTDs;
IMPORT int noOfTLs;
IMPORT int nothrow ();
IMPORT int objAlloc ();
IMPORT int objAllocExtra ();
IMPORT int objCoreInit ();
IMPORT int objCoreTerminate ();
IMPORT int objFree ();
IMPORT int objShow ();
IMPORT int oct__FR3ios ();
IMPORT int open ();
IMPORT int open__7filebufPCcT1 ();
IMPORT int open__7filebufPCcii ();
IMPORT int opendir ();
IMPORT int opfx__7ostream ();
IMPORT int osfx__7ostream ();
IMPORT int ostreambuf__C7ostream ();
IMPORT int out_waiting__9streambuf ();
IMPORT int overflow__7filebufi ();
IMPORT int overflow__9streambufi ();
IMPORT int pEndPktDev;
IMPORT int pFppTaskIdPrevious;
IMPORT int pInPkt;
IMPORT int pJobPool;
IMPORT int pMibRtn;
IMPORT int pRootMemStart;
IMPORT int pSockFdMap;
IMPORT int pTaskLastDspTcb;
IMPORT int pTaskLastFpTcb;
IMPORT int pTcpRandHook;
IMPORT int pTcpstates;
IMPORT int pWdbMemRegions;
IMPORT int pWdbRtIf;
IMPORT int pWvNetEventMap;
IMPORT int padn__9streambufci ();
IMPORT int panic ();
IMPORT int panicSuspend;
IMPORT int pathBuild ();
IMPORT int pathCat ();
IMPORT int pathCondense ();
IMPORT int pathLastName ();
IMPORT int pathLastNamePtr ();
IMPORT int pathParse ();
IMPORT int pathSplit ();
IMPORT int pause ();
IMPORT int pbackfail__9streambufi ();
IMPORT int pbase__C9streambuf ();
IMPORT int pbump__9streambufi ();
IMPORT int pc ();
IMPORT int peek__7istream ();
IMPORT int period ();
IMPORT int periodRun ();
IMPORT int perror ();
IMPORT int pfctlinput ();
IMPORT int pffindproto ();
IMPORT int pffindtype ();
IMPORT int ping ();
IMPORT int pingLibInit ();
IMPORT int pipeDevCreate ();
IMPORT int pipeDevDelete ();
IMPORT int pipeDrv ();
IMPORT int pipeMsgQOptions;
IMPORT int pow ();
IMPORT int ppGlobalEnviron;
IMPORT int pptr__C9streambuf ();
IMPORT int precision__3iosi ();
IMPORT int precision__C3ios ();
IMPORT int print64 ();
IMPORT int print64Fine ();
IMPORT int print64Mult ();
IMPORT int print64Row ();
IMPORT int printErr ();
IMPORT int printErrno ();
IMPORT int printExc ();
IMPORT int printLogo ();
IMPORT int printf ();
IMPORT int proxyArpHook;
IMPORT int proxyBroadcastHook;
IMPORT int psrShow ();
IMPORT int ptyDevCreate ();
IMPORT int ptyDevRemove ();
IMPORT int ptyDrv ();
IMPORT int pubseekoff__9streambuflQ23ios8seek_diri ();
IMPORT int pubseekpos__9streambufli ();
IMPORT int put__7ostreamSc ();
IMPORT int put__7ostreamUc ();
IMPORT int put__7ostreamc ();
IMPORT int put_mode__9streambuf ();
IMPORT int putback__7istreamc ();
IMPORT int putc ();
IMPORT int putchar ();
IMPORT int putenv ();
IMPORT int puts ();
IMPORT int putw ();
IMPORT int pwd ();
IMPORT int qAdvance ();
IMPORT int qCalibrate ();
IMPORT int qCreate ();
IMPORT int qDelete ();
IMPORT int qEach ();
IMPORT int qFifoClassId;
IMPORT int qFifoCreate ();
IMPORT int qFifoDelete ();
IMPORT int qFifoEach ();
IMPORT int qFifoGet ();
IMPORT int qFifoInfo ();
IMPORT int qFifoInit ();
IMPORT int qFifoPut ();
IMPORT int qFifoRemove ();
IMPORT int qFirst ();
IMPORT int qGet ();
IMPORT int qGetExpired ();
IMPORT int qInfo ();
IMPORT int qInit ();
IMPORT int qJobClassId;
IMPORT int qJobCreate ();
IMPORT int qJobDelete ();
IMPORT int qJobEach ();
IMPORT int qJobGet ();
IMPORT int qJobInfo ();
IMPORT int qJobInit ();
IMPORT int qJobPut ();
IMPORT int qJobTerminate ();
IMPORT int qKey ();
IMPORT int qPriBMapClassId;
IMPORT int qPriBMapCreate ();
IMPORT int qPriBMapDelete ();
IMPORT int qPriBMapEach ();
IMPORT int qPriBMapGet ();
IMPORT int qPriBMapInfo ();
IMPORT int qPriBMapInit ();
IMPORT int qPriBMapKey ();
IMPORT int qPriBMapListCreate ();
IMPORT int qPriBMapListDelete ();
IMPORT int qPriBMapPut ();
IMPORT int qPriBMapRemove ();
IMPORT int qPriBMapResort ();
IMPORT int qPriListAdvance ();
IMPORT int qPriListCalibrate ();
IMPORT int qPriListClassId;
IMPORT int qPriListCreate ();
IMPORT int qPriListDelete ();
IMPORT int qPriListEach ();
IMPORT int qPriListFromTailClassId;
IMPORT int qPriListGet ();
IMPORT int qPriListGetExpired ();
IMPORT int qPriListInfo ();
IMPORT int qPriListInit ();
IMPORT int qPriListKey ();
IMPORT int qPriListPut ();
IMPORT int qPriListPutFromTail ();
IMPORT int qPriListRemove ();
IMPORT int qPriListResort ();
IMPORT int qPriListTerminate ();
IMPORT int qPut ();
IMPORT int qRemove ();
IMPORT int qResort ();
IMPORT int qTerminate ();
IMPORT int qsort ();
IMPORT int r0 ();
IMPORT int r1 ();
IMPORT int r10 ();
IMPORT int r11 ();
IMPORT int r12 ();
IMPORT int r13 ();
IMPORT int r14 ();
IMPORT int r2 ();
IMPORT int r3 ();
IMPORT int r4 ();
IMPORT int r5 ();
IMPORT int r6 ();
IMPORT int r7 ();
IMPORT int r8 ();
IMPORT int r9 ();
IMPORT int raise ();
IMPORT int ramDevCreate ();
IMPORT int ramDrv ();
IMPORT int rand ();
IMPORT int random ();
IMPORT int rawIpLibInit ();
IMPORT int rawLibInit ();
IMPORT int rcmd ();
IMPORT int rdbuf__3iosP9streambuf ();
IMPORT int rdbuf__C3ios ();
IMPORT int rdstate__C3ios ();
IMPORT int read ();
IMPORT int read__7istreamPSci ();
IMPORT int read__7istreamPUci ();
IMPORT int read__7istreamPci ();
IMPORT int read__7istreamPvi ();
IMPORT int readable__3ios ();
IMPORT int readdir ();
IMPORT int readv ();
IMPORT int readyQBMap;
IMPORT int readyQHead;
IMPORT int realloc ();
IMPORT int reallocate__t23__malloc_alloc_template1i0PvUlUl ();
IMPORT int reallocate__t24__default_alloc_template2b1i0PvUlUl ();
IMPORT int reboot ();
IMPORT int rebootHookAdd ();
IMPORT int recv ();
IMPORT int recvfrom ();
IMPORT int recvmsg ();
IMPORT int redirInFd;
IMPORT int redirOutFd;
IMPORT int remCurIdGet ();
IMPORT int remCurIdSet ();
IMPORT int remLastResvPort;
IMPORT int remLibInit ();
IMPORT int remStdErrSetupTimeout;
IMPORT int remove ();
IMPORT int rename ();
IMPORT int repeat ();
IMPORT int repeatRun ();
IMPORT int replaceFATsector ();
IMPORT int reschedule ();
IMPORT int resetflash ();
IMPORT int restart485test ();
IMPORT int restartTaskName;
IMPORT int restartTaskOptions;
IMPORT int restartTaskPriority;
IMPORT int restartTaskStackSize;
IMPORT int rewind ();
IMPORT int rewinddir ();
IMPORT int rindex ();
IMPORT int rip_ctloutput ();
IMPORT int rip_init ();
IMPORT int rip_input ();
IMPORT int rip_output ();
IMPORT int rip_recvspace;
IMPORT int rip_sendspace;
IMPORT int rip_usrreq ();
IMPORT int rm ();
IMPORT int rmdir ();
IMPORT int rn_addmask ();
IMPORT int rn_addroute ();
IMPORT int rn_delete ();
IMPORT int rn_destroyhead ();
IMPORT int rn_init ();
IMPORT int rn_inithead ();
IMPORT int rn_insert ();
IMPORT int rn_lookup ();
IMPORT int rn_match ();
IMPORT int rn_mkfreelist;
IMPORT int rn_newpair ();
IMPORT int rn_refines ();
IMPORT int rn_search ();
IMPORT int rn_search_m ();
IMPORT int rn_walksubtree ();
IMPORT int rn_walktree ();
IMPORT int rngBufGet ();
IMPORT int rngBufPut ();
IMPORT int rngCreate ();
IMPORT int rngDelete ();
IMPORT int rngFlush ();
IMPORT int rngFreeBytes ();
IMPORT int rngIsEmpty ();
IMPORT int rngIsFull ();
IMPORT int rngMoveAhead ();
IMPORT int rngNBytes ();
IMPORT int rngPutAhead ();
IMPORT int rootMemNBytes;
IMPORT int rootTaskId;
IMPORT int roundRobinOn;
IMPORT int roundRobinSlice;
IMPORT int routeAdd ();
IMPORT int routeAgeSet ();
IMPORT int routeCmd ();
IMPORT int routeDelete ();
IMPORT int routeDrain ();
IMPORT int routeEntryFill ();
IMPORT int routeMetricSet ();
IMPORT int routeNetAdd ();
IMPORT int routeShow ();
IMPORT int routeSwap ();
IMPORT int route_init ();
IMPORT int routestatShow ();
IMPORT int rresvport ();
IMPORT int rtIfaceMsgHook;
IMPORT int rtMem ();
IMPORT int rtMissMsgHook;
IMPORT int rtNewAddrMsgHook;
IMPORT int rt_fixdelete ();
IMPORT int rt_maskedcopy ();
IMPORT int rt_setgate ();
IMPORT int rt_tables;
IMPORT int rtable_init ();
IMPORT int rtalloc ();
IMPORT int rtalloc1 ();
IMPORT int rtalloc2 ();
IMPORT int rtfree ();
IMPORT int rtinit ();
IMPORT int rtioctl ();
IMPORT int rtmodified;
IMPORT int rtredirect ();
IMPORT int rtrequest ();
IMPORT int rtrequestAddEqui ();
IMPORT int rtrequestDelEqui ();
IMPORT int rtstat;
IMPORT int rttrash;
IMPORT int runtimeName;
IMPORT int runtimeVersion;
IMPORT int s ();
IMPORT int sCurI2cPort;
IMPORT int saving__12streammarker ();
IMPORT int sb_lock ();
IMPORT int sb_max;
IMPORT int sbappend ();
IMPORT int sbappendaddr ();
IMPORT int sbappendcontrol ();
IMPORT int sbappendrecord ();
IMPORT int sbcompress ();
IMPORT int sbdrop ();
IMPORT int sbdroprecord ();
IMPORT int sbflush ();
IMPORT int sbinsertoob ();
IMPORT int sbrelease ();
IMPORT int sbreserve ();
IMPORT int sbseldequeue ();
IMPORT int sbselqueue ();
IMPORT int sbumpc__9streambuf ();
IMPORT int sbwait ();
IMPORT int sbwakeup ();
IMPORT int scalbn ();
IMPORT int scanCharSet ();
IMPORT int scanField ();
IMPORT int scan__7istreamPCce ();
IMPORT int scan__9streambufPCce ();
IMPORT int scanf ();
IMPORT int secEndLoad ();
IMPORT int seekg__7istreaml ();
IMPORT int seekg__7istreamlQ23ios8seek_dir ();
IMPORT int seekmark__9streambufR12streammarkeri ();
IMPORT int seekoff__7filebuflQ23ios8seek_diri ();
IMPORT int seekoff__9streambuflQ23ios8seek_diri ();
IMPORT int seekp__7ostreaml ();
IMPORT int seekp__7ostreamlQ23ios8seek_dir ();
IMPORT int seekpos__9streambufli ();
IMPORT int selNodeAdd ();
IMPORT int selNodeDelete ();
IMPORT int selTaskDeleteHookAdd ();
IMPORT int selWakeup ();
IMPORT int selWakeupAll ();
IMPORT int selWakeupListInit ();
IMPORT int selWakeupListLen ();
IMPORT int selWakeupListTerm ();
IMPORT int selWakeupType ();
IMPORT int select ();
IMPORT int selectInit ();
IMPORT int semBCoreInit ();
IMPORT int semBCreate ();
IMPORT int semBGive ();
IMPORT int semBGiveDefer ();
IMPORT int semBInit ();
IMPORT int semBLibInit ();
IMPORT int semBTake ();
IMPORT int semCCoreInit ();
IMPORT int semCCreate ();
IMPORT int semCGive ();
IMPORT int semCGiveDefer ();
IMPORT int semCInit ();
IMPORT int semCLibInit ();
IMPORT int semCTake ();
IMPORT int semClass;
IMPORT int semClassId;
IMPORT int semClear ();
IMPORT int semDelete ();
IMPORT int semDestroy ();
IMPORT int semEvIsFreeTbl;
IMPORT int semEvLibInit ();
IMPORT int semEvRsrcSend ();
IMPORT int semEvStart ();
IMPORT int semEvStop ();
IMPORT int semFlush ();
IMPORT int semFlushDefer ();
IMPORT int semFlushDeferTbl;
IMPORT int semFlushTbl;
IMPORT int semGive ();
IMPORT int semGiveDefer ();
IMPORT int semGiveDeferTbl;
IMPORT int semGiveTbl;
IMPORT int semI2cLock;
IMPORT int semInfo ();
IMPORT int semInstClass;
IMPORT int semInstClassId;
IMPORT int semIntRestrict ();
IMPORT int semInvalid ();
IMPORT int semLibInit ();
IMPORT int semMCoreInit ();
IMPORT int semMCreate ();
IMPORT int semMGive ();
IMPORT int semMGiveForce ();
IMPORT int semMGiveKern ();
IMPORT int semMGiveKernWork;
IMPORT int semMInit ();
IMPORT int semMLibInit ();
IMPORT int semMPendQPut ();
IMPORT int semMTake ();
IMPORT int semOTake ();
IMPORT int semQFlush ();
IMPORT int semQFlushDefer ();
IMPORT int semQGet ();
IMPORT int semQInit ();
IMPORT int semQPut ();
IMPORT int semShow ();
IMPORT int semShowInit ();
IMPORT int semSmInfoRtn;
IMPORT int semSmShowRtn;
IMPORT int semSpiLock;
IMPORT int semTake ();
IMPORT int semTakeTbl;
IMPORT int semTerminate ();
IMPORT int semVoltage;
IMPORT int send ();
IMPORT int sendmsg ();
IMPORT int sendpackage ();
IMPORT int sendto ();
IMPORT int set__3iosi ();
IMPORT int set_column__9streambufi ();
IMPORT int set_cplus_marker_for_demangling ();
IMPORT int set_if_addr ();
IMPORT int set_new_handler__FPFv_v ();
IMPORT int set_offset__12streammarkeri ();
IMPORT int set_terminate__FPFv_v ();
IMPORT int set_unexpected__FPFv_v ();
IMPORT int setb__9streambufPcT1i ();
IMPORT int setbuf ();
IMPORT int setbuf__7filebufPci ();
IMPORT int setbuf__9streambufPci ();
IMPORT int setbuffer ();
IMPORT int setf__3iosUl ();
IMPORT int setf__3iosUlUl ();
IMPORT int setg__9streambufPcN21 ();
IMPORT int sethostname ();
IMPORT int setjmp ();
IMPORT int setlinebuf ();
IMPORT int setlocale ();
IMPORT int setp__9streambufPcT1 ();
IMPORT int setsockopt ();
IMPORT int setstate ();
IMPORT int setstate__3iosi ();
IMPORT int setvbuf ();
IMPORT int sfpDoubleNormalize ();
IMPORT int sfpDoubleNormalize2 ();
IMPORT int sfpDoubleSetup ();
IMPORT int sfpFloatNormalize ();
IMPORT int sfpFloatSetup ();
IMPORT int sgetc__9streambuf ();
IMPORT int sgetn__9streambufPci ();
IMPORT int shell ();
IMPORT int shellHistSize;
IMPORT int shellHistory ();
IMPORT int shellInit ();
IMPORT int shellIsRemoteConnectedGet ();
IMPORT int shellIsRemoteConnectedSet ();
IMPORT int shellLock ();
IMPORT int shellLogin ();
IMPORT int shellLoginInstall ();
IMPORT int shellLogout ();
IMPORT int shellLogoutInstall ();
IMPORT int shellOrigStdSet ();
IMPORT int shellParserControl ();
IMPORT int shellPromptSet ();
IMPORT int shellRestart ();
IMPORT int shellScriptAbort ();
IMPORT int shellTaskId;
IMPORT int shellTaskName;
IMPORT int shellTaskOptions;
IMPORT int shellTaskPriority;
IMPORT int shellTaskStackSize;
IMPORT int shortbuf__9streambuf ();
IMPORT int show ();
IMPORT int shutdown ();
IMPORT int sigEvtRtn;
IMPORT int sigInit ();
IMPORT int sigPendDestroy ();
IMPORT int sigPendInit ();
IMPORT int sigPendKill ();
IMPORT int sigaction ();
IMPORT int sigaddset ();
IMPORT int sigblock ();
IMPORT int sigdelset ();
IMPORT int sigemptyset ();
IMPORT int sigfillset ();
IMPORT int sigismember ();
IMPORT int signal ();
IMPORT int sigpending ();
IMPORT int sigprocmask ();
IMPORT int sigqueue ();
IMPORT int sigqueueInit ();
IMPORT int sigreturn ();
IMPORT int sigsetjmp ();
IMPORT int sigsetmask ();
IMPORT int sigsuspend ();
IMPORT int sigtimedwait ();
IMPORT int sigvec ();
IMPORT int sigwait ();
IMPORT int sigwaitinfo ();
IMPORT int sin ();
IMPORT int sinh ();
IMPORT int skip__7istreami ();
IMPORT int skip_ws__FP9streambuf ();
IMPORT int sllCount ();
IMPORT SL_LIST *sllCreate ();
IMPORT int sllDelete ();
IMPORT SL_NODE *sllEach ();
IMPORT SL_NODE *sllGet ();
IMPORT int sllInit ();
IMPORT SL_NODE *sllPrevious ();
IMPORT void sllPutAtHead ();
IMPORT void sllPutAtTail ();
IMPORT void sllRemove ();
IMPORT int sllTerminate ();
IMPORT int smMemPartAddToPoolRtn;
IMPORT int smMemPartAllocRtn;
IMPORT int smMemPartFindMaxRtn;
IMPORT int smMemPartFreeRtn;
IMPORT int smMemPartOptionsSetRtn;
IMPORT int smMemPartReallocRtn;
IMPORT int smMemPartShowRtn;
IMPORT int smObjPoolMinusOne;
IMPORT int smObjTaskDeleteFailRtn;
IMPORT int smObjTcbFreeFailRtn;
IMPORT int smObjTcbFreeRtn;
IMPORT int snextc__9streambuf ();
IMPORT int so ();
IMPORT int soabort ();
IMPORT int soaccept ();
IMPORT int sobind ();
IMPORT int socantrcvmore ();
IMPORT int socantsendmore ();
IMPORT int sockFdtosockFunc ();
IMPORT int sockLibAdd ();
IMPORT int sockLibInit ();
IMPORT int socket ();
IMPORT int soclose ();
IMPORT int soconnect ();
IMPORT int soconnect2 ();
IMPORT int socreate ();
IMPORT int sodisconnect ();
IMPORT int sofree ();
IMPORT int sogetopt ();
IMPORT int sohasoutofband ();
IMPORT int soisconnected ();
IMPORT int soisconnecting ();
IMPORT int soisdisconnected ();
IMPORT int soisdisconnecting ();
IMPORT int solisten ();
IMPORT int sonewconn1 ();
IMPORT int soo_ioctl ();
IMPORT int soo_select ();
IMPORT int soo_unselect ();
IMPORT int soqinsque ();
IMPORT int soqremque ();
IMPORT int soreceive ();
IMPORT int soreserve ();
IMPORT int sorflush ();
IMPORT int sosend ();
IMPORT int sosetopt ();
IMPORT int soshutdown ();
IMPORT int sowakeup ();
IMPORT int sowakeupHook;
IMPORT int sp ();
IMPORT int spTaskOptions;
IMPORT int spTaskPriority;
IMPORT int spTaskStackSize;
IMPORT int splSemId;
IMPORT int splSemInit ();
IMPORT int splTid;
IMPORT int splimp ();
IMPORT int splnet ();
IMPORT int splnet2 ();
IMPORT int splx ();
IMPORT int sprintf ();
IMPORT int sputbackc__9streambufc ();
IMPORT int sputc__9streambufi ();
IMPORT int sputn__9streambufPCci ();
IMPORT int spy ();
IMPORT int spyClkStart ();
IMPORT int spyClkStartCommon ();
IMPORT int spyClkStop ();
IMPORT int spyClkStopCommon ();
IMPORT int spyComTask ();
IMPORT int spyCommon ();
IMPORT int spyHelp ();
IMPORT int spyIdleIncTicks;
IMPORT int spyIdleTicks;
IMPORT int spyIncTicks;
IMPORT int spyInterruptIncTicks;
IMPORT int spyInterruptTicks;
IMPORT int spyKernelIncTicks;
IMPORT int spyKernelTicks;
IMPORT int spyLibInit ();
IMPORT int spyReport ();
IMPORT int spyReportCommon ();
IMPORT int spyStop ();
IMPORT int spyStopCommon ();
IMPORT int spyTask ();
IMPORT int spyTaskId;
IMPORT int spyTaskOptions;
IMPORT int spyTaskPriority;
IMPORT int spyTaskStackSize;
IMPORT int spyTotalTicks;
IMPORT int sqrt ();
IMPORT int srand ();
IMPORT int srandom ();
IMPORT int sscanf ();
IMPORT int sseekoff__9streambuflQ23ios8seek_diri ();
IMPORT int sseekpos__9streambufli ();
IMPORT int stBdTmpTh;
IMPORT int stBdVolTh;
IMPORT int start485 ();
IMPORT int start485test ();
IMPORT int startmm ();
IMPORT int starttcp ();
IMPORT int starttimer ();
IMPORT int stat ();
IMPORT int statSymTbl;
IMPORT int statTbl;
IMPORT int statTblSize;
IMPORT int statfs ();
IMPORT int stdioFp ();
IMPORT int stdioFpCreate ();
IMPORT int stdioFpDestroy ();
IMPORT int stdioInit ();
IMPORT int stdioShow ();
IMPORT int stdioShowInit ();
IMPORT int stossc__9streambuf ();
IMPORT int strcat ();
IMPORT int strchr ();
IMPORT int strcmp ();
IMPORT int strcoll ();
IMPORT int strcpy ();
IMPORT int strcspn ();
IMPORT int strerror ();
IMPORT int strerror_r ();
IMPORT int strftime ();
IMPORT int strlen ();
IMPORT int strncat ();
IMPORT int strncmp ();
IMPORT int strncpy ();
IMPORT int strpbrk ();
IMPORT int strrchr ();
IMPORT int strspn ();
IMPORT int strstr ();
IMPORT int strtod ();
IMPORT int strtok ();
IMPORT int strtok_r ();
IMPORT int strtol ();
IMPORT int strtoul ();
IMPORT int strxfrm ();
IMPORT int subnetsarelocal;
IMPORT int substrcmp ();
IMPORT int sungetc__9streambuf ();
IMPORT int swab ();
IMPORT int switch_to_get_mode__9streambuf ();
IMPORT int symAdd ();
IMPORT int symAlloc ();
IMPORT int symByCNameFind ();
IMPORT int symByValueAndTypeFind ();
IMPORT int symByValueFind ();
IMPORT int symEach ();
IMPORT int symFindByCName ();
IMPORT int symFindByName ();
IMPORT int symFindByNameAndType ();
IMPORT int symFindByValue ();
IMPORT int symFindByValueAndType ();
IMPORT int symFindSymbol ();
IMPORT int symFree ();
IMPORT int symGroupDefault;
IMPORT int symInit ();
IMPORT int symLibInit ();
IMPORT int symLkupPgSz;
IMPORT int symName ();
IMPORT int symNameGet ();
IMPORT int symRemove ();
IMPORT int symSAdd ();
IMPORT int symShow ();
IMPORT int symShowInit ();
IMPORT int symTblAdd ();
IMPORT int symTblClassId;
IMPORT int symTblCreate ();
IMPORT int symTblDelete ();
IMPORT int symTblDestroy ();
IMPORT int symTblInit ();
IMPORT int symTblRemove ();
IMPORT int symTblTerminate ();
IMPORT int symTypeGet ();
IMPORT int symValueGet ();
IMPORT int syncLoadRtn;
IMPORT int syncSymAddRtn;
IMPORT int syncSymRemoveRtn;
IMPORT int sync__7filebuf ();
IMPORT int sync__7istream ();
IMPORT int sync__9streambuf ();
IMPORT int sync_with_stdio__3ios ();
IMPORT int sync_with_stdio__3iosi ();
IMPORT int sysAdaEnable;
IMPORT int sysAuxClkConnect ();
IMPORT int sysAuxClkDisable ();
IMPORT int sysAuxClkEnable ();
IMPORT int sysAuxClkRateGet ();
IMPORT int sysAuxClkRateSet ();
IMPORT int sysBootFile;
IMPORT int sysBootHost;
IMPORT int sysBootLine;
IMPORT int sysBootParams;
IMPORT int sysBspRev ();
IMPORT int sysBus;
IMPORT int sysBusIntAck ();
IMPORT int sysBusIntGen ();
IMPORT int sysBusTas ();
IMPORT int sysBusToLocalAdrs ();
IMPORT int sysCacheLibInit;
IMPORT int sysClDescTbl;
IMPORT int sysClDescTblNumEnt;
IMPORT int sysClkConnect ();
IMPORT int sysClkDisable ();
IMPORT int sysClkEnable ();
IMPORT int sysClkInit ();
IMPORT int sysClkRateGet ();
IMPORT int sysClkRateSet ();
IMPORT int sysCplusEnable;
IMPORT int sysCpu;
IMPORT int sysExcMsg;
IMPORT int sysFlags;
IMPORT int sysFlashErase16 ();
IMPORT int sysFlashWrite16 ();
IMPORT int sysFlashWriteEnable ();
IMPORT int sysHwInit ();
IMPORT int sysHwInit0 ();
IMPORT int sysHwInit2 ();
IMPORT int sysInByte ();
IMPORT int sysInit ();
IMPORT int sysIntDisablePIC ();
IMPORT int sysIntEnablePIC ();
IMPORT int sysIntLvlChgRtn;
IMPORT int sysIntLvlDisableRtn;
IMPORT int sysIntLvlEnableRtn;
IMPORT int sysIntLvlVecAckRtn;
IMPORT int sysIntLvlVecChkRtn;
IMPORT int sysIntStackSplit ();
IMPORT int sysLedsReadWrite ();
IMPORT int sysLocalToBusAdrs ();
IMPORT int sysMailboxConnect ();
IMPORT int sysMailboxEnable ();
IMPORT int sysMclBlkConfig;
IMPORT int sysMemTop ();
IMPORT int sysMmuLibInit;
IMPORT int sysModel ();
IMPORT int sysNvRamGet ();
IMPORT int sysNvRamSet ();
IMPORT int sysOutByte ();
IMPORT int sysPhysMemDesc;
IMPORT int sysPhysMemDescNumEnt;
IMPORT int sysPhysMemTop ();
IMPORT int sysProcNum;
IMPORT int sysProcNumGet ();
IMPORT int sysProcNumSet ();
IMPORT int sysSecEnetAddrGet ();
IMPORT int sysSecEnetAddrSet ();
IMPORT int sysSectorErase16 ();
IMPORT int sysSerialChanGet ();
IMPORT int sysSerialHwInit ();
IMPORT int sysSerialHwInit2 ();
IMPORT int sysSerialReset ();
IMPORT int sysStart ();
IMPORT int sysStartType;
IMPORT int sysSymTbl;
IMPORT int sysTffsFormat ();
IMPORT int sysToMonitor ();
IMPORT int sys_close__7filebuf ();
IMPORT int sys_close__9streambuf ();
IMPORT int sys_read__7filebufPci ();
IMPORT int sys_read__9streambufPci ();
IMPORT int sys_seek__7filebuflQ23ios8seek_dir ();
IMPORT int sys_seek__9streambuflQ23ios8seek_dir ();
IMPORT int sys_stat__7filebufPv ();
IMPORT int sys_stat__9streambufPv ();
IMPORT int sys_write__7filebufPCci ();
IMPORT int sys_write__9streambufPCci ();
IMPORT int system ();
IMPORT int tKeepAlive__10C485ClientPv ();
IMPORT int tKeepAlive__11CEthnClientPv ();
IMPORT int tListener__9CListenerPv ();
IMPORT int tModuleManager__14CModuleManagerPv ();
IMPORT int tPing ();
IMPORT int tPoll__13CTimerManagerPv ();
IMPORT int tReceiver__10C485ClientPv ();
IMPORT int tReceiver__11CEthnClientPv ();
IMPORT int tSender__10C485ClientPv ();
IMPORT int tSender__11CEthnClientPv ();
IMPORT int tTest ();
IMPORT int tUrgencyReceive ();
IMPORT int tUrgencySend ();
IMPORT int tan ();
IMPORT int tanh ();
IMPORT int taskAccept__13CCfgTcpSocketPv ();
IMPORT int taskAccept__14CSoftTcpSocketPv ();
IMPORT int taskAccept__15CAlarmTcpSocketPv ();
IMPORT int taskAccept__15CDebugTcpSocketPv ();
IMPORT int taskActivate ();
IMPORT int taskAlarmEvent ();
IMPORT int taskAlarmSocket ();
IMPORT int taskArgsGet ();
IMPORT int taskArgsSet ();
IMPORT int taskBpHook;
IMPORT int taskBpHookSet ();
IMPORT int taskCfgAndOper ();
IMPORT int taskCfgSocket ();
IMPORT int taskClassId;
IMPORT int taskCreat ();
IMPORT int taskCreateHookAdd ();
IMPORT int taskCreateHookDelete ();
IMPORT int taskCreateTable;
IMPORT int taskDebugSocket ();
IMPORT int taskDelay ();
IMPORT int taskDelete ();
IMPORT int taskDeleteForce ();
IMPORT int taskDeleteHookAdd ();
IMPORT int taskDeleteHookDelete ();
IMPORT int taskDeleteTable;
IMPORT int taskDestroy ();
IMPORT int taskHookInit ();
IMPORT int taskIdCurrent;
IMPORT int taskIdDefault ();
IMPORT int taskIdFigure ();
IMPORT int taskIdListGet ();
IMPORT int taskIdListSort ();
IMPORT int taskIdSelf ();
IMPORT int taskIdVerify ();
IMPORT int taskInfoGet ();
IMPORT int taskInit ();
IMPORT int taskInstClassId;
IMPORT int taskIsReady ();
IMPORT int taskIsSuspended ();
IMPORT int taskLibInit ();
IMPORT int taskLock ();
IMPORT int taskMainCtrlAll ();
IMPORT int taskName ();
IMPORT int taskNameToId ();
IMPORT int taskOptionsGet ();
IMPORT int taskOptionsSet ();
IMPORT int taskOptionsString ();
IMPORT int taskPriRangeCheck;
IMPORT int taskPriorityGet ();
IMPORT int taskPrioritySet ();
IMPORT int taskRecv__13CCfgTcpSocketPvUl ();
IMPORT int taskRecv__14CSoftTcpSocketPvUl ();
IMPORT int taskRecv__15CAlarmTcpSocketPvUl ();
IMPORT int taskRecv__15CDebugTcpSocketPvUl ();
IMPORT int taskRegName;
IMPORT int taskRegsFmt;
IMPORT int taskRegsGet ();
IMPORT int taskRegsInit ();
IMPORT int taskRegsSet ();
IMPORT int taskRegsShow ();
IMPORT int taskRestart ();
IMPORT int taskResume ();
IMPORT int taskRtnValueSet ();
IMPORT int taskSafe ();
IMPORT int taskShow ();
IMPORT int taskShowInit ();
IMPORT int taskSoftUpgrade ();
IMPORT int taskSoftupgradeSocket ();
IMPORT int taskSpawn ();
IMPORT int taskStackAllot ();
IMPORT int taskStatusString ();
IMPORT int taskSuspend ();
IMPORT int taskSwapHookAdd ();
IMPORT int taskSwapHookAttach ();
IMPORT int taskSwapHookDelete ();
IMPORT int taskSwapHookDetach ();
IMPORT int taskSwapReference;
IMPORT int taskSwapTable;
IMPORT int taskSwitchHookAdd ();
IMPORT int taskSwitchHookDelete ();
IMPORT int taskSwitchTable;
IMPORT int taskTcb ();
IMPORT int taskTerminate ();
IMPORT int taskUndelay ();
IMPORT int taskUnlock ();
IMPORT int taskUnsafe ();
IMPORT int taskVarAdd ();
IMPORT int taskVarDelete ();
IMPORT int taskVarGet ();
IMPORT int taskVarInfo ();
IMPORT int taskVarInit ();
IMPORT int taskVarSet ();
IMPORT int tcbinfo;
IMPORT int tcpCfgParams;
IMPORT int tcpLibInit ();
IMPORT int tcpOutRsts;
IMPORT int tcpRandHookAdd ();
IMPORT int tcpRandHookDelete ();
IMPORT int tcpReportRtn;
IMPORT int tcpTraceRtn;
IMPORT int tcp_alpha;
IMPORT int tcp_attach ();
IMPORT int tcp_backoff;
IMPORT int tcp_beta;
IMPORT int tcp_canceltimers ();
IMPORT int tcp_close ();
IMPORT int tcp_ctlinput ();
IMPORT int tcp_ctloutput ();
IMPORT int tcp_disconnect ();
IMPORT int tcp_do_rfc1323;
IMPORT int tcp_dooptions ();
IMPORT int tcp_drain ();
IMPORT int tcp_drop ();
IMPORT int tcp_fasttimo ();
IMPORT int tcp_init ();
IMPORT int tcp_input ();
IMPORT int tcp_iss;
IMPORT int tcp_keepcnt;
IMPORT int tcp_keepidle;
IMPORT int tcp_keepinit;
IMPORT int tcp_keepintvl;
IMPORT int tcp_last_inpcb;
IMPORT int tcp_maxidle;
IMPORT int tcp_maxpersistidle;
IMPORT int tcp_mss ();
IMPORT int tcp_mssdflt;
IMPORT int tcp_newtcpcb ();
IMPORT int tcp_notify ();
IMPORT int tcp_now;
IMPORT int tcp_outflags;
IMPORT int tcp_output ();
IMPORT int tcp_pcbhashsize;
IMPORT int tcp_pulloutofband ();
IMPORT int tcp_quench ();
IMPORT int tcp_reass ();
IMPORT int tcp_recvspace;
IMPORT int tcp_respond ();
IMPORT int tcp_rtlookup ();
IMPORT int tcp_rttdflt;
IMPORT int tcp_saveti;
IMPORT int tcp_sendspace;
IMPORT int tcp_setpersist ();
IMPORT int tcp_slowtimo ();
IMPORT int tcp_template ();
IMPORT int tcp_timers ();
IMPORT int tcp_totbackoff;
IMPORT int tcp_updatemtu ();
IMPORT int tcp_usrclosed ();
IMPORT int tcp_usrreq ();
IMPORT int tcp_xmit_timer ();
IMPORT int tcpcb;
IMPORT int tcprexmtthresh;
IMPORT int tcpstat;
IMPORT int tcpstates;
IMPORT int td ();
IMPORT int tellg__7istream ();
IMPORT int tellp__7ostream ();
IMPORT int telnetInTask ();
IMPORT int telnetOutTask ();
IMPORT int telnetTaskOptions;
IMPORT int telnetTaskPriority;
IMPORT int telnetTaskStackSize;
IMPORT int telnetd ();
IMPORT int telnetdCurrentClients;
IMPORT int telnetdExit ();
IMPORT int telnetdInit ();
IMPORT int telnetdParserSet ();
IMPORT int telnetdStart ();
IMPORT int telnetdStaticTaskInitializationGet ();
IMPORT int terminate__Fv ();
IMPORT int testCopy ();
IMPORT int testMEntry ();
IMPORT int testMultiMessage ();
IMPORT int testShow ();
IMPORT int testgetalarmstate ();
IMPORT int testio ();
IMPORT int testioRd ();
IMPORT int tffsDevCreate ();
IMPORT int tffsDevFormat ();
IMPORT int tffsDevOptionsSet ();
IMPORT int tffsDiskChangeAnnounce ();
IMPORT int tffsDrv ();
IMPORT int tffsRawio ();
IMPORT int tffsShow ();
IMPORT int tffsShowAll ();
IMPORT int tffscmpWords ();
IMPORT int tftpCopy ();
IMPORT int tftpErrorCreate ();
IMPORT int tftpGet ();
IMPORT int tftpInfoShow ();
IMPORT int tftpInit ();
IMPORT int tftpModeSet ();
IMPORT int tftpPeerSet ();
IMPORT int tftpPut ();
IMPORT int tftpQuit ();
IMPORT int tftpReXmit;
IMPORT int tftpSend ();
IMPORT int tftpTask ();
IMPORT int tftpTaskOptions;
IMPORT int tftpTaskPriority;
IMPORT int tftpTaskStackSize;
IMPORT int tftpTimeout;
IMPORT int tftpTrace;
IMPORT int tftpVerbose;
IMPORT int tftpXfer ();
IMPORT int ti ();
IMPORT int tick64Get ();
IMPORT int tick64Set ();
IMPORT int tickAnnounce ();
IMPORT int tickGet ();
IMPORT int tickQHead;
IMPORT int tickSet ();
IMPORT int tie__3iosP7ostream ();
IMPORT int tie__C3ios ();
IMPORT int time ();
IMPORT int timex ();
IMPORT int timexClear ();
IMPORT int timexFunc ();
IMPORT int timexHelp ();
IMPORT int timexInit ();
IMPORT int timexN ();
IMPORT int timexPost ();
IMPORT int timexPre ();
IMPORT int timexShow ();
IMPORT int tkRcvRtnCall ();
IMPORT int tlTable;
IMPORT int tmpfile ();
IMPORT int tmpnam ();
IMPORT int toBCD ();
IMPORT int toUNAL ();
IMPORT int toUNALLONG ();
IMPORT int tolower ();
IMPORT int toupper ();
IMPORT int tr ();
IMPORT int trcDefaultArgs;
IMPORT int trcStack ();
IMPORT int trgCnt;
IMPORT int trgEvtClass;
IMPORT int ts ();
IMPORT int tt ();
IMPORT int ttyDevCreate ();
IMPORT int ttyDrv ();
IMPORT int tyAbortFuncSet ();
IMPORT int tyAbortSet ();
IMPORT int tyBackspaceChar;
IMPORT int tyBackspaceSet ();
IMPORT int tyDeleteLineChar;
IMPORT int tyDeleteLineSet ();
IMPORT int tyDevInit ();
IMPORT int tyDevRemove ();
IMPORT int tyEOFSet ();
IMPORT int tyEofChar;
IMPORT int tyIRd ();
IMPORT int tyITx ();
IMPORT int tyIoctl ();
IMPORT int tyMonitorTrapSet ();
IMPORT int tyRead ();
IMPORT int tyWrite ();
IMPORT int udb;
IMPORT int udbinfo;
IMPORT int udpCfgParams;
IMPORT int udpCommIfInit ();
IMPORT int udpDoCkSumRcv;
IMPORT int udpLibInit ();
IMPORT int udpRcv ();
IMPORT int udp_ctlinput ();
IMPORT int udp_in;
IMPORT int udp_init ();
IMPORT int udp_input ();
IMPORT int udp_last_inpcb;
IMPORT int udp_output ();
IMPORT int udp_pcbhashsize;
IMPORT int udp_recvspace;
IMPORT int udp_sendspace;
IMPORT int udp_ttl;
IMPORT int udp_usrreq ();
IMPORT int udpcksum;
IMPORT int udpstat;
IMPORT int uflow__9streambuf ();
IMPORT int uiomove ();
IMPORT int unbuffered__9streambuf ();
IMPORT int unbuffered__9streambufi ();
IMPORT int uncaught_exception__Fv ();
IMPORT int underflow__7filebuf ();
IMPORT int underflow__9streambuf ();
IMPORT int unexpected__Fv ();
IMPORT int unget__7istream ();
IMPORT int unget__7istreamc ();
IMPORT int ungetc ();
IMPORT int unlink ();
IMPORT int unlock__FR7istream ();
IMPORT int unlock__FR7ostream ();
IMPORT int unsave_markers__9streambuf ();
IMPORT int unset__3ios11state_value ();
IMPORT int unsetf__3iosUl ();
IMPORT int upcast__C16__user_type_infoRC9type_infoPvPPv ();
IMPORT int urgencyInit ();
IMPORT int urgencySendTest ();
IMPORT int useloopback;
IMPORT int usrAppInit ();
IMPORT int usrBanner ();
IMPORT int usrBootLineCrack ();
IMPORT int usrBootLineInit ();
IMPORT int usrBootLineParse ();
IMPORT int usrBreakpointSet ();
IMPORT int usrBsdSockLibInit ();
IMPORT int usrCacheEnable ();
IMPORT int usrClock ();
IMPORT int usrDhcpcLeaseClean ();
IMPORT int usrDosFsInit ();
IMPORT int usrEndLibInit ();
IMPORT int usrFtpInit ();
IMPORT int usrInit ();
IMPORT int usrIosCoreInit ();
IMPORT int usrIosExtraInit ();
IMPORT int usrIpLibInit ();
IMPORT int usrKernelCoreInit ();
IMPORT int usrKernelExtraInit ();
IMPORT int usrKernelInit ();
IMPORT int usrMmuInit ();
IMPORT int usrMuxLibInit ();
IMPORT int usrNetAppInit ();
IMPORT int usrNetBoot ();
IMPORT int usrNetConfig ();
IMPORT int usrNetDevNameGet ();
IMPORT int usrNetEndDevStart ();
IMPORT int usrNetHostSetup ();
IMPORT int usrNetIfConfig ();
IMPORT int usrNetLibInit ();
IMPORT int usrNetLoopbackStart ();
IMPORT int usrNetProtoInit ();
IMPORT int usrNetRemoteCreate ();
IMPORT int usrNetRemoteInit ();
IMPORT int usrNetmaskGet ();
IMPORT int usrNetworkAddrCheck ();
IMPORT int usrNetworkAddrInit ();
IMPORT int usrNetworkBoot ();
IMPORT int usrNetworkDevStart ();
IMPORT int usrNetworkInit ();
IMPORT int usrRoot ();
IMPORT int usrSecurity ();
IMPORT int usrSerialInit ();
IMPORT int usrShellInit ();
IMPORT int usrShowInit ();
IMPORT int usrStandaloneInit ();
IMPORT int usrStatTblInit ();
IMPORT int usrTelnetdStart ();
IMPORT int usrTffsConfig ();
IMPORT int usrTffsLnConfig ();
IMPORT int usrToolsInit ();
IMPORT int usrWdbBanner ();
IMPORT int usrWdbBp ();
IMPORT int usrWdbInit ();
IMPORT int uswab ();
IMPORT int utime ();
IMPORT int valloc ();
IMPORT int version ();
IMPORT int vfdprintf ();
IMPORT int vfprintf ();
IMPORT int vmBaseGlobalMapInit ();
IMPORT int vmBaseLibInit ();
IMPORT int vmBasePageSizeGet ();
IMPORT int vmBaseStateSet ();
IMPORT int vmLibInfo;
IMPORT int vprintf ();
IMPORT int vscan__7istreamPCcPv ();
IMPORT int vscan__9streambufPCcPvP3ios ();
IMPORT int vsprintf ();
IMPORT int vxAbsTicks;
IMPORT int vxEventPendQ;
IMPORT int vxIntStackBase;
IMPORT int vxIntStackEnd;
IMPORT int vxIrqIntStackBase;
IMPORT int vxIrqIntStackEnd;
IMPORT int vxMemArchProbe ();
IMPORT int vxMemProbe ();
IMPORT int vxMemProbeSup ();
IMPORT int vxSvcIntStackBase;
IMPORT int vxSvcIntStackEnd;
IMPORT int vxTas ();
IMPORT int vxTaskEntry ();
IMPORT int vxTicks;
IMPORT int vxWorksVersion;
IMPORT int wakeup ();
IMPORT int wcstombs ();
IMPORT int wctomb ();
IMPORT int wdCancel ();
IMPORT int wdClassId;
IMPORT int wdCreate ();
IMPORT int wdDelete ();
IMPORT int wdDestroy ();
IMPORT int wdInit ();
IMPORT int wdInstClassId;
IMPORT int wdLibInit ();
IMPORT int wdShow ();
IMPORT int wdShowInit ();
IMPORT int wdStart ();
IMPORT int wdTerminate ();
IMPORT int wdTick ();
IMPORT int wdbBpInstall ();
IMPORT int wdbBpSysEnterHook;
IMPORT int wdbBpSysExitHook;
IMPORT int wdbCksum ();
IMPORT int wdbCommDevInit ();
IMPORT int wdbCommMtu;
IMPORT int wdbConfig ();
IMPORT int wdbConnectLibInit ();
IMPORT int wdbCtxCreate ();
IMPORT int wdbCtxExitLibInit ();
IMPORT int wdbCtxExitNotifyHook ();
IMPORT int wdbCtxLibInit ();
IMPORT int wdbCtxResume ();
IMPORT int wdbCtxStartLibInit ();
IMPORT int wdbDbgArchInit ();
IMPORT int wdbDbgBpFind ();
IMPORT int wdbDbgBpGet ();
IMPORT int wdbDbgBpListInit ();
IMPORT int wdbDbgBpRemove ();
IMPORT int wdbDbgBpRemoveAll ();
IMPORT int wdbDbgGetNpc ();
IMPORT int wdbDbgTraceModeClear ();
IMPORT int wdbDbgTraceModeSet ();
IMPORT int wdbDbgTrap ();
IMPORT int wdbDirectCallLibInit ();
IMPORT int wdbE ();
IMPORT int wdbEndDebug;
IMPORT int wdbEndPktDevInit ();
IMPORT int wdbEventDeq ();
IMPORT int wdbEventLibInit ();
IMPORT int wdbEventNodeInit ();
IMPORT int wdbEventPost ();
IMPORT int wdbEvtptClassConnect ();
IMPORT int wdbEvtptLibInit ();
IMPORT int wdbExcLibInit ();
IMPORT int wdbExternEnterHook ();
IMPORT int wdbExternExitHook ();
IMPORT int wdbExternInit ();
IMPORT int wdbExternRegSetObjAdd ();
IMPORT int wdbExternRegsGet ();
IMPORT int wdbExternRegsSet ();
IMPORT int wdbExternSystemRegs;
IMPORT int wdbFuncCallLibInit ();
IMPORT int wdbGopherLibInit ();
IMPORT int wdbGopherLock;
IMPORT int wdbInfoGet ();
IMPORT int wdbInstallCommIf ();
IMPORT int wdbInstallRtIf ();
IMPORT int wdbIsInitialized;
IMPORT int wdbIsNowExternal ();
IMPORT int wdbIsNowTasking ();
IMPORT int wdbMbufAlloc ();
IMPORT int wdbMbufFree ();
IMPORT int wdbMemCoreLibInit ();
IMPORT int wdbMemLibInit ();
IMPORT int wdbMemTest ();
IMPORT int wdbModeSet ();
IMPORT int wdbNotifyHost ();
IMPORT int wdbNptInt ();
IMPORT int wdbNptShutdown ();
IMPORT int wdbNumMemRegions;
IMPORT int wdbOneShot;
IMPORT int wdbRegsLibInit ();
IMPORT int wdbResumeSystem ();
IMPORT int wdbRpcGetArgs ();
IMPORT int wdbRpcNotifyConnect ();
IMPORT int wdbRpcNotifyHost ();
IMPORT int wdbRpcRcv ();
IMPORT int wdbRpcReply ();
IMPORT int wdbRpcReplyErr ();
IMPORT int wdbRpcResendReply ();
IMPORT int wdbRpcXportInit ();
IMPORT int wdbRtIf;
IMPORT int wdbRtInfoGet ();
IMPORT int wdbRunsExternal ();
IMPORT int wdbRunsTasking ();
IMPORT int wdbSp ();
IMPORT int wdbSuspendSystem ();
IMPORT int wdbSuspendSystemHere ();
IMPORT int wdbSvcAdd ();
IMPORT int wdbSvcDispatch ();
IMPORT int wdbSvcDsaSvcRemove ();
IMPORT int wdbSvcHookAdd ();
IMPORT int wdbSvcLibInit ();
IMPORT int wdbSysBpLibInit ();
IMPORT int wdbSysModeInit ();
IMPORT int wdbSystemSuspend ();
IMPORT int wdbTargetIsConnected ();
IMPORT int wdbTask ();
IMPORT int wdbTaskAvRegsGet;
IMPORT int wdbTaskAvRegsSet;
IMPORT int wdbTaskBpLibInit ();
IMPORT int wdbTaskDspRegsGet;
IMPORT int wdbTaskDspRegsSet;
IMPORT int wdbTaskFpRegsGet;
IMPORT int wdbTaskFpRegsSet;
IMPORT int wdbTaskId;
IMPORT int wdbTaskInit ();
IMPORT int wdbTaskModeInit ();
IMPORT int wdbTaskRestartHook;
IMPORT int wdbTgtHasAltivec ();
IMPORT int wdbTgtHasAltivecSet ();
IMPORT int wdbTgtHasDsp ();
IMPORT int wdbTgtHasDspSet ();
IMPORT int wdbTgtHasFpp ();
IMPORT int wdbTgtHasFppSet ();
IMPORT int wdbToolName ();
IMPORT int wdbUserEvtLibInit ();
IMPORT int wdbUserEvtPost ();
IMPORT int wdbVioChannelRegister ();
IMPORT int wdbVioChannelUnregister ();
IMPORT int wdbVioDrv ();
IMPORT int wdbVioLibInit ();
IMPORT int what__C9bad_alloc ();
IMPORT int what__C9exception ();
IMPORT int whoami ();
IMPORT int width__3iosi ();
IMPORT int width__C3ios ();
IMPORT int wildcard;
IMPORT int windDelay ();
IMPORT int windDelete ();
IMPORT int windExit ();
IMPORT int windIntStackSet ();
IMPORT int windPendQFlush ();
IMPORT int windPendQGet ();
IMPORT int windPendQPut ();
IMPORT int windPendQRemove ();
IMPORT int windPendQTerminate ();
IMPORT int windPriNormalSet ();
IMPORT int windPrioritySet ();
IMPORT int windReadyQPut ();
IMPORT int windReadyQRemove ();
IMPORT int windResume ();
IMPORT int windSemDelete ();
IMPORT int windSpawn ();
IMPORT int windSuspend ();
IMPORT int windTickAnnounce ();
IMPORT int windUndelay ();
IMPORT int windWdCancel ();
IMPORT int windWdStart ();
IMPORT int workQAdd0 ();
IMPORT int workQAdd1 ();
IMPORT int workQAdd2 ();
IMPORT int workQDoWork ();
IMPORT int workQInit ();
IMPORT int workQIsEmpty;
IMPORT int workQPanic ();
IMPORT int workQReadIx;
IMPORT int workQWriteIx;
IMPORT int writable__3ios ();
IMPORT int write ();
IMPORT int writeFlash16 ();
IMPORT int write__7ostreamPCSci ();
IMPORT int write__7ostreamPCUci ();
IMPORT int write__7ostreamPCci ();
IMPORT int write__7ostreamPCvi ();
IMPORT int writev ();
IMPORT int ws__FR7istream ();
IMPORT int wvEvtClass;
IMPORT int wvInstIsOn;
IMPORT int wvObjIsEnabled;
IMPORT int xattrib ();
IMPORT int xchain__9streambuf ();
IMPORT int xcopy ();
IMPORT int xdelete ();
IMPORT int xdrCksum ();
IMPORT int xdr_ARRAY ();
IMPORT int xdr_CHECKSUM ();
IMPORT int xdr_TGT_ADDR_T ();
IMPORT int xdr_TGT_INT_T ();
IMPORT int xdr_UINT32 ();
IMPORT int xdr_WDB_AGENT_INFO ();
IMPORT int xdr_WDB_CALL_RETURN_INFO ();
IMPORT int xdr_WDB_CTX ();
IMPORT int xdr_WDB_CTX_CREATE_DESC ();
IMPORT int xdr_WDB_CTX_STEP_DESC ();
IMPORT int xdr_WDB_EVTPT_ADD_DESC ();
IMPORT int xdr_WDB_EVTPT_DEL_DESC ();
IMPORT int xdr_WDB_EVT_DATA ();
IMPORT int xdr_WDB_EVT_INFO ();
IMPORT int xdr_WDB_MEM_REGION ();
IMPORT int xdr_WDB_MEM_SCAN_DESC ();
IMPORT int xdr_WDB_MEM_XFER ();
IMPORT int xdr_WDB_OPQ_DATA_T ();
IMPORT int xdr_WDB_PARAM_WRAPPER ();
IMPORT int xdr_WDB_REG_READ_DESC ();
IMPORT int xdr_WDB_REG_WRITE_DESC ();
IMPORT int xdr_WDB_REPLY_WRAPPER ();
IMPORT int xdr_WDB_RT_INFO ();
IMPORT int xdr_WDB_STRING_T ();
IMPORT int xdr_WDB_TGT_INFO ();
IMPORT int xdr_bool ();
IMPORT int xdr_bytes ();
IMPORT int xdr_char ();
IMPORT int xdr_double ();
IMPORT int xdr_enum ();
IMPORT int xdr_float ();
IMPORT int xdr_floatInclude ();
IMPORT int xdr_free ();
IMPORT int xdr_int ();
IMPORT int xdr_long ();
IMPORT int xdr_netobj ();
IMPORT int xdr_opaque ();
IMPORT int xdr_short ();
IMPORT int xdr_string ();
IMPORT int xdr_u_char ();
IMPORT int xdr_u_int ();
IMPORT int xdr_u_long ();
IMPORT int xdr_u_short ();
IMPORT int xdr_union ();
IMPORT int xdr_void ();
IMPORT int xdr_wrapstring ();
IMPORT int xdrmem_create ();
IMPORT int xflags__9streambuf ();
IMPORT int xflags__9streambufi ();
IMPORT int xmalloc ();
IMPORT int xput_char__9streambufc ();
IMPORT int xrealloc ();
IMPORT int xsetflags__9streambufi ();
IMPORT int xsetflags__9streambufii ();
IMPORT int xsgetn__7filebufPci ();
IMPORT int xsgetn__9streambufPci ();
IMPORT int xsputn__7filebufPCci ();
IMPORT int xsputn__9streambufPCci ();
IMPORT int yy_yys;
IMPORT int yy_yyv;
IMPORT int yychar;
IMPORT int yydebug;
IMPORT int yyerrflag;
IMPORT int yylval;
IMPORT int yynerrs;
IMPORT int yyparse ();
IMPORT int yyps;
IMPORT int yypv;
IMPORT int yys;
IMPORT int yystart ();
IMPORT int yystate;
IMPORT int yytmp;
IMPORT int yyv;
IMPORT int yyval;
IMPORT int zeroin_addr;

SYMBOL standTbl [5241] =
    {
        {{NULL}, "AT91F_AIC_AcknowledgeIt", (char*) AT91F_AIC_AcknowledgeIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_CfgPMC", (char*) AT91F_AIC_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_ClearIt", (char*) AT91F_AIC_ClearIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_ConfigureIt", (char*) AT91F_AIC_ConfigureIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_DisableIt", (char*) AT91F_AIC_DisableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_EnableIt", (char*) AT91F_AIC_EnableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_IsActive", (char*) AT91F_AIC_IsActive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_IsPending", (char*) AT91F_AIC_IsPending, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_Open", (char*) AT91F_AIC_Open, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_SetExceptionVector", (char*) AT91F_AIC_SetExceptionVector, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_AIC_Trig", (char*) AT91F_AIC_Trig, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_CKGR_GetMainClock", (char*) AT91F_CKGR_GetMainClock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_DBGU_CfgPIO", (char*) AT91F_DBGU_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_DBGU_CfgPMC", (char*) AT91F_DBGU_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_DBGU_GetInterruptMaskStatus", (char*) AT91F_DBGU_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_DBGU_InterruptDisable", (char*) AT91F_DBGU_InterruptDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_DBGU_InterruptEnable", (char*) AT91F_DBGU_InterruptEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_DBGU_IsInterruptMasked", (char*) AT91F_DBGU_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_EBI_CfgPIO", (char*) AT91F_EBI_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_EMAC_CfgPIO", (char*) AT91F_EMAC_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_EMAC_CfgPMC", (char*) AT91F_EMAC_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_MCI_CfgPIO", (char*) AT91F_MCI_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_MCI_CfgPMC", (char*) AT91F_MCI_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_MCI_Cfg_ModeRegister", (char*) AT91F_MCI_Cfg_ModeRegister, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_MCI_Configure", (char*) AT91F_MCI_Configure, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_MCI_DisableIt", (char*) AT91F_MCI_DisableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_MCI_Disable_Interface", (char*) AT91F_MCI_Disable_Interface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_MCI_EnableIt", (char*) AT91F_MCI_EnableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_MCI_Enable_Interface", (char*) AT91F_MCI_Enable_Interface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_Close", (char*) AT91F_PDC_Close, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_DisableRx", (char*) AT91F_PDC_DisableRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_DisableTx", (char*) AT91F_PDC_DisableTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_EnableRx", (char*) AT91F_PDC_EnableRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_EnableTx", (char*) AT91F_PDC_EnableTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_IsNextRxEmpty", (char*) AT91F_PDC_IsNextRxEmpty, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_IsNextTxEmpty", (char*) AT91F_PDC_IsNextTxEmpty, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_IsRxEmpty", (char*) AT91F_PDC_IsRxEmpty, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_IsTxEmpty", (char*) AT91F_PDC_IsTxEmpty, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_Open", (char*) AT91F_PDC_Open, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_ReceiveFrame", (char*) AT91F_PDC_ReceiveFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_SendFrame", (char*) AT91F_PDC_SendFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_SetNextRx", (char*) AT91F_PDC_SetNextRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_SetNextTx", (char*) AT91F_PDC_SetNextTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_SetRx", (char*) AT91F_PDC_SetRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PDC_SetTx", (char*) AT91F_PDC_SetTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIOA_CfgPMC", (char*) AT91F_PIOA_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIOB_CfgPMC", (char*) AT91F_PIOB_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIOC_CfgPMC", (char*) AT91F_PIOC_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIOD_CfgPMC", (char*) AT91F_PIOD_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_A_RegisterSelection", (char*) AT91F_PIO_A_RegisterSelection, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_B_RegisterSelection", (char*) AT91F_PIO_B_RegisterSelection, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_CfgDirectDrive", (char*) AT91F_PIO_CfgDirectDrive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_CfgInput", (char*) AT91F_PIO_CfgInput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_CfgInputFilter", (char*) AT91F_PIO_CfgInputFilter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_CfgOpendrain", (char*) AT91F_PIO_CfgOpendrain, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_CfgOutput", (char*) AT91F_PIO_CfgOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_CfgPeriph", (char*) AT91F_PIO_CfgPeriph, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_CfgPullup", (char*) AT91F_PIO_CfgPullup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_ClearOutput", (char*) AT91F_PIO_ClearOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_Disable", (char*) AT91F_PIO_Disable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_Enable", (char*) AT91F_PIO_Enable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_ForceOutput", (char*) AT91F_PIO_ForceOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetCfgPullup", (char*) AT91F_PIO_GetCfgPullup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetInput", (char*) AT91F_PIO_GetInput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetInputFilterStatus", (char*) AT91F_PIO_GetInputFilterStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetInterruptMaskStatus", (char*) AT91F_PIO_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetInterruptStatus", (char*) AT91F_PIO_GetInterruptStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetMultiDriverStatus", (char*) AT91F_PIO_GetMultiDriverStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetOutputDataStatus", (char*) AT91F_PIO_GetOutputDataStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetOutputStatus", (char*) AT91F_PIO_GetOutputStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetOutputWriteStatus", (char*) AT91F_PIO_GetOutputWriteStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_GetStatus", (char*) AT91F_PIO_GetStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_Get_AB_RegisterStatus", (char*) AT91F_PIO_Get_AB_RegisterStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_InputFilterDisable", (char*) AT91F_PIO_InputFilterDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_InputFilterEnable", (char*) AT91F_PIO_InputFilterEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_InterruptDisable", (char*) AT91F_PIO_InterruptDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_InterruptEnable", (char*) AT91F_PIO_InterruptEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsAB_RegisterSet", (char*) AT91F_PIO_IsAB_RegisterSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsCfgPullupStatusSet", (char*) AT91F_PIO_IsCfgPullupStatusSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsInputFilterSet", (char*) AT91F_PIO_IsInputFilterSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsInputSet", (char*) AT91F_PIO_IsInputSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsInterruptMasked", (char*) AT91F_PIO_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsInterruptSet", (char*) AT91F_PIO_IsInterruptSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsMultiDriverSet", (char*) AT91F_PIO_IsMultiDriverSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsOutputDataStatusSet", (char*) AT91F_PIO_IsOutputDataStatusSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsOutputSet", (char*) AT91F_PIO_IsOutputSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsOutputWriteSet", (char*) AT91F_PIO_IsOutputWriteSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_IsSet", (char*) AT91F_PIO_IsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_MultiDriverDisable", (char*) AT91F_PIO_MultiDriverDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_MultiDriverEnable", (char*) AT91F_PIO_MultiDriverEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_OutputDisable", (char*) AT91F_PIO_OutputDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_OutputEnable", (char*) AT91F_PIO_OutputEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_OutputWriteDisable", (char*) AT91F_PIO_OutputWriteDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_OutputWriteEnable", (char*) AT91F_PIO_OutputWriteEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PIO_SetOutput", (char*) AT91F_PIO_SetOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PMC_CfgPIO", (char*) AT91F_PMC_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PMC_CfgPMC", (char*) AT91F_PMC_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PMC_DisablePCK", (char*) AT91F_PMC_DisablePCK, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PMC_DisablePeriphClock", (char*) AT91F_PMC_DisablePeriphClock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PMC_EnablePCK", (char*) AT91F_PMC_EnablePCK, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PMC_EnablePeriphClock", (char*) AT91F_PMC_EnablePeriphClock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PMC_GetMasterClock", (char*) AT91F_PMC_GetMasterClock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_PMC_GetProcessorClock", (char*) AT91F_PMC_GetProcessorClock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_RTC_CfgPMC", (char*) AT91F_RTC_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_RTC_GetInterruptMaskStatus", (char*) AT91F_RTC_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_RTC_InterruptDisable", (char*) AT91F_RTC_InterruptDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_RTC_InterruptEnable", (char*) AT91F_RTC_InterruptEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_RTC_IsInterruptMasked", (char*) AT91F_RTC_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SDRC_CfgPIO", (char*) AT91F_SDRC_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SMC2_CfgPIO", (char*) AT91F_SMC2_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_CfgCs", (char*) AT91F_SPI_CfgCs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_CfgMode", (char*) AT91F_SPI_CfgMode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_CfgPCS", (char*) AT91F_SPI_CfgPCS, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_CfgPIO", (char*) AT91F_SPI_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_CfgPMC", (char*) AT91F_SPI_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_Close", (char*) AT91F_SPI_Close, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_Disable", (char*) AT91F_SPI_Disable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_DisableIt", (char*) AT91F_SPI_DisableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_Enable", (char*) AT91F_SPI_Enable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_EnableIt", (char*) AT91F_SPI_EnableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_GetChar", (char*) AT91F_SPI_GetChar, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_GetInterruptMaskStatus", (char*) AT91F_SPI_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_IsInterruptMasked", (char*) AT91F_SPI_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_Open", (char*) AT91F_SPI_Open, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_PutChar", (char*) AT91F_SPI_PutChar, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_ReceiveFrame", (char*) AT91F_SPI_ReceiveFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_Reset", (char*) AT91F_SPI_Reset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SPI_SendFrame", (char*) AT91F_SPI_SendFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC0_CfgPIO", (char*) AT91F_SSC0_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC0_CfgPMC", (char*) AT91F_SSC0_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC1_CfgPIO", (char*) AT91F_SSC1_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC1_CfgPMC", (char*) AT91F_SSC1_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC2_CfgPIO", (char*) AT91F_SSC2_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC2_CfgPMC", (char*) AT91F_SSC2_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_Configure", (char*) AT91F_SSC_Configure, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_DisableIt", (char*) AT91F_SSC_DisableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_DisableRx", (char*) AT91F_SSC_DisableRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_DisableTx", (char*) AT91F_SSC_DisableTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_EnableIt", (char*) AT91F_SSC_EnableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_EnableRx", (char*) AT91F_SSC_EnableRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_EnableTx", (char*) AT91F_SSC_EnableTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_GetInterruptMaskStatus", (char*) AT91F_SSC_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_GetStatus", (char*) AT91F_SSC_GetStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_IsInterruptMasked", (char*) AT91F_SSC_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_ReceiveFrame", (char*) AT91F_SSC_ReceiveFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_SendFrame", (char*) AT91F_SSC_SendFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SSC_SetBaudrate", (char*) AT91F_SSC_SetBaudrate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_ST_CfgPMC", (char*) AT91F_ST_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_ST_DisableIt", (char*) AT91F_ST_DisableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_ST_EnableIt", (char*) AT91F_ST_EnableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_ST_GetInterruptMaskStatus", (char*) AT91F_ST_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_ST_IsInterruptMasked", (char*) AT91F_ST_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_SYS_CfgPMC", (char*) AT91F_SYS_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC0_CfgPMC", (char*) AT91F_TC0_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC1_CfgPMC", (char*) AT91F_TC1_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC2_CfgPMC", (char*) AT91F_TC2_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC3_CfgPMC", (char*) AT91F_TC3_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC4_CfgPMC", (char*) AT91F_TC4_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC5_CfgPMC", (char*) AT91F_TC5_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC_GetInterruptMaskStatus", (char*) AT91F_TC_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC_InterruptDisable", (char*) AT91F_TC_InterruptDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC_InterruptEnable", (char*) AT91F_TC_InterruptEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TC_IsInterruptMasked", (char*) AT91F_TC_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TWI_CfgPIO", (char*) AT91F_TWI_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TWI_CfgPMC", (char*) AT91F_TWI_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TWI_Configure", (char*) AT91F_TWI_Configure, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TWI_DisableIt", (char*) AT91F_TWI_DisableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TWI_EnableIt", (char*) AT91F_TWI_EnableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TWI_GetInterruptMaskStatus", (char*) AT91F_TWI_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_TWI_IsInterruptMasked", (char*) AT91F_TWI_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_CfgPMC", (char*) AT91F_UDP_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_DisableEp", (char*) AT91F_UDP_DisableEp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_DisableIt", (char*) AT91F_UDP_DisableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EnableEp", (char*) AT91F_UDP_EnableEp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EnableIt", (char*) AT91F_UDP_EnableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EpClear", (char*) AT91F_UDP_EpClear, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EpEndOfWr", (char*) AT91F_UDP_EpEndOfWr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EpRead", (char*) AT91F_UDP_EpRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EpSet", (char*) AT91F_UDP_EpSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EpStall", (char*) AT91F_UDP_EpStall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EpStatus", (char*) AT91F_UDP_EpStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_EpWrite", (char*) AT91F_UDP_EpWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_GetInterruptMaskStatus", (char*) AT91F_UDP_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_GetState", (char*) AT91F_UDP_GetState, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_IsInterruptMasked", (char*) AT91F_UDP_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_ResetEp", (char*) AT91F_UDP_ResetEp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_SetAddress", (char*) AT91F_UDP_SetAddress, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UDP_SetState", (char*) AT91F_UDP_SetState, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_UHP_CfgPMC", (char*) AT91F_UHP_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US0_CfgPIO", (char*) AT91F_US0_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US0_CfgPMC", (char*) AT91F_US0_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US1_CfgPIO", (char*) AT91F_US1_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US1_CfgPMC", (char*) AT91F_US1_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US2_CfgPIO", (char*) AT91F_US2_CfgPIO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US2_CfgPMC", (char*) AT91F_US2_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US3_CfgPMC", (char*) AT91F_US3_CfgPMC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_Baudrate", (char*) AT91F_US_Baudrate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_Close", (char*) AT91F_US_Close, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_Configure", (char*) AT91F_US_Configure, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_DisableIt", (char*) AT91F_US_DisableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_DisableRx", (char*) AT91F_US_DisableRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_DisableTx", (char*) AT91F_US_DisableTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_EnableIt", (char*) AT91F_US_EnableIt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_EnableRx", (char*) AT91F_US_EnableRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_EnableTx", (char*) AT91F_US_EnableTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_Error", (char*) AT91F_US_Error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_GetChar", (char*) AT91F_US_GetChar, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_PutChar", (char*) AT91F_US_PutChar, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_ReceiveFrame", (char*) AT91F_US_ReceiveFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_ResetRx", (char*) AT91F_US_ResetRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_ResetTx", (char*) AT91F_US_ResetTx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_RxReady", (char*) AT91F_US_RxReady, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_SendFrame", (char*) AT91F_US_SendFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_SetBaudrate", (char*) AT91F_US_SetBaudrate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_SetIrdaFilter", (char*) AT91F_US_SetIrdaFilter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_SetTimeguard", (char*) AT91F_US_SetTimeguard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AT91F_US_TxReady", (char*) AT91F_US_TxReady, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Add485Node__12C485NodePoolUcUc", (char*) Add485Node__12C485NodePoolUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddAlarmNode__10CAlarmInfoRC13st_Alarm_InfoUc", (char*) AddAlarmNode__10CAlarmInfoRC13st_Alarm_InfoUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddDumbTimes__11CSocketNode", (char*) AddDumbTimes__11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddDumbTimes__11CSocketPoolRCl", (char*) AddDumbTimes__11CSocketPoolRCl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddDumbTimes__12C485NodePoolUc", (char*) AddDumbTimes__12C485NodePoolUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddDumbTimes__9CLinkNode", (char*) AddDumbTimes__9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddErrorTimes__11CSocketNode", (char*) AddErrorTimes__11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddErrorTimes__11CSocketPoolRCl", (char*) AddErrorTimes__11CSocketPoolRCl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddErrorTimes__12C485NodePoolUc", (char*) AddErrorTimes__12C485NodePoolUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddErrorTimes__9CLinkNode", (char*) AddErrorTimes__9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddFunction__6CBoardP5CRoot", (char*) AddFunction__6CBoardP5CRoot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddMessages__7CModuleUs", (char*) AddMessages__7CModuleUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddRcvCtrlPackages__15CPackageCounter", (char*) AddRcvCtrlPackages__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddRcvDataPackages__15CPackageCounter", (char*) AddRcvDataPackages__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddRcvNormalPackages__15CPackageCounter", (char*) AddRcvNormalPackages__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddReceiveOKTimes__15CPackageCounter", (char*) AddReceiveOKTimes__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddReceiveTimes__15CPackageCounter", (char*) AddReceiveTimes__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddRecvCounter__C12CCtrlPackageR15CPackageCounter", (char*) AddRecvCounter__C12CCtrlPackageR15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddRecvCounter__C12CDataPackageR15CPackageCounter", (char*) AddRecvCounter__C12CDataPackageR15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddRecvCounter__C8CPackageR15CPackageCounter", (char*) AddRecvCounter__C8CPackageR15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddSendCounter__C12CCtrlPackageR15CPackageCounter", (char*) AddSendCounter__C12CCtrlPackageR15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddSendCounter__C12CDataPackageR15CPackageCounter", (char*) AddSendCounter__C12CDataPackageR15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddSendCounter__C8CPackageR15CPackageCounter", (char*) AddSendCounter__C8CPackageR15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddSendCtrlPackages__15CPackageCounter", (char*) AddSendCtrlPackages__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddSendDataPackages__15CPackageCounter", (char*) AddSendDataPackages__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddSendOKTimes__15CPackageCounter", (char*) AddSendOKTimes__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddSendTimes__15CPackageCounter", (char*) AddSendTimes__15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AddSocketNode__11CSocketPoollUlUcUc", (char*) AddSocketNode__11CSocketPoollUlUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AlarmRspCmdToNs__FP10VWAS_CMD_SUlUl", (char*) AlarmRspCmdToNs__FP10VWAS_CMD_SUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AllocateBlock__11CMemoryPool", (char*) AllocateBlock__11CMemoryPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AllocateInputChannel__6CCrossUc", (char*) AllocateInputChannel__6CCrossUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AllocateMessage__13CAppInterfaceUsPP9S_MESSAGE", (char*) AllocateMessage__13CAppInterfaceUsPP9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AllocateOutputChannel__6CCrossPUcUc", (char*) AllocateOutputChannel__6CCrossPUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AllocateTimerID__12CTimerIDPool", (char*) AllocateTimerID__12CTimerIDPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AutoReportAlarm__10CAlarmInfoP10VWAS_CMD_SUcUl", (char*) AutoReportAlarm__10CAlarmInfoP10VWAS_CMD_SUcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AutoReportEvent__10CAlarmInfoP10VWAS_CMD_SUcUl", (char*) AutoReportEvent__10CAlarmInfoP10VWAS_CMD_SUcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "AutoWhiteBalance__8CChannelP10VWAS_CMD_SUl", (char*) AutoWhiteBalance__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPBooter", (char*) BSPBooter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPCheckSum", (char*) BSPCheckSum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPGetSoft", (char*) BSPGetSoft, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPGetSoft_TEST", (char*) BSPGetSoft_TEST, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPLoadSoft", (char*) BSPLoadSoft, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_OR_PIO_CfgInput", (char*) BSP_AT91F_OR_PIO_CfgInput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_OR_PIO_CfgOutput", (char*) BSP_AT91F_OR_PIO_CfgOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_OR_PIO_CfgPeriphA", (char*) BSP_AT91F_OR_PIO_CfgPeriphA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_OR_PIO_CfgPeriphB", (char*) BSP_AT91F_OR_PIO_CfgPeriphB, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_OR_PIO_ClearOutput", (char*) BSP_AT91F_OR_PIO_ClearOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_OR_PIO_GetInput", (char*) BSP_AT91F_OR_PIO_GetInput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_OR_PIO_SetOutput", (char*) BSP_AT91F_OR_PIO_SetOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_A_RegisterSelection", (char*) BSP_AT91F_PIO_A_RegisterSelection, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_B_RegisterSelection", (char*) BSP_AT91F_PIO_B_RegisterSelection, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_CfgInputFilter", (char*) BSP_AT91F_PIO_CfgInputFilter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_CfgOpendrain", (char*) BSP_AT91F_PIO_CfgOpendrain, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_CfgPullup", (char*) BSP_AT91F_PIO_CfgPullup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_CfgPullupDisable", (char*) BSP_AT91F_PIO_CfgPullupDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_CfgdwDirectDrive", (char*) BSP_AT91F_PIO_CfgdwDirectDrive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_Disable", (char*) BSP_AT91F_PIO_Disable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_Enable", (char*) BSP_AT91F_PIO_Enable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_ForceOutput", (char*) BSP_AT91F_PIO_ForceOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetCfgPullup", (char*) BSP_AT91F_PIO_GetCfgPullup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetInput", (char*) BSP_AT91F_PIO_GetInput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetInputFilterStatus", (char*) BSP_AT91F_PIO_GetInputFilterStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetInterruptMaskStatus", (char*) BSP_AT91F_PIO_GetInterruptMaskStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetInterruptStatus", (char*) BSP_AT91F_PIO_GetInterruptStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetMultiDriverStatus", (char*) BSP_AT91F_PIO_GetMultiDriverStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetOutputDataStatus", (char*) BSP_AT91F_PIO_GetOutputDataStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetOutputStatus", (char*) BSP_AT91F_PIO_GetOutputStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetOutputWriteStatus", (char*) BSP_AT91F_PIO_GetOutputWriteStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_GetStatus", (char*) BSP_AT91F_PIO_GetStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_Get_AB_RegisterStatus", (char*) BSP_AT91F_PIO_Get_AB_RegisterStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_InputFilterDisable", (char*) BSP_AT91F_PIO_InputFilterDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_InputFilterEnable", (char*) BSP_AT91F_PIO_InputFilterEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_InterruptDisable", (char*) BSP_AT91F_PIO_InterruptDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_InterruptEnable", (char*) BSP_AT91F_PIO_InterruptEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsAB_RegisterSet", (char*) BSP_AT91F_PIO_IsAB_RegisterSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsCfgPullupStatusSet", (char*) BSP_AT91F_PIO_IsCfgPullupStatusSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsInputFilterSet", (char*) BSP_AT91F_PIO_IsInputFilterSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsInputSet", (char*) BSP_AT91F_PIO_IsInputSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsInterruptMasked", (char*) BSP_AT91F_PIO_IsInterruptMasked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsInterruptSet", (char*) BSP_AT91F_PIO_IsInterruptSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsMultiDriverSet", (char*) BSP_AT91F_PIO_IsMultiDriverSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsOutputDataStatusSet", (char*) BSP_AT91F_PIO_IsOutputDataStatusSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsOutputSet", (char*) BSP_AT91F_PIO_IsOutputSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsOutputWriteSet", (char*) BSP_AT91F_PIO_IsOutputWriteSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_IsSet", (char*) BSP_AT91F_PIO_IsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_MultiDriverDisable", (char*) BSP_AT91F_PIO_MultiDriverDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_MultiDriverEnable", (char*) BSP_AT91F_PIO_MultiDriverEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_OutputDisable", (char*) BSP_AT91F_PIO_OutputDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_OutputEnable", (char*) BSP_AT91F_PIO_OutputEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_OutputWriteDisable", (char*) BSP_AT91F_PIO_OutputWriteDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_AT91F_PIO_OutputWriteEnable", (char*) BSP_AT91F_PIO_OutputWriteEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_BoardIsOnline", (char*) BSP_BoardIsOnline, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_BoardSolt", (char*) BSP_BoardSolt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_CalBackTest", (char*) BSP_CalBackTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_CpuUsage", (char*) BSP_CpuUsage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_Debug", (char*) BSP_Debug, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_DeleteSoft", (char*) BSP_DeleteSoft, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_DisableHardDog", (char*) BSP_DisableHardDog, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_DrvGetMac", (char*) BSP_DrvGetMac, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_DrvInit", (char*) BSP_DrvInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_EnableHardDog", (char*) BSP_EnableHardDog, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_FeedHardDog", (char*) BSP_FeedHardDog, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_FlashWriteEnable", (char*) BSP_FlashWriteEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetAllFPGAStatus", (char*) BSP_GetAllFPGAStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetBoardTypeId", (char*) BSP_GetBoardTypeId, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetBoardslotNo", (char*) BSP_GetBoardslotNo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetBootromStatus", (char*) BSP_GetBootromStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetBootromVer", (char*) BSP_GetBootromVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetCurSecondTest", (char*) BSP_GetCurSecondTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetCurStatus", (char*) BSP_GetCurStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetCurSysDateTime", (char*) BSP_GetCurSysDateTime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetCurSysDateTimeBySecond", (char*) BSP_GetCurSysDateTimeBySecond, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetCurTimeTest", (char*) BSP_GetCurTimeTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetFPGAStatus", (char*) BSP_GetFPGAStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetFpgaVer", (char*) BSP_GetFpgaVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetMainSoftStatus", (char*) BSP_GetMainSoftStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetManInfo", (char*) BSP_GetManInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetMiniSysVer", (char*) BSP_GetMiniSysVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetMiniSystemStatus", (char*) BSP_GetMiniSystemStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetPcbVer", (char*) BSP_GetPcbVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetSysSoftVer", (char*) BSP_GetSysSoftVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetTemperatureVal", (char*) BSP_GetTemperatureVal, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_GetVoltageStatus", (char*) BSP_GetVoltageStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_InitPll", (char*) BSP_InitPll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_LoadFpga", (char*) BSP_LoadFpga, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_LoadFpga_ALTERA", (char*) BSP_LoadFpga_ALTERA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_LoadFpga_LATTICE", (char*) BSP_LoadFpga_LATTICE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_MULTest", (char*) BSP_MULTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_MemUsage", (char*) BSP_MemUsage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_MulAdd", (char*) BSP_MulAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_NandFlashFileGetLength", (char*) BSP_NandFlashFileGetLength, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_NandFlashFileInit", (char*) BSP_NandFlashFileInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_NandFlashFileRead", (char*) BSP_NandFlashFileRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_NandFlashFileRead_L", (char*) BSP_NandFlashFileRead_L, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_NandFlashFileWrite", (char*) BSP_NandFlashFileWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_NandFlashFileWrite_L", (char*) BSP_NandFlashFileWrite_L, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_NandFlashIDGet", (char*) BSP_NandFlashIDGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_NandFlashReset", (char*) BSP_NandFlashReset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_PHYRead", (char*) BSP_PHYRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_PHYScan", (char*) BSP_PHYScan, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_RTCTEST", (char*) BSP_RTCTEST, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_Read5324", (char*) BSP_Read5324, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_ReceiveUrgentFrame", (char*) BSP_ReceiveUrgentFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_Reset", (char*) BSP_Reset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_ResetFpga", (char*) BSP_ResetFpga, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_Reset_FPGA", (char*) BSP_Reset_FPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_Reset_PCIE", (char*) BSP_Reset_PCIE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_RunAllTask", (char*) BSP_RunAllTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SaveFile", (char*) BSP_SaveFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SetCurSysDateTime", (char*) BSP_SetCurSysDateTime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SetCurTimeTest", (char*) BSP_SetCurTimeTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_ShowDog", (char*) BSP_ShowDog, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SoftBackUP", (char*) BSP_SoftBackUP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SoftStart", (char*) BSP_SoftStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SoftUpgrade", (char*) BSP_SoftUpgrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SoftWareUPTest", (char*) BSP_SoftWareUPTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SoftWareUPinit", (char*) BSP_SoftWareUPinit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_StopAllTask", (char*) BSP_StopAllTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SysAlarmLedFlic", (char*) BSP_SysAlarmLedFlic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_SysRunLedFlic", (char*) BSP_SysRunLedFlic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_TEST", (char*) BSP_TEST, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_TimeGet", (char*) BSP_TimeGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_TimeInit", (char*) BSP_TimeInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_UP", (char*) &BSP_UP, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "BSP_UrgencySend", (char*) BSP_UrgencySend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_UrgencySetMulAdd", (char*) BSP_UrgencySetMulAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_Write5324", (char*) BSP_Write5324, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_disable_mdi", (char*) BSP_disable_mdi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_enable_mdi", (char*) BSP_enable_mdi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_memPartShow", (char*) BSP_memPartShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_read_phy", (char*) BSP_read_phy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSP_write_phy", (char*) BSP_write_phy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BY2DW", (char*) BY2DW, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BY2W", (char*) BY2W, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Bbase__9streambuf", (char*) Bbase__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BdGetTestTime", (char*) BdGetTestTime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BeginUpgrade__12CSoftUpGradeP10VWAS_CMD_SUl", (char*) BeginUpgrade__12CSoftUpGradeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BinarySearchLeft__5CFileUlUlR5SYS_T", (char*) BinarySearchLeft__5CFileUlUlR5SYS_T, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BinarySearchRight__5CFileUlUlR5SYS_T", (char*) BinarySearchRight__5CFileUlUlR5SYS_T, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BoardID2Socket__11CSocketPoolUcRl", (char*) BoardID2Socket__11CSocketPoolUcRl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BoardOfflineTest__FUcUc", (char*) BoardOfflineTest__FUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BoardOffline__14CModuleManagerUlUc", (char*) BoardOffline__14CModuleManagerUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BoardOnlineTest__FUcUc", (char*) BoardOnlineTest__FUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BoardOnline__14CModuleManagerUlUc", (char*) BoardOnline__14CModuleManagerUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Bptr__9streambuf", (char*) Bptr__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CRC", (char*) &CRC, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "CRC_Poly", (char*) &CRC_Poly, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "CancelUpgrade__12CSoftUpGradeP10VWAS_CMD_SUl", (char*) CancelUpgrade__12CSoftUpGradeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CfgRspCmdToNs__FP10VWAS_CMD_SUlUl", (char*) CfgRspCmdToNs__FP10VWAS_CMD_SUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CfgSendCmdToBsWaitReturn__FUcP10VWAS_CMD_SUlUlT1", (char*) CfgSendCmdToBsWaitReturn__FUcP10VWAS_CMD_SUlUlT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CfgSendCmdToBs__FUcP10VWAS_CMD_SUlUl", (char*) CfgSendCmdToBs__FUcP10VWAS_CMD_SUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ChannelMap__10COperationUcUc", (char*) ChannelMap__10COperationUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CheckDateTimeIsCorrect__FR5SYS_T", (char*) CheckDateTimeIsCorrect__FR5SYS_T, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CheckDayIsCorrect__FUsUcUc", (char*) CheckDayIsCorrect__FUsUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CheckFpgaSupport__FUl", (char*) CheckFpgaSupport__FUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CheckVoltageUniteSupport__FUl", (char*) CheckVoltageUniteSupport__FUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ClearAlarmLog__10CAlarmInfoP10VWAS_CMD_SUl", (char*) ClearAlarmLog__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ClearEventLog__10CAlarmInfoP10VWAS_CMD_SUl", (char*) ClearEventLog__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ClearFlashLed__10CMainBoardP10VWAS_CMD_SUl", (char*) ClearFlashLed__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Clear__5CFilePCc", (char*) Clear__5CFilePCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CloseBus", (char*) CloseBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CloseWindow__4CWndP10VWAS_CMD_SUl", (char*) CloseWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Close__5CFile", (char*) Close__5CFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ClrLed__12CFunctionLedP10VWAS_CMD_SUl", (char*) ClrLed__12CFunctionLedP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CpLDDogClose", (char*) CpLDDogClose, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CpLDDogOpen", (char*) CpLDDogOpen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreateBoard__3CNeUcUs", (char*) CreateBoard__3CNeUcUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CreateMailBox__13CAppInterfaceUsUlUsiUli", (char*) CreateMailBox__13CAppInterfaceUsUlUsiUli, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CtrlBuzzer__10CAlarmInfoRC13st_Alarm_InfoUc", (char*) CtrlBuzzer__10CAlarmInfoRC13st_Alarm_InfoUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CtrlLcdAlarm__10CAlarmInfoUc", (char*) CtrlLcdAlarm__10CAlarmInfoUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DCACHE_CTRL", (char*) &DCACHE_CTRL, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "DW2BY", (char*) DW2BY, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DW2W", (char*) DW2W, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DebugOut", (char*) DebugOut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DecreaseNode__10CTcpSocketi", (char*) DecreaseNode__10CTcpSocketi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DelFunction__6CBoardUs", (char*) DelFunction__6CBoardUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DeleteMailBox__13CAppInterfaceUs", (char*) DeleteMailBox__13CAppInterfaceUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DeleteMessages__7CModuleUs", (char*) DeleteMessages__7CModuleUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DeleteSoft__12CSoftUpGradeP10VWAS_CMD_SUl", (char*) DeleteSoft__12CSoftUpGradeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Delete__11CMailBoxMapRCUs", (char*) Delete__11CMailBoxMapRCUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Disable_mac_address", (char*) Disable_mac_address, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Dispatch__18CProtocolInterfaceR8CPackage", (char*) Dispatch__18CProtocolInterfaceR8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Dispatch__C13CAppInterfaceR9S_MESSAGE", (char*) Dispatch__C13CAppInterfaceR9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Display485PingResult", (char*) Display485PingResult, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Display485TestResult", (char*) Display485TestResult, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Enable_mac_address", (char*) Enable_mac_address, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EnumWindow__4CWndP10VWAS_CMD_SUl", (char*) EnumWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EventRspCmdToNs__FP10VWAS_CMD_SUlUl", (char*) EventRspCmdToNs__FP10VWAS_CMD_SUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EventSignSourceChange__10CAlarmProcUcUc", (char*) EventSignSourceChange__10CAlarmProcUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "EventSystemClockChange__10CAlarmProc", (char*) EventSystemClockChange__10CAlarmProc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FileSysTest", (char*) FileSysTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FillAlarmInfo__10CAlarmInfoR13st_Alarm_InfoP12ALARM_REPORTUc", (char*) FillAlarmInfo__10CAlarmInfoR13st_Alarm_InfoP12ALARM_REPORTUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FillEventInfo__10CAlarmInfoR13st_Event_InfoP12EVENT_REPORTUc", (char*) FillEventInfo__10CAlarmInfoR13st_Event_InfoP12EVENT_REPORTUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FindFunction__6CBoardUs", (char*) FindFunction__6CBoardUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashPageRTest", (char*) FlashPageRTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashPageWTest", (char*) FlashPageWTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashReadTest", (char*) FlashReadTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashWriteTest", (char*) FlashWriteTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreeBlock__11CMemoryPoolPv", (char*) FreeBlock__11CMemoryPoolPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreeCross__6CCrossUcUcPUcUc", (char*) FreeCross__6CCrossUcUcPUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreeInputChannel__6CCrossUc", (char*) FreeInputChannel__6CCrossUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreeListMemory__12CSoftUpGrade", (char*) FreeListMemory__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreeMessage__13CAppInterfaceP9S_MESSAGE", (char*) FreeMessage__13CAppInterfaceP9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreeOutputChannel__6CCrossPUcUc", (char*) FreeOutputChannel__6CCrossPUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreeTimerID__12CTimerIDPoolUl", (char*) FreeTimerID__12CTimerIDPoolUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreezeChannel__8CChannelP10VWAS_CMD_SUl", (char*) FreezeChannel__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Gbase__9streambuf", (char*) Gbase__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GenerateHwnd__4CWnd", (char*) GenerateHwnd__4CWnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetAlarmAutoReport__10CAlarmInfoP10VWAS_CMD_SUl", (char*) GetAlarmAutoReport__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetAlarmState__10CAlarmInfoUcUc", (char*) GetAlarmState__10CAlarmInfoUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetAlarm__10CAlarmInfoP10VWAS_CMD_SUl", (char*) GetAlarm__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetAllFileRecord__5CFilePUc", (char*) GetAllFileRecord__5CFilePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetAllMailBoxes__C11CMailBoxMap", (char*) GetAllMailBoxes__C11CMailBoxMap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetAllModules__14CModuleManager", (char*) GetAllModules__14CModuleManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetAllRecordCount__5CFileRUlT1", (char*) GetAllRecordCount__5CFileRUlT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBoardID__C11CSocketNode", (char*) GetBoardID__C11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBoardID__C9CLinkNode", (char*) GetBoardID__C9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBoardSet__C12C485NodePoolRUcPUc", (char*) GetBoardSet__C12C485NodePoolRUcPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBoardType__C11CSocketNode", (char*) GetBoardType__C11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBoardType__C9CLinkNode", (char*) GetBoardType__C9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBoardslotNo__9CFunction", (char*) GetBoardslotNo__9CFunction, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBuzzer__10CMainBoardP10VWAS_CMD_SUl", (char*) GetBuzzer__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetChannelOffset__14COperAttributeP10VWAS_CMD_SUl", (char*) GetChannelOffset__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetColorKey__9CColorKeyP10VWAS_CMD_SUl", (char*) GetColorKey__9CColorKeyP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetColorKiller__8CChannelP10VWAS_CMD_SUl", (char*) GetColorKiller__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetCross__6CCrossP10VWAS_CMD_SUl", (char*) GetCross__6CCrossP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetCurRecNo__5CFileRUl", (char*) GetCurRecNo__5CFileRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetCutArea__14COperAttributeP10VWAS_CMD_SUl", (char*) GetCutArea__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetCutWindow__4CWndP10VWAS_CMD_SUl", (char*) GetCutWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataAddress__C12CCtrlPackageRPUc", (char*) GetDataAddress__C12CCtrlPackageRPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataAddress__C12CDataPackageRPUc", (char*) GetDataAddress__C12CDataPackageRPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataAddress__C8CPackageRPUc", (char*) GetDataAddress__C8CPackageRPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataLength__C12CCtrlPackageRUs", (char*) GetDataLength__C12CCtrlPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataLength__C12CDataPackageRUs", (char*) GetDataLength__C12CDataPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataLength__C20CRebootSystemMessage", (char*) GetDataLength__C20CRebootSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataLength__C21COfflineSystemMessage", (char*) GetDataLength__C21COfflineSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataLength__C21CStandbySystemMessage", (char*) GetDataLength__C21CStandbySystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataLength__C21CStartupSystemMessage", (char*) GetDataLength__C21CStartupSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDataLength__C8CPackageRUs", (char*) GetDataLength__C8CPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDateTime__10CMainBoardP10VWAS_CMD_SUl", (char*) GetDateTime__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDateTime__C10CAlarmFilePUc", (char*) GetDateTime__C10CAlarmFilePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDateTime__C10CEventFilePUc", (char*) GetDateTime__C10CEventFilePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDateTime__C5CFilePUc", (char*) GetDateTime__C5CFilePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDestinationBD__C12CCtrlPackageRUc", (char*) GetDestinationBD__C12CCtrlPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDestinationBD__C12CDataPackageRUc", (char*) GetDestinationBD__C12CDataPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDestinationBD__C8CPackageRUc", (char*) GetDestinationBD__C8CPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDestinationMailBox__C12CDataPackageRUs", (char*) GetDestinationMailBox__C12CDataPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDestinationMailBox__C8CPackageRUs", (char*) GetDestinationMailBox__C8CPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDeviceType__10CMainBoardP10VWAS_CMD_SUl", (char*) GetDeviceType__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDumbTimes__11CSocketPoollRUc", (char*) GetDumbTimes__11CSocketPoollRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDumbTimes__12C485NodePoolUcRUc", (char*) GetDumbTimes__12C485NodePoolUcRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDumbTimes__C11CSocketNode", (char*) GetDumbTimes__C11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetDumbTimes__C9CLinkNode", (char*) GetDumbTimes__C9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl", (char*) GetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetErrorTimes__11CSocketPoollRUc", (char*) GetErrorTimes__11CSocketPoollRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetErrorTimes__12C485NodePoolUcRUc", (char*) GetErrorTimes__12C485NodePoolUcRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetErrorTimes__C11CSocketNode", (char*) GetErrorTimes__C11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetErrorTimes__C9CLinkNode", (char*) GetErrorTimes__C9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetEventAutoReport__10CAlarmInfoP10VWAS_CMD_SUl", (char*) GetEventAutoReport__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetEvent__10CAlarmInfoP10VWAS_CMD_SUl", (char*) GetEvent__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetEvent__C11CMailBoxMapUsRUl", (char*) GetEvent__C11CMailBoxMapUsRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetFanStatus__10CMainBoardP10VWAS_CMD_SUl", (char*) GetFanStatus__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetFileCurSize__5CFile", (char*) GetFileCurSize__5CFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetFileNo__12CSoftUpGradeUcUcUcRUc", (char*) GetFileNo__12CSoftUpGradeUcUcUcRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetFileSize__5CFile", (char*) GetFileSize__5CFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetGatherChannelStat__14COperAttributeP10VWAS_CMD_SUl", (char*) GetGatherChannelStat__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetGatherOffset__14COperAttributeP10VWAS_CMD_SUl", (char*) GetGatherOffset__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl", (char*) GetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetGatherSignFormat__14COperAttributeP10VWAS_CMD_SUl", (char*) GetGatherSignFormat__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl", (char*) GetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetHardVer__12CFunctionVerP10VWAS_CMD_SUl", (char*) GetHardVer__12CFunctionVerP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetHeadPointer__C8CPackage", (char*) GetHeadPointer__C8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetIPAddress__C11CSocketNode", (char*) GetIPAddress__C11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetIP__11CFunctionIPP10VWAS_CMD_SUl", (char*) GetIP__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInSlotStatus__15CFunctionInSlotP10VWAS_CMD_SUl", (char*) GetInSlotStatus__15CFunctionInSlotP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInfo__C11CMemoryPoolRUcRUlT2", (char*) GetInfo__C11CMemoryPoolRUcRUlT2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInputChannelByDataBoardInfo__6CCrossUcUcRUcT3", (char*) GetInputChannelByDataBoardInfo__6CCrossUcUcRUcT3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInslotProcBdNum__3CNe", (char*) GetInslotProcBdNum__3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInstance__10CProcAlarm", (char*) GetInstance__10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInstance__11COperAndCfg", (char*) GetInstance__11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInstance__12CSoftUpGrade", (char*) GetInstance__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInstance__13CCfgTcpSocket", (char*) GetInstance__13CCfgTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInstance__14CSoftTcpSocket", (char*) GetInstance__14CSoftTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInstance__15CAlarmTcpSocket", (char*) GetInstance__15CAlarmTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetInstance__15CDebugTcpSocket", (char*) GetInstance__15CDebugTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetLocalBoardID__13CAppInterface", (char*) GetLocalBoardID__13CAppInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetLocalBoardType__13CAppInterface", (char*) GetLocalBoardType__13CAppInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetLogFileLength__10CMainBoardP10VWAS_CMD_SUl", (char*) GetLogFileLength__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMailBox__C7CModule", (char*) GetMailBox__C7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl", (char*) GetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMaxSocket__C11CSocketPool", (char*) GetMaxSocket__C11CSocketPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMessageID__C20CRebootSystemMessage", (char*) GetMessageID__C20CRebootSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMessageID__C21COfflineSystemMessage", (char*) GetMessageID__C21COfflineSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMessageID__C21CStandbySystemMessage", (char*) GetMessageID__C21CStandbySystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMessageID__C21CStartupSystemMessage", (char*) GetMessageID__C21CStartupSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMessageNumber__13CAppInterfaceUs", (char*) GetMessageNumber__13CAppInterfaceUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMessageSet__C7CModule", (char*) GetMessageSet__C7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMilliseconds__6CTimer", (char*) GetMilliseconds__6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetModuleID__C7CModule", (char*) GetModuleID__C7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetModule__14CModuleManagerUs", (char*) GetModule__14CModuleManagerUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMsgPara__10CAlarmInfoPUcR10VWAS_CMD_SRUl", (char*) GetMsgPara__10CAlarmInfoPUcR10VWAS_CMD_SRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMsgPara__11COperAndCfgPUcR10VWAS_CMD_SRUl", (char*) GetMsgPara__11COperAndCfgPUcR10VWAS_CMD_SRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetMsgQID__C11CMailBoxMapUsRP5msg_q", (char*) GetMsgQID__C11CMailBoxMapUsRP5msg_q, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetNetStatus__11CFunctionIPP10VWAS_CMD_SUl", (char*) GetNetStatus__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetOutputChannelBySignBoardInfo__6CCrossUcUcUcRUcT4", (char*) GetOutputChannelBySignBoardInfo__6CCrossUcUcUcRUcT4, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetPackageLength__C12CCtrlPackageRUs", (char*) GetPackageLength__C12CCtrlPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetPackageLength__C12CDataPackageRUs", (char*) GetPackageLength__C12CDataPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetPackageLength__C8CPackageRUs", (char*) GetPackageLength__C8CPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetPortInfo__17CFunctionPortInfoP10VWAS_CMD_SUl", (char*) GetPortInfo__17CFunctionPortInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetPowerStatus__10CMainBoardP10VWAS_CMD_SUl", (char*) GetPowerStatus__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetPrivilege__C12CDataPackageRUc", (char*) GetPrivilege__C12CDataPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetPrivilege__C8CPackageRUc", (char*) GetPrivilege__C8CPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetProcBdInfoByWallUnitNo__4CWndP10VWAS_CMD_SUl", (char*) GetProcBdInfoByWallUnitNo__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetProtocalVer__10CMainBoardP10VWAS_CMD_SUl", (char*) GetProtocalVer__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetQueryResult__5CFilePUc", (char*) GetQueryResult__5CFilePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetQuerySize__5CFileR5SYS_TT1RUlT3", (char*) GetQuerySize__5CFileR5SYS_TT1RUlT3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetRcvCtrlPackages__C15CPackageCounter", (char*) GetRcvCtrlPackages__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetRcvDataPackages__C15CPackageCounter", (char*) GetRcvDataPackages__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetRcvNormalPackages__C15CPackageCounter", (char*) GetRcvNormalPackages__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetRecNum__5CFileRUl", (char*) GetRecNum__5CFileRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetReceiveOKTimes__C15CPackageCounter", (char*) GetReceiveOKTimes__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetReceiveTimes__C15CPackageCounter", (char*) GetReceiveTimes__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetRtc", (char*) GetRtc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSendCtrlPackages__C15CPackageCounter", (char*) GetSendCtrlPackages__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSendDataPackages__C15CPackageCounter", (char*) GetSendDataPackages__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSendOKTimes__C15CPackageCounter", (char*) GetSendOKTimes__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSendTimes__C15CPackageCounter", (char*) GetSendTimes__C15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSequenceNumber__11CSocketNode", (char*) GetSequenceNumber__11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSequenceNumber__11CSocketPoolRClRUs", (char*) GetSequenceNumber__11CSocketPoolRClRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSequenceNumber__12C485NodePoolUcRUs", (char*) GetSequenceNumber__12C485NodePoolUcRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSequenceNumber__9CLinkNode", (char*) GetSequenceNumber__9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSequenceNumber__C8CPackageRUl", (char*) GetSequenceNumber__C8CPackageRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSi5326Reg", (char*) GetSi5326Reg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl", (char*) GetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSlotNumber__10CMainBoardP10VWAS_CMD_SUl", (char*) GetSlotNumber__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSocketSet__C11CSocketPoolRUcPl", (char*) GetSocketSet__C11CSocketPoolRUcPl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSocket__C11CSocketNode", (char*) GetSocket__C11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSoftFromList__12CSoftUpGrade", (char*) GetSoftFromList__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSoftPara__10CMainBoardP10VWAS_CMD_SUl", (char*) GetSoftPara__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSoftStatus__12CFunctionVerP10VWAS_CMD_SUl", (char*) GetSoftStatus__12CFunctionVerP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSoftVer__12CFunctionVerP10VWAS_CMD_SUl", (char*) GetSoftVer__12CFunctionVerP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSourceBD__C12CCtrlPackageRUc", (char*) GetSourceBD__C12CCtrlPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSourceBD__C12CDataPackageRUc", (char*) GetSourceBD__C12CDataPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSourceBD__C8CPackageRUc", (char*) GetSourceBD__C8CPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSourceMailBox__C12CDataPackageRUs", (char*) GetSourceMailBox__C12CDataPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSourceMailBox__C8CPackageRUs", (char*) GetSourceMailBox__C8CPackageRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetStatus__C7CModule", (char*) GetStatus__C7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSteps__6CTimerUc", (char*) GetSteps__6CTimerUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSubMessageID__C14CSystemMessage", (char*) GetSubMessageID__C14CSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSubMessageID__C20CRebootSystemMessage", (char*) GetSubMessageID__C20CRebootSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSubMessageID__C21CStandbySystemMessage", (char*) GetSubMessageID__C21CStandbySystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSubType__C12CCtrlPackageRUc", (char*) GetSubType__C12CCtrlPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSubType__C8CPackageRUc", (char*) GetSubType__C8CPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSysInitInfo__10CMainBoardP10VWAS_CMD_SUl", (char*) GetSysInitInfo__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSysSync__8CChannelP10VWAS_CMD_SUl", (char*) GetSysSync__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetTaskID__6CTimer", (char*) GetTaskID__6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetTaskID__C11CMailBoxMapUsRi", (char*) GetTaskID__C11CMailBoxMapUsRi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetTempTh__13CFunctionTempP10VWAS_CMD_SUl", (char*) GetTempTh__13CFunctionTempP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetTemp__13CFunctionTempP10VWAS_CMD_SUl", (char*) GetTemp__13CFunctionTempP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetTime__12CSoftUpGradeRUl", (char*) GetTime__12CSoftUpGradeRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetTimerID__6CTimer", (char*) GetTimerID__6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetTimers__13CTimerManager", (char*) GetTimers__13CTimerManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetType__C12CCtrlPackageRUc", (char*) GetType__C12CCtrlPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetType__C12CDataPackageRUc", (char*) GetType__C12CDataPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetType__C8CPackageRUc", (char*) GetType__C8CPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetVersion__C12CCtrlPackageRUc", (char*) GetVersion__C12CCtrlPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetVersion__C12CDataPackageRUc", (char*) GetVersion__C12CDataPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetVersion__C8CPackageRUc", (char*) GetVersion__C8CPackageRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl", (char*) GetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetVoltageValue__16CFunctionVoltageP10VWAS_CMD_SUl", (char*) GetVoltageValue__16CFunctionVoltageP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetVsSync__8CChannelP10VWAS_CMD_SUl", (char*) GetVsSync__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetWallUnitNoByCoordinate__4CWndRC11st_PositionRUcP18st_Sign_Board_Info", (char*) GetWallUnitNoByCoordinate__4CWndRC11st_PositionRUcP18st_Sign_Board_Info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetWhiteBalance__8CChannelP10VWAS_CMD_SUl", (char*) GetWhiteBalance__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetWindowAdj__8CDesktopP10VWAS_CMD_SUl", (char*) GetWindowAdj__8CDesktopP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetWndSignChannel__4CWndRCUcPC18st_Sign_Board_InfoPUc", (char*) GetWndSignChannel__4CWndRCUcPC18st_Sign_Board_InfoPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cClk", (char*) I2cClk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cClkCycles", (char*) I2cClkCycles, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cCpldReset", (char*) I2cCpldReset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cData", (char*) I2cData, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cDeviceBusy", (char*) I2cDeviceBusy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cInit", (char*) I2cInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cRead", (char*) I2cRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cRead1014", (char*) I2cRead1014, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadBit", (char*) I2cReadBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadByte", (char*) I2cReadByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadCpld", (char*) I2cReadCpld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadSeq", (char*) I2cReadSeq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cStop", (char*) I2cStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cWrite", (char*) I2cWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cWriteBit", (char*) I2cWriteBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cWriteByte", (char*) I2cWriteByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cWritePage", (char*) I2cWritePage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IfBoardInstall__3CNeUc", (char*) IfBoardInstall__3CNeUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IncreaseNode__10CTcpSocketi", (char*) IncreaseNode__10CTcpSocketi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitFirstRecord__5CFile", (char*) InitFirstRecord__5CFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitFunction__10CMainBoard", (char*) InitFunction__10CMainBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitFunction__6CBoard", (char*) InitFunction__6CBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitLcd__10CMainBoard", (char*) InitLcd__10CMainBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitSi5326", (char*) InitSi5326, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitSocket__9CListener", (char*) InitSocket__9CListener, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Init__11COperAndCfg", (char*) Init__11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Init__12CSoftUpGrade", (char*) Init__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Insert__11CMailBoxMapUsUlUsiUli", (char*) Insert__11CMailBoxMapUsUlUsiUli, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__10C485Client", (char*) Instance__10C485Client, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__11CEthnClient", (char*) Instance__11CEthnClient, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__11CMailBoxMap", (char*) Instance__11CMailBoxMap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__11CSocketPool", (char*) Instance__11CSocketPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__12C485NodePool", (char*) Instance__12C485NodePool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__12CTimerIDPool", (char*) Instance__12CTimerIDPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__13CAppInterface", (char*) Instance__13CAppInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__13CTimerManager", (char*) Instance__13CTimerManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__14CModuleManager", (char*) Instance__14CModuleManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__18CProtocolInterface", (char*) Instance__18CProtocolInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__9CListener", (char*) Instance__9CListener, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IsBoardExist__C12C485NodePoolUc", (char*) IsBoardExist__C12C485NodePoolUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IsBoardOnline__10C485ClientUc", (char*) IsBoardOnline__10C485ClientUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IsBoardOnline__11CEthnClientUc", (char*) IsBoardOnline__11CEthnClientUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IsBoardOnline__9CProtocolUc", (char*) IsBoardOnline__9CProtocolUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IsTimeOut__12CSoftUpGrade", (char*) IsTimeOut__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "KeepAlive__10COperationP10VWAS_CMD_SUl", (char*) KeepAlive__10COperationP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "KillTimer__13CTimerManagerUl", (char*) KillTimer__13CTimerManagerUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LedAlarmStateChg", (char*) LedAlarmStateChg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LedDrvInit", (char*) LedDrvInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LedRunStateChg", (char*) LedRunStateChg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LedStateChg", (char*) LedStateChg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ListLastMsg", (char*) ListLastMsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LoadFpga_ALTERA", (char*) LoadFpga_ALTERA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LoadFpga_LATTICE", (char*) LoadFpga_LATTICE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LoadModule__14CModuleManagerUs", (char*) LoadModule__14CModuleManagerUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LoadModule__7CModule", (char*) LoadModule__7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MAX_FAN_COUNT", (char*) MAX_FAN_COUNT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MAX_POWER_COUNT", (char*) MAX_POWER_COUNT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MC_AlarmReport", (char*) MC_AlarmReport, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MC_EventReport", (char*) MC_EventReport, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MailBoxEventHandler__14CModuleManager", (char*) MailBoxEventHandler__14CModuleManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MainCtrlMsgPrintf", (char*) MainCtrlMsgPrintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "MainCtrlTace", (char*) MainCtrlTace, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ModuleChecker__14CModuleManager", (char*) ModuleChecker__14CModuleManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ModuleLoaded__14CModuleManagerUs", (char*) ModuleLoaded__14CModuleManagerUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ModuleLoaded__7CModule", (char*) ModuleLoaded__7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Nbase__9streambuf", (char*) Nbase__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OfflineAll__Fv", (char*) OfflineAll__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OfflineNotify__9CProtocolUc", (char*) OfflineNotify__9CProtocolUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OnlineAll__Fv", (char*) OnlineAll__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OpenBus", (char*) OpenBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OpenWindow__4CWndP10VWAS_CMD_SUlUcUl", (char*) OpenWindow__4CWndP10VWAS_CMD_SUlUcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Open__5CFilePCcT1", (char*) Open__5CFilePCcT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OperRspCmdToNs__FP10VWAS_CMD_SUlUl", (char*) OperRspCmdToNs__FP10VWAS_CMD_SUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OperSendCmdToBsWaitReturn__FUcP10VWAS_CMD_SUlUlT1", (char*) OperSendCmdToBsWaitReturn__FUcP10VWAS_CMD_SUlUlT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OperSendCmdToBs__FUcP10VWAS_CMD_SUlUl", (char*) OperSendCmdToBs__FUcP10VWAS_CMD_SUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_AllocateMessage", (char*) PF_AllocateMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_CreateMailBox", (char*) PF_CreateMailBox, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_DeleteMailBox", (char*) PF_DeleteMailBox, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_FreeMessage", (char*) PF_FreeMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_GetLocalBoardID", (char*) PF_GetLocalBoardID, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_GetLocalBoardType", (char*) PF_GetLocalBoardType, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_GetMessageNumber", (char*) PF_GetMessageNumber, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_KillTimer", (char*) PF_KillTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_LoadModule", (char*) PF_LoadModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_ModuleLoaded", (char*) PF_ModuleLoaded, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_Reboot", (char*) PF_Reboot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_ReceiveMessage", (char*) PF_ReceiveMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_ReceiveUrgentFrame", (char*) PF_ReceiveUrgentFrame, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_RegisterModule", (char*) PF_RegisterModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_RegisterSystemMessage", (char*) PF_RegisterSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_SendMessage", (char*) PF_SendMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_SetTimer", (char*) PF_SetTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_Standby", (char*) PF_Standby, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_UnloadModule", (char*) PF_UnloadModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_UnregisterModule", (char*) PF_UnregisterModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PF_UnregisterSystemMessage", (char*) PF_UnregisterSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PinAClk", (char*) PinAClk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PinACs", (char*) PinACs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PinADo", (char*) PinADo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Ping", (char*) Ping, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PostSend__12CCtrlPackage", (char*) PostSend__12CCtrlPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PostSend__12CDataPackage", (char*) PostSend__12CDataPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PostSend__8CPackage", (char*) PostSend__8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Proc15Timer__12CSoftUpGrade", (char*) Proc15Timer__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcAlarmBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl", (char*) ProcAlarmBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcAlarmNsCmd__10CAlarmInfoP10VWAS_CMD_SUl", (char*) ProcAlarmNsCmd__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcAlarm__10CAlarmInfoRC13st_Alarm_Info", (char*) ProcAlarm__10CAlarmInfoRC13st_Alarm_Info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcAlarm__10CProcAlarm", (char*) ProcAlarm__10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcAlarm__3CNe", (char*) ProcAlarm__3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBdOffline__3CNeUcUs", (char*) ProcBdOffline__3CNeUcUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBdOnline__3CNeUcUs", (char*) ProcBdOnline__3CNeUcUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBdSoftAlarm__10CProcAlarm", (char*) ProcBdSoftAlarm__10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBdTempAlarm__10CProcAlarm", (char*) ProcBdTempAlarm__10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBdVoltageAlarm__10CProcAlarm", (char*) ProcBdVoltageAlarm__10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl", (char*) ProcBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__10CDataBoardP10VWAS_CMD_SUl", (char*) ProcBsCmd__10CDataBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__10CMainBoardP10VWAS_CMD_SUl", (char*) ProcBsCmd__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__10COperationP10VWAS_CMD_SUl", (char*) ProcBsCmd__10COperationP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__10CSignBoardP10VWAS_CMD_SUl", (char*) ProcBsCmd__10CSignBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__11CCrossBoardP10VWAS_CMD_SUl", (char*) ProcBsCmd__11CCrossBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__11CFunctionIPP10VWAS_CMD_SUl", (char*) ProcBsCmd__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__11COperAndCfgUcP10VWAS_CMD_SUl", (char*) ProcBsCmd__11COperAndCfgUcP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__12CFunctionLedP10VWAS_CMD_SUl", (char*) ProcBsCmd__12CFunctionLedP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__12CFunctionVerP10VWAS_CMD_SUl", (char*) ProcBsCmd__12CFunctionVerP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__12CHDDataBoardP10VWAS_CMD_SUl", (char*) ProcBsCmd__12CHDDataBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__12CSDDataBoardP10VWAS_CMD_SUl", (char*) ProcBsCmd__12CSDDataBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__13CFunctionTempP10VWAS_CMD_SUl", (char*) ProcBsCmd__13CFunctionTempP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__14C2800DataBoardP10VWAS_CMD_SUl", (char*) ProcBsCmd__14C2800DataBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__14COperAttributeP10VWAS_CMD_SUl", (char*) ProcBsCmd__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__15CFunctionInSlotP10VWAS_CMD_SUl", (char*) ProcBsCmd__15CFunctionInSlotP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__16CFunctionRestartP10VWAS_CMD_SUl", (char*) ProcBsCmd__16CFunctionRestartP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__16CFunctionVoltageP10VWAS_CMD_SUl", (char*) ProcBsCmd__16CFunctionVoltageP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__17CFunctionPortInfoP10VWAS_CMD_SUl", (char*) ProcBsCmd__17CFunctionPortInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__20CFunctionManufactureP10VWAS_CMD_SUl", (char*) ProcBsCmd__20CFunctionManufactureP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__3CNeUcP10VWAS_CMD_SUl", (char*) ProcBsCmd__3CNeUcP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__4CWndP10VWAS_CMD_SUl", (char*) ProcBsCmd__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__5CRootP10VWAS_CMD_SUl", (char*) ProcBsCmd__5CRootP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__6CBoardP10VWAS_CMD_SUl", (char*) ProcBsCmd__6CBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__6CCrossP10VWAS_CMD_SUl", (char*) ProcBsCmd__6CCrossP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__8CChannelP10VWAS_CMD_SUl", (char*) ProcBsCmd__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__8CDesktopP10VWAS_CMD_SUl", (char*) ProcBsCmd__8CDesktopP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__9CColorKeyP10VWAS_CMD_SUl", (char*) ProcBsCmd__9CColorKeyP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcBsCmd__9CFunctionP10VWAS_CMD_SUl", (char*) ProcBsCmd__9CFunctionP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcCpuUsage__10CProcAlarm", (char*) ProcCpuUsage__10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcEnvTmp__10CProcAlarm", (char*) ProcEnvTmp__10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcEventBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl", (char*) ProcEventBsCmd__10CAlarmInfoP10VWAS_CMD_SUcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcEventNsCmd__10CAlarmInfoP10VWAS_CMD_SUl", (char*) ProcEventNsCmd__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcEvent__10CAlarmInfoR13st_Event_Info", (char*) ProcEvent__10CAlarmInfoR13st_Event_Info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcFpgaStatus__10CProcAlarm", (char*) ProcFpgaStatus__10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__10CAlarmInfoP10VWAS_CMD_SUl", (char*) ProcNsCmd__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__10CDataBoardP10VWAS_CMD_SUl", (char*) ProcNsCmd__10CDataBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__10CMainBoardP10VWAS_CMD_SUl", (char*) ProcNsCmd__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__10COperationP10VWAS_CMD_SUl", (char*) ProcNsCmd__10COperationP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__10CSignBoardP10VWAS_CMD_SUl", (char*) ProcNsCmd__10CSignBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__11CBackGroundP10VWAS_CMD_SUl", (char*) ProcNsCmd__11CBackGroundP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__11CCrossBoardP10VWAS_CMD_SUl", (char*) ProcNsCmd__11CCrossBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__11CFunctionIPP10VWAS_CMD_SUl", (char*) ProcNsCmd__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__11COperAndCfgP10VWAS_CMD_SUl", (char*) ProcNsCmd__11COperAndCfgP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__12CFunctionLedP10VWAS_CMD_SUl", (char*) ProcNsCmd__12CFunctionLedP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__12CFunctionVerP10VWAS_CMD_SUl", (char*) ProcNsCmd__12CFunctionVerP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__12CHDDataBoardP10VWAS_CMD_SUl", (char*) ProcNsCmd__12CHDDataBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__12CSDDataBoardP10VWAS_CMD_SUl", (char*) ProcNsCmd__12CSDDataBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__12CSoftUpGradeP10VWAS_CMD_SUl", (char*) ProcNsCmd__12CSoftUpGradeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__13CFunctionTempP10VWAS_CMD_SUl", (char*) ProcNsCmd__13CFunctionTempP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__14C2800DataBoardP10VWAS_CMD_SUl", (char*) ProcNsCmd__14C2800DataBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__14COperAttributeP10VWAS_CMD_SUl", (char*) ProcNsCmd__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__15CFunctionInSlotP10VWAS_CMD_SUl", (char*) ProcNsCmd__15CFunctionInSlotP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__16CFunctionRestartP10VWAS_CMD_SUl", (char*) ProcNsCmd__16CFunctionRestartP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__16CFunctionVoltageP10VWAS_CMD_SUl", (char*) ProcNsCmd__16CFunctionVoltageP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__17CFunctionPortInfoP10VWAS_CMD_SUl", (char*) ProcNsCmd__17CFunctionPortInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__20CFunctionManufactureP10VWAS_CMD_SUl", (char*) ProcNsCmd__20CFunctionManufactureP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__3CNeP10VWAS_CMD_SUl", (char*) ProcNsCmd__3CNeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__4CWndP10VWAS_CMD_SUl", (char*) ProcNsCmd__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__5CRootP10VWAS_CMD_SUl", (char*) ProcNsCmd__5CRootP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__6CBoardP10VWAS_CMD_SUl", (char*) ProcNsCmd__6CBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__6CCrossP10VWAS_CMD_SUl", (char*) ProcNsCmd__6CCrossP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__8CChannelP10VWAS_CMD_SUl", (char*) ProcNsCmd__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__8CDesktopP10VWAS_CMD_SUl", (char*) ProcNsCmd__8CDesktopP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__9CColorKeyP10VWAS_CMD_SUl", (char*) ProcNsCmd__9CColorKeyP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcNsCmd__9CFunctionP10VWAS_CMD_SUl", (char*) ProcNsCmd__9CFunctionP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcProtocalVer1__10CAlarmInfoPUc", (char*) ProcProtocalVer1__10CAlarmInfoPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcProtocalVer1__11COperAndCfgPUc", (char*) ProcProtocalVer1__11COperAndCfgPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcProtocalVer1__12CSoftUpGradePUc", (char*) ProcProtocalVer1__12CSoftUpGradePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcProtocalVer2__10CAlarmInfoPUc", (char*) ProcProtocalVer2__10CAlarmInfoPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcProtocalVer2__11COperAndCfgPUc", (char*) ProcProtocalVer2__11COperAndCfgPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcProtocalVer2__12CSoftUpGradePUc", (char*) ProcProtocalVer2__12CSoftUpGradePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcTimer__10CAlarmInfo", (char*) ProcTimer__10CAlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcTimer__10CMainBoard", (char*) ProcTimer__10CMainBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcTimer__10COperation", (char*) ProcTimer__10COperation, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcTimer__10CTcpSocket", (char*) ProcTimer__10CTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcTimer__11COperAndCfg", (char*) ProcTimer__11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcTimer__12CSoftUpGrade", (char*) ProcTimer__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcTimer__3CNe", (char*) ProcTimer__3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ProcTimer__6CBoard", (char*) ProcTimer__6CBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReadFirstRecord__5CFileR19st_File_Config_Info", (char*) ReadFirstRecord__5CFileR19st_File_Config_Info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReadLM73", (char*) ReadLM73, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Read__5CFileUlUlPUc", (char*) Read__5CFileUlUlPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Reboot__14CModuleManagerUc", (char*) Reboot__14CModuleManagerUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveAction__12CCtrlPackageP9CProtocoll", (char*) ReceiveAction__12CCtrlPackageP9CProtocoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveAction__12CDataPackageP9CProtocoll", (char*) ReceiveAction__12CDataPackageP9CProtocoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveAction__14COnLinePackageP9CProtocoll", (char*) ReceiveAction__14COnLinePackageP9CProtocoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveAction__17CKeepAlivePackageP9CProtocoll", (char*) ReceiveAction__17CKeepAlivePackageP9CProtocoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveAction__8CPackageP9CProtocoll", (char*) ReceiveAction__8CPackageP9CProtocoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveBsBlockMsg__11COperAndCfg", (char*) ReceiveBsBlockMsg__11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveBsMsg__10CAlarmInfo", (char*) ReceiveBsMsg__10CAlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveBsMsg__11COperAndCfg", (char*) ReceiveBsMsg__11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveFrameCallBack__10C485ClientUlPUc", (char*) ReceiveFrameCallBack__10C485ClientUlPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveMessage__13CAppInterfaceUsP9S_MESSAGEi", (char*) ReceiveMessage__13CAppInterfaceUsP9S_MESSAGEi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveNsCancelMsg__12CSoftUpGrade", (char*) ReceiveNsCancelMsg__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveNsMsg__10CAlarmInfo", (char*) ReceiveNsMsg__10CAlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveNsMsg__11COperAndCfg", (char*) ReceiveNsMsg__11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceiveNsMsg__12CSoftUpGrade", (char*) ReceiveNsMsg__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReceivePackage__11CEthnClientRCl", (char*) ReceivePackage__11CEthnClientRCl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RegisterModule__14CModuleManagerUsUsPFUl_lUlT3Ul", (char*) RegisterModule__14CModuleManagerUsUsPFUl_lUlT3Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RegisterNotify__9CProtocolUcPFUlUc_v", (char*) RegisterNotify__9CProtocolUcPFUlUc_v, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RegisterSystemMessage__14CModuleManagerUsUs", (char*) RegisterSystemMessage__14CModuleManagerUsUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Remove485Node__12C485NodePoolUc", (char*) Remove485Node__12C485NodePoolUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemoveSocketNode__11CSocketPoolRCl", (char*) RemoveSocketNode__11CSocketPoolRCl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RemoveWindow__4CWndP10VWAS_CMD_SUl", (char*) RemoveWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReportWriteFlashProgress__12CSoftUpGradePUlT1", (char*) ReportWriteFlashProgress__12CSoftUpGradePUlT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetDumbTimes__11CSocketNode", (char*) ResetDumbTimes__11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetDumbTimes__9CLinkNode", (char*) ResetDumbTimes__9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetErrorTimes__11CSocketNode", (char*) ResetErrorTimes__11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetErrorTimes__11CSocketPoolRCl", (char*) ResetErrorTimes__11CSocketPoolRCl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetErrorTimes__12C485NodePoolUc", (char*) ResetErrorTimes__12C485NodePoolUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetErrorTimes__9CLinkNode", (char*) ResetErrorTimes__9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetFpga_ALTERA", (char*) ResetFpga_ALTERA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetFpga_LATTICE", (char*) ResetFpga_LATTICE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetKeepAliveTimer__10C485Clientl", (char*) ResetKeepAliveTimer__10C485Clientl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetKeepAliveTimer__11CEthnClientl", (char*) ResetKeepAliveTimer__11CEthnClientl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetKeepAliveTimer__11CSocketPoolRCl", (char*) ResetKeepAliveTimer__11CSocketPoolRCl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetKeepAliveTimer__12C485NodePoolUc", (char*) ResetKeepAliveTimer__12C485NodePoolUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetKeepAliveTimer__9CProtocoll", (char*) ResetKeepAliveTimer__9CProtocoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetKeepAlive__10C485Client", (char*) ResetKeepAlive__10C485Client, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetWindow__4CWndP10VWAS_CMD_SUl", (char*) ResetWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Reset__6CTimer", (char*) Reset__6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RestartBoard__16CFunctionRestartP10VWAS_CMD_SUl", (char*) RestartBoard__16CFunctionRestartP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResumeInitInfo__10CSignBoardUc", (char*) ResumeInitInfo__10CSignBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResumeInitInfo__6CBoardUc", (char*) ResumeInitInfo__6CBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResumeWindow__4CWndUc", (char*) ResumeWindow__4CWndUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspAutoWhiteBalance__8CChannelP10VWAS_CMD_SUl", (char*) RspAutoWhiteBalance__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspClrLed__12CFunctionLedP10VWAS_CMD_SUl", (char*) RspClrLed__12CFunctionLedP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspCmdToNs__10CTcpSocketP10VWAS_CMD_SUlUl", (char*) RspCmdToNs__10CTcpSocketP10VWAS_CMD_SUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspErrToNs__11CBackGroundUsP10VWAS_CMD_SUl", (char*) RspErrToNs__11CBackGroundUsP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspErrToNs__4CWndUsP10VWAS_CMD_SUl", (char*) RspErrToNs__4CWndUsP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspFreezeChannel__8CChannelP10VWAS_CMD_SUl", (char*) RspFreezeChannel__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetChannelOffset__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetChannelOffset__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetColorKey__9CColorKeyP10VWAS_CMD_SUl", (char*) RspGetColorKey__9CColorKeyP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetColorKiller__8CChannelP10VWAS_CMD_SUl", (char*) RspGetColorKiller__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetCutArea__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetCutArea__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetGatherChannelStat__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetGatherChannelStat__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetGatherOffset__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetGatherOffset__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetGatherSignFormat__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetGatherSignFormat__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetIP__11CFunctionIPP10VWAS_CMD_SUl", (char*) RspGetIP__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl", (char*) RspGetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetNetStatus__11CFunctionIPP10VWAS_CMD_SUl", (char*) RspGetNetStatus__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetPortInfo__17CFunctionPortInfoP10VWAS_CMD_SUl", (char*) RspGetPortInfo__17CFunctionPortInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl", (char*) RspGetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetSysSync__8CChannelP10VWAS_CMD_SUl", (char*) RspGetSysSync__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetTempTh__13CFunctionTempP10VWAS_CMD_SUl", (char*) RspGetTempTh__13CFunctionTempP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetTemp__13CFunctionTempP10VWAS_CMD_SUl", (char*) RspGetTemp__13CFunctionTempP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl", (char*) RspGetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetWhiteBalance__8CChannelP10VWAS_CMD_SUl", (char*) RspGetWhiteBalance__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspGetWindowAdj__8CDesktopP10VWAS_CMD_SUl", (char*) RspGetWindowAdj__8CDesktopP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspHardVer__12CFunctionVerP10VWAS_CMD_SUl", (char*) RspHardVer__12CFunctionVerP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspRestartBoard__16CFunctionRestartP10VWAS_CMD_SUl", (char*) RspRestartBoard__16CFunctionRestartP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetChannelOffset__14COperAttributeP10VWAS_CMD_SUl", (char*) RspSetChannelOffset__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetChannelsOff__8CChannelP10VWAS_CMD_SUl", (char*) RspSetChannelsOff__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetChannelsOn__8CChannelP10VWAS_CMD_SUl", (char*) RspSetChannelsOn__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetColorKey__9CColorKeyP10VWAS_CMD_SUl", (char*) RspSetColorKey__9CColorKeyP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetColorKiller__8CChannelP10VWAS_CMD_SUl", (char*) RspSetColorKiller__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetCutArea__14COperAttributeP10VWAS_CMD_SUl", (char*) RspSetCutArea__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl", (char*) RspSetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetGatherOffset__14COperAttributeP10VWAS_CMD_SUl", (char*) RspSetGatherOffset__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl", (char*) RspSetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl", (char*) RspSetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetIP__11CFunctionIPP10VWAS_CMD_SUl", (char*) RspSetIP__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl", (char*) RspSetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetNetStatus__11CFunctionIPP10VWAS_CMD_SUl", (char*) RspSetNetStatus__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl", (char*) RspSetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetSysSync__8CChannelP10VWAS_CMD_SUl", (char*) RspSetSysSync__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetTempTh__13CFunctionTempP10VWAS_CMD_SUl", (char*) RspSetTempTh__13CFunctionTempP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl", (char*) RspSetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetWhiteBalance__8CChannelP10VWAS_CMD_SUl", (char*) RspSetWhiteBalance__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSetWindowAdj__8CDesktopP10VWAS_CMD_SUl", (char*) RspSetWindowAdj__8CDesktopP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSoftStatus__12CFunctionVerP10VWAS_CMD_SUl", (char*) RspSoftStatus__12CFunctionVerP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspSoftVer__12CFunctionVerP10VWAS_CMD_SUl", (char*) RspSoftVer__12CFunctionVerP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspTopWindow__4CWndP10VWAS_CMD_SUl", (char*) RspTopWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspViewLoopOff__8CChannelP10VWAS_CMD_SUl", (char*) RspViewLoopOff__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspViewLoopOn__8CChannelP10VWAS_CMD_SUl", (char*) RspViewLoopOn__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "RspVoltageValue__16CFunctionVoltageP10VWAS_CMD_SUl", (char*) RspVoltageValue__16CFunctionVoltageP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendCmdToBsWaitReturn__11COperAndCfgUcPP10VWAS_CMD_SUlUlUlUlUlP10VWAS_CMD_S", (char*) SendCmdToBsWaitReturn__11COperAndCfgUcPP10VWAS_CMD_SUlUlUlUlUlP10VWAS_CMD_S, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendCmdToBs__11COperAndCfgUcPP10VWAS_CMD_SUlUlUlUlUl", (char*) SendCmdToBs__11COperAndCfgUcPP10VWAS_CMD_SUlUlUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendMessage__13CAppInterfaceP9S_MESSAGE", (char*) SendMessage__13CAppInterfaceP9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendMessage__18CProtocolInterfaceR9S_MESSAGE", (char*) SendMessage__18CProtocolInterfaceR9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendMsg2Lcd", (char*) SendMsg2Lcd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendMsgToMailBox__10CTcpSocketPUcUliUl", (char*) SendMsgToMailBox__10CTcpSocketPUcUliUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendMsgToMailBox__15CDebugTcpSocketPUcUliUl", (char*) SendMsgToMailBox__15CDebugTcpSocketPUcUliUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendPackage__9CProtocolR8CPackage", (char*) SendPackage__9CProtocolR8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendStartupMessageToServer__14CModuleManagerUc", (char*) SendStartupMessageToServer__14CModuleManagerUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Send__10C485ClientP8CPackage", (char*) Send__10C485ClientP8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Send__11CEthnClientP8CPackage", (char*) Send__11CEthnClientP8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SerializePackage__9CProtocolPUcRP8CPackage", (char*) SerializePackage__9CProtocolPUcRP8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetAlarmAutoReport__10CAlarmInfoP10VWAS_CMD_SUl", (char*) SetAlarmAutoReport__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBackGround__11CBackGroundP10VWAS_CMD_SUl", (char*) SetBackGround__11CBackGroundP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardID__11CSocketNodeUc", (char*) SetBoardID__11CSocketNodeUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardID__11CSocketPoollUc", (char*) SetBoardID__11CSocketPoollUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardID__9CLinkNodeUc", (char*) SetBoardID__9CLinkNodeUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardInfo__10C485ClientlUcUc", (char*) SetBoardInfo__10C485ClientlUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardInfo__11CEthnClientlUcUc", (char*) SetBoardInfo__11CEthnClientlUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardInfo__9CProtocollUcUc", (char*) SetBoardInfo__9CProtocollUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardType__11CSocketNodeUc", (char*) SetBoardType__11CSocketNodeUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardType__11CSocketPoollUc", (char*) SetBoardType__11CSocketPoollUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardType__12C485NodePoolUcUc", (char*) SetBoardType__12C485NodePoolUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBoardType__9CLinkNodeUc", (char*) SetBoardType__9CLinkNodeUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBuzzer__10CMainBoardP10VWAS_CMD_SUl", (char*) SetBuzzer__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetChannelOffset__14COperAttributeP10VWAS_CMD_SUl", (char*) SetChannelOffset__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetChannelsOff__8CChannelP10VWAS_CMD_SUl", (char*) SetChannelsOff__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetChannelsOn__8CChannelP10VWAS_CMD_SUl", (char*) SetChannelsOn__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetColorKey__9CColorKeyP10VWAS_CMD_SUl", (char*) SetColorKey__9CColorKeyP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetColorKiller__8CChannelP10VWAS_CMD_SUl", (char*) SetColorKiller__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetCross__6CCrossUcUcPUcUc", (char*) SetCross__6CCrossUcUcPUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetCutArea__14COperAttributeP10VWAS_CMD_SUl", (char*) SetCutArea__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetCutWindow__4CWndP10VWAS_CMD_SUl", (char*) SetCutWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetDateTime__10CMainBoardP10VWAS_CMD_SUl", (char*) SetDateTime__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetDebugSwitch", (char*) SetDebugSwitch, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetDestTop__11CBackGroundP10VWAS_CMD_SUl", (char*) SetDestTop__11CBackGroundP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl", (char*) SetElectricityPashic__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetEventAutoReport__10CAlarmInfoP10VWAS_CMD_SUl", (char*) SetEventAutoReport__10CAlarmInfoP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetGatherOffset__14COperAttributeP10VWAS_CMD_SUl", (char*) SetGatherOffset__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl", (char*) SetGatherPhasic__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl", (char*) SetGatherSignPara__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetHeadPointer__8CPackagePCUc", (char*) SetHeadPointer__8CPackagePCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetIPAddress__11CSocketNodeUl", (char*) SetIPAddress__11CSocketNodeUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetIP__11CFunctionIPP10VWAS_CMD_SUl", (char*) SetIP__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetInfoDisplay__11CBackGroundP10VWAS_CMD_SUl", (char*) SetInfoDisplay__11CBackGroundP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetMainCtrlOnLine__3CNe", (char*) SetMainCtrlOnLine__3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl", (char*) SetManInfo__20CFunctionManufactureP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetNetStatus__11CFunctionIPP10VWAS_CMD_SUl", (char*) SetNetStatus__11CFunctionIPP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetRcvCtrlPackages__15CPackageCounterUl", (char*) SetRcvCtrlPackages__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetRcvDataPackages__15CPackageCounterUl", (char*) SetRcvDataPackages__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetRcvNormalPackages__15CPackageCounterUl", (char*) SetRcvNormalPackages__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetReceiveOKTimes__15CPackageCounterUl", (char*) SetReceiveOKTimes__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetReceiveTimes__15CPackageCounterUl", (char*) SetReceiveTimes__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetRtc", (char*) SetRtc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSendCtrlPackages__15CPackageCounterUl", (char*) SetSendCtrlPackages__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSendDataPackages__15CPackageCounterUl", (char*) SetSendDataPackages__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSendOKTimes__15CPackageCounterUl", (char*) SetSendOKTimes__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSendTimes__15CPackageCounterUl", (char*) SetSendTimes__15CPackageCounterUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSequenceNumber__12CCtrlPackageUs", (char*) SetSequenceNumber__12CCtrlPackageUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSequenceNumber__12CDataPackageUs", (char*) SetSequenceNumber__12CDataPackageUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSequenceNumber__8CPackageUs", (char*) SetSequenceNumber__8CPackageUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSi5326Reg", (char*) SetSi5326Reg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl", (char*) SetSignBoardInitInfo__14COperAttributeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSocketOption__9CListenerl", (char*) SetSocketOption__9CListenerl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSocket__11CSocketNodel", (char*) SetSocket__11CSocketNodel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSoftPara__10CMainBoardP10VWAS_CMD_SUl", (char*) SetSoftPara__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSysInitInfo__10CMainBoardP10VWAS_CMD_SUl", (char*) SetSysInitInfo__10CMainBoardP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSysSync__8CChannelP10VWAS_CMD_SUl", (char*) SetSysSync__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetTempTh__13CFunctionTempP10VWAS_CMD_SUl", (char*) SetTempTh__13CFunctionTempP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetTestMap__11CBackGroundP10VWAS_CMD_SUl", (char*) SetTestMap__11CBackGroundP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetTimer__13CTimerManagerP6CTimer", (char*) SetTimer__13CTimerManagerP6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetTimer__13CTimerManagerRPt12PF_list_node1ZP6CTimer", (char*) SetTimer__13CTimerManagerRPt12PF_list_node1ZP6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetTimer__13CTimerManagerlUlUcUl", (char*) SetTimer__13CTimerManagerlUlUcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl", (char*) SetVoltageTh__16CFunctionVoltageP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetVsSync__8CChannelP10VWAS_CMD_SUl", (char*) SetVsSync__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetWhiteBalance__8CChannelP10VWAS_CMD_SUl", (char*) SetWhiteBalance__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetWindowAdj__8CDesktopP10VWAS_CMD_SUl", (char*) SetWindowAdj__8CDesktopP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ShowWindow__4CWndP10VWAS_CMD_SUl", (char*) ShowWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Socket2BoardID__11CSocketPoollRUc", (char*) Socket2BoardID__11CSocketPoollRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SoftRspCmdToNs__FP10VWAS_CMD_SUlUl", (char*) SoftRspCmdToNs__FP10VWAS_CMD_SUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SoftwareIsCorrect__12CSoftUpGrade", (char*) SoftwareIsCorrect__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi0Test", (char*) Spi0Test, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiInit", (char*) SpiInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiRead", (char*) SpiRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiReadBit", (char*) SpiReadBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiReadByte", (char*) SpiReadByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiWrite", (char*) SpiWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiWriteBit", (char*) SpiWriteBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiWriteByte", (char*) SpiWriteByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Standby__14CModuleManagerUc", (char*) Standby__14CModuleManagerUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "StartAccept__10CTcpSocket", (char*) StartAccept__10CTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "StartRecv__10CTcpSocketUl", (char*) StartRecv__10CTcpSocketUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Startup__14CModuleManagerUcUc", (char*) Startup__14CModuleManagerUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SystemMessage__14CModuleManagerR14CSystemMessage", (char*) SystemMessage__14CModuleManagerR14CSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SystemMessage__7CModuleR14CSystemMessage", (char*) SystemMessage__7CModuleR14CSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TASKID_ALARMEVENT", (char*) &TASKID_ALARMEVENT, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "TASKID_CFGOPER", (char*) &TASKID_CFGOPER, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "TASKID_UPGRADE", (char*) &TASKID_UPGRADE, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "TAlarmEvent_ReceiveTask__10CAlarmInfoPv", (char*) TAlarmEvent_ReceiveTask__10CAlarmInfoPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TCFGOPER_ReceiveBsTaskBlock__11COperAndCfgPv", (char*) TCFGOPER_ReceiveBsTaskBlock__11COperAndCfgPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TCFGOPER_ReceiveTask__11COperAndCfgPv", (char*) TCFGOPER_ReceiveTask__11COperAndCfgPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TUpgrade_CancelTask__12CSoftUpGradePv", (char*) TUpgrade_CancelTask__12CSoftUpGradePv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TUpgrade_ReceiveTask__12CSoftUpGradePv", (char*) TUpgrade_ReceiveTask__12CSoftUpGradePv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TempTest", (char*) TempTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestBoardInstalled__3CNe", (char*) TestBoardInstalled__3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestBspTimer", (char*) TestBspTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestCpld", (char*) TestCpld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestLm73", (char*) TestLm73, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Tick__14CPeriodicTimer", (char*) Tick__14CPeriodicTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Tick__6CTimer", (char*) Tick__6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TopWindow__4CWndP10VWAS_CMD_SUl", (char*) TopWindow__4CWndP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TransFileBegin__12CSoftUpGradeP10VWAS_CMD_SUl", (char*) TransFileBegin__12CSoftUpGradeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TransFileEnd__12CSoftUpGradeP10VWAS_CMD_SUl", (char*) TransFileEnd__12CSoftUpGradeP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Uninstance__10C485Client", (char*) Uninstance__10C485Client, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Uninstance__11CEthnClient", (char*) Uninstance__11CEthnClient, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UnloadModule__14CModuleManagerUs", (char*) UnloadModule__14CModuleManagerUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UnloadModule__7CModule", (char*) UnloadModule__7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UnregisterModule__14CModuleManagerUs", (char*) UnregisterModule__14CModuleManagerUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UnregisterSystemMessage__14CModuleManagerUsUs", (char*) UnregisterSystemMessage__14CModuleManagerUsUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UpdateConfigureInfo__5CFileR19st_File_Config_Info", (char*) UpdateConfigureInfo__5CFileR19st_File_Config_Info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyJobAdd", (char*) UrgencyJobAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyJobAlloc", (char*) UrgencyJobAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyLibInit", (char*) UrgencyLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyShow", (char*) UrgencyShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyStart", (char*) UrgencyStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyStop", (char*) UrgencyStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyTask", (char*) UrgencyTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_AddExcHook", (char*) VOS_AddExcHook, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_CloseSocket", (char*) VOS_CloseSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_ConnectClk", (char*) VOS_ConnectClk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_CreateBSem", (char*) VOS_CreateBSem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_CreateCSem", (char*) VOS_CreateCSem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_CreateMSem", (char*) VOS_CreateMSem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_CreateMsgQue", (char*) VOS_CreateMsgQue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_CreateTask", (char*) VOS_CreateTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_DelayTask", (char*) VOS_DelayTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_DeleteMsgQue", (char*) VOS_DeleteMsgQue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_DeleteSem", (char*) VOS_DeleteSem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_DeleteTask", (char*) VOS_DeleteTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_Display", (char*) VOS_Display, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GetBoardID", (char*) VOS_GetBoardID, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GetBoardType", (char*) VOS_GetBoardType, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GetErrno", (char*) VOS_GetErrno, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GetMsgNum", (char*) VOS_GetMsgNum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GetPriority", (char*) VOS_GetPriority, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GetSelfTaskID", (char*) VOS_GetSelfTaskID, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GetSysClkRate", (char*) VOS_GetSysClkRate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GetTick", (char*) VOS_GetTick, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_GiveSem", (char*) VOS_GiveSem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_InitVOS", (char*) VOS_InitVOS, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_ReceiveEvent", (char*) VOS_ReceiveEvent, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_ReceiveMsg", (char*) VOS_ReceiveMsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_ResumeTask", (char*) VOS_ResumeTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_SendEvent", (char*) VOS_SendEvent, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_SendMsg", (char*) VOS_SendMsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_SetIOControl", (char*) VOS_SetIOControl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_SetPriority", (char*) VOS_SetPriority, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_SetSysClkRate", (char*) VOS_SetSysClkRate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_SuspendSelf", (char*) VOS_SuspendSelf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_SuspendTask", (char*) VOS_SuspendTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "VOS_TakeSem", (char*) VOS_TakeSem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ViewLoopOff__8CChannelP10VWAS_CMD_SUl", (char*) ViewLoopOff__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ViewLoopOn__8CChannelP10VWAS_CMD_SUl", (char*) ViewLoopOn__8CChannelP10VWAS_CMD_SUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "W2BY", (char*) W2BY, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "W2DW", (char*) W2DW, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WDCallBack__13CTimerManagerl", (char*) WDCallBack__13CTimerManagerl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WndHandleIsExist__4CWndUl", (char*) WndHandleIsExist__4CWndUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WriteLM73", (char*) WriteLM73, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WriteMessage__14CSystemMessagePUc", (char*) WriteMessage__14CSystemMessagePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WriteMessage__21COfflineSystemMessagePUc", (char*) WriteMessage__21COfflineSystemMessagePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WriteMessage__21CStartupSystemMessagePUc", (char*) WriteMessage__21CStartupSystemMessagePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WriteSoftwareToFlash__12CSoftUpGrade", (char*) WriteSoftwareToFlash__12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Write__5CFilePCUc", (char*) Write__5CFilePCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10C485Client", (char*) _$_10C485Client, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CAlarmFile", (char*) _$_10CAlarmFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CAlarmInfo", (char*) _$_10CAlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CAlarmProc", (char*) _$_10CAlarmProc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CDataBoard", (char*) _$_10CDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CEventFile", (char*) _$_10CEventFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CMainBoard", (char*) _$_10CMainBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10COperation", (char*) _$_10COperation, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CProcAlarm", (char*) _$_10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CSignBoard", (char*) _$_10CSignBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10CTcpSocket", (char*) _$_10CTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10bad_typeid", (char*) _$_10bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11CBackGround", (char*) _$_11CBackGround, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11CCrossBoard", (char*) _$_11CCrossBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11CEthnClient", (char*) _$_11CEthnClient, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11CFunctionIP", (char*) _$_11CFunctionIP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11CMailBoxMap", (char*) _$_11CMailBoxMap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11CMemoryPool", (char*) _$_11CMemoryPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11COperAndCfg", (char*) _$_11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11CSocketNode", (char*) _$_11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11CSocketPool", (char*) _$_11CSocketPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12C485NodePool", (char*) _$_12C485NodePool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12CCtrlPackage", (char*) _$_12CCtrlPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12CDataPackage", (char*) _$_12CDataPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12CFunctionLed", (char*) _$_12CFunctionLed, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12CFunctionVer", (char*) _$_12CFunctionVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12CHDDataBoard", (char*) _$_12CHDDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12CSDDataBoard", (char*) _$_12CSDDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12CSoftUpGrade", (char*) _$_12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12CTimerIDPool", (char*) _$_12CTimerIDPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12streammarker", (char*) _$_12streammarker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_13CAppInterface", (char*) _$_13CAppInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_13CFunctionTemp", (char*) _$_13CFunctionTemp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_13CTimerManager", (char*) _$_13CTimerManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_13bad_exception", (char*) _$_13bad_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_14C2800DataBoard", (char*) _$_14C2800DataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_14CModuleManager", (char*) _$_14CModuleManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_14COnLinePackage", (char*) _$_14COnLinePackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_14COperAttribute", (char*) _$_14COperAttribute, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_14CSystemMessage", (char*) _$_14CSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_14__si_type_info", (char*) _$_14__si_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_15CDebugTcpSocket", (char*) _$_15CDebugTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_15CFunctionInSlot", (char*) _$_15CFunctionInSlot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_15CPackageCounter", (char*) _$_15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_16CFunctionRestart", (char*) _$_16CFunctionRestart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_16CFunctionVoltage", (char*) _$_16CFunctionVoltage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_16__user_type_info", (char*) _$_16__user_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_17CFunctionPortInfo", (char*) _$_17CFunctionPortInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_17CKeepAlivePackage", (char*) _$_17CKeepAlivePackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_17__class_type_info", (char*) _$_17__class_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_18CProtocolInterface", (char*) _$_18CProtocolInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_20CFunctionManufacture", (char*) _$_20CFunctionManufacture, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_20CRebootSystemMessage", (char*) _$_20CRebootSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_21COfflineSystemMessage", (char*) _$_21COfflineSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_21CStandbySystemMessage", (char*) _$_21CStandbySystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_21CStartupSystemMessage", (char*) _$_21CStartupSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_22_IO_istream_withassign", (char*) _$_22_IO_istream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_22_IO_ostream_withassign", (char*) _$_22_IO_ostream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_3CNe", (char*) _$_3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_3ios", (char*) _$_3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_4CWnd", (char*) _$_4CWnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_5CFile", (char*) _$_5CFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_5CRoot", (char*) _$_5CRoot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_6CBoard", (char*) _$_6CBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_6CCross", (char*) _$_6CCross, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_6CTimer", (char*) _$_6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7CModule", (char*) _$_7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7filebuf", (char*) _$_7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7istream", (char*) _$_7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7ostream", (char*) _$_7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_8CChannel", (char*) _$_8CChannel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_8CDesktop", (char*) _$_8CDesktop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_8CPackage", (char*) _$_8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_8bad_cast", (char*) _$_8bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_8iostream", (char*) _$_8iostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9CColorKey", (char*) _$_9CColorKey, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9CFunction", (char*) _$_9CFunction, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9CLinkNode", (char*) _$_9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9CListener", (char*) _$_9CListener, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9CProtocol", (char*) _$_9CProtocol, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9bad_alloc", (char*) _$_9bad_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9exception", (char*) _$_9exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9streambuf", (char*) _$_9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9type_info", (char*) _$_9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q2t24__default_alloc_template2b1i05_Lock", (char*) _$_Q2t24__default_alloc_template2b1i05_Lock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_10C485Client$m_spInstance", (char*) &_10C485Client$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_10CAlarmInfo$m_pAlarmFile", (char*) &_10CAlarmInfo$m_pAlarmFile, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_10CAlarmInfo$m_pEventFile", (char*) &_10CAlarmInfo$m_pEventFile, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_10CProcAlarm$m_pInstance", (char*) &_10CProcAlarm$m_pInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_11CEthnClient$m_spInstance", (char*) &_11CEthnClient$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_11CMailBoxMap$m_spInstance", (char*) &_11CMailBoxMap$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_11COperAndCfg$m_pInstance", (char*) &_11COperAndCfg$m_pInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_11CSocketPool$m_spInstance", (char*) &_11CSocketPool$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_12C485NodePool$m_spInstance", (char*) &_12C485NodePool$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_12CSoftUpGrade$m_pUpgrade", (char*) &_12CSoftUpGrade$m_pUpgrade, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_12CSoftUpGrade$m_slRspWriteFlashResult", (char*) &_12CSoftUpGrade$m_slRspWriteFlashResult, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_12CTimerIDPool$m_pclaInstance", (char*) &_12CTimerIDPool$m_pclaInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_13CAppInterface$m_spInstance", (char*) &_13CAppInterface$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_13CCfgTcpSocket$m_pCfgTcpSocket", (char*) &_13CCfgTcpSocket$m_pCfgTcpSocket, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_13CTimerManager$m_pclaInstance", (char*) &_13CTimerManager$m_pclaInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_14CModuleManager$m_spInstance", (char*) &_14CModuleManager$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_14CSoftTcpSocket$m_pSoftTcpSocket", (char*) &_14CSoftTcpSocket$m_pSoftTcpSocket, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_15CAlarmTcpSocket$m_pAlarmTcpSocket", (char*) &_15CAlarmTcpSocket$m_pAlarmTcpSocket, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_15CDebugTcpSocket$m_pDebugTcpSocket", (char*) &_15CDebugTcpSocket$m_pDebugTcpSocket, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_18CProtocolInterface$m_spInstance", (char*) &_18CProtocolInterface$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_4CWnd$m_dwWndHwnd", (char*) &_4CWnd$m_dwWndHwnd, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_7filebuf$openprot", (char*) _7filebuf$openprot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_9CListener$m_spInstance", (char*) &_9CListener$m_spInstance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_GLOBAL_$D$MAX_POWER_COUNT", (char*) _GLOBAL_$D$MAX_POWER_COUNT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$MC_AlarmReport", (char*) _GLOBAL_$D$MC_AlarmReport, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_11CMailBoxMap$m_spInstance", (char*) _GLOBAL_$D$_11CMailBoxMap$m_spInstance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_11CSocketPool$m_spInstance", (char*) _GLOBAL_$D$_11CSocketPool$m_spInstance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_12C485NodePool$m_spInstance", (char*) _GLOBAL_$D$_12C485NodePool$m_spInstance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_12CSoftUpGrade$m_pUpgrade", (char*) _GLOBAL_$D$_12CSoftUpGrade$m_pUpgrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_4CWnd$m_dwWndHwnd", (char*) _GLOBAL_$D$_4CWnd$m_dwWndHwnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_IO_stdin_", (char*) _GLOBAL_$D$_IO_stdin_, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__11CMemoryPoolUlUlUc", (char*) _GLOBAL_$D$__11CMemoryPoolUlUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_t24__default_alloc_template2b1i0$_S_end_free", (char*) _GLOBAL_$D$_t24__default_alloc_template2b1i0$_S_end_free, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_un_link__9streambuf", (char*) _GLOBAL_$D$_un_link__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$g_AlarmInfo", (char*) _GLOBAL_$D$g_AlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$g_dwStartTimeSec", (char*) _GLOBAL_$D$g_dwStartTimeSec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$MAX_POWER_COUNT", (char*) _GLOBAL_$I$MAX_POWER_COUNT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$MC_AlarmReport", (char*) _GLOBAL_$I$MC_AlarmReport, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_11CMailBoxMap$m_spInstance", (char*) _GLOBAL_$I$_11CMailBoxMap$m_spInstance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_11CSocketPool$m_spInstance", (char*) _GLOBAL_$I$_11CSocketPool$m_spInstance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_12C485NodePool$m_spInstance", (char*) _GLOBAL_$I$_12C485NodePool$m_spInstance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_12CSoftUpGrade$m_pUpgrade", (char*) _GLOBAL_$I$_12CSoftUpGrade$m_pUpgrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_4CWnd$m_dwWndHwnd", (char*) _GLOBAL_$I$_4CWnd$m_dwWndHwnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_IO_stdin_", (char*) _GLOBAL_$I$_IO_stdin_, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__11CMemoryPoolUlUlUc", (char*) _GLOBAL_$I$__11CMemoryPoolUlUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_t24__default_alloc_template2b1i0$_S_end_free", (char*) _GLOBAL_$I$_t24__default_alloc_template2b1i0$_S_end_free, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_un_link__9streambuf", (char*) _GLOBAL_$I$_un_link__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$g_AlarmInfo", (char*) _GLOBAL_$I$g_AlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$g_CommVer1", (char*) _GLOBAL_$I$g_CommVer1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$g_dwStartTimeSec", (char*) _GLOBAL_$I$g_dwStartTimeSec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_adjust_column", (char*) _IO_adjust_column, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_cleanup", (char*) _IO_cleanup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_cleanup_registration_needed", (char*) &_IO_cleanup_registration_needed, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_IO_default_doallocate", (char*) _IO_default_doallocate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_finish", (char*) _IO_default_finish, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_pbackfail", (char*) _IO_default_pbackfail, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_read", (char*) _IO_default_read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_seek", (char*) _IO_default_seek, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_seekoff", (char*) _IO_default_seekoff, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_seekpos", (char*) _IO_default_seekpos, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_setbuf", (char*) _IO_default_setbuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_stat", (char*) _IO_default_stat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_sync", (char*) _IO_default_sync, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_uflow", (char*) _IO_default_uflow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_underflow", (char*) _IO_default_underflow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_write", (char*) _IO_default_write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_xsgetn", (char*) _IO_default_xsgetn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_default_xsputn", (char*) _IO_default_xsputn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_do_write", (char*) _IO_do_write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_doallocbuf", (char*) _IO_doallocbuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_dtoa", (char*) _IO_dtoa, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_attach", (char*) _IO_file_attach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_close", (char*) _IO_file_close, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_close_it", (char*) _IO_file_close_it, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_doallocate", (char*) _IO_file_doallocate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_finish", (char*) _IO_file_finish, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_fopen", (char*) _IO_file_fopen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_init", (char*) _IO_file_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_jumps", (char*) &_IO_file_jumps, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_IO_file_overflow", (char*) _IO_file_overflow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_read", (char*) _IO_file_read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_seek", (char*) _IO_file_seek, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_seekoff", (char*) _IO_file_seekoff, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_setbuf", (char*) _IO_file_setbuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_stat", (char*) _IO_file_stat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_sync", (char*) _IO_file_sync, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_underflow", (char*) _IO_file_underflow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_write", (char*) _IO_file_write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_file_xsputn", (char*) _IO_file_xsputn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_flush_all", (char*) _IO_flush_all, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_flush_all_linebuffered", (char*) _IO_flush_all_linebuffered, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_free_backup_area", (char*) _IO_free_backup_area, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_getc", (char*) _IO_getc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_getline", (char*) _IO_getline, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_getline_info", (char*) _IO_getline_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_init", (char*) _IO_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_init_marker", (char*) _IO_init_marker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_link_in", (char*) _IO_link_in, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_list_all", (char*) &_IO_list_all, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_IO_marker_delta", (char*) _IO_marker_delta, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_marker_difference", (char*) _IO_marker_difference, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_outfloat", (char*) _IO_outfloat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_padn", (char*) _IO_padn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_peekc_locked", (char*) _IO_peekc_locked, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_putc", (char*) _IO_putc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_remove_marker", (char*) _IO_remove_marker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_seekmark", (char*) _IO_seekmark, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_seekoff", (char*) _IO_seekoff, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_seekpos", (char*) _IO_seekpos, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_setb", (char*) _IO_setb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_sgetn", (char*) _IO_sgetn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_sputbackc", (char*) _IO_sputbackc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_stderr_", (char*) &_IO_stderr_, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_IO_stdin_", (char*) &_IO_stdin_, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_IO_stdout_", (char*) &_IO_stdout_, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_IO_strtod", (char*) _IO_strtod, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_sungetc", (char*) _IO_sungetc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_switch_to_backup_area", (char*) _IO_switch_to_backup_area, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_switch_to_get_mode", (char*) _IO_switch_to_get_mode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_switch_to_main_get_area", (char*) _IO_switch_to_main_get_area, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_un_link", (char*) _IO_un_link, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_ungetc", (char*) _IO_ungetc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_unsave_markers", (char*) _IO_unsave_markers, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_IO_vfscanf", (char*) _IO_vfscanf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_Randseed", (char*) &_Randseed, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_S_chunk_alloc__t24__default_alloc_template2b1i0UlRi", (char*) _S_chunk_alloc__t24__default_alloc_template2b1i0UlRi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_freelist_index__t24__default_alloc_template2b1i0Ul", (char*) _S_freelist_index__t24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_oom_malloc__t23__malloc_alloc_template1i0Ul", (char*) _S_oom_malloc__t23__malloc_alloc_template1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_oom_realloc__t23__malloc_alloc_template1i0PvUl", (char*) _S_oom_realloc__t23__malloc_alloc_template1i0PvUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_refill__t24__default_alloc_template2b1i0Ul", (char*) _S_refill__t24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_round_up__t24__default_alloc_template2b1i0Ul", (char*) _S_round_up__t24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10C485Client", (char*) __10C485Client, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CAlarmFilePcT1", (char*) __10CAlarmFilePcT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CAlarmInfo", (char*) __10CAlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CAlarmProc", (char*) __10CAlarmProc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CDataBoardUc", (char*) __10CDataBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CEventFilePcT1", (char*) __10CEventFilePcT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CMainBoardUc", (char*) __10CMainBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10COperation", (char*) __10COperation, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CProcAlarm", (char*) __10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CSignBoardUc", (char*) __10CSignBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10CTcpSocketUlUl", (char*) __10CTcpSocketUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10bad_typeid", (char*) __10bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11CBackGround", (char*) __11CBackGround, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11CCrossBoardUc", (char*) __11CCrossBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11CEthnClient", (char*) __11CEthnClient, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11CFunctionIP", (char*) __11CFunctionIP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11CMailBoxMap", (char*) __11CMailBoxMap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11CMemoryPoolUlUlUc", (char*) __11CMemoryPoolUlUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11COperAndCfg", (char*) __11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11CSocketNodelUlUcUc", (char*) __11CSocketNodelUlUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11CSocketPool", (char*) __11CSocketPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12C485NodePool", (char*) __12C485NodePool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CCtrlPackagePUc", (char*) __12CCtrlPackagePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CCtrlPackageR9S_MESSAGE", (char*) __12CCtrlPackageR9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CCtrlPackageUcUcUsPUc", (char*) __12CCtrlPackageUcUcUsPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CDataPackagePUc", (char*) __12CDataPackagePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CDataPackageR9S_MESSAGE", (char*) __12CDataPackageR9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CFunctionLed", (char*) __12CFunctionLed, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CFunctionVer", (char*) __12CFunctionVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CHDDataBoardUc", (char*) __12CHDDataBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CSDDataBoardUc", (char*) __12CSDDataBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CSoftUpGrade", (char*) __12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12CTimerIDPool", (char*) __12CTimerIDPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12streammarkerP9streambuf", (char*) __12streammarkerP9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13CAppInterface", (char*) __13CAppInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13CAppInterfaceRC13CAppInterface", (char*) __13CAppInterfaceRC13CAppInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13CCfgTcpSocket", (char*) __13CCfgTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13CFunctionTemp", (char*) __13CFunctionTemp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13CTimerManager", (char*) __13CTimerManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13bad_exception", (char*) __13bad_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14C2800DataBoardUc", (char*) __14C2800DataBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14CModuleManager", (char*) __14CModuleManager, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14COnLinePackage", (char*) __14COnLinePackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14COnLinePackagePUc", (char*) __14COnLinePackagePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14COperAttribute", (char*) __14COperAttribute, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14CPeriodicTimerUllUlUl", (char*) __14CPeriodicTimerUllUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14CRelativeTimerUllUlUl", (char*) __14CRelativeTimerUllUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14CSoftTcpSocket", (char*) __14CSoftTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14CSystemMessage", (char*) __14CSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14__si_type_infoPCcRC16__user_type_info", (char*) __14__si_type_infoPCcRC16__user_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14tagMailBoxNodeUsP5msg_qiUl", (char*) __14tagMailBoxNodeUsP5msg_qiUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__15CAlarmTcpSocket", (char*) __15CAlarmTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__15CDebugTcpSocket", (char*) __15CDebugTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__15CFunctionInSlot", (char*) __15CFunctionInSlot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__15CPackageCounter", (char*) __15CPackageCounter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__16CFunctionRestart", (char*) __16CFunctionRestart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__16CFunctionVoltage", (char*) __16CFunctionVoltage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__16__user_type_infoPCc", (char*) __16__user_type_infoPCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__17CFunctionPortInfo", (char*) __17CFunctionPortInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__17CKeepAlivePackagePUc", (char*) __17CKeepAlivePackagePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__17CKeepAlivePackageUcUcUsPUc", (char*) __17CKeepAlivePackageUcUcUsPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__17__class_type_infoPCcPCQ217__class_type_info9base_infoUl", (char*) __17__class_type_infoPCcPCQ217__class_type_info9base_infoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__18CProtocolInterface", (char*) __18CProtocolInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__20CFunctionManufacture", (char*) __20CFunctionManufacture, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__20CRebootSystemMessageUc", (char*) __20CRebootSystemMessageUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__21COfflineSystemMessageUc", (char*) __21COfflineSystemMessageUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__21CStandbySystemMessageUs", (char*) __21CStandbySystemMessageUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__21CStartupSystemMessageUcUc", (char*) __21CStartupSystemMessageUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__3CNe", (char*) __3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__3iosP9streambufP7ostream", (char*) __3iosP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__4CWnd", (char*) __4CWnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__5CFilePcT1UlUl", (char*) __5CFilePcT1UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__5CRoot", (char*) __5CRoot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__5CRootUc", (char*) __5CRootUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__6CBoardUc", (char*) __6CBoardUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__6CCross", (char*) __6CCross, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__6CTimerUllUlUl", (char*) __6CTimerUllUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7CModuleUsUsPFUl_lUlT3UlUs", (char*) __7CModuleUsUsPFUl_lUlT3UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7filebuf", (char*) __7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7filebufi", (char*) __7filebufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7filebufiPci", (char*) __7filebufiPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7istreami", (char*) __7istreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7istreamiP9streambufP7ostream", (char*) __7istreamiP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7ostreami", (char*) __7ostreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7ostreamiP9streambufP7ostream", (char*) __7ostreamiP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8CChannel", (char*) __8CChannel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8CDesktop", (char*) __8CDesktop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8CPackagePUc", (char*) __8CPackagePUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8CPackageR9S_MESSAGE", (char*) __8CPackageR9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8bad_cast", (char*) __8bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8iostreami", (char*) __8iostreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8iostreamiP9streambufP7ostream", (char*) __8iostreamiP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9CColorKey", (char*) __9CColorKey, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9CFunction", (char*) __9CFunction, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9CLinkNodeUcUc", (char*) __9CLinkNodeUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9CListener", (char*) __9CListener, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9CProtocol", (char*) __9CProtocol, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9exception", (char*) __9exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9streambufi", (char*) __9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9type_infoPCc", (char*) __9type_infoPCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_rd_pk_db", (char*) __DIAB_rd_pk_db, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_rd_pk_fl", (char*) __DIAB_rd_pk_fl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_rd_pk_ld", (char*) __DIAB_rd_pk_ld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_rd_sw_db", (char*) __DIAB_rd_sw_db, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_rd_sw_fl", (char*) __DIAB_rd_sw_fl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_rd_sw_ld", (char*) __DIAB_rd_sw_ld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_wr_pk_db", (char*) __DIAB_wr_pk_db, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_wr_pk_fl", (char*) __DIAB_wr_pk_fl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_wr_pk_ld", (char*) __DIAB_wr_pk_ld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_wr_sw_db", (char*) __DIAB_wr_sw_db, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_wr_sw_fl", (char*) __DIAB_wr_sw_fl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__DIAB_wr_sw_ld", (char*) __DIAB_wr_sw_ld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__POL", (char*) __POL, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23ios4Init", (char*) __Q23ios4Init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q2t24__default_alloc_template2b1i05_Lock", (char*) __Q2t24__default_alloc_template2b1i05_Lock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "___x_diab_arm_div_o", (char*) &___x_diab_arm_div_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_comljmp_o", (char*) &___x_diab_comljmp_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_ff1_o", (char*) &___x_diab_ff1_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_libg_o", (char*) &___x_diab_libg_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_rd_pk_db_o", (char*) &___x_diab_rd_pk_db_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_rd_pk_fl_o", (char*) &___x_diab_rd_pk_fl_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_rd_pk_ld_o", (char*) &___x_diab_rd_pk_ld_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_rd_sw_db_o", (char*) &___x_diab_rd_sw_db_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_rd_sw_fl_o", (char*) &___x_diab_rd_sw_fl_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_rd_sw_ld_o", (char*) &___x_diab_rd_sw_ld_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_rtahooks_o", (char*) &___x_diab_rtahooks_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpdcmp_o", (char*) &___x_diab_sfpdcmp_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpdcmpe_o", (char*) &___x_diab_sfpdcmpe_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpdnorm_o", (char*) &___x_diab_sfpdnorm_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpdpol_o", (char*) &___x_diab_sfpdpol_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpdsetup_o", (char*) &___x_diab_sfpdsetup_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpfcmp_o", (char*) &___x_diab_sfpfcmp_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpfcmpe_o", (char*) &___x_diab_sfpfcmpe_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpfnorm_o", (char*) &___x_diab_sfpfnorm_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpfsetup_o", (char*) &___x_diab_sfpfsetup_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sfpround_o", (char*) &___x_diab_sfpround_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxpadd64_o", (char*) &___x_diab_sxpadd64_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxpasr64_o", (char*) &___x_diab_sxpasr64_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxpcmp64_o", (char*) &___x_diab_sxpcmp64_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxpdiv64_o", (char*) &___x_diab_sxpdiv64_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxplsl64_o", (char*) &___x_diab_sxplsl64_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxplsr64_o", (char*) &___x_diab_sxplsr64_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxpm6432_o", (char*) &___x_diab_sxpm6432_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxpmul64_o", (char*) &___x_diab_sxpmul64_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxprem32_o", (char*) &___x_diab_sxprem32_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_sxprem64_o", (char*) &___x_diab_sxprem64_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_torn_syncatomic_o", (char*) &___x_diab_torn_syncatomic_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_torn_syncmutex_o", (char*) &___x_diab_torn_syncmutex_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_torn_syncsem_o", (char*) &___x_diab_torn_syncsem_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_wr_pk_db_o", (char*) &___x_diab_wr_pk_db_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_wr_pk_fl_o", (char*) &___x_diab_wr_pk_fl_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_wr_pk_ld_o", (char*) &___x_diab_wr_pk_ld_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_wr_sw_db_o", (char*) &___x_diab_wr_sw_db_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_wr_sw_fl_o", (char*) &___x_diab_wr_sw_fl_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_diab_wr_sw_ld_o", (char*) &___x_diab_wr_sw_ld_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu___gcc_bcmp_o", (char*) &___x_gnu___gcc_bcmp_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ashldi3_o", (char*) &___x_gnu__ashldi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ashrdi3_o", (char*) &___x_gnu__ashrdi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__bb_init_func_o", (char*) &___x_gnu__bb_init_func_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__bb_o", (char*) &___x_gnu__bb_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__clear_cache_o", (char*) &___x_gnu__clear_cache_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__cmpdi2_o", (char*) &___x_gnu__cmpdi2_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__df_to_usi_o", (char*) &___x_gnu__df_to_usi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__divdi3_o", (char*) &___x_gnu__divdi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__divsi3_o", (char*) &___x_gnu__divsi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__dp_df_to_usi_o", (char*) &___x_gnu__dp_df_to_usi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__dp_fpcmp_parts_df_o", (char*) &___x_gnu__dp_fpcmp_parts_df_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__dp_make_df_o", (char*) &___x_gnu__dp_make_df_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__dp_pack_df_o", (char*) &___x_gnu__dp_pack_df_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__dp_sf_to_usi_o", (char*) &___x_gnu__dp_sf_to_usi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__dp_thenan_df_o", (char*) &___x_gnu__dp_thenan_df_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__dp_unpack_df_o", (char*) &___x_gnu__dp_unpack_df_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__dvmd_tls_o", (char*) &___x_gnu__dvmd_tls_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__eh_o", (char*) &___x_gnu__eh_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__eprintf_o", (char*) &___x_gnu__eprintf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixtfdi_o", (char*) &___x_gnu__fixtfdi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunstfdi_o", (char*) &___x_gnu__fixunstfdi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunsxfdi_o", (char*) &___x_gnu__fixunsxfdi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixunsxfsi_o", (char*) &___x_gnu__fixunsxfsi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fixxfdi_o", (char*) &___x_gnu__fixxfdi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatditf_o", (char*) &___x_gnu__floatditf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__floatdixf_o", (char*) &___x_gnu__floatdixf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__fpcmp_parts_sf_o", (char*) &___x_gnu__fpcmp_parts_sf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__interwork_call_via_rX_o", (char*) &___x_gnu__interwork_call_via_rX_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__lshrdi3_o", (char*) &___x_gnu__lshrdi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__make_sf_o", (char*) &___x_gnu__make_sf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__moddi3_o", (char*) &___x_gnu__moddi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__modsi3_o", (char*) &___x_gnu__modsi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__muldi3_o", (char*) &___x_gnu__muldi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__negdi2_o", (char*) &___x_gnu__negdi2_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__pack_sf_o", (char*) &___x_gnu__pack_sf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__sf_to_usi_o", (char*) &___x_gnu__sf_to_usi_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__shtab_o", (char*) &___x_gnu__shtab_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__thenan_sf_o", (char*) &___x_gnu__thenan_sf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__trampoline_o", (char*) &___x_gnu__trampoline_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__ucmpdi2_o", (char*) &___x_gnu__ucmpdi2_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__udiv_w_sdiv_o", (char*) &___x_gnu__udiv_w_sdiv_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__udivdi3_o", (char*) &___x_gnu__udivdi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__udivmoddi4_o", (char*) &___x_gnu__udivmoddi4_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__udivsi3_o", (char*) &___x_gnu__udivsi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__umoddi3_o", (char*) &___x_gnu__umoddi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__umodsi3_o", (char*) &___x_gnu__umodsi3_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu__unpack_sf_o", (char*) &___x_gnu__unpack_sf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_cleanup_o", (char*) &___x_gnu_cleanup_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_exception_o", (char*) &___x_gnu_exception_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_filebuf_o", (char*) &___x_gnu_filebuf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_filedoalloc_o", (char*) &___x_gnu_filedoalloc_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_fileops_o", (char*) &___x_gnu_fileops_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_floatconv_o", (char*) &___x_gnu_floatconv_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_frame_o", (char*) &___x_gnu_frame_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_genops_o", (char*) &___x_gnu_genops_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_ioassign_o", (char*) &___x_gnu_ioassign_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_iogetc_o", (char*) &___x_gnu_iogetc_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_iogetline_o", (char*) &___x_gnu_iogetline_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_iopadn_o", (char*) &___x_gnu_iopadn_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_ioputc_o", (char*) &___x_gnu_ioputc_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_ioseekoff_o", (char*) &___x_gnu_ioseekoff_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_ioseekpos_o", (char*) &___x_gnu_ioseekpos_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_iostream_o", (char*) &___x_gnu_iostream_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_ioungetc_o", (char*) &___x_gnu_ioungetc_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_iovfscanf_o", (char*) &___x_gnu_iovfscanf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_isgetline_o", (char*) &___x_gnu_isgetline_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_isscan_o", (char*) &___x_gnu_isscan_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_new_o", (char*) &___x_gnu_new_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_outfloat_o", (char*) &___x_gnu_outfloat_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_peekc_o", (char*) &___x_gnu_peekc_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_sbscan_o", (char*) &___x_gnu_sbscan_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_stdstrbufs_o", (char*) &___x_gnu_stdstrbufs_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_stdstreams_o", (char*) &___x_gnu_stdstreams_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_stlinst_o", (char*) &___x_gnu_stlinst_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_streambuf_o", (char*) &___x_gnu_streambuf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_tinfo2_o", (char*) &___x_gnu_tinfo2_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_tinfo_o", (char*) &___x_gnu_tinfo_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__add64", (char*) __add64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__adddf3", (char*) __adddf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__addsf3", (char*) __addsf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__arm_call_via_o", (char*) &__arm_call_via_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__as__13CAppInterfaceR13CAppInterface", (char*) __as__13CAppInterfaceR13CAppInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__22_IO_istream_withassignR22_IO_istream_withassign", (char*) __as__22_IO_istream_withassignR22_IO_istream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__22_IO_istream_withassignR7istream", (char*) __as__22_IO_istream_withassignR7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__22_IO_ostream_withassignR22_IO_ostream_withassign", (char*) __as__22_IO_ostream_withassignR22_IO_ostream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__22_IO_ostream_withassignR7ostream", (char*) __as__22_IO_ostream_withassignR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ashldi3", (char*) __ashldi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ashrdi3", (char*) __ashrdi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__asr64", (char*) __asr64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__assert", (char*) __assert, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__builtin_delete", (char*) __builtin_delete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__builtin_new", (char*) __builtin_new, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__builtin_vec_delete", (char*) __builtin_vec_delete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__builtin_vec_new", (char*) __builtin_vec_new, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__check_eh_spec", (char*) __check_eh_spec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__clear_cache", (char*) __clear_cache, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__clocale", (char*) &__clocale, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cmpdf2", (char*) __cmpdf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__cmpdi2", (char*) __cmpdi2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__cmpsf2", (char*) __cmpsf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__common_intrinsicsInit", (char*) __common_intrinsicsInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__common_long_jmp", (char*) __common_long_jmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__costate", (char*) &__costate, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cp_eh_info", (char*) __cp_eh_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__cp_exception_info", (char*) __cp_exception_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__cp_pop_exception", (char*) __cp_pop_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__cp_push_exception", (char*) __cp_push_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__cplusCore_o", (char*) &__cplusCore_o, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__cplusDem_o", (char*) &__cplusDem_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplusLoadObjFiles", (char*) &__cplusLoadObjFiles, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplusLoad_o", (char*) &__cplusLoad_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplusUsr_o", (char*) &__cplusUsr_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplusXtors_o", (char*) &__cplusXtors_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__cplus_type_matcher", (char*) __cplus_type_matcher, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ctype", (char*) &__ctype, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__daysSinceEpoch", (char*) __daysSinceEpoch, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__default_terminate", (char*) __default_terminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__default_unexpected__Fv", (char*) __default_unexpected__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dflt_normalise", (char*) __dflt_normalise, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_alloc_mutex", (char*) __diab_alloc_mutex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_alloc_semaphore", (char*) __diab_alloc_semaphore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_atomic_enter", (char*) __diab_atomic_enter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_atomic_restore", (char*) __diab_atomic_restore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_free_mutex", (char*) __diab_free_mutex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_free_semaphore", (char*) __diab_free_semaphore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_intrinsics_impfpInit", (char*) __diab_intrinsics_impfpInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_intrinsics_implInit", (char*) __diab_intrinsics_implInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_intrinsics_tornInit", (char*) __diab_intrinsics_tornInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_lock_mutex", (char*) __diab_lock_mutex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_lock_semaphore", (char*) __diab_lock_semaphore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_trylock_mutex", (char*) __diab_trylock_mutex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_trylock_semaphore", (char*) __diab_trylock_semaphore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_unlock_mutex", (char*) __diab_unlock_mutex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__diab_unlock_semaphore", (char*) __diab_unlock_semaphore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__div0", (char*) __div0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__div32", (char*) __div32, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__div64", (char*) __div64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__divdf3", (char*) __divdf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__divdi3", (char*) __divdi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__divsf3", (char*) __divsf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__divsi3", (char*) __divsi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dunder", (char*) __dunder, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dunder_d", (char*) __dunder_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dynamic_cast", (char*) __dynamic_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dynamic_cast_2", (char*) __dynamic_cast_2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eh_alloc", (char*) __eh_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eh_free", (char*) __eh_free, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eh_rtime_match", (char*) __eh_rtime_match, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__empty", (char*) __empty, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq64", (char*) __eq64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq__C11CSocketNodeRCUc", (char*) __eq__C11CSocketNodeRCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq__C11CSocketNodeRCl", (char*) __eq__C11CSocketNodeRCl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq__C9CLinkNodeRCUc", (char*) __eq__C9CLinkNodeRCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq__C9type_infoRC9type_info", (char*) __eq__C9type_infoRC9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eqdf2", (char*) __eqdf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eqsf2", (char*) __eqsf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__errno", (char*) __errno, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__exp10", (char*) __exp10, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__extendsfdf2", (char*) __extendsfdf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ff1", (char*) __ff1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ff1l", (char*) __ff1l, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ff1ll", (char*) __ff1ll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fflt_normalise", (char*) __fflt_normalise, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixdfdi", (char*) __fixdfdi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixdfsi", (char*) __fixdfsi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixsfdi", (char*) __fixsfdi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixsfsi", (char*) __fixsfsi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunsdfdi", (char*) __fixunsdfdi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunsdfsi", (char*) __fixunsdfsi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunssfdi", (char*) __fixunssfdi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fixunssfsi", (char*) __fixunssfsi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatdidf", (char*) __floatdidf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatdisf", (char*) __floatdisf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatsidf", (char*) __floatsidf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__floatsisf", (char*) __floatsisf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpcmp_parts_d", (char*) __fpcmp_parts_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpcmp_parts_f", (char*) __fpcmp_parts_f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpl_cmpreturn", (char*) __fpl_cmpreturn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpl_dcheck_NaN2", (char*) __fpl_dcheck_NaN2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpl_dcmp_InfNaN", (char*) __fpl_dcmp_InfNaN, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpl_exception", (char*) __fpl_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpl_fcheck_NaN2", (char*) __fpl_fcheck_NaN2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpl_normalise2", (char*) __fpl_normalise2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__fpl_return_NaN", (char*) __fpl_return_NaN, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__funder", (char*) __funder, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__funder_d", (char*) __funder_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gcc_bcmp", (char*) __gcc_bcmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gcc_intrinsicsInit", (char*) __gcc_intrinsicsInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ge64", (char*) __ge64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gedf2", (char*) __gedf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gesf2", (char*) __gesf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getDstInfo", (char*) __getDstInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getTime", (char*) __getTime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getZoneInfo", (char*) __getZoneInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__get_dynamic_handler_chain", (char*) __get_dynamic_handler_chain, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__get_eh_context", (char*) __get_eh_context, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__get_eh_info", (char*) __get_eh_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gt64", (char*) __gt64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gtdf2", (char*) __gtdf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gtsf2", (char*) __gtsf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ieee754_rem_pio2", (char*) __ieee754_rem_pio2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__includeDiabIntrinsics", (char*) &__includeDiabIntrinsics, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__includeGnuIntrinsics", (char*) &__includeGnuIntrinsics, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__is_pointer__FPv", (char*) __is_pointer__FPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__julday", (char*) __julday, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__kernel_cos", (char*) __kernel_cos, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__kernel_poly", (char*) __kernel_poly, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__kernel_rem_pio2", (char*) __kernel_rem_pio2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__kernel_sin", (char*) __kernel_sin, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__kernel_tan", (char*) __kernel_tan, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__le64", (char*) __le64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ledf2", (char*) __ledf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lesf2", (char*) __lesf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__locale", (char*) &__locale, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__loctime", (char*) &__loctime, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__ls__7ostreamP9streambuf", (char*) __ls__7ostreamP9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamPCSc", (char*) __ls__7ostreamPCSc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamPCUc", (char*) __ls__7ostreamPCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamPCc", (char*) __ls__7ostreamPCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamPFR3ios_R3ios", (char*) __ls__7ostreamPFR3ios_R3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamPFR7ostream_R7ostream", (char*) __ls__7ostreamPFR7ostream_R7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamSc", (char*) __ls__7ostreamSc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamUc", (char*) __ls__7ostreamUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamUi", (char*) __ls__7ostreamUi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamUl", (char*) __ls__7ostreamUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamUs", (char*) __ls__7ostreamUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamUx", (char*) __ls__7ostreamUx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamb", (char*) __ls__7ostreamb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamc", (char*) __ls__7ostreamc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamd", (char*) __ls__7ostreamd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamf", (char*) __ls__7ostreamf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreami", (char*) __ls__7ostreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreaml", (char*) __ls__7ostreaml, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamr", (char*) __ls__7ostreamr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreams", (char*) __ls__7ostreams, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ls__7ostreamx", (char*) __ls__7ostreamx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lshrdi3", (char*) __lshrdi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lsl64", (char*) __lsl64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lsr64", (char*) __lsr64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lt64", (char*) __lt64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lt__C14tagMailBoxNodeUs", (char*) __lt__C14tagMailBoxNodeUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lt__FRC14tagMailBoxNodeT0", (char*) __lt__FRC14tagMailBoxNodeT0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ltdf2", (char*) __ltdf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ltsf2", (char*) __ltsf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__make_dp", (char*) __make_dp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__make_fp", (char*) __make_fp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__moddi3", (char*) __moddi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__modsi3", (char*) __modsi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__mul64", (char*) __mul64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__mul6432", (char*) __mul6432, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__muldf3", (char*) __muldf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__muldi3", (char*) __muldi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__mulsf3", (char*) __mulsf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ne64", (char*) __ne64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ne__C11CSocketNodeRCUc", (char*) __ne__C11CSocketNodeRCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ne__C11CSocketNodeRCl", (char*) __ne__C11CSocketNodeRCl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ne__C9CLinkNodeRCUc", (char*) __ne__C9CLinkNodeRCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ne__C9type_infoRC9type_info", (char*) __ne__C9type_infoRC9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__nedf2", (char*) __nedf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negdf2", (char*) __negdf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negdi2", (char*) __negdi2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negsf2", (char*) __negsf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__nesf2", (char*) __nesf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__new_handler", (char*) &__new_handler, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__nt__C3ios", (char*) __nt__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__nw__FUlPv", (char*) __nw__FUlPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__opPv__C3ios", (char*) __opPv__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__overflow", (char*) __overflow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__overflow__FP9streambufi", (char*) __overflow__FP9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pack_d", (char*) __pack_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pack_f", (char*) __pack_f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pure_virtual", (char*) __pure_virtual, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pure_virtual_called", (char*) __pure_virtual_called, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rem32", (char*) __rem32, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rem64", (char*) __rem64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamP9streambuf", (char*) __rs__7istreamP9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamPFR3ios_R3ios", (char*) __rs__7istreamPFR3ios_R3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamPFR7istream_R7istream", (char*) __rs__7istreamPFR7istream_R7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamPSc", (char*) __rs__7istreamPSc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamPUc", (char*) __rs__7istreamPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamPc", (char*) __rs__7istreamPc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRSc", (char*) __rs__7istreamRSc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRUc", (char*) __rs__7istreamRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRUi", (char*) __rs__7istreamRUi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRUl", (char*) __rs__7istreamRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRUs", (char*) __rs__7istreamRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRUx", (char*) __rs__7istreamRUx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRb", (char*) __rs__7istreamRb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRc", (char*) __rs__7istreamRc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRd", (char*) __rs__7istreamRd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRf", (char*) __rs__7istreamRf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRi", (char*) __rs__7istreamRi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRl", (char*) __rs__7istreamRl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRr", (char*) __rs__7istreamRr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRs", (char*) __rs__7istreamRs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__7istreamRx", (char*) __rs__7istreamRx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__FRC8CPackageR9S_MESSAGE", (char*) __rs__FRC8CPackageR9S_MESSAGE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rs__FRC9S_MESSAGEPUc", (char*) __rs__FRC9S_MESSAGEPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rt_fp_status_addr", (char*) __rt_fp_status_addr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rta_longjmp", (char*) &__rta_longjmp, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__rtc_alloc_ptr", (char*) &__rtc_alloc_ptr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__rtc_blkinfo_ptr", (char*) &__rtc_blkinfo_ptr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__rtc_free_ptr", (char*) &__rtc_free_ptr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__rtti_array", (char*) __rtti_array, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rtti_attr", (char*) __rtti_attr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rtti_class", (char*) __rtti_class, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rtti_func", (char*) __rtti_func, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rtti_ptmd", (char*) __rtti_ptmd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rtti_ptmf", (char*) __rtti_ptmf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rtti_ptr", (char*) __rtti_ptr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rtti_si", (char*) __rtti_si, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__rtti_user", (char*) __rtti_user, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sclose", (char*) __sclose, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__set_malloc_handler__t23__malloc_alloc_template1i0PFv_v", (char*) __set_malloc_handler__t23__malloc_alloc_template1i0PFv_v, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sflags", (char*) __sflags, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sflush", (char*) __sflush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sfpRoundMode", (char*) &__sfpRoundMode, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__sfvwrite", (char*) __sfvwrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__shtab", (char*) &__shtab, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__sjpopnthrow", (char*) __sjpopnthrow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sjthrow", (char*) __sjthrow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__smakebuf", (char*) __smakebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sn_t24__default_alloc_template2b1i0$_S_node_allocator_lock", (char*) &__sn_t24__default_alloc_template2b1i0$_S_node_allocator_lock, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__sread", (char*) __sread, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__srefill", (char*) __srefill, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__srget", (char*) __srget, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sseek", (char*) __sseek, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__start_cp_handler", (char*) __start_cp_handler, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__stderr", (char*) __stderr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__stdin", (char*) __stdin, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__stdout", (char*) __stdout, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__strxfrm", (char*) __strxfrm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__sub64", (char*) __sub64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__subdf3", (char*) __subdf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__subsf3", (char*) __subsf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__swbuf", (char*) __swbuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__swrite", (char*) __swrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__swsetup", (char*) __swsetup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__terminate", (char*) __terminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__terminate_func", (char*) &__terminate_func, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__tf10C485Client", (char*) __tf10C485Client, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CAlarmFile", (char*) __tf10CAlarmFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CAlarmInfo", (char*) __tf10CAlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CAlarmProc", (char*) __tf10CAlarmProc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CDataBoard", (char*) __tf10CDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CEventFile", (char*) __tf10CEventFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CMainBoard", (char*) __tf10CMainBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10COperation", (char*) __tf10COperation, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CProcAlarm", (char*) __tf10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CSignBoard", (char*) __tf10CSignBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10CTcpSocket", (char*) __tf10CTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10bad_typeid", (char*) __tf10bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf11CBackGround", (char*) __tf11CBackGround, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf11CCrossBoard", (char*) __tf11CCrossBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf11CEthnClient", (char*) __tf11CEthnClient, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf11CFunctionIP", (char*) __tf11CFunctionIP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf11COperAndCfg", (char*) __tf11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf11CSocketNode", (char*) __tf11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12CCtrlPackage", (char*) __tf12CCtrlPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12CDataPackage", (char*) __tf12CDataPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12CFunctionLed", (char*) __tf12CFunctionLed, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12CFunctionVer", (char*) __tf12CFunctionVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12CHDDataBoard", (char*) __tf12CHDDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12CSDDataBoard", (char*) __tf12CSDDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12CSoftUpGrade", (char*) __tf12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf13CFunctionTemp", (char*) __tf13CFunctionTemp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf13bad_exception", (char*) __tf13bad_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf14C2800DataBoard", (char*) __tf14C2800DataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf14COnLinePackage", (char*) __tf14COnLinePackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf14COperAttribute", (char*) __tf14COperAttribute, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf14CPeriodicTimer", (char*) __tf14CPeriodicTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf14CSystemMessage", (char*) __tf14CSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf14__si_type_info", (char*) __tf14__si_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf15CDebugTcpSocket", (char*) __tf15CDebugTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf15CFunctionInSlot", (char*) __tf15CFunctionInSlot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf16CFunctionRestart", (char*) __tf16CFunctionRestart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf16CFunctionVoltage", (char*) __tf16CFunctionVoltage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf16__user_type_info", (char*) __tf16__user_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf17CFunctionPortInfo", (char*) __tf17CFunctionPortInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf17CKeepAlivePackage", (char*) __tf17CKeepAlivePackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf17__class_type_info", (char*) __tf17__class_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf18CProtocolInterface", (char*) __tf18CProtocolInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf20CFunctionManufacture", (char*) __tf20CFunctionManufacture, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf20CRebootSystemMessage", (char*) __tf20CRebootSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf21COfflineSystemMessage", (char*) __tf21COfflineSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf21CStandbySystemMessage", (char*) __tf21CStandbySystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf21CStartupSystemMessage", (char*) __tf21CStartupSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf22_IO_istream_withassign", (char*) __tf22_IO_istream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf22_IO_ostream_withassign", (char*) __tf22_IO_ostream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf3CNe", (char*) __tf3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf3ios", (char*) __tf3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf4CWnd", (char*) __tf4CWnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf5CFile", (char*) __tf5CFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf5CRoot", (char*) __tf5CRoot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf6CBoard", (char*) __tf6CBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf6CCross", (char*) __tf6CCross, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf6CTimer", (char*) __tf6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7CModule", (char*) __tf7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7filebuf", (char*) __tf7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7istream", (char*) __tf7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7ostream", (char*) __tf7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf8CChannel", (char*) __tf8CChannel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf8CDesktop", (char*) __tf8CDesktop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf8CPackage", (char*) __tf8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf8bad_cast", (char*) __tf8bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf8iostream", (char*) __tf8iostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9CColorKey", (char*) __tf9CColorKey, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9CFunction", (char*) __tf9CFunction, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9CLinkNode", (char*) __tf9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9CListener", (char*) __tf9CListener, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9CProtocol", (char*) __tf9CProtocol, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9bad_alloc", (char*) __tf9bad_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9exception", (char*) __tf9exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9streambuf", (char*) __tf9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9type_info", (char*) __tf9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfSc", (char*) __tfSc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfUc", (char*) __tfUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfUi", (char*) __tfUi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfUl", (char*) __tfUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfUs", (char*) __tfUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfUx", (char*) __tfUx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfb", (char*) __tfb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfc", (char*) __tfc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfd", (char*) __tfd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tff", (char*) __tff, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfi", (char*) __tfi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfl", (char*) __tfl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfr", (char*) __tfr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfs", (char*) __tfs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfv", (char*) __tfv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfw", (char*) __tfw, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfx", (char*) __tfx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__thenan_df", (char*) __thenan_df, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__thenan_sf", (char*) __thenan_sf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__throw_bad_cast", (char*) __throw_bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__throw_bad_typeid", (char*) __throw_bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__throw_type_match", (char*) __throw_type_match, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__throw_type_match_rtti", (char*) __throw_type_match_rtti, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__throw_type_match_rtti_2", (char*) __throw_type_match_rtti_2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ti10C485Client", (char*) &__ti10C485Client, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CAlarmFile", (char*) &__ti10CAlarmFile, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CAlarmInfo", (char*) &__ti10CAlarmInfo, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CAlarmProc", (char*) &__ti10CAlarmProc, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CDataBoard", (char*) &__ti10CDataBoard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CEventFile", (char*) &__ti10CEventFile, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CMainBoard", (char*) &__ti10CMainBoard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10COperation", (char*) &__ti10COperation, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CProcAlarm", (char*) &__ti10CProcAlarm, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CSignBoard", (char*) &__ti10CSignBoard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10CTcpSocket", (char*) &__ti10CTcpSocket, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10bad_typeid", (char*) &__ti10bad_typeid, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11CBackGround", (char*) &__ti11CBackGround, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11CCrossBoard", (char*) &__ti11CCrossBoard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11CEthnClient", (char*) &__ti11CEthnClient, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11CFunctionIP", (char*) &__ti11CFunctionIP, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11COperAndCfg", (char*) &__ti11COperAndCfg, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11CSocketNode", (char*) &__ti11CSocketNode, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11_ios_fields", (char*) &__ti11_ios_fields, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12CCtrlPackage", (char*) &__ti12CCtrlPackage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12CDataPackage", (char*) &__ti12CDataPackage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12CFunctionLed", (char*) &__ti12CFunctionLed, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12CFunctionVer", (char*) &__ti12CFunctionVer, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12CHDDataBoard", (char*) &__ti12CHDDataBoard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12CSDDataBoard", (char*) &__ti12CSDDataBoard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12CSoftUpGrade", (char*) &__ti12CSoftUpGrade, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti13CCfgTcpSocket", (char*) &__ti13CCfgTcpSocket, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti13CFunctionTemp", (char*) &__ti13CFunctionTemp, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti13bad_exception", (char*) &__ti13bad_exception, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14C2800DataBoard", (char*) &__ti14C2800DataBoard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14COnLinePackage", (char*) &__ti14COnLinePackage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14COperAttribute", (char*) &__ti14COperAttribute, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14CPeriodicTimer", (char*) &__ti14CPeriodicTimer, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14CRelativeTimer", (char*) &__ti14CRelativeTimer, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14CSoftTcpSocket", (char*) &__ti14CSoftTcpSocket, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14CSystemMessage", (char*) &__ti14CSystemMessage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14__si_type_info", (char*) &__ti14__si_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti15CAlarmTcpSocket", (char*) &__ti15CAlarmTcpSocket, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti15CDebugTcpSocket", (char*) &__ti15CDebugTcpSocket, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti15CFunctionInSlot", (char*) &__ti15CFunctionInSlot, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16CFunctionRestart", (char*) &__ti16CFunctionRestart, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16CFunctionVoltage", (char*) &__ti16CFunctionVoltage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__attr_type_info", (char*) &__ti16__attr_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__func_type_info", (char*) &__ti16__func_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__ptmd_type_info", (char*) &__ti16__ptmd_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__ptmf_type_info", (char*) &__ti16__ptmf_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__user_type_info", (char*) &__ti16__user_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti17CFunctionPortInfo", (char*) &__ti17CFunctionPortInfo, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti17CKeepAlivePackage", (char*) &__ti17CKeepAlivePackage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti17__array_type_info", (char*) &__ti17__array_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti17__class_type_info", (char*) &__ti17__class_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti18CProtocolInterface", (char*) &__ti18CProtocolInterface, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti19__builtin_type_info", (char*) &__ti19__builtin_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti19__pointer_type_info", (char*) &__ti19__pointer_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti20CFunctionManufacture", (char*) &__ti20CFunctionManufacture, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti20CRebootSystemMessage", (char*) &__ti20CRebootSystemMessage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti21COfflineSystemMessage", (char*) &__ti21COfflineSystemMessage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti21CStandbySystemMessage", (char*) &__ti21CStandbySystemMessage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti21CStartupSystemMessage", (char*) &__ti21CStartupSystemMessage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti22_IO_istream_withassign", (char*) &__ti22_IO_istream_withassign, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti22_IO_ostream_withassign", (char*) &__ti22_IO_ostream_withassign, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti3CNe", (char*) &__ti3CNe, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti3ios", (char*) &__ti3ios, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti4CWnd", (char*) &__ti4CWnd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti5CFile", (char*) &__ti5CFile, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti5CRoot", (char*) &__ti5CRoot, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti6CBoard", (char*) &__ti6CBoard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti6CCross", (char*) &__ti6CCross, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti6CTimer", (char*) &__ti6CTimer, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7CModule", (char*) &__ti7CModule, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7filebuf", (char*) &__ti7filebuf, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7istream", (char*) &__ti7istream, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7ostream", (char*) &__ti7ostream, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8CChannel", (char*) &__ti8CChannel, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8CDesktop", (char*) &__ti8CDesktop, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8CPackage", (char*) &__ti8CPackage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8_IO_FILE", (char*) &__ti8_IO_FILE, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8bad_cast", (char*) &__ti8bad_cast, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8iostream", (char*) &__ti8iostream, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9CColorKey", (char*) &__ti9CColorKey, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9CFunction", (char*) &__ti9CFunction, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9CLinkNode", (char*) &__ti9CLinkNode, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9CListener", (char*) &__ti9CListener, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9CProtocol", (char*) &__ti9CProtocol, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9bad_alloc", (char*) &__ti9bad_alloc, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9exception", (char*) &__ti9exception, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9streambuf", (char*) &__ti9streambuf, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9type_info", (char*) &__ti9type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiSc", (char*) &__tiSc, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiUc", (char*) &__tiUc, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiUi", (char*) &__tiUi, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiUl", (char*) &__tiUl, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiUs", (char*) &__tiUs, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiUx", (char*) &__tiUx, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tib", (char*) &__tib, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tic", (char*) &__tic, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tid", (char*) &__tid, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tif", (char*) &__tif, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tii", (char*) &__tii, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__til", (char*) &__til, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tir", (char*) &__tir, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tis", (char*) &__tis, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiv", (char*) &__tiv, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiw", (char*) &__tiw, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tix", (char*) &__tix, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__truncdfsf2", (char*) __truncdfsf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ucmpdi2", (char*) __ucmpdi2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udiv32", (char*) __udiv32, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udiv64", (char*) __udiv64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udiv_w_sdiv", (char*) __udiv_w_sdiv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udivdi3", (char*) __udivdi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udivmoddi4", (char*) __udivmoddi4, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__udivsi3", (char*) __udivsi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__uflow", (char*) __uflow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__uge64", (char*) __uge64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ugt64", (char*) __ugt64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ule64", (char*) __ule64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ult64", (char*) __ult64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__umoddi3", (char*) __umoddi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__umodsi3", (char*) __umodsi3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__uncatch_exception", (char*) __uncatch_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__underflow", (char*) __underflow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__unpack_d", (char*) __unpack_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__unpack_f", (char*) __unpack_f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__urem32", (char*) __urem32, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__urem64", (char*) __urem64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vn__FUlPv", (char*) __vn__FUlPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__wdbEventListIsEmpty", (char*) &__wdbEventListIsEmpty, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__wdbEvtptDeleteAll", (char*) &__wdbEvtptDeleteAll, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_archHelp_msg", (char*) &_archHelp_msg, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_arpCmd", (char*) _arpCmd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_clockRealtime", (char*) &_clockRealtime, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_cplusDemangle", (char*) _cplusDemangle, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d2f", (char*) _d2f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_add", (char*) _d_add, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_cmp", (char*) _d_cmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_cmpe", (char*) _d_cmpe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_div", (char*) _d_div, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_dtof", (char*) _d_dtof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_dtoi", (char*) _d_dtoi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_dtoll", (char*) _d_dtoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_dtou", (char*) _d_dtou, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_dtoull", (char*) _d_dtoull, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_feq", (char*) _d_feq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_fge", (char*) _d_fge, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_fgt", (char*) _d_fgt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_fle", (char*) _d_fle, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_flt", (char*) _d_flt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_fne", (char*) _d_fne, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_itod", (char*) _d_itod, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_lltod", (char*) _d_lltod, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_mul", (char*) _d_mul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_sub", (char*) _d_sub, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_ulltod", (char*) _d_ulltod, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_d_utod", (char*) _d_utod, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dabs", (char*) _dabs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dadd", (char*) _dadd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_db_show_arptab", (char*) _db_show_arptab, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgArchInit", (char*) _dbgArchInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgDsmInstRtn", (char*) &_dbgDsmInstRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_dbgFuncCallCheck", (char*) _dbgFuncCallCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgInstSizeGet", (char*) _dbgInstSizeGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgRetAdrsGet", (char*) _dbgRetAdrsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgTaskPCGet", (char*) _dbgTaskPCGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dbgTaskPCSet", (char*) _dbgTaskPCSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dcmpeq", (char*) _dcmpeq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dcmpge", (char*) _dcmpge, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dcmple", (char*) _dcmple, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ddiv", (char*) _ddiv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_deq", (char*) _deq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dfix", (char*) _dfix, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dfix_r", (char*) _dfix_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dfixu", (char*) _dfixu, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dfixu_r", (char*) _dfixu_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dflt", (char*) _dflt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dfltu", (char*) _dfltu, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dgeq", (char*) _dgeq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dgr", (char*) _dgr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dleq", (char*) _dleq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dls", (char*) _dls, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dmul", (char*) _dmul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dneg", (char*) _dneg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dneq", (char*) _dneq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_drdiv", (char*) _drdiv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_drem", (char*) _drem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_drsb", (char*) _drsb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dsqrt", (char*) _dsqrt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_dsub", (char*) _dsub, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f2d", (char*) _f2d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_add", (char*) _f_add, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_cmp", (char*) _f_cmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_cmpe", (char*) _f_cmpe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_div", (char*) _f_div, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_feq", (char*) _f_feq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_fge", (char*) _f_fge, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_fgt", (char*) _f_fgt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_fle", (char*) _f_fle, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_flt", (char*) _f_flt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_fne", (char*) _f_fne, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_ftod", (char*) _f_ftod, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_ftoi", (char*) _f_ftoi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_ftoll", (char*) _f_ftoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_ftou", (char*) _f_ftou, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_ftoull", (char*) _f_ftoull, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_itof", (char*) _f_itof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_lltof", (char*) _f_lltof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_mul", (char*) _f_mul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_sub", (char*) _f_sub, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_ulltof", (char*) _f_ulltof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_f_utof", (char*) _f_utof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fabs", (char*) _fabs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fadd", (char*) _fadd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fcmpeq", (char*) _fcmpeq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fcmpge", (char*) _fcmpge, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fcmple", (char*) _fcmple, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fdiv", (char*) _fdiv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_feq", (char*) _feq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ffix", (char*) _ffix, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ffix_r", (char*) _ffix_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ffixu", (char*) _ffixu, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ffixu_r", (char*) _ffixu_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fflt", (char*) _fflt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ffltu", (char*) _ffltu, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fgeq", (char*) _fgeq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fgr", (char*) _fgr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fleq", (char*) _fleq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fls", (char*) _fls, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fmul", (char*) _fmul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fneg", (char*) _fneg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fneq", (char*) _fneq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fpStatus", (char*) &_fpStatus, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_fp_round", (char*) _fp_round, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fp_trap", (char*) _fp_trap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fp_trapveneer", (char*) _fp_trapveneer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_frdiv", (char*) _frdiv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_frsb", (char*) _frsb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_fsub", (char*) _fsub, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_func_armIntStackSplit", (char*) &_func_armIntStackSplit, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_armIrqHandler", (char*) &_func_armIrqHandler, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_armPageSource", (char*) &_func_armPageSource, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_bdall", (char*) &_func_bdall, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_dbgHostNotify", (char*) &_func_dbgHostNotify, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_dbgTargetNotify", (char*) &_func_dbgTargetNotify, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_dspMregsHook", (char*) &_func_dspMregsHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_dspRegsListHook", (char*) &_func_dspRegsListHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_dspTaskRegsShow", (char*) &_func_dspTaskRegsShow, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogM0", (char*) &_func_evtLogM0, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogM1", (char*) &_func_evtLogM1, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogM2", (char*) &_func_evtLogM2, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogM3", (char*) &_func_evtLogM3, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogO", (char*) &_func_evtLogO, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogOIntLock", (char*) &_func_evtLogOIntLock, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogPoint", (char*) &_func_evtLogPoint, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogReserveTaskName", (char*) &_func_evtLogReserveTaskName, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogString", (char*) &_func_evtLogString, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogT0", (char*) &_func_evtLogT0, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogT0_noInt", (char*) &_func_evtLogT0_noInt, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogT1", (char*) &_func_evtLogT1, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogT1_noTS", (char*) &_func_evtLogT1_noTS, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_evtLogTSched", (char*) &_func_evtLogTSched, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excBaseHook", (char*) &_func_excBaseHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excBreakpoint", (char*) &_func_excBreakpoint, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_excInfoShow", (char*) &_func_excInfoShow, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excIntHook", (char*) &_func_excIntHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excJobAdd", (char*) &_func_excJobAdd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_excPanicHook", (char*) &_func_excPanicHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fclose", (char*) &_func_fclose, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_fileDoesNotExist", (char*) &_func_fileDoesNotExist, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_fppTaskRegsShow", (char*) &_func_fppTaskRegsShow, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ftpLs", (char*) &_func_ftpLs, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ftpTransientFatal", (char*) &_func_ftpTransientFatal, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_ioTaskStdSet", (char*) &_func_ioTaskStdSet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ipsecFilterHook", (char*) &_func_ipsecFilterHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ipsecInput", (char*) &_func_ipsecInput, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_ipsecOutput", (char*) &_func_ipsecOutput, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_logMsg", (char*) &_func_logMsg, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_memalign", (char*) &_func_memalign, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_netLsByName", (char*) &_func_netLsByName, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_printErr", (char*) &_func_printErr, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_pthread_setcanceltype", (char*) &_func_pthread_setcanceltype, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_remCurIdGet", (char*) &_func_remCurIdGet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_remCurIdSet", (char*) &_func_remCurIdSet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selPtyAdd", (char*) &_func_selPtyAdd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selPtyDelete", (char*) &_func_selPtyDelete, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selTyAdd", (char*) &_func_selTyAdd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selTyDelete", (char*) &_func_selTyDelete, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selWakeupAll", (char*) &_func_selWakeupAll, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selWakeupListInit", (char*) &_func_selWakeupListInit, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_selWakeupListTerm", (char*) &_func_selWakeupListTerm, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sigExcKill", (char*) &_func_sigExcKill, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sigTimeoutRecalc", (char*) &_func_sigTimeoutRecalc, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sigprocmask", (char*) &_func_sigprocmask, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_smObjObjShow", (char*) &_func_smObjObjShow, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spy", (char*) &_func_spy, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyClkStart", (char*) &_func_spyClkStart, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyClkStop", (char*) &_func_spyClkStop, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyReport", (char*) &_func_spyReport, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyStop", (char*) &_func_spyStop, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_spyTask", (char*) &_func_spyTask, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_sseTaskRegsShow", (char*) &_func_sseTaskRegsShow, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symFindByValue", (char*) &_func_symFindByValue, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symFindByValueAndType", (char*) &_func_symFindByValueAndType, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symFindSymbol", (char*) &_func_symFindSymbol, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symNameGet", (char*) &_func_symNameGet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symTypeGet", (char*) &_func_symTypeGet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_symValueGet", (char*) &_func_symValueGet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskCreateHookAdd", (char*) &_func_taskCreateHookAdd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskDeleteHookAdd", (char*) &_func_taskDeleteHookAdd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_taskRegsShowRtn", (char*) &_func_taskRegsShowRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrConnect", (char*) &_func_tmrConnect, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrDisable", (char*) &_func_tmrDisable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrEnable", (char*) &_func_tmrEnable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrFreq", (char*) &_func_tmrFreq, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrPeriod", (char*) &_func_tmrPeriod, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrStamp", (char*) &_func_tmrStamp, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_tmrStampLock", (char*) &_func_tmrStampLock, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_trap", (char*) &_func_trap, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_trgCheck", (char*) &_func_trgCheck, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_valloc", (char*) &_func_valloc, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_vxMemProbeHook", (char*) &_func_vxMemProbeHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_wdbIsNowExternal", (char*) &_func_wdbIsNowExternal, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_func_wvNetAddressFilterTest", (char*) &_func_wvNetAddressFilterTest, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_func_wvNetPortFilterTest", (char*) &_func_wvNetPortFilterTest, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_icmpErrorHook", (char*) &_icmpErrorHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_igmpJoinAlertHook", (char*) &_igmpJoinAlertHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_igmpJoinGrpHook", (char*) &_igmpJoinGrpHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_igmpLeaveAlertHook", (char*) &_igmpLeaveAlertHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_igmpLeaveGrpHook", (char*) &_igmpLeaveGrpHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_igmpMessageHook", (char*) &_igmpMessageHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_igmpQuerierTimeUpdateHook", (char*) &_igmpQuerierTimeUpdateHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_insque", (char*) _insque, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ipCfgFlags", (char*) &_ipCfgFlags, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_ipFilterHook", (char*) &_ipFilterHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_landAttackSafe", (char*) &_landAttackSafe, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_link_in__9streambuf", (char*) _link_in__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_sfrom_d", (char*) _ll_sfrom_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_sfrom_d_r", (char*) _ll_sfrom_d_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_sfrom_f", (char*) _ll_sfrom_f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_sfrom_f_r", (char*) _ll_sfrom_f_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_sto_d", (char*) _ll_sto_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_sto_f", (char*) _ll_sto_f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_ufrom_d", (char*) _ll_ufrom_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_ufrom_d_r", (char*) _ll_ufrom_d_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_ufrom_f", (char*) _ll_ufrom_f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_ufrom_f_r", (char*) _ll_ufrom_f_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_uto_d", (char*) _ll_uto_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_ll_uto_f", (char*) _ll_uto_f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_m2IfTableUpdate", (char*) &_m2IfTableUpdate, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_m2SetIfLastChange", (char*) &_m2SetIfLastChange, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_mCastRouteCmdHook", (char*) &_mCastRouteCmdHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_mCastRouteFwdHook", (char*) &_mCastRouteFwdHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_mmuCrValue", (char*) &_mmuCrValue, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_netFree", (char*) _netFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_netMalloc", (char*) _netMalloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_pNetBufCollect", (char*) &_pNetBufCollect, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pNetDpool", (char*) &_pNetDpool, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pNetPoolFuncTbl", (char*) &_pNetPoolFuncTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pNetSysPool", (char*) &_pNetSysPool, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pSigQueueFreeHead", (char*) &_pSigQueueFreeHead, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_pTcpPcbHead", (char*) &_pTcpPcbHead, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pTcpPcbPrint", (char*) &_pTcpPcbPrint, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pUdpPcbHead", (char*) &_pUdpPcbHead, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_panicHook", (char*) &_panicHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pingTxInterval", (char*) &_pingTxInterval, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pingTxLen", (char*) &_pingTxLen, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_pingTxTmo", (char*) &_pingTxTmo, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_presolvHostLibGetByAddr", (char*) &_presolvHostLibGetByAddr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_presolvHostLibGetByName", (char*) &_presolvHostLibGetByName, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_procNumWasSet", (char*) &_procNumWasSet, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_protoSwIndex", (char*) &_protoSwIndex, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_remque", (char*) _remque, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sb_readline__FP9streambufRlc", (char*) _sb_readline__FP9streambufRlc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sch_istable", (char*) _sch_istable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sch_tolower", (char*) _sch_tolower, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sch_toupper", (char*) _sch_toupper, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_setjmpSetup", (char*) _setjmpSetup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxLoad", (char*) _sigCtxLoad, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxRtnValSet", (char*) _sigCtxRtnValSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxSave", (char*) _sigCtxSave, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxSetup", (char*) _sigCtxSetup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigCtxStackEnd", (char*) _sigCtxStackEnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_sigfaulttable", (char*) &_sigfaulttable, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_skip_ws__7istream", (char*) _skip_ws__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_t23__malloc_alloc_template1i0$__malloc_alloc_oom_handler", (char*) &_t23__malloc_alloc_template1i0$__malloc_alloc_oom_handler, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_end_free", (char*) &_t24__default_alloc_template2b1i0$_S_end_free, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_free_list", (char*) &_t24__default_alloc_template2b1i0$_S_free_list, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_heap_size", (char*) &_t24__default_alloc_template2b1i0$_S_heap_size, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_node_allocator_lock", (char*) &_t24__default_alloc_template2b1i0$_S_node_allocator_lock, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_start_free", (char*) &_t24__default_alloc_template2b1i0$_S_start_free, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_throw_failure__C3ios", (char*) _throw_failure__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_un_link__9streambuf", (char*) _un_link__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10C485Client", (char*) _vt$10C485Client, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CAlarmFile", (char*) _vt$10CAlarmFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CAlarmInfo", (char*) _vt$10CAlarmInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CAlarmProc", (char*) _vt$10CAlarmProc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CDataBoard", (char*) _vt$10CDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CEventFile", (char*) _vt$10CEventFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CMainBoard", (char*) _vt$10CMainBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10COperation", (char*) _vt$10COperation, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CProcAlarm", (char*) _vt$10CProcAlarm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CSignBoard", (char*) _vt$10CSignBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10CTcpSocket", (char*) _vt$10CTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10bad_typeid", (char*) _vt$10bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$11CBackGround", (char*) _vt$11CBackGround, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$11CCrossBoard", (char*) _vt$11CCrossBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$11CEthnClient", (char*) _vt$11CEthnClient, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$11CFunctionIP", (char*) _vt$11CFunctionIP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$11COperAndCfg", (char*) _vt$11COperAndCfg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$11CSocketNode", (char*) _vt$11CSocketNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12CCtrlPackage", (char*) _vt$12CCtrlPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12CDataPackage", (char*) _vt$12CDataPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12CFunctionLed", (char*) _vt$12CFunctionLed, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12CFunctionVer", (char*) _vt$12CFunctionVer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12CHDDataBoard", (char*) _vt$12CHDDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12CSDDataBoard", (char*) _vt$12CSDDataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12CSoftUpGrade", (char*) _vt$12CSoftUpGrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$13CFunctionTemp", (char*) _vt$13CFunctionTemp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$13bad_exception", (char*) _vt$13bad_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$14C2800DataBoard", (char*) _vt$14C2800DataBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$14COnLinePackage", (char*) _vt$14COnLinePackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$14COperAttribute", (char*) _vt$14COperAttribute, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$14CPeriodicTimer", (char*) _vt$14CPeriodicTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$14CSystemMessage", (char*) _vt$14CSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$14__si_type_info", (char*) _vt$14__si_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$15CDebugTcpSocket", (char*) _vt$15CDebugTcpSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$15CFunctionInSlot", (char*) _vt$15CFunctionInSlot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$16CFunctionRestart", (char*) _vt$16CFunctionRestart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$16CFunctionVoltage", (char*) _vt$16CFunctionVoltage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$16__user_type_info", (char*) _vt$16__user_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$17CFunctionPortInfo", (char*) _vt$17CFunctionPortInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$17CKeepAlivePackage", (char*) _vt$17CKeepAlivePackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$17__class_type_info", (char*) _vt$17__class_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$18CProtocolInterface", (char*) _vt$18CProtocolInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$20CFunctionManufacture", (char*) _vt$20CFunctionManufacture, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$20CRebootSystemMessage", (char*) _vt$20CRebootSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$21COfflineSystemMessage", (char*) _vt$21COfflineSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$21CStandbySystemMessage", (char*) _vt$21CStandbySystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$21CStartupSystemMessage", (char*) _vt$21CStartupSystemMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$22_IO_istream_withassign$3ios", (char*) _vt$22_IO_istream_withassign$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$22_IO_ostream_withassign$3ios", (char*) _vt$22_IO_ostream_withassign$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$3CNe", (char*) _vt$3CNe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$3ios", (char*) _vt$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$4CWnd", (char*) _vt$4CWnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$5CFile", (char*) _vt$5CFile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$5CRoot", (char*) _vt$5CRoot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$6CBoard", (char*) _vt$6CBoard, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$6CCross", (char*) _vt$6CCross, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$6CTimer", (char*) _vt$6CTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7CModule", (char*) _vt$7CModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7filebuf", (char*) _vt$7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7istream$3ios", (char*) _vt$7istream$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7ostream$3ios", (char*) _vt$7ostream$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$8CChannel", (char*) _vt$8CChannel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$8CDesktop", (char*) _vt$8CDesktop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$8CPackage", (char*) _vt$8CPackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$8bad_cast", (char*) _vt$8bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$8iostream$3ios", (char*) _vt$8iostream$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9CColorKey", (char*) _vt$9CColorKey, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9CFunction", (char*) _vt$9CFunction, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9CLinkNode", (char*) _vt$9CLinkNode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9CListener", (char*) _vt$9CListener, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9CProtocol", (char*) _vt$9CProtocol, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9bad_alloc", (char*) _vt$9bad_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9exception", (char*) _vt$9exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9streambuf", (char*) _vt$9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9type_info", (char*) _vt$9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vtable__9streambuf", (char*) _vtable__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_wdbTaskBpAdd", (char*) &_wdbTaskBpAdd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_wdbTaskBpTrap", (char*) &_wdbTaskBpTrap, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_wdbTaskCont", (char*) &_wdbTaskCont, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_wdbTaskStep", (char*) &_wdbTaskStep, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_wdbTgtHasAltivec", (char*) &_wdbTgtHasAltivec, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_wdbTgtHasDsp", (char*) &_wdbTgtHasDsp, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_wdbTgtHasFpp", (char*) &_wdbTgtHasFpp, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "abort", (char*) abort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "abs", (char*) abs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "accept", (char*) accept, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ack1", (char*) &ack1, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ack2", (char*) &ack2, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "acos", (char*) acos, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "activeQHead", (char*) &activeQHead, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "addDomain", (char*) addDomain, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "addSegNames", (char*) addSegNames, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "alarmDebug", (char*) alarmDebug, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocate__9streambuf", (char*) allocate__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocate__t23__malloc_alloc_template1i0Ul", (char*) allocate__t23__malloc_alloc_template1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocate__t24__default_alloc_template2b1i0Ul", (char*) allocate__t24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocbuf__9streambuf", (char*) allocbuf__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "armGetNpc", (char*) armGetNpc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "armInitExceptionModes", (char*) armInitExceptionModes, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "armInstrChangesPc", (char*) armInstrChangesPc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpAdd", (char*) arpAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpCmd", (char*) arpCmd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpDelete", (char*) arpDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpFlush", (char*) arpFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpLibInit", (char*) arpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpMaxEntries", (char*) &arpMaxEntries, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "arpResolve", (char*) arpResolve, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpRxmitTicks", (char*) &arpRxmitTicks, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "arpShow", (char*) arpShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arp_allocated", (char*) &arp_allocated, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "arp_intimer", (char*) &arp_intimer, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "arp_inuse", (char*) &arp_inuse, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "arp_maxtries", (char*) &arp_maxtries, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "arp_rtrequest", (char*) arp_rtrequest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpinit_done", (char*) &arpinit_done, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "arpintr", (char*) arpintr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpintrq", (char*) &arpintrq, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "arpioctl", (char*) arpioctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpresolve", (char*) arpresolve, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpt_down", (char*) &arpt_down, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "arpt_keep", (char*) &arpt_keep, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "arpt_prune", (char*) &arpt_prune, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "arptabShow", (char*) arptabShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arptfree", (char*) arptfree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "arpwhohas", (char*) arpwhohas, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "asctime", (char*) asctime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "asctime_r", (char*) asctime_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "asin", (char*) asin, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthFlagsSet", (char*) at91EthFlagsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthInit", (char*) at91EthInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthLoopSet", (char*) at91EthLoopSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthMCastAdd", (char*) at91EthMCastAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthMCastDel", (char*) at91EthMCastDel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthMiiShow", (char*) at91EthMiiShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthMulTest", (char*) at91EthMulTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthPollReceive", (char*) at91EthPollReceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthPollSend", (char*) at91EthPollSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthPollStart", (char*) at91EthPollStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthPollStop", (char*) at91EthPollStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthRbdCheck", (char*) at91EthRbdCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthRbdFree", (char*) at91EthRbdFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthRbdProcess", (char*) at91EthRbdProcess, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthSend", (char*) at91EthSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthSend2", (char*) at91EthSend2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthShow", (char*) at91EthShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthStart", (char*) at91EthStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthStop", (char*) at91EthStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthTbdCheck", (char*) at91EthTbdCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthTbdFree", (char*) at91EthTbdFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthTbdGet", (char*) at91EthTbdGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthTbdProcess", (char*) at91EthTbdProcess, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthTbdStart", (char*) at91EthTbdStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthURbdProcess", (char*) at91EthURbdProcess, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91IntDevInit", (char*) at91IntDevInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91SioDevInit", (char*) at91SioDevInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91SioDevInit2", (char*) at91SioDevInit2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91SioInt", (char*) at91SioInt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atan", (char*) atan, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atan2", (char*) atan2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atexit", (char*) atexit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atof", (char*) atof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atoi", (char*) atoi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "atol", (char*) atol, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "attach__7filebufi", (char*) attach__7filebufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "attrib", (char*) attrib, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "b", (char*) b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bad__C3ios", (char*) bad__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "base__C9streambuf", (char*) base__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcmp", (char*) bcmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopy", (char*) bcopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopyBytes", (char*) bcopyBytes, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopyLongs", (char*) bcopyLongs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopyWords", (char*) bcopyWords, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bcopy_to_mbufs", (char*) bcopy_to_mbufs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bd", (char*) bd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bdall", (char*) bdall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "before__C9type_infoRC9type_info", (char*) before__C9type_infoRC9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bfill", (char*) bfill, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bfillBytes", (char*) bfillBytes, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bind", (char*) bind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bindresvport", (char*) bindresvport, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "binvert", (char*) binvert, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bitreverse", (char*) bitreverse, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "blen__C9streambuf", (char*) blen__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootBpAnchorExtract", (char*) bootBpAnchorExtract, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootChange", (char*) bootChange, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootLeaseExtract", (char*) bootLeaseExtract, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootNetmaskExtract", (char*) bootNetmaskExtract, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootParamsErrorPrint", (char*) bootParamsErrorPrint, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootParamsPrompt", (char*) bootParamsPrompt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootParamsShow", (char*) bootParamsShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootScanNum", (char*) bootScanNum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootStringToStruct", (char*) bootStringToStruct, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bootStructToString", (char*) bootStructToString, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bpFreeList", (char*) &bpFreeList, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bpList", (char*) &bpList, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "bsdAccept", (char*) bsdAccept, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdBind", (char*) bsdBind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdConnect", (char*) bsdConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdConnectWithTimeout", (char*) bsdConnectWithTimeout, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdGetpeername", (char*) bsdGetpeername, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdGetsockname", (char*) bsdGetsockname, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdGetsockopt", (char*) bsdGetsockopt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdListen", (char*) bsdListen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdRecv", (char*) bsdRecv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdRecvfrom", (char*) bsdRecvfrom, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdRecvmsg", (char*) bsdRecvmsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdSend", (char*) bsdSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdSendmsg", (char*) bsdSendmsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdSendto", (char*) bsdSendto, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdSetsockopt", (char*) bsdSetsockopt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdShutdown", (char*) bsdShutdown, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdSock43ApiFlag", (char*) &bsdSock43ApiFlag, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "bsdSockFunc", (char*) &bsdSockFunc, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "bsdSockLibInit", (char*) bsdSockLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdSocket", (char*) bsdSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsdZbufSockRtn", (char*) bsdZbufSockRtn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bsearch", (char*) bsearch, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bswap", (char*) bswap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bufAlloc", (char*) bufAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bufFree", (char*) bufFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bufPoolInit", (char*) bufPoolInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bufferedRtShow", (char*) bufferedRtShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "build_cluster", (char*) build_cluster, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "bzero", (char*) bzero, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "c", (char*) c, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchAlignSize", (char*) &cacheArchAlignSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheArchIntLock", (char*) cacheArchIntLock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArchIntMask", (char*) &cacheArchIntMask, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheArchState", (char*) &cacheArchState, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheArm920tArchPipeFlush", (char*) cacheArm920tArchPipeFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tDClear", (char*) cacheArm920tDClear, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tDClearAll", (char*) cacheArm920tDClearAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tDClearDisable", (char*) cacheArm920tDClearDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tDFlush", (char*) cacheArm920tDFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tDFlushAll", (char*) cacheArm920tDFlushAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tDInvalidate", (char*) cacheArm920tDInvalidate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tDInvalidateAll", (char*) cacheArm920tDInvalidateAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tIClearDisable", (char*) cacheArm920tIClearDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tIInvalidate", (char*) cacheArm920tIInvalidate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tIInvalidateAll", (char*) cacheArm920tIInvalidateAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheArm920tLibInstall", (char*) cacheArm920tLibInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheClear", (char*) cacheClear, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDataEnabled", (char*) &cacheDataEnabled, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDataMode", (char*) &cacheDataMode, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDisable", (char*) cacheDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDmaFree", (char*) cacheDmaFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDmaFreeRtn", (char*) &cacheDmaFreeRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDmaFuncs", (char*) &cacheDmaFuncs, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDmaMalloc", (char*) cacheDmaMalloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDmaMallocRtn", (char*) &cacheDmaMallocRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheDrvFlush", (char*) cacheDrvFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDrvInvalidate", (char*) cacheDrvInvalidate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDrvPhysToVirt", (char*) cacheDrvPhysToVirt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheDrvVirtToPhys", (char*) cacheDrvVirtToPhys, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheEnable", (char*) cacheEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheFlush", (char*) cacheFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheFuncsSet", (char*) cacheFuncsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheInvalidate", (char*) cacheInvalidate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheLib", (char*) &cacheLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheLibInit", (char*) cacheLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheLock", (char*) cacheLock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheMmuAvailable", (char*) &cacheMmuAvailable, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cacheNullFuncs", (char*) &cacheNullFuncs, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cachePipeFlush", (char*) cachePipeFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheTextUpdate", (char*) cacheTextUpdate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheUnlock", (char*) cacheUnlock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cacheUserFuncs", (char*) &cacheUserFuncs, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "calloc", (char*) calloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioBlkCopy", (char*) cbioBlkCopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioBlkRW", (char*) cbioBlkRW, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioBytesRW", (char*) cbioBytesRW, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioClass", (char*) &cbioClass, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "cbioClassId", (char*) &cbioClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cbioDevCreate", (char*) cbioDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioDevVerify", (char*) cbioDevVerify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioIoctl", (char*) cbioIoctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioLibInit", (char*) cbioLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioLock", (char*) cbioLock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioModeGet", (char*) cbioModeGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioModeSet", (char*) cbioModeSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioMutexSemOptions", (char*) &cbioMutexSemOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cbioParamsGet", (char*) cbioParamsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioRdyChgdGet", (char*) cbioRdyChgdGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioRdyChgdSet", (char*) cbioRdyChgdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioRdyChk", (char*) cbioRdyChk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioShow", (char*) cbioShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioUnlock", (char*) cbioUnlock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cbioWrapBlkDev", (char*) cbioWrapBlkDev, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cd", (char*) cd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ceil", (char*) ceil, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cerr", (char*) &cerr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cfree", (char*) cfree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "changeReg", (char*) changeReg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "chdir", (char*) chdir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "checkInetAddrField", (char*) checkInetAddrField, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "checkStack", (char*) checkStack, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "check_trailer", (char*) check_trailer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "checksum", (char*) checksum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "chkdsk", (char*) chkdsk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cin", (char*) &cin, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cksum", (char*) cksum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clDescTbl", (char*) &clDescTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "clDescTblNumEnt", (char*) &clDescTblNumEnt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "classClassId", (char*) &classClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "classCreate", (char*) classCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classDestroy", (char*) classDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classInit", (char*) classInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classInstConnect", (char*) classInstConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classInstrument", (char*) classInstrument, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classLibInit", (char*) classLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classMemPartIdSet", (char*) classMemPartIdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "classShowConnect", (char*) classShowConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clear__3iosi", (char*) clear__3iosi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clearerr", (char*) clearerr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock", (char*) clock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clockLibInit", (char*) clockLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_getres", (char*) clock_getres, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_gettime", (char*) clock_gettime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_setres", (char*) clock_setres, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_settime", (char*) clock_settime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clock_show", (char*) clock_show, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "clog", (char*) &clog, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "close", (char*) close, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "close__3ios", (char*) close__3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "close__7filebuf", (char*) close__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "closedir", (char*) closedir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "commtest", (char*) commtest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "connect", (char*) connect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "connectWithTimeout", (char*) connectWithTimeout, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "consoleFd", (char*) &consoleFd, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "contained_nonpublic_p__16__user_type_infoQ216__user_type_info8sub_kind", (char*) contained_nonpublic_p__16__user_type_infoQ216__user_type_info8sub_kind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "contained_nonvirtual_p__16__user_type_infoQ216__user_type_info8sub_kind", (char*) contained_nonvirtual_p__16__user_type_infoQ216__user_type_info8sub_kind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "contained_p__16__user_type_infoQ216__user_type_info8sub_kind", (char*) contained_p__16__user_type_infoQ216__user_type_info8sub_kind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "contained_public_p__16__user_type_infoQ216__user_type_info8sub_kind", (char*) contained_public_p__16__user_type_infoQ216__user_type_info8sub_kind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copy", (char*) copy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copyFromMbufs", (char*) copyFromMbufs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copyStreams", (char*) copyStreams, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copyright_wind_river", (char*) &copyright_wind_river, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "copysign", (char*) copysign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cos", (char*) cos, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cosh", (char*) cosh, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cout", (char*) &cout, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cp", (char*) cp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusArraysInit", (char*) cplusArraysInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCallCtors", (char*) cplusCallCtors, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCallDtors", (char*) cplusCallDtors, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCallNewHandler__Fv", (char*) cplusCallNewHandler__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCtors", (char*) cplusCtors, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusCtorsLink", (char*) cplusCtorsLink, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemangle", (char*) cplusDemangle, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemangleFunc", (char*) &cplusDemangleFunc, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cplusDemanglerInit", (char*) cplusDemanglerInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemanglerMode", (char*) &cplusDemanglerMode, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cplusDemanglerSet", (char*) cplusDemanglerSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDemanglerStyle", (char*) &cplusDemanglerStyle, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "cplusDemanglerStyleSet", (char*) cplusDemanglerStyleSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDtors", (char*) cplusDtors, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusDtorsLink", (char*) cplusDtorsLink, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusLibMinInit", (char*) cplusLibMinInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusLoadFixup", (char*) cplusLoadFixup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusMatchMangled", (char*) cplusMatchMangled, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusNewHandlerExists__Fv", (char*) cplusNewHandlerExists__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusNewHdlMutex", (char*) &cplusNewHdlMutex, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "cplusTerminate__Fv", (char*) cplusTerminate__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusUnloadFixup", (char*) cplusUnloadFixup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusXtorSet", (char*) cplusXtorSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplusXtorStrategy", (char*) &cplusXtorStrategy, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cplus_demangle", (char*) cplus_demangle, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplus_demangle_name_to_style", (char*) cplus_demangle_name_to_style, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplus_demangle_opname", (char*) cplus_demangle_opname, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplus_demangle_set_style", (char*) cplus_demangle_set_style, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplus_demangle_v3", (char*) cplus_demangle_v3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cplus_mangle_opname", (char*) cplus_mangle_opname, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cpsr", (char*) cpsr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "crc32_le", (char*) crc32_le, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "creat", (char*) creat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "creationDate", (char*) &creationDate, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cret", (char*) cret, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ctime", (char*) ctime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ctime_r", (char*) ctime_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cur_ptr__7filebuf", (char*) cur_ptr__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "currentContext", (char*) &currentContext, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "current_demangling_style", (char*) &current_demangling_style, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "d", (char*) d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "db_print_sa", (char*) db_print_sa, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "db_show_arptab", (char*) db_show_arptab, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgHelp", (char*) dbgHelp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgInit", (char*) dbgInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgLockUnbreakable", (char*) &dbgLockUnbreakable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dbgPrintCall", (char*) dbgPrintCall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgPrintDsp", (char*) &dbgPrintDsp, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dbgPrintFpp", (char*) &dbgPrintFpp, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dbgPrintSimd", (char*) &dbgPrintSimd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dbgSafeUnbreakable", (char*) &dbgSafeUnbreakable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dbgTaskBpBreakpoint", (char*) dbgTaskBpBreakpoint, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgTaskBpHooksInstall", (char*) dbgTaskBpHooksInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgTaskBpTrace", (char*) dbgTaskBpTrace, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgTaskBpTrap", (char*) dbgTaskBpTrap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgTaskCont", (char*) dbgTaskCont, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgTaskStep", (char*) dbgTaskStep, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dbgUnbreakableOld", (char*) &dbgUnbreakableOld, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dcacheCtrl", (char*) &dcacheCtrl, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dcacheDevCreate", (char*) dcacheDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dcacheDevDisable", (char*) dcacheDevDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dcacheDevEnable", (char*) dcacheDevEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dcacheDevMemResize", (char*) dcacheDevMemResize, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dcacheDevTune", (char*) dcacheDevTune, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dcacheShow", (char*) dcacheShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dcacheUpd", (char*) dcacheUpd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dcacheUpdTaskId", (char*) &dcacheUpdTaskId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dcacheUpdTaskOptions", (char*) &dcacheUpdTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dcacheUpdTaskPriority", (char*) &dcacheUpdTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dcacheUpdTaskStack", (char*) &dcacheUpdTaskStack, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ddiv_mantissas", (char*) ddiv_mantissas, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "deallocate__t23__malloc_alloc_template1i0PvUl", (char*) deallocate__t23__malloc_alloc_template1i0PvUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "deallocate__t24__default_alloc_template2b1i0PvUl", (char*) deallocate__t24__default_alloc_template2b1i0PvUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dec__FR3ios", (char*) dec__FR3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "decode_identifier", (char*) decode_identifier, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "decode_identifier_styled", (char*) decode_identifier_styled, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "delayNSec", (char*) delayNSec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "delayUSec", (char*) delayUSec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "delta__12streammarker", (char*) delta__12streammarker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "delta__12streammarkerR12streammarker", (char*) delta__12streammarkerR12streammarker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devSplit", (char*) devSplit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devs", (char*) devs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "difftime", (char*) difftime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dirList", (char*) dirList, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "diskFormat", (char*) diskFormat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "diskInit", (char*) diskInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dispLM73reg", (char*) dispLM73reg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "div", (char*) div, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "div_r", (char*) div_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllAdd", (char*) dllAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllCount", (char*) dllCount, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllCreate", (char*) dllCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllDelete", (char*) dllDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllEach", (char*) dllEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllGet", (char*) dllGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllInit", (char*) dllInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllInsert", (char*) dllInsert, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllRemove", (char*) dllRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dllTerminate", (char*) dllTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_dyncast__C14__si_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result", (char*) do_dyncast__C14__si_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_dyncast__C16__user_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result", (char*) do_dyncast__C16__user_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_dyncast__C17__class_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result", (char*) do_dyncast__C17__class_type_infoiQ216__user_type_info8sub_kindRC9type_infoPvT3T4RQ216__user_type_info14dyncast_result, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_find_public_subobj__C14__si_type_infoiRC9type_infoPvT3", (char*) do_find_public_subobj__C14__si_type_infoiRC9type_infoPvT3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_find_public_subobj__C16__user_type_infoiRC9type_infoPvT3", (char*) do_find_public_subobj__C16__user_type_infoiRC9type_infoPvT3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_find_public_subobj__C17__class_type_infoiRC9type_infoPvT3", (char*) do_find_public_subobj__C17__class_type_infoiRC9type_infoPvT3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_osfx__7ostream", (char*) do_osfx__7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_protocol_with_type", (char*) do_protocol_with_type, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_upcast__C14__si_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result", (char*) do_upcast__C14__si_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_upcast__C16__user_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result", (char*) do_upcast__C16__user_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "do_upcast__C17__class_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result", (char*) do_upcast__C17__class_type_infoQ216__user_type_info8sub_kindRC9type_infoPvRQ216__user_type_info13upcast_result, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "doallocate__7filebuf", (char*) doallocate__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "doallocate__9streambuf", (char*) doallocate__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "doallocbuf__9streambuf", (char*) doallocbuf__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "domaininit", (char*) domaininit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "domains", (char*) &domains, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dosChkDebug", (char*) &dosChkDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosChkDsk", (char*) dosChkDsk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosChkEntryMark", (char*) dosChkEntryMark, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosChkLibInit", (char*) dosChkLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosChkMinDate", (char*) &dosChkMinDate, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosDirHdlrsList", (char*) &dosDirHdlrsList, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosDirOldDebug", (char*) &dosDirOldDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosDirOldLibInit", (char*) dosDirOldLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFatHdlrsList", (char*) &dosFatHdlrsList, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsCacheSizeDefault", (char*) &dosFsCacheSizeDefault, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsChkDsk", (char*) dosFsChkDsk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsChkRtn", (char*) &dosFsChkRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsChkTree", (char*) dosFsChkTree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsConfigGet", (char*) dosFsConfigGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsConfigInit", (char*) dosFsConfigInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsConfigShow", (char*) dosFsConfigShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDateTimeInstall", (char*) dosFsDateTimeInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDebug", (char*) &dosFsDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsDevCreate", (char*) dosFsDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDevInit", (char*) dosFsDevInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDevInitOptionsSet", (char*) dosFsDevInitOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsDrvNum", (char*) &dosFsDrvNum, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsFatInit", (char*) dosFsFatInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsFmtLibInit", (char*) dosFsFmtLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsHdlrInstall", (char*) dosFsHdlrInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsInit", (char*) dosFsInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsLastAccessDateEnable", (char*) dosFsLastAccessDateEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsLibInit", (char*) dosFsLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsMkfs", (char*) dosFsMkfs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsMkfsOptionsSet", (char*) dosFsMkfsOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsModeChange", (char*) dosFsModeChange, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsReadyChange", (char*) dosFsReadyChange, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsShow", (char*) dosFsShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolDescGet", (char*) dosFsVolDescGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolFormat", (char*) dosFsVolFormat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolFormatRtn", (char*) &dosFsVolFormatRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosFsVolIsFat12", (char*) dosFsVolIsFat12, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolOptionsGet", (char*) dosFsVolOptionsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolOptionsSet", (char*) dosFsVolOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosFsVolUnmount", (char*) dosFsVolUnmount, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosSetVolCaseSens", (char*) dosSetVolCaseSens, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dosVDirDebug", (char*) &dosVDirDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "dosVDirLibInit", (char*) dosVDirLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "drvTable", (char*) &drvTable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "dsmInst", (char*) dsmInst, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dsmNbytes", (char*) dsmNbytes, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dyncast__C16__user_type_infoiRC9type_infoPvT2T3", (char*) dyncast__C16__user_type_infoiRC9type_infoPvT2T3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "e", (char*) e, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eBptr__9streambuf", (char*) eBptr__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eGptr__9streambuf", (char*) eGptr__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eNptr__9streambuf", (char*) eNptr__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eback__C9streambuf", (char*) eback__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ebuf__C9streambuf", (char*) ebuf__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eepromRead", (char*) eepromRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "egptr__C9streambuf", (char*) egptr__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "elfArmInit", (char*) elfArmInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "elfRelocRelEntryRd", (char*) elfRelocRelEntryRd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "elfRelocRelaEntryRd", (char*) elfRelocRelaEntryRd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "end8023AddressForm", (char*) end8023AddressForm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endDevName", (char*) endDevName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endDevTbl", (char*) &endDevTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "endEtherAddressForm", (char*) endEtherAddressForm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endEtherPacketAddrGet", (char*) endEtherPacketAddrGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endEtherPacketDataGet", (char*) endEtherPacketDataGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFindByName", (char*) endFindByName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFlagsClr", (char*) endFlagsClr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFlagsGet", (char*) endFlagsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endFlagsSet", (char*) endFlagsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endMibIfInit", (char*) endMibIfInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endMultiLstCnt", (char*) endMultiLstCnt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endMultiLstFirst", (char*) endMultiLstFirst, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endMultiLstNext", (char*) endMultiLstNext, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endObjFlagSet", (char*) endObjFlagSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endObjInit", (char*) endObjInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endObjectUnload", (char*) endObjectUnload, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endRcvRtnCall", (char*) endRcvRtnCall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endTxSemGive", (char*) endTxSemGive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endTxSemTake", (char*) endTxSemTake, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endl__FR7ostream", (char*) endl__FR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ends__FR7ostream", (char*) ends__FR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envLibInit", (char*) envLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envPrivateCreate", (char*) envPrivateCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envPrivateDestroy", (char*) envPrivateDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envShow", (char*) envShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eof__C3ios", (char*) eof__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "epptr__C9streambuf", (char*) epptr__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "errno", (char*) &errno, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "errnoGet", (char*) errnoGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "errnoOfTaskGet", (char*) errnoOfTaskGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "errnoOfTaskSet", (char*) errnoOfTaskSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "errnoSet", (char*) errnoSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "etherMultiAdd", (char*) etherMultiAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "etherMultiDebug", (char*) &etherMultiDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "etherMultiDel", (char*) etherMultiDel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "etherMultiGet", (char*) etherMultiGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ether_addmulti", (char*) ether_addmulti, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ether_attach", (char*) ether_attach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ether_delmulti", (char*) ether_delmulti, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ether_ifattach", (char*) ether_ifattach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ether_input", (char*) ether_input, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ether_ipmulticast_max", (char*) &ether_ipmulticast_max, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ether_ipmulticast_min", (char*) &ether_ipmulticast_min, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ether_output", (char*) ether_output, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ether_sprintf", (char*) ether_sprintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "etherbroadcastaddr", (char*) &etherbroadcastaddr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "eventClear", (char*) eventClear, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventEvtRtn", (char*) &eventEvtRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "eventInit", (char*) eventInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventLibInit", (char*) eventLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventReceive", (char*) eventReceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventRsrcSend", (char*) eventRsrcSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventRsrcShow", (char*) eventRsrcShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventSend", (char*) eventSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventStart", (char*) eventStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventTaskShow", (char*) eventTaskShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eventTerminate", (char*) eventTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "evtAction", (char*) &evtAction, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excEnterDataAbort", (char*) excEnterDataAbort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excEnterPrefetchAbort", (char*) excEnterPrefetchAbort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excEnterSwi", (char*) excEnterSwi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excEnterUndef", (char*) excEnterUndef, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excExcContinue", (char*) excExcContinue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excExcHandle", (char*) excExcHandle, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excExcepHook", (char*) &excExcepHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "excHookAdd", (char*) excHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excInit", (char*) excInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excIntConnect", (char*) excIntConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excIntHandle", (char*) excIntHandle, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excJobAdd", (char*) excJobAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excMsgQId", (char*) &excMsgQId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "excShowInit", (char*) excShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excTask", (char*) excTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excTaskId", (char*) &excTaskId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "excTaskOptions", (char*) &excTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excTaskPriority", (char*) &excTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excTaskStackSize", (char*) &excTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "excVecGet", (char*) excVecGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excVecInit", (char*) excVecInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "excVecSet", (char*) excVecSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "exceptions__3iosi", (char*) exceptions__3iosi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "exceptions__C3ios", (char*) exceptions__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "execute", (char*) execute, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "exit", (char*) exit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "exp", (char*) exp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "expm1", (char*) expm1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fabs", (char*) fabs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fail__C3ios", (char*) fail__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fat16ClustValueGet", (char*) fat16ClustValueGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fat16ClustValueSet", (char*) fat16ClustValueSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fat16Debug", (char*) &fat16Debug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fat16VolMount", (char*) fat16VolMount, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fatClugFac", (char*) &fatClugFac, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fclose", (char*) fclose, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fd", (char*) &fd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "fdTable", (char*) &fdTable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "fd__C7filebuf", (char*) fd__C7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fdopen", (char*) fdopen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fdprintf", (char*) fdprintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "feof", (char*) feof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ferror", (char*) ferror, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fflush", (char*) fflush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ffsLsb", (char*) ffsLsb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ffsLsbTbl", (char*) &ffsLsbTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ffsMsb", (char*) ffsMsb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ffsMsbTbl", (char*) &ffsMsbTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fgetc", (char*) fgetc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fgetpos", (char*) fgetpos, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fgets", (char*) fgets, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fieldSzIncludeSign", (char*) &fieldSzIncludeSign, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "file_ptr__7filebuf", (char*) file_ptr__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fileno", (char*) fileno, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fill__3ioss", (char*) fill__3ioss, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fill__C3ios", (char*) fill__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_public_subobj__C16__user_type_infoiRC9type_infoPvT3", (char*) find_public_subobj__C16__user_type_infoiRC9type_infoPvT3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioFltInstall", (char*) fioFltInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioFormatV", (char*) fioFormatV, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioLibInit", (char*) fioLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioRdString", (char*) fioRdString, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioRead", (char*) fioRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fioScanV", (char*) fioScanV, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flAddLongToFarPointer", (char*) flAddLongToFarPointer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flBufferOf", (char*) flBufferOf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flCall", (char*) flCall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flCreateMutex", (char*) flCreateMutex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flCurrentDate", (char*) flCurrentDate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flCurrentTime", (char*) flCurrentTime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flDelayLoop", (char*) flDelayLoop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flDontNeedVcc", (char*) flDontNeedVcc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flDontNeedVpp", (char*) flDontNeedVpp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flDosFormat", (char*) flDosFormat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flFitInSocketWindow", (char*) flFitInSocketWindow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flFormat", (char*) flFormat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flFreeMutex", (char*) flFreeMutex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flGetMappingContext", (char*) flGetMappingContext, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flIdentifyFlash", (char*) flIdentifyFlash, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flInit", (char*) flInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flInitSockets", (char*) flInitSockets, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flInstallTimer", (char*) flInstallTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flIntelIdentify", (char*) flIntelIdentify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flIntelSize", (char*) flIntelSize, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flIntervalRoutine", (char*) flIntervalRoutine, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flMap", (char*) flMap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flMediaCheck", (char*) flMediaCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flMinClusterSize", (char*) &flMinClusterSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "flMount", (char*) flMount, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flMsecCounter", (char*) &flMsecCounter, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "flNeedVcc", (char*) flNeedVcc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flNeedVpp", (char*) flNeedVpp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flPollSemId", (char*) &flPollSemId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "flPollTask", (char*) flPollTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flRandByte", (char*) flRandByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flRegisterComponents", (char*) flRegisterComponents, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flResetCardChanged", (char*) flResetCardChanged, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flSetPowerOnCallback", (char*) flSetPowerOnCallback, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flSetWindowBusWidth", (char*) flSetWindowBusWidth, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flSetWindowSize", (char*) flSetWindowSize, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flSetWindowSpeed", (char*) flSetWindowSpeed, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flSocketNoOf", (char*) flSocketNoOf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flSocketOf", (char*) flSocketOf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flSocketSetBusy", (char*) flSocketSetBusy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flSysfunInit", (char*) flSysfunInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flTakeMutex", (char*) flTakeMutex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flWriteProtected", (char*) flWriteProtected, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flags__3iosUl", (char*) flags__3iosUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flags__C3ios", (char*) flags__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "floatInit", (char*) floatInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "floor", (char*) floor, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flush__7ostream", (char*) flush__7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flush__FR7ostream", (char*) flush__FR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flush_all__9streambuf", (char*) flush_all__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flush_all_linebuffered__9streambuf", (char*) flush_all_linebuffered__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flwAmdIdentify", (char*) flwAmdIdentify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flwAmdMTDIdentify", (char*) flwAmdMTDIdentify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flwAmdSize", (char*) flwAmdSize, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fmod", (char*) fmod, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fopen", (char*) fopen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "formatFTL", (char*) formatFTL, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fpArmModules", (char*) &fpArmModules, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fpClassId", (char*) &fpClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fpCtlRegName", (char*) &fpCtlRegName, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fpRegName", (char*) &fpRegName, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fpTypeGet", (char*) fpTypeGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppArchInit", (char*) fppArchInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppArchTaskCreateInit", (char*) fppArchTaskCreateInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppCreateHookRtn", (char*) &fppCreateHookRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "fppDisplayHookRtn", (char*) &fppDisplayHookRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "fppInit", (char*) fppInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppProbe", (char*) fppProbe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppRestore", (char*) fppRestore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppSave", (char*) fppSave, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppShowInit", (char*) fppShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppTaskRegsCFmt", (char*) &fppTaskRegsCFmt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fppTaskRegsDFmt", (char*) &fppTaskRegsDFmt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fppTaskRegsGet", (char*) fppTaskRegsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppTaskRegsSet", (char*) fppTaskRegsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fppTaskRegsShow", (char*) fppTaskRegsShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fprintf", (char*) fprintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fputc", (char*) fputc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fputs", (char*) fputs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fread", (char*) fread, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "free", (char*) free, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "free_backup_area__9streambuf", (char*) free_backup_area__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "freopen", (char*) freopen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "frexp", (char*) frexp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fromBCD", (char*) fromBCD, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fromUNAL", (char*) fromUNAL, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fromUNALLONG", (char*) fromUNALLONG, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fscanf", (char*) fscanf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fseek", (char*) fseek, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fsetpos", (char*) fsetpos, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fstat", (char*) fstat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "fstatfs", (char*) fstatfs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftell", (char*) ftell, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpCommand", (char*) ftpCommand, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpCommandEnhanced", (char*) ftpCommandEnhanced, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpDataConnGet", (char*) ftpDataConnGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpDataConnInit", (char*) ftpDataConnInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpDataConnInitPassiveMode", (char*) ftpDataConnInitPassiveMode, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpHookup", (char*) ftpHookup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpLibDebugOptionsSet", (char*) ftpLibDebugOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpLogin", (char*) ftpLogin, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpLs", (char*) ftpLs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpReplyGet", (char*) ftpReplyGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpReplyGetEnhanced", (char*) ftpReplyGetEnhanced, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpTransientConfigGet", (char*) ftpTransientConfigGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpTransientConfigSet", (char*) ftpTransientConfigSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpTransientFatalInstall", (char*) ftpTransientFatalInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpXfer", (char*) ftpXfer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpdDebug", (char*) &ftpdDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpdDelete", (char*) ftpdDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpdInit", (char*) ftpdInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ftpdTaskOptions", (char*) &ftpdTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpdTaskPriority", (char*) &ftpdTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpdWindowSize", (char*) &ftpdWindowSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpdWorkTaskOptions", (char*) &ftpdWorkTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpdWorkTaskPriority", (char*) &ftpdWorkTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpdWorkTaskStackSize", (char*) &ftpdWorkTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftplDebug", (char*) &ftplDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftplPasvModeDisable", (char*) &ftplPasvModeDisable, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftplTransientMaxRetryCount", (char*) &ftplTransientMaxRetryCount, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftplTransientRetryInterval", (char*) &ftplTransientRetryInterval, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ftpsCurrentClients", (char*) &ftpsCurrentClients, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ftpsMaxClients", (char*) &ftpsMaxClients, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "fwrite", (char*) fwrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "g_AlarmInfo", (char*) &g_AlarmInfo, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_CommVer1", (char*) &g_CommVer1, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_CommVer2", (char*) &g_CommVer2, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_EventInfo", (char*) &g_EventInfo, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_SysInitInfo", (char*) &g_SysInitInfo, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_UpgradeFlage", (char*) &g_UpgradeFlage, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_as485TestResult", (char*) &g_as485TestResult, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_asPingResult", (char*) &g_asPingResult, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_by485Test", (char*) &g_by485Test, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_byBuzzer", (char*) &g_byBuzzer, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwAlarmPrint", (char*) &g_dwAlarmPrint, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwBdInterPrint", (char*) &g_dwBdInterPrint, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwCommTestPri", (char*) &g_dwCommTestPri, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwEndTimeMSec", (char*) &g_dwEndTimeMSec, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwEndTimeSec", (char*) &g_dwEndTimeSec, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwInterPrint", (char*) &g_dwInterPrint, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwPingSerialNumber", (char*) &g_dwPingSerialNumber, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwPrintTrace", (char*) &g_dwPrintTrace, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwPrintfAllLog", (char*) &g_dwPrintfAllLog, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwPrintfDugLog", (char*) &g_dwPrintfDugLog, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwPrintfEntryLog", (char*) &g_dwPrintfEntryLog, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwPrintfErrLog", (char*) &g_dwPrintfErrLog, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwPrintfExitLog", (char*) &g_dwPrintfExitLog, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwPrintfTimeLog", (char*) &g_dwPrintfTimeLog, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwRecvNormalPkg", (char*) &g_dwRecvNormalPkg, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwRecvUrgentPkg", (char*) &g_dwRecvUrgentPkg, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwSend", (char*) &g_dwSend, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwSendNormalPkg", (char*) &g_dwSendNormalPkg, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwSendUrgentPkg", (char*) &g_dwSendUrgentPkg, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwSerialNumber", (char*) &g_dwSerialNumber, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwSockPrint", (char*) &g_dwSockPrint, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwSoftPara", (char*) &g_dwSoftPara, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwStartTimeMSec", (char*) &g_dwStartTimeMSec, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_dwStartTimeSec", (char*) &g_dwStartTimeSec, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_iDebugSwitch", (char*) &g_iDebugSwitch, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_iVoltageUniteVal", (char*) &g_iVoltageUniteVal, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_pObject", (char*) &g_pObject, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_pclaDataPackage", (char*) &g_pclaDataPackage, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_psMessage", (char*) &g_psMessage, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "g_semFileOper", (char*) &g_semFileOper, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "g_stLastSocketBuf", (char*) &g_stLastSocketBuf, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "gbump__9streambufi", (char*) gbump__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gcount__7istream", (char*) gcount__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get485clients", (char*) get485clients, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getTemperatureValue", (char*) getTemperatureValue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getVoltage", (char*) getVoltage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get__7istream", (char*) get__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get__7istreamPScic", (char*) get__7istreamPScic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get__7istreamPUcic", (char*) get__7istreamPUcic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get__7istreamPcic", (char*) get__7istreamPcic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get__7istreamRSc", (char*) get__7istreamRSc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get__7istreamRUc", (char*) get__7istreamRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get__7istreamRc", (char*) get__7istreamRc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get_column__9streambuf", (char*) get_column__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getc", (char*) getc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getchar", (char*) getchar, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getcwd", (char*) getcwd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getenv", (char*) getenv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gethostname", (char*) gethostname, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getline__7istreamPScic", (char*) getline__7istreamPScic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getline__7istreamPUcic", (char*) getline__7istreamPUcic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getline__7istreamPcic", (char*) getline__7istreamPcic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getmailboxes", (char*) getmailboxes, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getmodules", (char*) getmodules, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getpeername", (char*) getpeername, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gets", (char*) gets, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gets__7istreamPPcc", (char*) gets__7istreamPPcc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getsockname", (char*) getsockname, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getsockopt", (char*) getsockopt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gettcpclients", (char*) gettcpclients, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gettimers", (char*) gettimers, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getw", (char*) getw, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getwd", (char*) getwd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gmtime", (char*) gmtime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gmtime_r", (char*) gmtime_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "good__C3ios", (char*) good__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gptr__C9streambuf", (char*) gptr__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "h", (char*) h, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashClassId", (char*) &hashClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hashFuncIterScale", (char*) hashFuncIterScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashFuncModulo", (char*) hashFuncModulo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashFuncMultiply", (char*) hashFuncMultiply, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashKeyCmp", (char*) hashKeyCmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashKeyStrCmp", (char*) hashKeyStrCmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashLibInit", (char*) hashLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblCreate", (char*) hashTblCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblDelete", (char*) hashTblDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblDestroy", (char*) hashTblDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblEach", (char*) hashTblEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblFind", (char*) hashTblFind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblInit", (char*) hashTblInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblPut", (char*) hashTblPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblRemove", (char*) hashTblRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashTblTerminate", (char*) hashTblTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hashinit", (char*) hashinit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "have_backup__9streambuf", (char*) have_backup__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "have_markers__9streambuf", (char*) have_markers__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "help", (char*) help, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hex__FR3ios", (char*) hex__FR3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostAdd", (char*) hostAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostDelete", (char*) hostDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostGetByAddr", (char*) hostGetByAddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostGetByName", (char*) hostGetByName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostInitFlag", (char*) &hostInitFlag, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hostList", (char*) &hostList, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "hostListSem", (char*) &hostListSem, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "hostShow", (char*) hostShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostTblInit", (char*) hostTblInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostTblSearchByAddr", (char*) hostTblSearchByAddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "hostTblSearchByName", (char*) hostTblSearchByName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i", (char*) i, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i2cReadWrite", (char*) i2cReadWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i2cStart", (char*) i2cStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "i2c_ack_stat", (char*) &i2c_ack_stat, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "iam", (char*) iam, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmpCfgParams", (char*) &icmpCfgParams, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "icmpLibInit", (char*) icmpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmpMaskGet", (char*) icmpMaskGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmp_ctloutput", (char*) icmp_ctloutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmp_init", (char*) icmp_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmp_input", (char*) icmp_input, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmpmask", (char*) &icmpmask, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "icmpmaskrepl", (char*) &icmpmaskrepl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "icmpstat", (char*) &icmpstat, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ifAddrAdd", (char*) ifAddrAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAddrDelete", (char*) ifAddrDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAddrGet", (char*) ifAddrGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAddrSet", (char*) ifAddrSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifAllRoutesDelete", (char*) ifAllRoutesDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifBroadcastGet", (char*) ifBroadcastGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifBroadcastSet", (char*) ifBroadcastSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifDstAddrGet", (char*) ifDstAddrGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifDstAddrSet", (char*) ifDstAddrSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifFlagChange", (char*) ifFlagChange, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifFlagGet", (char*) ifFlagGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifFlagSet", (char*) ifFlagSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifIndexAlloc", (char*) ifIndexAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifIndexLibInit", (char*) ifIndexLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifIndexLibShutdown", (char*) ifIndexLibShutdown, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifIndexTest", (char*) ifIndexTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifIndexToIfName", (char*) ifIndexToIfName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifIndexToIfp", (char*) ifIndexToIfp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifMaskGet", (char*) ifMaskGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifMaskSet", (char*) ifMaskSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifMetricGet", (char*) ifMetricGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifMetricSet", (char*) ifMetricSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifNameToIfIndex", (char*) ifNameToIfIndex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifRouteDelete", (char*) ifRouteDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifShow", (char*) ifShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "if_attach", (char*) if_attach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "if_dettach", (char*) if_dettach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "if_down", (char*) if_down, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "if_qflush", (char*) if_qflush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "if_slowtimo", (char*) if_slowtimo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "if_slowtimoRestart", (char*) if_slowtimoRestart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "if_up", (char*) if_up, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifa_ifwithaddr", (char*) ifa_ifwithaddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifa_ifwithaf", (char*) ifa_ifwithaf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifa_ifwithdstaddr", (char*) ifa_ifwithdstaddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifa_ifwithnet", (char*) ifa_ifwithnet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifa_ifwithroute", (char*) ifa_ifwithroute, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifafree", (char*) ifafree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifaof_ifpforaddr", (char*) ifaof_ifpforaddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifconf", (char*) ifconf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifinit", (char*) ifinit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifioctl", (char*) ifioctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifnet", (char*) &ifnet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ifpromisc", (char*) ifpromisc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifreset", (char*) ifreset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifreset2", (char*) ifreset2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifresetImmediate", (char*) ifresetImmediate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ifunit", (char*) ifunit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "igmpLibInit", (char*) igmpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "igmp_fasttimo", (char*) igmp_fasttimo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "igmp_init", (char*) igmp_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "igmp_input", (char*) igmp_input, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "igmp_slowtimo", (char*) igmp_slowtimo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "igmpstat", (char*) &igmpstat, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ignore__7istreamii", (char*) ignore__7istreamii, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ignore__9streambufi", (char*) ignore__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_addmulti", (char*) in_addmulti, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_avail__9streambuf", (char*) in_avail__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_backup__9streambuf", (char*) in_backup__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_broadcast", (char*) in_broadcast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_canforward", (char*) in_canforward, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_cksum", (char*) in_cksum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_control", (char*) in_control, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_delmulti", (char*) in_delmulti, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_iaonnetof", (char*) in_iaonnetof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_ifaddr", (char*) &in_ifaddr, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "in_ifaddr_remove", (char*) in_ifaddr_remove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_ifinit", (char*) in_ifinit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_ifscrub", (char*) in_ifscrub, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_interfaces", (char*) &in_interfaces, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "in_lnaof", (char*) in_lnaof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_localaddr", (char*) in_localaddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_losing", (char*) in_losing, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_netof", (char*) in_netof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcballoc", (char*) in_pcballoc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcbbind", (char*) in_pcbbind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcbconnect", (char*) in_pcbconnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcbdetach", (char*) in_pcbdetach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcbdisconnect", (char*) in_pcbdisconnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcbinshash", (char*) in_pcbinshash, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcbladdr", (char*) in_pcbladdr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcblookup", (char*) in_pcblookup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcblookuphash", (char*) in_pcblookuphash, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcbnotify", (char*) in_pcbnotify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_pcbrehash", (char*) in_pcbrehash, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_rtchange", (char*) in_rtchange, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_setpeeraddr", (char*) in_setpeeraddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_setsockaddr", (char*) in_setsockaddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "in_socktrim", (char*) in_socktrim, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "index", (char*) index, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_addr", (char*) inet_addr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_aton", (char*) inet_aton, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_lnaof", (char*) inet_lnaof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_makeaddr", (char*) inet_makeaddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_makeaddr_b", (char*) inet_makeaddr_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_netmatch", (char*) inet_netmatch, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_netof", (char*) inet_netof, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_netof_string", (char*) inet_netof_string, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_network", (char*) inet_network, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_ntoa", (char*) inet_ntoa, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inet_ntoa_b", (char*) inet_ntoa_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inetctlerrmap", (char*) &inetctlerrmap, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "inetdomain", (char*) &inetdomain, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "inetstatShow", (char*) inetstatShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inetsw", (char*) &inetsw, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "inflate", (char*) inflate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "inflateCksum", (char*) &inflateCksum, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "initDog", (char*) initDog, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "init__3iosP9streambufP7ostream", (char*) init__3iosP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "init__7filebuf", (char*) init__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initstate", (char*) initstate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "input_ipaddr", (char*) &input_ipaddr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intCnt", (char*) &intCnt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intConnect", (char*) intConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intContext", (char*) intContext, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intCount", (char*) intCount, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intDemuxErrorCount", (char*) &intDemuxErrorCount, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "intDisable", (char*) intDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intEnable", (char*) intEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intEnt", (char*) intEnt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intExit", (char*) intExit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intIFLock", (char*) intIFLock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intIFUnlock", (char*) intIFUnlock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intIntRtnNonPreempt", (char*) intIntRtnNonPreempt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intIntRtnPreempt", (char*) intIntRtnPreempt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLevelSet", (char*) intLevelSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLibInit", (char*) intLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLock", (char*) intLock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLockLevelGet", (char*) intLockLevelGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intLockLevelSet", (char*) intLockLevelSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intRegsLock", (char*) intRegsLock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intRegsUnlock", (char*) intRegsUnlock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intRestrict", (char*) intRestrict, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intUninitVecSet", (char*) intUninitVecSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intUnlock", (char*) intUnlock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVBRSet", (char*) intVBRSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecBaseGet", (char*) intVecBaseGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecBaseSet", (char*) intVecBaseSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "intVecTableWriteProtect", (char*) intVecTableWriteProtect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioDefDevGet", (char*) ioDefDevGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioDefDirGet", (char*) ioDefDirGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioDefPath", (char*) &ioDefPath, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ioDefPathCat", (char*) ioDefPathCat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioDefPathGet", (char*) ioDefPathGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioDefPathSet", (char*) ioDefPathSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioFullFileNameGet", (char*) ioFullFileNameGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioGlobalStdGet", (char*) ioGlobalStdGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioGlobalStdSet", (char*) ioGlobalStdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioHelp", (char*) ioHelp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioMaxLinkLevels", (char*) &ioMaxLinkLevels, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ioTaskStdGet", (char*) ioTaskStdGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ioTaskStdSet", (char*) ioTaskStdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "io_defs__", (char*) &io_defs__, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ioctl", (char*) ioctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosClose", (char*) iosClose, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosCreate", (char*) iosCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDelete", (char*) iosDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevAdd", (char*) iosDevAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevDelete", (char*) iosDevDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevFind", (char*) iosDevFind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDevShow", (char*) iosDevShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvInstall", (char*) iosDrvInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvRemove", (char*) iosDrvRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDrvShow", (char*) iosDrvShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosDvList", (char*) &iosDvList, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "iosFdDevFind", (char*) iosFdDevFind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdFree", (char*) iosFdFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdFreeHookRtn", (char*) &iosFdFreeHookRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "iosFdNew", (char*) iosFdNew, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdNewHookRtn", (char*) &iosFdNewHookRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "iosFdSet", (char*) iosFdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdShow", (char*) iosFdShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosFdValue", (char*) iosFdValue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosInit", (char*) iosInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosIoctl", (char*) iosIoctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosLibInitialized", (char*) &iosLibInitialized, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "iosNextDevGet", (char*) iosNextDevGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosOpen", (char*) iosOpen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosRead", (char*) iosRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosShowInit", (char*) iosShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iosWrite", (char*) iosWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipAttach", (char*) ipAttach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipCfgParams", (char*) &ipCfgParams, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipDetach", (char*) ipDetach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipDrvCtrl", (char*) &ipDrvCtrl, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipEtherResolvRtn", (char*) ipEtherResolvRtn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipHeaderCreate", (char*) ipHeaderCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipHeaderVerify", (char*) ipHeaderVerify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipLibInit", (char*) ipLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipMaxUnits", (char*) &ipMaxUnits, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipMuxCookieGet", (char*) ipMuxCookieGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipStrongEnded", (char*) &ipStrongEnded, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipTkError", (char*) ipTkError, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipToEtherMCastMap", (char*) ipToEtherMCastMap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_ctloutput", (char*) ip_ctloutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_defttl", (char*) &ip_defttl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ip_dooptions", (char*) ip_dooptions, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_drain", (char*) ip_drain, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_forward", (char*) ip_forward, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_freef", (char*) ip_freef, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_freemoptions", (char*) ip_freemoptions, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_getmoptions", (char*) ip_getmoptions, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_id", (char*) &ip_id, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ip_init", (char*) ip_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_mloopback", (char*) ip_mloopback, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_nhops", (char*) &ip_nhops, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ip_optcopy", (char*) ip_optcopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_output", (char*) ip_output, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_pcbopts", (char*) ip_pcbopts, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_protox", (char*) &ip_protox, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ip_rtaddr", (char*) ip_rtaddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_slowtimo", (char*) ip_slowtimo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ip_stripoptions", (char*) ip_stripoptions, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipforward_rt", (char*) &ipforward_rt, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipfragttl", (char*) &ipfragttl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipfx0__7istream", (char*) ipfx0__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipfx1__7istream", (char*) ipfx1__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipfx__7istreami", (char*) ipfx__7istreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipintr", (char*) ipintr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ipintrq", (char*) &ipintrq, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipq", (char*) &ipq, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipqmaxlen", (char*) &ipqmaxlen, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ipstat", (char*) &ipstat, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ipstatShow", (char*) ipstatShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iptime", (char*) iptime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "is_open__3ios", (char*) is_open__3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "is_open__C7filebuf", (char*) is_open__C7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "is_reading__7filebuf", (char*) is_reading__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isalnum", (char*) isalnum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isalpha", (char*) isalpha, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isatty", (char*) isatty, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "iscntrl", (char*) iscntrl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isdigit", (char*) isdigit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isfx__7istream", (char*) isfx__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isgraph", (char*) isgraph, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "islower", (char*) islower, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isprint", (char*) isprint, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ispunct", (char*) ispunct, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isspace", (char*) isspace, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "istreambuf__C7istream", (char*) istreambuf__C7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isupper", (char*) isupper, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "isxdigit", (char*) isxdigit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ixdr_get_long", (char*) ixdr_get_long, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelInit", (char*) kernelInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelIsIdle", (char*) &kernelIsIdle, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "kernelState", (char*) &kernelState, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "kernelTimeSlice", (char*) kernelTimeSlice, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kernelVersion", (char*) kernelVersion, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "kill", (char*) kill, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ksleep", (char*) ksleep, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "l", (char*) l, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "labs", (char*) labs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ld", (char*) ld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ldCommonMatchAll", (char*) &ldCommonMatchAll, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "ldexp", (char*) ldexp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ldiv", (char*) ldiv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ldiv_r", (char*) ldiv_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledClose", (char*) ledClose, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledControl", (char*) ledControl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledId", (char*) &ledId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ledOpen", (char*) ledOpen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ledRead", (char*) ledRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lexActions", (char*) lexActions, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lexClass", (char*) &lexClass, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "lexNclasses", (char*) &lexNclasses, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "lexStateTable", (char*) &lexStateTable, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "libiberty_demanglers", (char*) &libiberty_demanglers, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "linebuffered__9streambuf", (char*) linebuffered__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "linebuffered__9streambufi", (char*) linebuffered__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "linkDataSyms", (char*) &linkDataSyms, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "linkSyms", (char*) &linkSyms, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "link_rtrequest", (char*) link_rtrequest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "linkedCtorsInitialized", (char*) &linkedCtorsInitialized, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "listen", (char*) listen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lkAddr", (char*) lkAddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lkup", (char*) lkup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ll", (char*) ll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "llinfo_arp", (char*) &llinfo_arp, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "llr", (char*) llr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadCommonManage", (char*) loadCommonManage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadCommonMatch", (char*) loadCommonMatch, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadElfInit", (char*) loadElfInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModule", (char*) loadModule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleAt", (char*) loadModuleAt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleAtSym", (char*) loadModuleAtSym, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadModuleGet", (char*) loadModuleGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loadRoutine", (char*) &loadRoutine, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "loadSegmentsAllocate", (char*) loadSegmentsAllocate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "load_fpga_ALTERA", (char*) load_fpga_ALTERA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "load_fpga_LATTICE", (char*) load_fpga_LATTICE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loattach", (char*) loattach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "localToGlobalOffset", (char*) &localToGlobalOffset, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "localeconv", (char*) localeconv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "localtime", (char*) localtime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "localtime_r", (char*) localtime_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lock__FR7istream", (char*) lock__FR7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lock__FR7ostream", (char*) lock__FR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "log", (char*) log, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "log10", (char*) log10, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logFdAdd", (char*) logFdAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logFdDelete", (char*) logFdDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logFdFromRlogin", (char*) &logFdFromRlogin, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logFdSet", (char*) logFdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logInit", (char*) logInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logMsg", (char*) logMsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logShow", (char*) logShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logTask", (char*) logTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "logTaskId", (char*) &logTaskId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logTaskOptions", (char*) &logTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logTaskPriority", (char*) &logTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "logTaskStackSize", (char*) &logTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "loginDefaultEncrypt", (char*) loginDefaultEncrypt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginEncryptInstall", (char*) loginEncryptInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginInit", (char*) loginInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginPrompt", (char*) loginPrompt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginStringSet", (char*) loginStringSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginTimeOutInSecond", (char*) &loginTimeOutInSecond, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "loginUserAdd", (char*) loginUserAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginUserDelete", (char*) loginUserDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginUserShow", (char*) loginUserShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginUserVerify", (char*) loginUserVerify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loginVerifyRtn", (char*) &loginVerifyRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "logout", (char*) logout, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "loif", (char*) &loif, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "longjmp", (char*) longjmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "looutput", (char*) looutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ls", (char*) ls, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lseek", (char*) lseek, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lsr", (char*) lsr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstAdd", (char*) lstAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstConcat", (char*) lstConcat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstCount", (char*) lstCount, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstDelete", (char*) lstDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstExtract", (char*) lstExtract, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstFind", (char*) lstFind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstFirst", (char*) lstFirst, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstFree", (char*) lstFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstGet", (char*) lstGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstInit", (char*) lstInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstInsert", (char*) lstInsert, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstLast", (char*) lstLast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstLibInit", (char*) lstLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstNStep", (char*) lstNStep, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstNext", (char*) lstNext, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstNth", (char*) lstNth, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "lstPrevious", (char*) lstPrevious, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m", (char*) m, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mBufClGet", (char*) mBufClGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mCastHashInfo", (char*) &mCastHashInfo, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mCastHashTblSize", (char*) &mCastHashTblSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mClBlkConfig", (char*) &mClBlkConfig, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mHdrClGet", (char*) mHdrClGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mPrivRouteEntryAdd", (char*) mPrivRouteEntryAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mPrivRouteEntryDelete", (char*) mPrivRouteEntryDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mRegs", (char*) mRegs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mRouteAdd", (char*) mRouteAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mRouteDelete", (char*) mRouteDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mRouteEntryAdd", (char*) mRouteEntryAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mRouteEntryDelete", (char*) mRouteEntryDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mRouteShow", (char*) mRouteShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m_adj", (char*) m_adj, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m_cat", (char*) m_cat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m_devget", (char*) m_devget, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m_getclr", (char*) m_getclr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m_prepend", (char*) m_prepend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "m_pullup", (char*) m_pullup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "malloc", (char*) malloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mask_rnhead", (char*) &mask_rnhead, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mathSoftInit", (char*) mathSoftInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "maxDrivers", (char*) &maxDrivers, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "maxFiles", (char*) &maxFiles, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_hdr", (char*) &max_hdr, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_keylen", (char*) &max_keylen, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_linkhdr", (char*) &max_linkhdr, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_protohdr", (char*) &max_protohdr, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mbinit", (char*) mbinit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mblen", (char*) mblen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mbstowcs", (char*) mbstowcs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mbtowc", (char*) mbtowc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mbufShow", (char*) mbufShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mcastHashInit", (char*) mcastHashInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mcastHashTblDelete", (char*) mcastHashTblDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mcastHashTblInsert", (char*) mcastHashTblInsert, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mcastHashTblLookup", (char*) mcastHashTblLookup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memAddToPool", (char*) memAddToPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memDefaultAlignment", (char*) &memDefaultAlignment, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memFindMax", (char*) memFindMax, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memInit", (char*) memInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memLibInit", (char*) memLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memOptionsSet", (char*) memOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartAddToPool", (char*) memPartAddToPool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartAlignedAlloc", (char*) memPartAlignedAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartAlloc", (char*) memPartAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartAllocErrorRtn", (char*) &memPartAllocErrorRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartBlockErrorRtn", (char*) &memPartBlockErrorRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartBlockIsValid", (char*) memPartBlockIsValid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartClassId", (char*) &memPartClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartCreate", (char*) memPartCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartFindMax", (char*) memPartFindMax, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartFree", (char*) memPartFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartInfoGet", (char*) memPartInfoGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartInit", (char*) memPartInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartInstClassId", (char*) &memPartInstClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartLibInit", (char*) memPartLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartOptionsDefault", (char*) &memPartOptionsDefault, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartOptionsSet", (char*) memPartOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartRealloc", (char*) memPartRealloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memPartSemInitRtn", (char*) &memPartSemInitRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memPartShow", (char*) memPartShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memShow", (char*) memShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memShowInit", (char*) memShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memSysPartId", (char*) &memSysPartId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "memTest", (char*) memTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memalign", (char*) memalign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memchr", (char*) memchr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memcmp", (char*) memcmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memcpy", (char*) memcpy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memdebug", (char*) memdebug, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memmove", (char*) memmove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memset", (char*) memset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memshow", (char*) memshow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mib2ErrorAdd", (char*) mib2ErrorAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mib2Init", (char*) mib2Init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mkdir", (char*) mkdir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mktime", (char*) mktime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmtest", (char*) mmtest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuArm920tADisable", (char*) mmuArm920tADisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuArm920tAEnable", (char*) mmuArm920tAEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuArm920tDacrSet", (char*) mmuArm920tDacrSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuArm920tLibInstall", (char*) mmuArm920tLibInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuArm920tTLBIDFlushAll", (char*) mmuArm920tTLBIDFlushAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuArm920tTLBIDFlushEntry", (char*) mmuArm920tTLBIDFlushEntry, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuArm920tTtbrSet", (char*) mmuArm920tTtbrSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuCrGet", (char*) &mmuCrGet, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mmuHardCrGet", (char*) mmuHardCrGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuLibFuncs", (char*) &mmuLibFuncs, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuModifyCr", (char*) &mmuModifyCr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mmuModifyHardCr", (char*) mmuModifyHardCr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuModifySoftCr", (char*) mmuModifySoftCr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuPageBlockSize", (char*) &mmuPageBlockSize, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuPhysAddrShift", (char*) &mmuPhysAddrShift, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mmuReadId", (char*) mmuReadId, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuSoftCrGet", (char*) mmuSoftCrGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mmuStateTransArray", (char*) &mmuStateTransArray, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mmuStateTransArraySize", (char*) &mmuStateTransArraySize, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "modf", (char*) modf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleCheck", (char*) moduleCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleClassId", (char*) &moduleClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "moduleCreate", (char*) moduleCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleCreateHookAdd", (char*) moduleCreateHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleCreateHookDelete", (char*) moduleCreateHookDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleDelete", (char*) moduleDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleEach", (char*) moduleEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFindByGroup", (char*) moduleFindByGroup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFindByName", (char*) moduleFindByName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFindByNameAndPath", (char*) moduleFindByNameAndPath, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleFlagsGet", (char*) moduleFlagsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleIdFigure", (char*) moduleIdFigure, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleIdListGet", (char*) moduleIdListGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleInfoGet", (char*) moduleInfoGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleInit", (char*) moduleInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleLibInit", (char*) moduleLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleNameGet", (char*) moduleNameGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegAdd", (char*) moduleSegAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegEach", (char*) moduleSegEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegFirst", (char*) moduleSegFirst, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegGet", (char*) moduleSegGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleSegNext", (char*) moduleSegNext, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleShow", (char*) moduleShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moduleTerminate", (char*) moduleTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mountFTL", (char*) mountFTL, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQClassId", (char*) &msgQClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "msgQCreate", (char*) msgQCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQDelete", (char*) msgQDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQDistInfoGetRtn", (char*) &msgQDistInfoGetRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQDistNumMsgsRtn", (char*) &msgQDistNumMsgsRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQDistReceiveRtn", (char*) &msgQDistReceiveRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQDistSendRtn", (char*) &msgQDistSendRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQDistShowRtn", (char*) &msgQDistShowRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQEvLibInit", (char*) msgQEvLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQEvStart", (char*) msgQEvStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQEvStop", (char*) msgQEvStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQInfoGet", (char*) msgQInfoGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQInit", (char*) msgQInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQInstClassId", (char*) &msgQInstClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "msgQLibInit", (char*) msgQLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQNumMsgs", (char*) msgQNumMsgs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQReceive", (char*) msgQReceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQSend", (char*) msgQSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQShow", (char*) msgQShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQShowInit", (char*) msgQShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "msgQSmInfoGetRtn", (char*) &msgQSmInfoGetRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQSmNumMsgsRtn", (char*) &msgQSmNumMsgsRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQSmReceiveRtn", (char*) &msgQSmReceiveRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQSmSendRtn", (char*) &msgQSmSendRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQSmShowRtn", (char*) &msgQSmShowRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "msgQTerminate", (char*) msgQTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mtdTable", (char*) &mtdTable, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsHostLib", (char*) &mutexOptionsHostLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsIosLib", (char*) &mutexOptionsIosLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsLogLib", (char*) &mutexOptionsLogLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsMemLib", (char*) &mutexOptionsMemLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsNetDrv", (char*) &mutexOptionsNetDrv, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsSelectLib", (char*) &mutexOptionsSelectLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsSymLib", (char*) &mutexOptionsSymLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsTyLib", (char*) &mutexOptionsTyLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsUnixLib", (char*) &mutexOptionsUnixLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "mutexOptionsVmBaseLib", (char*) &mutexOptionsVmBaseLib, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "muxAddrResFuncAdd", (char*) muxAddrResFuncAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxAddrResFuncDel", (char*) muxAddrResFuncDel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxAddrResFuncGet", (char*) muxAddrResFuncGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxAddressForm", (char*) muxAddressForm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxBibLock", (char*) &muxBibLock, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "muxBind", (char*) muxBind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevExists", (char*) muxDevExists, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevLoad", (char*) muxDevLoad, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevStart", (char*) muxDevStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevStartAll", (char*) muxDevStartAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevStop", (char*) muxDevStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevStopAll", (char*) muxDevStopAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxDevUnload", (char*) muxDevUnload, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxError", (char*) muxError, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxIoctl", (char*) muxIoctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxLibInit", (char*) muxLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxLinkHeaderCreate", (char*) muxLinkHeaderCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMCastAddrAdd", (char*) muxMCastAddrAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMCastAddrDel", (char*) muxMCastAddrDel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMCastAddrGet", (char*) muxMCastAddrGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxMaxBinds", (char*) &muxMaxBinds, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "muxPacketAddrGet", (char*) muxPacketAddrGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPacketDataGet", (char*) muxPacketDataGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollDevAdd", (char*) muxPollDevAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollDevDel", (char*) muxPollDevDel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollDevStat", (char*) muxPollDevStat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollEnd", (char*) muxPollEnd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollReceive", (char*) muxPollReceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollSend", (char*) muxPollSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollStart", (char*) muxPollStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxPollTask", (char*) muxPollTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxReceive", (char*) muxReceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxSend", (char*) muxSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxShow", (char*) muxShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTaskDelayGet", (char*) muxTaskDelayGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTaskDelaySet", (char*) muxTaskDelaySet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTaskPriorityGet", (char*) muxTaskPriorityGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTaskPrioritySet", (char*) muxTaskPrioritySet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkBibInit", (char*) muxTkBibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkBibShow", (char*) muxTkBibShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkBind", (char*) muxTkBind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkBindUpdate", (char*) muxTkBindUpdate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkCookieGet", (char*) muxTkCookieGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkDebug", (char*) &muxTkDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "muxTkDevLoadUpdate", (char*) muxTkDevLoadUpdate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkDrvCheck", (char*) muxTkDrvCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkPollReceive", (char*) muxTkPollReceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkPollReceive2", (char*) muxTkPollReceive2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkPollSend", (char*) muxTkPollSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkReceive", (char*) muxTkReceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkSend", (char*) muxTkSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkUnbindUpdate", (char*) muxTkUnbindUpdate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTkUnloadUpdate", (char*) muxTkUnloadUpdate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxTxRestart", (char*) muxTxRestart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "muxUnbind", (char*) muxUnbind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mv", (char*) mv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "name__C9type_info", (char*) name__C9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "namelessPrefix", (char*) &namelessPrefix, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netBufLibInit", (char*) netBufLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClBlkFree", (char*) netClBlkFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClBlkGet", (char*) netClBlkGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClBlkJoin", (char*) netClBlkJoin, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClFree", (char*) netClFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClPoolIdGet", (char*) netClPoolIdGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netClusterGet", (char*) netClusterGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDevCreate", (char*) netDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDevCreate2", (char*) netDevCreate2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDrv", (char*) netDrv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDrvDebugLevelSet", (char*) netDrvDebugLevelSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDrvFileDoesNotExist", (char*) netDrvFileDoesNotExist, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netDrvFileDoesNotExistInstall", (char*) netDrvFileDoesNotExistInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netErrnoSet", (char*) netErrnoSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netHelp", (char*) netHelp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netJobAdd", (char*) netJobAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netLibGeneralInit", (char*) netLibGeneralInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netLibInit", (char*) netLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netLibInitialized", (char*) &netLibInitialized, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netLsByName", (char*) netLsByName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkChainDup", (char*) netMblkChainDup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkClChainFree", (char*) netMblkClChainFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkClFree", (char*) netMblkClFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkClGet", (char*) netMblkClGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkClJoin", (char*) netMblkClJoin, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkDup", (char*) netMblkDup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkFree", (char*) netMblkFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkGet", (char*) netMblkGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkOffsetToBufCopy", (char*) netMblkOffsetToBufCopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netMblkToBufCopy", (char*) netMblkToBufCopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolDelete", (char*) netPoolDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolInit", (char*) netPoolInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolKheapInit", (char*) netPoolKheapInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netPoolShow", (char*) netPoolShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netShowInit", (char*) netShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netStackDataPoolShow", (char*) netStackDataPoolShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netStackSysPoolShow", (char*) netStackSysPoolShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netTask", (char*) netTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netTaskId", (char*) &netTaskId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "netTaskOptions", (char*) &netTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netTaskPriority", (char*) &netTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netTaskSemId", (char*) &netTaskSemId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netTaskStackSize", (char*) &netTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "netTupleGet", (char*) netTupleGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netTupleGet2", (char*) netTupleGet2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netTypeAdd", (char*) netTypeAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netTypeDelete", (char*) netTypeDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "netTypeInit", (char*) netTypeInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "net_sysctl", (char*) net_sysctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "noOfDrives", (char*) &noOfDrives, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "noOfMTDs", (char*) &noOfMTDs, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "noOfTLs", (char*) &noOfTLs, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "nothrow", (char*) nothrow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objAlloc", (char*) objAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objAllocExtra", (char*) objAllocExtra, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objCoreInit", (char*) objCoreInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objCoreTerminate", (char*) objCoreTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objFree", (char*) objFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "objShow", (char*) objShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "oct__FR3ios", (char*) oct__FR3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "open", (char*) open, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "open__7filebufPCcT1", (char*) open__7filebufPCcT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "open__7filebufPCcii", (char*) open__7filebufPCcii, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "opendir", (char*) opendir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "opfx__7ostream", (char*) opfx__7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "osfx__7ostream", (char*) osfx__7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ostreambuf__C7ostream", (char*) ostreambuf__C7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "out_waiting__9streambuf", (char*) out_waiting__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "overflow__7filebufi", (char*) overflow__7filebufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "overflow__9streambufi", (char*) overflow__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pEndPktDev", (char*) &pEndPktDev, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pFppTaskIdPrevious", (char*) &pFppTaskIdPrevious, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pInPkt", (char*) &pInPkt, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pJobPool", (char*) &pJobPool, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pMibRtn", (char*) &pMibRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pRootMemStart", (char*) &pRootMemStart, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pSockFdMap", (char*) &pSockFdMap, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pTaskLastDspTcb", (char*) &pTaskLastDspTcb, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pTaskLastFpTcb", (char*) &pTaskLastFpTcb, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pTcpRandHook", (char*) &pTcpRandHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pTcpstates", (char*) &pTcpstates, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pWdbMemRegions", (char*) &pWdbMemRegions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pWdbRtIf", (char*) &pWdbRtIf, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pWvNetEventMap", (char*) &pWvNetEventMap, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "padn__9streambufci", (char*) padn__9streambufci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "panic", (char*) panic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "panicSuspend", (char*) &panicSuspend, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pathBuild", (char*) pathBuild, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathCat", (char*) pathCat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathCondense", (char*) pathCondense, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathLastName", (char*) pathLastName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathLastNamePtr", (char*) pathLastNamePtr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathParse", (char*) pathParse, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pathSplit", (char*) pathSplit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pause", (char*) pause, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pbackfail__9streambufi", (char*) pbackfail__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pbase__C9streambuf", (char*) pbase__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pbump__9streambufi", (char*) pbump__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pc", (char*) pc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "peek__7istream", (char*) peek__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "period", (char*) period, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "periodRun", (char*) periodRun, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "perror", (char*) perror, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pfctlinput", (char*) pfctlinput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pffindproto", (char*) pffindproto, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pffindtype", (char*) pffindtype, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ping", (char*) ping, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pingLibInit", (char*) pingLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pipeDevCreate", (char*) pipeDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pipeDevDelete", (char*) pipeDevDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pipeDrv", (char*) pipeDrv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pipeMsgQOptions", (char*) &pipeMsgQOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "pow", (char*) pow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ppGlobalEnviron", (char*) &ppGlobalEnviron, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "pptr__C9streambuf", (char*) pptr__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "precision__3iosi", (char*) precision__3iosi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "precision__C3ios", (char*) precision__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "print64", (char*) print64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "print64Fine", (char*) print64Fine, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "print64Mult", (char*) print64Mult, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "print64Row", (char*) print64Row, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printErr", (char*) printErr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printErrno", (char*) printErrno, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printExc", (char*) printExc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printLogo", (char*) printLogo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "printf", (char*) printf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "proxyArpHook", (char*) &proxyArpHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "proxyBroadcastHook", (char*) &proxyBroadcastHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "psrShow", (char*) psrShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ptyDevCreate", (char*) ptyDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ptyDevRemove", (char*) ptyDevRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ptyDrv", (char*) ptyDrv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pubseekoff__9streambuflQ23ios8seek_diri", (char*) pubseekoff__9streambuflQ23ios8seek_diri, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pubseekpos__9streambufli", (char*) pubseekpos__9streambufli, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "put__7ostreamSc", (char*) put__7ostreamSc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "put__7ostreamUc", (char*) put__7ostreamUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "put__7ostreamc", (char*) put__7ostreamc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "put_mode__9streambuf", (char*) put_mode__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putback__7istreamc", (char*) putback__7istreamc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putc", (char*) putc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putchar", (char*) putchar, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putenv", (char*) putenv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "puts", (char*) puts, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "putw", (char*) putw, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pwd", (char*) pwd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qAdvance", (char*) qAdvance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qCalibrate", (char*) qCalibrate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qCreate", (char*) qCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qDelete", (char*) qDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qEach", (char*) qEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoClassId", (char*) &qFifoClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qFifoCreate", (char*) qFifoCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoDelete", (char*) qFifoDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoEach", (char*) qFifoEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoGet", (char*) qFifoGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoInfo", (char*) qFifoInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoInit", (char*) qFifoInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoPut", (char*) qFifoPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFifoRemove", (char*) qFifoRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qFirst", (char*) qFirst, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qGet", (char*) qGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qGetExpired", (char*) qGetExpired, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qInfo", (char*) qInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qInit", (char*) qInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qJobClassId", (char*) &qJobClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qJobCreate", (char*) qJobCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qJobDelete", (char*) qJobDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qJobEach", (char*) qJobEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qJobGet", (char*) qJobGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qJobInfo", (char*) qJobInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qJobInit", (char*) qJobInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qJobPut", (char*) qJobPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qJobTerminate", (char*) qJobTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qKey", (char*) qKey, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapClassId", (char*) &qPriBMapClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qPriBMapCreate", (char*) qPriBMapCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapDelete", (char*) qPriBMapDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapEach", (char*) qPriBMapEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapGet", (char*) qPriBMapGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapInfo", (char*) qPriBMapInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapInit", (char*) qPriBMapInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapKey", (char*) qPriBMapKey, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapListCreate", (char*) qPriBMapListCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapListDelete", (char*) qPriBMapListDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapPut", (char*) qPriBMapPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapRemove", (char*) qPriBMapRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriBMapResort", (char*) qPriBMapResort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListAdvance", (char*) qPriListAdvance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListCalibrate", (char*) qPriListCalibrate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListClassId", (char*) &qPriListClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qPriListCreate", (char*) qPriListCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListDelete", (char*) qPriListDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListEach", (char*) qPriListEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListFromTailClassId", (char*) &qPriListFromTailClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "qPriListGet", (char*) qPriListGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListGetExpired", (char*) qPriListGetExpired, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListInfo", (char*) qPriListInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListInit", (char*) qPriListInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListKey", (char*) qPriListKey, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListPut", (char*) qPriListPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListPutFromTail", (char*) qPriListPutFromTail, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListRemove", (char*) qPriListRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListResort", (char*) qPriListResort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPriListTerminate", (char*) qPriListTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qPut", (char*) qPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qRemove", (char*) qRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qResort", (char*) qResort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qTerminate", (char*) qTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "qsort", (char*) qsort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r0", (char*) r0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r1", (char*) r1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r10", (char*) r10, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r11", (char*) r11, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r12", (char*) r12, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r13", (char*) r13, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r14", (char*) r14, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r2", (char*) r2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r3", (char*) r3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r4", (char*) r4, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r5", (char*) r5, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r6", (char*) r6, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r7", (char*) r7, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r8", (char*) r8, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "r9", (char*) r9, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "raise", (char*) raise, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ramDevCreate", (char*) ramDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ramDrv", (char*) ramDrv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rand", (char*) rand, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "random", (char*) random, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rawIpLibInit", (char*) rawIpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rawLibInit", (char*) rawLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rcmd", (char*) rcmd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rdbuf__3iosP9streambuf", (char*) rdbuf__3iosP9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rdbuf__C3ios", (char*) rdbuf__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rdstate__C3ios", (char*) rdstate__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read", (char*) read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read__7istreamPSci", (char*) read__7istreamPSci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read__7istreamPUci", (char*) read__7istreamPUci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read__7istreamPci", (char*) read__7istreamPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read__7istreamPvi", (char*) read__7istreamPvi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readable__3ios", (char*) readable__3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readdir", (char*) readdir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readv", (char*) readv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readyQBMap", (char*) &readyQBMap, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "readyQHead", (char*) &readyQHead, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "realloc", (char*) realloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reallocate__t23__malloc_alloc_template1i0PvUlUl", (char*) reallocate__t23__malloc_alloc_template1i0PvUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reallocate__t24__default_alloc_template2b1i0PvUlUl", (char*) reallocate__t24__default_alloc_template2b1i0PvUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reboot", (char*) reboot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rebootHookAdd", (char*) rebootHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "recv", (char*) recv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "recvfrom", (char*) recvfrom, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "recvmsg", (char*) recvmsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "redirInFd", (char*) &redirInFd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "redirOutFd", (char*) &redirOutFd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "remCurIdGet", (char*) remCurIdGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remCurIdSet", (char*) remCurIdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remLastResvPort", (char*) &remLastResvPort, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "remLibInit", (char*) remLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remStdErrSetupTimeout", (char*) &remStdErrSetupTimeout, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "remove", (char*) remove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rename", (char*) rename, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "repeat", (char*) repeat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "repeatRun", (char*) repeatRun, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replaceFATsector", (char*) replaceFATsector, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reschedule", (char*) reschedule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "resetflash", (char*) resetflash, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "restart485test", (char*) restart485test, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "restartTaskName", (char*) &restartTaskName, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskOptions", (char*) &restartTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskPriority", (char*) &restartTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskStackSize", (char*) &restartTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rewind", (char*) rewind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rewinddir", (char*) rewinddir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rindex", (char*) rindex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rip_ctloutput", (char*) rip_ctloutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rip_init", (char*) rip_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rip_input", (char*) rip_input, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rip_output", (char*) rip_output, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rip_recvspace", (char*) &rip_recvspace, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rip_sendspace", (char*) &rip_sendspace, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rip_usrreq", (char*) rip_usrreq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rm", (char*) rm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rmdir", (char*) rmdir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_addmask", (char*) rn_addmask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_addroute", (char*) rn_addroute, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_delete", (char*) rn_delete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_destroyhead", (char*) rn_destroyhead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_init", (char*) rn_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_inithead", (char*) rn_inithead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_insert", (char*) rn_insert, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_lookup", (char*) rn_lookup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_match", (char*) rn_match, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_mkfreelist", (char*) &rn_mkfreelist, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "rn_newpair", (char*) rn_newpair, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_refines", (char*) rn_refines, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_search", (char*) rn_search, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_search_m", (char*) rn_search_m, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_walksubtree", (char*) rn_walksubtree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rn_walktree", (char*) rn_walktree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngBufGet", (char*) rngBufGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngBufPut", (char*) rngBufPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngCreate", (char*) rngCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngDelete", (char*) rngDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngFlush", (char*) rngFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngFreeBytes", (char*) rngFreeBytes, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngIsEmpty", (char*) rngIsEmpty, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngIsFull", (char*) rngIsFull, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngMoveAhead", (char*) rngMoveAhead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngNBytes", (char*) rngNBytes, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rngPutAhead", (char*) rngPutAhead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rootMemNBytes", (char*) &rootMemNBytes, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "rootTaskId", (char*) &rootTaskId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "roundRobinOn", (char*) &roundRobinOn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "roundRobinSlice", (char*) &roundRobinSlice, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "routeAdd", (char*) routeAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeAgeSet", (char*) routeAgeSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeCmd", (char*) routeCmd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeDelete", (char*) routeDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeDrain", (char*) routeDrain, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeEntryFill", (char*) routeEntryFill, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeMetricSet", (char*) routeMetricSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeNetAdd", (char*) routeNetAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeShow", (char*) routeShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routeSwap", (char*) routeSwap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "route_init", (char*) route_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "routestatShow", (char*) routestatShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rresvport", (char*) rresvport, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtIfaceMsgHook", (char*) &rtIfaceMsgHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rtMem", (char*) rtMem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtMissMsgHook", (char*) &rtMissMsgHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rtNewAddrMsgHook", (char*) &rtNewAddrMsgHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rt_fixdelete", (char*) rt_fixdelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rt_maskedcopy", (char*) rt_maskedcopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rt_setgate", (char*) rt_setgate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rt_tables", (char*) &rt_tables, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "rtable_init", (char*) rtable_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtalloc", (char*) rtalloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtalloc1", (char*) rtalloc1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtalloc2", (char*) rtalloc2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtfree", (char*) rtfree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtinit", (char*) rtinit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtioctl", (char*) rtioctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtmodified", (char*) &rtmodified, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "rtredirect", (char*) rtredirect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtrequest", (char*) rtrequest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtrequestAddEqui", (char*) rtrequestAddEqui, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtrequestDelEqui", (char*) rtrequestDelEqui, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rtstat", (char*) &rtstat, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "rttrash", (char*) &rttrash, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "runtimeName", (char*) &runtimeName, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "runtimeVersion", (char*) &runtimeVersion, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "s", (char*) s, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sCurI2cPort", (char*) &sCurI2cPort, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "saving__12streammarker", (char*) saving__12streammarker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sb_lock", (char*) sb_lock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sb_max", (char*) &sb_max, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sbappend", (char*) sbappend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbappendaddr", (char*) sbappendaddr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbappendcontrol", (char*) sbappendcontrol, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbappendrecord", (char*) sbappendrecord, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbcompress", (char*) sbcompress, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbdrop", (char*) sbdrop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbdroprecord", (char*) sbdroprecord, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbflush", (char*) sbflush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbinsertoob", (char*) sbinsertoob, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbrelease", (char*) sbrelease, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbreserve", (char*) sbreserve, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbseldequeue", (char*) sbseldequeue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbselqueue", (char*) sbselqueue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbumpc__9streambuf", (char*) sbumpc__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbwait", (char*) sbwait, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sbwakeup", (char*) sbwakeup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scalbn", (char*) scalbn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scanCharSet", (char*) scanCharSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scanField", (char*) scanField, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scan__7istreamPCce", (char*) scan__7istreamPCce, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scan__9streambufPCce", (char*) scan__9streambufPCce, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "scanf", (char*) scanf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "secEndLoad", (char*) secEndLoad, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "seekg__7istreaml", (char*) seekg__7istreaml, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "seekg__7istreamlQ23ios8seek_dir", (char*) seekg__7istreamlQ23ios8seek_dir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "seekmark__9streambufR12streammarkeri", (char*) seekmark__9streambufR12streammarkeri, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "seekoff__7filebuflQ23ios8seek_diri", (char*) seekoff__7filebuflQ23ios8seek_diri, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "seekoff__9streambuflQ23ios8seek_diri", (char*) seekoff__9streambuflQ23ios8seek_diri, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "seekp__7ostreaml", (char*) seekp__7ostreaml, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "seekp__7ostreamlQ23ios8seek_dir", (char*) seekp__7ostreamlQ23ios8seek_dir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "seekpos__9streambufli", (char*) seekpos__9streambufli, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selNodeAdd", (char*) selNodeAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selNodeDelete", (char*) selNodeDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selTaskDeleteHookAdd", (char*) selTaskDeleteHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeup", (char*) selWakeup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupAll", (char*) selWakeupAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupListInit", (char*) selWakeupListInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupListLen", (char*) selWakeupListLen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupListTerm", (char*) selWakeupListTerm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selWakeupType", (char*) selWakeupType, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "select", (char*) select, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selectInit", (char*) selectInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBCoreInit", (char*) semBCoreInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBCreate", (char*) semBCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBGive", (char*) semBGive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBGiveDefer", (char*) semBGiveDefer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBInit", (char*) semBInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBLibInit", (char*) semBLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semBTake", (char*) semBTake, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCCoreInit", (char*) semCCoreInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCCreate", (char*) semCCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCGive", (char*) semCGive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCGiveDefer", (char*) semCGiveDefer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCInit", (char*) semCInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCLibInit", (char*) semCLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semCTake", (char*) semCTake, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semClass", (char*) &semClass, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "semClassId", (char*) &semClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semClear", (char*) semClear, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semDelete", (char*) semDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semDestroy", (char*) semDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semEvIsFreeTbl", (char*) &semEvIsFreeTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semEvLibInit", (char*) semEvLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semEvRsrcSend", (char*) semEvRsrcSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semEvStart", (char*) semEvStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semEvStop", (char*) semEvStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semFlush", (char*) semFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semFlushDefer", (char*) semFlushDefer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semFlushDeferTbl", (char*) &semFlushDeferTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semFlushTbl", (char*) &semFlushTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semGive", (char*) semGive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semGiveDefer", (char*) semGiveDefer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semGiveDeferTbl", (char*) &semGiveDeferTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semGiveTbl", (char*) &semGiveTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semI2cLock", (char*) &semI2cLock, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semInfo", (char*) semInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semInstClass", (char*) &semInstClass, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "semInstClassId", (char*) &semInstClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semIntRestrict", (char*) semIntRestrict, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semInvalid", (char*) semInvalid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semLibInit", (char*) semLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMCoreInit", (char*) semMCoreInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMCreate", (char*) semMCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGive", (char*) semMGive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGiveForce", (char*) semMGiveForce, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGiveKern", (char*) semMGiveKern, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMGiveKernWork", (char*) &semMGiveKernWork, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "semMInit", (char*) semMInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMLibInit", (char*) semMLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMPendQPut", (char*) semMPendQPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semMTake", (char*) semMTake, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semOTake", (char*) semOTake, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semQFlush", (char*) semQFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semQFlushDefer", (char*) semQFlushDefer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semQGet", (char*) semQGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semQInit", (char*) semQInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semQPut", (char*) semQPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semShow", (char*) semShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semShowInit", (char*) semShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semSmInfoRtn", (char*) &semSmInfoRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "semSmShowRtn", (char*) &semSmShowRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "semSpiLock", (char*) &semSpiLock, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semTake", (char*) semTake, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semTakeTbl", (char*) &semTakeTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "semTerminate", (char*) semTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "semVoltage", (char*) &semVoltage, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "send", (char*) send, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sendmsg", (char*) sendmsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sendpackage", (char*) sendpackage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sendto", (char*) sendto, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set__3iosi", (char*) set__3iosi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set_column__9streambufi", (char*) set_column__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set_cplus_marker_for_demangling", (char*) set_cplus_marker_for_demangling, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set_if_addr", (char*) set_if_addr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set_new_handler__FPFv_v", (char*) set_new_handler__FPFv_v, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set_offset__12streammarkeri", (char*) set_offset__12streammarkeri, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set_terminate__FPFv_v", (char*) set_terminate__FPFv_v, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set_unexpected__FPFv_v", (char*) set_unexpected__FPFv_v, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setb__9streambufPcT1i", (char*) setb__9streambufPcT1i, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setbuf", (char*) setbuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setbuf__7filebufPci", (char*) setbuf__7filebufPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setbuf__9streambufPci", (char*) setbuf__9streambufPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setbuffer", (char*) setbuffer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setf__3iosUl", (char*) setf__3iosUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setf__3iosUlUl", (char*) setf__3iosUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setg__9streambufPcN21", (char*) setg__9streambufPcN21, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sethostname", (char*) sethostname, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setjmp", (char*) setjmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setlinebuf", (char*) setlinebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setlocale", (char*) setlocale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setp__9streambufPcT1", (char*) setp__9streambufPcT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setsockopt", (char*) setsockopt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setstate", (char*) setstate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setstate__3iosi", (char*) setstate__3iosi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setvbuf", (char*) setvbuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sfpDoubleNormalize", (char*) sfpDoubleNormalize, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sfpDoubleNormalize2", (char*) sfpDoubleNormalize2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sfpDoubleSetup", (char*) sfpDoubleSetup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sfpFloatNormalize", (char*) sfpFloatNormalize, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sfpFloatSetup", (char*) sfpFloatSetup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sgetc__9streambuf", (char*) sgetc__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sgetn__9streambufPci", (char*) sgetn__9streambufPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shell", (char*) shell, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellHistSize", (char*) &shellHistSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shellHistory", (char*) shellHistory, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellInit", (char*) shellInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellIsRemoteConnectedGet", (char*) shellIsRemoteConnectedGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellIsRemoteConnectedSet", (char*) shellIsRemoteConnectedSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLock", (char*) shellLock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLogin", (char*) shellLogin, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLoginInstall", (char*) shellLoginInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLogout", (char*) shellLogout, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellLogoutInstall", (char*) shellLogoutInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellOrigStdSet", (char*) shellOrigStdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellParserControl", (char*) shellParserControl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellPromptSet", (char*) shellPromptSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellRestart", (char*) shellRestart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellScriptAbort", (char*) shellScriptAbort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shellTaskId", (char*) &shellTaskId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "shellTaskName", (char*) &shellTaskName, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shellTaskOptions", (char*) &shellTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shellTaskPriority", (char*) &shellTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shellTaskStackSize", (char*) &shellTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "shortbuf__9streambuf", (char*) shortbuf__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "show", (char*) show, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "shutdown", (char*) shutdown, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigEvtRtn", (char*) &sigEvtRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sigInit", (char*) sigInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigPendDestroy", (char*) sigPendDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigPendInit", (char*) sigPendInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigPendKill", (char*) sigPendKill, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigaction", (char*) sigaction, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigaddset", (char*) sigaddset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigblock", (char*) sigblock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigdelset", (char*) sigdelset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigemptyset", (char*) sigemptyset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigfillset", (char*) sigfillset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigismember", (char*) sigismember, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "signal", (char*) signal, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigpending", (char*) sigpending, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigprocmask", (char*) sigprocmask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigqueue", (char*) sigqueue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigqueueInit", (char*) sigqueueInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigreturn", (char*) sigreturn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigsetjmp", (char*) sigsetjmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigsetmask", (char*) sigsetmask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigsuspend", (char*) sigsuspend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigtimedwait", (char*) sigtimedwait, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigvec", (char*) sigvec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigwait", (char*) sigwait, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sigwaitinfo", (char*) sigwaitinfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sin", (char*) sin, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sinh", (char*) sinh, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "skip__7istreami", (char*) skip__7istreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "skip_ws__FP9streambuf", (char*) skip_ws__FP9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllCount", (char*) sllCount, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllCreate", (char*) sllCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllDelete", (char*) sllDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllEach", (char*) sllEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllGet", (char*) sllGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllInit", (char*) sllInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllPrevious", (char*) sllPrevious, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllPutAtHead", (char*) sllPutAtHead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllPutAtTail", (char*) sllPutAtTail, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllRemove", (char*) sllRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sllTerminate", (char*) sllTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "smMemPartAddToPoolRtn", (char*) &smMemPartAddToPoolRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "smMemPartAllocRtn", (char*) &smMemPartAllocRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "smMemPartFindMaxRtn", (char*) &smMemPartFindMaxRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smMemPartFreeRtn", (char*) &smMemPartFreeRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "smMemPartOptionsSetRtn", (char*) &smMemPartOptionsSetRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smMemPartReallocRtn", (char*) &smMemPartReallocRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smMemPartShowRtn", (char*) &smMemPartShowRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smObjPoolMinusOne", (char*) &smObjPoolMinusOne, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smObjTaskDeleteFailRtn", (char*) &smObjTaskDeleteFailRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smObjTcbFreeFailRtn", (char*) &smObjTcbFreeFailRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "smObjTcbFreeRtn", (char*) &smObjTcbFreeRtn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "snextc__9streambuf", (char*) snextc__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "so", (char*) so, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soabort", (char*) soabort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soaccept", (char*) soaccept, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sobind", (char*) sobind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "socantrcvmore", (char*) socantrcvmore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "socantsendmore", (char*) socantsendmore, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sockFdtosockFunc", (char*) sockFdtosockFunc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sockLibAdd", (char*) sockLibAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sockLibInit", (char*) sockLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "socket", (char*) socket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soclose", (char*) soclose, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soconnect", (char*) soconnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soconnect2", (char*) soconnect2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "socreate", (char*) socreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sodisconnect", (char*) sodisconnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sofree", (char*) sofree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sogetopt", (char*) sogetopt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sohasoutofband", (char*) sohasoutofband, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soisconnected", (char*) soisconnected, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soisconnecting", (char*) soisconnecting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soisdisconnected", (char*) soisdisconnected, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soisdisconnecting", (char*) soisdisconnecting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "solisten", (char*) solisten, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sonewconn1", (char*) sonewconn1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soo_ioctl", (char*) soo_ioctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soo_select", (char*) soo_select, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soo_unselect", (char*) soo_unselect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soqinsque", (char*) soqinsque, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soqremque", (char*) soqremque, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soreceive", (char*) soreceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soreserve", (char*) soreserve, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sorflush", (char*) sorflush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sosend", (char*) sosend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sosetopt", (char*) sosetopt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "soshutdown", (char*) soshutdown, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sowakeup", (char*) sowakeup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sowakeupHook", (char*) &sowakeupHook, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sp", (char*) sp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spTaskOptions", (char*) &spTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "spTaskPriority", (char*) &spTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "spTaskStackSize", (char*) &spTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "splSemId", (char*) &splSemId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "splSemInit", (char*) splSemInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "splTid", (char*) &splTid, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "splimp", (char*) splimp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "splnet", (char*) splnet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "splnet2", (char*) splnet2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "splx", (char*) splx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sprintf", (char*) sprintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sputbackc__9streambufc", (char*) sputbackc__9streambufc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sputc__9streambufi", (char*) sputc__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sputn__9streambufPCci", (char*) sputn__9streambufPCci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spy", (char*) spy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyClkStart", (char*) spyClkStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyClkStartCommon", (char*) spyClkStartCommon, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyClkStop", (char*) spyClkStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyClkStopCommon", (char*) spyClkStopCommon, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyComTask", (char*) spyComTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyCommon", (char*) spyCommon, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyHelp", (char*) spyHelp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyIdleIncTicks", (char*) &spyIdleIncTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "spyIdleTicks", (char*) &spyIdleTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "spyIncTicks", (char*) &spyIncTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "spyInterruptIncTicks", (char*) &spyInterruptIncTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "spyInterruptTicks", (char*) &spyInterruptTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "spyKernelIncTicks", (char*) &spyKernelIncTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "spyKernelTicks", (char*) &spyKernelTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "spyLibInit", (char*) spyLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyReport", (char*) spyReport, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyReportCommon", (char*) spyReportCommon, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyStop", (char*) spyStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyStopCommon", (char*) spyStopCommon, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyTask", (char*) spyTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spyTaskId", (char*) &spyTaskId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "spyTaskOptions", (char*) &spyTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "spyTaskPriority", (char*) &spyTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "spyTaskStackSize", (char*) &spyTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "spyTotalTicks", (char*) &spyTotalTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sqrt", (char*) sqrt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "srand", (char*) srand, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "srandom", (char*) srandom, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sscanf", (char*) sscanf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sseekoff__9streambuflQ23ios8seek_diri", (char*) sseekoff__9streambuflQ23ios8seek_diri, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sseekpos__9streambufli", (char*) sseekpos__9streambufli, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stBdTmpTh", (char*) &stBdTmpTh, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "stBdVolTh", (char*) &stBdVolTh, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "start485", (char*) start485, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "start485test", (char*) start485test, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "startmm", (char*) startmm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "starttcp", (char*) starttcp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "starttimer", (char*) starttimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stat", (char*) stat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "statSymTbl", (char*) &statSymTbl, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "statTbl", (char*) &statTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "statTblSize", (char*) &statTblSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "statfs", (char*) statfs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioFp", (char*) stdioFp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioFpCreate", (char*) stdioFpCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioFpDestroy", (char*) stdioFpDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioInit", (char*) stdioInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioShow", (char*) stdioShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stdioShowInit", (char*) stdioShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "stossc__9streambuf", (char*) stossc__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcat", (char*) strcat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strchr", (char*) strchr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcmp", (char*) strcmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcoll", (char*) strcoll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcpy", (char*) strcpy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strcspn", (char*) strcspn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strerror", (char*) strerror, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strerror_r", (char*) strerror_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strftime", (char*) strftime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strlen", (char*) strlen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strncat", (char*) strncat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strncmp", (char*) strncmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strncpy", (char*) strncpy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strpbrk", (char*) strpbrk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strrchr", (char*) strrchr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strspn", (char*) strspn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strstr", (char*) strstr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtod", (char*) strtod, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtok", (char*) strtok, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtok_r", (char*) strtok_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtol", (char*) strtol, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strtoul", (char*) strtoul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "strxfrm", (char*) strxfrm, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "subnetsarelocal", (char*) &subnetsarelocal, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "substrcmp", (char*) substrcmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sungetc__9streambuf", (char*) sungetc__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "swab", (char*) swab, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "switch_to_get_mode__9streambuf", (char*) switch_to_get_mode__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symAdd", (char*) symAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symAlloc", (char*) symAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symByCNameFind", (char*) symByCNameFind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symByValueAndTypeFind", (char*) symByValueAndTypeFind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symByValueFind", (char*) symByValueFind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symEach", (char*) symEach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByCName", (char*) symFindByCName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByName", (char*) symFindByName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByNameAndType", (char*) symFindByNameAndType, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByValue", (char*) symFindByValue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindByValueAndType", (char*) symFindByValueAndType, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFindSymbol", (char*) symFindSymbol, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symFree", (char*) symFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symGroupDefault", (char*) &symGroupDefault, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "symInit", (char*) symInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symLibInit", (char*) symLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symLkupPgSz", (char*) &symLkupPgSz, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "symName", (char*) symName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symNameGet", (char*) symNameGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symRemove", (char*) symRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symSAdd", (char*) symSAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symShow", (char*) symShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symShowInit", (char*) symShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblAdd", (char*) symTblAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblClassId", (char*) &symTblClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "symTblCreate", (char*) symTblCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblDelete", (char*) symTblDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblDestroy", (char*) symTblDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblInit", (char*) symTblInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblRemove", (char*) symTblRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTblTerminate", (char*) symTblTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symTypeGet", (char*) symTypeGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "symValueGet", (char*) symValueGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "syncLoadRtn", (char*) &syncLoadRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "syncSymAddRtn", (char*) &syncSymAddRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "syncSymRemoveRtn", (char*) &syncSymRemoveRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sync__7filebuf", (char*) sync__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sync__7istream", (char*) sync__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sync__9streambuf", (char*) sync__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sync_with_stdio__3ios", (char*) sync_with_stdio__3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sync_with_stdio__3iosi", (char*) sync_with_stdio__3iosi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysAdaEnable", (char*) &sysAdaEnable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysAuxClkConnect", (char*) sysAuxClkConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysAuxClkDisable", (char*) sysAuxClkDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysAuxClkEnable", (char*) sysAuxClkEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysAuxClkRateGet", (char*) sysAuxClkRateGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysAuxClkRateSet", (char*) sysAuxClkRateSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBootFile", (char*) &sysBootFile, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysBootHost", (char*) &sysBootHost, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysBootLine", (char*) &sysBootLine, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysBootParams", (char*) &sysBootParams, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysBspRev", (char*) sysBspRev, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBus", (char*) &sysBus, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysBusIntAck", (char*) sysBusIntAck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBusIntGen", (char*) sysBusIntGen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBusTas", (char*) sysBusTas, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysBusToLocalAdrs", (char*) sysBusToLocalAdrs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysCacheLibInit", (char*) &sysCacheLibInit, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysClDescTbl", (char*) &sysClDescTbl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysClDescTblNumEnt", (char*) &sysClDescTblNumEnt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysClkConnect", (char*) sysClkConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkDisable", (char*) sysClkDisable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkEnable", (char*) sysClkEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkInit", (char*) sysClkInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkRateGet", (char*) sysClkRateGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysClkRateSet", (char*) sysClkRateSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysCplusEnable", (char*) &sysCplusEnable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysCpu", (char*) &sysCpu, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysExcMsg", (char*) &sysExcMsg, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysFlags", (char*) &sysFlags, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysFlashErase16", (char*) sysFlashErase16, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysFlashWrite16", (char*) sysFlashWrite16, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysFlashWriteEnable", (char*) sysFlashWriteEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysHwInit", (char*) sysHwInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysHwInit0", (char*) sysHwInit0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysHwInit2", (char*) sysHwInit2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInByte", (char*) sysInByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysInit", (char*) sysInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntDisablePIC", (char*) sysIntDisablePIC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntEnablePIC", (char*) sysIntEnablePIC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysIntLvlChgRtn", (char*) &sysIntLvlChgRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysIntLvlDisableRtn", (char*) &sysIntLvlDisableRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysIntLvlEnableRtn", (char*) &sysIntLvlEnableRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysIntLvlVecAckRtn", (char*) &sysIntLvlVecAckRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysIntLvlVecChkRtn", (char*) &sysIntLvlVecChkRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysIntStackSplit", (char*) sysIntStackSplit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysLedsReadWrite", (char*) sysLedsReadWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysLocalToBusAdrs", (char*) sysLocalToBusAdrs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysMailboxConnect", (char*) sysMailboxConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysMailboxEnable", (char*) sysMailboxEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysMclBlkConfig", (char*) &sysMclBlkConfig, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysMemTop", (char*) sysMemTop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysMmuLibInit", (char*) &sysMmuLibInit, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysModel", (char*) sysModel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysNvRamGet", (char*) sysNvRamGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysNvRamSet", (char*) sysNvRamSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysOutByte", (char*) sysOutByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysPhysMemDesc", (char*) &sysPhysMemDesc, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysPhysMemDescNumEnt", (char*) &sysPhysMemDescNumEnt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "sysPhysMemTop", (char*) sysPhysMemTop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysProcNum", (char*) &sysProcNum, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysProcNumGet", (char*) sysProcNumGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysProcNumSet", (char*) sysProcNumSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSecEnetAddrGet", (char*) sysSecEnetAddrGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSecEnetAddrSet", (char*) sysSecEnetAddrSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSectorErase16", (char*) sysSectorErase16, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSerialChanGet", (char*) sysSerialChanGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSerialHwInit", (char*) sysSerialHwInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSerialHwInit2", (char*) sysSerialHwInit2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysSerialReset", (char*) sysSerialReset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysStart", (char*) sysStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysStartType", (char*) &sysStartType, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysSymTbl", (char*) &sysSymTbl, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "sysTffsFormat", (char*) sysTffsFormat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sysToMonitor", (char*) sysToMonitor, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_close__7filebuf", (char*) sys_close__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_close__9streambuf", (char*) sys_close__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_read__7filebufPci", (char*) sys_read__7filebufPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_read__9streambufPci", (char*) sys_read__9streambufPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_seek__7filebuflQ23ios8seek_dir", (char*) sys_seek__7filebuflQ23ios8seek_dir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_seek__9streambuflQ23ios8seek_dir", (char*) sys_seek__9streambuflQ23ios8seek_dir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_stat__7filebufPv", (char*) sys_stat__7filebufPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_stat__9streambufPv", (char*) sys_stat__9streambufPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_write__7filebufPCci", (char*) sys_write__7filebufPCci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sys_write__9streambufPCci", (char*) sys_write__9streambufPCci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "system", (char*) system, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tKeepAlive__10C485ClientPv", (char*) tKeepAlive__10C485ClientPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tKeepAlive__11CEthnClientPv", (char*) tKeepAlive__11CEthnClientPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tListener__9CListenerPv", (char*) tListener__9CListenerPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tModuleManager__14CModuleManagerPv", (char*) tModuleManager__14CModuleManagerPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tPing", (char*) tPing, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tPoll__13CTimerManagerPv", (char*) tPoll__13CTimerManagerPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tReceiver__10C485ClientPv", (char*) tReceiver__10C485ClientPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tReceiver__11CEthnClientPv", (char*) tReceiver__11CEthnClientPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tSender__10C485ClientPv", (char*) tSender__10C485ClientPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tSender__11CEthnClientPv", (char*) tSender__11CEthnClientPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tTest", (char*) tTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tUrgencyReceive", (char*) tUrgencyReceive, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tUrgencySend", (char*) tUrgencySend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tan", (char*) tan, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tanh", (char*) tanh, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskAccept__13CCfgTcpSocketPv", (char*) taskAccept__13CCfgTcpSocketPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskAccept__14CSoftTcpSocketPv", (char*) taskAccept__14CSoftTcpSocketPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskAccept__15CAlarmTcpSocketPv", (char*) taskAccept__15CAlarmTcpSocketPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskAccept__15CDebugTcpSocketPv", (char*) taskAccept__15CDebugTcpSocketPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskActivate", (char*) taskActivate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskAlarmEvent", (char*) taskAlarmEvent, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskAlarmSocket", (char*) taskAlarmSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskArgsGet", (char*) taskArgsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskArgsSet", (char*) taskArgsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskBpHook", (char*) &taskBpHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskBpHookSet", (char*) taskBpHookSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCfgAndOper", (char*) taskCfgAndOper, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCfgSocket", (char*) taskCfgSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskClassId", (char*) &taskClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskCreat", (char*) taskCreat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateHookAdd", (char*) taskCreateHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateHookDelete", (char*) taskCreateHookDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateTable", (char*) &taskCreateTable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskDebugSocket", (char*) taskDebugSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDelay", (char*) taskDelay, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDelete", (char*) taskDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDeleteForce", (char*) taskDeleteForce, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDeleteHookAdd", (char*) taskDeleteHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDeleteHookDelete", (char*) taskDeleteHookDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskDeleteTable", (char*) &taskDeleteTable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskDestroy", (char*) taskDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskHookInit", (char*) taskHookInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdCurrent", (char*) &taskIdCurrent, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskIdDefault", (char*) taskIdDefault, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdFigure", (char*) taskIdFigure, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdListGet", (char*) taskIdListGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdListSort", (char*) taskIdListSort, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdSelf", (char*) taskIdSelf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIdVerify", (char*) taskIdVerify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskInfoGet", (char*) taskInfoGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskInit", (char*) taskInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskInstClassId", (char*) &taskInstClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskIsReady", (char*) taskIsReady, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskIsSuspended", (char*) taskIsSuspended, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskLibInit", (char*) taskLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskLock", (char*) taskLock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskMainCtrlAll", (char*) taskMainCtrlAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskName", (char*) taskName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskNameToId", (char*) taskNameToId, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsGet", (char*) taskOptionsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsSet", (char*) taskOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsString", (char*) taskOptionsString, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskPriRangeCheck", (char*) &taskPriRangeCheck, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskPriorityGet", (char*) taskPriorityGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskPrioritySet", (char*) taskPrioritySet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRecv__13CCfgTcpSocketPvUl", (char*) taskRecv__13CCfgTcpSocketPvUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRecv__14CSoftTcpSocketPvUl", (char*) taskRecv__14CSoftTcpSocketPvUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRecv__15CAlarmTcpSocketPvUl", (char*) taskRecv__15CAlarmTcpSocketPvUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRecv__15CDebugTcpSocketPvUl", (char*) taskRecv__15CDebugTcpSocketPvUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegName", (char*) &taskRegName, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskRegsFmt", (char*) &taskRegsFmt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskRegsGet", (char*) taskRegsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegsInit", (char*) taskRegsInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegsSet", (char*) taskRegsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRegsShow", (char*) taskRegsShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRestart", (char*) taskRestart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskResume", (char*) taskResume, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskRtnValueSet", (char*) taskRtnValueSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSafe", (char*) taskSafe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskShow", (char*) taskShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskShowInit", (char*) taskShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSoftUpgrade", (char*) taskSoftUpgrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSoftupgradeSocket", (char*) taskSoftupgradeSocket, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSpawn", (char*) taskSpawn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskStackAllot", (char*) taskStackAllot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskStatusString", (char*) taskStatusString, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSuspend", (char*) taskSuspend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapHookAdd", (char*) taskSwapHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapHookAttach", (char*) taskSwapHookAttach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapHookDelete", (char*) taskSwapHookDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapHookDetach", (char*) taskSwapHookDetach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwapReference", (char*) &taskSwapReference, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskSwapTable", (char*) &taskSwapTable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskSwitchHookAdd", (char*) taskSwitchHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwitchHookDelete", (char*) taskSwitchHookDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskSwitchTable", (char*) &taskSwitchTable, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskTcb", (char*) taskTcb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskTerminate", (char*) taskTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskUndelay", (char*) taskUndelay, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskUnlock", (char*) taskUnlock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskUnsafe", (char*) taskUnsafe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarAdd", (char*) taskVarAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarDelete", (char*) taskVarDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarGet", (char*) taskVarGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarInfo", (char*) taskVarInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarInit", (char*) taskVarInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskVarSet", (char*) taskVarSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcbinfo", (char*) &tcbinfo, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcpCfgParams", (char*) &tcpCfgParams, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcpLibInit", (char*) tcpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcpOutRsts", (char*) &tcpOutRsts, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcpRandHookAdd", (char*) tcpRandHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcpRandHookDelete", (char*) tcpRandHookDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcpReportRtn", (char*) &tcpReportRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcpTraceRtn", (char*) &tcpTraceRtn, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_alpha", (char*) &tcp_alpha, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcp_attach", (char*) tcp_attach, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_backoff", (char*) &tcp_backoff, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_beta", (char*) &tcp_beta, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcp_canceltimers", (char*) tcp_canceltimers, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_close", (char*) tcp_close, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_ctlinput", (char*) tcp_ctlinput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_ctloutput", (char*) tcp_ctloutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_disconnect", (char*) tcp_disconnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_do_rfc1323", (char*) &tcp_do_rfc1323, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_dooptions", (char*) tcp_dooptions, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_drain", (char*) tcp_drain, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_drop", (char*) tcp_drop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_fasttimo", (char*) tcp_fasttimo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_init", (char*) tcp_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_input", (char*) tcp_input, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_iss", (char*) &tcp_iss, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcp_keepcnt", (char*) &tcp_keepcnt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_keepidle", (char*) &tcp_keepidle, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_keepinit", (char*) &tcp_keepinit, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_keepintvl", (char*) &tcp_keepintvl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_last_inpcb", (char*) &tcp_last_inpcb, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_maxidle", (char*) &tcp_maxidle, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcp_maxpersistidle", (char*) &tcp_maxpersistidle, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_mss", (char*) tcp_mss, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_mssdflt", (char*) &tcp_mssdflt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_newtcpcb", (char*) tcp_newtcpcb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_notify", (char*) tcp_notify, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_now", (char*) &tcp_now, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcp_outflags", (char*) &tcp_outflags, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_output", (char*) tcp_output, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_pcbhashsize", (char*) &tcp_pcbhashsize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_pulloutofband", (char*) tcp_pulloutofband, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_quench", (char*) tcp_quench, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_reass", (char*) tcp_reass, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_recvspace", (char*) &tcp_recvspace, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_respond", (char*) tcp_respond, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_rtlookup", (char*) tcp_rtlookup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_rttdflt", (char*) &tcp_rttdflt, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_saveti", (char*) &tcp_saveti, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcp_sendspace", (char*) &tcp_sendspace, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_setpersist", (char*) tcp_setpersist, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_slowtimo", (char*) tcp_slowtimo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_template", (char*) tcp_template, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_timers", (char*) tcp_timers, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_totbackoff", (char*) &tcp_totbackoff, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcp_updatemtu", (char*) tcp_updatemtu, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_usrclosed", (char*) tcp_usrclosed, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_usrreq", (char*) tcp_usrreq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcp_xmit_timer", (char*) tcp_xmit_timer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tcpcb", (char*) &tcpcb, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcprexmtthresh", (char*) &tcprexmtthresh, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tcpstat", (char*) &tcpstat, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tcpstates", (char*) &tcpstates, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "td", (char*) td, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tellg__7istream", (char*) tellg__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tellp__7ostream", (char*) tellp__7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "telnetInTask", (char*) telnetInTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "telnetOutTask", (char*) telnetOutTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "telnetTaskOptions", (char*) &telnetTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "telnetTaskPriority", (char*) &telnetTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "telnetTaskStackSize", (char*) &telnetTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "telnetd", (char*) telnetd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "telnetdCurrentClients", (char*) &telnetdCurrentClients, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "telnetdExit", (char*) telnetdExit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "telnetdInit", (char*) telnetdInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "telnetdParserSet", (char*) telnetdParserSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "telnetdStart", (char*) telnetdStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "telnetdStaticTaskInitializationGet", (char*) telnetdStaticTaskInitializationGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "terminate__Fv", (char*) terminate__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testCopy", (char*) testCopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testMEntry", (char*) testMEntry, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testMultiMessage", (char*) testMultiMessage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testShow", (char*) testShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testgetalarmstate", (char*) testgetalarmstate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testio", (char*) testio, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testioRd", (char*) testioRd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffsDevCreate", (char*) tffsDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffsDevFormat", (char*) tffsDevFormat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffsDevOptionsSet", (char*) tffsDevOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffsDiskChangeAnnounce", (char*) tffsDiskChangeAnnounce, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffsDrv", (char*) tffsDrv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffsRawio", (char*) tffsRawio, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffsShow", (char*) tffsShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffsShowAll", (char*) tffsShowAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tffscmpWords", (char*) tffscmpWords, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpCopy", (char*) tftpCopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpErrorCreate", (char*) tftpErrorCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpGet", (char*) tftpGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpInfoShow", (char*) tftpInfoShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpInit", (char*) tftpInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpModeSet", (char*) tftpModeSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpPeerSet", (char*) tftpPeerSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpPut", (char*) tftpPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpQuit", (char*) tftpQuit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpReXmit", (char*) &tftpReXmit, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tftpSend", (char*) tftpSend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpTask", (char*) tftpTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tftpTaskOptions", (char*) &tftpTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tftpTaskPriority", (char*) &tftpTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tftpTaskStackSize", (char*) &tftpTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tftpTimeout", (char*) &tftpTimeout, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tftpTrace", (char*) &tftpTrace, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tftpVerbose", (char*) &tftpVerbose, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tftpXfer", (char*) tftpXfer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ti", (char*) ti, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tick64Get", (char*) tick64Get, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tick64Set", (char*) tick64Set, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tickAnnounce", (char*) tickAnnounce, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tickGet", (char*) tickGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tickQHead", (char*) &tickQHead, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "tickSet", (char*) tickSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tie__3iosP7ostream", (char*) tie__3iosP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tie__C3ios", (char*) tie__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "time", (char*) time, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timex", (char*) timex, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexClear", (char*) timexClear, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexFunc", (char*) timexFunc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexHelp", (char*) timexHelp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexInit", (char*) timexInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexN", (char*) timexN, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexPost", (char*) timexPost, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexPre", (char*) timexPre, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "timexShow", (char*) timexShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tkRcvRtnCall", (char*) tkRcvRtnCall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tlTable", (char*) &tlTable, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tmpfile", (char*) tmpfile, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tmpnam", (char*) tmpnam, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "toBCD", (char*) toBCD, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "toUNAL", (char*) toUNAL, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "toUNALLONG", (char*) toUNALLONG, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tolower", (char*) tolower, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "toupper", (char*) toupper, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tr", (char*) tr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "trcDefaultArgs", (char*) &trcDefaultArgs, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "trcStack", (char*) trcStack, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "trgCnt", (char*) &trgCnt, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "trgEvtClass", (char*) &trgEvtClass, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "ts", (char*) ts, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tt", (char*) tt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ttyDevCreate", (char*) ttyDevCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ttyDrv", (char*) ttyDrv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyAbortFuncSet", (char*) tyAbortFuncSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyAbortSet", (char*) tyAbortSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyBackspaceChar", (char*) &tyBackspaceChar, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tyBackspaceSet", (char*) tyBackspaceSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyDeleteLineChar", (char*) &tyDeleteLineChar, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tyDeleteLineSet", (char*) tyDeleteLineSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyDevInit", (char*) tyDevInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyDevRemove", (char*) tyDevRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyEOFSet", (char*) tyEOFSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyEofChar", (char*) &tyEofChar, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "tyIRd", (char*) tyIRd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyITx", (char*) tyITx, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyIoctl", (char*) tyIoctl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyMonitorTrapSet", (char*) tyMonitorTrapSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyRead", (char*) tyRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tyWrite", (char*) tyWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udb", (char*) &udb, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "udbinfo", (char*) &udbinfo, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "udpCfgParams", (char*) &udpCfgParams, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udpCommIfInit", (char*) udpCommIfInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udpDoCkSumRcv", (char*) &udpDoCkSumRcv, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udpLibInit", (char*) udpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udpRcv", (char*) udpRcv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_ctlinput", (char*) udp_ctlinput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_in", (char*) &udp_in, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udp_init", (char*) udp_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_input", (char*) udp_input, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_last_inpcb", (char*) &udp_last_inpcb, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udp_output", (char*) udp_output, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udp_pcbhashsize", (char*) &udp_pcbhashsize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udp_recvspace", (char*) &udp_recvspace, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udp_sendspace", (char*) &udp_sendspace, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udp_ttl", (char*) &udp_ttl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udp_usrreq", (char*) udp_usrreq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "udpcksum", (char*) &udpcksum, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "udpstat", (char*) &udpstat, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "uflow__9streambuf", (char*) uflow__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "uiomove", (char*) uiomove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unbuffered__9streambuf", (char*) unbuffered__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unbuffered__9streambufi", (char*) unbuffered__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "uncaught_exception__Fv", (char*) uncaught_exception__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "underflow__7filebuf", (char*) underflow__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "underflow__9streambuf", (char*) underflow__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unexpected__Fv", (char*) unexpected__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unget__7istream", (char*) unget__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unget__7istreamc", (char*) unget__7istreamc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ungetc", (char*) ungetc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unlink", (char*) unlink, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unlock__FR7istream", (char*) unlock__FR7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unlock__FR7ostream", (char*) unlock__FR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unsave_markers__9streambuf", (char*) unsave_markers__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unset__3ios11state_value", (char*) unset__3ios11state_value, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unsetf__3iosUl", (char*) unsetf__3iosUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "upcast__C16__user_type_infoRC9type_infoPvPPv", (char*) upcast__C16__user_type_infoRC9type_infoPvPPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "urgencyInit", (char*) urgencyInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "urgencySendTest", (char*) urgencySendTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "useloopback", (char*) &useloopback, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "usrAppInit", (char*) usrAppInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBanner", (char*) usrBanner, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBootLineCrack", (char*) usrBootLineCrack, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBootLineInit", (char*) usrBootLineInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBootLineParse", (char*) usrBootLineParse, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBreakpointSet", (char*) usrBreakpointSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrBsdSockLibInit", (char*) usrBsdSockLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrCacheEnable", (char*) usrCacheEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrClock", (char*) usrClock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrDhcpcLeaseClean", (char*) usrDhcpcLeaseClean, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrDosFsInit", (char*) usrDosFsInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrEndLibInit", (char*) usrEndLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrFtpInit", (char*) usrFtpInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrInit", (char*) usrInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrIosCoreInit", (char*) usrIosCoreInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrIosExtraInit", (char*) usrIosExtraInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrIpLibInit", (char*) usrIpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrKernelCoreInit", (char*) usrKernelCoreInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrKernelExtraInit", (char*) usrKernelExtraInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrKernelInit", (char*) usrKernelInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrMmuInit", (char*) usrMmuInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrMuxLibInit", (char*) usrMuxLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetAppInit", (char*) usrNetAppInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetBoot", (char*) usrNetBoot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetConfig", (char*) usrNetConfig, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetDevNameGet", (char*) usrNetDevNameGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetEndDevStart", (char*) usrNetEndDevStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetHostSetup", (char*) usrNetHostSetup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetIfConfig", (char*) usrNetIfConfig, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetLibInit", (char*) usrNetLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetLoopbackStart", (char*) usrNetLoopbackStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetProtoInit", (char*) usrNetProtoInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetRemoteCreate", (char*) usrNetRemoteCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetRemoteInit", (char*) usrNetRemoteInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetmaskGet", (char*) usrNetmaskGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetworkAddrCheck", (char*) usrNetworkAddrCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetworkAddrInit", (char*) usrNetworkAddrInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetworkBoot", (char*) usrNetworkBoot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetworkDevStart", (char*) usrNetworkDevStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrNetworkInit", (char*) usrNetworkInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrRoot", (char*) usrRoot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrSecurity", (char*) usrSecurity, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrSerialInit", (char*) usrSerialInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrShellInit", (char*) usrShellInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrShowInit", (char*) usrShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrStandaloneInit", (char*) usrStandaloneInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrStatTblInit", (char*) usrStatTblInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrTelnetdStart", (char*) usrTelnetdStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrTffsConfig", (char*) usrTffsConfig, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrTffsLnConfig", (char*) usrTffsLnConfig, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrToolsInit", (char*) usrToolsInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrWdbBanner", (char*) usrWdbBanner, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrWdbBp", (char*) usrWdbBp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "usrWdbInit", (char*) usrWdbInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "uswab", (char*) uswab, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "utime", (char*) utime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "valloc", (char*) valloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "version", (char*) version, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vfdprintf", (char*) vfdprintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vfprintf", (char*) vfprintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBaseGlobalMapInit", (char*) vmBaseGlobalMapInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBaseLibInit", (char*) vmBaseLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBasePageSizeGet", (char*) vmBasePageSizeGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmBaseStateSet", (char*) vmBaseStateSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vmLibInfo", (char*) &vmLibInfo, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "vprintf", (char*) vprintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vscan__7istreamPCcPv", (char*) vscan__7istreamPCcPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vscan__9streambufPCcPvP3ios", (char*) vscan__9streambufPCcPvP3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vsprintf", (char*) vsprintf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxAbsTicks", (char*) &vxAbsTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxEventPendQ", (char*) &vxEventPendQ, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIntStackBase", (char*) &vxIntStackBase, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIntStackEnd", (char*) &vxIntStackEnd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIrqIntStackBase", (char*) &vxIrqIntStackBase, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxIrqIntStackEnd", (char*) &vxIrqIntStackEnd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxMemArchProbe", (char*) vxMemArchProbe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbe", (char*) vxMemProbe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxMemProbeSup", (char*) vxMemProbeSup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxSvcIntStackBase", (char*) &vxSvcIntStackBase, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxSvcIntStackEnd", (char*) &vxSvcIntStackEnd, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxTas", (char*) vxTas, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxTaskEntry", (char*) vxTaskEntry, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "vxTicks", (char*) &vxTicks, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "vxWorksVersion", (char*) &vxWorksVersion, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wakeup", (char*) wakeup, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wcstombs", (char*) wcstombs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wctomb", (char*) wctomb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdCancel", (char*) wdCancel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdClassId", (char*) &wdClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdCreate", (char*) wdCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdDelete", (char*) wdDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdDestroy", (char*) wdDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdInit", (char*) wdInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdInstClassId", (char*) &wdInstClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdLibInit", (char*) wdLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdShow", (char*) wdShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdShowInit", (char*) wdShowInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdStart", (char*) wdStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdTerminate", (char*) wdTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdTick", (char*) wdTick, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbBpInstall", (char*) wdbBpInstall, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbBpSysEnterHook", (char*) &wdbBpSysEnterHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbBpSysExitHook", (char*) &wdbBpSysExitHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbCksum", (char*) wdbCksum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCommDevInit", (char*) wdbCommDevInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCommMtu", (char*) &wdbCommMtu, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbConfig", (char*) wdbConfig, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbConnectLibInit", (char*) wdbConnectLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxCreate", (char*) wdbCtxCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxExitLibInit", (char*) wdbCtxExitLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxExitNotifyHook", (char*) wdbCtxExitNotifyHook, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxLibInit", (char*) wdbCtxLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxResume", (char*) wdbCtxResume, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbCtxStartLibInit", (char*) wdbCtxStartLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgArchInit", (char*) wdbDbgArchInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgBpFind", (char*) wdbDbgBpFind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgBpGet", (char*) wdbDbgBpGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgBpListInit", (char*) wdbDbgBpListInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgBpRemove", (char*) wdbDbgBpRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgBpRemoveAll", (char*) wdbDbgBpRemoveAll, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgGetNpc", (char*) wdbDbgGetNpc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgTraceModeClear", (char*) wdbDbgTraceModeClear, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgTraceModeSet", (char*) wdbDbgTraceModeSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDbgTrap", (char*) wdbDbgTrap, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbDirectCallLibInit", (char*) wdbDirectCallLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbE", (char*) wdbE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEndDebug", (char*) &wdbEndDebug, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbEndPktDevInit", (char*) wdbEndPktDevInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEventDeq", (char*) wdbEventDeq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEventLibInit", (char*) wdbEventLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEventNodeInit", (char*) wdbEventNodeInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEventPost", (char*) wdbEventPost, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEvtptClassConnect", (char*) wdbEvtptClassConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbEvtptLibInit", (char*) wdbEvtptLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExcLibInit", (char*) wdbExcLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternEnterHook", (char*) wdbExternEnterHook, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternExitHook", (char*) wdbExternExitHook, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternInit", (char*) wdbExternInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternRegSetObjAdd", (char*) wdbExternRegSetObjAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternRegsGet", (char*) wdbExternRegsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternRegsSet", (char*) wdbExternRegsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbExternSystemRegs", (char*) &wdbExternSystemRegs, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbFuncCallLibInit", (char*) wdbFuncCallLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbGopherLibInit", (char*) wdbGopherLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbGopherLock", (char*) &wdbGopherLock, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbInfoGet", (char*) wdbInfoGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbInstallCommIf", (char*) wdbInstallCommIf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbInstallRtIf", (char*) wdbInstallRtIf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbIsInitialized", (char*) &wdbIsInitialized, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbIsNowExternal", (char*) wdbIsNowExternal, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbIsNowTasking", (char*) wdbIsNowTasking, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMbufAlloc", (char*) wdbMbufAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMbufFree", (char*) wdbMbufFree, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMemCoreLibInit", (char*) wdbMemCoreLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMemLibInit", (char*) wdbMemLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbMemTest", (char*) wdbMemTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbModeSet", (char*) wdbModeSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbNotifyHost", (char*) wdbNotifyHost, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbNptInt", (char*) wdbNptInt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbNptShutdown", (char*) wdbNptShutdown, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbNumMemRegions", (char*) &wdbNumMemRegions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbOneShot", (char*) &wdbOneShot, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "wdbRegsLibInit", (char*) wdbRegsLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbResumeSystem", (char*) wdbResumeSystem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcGetArgs", (char*) wdbRpcGetArgs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcNotifyConnect", (char*) wdbRpcNotifyConnect, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcNotifyHost", (char*) wdbRpcNotifyHost, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcRcv", (char*) wdbRpcRcv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcReply", (char*) wdbRpcReply, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcReplyErr", (char*) wdbRpcReplyErr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcResendReply", (char*) wdbRpcResendReply, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRpcXportInit", (char*) wdbRpcXportInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRtIf", (char*) &wdbRtIf, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbRtInfoGet", (char*) wdbRtInfoGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRunsExternal", (char*) wdbRunsExternal, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbRunsTasking", (char*) wdbRunsTasking, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSp", (char*) wdbSp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSuspendSystem", (char*) wdbSuspendSystem, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSuspendSystemHere", (char*) wdbSuspendSystemHere, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcAdd", (char*) wdbSvcAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcDispatch", (char*) wdbSvcDispatch, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcDsaSvcRemove", (char*) wdbSvcDsaSvcRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcHookAdd", (char*) wdbSvcHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSvcLibInit", (char*) wdbSvcLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSysBpLibInit", (char*) wdbSysBpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSysModeInit", (char*) wdbSysModeInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbSystemSuspend", (char*) wdbSystemSuspend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTargetIsConnected", (char*) wdbTargetIsConnected, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTask", (char*) wdbTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskAvRegsGet", (char*) &wdbTaskAvRegsGet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTaskAvRegsSet", (char*) &wdbTaskAvRegsSet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTaskBpLibInit", (char*) wdbTaskBpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskDspRegsGet", (char*) &wdbTaskDspRegsGet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTaskDspRegsSet", (char*) &wdbTaskDspRegsSet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTaskFpRegsGet", (char*) &wdbTaskFpRegsGet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTaskFpRegsSet", (char*) &wdbTaskFpRegsSet, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTaskId", (char*) &wdbTaskId, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTaskInit", (char*) wdbTaskInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskModeInit", (char*) wdbTaskModeInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTaskRestartHook", (char*) &wdbTaskRestartHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wdbTgtHasAltivec", (char*) wdbTgtHasAltivec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTgtHasAltivecSet", (char*) wdbTgtHasAltivecSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTgtHasDsp", (char*) wdbTgtHasDsp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTgtHasDspSet", (char*) wdbTgtHasDspSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTgtHasFpp", (char*) wdbTgtHasFpp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbTgtHasFppSet", (char*) wdbTgtHasFppSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbToolName", (char*) wdbToolName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbUserEvtLibInit", (char*) wdbUserEvtLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbUserEvtPost", (char*) wdbUserEvtPost, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbVioChannelRegister", (char*) wdbVioChannelRegister, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbVioChannelUnregister", (char*) wdbVioChannelUnregister, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbVioDrv", (char*) wdbVioDrv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wdbVioLibInit", (char*) wdbVioLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "what__C9bad_alloc", (char*) what__C9bad_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "what__C9exception", (char*) what__C9exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "whoami", (char*) whoami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "width__3iosi", (char*) width__3iosi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "width__C3ios", (char*) width__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wildcard", (char*) &wildcard, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "windDelay", (char*) windDelay, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windDelete", (char*) windDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windExit", (char*) windExit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windIntStackSet", (char*) windIntStackSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQFlush", (char*) windPendQFlush, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQGet", (char*) windPendQGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQPut", (char*) windPendQPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQRemove", (char*) windPendQRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPendQTerminate", (char*) windPendQTerminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPriNormalSet", (char*) windPriNormalSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windPrioritySet", (char*) windPrioritySet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windReadyQPut", (char*) windReadyQPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windReadyQRemove", (char*) windReadyQRemove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windResume", (char*) windResume, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windSemDelete", (char*) windSemDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windSpawn", (char*) windSpawn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windSuspend", (char*) windSuspend, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windTickAnnounce", (char*) windTickAnnounce, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windUndelay", (char*) windUndelay, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windWdCancel", (char*) windWdCancel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "windWdStart", (char*) windWdStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQAdd0", (char*) workQAdd0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQAdd1", (char*) workQAdd1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQAdd2", (char*) workQAdd2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQDoWork", (char*) workQDoWork, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQInit", (char*) workQInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQIsEmpty", (char*) &workQIsEmpty, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "workQPanic", (char*) workQPanic, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "workQReadIx", (char*) &workQReadIx, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "workQWriteIx", (char*) &workQWriteIx, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "writable__3ios", (char*) writable__3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write", (char*) write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "writeFlash16", (char*) writeFlash16, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write__7ostreamPCSci", (char*) write__7ostreamPCSci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write__7ostreamPCUci", (char*) write__7ostreamPCUci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write__7ostreamPCci", (char*) write__7ostreamPCci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write__7ostreamPCvi", (char*) write__7ostreamPCvi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "writev", (char*) writev, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ws__FR7istream", (char*) ws__FR7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "wvEvtClass", (char*) &wvEvtClass, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wvInstIsOn", (char*) &wvInstIsOn, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "wvObjIsEnabled", (char*) &wvObjIsEnabled, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "xattrib", (char*) xattrib, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xchain__9streambuf", (char*) xchain__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xcopy", (char*) xcopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdelete", (char*) xdelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdrCksum", (char*) xdrCksum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_ARRAY", (char*) xdr_ARRAY, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_CHECKSUM", (char*) xdr_CHECKSUM, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_TGT_ADDR_T", (char*) xdr_TGT_ADDR_T, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_TGT_INT_T", (char*) xdr_TGT_INT_T, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_UINT32", (char*) xdr_UINT32, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_AGENT_INFO", (char*) xdr_WDB_AGENT_INFO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CALL_RETURN_INFO", (char*) xdr_WDB_CALL_RETURN_INFO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CTX", (char*) xdr_WDB_CTX, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CTX_CREATE_DESC", (char*) xdr_WDB_CTX_CREATE_DESC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_CTX_STEP_DESC", (char*) xdr_WDB_CTX_STEP_DESC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_EVTPT_ADD_DESC", (char*) xdr_WDB_EVTPT_ADD_DESC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_EVTPT_DEL_DESC", (char*) xdr_WDB_EVTPT_DEL_DESC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_EVT_DATA", (char*) xdr_WDB_EVT_DATA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_EVT_INFO", (char*) xdr_WDB_EVT_INFO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_MEM_REGION", (char*) xdr_WDB_MEM_REGION, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_MEM_SCAN_DESC", (char*) xdr_WDB_MEM_SCAN_DESC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_MEM_XFER", (char*) xdr_WDB_MEM_XFER, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_OPQ_DATA_T", (char*) xdr_WDB_OPQ_DATA_T, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_PARAM_WRAPPER", (char*) xdr_WDB_PARAM_WRAPPER, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_REG_READ_DESC", (char*) xdr_WDB_REG_READ_DESC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_REG_WRITE_DESC", (char*) xdr_WDB_REG_WRITE_DESC, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_REPLY_WRAPPER", (char*) xdr_WDB_REPLY_WRAPPER, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_RT_INFO", (char*) xdr_WDB_RT_INFO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_STRING_T", (char*) xdr_WDB_STRING_T, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_WDB_TGT_INFO", (char*) xdr_WDB_TGT_INFO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_bool", (char*) xdr_bool, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_bytes", (char*) xdr_bytes, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_char", (char*) xdr_char, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_double", (char*) xdr_double, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_enum", (char*) xdr_enum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_float", (char*) xdr_float, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_floatInclude", (char*) xdr_floatInclude, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_free", (char*) xdr_free, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_int", (char*) xdr_int, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_long", (char*) xdr_long, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_netobj", (char*) xdr_netobj, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_opaque", (char*) xdr_opaque, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_short", (char*) xdr_short, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_string", (char*) xdr_string, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_u_char", (char*) xdr_u_char, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_u_int", (char*) xdr_u_int, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_u_long", (char*) xdr_u_long, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_u_short", (char*) xdr_u_short, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_union", (char*) xdr_union, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_void", (char*) xdr_void, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdr_wrapstring", (char*) xdr_wrapstring, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xdrmem_create", (char*) xdrmem_create, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xflags__9streambuf", (char*) xflags__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xflags__9streambufi", (char*) xflags__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xmalloc", (char*) xmalloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xput_char__9streambufc", (char*) xput_char__9streambufc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xrealloc", (char*) xrealloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xsetflags__9streambufi", (char*) xsetflags__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xsetflags__9streambufii", (char*) xsetflags__9streambufii, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xsgetn__7filebufPci", (char*) xsgetn__7filebufPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xsgetn__9streambufPci", (char*) xsgetn__9streambufPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xsputn__7filebufPCci", (char*) xsputn__7filebufPCci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "xsputn__9streambufPCci", (char*) xsputn__9streambufPCci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "yy_yys", (char*) &yy_yys, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yy_yyv", (char*) &yy_yyv, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yychar", (char*) &yychar, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yydebug", (char*) &yydebug, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yyerrflag", (char*) &yyerrflag, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yylval", (char*) &yylval, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yynerrs", (char*) &yynerrs, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yyparse", (char*) yyparse, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "yyps", (char*) &yyps, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yypv", (char*) &yypv, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yys", (char*) &yys, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "yystart", (char*) yystart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "yystate", (char*) &yystate, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yytmp", (char*) &yytmp, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "yyv", (char*) &yyv, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "yyval", (char*) &yyval, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "zeroin_addr", (char*) &zeroin_addr, 0, SYM_GLOBAL | SYM_BSS},
    };


ULONG standTblSize = 5241;
