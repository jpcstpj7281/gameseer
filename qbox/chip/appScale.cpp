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
#include "chipInterface.h"


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



    InputInfo info;
    info.hW = 702;
    info.Vw = 480;
    info.hStar = 269;
    info.vStar = 43;
 //   info.freqHL = 0;
    m_InputInfo[TYPE_INPUT_SIZE_702_480] = info;

    info.hW = 720;
    info.Vw = 576;
    info.hStar = 269;
    info.vStar = 46;
 //   info.freqHL = 0;
    m_InputInfo[TYPE_INPUT_SIZE_720_576] = info;

    info.hW = 800;
    info.Vw = 600;
    info.hStar = 269;
    info.vStar = 29;
//    info.freqHL = 0;
    m_InputInfo[TYPE_INPUT_SIZE_800_600_60] = info;

    info.hW = 1024;
    info.Vw = 768;
    info.hStar = 268;
    info.vStar = 37;
 //   info.freqHL = 0;
    m_InputInfo[TYPE_INPUT_SIZE_1024_768_60] = info;

    info.hW = 1280;
    info.Vw = 1024;
    info.hStar = 269;
    info.vStar = 43;
 //   info.freqHL = 1;
    m_InputInfo[TYPE_INPUT_SIZE_1280_1024_60] = info;

    info.hW = 1600;
    info.Vw = 1200;
    info.hStar = 269;
    info.vStar = 51;
 //   info.freqHL = 1;
    m_InputInfo[TYPE_INPUT_SIZE_1600_1200_60] = info;

    //-----------------------------------
    info.hW = 1024;
    info.Vw = 768;
    info.hStar = 269;
    info.vStar = 33;
 //   info.freqHL = 1;
    m_InputInfo[TYPE_INPUT_SIZE_1024_768_75] = info;

    info.hW = 1280;
    info.Vw = 1024;
    info.hStar = 269;
    info.vStar = 43;
 //   info.freqHL = 1;
    m_InputInfo[TYPE_INPUT_SIZE_1280_1024_75] = info;

    info.hW = 1440;
    info.Vw = 900;
    info.hStar = 269;
    info.vStar = 33;
 //   info.freqHL = 1;
    m_InputInfo[TYPE_INPUT_SIZE_1440_900_60] = info;

    info.hW = 1600;
    info.Vw = 900;
    info.hStar = 269;
    info.vStar = 101;
//    info.freqHL = 1;
    m_InputInfo[TYPE_INPUT_SIZE_1600_900_60] = info;

    info.hW = 1920;
    info.Vw = 1080;
    info.hStar = 269;
    info.vStar = 43;
//    info.freqHL = 1;
    m_InputInfo[TYPE_INPUT_SIZE_1920_1080_60] = info;


    info.hW = 1280;
    info.Vw = 960;
    info.hStar = 269;
    info.vStar = 41;
