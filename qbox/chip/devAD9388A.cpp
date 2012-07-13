/*
 * devTVP5160.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "devAD9388A.h"
#include "devAD9388AAddr.h"

using namespace chip;


DriverChip9388A::DriverChip9388A()
{

}

DriverChip9388A::~DriverChip9388A()
{

}

void DriverChip9388A::dev_InitAD9388A(uint32_t byChannels)
{
    /*Disable TOD*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP, AD9388_USER_TOD, 0x0c);
    /*28.63636MHz LLC Pin Active*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP,AD9388_USER_VER_SCAL_VAL, 0x40);
     /*PCLK polarity*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP,AD9388_USER_TLLC_POLARITY, 0x01);
     /*SOG Sync level for atenuated sync, PLL Qpump = 6h*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP,AD9388_USER_TLLC_CTRL, 0xae);
     /*Enable Automatic PLL_Qpump and VCO Range*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP,AD9388_USER_PLL_QPUMP_CTRL, 0x0a);
     /*Auto CSC , RGB Out*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP,AD9388_USER_CSC_23, 0xf2);
     /*TURN OFF EAV & SAV CODES*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP,AD9388_USER_CP_AV_CTRL, 0x1d);
     /*Progressive mode*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP, AD9388_USER_DPP_CP_64, 0x10);
     /*Enable HDMI and Analog in*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP,AD9388_USER_HDMI_CTRL, 0xa0);
     /*Max Drive Strength*/
	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP,AD9388_USER_DRIVE_STR, 0x3f);

	dev_I2C_Write(byChannels, I2C_ADDR_USER_MAP, AD9388_USER_ADC_CTRL, 0x60);

}

void DriverChip9388A::dev_DetectCPRun(uint32_t byChannels,uint8_t &byInputState)
{
    uint8_t byRtn = 0;

    dev_I2C_Read(byChannels,I2C_ADDR_USER_MAP,AD9388_USER_STATUS_2,byRtn);

    byRtn = byRtn & 0x40;
    if(byRtn == 0x40)
    {
    	byInputState = 1;
    }
    else
    {
    	byInputState = 0;
    }
}

void DriverChip9388A::getBL(uint32_t byChannel,uint16_t &wBLValue)
{
    uint8_t byValue = 0;

    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_1,byValue);
    wBLValue = byValue & 0x3f;
    wBLValue = wBLValue << 8;


    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_2,byValue);
    wBLValue = wBLValue | byValue;

}

void DriverChip9388A::getFL(uint32_t byChannel,uint16_t &wFLValue)
{
    uint8_t byValue = 0;


    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_FCL_1,byValue);
    wFLValue = byValue & 0x1f;
    wFLValue = wFLValue << 8;


    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_FCL_2,byValue);
    wFLValue = wFLValue | byValue;


}

void DriverChip9388A::getSCF(uint32_t byChannel,uint16_t &wSCFValue)
{
    uint8_t byValue = 0;

    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_3,byValue);
    wSCFValue = byValue & 0x07;
    wSCFValue = wSCFValue << 8;


    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_4,byValue);
    wSCFValue = wSCFValue | byValue;
}

void DriverChip9388A::getSCVS(uint32_t byChannel,uint16_t &wSCVSValue)
{

    uint8_t byValue = 0;

    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_3,byValue);
    wSCVSValue = byValue & 0xf8;
    wSCVSValue = wSCVSValue >> 3;


}

void DriverChip9388A::dev_ARGB_GetSTDI(uint32_t byChannel,uint16_t &wBLValue,uint16_t &wSCFValue,uint16_t &wSCVSValue,uint16_t &wFCLValue)
{
    uint8_t byValue = 0;


    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_1,byValue);

    byValue = byValue & 0x80;

    if(byValue == 0x80)
    {
        getBL(byChannel,wBLValue);
        getSCF(byChannel,wSCFValue);
        getSCVS(byChannel,wSCVSValue);
        getFL(byChannel,wFCLValue);
    }
    else
    {
        return ;
    }


}

void DriverChip9388A::getHsPol(uint32_t byChannel,uint8_t &byPolarity)
{
    uint8_t byValue = 0;

    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_5,byValue);

    byValue = byValue & 0x08;

    if(byValue == 0x08)
    {
    	byPolarity = POLARITY_POSITIVE;
    }
    else
    {
    	byPolarity = POLARITY_NEGATIVE;
    }

}

