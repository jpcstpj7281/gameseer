#include "appScale.h"
#include "dev.h"
#include "devFPGA.h"
#include "devICS307.h"
#include "chipCommon.h"

#include "devTVP5160.h"
#include "devC772.h"

#ifdef __cplusplus
    extern "C"{


using namespace chipApp;


void set753(uint8_t byAdd,uint8_t byVal)
{
	AppScale s_c753;
	debug_msg("Test C753 addr=%02x,byVal=%02x\n",byAdd,byVal);
	s_c753.SPI_Write(TYPE_CHIP_C753,byAdd,byVal);
}


void get753(uint8_t byAdd)
{

	uint8_t byVal=0;
	AppScale s_c753;
	s_c753.SPI_Read(TYPE_CHIP_C753,byAdd,byVal);
	debug_msg("addr=%02x,val=%02x\n",byAdd,byVal);
}

void chipSetFPGATest(uint16_t addr,uint16_t wVal)
{

	DriverChipFPGA s_FPGA;

	debug_msg("Test FPGA set addr=%04x,byVal=%04x\n",addr,wVal);

	s_FPGA.FPGA_Write(addr,wVal);

	uint16_t byVal=0;
	s_FPGA.FPGA_Read(addr,byVal);
	debug_msg("Read addr=%04x,val1=%04x\n",addr,byVal);

}


void chipGetFPGATest(uint16_t addr)
{
	uint16_t byVal=0;
	DriverChipFPGA s_FPGA;
	s_FPGA.FPGA_Read(addr,byVal);
	debug_msg("addr=%04x,val1=%04x\n",addr,byVal);
}
void testSPI()
{
	debug_msg("testSPI\n");
	uint8_t byVal=0x0a;
	uint8_t byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C753_CHANNEL,0,byVal);
	dev_SPI_Read(DEV_SPI_C753_CHANNEL,0,&byVal1);
	debug_msg("val1=%02x\n",byVal1);
}




void testFPGA()
{
	debug_msg("testFPGA\n");
	DriverChipFPGA s_FPGA;

	uint16_t byVal=0x0a;
	uint16_t byVal1=0x00;

	s_FPGA.setTestReg(byVal);
	s_FPGA.getTestReg(byVal1);
	if(byVal!=byVal1)
	{
		debug_msg("FPGA ERROR! TEST Reg write = %02x ,read=%02x \n",byVal,byVal1);
	}

	for(uint32_t i=1;i<=6;i++)
	{
		InputInfoT info;
		s_FPGA.getInputInfo(i,info);
		debug_msg("------FPGA CHID:%d--------\n",i);
		debug_msg("------HSFreq:%d--------\n",info.HSFreq);
		debug_msg("------VSFreq:%d--------\n",info.VSFreq);
		debug_msg("------PxielFreq:%d--------\n",info.PxielFreq);
		debug_msg("------HSRegister:%d--------\n",info.HSRegister);
		debug_msg("------VSRegister:%d--------\n",info.VSRegister);
		debug_msg("------ImgPol:%d--------\n",info.ImgPol);
		debug_msg("------HorSync:%d--------\n",info.HorSync);
		debug_msg("------VerSync:%d--------\n",info.VerSync);
		debug_msg("------HorFP:%d--------\n",info.HorFP);
		debug_msg("------HorBP:%d--------\n",info.HorBP);
		debug_msg("------VerFP:%d--------\n",info.VerFP);
		debug_msg("------VerBP:%d--------\n",info.VerBP);
		debug_msg("----------------------------------\n",i);
	}

	for(uint32_t i=1;i<=4;i++)
	{
		uint16_t inputValue=0;
		s_FPGA.getSelectInput(i,inputValue);
		debug_msg("FPGA CHID:%d select input:%d\n",i,inputValue);
	}


}

void setFpgaSelectChn(uint32_t chn,uint32_t input)
{
	DriverChipFPGA s_FPGA;
	s_FPGA.setSelectInput(chn,input);

}


