/*
 * devDriverChip753::C753.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "devC753.h"
#include "devC753Addr.h"

using namespace chip;


DriverChip753::DriverChip753()
{

}

DriverChip753::~DriverChip753()
{

}


/*Basic function*/
void DriverChip753::C753SetBasicAddress(uint32_t dwAddr){}
void DriverChip753::C753GetBasicAddress(uint32_t &dwAddr){}
void DriverChip753::C753SetMainControl(uint16_t wVal){}
void DriverChip753::C753SetCh1MainControl(uint8_t byVal){}
void DriverChip753::C753GetCh1MainControl(uint8_t &byVal){}
void DriverChip753::C753SetCh2MainControl(uint8_t byVal){}
void DriverChip753::C753GetCh2MainControl(uint8_t &byVal){}
void DriverChip753::C753SetDDRControl(uint8_t byVal){}
void DriverChip753::C753SetRegisterValueTransferControl(uint16_t wVal){}
void DriverChip753::C753SetMemoryControl(uint8_t byVal){}
void DriverChip753::C753Reset(uint8_t byVal){}
/*Bank0 function*/
void DriverChip753::C753SetOutputPortSyncControl(uint16_t wVal){}
void DriverChip753::C753GetOutputPortSyncControl(uint16_t &wVal){}

void DriverChip753::C753SetForcedSyncResetDelay(uint8_t byVal){}
void DriverChip753::C753SetForcedSyncResetControl(uint16_t wVal){}
void DriverChip753::C753SetFieldInterlockTransferControl(uint8_t byVal){}
void DriverChip753::C753SetFieldPropagationDelay1(uint8_t byVal){}
void DriverChip753::C753SetFieldPropagationDelay2(uint8_t byVal){}
void DriverChip753::C753SetOutputSignalSwap(uint8_t byVal){}
void DriverChip753::C753SetPOCLKControl(uint8_t byVal){}
void DriverChip753::C753SetScalingWidthControl(uint8_t byVal){}
void DriverChip753::C753SetInterlaceOutputControl(uint8_t byVal){}
void DriverChip753::C753SetOverlayControl(uint8_t byVal){}
void DriverChip753::C753GetOverlayControl(uint8_t &byVal){}
void DriverChip753::C753Set2ScreenBlendingAlphaCoefficient(uint8_t byVal){}
void DriverChip753::C753Set2ScreenBlendingBetaCoefficient(uint8_t byVal){}
void DriverChip753::C753SetOSDMode(uint8_t byVal){}
void DriverChip753::C753SetOSDControl(uint8_t byVal){}
void DriverChip753::C753SetOSDPenetrationColor(uint8_t byVal){}
void DriverChip753::C753SetOSDWriteInhibitColor(uint8_t byVal){}
void DriverChip753::C753SetOSDFillColor(uint8_t byVal){}
void DriverChip753::C753SetBlinkingTime(uint8_t byVal){}
void DriverChip753::C753SetBlinkCycle(uint8_t byVal){}

void DriverChip753::C753SetOSDACTHorizontalStart(uint16_t wVal){}
void DriverChip753::C753SetOSDACTHorizontalWidth(uint16_t wVal){}
void DriverChip753::C753SetOSDACTVerticalStart(uint16_t wVal){}
void DriverChip753::C753SetOSDACTVerticalWidth(uint16_t wVal){}
void DriverChip753::C753SetOSDStartAddress(uint32_t dwVal){}
void DriverChip753::C753SetOSDMemoryLinefeedWidth(uint8_t byVal){}
void DriverChip753::C753SetCharacterBufferHorizontalStart(uint8_t byVal){}
void DriverChip753::C753SetCharacterBufferHorizontalWidth(uint8_t byVal){}
void DriverChip753::C753SetCharacterBufferVerticalStart(uint8_t byVal){}
void DriverChip753::C753SetCharacterBufferVerticalWidth(uint8_t byVal){}
void DriverChip753::C753SetBitBLTHorizontalWidth(uint8_t wVal){}
void DriverChip753::C753SetBitBLTVerticalWidth(uint16_t wVal){}
void DriverChip753::C753SetCPUReadAddress(uint32_t dwVal){}
void DriverChip753::C753SetCPUWriteAddress(uint32_t dwVal){}
void DriverChip753::C753SetCPUData(uint8_t byVal){}
void DriverChip753::C753GetCPUData(uint8_t &byVal){}

