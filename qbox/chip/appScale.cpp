/*
 * appC753.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "appScale.h"
#include <math.h>



using namespace chip;
using namespace chipApp;




AppScale* AppScale::m_instance=0;
AppScale::AppScale()
:m_horFp(0)
,m_verFp(0)
{

	TimingIndexTableT timingIndex;
	timingIndex.wHorResolution=1024;
	timingIndex.wVerResolution = 768;
	m_asTimingIndexTable.push_back(timingIndex);


//	m_asTimingIndexTable[1].wHorResolution = 1400;
//	m_asTimingIndexTable[1].wVerResolution = 1050;
//
//	m_asTimingIndexTable[2].wHorResolution = 1600;
//	m_asTimingIndexTable[2].wVerResolution = 1200;
//
//	m_asTimingIndexTable[3].wHorResolution = 1920;
//	m_asTimingIndexTable[3].wVerResolution = 1080;
//
//	m_asTimingIndexTable[4].wHorResolution = 1366;
//	m_asTimingIndexTable[4].wVerResolution = 768;
//
//	m_asTimingIndexTable[5].wHorResolution = 1920;
//	m_asTimingIndexTable[5].wVerResolution = 1200;


	TimingT timing;

	timing.wHorResolution = 1024;
	timing.wVerResolution = 768;
	timing.iFrameRate = 60;
	timing.iClock = 65;
	timing.wHorTotal = 1344;
	timing.wHorSync = 136;
	timing.wHorStart = 296;
	timing.wVerTotal = 806;
	timing.wVerSync = 6;
	timing.wVerStart = 35;
	timing.sswC753OffsetX = -133;
	timing.sswC753OffsetY = -1;
	m_asSignalTiming.push_back(timing);

//	m_asSignalTiming[1].wHorResolution = 1366;
//	m_asSignalTiming[1].wVerResolution = 768;
//	m_asSignalTiming[1].iFrameRate = 60;
//	m_asSignalTiming[1].iClock = 85;
//	m_asSignalTiming[1].wHorTotal = 1792;
//	m_asSignalTiming[1].wHorSync = 112;
//	m_asSignalTiming[1].wHorStart = 368;
//	m_asSignalTiming[1].wVerTotal = 795;
//	m_asSignalTiming[1].wVerSync = 6;
//	m_asSignalTiming[1].wVerStart = 24;
//	m_asSignalTiming[1].sswC753OffsetX = -134;
//	m_asSignalTiming[1].sswC753OffsetY = -1;


	 /* ˮƽ   ��ֱ   ֡�� Ƶ��  ˮƽ���� �͵�ƽ ƫ�� ��ֱ���� �͵�ƽ ƫ��  ����ֵ ����ֵ*/
//	    {1024,  768,   60,  65,   1344,    136,  296,  806,     6,     35,  -133,   -1},
//	    {1366,  768,   60,  85,   1792,    112,  368,  795,     6,     24,  -134,   -1},
//	    {1366,  768,   60,  71,   1792,    112,  368,  795,     6,     24,  -134,   -1},
//	    {1400,  1050,  60,  108,  1688,    112,  240,  1066,    3,     15,  -135,   -1},
//	    {1400,  1050,  60,  121,  1864,    144,  376,  1089,    4,     36,  -135,   -1},
//	    {1600,  1200,  60,  162,  2160,    192,  496,  1250,    3,     49,  -135,   -1},
//	    {1920,  1080,  60,  148,  2200,     44,  192,  1125,    5,     41,  -135,   -1},
//	    {1920,  1200,  60,  154,  2080,     32,  112,  1235,    6,     32,  1941,   -2},



//	initTimingIndexTable();
    InputInfo info;
    info.hW = 702;
    info.Vw = 480;
    info.hStar = 137;
    info.vStar = 45;
    m_InputInfo[TYPE_INPUT_SIZE_702_480] = info;

    info.hW = 1024;
    info.Vw = 768;
    info.hStar = 303;
    info.vStar = 36;
    m_InputInfo[TYPE_INPUT_SIZE_1024_768] = info;

}

AppScale::~AppScale()
{

}

void AppScale::chipTest()
{
    uint8_t val1, val2;
    uint8_t regAddr;
    uint32_t memAddr;
    int i;

    printf("chip Test Begin\n");
    /*测试寄存器的读写*/
    val1 = 0x0b;
    C753SetBankRegister(val1);
    C753GetBankRegister(val2);
    if(val1 != val2)
    {
        printf("can not read base register value[val_in=0x%02x val_out=0x%02x]\n", val1, val2);
        return ;
    }

    for(regAddr = 0x08, i = 0x08; i < 0x48; i++, regAddr++)
    {
        val1 = regAddr;
        SPI_Write(TYPE_CHIP_C753, regAddr, val1);
    }

    for(regAddr = 0x08, i = 0x08; i < 0x48; i++, regAddr++)
    {
        val1 = regAddr;
        SPI_Read(TYPE_CHIP_C753, regAddr,val2);
        if(val2 != val1)
        {
            //SPCMsgErr("can not read bank register value[val1=0x%02x val2=0x%02x addr=0x%02x]\n", val1, val2, regAddr, 0);
        	printf("can not read bank register value[val_in=0x%02x val_out=0x%02x addr=0x%02x]\n", val1, val2, regAddr);
            return ;
        }
    }
    /*软件复位*/
    C753Reset(0x01);
    C753SetDDRControl(0x80);
    /*C753内存控制器初始化*/
    C753SetMemoryControl(0x28);
    /*至少延时200us*/

    for(i = 0; i < 40000; i++);
    C753SetMemoryControl(0x29);
    /*至少延时200us*/
    for(i = 0; i < 80000; i++);

    /*配置内存控制器寄存器*/
    C753SetDLLControl0(0xaa);
    C753SetDLLControl1(0xaa);
    C753SetDLLControl2(0xdd);
    C753SetDLLControl3(0xdd);
    C753SetDLLControl4(0xdd);
    C753SetDLLControl5(0xdd);
    C753SetDLLControl6(0x00);
    C753SetDLLControl7(0x00);
    C753SetDLLControl8(0x02);

    /*测试内存的读写*/
    val1 = 0x00;
    memAddr = 0x10000;
    C753SetCPUWriteAddress(memAddr);
    for(i = 0; i < 256; i++)
    {
        /*C753SetCPUWriteAddress(memAddr);*/
        C753SetCPUData(val1);
        val1++;
    }
    C753SetCPUData(0x00);
    val1 = 0x00;
    memAddr = 0x10000 - 1;
    C753SetCPUReadAddress(memAddr);
    C753GetCPUData(val2);
    for(i = 0; i < 256; i++)
    {
        /*C753SetCPUReadAddress(memAddr);*/
        C753GetCPUData(val2);
        if(val2 != val1)
        {
        	printf("can not read memory[val_in=0x%02x val_out=0x%02x index=%d]\n", val1, val2, i);
            //return ;
        }
        val1++;
    }

    return ;
}

void AppScale::initHardware()
{
	initChipDDR();
	initCLK();
}

void AppScale::initChannel(uint32_t iChID, ScaleChInfoT *pScalCh)
{

    /*重新设置窗口大小时窗口已经打开通道*/
    /*
    if(pScalCh->iChStatus != -1)
        return -1;
    */
    pScalCh->wOutputStartX += getHorizontalCompensation(m_asScaleConfig.wHorResolution, m_asScaleConfig.wVerResolution, m_asScaleConfig.byStandardType);
    pScalCh->wOutputStartY += getVerticalCompensation(m_asScaleConfig.wHorResolution, m_asScaleConfig.wVerResolution, m_asScaleConfig.byStandardType);
    memcpy(&m_asScaleChInfo[iChID], pScalCh, sizeof(ScaleChInfoT));

}

void AppScale::initTimingIndexTable(void)
{
    int i;

    printf("initTimingIndexTable\n");

    for(vector<TimingIndexTableT>::iterator it=m_asTimingIndexTable.begin();it!=m_asTimingIndexTable.end();it++)
    {
        int j;
        int start, end;
        int found = 0;
        for(vector<TimingT>::iterator itTiming=m_asSignalTiming.begin();itTiming!=m_asSignalTiming.end();it++)
        {
            if((m_asTimingIndexTable[i].wHorResolution == m_asSignalTiming[j].wHorResolution) &&
               (m_asTimingIndexTable[i].wVerResolution == m_asSignalTiming[j].wVerResolution))
            {
                if(!found)
                {
                    found = 1;
                    start = j;
                }
            }
            else if(found)
            {
                end = j;
                break;
            }
        }

        if(found)
        {
        	m_asTimingIndexTable[i].wStartIndex = start;
        	m_asTimingIndexTable[i].wCount = end - start;
        }
        else
        {
        	m_asTimingIndexTable[i].wStartIndex = 0;
        	m_asTimingIndexTable[i].wCount = 0;
        }
    }
}


