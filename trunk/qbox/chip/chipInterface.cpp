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
	s_c753.initMemory();
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
	s_c753.moveChannelInput(chid,hPoint+1,vPoint+1);
}


void setInputSize(uint32_t chid,uint16_t hw,uint16_t vw)
{
	AppScale &s_c753=*AppScale::Instance();

	uint16_t outHw =0;
	uint16_t outVw =0;


	s_c753.C753GetOutputPortACTHorizontalWidth(chid,outHw);
	s_c753.C753GetOutputPortACTVerticalWidth(chid,outVw);

	debug_msg("setInputSize getOut HW=%d,VW=%d!",outHw,outVw);

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

void setScal(uint32_t chid,uint16_t iHw,uint16_t iVw,uint16_t oHw,uint16_t oVw)
{
	debug_msg("setScal chid=%d,ihw=%d,ivw=%d,ohw=%d,ovw=%d!",chid,iHw,iVw,oHw,oVw);
	AppScale &s_c753=*AppScale::Instance();
	s_c753.initScal(chid,iHw,iVw,oHw,oVw);
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
	uint16_t tempInput=0;

	s_cfpga.getSelectInput(chn,tempInput);
	s_cfpga.getSignalModel(tempInput,model);



}



void setChnModel(uint32_t chn,uint32_t model)
{
	if(chn == 1 || chn== 2)
	{
		AppScale &s_c753=*AppScale::Instance();

		s_c753.setInputSignalModel(chn,model);
	}


}

void topChannel(uint32_t channel)
{
	AppScale &s_c753=*AppScale::Instance();
	s_c753.topChannel(channel);
}

void init5160(uint32_t chn)
{
	DriverChip5160 s_c5160;
	s_c5160.dev_5160_InitTVP5160(chn);
}

void init772(uint32_t chn,uint32_t flg)
{

	DriverChip772 s_c772;

	s_c772.dev_C772_Init(chn);
	if(flg == 0)
	{
		s_c772.set576(chn);
	}
	else
	{
		s_c772.set480(chn);
	}
}


void DLPI2c(uint8_t dwAddr, uint8_t dwCount,uint8_t *byDate)
{

	debug_msg("dwAddr = 0x%02X dwCount=%d!",dwAddr,dwCount);

	for(int i=0;i<dwCount;i++)
	{
		debug_msg("count=%d,date=0x%02X!",i,*(byDate+i));
	}


	DLPI2cWritePage(dwAddr,dwCount,byDate);



}

void DLPI2cR(uint8_t type,uint8_t subAddr,uint8_t dwCount,uint8_t *byDate)
{

	debug_msg("DLPI2cRead dwAddr = 0x%02X dwCount=%d!",subAddr,dwCount);

	if(0xfe == subAddr)
	{
		*(byDate) = 0x0a;
		*(byDate+1) = 0x0b;
		*(byDate+2) = 0x0c;
		*(byDate+3) = 0x0d;
		*(byDate+4) = 0xe;

	}
	else
	{
		DLPI2cReadData(type,subAddr,dwCount,byDate);
	}

	for(int i=0;i<dwCount;i++)
	{
		debug_msg(" DLPI2cRead count=%d,date=0x%02X!",i,*(byDate+i));
	}


}

