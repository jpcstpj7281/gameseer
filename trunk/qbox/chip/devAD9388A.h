/*
 * devTVP5160.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _DEV_AD9388A_H_
#define _DEV_AD9388A_H_

#include <map>
#include <list>
#include "devBus.h"

using namespace std;

namespace chip
{


class DriverChip9388A
:public I2CBus
{

public:
	DriverChip9388A();
	virtual ~DriverChip9388A();



#define POLARITY_NEGATIVE         0
#define POLARITY_POSITIVE         1

#define PLL_DIV_MAN_ENABLE       0x1
#define PLL_DIV_MAN_DISABLE      0x0


void dev_InitAD9388A(uint32_t byChannels);
void dev_DetectCPRun(uint32_t byChannels,uint8_t &byInputState);

void getBL(uint32_t byChannel,uint16_t &wBLValue);
void getFL(uint32_t byChannel,uint16_t &wFLValue);
void getSCF(uint32_t byChannel,uint16_t &wSCFValue);
void getSCVS(uint32_t byChannel,uint16_t &wSCVSValue);

void dev_ARGB_GetSTDI(uint32_t byChannel,uint16_t &wBLValue,uint16_t &wSCFValue,uint16_t &wSCVSValue,uint16_t &wFCLValue);

void getHsPol(uint32_t byChannel,uint8_t &byPolarity);
void getVsPol(uint32_t byChannel,uint8_t &byPolarity);

void dev_ARGB_Polarity(uint32_t byChannel,uint8_t &byHs,uint8_t &byVs);
void dev_DRGB_GeneralConfig(uint32_t byChannel);
void dev_ARGB_GeneralConfig(uint32_t byChannel);

void dev_ARGB_PLLVocManEn(uint32_t byChannel,uint8_t byFlg);
void dev_ARGB_SetPllDivRatio(uint32_t byChannel,uint16_t wPllDivRatio);
void dev_ARGB_SetVCORange(uint32_t byChannel,uint32_t dwPixelClock);
void dev_ARGB_SetFRLL(uint32_t byChannel,uint16_t wBL);
void dev_ARGB_SetFRLCountMax(uint32_t byChannel,uint16_t wLCountMax);
void dev_ARGB_SetSavEav(uint32_t byChannel,uint16_t  wCPSAV,uint16_t  wCPEAV,uint16_t  wVBISAV,uint16_t wVBIEAV);

void getLineWidth(uint32_t byChannel,uint16_t &wLineWidth);
void getTMDSFreq(uint32_t byChannel,uint8_t &byTMDSFreq);
void getF0H(uint32_t byChannel,uint16_t &wF0H);
void getF1H(uint32_t byChannel,uint16_t &wF1H);

void dev_DRGB_GetSignalPara(uint32_t byChannel,uint8_t &wTMDSFreq,uint16_t &wLineWidth,uint16_t &wF0H,uint16_t &wF1H);

void dev_ARGB_DetectInput(uint32_t byChannel, uint8_t &bySignalState);
void dev_DRGB_DetectInput(uint32_t byChannel, uint8_t &bySignalState);

void dev_ARGB_SetPhase(uint32_t byChannel,uint8_t byPhase);
void dev_ARGB_GetPhase(uint32_t byChannel,uint8_t &byPhase);

void dev_RGB_GetBrightness(uint32_t byChannels,uint8_t &byBrightness);
void dev_RGB_SetBrightness(uint32_t byChannels,uint8_t byBrightness);
void dev_RGB_GetContrast(uint32_t byChannels,uint8_t &byContrast);
void dev_RGB_SetContrast(uint32_t byChannels,uint8_t byContrast);
void dev_RGB_GetSaturation(uint32_t byChannels,uint8_t &bySaturation);
void dev_RGB_SetSaturation(uint32_t byChannels,uint8_t bySaturation);
void dev_RGB_GetColorPhase(uint32_t byChannels,uint8_t &byColorPhase);
void dev_RGB_SetColorPhase(uint32_t byChannels,uint8_t byColorPhase);



private:




};

};

#endif /* USER_H_ */