uint16_t AppScale::getHorizontalTotal(uint16_t wHorResolution, uint16_t wVerResolution, uint16_t byStandardType)
{
    int i;

    for(vector<TimingIndexTableT>::iterator it=m_asTimingIndexTable.begin();it!=m_asTimingIndexTable.end();it++)
    {
        if((m_asTimingIndexTable[i].wHorResolution == wHorResolution) &&
           (m_asTimingIndexTable[i].wVerResolution == wVerResolution))
        {
            uint16_t offset;

            if(byStandardType < m_asTimingIndexTable[i].wCount)
            {
                offset = m_asTimingIndexTable[i].wStartIndex + byStandardType;
            }
            else
            {
                offset = m_asTimingIndexTable[i].wStartIndex;
            }

            return m_asSignalTiming[offset].wHorTotal;
        }
    }

    return 0;
}

uint16_t AppScale::getHorizontalStart(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
{
    int i;

    for(vector<TimingIndexTableT>::iterator it=m_asTimingIndexTable.begin();it!=m_asTimingIndexTable.end();it++)
    {
        if((m_asTimingIndexTable[i].wHorResolution == wHorResolution) &&
           (m_asTimingIndexTable[i].wVerResolution == wVerResolution))
        {
            int offset;

            if(byStandardType < m_asTimingIndexTable[i].wCount)
            {
                offset = m_asTimingIndexTable[i].wStartIndex + byStandardType;
            }
            else
            {
                offset = m_asTimingIndexTable[i].wStartIndex;
            }

            return m_asSignalTiming[offset].wHorStart;
        }
    }

    return 0;
}

int16_t AppScale::getHorizontalCompensation(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
{
    int i;

    for(vector<TimingIndexTableT>::iterator it=m_asTimingIndexTable.begin();it!=m_asTimingIndexTable.end();it++)
    {
        if((m_asTimingIndexTable[i].wHorResolution == wHorResolution) &&
           (m_asTimingIndexTable[i].wVerResolution == wVerResolution))
        {
            int offset;

            if(byStandardType < m_asTimingIndexTable[i].wCount)
            {
                offset = m_asTimingIndexTable[i].wStartIndex + byStandardType;
            }
            else
            {
                offset = m_asTimingIndexTable[i].wStartIndex;
            }

            return m_asSignalTiming[offset].sswC753OffsetX;
        }
    }

    return 0;
}


uint16_t AppScale::getVerticalTotal(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
{
    int i;

    for(vector<TimingIndexTableT>::iterator it=m_asTimingIndexTable.begin();it!=m_asTimingIndexTable.end();it++)
    {
        if((m_asTimingIndexTable[i].wHorResolution == wHorResolution) &&
           (m_asTimingIndexTable[i].wVerResolution == wVerResolution))
        {
            int offset;

            if(byStandardType < m_asTimingIndexTable[i].wCount)
            {
                offset = m_asTimingIndexTable[i].wStartIndex + byStandardType;
            }
            else
            {
                offset = m_asTimingIndexTable[i].wStartIndex;
            }

            return m_asSignalTiming[offset].wVerTotal;
        }
    }

    return 0;
}


uint16_t  AppScale::getVerticalStart(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
{
    int i;

    for(vector<TimingIndexTableT>::iterator it=m_asTimingIndexTable.begin();it!=m_asTimingIndexTable.end();it++)
    {
        if((m_asTimingIndexTable[i].wHorResolution == wHorResolution) &&
           (m_asTimingIndexTable[i].wVerResolution == wVerResolution))
        {
            int offset;

            if(byStandardType < m_asTimingIndexTable[i].wCount)
            {
                offset = m_asTimingIndexTable[i].wStartIndex + byStandardType;
            }
            else
            {
                offset = m_asTimingIndexTable[i].wStartIndex;
            }

            return m_asSignalTiming[offset].wVerStart;
        }
    }

    return 0;
}



int16_t AppScale::getVerticalCompensation(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
{
    int i;

    for(vector<TimingIndexTableT>::iterator it=m_asTimingIndexTable.begin();it!=m_asTimingIndexTable.end();it++)
     {
        if((m_asTimingIndexTable[i].wHorResolution == wHorResolution) &&
           (m_asTimingIndexTable[i].wVerResolution == wVerResolution))
        {
            int offset;

            if(byStandardType < m_asTimingIndexTable[i].wCount)
            {
                offset = m_asTimingIndexTable[i].wStartIndex + byStandardType;
            }
            else
            {
                offset = m_asTimingIndexTable[i].wStartIndex;
            }

            return m_asSignalTiming[offset].sswC753OffsetY;
        }
    }

    return 0;
}


void AppScale::showWnd(uint32_t iChID)
{
//	printf("showWnd !\n");
	/*显示该通道*/
    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
        C753SetMainControl(iChID,0x03);

    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
    	C753SetMainControl(iChID,0x07);

    }

    debug_msg("showWnd iChid=%d\n",iChID);

}

void AppScale::hideWnd(uint32_t iChID)
{
    /*���ظ�ͨ��*/
    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
       C753SetMainControl(iChID,0x02);
    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
        C753SetMainControl(iChID,0x06);
    }
}


void AppScale::openChannel(uint32_t iChID)
{

    /*
    *  配置输入部分寄存器
    */
//    if(s_asScaleChInfo[iChID].iImageType == SCAL_IMAGE_IPFIELD)
//    {
//        /*IFLD[0]=PIFLD IFLD[1] toggles every 2 fields*/
//        /*水平同步信号低电平有效*/
//        /*垂直同步信号低电平有效*/
//        C753SetInputPortSyncControl(num, 0x06);
//    }
//    else
//    {
        /*IFLD 0到3循环*/
        /*水平同步信号低电平有效*/
        /*垂直同步信号低电平有效*/
    C753SetInputPortSyncControl(iChID, 0x01);
//    }
    C753SetInputImageControl(iChID, 0x00);
    /*设置输入图像区域*/
    C753SetInputPortACTHorizontalStart(iChID, (uint16_t)(m_asScaleChInfo[iChID].wInputStartX + m_asScaleChInfo[iChID].wInputClipOffsetX + m_asScaleChInfo[iChID].sswInputAdjustStartX - 1));
    C753SetInputPortACTHorizontalWidth(iChID, m_asScaleChInfo[iChID].wInputClipWidth + m_asScaleChInfo[iChID].sswInputAdjustWidth);
    C753SetInputPortACTVerticalStart(iChID, (uint16_t)(m_asScaleChInfo[iChID].wInputStartY + m_asScaleChInfo[iChID].wInputClipOffsetY + m_asScaleChInfo[iChID].sswInputAdjustStartY + 1));
    /*由于图像下边缘闪烁，高度补充4行数据*/
    C753SetInputPortACTVerticalWidth(iChID, m_asScaleChInfo[iChID].wInputClipHeight + m_asScaleChInfo[iChID].sswInputAdjustHeight + 4);
    if(m_asScaleChInfo[iChID].sswScaleModeH == SCAL_MODE_ZOOM)
    {
        /*放大比率大于2倍时要在输入宽度补偿2个像素，否则补偿1个像素*/
        if(m_asScaleChInfo[iChID].wScaleFactorUpH < 32768)
        {
            C753SetInputPortACTHorizontalWidth(iChID, m_asScaleChInfo[iChID].wInputClipWidth + m_asScaleChInfo[iChID].sswInputAdjustWidth + 2);
        }
        else
        {
            C753SetInputPortACTHorizontalWidth(iChID, m_asScaleChInfo[iChID].wInputClipWidth + m_asScaleChInfo[iChID].sswInputAdjustWidth + 1);
        }
    }
    else if(m_asScaleChInfo[iChID].sswScaleModeH == SCAL_MODE_SHRINK)
    {
        /*缩小时要将输入宽度设置成等于输出宽度*/
        C753SetInputPortACTHorizontalWidth(iChID, m_asScaleChInfo[iChID].wOutputActWidth);
    }
    else if(m_asScaleChInfo[iChID].sswScaleModeH == SCAL_MODE_BOTH)
    {
        /*缩小时要将输入宽度设置成等于缩小前的宽度*/
        C753SetInputPortACTHorizontalWidth(iChID, SCAL_FRAME_LINE_MAX);
    }
    /*
    *  配置输出部分寄存器
    */
    C753SetOutputImageControl(iChID, 0x02);

    /*配置OAOI区域为图像输出区域 防止放大时图像叠加产生顶层图像超出*/
    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
        C753SetOutputPortOAOI1HorizontalStart((uint16_t)(m_asScaleChInfo[iChID].wOutputStartX + m_asScaleChInfo[iChID].wOutputClipOffsetX));
        C753SetOutputPortOAOI1HorizontalEnd((uint16_t)(m_asScaleChInfo[iChID].wOutputStartX + m_asScaleChInfo[iChID].wOutputClipOffsetX + m_asScaleChInfo[iChID].wOutputClipWidth));
        C753SetOutputPortOAOI1VerticalStart((uint16_t)(m_asScaleChInfo[iChID].wOutputStartY + m_asScaleChInfo[iChID].wOutputClipOffsetY + 0));
        C753SetOutputPortOAOI1VerticalEnd((uint16_t)(m_asScaleChInfo[iChID].wOutputStartY + m_asScaleChInfo[iChID].wOutputClipOffsetY + m_asScaleChInfo[iChID].wOutputClipHeight + 1));
    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
        C753SetOutputPortOAOI2HorizontalStart((uint16_t)(m_asScaleChInfo[iChID].wOutputStartX + m_asScaleChInfo[iChID].wOutputClipOffsetX));
        C753SetOutputPortOAOI2HorizontalEnd((uint16_t)(m_asScaleChInfo[iChID].wOutputStartX + m_asScaleChInfo[iChID].wOutputClipOffsetX + m_asScaleChInfo[iChID].wOutputClipWidth));
        C753SetOutputPortOAOI2VerticalStart((uint16_t)(m_asScaleChInfo[iChID].wOutputStartY + m_asScaleChInfo[iChID].wOutputClipOffsetY + 0));
        C753SetOutputPortOAOI2VerticalEnd((uint16_t)(m_asScaleChInfo[iChID].wOutputStartY + m_asScaleChInfo[iChID].wOutputClipOffsetY + m_asScaleChInfo[iChID].wOutputClipHeight + 1));
    }
    /*输出图像区域*/
    C753SetOutputPortACTHorizontalStart(iChID, (uint16_t)(m_asScaleChInfo[iChID].wOutputStartX + m_asScaleChInfo[iChID].wOutputActOffsetX));
    C753SetOutputPortACTHorizontalWidth(iChID, m_asScaleChInfo[iChID].wOutputActWidth);
    C753SetOutputPortACTVerticalStart(iChID, (uint16_t)(m_asScaleChInfo[iChID].wOutputStartY + m_asScaleChInfo[iChID].wOutputActOffsetY + 0));
    C753SetOutputPortACTVerticalWidth(iChID, m_asScaleChInfo[iChID].wOutputActHeight + 1);

    if(m_asScaleChInfo[iChID].sswScaleModeH == SCAL_MODE_ZOOM)
    {
        /*放大比率大于2倍时要将输出宽度设置成等于输入宽度加上补偿2个像素，否则补偿1个像素*/
        if(m_asScaleChInfo[iChID].wScaleFactorUpH < 32768)
        {
            C753SetOutputPortACTHorizontalWidth(iChID, m_asScaleChInfo[iChID].wInputClipWidth + m_asScaleChInfo[iChID].sswInputAdjustWidth + 2);
        }
        else
        {
            C753SetOutputPortACTHorizontalWidth(iChID, m_asScaleChInfo[iChID].wInputClipWidth + m_asScaleChInfo[iChID].sswInputAdjustWidth + 1);
        }
    }
    else if(m_asScaleChInfo[iChID].sswScaleModeH == SCAL_MODE_BOTH)
    {
        /*放大时要将输出宽度设置成等于放大前的宽度*/
        C753SetOutputPortACTHorizontalWidth(iChID, SCAL_FRAME_LINE_MAX);
    }

    if(m_asScaleChInfo[iChID].sswScaleModeV == SCAL_MODE_ZOOM)
    {
        /*C753bug 放大时放大的图像层会下移1-2个像素*/
        C753SetOutputPortACTVerticalStart(iChID, (uint16_t)(m_asScaleChInfo[iChID].wOutputStartY + m_asScaleChInfo[iChID].wOutputActOffsetY - 2));
        C753SetOutputPortACTVerticalWidth(iChID, m_asScaleChInfo[iChID].wOutputActHeight + 3);
    }
    else if(m_asScaleChInfo[iChID].sswScaleModeV == SCAL_MODE_BOTH)
    {
        /*C753bug 放大时放大的图像层会下移1-2个像素*/
        C753SetOutputPortACTVerticalStart(iChID, (uint16_t)(m_asScaleChInfo[iChID].wOutputStartY + m_asScaleChInfo[iChID].wOutputActOffsetY - 2));
        C753SetOutputPortACTVerticalWidth(iChID, m_asScaleChInfo[iChID].wOutputActHeight + 3);
    }

    if(m_asScaleChInfo[iChID].sswScaleModeH == SCAL_MODE_SHRINK)
    {
        /*
        *  配置缩小寄存器
        */
        uint8_t lut[24];
        float ratio, win;

        ratio = (float)m_asScaleChInfo[iChID].wScaleFactorDownH / 65536;
        if(ratio > 0.5)
        {
            win = ratio;
        }
        else
        {
            win = 0.1;
        }
        calculate6SymbolLUT(&ratio, &win, lut);
        C753LoadInputHorizontalShrinkLookupTable(iChID, lut);
        C753SetInputShrinkCompensationControl(iChID, 0x00);
        C753SetInputHorizontalShrinkCompensation(iChID, 0x00);
        /*6-symbol LUT*/
        C753SetInputHorizontalShrinkControl(iChID, 0x07);
        /*关闭放大模块*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x00);
        C753SetInputHorizontalShrinkInitialValue(iChID, 0x00);
        C753SetInputHorizontalShrinkScale(iChID, m_asScaleChInfo[iChID].wScaleFactorDownH);
    }
    else if(m_asScaleChInfo[iChID].sswScaleModeH == SCAL_MODE_ZOOM)
    {
        /*
        *  配置放大寄存器
        */
        /*6-symbol LUT*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x07);
        /*关闭缩小模块*/
        C753SetInputHorizontalShrinkControl(iChID, 0x00);
        C753SetOutputHorizontalEnlargementInitialValue(iChID, 0x00);
        C753SetOutputHorizontalZoomScale(iChID, m_asScaleChInfo[iChID].wScaleFactorUpH);
    }
    else if(m_asScaleChInfo[iChID].sswScaleModeH == SCAL_MODE_BOTH)
    {
        uint8_t lut[24];
        float ratio, win;

        ratio = (float)m_asScaleChInfo[iChID].wScaleFactorDownH / 65536;
        if(ratio > 0.5)
        {
            win = ratio;
        }
        else
        {
            win = 0.1;
        }
        calculate6SymbolLUT(&ratio, &win, lut);
        C753LoadInputHorizontalShrinkLookupTable(iChID, lut);
        C753SetInputShrinkCompensationControl(iChID, 0x00);
        C753SetInputHorizontalShrinkCompensation(iChID, 0x00);
        /*6-symbol LUT*/
        C753SetInputHorizontalShrinkControl(iChID, 0x07);
        C753SetInputHorizontalShrinkInitialValue(iChID, 0x00);
        C753SetInputHorizontalShrinkScale(iChID, m_asScaleChInfo[iChID].wScaleFactorDownH);
        /*6-symbol LUT*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x07);
        C753SetOutputHorizontalEnlargementInitialValue(iChID, 0x00);
        C753SetOutputHorizontalZoomScale(iChID, m_asScaleChInfo[iChID].wScaleFactorUpH);
    }
    else
    {
        /*关闭缩小模块*/
        C753SetInputHorizontalShrinkControl(iChID, 0x00);
        /*关闭放大模块*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x00);
    }

    if(m_asScaleChInfo[iChID].sswScaleModeV == SCAL_MODE_SHRINK)
    {
        /*
        *  配置缩小寄存器
        */
        uint8_t lut[24];
        float ratio, win;

        ratio = (float)m_asScaleChInfo[iChID].wScaleFactorDownV / 65536;
        if(ratio > 0.5)
        {
            win = ratio;
        }
        else
        {
            win = 0.1;
        }
        calculate6SymbolLUT(&ratio, &win, lut);
        C753LoadInputVerticalShrinkLookupTable(iChID, lut);
        C753SetInputShrinkCompensationControl(iChID, 0x00);
        C753SetInputVerticalShrinkCompensation(iChID, 0x00);
        /*6-symbol LUT*/
        C753SetInputVerticalShrinkControl(iChID, 0x07);
        /*关闭放大模块*/
        C753SetOutputVerticalEnlargementControl(iChID, 0x00);
        C753SetInputVerticalShrinkInitialValue(iChID, 0x00);
        C753SetInputVerticalShrinkScale(iChID, m_asScaleChInfo[iChID].wScaleFactorDownV);
    }
    else if(m_asScaleChInfo[iChID].sswScaleModeV == SCAL_MODE_ZOOM)
    {
        /*
        *  配置放大寄存器
        */
        /*6-symbol LUT*/
        C753SetOutputVerticalEnlargementControl(iChID, 0x07);
        /*关闭缩小模块*/
        C753SetInputVerticalShrinkControl(iChID, 0x00);
        C753SetOutputVerticalEnlargementInitialValue(iChID, 0x00);
        C753SetOutputVerticalZoomScale(iChID, m_asScaleChInfo[iChID].wScaleFactorUpV);
    }
    else if(m_asScaleChInfo[iChID].sswScaleModeV == SCAL_MODE_BOTH)
    {
        uint8_t lut[24];
        float ratio, win;

        ratio = (float)m_asScaleChInfo[iChID].wScaleFactorDownV / 65536;
        if(ratio > 0.5)
        {
            win = ratio;
        }
        else
        {
            win = 0.1;
        }
        calculate6SymbolLUT(&ratio, &win, lut);
        C753LoadInputVerticalShrinkLookupTable(iChID, lut);
        C753SetInputShrinkCompensationControl(iChID, 0x00);
        C753SetInputVerticalShrinkCompensation(iChID, 0x00);
        /*6-symbol LUT*/
        C753SetInputVerticalShrinkControl(iChID, 0x07);
        C753SetInputVerticalShrinkInitialValue(iChID, 0x00);
        C753SetInputVerticalShrinkScale(iChID, m_asScaleChInfo[iChID].wScaleFactorDownV);
        /*6-symbol LUT*/
        C753SetOutputVerticalEnlargementControl(iChID, 0x07);
        C753SetOutputVerticalEnlargementInitialValue(iChID, 0x00);
        C753SetOutputVerticalZoomScale(iChID, m_asScaleChInfo[iChID].wScaleFactorUpV);
    }
    else
    {
        /*关闭放大模块*/
        C753SetOutputVerticalEnlargementControl(iChID, 0x00);
        /*关闭缩小模块*/
        C753SetInputVerticalShrinkControl(iChID, 0x00);
    }

    /*
    *  其他寄存器
    */
    /*通道已经打开，由于信号分辨率发生变化，要重新设置缩放参数
    *叠加层次保持不变，所以在这里返回
    */
    if(m_asScaleChInfo[iChID].iChStatus == SCAL_STATUS_REOPEN)
        return;

    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
        /*叠加控制 side 1*/
        C753SetOverlayControl(0x00);
        /*打开通道1*/
        if(m_asScaleChInfo[iChID].iChStatus == SCAL_STATUS_OPEN)
        {
            C753SetMainControl(iChID,0x03);
        }
        else
        {
            C753SetMainControl(iChID,0x02);
        }
    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
        /*叠加控制 side 2*/
        C753SetOverlayControl(0x01);
        /*打开通道2*/
        if(m_asScaleChInfo[iChID].iChStatus == SCAL_STATUS_OPEN)
        {
        	C753SetMainControl(iChID,0x07);
        }
        else
        {
        	C753SetMainControl(iChID,0x06);
        }
    }
}

void AppScale::pauseChannel(uint32_t iChID)
{
    uint8_t val=0;

    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
        C753GetMainControl(iChID,val);
        C753SetMainControl(iChID,0x01);
    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
        C753GetMainControl(iChID,val);
        C753SetMainControl(iChID,0x05);
    }
    else
    {
        return;
    }

    m_asScaleChInfo[iChID].byContextRegs[0] = val;
}

