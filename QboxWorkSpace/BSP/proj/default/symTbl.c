/* symTbl.c - standalone symbol tables wrapper */

/* CREATED BY C:\Tornado2.2/host/src/hutils/makeSymTbl.tcl
 *  WITH ARGS arm tmp.o symTbl.c
 *         ON Sun Aug 26 14:37:07 中国标准时间 2012
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
IMPORT int BSPBooter ();
IMPORT int BSPCheckSum ();
IMPORT int BSPFileUncompress ();
IMPORT int BSPGetFileFromNorFlash ();
IMPORT int BSPGetNandFileVerDevice ();
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
IMPORT int BSP_memPartShow ();
IMPORT int Bbase__9streambuf ();
IMPORT int BitmapCopy__FP14tagDispBitmapTUsUsT0 ();
IMPORT int BitmapDecode1Bit__FPUcllT0 ();
IMPORT int BitmapDecode24Bits__FPUcllT0 ();
IMPORT int BitmapDecode2FrameBuffer__FPUcUsUsP14tagDispBitmapT ();
IMPORT int BitmapDecode8Bits__FPUcllT0 ();
IMPORT int BitmapDecode__FPUcUlP14tagDispBitmapT ();
IMPORT int BitmapEncode16Bit__FP14tagDispBitmapTPUcPUl ();
IMPORT int BitmapEncode__FP14tagDispBitmapTPUcPUl ();
IMPORT int BitmapFormatFrameBuffer__FP14tagDispBitmapT ();
IMPORT int Bptr__9streambuf ();
IMPORT int BroadcastMsg__7IServerPcUl ();
IMPORT int BulkErase ();
IMPORT int C753Get22PulldownSequenceCount1__Q24chip13DriverChip753UlRUc ();
IMPORT int C753Get23PulldownSequenceCount1__Q24chip13DriverChip753UlRUc ();
IMPORT int C753Get23PulldownSequenceCount2__Q24chip13DriverChip753UlRUc ();
IMPORT int C753Get23PulldownSequenceCount3__Q24chip13DriverChip753UlRUc ();
IMPORT int C753Get23PulldownSequenceCount4__Q24chip13DriverChip753UlRUc ();
IMPORT int C753Get23PulldownSequenceCount5__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetAverageLuminanceLevelResult__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetBankRegister__Q24chip13DriverChip753RUc ();
IMPORT int C753GetBitmapOSDStatus__Q24chip13DriverChip753RUc ();
IMPORT int C753GetBlockNoiseHBoundaryCoordinate__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetBlockNoiseHMatchingCountsMax2__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetBlockNoiseHMatchingCountsMax__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetBlockNoiseVBoundaryCoordinate__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetBlockNoiseVMatchingCountsMax2__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetBlockNoiseVMatchingCountsMax__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetCPUData__Q24chip13DriverChip753RUc ();
IMPORT int C753GetCharacteristicsMeasurementResult0__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetCharacteristicsMeasurementResult1__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetCharacteristicsMeasurementResultHorizontalCoordinate0__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetCharacteristicsMeasurementResultHorizontalCoordinate1__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetCharacteristicsMeasurementResultVerticalCoordinate0__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetCharacteristicsMeasurementResultVerticalCoordinate1__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetDPMSInterruptStatus__Q24chip13DriverChip753RUc ();
IMPORT int C753GetDPMSStatus__Q24chip13DriverChip753RUc ();
IMPORT int C753GetFieldHistory__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetFlashStatus__Q24chip13DriverChip753RUc ();
IMPORT int C753GetHorizontalAndVerticalSyncPhaseDifference0__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetHorizontalAndVerticalSyncPhaseDifference1__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetInputPortACTHorizontalStart__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetInputPortACTVerticalStart__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetInputPortHorizontalSyncFrequency__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetInputPortHorizontalSyncPulseWidth__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetInputPortVerticalSyncFrequency__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetInputPortVerticalSyncPulseWidth__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetInterruptStatus__Q24chip13DriverChip753RUs ();
IMPORT int C753GetMAXFILTERResult__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetMINFILTERResult__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetMainControl__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetMeasurementStatusMonitor__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetMemoryReadLinefeedWidth__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetOutputField0MemoryReadStartAddress__Q24chip13DriverChip753UlRUl ();
IMPORT int C753GetOutputField1MemoryReadStartAddress__Q24chip13DriverChip753UlRUl ();
IMPORT int C753GetOutputField2MemoryReadStartAddress__Q24chip13DriverChip753UlRUl ();
IMPORT int C753GetOutputField3MemoryReadStartAddress__Q24chip13DriverChip753UlRUl ();
IMPORT int C753GetOutputPortACTHorizontalStart__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetOutputPortACTVerticalStart__Q24chip13DriverChip753UlRUs ();
IMPORT int C753GetOutputPortSyncControl__Q24chip13DriverChip753RUs ();
IMPORT int C753GetOutputPortVerticalSyncFrequency__Q24chip13DriverChip753RUs ();
IMPORT int C753GetOverlayControl__Q24chip13DriverChip753RUc ();
IMPORT int C753GetPWMHighPulseWidthCounterValue__Q24chip13DriverChip753RUs ();
IMPORT int C753GetPWMLowPulseWidthCounterValue__Q24chip13DriverChip753RUs ();
IMPORT int C753GetSNHistogramMeasurementResult__Q24chip13DriverChip753UlRUc ();
IMPORT int C753GetStatus__Q24chip13DriverChip753RUs ();
IMPORT int C753LoadDiagonalInterpolationThreshold__Q24chip13DriverChip753UlPCUc ();
IMPORT int C753LoadInputHorizontalShrinkLookupTable__Q24chip13DriverChip753UlPCUc ();
IMPORT int C753LoadInputVerticalShrinkLookupTable__Q24chip13DriverChip753UlPCUc ();
IMPORT int C753LoadOutputHorizontalZoomLookupTable__Q24chip13DriverChip753UlPCUc ();
IMPORT int C753LoadOutputVerticalZoomLookupTable__Q24chip13DriverChip753UlPCUc ();
IMPORT int C753ReadN24BitPixels__Q24chip13DriverChip753UsPUc ();
IMPORT int C753Reset__Q24chip13DriverChip753Uc ();
IMPORT int C753Set1MHzPulseGenerationControl__Q24chip13DriverChip753Uc ();
IMPORT int C753Set22PulldownMovementDetectThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753Set22PulldownResetDetectIndex__Q24chip13DriverChip753UlUc ();
IMPORT int C753Set23PulldownMovementDetectThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753Set23PulldownResetDetectIndex__Q24chip13DriverChip753UlUc ();
IMPORT int C753Set2ScreenBlendingAlphaCoefficient__Q24chip13DriverChip753Uc ();
IMPORT int C753Set2ScreenBlendingBetaCoefficient__Q24chip13DriverChip753Uc ();
IMPORT int C753Set90DegreeRotationField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753Set90DegreeRotationField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753Set90DegreeRotationField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753Set90DegreeRotationField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753Set90DegreeRotationField2MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753Set90DegreeRotationField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753Set90DegreeRotationField3MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753Set90DegreeRotationField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753Set90DegreeRotationMemoryReadLinefeedWidth__Q24chip13DriverChip753UlUc ();
IMPORT int C753Set90DegreeRotationMemoryWriteLinefeedWidth__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetAdaptiveNRCoefficient__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetAdaptiveNRControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetAdaptiveNRThreshold__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetBackgroundControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBankRegister__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBitBLTHorizontalWidth__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBitBLTReadLinefeedWidth__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBitBLTTriggerVSDelay__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBitBLTVerticalWidth__Q24chip13DriverChip753Us ();
IMPORT int C753SetBitBLTWriteLinefeedWidth__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBitmapOSD90DegreeRotation__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBitmapOSDAccessControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBlinkCycle__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBlinkingTime__Q24chip13DriverChip753Uc ();
IMPORT int C753SetBlockBoundaryPeripheralEdgeLevelThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockBoundaryPeripheralMovementValueThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRAlphaBlendCoefficient0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRAlphaBlendCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRControl__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetBlockNRDetectControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRLowPassFilterCoefficient0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRLowPassFilterCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRProjectionCoefficient__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRProjectionControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRProjectionReadAddress__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRProjectionReadData__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNRTest__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNoiseEdgeLevelThreshold0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNoiseEdgeLevelThreshold1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNoiseEdgeLevelThreshold2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetBlockNoiseEdgeLevelThreshold3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetCPUData__Q24chip13DriverChip753Uc ();
IMPORT int C753SetCPUReadAddress__Q24chip13DriverChip753Ul ();
IMPORT int C753SetCPUWriteAddress__Q24chip13DriverChip753Ul ();
IMPORT int C753SetChannel1Image90DegreeRotationControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetChannel1Image90DegreeRotationHorizontalActiveAreaWidth__Q24chip13DriverChip753Us ();
IMPORT int C753SetChannel1Image90DegreeRotationVerticalActiveAreaWidth__Q24chip13DriverChip753Us ();
IMPORT int C753SetChannel1Image90DegreeRotationVerticalSyncSignalDelay__Q24chip13DriverChip753Us ();
IMPORT int C753SetChannel2Image90DegreeRotationControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetChannel2Image90DegreeRotationHorizontalActiveAreaWidth__Q24chip13DriverChip753Us ();
IMPORT int C753SetChannel2Image90DegreeRotationVerticalActiveAreaWidth__Q24chip13DriverChip753Us ();
IMPORT int C753SetChannel2Image90DegreeRotationVerticalSyncSignalDelay__Q24chip13DriverChip753Us ();
IMPORT int C753SetCharacterBufferAddress__Q24chip13DriverChip753Us ();
IMPORT int C753SetCharacterBufferData__Q24chip13DriverChip753Uc ();
IMPORT int C753SetCharacterBufferHorizontalStart__Q24chip13DriverChip753Uc ();
IMPORT int C753SetCharacterBufferHorizontalWidth__Q24chip13DriverChip753Uc ();
IMPORT int C753SetCharacterBufferVerticalStart__Q24chip13DriverChip753Uc ();
IMPORT int C753SetCharacterBufferVerticalWidth__Q24chip13DriverChip753Uc ();
IMPORT int C753SetChromaErrorAutomaticCorrectionCounterUpperLimit__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetChromaErrorAutomaticCorrectionThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetChromaErrorCorrectionControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetChromaErrorCorrectionLowPassFilterCoefficient__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetChromaErrorDetectionCountThreshold__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetChromaErrorDetectionExclusionThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetChromaErrorDetectionThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetColorBarWidthSetting__Q24chip13DriverChip753Uc ();
IMPORT int C753SetCombingProcessControlHighLevelThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetCombingProcessControlLowLevelThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetCombingProcessControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetDDRControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl0__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl1__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl2__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl3__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl4__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl5__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl6__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl7__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDLLControl8__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDPMSControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDPMSInterruptReset__Q24chip13DriverChip753Uc ();
IMPORT int C753SetDiagonalInterpolationControl__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetFieldInterlockTransferControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetFieldPropagationDelay1__Q24chip13DriverChip753Uc ();
IMPORT int C753SetFieldPropagationDelay2__Q24chip13DriverChip753Uc ();
IMPORT int C753SetForcedSyncResetControl__Q24chip13DriverChip753Us ();
IMPORT int C753SetForcedSyncResetDelay__Q24chip13DriverChip753Uc ();
IMPORT int C753SetHBlockBoundaryMatchingCountsOffset__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHBlockBoundaryMatchingCountsThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHBlockBoundaryMatchingLowerLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHBlockBoundaryMatchingThresholdPeripheralPixel__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHBlockBoundaryMatchingUpperLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalBlockBoundaryCoordinate__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalBlockBoundaryInitialCoordinateForProjection__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetHorizontalBlockEnlargementScaleForProjection__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetHorizontalMovementValueGain0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalMovementValueGain1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalMovementValueGain2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalMovementValueGain3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalMovementValueGain__Q24chip13DriverChip753UlUcUcUcUc ();
IMPORT int C753SetHorizontalMovementValueNRCoefficient0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalMovementValueNRCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalMovementValueNRCoefficient2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalMovementValueNRCoefficient3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalMovementValueNRCoefficient__Q24chip13DriverChip753UlUcUcUcUc ();
IMPORT int C753SetHorizontalNRCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalNRCoefficient2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetHorizontalRAMPCounterLimitValue__Q24chip13DriverChip753Us ();
IMPORT int C753SetHorizontalSyncSignalAbsenceJudgmentValue__Q24chip13DriverChip753Us ();
IMPORT int C753SetHorizontalSyncSignalPresenceJudgmentValue__Q24chip13DriverChip753Us ();
IMPORT int C753SetHorizontalVerticalNRControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetIPCLKFeedbackDividing__Q24chip13DriverChip753Uc ();
IMPORT int C753SetIPCLKPLLControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetIPCLKReferenceDividing__Q24chip13DriverChip753Uc ();
IMPORT int C753SetIPConversionField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetIPConversionField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetIPConversionField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetIPConversionField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetIPConversionField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetIPConversionField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetIPConversionForcedSyncResetDelay__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetIPConversionMemoryLinefeedWidth__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetIPConversionMovementValueReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetIPConversionOutputPortActiveAreaHorizontalStart__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetIPConversionOutputPortActiveAreaHorizontalWidth__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetIPConversionOutputPortActiveAreaVerticalStart__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetIPConversionOutputPortActiveAreaVerticalWidth__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetIPConversionOutputPortHorizontalSyncCycle__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetIPConversionOutputPortVerticalSyncCycle__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetIPImageAdjustment__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetIPTest__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputCharacteristicsMeasurementThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputComponentInputControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputDigitalInterfaceControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetInputField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetInputField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetInputField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetInputFieldRecognitionControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputFill ();
IMPORT int C753SetInputFill__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetInputFormatControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputHorizontalShrinkCompensation__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputHorizontalShrinkControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputHorizontalShrinkInitialValue__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputHorizontalShrinkScale__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputImageCharacteristicsMeasurementControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputImageControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputMeasurementHorizontalEnd__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputMeasurementHorizontalStart__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputMeasurementVerticalEnd__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputMeasurementVerticalStart__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputPortACTHorizontalStart__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputPortACTHorizontalWidth__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputPortACTVerticalStart__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputPortACTVerticalWidth__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputPortSyncControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputRGBYUVCoefficientBU__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputRGBYUVCoefficientBV__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputRGBYUVCoefficientBY__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputRGBYUVCoefficientGU__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputRGBYUVCoefficientGV__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputRGBYUVCoefficientGY__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputRGBYUVCoefficientRU__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputRGBYUVCoefficientRV__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputRGBYUVCoefficientRY__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInputShrinkCompensationControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputSignalSwap__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputUVLowPassFilterCoefficient__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetInputVerticalShrinkCompensation__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputVerticalShrinkControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputVerticalShrinkInitialValue__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetInputVerticalShrinkScale__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetInterlaceOutputControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetInterruptEnable__Q24chip13DriverChip753Us ();
IMPORT int C753SetInterruptReset__Q24chip13DriverChip753Us ();
IMPORT int C753SetLUTCoefficient__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetLUTWriteAddress__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetLUTWriteEnable__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetLongFramesRegisterBlockBoundaryAutoDetect__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMainControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMemoryControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetMemoryProtect__Q24chip13DriverChip753Us ();
IMPORT int C753SetMemoryReadLinefeedWidth__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMemoryWriteLinefeedWidth__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRBlendCoefficientBias__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRBlendCoefficientGain__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRBlendLowPassFilterHCoefficient0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRBlendLowPassFilterHCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRBlendLowPassFilterHCoefficient2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRBlendLowPassFilterVCoefficient0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRBlendLowPassFilterVCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRBlendLowPassFilterVCoefficient2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRHDirectionCoefficient0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRHDirectionCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRHDirectionCoefficient2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRHDirectionCoefficient3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRHDirectionCoefficient4__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRHDirectionCoefficient5__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRNoiseBias__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRSubtractionBlendCoefficientGain__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThreshold0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThreshold1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThreshold2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThreshold3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThreshold4__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThreshold5__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThreshold6__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThreshold7__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThresholdBias0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThresholdBias1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThresholdBias2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThresholdBias3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThresholdBias4__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThresholdBias5__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThresholdBias6__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRThresholdBias7__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRVDirectionCoefficient0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRVDirectionCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRVDirectionCoefficient2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRVDirectionCoefficient3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRVDirectionCoefficient4__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMosquitoNRVDirectionCoefficient5__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMovementCoefficientNR__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetMovementNRControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOSDACTHorizontalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOSDACTHorizontalWidth__Q24chip13DriverChip753Us ();
IMPORT int C753SetOSDACTVerticalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOSDACTVerticalWidth__Q24chip13DriverChip753Us ();
IMPORT int C753SetOSDControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOSDFillColor__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOSDMemoryLinefeedWidth__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOSDMode__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOSDPenetrationColor__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOSDStartAddress__Q24chip13DriverChip753Ul ();
IMPORT int C753SetOSDWriteInhibitColor__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOutFill ();
IMPORT int C753SetOutputBackground0__Q24chip13DriverChip753Ul ();
IMPORT int C753SetOutputBackground1__Q24chip13DriverChip753Ul ();
IMPORT int C753SetOutputField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetOutputField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetOutputField2MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetOutputField3MemoryReadStartAddress__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetOutputFill__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetOutputHorizontalEdgeEmphasisControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputHorizontalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputHorizontalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputHorizontalEdgeEmphasisOvershootFilterCoefficient__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputHorizontalEdgeEmphasisUndershootFilterCoefficient__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputHorizontalEnlargementControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputHorizontalEnlargementInitialValue__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputHorizontalSync__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputHorizontalZoomScale__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetOutputImageControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPatternBarWidth__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOutputPatternCycle__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPatternSpeed__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOutputPortACTHorizontalStart__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetOutputPortACTHorizontalWidth__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetOutputPortACTVerticalStart__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetOutputPortACTVerticalWidth__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetOutputPortOAOI0HorizontalEnd__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI0HorizontalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI0VerticalEnd__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI0VerticalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI1HorizontalEnd__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI1HorizontalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI1VerticalEnd__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI1VerticalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI2HorizontalEnd__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI2HorizontalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI2VerticalEnd__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI2VerticalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI3HorizontalEnd__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI3HorizontalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI3VerticalEnd__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortOAOI3VerticalStart__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPortSyncControl__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputPostEnlargementHorizontalEdgeAreaSelect__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoefficient__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetOutputPostEnlargementHorizontalEdgeEmphasisControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPostEnlargementVerticalEdgeAreaSelect__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPostEnlargementVerticalEdgeEmphasisCoefficient__Q24chip13DriverChip753UlUl ();
IMPORT int C753SetOutputPostEnlargementVerticalEdgeEmphasisControl2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPostEnlargementVerticalEdgeEmphasisControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputSignalSwap__Q24chip13DriverChip753Uc ();
IMPORT int C753SetOutputVerticalEnlargementControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputVerticalEnlargementInitialValue__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetOutputVerticalSync__Q24chip13DriverChip753Us ();
IMPORT int C753SetOutputVerticalZoomScale__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetOverlayControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetPOCLKControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetPOCLKFeedbackDividing__Q24chip13DriverChip753Uc ();
IMPORT int C753SetPOCLKPLLControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetPOCLKReferenceDividing__Q24chip13DriverChip753Uc ();
IMPORT int C753SetPWMControl0__Q24chip13DriverChip753Us ();
IMPORT int C753SetPWMControl1__Q24chip13DriverChip753Us ();
IMPORT int C753SetPWMControl2__Q24chip13DriverChip753Us ();
IMPORT int C753SetPWMControl3__Q24chip13DriverChip753Us ();
IMPORT int C753SetPaletteAddress__Q24chip13DriverChip753Uc ();
IMPORT int C753SetPaletteData__Q24chip13DriverChip753Uc ();
IMPORT int C753SetPatternGeneratorControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetPulldownAreaWidthSelect__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetPulldownControl1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetPulldownControl2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetPulldownDetectAreaSelect__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetPulldownSequenceThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetRAMPCounterStepSetting__Q24chip13DriverChip753Uc ();
IMPORT int C753SetRegisterValueTransferControl__Q24chip13DriverChip753Us ();
IMPORT int C753SetScalingWidthControl__Q24chip13DriverChip753Uc ();
IMPORT int C753SetTESTAD__Q24chip13DriverChip753Uc ();
IMPORT int C753SetTESTDT__Q24chip13DriverChip753Uc ();
IMPORT int C753SetTemporalNRCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRCoefficient2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRCoefficient3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRCoefficient4__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRCoefficient5__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRCoefficient6__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRCoefficient7__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRCoefficient8__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRControl__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRReadStartAddressSelect__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRThreshold1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRThreshold2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRThreshold3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTemporalNRThreshold4__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetTestG__Q24chip13DriverChip753Uc ();
IMPORT int C753SetVBlockBoundaryMatchingCountsOffset__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVBlockBoundaryMatchingCountsThreshold__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVBlockBoundaryMatchingLowerLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVBlockBoundaryMatchingThresholdPeripheralPixel__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVBlockBoundaryMatchingUpperLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalBlockBoundaryCoordinate__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalBlockBoundaryInitialCoordinateForProjection__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetVerticalBlockEnlargementScaleForProjection__Q24chip13DriverChip753UlUs ();
IMPORT int C753SetVerticalDirectionMAXFilter__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalMovementValueGain0__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalMovementValueGain1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalMovementValueGain2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalMovementValueGain3__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalMovementValueGain__Q24chip13DriverChip753UlUcUcUcUc ();
IMPORT int C753SetVerticalNRCoefficient1__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalNRCoefficient2__Q24chip13DriverChip753UlUc ();
IMPORT int C753SetVerticalRAMPCounterLimitValue__Q24chip13DriverChip753Us ();
IMPORT int C753SetVerticalSyncSignalAbsenceJudgmentValue__Q24chip13DriverChip753Uc ();
IMPORT int C753SetVerticalSyncSignalPresenceJudgmentValue__Q24chip13DriverChip753Uc ();
IMPORT int C753WriteN1BitPixels__Q24chip13DriverChip753UsP10tagRGBQUADPPUcPUc ();
IMPORT int C753WriteN24BitPixels__Q24chip13DriverChip753UsPUc ();
IMPORT int C753WriteN8BitPixels__Q24chip13DriverChip753UsP10tagRGBQUADPUc ();
IMPORT int C753WritePixel__Q24chip13DriverChip753UcUcUcUc ();
IMPORT int C753_Reset ();
IMPORT int C772_Reset ();
IMPORT int CloseBus ();
IMPORT int CpLDDogClose ();
IMPORT int CpLDDogOpen ();
IMPORT int DCACHE_CTRL;
IMPORT int EnableCe ();
IMPORT int FLASH_CalBackTest ();
IMPORT int FPGA_Read__Q24chip7FPGABusUsRUs ();
IMPORT int FPGA_Write__Q24chip7FPGABusUsUs ();
IMPORT int FileSysTest ();
IMPORT int FlashPageRTest ();
IMPORT int FlashPageWTest ();
IMPORT int FlashReadTest ();
IMPORT int FlashTest ();
IMPORT int FlashWriteTest ();
IMPORT int FreeNandFlashBuffer ();
IMPORT int Gbase__9streambuf ();
IMPORT int GetBankRegister__Q24chip13DriverChip772UlRUc ();
IMPORT int GetNandBufLength ();
IMPORT int GetNandFlashBuffer ();
IMPORT int GetRtc ();
IMPORT int GetSi5326Reg ();
IMPORT int I2C_Driver ();
IMPORT int I2C_Read__Q24chip6I2CBusUlUlUcRUc ();
IMPORT int I2C_Write__Q24chip6I2CBusUlUlUcUc ();
IMPORT int I2cClk ();
IMPORT int I2cClkCycles ();
IMPORT int I2cCpldReset ();
IMPORT int I2cData ();
IMPORT int I2cDeviceBusy ();
IMPORT int I2cRead ();
IMPORT int I2cRead1014 ();
IMPORT int I2cReadBit ();
IMPORT int I2cReadByte ();
IMPORT int I2cReadCpld ();
IMPORT int I2cReadSeq ();
IMPORT int I2cReadTest ();
IMPORT int I2cStop ();
IMPORT int I2cWrite ();
IMPORT int I2cWriteBit ();
IMPORT int I2cWriteByte ();
IMPORT int I2cWritePage ();
IMPORT int ICS307_CLK_OP ();
IMPORT int ICS307_Data_OP ();
IMPORT int ICS307_SS_OP ();
IMPORT int ICS307_SendByte ();
IMPORT int ICS307_SendDWORD ();
IMPORT int ICS307_WriteBit ();
IMPORT int ICS307_config ();
IMPORT int ICS307_delay ();
IMPORT int InflateTest ();
IMPORT int IniBlockWrite ();
IMPORT int IniBlockWriteTask ();
IMPORT int InitSi5326 ();
IMPORT int Instance__10MsgHandler ();
IMPORT int Instance__7IServer ();
IMPORT int Instance__Q23ent10EntSetting ();
IMPORT int LedAlarmStateChg ();
IMPORT int LedDrvInit ();
IMPORT int LedRunStateChg ();
IMPORT int LedStateChg ();
IMPORT int LoadFpga_ALTERA ();
IMPORT int LoadFpga_LATTICE ();
IMPORT int NandAddrRead ();
IMPORT int NandAllStateRead ();
IMPORT int NandBlockComp ();
IMPORT int NandBlockCompTask ();
IMPORT int NandBlockStateRead ();
IMPORT int NandFileTableRead ();
IMPORT int NandFileTableWrite ();
IMPORT int NandFileUpgrade ();
IMPORT int NandFlashBlockCmp ();
IMPORT int NandFlashTest ();
IMPORT int NandLowFormat ();
IMPORT int NandTestCheck ();
IMPORT int Nbase__9streambuf ();
IMPORT int OpenBus ();
IMPORT int PhyBlockCheck ();
IMPORT int PhyBlockErase ();
IMPORT int PhyBlockRead ();
IMPORT int PhyBlockWrite ();
IMPORT int PhyDelay ();
IMPORT int PhyGetStatus ();
IMPORT int PhyPageRead ();
IMPORT int PhyPageWrite ();
IMPORT int PhyPageWriteTest ();
IMPORT int PinAClk ();
IMPORT int PinACs ();
IMPORT int PinADo ();
IMPORT int PrintTableBlock ();
IMPORT int Qbox_app_entry ();
IMPORT int ReadLM73 ();
IMPORT int ReadReg ();
IMPORT int ReleaseNandFlashBuffer ();
IMPORT int ResetFpga_ALTERA ();
IMPORT int ResetFpga_LATTICE ();
IMPORT int SPIFlashEnable ();
IMPORT int SPI_Read__Q24chip6SPIBusUlUcRUc ();
IMPORT int SPI_Write__Q24chip6SPIBusUlUcUc ();
IMPORT int SectorErase ();
IMPORT int SendNetMsg__7IServeriPcUl ();
IMPORT int Server_SM;
IMPORT int Server__7IServer ();
IMPORT int SetBankRegister__Q24chip13DriverChip772UlUc ();
IMPORT int SetRtc ();
IMPORT int SetSi5326Reg ();
IMPORT int Spi0Test ();
IMPORT int Spi0Test3 ();
IMPORT int SpiCS_OFF ();
IMPORT int SpiCS_ON ();
IMPORT int SpiFlashWrite ();
IMPORT int SpiRead ();
IMPORT int SpiReadBit ();
IMPORT int SpiReadByte ();
IMPORT int SpiWrite ();
IMPORT int SpiWriteBit ();
IMPORT int SpiWriteByte ();
IMPORT int Spi_753_Read ();
IMPORT int Spi_753_Read1 ();
IMPORT int Spi_753_Write ();
IMPORT int Spi_753_Write1 ();
IMPORT int Spi_753_test1 ();
IMPORT int Spi_C753_Bank_get ();
IMPORT int Spi_C753_Bank_set ();
IMPORT int Spi_C753_OFF ();
IMPORT int Spi_C753_ON ();
IMPORT int Spi_C753_Read ();
IMPORT int Spi_C753_Write ();
IMPORT int Spi_C772_Bank_get ();
IMPORT int Spi_C772_Bank_set ();
IMPORT int Spi_C772_OFF ();
IMPORT int Spi_C772_ON ();
IMPORT int Spi_C772_Read ();
IMPORT int Spi_C772_Read1 ();
IMPORT int Spi_C772_Write ();
IMPORT int Spi_C772_Write1 ();
IMPORT int Spi_C772_test1 ();
IMPORT int Spi_FPGA_OFF ();
IMPORT int Spi_FPGA_ON ();
IMPORT int Spi_FPGA_Read ();
IMPORT int Spi_FPGA_Write ();
IMPORT int Spi_PP ();
IMPORT int Spi_Read ();
IMPORT int Spi_Test ();
IMPORT int Spi_Write ();
IMPORT int TempTest ();
IMPORT int TestBspTimer ();
IMPORT int TestCpld ();
IMPORT int TestLm73 ();
IMPORT int UnpackMsg__7MsgBaseR7MsgInfo ();
IMPORT int UrgencyJobAdd ();
IMPORT int UrgencyJobAlloc ();
IMPORT int UrgencyLibInit ();
IMPORT int UrgencyShow ();
IMPORT int UrgencyStart ();
IMPORT int UrgencyStop ();
IMPORT int UrgencyTask ();
IMPORT int Wait_For_SPIF ();
IMPORT int Wait_For_WEL ();
IMPORT int WriteLM73 ();
IMPORT int WriteReg ();
IMPORT int _$_10MsgHandler ();
IMPORT int _$_10bad_typeid ();
IMPORT int _$_11logic_error ();
IMPORT int _$_11range_error ();
IMPORT int _$_12domain_error ();
IMPORT int _$_12length_error ();
IMPORT int _$_12out_of_range ();
IMPORT int _$_12streammarker ();
IMPORT int _$_13bad_exception ();
IMPORT int _$_13runtime_error ();
IMPORT int _$_14__si_type_info ();
IMPORT int _$_14overflow_error ();
IMPORT int _$_15underflow_error ();
IMPORT int _$_16__user_type_info ();
IMPORT int _$_16invalid_argument ();
IMPORT int _$_17__class_type_info ();
IMPORT int _$_22_IO_istream_withassign ();
IMPORT int _$_22_IO_ostream_withassign ();
IMPORT int _$_3ios ();
IMPORT int _$_7IServer ();
IMPORT int _$_7MsgBase ();
IMPORT int _$_7filebuf ();
IMPORT int _$_7istream ();
IMPORT int _$_7ostream ();
IMPORT int _$_8bad_cast ();
IMPORT int _$_8iostream ();
IMPORT int _$_9CommModel ();
IMPORT int _$_9bad_alloc ();
IMPORT int _$_9exception ();
IMPORT int _$_9streambuf ();
IMPORT int _$_9type_info ();
IMPORT int _$_Q23ent10EntSetting ();
IMPORT int _$_Q23msg13TaskCheckFPGA ();
IMPORT int _$_Q23msg5Event ();
IMPORT int _$_Q23msg6BGTest ();
IMPORT int _$_Q23msg6Status ();
IMPORT int _$_Q23msg7Channel ();
IMPORT int _$_Q23msg7Windows ();
IMPORT int _$_Q23msg9BusDriver ();
IMPORT int _$_Q24chip13DriverChip753 ();
IMPORT int _$_Q24chip13DriverChip772 ();
IMPORT int _$_Q24chip14DriverChip5160 ();
IMPORT int _$_Q24chip14DriverChipFPGA ();
IMPORT int _$_Q24chip15DriverChip9388A ();
IMPORT int _$_Q24chip16DriverChipICS307 ();
IMPORT int _$_Q24chip6I2CBus ();
IMPORT int _$_Q24chip6SPIBus ();
IMPORT int _$_Q24chip7FPGABus ();
IMPORT int _$_Q27chipApp8AppScale ();
IMPORT int _$_Q2t24__default_alloc_template2b1i05_Lock ();
IMPORT int _$_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int _10MsgHandler$m_instance;
IMPORT int _7IServer$m_instance;
IMPORT int _7filebuf$openprot ();
IMPORT int _GLOBAL_$D$_10MsgHandler$m_instance ();
IMPORT int _GLOBAL_$D$_7IServer$m_instance ();
IMPORT int _GLOBAL_$D$_IO_stdin_ ();
IMPORT int _GLOBAL_$D$_Q23ent10EntSetting$m_instance ();
IMPORT int _GLOBAL_$D$__7MsgBase ();
IMPORT int _GLOBAL_$D$__9CommModel ();
IMPORT int _GLOBAL_$D$__Q23msg13TaskCheckFPGA ();
IMPORT int _GLOBAL_$D$__Q23msg5Event ();
IMPORT int _GLOBAL_$D$__Q23msg6BGTest ();
IMPORT int _GLOBAL_$D$__Q23msg6Status ();
IMPORT int _GLOBAL_$D$__Q23msg7Channel ();
IMPORT int _GLOBAL_$D$__Q23msg7Windows ();
IMPORT int _GLOBAL_$D$__Q23msg9BusDriver ();
IMPORT int _GLOBAL_$D$__Q24chip13DriverChip772 ();
IMPORT int _GLOBAL_$D$__Q24chip14DriverChip5160 ();
IMPORT int _GLOBAL_$D$__Q24chip6I2CBus ();
IMPORT int _GLOBAL_$D$__Q27chipApp8AppScale ();
IMPORT int _GLOBAL_$D$_t24__default_alloc_template2b1i0$_S_end_free ();
IMPORT int _GLOBAL_$D$_un_link__9streambuf ();
IMPORT int _GLOBAL_$D$testMenu ();
IMPORT int _GLOBAL_$I$_10MsgHandler$m_instance ();
IMPORT int _GLOBAL_$I$_7IServer$m_instance ();
IMPORT int _GLOBAL_$I$_IO_stdin_ ();
IMPORT int _GLOBAL_$I$_Q23ent10EntSetting$m_instance ();
IMPORT int _GLOBAL_$I$__7MsgBase ();
IMPORT int _GLOBAL_$I$__9CommModel ();
IMPORT int _GLOBAL_$I$__Q23msg13TaskCheckFPGA ();
IMPORT int _GLOBAL_$I$__Q23msg5Event ();
IMPORT int _GLOBAL_$I$__Q23msg6BGTest ();
IMPORT int _GLOBAL_$I$__Q23msg6Status ();
IMPORT int _GLOBAL_$I$__Q23msg7Channel ();
IMPORT int _GLOBAL_$I$__Q23msg7Windows ();
IMPORT int _GLOBAL_$I$__Q23msg9BusDriver ();
IMPORT int _GLOBAL_$I$__Q24chip13DriverChip772 ();
IMPORT int _GLOBAL_$I$__Q24chip14DriverChip5160 ();
IMPORT int _GLOBAL_$I$__Q24chip6I2CBus ();
IMPORT int _GLOBAL_$I$__Q27chipApp8AppScale ();
IMPORT int _GLOBAL_$I$_t24__default_alloc_template2b1i0$_S_end_free ();
IMPORT int _GLOBAL_$I$_un_link__9streambuf ();
IMPORT int _GLOBAL_$I$testMenu ();
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
IMPORT int _Q23ent10EntSetting$m_instance;
IMPORT int _Randseed;
IMPORT int _S_chunk_alloc__t24__default_alloc_template2b1i0UlRi ();
IMPORT int _S_freelist_index__t24__default_alloc_template2b1i0Ul ();
IMPORT int _S_oom_malloc__t23__malloc_alloc_template1i0Ul ();
IMPORT int _S_oom_realloc__t23__malloc_alloc_template1i0PvUl ();
IMPORT int _S_refill__t24__default_alloc_template2b1i0Ul ();
IMPORT int _S_round_up__t24__default_alloc_template2b1i0Ul ();
IMPORT int __10MsgHandler ();
IMPORT int __10bad_typeid ();
IMPORT int __11logic_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __11range_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __12domain_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __12length_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __12out_of_rangeRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __12streammarkerP9streambuf ();
IMPORT int __13bad_exception ();
IMPORT int __13runtime_error ();
IMPORT int __13runtime_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __14__si_type_infoPCcRC16__user_type_info ();
IMPORT int __14overflow_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __15underflow_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __16__user_type_infoPCc ();
IMPORT int __16invalid_argumentRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __17__class_type_infoPCcPCQ217__class_type_info9base_infoUl ();
IMPORT int __3iosP9streambufP7ostream ();
IMPORT int __7IServer ();
IMPORT int __7MsgBase ();
IMPORT int __7filebuf ();
IMPORT int __7filebufi ();
IMPORT int __7filebufiPci ();
IMPORT int __7istreami ();
IMPORT int __7istreamiP9streambufP7ostream ();
IMPORT int __7ostreami ();
IMPORT int __7ostreamiP9streambufP7ostream ();
IMPORT int __8bad_cast ();
IMPORT int __8iostreami ();
IMPORT int __8iostreamiP9streambufP7ostream ();
IMPORT int __9CommModel ();
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
IMPORT int __Q23ent10EntSetting ();
IMPORT int __Q23ios4Init ();
IMPORT int __Q23msg13TaskCheckFPGA ();
IMPORT int __Q23msg5Event ();
IMPORT int __Q23msg6BGTest ();
IMPORT int __Q23msg6Status ();
IMPORT int __Q23msg7Channel ();
IMPORT int __Q23msg7Windows ();
IMPORT int __Q23msg9BusDriver ();
IMPORT int __Q24chip13DriverChip753 ();
IMPORT int __Q24chip13DriverChip772 ();
IMPORT int __Q24chip14DriverChip5160 ();
IMPORT int __Q24chip14DriverChipFPGA ();
IMPORT int __Q24chip15DriverChip9388A ();
IMPORT int __Q24chip16DriverChipICS307 ();
IMPORT int __Q24chip6I2CBus ();
IMPORT int __Q24chip6SPIBus ();
IMPORT int __Q24chip7FPGABus ();
IMPORT int __Q27chipApp8AppScale ();
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
IMPORT int ___x_gnu_cstrmain_o;
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
IMPORT int ___x_gnu_opdel_o;
IMPORT int ___x_gnu_opnew_o;
IMPORT int ___x_gnu_opvdel_o;
IMPORT int ___x_gnu_opvnew_o;
IMPORT int ___x_gnu_outfloat_o;
IMPORT int ___x_gnu_peekc_o;
IMPORT int ___x_gnu_sbscan_o;
IMPORT int ___x_gnu_stdexcepti_o;
IMPORT int ___x_gnu_stdstrbufs_o;
IMPORT int ___x_gnu_stdstreams_o;
IMPORT int ___x_gnu_stlinst_o;
IMPORT int ___x_gnu_streambuf_o;
IMPORT int ___x_gnu_tinfo2_o;
IMPORT int ___x_gnu_tinfo_o;
IMPORT int __add64 ();
IMPORT int __adddf3 ();
IMPORT int __addsf3 ();
IMPORT int __apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc ();
IMPORT int __apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c ();
IMPORT int __arm_call_via_o;
IMPORT int __as__22_IO_istream_withassignR22_IO_istream_withassign ();
IMPORT int __as__22_IO_istream_withassignR7istream ();
IMPORT int __as__22_IO_ostream_withassignR22_IO_ostream_withassign ();
IMPORT int __as__22_IO_ostream_withassignR7ostream ();
IMPORT int __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc ();
IMPORT int __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c ();
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
IMPORT int __dl__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepPv ();
IMPORT int __dunder ();
IMPORT int __dunder_d ();
IMPORT int __dynamic_cast ();
IMPORT int __dynamic_cast_2 ();
IMPORT int __eh_alloc ();
IMPORT int __eh_free ();
IMPORT int __eh_rtime_match ();
IMPORT int __empty ();
IMPORT int __eq64 ();
IMPORT int __eq__C9type_infoRC9type_info ();
IMPORT int __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b ();
IMPORT int __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b ();
IMPORT int __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b ();
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
IMPORT int __ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b ();
IMPORT int __ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b ();
IMPORT int __ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b ();
IMPORT int __gedf2 ();
IMPORT int __gesf2 ();
IMPORT int __getDstInfo ();
IMPORT int __getTime ();
IMPORT int __getZoneInfo ();
IMPORT int __get_dynamic_handler_chain ();
IMPORT int __get_eh_context ();
IMPORT int __get_eh_info ();
IMPORT int __gt64 ();
IMPORT int __gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b ();
IMPORT int __gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b ();
IMPORT int __gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b ();
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
IMPORT int __le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b ();
IMPORT int __le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b ();
IMPORT int __le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b ();
IMPORT int __ledf2 ();
IMPORT int __length_error__FPCc ();
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
IMPORT int __lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b ();
IMPORT int __lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b ();
IMPORT int __lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b ();
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
IMPORT int __ne__C9type_infoRC9type_info ();
IMPORT int __ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b ();
IMPORT int __ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b ();
IMPORT int __ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b ();
IMPORT int __nedf2 ();
IMPORT int __negdf2 ();
IMPORT int __negdi2 ();
IMPORT int __negsf2 ();
IMPORT int __nesf2 ();
IMPORT int __new_handler;
IMPORT int __nt__C3ios ();
IMPORT int __nw__FUlPv ();
IMPORT int __nw__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlUl ();
IMPORT int __opPv__C3ios ();
IMPORT int __out_of_range__FPCc ();
IMPORT int __overflow ();
IMPORT int __overflow__FP9streambufi ();
IMPORT int __pack_d ();
IMPORT int __pack_f ();
IMPORT int __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_t12basic_string3ZX01ZX11ZX21 ();
IMPORT int __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_t12basic_string3ZX01ZX11ZX21 ();
IMPORT int __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_t12basic_string3ZX01ZX11ZX21 ();
IMPORT int __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21X01_t12basic_string3ZX01ZX11ZX21 ();
IMPORT int __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_X01RCt12basic_string3ZX01ZX11ZX21_t12basic_string3ZX01ZX11ZX21 ();
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
IMPORT int __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc ();
IMPORT int __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl ();
IMPORT int __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc ();
IMPORT int __terminate ();
IMPORT int __terminate_func;
IMPORT int __tf10MsgHandler ();
IMPORT int __tf10bad_typeid ();
IMPORT int __tf11logic_error ();
IMPORT int __tf11range_error ();
IMPORT int __tf12domain_error ();
IMPORT int __tf12length_error ();
IMPORT int __tf12out_of_range ();
IMPORT int __tf13bad_exception ();
IMPORT int __tf13runtime_error ();
IMPORT int __tf14__si_type_info ();
IMPORT int __tf14overflow_error ();
IMPORT int __tf15underflow_error ();
IMPORT int __tf16__user_type_info ();
IMPORT int __tf16invalid_argument ();
IMPORT int __tf17__class_type_info ();
IMPORT int __tf22_IO_istream_withassign ();
IMPORT int __tf22_IO_ostream_withassign ();
IMPORT int __tf3ios ();
IMPORT int __tf7IServer ();
IMPORT int __tf7MsgBase ();
IMPORT int __tf7filebuf ();
IMPORT int __tf7istream ();
IMPORT int __tf7ostream ();
IMPORT int __tf8bad_cast ();
IMPORT int __tf8iostream ();
IMPORT int __tf9CommModel ();
IMPORT int __tf9bad_alloc ();
IMPORT int __tf9exception ();
IMPORT int __tf9streambuf ();
IMPORT int __tf9type_info ();
IMPORT int __tfQ23ent10EntSetting ();
IMPORT int __tfQ23msg13TaskCheckFPGA ();
IMPORT int __tfQ23msg5Event ();
IMPORT int __tfQ23msg6BGTest ();
IMPORT int __tfQ23msg6Status ();
IMPORT int __tfQ23msg7Channel ();
IMPORT int __tfQ23msg7Windows ();
IMPORT int __tfQ23msg9BusDriver ();
IMPORT int __tfQ24chip13DriverChip753 ();
IMPORT int __tfQ24chip13DriverChip772 ();
IMPORT int __tfQ24chip14DriverChip5160 ();
IMPORT int __tfQ24chip14DriverChipFPGA ();
IMPORT int __tfQ24chip15DriverChip9388A ();
IMPORT int __tfQ24chip16DriverChipICS307 ();
IMPORT int __tfQ24chip6I2CBus ();
IMPORT int __tfQ24chip6SPIBus ();
IMPORT int __tfQ24chip7FPGABus ();
IMPORT int __tfQ27chipApp8AppScale ();
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
IMPORT int __ti10MsgHandler;
IMPORT int __ti10bad_typeid;
IMPORT int __ti11_ios_fields;
IMPORT int __ti11logic_error;
IMPORT int __ti11range_error;
IMPORT int __ti12domain_error;
IMPORT int __ti12length_error;
IMPORT int __ti12out_of_range;
IMPORT int __ti13bad_exception;
IMPORT int __ti13ostringstream;
IMPORT int __ti13runtime_error;
IMPORT int __ti14__si_type_info;
IMPORT int __ti14overflow_error;
IMPORT int __ti15ModuleInterface;
IMPORT int __ti15underflow_error;
IMPORT int __ti16__attr_type_info;
IMPORT int __ti16__func_type_info;
IMPORT int __ti16__ptmd_type_info;
IMPORT int __ti16__ptmf_type_info;
IMPORT int __ti16__user_type_info;
IMPORT int __ti16invalid_argument;
IMPORT int __ti16stringstreambase;
IMPORT int __ti17__array_type_info;
IMPORT int __ti17__class_type_info;
IMPORT int __ti19__builtin_type_info;
IMPORT int __ti19__pointer_type_info;
IMPORT int __ti22_IO_istream_withassign;
IMPORT int __ti22_IO_ostream_withassign;
IMPORT int __ti3ios;
IMPORT int __ti7IServer;
IMPORT int __ti7MsgBase;
IMPORT int __ti7filebuf;
IMPORT int __ti7istream;
IMPORT int __ti7ostream;
IMPORT int __ti8_IO_FILE;
IMPORT int __ti8bad_cast;
IMPORT int __ti8iostream;
IMPORT int __ti9CommModel;
IMPORT int __ti9bad_alloc;
IMPORT int __ti9exception;
IMPORT int __ti9streambuf;
IMPORT int __ti9stringbuf;
IMPORT int __ti9type_info;
IMPORT int __tiQ23ent10EntSetting;
IMPORT int __tiQ23msg13TaskCheckFPGA;
IMPORT int __tiQ23msg5Event;
IMPORT int __tiQ23msg6BGTest;
IMPORT int __tiQ23msg6Status;
IMPORT int __tiQ23msg7Channel;
IMPORT int __tiQ23msg7Windows;
IMPORT int __tiQ23msg9BusDriver;
IMPORT int __tiQ24chip13DriverChip753;
IMPORT int __tiQ24chip13DriverChip772;
IMPORT int __tiQ24chip14DriverChip5160;
IMPORT int __tiQ24chip14DriverChipFPGA;
IMPORT int __tiQ24chip15DriverChip9388A;
IMPORT int __tiQ24chip16DriverChipICS307;
IMPORT int __tiQ24chip6I2CBus;
IMPORT int __tiQ24chip6SPIBus;
IMPORT int __tiQ24chip7FPGABus;
IMPORT int __tiQ27chipApp8AppScale;
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
IMPORT int __vc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int __vc__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl ();
IMPORT int __vc__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
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
IMPORT int _find__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCccUlUl ();
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
IMPORT int _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0$nilRep;
IMPORT int _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0$npos ();
IMPORT int _t23__malloc_alloc_template1i0$__malloc_alloc_oom_handler;
IMPORT int _t24__default_alloc_template2b1i0$_S_end_free;
IMPORT int _t24__default_alloc_template2b1i0$_S_free_list;
IMPORT int _t24__default_alloc_template2b1i0$_S_heap_size;
IMPORT int _t24__default_alloc_template2b1i0$_S_node_allocator_lock;
IMPORT int _t24__default_alloc_template2b1i0$_S_start_free;
IMPORT int _throw_failure__C3ios ();
IMPORT int _un_link__9streambuf ();
IMPORT int _vt$10MsgHandler ();
IMPORT int _vt$10bad_typeid ();
IMPORT int _vt$11logic_error ();
IMPORT int _vt$11range_error ();
IMPORT int _vt$12domain_error ();
IMPORT int _vt$12length_error ();
IMPORT int _vt$12out_of_range ();
IMPORT int _vt$13bad_exception ();
IMPORT int _vt$13runtime_error ();
IMPORT int _vt$14__si_type_info ();
IMPORT int _vt$14overflow_error ();
IMPORT int _vt$15underflow_error ();
IMPORT int _vt$16__user_type_info ();
IMPORT int _vt$16invalid_argument ();
IMPORT int _vt$17__class_type_info ();
IMPORT int _vt$22_IO_istream_withassign$3ios ();
IMPORT int _vt$22_IO_ostream_withassign$3ios ();
IMPORT int _vt$3ios ();
IMPORT int _vt$7IServer ();
IMPORT int _vt$7MsgBase ();
IMPORT int _vt$7filebuf ();
IMPORT int _vt$7istream$3ios ();
IMPORT int _vt$7ostream$3ios ();
IMPORT int _vt$8bad_cast ();
IMPORT int _vt$8iostream$3ios ();
IMPORT int _vt$9CommModel ();
IMPORT int _vt$9CommModel$15ModuleInterface ();
IMPORT int _vt$9bad_alloc ();
IMPORT int _vt$9exception ();
IMPORT int _vt$9streambuf ();
IMPORT int _vt$9type_info ();
IMPORT int _vt$Q23ent10EntSetting ();
IMPORT int _vt$Q23msg13TaskCheckFPGA ();
IMPORT int _vt$Q23msg13TaskCheckFPGA$15ModuleInterface ();
IMPORT int _vt$Q23msg5Event ();
IMPORT int _vt$Q23msg5Event$15ModuleInterface ();
IMPORT int _vt$Q23msg6BGTest ();
IMPORT int _vt$Q23msg6BGTest$15ModuleInterface ();
IMPORT int _vt$Q23msg6Status ();
IMPORT int _vt$Q23msg6Status$15ModuleInterface ();
IMPORT int _vt$Q23msg7Channel ();
IMPORT int _vt$Q23msg7Channel$15ModuleInterface ();
IMPORT int _vt$Q23msg7Windows ();
IMPORT int _vt$Q23msg7Windows$15ModuleInterface ();
IMPORT int _vt$Q23msg9BusDriver ();
IMPORT int _vt$Q23msg9BusDriver$15ModuleInterface ();
IMPORT int _vt$Q23msg9BusDriver$Q24chip6I2CBus ();
IMPORT int _vt$Q23msg9BusDriver$Q24chip6SPIBus ();
IMPORT int _vt$Q24chip13DriverChip753 ();
IMPORT int _vt$Q24chip13DriverChip772 ();
IMPORT int _vt$Q24chip14DriverChip5160 ();
IMPORT int _vt$Q24chip14DriverChipFPGA ();
IMPORT int _vt$Q24chip15DriverChip9388A ();
IMPORT int _vt$Q24chip16DriverChipICS307 ();
IMPORT int _vt$Q24chip6I2CBus ();
IMPORT int _vt$Q24chip6SPIBus ();
IMPORT int _vt$Q24chip7FPGABus ();
IMPORT int _vt$Q27chipApp8AppScale ();
IMPORT int _vt$Q27chipApp8AppScale$Q24chip16DriverChipICS307 ();
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
IMPORT int alloc__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulb ();
IMPORT int allocate__9streambuf ();
IMPORT int allocate__t23__malloc_alloc_template1i0Ul ();
IMPORT int allocate__t24__default_alloc_template2b1i0Ul ();
IMPORT int allocbuf__9streambuf ();
IMPORT int append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc ();
IMPORT int append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl ();
IMPORT int append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc ();
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
IMPORT int assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc ();
IMPORT int assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl ();
IMPORT int assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc ();
IMPORT int assign__t18string_char_traits1ZcRcRCc ();
IMPORT int at91EthFlagsSet ();
IMPORT int at91EthInit ();
IMPORT int at91EthLoopSet ();
IMPORT int at91EthMCastAdd ();
IMPORT int at91EthMCastDel ();
IMPORT int at91EthMiiShow ();
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
IMPORT int at91IntDevInit ();
IMPORT int at91SioDevInit ();
IMPORT int at91SioDevInit2 ();
IMPORT int at91SioInt ();
IMPORT int at__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int at__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
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
IMPORT int begin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int begin__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int broadcastMsg__10MsgHandlerP7MsgInfo ();
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
IMPORT int c_str__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int calculate6SymbolLUT__Q27chipApp8AppScalePfT1PUc ();
IMPORT int calloc ();
IMPORT int capacity__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int check_realloc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int check_trailer ();
IMPORT int checksum ();
IMPORT int chipGetFPGATest ();
IMPORT int chipSetFPGATest ();
IMPORT int chipTest__Q27chipApp8AppScale ();
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
IMPORT int clone__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep ();
IMPORT int close ();
IMPORT int close__3ios ();
IMPORT int close__7filebuf ();
IMPORT int closedir ();
IMPORT int compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl ();
IMPORT int compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl ();
IMPORT int compare__t18string_char_traits1ZcPCcT1Ul ();
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
IMPORT int copy__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUlUl ();
IMPORT int copy__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlPCcUl ();
IMPORT int copy__t18string_char_traits1ZcPcPCcUl ();
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
IMPORT int createWindow__Q23ent10EntSettingUlUlUlUl ();
IMPORT int create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl ();
IMPORT int creationDate;
IMPORT int cret ();
IMPORT int ctime ();
IMPORT int ctime_r ();
IMPORT int cur_ptr__7filebuf ();
IMPORT int currentContext;
IMPORT int current_demangling_style;
IMPORT int d ();
IMPORT int data__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int data__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep ();
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
IMPORT int delWindow__Q23ent10EntSettingUl ();
IMPORT int delayNSec ();
IMPORT int delayUSec ();
IMPORT int delta__12streammarker ();
IMPORT int delta__12streammarkerR12streammarker ();
IMPORT int demo ();
IMPORT int demoMove ();
IMPORT int devSplit ();
IMPORT int dev_5160_DetectInputSignal__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetAcutance__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetAutoGainFlg__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetBrightness__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetColorPhasic__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetColorScope__Q24chip14DriverChip5160UlRUcT2 ();
IMPORT int dev_5160_GetContrast__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetInputType__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetManualGainValue__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetSaturation__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetSignalMode__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_GetVsFreq__Q24chip14DriverChip5160UlRUc ();
IMPORT int dev_5160_InitTVP5160__Q24chip14DriverChip5160Ul ();
IMPORT int dev_5160_SetAcutance__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_5160_SetAutoGainFlg__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_5160_SetBrightness__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_5160_SetColorPhasic__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_5160_SetColorScope__Q24chip14DriverChip5160UlUcUc ();
IMPORT int dev_5160_SetContrast__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_5160_SetInputType__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_5160_SetManualGainValue__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_5160_SetSaturation__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_5160_SetSignalMode__Q24chip14DriverChip5160UlUc ();
IMPORT int dev_ARGB_DetectInput__Q24chip15DriverChip9388AUlRUc ();
IMPORT int dev_ARGB_GeneralConfig__Q24chip15DriverChip9388AUl ();
IMPORT int dev_ARGB_GetPhase__Q24chip15DriverChip9388AUlRUc ();
IMPORT int dev_ARGB_GetSTDI__Q24chip15DriverChip9388AUlRUsN32 ();
IMPORT int dev_ARGB_PLLVocManEn__Q24chip15DriverChip9388AUlUc ();
IMPORT int dev_ARGB_Polarity__Q24chip15DriverChip9388AUlRUcT2 ();
IMPORT int dev_ARGB_SetFRLCountMax__Q24chip15DriverChip9388AUlUs ();
IMPORT int dev_ARGB_SetFRLL__Q24chip15DriverChip9388AUlUs ();
IMPORT int dev_ARGB_SetPhase__Q24chip15DriverChip9388AUlUc ();
IMPORT int dev_ARGB_SetPllDivRatio__Q24chip15DriverChip9388AUlUs ();
IMPORT int dev_ARGB_SetSavEav__Q24chip15DriverChip9388AUlUsUsUsUs ();
IMPORT int dev_ARGB_SetVCORange__Q24chip15DriverChip9388AUlUl ();
IMPORT int dev_C772_ChangeModel__Q24chip13DriverChip772UlUl ();
IMPORT int dev_C772_InitColorConversion__Q24chip13DriverChip772Ul ();
IMPORT int dev_C772_InitIPConversion__Q24chip13DriverChip772Ul ();
IMPORT int dev_C772_InitLUT__Q24chip13DriverChip772Ul ();
IMPORT int dev_C772_Reset__Q24chip13DriverChip772Ul ();
IMPORT int dev_C772_Set480__Q24chip13DriverChip772Ul ();
IMPORT int dev_C772_Set576__Q24chip13DriverChip772Ul ();
IMPORT int dev_C772_SetBlueScreen__Q24chip13DriverChip772UlUl ();
IMPORT int dev_C772_SetHorAndVerSyncCtrl__Q24chip13DriverChip772UlUlUlUlUl ();
IMPORT int dev_C772_SetInputSize__Q24chip13DriverChip772UlUlUlUlUl ();
IMPORT int dev_C772_SetOutputSize__Q24chip13DriverChip772UlUlUlUlUl ();
IMPORT int dev_C772_SetOutputSyncCycle__Q24chip13DriverChip772UlUlUl ();
IMPORT int dev_DRGB_DetectInput__Q24chip15DriverChip9388AUlRUc ();
IMPORT int dev_DRGB_GeneralConfig__Q24chip15DriverChip9388AUl ();
IMPORT int dev_DRGB_GetSignalPara__Q24chip15DriverChip9388AUlRUcRUsN23 ();
IMPORT int dev_DetectCPRun__Q24chip15DriverChip9388AUlRUc ();
IMPORT int dev_FPGA_Read ();
IMPORT int dev_FPGA_Write ();
IMPORT int dev_I2C_Read ();
IMPORT int dev_I2C_Write ();
IMPORT int dev_I2C_WriteMult__Q24chip6I2CBusUlUlGt4list2Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUcZt9allocator1Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUc ();
IMPORT int dev_I2cInit ();
IMPORT int dev_InitAD9388A__Q24chip15DriverChip9388AUl ();
IMPORT int dev_InitIP00c772__Q24chip13DriverChip772Ul ();
IMPORT int dev_RGB_GetBrightness__Q24chip15DriverChip9388AUlRUc ();
IMPORT int dev_RGB_GetColorPhase__Q24chip15DriverChip9388AUlRUc ();
IMPORT int dev_RGB_GetContrast__Q24chip15DriverChip9388AUlRUc ();
IMPORT int dev_RGB_GetSaturation__Q24chip15DriverChip9388AUlRUc ();
IMPORT int dev_RGB_SetBrightness__Q24chip15DriverChip9388AUlUc ();
IMPORT int dev_RGB_SetColorPhase__Q24chip15DriverChip9388AUlUc ();
IMPORT int dev_RGB_SetContrast__Q24chip15DriverChip9388AUlUc ();
IMPORT int dev_RGB_SetSaturation__Q24chip15DriverChip9388AUlUc ();
IMPORT int dev_SPI_Read ();
IMPORT int dev_SPI_Write ();
IMPORT int dev_SPI_WriteMult__Q24chip6SPIBusUlGt4list2Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUcZt9allocator1Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUc ();
IMPORT int dev_SpiCsOff ();
IMPORT int dev_SpiCsOn ();
IMPORT int dev_SpiInit ();
IMPORT int dev_spi_test ();
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
IMPORT int downloadBootrom ();
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
IMPORT int empty__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int end__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int end__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int endl__FR7ostream ();
IMPORT int ends__FR7ostream ();
IMPORT int envLibInit ();
IMPORT int envPrivateCreate ();
IMPORT int envPrivateDestroy ();
IMPORT int envShow ();
IMPORT int eof__C3ios ();
IMPORT int eos__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int eos__t18string_char_traits1Zc ();
IMPORT int epptr__C9streambuf ();
IMPORT int eq__t18string_char_traits1ZcRCcT1 ();
IMPORT int erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pc ();
IMPORT int erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1 ();
IMPORT int erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl ();
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
IMPORT int excess_slop__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlUl ();
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
IMPORT int find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl ();
IMPORT int find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl ();
IMPORT int find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl ();
IMPORT int find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl ();
IMPORT int find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl ();
IMPORT int find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl ();
IMPORT int find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl ();
IMPORT int find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl ();
IMPORT int find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl ();
IMPORT int find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl ();
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
IMPORT int flashreset ();
IMPORT int flashtest ();
IMPORT int flashwrite ();
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
IMPORT int frob_size__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl ();
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
IMPORT int gbump__9streambufi ();
IMPORT int gcount__7istream ();
IMPORT int get753 ();
IMPORT int getBL__Q24chip15DriverChip9388AUlRUs ();
IMPORT int getBoardTypeReg__Q24chip14DriverChipFPGARUs ();
IMPORT int getC753ChnInput ();
IMPORT int getDateReg__Q24chip14DriverChipFPGARUs ();
IMPORT int getF0H__Q24chip15DriverChip9388AUlRUs ();
IMPORT int getF1H__Q24chip15DriverChip9388AUlRUs ();
IMPORT int getFL__Q24chip15DriverChip9388AUlRUs ();
IMPORT int getHorizontalCompensation__Q27chipApp8AppScaleUsUsUc ();
IMPORT int getHorizontalStart__Q27chipApp8AppScaleUsUsUc ();
IMPORT int getHorizontalTotal__Q27chipApp8AppScaleUsUsUs ();
IMPORT int getHsPol__Q24chip15DriverChip9388AUlRUc ();
IMPORT int getInputInfoFlg__Q23ent10EntSettingUl ();
IMPORT int getInputInfoSize__Q23ent10EntSettingUlRUlT2 ();
IMPORT int getInputInfoType__Q23ent10EntSettingUl ();
IMPORT int getInputInfo__Q24chip14DriverChipFPGAUlRQ24chip10InputInfoT ();
IMPORT int getInputTotal__Q23ent10EntSetting ();
IMPORT int getInput__Q23ent10EntSettingUlRUl ();
IMPORT int getLayer__Q23ent10EntSettingUlRUl ();
IMPORT int getLineWidth__Q24chip15DriverChip9388AUlRUs ();
IMPORT int getModule__10MsgHandlerUl ();
IMPORT int getOutputInfoFlg__Q23ent10EntSettingUl ();
IMPORT int getOutputInfoSize__Q23ent10EntSettingUlRUlT2 ();
IMPORT int getOutputInfoType__Q23ent10EntSettingUl ();
IMPORT int getOutputTotal__Q23ent10EntSetting ();
IMPORT int getOutput__Q23ent10EntSettingUlRUl ();
IMPORT int getSCF__Q24chip15DriverChip9388AUlRUs ();
IMPORT int getSCVS__Q24chip15DriverChip9388AUlRUs ();
IMPORT int getSelectInput__Q24chip14DriverChipFPGAUlRUs ();
IMPORT int getShowStatus__Q23ent10EntSettingUlRUl ();
IMPORT int getSlotStatusFlg__Q23ent10EntSettingUl ();
IMPORT int getSlotStatusType__Q23ent10EntSettingUl ();
IMPORT int getSysIp__Q23ent10EntSetting ();
IMPORT int getTMDSFreq__Q24chip15DriverChip9388AUlRUc ();
IMPORT int getTemperatureValue ();
IMPORT int getTestConfig__Q24chip14DriverChipFPGARQ24chip11TestConfigT ();
IMPORT int getTestReg__Q24chip14DriverChipFPGARUs ();
IMPORT int getTestVersionReg__Q24chip14DriverChipFPGARUs ();
IMPORT int getUserVersionReg__Q24chip14DriverChipFPGARUs ();
IMPORT int getVersion__Q23ent10EntSetting ();
IMPORT int getVerticalCompensation__Q27chipApp8AppScaleUsUsUc ();
IMPORT int getVerticalStart__Q27chipApp8AppScaleUsUsUc ();
IMPORT int getVerticalTotal__Q27chipApp8AppScaleUsUsUc ();
IMPORT int getVoltage ();
IMPORT int getVsPol__Q24chip15DriverChip9388AUlRUc ();
IMPORT int getWindowsHandle__Q23ent10EntSettingRt3set3ZUlZt4less1ZUlZt9allocator1ZUl ();
IMPORT int getWindowsInfo__Q23ent10EntSettingUlRQ23ent10WindowInfo ();
IMPORT int getWindowsTotal__Q23ent10EntSetting ();
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
IMPORT int getpeername ();
IMPORT int gets ();
IMPORT int gets__7istreamPPcc ();
IMPORT int getsockname ();
IMPORT int getsockopt ();
IMPORT int getw ();
IMPORT int getwd ();
IMPORT int gmtime ();
IMPORT int gmtime_r ();
IMPORT int good__C3ios ();
IMPORT int gptr__C9streambuf ();
IMPORT int grab__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep ();
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
IMPORT int hideWnd__Q27chipApp8AppScaleUl ();
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
IMPORT int ibegin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int icmpCfgParams;
IMPORT int icmpLibInit ();
IMPORT int icmpMaskGet ();
IMPORT int icmp_ctloutput ();
IMPORT int icmp_init ();
IMPORT int icmp_input ();
IMPORT int icmpmask;
IMPORT int icmpmaskrepl;
IMPORT int icmpstat;
IMPORT int iend__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int inflateTask ();
IMPORT int initCLK__Q27chipApp8AppScale ();
IMPORT int initChannel__Q27chipApp8AppScaleUlPQ27chipApp12ScaleChInfoT ();
IMPORT int initChipDDR__Q27chipApp8AppScale ();
IMPORT int initDog ();
IMPORT int initHardware__Q27chipApp8AppScale ();
IMPORT int initMemoryLineFeedWidth__Q27chipApp8AppScaleUl ();
IMPORT int initMoney ();
IMPORT int initScal__Q27chipApp8AppScaleUlUlUlUlUl ();
IMPORT int initScaleTable__Q27chipApp8AppScaleUl ();
IMPORT int initTest1024__Q27chipApp8AppScale ();
IMPORT int initTest1400 ();
IMPORT int initTest1400__Q27chipApp8AppScale ();
IMPORT int initTimingIndexTable__Q27chipApp8AppScale ();
IMPORT int init__3iosP9streambufP7ostream ();
IMPORT int init__7filebuf ();
IMPORT int initstate ();
IMPORT int input_ipaddr;
IMPORT int insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUlc ();
IMPORT int insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pcc ();
IMPORT int insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlPCc ();
IMPORT int insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlPCcUl ();
IMPORT int insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl ();
IMPORT int insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlc ();
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
IMPORT int is_del__t18string_char_traits1Zcc ();
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
IMPORT int length__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int length__t18string_char_traits1ZcPCc ();
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
IMPORT int lt__t18string_char_traits1ZcRCcT1 ();
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
IMPORT int main ();
IMPORT int malloc ();
IMPORT int mask_rnhead;
IMPORT int mathSoftInit ();
IMPORT int maxDrivers;
IMPORT int maxFiles;
IMPORT int max_hdr;
IMPORT int max_keylen;
IMPORT int max_linkhdr;
IMPORT int max_protohdr;
IMPORT int max_size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int memalign ();
IMPORT int memchr ();
IMPORT int memcmp ();
IMPORT int memcpy ();
IMPORT int memmove ();
IMPORT int memset ();
IMPORT int mib2ErrorAdd ();
IMPORT int mib2Init ();
IMPORT int mifCommonEvent__Q23msg5EventUl ();
IMPORT int mifI2CRead__Q23msg9BusDriverUlUl ();
IMPORT int mifI2CWrite__Q23msg9BusDriverUlUlUl ();
IMPORT int mifImportanceEvent__Q23msg5EventUl ();
IMPORT int mifSPIRead__Q23msg9BusDriverUlUl ();
IMPORT int mifSPIWrite__Q23msg9BusDriverUlUlUl ();
IMPORT int mkdir ();
IMPORT int mktime ();
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
IMPORT int moveChannelInput__Q27chipApp8AppScaleUlii ();
IMPORT int moveChannelOutput__Q27chipApp8AppScaleUlii ();
IMPORT int moveInput ();
IMPORT int moveOutput ();
IMPORT int move__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlPCcUl ();
IMPORT int move__t18string_char_traits1ZcPcPCcUl ();
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
IMPORT int ne__t18string_char_traits1ZcRCcT1 ();
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
IMPORT int netMsgInput__10MsgHandlerUlPcUl ();
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
IMPORT int onGetInPutReq__Q23msg6StatusP7MsgInfoUl ();
IMPORT int onGetInPutSizeReq__Q23msg6StatusP7MsgInfoUl ();
IMPORT int onGetOutPutReq__Q23msg6StatusP7MsgInfoUl ();
IMPORT int onGetOutPutSizeReq__Q23msg6StatusP7MsgInfoUl ();
IMPORT int onMsgReq__Q23msg13TaskCheckFPGAP7MsgInfoUl ();
IMPORT int onMsgReq__Q23msg5EventP7MsgInfoUl ();
IMPORT int onMsgReq__Q23msg6BGTestP7MsgInfoUl ();
IMPORT int onMsgReq__Q23msg6StatusP7MsgInfoUl ();
IMPORT int onMsgReq__Q23msg7ChannelP7MsgInfoUl ();
IMPORT int onMsgReq__Q23msg7WindowsP7MsgInfoUl ();
IMPORT int onMsgReq__Q23msg9BusDriverP7MsgInfoUl ();
IMPORT int onPChangeInputReq__Q23msg7ChannelP7MsgInfoUl ();
IMPORT int onPCommonEventUpLoadRsp__Q23msg5EventP7MsgInfoUl ();
IMPORT int onPCreateWindowsReq__Q23msg7WindowsP7MsgInfoUl ();
IMPORT int onPDelWindowsReq__Q23msg7WindowsP7MsgInfoUl ();
IMPORT int onPGetWindowsHandleReq__Q23msg7WindowsP7MsgInfoUl ();
IMPORT int onPGetWindowsInfoReq__Q23msg7WindowsP7MsgInfoUl ();
IMPORT int onPImportanceEventUpLoadRsp__Q23msg5EventP7MsgInfoUl ();
IMPORT int onPMoveWindowsReq__Q23msg7WindowsP7MsgInfoUl ();
IMPORT int onPReadI2CReq__Q23msg6BGTestP7MsgInfoUl ();
IMPORT int onPReadSPIReq__Q23msg6BGTestP7MsgInfoUl ();
IMPORT int onPSetInPutPicReq__Q23msg7ChannelP7MsgInfoUl ();
IMPORT int onPSetOutPutSizeReq__Q23msg7ChannelP7MsgInfoUl ();
IMPORT int onPSetWindowsLayerReq__Q23msg7WindowsP7MsgInfoUl ();
IMPORT int onPSetWindowsShowStateReq__Q23msg7WindowsP7MsgInfoUl ();
IMPORT int onPWriteI2CReq__Q23msg6BGTestP7MsgInfoUl ();
IMPORT int onPWriteSPIReq__Q23msg6BGTestP7MsgInfoUl ();
IMPORT int onProtocolVersionReq__Q23msg6StatusP7MsgInfoUl ();
IMPORT int open ();
IMPORT int openChannelTest__Q27chipApp8AppScale ();
IMPORT int openChannel__Q27chipApp8AppScaleUl ();
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
IMPORT int packMsg__7MsgBaseR10NetMsgBody ();
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
IMPORT int pauseChannel__Q27chipApp8AppScaleUl ();
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
IMPORT int pop_string__7MsgBase ();
IMPORT int pop_u16__7MsgBase ();
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
IMPORT int push_back__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c ();
IMPORT int push_string__7MsgBaseGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int push_u16__7MsgBaseUs ();
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
IMPORT int rbegin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int rbegin__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int rcmd ();
IMPORT int rdbuf__3iosP9streambuf ();
IMPORT int rdbuf__C3ios ();
IMPORT int rdstate__C3ios ();
IMPORT int read ();
IMPORT int readBackground__Q27chipApp8AppScaleUllUsUsPUc ();
IMPORT int read__7istreamPSci ();
IMPORT int read__7istreamPUci ();
IMPORT int read__7istreamPci ();
IMPORT int read__7istreamPvi ();
IMPORT int read_id_register ();
IMPORT int read_status_register ();
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
IMPORT int release__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep ();
IMPORT int remCurIdGet ();
IMPORT int remCurIdSet ();
IMPORT int remLastResvPort;
IMPORT int remLibInit ();
IMPORT int remStdErrSetupTimeout;
IMPORT int remove ();
IMPORT int rename ();
IMPORT int rend__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int rend__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int repeat ();
IMPORT int repeatRun ();
IMPORT int replaceFATsector ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCc ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCcUl ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1Ulc ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlPCc ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlPCcUl ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlUlc ();
IMPORT int replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlc ();
IMPORT int repup__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep ();
IMPORT int reschedule ();
IMPORT int reserve__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int resetflash ();
IMPORT int resize__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int resize__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc ();
IMPORT int restartTaskName;
IMPORT int restartTaskOptions;
IMPORT int restartTaskPriority;
IMPORT int restartTaskStackSize;
IMPORT int resumeChannel__Q27chipApp8AppScaleUl ();
IMPORT int rewind ();
IMPORT int rewinddir ();
IMPORT int rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl ();
IMPORT int rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl ();
IMPORT int rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul ();
IMPORT int rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl ();
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
IMPORT int runServer ();
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
IMPORT int selectOutPut ();
IMPORT int selectOutPutModel__Q27chipApp8AppScaleUl ();
IMPORT int selfish__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int send ();
IMPORT int sendMsg__10MsgHandlerUlP7MsgInfo ();
IMPORT int sendmsg ();
IMPORT int sendto ();
IMPORT int server_proc__7IServeri ();
IMPORT int set753 ();
IMPORT int setC753InputACT ();
IMPORT int setC753OutPutACT ();
IMPORT int setC753OutPutOAI0 ();
IMPORT int setC753OutPutOAI1 ();
IMPORT int setFlashConfig ();
IMPORT int setFpgaSelectChn ();
IMPORT int setInputChannelACT__Q27chipApp8AppScaleUlUsUsUsUs ();
IMPORT int setInputInfoFlg__Q23ent10EntSettingUlUl ();
IMPORT int setInputInfoSize__Q23ent10EntSettingUlUlUl ();
IMPORT int setInputInfoType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int setInput__Q23ent10EntSettingUlUl ();
IMPORT int setLayer__Q23ent10EntSettingUlUl ();
IMPORT int setModel__10MsgHandlerUlP9CommModel ();
IMPORT int setMsgHandler__7IServerP10MsgHandler ();
IMPORT int setMsgInfo__7MsgBaseP7MsgInfo ();
IMPORT int setNetMsgBody__7MsgBaseP10NetMsgBody ();
IMPORT int setOutputBGColor__Q27chipApp8AppScaleUlUl ();
IMPORT int setOutputChannelACT__Q27chipApp8AppScaleUlUsUsUsUs ();
IMPORT int setOutputImage__Q27chipApp8AppScaleUlUl ();
IMPORT int setOutputInfoFlg__Q23ent10EntSettingUlUl ();
IMPORT int setOutputInfoSize__Q23ent10EntSettingUlUlUl ();
IMPORT int setOutputInfoType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int setOutputSize__Q27chipApp8AppScaleUl ();
IMPORT int setOutput__Q23ent10EntSettingUlUl ();
IMPORT int setPOCLK__Q24chip16DriverChipICS307Ul ();
IMPORT int setPort__7IServerUl ();
IMPORT int setSMC2 ();
IMPORT int setSelectInput__Q24chip14DriverChipFPGAUlUs ();
IMPORT int setServerFlg__7IServerb ();
IMPORT int setShowStatus__Q23ent10EntSettingUlUl ();
IMPORT int setSlotStatusFlg__Q23ent10EntSettingUlUl ();
IMPORT int setSlotStatusType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int setSysIp__Q23ent10EntSettingGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int setTestConfig__Q24chip14DriverChipFPGAGQ24chip11TestConfigT ();
IMPORT int setTestReg__Q24chip14DriverChipFPGAUs ();
IMPORT int setVersion__Q23ent10EntSettingGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int setWindowPosition__Q23ent10EntSettingUlUlUlUlUl ();
IMPORT int set__3iosi ();
IMPORT int set__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlcUl ();
IMPORT int set__t18string_char_traits1ZcPcRCcUl ();
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
IMPORT int showWnd__Q27chipApp8AppScaleUl ();
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
IMPORT int size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int spiFlashRead ();
IMPORT int spiFlashWriteTest ();
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
IMPORT int start_spi ();
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
IMPORT int substr__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl ();
IMPORT int substrcmp ();
IMPORT int sungetc__9streambuf ();
IMPORT int swab ();
IMPORT int swap__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Rt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int sysFlashDataPoll16 ();
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
IMPORT int tan ();
IMPORT int tanh ();
IMPORT int taskActivate ();
IMPORT int taskArgsGet ();
IMPORT int taskArgsSet ();
IMPORT int taskBpHook;
IMPORT int taskBpHookSet ();
IMPORT int taskClassId;
IMPORT int taskCreat ();
IMPORT int taskCreateHookAdd ();
IMPORT int taskCreateHookDelete ();
IMPORT int taskCreateTable;
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
IMPORT int taskMain__Q23msg13TaskCheckFPGA ();
IMPORT int taskName ();
IMPORT int taskNameToId ();
IMPORT int taskOptionsGet ();
IMPORT int taskOptionsSet ();
IMPORT int taskOptionsString ();
IMPORT int taskPriRangeCheck;
IMPORT int taskPriorityGet ();
IMPORT int taskPrioritySet ();
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
IMPORT int terminate__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
IMPORT int terminate__Fv ();
IMPORT int test5160 ();
IMPORT int testC772 ();
IMPORT int testCopy ();
IMPORT int testFPGA ();
IMPORT int testMACRO ();
IMPORT int testMenu ();
IMPORT int testSPI ();
IMPORT int testScale ();
IMPORT int testShow ();
IMPORT int testTaskServer ();
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
IMPORT int topChannel ();
IMPORT int topChannel__Q27chipApp8AppScaleUl ();
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
IMPORT int uncompress ();
IMPORT int underflow__7filebuf ();
IMPORT int underflow__9streambuf ();
IMPORT int unexpected__Fv ();
IMPORT int unget__7istream ();
IMPORT int unget__7istreamc ();
IMPORT int ungetc ();
IMPORT int unique__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0 ();
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
IMPORT int what__C11logic_error ();
IMPORT int what__C13runtime_error ();
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
IMPORT int writeBackground__Q27chipApp8AppScaleUlUsUsP14tagDispBitmapT ();
IMPORT int writeFlash16 ();
IMPORT int write__7ostreamPCSci ();
IMPORT int write__7ostreamPCUci ();
IMPORT int write__7ostreamPCci ();
IMPORT int write__7ostreamPCvi ();
IMPORT int write_status_register ();
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

SYMBOL standTbl [5247] =
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
        {{NULL}, "BSPBooter", (char*) BSPBooter, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPCheckSum", (char*) BSPCheckSum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPFileUncompress", (char*) BSPFileUncompress, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPGetFileFromNorFlash", (char*) BSPGetFileFromNorFlash, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BSPGetNandFileVerDevice", (char*) BSPGetNandFileVerDevice, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "BSP_memPartShow", (char*) BSP_memPartShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Bbase__9streambuf", (char*) Bbase__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapCopy__FP14tagDispBitmapTUsUsT0", (char*) BitmapCopy__FP14tagDispBitmapTUsUsT0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapDecode1Bit__FPUcllT0", (char*) BitmapDecode1Bit__FPUcllT0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapDecode24Bits__FPUcllT0", (char*) BitmapDecode24Bits__FPUcllT0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapDecode2FrameBuffer__FPUcUsUsP14tagDispBitmapT", (char*) BitmapDecode2FrameBuffer__FPUcUsUsP14tagDispBitmapT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapDecode8Bits__FPUcllT0", (char*) BitmapDecode8Bits__FPUcllT0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapDecode__FPUcUlP14tagDispBitmapT", (char*) BitmapDecode__FPUcUlP14tagDispBitmapT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapEncode16Bit__FP14tagDispBitmapTPUcPUl", (char*) BitmapEncode16Bit__FP14tagDispBitmapTPUcPUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapEncode__FP14tagDispBitmapTPUcPUl", (char*) BitmapEncode__FP14tagDispBitmapTPUcPUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BitmapFormatFrameBuffer__FP14tagDispBitmapT", (char*) BitmapFormatFrameBuffer__FP14tagDispBitmapT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Bptr__9streambuf", (char*) Bptr__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BroadcastMsg__7IServerPcUl", (char*) BroadcastMsg__7IServerPcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "BulkErase", (char*) BulkErase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Get22PulldownSequenceCount1__Q24chip13DriverChip753UlRUc", (char*) C753Get22PulldownSequenceCount1__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Get23PulldownSequenceCount1__Q24chip13DriverChip753UlRUc", (char*) C753Get23PulldownSequenceCount1__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Get23PulldownSequenceCount2__Q24chip13DriverChip753UlRUc", (char*) C753Get23PulldownSequenceCount2__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Get23PulldownSequenceCount3__Q24chip13DriverChip753UlRUc", (char*) C753Get23PulldownSequenceCount3__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Get23PulldownSequenceCount4__Q24chip13DriverChip753UlRUc", (char*) C753Get23PulldownSequenceCount4__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Get23PulldownSequenceCount5__Q24chip13DriverChip753UlRUc", (char*) C753Get23PulldownSequenceCount5__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetAverageLuminanceLevelResult__Q24chip13DriverChip753UlRUc", (char*) C753GetAverageLuminanceLevelResult__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetBankRegister__Q24chip13DriverChip753RUc", (char*) C753GetBankRegister__Q24chip13DriverChip753RUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetBitmapOSDStatus__Q24chip13DriverChip753RUc", (char*) C753GetBitmapOSDStatus__Q24chip13DriverChip753RUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetBlockNoiseHBoundaryCoordinate__Q24chip13DriverChip753UlRUc", (char*) C753GetBlockNoiseHBoundaryCoordinate__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetBlockNoiseHMatchingCountsMax2__Q24chip13DriverChip753UlRUc", (char*) C753GetBlockNoiseHMatchingCountsMax2__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetBlockNoiseHMatchingCountsMax__Q24chip13DriverChip753UlRUc", (char*) C753GetBlockNoiseHMatchingCountsMax__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetBlockNoiseVBoundaryCoordinate__Q24chip13DriverChip753UlRUc", (char*) C753GetBlockNoiseVBoundaryCoordinate__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetBlockNoiseVMatchingCountsMax2__Q24chip13DriverChip753UlRUc", (char*) C753GetBlockNoiseVMatchingCountsMax2__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetBlockNoiseVMatchingCountsMax__Q24chip13DriverChip753UlRUc", (char*) C753GetBlockNoiseVMatchingCountsMax__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetCPUData__Q24chip13DriverChip753RUc", (char*) C753GetCPUData__Q24chip13DriverChip753RUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetCharacteristicsMeasurementResult0__Q24chip13DriverChip753UlRUc", (char*) C753GetCharacteristicsMeasurementResult0__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetCharacteristicsMeasurementResult1__Q24chip13DriverChip753UlRUc", (char*) C753GetCharacteristicsMeasurementResult1__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetCharacteristicsMeasurementResultHorizontalCoordinate0__Q24chip13DriverChip753UlRUs", (char*) C753GetCharacteristicsMeasurementResultHorizontalCoordinate0__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetCharacteristicsMeasurementResultHorizontalCoordinate1__Q24chip13DriverChip753UlRUs", (char*) C753GetCharacteristicsMeasurementResultHorizontalCoordinate1__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetCharacteristicsMeasurementResultVerticalCoordinate0__Q24chip13DriverChip753UlRUs", (char*) C753GetCharacteristicsMeasurementResultVerticalCoordinate0__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetCharacteristicsMeasurementResultVerticalCoordinate1__Q24chip13DriverChip753UlRUs", (char*) C753GetCharacteristicsMeasurementResultVerticalCoordinate1__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetDPMSInterruptStatus__Q24chip13DriverChip753RUc", (char*) C753GetDPMSInterruptStatus__Q24chip13DriverChip753RUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetDPMSStatus__Q24chip13DriverChip753RUc", (char*) C753GetDPMSStatus__Q24chip13DriverChip753RUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetFieldHistory__Q24chip13DriverChip753UlRUc", (char*) C753GetFieldHistory__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetFlashStatus__Q24chip13DriverChip753RUc", (char*) C753GetFlashStatus__Q24chip13DriverChip753RUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetHorizontalAndVerticalSyncPhaseDifference0__Q24chip13DriverChip753UlRUs", (char*) C753GetHorizontalAndVerticalSyncPhaseDifference0__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetHorizontalAndVerticalSyncPhaseDifference1__Q24chip13DriverChip753UlRUs", (char*) C753GetHorizontalAndVerticalSyncPhaseDifference1__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetInputPortACTHorizontalStart__Q24chip13DriverChip753UlRUs", (char*) C753GetInputPortACTHorizontalStart__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetInputPortACTVerticalStart__Q24chip13DriverChip753UlRUs", (char*) C753GetInputPortACTVerticalStart__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetInputPortHorizontalSyncFrequency__Q24chip13DriverChip753UlRUs", (char*) C753GetInputPortHorizontalSyncFrequency__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetInputPortHorizontalSyncPulseWidth__Q24chip13DriverChip753UlRUc", (char*) C753GetInputPortHorizontalSyncPulseWidth__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetInputPortVerticalSyncFrequency__Q24chip13DriverChip753UlRUs", (char*) C753GetInputPortVerticalSyncFrequency__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetInputPortVerticalSyncPulseWidth__Q24chip13DriverChip753UlRUc", (char*) C753GetInputPortVerticalSyncPulseWidth__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetInterruptStatus__Q24chip13DriverChip753RUs", (char*) C753GetInterruptStatus__Q24chip13DriverChip753RUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetMAXFILTERResult__Q24chip13DriverChip753UlRUc", (char*) C753GetMAXFILTERResult__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetMINFILTERResult__Q24chip13DriverChip753UlRUc", (char*) C753GetMINFILTERResult__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetMainControl__Q24chip13DriverChip753UlRUc", (char*) C753GetMainControl__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetMeasurementStatusMonitor__Q24chip13DriverChip753UlRUc", (char*) C753GetMeasurementStatusMonitor__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetMemoryReadLinefeedWidth__Q24chip13DriverChip753UlRUc", (char*) C753GetMemoryReadLinefeedWidth__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOutputField0MemoryReadStartAddress__Q24chip13DriverChip753UlRUl", (char*) C753GetOutputField0MemoryReadStartAddress__Q24chip13DriverChip753UlRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOutputField1MemoryReadStartAddress__Q24chip13DriverChip753UlRUl", (char*) C753GetOutputField1MemoryReadStartAddress__Q24chip13DriverChip753UlRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOutputField2MemoryReadStartAddress__Q24chip13DriverChip753UlRUl", (char*) C753GetOutputField2MemoryReadStartAddress__Q24chip13DriverChip753UlRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOutputField3MemoryReadStartAddress__Q24chip13DriverChip753UlRUl", (char*) C753GetOutputField3MemoryReadStartAddress__Q24chip13DriverChip753UlRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOutputPortACTHorizontalStart__Q24chip13DriverChip753UlRUs", (char*) C753GetOutputPortACTHorizontalStart__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOutputPortACTVerticalStart__Q24chip13DriverChip753UlRUs", (char*) C753GetOutputPortACTVerticalStart__Q24chip13DriverChip753UlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOutputPortSyncControl__Q24chip13DriverChip753RUs", (char*) C753GetOutputPortSyncControl__Q24chip13DriverChip753RUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOutputPortVerticalSyncFrequency__Q24chip13DriverChip753RUs", (char*) C753GetOutputPortVerticalSyncFrequency__Q24chip13DriverChip753RUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetOverlayControl__Q24chip13DriverChip753RUc", (char*) C753GetOverlayControl__Q24chip13DriverChip753RUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetPWMHighPulseWidthCounterValue__Q24chip13DriverChip753RUs", (char*) C753GetPWMHighPulseWidthCounterValue__Q24chip13DriverChip753RUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetPWMLowPulseWidthCounterValue__Q24chip13DriverChip753RUs", (char*) C753GetPWMLowPulseWidthCounterValue__Q24chip13DriverChip753RUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetSNHistogramMeasurementResult__Q24chip13DriverChip753UlRUc", (char*) C753GetSNHistogramMeasurementResult__Q24chip13DriverChip753UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753GetStatus__Q24chip13DriverChip753RUs", (char*) C753GetStatus__Q24chip13DriverChip753RUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753LoadDiagonalInterpolationThreshold__Q24chip13DriverChip753UlPCUc", (char*) C753LoadDiagonalInterpolationThreshold__Q24chip13DriverChip753UlPCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753LoadInputHorizontalShrinkLookupTable__Q24chip13DriverChip753UlPCUc", (char*) C753LoadInputHorizontalShrinkLookupTable__Q24chip13DriverChip753UlPCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753LoadInputVerticalShrinkLookupTable__Q24chip13DriverChip753UlPCUc", (char*) C753LoadInputVerticalShrinkLookupTable__Q24chip13DriverChip753UlPCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753LoadOutputHorizontalZoomLookupTable__Q24chip13DriverChip753UlPCUc", (char*) C753LoadOutputHorizontalZoomLookupTable__Q24chip13DriverChip753UlPCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753LoadOutputVerticalZoomLookupTable__Q24chip13DriverChip753UlPCUc", (char*) C753LoadOutputVerticalZoomLookupTable__Q24chip13DriverChip753UlPCUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753ReadN24BitPixels__Q24chip13DriverChip753UsPUc", (char*) C753ReadN24BitPixels__Q24chip13DriverChip753UsPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Reset__Q24chip13DriverChip753Uc", (char*) C753Reset__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set1MHzPulseGenerationControl__Q24chip13DriverChip753Uc", (char*) C753Set1MHzPulseGenerationControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set22PulldownMovementDetectThreshold__Q24chip13DriverChip753UlUc", (char*) C753Set22PulldownMovementDetectThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set22PulldownResetDetectIndex__Q24chip13DriverChip753UlUc", (char*) C753Set22PulldownResetDetectIndex__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set23PulldownMovementDetectThreshold__Q24chip13DriverChip753UlUc", (char*) C753Set23PulldownMovementDetectThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set23PulldownResetDetectIndex__Q24chip13DriverChip753UlUc", (char*) C753Set23PulldownResetDetectIndex__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set2ScreenBlendingAlphaCoefficient__Q24chip13DriverChip753Uc", (char*) C753Set2ScreenBlendingAlphaCoefficient__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set2ScreenBlendingBetaCoefficient__Q24chip13DriverChip753Uc", (char*) C753Set2ScreenBlendingBetaCoefficient__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753Set90DegreeRotationField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753Set90DegreeRotationField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753Set90DegreeRotationField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753Set90DegreeRotationField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationField2MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753Set90DegreeRotationField2MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753Set90DegreeRotationField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationField3MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753Set90DegreeRotationField3MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753Set90DegreeRotationField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationMemoryReadLinefeedWidth__Q24chip13DriverChip753UlUc", (char*) C753Set90DegreeRotationMemoryReadLinefeedWidth__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753Set90DegreeRotationMemoryWriteLinefeedWidth__Q24chip13DriverChip753UlUc", (char*) C753Set90DegreeRotationMemoryWriteLinefeedWidth__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetAdaptiveNRCoefficient__Q24chip13DriverChip753UlUl", (char*) C753SetAdaptiveNRCoefficient__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetAdaptiveNRControl__Q24chip13DriverChip753UlUc", (char*) C753SetAdaptiveNRControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetAdaptiveNRThreshold__Q24chip13DriverChip753UlUl", (char*) C753SetAdaptiveNRThreshold__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBackgroundControl__Q24chip13DriverChip753Uc", (char*) C753SetBackgroundControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBankRegister__Q24chip13DriverChip753Uc", (char*) C753SetBankRegister__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBitBLTHorizontalWidth__Q24chip13DriverChip753Uc", (char*) C753SetBitBLTHorizontalWidth__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBitBLTReadLinefeedWidth__Q24chip13DriverChip753Uc", (char*) C753SetBitBLTReadLinefeedWidth__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBitBLTTriggerVSDelay__Q24chip13DriverChip753Uc", (char*) C753SetBitBLTTriggerVSDelay__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBitBLTVerticalWidth__Q24chip13DriverChip753Us", (char*) C753SetBitBLTVerticalWidth__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBitBLTWriteLinefeedWidth__Q24chip13DriverChip753Uc", (char*) C753SetBitBLTWriteLinefeedWidth__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBitmapOSD90DegreeRotation__Q24chip13DriverChip753Uc", (char*) C753SetBitmapOSD90DegreeRotation__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBitmapOSDAccessControl__Q24chip13DriverChip753Uc", (char*) C753SetBitmapOSDAccessControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlinkCycle__Q24chip13DriverChip753Uc", (char*) C753SetBlinkCycle__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlinkingTime__Q24chip13DriverChip753Uc", (char*) C753SetBlinkingTime__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockBoundaryPeripheralEdgeLevelThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetBlockBoundaryPeripheralEdgeLevelThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockBoundaryPeripheralMovementValueThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetBlockBoundaryPeripheralMovementValueThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRAlphaBlendCoefficient0__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRAlphaBlendCoefficient0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRAlphaBlendCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRAlphaBlendCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRControl__Q24chip13DriverChip753UlUs", (char*) C753SetBlockNRControl__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRDetectControl__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRDetectControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRLowPassFilterCoefficient0__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRLowPassFilterCoefficient0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRLowPassFilterCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRLowPassFilterCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRProjectionCoefficient__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRProjectionCoefficient__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRProjectionControl__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRProjectionControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRProjectionReadAddress__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRProjectionReadAddress__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRProjectionReadData__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRProjectionReadData__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNRTest__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNRTest__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNoiseEdgeLevelThreshold0__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNoiseEdgeLevelThreshold0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNoiseEdgeLevelThreshold1__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNoiseEdgeLevelThreshold1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNoiseEdgeLevelThreshold2__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNoiseEdgeLevelThreshold2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetBlockNoiseEdgeLevelThreshold3__Q24chip13DriverChip753UlUc", (char*) C753SetBlockNoiseEdgeLevelThreshold3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCPUData__Q24chip13DriverChip753Uc", (char*) C753SetCPUData__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCPUReadAddress__Q24chip13DriverChip753Ul", (char*) C753SetCPUReadAddress__Q24chip13DriverChip753Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCPUWriteAddress__Q24chip13DriverChip753Ul", (char*) C753SetCPUWriteAddress__Q24chip13DriverChip753Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChannel1Image90DegreeRotationControl__Q24chip13DriverChip753Uc", (char*) C753SetChannel1Image90DegreeRotationControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChannel1Image90DegreeRotationHorizontalActiveAreaWidth__Q24chip13DriverChip753Us", (char*) C753SetChannel1Image90DegreeRotationHorizontalActiveAreaWidth__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChannel1Image90DegreeRotationVerticalActiveAreaWidth__Q24chip13DriverChip753Us", (char*) C753SetChannel1Image90DegreeRotationVerticalActiveAreaWidth__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChannel1Image90DegreeRotationVerticalSyncSignalDelay__Q24chip13DriverChip753Us", (char*) C753SetChannel1Image90DegreeRotationVerticalSyncSignalDelay__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChannel2Image90DegreeRotationControl__Q24chip13DriverChip753Uc", (char*) C753SetChannel2Image90DegreeRotationControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChannel2Image90DegreeRotationHorizontalActiveAreaWidth__Q24chip13DriverChip753Us", (char*) C753SetChannel2Image90DegreeRotationHorizontalActiveAreaWidth__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChannel2Image90DegreeRotationVerticalActiveAreaWidth__Q24chip13DriverChip753Us", (char*) C753SetChannel2Image90DegreeRotationVerticalActiveAreaWidth__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChannel2Image90DegreeRotationVerticalSyncSignalDelay__Q24chip13DriverChip753Us", (char*) C753SetChannel2Image90DegreeRotationVerticalSyncSignalDelay__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCharacterBufferAddress__Q24chip13DriverChip753Us", (char*) C753SetCharacterBufferAddress__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCharacterBufferData__Q24chip13DriverChip753Uc", (char*) C753SetCharacterBufferData__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCharacterBufferHorizontalStart__Q24chip13DriverChip753Uc", (char*) C753SetCharacterBufferHorizontalStart__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCharacterBufferHorizontalWidth__Q24chip13DriverChip753Uc", (char*) C753SetCharacterBufferHorizontalWidth__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCharacterBufferVerticalStart__Q24chip13DriverChip753Uc", (char*) C753SetCharacterBufferVerticalStart__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCharacterBufferVerticalWidth__Q24chip13DriverChip753Uc", (char*) C753SetCharacterBufferVerticalWidth__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChromaErrorAutomaticCorrectionCounterUpperLimit__Q24chip13DriverChip753UlUc", (char*) C753SetChromaErrorAutomaticCorrectionCounterUpperLimit__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChromaErrorAutomaticCorrectionThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetChromaErrorAutomaticCorrectionThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChromaErrorCorrectionControl__Q24chip13DriverChip753UlUc", (char*) C753SetChromaErrorCorrectionControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChromaErrorCorrectionLowPassFilterCoefficient__Q24chip13DriverChip753UlUc", (char*) C753SetChromaErrorCorrectionLowPassFilterCoefficient__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChromaErrorDetectionCountThreshold__Q24chip13DriverChip753UlUs", (char*) C753SetChromaErrorDetectionCountThreshold__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChromaErrorDetectionExclusionThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetChromaErrorDetectionExclusionThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetChromaErrorDetectionThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetChromaErrorDetectionThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetColorBarWidthSetting__Q24chip13DriverChip753Uc", (char*) C753SetColorBarWidthSetting__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCombingProcessControlHighLevelThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetCombingProcessControlHighLevelThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCombingProcessControlLowLevelThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetCombingProcessControlLowLevelThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetCombingProcessControl__Q24chip13DriverChip753UlUc", (char*) C753SetCombingProcessControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDDRControl__Q24chip13DriverChip753Uc", (char*) C753SetDDRControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl0__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl0__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl1__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl1__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl2__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl2__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl3__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl3__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl4__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl4__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl5__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl5__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl6__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl6__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl7__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl7__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDLLControl8__Q24chip13DriverChip753Uc", (char*) C753SetDLLControl8__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDPMSControl__Q24chip13DriverChip753Uc", (char*) C753SetDPMSControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDPMSInterruptReset__Q24chip13DriverChip753Uc", (char*) C753SetDPMSInterruptReset__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetDiagonalInterpolationControl__Q24chip13DriverChip753UlUl", (char*) C753SetDiagonalInterpolationControl__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetFieldInterlockTransferControl__Q24chip13DriverChip753Uc", (char*) C753SetFieldInterlockTransferControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetFieldPropagationDelay1__Q24chip13DriverChip753Uc", (char*) C753SetFieldPropagationDelay1__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetFieldPropagationDelay2__Q24chip13DriverChip753Uc", (char*) C753SetFieldPropagationDelay2__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetForcedSyncResetControl__Q24chip13DriverChip753Us", (char*) C753SetForcedSyncResetControl__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetForcedSyncResetDelay__Q24chip13DriverChip753Uc", (char*) C753SetForcedSyncResetDelay__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHBlockBoundaryMatchingCountsOffset__Q24chip13DriverChip753UlUc", (char*) C753SetHBlockBoundaryMatchingCountsOffset__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHBlockBoundaryMatchingCountsThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetHBlockBoundaryMatchingCountsThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHBlockBoundaryMatchingLowerLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc", (char*) C753SetHBlockBoundaryMatchingLowerLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHBlockBoundaryMatchingThresholdPeripheralPixel__Q24chip13DriverChip753UlUc", (char*) C753SetHBlockBoundaryMatchingThresholdPeripheralPixel__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHBlockBoundaryMatchingUpperLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc", (char*) C753SetHBlockBoundaryMatchingUpperLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalBlockBoundaryCoordinate__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalBlockBoundaryCoordinate__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalBlockBoundaryInitialCoordinateForProjection__Q24chip13DriverChip753UlUs", (char*) C753SetHorizontalBlockBoundaryInitialCoordinateForProjection__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalBlockEnlargementScaleForProjection__Q24chip13DriverChip753UlUs", (char*) C753SetHorizontalBlockEnlargementScaleForProjection__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueGain0__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalMovementValueGain0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueGain1__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalMovementValueGain1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueGain2__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalMovementValueGain2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueGain3__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalMovementValueGain3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueGain__Q24chip13DriverChip753UlUcUcUcUc", (char*) C753SetHorizontalMovementValueGain__Q24chip13DriverChip753UlUcUcUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueNRCoefficient0__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalMovementValueNRCoefficient0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueNRCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalMovementValueNRCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueNRCoefficient2__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalMovementValueNRCoefficient2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueNRCoefficient3__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalMovementValueNRCoefficient3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalMovementValueNRCoefficient__Q24chip13DriverChip753UlUcUcUcUc", (char*) C753SetHorizontalMovementValueNRCoefficient__Q24chip13DriverChip753UlUcUcUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalNRCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalNRCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalNRCoefficient2__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalNRCoefficient2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalRAMPCounterLimitValue__Q24chip13DriverChip753Us", (char*) C753SetHorizontalRAMPCounterLimitValue__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalSyncSignalAbsenceJudgmentValue__Q24chip13DriverChip753Us", (char*) C753SetHorizontalSyncSignalAbsenceJudgmentValue__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalSyncSignalPresenceJudgmentValue__Q24chip13DriverChip753Us", (char*) C753SetHorizontalSyncSignalPresenceJudgmentValue__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetHorizontalVerticalNRControl__Q24chip13DriverChip753UlUc", (char*) C753SetHorizontalVerticalNRControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPCLKFeedbackDividing__Q24chip13DriverChip753Uc", (char*) C753SetIPCLKFeedbackDividing__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPCLKPLLControl__Q24chip13DriverChip753Uc", (char*) C753SetIPCLKPLLControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPCLKReferenceDividing__Q24chip13DriverChip753Uc", (char*) C753SetIPCLKReferenceDividing__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetIPConversionField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetIPConversionField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetIPConversionField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetIPConversionField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetIPConversionField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetIPConversionField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionForcedSyncResetDelay__Q24chip13DriverChip753UlUc", (char*) C753SetIPConversionForcedSyncResetDelay__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionMemoryLinefeedWidth__Q24chip13DriverChip753UlUc", (char*) C753SetIPConversionMemoryLinefeedWidth__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionMovementValueReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetIPConversionMovementValueReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionOutputPortActiveAreaHorizontalStart__Q24chip13DriverChip753UlUs", (char*) C753SetIPConversionOutputPortActiveAreaHorizontalStart__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionOutputPortActiveAreaHorizontalWidth__Q24chip13DriverChip753UlUs", (char*) C753SetIPConversionOutputPortActiveAreaHorizontalWidth__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionOutputPortActiveAreaVerticalStart__Q24chip13DriverChip753UlUs", (char*) C753SetIPConversionOutputPortActiveAreaVerticalStart__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionOutputPortActiveAreaVerticalWidth__Q24chip13DriverChip753UlUs", (char*) C753SetIPConversionOutputPortActiveAreaVerticalWidth__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionOutputPortHorizontalSyncCycle__Q24chip13DriverChip753UlUs", (char*) C753SetIPConversionOutputPortHorizontalSyncCycle__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPConversionOutputPortVerticalSyncCycle__Q24chip13DriverChip753UlUs", (char*) C753SetIPConversionOutputPortVerticalSyncCycle__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPImageAdjustment__Q24chip13DriverChip753UlUc", (char*) C753SetIPImageAdjustment__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetIPTest__Q24chip13DriverChip753UlUc", (char*) C753SetIPTest__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputCharacteristicsMeasurementThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetInputCharacteristicsMeasurementThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputComponentInputControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputComponentInputControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputDigitalInterfaceControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputDigitalInterfaceControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetInputField0MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetInputField1MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetInputField2MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetInputField3MemoryWriteStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputFieldRecognitionControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputFieldRecognitionControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputFill", (char*) C753SetInputFill, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputFill__Q24chip13DriverChip753UlUl", (char*) C753SetInputFill__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputFormatControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputFormatControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputHorizontalShrinkCompensation__Q24chip13DriverChip753UlUc", (char*) C753SetInputHorizontalShrinkCompensation__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputHorizontalShrinkControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputHorizontalShrinkControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputHorizontalShrinkInitialValue__Q24chip13DriverChip753UlUc", (char*) C753SetInputHorizontalShrinkInitialValue__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputHorizontalShrinkScale__Q24chip13DriverChip753UlUs", (char*) C753SetInputHorizontalShrinkScale__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputImageCharacteristicsMeasurementControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputImageCharacteristicsMeasurementControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputImageControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputImageControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputMeasurementHorizontalEnd__Q24chip13DriverChip753UlUs", (char*) C753SetInputMeasurementHorizontalEnd__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputMeasurementHorizontalStart__Q24chip13DriverChip753UlUs", (char*) C753SetInputMeasurementHorizontalStart__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputMeasurementVerticalEnd__Q24chip13DriverChip753UlUs", (char*) C753SetInputMeasurementVerticalEnd__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputMeasurementVerticalStart__Q24chip13DriverChip753UlUs", (char*) C753SetInputMeasurementVerticalStart__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputPortACTHorizontalStart__Q24chip13DriverChip753UlUs", (char*) C753SetInputPortACTHorizontalStart__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputPortACTHorizontalWidth__Q24chip13DriverChip753UlUs", (char*) C753SetInputPortACTHorizontalWidth__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputPortACTVerticalStart__Q24chip13DriverChip753UlUs", (char*) C753SetInputPortACTVerticalStart__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputPortACTVerticalWidth__Q24chip13DriverChip753UlUs", (char*) C753SetInputPortACTVerticalWidth__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputPortSyncControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputPortSyncControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientBU__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientBU__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientBV__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientBV__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientBY__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientBY__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientGU__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientGU__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientGV__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientGV__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientGY__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientGY__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientRU__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientRU__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientRV__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientRV__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputRGBYUVCoefficientRY__Q24chip13DriverChip753UlUs", (char*) C753SetInputRGBYUVCoefficientRY__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputShrinkCompensationControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputShrinkCompensationControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputSignalSwap__Q24chip13DriverChip753UlUc", (char*) C753SetInputSignalSwap__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputUVLowPassFilterCoefficient__Q24chip13DriverChip753UlUl", (char*) C753SetInputUVLowPassFilterCoefficient__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputVerticalShrinkCompensation__Q24chip13DriverChip753UlUc", (char*) C753SetInputVerticalShrinkCompensation__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputVerticalShrinkControl__Q24chip13DriverChip753UlUc", (char*) C753SetInputVerticalShrinkControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputVerticalShrinkInitialValue__Q24chip13DriverChip753UlUc", (char*) C753SetInputVerticalShrinkInitialValue__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInputVerticalShrinkScale__Q24chip13DriverChip753UlUs", (char*) C753SetInputVerticalShrinkScale__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInterlaceOutputControl__Q24chip13DriverChip753Uc", (char*) C753SetInterlaceOutputControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInterruptEnable__Q24chip13DriverChip753Us", (char*) C753SetInterruptEnable__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetInterruptReset__Q24chip13DriverChip753Us", (char*) C753SetInterruptReset__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetLUTCoefficient__Q24chip13DriverChip753UlUl", (char*) C753SetLUTCoefficient__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetLUTWriteAddress__Q24chip13DriverChip753UlUc", (char*) C753SetLUTWriteAddress__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetLUTWriteEnable__Q24chip13DriverChip753UlUc", (char*) C753SetLUTWriteEnable__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetLongFramesRegisterBlockBoundaryAutoDetect__Q24chip13DriverChip753UlUc", (char*) C753SetLongFramesRegisterBlockBoundaryAutoDetect__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMainControl__Q24chip13DriverChip753UlUc", (char*) C753SetMainControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMemoryControl__Q24chip13DriverChip753Uc", (char*) C753SetMemoryControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMemoryProtect__Q24chip13DriverChip753Us", (char*) C753SetMemoryProtect__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMemoryReadLinefeedWidth__Q24chip13DriverChip753UlUc", (char*) C753SetMemoryReadLinefeedWidth__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMemoryWriteLinefeedWidth__Q24chip13DriverChip753UlUc", (char*) C753SetMemoryWriteLinefeedWidth__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRBlendCoefficientBias__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRBlendCoefficientBias__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRBlendCoefficientGain__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRBlendCoefficientGain__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRBlendLowPassFilterHCoefficient0__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRBlendLowPassFilterHCoefficient0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRBlendLowPassFilterHCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRBlendLowPassFilterHCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRBlendLowPassFilterHCoefficient2__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRBlendLowPassFilterHCoefficient2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRBlendLowPassFilterVCoefficient0__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRBlendLowPassFilterVCoefficient0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRBlendLowPassFilterVCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRBlendLowPassFilterVCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRBlendLowPassFilterVCoefficient2__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRBlendLowPassFilterVCoefficient2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRControl__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRHDirectionCoefficient0__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRHDirectionCoefficient0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRHDirectionCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRHDirectionCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRHDirectionCoefficient2__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRHDirectionCoefficient2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRHDirectionCoefficient3__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRHDirectionCoefficient3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRHDirectionCoefficient4__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRHDirectionCoefficient4__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRHDirectionCoefficient5__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRHDirectionCoefficient5__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRNoiseBias__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRNoiseBias__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRSubtractionBlendCoefficientGain__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRSubtractionBlendCoefficientGain__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThreshold0__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThreshold0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThreshold1__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThreshold1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThreshold2__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThreshold2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThreshold3__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThreshold3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThreshold4__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThreshold4__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThreshold5__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThreshold5__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThreshold6__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThreshold6__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThreshold7__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThreshold7__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThresholdBias0__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThresholdBias0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThresholdBias1__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThresholdBias1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThresholdBias2__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThresholdBias2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThresholdBias3__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThresholdBias3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThresholdBias4__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThresholdBias4__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThresholdBias5__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThresholdBias5__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThresholdBias6__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThresholdBias6__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRThresholdBias7__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRThresholdBias7__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRVDirectionCoefficient0__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRVDirectionCoefficient0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRVDirectionCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRVDirectionCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRVDirectionCoefficient2__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRVDirectionCoefficient2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRVDirectionCoefficient3__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRVDirectionCoefficient3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRVDirectionCoefficient4__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRVDirectionCoefficient4__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMosquitoNRVDirectionCoefficient5__Q24chip13DriverChip753UlUc", (char*) C753SetMosquitoNRVDirectionCoefficient5__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMovementCoefficientNR__Q24chip13DriverChip753UlUc", (char*) C753SetMovementCoefficientNR__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetMovementNRControl__Q24chip13DriverChip753UlUc", (char*) C753SetMovementNRControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDACTHorizontalStart__Q24chip13DriverChip753Us", (char*) C753SetOSDACTHorizontalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDACTHorizontalWidth__Q24chip13DriverChip753Us", (char*) C753SetOSDACTHorizontalWidth__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDACTVerticalStart__Q24chip13DriverChip753Us", (char*) C753SetOSDACTVerticalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDACTVerticalWidth__Q24chip13DriverChip753Us", (char*) C753SetOSDACTVerticalWidth__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDControl__Q24chip13DriverChip753Uc", (char*) C753SetOSDControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDFillColor__Q24chip13DriverChip753Uc", (char*) C753SetOSDFillColor__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDMemoryLinefeedWidth__Q24chip13DriverChip753Uc", (char*) C753SetOSDMemoryLinefeedWidth__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDMode__Q24chip13DriverChip753Uc", (char*) C753SetOSDMode__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDPenetrationColor__Q24chip13DriverChip753Uc", (char*) C753SetOSDPenetrationColor__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDStartAddress__Q24chip13DriverChip753Ul", (char*) C753SetOSDStartAddress__Q24chip13DriverChip753Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOSDWriteInhibitColor__Q24chip13DriverChip753Uc", (char*) C753SetOSDWriteInhibitColor__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutFill", (char*) C753SetOutFill, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputBackground0__Q24chip13DriverChip753Ul", (char*) C753SetOutputBackground0__Q24chip13DriverChip753Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputBackground1__Q24chip13DriverChip753Ul", (char*) C753SetOutputBackground1__Q24chip13DriverChip753Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetOutputField0MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetOutputField1MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputField2MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetOutputField2MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputField3MemoryReadStartAddress__Q24chip13DriverChip753UlUl", (char*) C753SetOutputField3MemoryReadStartAddress__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputFill__Q24chip13DriverChip753UlUl", (char*) C753SetOutputFill__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalEdgeEmphasisControl__Q24chip13DriverChip753UlUc", (char*) C753SetOutputHorizontalEdgeEmphasisControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc", (char*) C753SetOutputHorizontalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc", (char*) C753SetOutputHorizontalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalEdgeEmphasisOvershootFilterCoefficient__Q24chip13DriverChip753UlUc", (char*) C753SetOutputHorizontalEdgeEmphasisOvershootFilterCoefficient__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalEdgeEmphasisUndershootFilterCoefficient__Q24chip13DriverChip753UlUc", (char*) C753SetOutputHorizontalEdgeEmphasisUndershootFilterCoefficient__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalEnlargementControl__Q24chip13DriverChip753UlUc", (char*) C753SetOutputHorizontalEnlargementControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalEnlargementInitialValue__Q24chip13DriverChip753UlUc", (char*) C753SetOutputHorizontalEnlargementInitialValue__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalSync__Q24chip13DriverChip753Us", (char*) C753SetOutputHorizontalSync__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputHorizontalZoomScale__Q24chip13DriverChip753UlUs", (char*) C753SetOutputHorizontalZoomScale__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputImageControl__Q24chip13DriverChip753UlUc", (char*) C753SetOutputImageControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPatternBarWidth__Q24chip13DriverChip753Uc", (char*) C753SetOutputPatternBarWidth__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPatternCycle__Q24chip13DriverChip753Us", (char*) C753SetOutputPatternCycle__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPatternSpeed__Q24chip13DriverChip753Uc", (char*) C753SetOutputPatternSpeed__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortACTHorizontalStart__Q24chip13DriverChip753UlUs", (char*) C753SetOutputPortACTHorizontalStart__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortACTHorizontalWidth__Q24chip13DriverChip753UlUs", (char*) C753SetOutputPortACTHorizontalWidth__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortACTVerticalStart__Q24chip13DriverChip753UlUs", (char*) C753SetOutputPortACTVerticalStart__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortACTVerticalWidth__Q24chip13DriverChip753UlUs", (char*) C753SetOutputPortACTVerticalWidth__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI0HorizontalEnd__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI0HorizontalEnd__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI0HorizontalStart__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI0HorizontalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI0VerticalEnd__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI0VerticalEnd__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI0VerticalStart__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI0VerticalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI1HorizontalEnd__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI1HorizontalEnd__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI1HorizontalStart__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI1HorizontalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI1VerticalEnd__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI1VerticalEnd__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI1VerticalStart__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI1VerticalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI2HorizontalEnd__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI2HorizontalEnd__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI2HorizontalStart__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI2HorizontalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI2VerticalEnd__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI2VerticalEnd__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI2VerticalStart__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI2VerticalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI3HorizontalEnd__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI3HorizontalEnd__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI3HorizontalStart__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI3HorizontalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI3VerticalEnd__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI3VerticalEnd__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortOAOI3VerticalStart__Q24chip13DriverChip753Us", (char*) C753SetOutputPortOAOI3VerticalStart__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPortSyncControl__Q24chip13DriverChip753Us", (char*) C753SetOutputPortSyncControl__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementHorizontalEdgeAreaSelect__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementHorizontalEdgeAreaSelect__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoefficient__Q24chip13DriverChip753UlUl", (char*) C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoefficient__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementHorizontalEdgeEmphasisControl__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementHorizontalEdgeEmphasisControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementVerticalEdgeAreaSelect__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementVerticalEdgeAreaSelect__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementVerticalEdgeEmphasisCoefficient__Q24chip13DriverChip753UlUl", (char*) C753SetOutputPostEnlargementVerticalEdgeEmphasisCoefficient__Q24chip13DriverChip753UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementVerticalEdgeEmphasisControl2__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementVerticalEdgeEmphasisControl2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementVerticalEdgeEmphasisControl__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementVerticalEdgeEmphasisControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringH__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc", (char*) C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringL__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputSignalSwap__Q24chip13DriverChip753Uc", (char*) C753SetOutputSignalSwap__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputVerticalEnlargementControl__Q24chip13DriverChip753UlUc", (char*) C753SetOutputVerticalEnlargementControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputVerticalEnlargementInitialValue__Q24chip13DriverChip753UlUc", (char*) C753SetOutputVerticalEnlargementInitialValue__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputVerticalSync__Q24chip13DriverChip753Us", (char*) C753SetOutputVerticalSync__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOutputVerticalZoomScale__Q24chip13DriverChip753UlUs", (char*) C753SetOutputVerticalZoomScale__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetOverlayControl__Q24chip13DriverChip753Uc", (char*) C753SetOverlayControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPOCLKControl__Q24chip13DriverChip753Uc", (char*) C753SetPOCLKControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPOCLKFeedbackDividing__Q24chip13DriverChip753Uc", (char*) C753SetPOCLKFeedbackDividing__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPOCLKPLLControl__Q24chip13DriverChip753Uc", (char*) C753SetPOCLKPLLControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPOCLKReferenceDividing__Q24chip13DriverChip753Uc", (char*) C753SetPOCLKReferenceDividing__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPWMControl0__Q24chip13DriverChip753Us", (char*) C753SetPWMControl0__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPWMControl1__Q24chip13DriverChip753Us", (char*) C753SetPWMControl1__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPWMControl2__Q24chip13DriverChip753Us", (char*) C753SetPWMControl2__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPWMControl3__Q24chip13DriverChip753Us", (char*) C753SetPWMControl3__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPaletteAddress__Q24chip13DriverChip753Uc", (char*) C753SetPaletteAddress__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPaletteData__Q24chip13DriverChip753Uc", (char*) C753SetPaletteData__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPatternGeneratorControl__Q24chip13DriverChip753Uc", (char*) C753SetPatternGeneratorControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPulldownAreaWidthSelect__Q24chip13DriverChip753UlUc", (char*) C753SetPulldownAreaWidthSelect__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPulldownControl1__Q24chip13DriverChip753UlUc", (char*) C753SetPulldownControl1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPulldownControl2__Q24chip13DriverChip753UlUc", (char*) C753SetPulldownControl2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPulldownDetectAreaSelect__Q24chip13DriverChip753UlUc", (char*) C753SetPulldownDetectAreaSelect__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetPulldownSequenceThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetPulldownSequenceThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetRAMPCounterStepSetting__Q24chip13DriverChip753Uc", (char*) C753SetRAMPCounterStepSetting__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetRegisterValueTransferControl__Q24chip13DriverChip753Us", (char*) C753SetRegisterValueTransferControl__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetScalingWidthControl__Q24chip13DriverChip753Uc", (char*) C753SetScalingWidthControl__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTESTAD__Q24chip13DriverChip753Uc", (char*) C753SetTESTAD__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTESTDT__Q24chip13DriverChip753Uc", (char*) C753SetTESTDT__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRCoefficient2__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRCoefficient2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRCoefficient3__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRCoefficient3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRCoefficient4__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRCoefficient4__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRCoefficient5__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRCoefficient5__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRCoefficient6__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRCoefficient6__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRCoefficient7__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRCoefficient7__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRCoefficient8__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRCoefficient8__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRControl__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRControl__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRReadStartAddressSelect__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRReadStartAddressSelect__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRThreshold1__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRThreshold1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRThreshold2__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRThreshold2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRThreshold3__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRThreshold3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTemporalNRThreshold4__Q24chip13DriverChip753UlUc", (char*) C753SetTemporalNRThreshold4__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetTestG__Q24chip13DriverChip753Uc", (char*) C753SetTestG__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVBlockBoundaryMatchingCountsOffset__Q24chip13DriverChip753UlUc", (char*) C753SetVBlockBoundaryMatchingCountsOffset__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVBlockBoundaryMatchingCountsThreshold__Q24chip13DriverChip753UlUc", (char*) C753SetVBlockBoundaryMatchingCountsThreshold__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVBlockBoundaryMatchingLowerLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc", (char*) C753SetVBlockBoundaryMatchingLowerLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVBlockBoundaryMatchingThresholdPeripheralPixel__Q24chip13DriverChip753UlUc", (char*) C753SetVBlockBoundaryMatchingThresholdPeripheralPixel__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVBlockBoundaryMatchingUpperLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc", (char*) C753SetVBlockBoundaryMatchingUpperLimitThresholdCenterPixel__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalBlockBoundaryCoordinate__Q24chip13DriverChip753UlUc", (char*) C753SetVerticalBlockBoundaryCoordinate__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalBlockBoundaryInitialCoordinateForProjection__Q24chip13DriverChip753UlUs", (char*) C753SetVerticalBlockBoundaryInitialCoordinateForProjection__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalBlockEnlargementScaleForProjection__Q24chip13DriverChip753UlUs", (char*) C753SetVerticalBlockEnlargementScaleForProjection__Q24chip13DriverChip753UlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalDirectionMAXFilter__Q24chip13DriverChip753UlUc", (char*) C753SetVerticalDirectionMAXFilter__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalMovementValueGain0__Q24chip13DriverChip753UlUc", (char*) C753SetVerticalMovementValueGain0__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalMovementValueGain1__Q24chip13DriverChip753UlUc", (char*) C753SetVerticalMovementValueGain1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalMovementValueGain2__Q24chip13DriverChip753UlUc", (char*) C753SetVerticalMovementValueGain2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalMovementValueGain3__Q24chip13DriverChip753UlUc", (char*) C753SetVerticalMovementValueGain3__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalMovementValueGain__Q24chip13DriverChip753UlUcUcUcUc", (char*) C753SetVerticalMovementValueGain__Q24chip13DriverChip753UlUcUcUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalNRCoefficient1__Q24chip13DriverChip753UlUc", (char*) C753SetVerticalNRCoefficient1__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalNRCoefficient2__Q24chip13DriverChip753UlUc", (char*) C753SetVerticalNRCoefficient2__Q24chip13DriverChip753UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalRAMPCounterLimitValue__Q24chip13DriverChip753Us", (char*) C753SetVerticalRAMPCounterLimitValue__Q24chip13DriverChip753Us, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalSyncSignalAbsenceJudgmentValue__Q24chip13DriverChip753Uc", (char*) C753SetVerticalSyncSignalAbsenceJudgmentValue__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753SetVerticalSyncSignalPresenceJudgmentValue__Q24chip13DriverChip753Uc", (char*) C753SetVerticalSyncSignalPresenceJudgmentValue__Q24chip13DriverChip753Uc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753WriteN1BitPixels__Q24chip13DriverChip753UsP10tagRGBQUADPPUcPUc", (char*) C753WriteN1BitPixels__Q24chip13DriverChip753UsP10tagRGBQUADPPUcPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753WriteN24BitPixels__Q24chip13DriverChip753UsPUc", (char*) C753WriteN24BitPixels__Q24chip13DriverChip753UsPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753WriteN8BitPixels__Q24chip13DriverChip753UsP10tagRGBQUADPUc", (char*) C753WriteN8BitPixels__Q24chip13DriverChip753UsP10tagRGBQUADPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753WritePixel__Q24chip13DriverChip753UcUcUcUc", (char*) C753WritePixel__Q24chip13DriverChip753UcUcUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C753_Reset", (char*) C753_Reset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "C772_Reset", (char*) C772_Reset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CloseBus", (char*) CloseBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CpLDDogClose", (char*) CpLDDogClose, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "CpLDDogOpen", (char*) CpLDDogOpen, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "DCACHE_CTRL", (char*) &DCACHE_CTRL, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "EnableCe", (char*) EnableCe, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FLASH_CalBackTest", (char*) FLASH_CalBackTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FPGA_Read__Q24chip7FPGABusUsRUs", (char*) FPGA_Read__Q24chip7FPGABusUsRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FPGA_Write__Q24chip7FPGABusUsUs", (char*) FPGA_Write__Q24chip7FPGABusUsUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FileSysTest", (char*) FileSysTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashPageRTest", (char*) FlashPageRTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashPageWTest", (char*) FlashPageWTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashReadTest", (char*) FlashReadTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashTest", (char*) FlashTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FlashWriteTest", (char*) FlashWriteTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "FreeNandFlashBuffer", (char*) FreeNandFlashBuffer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Gbase__9streambuf", (char*) Gbase__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetBankRegister__Q24chip13DriverChip772UlRUc", (char*) GetBankRegister__Q24chip13DriverChip772UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetNandBufLength", (char*) GetNandBufLength, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetNandFlashBuffer", (char*) GetNandFlashBuffer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetRtc", (char*) GetRtc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "GetSi5326Reg", (char*) GetSi5326Reg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2C_Driver", (char*) I2C_Driver, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2C_Read__Q24chip6I2CBusUlUlUcRUc", (char*) I2C_Read__Q24chip6I2CBusUlUlUcRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2C_Write__Q24chip6I2CBusUlUlUcUc", (char*) I2C_Write__Q24chip6I2CBusUlUlUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cClk", (char*) I2cClk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cClkCycles", (char*) I2cClkCycles, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cCpldReset", (char*) I2cCpldReset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cData", (char*) I2cData, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cDeviceBusy", (char*) I2cDeviceBusy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cRead", (char*) I2cRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cRead1014", (char*) I2cRead1014, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadBit", (char*) I2cReadBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadByte", (char*) I2cReadByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadCpld", (char*) I2cReadCpld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadSeq", (char*) I2cReadSeq, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cReadTest", (char*) I2cReadTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cStop", (char*) I2cStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cWrite", (char*) I2cWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cWriteBit", (char*) I2cWriteBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cWriteByte", (char*) I2cWriteByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "I2cWritePage", (char*) I2cWritePage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ICS307_CLK_OP", (char*) ICS307_CLK_OP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ICS307_Data_OP", (char*) ICS307_Data_OP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ICS307_SS_OP", (char*) ICS307_SS_OP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ICS307_SendByte", (char*) ICS307_SendByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ICS307_SendDWORD", (char*) ICS307_SendDWORD, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ICS307_WriteBit", (char*) ICS307_WriteBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ICS307_config", (char*) ICS307_config, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ICS307_delay", (char*) ICS307_delay, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InflateTest", (char*) InflateTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IniBlockWrite", (char*) IniBlockWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "IniBlockWriteTask", (char*) IniBlockWriteTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "InitSi5326", (char*) InitSi5326, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__10MsgHandler", (char*) Instance__10MsgHandler, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__7IServer", (char*) Instance__7IServer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Instance__Q23ent10EntSetting", (char*) Instance__Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LedAlarmStateChg", (char*) LedAlarmStateChg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LedDrvInit", (char*) LedDrvInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LedRunStateChg", (char*) LedRunStateChg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LedStateChg", (char*) LedStateChg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LoadFpga_ALTERA", (char*) LoadFpga_ALTERA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "LoadFpga_LATTICE", (char*) LoadFpga_LATTICE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandAddrRead", (char*) NandAddrRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandAllStateRead", (char*) NandAllStateRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandBlockComp", (char*) NandBlockComp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandBlockCompTask", (char*) NandBlockCompTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandBlockStateRead", (char*) NandBlockStateRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandFileTableRead", (char*) NandFileTableRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandFileTableWrite", (char*) NandFileTableWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandFileUpgrade", (char*) NandFileUpgrade, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandFlashBlockCmp", (char*) NandFlashBlockCmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandFlashTest", (char*) NandFlashTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandLowFormat", (char*) NandLowFormat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "NandTestCheck", (char*) NandTestCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Nbase__9streambuf", (char*) Nbase__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "OpenBus", (char*) OpenBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyBlockCheck", (char*) PhyBlockCheck, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyBlockErase", (char*) PhyBlockErase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyBlockRead", (char*) PhyBlockRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyBlockWrite", (char*) PhyBlockWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyDelay", (char*) PhyDelay, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyGetStatus", (char*) PhyGetStatus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyPageRead", (char*) PhyPageRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyPageWrite", (char*) PhyPageWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PhyPageWriteTest", (char*) PhyPageWriteTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PinAClk", (char*) PinAClk, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PinACs", (char*) PinACs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PinADo", (char*) PinADo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "PrintTableBlock", (char*) PrintTableBlock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Qbox_app_entry", (char*) Qbox_app_entry, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReadLM73", (char*) ReadLM73, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReadReg", (char*) ReadReg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ReleaseNandFlashBuffer", (char*) ReleaseNandFlashBuffer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetFpga_ALTERA", (char*) ResetFpga_ALTERA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ResetFpga_LATTICE", (char*) ResetFpga_LATTICE, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SPIFlashEnable", (char*) SPIFlashEnable, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SPI_Read__Q24chip6SPIBusUlUcRUc", (char*) SPI_Read__Q24chip6SPIBusUlUcRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SPI_Write__Q24chip6SPIBusUlUcUc", (char*) SPI_Write__Q24chip6SPIBusUlUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SectorErase", (char*) SectorErase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SendNetMsg__7IServeriPcUl", (char*) SendNetMsg__7IServeriPcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Server_SM", (char*) &Server_SM, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "Server__7IServer", (char*) Server__7IServer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetBankRegister__Q24chip13DriverChip772UlUc", (char*) SetBankRegister__Q24chip13DriverChip772UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetRtc", (char*) SetRtc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SetSi5326Reg", (char*) SetSi5326Reg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi0Test", (char*) Spi0Test, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi0Test3", (char*) Spi0Test3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiCS_OFF", (char*) SpiCS_OFF, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiCS_ON", (char*) SpiCS_ON, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiFlashWrite", (char*) SpiFlashWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiRead", (char*) SpiRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiReadBit", (char*) SpiReadBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiReadByte", (char*) SpiReadByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiWrite", (char*) SpiWrite, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiWriteBit", (char*) SpiWriteBit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "SpiWriteByte", (char*) SpiWriteByte, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_753_Read", (char*) Spi_753_Read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_753_Read1", (char*) Spi_753_Read1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_753_Write", (char*) Spi_753_Write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_753_Write1", (char*) Spi_753_Write1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_753_test1", (char*) Spi_753_test1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C753_Bank_get", (char*) Spi_C753_Bank_get, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C753_Bank_set", (char*) Spi_C753_Bank_set, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C753_OFF", (char*) Spi_C753_OFF, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C753_ON", (char*) Spi_C753_ON, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C753_Read", (char*) Spi_C753_Read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C753_Write", (char*) Spi_C753_Write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_Bank_get", (char*) Spi_C772_Bank_get, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_Bank_set", (char*) Spi_C772_Bank_set, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_OFF", (char*) Spi_C772_OFF, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_ON", (char*) Spi_C772_ON, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_Read", (char*) Spi_C772_Read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_Read1", (char*) Spi_C772_Read1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_Write", (char*) Spi_C772_Write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_Write1", (char*) Spi_C772_Write1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_C772_test1", (char*) Spi_C772_test1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_FPGA_OFF", (char*) Spi_FPGA_OFF, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_FPGA_ON", (char*) Spi_FPGA_ON, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_FPGA_Read", (char*) Spi_FPGA_Read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_FPGA_Write", (char*) Spi_FPGA_Write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_PP", (char*) Spi_PP, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_Read", (char*) Spi_Read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_Test", (char*) Spi_Test, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Spi_Write", (char*) Spi_Write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TempTest", (char*) TempTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestBspTimer", (char*) TestBspTimer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestCpld", (char*) TestCpld, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "TestLm73", (char*) TestLm73, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UnpackMsg__7MsgBaseR7MsgInfo", (char*) UnpackMsg__7MsgBaseR7MsgInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyJobAdd", (char*) UrgencyJobAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyJobAlloc", (char*) UrgencyJobAlloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyLibInit", (char*) UrgencyLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyShow", (char*) UrgencyShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyStart", (char*) UrgencyStart, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyStop", (char*) UrgencyStop, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "UrgencyTask", (char*) UrgencyTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Wait_For_SPIF", (char*) Wait_For_SPIF, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "Wait_For_WEL", (char*) Wait_For_WEL, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WriteLM73", (char*) WriteLM73, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "WriteReg", (char*) WriteReg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10MsgHandler", (char*) _$_10MsgHandler, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_10bad_typeid", (char*) _$_10bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11logic_error", (char*) _$_11logic_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_11range_error", (char*) _$_11range_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12domain_error", (char*) _$_12domain_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12length_error", (char*) _$_12length_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12out_of_range", (char*) _$_12out_of_range, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_12streammarker", (char*) _$_12streammarker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_13bad_exception", (char*) _$_13bad_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_13runtime_error", (char*) _$_13runtime_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_14__si_type_info", (char*) _$_14__si_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_14overflow_error", (char*) _$_14overflow_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_15underflow_error", (char*) _$_15underflow_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_16__user_type_info", (char*) _$_16__user_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_16invalid_argument", (char*) _$_16invalid_argument, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_17__class_type_info", (char*) _$_17__class_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_22_IO_istream_withassign", (char*) _$_22_IO_istream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_22_IO_ostream_withassign", (char*) _$_22_IO_ostream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_3ios", (char*) _$_3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7IServer", (char*) _$_7IServer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7MsgBase", (char*) _$_7MsgBase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7filebuf", (char*) _$_7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7istream", (char*) _$_7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_7ostream", (char*) _$_7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_8bad_cast", (char*) _$_8bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_8iostream", (char*) _$_8iostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9CommModel", (char*) _$_9CommModel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9bad_alloc", (char*) _$_9bad_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9exception", (char*) _$_9exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9streambuf", (char*) _$_9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_9type_info", (char*) _$_9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q23ent10EntSetting", (char*) _$_Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q23msg13TaskCheckFPGA", (char*) _$_Q23msg13TaskCheckFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q23msg5Event", (char*) _$_Q23msg5Event, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q23msg6BGTest", (char*) _$_Q23msg6BGTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q23msg6Status", (char*) _$_Q23msg6Status, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q23msg7Channel", (char*) _$_Q23msg7Channel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q23msg7Windows", (char*) _$_Q23msg7Windows, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q23msg9BusDriver", (char*) _$_Q23msg9BusDriver, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip13DriverChip753", (char*) _$_Q24chip13DriverChip753, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip13DriverChip772", (char*) _$_Q24chip13DriverChip772, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip14DriverChip5160", (char*) _$_Q24chip14DriverChip5160, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip14DriverChipFPGA", (char*) _$_Q24chip14DriverChipFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip15DriverChip9388A", (char*) _$_Q24chip15DriverChip9388A, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip16DriverChipICS307", (char*) _$_Q24chip16DriverChipICS307, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip6I2CBus", (char*) _$_Q24chip6I2CBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip6SPIBus", (char*) _$_Q24chip6SPIBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q24chip7FPGABus", (char*) _$_Q24chip7FPGABus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q27chipApp8AppScale", (char*) _$_Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_Q2t24__default_alloc_template2b1i05_Lock", (char*) _$_Q2t24__default_alloc_template2b1i05_Lock, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_$_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) _$_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_10MsgHandler$m_instance", (char*) &_10MsgHandler$m_instance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_7IServer$m_instance", (char*) &_7IServer$m_instance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_7filebuf$openprot", (char*) _7filebuf$openprot, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_10MsgHandler$m_instance", (char*) _GLOBAL_$D$_10MsgHandler$m_instance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_7IServer$m_instance", (char*) _GLOBAL_$D$_7IServer$m_instance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_IO_stdin_", (char*) _GLOBAL_$D$_IO_stdin_, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_Q23ent10EntSetting$m_instance", (char*) _GLOBAL_$D$_Q23ent10EntSetting$m_instance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__7MsgBase", (char*) _GLOBAL_$D$__7MsgBase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__9CommModel", (char*) _GLOBAL_$D$__9CommModel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q23msg13TaskCheckFPGA", (char*) _GLOBAL_$D$__Q23msg13TaskCheckFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q23msg5Event", (char*) _GLOBAL_$D$__Q23msg5Event, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q23msg6BGTest", (char*) _GLOBAL_$D$__Q23msg6BGTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q23msg6Status", (char*) _GLOBAL_$D$__Q23msg6Status, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q23msg7Channel", (char*) _GLOBAL_$D$__Q23msg7Channel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q23msg7Windows", (char*) _GLOBAL_$D$__Q23msg7Windows, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q23msg9BusDriver", (char*) _GLOBAL_$D$__Q23msg9BusDriver, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q24chip13DriverChip772", (char*) _GLOBAL_$D$__Q24chip13DriverChip772, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q24chip14DriverChip5160", (char*) _GLOBAL_$D$__Q24chip14DriverChip5160, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q24chip6I2CBus", (char*) _GLOBAL_$D$__Q24chip6I2CBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$__Q27chipApp8AppScale", (char*) _GLOBAL_$D$__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_t24__default_alloc_template2b1i0$_S_end_free", (char*) _GLOBAL_$D$_t24__default_alloc_template2b1i0$_S_end_free, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$_un_link__9streambuf", (char*) _GLOBAL_$D$_un_link__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$D$testMenu", (char*) _GLOBAL_$D$testMenu, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_10MsgHandler$m_instance", (char*) _GLOBAL_$I$_10MsgHandler$m_instance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_7IServer$m_instance", (char*) _GLOBAL_$I$_7IServer$m_instance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_IO_stdin_", (char*) _GLOBAL_$I$_IO_stdin_, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_Q23ent10EntSetting$m_instance", (char*) _GLOBAL_$I$_Q23ent10EntSetting$m_instance, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__7MsgBase", (char*) _GLOBAL_$I$__7MsgBase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__9CommModel", (char*) _GLOBAL_$I$__9CommModel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q23msg13TaskCheckFPGA", (char*) _GLOBAL_$I$__Q23msg13TaskCheckFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q23msg5Event", (char*) _GLOBAL_$I$__Q23msg5Event, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q23msg6BGTest", (char*) _GLOBAL_$I$__Q23msg6BGTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q23msg6Status", (char*) _GLOBAL_$I$__Q23msg6Status, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q23msg7Channel", (char*) _GLOBAL_$I$__Q23msg7Channel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q23msg7Windows", (char*) _GLOBAL_$I$__Q23msg7Windows, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q23msg9BusDriver", (char*) _GLOBAL_$I$__Q23msg9BusDriver, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q24chip13DriverChip772", (char*) _GLOBAL_$I$__Q24chip13DriverChip772, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q24chip14DriverChip5160", (char*) _GLOBAL_$I$__Q24chip14DriverChip5160, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q24chip6I2CBus", (char*) _GLOBAL_$I$__Q24chip6I2CBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$__Q27chipApp8AppScale", (char*) _GLOBAL_$I$__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_t24__default_alloc_template2b1i0$_S_end_free", (char*) _GLOBAL_$I$_t24__default_alloc_template2b1i0$_S_end_free, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$_un_link__9streambuf", (char*) _GLOBAL_$I$_un_link__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_GLOBAL_$I$testMenu", (char*) _GLOBAL_$I$testMenu, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "_Q23ent10EntSetting$m_instance", (char*) &_Q23ent10EntSetting$m_instance, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_Randseed", (char*) &_Randseed, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_S_chunk_alloc__t24__default_alloc_template2b1i0UlRi", (char*) _S_chunk_alloc__t24__default_alloc_template2b1i0UlRi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_freelist_index__t24__default_alloc_template2b1i0Ul", (char*) _S_freelist_index__t24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_oom_malloc__t23__malloc_alloc_template1i0Ul", (char*) _S_oom_malloc__t23__malloc_alloc_template1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_oom_realloc__t23__malloc_alloc_template1i0PvUl", (char*) _S_oom_realloc__t23__malloc_alloc_template1i0PvUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_refill__t24__default_alloc_template2b1i0Ul", (char*) _S_refill__t24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_S_round_up__t24__default_alloc_template2b1i0Ul", (char*) _S_round_up__t24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10MsgHandler", (char*) __10MsgHandler, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__10bad_typeid", (char*) __10bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11logic_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __11logic_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__11range_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __11range_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12domain_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __12domain_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12length_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __12length_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12out_of_rangeRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __12out_of_rangeRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__12streammarkerP9streambuf", (char*) __12streammarkerP9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13bad_exception", (char*) __13bad_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13runtime_error", (char*) __13runtime_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__13runtime_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __13runtime_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14__si_type_infoPCcRC16__user_type_info", (char*) __14__si_type_infoPCcRC16__user_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__14overflow_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __14overflow_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__15underflow_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __15underflow_errorRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__16__user_type_infoPCc", (char*) __16__user_type_infoPCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__16invalid_argumentRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __16invalid_argumentRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__17__class_type_infoPCcPCQ217__class_type_info9base_infoUl", (char*) __17__class_type_infoPCcPCQ217__class_type_info9base_infoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__3iosP9streambufP7ostream", (char*) __3iosP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7IServer", (char*) __7IServer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7MsgBase", (char*) __7MsgBase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7filebuf", (char*) __7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7filebufi", (char*) __7filebufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7filebufiPci", (char*) __7filebufiPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7istreami", (char*) __7istreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7istreamiP9streambufP7ostream", (char*) __7istreamiP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7ostreami", (char*) __7ostreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__7ostreamiP9streambufP7ostream", (char*) __7ostreamiP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8bad_cast", (char*) __8bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8iostreami", (char*) __8iostreami, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__8iostreamiP9streambufP7ostream", (char*) __8iostreamiP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__9CommModel", (char*) __9CommModel, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "__Q23ent10EntSetting", (char*) __Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23ios4Init", (char*) __Q23ios4Init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23msg13TaskCheckFPGA", (char*) __Q23msg13TaskCheckFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23msg5Event", (char*) __Q23msg5Event, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23msg6BGTest", (char*) __Q23msg6BGTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23msg6Status", (char*) __Q23msg6Status, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23msg7Channel", (char*) __Q23msg7Channel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23msg7Windows", (char*) __Q23msg7Windows, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q23msg9BusDriver", (char*) __Q23msg9BusDriver, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip13DriverChip753", (char*) __Q24chip13DriverChip753, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip13DriverChip772", (char*) __Q24chip13DriverChip772, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip14DriverChip5160", (char*) __Q24chip14DriverChip5160, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip14DriverChipFPGA", (char*) __Q24chip14DriverChipFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip15DriverChip9388A", (char*) __Q24chip15DriverChip9388A, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip16DriverChipICS307", (char*) __Q24chip16DriverChipICS307, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip6I2CBus", (char*) __Q24chip6I2CBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip6SPIBus", (char*) __Q24chip6SPIBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q24chip7FPGABus", (char*) __Q24chip7FPGABus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__Q27chipApp8AppScale", (char*) __Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "___x_gnu_cstrmain_o", (char*) &___x_gnu_cstrmain_o, 0, SYM_GLOBAL | SYM_DATA},
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
        {{NULL}, "___x_gnu_opdel_o", (char*) &___x_gnu_opdel_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_opnew_o", (char*) &___x_gnu_opnew_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_opvdel_o", (char*) &___x_gnu_opvdel_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_opvnew_o", (char*) &___x_gnu_opvnew_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_outfloat_o", (char*) &___x_gnu_outfloat_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_peekc_o", (char*) &___x_gnu_peekc_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_sbscan_o", (char*) &___x_gnu_sbscan_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_stdexcepti_o", (char*) &___x_gnu_stdexcepti_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_stdstrbufs_o", (char*) &___x_gnu_stdstrbufs_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_stdstreams_o", (char*) &___x_gnu_stdstreams_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_stlinst_o", (char*) &___x_gnu_stlinst_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_streambuf_o", (char*) &___x_gnu_streambuf_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_tinfo2_o", (char*) &___x_gnu_tinfo2_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "___x_gnu_tinfo_o", (char*) &___x_gnu_tinfo_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__add64", (char*) __add64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__adddf3", (char*) __adddf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__addsf3", (char*) __addsf3, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc", (char*) __apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c", (char*) __apl__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__arm_call_via_o", (char*) &__arm_call_via_o, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__as__22_IO_istream_withassignR22_IO_istream_withassign", (char*) __as__22_IO_istream_withassignR22_IO_istream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__22_IO_istream_withassignR7istream", (char*) __as__22_IO_istream_withassignR7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__22_IO_ostream_withassignR22_IO_ostream_withassign", (char*) __as__22_IO_ostream_withassignR22_IO_ostream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__22_IO_ostream_withassignR7ostream", (char*) __as__22_IO_ostream_withassignR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc", (char*) __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c", (char*) __as__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "__dl__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepPv", (char*) __dl__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dunder", (char*) __dunder, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dunder_d", (char*) __dunder_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dynamic_cast", (char*) __dynamic_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__dynamic_cast_2", (char*) __dynamic_cast_2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eh_alloc", (char*) __eh_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eh_free", (char*) __eh_free, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eh_rtime_match", (char*) __eh_rtime_match, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__empty", (char*) __empty, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq64", (char*) __eq64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq__C9type_infoRC9type_info", (char*) __eq__C9type_infoRC9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b", (char*) __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b", (char*) __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b", (char*) __eq__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "__ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b", (char*) __ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b", (char*) __ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b", (char*) __ge__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gedf2", (char*) __gedf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gesf2", (char*) __gesf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getDstInfo", (char*) __getDstInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getTime", (char*) __getTime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__getZoneInfo", (char*) __getZoneInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__get_dynamic_handler_chain", (char*) __get_dynamic_handler_chain, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__get_eh_context", (char*) __get_eh_context, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__get_eh_info", (char*) __get_eh_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gt64", (char*) __gt64, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b", (char*) __gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b", (char*) __gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b", (char*) __gt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "__le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b", (char*) __le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b", (char*) __le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b", (char*) __le__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ledf2", (char*) __ledf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__length_error__FPCc", (char*) __length_error__FPCc, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "__lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b", (char*) __lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b", (char*) __lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b", (char*) __lt__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "__ne__C9type_infoRC9type_info", (char*) __ne__C9type_infoRC9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b", (char*) __ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b", (char*) __ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b", (char*) __ne__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_b, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__nedf2", (char*) __nedf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negdf2", (char*) __negdf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negdi2", (char*) __negdi2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__negsf2", (char*) __negsf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__nesf2", (char*) __nesf2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__new_handler", (char*) &__new_handler, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__nt__C3ios", (char*) __nt__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__nw__FUlPv", (char*) __nw__FUlPv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__nw__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlUl", (char*) __nw__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__opPv__C3ios", (char*) __opPv__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__out_of_range__FPCc", (char*) __out_of_range__FPCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__overflow", (char*) __overflow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__overflow__FP9streambufi", (char*) __overflow__FP9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pack_d", (char*) __pack_d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pack_f", (char*) __pack_f, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_t12basic_string3ZX01ZX11ZX21", (char*) __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_PCX01RCt12basic_string3ZX01ZX11ZX21_t12basic_string3ZX01ZX11ZX21, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_t12basic_string3ZX01ZX11ZX21", (char*) __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21PCX01_t12basic_string3ZX01ZX11ZX21, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_t12basic_string3ZX01ZX11ZX21", (char*) __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21T0_t12basic_string3ZX01ZX11ZX21, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21X01_t12basic_string3ZX01ZX11ZX21", (char*) __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_RCt12basic_string3ZX01ZX11ZX21X01_t12basic_string3ZX01ZX11ZX21, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_X01RCt12basic_string3ZX01ZX11ZX21_t12basic_string3ZX01ZX11ZX21", (char*) __pl__H3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_X01RCt12basic_string3ZX01ZX11ZX21_t12basic_string3ZX01ZX11ZX21, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc", (char*) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl", (char*) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc", (char*) __t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__terminate", (char*) __terminate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__terminate_func", (char*) &__terminate_func, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "__tf10MsgHandler", (char*) __tf10MsgHandler, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf10bad_typeid", (char*) __tf10bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf11logic_error", (char*) __tf11logic_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf11range_error", (char*) __tf11range_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12domain_error", (char*) __tf12domain_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12length_error", (char*) __tf12length_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf12out_of_range", (char*) __tf12out_of_range, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf13bad_exception", (char*) __tf13bad_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf13runtime_error", (char*) __tf13runtime_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf14__si_type_info", (char*) __tf14__si_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf14overflow_error", (char*) __tf14overflow_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf15underflow_error", (char*) __tf15underflow_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf16__user_type_info", (char*) __tf16__user_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf16invalid_argument", (char*) __tf16invalid_argument, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf17__class_type_info", (char*) __tf17__class_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf22_IO_istream_withassign", (char*) __tf22_IO_istream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf22_IO_ostream_withassign", (char*) __tf22_IO_ostream_withassign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf3ios", (char*) __tf3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7IServer", (char*) __tf7IServer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7MsgBase", (char*) __tf7MsgBase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7filebuf", (char*) __tf7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7istream", (char*) __tf7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf7ostream", (char*) __tf7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf8bad_cast", (char*) __tf8bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf8iostream", (char*) __tf8iostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9CommModel", (char*) __tf9CommModel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9bad_alloc", (char*) __tf9bad_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9exception", (char*) __tf9exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9streambuf", (char*) __tf9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tf9type_info", (char*) __tf9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ23ent10EntSetting", (char*) __tfQ23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ23msg13TaskCheckFPGA", (char*) __tfQ23msg13TaskCheckFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ23msg5Event", (char*) __tfQ23msg5Event, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ23msg6BGTest", (char*) __tfQ23msg6BGTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ23msg6Status", (char*) __tfQ23msg6Status, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ23msg7Channel", (char*) __tfQ23msg7Channel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ23msg7Windows", (char*) __tfQ23msg7Windows, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ23msg9BusDriver", (char*) __tfQ23msg9BusDriver, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip13DriverChip753", (char*) __tfQ24chip13DriverChip753, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip13DriverChip772", (char*) __tfQ24chip13DriverChip772, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip14DriverChip5160", (char*) __tfQ24chip14DriverChip5160, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip14DriverChipFPGA", (char*) __tfQ24chip14DriverChipFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip15DriverChip9388A", (char*) __tfQ24chip15DriverChip9388A, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip16DriverChipICS307", (char*) __tfQ24chip16DriverChipICS307, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip6I2CBus", (char*) __tfQ24chip6I2CBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip6SPIBus", (char*) __tfQ24chip6SPIBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ24chip7FPGABus", (char*) __tfQ24chip7FPGABus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__tfQ27chipApp8AppScale", (char*) __tfQ27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "__ti10MsgHandler", (char*) &__ti10MsgHandler, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti10bad_typeid", (char*) &__ti10bad_typeid, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11_ios_fields", (char*) &__ti11_ios_fields, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11logic_error", (char*) &__ti11logic_error, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti11range_error", (char*) &__ti11range_error, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12domain_error", (char*) &__ti12domain_error, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12length_error", (char*) &__ti12length_error, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti12out_of_range", (char*) &__ti12out_of_range, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti13bad_exception", (char*) &__ti13bad_exception, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti13ostringstream", (char*) &__ti13ostringstream, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti13runtime_error", (char*) &__ti13runtime_error, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14__si_type_info", (char*) &__ti14__si_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti14overflow_error", (char*) &__ti14overflow_error, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti15ModuleInterface", (char*) &__ti15ModuleInterface, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti15underflow_error", (char*) &__ti15underflow_error, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__attr_type_info", (char*) &__ti16__attr_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__func_type_info", (char*) &__ti16__func_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__ptmd_type_info", (char*) &__ti16__ptmd_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__ptmf_type_info", (char*) &__ti16__ptmf_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16__user_type_info", (char*) &__ti16__user_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16invalid_argument", (char*) &__ti16invalid_argument, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti16stringstreambase", (char*) &__ti16stringstreambase, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti17__array_type_info", (char*) &__ti17__array_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti17__class_type_info", (char*) &__ti17__class_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti19__builtin_type_info", (char*) &__ti19__builtin_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti19__pointer_type_info", (char*) &__ti19__pointer_type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti22_IO_istream_withassign", (char*) &__ti22_IO_istream_withassign, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti22_IO_ostream_withassign", (char*) &__ti22_IO_ostream_withassign, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti3ios", (char*) &__ti3ios, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7IServer", (char*) &__ti7IServer, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7MsgBase", (char*) &__ti7MsgBase, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7filebuf", (char*) &__ti7filebuf, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7istream", (char*) &__ti7istream, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti7ostream", (char*) &__ti7ostream, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8_IO_FILE", (char*) &__ti8_IO_FILE, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8bad_cast", (char*) &__ti8bad_cast, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti8iostream", (char*) &__ti8iostream, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9CommModel", (char*) &__ti9CommModel, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9bad_alloc", (char*) &__ti9bad_alloc, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9exception", (char*) &__ti9exception, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9streambuf", (char*) &__ti9streambuf, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9stringbuf", (char*) &__ti9stringbuf, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__ti9type_info", (char*) &__ti9type_info, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ23ent10EntSetting", (char*) &__tiQ23ent10EntSetting, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ23msg13TaskCheckFPGA", (char*) &__tiQ23msg13TaskCheckFPGA, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ23msg5Event", (char*) &__tiQ23msg5Event, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ23msg6BGTest", (char*) &__tiQ23msg6BGTest, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ23msg6Status", (char*) &__tiQ23msg6Status, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ23msg7Channel", (char*) &__tiQ23msg7Channel, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ23msg7Windows", (char*) &__tiQ23msg7Windows, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ23msg9BusDriver", (char*) &__tiQ23msg9BusDriver, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip13DriverChip753", (char*) &__tiQ24chip13DriverChip753, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip13DriverChip772", (char*) &__tiQ24chip13DriverChip772, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip14DriverChip5160", (char*) &__tiQ24chip14DriverChip5160, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip14DriverChipFPGA", (char*) &__tiQ24chip14DriverChipFPGA, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip15DriverChip9388A", (char*) &__tiQ24chip15DriverChip9388A, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip16DriverChipICS307", (char*) &__tiQ24chip16DriverChipICS307, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip6I2CBus", (char*) &__tiQ24chip6I2CBus, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip6SPIBus", (char*) &__tiQ24chip6SPIBus, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ24chip7FPGABus", (char*) &__tiQ24chip7FPGABus, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "__tiQ27chipApp8AppScale", (char*) &__tiQ27chipApp8AppScale, 0, SYM_GLOBAL | SYM_BSS},
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
        {{NULL}, "__vc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) __vc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vc__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl", (char*) __vc__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "__vc__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) __vc__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "_find__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCccUlUl", (char*) _find__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCccUlUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0$nilRep", (char*) &_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0$nilRep, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0$npos", (char*) _t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0$npos, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_t23__malloc_alloc_template1i0$__malloc_alloc_oom_handler", (char*) &_t23__malloc_alloc_template1i0$__malloc_alloc_oom_handler, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_end_free", (char*) &_t24__default_alloc_template2b1i0$_S_end_free, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_free_list", (char*) &_t24__default_alloc_template2b1i0$_S_free_list, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_heap_size", (char*) &_t24__default_alloc_template2b1i0$_S_heap_size, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_node_allocator_lock", (char*) &_t24__default_alloc_template2b1i0$_S_node_allocator_lock, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "_t24__default_alloc_template2b1i0$_S_start_free", (char*) &_t24__default_alloc_template2b1i0$_S_start_free, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "_throw_failure__C3ios", (char*) _throw_failure__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_un_link__9streambuf", (char*) _un_link__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10MsgHandler", (char*) _vt$10MsgHandler, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$10bad_typeid", (char*) _vt$10bad_typeid, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$11logic_error", (char*) _vt$11logic_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$11range_error", (char*) _vt$11range_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12domain_error", (char*) _vt$12domain_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12length_error", (char*) _vt$12length_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$12out_of_range", (char*) _vt$12out_of_range, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$13bad_exception", (char*) _vt$13bad_exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$13runtime_error", (char*) _vt$13runtime_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$14__si_type_info", (char*) _vt$14__si_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$14overflow_error", (char*) _vt$14overflow_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$15underflow_error", (char*) _vt$15underflow_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$16__user_type_info", (char*) _vt$16__user_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$16invalid_argument", (char*) _vt$16invalid_argument, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$17__class_type_info", (char*) _vt$17__class_type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$22_IO_istream_withassign$3ios", (char*) _vt$22_IO_istream_withassign$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$22_IO_ostream_withassign$3ios", (char*) _vt$22_IO_ostream_withassign$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$3ios", (char*) _vt$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7IServer", (char*) _vt$7IServer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7MsgBase", (char*) _vt$7MsgBase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7filebuf", (char*) _vt$7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7istream$3ios", (char*) _vt$7istream$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$7ostream$3ios", (char*) _vt$7ostream$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$8bad_cast", (char*) _vt$8bad_cast, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$8iostream$3ios", (char*) _vt$8iostream$3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9CommModel", (char*) _vt$9CommModel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9CommModel$15ModuleInterface", (char*) _vt$9CommModel$15ModuleInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9bad_alloc", (char*) _vt$9bad_alloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9exception", (char*) _vt$9exception, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9streambuf", (char*) _vt$9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$9type_info", (char*) _vt$9type_info, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23ent10EntSetting", (char*) _vt$Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg13TaskCheckFPGA", (char*) _vt$Q23msg13TaskCheckFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg13TaskCheckFPGA$15ModuleInterface", (char*) _vt$Q23msg13TaskCheckFPGA$15ModuleInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg5Event", (char*) _vt$Q23msg5Event, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg5Event$15ModuleInterface", (char*) _vt$Q23msg5Event$15ModuleInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg6BGTest", (char*) _vt$Q23msg6BGTest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg6BGTest$15ModuleInterface", (char*) _vt$Q23msg6BGTest$15ModuleInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg6Status", (char*) _vt$Q23msg6Status, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg6Status$15ModuleInterface", (char*) _vt$Q23msg6Status$15ModuleInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg7Channel", (char*) _vt$Q23msg7Channel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg7Channel$15ModuleInterface", (char*) _vt$Q23msg7Channel$15ModuleInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg7Windows", (char*) _vt$Q23msg7Windows, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg7Windows$15ModuleInterface", (char*) _vt$Q23msg7Windows$15ModuleInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg9BusDriver", (char*) _vt$Q23msg9BusDriver, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg9BusDriver$15ModuleInterface", (char*) _vt$Q23msg9BusDriver$15ModuleInterface, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg9BusDriver$Q24chip6I2CBus", (char*) _vt$Q23msg9BusDriver$Q24chip6I2CBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q23msg9BusDriver$Q24chip6SPIBus", (char*) _vt$Q23msg9BusDriver$Q24chip6SPIBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip13DriverChip753", (char*) _vt$Q24chip13DriverChip753, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip13DriverChip772", (char*) _vt$Q24chip13DriverChip772, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip14DriverChip5160", (char*) _vt$Q24chip14DriverChip5160, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip14DriverChipFPGA", (char*) _vt$Q24chip14DriverChipFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip15DriverChip9388A", (char*) _vt$Q24chip15DriverChip9388A, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip16DriverChipICS307", (char*) _vt$Q24chip16DriverChipICS307, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip6I2CBus", (char*) _vt$Q24chip6I2CBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip6SPIBus", (char*) _vt$Q24chip6SPIBus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q24chip7FPGABus", (char*) _vt$Q24chip7FPGABus, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q27chipApp8AppScale", (char*) _vt$Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "_vt$Q27chipApp8AppScale$Q24chip16DriverChipICS307", (char*) _vt$Q27chipApp8AppScale$Q24chip16DriverChipICS307, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "alloc__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulb", (char*) alloc__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocate__9streambuf", (char*) allocate__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocate__t23__malloc_alloc_template1i0Ul", (char*) allocate__t23__malloc_alloc_template1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocate__t24__default_alloc_template2b1i0Ul", (char*) allocate__t24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "allocbuf__9streambuf", (char*) allocbuf__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc", (char*) append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl", (char*) append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc", (char*) append__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc", (char*) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl", (char*) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc", (char*) assign__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "assign__t18string_char_traits1ZcRcRCc", (char*) assign__t18string_char_traits1ZcRcRCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthFlagsSet", (char*) at91EthFlagsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthInit", (char*) at91EthInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthLoopSet", (char*) at91EthLoopSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthMCastAdd", (char*) at91EthMCastAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthMCastDel", (char*) at91EthMCastDel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91EthMiiShow", (char*) at91EthMiiShow, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "at91IntDevInit", (char*) at91IntDevInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91SioDevInit", (char*) at91SioDevInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91SioDevInit2", (char*) at91SioDevInit2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at91SioInt", (char*) at91SioInt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) at__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "at__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) at__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "begin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) begin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "begin__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) begin__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "broadcastMsg__10MsgHandlerP7MsgInfo", (char*) broadcastMsg__10MsgHandlerP7MsgInfo, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "c_str__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) c_str__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "calculate6SymbolLUT__Q27chipApp8AppScalePfT1PUc", (char*) calculate6SymbolLUT__Q27chipApp8AppScalePfT1PUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "calloc", (char*) calloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "capacity__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) capacity__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "check_realloc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) check_realloc__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "check_trailer", (char*) check_trailer, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "checksum", (char*) checksum, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "chipGetFPGATest", (char*) chipGetFPGATest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "chipSetFPGATest", (char*) chipSetFPGATest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "chipTest__Q27chipApp8AppScale", (char*) chipTest__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "clone__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep", (char*) clone__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "close", (char*) close, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "close__3ios", (char*) close__3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "close__7filebuf", (char*) close__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "closedir", (char*) closedir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl", (char*) compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl", (char*) compare__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "compare__t18string_char_traits1ZcPCcT1Ul", (char*) compare__t18string_char_traits1ZcPCcT1Ul, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "copy__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUlUl", (char*) copy__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copy__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlPCcUl", (char*) copy__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlPCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "copy__t18string_char_traits1ZcPcPCcUl", (char*) copy__t18string_char_traits1ZcPcPCcUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "createWindow__Q23ent10EntSettingUlUlUlUl", (char*) createWindow__Q23ent10EntSettingUlUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl", (char*) create__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "creationDate", (char*) &creationDate, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "cret", (char*) cret, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ctime", (char*) ctime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ctime_r", (char*) ctime_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "cur_ptr__7filebuf", (char*) cur_ptr__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "currentContext", (char*) &currentContext, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "current_demangling_style", (char*) &current_demangling_style, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "d", (char*) d, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "data__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) data__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "data__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep", (char*) data__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "delWindow__Q23ent10EntSettingUl", (char*) delWindow__Q23ent10EntSettingUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "delayNSec", (char*) delayNSec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "delayUSec", (char*) delayUSec, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "delta__12streammarker", (char*) delta__12streammarker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "delta__12streammarkerR12streammarker", (char*) delta__12streammarkerR12streammarker, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "demo", (char*) demo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "demoMove", (char*) demoMove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "devSplit", (char*) devSplit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_DetectInputSignal__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_DetectInputSignal__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetAcutance__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetAcutance__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetAutoGainFlg__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetAutoGainFlg__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetBrightness__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetBrightness__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetColorPhasic__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetColorPhasic__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetColorScope__Q24chip14DriverChip5160UlRUcT2", (char*) dev_5160_GetColorScope__Q24chip14DriverChip5160UlRUcT2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetContrast__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetContrast__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetInputType__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetInputType__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetManualGainValue__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetManualGainValue__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetSaturation__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetSaturation__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetSignalMode__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetSignalMode__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_GetVsFreq__Q24chip14DriverChip5160UlRUc", (char*) dev_5160_GetVsFreq__Q24chip14DriverChip5160UlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_InitTVP5160__Q24chip14DriverChip5160Ul", (char*) dev_5160_InitTVP5160__Q24chip14DriverChip5160Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetAcutance__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetAcutance__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetAutoGainFlg__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetAutoGainFlg__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetBrightness__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetBrightness__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetColorPhasic__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetColorPhasic__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetColorScope__Q24chip14DriverChip5160UlUcUc", (char*) dev_5160_SetColorScope__Q24chip14DriverChip5160UlUcUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetContrast__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetContrast__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetInputType__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetInputType__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetManualGainValue__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetManualGainValue__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetSaturation__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetSaturation__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_5160_SetSignalMode__Q24chip14DriverChip5160UlUc", (char*) dev_5160_SetSignalMode__Q24chip14DriverChip5160UlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_DetectInput__Q24chip15DriverChip9388AUlRUc", (char*) dev_ARGB_DetectInput__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_GeneralConfig__Q24chip15DriverChip9388AUl", (char*) dev_ARGB_GeneralConfig__Q24chip15DriverChip9388AUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_GetPhase__Q24chip15DriverChip9388AUlRUc", (char*) dev_ARGB_GetPhase__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_GetSTDI__Q24chip15DriverChip9388AUlRUsN32", (char*) dev_ARGB_GetSTDI__Q24chip15DriverChip9388AUlRUsN32, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_PLLVocManEn__Q24chip15DriverChip9388AUlUc", (char*) dev_ARGB_PLLVocManEn__Q24chip15DriverChip9388AUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_Polarity__Q24chip15DriverChip9388AUlRUcT2", (char*) dev_ARGB_Polarity__Q24chip15DriverChip9388AUlRUcT2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_SetFRLCountMax__Q24chip15DriverChip9388AUlUs", (char*) dev_ARGB_SetFRLCountMax__Q24chip15DriverChip9388AUlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_SetFRLL__Q24chip15DriverChip9388AUlUs", (char*) dev_ARGB_SetFRLL__Q24chip15DriverChip9388AUlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_SetPhase__Q24chip15DriverChip9388AUlUc", (char*) dev_ARGB_SetPhase__Q24chip15DriverChip9388AUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_SetPllDivRatio__Q24chip15DriverChip9388AUlUs", (char*) dev_ARGB_SetPllDivRatio__Q24chip15DriverChip9388AUlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_SetSavEav__Q24chip15DriverChip9388AUlUsUsUsUs", (char*) dev_ARGB_SetSavEav__Q24chip15DriverChip9388AUlUsUsUsUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_ARGB_SetVCORange__Q24chip15DriverChip9388AUlUl", (char*) dev_ARGB_SetVCORange__Q24chip15DriverChip9388AUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_ChangeModel__Q24chip13DriverChip772UlUl", (char*) dev_C772_ChangeModel__Q24chip13DriverChip772UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_InitColorConversion__Q24chip13DriverChip772Ul", (char*) dev_C772_InitColorConversion__Q24chip13DriverChip772Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_InitIPConversion__Q24chip13DriverChip772Ul", (char*) dev_C772_InitIPConversion__Q24chip13DriverChip772Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_InitLUT__Q24chip13DriverChip772Ul", (char*) dev_C772_InitLUT__Q24chip13DriverChip772Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_Reset__Q24chip13DriverChip772Ul", (char*) dev_C772_Reset__Q24chip13DriverChip772Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_Set480__Q24chip13DriverChip772Ul", (char*) dev_C772_Set480__Q24chip13DriverChip772Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_Set576__Q24chip13DriverChip772Ul", (char*) dev_C772_Set576__Q24chip13DriverChip772Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_SetBlueScreen__Q24chip13DriverChip772UlUl", (char*) dev_C772_SetBlueScreen__Q24chip13DriverChip772UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_SetHorAndVerSyncCtrl__Q24chip13DriverChip772UlUlUlUlUl", (char*) dev_C772_SetHorAndVerSyncCtrl__Q24chip13DriverChip772UlUlUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_SetInputSize__Q24chip13DriverChip772UlUlUlUlUl", (char*) dev_C772_SetInputSize__Q24chip13DriverChip772UlUlUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_SetOutputSize__Q24chip13DriverChip772UlUlUlUlUl", (char*) dev_C772_SetOutputSize__Q24chip13DriverChip772UlUlUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_C772_SetOutputSyncCycle__Q24chip13DriverChip772UlUlUl", (char*) dev_C772_SetOutputSyncCycle__Q24chip13DriverChip772UlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_DRGB_DetectInput__Q24chip15DriverChip9388AUlRUc", (char*) dev_DRGB_DetectInput__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_DRGB_GeneralConfig__Q24chip15DriverChip9388AUl", (char*) dev_DRGB_GeneralConfig__Q24chip15DriverChip9388AUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_DRGB_GetSignalPara__Q24chip15DriverChip9388AUlRUcRUsN23", (char*) dev_DRGB_GetSignalPara__Q24chip15DriverChip9388AUlRUcRUsN23, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_DetectCPRun__Q24chip15DriverChip9388AUlRUc", (char*) dev_DetectCPRun__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_FPGA_Read", (char*) dev_FPGA_Read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_FPGA_Write", (char*) dev_FPGA_Write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_I2C_Read", (char*) dev_I2C_Read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_I2C_Write", (char*) dev_I2C_Write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_I2C_WriteMult__Q24chip6I2CBusUlUlGt4list2Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUcZt9allocator1Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUc", (char*) dev_I2C_WriteMult__Q24chip6I2CBusUlUlGt4list2Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUcZt9allocator1Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_I2cInit", (char*) dev_I2cInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_InitAD9388A__Q24chip15DriverChip9388AUl", (char*) dev_InitAD9388A__Q24chip15DriverChip9388AUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_InitIP00c772__Q24chip13DriverChip772Ul", (char*) dev_InitIP00c772__Q24chip13DriverChip772Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_RGB_GetBrightness__Q24chip15DriverChip9388AUlRUc", (char*) dev_RGB_GetBrightness__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_RGB_GetColorPhase__Q24chip15DriverChip9388AUlRUc", (char*) dev_RGB_GetColorPhase__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_RGB_GetContrast__Q24chip15DriverChip9388AUlRUc", (char*) dev_RGB_GetContrast__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_RGB_GetSaturation__Q24chip15DriverChip9388AUlRUc", (char*) dev_RGB_GetSaturation__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_RGB_SetBrightness__Q24chip15DriverChip9388AUlUc", (char*) dev_RGB_SetBrightness__Q24chip15DriverChip9388AUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_RGB_SetColorPhase__Q24chip15DriverChip9388AUlUc", (char*) dev_RGB_SetColorPhase__Q24chip15DriverChip9388AUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_RGB_SetContrast__Q24chip15DriverChip9388AUlUc", (char*) dev_RGB_SetContrast__Q24chip15DriverChip9388AUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_RGB_SetSaturation__Q24chip15DriverChip9388AUlUc", (char*) dev_RGB_SetSaturation__Q24chip15DriverChip9388AUlUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_SPI_Read", (char*) dev_SPI_Read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_SPI_Write", (char*) dev_SPI_Write, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_SPI_WriteMult__Q24chip6SPIBusUlGt4list2Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUcZt9allocator1Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUc", (char*) dev_SPI_WriteMult__Q24chip6SPIBusUlGt4list2Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUcZt9allocator1Zt3map4ZUcZUcZt4less1ZUcZt9allocator1ZUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_SpiCsOff", (char*) dev_SpiCsOff, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_SpiCsOn", (char*) dev_SpiCsOn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_SpiInit", (char*) dev_SpiInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "dev_spi_test", (char*) dev_spi_test, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "downloadBootrom", (char*) downloadBootrom, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "empty__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) empty__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "end__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) end__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "end__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) end__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "endl__FR7ostream", (char*) endl__FR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ends__FR7ostream", (char*) ends__FR7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envLibInit", (char*) envLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envPrivateCreate", (char*) envPrivateCreate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envPrivateDestroy", (char*) envPrivateDestroy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "envShow", (char*) envShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eof__C3ios", (char*) eof__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eos__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) eos__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eos__t18string_char_traits1Zc", (char*) eos__t18string_char_traits1Zc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "epptr__C9streambuf", (char*) epptr__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "eq__t18string_char_traits1ZcRCcT1", (char*) eq__t18string_char_traits1ZcRCcT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pc", (char*) erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1", (char*) erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl", (char*) erase__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "excess_slop__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlUl", (char*) excess_slop__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl", (char*) find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl", (char*) find__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl", (char*) find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl", (char*) find_first_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl", (char*) find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl", (char*) find_first_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl", (char*) find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl", (char*) find_last_not_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl", (char*) find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl", (char*) find_last_of__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "flashreset", (char*) flashreset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flashtest", (char*) flashtest, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "flashwrite", (char*) flashwrite, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "frob_size__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl", (char*) frob_size__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "gbump__9streambufi", (char*) gbump__9streambufi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gcount__7istream", (char*) gcount__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "get753", (char*) get753, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getBL__Q24chip15DriverChip9388AUlRUs", (char*) getBL__Q24chip15DriverChip9388AUlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getBoardTypeReg__Q24chip14DriverChipFPGARUs", (char*) getBoardTypeReg__Q24chip14DriverChipFPGARUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getC753ChnInput", (char*) getC753ChnInput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getDateReg__Q24chip14DriverChipFPGARUs", (char*) getDateReg__Q24chip14DriverChipFPGARUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getF0H__Q24chip15DriverChip9388AUlRUs", (char*) getF0H__Q24chip15DriverChip9388AUlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getF1H__Q24chip15DriverChip9388AUlRUs", (char*) getF1H__Q24chip15DriverChip9388AUlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getFL__Q24chip15DriverChip9388AUlRUs", (char*) getFL__Q24chip15DriverChip9388AUlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getHorizontalCompensation__Q27chipApp8AppScaleUsUsUc", (char*) getHorizontalCompensation__Q27chipApp8AppScaleUsUsUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getHorizontalStart__Q27chipApp8AppScaleUsUsUc", (char*) getHorizontalStart__Q27chipApp8AppScaleUsUsUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getHorizontalTotal__Q27chipApp8AppScaleUsUsUs", (char*) getHorizontalTotal__Q27chipApp8AppScaleUsUsUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getHsPol__Q24chip15DriverChip9388AUlRUc", (char*) getHsPol__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getInputInfoFlg__Q23ent10EntSettingUl", (char*) getInputInfoFlg__Q23ent10EntSettingUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getInputInfoSize__Q23ent10EntSettingUlRUlT2", (char*) getInputInfoSize__Q23ent10EntSettingUlRUlT2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getInputInfoType__Q23ent10EntSettingUl", (char*) getInputInfoType__Q23ent10EntSettingUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getInputInfo__Q24chip14DriverChipFPGAUlRQ24chip10InputInfoT", (char*) getInputInfo__Q24chip14DriverChipFPGAUlRQ24chip10InputInfoT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getInputTotal__Q23ent10EntSetting", (char*) getInputTotal__Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getInput__Q23ent10EntSettingUlRUl", (char*) getInput__Q23ent10EntSettingUlRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getLayer__Q23ent10EntSettingUlRUl", (char*) getLayer__Q23ent10EntSettingUlRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getLineWidth__Q24chip15DriverChip9388AUlRUs", (char*) getLineWidth__Q24chip15DriverChip9388AUlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getModule__10MsgHandlerUl", (char*) getModule__10MsgHandlerUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getOutputInfoFlg__Q23ent10EntSettingUl", (char*) getOutputInfoFlg__Q23ent10EntSettingUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getOutputInfoSize__Q23ent10EntSettingUlRUlT2", (char*) getOutputInfoSize__Q23ent10EntSettingUlRUlT2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getOutputInfoType__Q23ent10EntSettingUl", (char*) getOutputInfoType__Q23ent10EntSettingUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getOutputTotal__Q23ent10EntSetting", (char*) getOutputTotal__Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getOutput__Q23ent10EntSettingUlRUl", (char*) getOutput__Q23ent10EntSettingUlRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getSCF__Q24chip15DriverChip9388AUlRUs", (char*) getSCF__Q24chip15DriverChip9388AUlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getSCVS__Q24chip15DriverChip9388AUlRUs", (char*) getSCVS__Q24chip15DriverChip9388AUlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getSelectInput__Q24chip14DriverChipFPGAUlRUs", (char*) getSelectInput__Q24chip14DriverChipFPGAUlRUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getShowStatus__Q23ent10EntSettingUlRUl", (char*) getShowStatus__Q23ent10EntSettingUlRUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getSlotStatusFlg__Q23ent10EntSettingUl", (char*) getSlotStatusFlg__Q23ent10EntSettingUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getSlotStatusType__Q23ent10EntSettingUl", (char*) getSlotStatusType__Q23ent10EntSettingUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getSysIp__Q23ent10EntSetting", (char*) getSysIp__Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getTMDSFreq__Q24chip15DriverChip9388AUlRUc", (char*) getTMDSFreq__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getTemperatureValue", (char*) getTemperatureValue, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getTestConfig__Q24chip14DriverChipFPGARQ24chip11TestConfigT", (char*) getTestConfig__Q24chip14DriverChipFPGARQ24chip11TestConfigT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getTestReg__Q24chip14DriverChipFPGARUs", (char*) getTestReg__Q24chip14DriverChipFPGARUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getTestVersionReg__Q24chip14DriverChipFPGARUs", (char*) getTestVersionReg__Q24chip14DriverChipFPGARUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getUserVersionReg__Q24chip14DriverChipFPGARUs", (char*) getUserVersionReg__Q24chip14DriverChipFPGARUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getVersion__Q23ent10EntSetting", (char*) getVersion__Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getVerticalCompensation__Q27chipApp8AppScaleUsUsUc", (char*) getVerticalCompensation__Q27chipApp8AppScaleUsUsUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getVerticalStart__Q27chipApp8AppScaleUsUsUc", (char*) getVerticalStart__Q27chipApp8AppScaleUsUsUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getVerticalTotal__Q27chipApp8AppScaleUsUsUc", (char*) getVerticalTotal__Q27chipApp8AppScaleUsUsUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getVoltage", (char*) getVoltage, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getVsPol__Q24chip15DriverChip9388AUlRUc", (char*) getVsPol__Q24chip15DriverChip9388AUlRUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getWindowsHandle__Q23ent10EntSettingRt3set3ZUlZt4less1ZUlZt9allocator1ZUl", (char*) getWindowsHandle__Q23ent10EntSettingRt3set3ZUlZt4less1ZUlZt9allocator1ZUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getWindowsInfo__Q23ent10EntSettingUlRQ23ent10WindowInfo", (char*) getWindowsInfo__Q23ent10EntSettingUlRQ23ent10WindowInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getWindowsTotal__Q23ent10EntSetting", (char*) getWindowsTotal__Q23ent10EntSetting, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "getpeername", (char*) getpeername, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gets", (char*) gets, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gets__7istreamPPcc", (char*) gets__7istreamPPcc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getsockname", (char*) getsockname, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getsockopt", (char*) getsockopt, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getw", (char*) getw, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "getwd", (char*) getwd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gmtime", (char*) gmtime, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gmtime_r", (char*) gmtime_r, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "good__C3ios", (char*) good__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "gptr__C9streambuf", (char*) gptr__C9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "grab__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep", (char*) grab__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "hideWnd__Q27chipApp8AppScaleUl", (char*) hideWnd__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "ibegin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) ibegin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmpCfgParams", (char*) &icmpCfgParams, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "icmpLibInit", (char*) icmpLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmpMaskGet", (char*) icmpMaskGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmp_ctloutput", (char*) icmp_ctloutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmp_init", (char*) icmp_init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmp_input", (char*) icmp_input, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "icmpmask", (char*) &icmpmask, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "icmpmaskrepl", (char*) &icmpmaskrepl, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "icmpstat", (char*) &icmpstat, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "iend__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) iend__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "inflateTask", (char*) inflateTask, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initCLK__Q27chipApp8AppScale", (char*) initCLK__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initChannel__Q27chipApp8AppScaleUlPQ27chipApp12ScaleChInfoT", (char*) initChannel__Q27chipApp8AppScaleUlPQ27chipApp12ScaleChInfoT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initChipDDR__Q27chipApp8AppScale", (char*) initChipDDR__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initDog", (char*) initDog, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initHardware__Q27chipApp8AppScale", (char*) initHardware__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initMemoryLineFeedWidth__Q27chipApp8AppScaleUl", (char*) initMemoryLineFeedWidth__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initMoney", (char*) initMoney, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initScal__Q27chipApp8AppScaleUlUlUlUlUl", (char*) initScal__Q27chipApp8AppScaleUlUlUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initScaleTable__Q27chipApp8AppScaleUl", (char*) initScaleTable__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initTest1024__Q27chipApp8AppScale", (char*) initTest1024__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initTest1400", (char*) initTest1400, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initTest1400__Q27chipApp8AppScale", (char*) initTest1400__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initTimingIndexTable__Q27chipApp8AppScale", (char*) initTimingIndexTable__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "init__3iosP9streambufP7ostream", (char*) init__3iosP9streambufP7ostream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "init__7filebuf", (char*) init__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "initstate", (char*) initstate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "input_ipaddr", (char*) &input_ipaddr, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUlc", (char*) insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcUlc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pcc", (char*) insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Pcc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlPCc", (char*) insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlPCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlPCcUl", (char*) insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlPCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl", (char*) insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlc", (char*) insert__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlc, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "is_del__t18string_char_traits1Zcc", (char*) is_del__t18string_char_traits1Zcc, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "length__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) length__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "length__t18string_char_traits1ZcPCc", (char*) length__t18string_char_traits1ZcPCc, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "lt__t18string_char_traits1ZcRCcT1", (char*) lt__t18string_char_traits1ZcRCcT1, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "main", (char*) main, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "malloc", (char*) malloc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mask_rnhead", (char*) &mask_rnhead, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "mathSoftInit", (char*) mathSoftInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "maxDrivers", (char*) &maxDrivers, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "maxFiles", (char*) &maxFiles, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_hdr", (char*) &max_hdr, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_keylen", (char*) &max_keylen, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_linkhdr", (char*) &max_linkhdr, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_protohdr", (char*) &max_protohdr, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "max_size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) max_size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "memalign", (char*) memalign, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memchr", (char*) memchr, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memcmp", (char*) memcmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memcpy", (char*) memcpy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memmove", (char*) memmove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "memset", (char*) memset, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mib2ErrorAdd", (char*) mib2ErrorAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mib2Init", (char*) mib2Init, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mifCommonEvent__Q23msg5EventUl", (char*) mifCommonEvent__Q23msg5EventUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mifI2CRead__Q23msg9BusDriverUlUl", (char*) mifI2CRead__Q23msg9BusDriverUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mifI2CWrite__Q23msg9BusDriverUlUlUl", (char*) mifI2CWrite__Q23msg9BusDriverUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mifImportanceEvent__Q23msg5EventUl", (char*) mifImportanceEvent__Q23msg5EventUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mifSPIRead__Q23msg9BusDriverUlUl", (char*) mifSPIRead__Q23msg9BusDriverUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mifSPIWrite__Q23msg9BusDriverUlUlUl", (char*) mifSPIWrite__Q23msg9BusDriverUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mkdir", (char*) mkdir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "mktime", (char*) mktime, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "moveChannelInput__Q27chipApp8AppScaleUlii", (char*) moveChannelInput__Q27chipApp8AppScaleUlii, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moveChannelOutput__Q27chipApp8AppScaleUlii", (char*) moveChannelOutput__Q27chipApp8AppScaleUlii, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moveInput", (char*) moveInput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "moveOutput", (char*) moveOutput, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "move__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlPCcUl", (char*) move__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlPCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "move__t18string_char_traits1ZcPcPCcUl", (char*) move__t18string_char_traits1ZcPcPCcUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "ne__t18string_char_traits1ZcRCcT1", (char*) ne__t18string_char_traits1ZcRCcT1, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "netMsgInput__10MsgHandlerUlPcUl", (char*) netMsgInput__10MsgHandlerUlPcUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "onGetInPutReq__Q23msg6StatusP7MsgInfoUl", (char*) onGetInPutReq__Q23msg6StatusP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onGetInPutSizeReq__Q23msg6StatusP7MsgInfoUl", (char*) onGetInPutSizeReq__Q23msg6StatusP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onGetOutPutReq__Q23msg6StatusP7MsgInfoUl", (char*) onGetOutPutReq__Q23msg6StatusP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onGetOutPutSizeReq__Q23msg6StatusP7MsgInfoUl", (char*) onGetOutPutSizeReq__Q23msg6StatusP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onMsgReq__Q23msg13TaskCheckFPGAP7MsgInfoUl", (char*) onMsgReq__Q23msg13TaskCheckFPGAP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onMsgReq__Q23msg5EventP7MsgInfoUl", (char*) onMsgReq__Q23msg5EventP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onMsgReq__Q23msg6BGTestP7MsgInfoUl", (char*) onMsgReq__Q23msg6BGTestP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onMsgReq__Q23msg6StatusP7MsgInfoUl", (char*) onMsgReq__Q23msg6StatusP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onMsgReq__Q23msg7ChannelP7MsgInfoUl", (char*) onMsgReq__Q23msg7ChannelP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onMsgReq__Q23msg7WindowsP7MsgInfoUl", (char*) onMsgReq__Q23msg7WindowsP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onMsgReq__Q23msg9BusDriverP7MsgInfoUl", (char*) onMsgReq__Q23msg9BusDriverP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPChangeInputReq__Q23msg7ChannelP7MsgInfoUl", (char*) onPChangeInputReq__Q23msg7ChannelP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPCommonEventUpLoadRsp__Q23msg5EventP7MsgInfoUl", (char*) onPCommonEventUpLoadRsp__Q23msg5EventP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPCreateWindowsReq__Q23msg7WindowsP7MsgInfoUl", (char*) onPCreateWindowsReq__Q23msg7WindowsP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPDelWindowsReq__Q23msg7WindowsP7MsgInfoUl", (char*) onPDelWindowsReq__Q23msg7WindowsP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPGetWindowsHandleReq__Q23msg7WindowsP7MsgInfoUl", (char*) onPGetWindowsHandleReq__Q23msg7WindowsP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPGetWindowsInfoReq__Q23msg7WindowsP7MsgInfoUl", (char*) onPGetWindowsInfoReq__Q23msg7WindowsP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPImportanceEventUpLoadRsp__Q23msg5EventP7MsgInfoUl", (char*) onPImportanceEventUpLoadRsp__Q23msg5EventP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPMoveWindowsReq__Q23msg7WindowsP7MsgInfoUl", (char*) onPMoveWindowsReq__Q23msg7WindowsP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPReadI2CReq__Q23msg6BGTestP7MsgInfoUl", (char*) onPReadI2CReq__Q23msg6BGTestP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPReadSPIReq__Q23msg6BGTestP7MsgInfoUl", (char*) onPReadSPIReq__Q23msg6BGTestP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPSetInPutPicReq__Q23msg7ChannelP7MsgInfoUl", (char*) onPSetInPutPicReq__Q23msg7ChannelP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPSetOutPutSizeReq__Q23msg7ChannelP7MsgInfoUl", (char*) onPSetOutPutSizeReq__Q23msg7ChannelP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPSetWindowsLayerReq__Q23msg7WindowsP7MsgInfoUl", (char*) onPSetWindowsLayerReq__Q23msg7WindowsP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPSetWindowsShowStateReq__Q23msg7WindowsP7MsgInfoUl", (char*) onPSetWindowsShowStateReq__Q23msg7WindowsP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPWriteI2CReq__Q23msg6BGTestP7MsgInfoUl", (char*) onPWriteI2CReq__Q23msg6BGTestP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onPWriteSPIReq__Q23msg6BGTestP7MsgInfoUl", (char*) onPWriteSPIReq__Q23msg6BGTestP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "onProtocolVersionReq__Q23msg6StatusP7MsgInfoUl", (char*) onProtocolVersionReq__Q23msg6StatusP7MsgInfoUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "open", (char*) open, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "openChannelTest__Q27chipApp8AppScale", (char*) openChannelTest__Q27chipApp8AppScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "openChannel__Q27chipApp8AppScaleUl", (char*) openChannel__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "packMsg__7MsgBaseR10NetMsgBody", (char*) packMsg__7MsgBaseR10NetMsgBody, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "pauseChannel__Q27chipApp8AppScaleUl", (char*) pauseChannel__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "pop_string__7MsgBase", (char*) pop_string__7MsgBase, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "pop_u16__7MsgBase", (char*) pop_u16__7MsgBase, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "push_back__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c", (char*) push_back__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0c, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "push_string__7MsgBaseGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) push_string__7MsgBaseGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "push_u16__7MsgBaseUs", (char*) push_u16__7MsgBaseUs, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "rbegin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) rbegin__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rbegin__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) rbegin__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rcmd", (char*) rcmd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rdbuf__3iosP9streambuf", (char*) rdbuf__3iosP9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rdbuf__C3ios", (char*) rdbuf__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rdstate__C3ios", (char*) rdstate__C3ios, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read", (char*) read, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "readBackground__Q27chipApp8AppScaleUllUsUsPUc", (char*) readBackground__Q27chipApp8AppScaleUllUsUsPUc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read__7istreamPSci", (char*) read__7istreamPSci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read__7istreamPUci", (char*) read__7istreamPUci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read__7istreamPci", (char*) read__7istreamPci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read__7istreamPvi", (char*) read__7istreamPvi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read_id_register", (char*) read_id_register, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "read_status_register", (char*) read_status_register, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "release__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep", (char*) release__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remCurIdGet", (char*) remCurIdGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remCurIdSet", (char*) remCurIdSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remLastResvPort", (char*) &remLastResvPort, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "remLibInit", (char*) remLibInit, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "remStdErrSetupTimeout", (char*) &remStdErrSetupTimeout, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "remove", (char*) remove, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rename", (char*) rename, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rend__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) rend__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rend__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) rend__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) rep__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "repeat", (char*) repeat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "repeatRun", (char*) repeatRun, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replaceFATsector", (char*) replaceFATsector, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCc", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCcUl", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1Ulc", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PcT1Ulc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlPCc", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlPCc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlPCcUl", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlPCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlRCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlUlc", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlUlc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlc", (char*) replace__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUlc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "repup__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep", (char*) repup__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PQ2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3Rep, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reschedule", (char*) reschedule, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "reserve__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) reserve__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "resetflash", (char*) resetflash, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "resize__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) resize__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "resize__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc", (char*) resize__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ulc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "restartTaskName", (char*) &restartTaskName, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskOptions", (char*) &restartTaskOptions, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskPriority", (char*) &restartTaskPriority, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "restartTaskStackSize", (char*) &restartTaskStackSize, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "resumeChannel__Q27chipApp8AppScaleUl", (char*) resumeChannel__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rewind", (char*) rewind, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rewinddir", (char*) rewinddir, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl", (char*) rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl", (char*) rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0PCcUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul", (char*) rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0RCt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl", (char*) rfind__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0cUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "runServer", (char*) runServer, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "selectOutPut", (char*) selectOutPut, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selectOutPutModel__Q27chipApp8AppScaleUl", (char*) selectOutPutModel__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "selfish__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) selfish__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "send", (char*) send, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sendMsg__10MsgHandlerUlP7MsgInfo", (char*) sendMsg__10MsgHandlerUlP7MsgInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sendmsg", (char*) sendmsg, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sendto", (char*) sendto, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "server_proc__7IServeri", (char*) server_proc__7IServeri, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set753", (char*) set753, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setC753InputACT", (char*) setC753InputACT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setC753OutPutACT", (char*) setC753OutPutACT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setC753OutPutOAI0", (char*) setC753OutPutOAI0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setC753OutPutOAI1", (char*) setC753OutPutOAI1, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setFlashConfig", (char*) setFlashConfig, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setFpgaSelectChn", (char*) setFpgaSelectChn, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setInputChannelACT__Q27chipApp8AppScaleUlUsUsUsUs", (char*) setInputChannelACT__Q27chipApp8AppScaleUlUsUsUsUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setInputInfoFlg__Q23ent10EntSettingUlUl", (char*) setInputInfoFlg__Q23ent10EntSettingUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setInputInfoSize__Q23ent10EntSettingUlUlUl", (char*) setInputInfoSize__Q23ent10EntSettingUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setInputInfoType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) setInputInfoType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setInput__Q23ent10EntSettingUlUl", (char*) setInput__Q23ent10EntSettingUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setLayer__Q23ent10EntSettingUlUl", (char*) setLayer__Q23ent10EntSettingUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setModel__10MsgHandlerUlP9CommModel", (char*) setModel__10MsgHandlerUlP9CommModel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setMsgHandler__7IServerP10MsgHandler", (char*) setMsgHandler__7IServerP10MsgHandler, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setMsgInfo__7MsgBaseP7MsgInfo", (char*) setMsgInfo__7MsgBaseP7MsgInfo, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setNetMsgBody__7MsgBaseP10NetMsgBody", (char*) setNetMsgBody__7MsgBaseP10NetMsgBody, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setOutputBGColor__Q27chipApp8AppScaleUlUl", (char*) setOutputBGColor__Q27chipApp8AppScaleUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setOutputChannelACT__Q27chipApp8AppScaleUlUsUsUsUs", (char*) setOutputChannelACT__Q27chipApp8AppScaleUlUsUsUsUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setOutputImage__Q27chipApp8AppScaleUlUl", (char*) setOutputImage__Q27chipApp8AppScaleUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setOutputInfoFlg__Q23ent10EntSettingUlUl", (char*) setOutputInfoFlg__Q23ent10EntSettingUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setOutputInfoSize__Q23ent10EntSettingUlUlUl", (char*) setOutputInfoSize__Q23ent10EntSettingUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setOutputInfoType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) setOutputInfoType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setOutputSize__Q27chipApp8AppScaleUl", (char*) setOutputSize__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setOutput__Q23ent10EntSettingUlUl", (char*) setOutput__Q23ent10EntSettingUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setPOCLK__Q24chip16DriverChipICS307Ul", (char*) setPOCLK__Q24chip16DriverChipICS307Ul, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setPort__7IServerUl", (char*) setPort__7IServerUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setSMC2", (char*) setSMC2, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setSelectInput__Q24chip14DriverChipFPGAUlUs", (char*) setSelectInput__Q24chip14DriverChipFPGAUlUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setServerFlg__7IServerb", (char*) setServerFlg__7IServerb, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setShowStatus__Q23ent10EntSettingUlUl", (char*) setShowStatus__Q23ent10EntSettingUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setSlotStatusFlg__Q23ent10EntSettingUlUl", (char*) setSlotStatusFlg__Q23ent10EntSettingUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setSlotStatusType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) setSlotStatusType__Q23ent10EntSettingUlGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setSysIp__Q23ent10EntSettingGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) setSysIp__Q23ent10EntSettingGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setTestConfig__Q24chip14DriverChipFPGAGQ24chip11TestConfigT", (char*) setTestConfig__Q24chip14DriverChipFPGAGQ24chip11TestConfigT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setTestReg__Q24chip14DriverChipFPGAUs", (char*) setTestReg__Q24chip14DriverChipFPGAUs, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setVersion__Q23ent10EntSettingGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) setVersion__Q23ent10EntSettingGt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "setWindowPosition__Q23ent10EntSettingUlUlUlUlUl", (char*) setWindowPosition__Q23ent10EntSettingUlUlUlUlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set__3iosi", (char*) set__3iosi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlcUl", (char*) set__Q2t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0_3RepUlcUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "set__t18string_char_traits1ZcPcRCcUl", (char*) set__t18string_char_traits1ZcPcRCcUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "showWnd__Q27chipApp8AppScaleUl", (char*) showWnd__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) size__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "spiFlashRead", (char*) spiFlashRead, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "spiFlashWriteTest", (char*) spiFlashWriteTest, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "start_spi", (char*) start_spi, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "substr__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl", (char*) substr__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0UlUl, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "substrcmp", (char*) substrcmp, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "sungetc__9streambuf", (char*) sungetc__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "swab", (char*) swab, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "swap__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Rt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) swap__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0Rt12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "sysFlashDataPoll16", (char*) sysFlashDataPoll16, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "tan", (char*) tan, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "tanh", (char*) tanh, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskActivate", (char*) taskActivate, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskArgsGet", (char*) taskArgsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskArgsSet", (char*) taskArgsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskBpHook", (char*) &taskBpHook, 0, SYM_GLOBAL | SYM_BSS},
        {{NULL}, "taskBpHookSet", (char*) taskBpHookSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskClassId", (char*) &taskClassId, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskCreat", (char*) taskCreat, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateHookAdd", (char*) taskCreateHookAdd, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateHookDelete", (char*) taskCreateHookDelete, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskCreateTable", (char*) &taskCreateTable, 0, SYM_GLOBAL | SYM_BSS},
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
        {{NULL}, "taskMain__Q23msg13TaskCheckFPGA", (char*) taskMain__Q23msg13TaskCheckFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskName", (char*) taskName, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskNameToId", (char*) taskNameToId, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsGet", (char*) taskOptionsGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsSet", (char*) taskOptionsSet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskOptionsString", (char*) taskOptionsString, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskPriRangeCheck", (char*) &taskPriRangeCheck, 0, SYM_GLOBAL | SYM_DATA},
        {{NULL}, "taskPriorityGet", (char*) taskPriorityGet, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "taskPrioritySet", (char*) taskPrioritySet, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "terminate__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) terminate__Ct12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "terminate__Fv", (char*) terminate__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "test5160", (char*) test5160, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testC772", (char*) testC772, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testCopy", (char*) testCopy, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testFPGA", (char*) testFPGA, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testMACRO", (char*) testMACRO, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testMenu", (char*) testMenu, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testSPI", (char*) testSPI, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testScale", (char*) testScale, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testShow", (char*) testShow, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "testTaskServer", (char*) testTaskServer, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "topChannel", (char*) topChannel, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "topChannel__Q27chipApp8AppScaleUl", (char*) topChannel__Q27chipApp8AppScaleUl, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "uncompress", (char*) uncompress, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "underflow__7filebuf", (char*) underflow__7filebuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "underflow__9streambuf", (char*) underflow__9streambuf, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unexpected__Fv", (char*) unexpected__Fv, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unget__7istream", (char*) unget__7istream, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unget__7istreamc", (char*) unget__7istreamc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "ungetc", (char*) ungetc, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "unique__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0", (char*) unique__t12basic_string3ZcZt18string_char_traits1ZcZt24__default_alloc_template2b1i0, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "what__C11logic_error", (char*) what__C11logic_error, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "what__C13runtime_error", (char*) what__C13runtime_error, 0, SYM_GLOBAL | SYM_TEXT},
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
        {{NULL}, "writeBackground__Q27chipApp8AppScaleUlUsUsP14tagDispBitmapT", (char*) writeBackground__Q27chipApp8AppScaleUlUsUsP14tagDispBitmapT, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "writeFlash16", (char*) writeFlash16, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write__7ostreamPCSci", (char*) write__7ostreamPCSci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write__7ostreamPCUci", (char*) write__7ostreamPCUci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write__7ostreamPCci", (char*) write__7ostreamPCci, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write__7ostreamPCvi", (char*) write__7ostreamPCvi, 0, SYM_GLOBAL | SYM_TEXT},
        {{NULL}, "write_status_register", (char*) write_status_register, 0, SYM_GLOBAL | SYM_TEXT},
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


ULONG standTblSize = 5247;
