/*
 * devTVP5160.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "devTVP5160.h"
#include "CPTVP5160Addr.h"

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



//			CHIP_WriteTVP5160(byChannels, CP_TVP5160_CHIP_COLOR_SCOPE_ADDR, byRegData);
			break;

		case COLORSCOPE_ENABLED:
			byColorMode = byColorMode + 1;
			byColorMode = (byColorMode << COLORSCOPE_MODEMOVE);
			byRegData = (byColorMode | byColorValue);
//			CHIP_WriteTVP5160(byChannels, CP_TVP5160_CHIP_COLOR_SCOPE_ADDR, byRegData);

			break;

		case COLORSCOPE_DISABLED:
			byColorMode = byColorMode + 1;
			byColorMode = (byColorMode << COLORSCOPE_MODEMOVE);
			byRegData = (byColorMode | byColorValue);
//			CHIP_WriteTVP5160(byChannels, CP_TVP5160_CHIP_COLOR_SCOPE_ADDR, byRegData);
			break;

		default:
			//PFPrintMsg(CP_LOG_ERROR,"SetColorScope Error Channels = %d!\n",byChannels);
			return ;

	    }

	map<uint8_t,uint8_t> bank0;
	bank0[CP_TVP5160_CHIP_COLOR_SCOPE_ADDR] = byRegData;
	value.push_back(bank0);


}

void DriverChip5160::dev_5160_GetColorScope(uint32_t byChannels,uint8_t &byColorMode,uint8_t &byColorValue)
{
    uint8_t valueRegData = 0;
    uint8_t valueColorMode = 0;

//    CHIP_ReadTVP5160(byChannels, CP_TVP5160_CHIP_COLOR_SCOPE_ADDR,&byRegData);

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
//    CHIP_ReadTVP5160(byChannels, CP_TVP5160_LUM_BRIGHTNESS_ADDR,byBrightness);

}

void DriverChip5160::dev_5160_SetBrightness(uint32_t byChannels,uint8_t byBrightness)
{
//	CHIP_WriteTVP5160(byChannels, CP_TVP5160_LUM_BRIGHTNESS_ADDR, byBrightness);
}

/*调节图像的对比度函数*/
void DriverChip5160::dev_5160_SetContrast(uint32_t byChannels,uint8_t byContrast)
{
//	CHIP_WriteTVP5160(byChannels, CP_TVP5160_LUM_CONTRAST_ADDR, byContrast);
}

void DriverChip5160::dev_5160_GetContrast(uint32_t byChannels,uint8_t &byContrast)
{
//	CHIP_ReadTVP5160(byChannels, CP_TVP5160_LUM_CONTRAST_ADDR,byContrast);
}

/*调节图像的饱和度函数*/
void DriverChip5160::dev_5160_SetSaturation(uint32_t byChannels,uint8_t bySaturation)
{
//	CHIP_WriteTVP5160(byChannels, CP_TVP5160_CHROMA_SATURATION_ADDR, bySaturation);
}

void DriverChip5160::dev_5160_GetSaturation(uint32_t byChannels,uint8_t &bySaturation)
{
//	CHIP_ReadTVP5160(byChannels, CP_TVP5160_CHROMA_SATURATION_ADDR,bySaturation);
}


/*调节图像的锐度函数*/
void DriverChip5160::dev_5160_SetAcutance(uint32_t byChannels,uint8_t byAcutance)
{
//	CHIP_WriteTVP5160(byChannels, CP_TVP5160_VIDEO_ACUTANCE_ADDR, byAcutance);
}

void DriverChip5160::dev_5160_GetAcutance(uint32_t byChannels,uint8_t &byAcutance)
{
//	CHIP_ReadTVP5160(byChannels, CP_TVP5160_VIDEO_ACUTANCE_ADDR,byAcutance);
}

/*调节图像的颜色相位函数*/
void DriverChip5160::dev_5160_SetColorPhasic(uint32_t byChannels,uint8_t byColorPhasic)
{
//	CHIP_WriteTVP5160(byChannels, CP_TVP5160_CHROMA_HUE_ADDR, byColorPhasic);
}

void DriverChip5160::dev_5160_GetColorPhasic(uint32_t byChannels,uint8_t &byColorPhasic)
{
//	CHIP_ReadTVP5160(byChannels, CP_TVP5160_CHROMA_HUE_ADDR,pbyColorPhasic);
}

/*调节视频信号模式函数*/
void DriverChip5160::dev_5160_SetSignalMode(uint32_t byChannels,uint8_t bySignalMode)
{
//	CHIP_WriteTVP5160(byChannels, CP_TVP5160_VIDEO_STANDARD_SEL_ADDR, bySignalMode);
}

void DriverChip5160::dev_5160_GetSignalMode(uint32_t byChannels,uint8_t &bySignalMode)
{
//	  CHIP_ReadTVP5160(byChannels, CP_TVP5160_VIDEO_STANDARD_STATUS_ADDR,pbySignalMode);
//	  *pbySignalMode = *pbySignalMode & MODEL_MASK;
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


//    CHIP_WriteTVP5160(byChannels, CP_TVP5160_AUTO_MANUAL_GAIN_ADDR, byValue);

}

