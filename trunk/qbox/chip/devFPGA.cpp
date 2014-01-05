/*
 * devFPGA.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "devFPGA.h"
#include "devFPGAAddr.h"
#include "chipCommon.h"

using namespace chip;


DriverChipFPGA::DriverChipFPGA()
{
	FpgaSetInfo info;

	info.fp = 0xc8;
	info.freqA = 0x36;
	info.freqB = 0x02;
	info.freqC = 0x06;

	info.hs  = 702;
	info.vs = 480;
	info.pxielFreq = 2797;

	m_fpgaSetInfo[TYPE_INPUT_SIZE_702_480] = info;


	info.fp = 0xc8;
	info.freqA = 0x36;
	info.freqB = 0x02;
	info.freqC = 0x06;
	info.hs  = 720;
	info.vs = 576;
	info.pxielFreq = 2797;

	m_fpgaSetInfo[TYPE_INPUT_SIZE_720_576] = info;


	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x10;
	info.freqC = 0x19;

	info.hs  = 800;
	info.vs = 600;
	info.pxielFreq = 3998;

	m_fpgaSetInfo[TYPE_INPUT_SIZE_800_600_60] = info;

	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x1c;
	info.freqC = 0x99;

	info.hs  = 1024;
	info.vs = 768;
	info.pxielFreq = 6497;

	m_fpgaSetInfo[TYPE_INPUT_SIZE_1024_768_60] = info;


	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x02;
	info.freqC = 0x01;

	info.hs  = 1280;
	info.vs = 1024;
	info.pxielFreq = 10797;

	m_fpgaSetInfo[TYPE_INPUT_SIZE_1280_1024_60] = info;


	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x05;
	info.freqC = 0x01;

	info.hs  = 1600;
	info.vs = 1200;
	info.pxielFreq = 16196;

	m_fpgaSetInfo[TYPE_INPUT_SIZE_1600_1200_60] = info;


	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x0d;
	info.freqC = 0x8a;

	info.hs  = 1024;
	info.vs = 768;
	info.pxielFreq = 7872;


	m_fpgaSetInfo[TYPE_INPUT_SIZE_1024_768_75] = info;

	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x03;
	info.freqC = 0x81;

	info.hs  = 1280;
	info.vs = 1024;
	info.pxielFreq = 13496;

	m_fpgaSetInfo[TYPE_INPUT_SIZE_1280_1024_75] = info;



	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x1f;
	info.freqC = 0x90;

	info.hs  = 1440;
	info.vs = 900;
	info.pxielFreq = 10646;

	m_fpgaSetInfo[TYPE_INPUT_SIZE_1440_900_60] = info;


	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x07;
	info.freqC = 0x02;

	info.hs  = 1920;
	info.vs = 1080;
	info.pxielFreq = 14846;


	m_fpgaSetInfo[TYPE_INPUT_SIZE_1920_1080_60] = info;


	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x02;
	info.freqC = 0x01;

	info.hs  = 1600;
	info.vs = 900;
	info.pxielFreq = 10797;


	m_fpgaSetInfo[TYPE_INPUT_SIZE_1600_900_60] = info;

	info.fp = 0xc8;
	info.freqA = 0x31;
	info.freqB = 0x02;
	info.freqC = 0x01;

	info.hs  = 1280;
	info.vs = 960;
	info.pxielFreq = 10797;


	m_fpgaSetInfo[TYPE_INPUT_SIZE_1280_960_60] = info;
}

DriverChipFPGA::~DriverChipFPGA()
{

}

void DriverChipFPGA::setTestReg(uint16_t wVal)
{
	FPGA_Write(FPGA_TEST_REGISTER_ADDR_RW,wVal);
}
void DriverChipFPGA::getTestReg(uint16_t &wVal)
{
	FPGA_Read(FPGA_TEST_REGISTER_ADDR_RW,wVal);
}


void DriverChipFPGA::getUserVersionReg(uint16_t &wVal)
{
	FPGA_Read(FPGA_USER_VERSION_ADDR_R,wVal);
}

void DriverChipFPGA::getTestVersionReg(uint16_t &wVal)
{
	FPGA_Read(FPGA_TEST_VERSION_ADDR_R,wVal);
}

void DriverChipFPGA::getBoardTypeReg(uint16_t &wVal)
{
	FPGA_Read(FPGA_BOARD_TYPE_ADDR_R,wVal);
}

void DriverChipFPGA::getDateReg(uint16_t &wVal)
{
	FPGA_Read(FPGA_DATE_REGISTER_ADDR_R,wVal);
}



void DriverChipFPGA::setTestConfig(TestConfigT config)
{
	FPGA_Write(FPGA_TEST_HST_ADDR_RW,config.HST);
	FPGA_Write(FPGA_TEST_VST_ADDR_RW,config.VST);
	FPGA_Write(FPGA_TEST_DEW_ADDR_RW,config.DEW);
	FPGA_Write(FPGA_TEST_DEH_ADDR_RW,config.DEH);
}

void DriverChipFPGA::getTestConfig(TestConfigT &config)
{
	FPGA_Read(FPGA_TEST_HST_ADDR_RW,config.HST);
	FPGA_Read(FPGA_TEST_VST_ADDR_RW,config.VST);
	FPGA_Read(FPGA_TEST_DEW_ADDR_RW,config.DEW);
	FPGA_Read(FPGA_TEST_DEH_ADDR_RW,config.DEH);
	FPGA_Read(FPGA_TEST_EPY_ADDR_R,config.EPY);
	FPGA_Read(FPGA_TEST_FUL_ADDR_R,config.FUL);
}


void DriverChipFPGA::getInputInfo(uint32_t iChID,InputInfoT &inputInfo)
{
	switch(iChID)
	{
		case 1:
		{
			FPGA_Read(FPGA_HS_FREQ_1_ADDR,inputInfo.HSFreq);
			FPGA_Read(FPGA_VS_FREQ_1_ADDR,inputInfo.VSFreq);
			FPGA_Read(FPGA_PIXEL_FREQ_1_ADDR,inputInfo.PxielFreq);
			FPGA_Read(FPGA_HS_REGISTER_1_ADDR,inputInfo.HSRegister);
			FPGA_Read(FPGA_VS_REGISTER_1_ADDR,inputInfo.VSRegister);
			FPGA_Read(FPGA_IMG_POL_1_ADDR,inputInfo.ImgPol);
			FPGA_Read(FPGA_HOR_SYNC_1_ADDR,inputInfo.HorSync);
			FPGA_Read(FPGA_VER_SYNC_1_ADDR,inputInfo.VerSync);
			FPGA_Read(FPGA_HOR_FP_1_ADDR,inputInfo.HorFP);
			FPGA_Read(FPGA_HOR_BP_1_ADDR,inputInfo.HorBP);
			FPGA_Read(FPGA_VER_FP_1_ADDR,inputInfo.VerFP);
			FPGA_Read(FPGA_VER_BP_1_ADDR,inputInfo.VerBP);
			break;
		}
		case 2:
		{
			FPGA_Read(FPGA_HS_FREQ_2_ADDR,inputInfo.HSFreq);
			FPGA_Read(FPGA_VS_FREQ_2_ADDR,inputInfo.VSFreq);
			FPGA_Read(FPGA_PIXEL_FREQ_2_ADDR,inputInfo.PxielFreq);
			FPGA_Read(FPGA_HS_REGISTER_2_ADDR,inputInfo.HSRegister);
			FPGA_Read(FPGA_VS_REGISTER_2_ADDR,inputInfo.VSRegister);
			FPGA_Read(FPGA_IMG_POL_2_ADDR,inputInfo.ImgPol);
			FPGA_Read(FPGA_HOR_SYNC_2_ADDR,inputInfo.HorSync);
			FPGA_Read(FPGA_VER_SYNC_2_ADDR,inputInfo.VerSync);
			FPGA_Read(FPGA_HOR_FP_2_ADDR,inputInfo.HorFP);
			FPGA_Read(FPGA_HOR_BP_2_ADDR,inputInfo.HorBP);
			FPGA_Read(FPGA_VER_FP_2_ADDR,inputInfo.VerFP);
			FPGA_Read(FPGA_VER_BP_2_ADDR,inputInfo.VerBP);
			break;
		}
		case 3:
		{
			FPGA_Read(FPGA_HS_FREQ_3_ADDR,inputInfo.HSFreq);
			FPGA_Read(FPGA_VS_FREQ_3_ADDR,inputInfo.VSFreq);
			FPGA_Read(FPGA_PIXEL_FREQ_3_ADDR,inputInfo.PxielFreq);
			FPGA_Read(FPGA_HS_REGISTER_3_ADDR,inputInfo.HSRegister);
			FPGA_Read(FPGA_VS_REGISTER_3_ADDR,inputInfo.VSRegister);
			FPGA_Read(FPGA_IMG_POL_3_ADDR,inputInfo.ImgPol);
			FPGA_Read(FPGA_HOR_SYNC_3_ADDR,inputInfo.HorSync);
			FPGA_Read(FPGA_VER_SYNC_3_ADDR,inputInfo.VerSync);
			FPGA_Read(FPGA_HOR_FP_3_ADDR,inputInfo.HorFP);
			FPGA_Read(FPGA_HOR_BP_3_ADDR,inputInfo.HorBP);
			FPGA_Read(FPGA_VER_FP_3_ADDR,inputInfo.VerFP);
			FPGA_Read(FPGA_VER_BP_3_ADDR,inputInfo.VerBP);
			break;
		}
		case 4:
		{
			FPGA_Read(FPGA_HS_FREQ_4_ADDR,inputInfo.HSFreq);
			FPGA_Read(FPGA_VS_FREQ_4_ADDR,inputInfo.VSFreq);
			FPGA_Read(FPGA_PIXEL_FREQ_4_ADDR,inputInfo.PxielFreq);
			FPGA_Read(FPGA_HS_REGISTER_4_ADDR,inputInfo.HSRegister);
			FPGA_Read(FPGA_VS_REGISTER_4_ADDR,inputInfo.VSRegister);
			FPGA_Read(FPGA_IMG_POL_4_ADDR,inputInfo.ImgPol);
			FPGA_Read(FPGA_HOR_SYNC_4_ADDR,inputInfo.HorSync);
			FPGA_Read(FPGA_VER_SYNC_4_ADDR,inputInfo.VerSync);
			FPGA_Read(FPGA_HOR_FP_4_ADDR,inputInfo.HorFP);
			FPGA_Read(FPGA_HOR_BP_4_ADDR,inputInfo.HorBP);
			FPGA_Read(FPGA_VER_FP_4_ADDR,inputInfo.VerFP);
			FPGA_Read(FPGA_VER_BP_4_ADDR,inputInfo.VerBP);

			break;
		}
		case 5:
		{
			FPGA_Read(FPGA_HS_FREQ_5_ADDR,inputInfo.HSFreq);
			FPGA_Read(FPGA_VS_FREQ_5_ADDR,inputInfo.VSFreq);
			FPGA_Read(FPGA_PIXEL_FREQ_5_ADDR,inputInfo.PxielFreq);
			FPGA_Read(FPGA_HS_REGISTER_5_ADDR,inputInfo.HSRegister);
			FPGA_Read(FPGA_VS_REGISTER_5_ADDR,inputInfo.VSRegister);
			FPGA_Read(FPGA_IMG_POL_5_ADDR,inputInfo.ImgPol);
			FPGA_Read(FPGA_HOR_SYNC_5_ADDR,inputInfo.HorSync);
			FPGA_Read(FPGA_VER_SYNC_5_ADDR,inputInfo.VerSync);
			FPGA_Read(FPGA_HOR_FP_5_ADDR,inputInfo.HorFP);
			FPGA_Read(FPGA_HOR_BP_5_ADDR,inputInfo.HorBP);
			FPGA_Read(FPGA_VER_FP_5_ADDR,inputInfo.VerFP);
			FPGA_Read(FPGA_VER_BP_5_ADDR,inputInfo.VerBP);

			break;
		}
		case 6:
		{
			FPGA_Read(FPGA_HS_FREQ_6_ADDR,inputInfo.HSFreq);
			FPGA_Read(FPGA_VS_FREQ_6_ADDR,inputInfo.VSFreq);
			FPGA_Read(FPGA_PIXEL_FREQ_6_ADDR,inputInfo.PxielFreq);
			FPGA_Read(FPGA_HS_REGISTER_6_ADDR,inputInfo.HSRegister);
			FPGA_Read(FPGA_VS_REGISTER_6_ADDR,inputInfo.VSRegister);
			FPGA_Read(FPGA_IMG_POL_6_ADDR,inputInfo.ImgPol);
			FPGA_Read(FPGA_HOR_SYNC_6_ADDR,inputInfo.HorSync);
			FPGA_Read(FPGA_VER_SYNC_6_ADDR,inputInfo.VerSync);
			FPGA_Read(FPGA_HOR_FP_6_ADDR,inputInfo.HorFP);
			FPGA_Read(FPGA_HOR_BP_6_ADDR,inputInfo.HorBP);
			FPGA_Read(FPGA_VER_FP_6_ADDR,inputInfo.VerFP);
			FPGA_Read(FPGA_VER_BP_6_ADDR,inputInfo.VerBP);

			break;
		}
		default:
		{
			printf("FPGA Unknow getInputInfo! iChID=%d\n",iChID);
			break;
		}
	}
}


void DriverChipFPGA::setSelectInput(uint32_t iChID,uint16_t input)
{

	uint32_t tempChid = 0;

	if(iChID == 1 || iChID== 2)
	{
		tempChid = iChID +2;
	}

	if(iChID == 3 || iChID== 4)
	{
		tempChid = iChID -2;
	}


	uint16_t inputValue = 0;
	if(input>=1 && input<=6)
	{

		if(input == 1)
		{
			inputValue = 1;
		}
		else
		{
			inputValue =  1 << (input -1);
		}
	}
	else
	{
		printf("input Error!\n");
	}


	switch(tempChid)
	{
		case 1:
		{
			FPGA_Write(FPGA_SEL_1_ADDR,inputValue);
			break;
		}
		case 2:
		{
			FPGA_Write(FPGA_SEL_2_ADDR,inputValue);
			break;
		}
		case 3:
		{
			FPGA_Write(FPGA_SEL_3_ADDR,inputValue);
			break;
		}
		case 4:
		{
			FPGA_Write(FPGA_SEL_4_ADDR,inputValue);
			break;
		}
		case 5:
		{
			FPGA_Write(FPGA_SEL_5_ADDR,inputValue);
			break;
		}
		case 6:
		{
			FPGA_Write(FPGA_SEL_6_ADDR,inputValue);
			break;
		}
	}





}


void DriverChipFPGA::getSelectInput(uint32_t iChID,uint16_t &input)
{
	uint32_t tempChid = 0;

	if(iChID == 1 || iChID== 2)
	{
		tempChid = iChID +2;
	}

	if(iChID == 3 || iChID== 4)
	{
		tempChid = iChID -2;
	}


	uint16_t tempValue = 0;

	if(tempChid>=1 && tempChid<=6)
	{
		switch(tempChid)
		{
			case 1:
			{
				FPGA_Read(FPGA_SEL_1_ADDR,tempValue);
				break;
			}
			case 2:
			{
				FPGA_Read(FPGA_SEL_2_ADDR,tempValue);
				break;
			}
			case 3:
			{
				FPGA_Read(FPGA_SEL_3_ADDR,tempValue);
				break;
			}
			case 4:
			{
				FPGA_Read(FPGA_SEL_4_ADDR,tempValue);
				break;
			}
			case 5:
			{
				FPGA_Read(FPGA_SEL_5_ADDR,tempValue);
				break;
			}
			case 6:
			{
				FPGA_Read(FPGA_SEL_6_ADDR,tempValue);
				break;
			}
		}
	}

	if(tempValue ==1)
	{
		input =1;
	}

	if(tempValue == 2)
	{
		input =2;
	}

	if(tempValue == 4)
	{
		input =3;
	}
	if(tempValue == 8)
	{
		input =4;
	}
	if(tempValue == 16)
	{
		input =5;
	}
	if(tempValue == 32)
	{
		input =6;
	}
}

void DriverChipFPGA::getSignalModel(uint32_t signal,uint32_t &model)
{
	uint16_t wHs = 0;
	uint16_t wVs = 0;
	uint16_t wPf = 0;


//	debug_msg("getSignalModel signal=%d!",signal);



	if(signal>=1 && signal<=6)
	{
		switch(signal)
		{
			case 1:
			{
				FPGA_Read(FPGA_HS_REGISTER_1_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_1_ADDR,wVs);
				FPGA_Read(FPGA_PIXEL_FREQ_1_ADDR,wPf);
				break;
			}
			case 2:
			{
				FPGA_Read(FPGA_HS_REGISTER_2_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_2_ADDR,wVs);
				FPGA_Read(FPGA_PIXEL_FREQ_2_ADDR,wPf);
				break;
			}
			case 3:
			{
				FPGA_Read(FPGA_HS_REGISTER_3_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_3_ADDR,wVs);
				FPGA_Read(FPGA_PIXEL_FREQ_3_ADDR,wPf);
				break;
			}
			case 4:
			{
				FPGA_Read(FPGA_HS_REGISTER_4_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_4_ADDR,wVs);
				FPGA_Read(FPGA_PIXEL_FREQ_4_ADDR,wPf);
				break;
			}
			case 5:
			{
				FPGA_Read(FPGA_HS_REGISTER_5_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_5_ADDR,wVs);
				FPGA_Read(FPGA_PIXEL_FREQ_5_ADDR,wPf);
				break;
			}
			case 6:
			{
				FPGA_Read(FPGA_HS_REGISTER_6_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_6_ADDR,wVs);
				FPGA_Read(FPGA_PIXEL_FREQ_6_ADDR,wPf);
				break;
			}
		}
	}
	else
	{
		debug_msg("getSignalModel chId Error!");
	}

//	debug_msg("wHs=%d,wVs=%d!",wHs,wVs);

	model = TYPE_INPUT_SIZE_DEFAULT;

	for(map<uint32_t,FpgaSetInfo>::iterator it=m_fpgaSetInfo.begin();it!=m_fpgaSetInfo.end();++it)
	{
		if(wHs >= it->second.hs - 50
		   && wHs <= it->second.hs + 50
		   && wVs >= it->second.vs - 20
		   && wVs <= it->second.vs + 20
		   && wPf >= it->second.pxielFreq - 100
		   && wPf <= it->second.pxielFreq + 100)

		{
			model = it->first;
			break;
		}
	}

}


void DriverChipFPGA::setRingChannelMH(uint32_t channel,uint32_t flg)
{
	if(channel == 3)
	{
		if(flg == 0)
		{
			FPGA_Write(0xc6,0x31);
			FPGA_Write(0xc7,0x2);
			FPGA_Write(0xc8,0x4);
		}
		else
		{
			FPGA_Write(0xc6,0x31);
			FPGA_Write(0xc7,0x5);
			FPGA_Write(0xc8,0x1);

		}
	}

	if(channel == 4)
	{
		if(flg == 0)
		{
			FPGA_Write(0xc9,0x31);
			FPGA_Write(0xca,0x2);
			FPGA_Write(0xcb,0x4);

		}
		else
		{
			FPGA_Write(0xc9,0x31);
			FPGA_Write(0xca,0x5);
			FPGA_Write(0xcb,0x1);
		}
	}


}



void DriverChipFPGA::set753ChannelMH(uint32_t chn,uint32_t flg)
{
	uint16_t tempFlg = 0;

	FPGA_Read(0x0,tempFlg);

	if(chn == 1)
	{
		if(flg == 0)
		{
			tempFlg  = tempFlg | 0x0001;
		}
		else
		{
			tempFlg  = tempFlg & 0xfffe;
		}
	}

	if(chn == 2)
	{
		if(flg == 0)
		{
			tempFlg  = tempFlg | 0x0002;
		}
		else
		{
			tempFlg  = tempFlg & 0xfffd;
		}
	}

	FPGA_Write(0x0,tempFlg);


}

void DriverChipFPGA::setRingFreq(uint32_t channel,uint32_t model)
{
	if(channel==1 || channel==2)
	{
		return;
	}


	if(channel == 3)
	{
		FPGA_Write(0xc6,m_fpgaSetInfo[model].freqA);
		FPGA_Write(0xc7,m_fpgaSetInfo[model].freqB);
		FPGA_Write(0xc8,m_fpgaSetInfo[model].freqC);
	}
	else if(channel == 4)
	{
		FPGA_Write(0xc9,m_fpgaSetInfo[model].freqA);
		FPGA_Write(0xca,m_fpgaSetInfo[model].freqB);
		FPGA_Write(0xcb,m_fpgaSetInfo[model].freqC);
	}
}

void DriverChipFPGA::setRingFp(uint32_t channel,uint32_t model)
{

	if(channel == 1)
	{
		FPGA_Write(0xd6,m_fpgaSetInfo[model].fp);
	}
	else if(channel == 2)
	{
		FPGA_Write(0xd9,m_fpgaSetInfo[model].fp);

	}
	else if(channel == 3)
	{
		FPGA_Write(0xd0,m_fpgaSetInfo[model].fp);

	}
	else if(channel == 4)
	{
		FPGA_Write(0xd3,m_fpgaSetInfo[model].fp);
	}

}

