/*
 * devC753.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _DEV_C753_H_
#define _DEV_C753_H_

#include <map>
#include <list>
#include "Bitmap.h"
#include "devBus.h"

using namespace std;

namespace chip
{

#define C753_BUSCAHNNEL  0

enum
{
    C753_INPUT_CHANNEL_1 = 1,
    C753_INPUT_CHANNEL_2
};

enum
{
    C753_OUTPUT_CHANNEL_1 = 1,
    C753_OUTPUT_CHANNEL_2
};

enum
{
    C753_CHANNEL_1 = 1,
    C753_CHANNEL_2
};






class DriverChip753
:public SPIBus
{

public:
	DriverChip753();
	virtual ~DriverChip753();

	/*Basic function*/
	void C753SetBankRegister(uint8_t byVal);
	void C753GetBankRegister(uint8_t &byVal);
//	void C753SetMainControl(uint16_t wVal);
	void C753SetMainControl(uint32_t iCh,uint8_t byVal);
	void C753GetMainControl(uint32_t iCh,uint8_t &byVal);
	void C753SetDDRControl(uint8_t byVal);
	void C753SetRegisterValueTransferControl(uint16_t wVal);
	void C753SetMemoryControl(uint8_t byVal);
	void C753Reset(uint8_t byVal);
	/*Bank0 function*/
	void C753SetOutputPortSyncControl(uint16_t wVal);
	void C753GetOutputPortSyncControl(uint16_t &wVal);

	void C753SetForcedSyncResetDelay(uint8_t byVal);
	void C753SetForcedSyncResetControl(uint16_t wVal);
	void C753SetFieldInterlockTransferControl(uint8_t byVal);
	void C753SetFieldPropagationDelay1(uint8_t byVal);
	void C753SetFieldPropagationDelay2(uint8_t byVal);
	void C753SetOutputSignalSwap(uint8_t byVal);
	void C753SetPOCLKControl(uint8_t byVal);
	void C753SetScalingWidthControl(uint8_t byVal);
	void C753SetInterlaceOutputControl(uint8_t byVal);
	void C753SetOverlayControl(uint8_t byVal);
	void C753GetOverlayControl(uint8_t &byVal);
	void C753Set2ScreenBlendingAlphaCoefficient(uint8_t byVal);
	void C753Set2ScreenBlendingBetaCoefficient(uint8_t byVal);
	void C753SetOSDMode(uint8_t byVal);
	void C753SetOSDControl(uint8_t byVal);
	void C753SetOSDPenetrationColor(uint8_t byVal);
	void C753SetOSDWriteInhibitColor(uint8_t byVal);
	void C753SetOSDFillColor(uint8_t byVal);
	void C753SetBlinkingTime(uint8_t byVal);
	void C753SetBlinkCycle(uint8_t byVal);

	void C753SetOSDACTHorizontalStart(uint16_t wVal);
	void C753SetOSDACTHorizontalWidth(uint16_t wVal);
	void C753SetOSDACTVerticalStart(uint16_t wVal);
	void C753SetOSDACTVerticalWidth(uint16_t wVal);
	void C753SetOSDStartAddress(uint32_t dwVal);
	void C753SetOSDMemoryLinefeedWidth(uint8_t byVal);
	void C753SetCharacterBufferHorizontalStart(uint8_t byVal);
	void C753SetCharacterBufferHorizontalWidth(uint8_t byVal);
	void C753SetCharacterBufferVerticalStart(uint8_t byVal);
	void C753SetCharacterBufferVerticalWidth(uint8_t byVal);
	void C753SetBitBLTHorizontalWidth(uint8_t wVal);
	void C753SetBitBLTVerticalWidth(uint16_t wVal);
	void C753SetCPUReadAddress(uint32_t dwVal);
	void C753SetCPUWriteAddress(uint32_t dwVal);
	void C753SetCPUData(uint8_t byVal);
	void C753GetCPUData(uint8_t &byVal);

	void C753WritePixel(uint8_t byRed, uint8_t byGreen, uint8_t byBlue, uint8_t byDump);
	void C753WriteN1BitPixels(uint16_t wNPixels, RGBQUAD *pC753Plt, uint8_t **ppbyMap, uint8_t *pbyBuf);
	void C753WriteN8BitPixels(uint16_t wNPixels, RGBQUAD *pC753Plt, uint8_t *pbyBuf);
	void C753WriteN24BitPixels(uint16_t wNPixels, uint8_t *pbyBuf);
	void C753ReadN24BitPixels(uint16_t wNPixels, uint8_t *pbyBuf);
	void C753SetCharacterBufferAddress(uint16_t wVal);
	void C753SetCharacterBufferData(uint8_t byVal);
	void C753SetPaletteAddress(uint8_t byVal);
	void C753SetPaletteData(uint8_t byVal);
	void C753GetBitmapOSDStatus(uint8_t &byVal);
	void C753SetBitmapOSD90DegreeRotation(uint8_t byVal);
	void C753SetBitBLTWriteLinefeedWidth(uint8_t byVal);
	void C753SetBitBLTReadLinefeedWidth(uint8_t byVal);
	void C753SetBitmapOSDAccessControl(uint8_t byVal);
	void C753SetMemoryProtect(uint16_t wVal);
	void C753SetBitBLTTriggerVSDelay(uint8_t byVal);
	void C753SetInterruptEnable(uint16_t wVal);
	void C753SetInterruptReset(uint16_t wVal);
	void C753SetTESTDT(uint8_t byVal);
	void C753SetTESTAD(uint8_t byVal);
	void C753SetTestG(uint8_t byVal);

	/*Bank 1 function*/
	void C753SetOutputPortOAOI0HorizontalStart(uint16_t wVal);
	void C753SetOutputPortOAOI0HorizontalEnd(uint16_t wVal);
	void C753SetOutputPortOAOI0VerticalStart(uint16_t wVal);
	void C753SetOutputPortOAOI0VerticalEnd(uint16_t wVal);
	void C753SetOutputPortOAOI1HorizontalStart(uint16_t wVal);
	void C753SetOutputPortOAOI1HorizontalEnd(uint16_t wVal);
	void C753SetOutputPortOAOI1VerticalStart(uint16_t wVal);
	void C753SetOutputPortOAOI1VerticalEnd(uint16_t wVal);
	void C753SetOutputPortOAOI2HorizontalStart(uint16_t wVal);
	void C753SetOutputPortOAOI2HorizontalEnd(uint16_t wVal);
	void C753SetOutputPortOAOI2VerticalStart(uint16_t wVal);
	void C753SetOutputPortOAOI2VerticalEnd(uint16_t wVal);
	void C753SetOutputPortOAOI3HorizontalStart(uint16_t wVal);
	void C753SetOutputPortOAOI3HorizontalEnd(uint16_t wVal);
	void C753SetOutputPortOAOI3VerticalStart(uint16_t wVal);
	void C753SetOutputPortOAOI3VerticalEnd(uint16_t wVal);
	void C753SetBackgroundControl(uint8_t byVal);
	void C753SetOutputBackground0(uint32_t dwVal);
	void C753SetOutputBackground1(uint32_t dwVal);
	void C753SetOutputPatternBarWidth(uint8_t byVal);
	void C753SetOutputPatternSpeed(uint8_t byVal);
	void C753SetOutputPatternCycle(uint16_t wVal);
	void C753SetPatternGeneratorControl(uint8_t byVal);
	void C753SetRAMPCounterStepSetting(uint8_t byVal);
	void C753SetHorizontalRAMPCounterLimitValue(uint16_t wVal);
	void C753SetVerticalRAMPCounterLimitValue(uint16_t wVal);
	void C753SetColorBarWidthSetting(uint8_t byVal);
	void C753SetPWMControl0(uint16_t wVal);
	void C753SetPWMControl1(uint16_t wVal);
	void C753SetPWMControl2(uint16_t wVal);
	void C753SetPWMControl3(uint16_t wVal);
	void C753SetIPCLKPLLControl(uint8_t byVal);
	void C753SetIPCLKReferenceDividing(uint8_t byVal);
	void C753SetIPCLKFeedbackDividing(uint8_t byVal);
	void C753SetPOCLKPLLControl(uint8_t byVal);
	void C753SetPOCLKReferenceDividing(uint8_t byVal);
	void C753SetPOCLKFeedbackDividing(uint8_t byVal);
	void C753SetDLLControl0(uint8_t byVal);
	void C753SetDLLControl1(uint8_t byVal);
	void C753SetDLLControl2(uint8_t byVal);
	void C753SetDLLControl3(uint8_t byVal);
	void C753SetDLLControl4(uint8_t byVal);
	void C753SetDLLControl5(uint8_t byVal);
	void C753SetDLLControl6(uint8_t byVal);
	void C753SetDLLControl7(uint8_t byVal);
	void C753SetDLLControl8(uint8_t byVal);

	/*Bank 2/4 function*/
	void C753SetOutputPortACTHorizontalStart(uint32_t iCh, uint16_t wVal);
	void C753SetOutputPortACTHorizontalWidth(uint32_t iCh, uint16_t wVal);
	void C753SetOutputPortACTVerticalStart(uint32_t iCh, uint16_t wVal);
	void C753SetOutputPortACTVerticalWidth(uint32_t iCh, uint16_t wVal);
	void C753SetOutputPostEnlargementHorizontalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal);
	void C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal);
	void C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal);
	void C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoefficient(uint32_t iCh, uint32_t dwVal);
	void C753SetOutputPostEnlargementHorizontalEdgeAreaSelect(uint32_t iCh, uint8_t byVal);
	void C753SetOutputPostEnlargementVerticalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal);
	void C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal);
	void C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal);
	void C753SetOutputPostEnlargementVerticalEdgeEmphasisCoefficient(uint32_t iCh, uint32_t dwVal);
	void C753SetOutputPostEnlargementVerticalEdgeAreaSelect(uint32_t iCh, uint8_t byVal);
	void C753SetOutputPostEnlargementVerticalEdgeEmphasisControl2(uint32_t iCh, uint8_t byVal);
	void C753SetOutputFill(uint32_t iCh, uint32_t dwVal);
	void C753SetOutputImageControl(uint32_t iCh, uint8_t byVal);
	void C753SetOutputHorizontalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal);
	void C753SetOutputHorizontalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal);
	void C753SetOutputHorizontalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal);
	void C753SetOutputHorizontalEdgeEmphasisOvershootFilterCoefficient(uint32_t iCh, uint8_t byVal);
	void C753SetOutputHorizontalEdgeEmphasisUndershootFilterCoefficient(uint32_t iCh, uint8_t byVal);
	void C753SetOutputHorizontalEnlargementControl(uint32_t iCh, uint8_t byVal);
	void C753SetOutputHorizontalEnlargementInitialValue(uint32_t iCh, uint8_t byVal);
	void C753SetOutputHorizontalZoomScale(uint32_t iCh, uint16_t wVal);
	void C753SetOutputVerticalEnlargementControl(uint32_t iCh, uint8_t byVal);
	void C753SetOutputVerticalEnlargementInitialValue(uint32_t iCh, uint8_t byVal);
	void C753SetOutputVerticalZoomScale(uint32_t iCh, uint16_t wVal);
	void C753LoadOutputHorizontalZoomLookupTable(uint32_t iCh, const uint8_t *pbyVal);
	void C753LoadOutputVerticalZoomLookupTable(uint32_t iCh, const uint8_t *pbyVal);

	/*Bank 6/8 function*/
	void C753SetInputFormatControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputPortSyncControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputFieldRecognitionControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputDigitalInterfaceControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputComponentInputControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputPortACTHorizontalStart(uint32_t iCh, uint16_t wVal);
	void C753SetInputPortACTHorizontalWidth(uint32_t iCh, uint16_t wVal);
	void C753SetInputPortACTVerticalStart(uint32_t iCh, uint16_t wVal);
	void C753SetInputPortACTVerticalWidth(uint32_t iCh, uint16_t wVal);
	void C753SetInputSignalSwap(uint32_t iCh, uint8_t byVal);
	void C753SetInputImageControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputFill(uint32_t iCh, uint32_t dwVal);
	void C753SetInputUVLowPassFilterCoefficient(uint32_t iCh, uint32_t dwVal);
	void C753SetInputRGBYUVCoefficientRY(uint32_t iCh, uint16_t wVal);
	void C753SetInputRGBYUVCoefficientGY(uint32_t iCh, uint16_t wVal);
	void C753SetInputRGBYUVCoefficientBY(uint32_t iCh, uint16_t wVal);
	void C753SetInputRGBYUVCoefficientRU(uint32_t iCh, uint16_t wVal);
	void C753SetInputRGBYUVCoefficientGU(uint32_t iCh, uint16_t wVal);
	void C753SetInputRGBYUVCoefficientBU(uint32_t iCh, uint16_t wVal);
	void C753SetInputRGBYUVCoefficientRV(uint32_t iCh, uint16_t wVal);
	void C753SetInputRGBYUVCoefficientGV(uint32_t iCh, uint16_t wVal);
	void C753SetInputRGBYUVCoefficientBV(uint32_t iCh, uint16_t wVal);
	void C753SetInputShrinkCompensationControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputHorizontalShrinkControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputHorizontalShrinkInitialValue(uint32_t iCh, uint8_t byVal);
	void C753SetInputHorizontalShrinkScale(uint32_t iCh, uint16_t wVal);
	void C753SetInputVerticalShrinkControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputVerticalShrinkInitialValue(uint32_t iCh, uint8_t byVal);
	void C753SetInputVerticalShrinkScale(uint32_t iCh, uint16_t wVal);
	void C753SetInputHorizontalShrinkCompensation(uint32_t iCh, uint8_t byVal);
	void C753SetInputVerticalShrinkCompensation(uint32_t iCh, uint8_t byVal);
	void C753LoadInputHorizontalShrinkLookupTable(uint32_t iCh, const uint8_t *pbyVal);
	void C753LoadInputVerticalShrinkLookupTable(uint32_t iCh, const uint8_t *pbyVal);
	/*Bank 7/9 function*/
	void C753SetInputImageCharacteristicsMeasurementControl(uint32_t iCh, uint8_t byVal);
	void C753SetInputMeasurementHorizontalStart(uint32_t iCh, uint16_t wVal);
	void C753SetInputMeasurementVerticalStart(uint32_t iCh, uint16_t wVal);
	void C753SetInputMeasurementHorizontalEnd(uint32_t iCh, uint16_t wVal);
	void C753SetInputMeasurementVerticalEnd(uint32_t iCh, uint16_t wVal);
	void C753SetInputCharacteristicsMeasurementThreshold(uint32_t iCh, uint8_t byVal);
	/*Bank 10/11 function*/
	void C753SetIPConversionOutputPortHorizontalSyncCycle(uint32_t iCh, uint16_t wVal);
	void C753SetIPConversionOutputPortVerticalSyncCycle(uint32_t iCh, uint16_t wVal);
	void C753SetIPConversionForcedSyncResetDelay(uint32_t iCh, uint8_t byVal);
	void C753SetIPConversionOutputPortActiveAreaHorizontalStart(uint32_t iCh, uint16_t wVal);
	void C753SetIPConversionOutputPortActiveAreaHorizontalWidth(uint32_t iCh, uint16_t wVal);
	void C753SetIPConversionOutputPortActiveAreaVerticalStart(uint32_t iCh, uint16_t wVal);
	void C753SetIPConversionOutputPortActiveAreaVerticalWidth(uint32_t iCh, uint16_t wVal);
	void C753SetMovementNRControl(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalMovementValueNRCoefficient(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD);
	void C753SetHorizontalMovementValueNRCoefficient3(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalMovementValueNRCoefficient2(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalMovementValueNRCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalMovementValueNRCoefficient0(uint32_t iCh, uint8_t byVal);
	void C753SetVerticalMovementValueGain(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD);
	void C753SetVerticalMovementValueGain3(uint32_t iCh, uint8_t byVal);
	void C753SetVerticalMovementValueGain2(uint32_t iCh, uint8_t byVal);
	void C753SetVerticalMovementValueGain1(uint32_t iCh, uint8_t byVal);
	void C753SetVerticalMovementValueGain0(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalMovementValueGain(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD);
	void C753SetHorizontalMovementValueGain3(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalMovementValueGain2(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalMovementValueGain1(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalMovementValueGain0(uint32_t iCh, uint8_t byVal);
	void C753SetVerticalDirectionMAXFilter(uint32_t iCh, uint8_t byVal);
	void C753SetMovementCoefficientNR(uint32_t iCh, uint8_t byVal);
	void C753SetLUTWriteAddress(uint32_t iCh, uint8_t byVal);
	void C753SetLUTCoefficient(uint32_t iCh, uint32_t dwVal);
	void C753SetLUTWriteEnable(uint32_t iCh, uint8_t byVal);
	void C753SetIPImageAdjustment(uint32_t iCh, uint8_t byVal);
	void C753SetIPTest(uint32_t iCh, uint8_t byVal);
	void C753SetPulldownControl1(uint32_t iCh, uint8_t byVal);
	void C753SetPulldownControl2(uint32_t iCh, uint8_t byVal);
	void C753Set22PulldownMovementDetectThreshold(uint32_t iCh, uint8_t byVal);
	void C753Set23PulldownMovementDetectThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetPulldownSequenceThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetPulldownAreaWidthSelect(uint32_t iCh, uint8_t byVal);
	void C753SetPulldownDetectAreaSelect(uint32_t iCh, uint8_t byVal);
	void C753Set22PulldownResetDetectIndex(uint32_t iCh, uint8_t byVal);
	void C753Set23PulldownResetDetectIndex(uint32_t iCh, uint8_t byVal);
	void C753SetCombingProcessControl(uint32_t iCh, uint8_t byVal);
	void C753SetCombingProcessControlLowLevelThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetCombingProcessControlHighLevelThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetDiagonalInterpolationControl(uint32_t iCh, uint32_t dwVal);
	void C753LoadDiagonalInterpolationThreshold(uint32_t iCh, const uint8_t *pbyVal);
	/*Bank 12/13 function*/
	void C753SetOutputField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetOutputField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetOutputField2MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetOutputField3MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753GetOutputField0MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal);
	void C753GetOutputField1MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal);
	void C753GetOutputField2MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal);
	void C753GetOutputField3MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal);
	void C753SetInputField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetInputField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetInputField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetInputField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetMemoryReadLinefeedWidth(uint32_t iCh, uint8_t byVal);
	void C753GetMemoryReadLinefeedWidth(uint32_t iCh, uint8_t &byVal);
	void C753SetMemoryWriteLinefeedWidth(uint32_t iCh, uint8_t byVal);
	void C753SetIPConversionField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetIPConversionField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetIPConversionField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetIPConversionField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetIPConversionField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetIPConversionField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetIPConversionMemoryLinefeedWidth(uint32_t iCh, uint8_t byVal);
	void C753SetIPConversionMovementValueReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753SetTemporalNRReadStartAddressSelect(uint32_t iCh, uint8_t byVal);
	void C753Set90DegreeRotationField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753Set90DegreeRotationField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753Set90DegreeRotationField2MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753Set90DegreeRotationField3MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753Set90DegreeRotationField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753Set90DegreeRotationField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753Set90DegreeRotationField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753Set90DegreeRotationField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal);
	void C753Set90DegreeRotationMemoryReadLinefeedWidth(uint32_t iCh, uint8_t byVal);
	void C753Set90DegreeRotationMemoryWriteLinefeedWidth(uint32_t iCh, uint8_t byVal);
	void C753SetChannel1Image90DegreeRotationControl(uint8_t byVal);
	void C753SetChannel1Image90DegreeRotationHorizontalActiveAreaWidth(uint16_t wVal);
	void C753SetChannel1Image90DegreeRotationVerticalActiveAreaWidth(uint16_t wVal);
	void C753SetChannel1Image90DegreeRotationVerticalSyncSignalDelay(uint16_t wVal);
	void C753SetChannel2Image90DegreeRotationControl(uint8_t byVal);
	void C753SetChannel2Image90DegreeRotationHorizontalActiveAreaWidth(uint16_t wVal);
	void C753SetChannel2Image90DegreeRotationVerticalActiveAreaWidth(uint16_t wVal);
	void C753SetChannel2Image90DegreeRotationVerticalSyncSignalDelay(uint16_t wVal);
	void C753SetHorizontalSyncSignalAbsenceJudgmentValue(uint16_t wVal);
	void C753SetHorizontalSyncSignalPresenceJudgmentValue(uint16_t wVal);
	void C753SetVerticalSyncSignalAbsenceJudgmentValue(uint8_t byVal);
	void C753SetVerticalSyncSignalPresenceJudgmentValue(uint8_t byVal);
	void C753Set1MHzPulseGenerationControl(uint8_t byVal);
	void C753SetDPMSControl(uint8_t byVal);
	void C753SetDPMSInterruptReset(uint8_t byVal);
	void C753SetTemporalNRControl(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRThreshold1(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRThreshold2(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRThreshold3(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRThreshold4(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRCoefficient2(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRCoefficient3(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRCoefficient4(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRCoefficient5(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRCoefficient6(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRCoefficient7(uint32_t iCh, uint8_t byVal);
	void C753SetTemporalNRCoefficient8(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRControl(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRBlendLowPassFilterHCoefficient0(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRBlendLowPassFilterHCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRBlendLowPassFilterHCoefficient2(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRBlendLowPassFilterVCoefficient0(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRBlendLowPassFilterVCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRBlendLowPassFilterVCoefficient2(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRVDirectionCoefficient0(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRVDirectionCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRVDirectionCoefficient2(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRVDirectionCoefficient3(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRVDirectionCoefficient4(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRVDirectionCoefficient5(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRHDirectionCoefficient0(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRHDirectionCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRHDirectionCoefficient2(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRHDirectionCoefficient3(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRHDirectionCoefficient4(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRHDirectionCoefficient5(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRBlendCoefficientBias(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRBlendCoefficientGain(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRNoiseBias(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRSubtractionBlendCoefficientGain(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThreshold0(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThreshold1(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThreshold2(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThreshold3(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThreshold4(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThreshold5(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThreshold6(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThreshold7(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThresholdBias0(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThresholdBias1(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThresholdBias2(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThresholdBias3(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThresholdBias4(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThresholdBias5(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThresholdBias6(uint32_t iCh, uint8_t byVal);
	void C753SetMosquitoNRThresholdBias7(uint32_t iCh, uint8_t byVal);
	void C753SetAdaptiveNRControl(uint32_t iCh, uint8_t byVal);
	void C753SetAdaptiveNRThreshold(uint32_t iCh, uint32_t dwVal);
	void C753SetAdaptiveNRCoefficient(uint32_t iCh, uint32_t dwVal);
	void C753SetBlockNRControl(uint32_t iCh, uint16_t wVal);
	void C753SetBlockNRTest(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNoiseEdgeLevelThreshold0(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNoiseEdgeLevelThreshold1(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNoiseEdgeLevelThreshold2(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNoiseEdgeLevelThreshold3(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRAlphaBlendCoefficient0(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRAlphaBlendCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRLowPassFilterCoefficient0(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRLowPassFilterCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetBlockBoundaryPeripheralMovementValueThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetBlockBoundaryPeripheralEdgeLevelThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalBlockBoundaryCoordinate(uint32_t iCh, uint8_t byVal);
	void C753SetVerticalBlockBoundaryCoordinate(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRDetectControl(uint32_t iCh, uint8_t byVal);
	void C753SetLongFramesRegisterBlockBoundaryAutoDetect(uint32_t iCh, uint8_t byVal);
	void C753SetHBlockBoundaryMatchingUpperLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal);
	void C753SetHBlockBoundaryMatchingLowerLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal);
	void C753SetHBlockBoundaryMatchingThresholdPeripheralPixel(uint32_t iCh, uint8_t byVal);
	void C753SetHBlockBoundaryMatchingCountsThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetHBlockBoundaryMatchingCountsOffset(uint32_t iCh, uint8_t byVal);
	void C753SetVBlockBoundaryMatchingUpperLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal);
	void C753SetVBlockBoundaryMatchingLowerLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal);
	void C753SetVBlockBoundaryMatchingThresholdPeripheralPixel(uint32_t iCh, uint8_t byVal);
	void C753SetVBlockBoundaryMatchingCountsThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetVBlockBoundaryMatchingCountsOffset(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRProjectionControl(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRProjectionCoefficient(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRProjectionReadAddress(uint32_t iCh, uint8_t byVal);
	void C753SetBlockNRProjectionReadData(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalBlockBoundaryInitialCoordinateForProjection(uint32_t iCh, uint16_t wVal);
	void C753SetHorizontalBlockEnlargementScaleForProjection(uint32_t iCh, uint16_t wVal);
	void C753SetVerticalBlockBoundaryInitialCoordinateForProjection(uint32_t iCh, uint16_t wVal);
	void C753SetVerticalBlockEnlargementScaleForProjection(uint32_t iCh, uint16_t wVal);
	void C753SetHorizontalVerticalNRControl(uint32_t iCh, uint8_t byVal);
	void C753SetVerticalNRCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetVerticalNRCoefficient2(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalNRCoefficient1(uint32_t iCh, uint8_t byVal);
	void C753SetHorizontalNRCoefficient2(uint32_t iCh, uint8_t byVal);
	void C753SetChromaErrorCorrectionControl(uint32_t iCh, uint8_t byVal);
	void C753SetChromaErrorDetectionThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetChromaErrorDetectionCountThreshold(uint32_t iCh, uint16_t wVal);
	void C753SetChromaErrorDetectionExclusionThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetChromaErrorAutomaticCorrectionThreshold(uint32_t iCh, uint8_t byVal);
	void C753SetChromaErrorAutomaticCorrectionCounterUpperLimit(uint32_t iCh, uint8_t byVal);
	void C753SetChromaErrorCorrectionLowPassFilterCoefficient(uint32_t iCh, uint8_t byVal);

	void C753GetInputPortHorizontalSyncFrequency(uint32_t iCh, uint16_t &wVal);
	void C753GetInputPortVerticalSyncFrequency(uint32_t iCh, uint16_t &wVal);
	void C753GetInputPortHorizontalSyncPulseWidth(uint32_t iCh, uint8_t &byVal);
	void C753GetInputPortVerticalSyncPulseWidth(uint32_t iCh, uint8_t &byVal);

	void C753GetHorizontalAndVerticalSyncPhaseDifference0(uint32_t iCh,uint16_t &wVal);
	void C753GetHorizontalAndVerticalSyncPhaseDifference1(uint32_t iCh,uint16_t &wVal);

	void C753GetStatus(uint16_t &wVal);
	void C753GetFieldHistory(uint32_t iCh,uint8_t &byVal);


	void C753GetMeasurementStatusMonitor(uint32_t iCh,uint8_t &byVal);
	void C753GetCharacteristicsMeasurementResult0(uint32_t iCh,uint8_t &byVal);
	void C753GetCharacteristicsMeasurementResult1(uint32_t iCh,uint8_t &byVal);

	void C753GetCharacteristicsMeasurementResultHorizontalCoordinate0(uint32_t iCh,uint16_t &wVal);
	void C753GetCharacteristicsMeasurementResultVerticalCoordinate0(uint32_t iCh,uint16_t &wVal);

	void C753GetCharacteristicsMeasurementResultHorizontalCoordinate1(uint32_t iCh,uint16_t &wVal);
	void C753GetCharacteristicsMeasurementResultVerticalCoordinate1(uint32_t iCh,uint16_t &wVal);

	void C753GetSNHistogramMeasurementResult(uint32_t iCh,uint8_t &byVal);

	void C753GetMAXFILTERResult(uint32_t iCh,uint8_t &byVal);
	void C753GetMINFILTERResult(uint32_t iCh,uint8_t &byVal);

	void C753GetAverageLuminanceLevelResult(uint32_t iCh,uint8_t &byVal);

	void C753Get23PulldownSequenceCount1(uint32_t iCh,uint8_t &byVal);
	void C753Get23PulldownSequenceCount2(uint32_t iCh,uint8_t &byVal);
	void C753Get23PulldownSequenceCount3(uint32_t iCh,uint8_t &byVal);
	void C753Get23PulldownSequenceCount4(uint32_t iCh,uint8_t &byVal);
	void C753Get23PulldownSequenceCount5(uint32_t iCh,uint8_t &byVal);

	void C753Get22PulldownSequenceCount1(uint32_t iCh,uint8_t &byVal);


	void C753GetOutputPortVerticalSyncFrequency(uint16_t &wVal);
	void C753GetPWMLowPulseWidthCounterValue(uint16_t &wVal);
	void C753GetPWMHighPulseWidthCounterValue(uint16_t &wVal);
	void C753GetFlashStatus(uint8_t &byVal);
	void C753GetInterruptStatus(uint16_t &wVal);
	void C753GetDPMSInterruptStatus(uint8_t &byVal);
	void C753GetDPMSStatus(uint8_t &byVal);

	void C753GetBlockNoiseHMatchingCountsMax(uint32_t iCh,uint8_t &byVal);
	void C753GetBlockNoiseHMatchingCountsMax2(uint32_t iCh,uint8_t &byVal);
	void C753GetBlockNoiseHBoundaryCoordinate(uint32_t iCh,uint8_t &byVal);
	void C753GetBlockNoiseVMatchingCountsMax(uint32_t iCh,uint8_t &byVal);
	void C753GetBlockNoiseVMatchingCountsMax2(uint32_t iCh,uint8_t &byVal);
	void C753GetBlockNoiseVBoundaryCoordinate(uint32_t iCh,uint8_t &byVal);


private:




};

};

#endif /* USER_H_ */
