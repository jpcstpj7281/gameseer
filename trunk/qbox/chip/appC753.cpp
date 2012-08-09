/*
 * appC753.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "appC753.h"



using namespace chip;
using namespace chipApp;





AppC753::AppC753()
{
	m_asTimingIndexTable[0].wHorResolution = 1024;
	m_asTimingIndexTable[0].wVerResolution = 768;

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


	m_asSignalTiming[0].wHorResolution = 1024;
	m_asSignalTiming[0].wVerResolution = 768;
	m_asSignalTiming[0].iFrameRate = 60;
	m_asSignalTiming[0].iClock = 65;
	m_asSignalTiming[0].wHorTotal = 1344;
	m_asSignalTiming[0].wHorSync = 136;
	m_asSignalTiming[0].wHorStart = 296;
	m_asSignalTiming[0].wVerTotal = 806;
	m_asSignalTiming[0].wVerSync = 6;
	m_asSignalTiming[0].wVerStart = 35;
	m_asSignalTiming[0].sswC753OffsetX = -133;
	m_asSignalTiming[0].sswC753OffsetY = -1;

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



	initTimingIndexTable();

}

AppC753::~AppC753()
{

}

void AppC753::chipTest()
{
    uint8_t val1, val2;
    uint8_t regAddr;
    uint32_t memAddr;
    int i;

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
        dev_SPI_Write(C753_BUSCAHNNEL, regAddr, val1);
    }

    for(regAddr = 0x08, i = 0x08; i < 0x48; i++, regAddr++)
    {
        val1 = regAddr;
        dev_SPI_Read(C753_BUSCAHNNEL, regAddr,val2);
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
            //SPCMsgErr("can not read memory[val1=0x%02x val2=0x%02x index=%d]\n", val1, val2, i, 0);
        	printf("can not read memory[val_in=0x%02x val_out=0x%02x index=%d]\n", val1, val2, i);
            return ;
        }
        val1++;
    }

    return ;
}

void AppC753::initHardware(uint32_t iChID, ScaleConfigT *pScaleConfig)
{
    int i;


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
    /*OFLDC输出同步方式，OFLD1=IFLD1, OFLD2=IFLD2*/
    if((pScaleConfig->wHorResolution == 1920) && (pScaleConfig->wVerResolution == 1200))
    {
	    /*POACT active low Select AOI0*/
        C753SetOutputPortSyncControl(0x2310);
    }
    else
    {
	    /*POACT active high Select AOI0*/
        C753SetOutputPortSyncControl(0x2350);
    }
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
    /*IPCLK PLL配置*/
    C753SetIPCLKPLLControl(0x01);
    C753SetIPCLKReferenceDividing(0x01);
    C753SetIPCLKFeedbackDividing(0x03);



    uint16_t startX=0;
    uint16_t startY=0;
    uint16_t width=0;
    uint16_t height=0;

    startX = getHorizontalStart(pScaleConfig->wHorResolution, pScaleConfig->wVerResolution, pScaleConfig->byStandardType);
    startX += getHorizontalCompensation(pScaleConfig->wHorResolution, pScaleConfig->wVerResolution, pScaleConfig->byStandardType);
    startY = getVerticalStart(pScaleConfig->wHorResolution, pScaleConfig->wVerResolution, pScaleConfig->byStandardType);
    startY += getVerticalCompensation(pScaleConfig->wHorResolution, pScaleConfig->wVerResolution, pScaleConfig->byStandardType);
    width = pScaleConfig->wHorResolution;
    height = pScaleConfig->wVerResolution;
//    if((pScaleConfig->wHorResolution == 1920) && (pScaleConfig->wVerResolution == 1200))
//    {
//        uint16_t total = getHorizontalTotal(pScaleConfig->wHorResolution, pScaleConfig->wVerResolution, pScaleConfig->byStandardType);
//        /*配置POACT区域*/
//        C753SetOutputPortOAOI0HorizontalStart((WORD)(startX + width - total));
//        C753SetOutputPortOAOI0HorizontalEnd((WORD)(startX));
//        C753SetOutputPortOAOI0VerticalStart((WORD)(startY + 1));
//        C753SetOutputPortOAOI0VerticalEnd((WORD)(startY + height + 1));
//    }
//    else
//    {
        /*配置POACT区域*/
        C753SetOutputPortOAOI0HorizontalStart((uint16_t)startX);
        C753SetOutputPortOAOI0HorizontalEnd((uint16_t)(startX + width));
        C753SetOutputPortOAOI0VerticalStart((uint16_t)startY);
        C753SetOutputPortOAOI0VerticalEnd((uint16_t)(startY + height + 1));
//    }
    /*背景区域*/
    /*
    C753SetOutputPortOAOI0HorizontalStart(s_asScaleChInfo[iChID].wOutputStartX);
    C753SetOutputPortOAOI0HorizontalEnd((WORD)(s_asScaleChInfo[iChID].wOutputStartX + s_asScaleChInfo[iChID].wOutputWidth));
    C753SetOutputPortOAOI0VerticalStart((WORD)(s_asScaleChInfo[iChID].wOutputStartY - 1));
    C753SetOutputPortOAOI0VerticalEnd((WORD)(s_asScaleChInfo[iChID].wOutputStartY + s_asScaleChInfo[iChID].wOutputHeight - 1));
    */
    /*
    *  配置缩放系数表
    */
    C753LoadInputHorizontalShrinkLookupTable(iChID, s_abyScaleShrinkCoefficient4SymbolTable);
    C753LoadInputVerticalShrinkLookupTable(iChID, s_abyScaleShrinkCoefficient4SymbolTable);
    C753LoadOutputHorizontalZoomLookupTable(iChID, s_abyScaleZoomCoefficient4SymbolTable);
    C753LoadOutputVerticalZoomLookupTable(iChID, s_abyScaleZoomCoefficient4SymbolTable);
    /*
    *  配置图像数据存储器
    */
    m_asScaleConfig.wHorResolution = pScaleConfig->wHorResolution;
    m_asScaleConfig.wVerResolution = pScaleConfig->wVerResolution;
    m_asScaleConfig.byStandardType = pScaleConfig->byStandardType;
//    if(m_asScaleConfig.wHorResolution <= 1600)
//    {
//        if(iChID == SCAL_CHANNEL_1)
//        {
//            pAddr = (DWORD *)s_adw4FieldsRGBMemoryStartAddress1;
//        }
//        else if(iChID == SCAL_CHANNEL_2)
//        {
//            pAddr = (DWORD *)s_adw4FieldsRGBMemoryStartAddress2;
//        }
//    }
//    else
//    {
//        if(num == SCAL_CHANNEL_1)
//        {
//            pAddr = (DWORD *)s_adwHightDefine4FieldsMemoryStartAddress1;
//        }
//        else if(num == SCAL_CHANNEL_2)
//        {
//            pAddr = (DWORD *)s_adwHightDefine4FieldsMemoryStartAddress2;
//        }
//    }

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

void AppC753::initTimingIndexTable(void)
{
    int i;

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


uint16_t AppC753::getHorizontalTotal(uint16_t wHorResolution, uint16_t wVerResolution, uint16_t byStandardType)
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

uint16_t AppC753::getHorizontalStart(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
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

int16_t AppC753::getHorizontalCompensation(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
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


uint16_t AppC753::getVerticalTotal(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
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


uint16_t  AppC753::getVerticalStart(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
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



int16_t AppC753::getVerticalCompensation(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType)
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