void getC753ChnInput(uint32_t chn)
{
	debug_msg("getC753ChnInput\n");
	AppScale s_c753;

	uint16_t wHsFreq=0;
	s_c753.C753GetInputPortHorizontalSyncFrequency(chn,wHsFreq);

	uint16_t wVsFreq=0;
	s_c753.C753GetInputPortVerticalSyncFrequency(chn,wVsFreq);

	uint8_t byHsWidth=0;
	s_c753.C753GetInputPortHorizontalSyncPulseWidth(chn,byHsWidth);

	uint8_t byVsWidth=0;
	s_c753.C753GetInputPortVerticalSyncPulseWidth(chn,byVsWidth);

	debug_msg("\n--------------C753 CHN=%d INFO-----------------\n",chn);
	debug_msg("\nwHsFreq:%d,wVsFreq:%d,byHsWidth:%d,byVsWidth:%d\n",wHsFreq,wVsFreq,byHsWidth,byVsWidth);



}



void initMoney()
{
	AppScale s_c753;

//	s_c753.C753SetOutputField0MemoryReadStartAddress(1, 0x00c00000);
//	s_c753.C753SetOutputField1MemoryReadStartAddress(1, 0x00000000);
//	s_c753.C753SetOutputField2MemoryReadStartAddress(1, 0x00400000);
//	s_c753.C753SetOutputField3MemoryReadStartAddress(1, 0x00800000);
//	s_c753.C753SetInputField0MemoryWriteStartAddress(1, 0x00000000);
//	s_c753.C753SetInputField1MemoryWriteStartAddress(1, 0x00400000);
//	s_c753.C753SetInputField2MemoryWriteStartAddress(1, 0x00800000);
//	s_c753.C753SetInputField3MemoryWriteStartAddress(1, 0x00C00000);

	s_c753.C753SetOutputField0MemoryReadStartAddress(1, 0x00000000);
	s_c753.C753SetOutputField1MemoryReadStartAddress(1, 0x00400000);
	s_c753.C753SetOutputField2MemoryReadStartAddress(1, 0x00800000);
	s_c753.C753SetOutputField3MemoryReadStartAddress(1, 0x00c00000);
	s_c753.C753SetInputField0MemoryWriteStartAddress(1, 0x00000000);
	s_c753.C753SetInputField1MemoryWriteStartAddress(1, 0x00400000);
	s_c753.C753SetInputField2MemoryWriteStartAddress(1, 0x00800000);
	s_c753.C753SetInputField3MemoryWriteStartAddress(1, 0x00C00000);
}



void initTest1400()
{
	debug_msg("initTest1400\n");
	AppScale s_c753;
	DriverChipICS307 s_ics307;

	s_ics307.setPOCLK(ICS307_FREQUENCY_121750KHZ);
	s_c753.initTest1400();
	debug_msg("showWnd\n");
	s_c753.showWnd(1);
}

void selectOutPut(uint32_t model)
{
	AppScale s_c753;
	s_c753.selectOutPutModel(model);
}



void setC753OutPutOAI1(uint32_t hStar,uint32_t hWidth,uint32_t VStar,uint32_t VWidth)
{
	AppScale s_c753;
	s_c753.C753SetOutputPortOAOI1HorizontalStart((uint16_t)hStar);
	s_c753.C753SetOutputPortOAOI1HorizontalEnd((uint16_t)hWidth);
	s_c753.C753SetOutputPortOAOI1VerticalStart((uint16_t)VStar);
	s_c753.C753SetOutputPortOAOI1VerticalEnd((uint16_t)VWidth);
}

void setC753OutPutOAI0(uint32_t hStar,uint32_t hWidth,uint32_t VStar,uint32_t VWidth)
{
	AppScale s_c753;
	s_c753.C753SetOutputPortOAOI0HorizontalStart((uint16_t)hStar);
	s_c753.C753SetOutputPortOAOI0HorizontalEnd((uint16_t)hWidth);
	s_c753.C753SetOutputPortOAOI0VerticalStart((uint16_t)VStar);
	s_c753.C753SetOutputPortOAOI0VerticalEnd((uint16_t)VWidth);
}