void DriverChip9388A::getVsPol(uint32_t byChannel,uint8_t &byPolarity)
{
    uint8_t byValue = 0;

    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_5,byValue);

    byValue = byValue & 0x20;

    if(byValue == 0x20)
    {
    	byPolarity = POLARITY_POSITIVE;
    }
    else
    {
    	byPolarity = POLARITY_NEGATIVE;
    }

}

void DriverChip9388A::dev_ARGB_Polarity(uint32_t byChannel,uint8_t &byHs,uint8_t &byVs)
{
    uint8_t byRtn = 0;
    uint8_t byValue = 0;

    getHsPol(byChannel, byHs);
	getVsPol(byChannel, byVs);
}

void DriverChip9388A::dev_DRGB_GeneralConfig(uint32_t byChannel)
{
    uint16_t wValue = 0;
	int iRtn = 0;


    	/*HDMI Graphics mode PRIM_MODE_HDMI_GR*/
	dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_PRIM_MODE, 0x06);
    	/*VID_STD=00111b for automatic graphics mode VID_STD_RESERVED*/
	dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_VID_STD, 0x07);

        /*Setting cp_op_sel = 2 & Enable DE VS HS*/
	dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_CP_OUT_SEL, 0xe2);
    	/*color too white rgb 656 range*/
	dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_CSC_22, 0x01);

    dev_ARGB_SetSavEav(byChannel,0,0,0,0);

        /*Sed DE start H Start to prevent to masked data*/

    dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_CP_DE_CTRL_1, 0x40);

    dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_CP_DE_CTRL_3, 0x00);
        //以下为非正常情况下使用
}

void DriverChip9388A::dev_ARGB_GeneralConfig(uint32_t byChannel)
{
    int iRtn = 0;

        /*Prim_Mode =010b for GR*/
    dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_PRIM_MODE, 0x02);

    	/*VID_STD=00111b for automatic graphics mode*/
    dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_VID_STD, 0x07);

    	/*SOG Sync level for atenuated sync, PLL Qpump = 6h*/
    dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_TLLC_CTRL, 0xae);

        /*Enable Automatic VCO Range. Enable auto PLL-Qpump for this mode.*/
    dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_PLL_QPUMP_CTRL, 0x0a);

        /*Setup CPOP_SEL & Field Enable*/
    dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_CP_OUT_SEL, 0xe2);

}

void DriverChip9388A::dev_ARGB_PLLVocManEn(uint32_t byChannel,uint8_t byFlg)
{
    uint8_t byValue = 0;

    dev_I2C_Read(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_CP_TLLC_CTRL_1,byValue);

    if(byFlg == PLL_DIV_MAN_ENABLE)
    {
        byValue = byValue | 0x80;
    }
    else
    {
        byValue = byValue & 0x7f;
    }

    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_CP_TLLC_CTRL_1,byValue);



    dev_I2C_Read(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_CP_TLLC_CTRL_4,byValue);

    if(byFlg == PLL_DIV_MAN_ENABLE)
    {
        byValue = byValue | 0x80;
    }
    else
    {
        byValue = byValue & 0x7f;
    }
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_CP_TLLC_CTRL_4,byValue);

}

void DriverChip9388A::dev_ARGB_SetPllDivRatio(uint32_t byChannel,uint16_t wPllDivRatio)
{
    uint8_t byValue = 0;
    uint8_t byHByte = 0;
    uint8_t byLByte = 0;

    byHByte = (uint8_t)((wPllDivRatio >> 8) & 0x000f);
    byLByte = (uint8_t)(wPllDivRatio & 0x00ff);


    dev_I2C_Read(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_CP_TLLC_CTRL_1, byValue);
    byValue  = byValue & 0xf0;
    byValue  = byValue | byHByte;
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_CP_TLLC_CTRL_1,byValue);

    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_CP_TLLC_CTRL_2,byLByte);

}

void DriverChip9388A::dev_ARGB_SetVCORange(uint32_t byChannel,uint32_t dwPixelClock)
{
	uint8_t byValue = 0;

    if(dwPixelClock < 22000)
	{
		byValue = 0x90;
	}
	else if(dwPixelClock < 45000)
	{
		byValue = 0xb0;
	}
	else if(dwPixelClock < 90000)
	{
		byValue = 0xd0;
	}
	else
	{
		byValue = 0xf0;
	}

    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_CP_TLLC_CTRL_4,byValue);

}

