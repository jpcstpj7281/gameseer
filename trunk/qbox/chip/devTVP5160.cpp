/*
 * devTVP5160.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "devTVP5160.h"
#include "devTVP5160Addr.h"

using namespace chip;


DriverChip5160::DriverChip5160()
{

}

DriverChip5160::~DriverChip5160()
{

}

void DriverChip5160::dev_5160_SetColorScope(uint32_t byChannels,uint8_t byColorMode,uint8_t byColorValue)
{
	list<map<uint8_t,uint8_t> > value;
	uint8_t byRegData = 0;

	switch (byColorMode)
	{
		case COLORSCOPE_AUTO:
			byColorMode = (byColorMode << COLORSCOPE_MODEMOVE);
			byRegData = (byColorMode | byColorValue);
			break;

		case COLORSCOPE_ENABLED:
			byColorMode = byColorMode + 1;
			byColorMode = (byColorMode << COLORSCOPE_MODEMOVE);
			byRegData = (byColorMode | byColorValue);
			break;

		case COLORSCOPE_DISABLED:
			byColorMode = byColorMode + 1;
			byColorMode = (byColorMode << COLORSCOPE_MODEMOVE);
			byRegData = (byColorMode | byColorValue);
			break;

		default:
			//PFPrintMsg(CP_LOG_ERROR,"SetColorScope Error Channels = %d!\n",byChannels);
			return ;

	    }

	I2C_5160_Write(byChannels,CP_TVP5160_CHIP_COLOR_SCOPE_ADDR,byRegData);


}

void DriverChip5160::dev_5160_GetColorScope(uint32_t byChannels,uint8_t &byColorMode,uint8_t &byColorValue)
{
    uint8_t valueRegData = 0;
    uint8_t valueColorMode = 0;

    I2C_5160_Read(byChannels,CP_TVP5160_CHIP_COLOR_SCOPE_ADDR,valueRegData);

    byColorValue = (valueRegData & COLORSCOPE_VALUEMASK);

    valueColorMode = (valueRegData & COLORSCOPE_MODEMASK);
    valueColorMode = byColorMode >> COLORSCOPE_MODEMOVE;

    switch (valueColorMode)
    {
    	case 0:
    		byColorMode = COLORSCOPE_AUTO;
    		break;

    	case 2:
    		byColorMode = COLORSCOPE_ENABLED;
    		break;

    	case 3:
    		byColorMode = COLORSCOPE_DISABLED;
    		break;

    	default:

    		return ;
    }
}

/*读取图像的亮度函数*/
void DriverChip5160::dev_5160_GetBrightness(uint32_t byChannels,uint8_t &byBrightness)
{
	I2C_5160_Read(byChannels,CP_TVP5160_LUM_BRIGHTNESS_ADDR,byBrightness);
}

void DriverChip5160::dev_5160_SetBrightness(uint32_t byChannels,uint8_t byBrightness)
{
	I2C_5160_Write(byChannels,CP_TVP5160_LUM_BRIGHTNESS_ADDR,byBrightness);
}

/*调节图像的对比度函数*/
void DriverChip5160::dev_5160_SetContrast(uint32_t byChannels,uint8_t byContrast)
{
	I2C_5160_Write(byChannels,CP_TVP5160_LUM_CONTRAST_ADDR,byContrast);
}

void DriverChip5160::dev_5160_GetContrast(uint32_t byChannels,uint8_t &byContrast)
{
	I2C_5160_Read(byChannels,CP_TVP5160_LUM_CONTRAST_ADDR,byContrast);
}

/*调节图像的饱和度函数*/
void DriverChip5160::dev_5160_SetSaturation(uint32_t byChannels,uint8_t bySaturation)
{
	I2C_5160_Write(byChannels,CP_TVP5160_CHROMA_SATURATION_ADDR,bySaturation);
}

void DriverChip5160::dev_5160_GetSaturation(uint32_t byChannels,uint8_t &bySaturation)
{
	I2C_5160_Read(byChannels,CP_TVP5160_CHROMA_SATURATION_ADDR,bySaturation);

}


/*调节图像的锐度函数*/
void DriverChip5160::dev_5160_SetAcutance(uint32_t byChannels,uint8_t byAcutance)
{
	I2C_5160_Write(byChannels,CP_TVP5160_VIDEO_ACUTANCE_ADDR,byAcutance);
}