void testMACRO()
{
	#ifdef __unix__
		cout<<"unix!"<<endl;
	#else
		cout<<"vxWork!"<<endl;
	#endif

}

void C753SetOutFill(uint32_t chn,uint32_t color,uint8_t model)
{
	debug_msg("C753SetOutFill\n");
	AppScale s_c753;
	s_c753.C753SetOutputFill(chn,color);
	s_c753.C753SetOutputImageControl(chn,model);

	s_c753.showWnd(chn);
}


void C753SetInputFill(uint32_t flg,uint32_t chid,uint32_t color)
{
	debug_msg("C753SetInputFill\n");
	AppScale s_c753;

	s_c753.C753SetInputFill(chid,color);
	if(flg == 1)
	{

		s_c753.C753SetInputImageControl(chid,0x10);
	}
	else
	{
		s_c753.C753SetInputImageControl(chid,0);
	}




}

void demo()
{
	AppScale s_c753;
	s_c753.initHardware();
	s_c753.initMemoryLineFeedWidth(1);
	s_c753.initMemoryLineFeedWidth(2);

	s_c753.setOutputBGColor(0x000000ff,0x000000ff);
	s_c753.setOutputImage(TYPE_OUTPUT_AOI1,TYPE_OUTPUT_SIZE_1440_1050);


	s_c753.setInputChannelACT(1,1024,768,303,36);
	s_c753.setOutputChannelACT(1,1024,768,20,10);

	s_c753.setInputChannelACT(2,1024,768,303,36);
	s_c753.setOutputChannelACT(2,1024,768,350,300);

}

void demoMove()
{

}

void topChannel(uint32_t channel)
{
	AppScale s_c753;
	s_c753.topChannel(channel);
}


void testScale(uint32_t chId,uint32_t hInput,uint32_t vInput,uint32_t hOutput,uint32_t vOutput)
{
	AppScale s_c753;


	s_c753.initScaleTable(chId);
	s_c753.initScal(chId,hInput,hOutput,vInput,vOutput);

	s_c753.C753SetInputPortACTHorizontalWidth(chId,hInput);
	s_c753.C753SetInputPortACTVerticalWidth(chId,vInput);

	s_c753.C753SetOutputPortACTHorizontalWidth(chId, hOutput);
	s_c753.C753SetOutputPortACTVerticalWidth(chId,vOutput);

}

void setC753OutPutACT(uint32_t chid,uint32_t hWidth,uint32_t VWidth,uint32_t hStar,uint32_t VStar)
{

	AppScale s_c753;
	s_c753.setOutputChannelACT(chid,hWidth,VWidth,hStar,VStar);
}


void setC753InputACT(uint32_t chid,uint32_t hWidth,uint32_t VWidth,uint32_t hStar,uint32_t VStar)
{
	AppScale s_c753;
	s_c753.setInputChannelACT(chid,hWidth,VWidth,hStar,VStar);

}

void moveOutput(uint32_t chid,int hPoint,int vPoint)
{
	AppScale s_c753;
	s_c753.moveChannelOutput(chid,hPoint,vPoint);

}

void moveInput(uint32_t chid,int hPoint,int vPoint)
{
	AppScale s_c753;
	s_c753.moveChannelInput(chid,hPoint,vPoint);
}

void test5160()
{
	DriverChip5160 s_c5160;
	uint8_t val1 = 0x40;
	uint8_t val = 0x00;
	s_c5160.dev_5160_SetInputType(1,val1);
	s_c5160.dev_5160_GetInputType(1,val);
	if(val1!=val)
	{
		debug_msg("test5160 error val1=%02x,val=%02x\n",val1,val);
	}
}

void testC772()
{
	DriverChip772 s_c772;
	uint8_t val1 = 0x0a;
	uint8_t val = 0x00;

	s_c772.SetBankRegister(1,val1);
	s_c772.SetBankRegister(1,val);
	if(val1!=val)
	{
		debug_msg("testC772 error val1=%02x,val=%02x\n",val1,val);
	}

}


}
#endif /* __cplusplus */



