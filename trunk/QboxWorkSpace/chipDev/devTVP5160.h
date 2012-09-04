/*
 * devTVP5160.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _DEV_TVP5160_H_
#define _DEV_TVP5160_H_

#include <map>
#include <list>
#include "devBus.h"

using namespace std;

namespace chip
{

#define HIGH4_MASK				0xf0
#define LOW4_MASK				0x0f

#define COLORSCOPE_AUTO                     0
#define COLORSCOPE_ENABLED                  1
#define COLORSCOPE_DISABLED                 2
#define COLORSCOPE_VALUEMASK                0x1f
#define COLORSCOPE_MODEMASK                 0x60
#define COLORSCOPE_MODEMOVE                 5

#define GAIN_AUTO						    0
#define GAIN_MANUAL				            1
#define GAIN_AUTO_VALUE						0x0f
#define GAIN_MANUAL_VALUE					0x0e

#define MODEL_MASK 							0x7f


#define FREQ_MASK                0x20
#define FIELD_60_HZ              60
#define FIELD_50_HZ              50

#define VIEW_S_VIDEO           0x40          //选择输入通道为S_VIDEO信号
#define VIEW_CVBS              0x00

class DriverChip5160
:public I2CBus
{

public:
	DriverChip5160();
	virtual ~DriverChip5160();

	void dev_5160_SetColorScope(uint32_t byChannels,uint8_t byColorMode,uint8_t byColorValue);
	void dev_5160_GetColorScope(uint32_t byChannels,uint8_t &byColorMode,uint8_t &byColorValue);


	void dev_5160_GetBrightness(uint32_t byChannels,uint8_t &byBrightness);
	void dev_5160_SetBrightness(uint32_t byChannels,uint8_t byBrightness);

	void dev_5160_SetContrast(uint32_t byChannels,uint8_t byContrast);
	void dev_5160_GetContrast(uint32_t byChannels,uint8_t &byContrast);

	void dev_5160_SetSaturation(uint32_t byChannels,uint8_t bySaturation);
	void dev_5160_GetSaturation(uint32_t byChannels,uint8_t &bySaturation);

	void dev_5160_SetAcutance(uint32_t byChannels,uint8_t byAcutance);
	void dev_5160_GetAcutance(uint32_t byChannels,uint8_t &byAcutance);

	void dev_5160_SetColorPhasic(uint32_t byChannels,uint8_t byColorPhasic);
	void dev_5160_GetColorPhasic(uint32_t byChannels,uint8_t &byColorPhasic);

	void dev_5160_SetSignalMode(uint32_t byChannels,uint8_t bySignalMode);
	void dev_5160_GetSignalMode(uint32_t byChannels,uint8_t &bySignalMode);

	void dev_5160_SetAutoGainFlg(uint32_t byChannels,uint8_t byAutoGainFlg);
	void dev_5160_GetAutoGainFlg(uint32_t byChannels,uint8_t &byAutoGainFlg);

	void dev_5160_SetManualGainValue(uint32_t byChannels,uint8_t byManualGainValue);
	void dev_5160_GetManualGainValue(uint32_t byChannels,uint8_t &byManualGainValue);

	void dev_5160_InitTVP5160(uint32_t byChannels);
	void dev_5160_DetectInputSignal(uint32_t byChannels,uint8_t  &byInputState);
	void dev_5160_GetVsFreq(uint32_t byChannel,uint8_t &byVsFreq);
	void dev_5160_GetInputType(uint32_t byChannel,uint8_t &byInputType);
	void dev_5160_SetInputType(uint32_t byChannel,uint8_t byInputType);

private:




};

};

#endif /* USER_H_ */