void DriverChip9388A::dev_ARGB_SetFRLL(uint32_t byChannel,uint16_t wBL)
{
	uint8_t byValue = 0;
	uint8_t byHByte = 0;
	uint8_t byLByte = 0;
    uint16_t wTrueFRLL = 0;

    //TrueFRLL = Htotal*28.63636/PixelRate = BL/8;

    wTrueFRLL = wBL / 8;

    byHByte = (uint8_t)((wTrueFRLL >> 8) & 0x0007);
    byLByte = (uint8_t)(wTrueFRLL & 0x00ff);


    dev_I2C_Read(byChannel, I2C_ADDR_USER_MAP, AD9388_USER_FR_LL_1,byValue);
    byValue  = byValue & 0xf8;
    byValue  = byValue | byHByte;
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_FR_LL_1,byValue);

    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_FR_LL_2,byLByte);

}

void DriverChip9388A::dev_ARGB_SetFRLCountMax(uint32_t byChannel,uint16_t wLCountMax)
{
	uint8_t byValue = 0;
	uint8_t byHByte = 0;
	uint8_t byLByte = 0;


    byHByte = (uint8_t)((wLCountMax >> 4) & 0x00ff);
    byLByte = (uint8_t)((wLCountMax << 4) & 0x00f0);

    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_DPP_CP_90,byHByte);
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_DPP_CP_91,byLByte);

}

void DriverChip9388A::dev_ARGB_SetSavEav(uint32_t byChannel,uint16_t  wCPSAV,uint16_t  wCPEAV,uint16_t  wVBISAV,uint16_t wVBIEAV)
{
    uint8_t  byValue = 0;

    byValue = (uint8_t)((wCPSAV >> 4) & 0x00ff);
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_CP_START_SAV,byValue);

    byValue = (uint8_t)( ((wCPSAV << 4) & 0x00f0) | ((wCPEAV >> 8) & 0x000f) );
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_CP_START_SAV_EAV,byValue);

    byValue = (uint8_t)(wCPEAV & 0x00ff);
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_CP_START_EAV,byValue);

    byValue =  (uint8_t)((wVBISAV >> 4) & 0x00ff);
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_CP_START_VBI,byValue);

    byValue = (uint8_t)( ((wVBISAV << 4) & 0x00f0) | ((wVBIEAV >> 8) & 0x000f) );
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_CP_START_END_VBI,byValue);

    byValue = (uint8_t)(wVBIEAV & 0x00ff);
    dev_I2C_Write(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_CP_END_VBI,byValue);


}

void DriverChip9388A::getLineWidth(uint32_t byChannel,uint16_t &wLineWidth)
{
	uint8_t  byValue = 0;

	dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_REG_07,byValue);

	wLineWidth = byValue & 0x0f;
	wLineWidth = wLineWidth << 8;

	dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_LINE_WIDTH,byValue);

	wLineWidth = wLineWidth | byValue;
}

void DriverChip9388A::getTMDSFreq(uint32_t byChannel,uint8_t &byTMDSFreq)
{
	uint8_t  byValue = 0;

	dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_TMDSFREQ,byValue);

	byTMDSFreq = byValue;

}

void DriverChip9388A::getF0H(uint32_t byChannel,uint16_t &wF0H)
{

	uint8_t  byValue = 0;

	dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_FLD_0_HT_H,byValue);

	wF0H = byValue & 0x0f;
	wF0H = wF0H << 8;

	dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_FLD_0_HT_L,byValue);

	wF0H = wF0H | byValue;

}

void DriverChip9388A::getF1H(uint32_t byChannel,uint16_t &wF1H)
{
    uint8_t  byValue = 0;

    dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_REG_0B,byValue);

    wF1H = byValue & 0x0f;
    wF1H = wF1H << 8;

    dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_FLD_1_HT,byValue);

    wF1H = wF1H | byValue;


}

void DriverChip9388A::dev_DRGB_GetSignalPara(uint32_t byChannel,uint8_t &wTMDSFreq,uint16_t &wLineWidth,uint16_t &wF0H,uint16_t &wF1H)
{
	getTMDSFreq(byChannel,wTMDSFreq);
    getLineWidth(byChannel,wLineWidth);

    getF0H(byChannel,wF0H);
    getF1H(byChannel,wF1H);

}