void DriverChip5160::dev_5160_GetAcutance(uint32_t byChannels,uint8_t &byAcutance)
{
	I2C_5160_Read(byChannels,CP_TVP5160_VIDEO_ACUTANCE_ADDR,byAcutance);

}

/*调节图像的颜色相位函数*/
void DriverChip5160::dev_5160_SetColorPhasic(uint32_t byChannels,uint8_t byColorPhasic)
{
	I2C_5160_Write(byChannels,CP_TVP5160_CHROMA_HUE_ADDR,byColorPhasic);
}

void DriverChip5160::dev_5160_GetColorPhasic(uint32_t byChannels,uint8_t &byColorPhasic)
{
	I2C_5160_Write(byChannels,CP_TVP5160_CHROMA_HUE_ADDR,byColorPhasic);
}

/*调节视频信号模式函数*/
void DriverChip5160::dev_5160_SetSignalMode(uint32_t byChannels,uint8_t bySignalMode)
{
	I2C_5160_Write(byChannels,CP_TVP5160_VIDEO_STANDARD_SEL_ADDR,bySignalMode);
}

void DriverChip5160::dev_5160_GetSignalMode(uint32_t byChannels,uint8_t &bySignalMode)
{
	I2C_5160_Read(byChannels,CP_TVP5160_CHROMA_HUE_ADDR,bySignalMode);
}

/*调节视频自动增益模式函数*/
void DriverChip5160::dev_5160_SetAutoGainFlg(uint32_t byChannels,uint8_t byAutoGainFlg)
{
    uint8_t byValue = 0;

    if(byAutoGainFlg == GAIN_AUTO)
    {
        byValue = GAIN_AUTO_VALUE;
    }
    else
    {
        byValue = GAIN_MANUAL_VALUE;
    }

    I2C_5160_Write(byChannels,CP_TVP5160_AUTO_MANUAL_GAIN_ADDR,byValue);

}

void DriverChip5160::dev_5160_GetAutoGainFlg(uint32_t byChannels,uint8_t &byAutoGainFlg)
{
	I2C_5160_Write(byChannels,CP_TVP5160_AUTO_MANUAL_GAIN_ADDR,byAutoGainFlg);
}

void DriverChip5160::dev_5160_SetManualGainValue(uint32_t byChannels,uint8_t byManualGainValue)
{

    uint8_t byCoarseGain = 0;
    uint8_t byFineGain   = 0;


    byCoarseGain = byManualGainValue & HIGH4_MASK;
    byFineGain   = byManualGainValue & LOW4_MASK;



/*设置CVBS粗精度增益寄存器的值为byManualGain的高4位*/
    I2C_5160_Write(byChannels,CP_TVP5160_CVBS_COARSE_GAIN_ADDR,byCoarseGain);
//        /*设置CVBS细精度增益寄存器的值为byManualGain的低4位*/
    I2C_5160_Write(byChannels,CP_TVP5160_SVIDEO_CHROMA_FINE_GAIN_ADDR1,byFineGain);
    I2C_5160_Write(byChannels,CP_TVP5160_LUMA_CVBS_FINE_GAIN_ADDR1,byFineGain);


}

void DriverChip5160::dev_5160_GetManualGainValue(uint32_t byChannels,uint8_t &byManualGainValue)
{

	uint8_t byInputMode = 0;

	uint8_t byCoarseGain = 0;
	uint8_t byFineGain   = 0;

        /*设置CVBS粗精度增益寄存器的值为byManualGain的高4位*/
	I2C_5160_Read(byChannels,CP_TVP5160_CVBS_COARSE_GAIN_ADDR,byCoarseGain);
        /*设置CVBS细精度增益寄存器的值为byManualGain的低4位*/
	I2C_5160_Read(byChannels,CP_TVP5160_SVIDEO_CHROMA_FINE_GAIN_ADDR1,byFineGain);

    byCoarseGain = byCoarseGain & HIGH4_MASK;
    byFineGain = byFineGain & LOW4_MASK;

    byManualGainValue = byCoarseGain | byFineGain;
}