void AppScale::resumeChannel(uint32_t iChID)
{
    uint8_t val=0;


    val = m_asScaleChInfo[iChID].byContextRegs[0];
    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
        C753SetMainControl(iChID,val);
    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
    	C753SetMainControl(iChID,val);
    }
    else
    {
        return;
    }
}

int32_t AppScale::calculate6SymbolLUT(float *pfCutoff, float *pfWinfact, uint8_t *pbyLut)
{
    int i, icoeff[32], ik[8];
    float fj, fpara, fCutoff, fWinfact, fcoeff[32], fk[8];

    fCutoff = *pfCutoff;
    fWinfact = *pfWinfact;
    if(fCutoff < 0.3)
    {
        fCutoff = 0.3;
    }
    else if(fCutoff > 1.2)
    {
        fCutoff = 1.2;
    }

    if(fWinfact < 0.1)
    {
        fWinfact = 0.1;
    }
    else if(fWinfact > 1.0)
    {
        fWinfact = 1.0;
    }

    for(i = 0; i < 25; i++)
    {
		fj = (float)(i - 24);
		if(i == 24)
        {
            fj = 0.0001;
		}

		fcoeff[i] = (sin(3.141592*fj*fCutoff/8.0)) / (3.141592*fj*fCutoff);

		if(i == 0)
		{
            fcoeff[0] = 0;
		}

		fpara = 1 - fWinfact * (24 - i) / 24;
		if(fpara < 0.01)
        {
            fpara = 0;
        }
		fcoeff[i] = fcoeff[i] * fpara;
    }

	fk[0] = fcoeff[0] + fcoeff[8]  + fcoeff[16] + fcoeff[24] + fcoeff[16] + fcoeff[8] + fcoeff[0];
	fk[1] = fcoeff[1] + fcoeff[9]  + fcoeff[17] + fcoeff[23] + fcoeff[15] + fcoeff[7];
	fk[2] = fcoeff[2] + fcoeff[10] + fcoeff[18] + fcoeff[22] + fcoeff[14] + fcoeff[6];
	fk[3] = fcoeff[3] + fcoeff[11] + fcoeff[19] + fcoeff[21] + fcoeff[13] + fcoeff[5];
	fk[4] = fcoeff[4] + fcoeff[12] + fcoeff[20] + fcoeff[20] + fcoeff[12] + fcoeff[4];
	fk[5] = fcoeff[5] + fcoeff[13] + fcoeff[21] + fcoeff[19] + fcoeff[11] + fcoeff[3];
	fk[6] = fcoeff[6] + fcoeff[14] + fcoeff[22] + fcoeff[18] + fcoeff[10] + fcoeff[2];
	fk[7] = fcoeff[7] + fcoeff[15] + fcoeff[23] + fcoeff[17] + fcoeff[9]  + fcoeff[1];

	for(i = 0; i < 25; i++)
    {
		if(fk[i%8] != 0)
        {
            icoeff[i] = (int)(64.0 * fcoeff[i] / fk[i%8]);
		}
		else
        {
            icoeff[i] = 0;
		}
	}

	ik[0] = icoeff[0] + icoeff[8]  + icoeff[16] + icoeff[24] + icoeff[16] + icoeff[8] + icoeff[0];
	ik[1] = icoeff[1] + icoeff[9]  + icoeff[17] + icoeff[23] + icoeff[15] + icoeff[7];
	ik[2] = icoeff[2] + icoeff[10] + icoeff[18] + icoeff[22] + icoeff[14] + icoeff[6];
	ik[3] = icoeff[3] + icoeff[11] + icoeff[19] + icoeff[21] + icoeff[13] + icoeff[5];

	icoeff[24] = icoeff[24] + 64 - ik[0];
	icoeff[23] = icoeff[23] + 64 - ik[1];
	icoeff[22] = icoeff[22] + 64 - ik[2];
	icoeff[21] = icoeff[21] + 64 - ik[3];
	icoeff[20] = 32 - icoeff[12] - icoeff[4];

    for(i = 0; i < 24; i++)
    {
        pbyLut[i] = (uint8_t)(icoeff[i+1] & 0xff);
    }

    return 0;
}