//    info.freqHL = 1;
    m_InputInfo[TYPE_INPUT_SIZE_1280_960_60] = info;


    info.hW = 702;
    info.Vw = 480;
    info.hStar = 137;
    info.vStar = 45;
 //   info.freqHL = 0;
    m_InputInfo[TYPE_INPUT_SIZE_DEFAULT] = info;


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
    /*娴嬭瘯瀵勫瓨鍣ㄧ殑璇诲啓*/
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
        SPI_Write(0, regAddr, val1);
    }

    for(regAddr = 0x08, i = 0x08; i < 0x48; i++, regAddr++)
    {
        val1 = regAddr;
        SPI_Read(0, regAddr,val2);
        if(val2 != val1)
        {
            //SPCMsgErr("can not read bank register value[val1=0x%02x val2=0x%02x addr=0x%02x]\n", val1, val2, regAddr, 0);
        	printf("can not read bank register value[val_in=0x%02x val_out=0x%02x addr=0x%02x]\n", val1, val2, regAddr);
            return ;
        }
    }
    /*杞欢澶嶄綅*/
    C753Reset(0x01);
    C753SetDDRControl(0x80);
    /*C753鍐呭瓨鎺у埗鍣ㄥ垵濮嬪寲*/
    C753SetMemoryControl(0x28);
    /*鑷冲皯寤舵椂200us*/

    for(i = 0; i < 40000; i++);
    C753SetMemoryControl(0x29);
    /*鑷冲皯寤舵椂200us*/
    for(i = 0; i < 80000; i++);

    /*閰嶇疆鍐呭瓨鎺у埗鍣ㄥ瘎瀛樺櫒*/
    C753SetDLLControl0(0xaa);
    C753SetDLLControl1(0xaa);
    C753SetDLLControl2(0xdd);
    C753SetDLLControl3(0xdd);
    C753SetDLLControl4(0xdd);
    C753SetDLLControl5(0xdd);
    C753SetDLLControl6(0x00);
    C753SetDLLControl7(0x00);
    C753SetDLLControl8(0x02);

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

    /*閲嶆柊璁剧疆绐楀彛澶у皬鏃剁獥鍙ｅ凡缁忔墦寮��閬�/
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

    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
        C753SetMainControl(iChID,0x03);

        uint8_t value1 = 0;
        C753GetMainControl(iChID,value1);
        while(value1 != 0x03)
        {
        	taskDelay(50);
        	debug_msg("retry showWnd iChid=%d,value=%02x\n",iChID,value1);
        	C753SetMainControl(iChID,0x03);
        	C753GetMainControl(iChID,value1);

        }

    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
    	C753SetMainControl(iChID,0x07);
        uint8_t value2 = 0;
        C753GetMainControl(iChID,value2);
        while(value2 != 0x07)
        {
        	taskDelay(50);
        	debug_msg("retry showWnd iChid=%d,value=%02x\n",iChID,value2);
        	C753SetMainControl(iChID,0x07);
        	C753GetMainControl(iChID,value2);

        }

    }

    debug_msg("showWnd iChid=%d\n",iChID);


}

void AppScale::hideWnd(uint32_t iChID)
{
    /*锟斤拷锟截革拷通锟斤拷*/
    if(iChID == C753_OUTPUT_CHANNEL_1)
    {
       C753SetMainControl(iChID,0x02);
       uint8_t value = 0;
       C753GetMainControl(iChID,value);
       while(value != 0x02)
       {
    	   taskDelay(50);
    	   debug_msg("retry hideWnd iChid=%d,value=%02x\n",iChID,value);
    	   C753SetMainControl(iChID,0x02);
    	   C753GetMainControl(iChID,value);

       }

    }
    else if(iChID == C753_OUTPUT_CHANNEL_2)
    {
        C753SetMainControl(iChID,0x06);
        uint8_t value = 0;
        C753GetMainControl(iChID,value);
        while(value != 0x06)
        {
           taskDelay(50);
           debug_msg("retry hideWnd iChid=%d,value=%02x\n",iChID,value);
     	   C753SetMainControl(iChID,0x06);
     	   C753GetMainControl(iChID,value);

        }
    }
    debug_msg("hideWnd iChid=%d\n",iChID);
}


void AppScale::openChannel(uint32_t iChID)
{
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

}

void AppScale::initTest1024()
{
    int i;
    uint32_t iChID=1;

    debug_msg("initTest1024\n");


    C753SetRegisterValueTransferControl(0x0);
    /*
    *  閰嶇疆杈撳叆閮ㄥ垎瀵勫瓨鍣�
    */
    /*RGB 30-bit 杈撳叆*/
    C753SetInputFormatControl(iChID, 0x00);
    /*IFLD 0鍒�寰幆*/

    C753SetInputPortSyncControl(iChID, 0x02);

    C753SetInputFieldRecognitionControl(iChID, 0x00);
    /*PIACT鍖哄煙澶栧浘鍍忎负0 PIACT POL*/
    C753SetInputDigitalInterfaceControl(iChID, 0x00);
    /*
    *  閰嶇疆杈撳嚭閮ㄥ垎瀵勫瓨鍣�
    */
    C753SetOutputPortSyncControl(0x2359);


    C753SetFieldPropagationDelay1(0x04);

    C753SetFieldPropagationDelay2(0x04);
    /*鑳屾櫙鍥惧儚*/
    C753SetOutputBackground0(0x00ff00);
    C753SetOutputBackground1(0x0000ff);
    /*POCLKO 杈撳嚭浣胯兘*/
    C753SetPOCLKControl(0x03);
    /*POCLK PLL閰嶇疆*/
    C753SetPOCLKPLLControl(0x81);
    C753SetPOCLKReferenceDividing(0x07);
    C753SetPOCLKFeedbackDividing(0x0f);

    C753SetIPCLKPLLControl(0x01);
    C753SetIPCLKReferenceDividing(0x01);
    C753SetIPCLKFeedbackDividing(0x03);

    debug_msg("initHardware PCL OK \n!");


    C753SetOutputHorizontalSync(0x053e);
    C753SetOutputVerticalSync(0x0324);




    /*杈撳嚭鍥惧儚鍖哄煙*/
    C753SetOutputPortACTHorizontalStart(iChID, (uint16_t)163);
    C753SetOutputPortACTHorizontalWidth(iChID, 1024);
    C753SetOutputPortACTVerticalStart(iChID, (uint16_t)34);
    C753SetOutputPortACTVerticalWidth(iChID,768);


    debug_msg("initHardware OUTPUT PORT OK \n!");






}