void DriverChip5160::dev_5160_InitTVP5160(uint32_t byChannels)
{

	I2C_5160_Write(byChannels,0xea,0xb0);
	I2C_5160_Write(byChannels,0xe9,0x00);
	I2C_5160_Write(byChannels,0xe8,0x60);
	I2C_5160_Write(byChannels,0xe1,0x03);
	I2C_5160_Write(byChannels,0xe1,0xb0);
	I2C_5160_Write(byChannels,0xe1,0xb0);
	I2C_5160_Write(byChannels,0xe1,0x01);

	I2C_5160_Write(byChannels,0xea,0xb0);
	I2C_5160_Write(byChannels,0xe9,0x00);
	I2C_5160_Write(byChannels,0xe8,0x60);
	I2C_5160_Write(byChannels,0xe1,0x02);
	I2C_5160_Write(byChannels,0xe1,0xb0);
	I2C_5160_Write(byChannels,0xe1,0xb0);
	I2C_5160_Write(byChannels,0xe1,0x01);

	I2C_5160_Write(byChannels,0xea,0x80);
	I2C_5160_Write(byChannels,0xe9,0x0A);
	I2C_5160_Write(byChannels,0xe8,0x68);
	I2C_5160_Write(byChannels,0xe1,0x08);


	I2C_5160_Write(byChannels,0xe9,0x0A);
	I2C_5160_Write(byChannels,0xe8,0x10);
	I2C_5160_Write(byChannels,0xe1,0x10);


	I2C_5160_Write(byChannels,0xe9,0x00);
	I2C_5160_Write(byChannels,0xe8,0x82);
	I2C_5160_Write(byChannels,0xe0,0x10);

	I2C_5160_Write(byChannels,0xe9,0x0A);
	I2C_5160_Write(byChannels,0xe8,0x11);
	I2C_5160_Write(byChannels,0xe0,0x03);

	I2C_5160_Write(byChannels,0xe9,0x0A);
	I2C_5160_Write(byChannels,0xe8,0x2A);
	I2C_5160_Write(byChannels,0xe0,0x01);

	I2C_5160_Write(byChannels,0xe9,0x0A);
	I2C_5160_Write(byChannels,0xe8,0x9c);
	I2C_5160_Write(byChannels,0xe0,0x10);

	I2C_5160_Write(byChannels,0xe9,0x0A);
	I2C_5160_Write(byChannels,0xe8,0x3c);
	I2C_5160_Write(byChannels,0xe0,0x03);

	I2C_5160_Write(byChannels,0xea,0x08);
	I2C_5160_Write(byChannels,0xe9,0x5c);
	I2C_5160_Write(byChannels,0xe8,0x03);
	I2C_5160_Write(byChannels,0xe1,0x00);
	I2C_5160_Write(byChannels,0xe1,0x00);

	I2C_5160_Write(byChannels,0xe8,0x80);
	I2C_5160_Write(byChannels,0xe1,0x08);
	I2C_5160_Write(byChannels,0xe1,0x08);

	I2C_5160_Write(byChannels,0x08,0x00);
	I2C_5160_Write(byChannels,0x0e,0x0c);

	I2C_5160_Write(byChannels,0x00,0x00);
	I2C_5160_Write(byChannels,0x02,0x00);
	I2C_5160_Write(byChannels,0x03,0x00);
	I2C_5160_Write(byChannels,0x04,0x3F);
	I2C_5160_Write(byChannels,0x06,0x40);
	I2C_5160_Write(byChannels,0x31,0x05);

	I2C_5160_Write(byChannels,0x0D,0x80);
	I2C_5160_Write(byChannels,0x59,0x07);

	I2C_5160_Write(byChannels,0x33,0x00);
	I2C_5160_Write(byChannels,0x34,0x11);
	I2C_5160_Write(byChannels,0x35,0xeA);
	I2C_5160_Write(byChannels,0x36,0xAF);
	I2C_5160_Write(byChannels,0x75,0x1A);

	// TVP5160 Direct I2C Registers
//	WR_REG,VID_DEC,0x01,0x00,0x00 // Input Selection - CVBS CH1
//	WR_REG,VID_DEC,0x01,0x02,0x00 // Auto Switch
//	WR_REG,VID_DEC,0x01,0x03,0x00 // Power Down ?Normal Operation
//	WR_REG,VID_DEC,0x01,0x04,0x3F // Auto Switch Mask
//	WR_REG,VID_DEC,0x01,0x06,0x40 // Pedestal off
//	WR_REG,VID_DEC,0x01,0x31,0x05 // GLCO in RTC mode
//
//	WR_REG,VID_DEC,0x01,0x0D,0x80 // Chrominance Processing Ctrl 1 Reg ?3DYC Only Enabled
//	WR_REG,VID_DEC,0x01,0x59,0x07 // Enabled SDRAM and set SDRAM size
//
//	WR_REG,VID_DEC,0x01,0x33,0x00 // Extended Coding Range, ITU-656
//	WR_REG,VID_DEC,0x01,0x34,0x11 // Outputs Enabled
//	WR_REG,VID_DEC,0x01,0x35,0xeA // GLCO and FID Enabled
//	WR_REG,VID_DEC,0x01,0x36,0xAF // HS and VS Enabled
//	WR_REG,VID_DEC,0x01,0x75,0x1A // F & V Bit Control

//	I2C_5160_Write(byChannels,0xee,0x01);
//
//
//	I2C_5160_Write(byChannels,0xea,0xb0);
//	I2C_5160_Write(byChannels,0xe9,0x00);
//	I2C_5160_Write(byChannels,0xe8,0x63);
//
//	I2C_5160_Write(byChannels,0xe0,0x01);
//	I2C_5160_Write(byChannels,0xee,0x00);
//
//
//	I2C_5160_Write(byChannels,0x4,0xff);
//	I2C_5160_Write(byChannels,0x6,0x40);
//	I2C_5160_Write(byChannels,0xd,0x84);
//
//	I2C_5160_Write(byChannels,0x30,0x0f);
//
//	I2C_5160_Write(byChannels,0x33,0x01);
//	I2C_5160_Write(byChannels,0x34,0x11);
//	I2C_5160_Write(byChannels,0x35,0x2a);
//	I2C_5160_Write(byChannels,0x36,0xaf);
//
//	I2C_5160_Write(byChannels,0x59,0x7);
//
//
//
//	I2C_5160_Write(byChannels,0x74,0xbf);
//	I2C_5160_Write(byChannels,0x75,0x1a);
//	I2C_5160_Write(byChannels,0x7f,0x1);
//
//
//
//	//
////	//设置没有信号时输出蓝屏
//	I2C_5160_Write(byChannels,0x5f,0x23);
//	I2C_5160_Write(byChannels,0x60,0xd4);
//	I2C_5160_Write(byChannels,0x61,0x72);




//
//	value.push_back(bank1);
//
//// 初始化片选寄存器 SMC_CSR4
////   (*(volatile DWORD *)(0xffffff80)) = 0x21003284;
//
//	dev_5160_WriteMult(byChannels,value);


}