static uint8_t *pMapTable[256];
void  AppScale::writeBackground(uint32_t iChID, uint16_t wOffsetX, uint16_t wOffsetY, DispBitmapT *BitmapPtr)
{
    uint32_t memAddr, memWidth;
    uint16_t status, field;
    uint16_t i, j, w, h;
    uint8_t *pbyBuf;


    C753GetStatus(status);
    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
        field = (status & 0x0003);
    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
        field = ((status>>2) & 0x0003);
    }

    if(field == 0)
         C753GetOutputField0MemoryReadStartAddress(iChID,memAddr);
    else if(field == 1)
    	 C753GetOutputField1MemoryReadStartAddress(iChID,memAddr);
    else if(field == 2)
        C753GetOutputField2MemoryReadStartAddress(iChID,memAddr);
    else if(field == 3)
        C753GetOutputField3MemoryReadStartAddress(iChID,memAddr);

    uint8_t byVal=0;
    C753GetMemoryReadLinefeedWidth(iChID,byVal);
    memWidth = ((uint32_t)byVal)<<8;
    memAddr += (wOffsetY*memWidth + wOffsetX*4);
    C753SetCPUWriteAddress(memAddr);
    w = BitmapPtr->w;
    h = BitmapPtr->h;
    pbyBuf = BitmapPtr->Bmp;
    if(BitmapPtr->BitCount == 24)
    {
        uint8_t r, g, b;
        for(i = 0; i < h; i++)
        {
            C753WriteN24BitPixels(w, pbyBuf);
            pbyBuf += w*3;
            memAddr += memWidth;
            C753SetCPUWriteAddress(memAddr);
        }
    }
    else if(BitmapPtr->BitCount == 8)
    {
        for(i = 0; i < h; i++)
        {
            C753WriteN8BitPixels(w, BitmapPtr->pPalette, pbyBuf);
            pbyBuf += w;
            memAddr += memWidth;
            C753SetCPUWriteAddress(memAddr);
        }
    }
    else if(BitmapPtr->BitCount == 1)
    {
        uint8_t val;
        uint8_t *pbySrc;

        pbySrc = (uint8_t *)malloc(256*8);
        memset(pbySrc, 0, 256*8);
        pMapTable[0] = pbySrc;
        for(i = 0; i < 256; i++)
        {
            pMapTable[i] = pbySrc + i*8;
            val = i;
            for(j = 0; j < 8; j++)
            {
                if(val & 0x80)
                {
                    pMapTable[i][j] = 0x01;
                }
                val <<= 1;
            }
        }

        for(i = 0; i < h; i++)
        {
            C753WriteN1BitPixels(w, BitmapPtr->pPalette, pMapTable, pbyBuf);
            pbyBuf += w/8;
            memAddr += memWidth;
            C753SetCPUWriteAddress(memAddr);
        }
        free(pMapTable[0]);
    }
}

