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
	if(input>=1 && input<=6)
	{
		switch(iChID)
		{
			case 1:
			{
				FPGA_Write(FPGA_SEL_1_ADDR,(input-1));
				break;
			}
			case 2:
			{
				FPGA_Write(FPGA_SEL_2_ADDR,(input-1));
				break;
			}
			case 3:
			{
				FPGA_Write(FPGA_SEL_3_ADDR,(input-1));
				break;
			}
			case 4:
			{
				FPGA_Write(FPGA_SEL_4_ADDR,(input-1));
				break;
			}
			case 5:
			{
				FPGA_Write(FPGA_SEL_5_ADDR,(input-1));
				break;
			}
			case 6:
			{
				FPGA_Write(FPGA_SEL_6_ADDR,(input-1));
				break;
			}
		}

	}
	else
	{
		printf("input Error!\n");
	}
}


void DriverChipFPGA::getSelectInput(uint32_t iChID,uint16_t &input)
{
	if(input>=1 && input<=6)
	{
		switch(iChID)
		{
			case 1:
			{
				FPGA_Read(FPGA_SEL_1_ADDR,input);
				break;
			}
			case 2:
			{
				FPGA_Read(FPGA_SEL_2_ADDR,input);
				break;
			}
			case 3:
			{
				FPGA_Read(FPGA_SEL_3_ADDR,input);
				break;
			}
			case 4:
			{
				FPGA_Read(FPGA_SEL_4_ADDR,input);
				break;
			}
			case 5:
			{
				FPGA_Read(FPGA_SEL_5_ADDR,input);
				break;
			}
			case 6:
			{
				FPGA_Read(FPGA_SEL_6_ADDR,input);
				break;
			}
		}
	}

	input++;
}