void DriverChip9388A::dev_ARGB_DetectInput(uint32_t byChannel, uint8_t &bySignalState)
{
    uint8_t byValue = 0;

    dev_I2C_Read(byChannel,I2C_ADDR_USER_MAP,AD9388_USER_RB_STD_ID_1,byValue);

    byValue = byValue & 0x80;

    if(byValue == 0x80)
    {
    	bySignalState = 1;
    }
    else
    {
    	bySignalState = 0;
    }

}

void DriverChip9388A::dev_DRGB_DetectInput(uint32_t byChannel, uint8_t &bySignalState)
{
    uint8_t byValue1 = 0;
    uint8_t byValue2 = 0;
    dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_REG_04,byValue1);
    dev_I2C_Read(byChannel,I2C_ADDR_HDMI_MAP,AD9388_HDMI_REG_07,byValue2);
    if((byValue1 & 0x02) &&  (byValue2 & 0x10))
    {
    	bySignalState = 1;
    }
    else
    {
    	bySignalState = 0;
    }

}

void DriverChip9388A::dev_ARGB_SetPhase(uint32_t byChannel,uint8_t byPhase)
{
    uint8_t byValue = 0;

    dev_I2C_Read(byChannel, I2C_ADDR_USER_MAP,AD9388_USER_TLLC_PHS_ADJ,byValue);

    byValue = (byValue & 0xe0) | (byPhase & 0x1f);

    dev_I2C_Write(byChannel, I2C_ADDR_USER_MAP,AD9388_USER_TLLC_PHS_ADJ, byValue);

}

void DriverChip9388A::dev_ARGB_GetPhase(uint32_t byChannel,uint8_t &byPhase)
{
	uint8_t byValue = 0;

    dev_I2C_Read(byChannel, I2C_ADDR_USER_MAP,AD9388_USER_TLLC_PHS_ADJ,byValue);

    byPhase = (byValue & 0x1f);

}

void DriverChip9388A::dev_RGB_GetBrightness(uint32_t byChannels,uint8_t &byBrightness)
{
	dev_I2C_Read(byChannels,I2C_ADDR_USER_SUB_MAP_1,AD9388_SUB1_CP_BRIGHTNESS,byBrightness);

}

void DriverChip9388A::dev_RGB_SetBrightness(uint32_t byChannels,uint8_t byBrightness)
{
	dev_I2C_Write(byChannels,I2C_ADDR_USER_SUB_MAP_1,AD9388_SUB1_CP_BRIGHTNESS,byBrightness);

}

void DriverChip9388A::dev_RGB_GetContrast(uint32_t byChannels,uint8_t &byContrast)
{
	dev_I2C_Read(byChannels,I2C_ADDR_USER_SUB_MAP_1,AD9388_SUB1_CP_CONTRAST,byContrast);
}
void DriverChip9388A::dev_RGB_SetContrast(uint32_t byChannels,uint8_t byContrast)
{
	dev_I2C_Write(byChannels,I2C_ADDR_USER_SUB_MAP_1,AD9388_SUB1_CP_CONTRAST,byContrast);


}

void DriverChip9388A::dev_RGB_GetSaturation(uint32_t byChannels,uint8_t &bySaturation)
{
	dev_I2C_Read(byChannels,I2C_ADDR_USER_SUB_MAP_1,AD9388_SUB1_CP_SATURATION,bySaturation);


}

void DriverChip9388A::dev_RGB_SetSaturation(uint32_t byChannels,uint8_t bySaturation)
{

	dev_I2C_Write(byChannels,I2C_ADDR_USER_SUB_MAP_1,AD9388_SUB1_CP_SATURATION,bySaturation);

}

void DriverChip9388A::dev_RGB_GetColorPhase(uint32_t byChannels,uint8_t &byColorPhase)
{

	dev_I2C_Read(byChannels,I2C_ADDR_USER_SUB_MAP_1,AD9388_SUB1_CP_HUE,byColorPhase);

}

void DriverChip9388A::dev_RGB_SetColorPhase(uint32_t byChannels,uint8_t byColorPhase)
{
	dev_I2C_Write(byChannels,I2C_ADDR_USER_SUB_MAP_1,AD9388_SUB1_CP_HUE,byColorPhase);


}
