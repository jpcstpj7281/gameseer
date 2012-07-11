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
{

public:
	DriverChip772();
	virtual ~DriverChip772();

	void dev_C772_Set480(list<map<uint8_t,uint8_t> > &value);
	void dev_C772_Set576(list<map<uint8_t,uint8_t> > &value);

	void dev_InitIP00c772(list<map<uint8_t,uint8_t> > &value);
	void dev_C772_InitColorConversion(list<map<uint8_t,uint8_t> > &value);
	void dev_C772_InitIPConversion(list<map<uint8_t,uint8_t> > &value);
	void dev_C772_InitLUT(list<map<uint8_t,uint8_t> > &value);
	void dev_C772_Reset(list<map<uint8_t,uint8_t> > &value);



	void dev_C772_ChangeModel(list<map<uint8_t,uint8_t> > &value,uint32_t byVideoModel);


	void dev_C772_SetInputSize(list<map<uint8_t,uint8_t> > &value,uint32_t wACTHStart,uint32_t wACTHWidth,uint32_t wACTVStart,uint32_t wACTVWidth);
	void dev_C772_SetOutputSize(list<map<uint8_t,uint8_t> > &value,uint32_t wACTHStart,uint32_t wACTHWidth,uint32_t wACTVStart,uint32_t wACTVWidth);


	void dev_C772_SetOutputSyncCycle(list<map<uint8_t,uint8_t> > &value,uint32_t wHSyncCycle,uint32_t wVSyncCycle);
	void dev_C772_SetBlueScreen(list<map<uint8_t,uint8_t> > &value,uint32_t byFlg);



	void dev_C772_SetHorAndVerSyncCtrl(list<map<uint8_t,uint8_t> > &value,uint32_t byHorPolarity,uint32_t byHorWidth,uint32_t byVerPolarty,uint32_t byVerWidth);


private:




};

};

#endif /* USER_H_ */