void AppScale::initTest1400()
{
    int i;
    uint32_t iChID=1;

    debug_msg("initTest1400\n");


    C753SetRegisterValueTransferControl(0x0);
    /*
    *  閰嶇疆杈撳叆閮ㄥ垎瀵勫瓨鍣�
    */
    /*RGB 30-bit 杈撳叆*/
    C753SetInputFormatControl(iChID, 0x00);
    /*IFLD 0鍒�寰幆*/

    C753SetInputPortSyncControl(iChID, 0x02);

    C753SetInputFieldRecognitionControl(iChID, 0x00);
    /*PIACT鍖哄煙澶栧浘鍍忎负0 PIACT POL*/
    C753SetInputDigitalInterfaceControl(iChID, 0x00);
    /*
    *  閰嶇疆杈撳嚭閮ㄥ垎瀵勫瓨鍣�
    */
    C753SetOutputPortSyncControl(0x2341);


    C753SetFieldPropagationDelay1(0x04);

    C753SetFieldPropagationDelay2(0x04);
    /*鑳屾櫙鍥惧儚*/
    C753SetOutputBackground0(0x00ff00);
    C753SetOutputBackground1(0x0000ff);
    /*POCLKO 杈撳嚭浣胯兘*/
    C753SetPOCLKControl(0x03);
    /*POCLK PLL閰嶇疆*/
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
    /*杈撳嚭鍥惧儚鍖哄煙*/
    C753SetOutputPortACTHorizontalStart(iChID, (uint16_t)341);
    C753SetOutputPortACTHorizontalWidth(iChID, 1024);
    C753SetOutputPortACTVerticalStart(iChID, (uint16_t)135);
    C753SetOutputPortACTVerticalWidth(iChID,768);


    debug_msg("initHardware OUTPUT PORT OK \n!");


}