void AppScale::readBackground(uint32_t iChID, int32_t iIndex, uint16_t wWidth, uint16_t wHeight, uint8_t *pbyBuf)
{
	uint8_t val, r, g, b;
    uint32_t memAddr, memWidth;
    int32_t i, j;
    int32_t width;
    uint8_t *pBase;

    width = (wWidth*3 + 3) & (-4);
    pBase = pbyBuf;
    if((iIndex < 0) || (iIndex > 3))
    {
        iIndex = 0;
    }

    if(iIndex == 0)
    {
        C753GetOutputField0MemoryReadStartAddress(iChID,memAddr);
    }
    else if(iIndex == 1)
    {
        C753GetOutputField1MemoryReadStartAddress(iChID,memAddr);
    }
    else if(iIndex == 2)
    {
        C753GetOutputField2MemoryReadStartAddress(iChID,memAddr);
    }
    else if(iIndex == 3)
    {
        C753GetOutputField3MemoryReadStartAddress(iChID,memAddr);
    }

    uint8_t byVal=0;
    C753GetMemoryReadLinefeedWidth(iChID,byVal);
    memWidth =((uint32_t)byVal)<<8;

    C753SetCPUReadAddress(memAddr-1);
    C753GetCPUData(byVal);
    for(i = 0; i < wHeight; i++)
    {
        C753ReadN24BitPixels(wWidth, pbyBuf);
        pbyBuf += width;
        memAddr += memWidth;
        C753SetCPUReadAddress(memAddr-1);
        C753GetCPUData(byVal);
    }

}


void AppScale::openChannelTest()
{
    int i;
    uint32_t iChID=1;

    printf("openChannelTest\n");

    /*配置传输寄存器*/
    /*RTCT4=000B RTCT3=000B RTCT2=110B RTCT1=101B RTCT0=011B*/
    C753SetRegisterValueTransferControl(0x01AB);
    /*
    *  配置输入部分寄存器
    */
    /*RGB 30-bit 输入*/
    C753SetInputFormatControl(iChID, 0x00);
    /*IFLD 0到3循环*/
    /*水平同步信号低电平有效*/
    /*垂直同步信号低电平有效*/
    C753SetInputPortSyncControl(iChID, 0x02);
    /*关闭场信号自动识别*/
    C753SetInputFieldRecognitionControl(iChID, 0x00);
    /*PIACT区域外图像为0 PIACT POL*/
    C753SetInputDigitalInterfaceControl(iChID, 0x00);
    /*
    *  配置输出部分寄存器
    */
    C753SetOutputPortSyncControl(0x2350);
    /*OFLDC输出同步方式，OFLD1=0, OFLD2=0*/
    /*POACT active high Select AOI3*/
    /*C753SetOutputSyncControl(0x0068);*/
    /*通道1输出场指针延时改变时间*/
    C753SetFieldPropagationDelay1(0x04);
    /*通道2输出场指针延时改变时间*/
    C753SetFieldPropagationDelay2(0x04);
    /*背景图像*/
    C753SetOutputBackground0(0x00);
    C753SetOutputBackground1(0x00);
    /*POCLKO 输出使能*/
    C753SetPOCLKControl(0x03);
    /*POCLK PLL配置*/
    C753SetPOCLKPLLControl(0x81);
    C753SetPOCLKReferenceDividing(0x07);
    C753SetPOCLKFeedbackDividing(0x0f);

    printf("initHardware PCL OK \n!");


    uint16_t startX=0;
    uint16_t startY=0;
    uint16_t width=0;
    uint16_t height=0;


    C753SetOutputPortOAOI1HorizontalStart((uint16_t)163);
    C753SetOutputPortOAOI1HorizontalEnd((uint16_t)1178);
    C753SetOutputPortOAOI1VerticalStart((uint16_t)34);
    C753SetOutputPortOAOI1VerticalEnd((uint16_t)803);

    /*输出图像区域*/
    C753SetOutputPortACTHorizontalStart(iChID, (uint16_t)163);
    C753SetOutputPortACTHorizontalWidth(iChID, 1024);
    C753SetOutputPortACTVerticalStart(iChID, (uint16_t)34);
    C753SetOutputPortACTVerticalWidth(iChID,769);


    printf("initHardware OUTPUT PORT OK \n!");

    C753LoadInputHorizontalShrinkLookupTable(iChID, s_abyScaleShrinkCoefficient4SymbolTable);
    C753LoadInputVerticalShrinkLookupTable(iChID, s_abyScaleShrinkCoefficient4SymbolTable);
    C753LoadOutputHorizontalZoomLookupTable(iChID, s_abyScaleZoomCoefficient4SymbolTable);
    C753LoadOutputVerticalZoomLookupTable(iChID, s_abyScaleZoomCoefficient4SymbolTable);
    /*
    *  配置图像数据存储器
    */

    C753SetOutputField0MemoryReadStartAddress(iChID, 0x00C00000);
    C753SetOutputField1MemoryReadStartAddress(iChID, 0x00000000);
    C753SetOutputField2MemoryReadStartAddress(iChID, 0x00400000);
    C753SetOutputField3MemoryReadStartAddress(iChID, 0x00800000);
    C753SetInputField0MemoryWriteStartAddress(iChID, 0x00000000);
    C753SetInputField1MemoryWriteStartAddress(iChID, 0x00400000);
    C753SetInputField2MemoryWriteStartAddress(iChID, 0x00800000);
    C753SetInputField3MemoryWriteStartAddress(iChID, 0x00C00000);


    C753SetMemoryReadLinefeedWidth(iChID, 0x10);
    C753SetMemoryWriteLinefeedWidth(iChID, 0x10);

        /*配置IP转换的输出区域*/
        C753SetIPConversionOutputPortHorizontalSyncCycle(iChID, 0x04b6);
        C753SetIPConversionOutputPortVerticalSyncCycle(iChID, 0x0fff);
        C753SetIPConversionForcedSyncResetDelay(iChID, 0x40);
        C753SetIPConversionOutputPortActiveAreaHorizontalStart(iChID, 0x0020);
        C753SetIPConversionOutputPortActiveAreaHorizontalWidth(iChID, 0x02d0);
        C753SetIPConversionOutputPortActiveAreaVerticalStart(iChID, 0x0008);
        C753SetIPConversionOutputPortActiveAreaVerticalWidth(iChID, 0x01e5);
        /*配置IP转换运动自适应补偿滤波器系数*/
        C753SetMovementNRControl(iChID, 0x17);
        C753SetHorizontalMovementValueNRCoefficient(iChID, 0x01, 0x01, 0x02, 0x08);
        C753SetVerticalMovementValueGain(iChID, 0x00, 0x00, 0x00, 0x00);
        C753SetHorizontalMovementValueGain(iChID, 0x08, 0x08, 0x10, 0x18);
        C753SetVerticalDirectionMAXFilter(iChID, 0x07);
        C753SetMovementCoefficientNR(iChID, 0x01);
        /*配置IP转换的内存配置*/

        C753SetIPConversionField0MemoryReadStartAddress(iChID, 0x00400000);
        C753SetIPConversionField1MemoryReadStartAddress(iChID, 0x00800000);
        C753SetIPConversionField0MemoryWriteStartAddress(iChID,	0x00401000);
        C753SetIPConversionField1MemoryWriteStartAddress(iChID, 0x00400000);
        C753SetIPConversionField2MemoryWriteStartAddress(iChID, 0x00801000);
        C753SetIPConversionField3MemoryWriteStartAddress(iChID, 0x00800000);
        C753SetIPConversionMovementValueReadStartAddress(iChID, 0x00C00000);


        C753SetIPConversionMemoryLinefeedWidth(iChID, 0x08);
        C753SetTemporalNRReadStartAddressSelect(iChID, 0x01);

        /*配置IP转换表参数*/
        for(i = 0; i < sizeof(s_sLUTIPTable)/sizeof(s_sLUTIPTable[0]); i++)
        {
            C753SetLUTCoefficient(iChID, s_sLUTIPTable[i].dwCoef);
            C753SetLUTWriteAddress(iChID, s_sLUTIPTable[i].byAddr);
            C753SetLUTWriteEnable(iChID, 0xff);
        }

}