void DriverChip5160::dev_5160_GetAutoGainFlg(uint32_t byChannels,uint8_t &byAutoGainFlg)
{
    uint8_t byValue = 0;
//  CHIP_ReadTVP5160(byChannels, CP_TVP5160_AUTO_MANUAL_GAIN_ADDR,&byValue);

	//芯片与协议正好相反
    if((byValue & GAIN_AUTO_VALUE) == GAIN_AUTO_VALUE)
    {
    	byAutoGainFlg = GAIN_AUTO;
    }
    else
    {
    	byAutoGainFlg = GAIN_MANUAL;
    }

}

void DriverChip5160::dev_5160_SetManualGainValue(uint32_t byChannels,uint8_t byManualGainValue)
{

    uint8_t byCoarseGain = 0;
    uint8_t byFineGain   = 0;


    byCoarseGain = byManualGainValue & HIGH4_MASK;
    byFineGain   = byManualGainValue & LOW4_MASK;



/*设置CVBS粗精度增益寄存器的值为byManualGain的高4位*/
//        CHIP_WriteTVP5160(byChannels, CP_TVP5160_CVBS_COARSE_GAIN_ADDR, byCoarseGain);
//        /*设置CVBS细精度增益寄存器的值为byManualGain的低4位*/
//        CHIP_WriteTVP5160(byChannels, CP_TVP5160_SVIDEO_CHROMA_FINE_GAIN_ADDR1, byFineGain);
//        CHIP_WriteTVP5160(byChannels, CP_TVP5160_LUMA_CVBS_FINE_GAIN_ADDR1, byFineGain);

}

void DriverChip5160::dev_5160_GetManualGainValue(uint32_t byChannels,uint8_t &byManualGainValue)
{

	uint8_t byInputMode = 0;

	uint8_t byCoarseGain = 0;
	uint8_t byFineGain   = 0;

        /*设置CVBS粗精度增益寄存器的值为byManualGain的高4位*/
//        CHIP_ReadTVP5160(byChannels, CP_TVP5160_CVBS_COARSE_GAIN_ADDR,&byCoarseGain);
        /*设置CVBS细精度增益寄存器的值为byManualGain的低4位*/
//        CHIP_ReadTVP5160(byChannels, CP_TVP5160_SVIDEO_CHROMA_FINE_GAIN_ADDR1,&byFineGain);

    byCoarseGain = byCoarseGain & HIGH4_MASK;
    byFineGain = byFineGain & LOW4_MASK;

    byManualGainValue = byCoarseGain | byFineGain;
}

void DriverChip5160::dev_5160_InitTVP5160(uint32_t byChannels)
{
	list<map<uint8_t,uint8_t> > value;

	map<uint8_t,uint8_t> bank0;
	bank0[0xee] = 0x01;
	bank0[0xea] = 0xb0;
	bank0[0xe9] = 0x00;
	bank0[0xe8] = 0x63;
	bank0[0xe0] = 0x01;

	value.push_back(bank0);

	map<uint8_t,uint8_t> bank1;
	bank1[0xee] = 0x00;

	bank1[0x4] = 0xff;
	bank1[0x6] = 0x40;
	bank1[0xd] = 0x84;
	bank1[0x30] = 0x0f;
	bank1[0x59] = 0x7;
	bank1[0x74] = 0xbf;
	bank1[0x75] = 0x1a;
	bank1[0x7f] = 0x1;
	bank1[0x33] = 0x01;
	bank1[0x34] = 0x11;
	bank1[0x35] = 0x2a;
	bank1[0x36] = 0xaf;

	//设置没有信号时输出蓝屏
	bank1[0x5f] = 0x23;
	bank1[0x60] = 0xd4;
	bank1[0x61] = 0x72;

	value.push_back(bank1);

// 初始化片选寄存器 SMC_CSR4
//   (*(volatile DWORD *)(0xffffff80)) = 0x21003284;



}

void DriverChip5160::dev_5160_DetectInputSignal(uint32_t byChannels,uint8_t  &byInputState)
{
    uint8_t byRtn = 0;

//    CHIP_ReadTVP5160(byChannels, CP_TVP5160_STATUS2_ADDR,&byRtn);

	//byRtn1 = byRtn1 & 0x08;
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

//  CHIP_ReadTVP5160(byChannel, CP_TVP5160_STATUS1_ADDR,&byData);

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
	uint8_t byRtnType = 0;

//	CHIP_ReadTVP5160(byChannel, CP_TVP5160_INPUT_SELECT_ADDR,&byRtnType);

	if(byRtnType == CP_TVP5160_INPUT_SELECT_CVBS)
	{
//		byInputType = CP_VIEWTYPE_CVBS;
	}

}

void DriverChip5160::dev_5160_SetInputType(uint32_t byChannel,uint8_t byInputType)
{
    uint8_t byTypeValue = 0;

    byTypeValue = CP_TVP5160_INPUT_SELECT_CVBS;

//    CHIP_WriteTVP5160(byChannel, CP_TVP5160_INPUT_SELECT_ADDR, byTypeValue);
//

}