void AppScale::initScal(uint32_t iChID,uint32_t hInput,uint32_t vInput,uint32_t hOutput,uint32_t vOutput)
{
	debug_msg("initScal iChid=%d",iChID);
	uint32_t tempVsOutPut = vOutput +3;
	uint32_t tempVsInPut = vInput +1;

	hideWnd(iChID);
    C753SetOutputVerticalEnlargementControl(iChID, 0x00);
    /*鍏抽棴缂╁皬妯″潡*/
    C753SetInputVerticalShrinkControl(iChID, 0x00);

    C753SetInputPortACTVerticalWidth(iChID,tempVsInPut);
    C753SetOutputPortACTVerticalWidth(iChID,vInput);

    /*鍏抽棴缂╁皬妯″潡*/
     C753SetInputHorizontalShrinkControl(iChID, 0x00);
     /*鍏抽棴鏀惧ぇ妯″潡*/
     C753SetOutputHorizontalEnlargementControl(iChID, 0x00);

     C753SetInputPortACTHorizontalWidth(iChID,hInput);
     C753SetOutputPortACTHorizontalWidth(iChID,hInput);



	debug_msg("initScal ichid=%d,hInput:%d,vInput:%d,hOutput:%d,vOutput:%d\n",iChID,hInput,vInput,hOutput,vOutput);
	if(hInput > hOutput)
	{
		debug_msg("hs shrinkScale \n!");

		uint16_t shrinkScale= ((hOutput-1) * 65536 / (hInput-1) ) + 1;

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

        /*鍏抽棴鏀惧ぇ妯″潡*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x00);
        C753SetInputHorizontalShrinkInitialValue(iChID, 0x00);



        C753SetInputHorizontalShrinkScale(iChID,shrinkScale);
//    	debug_msg("HorizontalShrinkScale:0x%X,%d\n",shrinkScale,shrinkScale);


        C753SetInputPortACTHorizontalWidth(iChID,hOutput);
        C753SetOutputPortACTHorizontalWidth(iChID, hOutput);

	}
	else if(hInput < hOutput)
	{
		debug_msg("hs zoomScale \n!");
		uint16_t zoomScale= hInput * 65536 / (hOutput );
        /*6-symbol LUT*/
		C753SetOutputHorizontalEnlargementControl(iChID, 0x07);
        C753SetOutputHorizontalZoomScale(iChID,zoomScale);

	}
	else
	{
		debug_msg("hs nomal \n!");
        /*鍏抽棴缂╁皬妯″潡*/
        C753SetInputHorizontalShrinkControl(iChID, 0x00);
        /*鍏抽棴鏀惧ぇ妯″潡*/
        C753SetOutputHorizontalEnlargementControl(iChID, 0x00);

        C753SetInputPortACTHorizontalWidth(iChID,hInput);
        C753SetOutputPortACTHorizontalWidth(iChID, hOutput);
	}


	if(vInput > vOutput)
	{
		debug_msg("vs shrinkScale \n!");

        uint16_t shrinkScale= ((tempVsOutPut-1) * 65536 /(tempVsInPut-2)) + 1;

//        uint16_t shrinkScale= ((tempVsOutPut-1) * 65536 /(tempVsInPut)) + 1;

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
        C753LoadInputVerticalShrinkLookupTable(iChID, lut);
        C753SetInputShrinkCompensationControl(iChID, 0x00);
        C753SetInputVerticalShrinkCompensation(iChID, 0x00);

        /*6-symbol LUT*/
        C753SetInputVerticalShrinkControl(iChID, 0x07);

        /*鍏抽棴鏀惧ぇ妯″潡*/
        C753SetOutputVerticalEnlargementControl(iChID, 0x00);
        C753SetInputVerticalShrinkInitialValue(iChID, 0x00);


        C753SetInputVerticalShrinkScale(iChID, shrinkScale);
//        debug_msg("VerticalShrinkScale:0x%X,%d\n",shrinkScale,shrinkScale);


        C753SetInputPortACTVerticalWidth(iChID,tempVsInPut);
        C753SetOutputPortACTVerticalWidth(iChID,tempVsOutPut);

//        C753SetInputPortACTVerticalStart(iChID, m_inputOffsetVS+1);

//       debug_msg("vs shrinkScale vs=%d \n!",m_inputOffsetVS+1);

	}
	else if(vInput < vOutput)
	{
		debug_msg("vs zome \n!");
		uint16_t zoomScale= tempVsInPut * 65536 / (tempVsOutPut + 1);
        /*
        *  閰嶇疆鏀惧ぇ瀵勫瓨鍣�
        */
        /*6-symbol LUT*/
        C753SetOutputVerticalEnlargementControl(iChID, 0x07);
        C753SetOutputVerticalZoomScale(iChID, zoomScale);
        C753SetOutputPortACTVerticalWidth(iChID,tempVsOutPut);

        uint16_t tempVStar = 0;

        C753GetOutputPortACTVerticalStart(iChID,tempVStar);
        C753SetOutputPortACTVerticalStart(iChID,tempVStar-1);
        debug_msg("vs zome get tempVStar=%d \n!",tempVStar-1);

	}
	else
	{
		debug_msg("vs nomal \n!");
        C753SetOutputVerticalEnlargementControl(iChID, 0x00);
        /*鍏抽棴缂╁皬妯″潡*/
        C753SetInputVerticalShrinkControl(iChID, 0x00);

        C753SetInputPortACTVerticalWidth(iChID,tempVsInPut);
        C753SetOutputPortACTVerticalWidth(iChID,tempVsOutPut);
	}

//	showWnd(iChID);
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
	debug_msg("initCLK OK !");
}