void DriverChip753::C753WritePixel(uint8_t byRed, uint8_t byGreen, uint8_t byBlue, uint8_t byDump){}
void DriverChip753::C753WriteN1BitPixels(uint16_t wNPixels, RGBQuad *pC753Plt, uint8_t **ppbyMap, uint8_t *pbyBuf){}
void DriverChip753::C753WriteN8BitPixels(uint16_t wNPixels, RGBQuad *pC753Plt, uint8_t *pbyBuf){}
void DriverChip753::C753WriteN24BitPixels(uint16_t wNPixels, uint8_t *pbyBuf){}
void DriverChip753::C753ReadN24BitPixels(uint16_t wNPixels, uint8_t *pbyBuf){}
void DriverChip753::C753SetCharacterBufferAddress(uint16_t wVal){}
void DriverChip753::C753SetCharacterBufferData(uint8_t byVal){}
void DriverChip753::C753SetPaletteAddress(uint8_t byVal){}
void DriverChip753::C753SetPaletteData(uint8_t byVal){}
void DriverChip753::C753GetBitmapOSDStatus(uint8_t &byVal){}
void DriverChip753::C753SetBitmapOSD90DegreeRotation(uint8_t byVal){}
void DriverChip753::C753SetBitBLTWriteLinefeedWidth(uint8_t byVal){}
void DriverChip753::C753SetBitBLTReadLinefeedWidth(uint8_t byVal){}
void DriverChip753::C753SetBitmapOSDAccessControl(uint8_t byVal){}
void DriverChip753::C753SetMemoryProtect(uint16_t wVal){}
void DriverChip753::C753SetBitBLTTriggerVSDelay(uint8_t byVal){}
void DriverChip753::C753SetInterruptEnable(uint16_t wVal){}
void DriverChip753::C753SetInterruptReset(uint16_t wVal){}
void DriverChip753::C753SetTESTDT(uint8_t byVal){}
void DriverChip753::C753SetTESTAD(uint8_t byVal){}
void DriverChip753::C753SetTestG(uint8_t byVal){}

