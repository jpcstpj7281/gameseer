/*
 * devC772.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _DEV_C772_H_
#define _DEV_C772_H_

#include <map>
#include <list>

#include "devBus.h"

#define C722_CHANNEL_1	0x0	  /* 0000'b */
#define C722_CHANNEL_2	0x1	  /* 0001'b */
#define C722_CHANNEL_3	0x2	  /* 0010'b */
#define C722_CHANNEL_4  0x3   /* 0011'b */
#define C722_CHANNEL_5	0x4	  /* 0100'b */
#define C722_CHANNEL_6	0x5	  /* 0101'b */

using namespace std;

namespace chip
{

#define MASK_HIGH8				0xff00
#define MASK_LOW8				0x00ff

#define VIDEO_MODEL_576				1
#define VIDEO_MODEL_480				0

#define POL_LOW					0
#define POL_HIGH				1

#define FLG_TRUE               1
#define FLG_FALSE              0


class DriverChip772
:public SPIBus
{

public:
	DriverChip772();
	virtual ~DriverChip772();

	void set480(uint32_t chn);
	void set576(uint32_t chn);

//	void dev_InitIP00c772(uint32_t chn);
	void initColorConversion(uint32_t chn);
	void initIPConversion(uint32_t chn);
	void initLUT(uint32_t chn);
	void reset(uint32_t chn);



	void changeModel(uint32_t chn,uint32_t byVideoModel);


	void setInputSize(uint32_t chn,uint32_t wACTHStart,uint32_t wACTHWidth,uint32_t wACTVStart,uint32_t wACTVWidth);
	void setOutputSize(uint32_t chn,uint32_t wACTHStart,uint32_t wACTHWidth,uint32_t wACTVStart,uint32_t wACTVWidth);


	void setOutputSyncCycle(uint32_t chn,uint32_t wHSyncCycle,uint32_t wVSyncCycle);
	void setBlueScreen(uint32_t chn,uint32_t byFlg);



	void setHorAndVerSyncCtrl(uint32_t chn,uint32_t byHorPolarity,uint32_t byHorWidth,uint32_t byVerPolarty,uint32_t byVerWidth);

	void setBankRegister(uint32_t chn,uint8_t byVal);
	void getBankRegister(uint32_t chn,uint8_t &byVal);

	void initBaseReg(uint32_t byChannel);

	void dev_C772_Init(uint32_t byChannel);
	void setForcedSyncReset(uint32_t byChannel,uint8_t byDelay,uint16_t wOVCyclMin);
	void initCLK(uint32_t byChannel);
	void initPurposPortIO(uint32_t byChannel);
	void initInputPara(uint32_t byChannel);
	void setPulldown(uint32_t byChannel,uint32_t byModel);
	void initPixelNR(uint32_t byChannel);


	bool isOnline(uint32_t byChannel);
private:




};

};

#endif /* USER_H_ */
