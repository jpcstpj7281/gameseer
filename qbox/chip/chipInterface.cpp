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

void getSignalModel(uint32_t chn,uint32_t &model)
{
	DriverChipFPGA s_cfpga;
	getSignalModel(chn,model);
}

void setChnSignalModel(uint32_t chn,uint32_t model)
{
	if(chn == 1 || chn== 2)
	{
		AppScale &s_c753=*AppScale::Instance();
		s_c753.setInputSignalModel(chn,model);
	}
}


//
//
//
//void topChannel(uint32_t channel)
//{
//	AppScale s_c753;
//	s_c753.topChannel(channel);
//}
//
//
//void testScale(uint32_t chId,uint32_t hInput,uint32_t vInput,uint32_t hOutput,uint32_t vOutput)
//{
//	AppScale s_c753;
//
//
//	s_c753.initScaleTable(chId);
//	s_c753.initScal(chId,hInput,hOutput,vInput,vOutput);
//
//	s_c753.C753SetInputPortACTHorizontalWidth(chId,hInput);
//	s_c753.C753SetInputPortACTVerticalWidth(chId,vInput);
//
//	s_c753.C753SetOutputPortACTHorizontalWidth(chId, hOutput);
//	s_c753.C753SetOutputPortACTVerticalWidth(chId,vOutput);
//
//}
//
//void setC753OutPutACT(uint32_t chid,uint32_t hWidth,uint32_t VWidth,uint32_t hStar,uint32_t VStar)
//{
//
//	AppScale s_c753;
//	s_c753.setOutputChannelACT(chid,hWidth,VWidth,hStar,VStar);
//}
//
//
//void setC753InputACT(uint32_t chid,uint32_t hWidth,uint32_t VWidth,uint32_t hStar,uint32_t VStar)
//{
//	AppScale s_c753;
//	s_c753.setInputChannelACT(chid,hWidth,VWidth,hStar,VStar);
//
//}
//
//void moveOutput(uint32_t chid,int hPoint,int vPoint)
//{
//	AppScale s_c753;
//	s_c753.moveChannelOutput(chid,hPoint,vPoint);
//
//}
//
//void moveInput(uint32_t chid,int hPoint,int vPoint)
//{
//	AppScale s_c753;
//	s_c753.moveChannelInput(chid,hPoint,vPoint);
//}
//
//void test5160()
//{
//	DriverChip5160 s_c5160;
//	uint8_t val1 = 0x40;
//	uint8_t val = 0x00;
//	s_c5160.dev_5160_SetInputType(1,val1);
//	s_c5160.dev_5160_GetInputType(1,val);
//	if(val1!=val)
//	{
//		debug_msg("test5160 error val1=%02x,val=%02x\n",val1,val);
//	}
//}
//
//void testC772()
//{
//	DriverChip772 s_c772;
//	uint8_t val1 = 0x0a;
//	uint8_t val = 0x00;
//
//	s_c772.SetBankRegister(1,val1);
//	s_c772.SetBankRegister(1,val);
//	if(val1!=val)
//	{
//		debug_msg("testC772 error val1=%02x,val=%02x\n",val1,val);
//	}
//
//}
//
//
//void initSD480(uint32_t chn)
//{
//	debug_msg("initSD480\n");
//	DriverChip5160 s_c5160;
//	DriverChip772 s_c772;
//
//	s_c5160.dev_5160_InitTVP5160(chn);
//	s_c772.dev_InitIP00c772(chn);
//	s_c772.dev_C772_Set480(chn);
//}
//
//
//
//void initSD576(uint32_t chn)
//{
//	debug_msg("initSD576\n");
//	DriverChip5160 s_c5160;
//	DriverChip772 s_c772;
//
//	s_c5160.dev_5160_InitTVP5160(chn);
//	s_c772.dev_InitIP00c772(chn);
//	s_c772.dev_C772_Set576(chn);
//}
//
//void init5160(uint32_t chn)
//{
//	DriverChip5160 s_c5160;
//	s_c5160.dev_5160_InitTVP5160(chn);
//}
//
//void init772(uint32_t chn,uint32_t flg)
//{
//	DriverChip772 s_c772;
//	if(flg == 0)
//	{
//		s_c772.dev_C772_Set576(chn);
//	}
//	else
//	{
//		s_c772.dev_C772_Set480(chn);
//	}
//}