/*Bank 1 function*/
void DriverChip753::C753SetOutputPortOAOI0HorizontalStart(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI0HorizontalEnd(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI0VerticalStart(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI0VerticalEnd(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI1HorizontalStart(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI1HorizontalEnd(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI1VerticalStart(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI1VerticalEnd(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI2HorizontalStart(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI2HorizontalEnd(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI2VerticalStart(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI2VerticalEnd(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI3HorizontalStart(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI3HorizontalEnd(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI3VerticalStart(uint16_t wVal){}
void DriverChip753::C753SetOutputPortOAOI3VerticalEnd(uint16_t wVal){}
void DriverChip753::C753SetBackgroundControl(uint8_t byVal){}
void DriverChip753::C753SetOutputBackground0(uint32_t dwVal){}
void DriverChip753::C753SetOutputBackground1(uint32_t dwVal){}
void DriverChip753::C753SetOutputPatternBarWidth(uint8_t byVal){}
void DriverChip753::C753SetOutputPatternSpeed(uint8_t byVal){}
void DriverChip753::C753SetOutputPatternCycle(uint16_t wVal){}
void DriverChip753::C753SetPatternGeneratorControl(uint8_t byVal){}
void DriverChip753::C753SetRAMPCounterStepSetting(uint8_t byVal){}
void DriverChip753::C753SetHorizontalRAMPCounterLimitValue(uint16_t wVal){}
void DriverChip753::C753SetVerticalRAMPCounterLimitValue(uint16_t wVal){}
void DriverChip753::C753SetColorBarWidthSetting(uint8_t byVal){}
void DriverChip753::C753SetPWMControl0(uint16_t wVal){}
void DriverChip753::C753SetPWMControl1(uint16_t wVal){}
void DriverChip753::C753SetPWMControl2(uint16_t wVal){}
void DriverChip753::C753SetPWMControl3(uint16_t wVal){}
void DriverChip753::C753SetIPCLKPLLControl(uint8_t byVal){}
void DriverChip753::C753SetIPCLKReferenceDividing(uint8_t byVal){}
void DriverChip753::C753SetIPCLKFeedbackDividing(uint8_t byVal){}
void DriverChip753::C753SetPOCLKPLLControl(uint8_t byVal){}
void DriverChip753::C753SetPOCLKReferenceDividing(uint8_t byVal){}
void DriverChip753::C753SetPOCLKFeedbackDividing(uint8_t byVal){}
void DriverChip753::C753SetDLLControl0(uint8_t byVal){}
void DriverChip753::C753SetDLLControl1(uint8_t byVal){}
void DriverChip753::C753SetDLLControl2(uint8_t byVal){}
void DriverChip753::C753SetDLLControl3(uint8_t byVal){}
void DriverChip753::C753SetDLLControl4(uint8_t byVal){}
void DriverChip753::C753SetDLLControl5(uint8_t byVal){}
void DriverChip753::C753SetDLLControl6(uint8_t byVal){}
void DriverChip753::C753SetDLLControl7(uint8_t byVal){}
void DriverChip753::C753SetDLLControl8(uint8_t byVal){}

/*Bank 2/4 function*/
void DriverChip753::C753SetOutputPortACTHorizontalStart(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetOutputPortACTHorizontalWidth(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetOutputPortACTVerticalStart(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetOutputPortACTVerticalWidth(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoefficient(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeAreaSelect(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisCoefficient(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeAreaSelect(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisControl2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputFill(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetOutputImageControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisOvershootFilterCoefficient(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisUndershootFilterCoefficient(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputHorizontalEnlargementControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputHorizontalEnlargementInitialValue(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputHorizontalZoomScale(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetOutputVerticalEnlargementControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputVerticalEnlargementInitialValue(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetOutputVerticalZoomScale(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753LoadOutputHorizontalZoomLookupTable(uint32_t iCh, const uint8_t *pbyVal){}
void DriverChip753::C753LoadOutputVerticalZoomLookupTable(uint32_t iCh, const uint8_t *pbyVal){}

/*Bank 6/8 function*/
void DriverChip753::C753SetInputFormatControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputPortSyncControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputFieldRecognitionControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputDigitalInterfaceControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputComponentInputControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputPortACTHorizontalStart(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputPortACTHorizontalWidth(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputPortACTVerticalStart(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputPortACTVerticalWidth(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputSignalSwap(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputImageControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputFill(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetInputUVLowPassFilterCoefficient(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientRY(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientGY(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientBY(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientRU(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientGU(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientBU(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientRV(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientGV(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputRGBYUVCoefficientBV(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputShrinkCompensationControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputHorizontalShrinkControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputHorizontalShrinkInitialValue(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputHorizontalShrinkScale(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputVerticalShrinkControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputVerticalShrinkInitialValue(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputVerticalShrinkScale(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputHorizontalShrinkCompensation(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputVerticalShrinkCompensation(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753LoadInputHorizontalShrinkLookupTable(uint32_t iCh, const uint8_t *pbyVal){}
void DriverChip753::C753LoadInputVerticalShrinkLookupTable(uint32_t iCh, const uint8_t *pbyVal){}
/*Bank 7/9 function*/
void DriverChip753::C753SetInputImageCharacteristicsMeasurementControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetInputMeasurementHorizontalStart(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputMeasurementVerticalStart(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputMeasurementHorizontalEnd(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputMeasurementVerticalEnd(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetInputCharacteristicsMeasurementThreshold(uint32_t iCh, uint8_t byVal){}
/*Bank 10/11 function*/
void DriverChip753::C753SetIPConversionOutputPortHorizontalSyncCycle(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetIPConversionOutputPortVerticalSyncCycle(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetIPConversionForcedSyncResetDelay(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetIPConversionOutputPortActiveAreaHorizontalStart(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetIPConversionOutputPortActiveAreaHorizontalWidth(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetIPConversionOutputPortActiveAreaVerticalStart(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetIPConversionOutputPortActiveAreaVerticalWidth(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetMovementNRControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD){}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVerticalMovementValueGain(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD){}
void DriverChip753::C753SetVerticalMovementValueGain3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVerticalMovementValueGain2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVerticalMovementValueGain1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVerticalMovementValueGain0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalMovementValueGain(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD){}
void DriverChip753::C753SetHorizontalMovementValueGain3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalMovementValueGain2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalMovementValueGain1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalMovementValueGain0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVerticalDirectionMAXFilter(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMovementCoefficientNR(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetLUTWriteAddress(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetLUTCoefficient(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetLUTWriteEnable(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetIPImageAdjustment(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetIPTest(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetPulldownControl1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetPulldownControl2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753Set22PulldownMovementDetectThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753Set23PulldownMovementDetectThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetPulldownSequenceThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetPulldownAreaWidthSelect(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetPulldownDetectAreaSelect(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753Set22PulldownResetDetectIndex(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753Set23PulldownResetDetectIndex(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetCombingProcessControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetCombingProcessControlLowLevelThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetCombingProcessControlHighLevelThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetDiagonalInterpolationControl(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753LoadDiagonalInterpolationThreshold(uint32_t iCh, const uint8_t *pbyVal){}
/*Bank 12/13 function*/
void DriverChip753::C753SetOutputField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetOutputField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetOutputField2MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetOutputField3MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753GetOutputField0MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal){}
void DriverChip753::C753GetOutputField1MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal){}
void DriverChip753::C753GetOutputField2MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal){}
void DriverChip753::C753GetOutputField3MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal){}
void DriverChip753::C753SetInputField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetInputField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetInputField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetInputField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetMemoryReadLinefeedWidth(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753GetMemoryReadLinefeedWidth(uint32_t iCh, uint8_t &byVal){}
void DriverChip753::C753SetMemoryWriteLinefeedWidth(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetIPConversionField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetIPConversionField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetIPConversionField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetIPConversionField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetIPConversionField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetIPConversionField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetIPConversionMemoryLinefeedWidth(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetIPConversionMovementValueReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetTemporalNRReadStartAddressSelect(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753Set90DegreeRotationField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753Set90DegreeRotationField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753Set90DegreeRotationField2MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753Set90DegreeRotationField3MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753Set90DegreeRotationField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753Set90DegreeRotationField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753Set90DegreeRotationField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753Set90DegreeRotationField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753Set90DegreeRotationMemoryReadLinefeedWidth(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753Set90DegreeRotationMemoryWriteLinefeedWidth(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetChannel1Image90DegreeRotationControl(uint8_t byVal){}
void DriverChip753::C753SetChannel1Image90DegreeRotationHorizontalActiveAreaWidth(uint16_t wVal){}
void DriverChip753::C753SetChannel1Image90DegreeRotationVerticalActiveAreaWidth(uint16_t wVal){}
void DriverChip753::C753SetChannel1Image90DegreeRotationVerticalSyncSignalDelay(uint16_t wVal){}
void DriverChip753::C753SetChannel2Image90DegreeRotationControl(uint8_t byVal){}
void DriverChip753::C753SetChannel2Image90DegreeRotationHorizontalActiveAreaWidth(uint16_t wVal){}
void DriverChip753::C753SetChannel2Image90DegreeRotationVerticalActiveAreaWidth(uint16_t wVal){}
void DriverChip753::C753SetChannel2Image90DegreeRotationVerticalSyncSignalDelay(uint16_t wVal){}
void DriverChip753::C753SetHorizontalSyncSignalAbsenceJudgmentValue(uint16_t wVal){}
void DriverChip753::C753SetHorizontalSyncSignalPresenceJudgmentValue(uint16_t wVal){}
void DriverChip753::C753SetVerticalSyncSignalAbsenceJudgmentValue(uint8_t byVal){}
void DriverChip753::C753SetVerticalSyncSignalPresenceJudgmentValue(uint8_t byVal){}
void DriverChip753::C753Set1MHzPulseGenerationControl(uint8_t byVal){}
void DriverChip753::C753SetDPMSControl(uint8_t byVal){}
void DriverChip753::C753SetDPMSInterruptReset(uint8_t byVal){}
void DriverChip753::C753SetTemporalNRControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRThreshold1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRThreshold2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRThreshold3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRThreshold4(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRCoefficient2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRCoefficient3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRCoefficient4(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRCoefficient5(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRCoefficient6(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRCoefficient7(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetTemporalNRCoefficient8(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterHCoefficient0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterHCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterHCoefficient2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterVCoefficient0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterVCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterVCoefficient2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient4(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient5(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient4(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient5(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRBlendCoefficientBias(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRBlendCoefficientGain(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRNoiseBias(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRSubtractionBlendCoefficientGain(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThreshold0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThreshold1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThreshold2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThreshold3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThreshold4(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThreshold5(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThreshold6(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThreshold7(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThresholdBias0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThresholdBias1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThresholdBias2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThresholdBias3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThresholdBias4(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThresholdBias5(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThresholdBias6(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetMosquitoNRThresholdBias7(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetAdaptiveNRControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetAdaptiveNRThreshold(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetAdaptiveNRCoefficient(uint32_t iCh, uint32_t dwVal){}
void DriverChip753::C753SetBlockNRControl(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetBlockNRTest(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNoiseEdgeLevelThreshold0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNoiseEdgeLevelThreshold1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNoiseEdgeLevelThreshold2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNoiseEdgeLevelThreshold3(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRAlphaBlendCoefficient0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRAlphaBlendCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRLowPassFilterCoefficient0(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRLowPassFilterCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockBoundaryPeripheralMovementValueThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockBoundaryPeripheralEdgeLevelThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalBlockBoundaryCoordinate(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVerticalBlockBoundaryCoordinate(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRDetectControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetLongFramesRegisterBlockBoundaryAutoDetect(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHBlockBoundaryMatchingUpperLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHBlockBoundaryMatchingLowerLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHBlockBoundaryMatchingThresholdPeripheralPixel(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHBlockBoundaryMatchingCountsThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHBlockBoundaryMatchingCountsOffset(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVBlockBoundaryMatchingUpperLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVBlockBoundaryMatchingLowerLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVBlockBoundaryMatchingThresholdPeripheralPixel(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVBlockBoundaryMatchingCountsThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVBlockBoundaryMatchingCountsOffset(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRProjectionControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRProjectionCoefficient(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRProjectionReadAddress(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetBlockNRProjectionReadData(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalBlockBoundaryInitialCoordinateForProjection(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetHorizontalBlockEnlargementScaleForProjection(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetVerticalBlockBoundaryInitialCoordinateForProjection(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetVerticalBlockEnlargementScaleForProjection(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetHorizontalVerticalNRControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVerticalNRCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetVerticalNRCoefficient2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalNRCoefficient1(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetHorizontalNRCoefficient2(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetChromaErrorCorrectionControl(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetChromaErrorDetectionThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetChromaErrorDetectionCountThreshold(uint32_t iCh, uint16_t wVal){}
void DriverChip753::C753SetChromaErrorDetectionExclusionThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetChromaErrorAutomaticCorrectionThreshold(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetChromaErrorAutomaticCorrectionCounterUpperLimit(uint32_t iCh, uint8_t byVal){}
void DriverChip753::C753SetChromaErrorCorrectionLowPassFilterCoefficient(uint32_t iCh, uint8_t byVal){}

uint16_t DriverChip753::C753GetChannel1InputPortHorizontalSyncFrequency(void){return 0;}
uint16_t DriverChip753::C753GetChannel1InputPortVerticalSyncFrequency(void){return 0;}
uint8_t DriverChip753::C753GetChannel1InputPortHorizontalSyncPulseWidth(void){return 0;}
uint8_t DriverChip753::C753GetChannel1InputPortVerticalSyncPulseWidth(void){return 0;}

uint16_t DriverChip753::C753GetChannel2InputPortHorizontalSyncFrequency(void){return 0;}
uint16_t DriverChip753::C753GetChannel2InputPortVerticalSyncFrequency(void){return 0;}
uint8_t DriverChip753::C753GetChannel2InputPortHorizontalSyncPulseWidth(void){return 0;}
uint8_t DriverChip753::C753GetChannel2InputPortVerticalSyncPulseWidth(void){return 0;}

uint16_t DriverChip753::C753GetChannel1HorizontalAndVerticalSyncPhaseDifference0(void){return 0;}
uint16_t DriverChip753::C753GetChannel1HorizontalAndVerticalSyncPhaseDifference1(void){return 0;}

uint16_t DriverChip753::C753GetChannel2HorizontalAndVerticalSyncPhaseDifference0(void){return 0;}
uint16_t DriverChip753::C753GetChannel2HorizontalAndVerticalSyncPhaseDifference1(void){return 0;}

uint16_t DriverChip753::C753GetStatus(void){return 0;}
uint8_t DriverChip753::C753GetChannel1FieldHistory(void){return 0;}
uint8_t DriverChip753::C753GetChannel2FieldHistory(void){return 0;}

uint8_t DriverChip753::C753GetChannel1MeasurementStatusMonitor(void){return 0;}

uint8_t DriverChip753::C753GetChannel1CharacteristicsMeasurementResult0(void){return 0;}
uint8_t DriverChip753::C753GetChannel1CharacteristicsMeasurementResult1(void){return 0;}

uint16_t DriverChip753::C753GetChannel1CharacteristicsMeasurementResultHorizontalCoordinate0(void){return 0;}
uint16_t DriverChip753::C753GetChannel1CharacteristicsMeasurementResultVerticalCoordinate0(void){return 0;}
uint16_t DriverChip753::C753GetChannel1CharacteristicsMeasurementResultHorizontalCoordinate1(void){return 0;}
uint16_t DriverChip753::C753GetChannel1CharacteristicsMeasurementResultVerticalCoordinate1(void){return 0;}
uint8_t DriverChip753::C753GetChannel1SNHistogramMeasurementResult(void){return 0;}

uint8_t DriverChip753::C753GetChannel2MeasurementStatusMonitor(void){return 0;}
uint8_t DriverChip753::C753GetChannel2CharacteristicsMeasurementResult0(void){return 0;}
uint8_t DriverChip753::C753GetChannel2CharacteristicsMeasurementResult1(void){return 0;}
uint16_t DriverChip753::C753GetChannel2CharacteristicsMeasurementResultHorizontalCoordinate0(void){return 0;}
uint16_t DriverChip753::C753GetChannel2CharacteristicsMeasurementResultVerticalCoordinate0(void){return 0;}
uint16_t DriverChip753::C753GetChannel2CharacteristicsMeasurementResultHorizontalCoordinate1(void){return 0;}
uint16_t DriverChip753::C753GetChannel2CharacteristicsMeasurementResultVerticalCoordinate1(void){return 0;}
uint8_t DriverChip753::C753GetChannel2SNHistogramMeasurementResult(void){return 0;}

uint8_t DriverChip753::C753GetChannel1MAXFILTERResult(void){return 0;}
uint8_t DriverChip753::C753GetChannel1MINFILTERResult(void){return 0;}

uint8_t DriverChip753::C753GetChannel2MAXFILTERResult(void){return 0;}
uint8_t DriverChip753::C753GetChannel2MINFILTERResult(void){return 0;}

uint8_t DriverChip753::C753GetChannel1AverageLuminanceLevelResult(void){return 0;}
uint8_t DriverChip753::C753GetChannel2AverageLuminanceLevelResult(void){return 0;}

uint8_t DriverChip753::C753GetChannel123PulldownSequenceCount1(void){return 0;}
uint8_t DriverChip753::C753GetChannel123PulldownSequenceCount2(void){return 0;}
uint8_t DriverChip753::C753GetChannel123PulldownSequenceCount3(void){return 0;}
uint8_t DriverChip753::C753GetChannel123PulldownSequenceCount4(void){return 0;}
uint8_t DriverChip753::C753GetChannel123PulldownSequenceCount5(void){return 0;}
uint8_t DriverChip753::C753GetChannel122PulldownSequenceCount1(void){return 0;}
uint8_t DriverChip753::C753GetChannel223PulldownSequenceCount1(void){return 0;}
uint8_t DriverChip753::C753GetChannel223PulldownSequenceCount2(void){return 0;}
uint8_t DriverChip753::C753GetChannel223PulldownSequenceCount3(void){return 0;}
uint8_t DriverChip753::C753GetChannel223PulldownSequenceCount4(void){return 0;}
uint8_t DriverChip753::C753GetChannel223PulldownSequenceCount5(void){return 0;}
uint8_t DriverChip753::C753GetChannel222PulldownSequenceCount1(void){return 0;}
uint16_t DriverChip753::C753GetOutputPortVerticalSyncFrequency(void){return 0;}
uint16_t DriverChip753::C753GetPWMLowPulseWidthCounterValue(void){return 0;}
uint16_t DriverChip753::C753GetPWMHighPulseWidthCounterValue(void){return 0;}
uint8_t DriverChip753::C753GetFlashStatus(void){return 0;}
uint16_t DriverChip753::C753GetInterruptStatus(void){return 0;}
uint8_t DriverChip753::C753GetDPMSInterruptStatus(void){return 0;}
uint8_t DriverChip753::C753GetDPMSStatus(void){return 0;}
uint8_t DriverChip753::C753GetChannel1BlockNoiseHMatchingCountsMax(void){return 0;}
uint8_t DriverChip753::C753GetChannel1BlockNoiseHMatchingCountsMax2(void){return 0;}
uint8_t DriverChip753::C753GetChannel1BlockNoiseHBoundaryCoordinate(void){return 0;}
uint8_t DriverChip753::C753GetChannel1BlockNoiseVMatchingCountsMax(void){return 0;}
uint8_t DriverChip753::C753GetChannel1BlockNoiseVMatchingCountsMax2(void){return 0;}
uint8_t DriverChip753::C753GetChannel1BlockNoiseVBoundaryCoordinate(void){return 0;}
uint8_t DriverChip753::C753GetChannel2BlockNoiseHMatchingCountsMax(void){return 0;}
uint8_t DriverChip753::C753GetChannel2BlockNoiseHMatchingCountsMax2(void){return 0;}
uint8_t DriverChip753::C753GetChannel2BlockNoiseHBoundaryCoordinate(void){return 0;}
uint8_t DriverChip753::C753GetChannel2BlockNoiseVMatchingCountsMax(void){return 0;}

uint8_t DriverChip753::C753GetChannel2BlockNoiseVMatchingCountsMax2(void)
{
	return 0;
}


uint8_t DriverChip753::C753GetChannel2BlockNoiseVBoundaryCoordinate(void)
{
	return 0;
}







