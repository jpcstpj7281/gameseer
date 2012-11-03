#include "appScale.h"
#include "dev.h"
#include "devFPGA.h"
#include "devICS307.h"
#include "chipCommon.h"
#include "chipInterface.h"

#include "devTVP5160.h"
#include "devC772.h"




using namespace chipApp;



void initOutputModel(uint32_t model)
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.initHardware();
	s_c753.initMemoryLineFeedWidth(1);
	s_c753.initMemoryLineFeedWidth(2);

	s_c753.initScaleTable(1);
	s_c753.initScaleTable(2);


	s_c753.setOutputBGColor(0x000000ff,0x000000ff);
	if(model == TYPE_MODEL_1024_768)
	{
		s_c753.setOutputImage(TYPE_OUTPUT_AOI1,TYPE_OUTPUT_SIZE_1024_768);
	}
	else if(model == TYPE_MODEL_1440_1050)
	{
		s_c753.setOutputImage(TYPE_OUTPUT_AOI1,TYPE_OUTPUT_SIZE_1440_1050);
	}
}

void setInputChannel(uint32_t chn,uint32_t hs,uint32_t vs,uint32_t hOffset,uint32_t vOffset)
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.setInputChannelACT(chn,hs,vs,hOffset,vOffset);
}

void setOutputChannel(uint32_t chn,uint32_t hs,uint32_t vs,uint32_t hOffset,uint32_t vOffset)
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.setOutputChannelACT(chn,hs,vs,hOffset,vOffset);
}

void moveOutputChannel(uint32_t chid,int hPoint,int vPoint)
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.moveChannelOutput(chid,hPoint,vPoint);

}

void moveInputChannel(uint32_t chid,int hPoint,int vPoint)
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.moveChannelInput(chid,hPoint,vPoint);
}


void setInputSize(uint32_t chid,uint16_t hw,uint16_t vw)
{
	AppScale &s_c753=*AppScale::Instance();

	uint16_t outHw =0;
	uint16_t outVw =0;


	s_c753.C753GetOutputPortACTHorizontalWidth(chid,outHw);
	s_c753.C753GetOutputPortACTVerticalWidth(chid,outVw);

	s_c753.initScal(chid,hw,vw,outHw,outVw);
}

void setOutputSize(uint32_t chid,uint16_t hw,uint16_t vw)
{
	AppScale &s_c753=*AppScale::Instance();

	uint16_t inputHw =0;
	uint16_t inputVw =0;


	s_c753.C753GetInputPortACTHorizontalWidth(chid,inputHw);
	s_c753.C753GetInputPortACTVerticalWidth(chid,inputVw);

	s_c753.initScal(chid,inputHw,inputVw,hw,vw);
}

void showChannel(uint32_t chn)
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.showWnd(chn);
}

void hideChannel(uint32_t chn)
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.hideWnd(chn);
}

void getSignalModel(uint32_t signal,uint32_t &model)
{
	DriverChipFPGA s_cfpga;

	s_cfpga.getSignalModel(signal,model);
}

void setChnSignalInput(uint32_t out,uint32_t in)
{
	DriverChipFPGA s_cfpga;
	s_cfpga.setSelectInput(out,(uint16_t)in);
}

void getChnSignalInput(uint32_t out,uint32_t &in)
{
	DriverChipFPGA s_cfpga;
	uint16_t input;
	s_cfpga.getSelectInput(out,input);
	in = (uint32_t)input;
}

void getChnModel(uint32_t chn,uint32_t &model)
{
	DriverChipFPGA s_cfpga;
	debug_msg("getChnModel chId=%d!",chn);
	uint16_t input=0;

	s_cfpga.getSelectInput(chn,input);
	s_cfpga.getSignalModel(input,model);


}



void setChnModel(uint32_t chn,uint32_t model)
{
	if(chn == 1 || chn== 2)
	{
		AppScale &s_c753=*AppScale::Instance();

		s_c753.setInputSignalModel(chn,model);
	}


}