void AppScale::initTest1024()
{
    int i;
    uint32_t iChID=1;

    debug_msg("initTest1024\n");

    /*配置传输寄存器*/
    C753SetRegisterValueTransferControl(0x0);
    /*
    *  配置输入部分寄存器
    */
    /*RGB 30-bit 输入*/
    C753SetInputFormatControl(iChID, 0x00);
    /*IFLD 0到3循环*/
    /*水平同步信号低电平有效*/
    /*垂直同步信号低电平有效*/
    C753SetInputPortSyncControl(iChID, 0x02);
    /*关闭场信号自动识别*/
    C753SetInputFieldRecognitionControl(iChID, 0x00);
    /*PIACT区域外图像为0 PIACT POL*/
    C753SetInputDigitalInterfaceControl(iChID, 0x00);
    /*
    *  配置输出部分寄存器
    */
    C753SetOutputPortSyncControl(0x2359);

    /*通道1输出场指针延时改变时间*/
    C753SetFieldPropagationDelay1(0x04);
    /*通道2输出场指针延时改变时间*/
    C753SetFieldPropagationDelay2(0x04);
    /*背景图像*/
    C753SetOutputBackground0(0x00ff00);
    C753SetOutputBackground1(0x0000ff);
    /*POCLKO 输出使能*/
    C753SetPOCLKControl(0x03);
    /*POCLK PLL配置*/
    C753SetPOCLKPLLControl(0x81);
    C753SetPOCLKReferenceDividing(0x07);
    C753SetPOCLKFeedbackDividing(0x0f);

    C753SetIPCLKPLLControl(0x01);
    C753SetIPCLKReferenceDividing(0x01);
    C753SetIPCLKFeedbackDividing(0x03);

    debug_msg("initHardware PCL OK \n!");


    C753SetOutputHorizontalSync(0x053e);
    C753SetOutputVerticalSync(0x0324);




    /*输出图像区域*/
    C753SetOutputPortACTHorizontalStart(iChID, (uint16_t)163);
    C753SetOutputPortACTHorizontalWidth(iChID, 1024);
    C753SetOutputPortACTVerticalStart(iChID, (uint16_t)34);
    C753SetOutputPortACTVerticalWidth(iChID,768);


    debug_msg("initHardware OUTPUT PORT OK \n!");

//    C753LoadInputHorizontalShrinkLookupTable(iChID, s_abyScaleShrinkCoefficient4SymbolTable);
//    C753LoadInputVerticalShrinkLookupTable(iChID, s_abyScaleShrinkCoefficient4SymbolTable);
//    C753LoadOutputHorizontalZoomLookupTable(iChID, s_abyScaleZoomCoefficient4SymbolTable);
//    C753LoadOutputVerticalZoomLookupTable(iChID, s_abyScaleZoomCoefficient4SymbolTable);
    /*
    *  配置图像数据存储器
    */

//    C753SetOutputField0MemoryReadStartAddress(iChID, 0x00C00000);
//    C753SetOutputField1MemoryReadStartAddress(iChID, 0x00000000);
//    C753SetOutputField2MemoryReadStartAddress(iChID, 0x00400000);
//    C753SetOutputField3MemoryReadStartAddress(iChID, 0x00800000);
//    C753SetInputField0MemoryWriteStartAddress(iChID, 0x00000000);
//    C753SetInputField1MemoryWriteStartAddress(iChID, 0x00400000);
//    C753SetInputField2MemoryWriteStartAddress(iChID, 0x00800000);
//    C753SetInputField3MemoryWriteStartAddress(iChID, 0x00C00000);
//
//
//    C753SetMemoryReadLinefeedWidth(iChID, 0x10);
//    C753SetMemoryWriteLinefeedWidth(iChID, 0x10);





}

void AppScale::initTest1400()
{
    int i;
    uint32_t iChID=1;

    debug_msg("initTest1400\n");

    /*配置传输寄存器*/
    C753SetRegisterValueTransferControl(0x0);
    /*
    *  配置输入部分寄存器
    */
    /*RGB 30-bit 输入*/
    C753SetInputFormatControl(iChID, 0x00);
    /*IFLD 0到3循环*/
    /*水平同步信号低电平有效*/
    /*垂直同步信号低电平有效*/
    C753SetInputPortSyncControl(iChID, 0x02);
    /*关闭场信号自动识别*/
    C753SetInputFieldRecognitionControl(iChID, 0x00);
    /*PIACT区域外图像为0 PIACT POL*/
    C753SetInputDigitalInterfaceControl(iChID, 0x00);
    /*
    *  配置输出部分寄存器
    */
    C753SetOutputPortSyncControl(0x2341);

    /*通道1输出场指针延时改变时间*/
    C753SetFieldPropagationDelay1(0x04);
    /*通道2输出场指针延时改变时间*/
    C753SetFieldPropagationDelay2(0x04);
    /*背景图像*/
    C753SetOutputBackground0(0x00ff00);
    C753SetOutputBackground1(0x0000ff);
    /*POCLKO 输出使能*/
    C753SetPOCLKControl(0x03);
    /*POCLK PLL配置*/
    C753SetPOCLKPLLControl(0x81);
    C753SetPOCLKReferenceDividing(0x07);
    C753SetPOCLKFeedbackDividing(0x0f);


    C753SetIPCLKPLLControl(0x01);
    C753SetIPCLKReferenceDividing(0x01);
    C753SetIPCLKFeedbackDividing(0x03);

    debug_msg("initHardware PCL OK \n!");


    C753SetOutputHorizontalSync(0x0746);
    C753SetOutputVerticalSync(0x043f);




    C753SetOutputPortOAOI1HorizontalStart((uint16_t)241);
    C753SetOutputPortOAOI1HorizontalEnd((uint16_t)1640);
    C753SetOutputPortOAOI1VerticalStart((uint16_t)35);
    C753SetOutputPortOAOI1VerticalEnd((uint16_t)1085);



    C753SetOutputPortOAOI0HorizontalStart((uint16_t)163);
    C753SetOutputPortOAOI0HorizontalEnd((uint16_t)1178);
    C753SetOutputPortOAOI0VerticalStart((uint16_t)34);
    C753SetOutputPortOAOI0VerticalEnd((uint16_t)803);


//    {1024,  768,   60,  65,   1344,    136,  296,  806,     6,     35,  -133,   -1},
//    {1400,  1050,  60,  121,  1864,    144,  376,  1089,    4,     36,  -135,   -1},
    /*输出图像区域*/
    C753SetOutputPortACTHorizontalStart(iChID, (uint16_t)341);
    C753SetOutputPortACTHorizontalWidth(iChID, 1024);
    C753SetOutputPortACTVerticalStart(iChID, (uint16_t)135);
    C753SetOutputPortACTVerticalWidth(iChID,768);


    debug_msg("initHardware OUTPUT PORT OK \n!");

//    C753LoadInputHorizontalShrinkLookupTable(iChID, s_abyScaleShrinkCoefficient4SymbolTable);
//    C753LoadInputVerticalShrinkLookupTable(iChID, s_abyScaleShrinkCoefficient4SymbolTable);
//    C753LoadOutputHorizontalZoomLookupTable(iChID, s_abyScaleZoomCoefficient4SymbolTable);
//    C753LoadOutputVerticalZoomLookupTable(iChID, s_abyScaleZoomCoefficient4SymbolTable);
//    /*
//    *  配置图像数据存储器
//    */
//
//    C753SetOutputField0MemoryReadStartAddress(iChID, 0x00C00000);
//    C753SetOutputField1MemoryReadStartAddress(iChID, 0x00000000);
//    C753SetOutputField2MemoryReadStartAddress(iChID, 0x00400000);
//    C753SetOutputField3MemoryReadStartAddress(iChID, 0x00800000);
//    C753SetInputField0MemoryWriteStartAddress(iChID, 0x00000000);
//    C753SetInputField1MemoryWriteStartAddress(iChID, 0x00400000);
//    C753SetInputField2MemoryWriteStartAddress(iChID, 0x00800000);
//    C753SetInputField3MemoryWriteStartAddress(iChID, 0x00C00000);
//
//
//    C753SetMemoryReadLinefeedWidth(iChID, 0x10);
//    C753SetMemoryWriteLinefeedWidth(iChID, 0x10);

}

