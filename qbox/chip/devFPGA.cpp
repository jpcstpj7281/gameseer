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


//	debug_msg("getSignalModel signal=%d!",signal);



	if(signal>=1 && signal<=6)
	{
		switch(signal)
		{
			case 1:
			{
				FPGA_Read(FPGA_HS_REGISTER_1_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_1_ADDR,wVs);
				break;
			}
			case 2:
			{
				FPGA_Read(FPGA_HS_REGISTER_2_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_2_ADDR,wVs);
				break;
			}
			case 3:
			{
				FPGA_Read(FPGA_HS_REGISTER_3_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_3_ADDR,wVs);
				break;
			}
			case 4:
			{
				FPGA_Read(FPGA_HS_REGISTER_4_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_4_ADDR,wVs);
				break;
			}
			case 5:
			{
				FPGA_Read(FPGA_HS_REGISTER_5_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_5_ADDR,wVs);
				break;
			}
			case 6:
			{
				FPGA_Read(FPGA_HS_REGISTER_6_ADDR,wHs);
				FPGA_Read(FPGA_VS_REGISTER_6_ADDR,wVs);
				break;
			}
		}
	}
	else
	{
		debug_msg("getSignalModel chId Error!");
	}

//	debug_msg("wHs=%d,wVs=%d!",wHs,wVs);


	if(wHs > 700
	   && wHs < 720
	   && wVs > 480
	   && wVs < 500)
	{
//		if(signal ==1 || signal ==2)
//		{
//			model = TYPE_INPUT_SIZE_702_480_RING;
//		}
//		else
		{
			model = TYPE_INPUT_SIZE_702_480;
		}
	}
	else if(wHs > 790
			   && wHs < 810
			   && wVs > 590
			   && wVs < 610)
	{
		model = TYPE_INPUT_SIZE_800_600;
	}
	else if(wHs > 1000
			   && wHs < 1100
			   && wVs > 750
			   && wVs < 780)
	{
		model = TYPE_INPUT_SIZE_1024_768_60;
	}
	else if(wHs > 1200
			   && wHs < 1350
			   && wVs > 1000
			   && wVs < 1100)
	{
		model = TYPE_INPUT_SIZE_1280_1024_60;
	}
	else if(wHs > 1580
			   && wHs < 1680
			   && wVs > 1180
			   && wVs < 1280)
	{
		model = TYPE_INPUT_SIZE_1600_1200_60;
	}
	else
	{
		model = TYPE_INPUT_SIZE_DEFAULT;
//		debug_msg("getSignalModel TYPE_INPUT_SIZE_DEFAULT");
	}

}