void AppScale::initCLK()
{
	/*POCLKO 杈撳嚭浣胯兘*/
	C753SetPOCLKControl(0x03);
	/*POCLK PLL閰嶇疆*/
	C753SetPOCLKPLLControl(0x81);
	C753SetPOCLKReferenceDividing(0x07);
	C753SetPOCLKFeedbackDividing(0x0f);


	C753SetIPCLKPLLControl(0x01);
	C753SetIPCLKReferenceDividing(0x01);
	C753SetIPCLKFeedbackDividing(0x03);



    C753SetFieldPropagationDelay1(0x04);

    C753SetFieldPropagationDelay2(0x04);

	debug_msg("initChipDDR OK !");
}

void AppScale::initScaleTable(uint32_t channelID)
{
	C753LoadInputHorizontalShrinkLookupTable(channelID, s_abyScaleShrinkCoefficient6SymbolTable);
	C753LoadInputVerticalShrinkLookupTable(channelID, s_abyScaleShrinkCoefficient6SymbolTable);
	C753LoadOutputHorizontalZoomLookupTable(channelID, s_abyScaleZoomCoefficient6SymbolTable);
	C753LoadOutputVerticalZoomLookupTable(channelID, s_abyScaleZoomCoefficient6SymbolTable);

	debug_msg("initScaleTable channelID=%d OK !",channelID);
}


void AppScale::initMemory()
{

//	  /*OSFLD0      OSFLD1      OSFLD2      OSFLD3*/
//	  0x00C00000, 0x00000000, 0x00400000, 0x00800000,
//	  /*ISFLD0      ISFLD1      ISFLD2      ISFLD3*/
//	  0x00000000, 0x00400000, 0x00800000, 0x00C00000
//	  /*OSFLD0      OSFLD1      OSFLD2      OSFLD3*/
//	  0x01C00000, 0x01000000, 0x01400000, 0x01800000,
//	  /*ISFLD0      ISFLD1      ISFLD2      ISFLD3*/
//	  0x01000000, 0x01400000, 0x01800000, 0x01C00000
//	7FBC00


	C753SetOutputField0MemoryReadStartAddress(1, 0x00c00000);
	C753SetOutputField1MemoryReadStartAddress(1, 0x00000000);
	C753SetOutputField2MemoryReadStartAddress(1, 0x00400000);
	C753SetOutputField3MemoryReadStartAddress(1, 0x00800000);
	C753SetInputField0MemoryWriteStartAddress(1, 0x00c00000);
	C753SetInputField1MemoryWriteStartAddress(1, 0x00000000);
	C753SetInputField2MemoryWriteStartAddress(1, 0x00400000);
	C753SetInputField3MemoryWriteStartAddress(1, 0x00800000);


	C753SetOutputField0MemoryReadStartAddress(2, 0x01c00000);
	C753SetOutputField1MemoryReadStartAddress(2, 0x01000000);
	C753SetOutputField2MemoryReadStartAddress(2, 0x01400000);
	C753SetOutputField3MemoryReadStartAddress(2, 0x01800000);
	C753SetInputField0MemoryWriteStartAddress(2, 0x01c00000);
	C753SetInputField1MemoryWriteStartAddress(2, 0x01000000);
	C753SetInputField2MemoryWriteStartAddress(2, 0x01400000);
	C753SetInputField3MemoryWriteStartAddress(2, 0x01800000);
}

void AppScale::initMemoryLineFeedWidth(uint32_t channelID)
{
	C753SetMemoryReadLinefeedWidth(channelID, 0x10);
	C753SetMemoryWriteLinefeedWidth(channelID, 0x10);

	debug_msg("initMemoryLineFeedWidth channelID=%d OK !",channelID);
}

void AppScale::selectOutPutModel(uint32_t model)
{
	if(model == TYPE_OUTPUT_ACT)
	{
		C753SetOutputPortSyncControl(0x2341);
		debug_msg("OutPut Model ACT !");
	}
	else if(model == TYPE_OUTPUT_AOI0)
	{
		C753SetOutputPortSyncControl(0x2351);
		debug_msg("OutPut Model AOI0 !");
	}
	else if(model == TYPE_OUTPUT_AOI1)
	{
		C753SetOutputPortSyncControl(0x2359);
		debug_msg("OutPut Model AOI1 !");
	}


}