void AppScale::initScal(uint32_t iChID,uint32_t hInput,uint32_t vInput,uint32_t hOutput,uint32_t vOutput)
{
	if(hInput > hOutput)
	{
		uint16_t shrinkScale= hOutput * 65536 / (hInput - 1) + 1;

        uint8_t lut[24];
        float ratio, win;



        ratio = (float)shrinkScale / 65536;
        if(ratio > 0.5)
        {
            win = ratio;
        }
        else
        {
            win = 0.1;
        }
        calculate6SymbolLUT(&ratio, &win, lut);
        C753LoadInputHorizontalShrinkLookupTable(iChID, lut);
        C753SetInputShrinkCompensationControl(iChID, 0x00);
        C753SetInputHorizontalShrinkCompensation(iChID, 0x00);
        /*6-symbol LUT*/
        C753SetInputHorizontalShrinkControl(iChID, 0x07);
        /*关闭放大模块*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x00);
        C753SetInputHorizontalShrinkInitialValue(iChID, 0x00);



        C753SetInputHorizontalShrinkScale(iChID,shrinkScale);

        C753SetInputPortACTHorizontalWidth(iChID,hInput);
        C753SetOutputPortACTHorizontalWidth(iChID, hOutput);

	}
	else if(hInput < hOutput)
	{

		 uint16_t zoomScale= hInput * 65536 / (hOutput + 1);

        /*
        *  配置放大寄存器
        */
        /*6-symbol LUT*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x07);
        /*关闭缩小模块*/
        C753SetInputHorizontalShrinkControl(iChID, 0x00);
        C753SetOutputHorizontalEnlargementInitialValue(iChID, 0x00);

        C753SetOutputHorizontalZoomScale(iChID,zoomScale);

        C753SetInputPortACTHorizontalWidth(iChID,hInput);
	}
	else
	{
        /*关闭缩小模块*/
        C753SetInputHorizontalShrinkControl(iChID, 0x00);
        /*关闭放大模块*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x00);

        C753SetInputPortACTHorizontalWidth(iChID,hInput);
        C753SetOutputPortACTHorizontalWidth(iChID, hOutput);
	}


	if(vInput > vOutput)
	{

        uint16_t shrinkScale= vOutput * 65536 / (vInput - 1) + 1;

//        uint8_t lut[24];
//        float ratio, win;
//
//
//
//
//        ratio = (float)shrinkScale / 65536;
//        if(ratio > 0.5)
//        {
//            win = ratio;
//        }
//        else
//        {
//            win = 0.1;
//        }
//        calculate6SymbolLUT(&ratio, &win, lut);
//        C753LoadInputVerticalShrinkLookupTable(iChID, lut);
        C753SetInputShrinkCompensationControl(iChID, 0x00);
        C753SetInputVerticalShrinkCompensation(iChID, 0x00);
        /*6-symbol LUT*/
        C753SetInputVerticalShrinkControl(iChID, 0x07);
        /*关闭放大模块*/
        C753SetOutputVerticalEnlargementControl(iChID, 0x00);
        C753SetInputVerticalShrinkInitialValue(iChID, 0x00);
        C753SetInputVerticalShrinkScale(iChID, shrinkScale);


        C753SetInputPortACTVerticalWidth(iChID,vInput);
        C753SetOutputPortACTVerticalWidth(iChID,vOutput);
	}
	else if(vInput < vOutput)
	{
		uint16_t zoomScale= vInput * 65536 / (vOutput + 1);
        /*
        *  配置放大寄存器
        */
        /*6-symbol LUT*/
        C753SetOutputVerticalEnlargementControl(iChID, 0x07);
        /*关闭缩小模块*/
        C753SetInputVerticalShrinkControl(iChID, 0x00);
        C753SetOutputVerticalEnlargementInitialValue(iChID, 0x00);


        C753SetOutputVerticalZoomScale(iChID, zoomScale);


        C753SetOutputPortACTVerticalWidth(iChID,vOutput);
	}
	else
	{
        C753SetOutputVerticalEnlargementControl(iChID, 0x00);
        /*关闭缩小模块*/
        C753SetInputVerticalShrinkControl(iChID, 0x00);

        C753SetInputPortACTVerticalWidth(iChID,vInput);
        C753SetOutputPortACTVerticalWidth(iChID,vOutput);
	}


}

void AppScale::initChipDDR()
{
	C753SetDDRControl(0x80);

	C753SetMemoryControl(0x28);
	for(int i = 0; i < 80000; i++);
	C753SetMemoryControl(0x29);
	for(int i = 0; i < 80000; i++);
	C753SetDLLControl0(0xaa);
	C753SetDLLControl1(0xaa);
	C753SetDLLControl2(0xdd);
	C753SetDLLControl3(0xdd);
	C753SetDLLControl4(0xdd);
	C753SetDLLControl5(0xdd);
	C753SetDLLControl6(0x00);
	C753SetDLLControl7(0x00);
	C753SetDLLControl8(0x02);
	debug_msg("initCLK OK \n!");
}

void AppScale::initCLK()
{
	/*POCLKO 输出使能*/
	C753SetPOCLKControl(0x03);
	/*POCLK PLL配置*/
	C753SetPOCLKPLLControl(0x81);
	C753SetPOCLKReferenceDividing(0x07);
	C753SetPOCLKFeedbackDividing(0x0f);


	C753SetIPCLKPLLControl(0x01);
	C753SetIPCLKReferenceDividing(0x01);
	C753SetIPCLKFeedbackDividing(0x03);


    /*通道1输出场指针延时改变时间*/
    C753SetFieldPropagationDelay1(0x04);
    /*通道2输出场指针延时改变时间*/
    C753SetFieldPropagationDelay2(0x04);

	debug_msg("initChipDDR OK \n!");
}

void AppScale::initScaleTable(uint32_t channelID)
{
	C753LoadInputHorizontalShrinkLookupTable(channelID, s_abyScaleShrinkCoefficient6SymbolTable);
	C753LoadInputVerticalShrinkLookupTable(channelID, s_abyScaleShrinkCoefficient6SymbolTable);
	C753LoadOutputHorizontalZoomLookupTable(channelID, s_abyScaleZoomCoefficient6SymbolTable);
	C753LoadOutputVerticalZoomLookupTable(channelID, s_abyScaleZoomCoefficient6SymbolTable);

	debug_msg("initScaleTable OK \n!");
}

void AppScale::initMemoryLineFeedWidth(uint32_t channelID)
{
	C753SetMemoryReadLinefeedWidth(channelID, 0x10);
	C753SetMemoryWriteLinefeedWidth(channelID, 0x10);

	debug_msg("initMemoryLineFeedWidth OK \n!");
}