void DriverChip5160::dev_5160_DetectInputSignal(uint32_t byChannels,uint8_t  &byInputState)
{
    uint8_t byRtn = 0;

    I2C_5160_Read(byChannels,CP_TVP5160_STATUS2_ADDR,byRtn);

    byRtn = byRtn & 0x80;
    if(byRtn == 0x80 )
    {
    	byInputState = 1;
    }
    else
    {
    	byInputState = 0;
    }

}

void DriverChip5160::dev_5160_GetVsFreq(uint32_t byChannel,uint8_t &byVsFreq)
{
    uint8_t byData = 0;

    I2C_5160_Read(byChannel,CP_TVP5160_STATUS2_ADDR,byData);

    byData = (FREQ_MASK & byData);

    if (byData == 0x0)
    {
    	byVsFreq = FIELD_60_HZ;
    }

    if (byData == FREQ_MASK)
    {
    	byVsFreq = FIELD_50_HZ;
    }
}

void DriverChip5160::dev_5160_GetInputType(uint32_t byChannel,uint8_t &byInputType)
{
	I2C_5160_Read(byChannel,CP_TVP5160_INPUT_SELECT_ADDR,byInputType);
}

void DriverChip5160::dev_5160_SetInputType(uint32_t byChannel,uint8_t byInputType)
{
    I2C_5160_Write(byChannel,CP_TVP5160_INPUT_SELECT_ADDR, byInputType);
}






