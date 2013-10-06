/*
 * devC772.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _DEV_FPGA_H_
#define _DEV_FPGA_H_

#include <map>
#include <list>

#include "devBus.h"

using namespace std;

namespace chip
{

struct TestConfigT
{
	uint16_t HST;
	uint16_t VST;
	uint16_t DEW;
	uint16_t DEH;
	uint16_t EPY;
	uint16_t FUL;

};

struct InputInfoT
{
	uint16_t HSFreq;
	uint16_t VSFreq;
	uint16_t PxielFreq;
	uint16_t HSRegister;
	uint16_t VSRegister;
	uint16_t ImgPol;
	uint16_t HorSync;
	uint16_t VerSync;
	uint16_t HorFP;
	uint16_t HorBP;
	uint16_t VerFP;
	uint16_t VerBP;


};

struct FpgaSetInfo
{
	uint8_t fp;
	uint8_t freqA;
	uint8_t freqB;
	uint8_t freqC;

};


class DriverChipFPGA
:public FPGABus
{

public:
	DriverChipFPGA();
	virtual ~DriverChipFPGA();

	void setTestReg(uint16_t wVal);
	void getTestReg(uint16_t &wVal);

	void getUserVersionReg(uint16_t &wVal);
	void getTestVersionReg(uint16_t &wVal);
	void getBoardTypeReg(uint16_t &wVal);
	void getDateReg(uint16_t &wVal);

	void setTestConfig(TestConfigT config);
	void getTestConfig(TestConfigT &config);

	void getInputInfo(uint32_t iChID,InputInfoT &inputInfo);

	void setSelectInput(uint32_t iChID,uint16_t input);
	void getSelectInput(uint32_t iChID,uint16_t &input);

	void getSignalModel(uint32_t signal,uint32_t &model);

	void setRing54MH();
	void setRing162MH();


	void set753ChannelMH(uint32_t chn,uint32_t flg);
	void setRingChannelMH(uint32_t channel,uint32_t flg);

	void setRingFreq(uint32_t channel,uint32_t model);
	void setRingFp(uint32_t channel,uint32_t model);


private:

	map<uint32_t,FpgaSetInfo> m_fpgaSetInfo;


};

};

#endif /* USER_H_ */
