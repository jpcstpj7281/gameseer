#include "appC753.h"
#include "dev.h"


#ifdef __cplusplus
    extern "C"{


using namespace chipApp;




void main()
{
	printf("hello world!\n");
}

void chipTest()
{
	printf("chipTest\n");
	AppC753 s_c753;
	s_c753.chipTest();
}

void chipSetBankTest()
{
	uint8_t byVal = 0x0a;
	uint8_t byVal1 = 0x00;

	AppC753 s_c753;
	printf("chipTest\n");
	s_c753.C753SetBankRegister(byVal);
	s_c753.C753GetBankRegister(byVal1);
	printf("val1=%02x\n",byVal1);

}

void testSPI()
{
	printf("testSPI\n");
	uint8_t byVal=0x0a;
	uint8_t byVal1=0x00;
	dev_SPI_Write(DEV_SPI_C753_CHANNEL,0,byVal);
	dev_SPI_Read(DEV_SPI_C753_CHANNEL,0,&byVal1);
	printf("val1=%02x\n",byVal1);
}


void initHardware()
{
	printf("initHardware\n");
	AppC753 s_c753;
	ScaleConfigT config;
//	config.byStandardType;
	config.wHorResolution = 1024;
	config.wVerResolution = 768;

	s_c753.initHardware(1,&config);
}


}
#endif /* __cplusplus */