void  AppScale::setOutputBGColor(uint32_t bg0Color,uint32_t bg1Color)
{
	C753SetOutputBackground0(bg0Color);
	C753SetOutputBackground1(bg1Color);
	debug_msg("setOutputBGColor bg0Color=%X,bg1Color=%X !",bg0Color,bg1Color);
}

void AppScale::setOutputBGSize(uint32_t type)
{
	 DriverChipICS307 s_ics307;

	 switch(type)
	 {
		 case TYPE_OUTPUT_SIZE_1024_768:
		 {
			 s_ics307.setPOCLK(ICS307_FREQUENCY_65000KHZ);
			 C753SetOutputHorizontalSync(0x053e);
		     C753SetOutputVerticalSync(0x0324);
     	     C753SetHorizontalSyncResetDelay(20);
		     C753SetVerticalSyncResetDelay(4);


		     debug_msg("setOutputSize 1024 X 768 @60Hz !");
			 break;
		 }

		 case TYPE_OUTPUT_SIZE_1400_1050:
		 {
			 s_ics307.setPOCLK(ICS307_FREQUENCY_121750KHZ);
			 C753SetOutputHorizontalSync(0x0746);
			 C753SetOutputVerticalSync(0x043f);
      	     C753SetHorizontalSyncResetDelay(20);
 		     C753SetVerticalSyncResetDelay(4);


			 debug_msg("setOutputSize 1400 X 1050 @60Hz !");
			 break;
		 }

		 default:
			 debug_msg("setOutputSize unknow !");
			 break;

	 }
}


void AppScale::setOutputImage(uint32_t model,uint32_t size)
{
	selectOutPutModel(model);
	setOutputBGSize(size);

	if(model == TYPE_OUTPUT_ACT)
	{

		debug_msg("Please set ACT !");
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
			m_verFp = 34;

		}
		else if(size == TYPE_OUTPUT_SIZE_1400_1050)
		{
			 C753SetOutputPortOAOI0HorizontalStart((uint16_t)241);
			 C753SetOutputPortOAOI0HorizontalEnd((uint16_t)1640);
			 C753SetOutputPortOAOI0VerticalStart((uint16_t)35);
			 C753SetOutputPortOAOI0VerticalEnd((uint16_t)1085);

			 m_horFp = 241;
			 m_verFp = 34;

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
			m_verFp = 34;
		}
		else if(size == TYPE_OUTPUT_SIZE_1400_1050)
		{
			C753SetOutputPortOAOI1HorizontalStart((uint16_t)241);
			C753SetOutputPortOAOI1HorizontalEnd((uint16_t)1640);
			C753SetOutputPortOAOI1VerticalStart((uint16_t)35);
			C753SetOutputPortOAOI1VerticalEnd((uint16_t)1085);

			m_horFp = 241;
			m_verFp = 34;
		}
	}
}

void AppScale::setOutputChannelACT(uint32_t iChID,uint16_t hw,uint16_t vw,uint16_t hs,uint16_t vs)
{
	debug_msg("setOutputChannelACT chid=%d  hw:%d,vw:%d,hs=%d,vs=%d",iChID,hw,vw,hs,vs);

	uint16_t tempHs = hs + m_horFp;
	uint16_t tempVs = vs + m_verFp;
	debug_msg("setOutputChannelACT chid=%d  hw:%d,vw:%d,tempHs=%d,tempVs=%d",iChID,hw,vw,tempHs,tempVs);

    C753SetOutputPortACTHorizontalStart(iChID, (uint16_t)tempHs);
    C753SetOutputPortACTHorizontalWidth(iChID, hw);
    C753SetOutputPortACTVerticalStart(iChID, (uint16_t)tempVs);
    C753SetOutputPortACTVerticalWidth(iChID,vw+3);
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
	debug_msg("setInputChannelACT chid=%d  hw:%d,vw:%d,hs=%d,vs=%d",iChID,hw,vw,hs,vs);
	C753SetInputPortACTHorizontalStart(iChID, (uint16_t)hs);
	m_inputOffsetHS = hs;
	m_inputOffsetVS = vs;
	C753SetInputPortACTHorizontalWidth(iChID,hw);
	C753SetInputPortACTVerticalStart(iChID, (uint16_t)vs);
	C753SetInputPortACTVerticalWidth(iChID,vw);
}