void AppScale::selectOutPutModel(uint32_t model)
{
	if(model == TYPE_OUTPUT_ACT)
	{
		C753SetOutputPortSyncControl(0x2341);
		debug_msg("OutPut Model ACT \n!");
	}
	else if(model == TYPE_OUTPUT_AOI0)
	{
		C753SetOutputPortSyncControl(0x2351);
		debug_msg("OutPut Model AOI0 \n!");
	}
	else if(model == TYPE_OUTPUT_AOI1)
	{
		C753SetOutputPortSyncControl(0x2359);
		debug_msg("OutPut Model AOI1 \n!");
	}


}


void  AppScale::setOutputBGColor(uint32_t bg0Color,uint32_t bg1Color)
{
	C753SetOutputBackground0(bg0Color);
	C753SetOutputBackground1(bg1Color);
	debug_msg("setOutputBGColor bg0Color=%X,bg1Color=%X \n!",bg0Color,bg1Color);
}

void AppScale::setOutputSize(uint32_t type)
{
	 DriverChipICS307 s_ics307;

	 switch(type)
	 {
		 case TYPE_OUTPUT_SIZE_1024_768:
		 {
			 s_ics307.setPOCLK(ICS307_FREQUENCY_65000KHZ);
			 C753SetOutputHorizontalSync(0x053e);
		     C753SetOutputVerticalSync(0x0324);
//		     C753SetHorizontalSyncResetDelay(1);
//		     C753SetVerticalSyncResetDelay(1);
     	     C753SetHorizontalSyncResetDelay(20);
		     C753SetVerticalSyncResetDelay(4);


		     debug_msg("setOutputSize 1024 X 768 @60Hz \n!");
			 break;
		 }

		 case TYPE_OUTPUT_SIZE_1440_1050:
		 {
			 s_ics307.setPOCLK(ICS307_FREQUENCY_121750KHZ);
			 C753SetOutputHorizontalSync(0x0746);
			 C753SetOutputVerticalSync(0x043f);
			 //		     C753SetHorizontalSyncResetDelay(1);
			 //		     C753SetVerticalSyncResetDelay(1);
			      	     C753SetHorizontalSyncResetDelay(20);
			 		     C753SetVerticalSyncResetDelay(4);


			 debug_msg("setOutputSize 1440 X 1050 @60Hz \n!");
			 break;
		 }

		 default:
			 debug_msg("setOutputSize unknow \n!");
			 break;

	 }
}


void AppScale::setOutputImage(uint32_t model,uint32_t size)
{
	selectOutPutModel(model);
	setOutputSize(size);

	if(model == TYPE_OUTPUT_ACT)
	{

		debug_msg("Please set ACT \n!");
	}
	else if(model == TYPE_OUTPUT_AOI0)
	{
		if(size == TYPE_OUTPUT_SIZE_1024_768)
		{
			C753SetOutputPortOAOI0HorizontalStart((uint16_t)296);
			C753SetOutputPortOAOI0HorizontalEnd((uint16_t)1320);
			C753SetOutputPortOAOI0VerticalStart((uint16_t)35);
			C753SetOutputPortOAOI0VerticalEnd((uint16_t)803);

			m_horFp = 296;
			m_verFp = 35;

		}
		else if(size == TYPE_OUTPUT_SIZE_1440_1050)
		{
			 C753SetOutputPortOAOI0HorizontalStart((uint16_t)241);
			 C753SetOutputPortOAOI0HorizontalEnd((uint16_t)1640);
			 C753SetOutputPortOAOI0VerticalStart((uint16_t)35);
			 C753SetOutputPortOAOI0VerticalEnd((uint16_t)1085);

			 m_horFp = 241;
			 m_verFp = 35;

		}

	}

	else if(model == TYPE_OUTPUT_AOI1)
	{
		if(size == TYPE_OUTPUT_SIZE_1024_768)
		{
			C753SetOutputPortOAOI1HorizontalStart((uint16_t)296);
			C753SetOutputPortOAOI1HorizontalEnd((uint16_t)1320);
			C753SetOutputPortOAOI1VerticalStart((uint16_t)35);
			C753SetOutputPortOAOI1VerticalEnd((uint16_t)803);

			m_horFp = 296;
			m_verFp = 35;
		}
		else if(size == TYPE_OUTPUT_SIZE_1440_1050)
		{
			C753SetOutputPortOAOI1HorizontalStart((uint16_t)241);
			C753SetOutputPortOAOI1HorizontalEnd((uint16_t)1640);
			C753SetOutputPortOAOI1VerticalStart((uint16_t)35);
			C753SetOutputPortOAOI1VerticalEnd((uint16_t)1085);

			m_horFp = 241;
			m_verFp = 35;
		}
	}
}

void AppScale::setOutputChannelACT(uint32_t iChID,uint16_t hw,uint16_t vw,uint16_t hs,uint16_t vs)
{
	debug_msg("setOutputChannelACT chid=%d  hw:%d,vw:%d,hs=%d,vs=%d\n",iChID,hw,vw,hs,vs);

	uint16_t tempHs = hs + m_horFp;
	uint16_t tempVs = vs + m_verFp;
	debug_msg("setOutputChannelACT chid=%d  hw:%d,vw:%d,tempHs=%d,tempVs=%d\n",iChID,hw,vw,tempHs,tempVs);

    C753SetOutputPortACTHorizontalStart(iChID, (uint16_t)tempHs);
    C753SetOutputPortACTHorizontalWidth(iChID, hw);
    C753SetOutputPortACTVerticalStart(iChID, (uint16_t)tempVs);
    C753SetOutputPortACTVerticalWidth(iChID,vw);
    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
    	C753SetOutputImageControl(iChID,0x02);
    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
    	C753SetOutputImageControl(iChID,0x00);
    }
//  showWnd(iChID);
}

void AppScale::setInputChannelACT(uint32_t iChID,uint16_t hw,uint16_t vw,uint16_t hs,uint16_t vs)
{
	debug_msg("setInputChannelACT chid=%d  hw:%d,vw:%d,hs=%d,vs=%d\n",iChID,hw,vw,hs,vs);
	C753SetInputPortACTHorizontalStart(iChID, (uint16_t)hs);
	C753SetInputPortACTHorizontalWidth(iChID,hw);
	C753SetInputPortACTVerticalStart(iChID, (uint16_t)vs);
	C753SetInputPortACTVerticalWidth(iChID,vw);
}

void AppScale::moveChannelInput(uint32_t channel,int hPoint,int vPoint)
{
	uint16_t temp = 0;

	debug_msg("move  hPoint:%d,vPoint:%d\n",hPoint,vPoint);
	C753GetInputPortACTHorizontalStart(channel,temp);
	debug_msg("src  oldHS:%d,newHS:%d\n",temp, temp + hPoint);
	temp = temp + hPoint;
	C753SetInputPortACTHorizontalStart(channel,temp);


	C753GetInputPortACTVerticalStart(channel,temp);
	temp = temp + vPoint;
	C753SetInputPortACTVerticalStart(channel,temp);
	debug_msg("src  oldHS:%d,newHS:%d\n",temp, temp + vPoint);
}

void AppScale::moveChannelOutput(uint32_t channel,int hPoint,int vPoint)
{
	uint16_t temp = 0;

	debug_msg("move  hPoint:%d,vPoint:%d\n",hPoint,vPoint);
	C753GetOutputPortACTHorizontalStart(channel,temp);
	debug_msg("src  oldHS:%d,newHS:%d\n",temp, temp + hPoint);
	temp = temp + hPoint;
	C753SetOutputPortACTHorizontalStart(channel,temp);


	C753GetOutputPortACTVerticalStart(channel,temp);
	temp = temp + vPoint;
	C753SetOutputPortACTVerticalStart(channel,temp);
	debug_msg("src  oldHS:%d,newHS:%d\n",temp, temp + vPoint);
}

void AppScale::topChannel(uint32_t channel)
{
    if(channel == C753_OUTPUT_CHANNEL_1)
    {
        C753SetOverlayControl(0x00);
    }
    else if(channel == C753_OUTPUT_CHANNEL_2)
    {
        C753SetOverlayControl(0x01);
    }
}

AppScale* AppScale::Instance()
{
	if(m_instance==NULL)
	{
		m_instance = new AppScale();
	}
	return m_instance;
}


void AppScale::setInputSignalModel(uint32_t chId,uint32_t model)
{

	setInputChannelACT(chId,m_InputInfo[model].hW,m_InputInfo[model].Vw,m_InputInfo[model].hStar,m_InputInfo[model].vStar);
}