void AppScale::moveChannelInput(uint32_t channel,int hPoint,int vPoint)
{
	uint16_t temp = 0;

	debug_msg("moveInput  hPoint:%d,vPoint:%d",hPoint,vPoint);
	C753GetInputPortACTHorizontalStart(channel,temp);
	debug_msg("moveInput src  oldHS:%d,newHS:%d",temp, temp + hPoint);
	temp = m_inputOffsetHS + hPoint;
	C753SetInputPortACTHorizontalStart(channel,temp);


	C753GetInputPortACTVerticalStart(channel,temp);
	temp = m_inputOffsetVS + vPoint;
	C753SetInputPortACTVerticalStart(channel,temp);
	debug_msg("moveInput src  oldVS:%d,newVS:%d",temp, temp + vPoint);
}

void AppScale::moveChannelOutput(uint32_t channel,int hPoint,int vPoint)
{
//	uint16_t tempHs = hPoint + m_horFp;
//	uint16_t tempVs = vPoint + m_verFp;

	uint16_t temp = 0;
	debug_msg("moveOutput  hPoint:%d,vPoint:%d",hPoint,vPoint);

	C753GetOutputPortACTHorizontalStart(channel,temp);
	debug_msg("moveOutput src  oldHS:%d,newHS:%d",temp,temp+ hPoint);
	temp = temp + hPoint;

	C753SetOutputPortACTHorizontalStart(channel,temp);


	C753GetOutputPortACTVerticalStart(channel,temp);
	debug_msg("moveOutput src  oldVS:%d,newVS:%d",temp,temp+ vPoint);
	C753SetOutputPortACTVerticalStart(channel,temp);


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

//	setChannelMH(chId,m_InputInfo[model].freqHL);

		debug_msg("setInputSignalModel  chId:%d,model:%d",chId,model);
		setInputChannelACT(chId,m_InputInfo[model].hW,m_InputInfo[model].Vw,m_InputInfo[model].hStar,m_InputInfo[model].vStar);

		uint16_t outHw =0;
		uint16_t outVw =0;


		C753GetOutputPortACTHorizontalWidth(chId,outHw);
		C753GetOutputPortACTVerticalWidth(chId,outVw);

		debug_msg("setInputSignalModel getOutput  chId:%d,outHw:%d,outVw:%d",chId,outHw,outVw);

		C753SetOutputPortACTHorizontalStart(chId,m_horFp);
		C753SetOutputPortACTVerticalStart(chId,m_verFp);


		initScal(chId,m_InputInfo[model].hW,m_InputInfo[model].Vw,outHw,outVw);
		C753SetInputPortACTHorizontalStart(chId,m_InputInfo[model].hStar);
		C753SetInputPortACTVerticalStart(chId,m_InputInfo[model].vStar);

}

void AppScale::setOSDSize(uint32_t wide,uint32_t high)
{

	debug_msg("setOSDSize  wide:%d,high:%d",wide,high);

	C753SetOSDACTHorizontalWidth(wide);
	C753SetOSDACTVerticalWidth(high);

}

void AppScale::setOSDPosition(uint32_t posX,uint32_t posY)
{

	debug_msg("setOSDSize  posX:%d,posY:%d",posX,posY);

	C753SetOSDACTHorizontalStart(posX);
	C753SetOSDACTVerticalStart(posY);

}

void AppScale::dumpLut()
{
	debug_msg("dumpLut!");
	uint8_t h[24]={0};
	uint8_t v[24]={0};


	C753DumpLoadInputHorizontalShrinkLookupTable(1,h);
	C753DumpLoadInputVerticalShrinkLookupTable(1,v);

	printf("\n Horizontal LUT\n");
	for(int i=0;i<24;i++)
	{
		printf("%02X ",h[i]);
	}
	printf("\n tVertical LUT\n");
	for(int i=0;i<24;i++)
	{
		printf("%02X ",v[i]);
	}
	printf("\n");
}







