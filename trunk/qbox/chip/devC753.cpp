
/*
 * devDriverChip753::C753.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "devC753.h"
#include "devC753Addr.h"


using namespace chip;


DriverChip753::DriverChip753()
{

}

DriverChip753::~DriverChip753()
{

}


/*Basic function*/
void DriverChip753::C753SetBankRegister(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,byVal);
}
void DriverChip753::C753GetBankRegister(uint8_t &byVal)
{
	SPI_Read(0,REG_C753_BSC_RGBNK,byVal);
}

//void DriverChip753::C753SetMainControl(uint16_t wVal)
void DriverChip753::C753SetMainControl(uint32_t iCh,uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_MCT_L, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_MCT_H, byVal);
    }
}

void DriverChip753::C753GetMainControl(uint32_t iCh,uint8_t &byVal)
{
	if(iCh == C753_INPUT_CHANNEL_1)
	{
		SPI_Read(0,REG_C753_BSC_MCT_L, byVal);
    }
	else if(iCh == C753_INPUT_CHANNEL_2)
	{
		SPI_Read(0,REG_C753_BSC_MCT_H, byVal);
	}
}

void DriverChip753::C753SetDDRControl(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_DDRCT, byVal);
}

void DriverChip753::C753SetRegisterValueTransferControl(uint16_t wVal)
{
	SPI_Write(0,REG_C753_BSC_RTCT_L, wVal&0x00ff);
	SPI_Write(0,REG_C753_BSC_RTCT_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetMemoryControl(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_MEMCT, byVal);
}
void DriverChip753::C753Reset(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_RSTCT,byVal);
}

/*Bank0 function*/
void DriverChip753::C753SetOutputPortSyncControl(uint16_t wVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_OSYCT_L, (wVal&0x00ff));
	SPI_Write(0,REG_C753_B0_OSYCT_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetOutputHorizontalSync(uint16_t wVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_OHCYCL_L, (wVal&0x00ff));
	SPI_Write(0,REG_C753_B0_OHCYCL_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetOutputVerticalSync(uint16_t wVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_OVCYCL_L, (wVal&0x00ff));
	SPI_Write(0,REG_C753_B0_OVCYCL_H, (wVal&0xff00)>>8);
}


void DriverChip753::C753GetOutputPortSyncControl(uint16_t &wVal)
{
	  uint16_t val=0;
	  uint8_t value1 = 0;
	  uint8_t value2 = 0;
	  SPI_Write(0,REG_C753_BSC_RGBNK,0);

	  SPI_Read(0,REG_C753_B0_OSYCT_L,value1);
	  SPI_Read(0,REG_C753_B0_OSYCT_H,value2);

	  val = value2;
	  val = val<<8 |value1;
}

void DriverChip753::C753SetHorizontalSyncResetDelay(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_OHSCT, byVal);
}

void DriverChip753::C753SetVerticalSyncResetDelay(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_OVSCT, byVal);
}

void DriverChip753::C753SetForcedSyncResetDelay(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_SYRDLY, byVal);
}
void DriverChip753::C753SetForcedSyncResetControl(uint16_t wVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_OVCYCLMIN_L, (wVal&0x00ff));
	SPI_Write(0,REG_C753_B0_OVCYCLMIN_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetFieldInterlockTransferControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_FLDRTCT, byVal);
}

void DriverChip753::C753SetFieldPropagationDelay1(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_FLDDLY1, byVal);
}
void DriverChip753::C753SetFieldPropagationDelay2(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_FLDDLY2, byVal);
}
void DriverChip753::C753SetOutputSignalSwap(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSWP, byVal);
}

void DriverChip753::C753SetPOCLKControl(uint8_t byVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,0);
	SPI_Write(0,REG_C753_B0_POCLKCT, byVal);
}

void DriverChip753::C753SetScalingWidthControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_SCWCT, byVal);
}
void DriverChip753::C753SetInterlaceOutputControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OINTCT, byVal);
}

void DriverChip753::C753SetOverlayControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OVLYCTL, byVal);
}

void DriverChip753::C753GetOverlayControl(uint8_t &byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Read(0,REG_C753_B0_OVLYCTL,byVal);
}

void DriverChip753::C753Set2ScreenBlendingAlphaCoefficient(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_GAIN3, byVal);
}

void DriverChip753::C753Set2ScreenBlendingBetaCoefficient(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_GAIN4, byVal);

}
void DriverChip753::C753SetOSDMode(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDMODE, byVal);
}
void DriverChip753::C753SetOSDControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDCT, byVal);
}
void DriverChip753::C753SetOSDPenetrationColor(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BOTRANS, byVal);
}
void DriverChip753::C753SetOSDWriteInhibitColor(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BOWIHN, byVal);
}
void DriverChip753::C753SetOSDFillColor(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDFILL, byVal);
}
void DriverChip753::C753SetBlinkingTime(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BLINKTIME, byVal);
}

void DriverChip753::C753SetBlinkCycle(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BLINKCYCL, byVal);
}

void DriverChip753::C753SetOSDACTHorizontalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDACTHST_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_OSDACTHST_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOSDACTHorizontalWidth(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDACTHW_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_OSDACTHW_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOSDACTVerticalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDACTVST_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_OSDACTVST_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetOSDACTVerticalWidth(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDACTVW_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_OSDACTVW_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetOSDStartAddress(uint32_t dwVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDSAD_0, (dwVal&0x000000ff));
    SPI_Write(0,REG_C753_B0_OSDSAD_1, (dwVal&0x0000ff00)>>8);
    SPI_Write(0,REG_C753_B0_OSDSAD_2, (dwVal&0x00ff0000)>>16);
    SPI_Write(0,REG_C753_B0_OSDSAD_3, (dwVal&0xff000000)>>24);
}

void DriverChip753::C753SetOSDMemoryLinefeedWidth(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_OSDMWI, byVal);
}

void DriverChip753::C753SetCharacterBufferHorizontalStart(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CBUFHST, byVal);
}

void DriverChip753::C753SetCharacterBufferHorizontalWidth(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CBUFHW, byVal);
}

void DriverChip753::C753SetCharacterBufferVerticalStart(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CBUFVST, byVal);
}
void DriverChip753::C753SetCharacterBufferVerticalWidth(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CBUFVW, byVal);
}
void DriverChip753::C753SetBitBLTHorizontalWidth(uint8_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BBACTHW_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_BBACTHW_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetBitBLTVerticalWidth(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BBACTVW_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_BBACTVW_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetCPUReadAddress(uint32_t dwVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CPURAD_0, (dwVal&0x000000ff));
    SPI_Write(0,REG_C753_B0_CPURAD_1, (dwVal&0x0000ff00)>>8);
    SPI_Write(0,REG_C753_B0_CPURAD_2, (dwVal&0x00ff0000)>>16);
    SPI_Write(0,REG_C753_B0_CPURAD_3, (dwVal&0xff000000)>>24);
}
void DriverChip753::C753SetCPUWriteAddress(uint32_t dwVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CPUWAD_0, (dwVal&0x000000ff));
    SPI_Write(0,REG_C753_B0_CPUWAD_1, (dwVal&0x0000ff00)>>8);
    SPI_Write(0,REG_C753_B0_CPUWAD_2, (dwVal&0x00ff0000)>>16);
    SPI_Write(0,REG_C753_B0_CPUWAD_3, (dwVal&0xff000000)>>24);
}

void DriverChip753::C753SetCPUData(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CPUDT, byVal);
}

void DriverChip753::C753GetCPUData(uint8_t &byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Read(0,REG_C753_B0_CPUDT,byVal);
}

void DriverChip753::C753WritePixel(uint8_t byRed, uint8_t byGreen, uint8_t byBlue, uint8_t byDump)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CPUDT, byRed);
    SPI_Write(0,REG_C753_B0_CPUDT, byGreen);
    SPI_Write(0,REG_C753_B0_CPUDT, byBlue);
    SPI_Write(0,REG_C753_B0_CPUDT, byDump);
}

void DriverChip753::C753WriteN1BitPixels(uint16_t wNPixels, RGBQUAD *pC753Plt, uint8_t **ppbyMap, uint8_t *pbyBuf)
{
    uint16_t i, j;
    register RGBQUAD *pPlt;
    register uint8_t *pbySrc;
    register uint8_t val;

    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    for(i = 0; i < wNPixels; i += 8)
    {
        val = *pbyBuf++;
        pbySrc = ppbyMap[val];
        for(j = 0; j < 8; j += 2)
        {
            val = *pbySrc++;
            pPlt = pC753Plt + val;
            SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbRed);
            SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbGreen);
            SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbBlue);
            SPI_Write(0,REG_C753_B0_CPUDT, 0x00);
            val = *pbySrc++;
            pPlt = pC753Plt + val;
            SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbRed);
            SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbGreen);
            SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbBlue);
            SPI_Write(0,REG_C753_B0_CPUDT, 0x00);
        }
    }
}

void DriverChip753::C753WriteN8BitPixels(uint16_t wNPixels, RGBQUAD *pC753Plt, uint8_t *pbyBuf)
{
	uint16_t i;
    register RGBQUAD *pPlt;
    register uint8_t val;

    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    for(i = 0; i < wNPixels; i += 2)
    {
        val = *pbyBuf++;
        pPlt = pC753Plt + val;
        SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbRed);
        SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbGreen);
        SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbBlue);
        SPI_Write(0,REG_C753_B0_CPUDT, 0x00);
        val = *pbyBuf++;
        pPlt = pC753Plt + val;
        SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbRed);
        SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbGreen);
        SPI_Write(0,REG_C753_B0_CPUDT, pPlt->rgbBlue);
        SPI_Write(0,REG_C753_B0_CPUDT, 0x00);
    }
}

void DriverChip753::C753WriteN24BitPixels(uint16_t wNPixels, uint8_t *pbyBuf)
{
    uint16_t i;
    register uint8_t r, g, b;

    SPI_Write(0,REG_C753_BSC_RGBNK,0);

    for(i = 0; i < wNPixels; i += 2)
    {
        b = *pbyBuf++;
        g = *pbyBuf++;
        r = *pbyBuf++;
        SPI_Write(0,REG_C753_B0_CPUDT, r);
        SPI_Write(0,REG_C753_B0_CPUDT, g);
        SPI_Write(0,REG_C753_B0_CPUDT, b);
        SPI_Write(0,REG_C753_B0_CPUDT, 0x00);
        b = *pbyBuf++;
        g = *pbyBuf++;
        r = *pbyBuf++;
        SPI_Write(0,REG_C753_B0_CPUDT, r);
        SPI_Write(0,REG_C753_B0_CPUDT, g);
        SPI_Write(0,REG_C753_B0_CPUDT, b);
        SPI_Write(0,REG_C753_B0_CPUDT, 0x00);
    }

}
void DriverChip753::C753ReadN24BitPixels(uint16_t wNPixels, uint8_t *pbyBuf)
{
    uint16_t i;
    register uint8_t r, g, b;

    SPI_Write(0,REG_C753_BSC_RGBNK,0);

    for(i = 0; i < wNPixels; i++)
    {
    	SPI_Write(0,REG_C753_B0_CPUDT,r);
    	SPI_Write(0,REG_C753_B0_CPUDT,g);
    	SPI_Write(0,REG_C753_B0_CPUDT,b);
        /*dump*/
//        C753GetReg(REG_C753_B0_CPUDT);
        *pbyBuf++ = b;
        *pbyBuf++ = g;
        *pbyBuf++ = r;
    }
}
void DriverChip753::C753SetCharacterBufferAddress(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CBUFAD_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_CBUFAD_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetCharacterBufferData(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_CBUFDT, byVal);
}
void DriverChip753::C753SetPaletteAddress(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_PLTAD, byVal);
}
void DriverChip753::C753SetPaletteData(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_PLTDT, byVal);
}

void DriverChip753::C753GetBitmapOSDStatus(uint8_t &byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Read(0,REG_C753_B0_BOSTAT,byVal);
}
void DriverChip753::C753SetBitmapOSD90DegreeRotation(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BOROT, byVal);
}
void DriverChip753::C753SetBitBLTWriteLinefeedWidth(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BBWMWI, byVal);
}

void DriverChip753::C753SetBitBLTReadLinefeedWidth(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BBRMWI, byVal);
}

void DriverChip753::C753SetBitmapOSDAccessControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BOACCT, byVal);
}
void DriverChip753::C753SetMemoryProtect(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_MPROTECT_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_MPROTECT_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetBitBLTTriggerVSDelay(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_BBVDLY, byVal);
}
void DriverChip753::C753SetInterruptEnable(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_INTEN_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_INTEN_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetInterruptReset(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,0);
    SPI_Write(0,REG_C753_B0_INTRST_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B0_INTRST_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetTESTDT(uint8_t byVal){}
void DriverChip753::C753SetTESTAD(uint8_t byVal){}
void DriverChip753::C753SetTestG(uint8_t byVal){}

/*Bank 1 function*/
void DriverChip753::C753SetOutputPortOAOI0HorizontalStart(uint16_t wVal)
{
	SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI0HST_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI0HST_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetOutputPortOAOI0HorizontalEnd(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI0HEND_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI0HEND_H, (wVal&0xff00)>>8);

}
void DriverChip753::C753SetOutputPortOAOI0VerticalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI0VST_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI0VST_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetOutputPortOAOI0VerticalEnd(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI0VEND_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI0VEND_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI1HorizontalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI1HST_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI1HST_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI1HorizontalEnd(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI1HEND_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI1HEND_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI1VerticalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI1VST_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI1VST_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI1VerticalEnd(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI1VEND_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI1VEND_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI2HorizontalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI2HST_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI2HST_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI2HorizontalEnd(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI2HEND_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI2HEND_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI2VerticalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI2VST_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI2VST_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI2VerticalEnd(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI2VEND_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI2VEND_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI3HorizontalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI3HST_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI3HST_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI3HorizontalEnd(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI3HEND_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI3HEND_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI3VerticalStart(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI3VST_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI3VST_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetOutputPortOAOI3VerticalEnd(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OAOI3VEND_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OAOI3VEND_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetBackgroundControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_BKGDCT, byVal);
}
void DriverChip753::C753SetOutputBackground0(uint32_t dwVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OBKGD0_R, (dwVal&0x00ff0000)>>16);
     SPI_Write(0,REG_C753_B1_OBKGD0_G, (dwVal&0x0000ff00)>>8);
     SPI_Write(0,REG_C753_B1_OBKGD0_B, (dwVal&0x000000ff));
}
void DriverChip753::C753SetOutputBackground1(uint32_t dwVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OBKGD1_R, (dwVal&0x00ff0000)>>16);
     SPI_Write(0,REG_C753_B1_OBKGD1_G, (dwVal&0x0000ff00)>>8);
     SPI_Write(0,REG_C753_B1_OBKGD1_B, (dwVal&0x000000ff));
}
void DriverChip753::C753SetOutputPatternBarWidth(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OPBWIDTH, byVal);
}
void DriverChip753::C753SetOutputPatternSpeed(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OPBRATE, byVal);
}
void DriverChip753::C753SetOutputPatternCycle(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OPBPERIOD_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OPBPERIOD_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetPatternGeneratorControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_XPGCTRL, byVal);
}
void DriverChip753::C753SetRAMPCounterStepSetting(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_XRAMPCNT, byVal);
}
void DriverChip753::C753SetHorizontalRAMPCounterLimitValue(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_XHLIMIT_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_XHLIMIT_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetVerticalRAMPCounterLimitValue(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_XVLIMIT_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_XVLIMIT_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetColorBarWidthSetting(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_XCLBWIDTH, byVal);
}

void DriverChip753::C753SetPWMControl0(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OFPWMA_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OFPWMA_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetPWMControl1(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OFPWMB_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OFPWMB_H, (wVal&0xff00)>>8);
}
void DriverChip753::C753SetPWMControl2(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OFPWMC_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OFPWMC_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetPWMControl3(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_OFPWMD_L, (wVal&0x00ff));
     SPI_Write(0,REG_C753_B1_OFPWMD_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetIPCLKPLLControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_IPPLLCT, byVal);
}

void DriverChip753::C753SetIPCLKReferenceDividing(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_IPREFDIV, byVal);
}
void DriverChip753::C753SetIPCLKFeedbackDividing(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_IPFBDIV, byVal);
}
void DriverChip753::C753SetPOCLKPLLControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_POPLLCT, byVal);
}
void DriverChip753::C753SetPOCLKReferenceDividing(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_POREFDIV, byVal);
}
void DriverChip753::C753SetPOCLKFeedbackDividing(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_POFBDIV, byVal);
}
void DriverChip753::C753SetDLLControl0(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT0, byVal);
}
void DriverChip753::C753SetDLLControl1(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT1, byVal);
}
void DriverChip753::C753SetDLLControl2(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT2, byVal);
}
void DriverChip753::C753SetDLLControl3(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT3, byVal);
}
void DriverChip753::C753SetDLLControl4(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT4, byVal);
}
void DriverChip753::C753SetDLLControl5(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT5, byVal);
}
void DriverChip753::C753SetDLLControl6(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT6, byVal);
}
void DriverChip753::C753SetDLLControl7(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT7, byVal);
}
void DriverChip753::C753SetDLLControl8(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,1);
     SPI_Write(0,REG_C753_B1_DLLCT8, byVal);
}

/*Bank 2/4 function*/
void DriverChip753::C753SetOutputPortACTHorizontalStart(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_O1ACTHST_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B2_O1ACTHST_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_O2ACTHST_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B4_O2ACTHST_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753GetOutputPortACTHorizontalStart(uint32_t iCh, uint16_t &wVal)
{

    uint8_t valH = 0;
    uint8_t valL = 0;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Read(0,REG_C753_B2_O1ACTHST_L, valL);
        SPI_Read(0,REG_C753_B2_O1ACTHST_H, valH);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Read(0,REG_C753_B4_O2ACTHST_L, valL);
        SPI_Read(0,REG_C753_B4_O2ACTHST_H,valH);
    }

   	wVal = valL| ((uint16_t)valH<<8);
}

void DriverChip753::C753SetOutputPortACTHorizontalWidth(uint32_t iCh, uint16_t wVal)
{
	if(iCh == C753_OUTPUT_CHANNEL_1)
	{
		SPI_Write(0,REG_C753_BSC_RGBNK,2);
		SPI_Write(0,REG_C753_B2_O1ACTHW_L, (wVal&0x00ff));
		SPI_Write(0,REG_C753_B2_O1ACTHW_H, (wVal&0xff00)>>8);
	}
	else if(iCh == C753_OUTPUT_CHANNEL_2)
	{
		SPI_Write(0,REG_C753_BSC_RGBNK,4);
		SPI_Write(0,REG_C753_B4_O2ACTHW_L, (wVal&0x00ff));
		SPI_Write(0,REG_C753_B4_O2ACTHW_H, (wVal&0xff00)>>8);
	}
}
void DriverChip753::C753SetOutputPortACTVerticalStart(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_O1ACTVST_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B2_O1ACTVST_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_O2ACTVST_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B4_O2ACTVST_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753GetOutputPortACTVerticalStart(uint32_t iCh, uint16_t &wVal)
{

    uint8_t valH = 0;
    uint8_t valL = 0;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Read(0,REG_C753_B2_O1ACTVST_L, valL);
        SPI_Read(0,REG_C753_B2_O1ACTVST_H, valH);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Read(0,REG_C753_B4_O2ACTVST_L, valL);
        SPI_Read(0,REG_C753_B4_O2ACTVST_H, valH);
    }

   	wVal = valL| ((uint16_t)valH<<8);
}


void DriverChip753::C753SetOutputPortACTVerticalWidth(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_O1ACTVW_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B2_O1ACTVW_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_O2ACTVW_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B4_O2ACTVW_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_HEGCTCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_HEGCTCH2, byVal);
    }

}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_HEGCRLLCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_HEGCRLLCH2, byVal);
    }
}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_HEGCRULCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_HEGCRULCH2, byVal);
    }
}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeEmphasisCoefficient(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_HEGCOEFCH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B2_HEGCOEFCH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B2_HEGCOEFCH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B2_HEGCOEFCH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_HEGCOEFCH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B4_HEGCOEFCH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B4_HEGCOEFCH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B4_HEGCOEFCH2_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetOutputPostEnlargementHorizontalEdgeAreaSelect(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_HEGACTCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_HEGACTCH2, byVal);
    }
}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VEGCTCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VEGCTCH2, byVal);
    }
}

void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VEGCRLLCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VEGCRLLCH2, byVal);
    }
}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VEGCRULCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VEGCRULCH2, byVal);
    }
}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisCoefficient(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VEGCOEFCH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B2_VEGCOEFCH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B2_VEGCOEFCH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B2_VEGCOEFCH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VEGCOEFCH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B4_VEGCOEFCH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B4_VEGCOEFCH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B4_VEGCOEFCH2_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeAreaSelect(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VEGACTCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VEGACTCH2, byVal);
    }
}
void DriverChip753::C753SetOutputPostEnlargementVerticalEdgeEmphasisControl2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VEGCT2CH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VEGCT2CH2, byVal);
    }
}
void DriverChip753::C753SetOutputFill(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_O1FILL_R, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B2_O1FILL_G, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B2_O1FILL_B, (dwVal&0x000000ff));
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_O2FILL_R, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B4_O2FILL_G, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B4_O2FILL_B, (dwVal&0x000000ff));
    }
}
void DriverChip753::C753SetOutputImageControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_O1IMGCT, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_O2IMGCT, byVal);
    }
}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_ZHEGCTRLCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_ZHEGCTRLCH2, byVal);
    }
}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisCoringL(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_ZHEGCRLLCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_ZHEGCRLLCH2, byVal);
    }
}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisCoringH(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_ZHEGCRULCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_ZHEGCRULCH2, byVal);
    }
}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisOvershootFilterCoefficient(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_ZHEGHGAINOCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_ZHEGHGAINOCH2, byVal);
    }
}
void DriverChip753::C753SetOutputHorizontalEdgeEmphasisUndershootFilterCoefficient(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_ZHEGHGAINUCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_ZHEGHGAINUCH2, byVal);
    }
}
void DriverChip753::C753SetOutputHorizontalEnlargementControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_HZOOMCTCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_HZOOMCTCH2, byVal);
    }
}
void DriverChip753::C753SetOutputHorizontalEnlargementInitialValue(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_HZINITCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_HZINITCH2, byVal);
    }
}
void DriverChip753::C753SetOutputHorizontalZoomScale(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_HZSCLCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B2_HZSCLCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_HZSCLCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B4_HZSCLCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetOutputVerticalEnlargementControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VZOOMCTCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VZOOMCTCH2, byVal);
    }
}
void DriverChip753::C753SetOutputVerticalEnlargementInitialValue(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VZINITCH1, byVal);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VZINITCH2, byVal);
    }
}
void DriverChip753::C753SetOutputVerticalZoomScale(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        SPI_Write(0,REG_C753_B2_VZSCLCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B2_VZSCLCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        SPI_Write(0,REG_C753_B4_VZSCLCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B4_VZSCLCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753LoadOutputHorizontalZoomLookupTable(uint32_t iCh, const uint8_t *pbyVal)
{
    int i;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        for(i = 0; i < 24; i++)
        {
            SPI_Write(0,REG_C753_B2_HZLUTCH1_0+i, pbyVal[i]);
        }
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        for(i = 0; i < 24; i++)
        {
            SPI_Write(0,REG_C753_B4_HZLUTCH2_0+i, pbyVal[i]);
        }
    }
}

void DriverChip753::C753LoadOutputVerticalZoomLookupTable(uint32_t iCh, const uint8_t *pbyVal)
{
    int i;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,2);
        for(i = 0; i < 24; i++)
        {
            SPI_Write(0,REG_C753_B2_VZLUTCH1_0+i, pbyVal[i]);
        }
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,4);
        for(i = 0; i < 24; i++)
        {
            SPI_Write(0,REG_C753_B4_VZLUTCH2_0+i, pbyVal[i]);
        }
    }
}

/*Bank 6/8 function*/
void DriverChip753::C753SetInputFormatControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1IMGCT, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2IMGCT, byVal);
    }
}

void DriverChip753::C753SetInputPortSyncControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1SYCT, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2SYCT, byVal);
    }
}

void DriverChip753::C753SetInputFieldRecognitionControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_AUTOFLDCH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_AUTOFLDCH2, byVal);
    }
}

void DriverChip753::C753SetInputDigitalInterfaceControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_DIFCTCH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_DIFCTCH2, byVal);
    }
}

void DriverChip753::C753SetInputComponentInputControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1CPNCT, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2CPNCT, byVal);
    }
}

void DriverChip753::C753SetInputPortACTHorizontalStart(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1ACTHST_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_I1ACTHST_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2ACTHST_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_I2ACTHST_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753GetInputPortACTHorizontalStart(uint32_t iCh, uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Read(0,REG_C753_B6_I1ACTHST_L, valL);
        SPI_Read(0,REG_C753_B6_I1ACTHST_H, valH);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Read(0,REG_C753_B8_I2ACTHST_L, valL);
        SPI_Read(0,REG_C753_B8_I2ACTHST_H,valH);
    }

   	wVal = valL| ((uint16_t)valH<<8);
}


void DriverChip753::C753SetInputPortACTHorizontalWidth(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1ACTHW_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_I1ACTHW_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2ACTHW_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_I2ACTHW_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputPortACTVerticalStart(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1ACTVST_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_I1ACTVST_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2ACTVST_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_I2ACTVST_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753GetInputPortACTVerticalStart(uint32_t iCh, uint16_t &wVal)
{


    uint8_t valH = 0;
    uint8_t valL = 0;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Read(0,REG_C753_B6_I1ACTVST_L, valL);
        SPI_Read(0,REG_C753_B6_I1ACTVST_H, valH);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Read(0,REG_C753_B8_I2ACTVST_L, valL);
        SPI_Read(0,REG_C753_B8_I2ACTVST_H,valH);
    }

   	wVal = valL| ((uint16_t)valH<<8);
}

void DriverChip753::C753SetInputPortACTVerticalWidth(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1ACTVW_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_I1ACTVW_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2ACTVW_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_I2ACTVW_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputSignalSwap(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1SWP, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2SWP, byVal);
    }
}

void DriverChip753::C753SetInputImageControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1COLORCT, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2COLORCT, byVal);
    }
}

void DriverChip753::C753SetInputFill(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1FILL_R, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B6_I1FILL_G, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B6_I1FILL_B, (dwVal&0x000000ff));
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2FILL_R, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B8_I2FILL_G, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B8_I2FILL_B, (dwVal&0x000000ff));
    }
}

void DriverChip753::C753SetInputUVLowPassFilterCoefficient(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_UVLPCOEFCH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B6_UVLPCOEFCH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B6_UVLPCOEFCH1_2, (dwVal&0x00ff0000)>>16);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_UVLPCOEFCH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B8_UVLPCOEFCH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B8_UVLPCOEFCH2_2, (dwVal&0x00ff0000)>>16);
    }
}
void DriverChip753::C753SetInputRGBYUVCoefficientRY(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFRYCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFRYCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFRYCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFRYCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetInputRGBYUVCoefficientGY(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFGYCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFGYCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFGYCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFGYCH2_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputRGBYUVCoefficientBY(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFBYCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFBYCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFBYCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFBYCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetInputRGBYUVCoefficientRU(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFRUCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFRUCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFRUCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFRUCH2_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputRGBYUVCoefficientGU(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFGUCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFGUCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFGUCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFGUCH2_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputRGBYUVCoefficientBU(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFBUCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFBUCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFBUCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFBUCH2_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputRGBYUVCoefficientRV(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFRVCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFRVCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFRVCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFRVCH2_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputRGBYUVCoefficientGV(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFGVCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFGVCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFGVCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFGVCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetInputRGBYUVCoefficientBV(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_XCOEFBVCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_XCOEFBVCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_XCOEFBVCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_XCOEFBVCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetInputShrinkCompensationControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_SHRNKADJCH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_SHRNKADJCH2, byVal);
    }
}
void DriverChip753::C753SetInputHorizontalShrinkControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_HSHRNKCTCH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_HSHRNKCTCH2, byVal);
    }
}
void DriverChip753::C753SetInputHorizontalShrinkInitialValue(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_HSINITCH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_HSINITCH2, byVal);
    }
}
void DriverChip753::C753SetInputHorizontalShrinkScale(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_HSSCLCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_HSSCLCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_HSSCLCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_HSSCLCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetInputVerticalShrinkControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_VSHRNKCTCH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_VSHRNKCTCH2, byVal);
    }
}
void DriverChip753::C753SetInputVerticalShrinkInitialValue(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_VSINITCH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_VSINITCH2, byVal);
    }
}
void DriverChip753::C753SetInputVerticalShrinkScale(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_VSSCLCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B6_VSSCLCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_VSSCLCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B8_VSSCLCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetInputHorizontalShrinkCompensation(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1HSHCMP, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2HSHCMP, byVal);
    }
}

void DriverChip753::C753SetInputVerticalShrinkCompensation(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        SPI_Write(0,REG_C753_B6_I1VSHCMP, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        SPI_Write(0,REG_C753_B8_I2VSHCMP, byVal);
    }
}

void DriverChip753::C753LoadInputHorizontalShrinkLookupTable(uint32_t iCh, const uint8_t *pbyVal)
{
    int i;

    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        for(i = 0; i < 24; i++)
        {
            SPI_Write(0,REG_C753_B6_HSLUTCH1_0+i, pbyVal[i]);
        }
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        for(i = 0; i < 24; i++)
        {
            SPI_Write(0,REG_C753_B8_HSLUTCH2_0+i, pbyVal[i]);
        }
    }
}
void DriverChip753::C753LoadInputVerticalShrinkLookupTable(uint32_t iCh, const uint8_t *pbyVal)
{
    int i;

    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,6);
        for(i = 0; i < 24; i++)
        {
            SPI_Write(0,REG_C753_B6_VSLUTCH1_0+i, pbyVal[i]);
        }
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,8);
        for(i = 0; i < 24; i++)
        {
            SPI_Write(0,REG_C753_B8_VSLUTCH2_0+i, pbyVal[i]);
        }
    }
}
/*Bank 7/9 function*/
void DriverChip753::C753SetInputImageCharacteristicsMeasurementControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,7);
        SPI_Write(0,REG_C753_B7_PMODECH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,9);
        SPI_Write(0,REG_C753_B9_PMODECH2, byVal);
    }

}
void DriverChip753::C753SetInputMeasurementHorizontalStart(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,7);
        SPI_Write(0,REG_C753_B7_PI1H0_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B7_PI1H0_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,9);
        SPI_Write(0,REG_C753_B9_PI1H0_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B9_PI1H0_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetInputMeasurementVerticalStart(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,7);
        SPI_Write(0,REG_C753_B7_PI1V0_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B7_PI1V0_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,9);
        SPI_Write(0,REG_C753_B9_PI1V0_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B9_PI1V0_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetInputMeasurementHorizontalEnd(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,7);
        SPI_Write(0,REG_C753_B7_PI1H1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B7_PI1H1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,9);
        SPI_Write(0,REG_C753_B9_PI1H1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B9_PI1H1_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputMeasurementVerticalEnd(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,7);
        SPI_Write(0,REG_C753_B7_PI1V1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B7_PI1V1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,9);
        SPI_Write(0,REG_C753_B9_PI1V1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B9_PI1V1_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetInputCharacteristicsMeasurementThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,7);
        SPI_Write(0,REG_C753_B7_PTHCH1, byVal);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,9);
        SPI_Write(0,REG_C753_B9_PTHCH2, byVal);
    }
}
/*Bank 10/11 function*/
void DriverChip753::C753SetIPConversionOutputPortHorizontalSyncCycle(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPOHCYCLCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B10_IPOHCYCLCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPOHCYCLCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B11_IPOHCYCLCH2_H, (wVal&0xff00)>>8);
    }
}

void DriverChip753::C753SetIPConversionOutputPortVerticalSyncCycle(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPOVCYCLCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B10_IPOVCYCLCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPOVCYCLCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B11_IPOVCYCLCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetIPConversionForcedSyncResetDelay(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPSYRDLYCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPSYRDLYCH2, byVal);
    }
}
void DriverChip753::C753SetIPConversionOutputPortActiveAreaHorizontalStart(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPOACTHSTCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B10_IPOACTHSTCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPOACTHSTCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B11_IPOACTHSTCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetIPConversionOutputPortActiveAreaHorizontalWidth(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPOACTHWCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B10_IPOACTHWCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPOACTHWCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B11_IPOACTHWCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetIPConversionOutputPortActiveAreaVerticalStart(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPOACTVSTCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B10_IPOACTVSTCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPOACTVSTCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B11_IPOACTVSTCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetIPConversionOutputPortActiveAreaVerticalWidth(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPOACTVWCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B10_IPOACTVWCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPOACTVWCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B11_IPOACTVWCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetMovementNRControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_MVNRCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_MVNRCTCH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HMVNRCFACH1, byCoefA);
        SPI_Write(0,REG_C753_B10_HMVNRCFBCH1, byCoefB);
        SPI_Write(0,REG_C753_B10_HMVNRCFCCH1, byCoefC);
        SPI_Write(0,REG_C753_B10_HMVNRCFDCH1, byCoefD);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HMVNRCFACH2, byCoefA);
        SPI_Write(0,REG_C753_B11_HMVNRCFBCH2, byCoefB);
        SPI_Write(0,REG_C753_B11_HMVNRCFCCH2, byCoefC);
        SPI_Write(0,REG_C753_B11_HMVNRCFDCH2, byCoefD);
    }
}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HMVNRCFACH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HMVNRCFACH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HMVNRCFBCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HMVNRCFBCH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HMVNRCFCCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HMVNRCFCCH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalMovementValueNRCoefficient0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HMVNRCFDCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HMVNRCFDCH2, byVal);
    }
}
void DriverChip753::C753SetVerticalMovementValueGain(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_VFILCFACH1, byCoefA);
        SPI_Write(0,REG_C753_B10_VFILCFBCH1, byCoefB);
        SPI_Write(0,REG_C753_B10_VFILCFCCH1, byCoefC);
        SPI_Write(0,REG_C753_B10_VFILCFDCH1, byCoefD);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_VFILCFACH2, byCoefA);
        SPI_Write(0,REG_C753_B11_VFILCFBCH2, byCoefB);
        SPI_Write(0,REG_C753_B11_VFILCFCCH2, byCoefC);
        SPI_Write(0,REG_C753_B11_VFILCFDCH2, byCoefD);
    }
}
void DriverChip753::C753SetVerticalMovementValueGain3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_VFILCFACH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_VFILCFACH2, byVal);
    }
}
void DriverChip753::C753SetVerticalMovementValueGain2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_VFILCFBCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_VFILCFBCH2, byVal);
    }
}
void DriverChip753::C753SetVerticalMovementValueGain1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_VFILCFCCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_VFILCFCCH2, byVal);
    }
}
void DriverChip753::C753SetVerticalMovementValueGain0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_VFILCFDCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_VFILCFDCH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalMovementValueGain(uint32_t iCh, uint8_t byCoefA, uint8_t byCoefB, uint8_t byCoefC, uint8_t byCoefD)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HFILCFACH1, byCoefA);
        SPI_Write(0,REG_C753_B10_HFILCFBCH1, byCoefB);
        SPI_Write(0,REG_C753_B10_HFILCFCCH1, byCoefC);
        SPI_Write(0,REG_C753_B10_HFILCFDCH1, byCoefD);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HFILCFACH2, byCoefA);
        SPI_Write(0,REG_C753_B11_HFILCFBCH2, byCoefB);
        SPI_Write(0,REG_C753_B11_HFILCFCCH2, byCoefC);
        SPI_Write(0,REG_C753_B11_HFILCFDCH2, byCoefD);
    }
}
void DriverChip753::C753SetHorizontalMovementValueGain3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HFILCFACH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HFILCFACH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalMovementValueGain2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HFILCFBCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HFILCFBCH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalMovementValueGain1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HFILCFCCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HFILCFCCH2, byVal);
    }

}
void DriverChip753::C753SetHorizontalMovementValueGain0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_HFILCFDCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_HFILCFDCH2, byVal);
    }
}


void DriverChip753::C753SetVerticalDirectionMAXFilter(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_XVFILMDCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_XVFILMDCH2, byVal);
    }

}
void DriverChip753::C753SetMovementCoefficientNR(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_XNRCUTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_XNRCUTCH2, byVal);
    }

}
void DriverChip753::C753SetLUTWriteAddress(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_LUTWADCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_LUTWADCH2, byVal);
    }
}
void DriverChip753::C753SetLUTCoefficient(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_LUTCOEFCH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B10_LUTCOEFCH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B10_LUTCOEFCH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B10_LUTCOEFCH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_LUTCOEFCH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B11_LUTCOEFCH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B11_LUTCOEFCH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B11_LUTCOEFCH2_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetLUTWriteEnable(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_LUTWRCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_LUTWRCH2, byVal);
    }
}
void DriverChip753::C753SetIPImageAdjustment(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPADJCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPADJCTCH2, byVal);
    }
}
void DriverChip753::C753SetIPTest(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_IPTESTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_IPTESTCH2, byVal);
    }
}
void DriverChip753::C753SetPulldownControl1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_PDCTRL1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_PDCTRL1CH2, byVal);
    }
}
void DriverChip753::C753SetPulldownControl2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_PDCTRL2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_PDCTRL2CH2, byVal);
    }
}

void DriverChip753::C753Set22PulldownMovementDetectThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_PDMV22THCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_PDMV22THCH2, byVal);
    }
}
void DriverChip753::C753Set23PulldownMovementDetectThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_PDMV23THCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_PDMV23THCH2, byVal);
    }
}
void DriverChip753::C753SetPulldownSequenceThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_PDSQTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_PDSQTHCH2, byVal);
    }
}
void DriverChip753::C753SetPulldownAreaWidthSelect(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_MVACCSELCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_MVACCSELCH2, byVal);
    }
}
void DriverChip753::C753SetPulldownDetectAreaSelect(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_PDACTSELCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_PDACTSELCH2, byVal);
    }
}
void DriverChip753::C753Set22PulldownResetDetectIndex(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_PD22RSTCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_PD22RSTCTCH2, byVal);
    }
}
void DriverChip753::C753Set23PulldownResetDetectIndex(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_PD23RSTTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_PD23RSTTHCH2, byVal);
    }
}
void DriverChip753::C753SetCombingProcessControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_COMBCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_COMBCTCH2, byVal);
    }
}
void DriverChip753::C753SetCombingProcessControlLowLevelThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_COMBLTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_COMBLTHCH2, byVal);
    }
}
void DriverChip753::C753SetCombingProcessControlHighLevelThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_COMBHTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_COMBHTHCH2, byVal);
    }
}
void DriverChip753::C753SetDiagonalInterpolationControl(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        SPI_Write(0,REG_C753_B10_DIAGCTCH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B10_DIAGCTCH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B10_DIAGCTCH1_2, (dwVal&0x00ff0000)>>16);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        SPI_Write(0,REG_C753_B11_DIAGCTCH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B11_DIAGCTCH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B11_DIAGCTCH2_2, (dwVal&0x00ff0000)>>16);
    }
}
void DriverChip753::C753LoadDiagonalInterpolationThreshold(uint32_t iCh, const uint8_t *pbyVal)
{
    int i;

    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,10);
        for(i = 0; i < 13; i++)
        {
            SPI_Write(0,REG_C753_B10_DIAGTHCH1_0+i, pbyVal[i]);
        }
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,11);
        for(i = 0; i < 13; i++)
        {
            SPI_Write(0,REG_C753_B11_DIAGTHCH2_0+i, pbyVal[i]);
        }
    }
}
/*Bank 12/13 function*/
void DriverChip753::C753SetOutputField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_O1SFLD0_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_O1SFLD0_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_O1SFLD0_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_O1SFLD0_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_O2SFLD0_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_O2SFLD0_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_O2SFLD0_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_O2SFLD0_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetOutputField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_O1SFLD1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_O1SFLD1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_O1SFLD1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_O1SFLD1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_O2SFLD1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_O2SFLD1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_O2SFLD1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_O2SFLD1_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetOutputField2MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_O1SFLD2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_O1SFLD2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_O1SFLD2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_O1SFLD2_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_O2SFLD2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_O2SFLD2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_O2SFLD2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_O2SFLD2_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetOutputField3MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_O1SFLD3_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_O1SFLD3_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_O1SFLD3_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_O1SFLD3_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_O2SFLD3_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_O2SFLD3_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_O2SFLD3_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_O2SFLD3_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753GetOutputField0MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal)
{
    uint8_t val1 = 0;
    uint8_t val2 = 0;
    uint8_t val3 = 0;
    uint8_t val4 = 0;



    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Read(0,REG_C753_B12_O1SFLD0_0,val1);
        SPI_Read(0,REG_C753_B12_O1SFLD0_1,val2);
        SPI_Read(0,REG_C753_B12_O1SFLD0_2,val3);
        SPI_Read(0,REG_C753_B12_O1SFLD0_3,val4);



    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Read(0,REG_C753_B13_O2SFLD0_0,val1);
        SPI_Read(0,REG_C753_B13_O2SFLD0_1,val2);
        SPI_Read(0,REG_C753_B13_O2SFLD0_2,val3);
        SPI_Read(0,REG_C753_B13_O2SFLD0_3,val4);
    }

    dwVal = val4;
    dwVal = dwVal<<8|val3;
    dwVal = dwVal<<8|val2;
    dwVal = dwVal<<8|val1;
}
void DriverChip753::C753GetOutputField1MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal)
{
    uint8_t val1 = 0;
    uint8_t val2 = 0;
    uint8_t val3 = 0;
    uint8_t val4 = 0;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Read(0,REG_C753_B12_O1SFLD1_0,val1);
        SPI_Read(0,REG_C753_B12_O1SFLD1_1,val2);
        SPI_Read(0,REG_C753_B12_O1SFLD1_2,val3);
        SPI_Read(0,REG_C753_B12_O1SFLD1_3,val4);

    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Read(0,REG_C753_B13_O2SFLD1_0,val1);
        SPI_Read(0,REG_C753_B13_O2SFLD1_1,val2);
        SPI_Read(0,REG_C753_B13_O2SFLD1_2,val3);
        SPI_Read(0,REG_C753_B13_O2SFLD1_3,val4);
    }

    dwVal = val4;
    dwVal = dwVal<<8|val3;
    dwVal = dwVal<<8|val2;
    dwVal = dwVal<<8|val1;
}
void DriverChip753::C753GetOutputField2MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal)
{
    uint8_t val1 = 0;
    uint8_t val2 = 0;
    uint8_t val3 = 0;
    uint8_t val4 = 0;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Read(0,REG_C753_B12_O1SFLD2_0,val1);
        SPI_Read(0,REG_C753_B12_O1SFLD2_1,val2);
        SPI_Read(0,REG_C753_B12_O1SFLD2_2,val3);
        SPI_Read(0,REG_C753_B12_O1SFLD2_3,val4);

    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Read(0,REG_C753_B13_O2SFLD2_0,val1);
        SPI_Read(0,REG_C753_B13_O2SFLD2_1,val2);
        SPI_Read(0,REG_C753_B13_O2SFLD2_2,val3);
        SPI_Read(0,REG_C753_B13_O2SFLD2_3,val4);

    }

    dwVal = val4;
    dwVal = dwVal<<8|val3;
    dwVal = dwVal<<8|val2;
    dwVal = dwVal<<8|val1;
}
void DriverChip753::C753GetOutputField3MemoryReadStartAddress(uint32_t iCh,uint32_t &dwVal)
{
    uint8_t val1 = 0;
    uint8_t val2 = 0;
    uint8_t val3 = 0;
    uint8_t val4 = 0;

    if(iCh == C753_OUTPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Read(0,REG_C753_B12_O1SFLD3_0,val1);
        SPI_Read(0,REG_C753_B12_O1SFLD3_1,val2);
        SPI_Read(0,REG_C753_B12_O1SFLD3_2,val3);
        SPI_Read(0,REG_C753_B12_O1SFLD3_3,val4);

    }
    else if(iCh == C753_OUTPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Read(0,REG_C753_B13_O2SFLD3_0,val1);
        SPI_Read(0,REG_C753_B13_O2SFLD3_1,val2);
        SPI_Read(0,REG_C753_B13_O2SFLD3_2,val3);
        SPI_Read(0,REG_C753_B13_O2SFLD3_3,val4);
    }

    dwVal = val4;
    dwVal = dwVal<<8|val3;
    dwVal = dwVal<<8|val2;
    dwVal = dwVal<<8|val1;
}
void DriverChip753::C753SetInputField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_I1SFLD0_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_I1SFLD0_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_I1SFLD0_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_I1SFLD0_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_I2SFLD0_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_I2SFLD0_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_I2SFLD0_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_I2SFLD0_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetInputField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_I1SFLD1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_I1SFLD1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_I1SFLD1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_I1SFLD1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_I2SFLD1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_I2SFLD1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_I2SFLD1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_I2SFLD1_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetInputField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_I1SFLD2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_I1SFLD2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_I1SFLD2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_I1SFLD2_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_I2SFLD2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_I2SFLD2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_I2SFLD2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_I2SFLD2_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetInputField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_INPUT_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_I1SFLD3_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_I1SFLD3_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_I1SFLD3_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_I1SFLD3_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_INPUT_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_I2SFLD3_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_I2SFLD3_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_I2SFLD3_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_I2SFLD3_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetMemoryReadLinefeedWidth(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_O1MWI, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_O2MWI, byVal);
    }
}

void DriverChip753::C753GetMemoryReadLinefeedWidth(uint32_t iCh, uint8_t &byVal)
{

    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Read(0,REG_C753_B12_O1MWI,byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Read(0,REG_C753_B13_O2MWI,byVal);
    }
}

void DriverChip753::C753SetMemoryWriteLinefeedWidth(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_I1MWI, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_I2MWI, byVal);
    }
}

void DriverChip753::C753SetIPConversionField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_IPOSFLD0CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_IPOSFLD0CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_IPOSFLD0CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_IPOSFLD0CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_IPOSFLD0CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_IPOSFLD0CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_IPOSFLD0CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_IPOSFLD0CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753SetIPConversionField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_IPOSFLD1CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_IPOSFLD1CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_IPOSFLD1CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_IPOSFLD1CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_IPOSFLD1CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_IPOSFLD1CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_IPOSFLD1CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_IPOSFLD1CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753SetIPConversionField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_IPISFLD0CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_IPISFLD0CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_IPISFLD0CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_IPISFLD0CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_IPISFLD0CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_IPISFLD0CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_IPISFLD0CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_IPISFLD0CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753SetIPConversionField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_IPISFLD1CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_IPISFLD1CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_IPISFLD1CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_IPISFLD1CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_IPISFLD1CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_IPISFLD1CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_IPISFLD1CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_IPISFLD1CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753SetIPConversionField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_IPISFLD2CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_IPISFLD2CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_IPISFLD2CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_IPISFLD2CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_IPISFLD2CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_IPISFLD2CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_IPISFLD2CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_IPISFLD2CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753SetIPConversionField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_IPISFLD3CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_IPISFLD3CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_IPISFLD3CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_IPISFLD3CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_IPISFLD3CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_IPISFLD3CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_IPISFLD3CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_IPISFLD3CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753SetIPConversionMemoryLinefeedWidth(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_IPMWICH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_IPMWICH2, byVal);
    }
}

void DriverChip753::C753SetIPConversionMovementValueReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MVFLDCH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MVFLDCH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MVFLDCH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MVFLDCH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MVFLDCH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MVFLDCH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MVFLDCH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MVFLDCH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753SetTemporalNRReadStartAddressSelect(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_TMSASELCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_TMSASELCH2, byVal);
    }

}

void DriverChip753::C753Set90DegreeRotationField0MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTOSFLD0CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MRTOSFLD0CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MRTOSFLD0CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MRTOSFLD0CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTOSFLD0CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MRTOSFLD0CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MRTOSFLD0CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MRTOSFLD0CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753Set90DegreeRotationField1MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTOSFLD1CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MRTOSFLD1CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MRTOSFLD1CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MRTOSFLD1CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTOSFLD1CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MRTOSFLD1CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MRTOSFLD1CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MRTOSFLD1CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753Set90DegreeRotationField2MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTOSFLD2CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MRTOSFLD2CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MRTOSFLD2CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MRTOSFLD2CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTOSFLD2CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MRTOSFLD2CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MRTOSFLD2CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MRTOSFLD2CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753Set90DegreeRotationField3MemoryReadStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTOSFLD3CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MRTOSFLD3CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MRTOSFLD3CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MRTOSFLD3CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTOSFLD3CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MRTOSFLD3CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MRTOSFLD3CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MRTOSFLD3CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753Set90DegreeRotationField0MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTISFLD0CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MRTISFLD0CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MRTISFLD0CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MRTISFLD0CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTISFLD0CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MRTISFLD0CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MRTISFLD0CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MRTISFLD0CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753Set90DegreeRotationField1MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTISFLD1CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MRTISFLD1CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MRTISFLD1CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MRTISFLD1CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTISFLD1CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MRTISFLD1CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MRTISFLD1CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MRTISFLD1CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753Set90DegreeRotationField2MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTISFLD2CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MRTISFLD2CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MRTISFLD2CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MRTISFLD2CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTISFLD2CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MRTISFLD2CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MRTISFLD2CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MRTISFLD2CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753Set90DegreeRotationField3MemoryWriteStartAddress(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTISFLD3CH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B12_MRTISFLD3CH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B12_MRTISFLD3CH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B12_MRTISFLD3CH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTISFLD3CH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B13_MRTISFLD3CH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B13_MRTISFLD3CH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B13_MRTISFLD3CH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753Set90DegreeRotationMemoryReadLinefeedWidth(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTOMWICH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTOMWICH2, byVal);
    }
}

void DriverChip753::C753Set90DegreeRotationMemoryWriteLinefeedWidth(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,12);
        SPI_Write(0,REG_C753_B12_MRTIMWICH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,13);
        SPI_Write(0,REG_C753_B13_MRTIMWICH2, byVal);
    }
}

void DriverChip753::C753SetChannel1Image90DegreeRotationControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_MRTCTCH1, byVal);
}

void DriverChip753::C753SetChannel1Image90DegreeRotationHorizontalActiveAreaWidth(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_MRTACTHWCH1_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B14_MRTACTHWCH1_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetChannel1Image90DegreeRotationVerticalActiveAreaWidth(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_MRTACTVWCH1_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B14_MRTACTVWCH1_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetChannel1Image90DegreeRotationVerticalSyncSignalDelay(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_MRTVDLYCH1_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B14_MRTVDLYCH1_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetChannel2Image90DegreeRotationControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_MRTCTCH2, byVal);
}

void DriverChip753::C753SetChannel2Image90DegreeRotationHorizontalActiveAreaWidth(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_MRTACTHWCH2_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B14_MRTACTHWCH2_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetChannel2Image90DegreeRotationVerticalActiveAreaWidth(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_MRTACTVWCH2_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B14_MRTACTVWCH2_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetChannel2Image90DegreeRotationVerticalSyncSignalDelay(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_MRTVDLYCH2_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B14_MRTVDLYCH2_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetHorizontalSyncSignalAbsenceJudgmentValue(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_HSLLD_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B14_HSLLD_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetHorizontalSyncSignalPresenceJudgmentValue(uint16_t wVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_HSHLD_L, (wVal&0x00ff));
    SPI_Write(0,REG_C753_B14_HSHLD_H, (wVal&0xff00)>>8);
}

void DriverChip753::C753SetVerticalSyncSignalAbsenceJudgmentValue(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_VSLLD, byVal);
}

void DriverChip753::C753SetVerticalSyncSignalPresenceJudgmentValue(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_VSHLD, byVal);
}

void DriverChip753::C753Set1MHzPulseGenerationControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_1MPLSCT, byVal);
}

void DriverChip753::C753SetDPMSControl(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_DPMSCT, byVal);
}

void DriverChip753::C753SetDPMSInterruptReset(uint8_t byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,14);
    SPI_Write(0,REG_C753_B14_DPMSINTRST, byVal);
}

void DriverChip753::C753SetTemporalNRControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TMPPXNRCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TMPPXNRCTCH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRThreshold1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRTH1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRTH1CH2, byVal);
    }

}

void DriverChip753::C753SetTemporalNRThreshold2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRTH2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRTH2CH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRThreshold3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRTH3CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRTH3CH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRThreshold4(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRTH4CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRTH4CH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRCF1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRCF1CH2, byVal);
    }
}
void DriverChip753::C753SetTemporalNRCoefficient2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRCF2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRCF2CH2, byVal);
    }
}
void DriverChip753::C753SetTemporalNRCoefficient3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRCF3CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRCF3CH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRCoefficient4(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRCF4CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRCF4CH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRCoefficient5(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRCF5CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRCF5CH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRCoefficient6(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRCF6CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRCF6CH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRCoefficient7(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRCF7CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRCF7CH2, byVal);
    }
}

void DriverChip753::C753SetTemporalNRCoefficient8(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_TPXNRCF8CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_TPXNRCF8CH2, byVal);
    }
}


void DriverChip753::C753SetMosquitoNRControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQENCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQENCH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterHCoefficient0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQLPF5H0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQLPF5H0CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterHCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQLPF5H1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQLPF5H1CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterHCoefficient2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQLPF5H2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQLPF5H2CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterVCoefficient0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQLPF5V0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQLPF5V0CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterVCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQLPF5V1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQLPF5V1CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRBlendLowPassFilterVCoefficient2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQLPF5V2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQLPF5V2CH2, byVal);
    }
}



void DriverChip753::C753SetMosquitoNRVDirectionCoefficient0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQVEGLPF0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQVEGLPF0CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQVEGLPF1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQVEGLPF1CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQVEGLPF2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQVEGLPF2CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQVEGLPF3CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQVEGLPF3CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient4(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQVEGLPF4CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQVEGLPF4CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRVDirectionCoefficient5(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQVEGLPF5CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQVEGLPF5CH2, byVal);
    }
}

void DriverChip753::C753SetMosquitoNRHDirectionCoefficient0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQHEGLPF0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQHEGLPF0CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQHEGLPF1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQHEGLPF1CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQHEGLPF2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQHEGLPF2CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQHEGLPF3CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQHEGLPF3CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient4(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQHEGLPF4CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQHEGLPF4CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRHDirectionCoefficient5(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQHEGLPF5CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQHEGLPF5CH2, byVal);
    }
}



void DriverChip753::C753SetMosquitoNRBlendCoefficientBias(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BLENDBIASCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BLENDBIASCH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRBlendCoefficientGain(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BLENDGAINCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BLENDGAINCH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRNoiseBias(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQMAXBIASCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQMAXBIASCH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRSubtractionBlendCoefficientGain(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQSUBGAINCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQSUBGAINCH2, byVal);
    }
}

void DriverChip753::C753SetMosquitoNRThreshold0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYTH0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYTH0CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThreshold1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYTH1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYTH1CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThreshold2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYTH2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYTH2CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThreshold3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYTH3CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYTH3CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThreshold4(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYTH4CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYTH4CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThreshold5(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYTH5CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYTH5CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThreshold6(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYTH6CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYTH6CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThreshold7(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYTH7CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYTH7CH2, byVal);
    }
}

void DriverChip753::C753SetMosquitoNRThresholdBias0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYSUB0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYSUB0CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThresholdBias1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYSUB1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYSUB1CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThresholdBias2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYSUB2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYSUB2CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThresholdBias3(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYSUB3CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYSUB3CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThresholdBias4(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYSUB4CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYSUB4CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThresholdBias5(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYSUB5CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYSUB5CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThresholdBias6(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYSUB6CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYSUB6CH2, byVal);
    }
}
void DriverChip753::C753SetMosquitoNRThresholdBias7(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_MSQYSUB7CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_MSQYSUB7CH2, byVal);
    }
}


void DriverChip753::C753SetAdaptiveNRControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_EPNRCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_EPNRCTCH2, byVal);
    }
}
void DriverChip753::C753SetAdaptiveNRThreshold(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_EPNRTHCH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B15_EPNRTHCH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B15_EPNRTHCH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B15_EPNRTHCH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_EPNRTHCH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B16_EPNRTHCH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B16_EPNRTHCH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B16_EPNRTHCH2_3, (dwVal&0xff000000)>>24);
    }
}
void DriverChip753::C753SetAdaptiveNRCoefficient(uint32_t iCh, uint32_t dwVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_EPNRCFCH1_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B15_EPNRCFCH1_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B15_EPNRCFCH1_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B15_EPNRCFCH1_3, (dwVal&0xff000000)>>24);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_EPNRCFCH2_0, (dwVal&0x000000ff));
        SPI_Write(0,REG_C753_B16_EPNRCFCH2_1, (dwVal&0x0000ff00)>>8);
        SPI_Write(0,REG_C753_B16_EPNRCFCH2_2, (dwVal&0x00ff0000)>>16);
        SPI_Write(0,REG_C753_B16_EPNRCFCH2_3, (dwVal&0xff000000)>>24);
    }
}

void DriverChip753::C753SetBlockNRControl(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNRCTCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B15_BNRCTCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNRCTCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B16_BNRCTCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetBlockNRTest(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNTESTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNTESTCH2, byVal);
    }
}
void DriverChip753::C753SetBlockNoiseEdgeLevelThreshold0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNEGTH0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNEGTH0CH2, byVal);
    }
}
void DriverChip753::C753SetBlockNoiseEdgeLevelThreshold1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNEGTH1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNEGTH1CH2, byVal);
    }
}
void DriverChip753::C753SetBlockNoiseEdgeLevelThreshold2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNEGTH2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNEGTH2CH2, byVal);
    }
}
void DriverChip753::C753SetBlockNoiseEdgeLevelThreshold3(uint32_t iCh, uint8_t byVal)
{
	if(iCh == C753_CHANNEL_1)
	{
		SPI_Write(0,REG_C753_BSC_RGBNK,15);
		SPI_Write(0,REG_C753_B15_BNEGTH3CH1, byVal);
	}
	else if(iCh == C753_CHANNEL_2)
	{
		SPI_Write(0,REG_C753_BSC_RGBNK,16);
		SPI_Write(0,REG_C753_B16_BNEGTH3CH2, byVal);
	}
}
void DriverChip753::C753SetBlockNRAlphaBlendCoefficient0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNRABLCF0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNRABLCF0CH2, byVal);
    }
}
void DriverChip753::C753SetBlockNRAlphaBlendCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNRABLCF1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNRABLCF1CH2, byVal);
    }
}
void DriverChip753::C753SetBlockNRLowPassFilterCoefficient0(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNLPCF0CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNLPCF0CH2, byVal);
    }
}
void DriverChip753::C753SetBlockNRLowPassFilterCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNLPCF1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNLPCF1CH2, byVal);
    }
}
void DriverChip753::C753SetBlockBoundaryPeripheralMovementValueThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNAMVTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNAMVTHCH2, byVal);
    }
}
void DriverChip753::C753SetBlockBoundaryPeripheralEdgeLevelThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNAEGTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNAEGTHCH2, byVal);
    }
}


void DriverChip753::C753SetHorizontalBlockBoundaryCoordinate(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNHPOSCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNHPOSCH2, byVal);
    }
}
void DriverChip753::C753SetVerticalBlockBoundaryCoordinate(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNVPOSCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNVPOSCH2, byVal);
    }
}
void DriverChip753::C753SetBlockNRDetectControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNDETCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNDETCTCH2, byVal);
    }
}
void DriverChip753::C753SetLongFramesRegisterBlockBoundaryAutoDetect(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNLFCYCLCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNLFCYCLCH2, byVal);
    }
}


void DriverChip753::C753SetHBlockBoundaryMatchingUpperLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNHMTHHCCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNHMTHHCCH2, byVal);
    }
}
void DriverChip753::C753SetHBlockBoundaryMatchingLowerLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNHMTHLCCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNHMTHLCCH2, byVal);
    }
}
void DriverChip753::C753SetHBlockBoundaryMatchingThresholdPeripheralPixel(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNHMTHSCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNHMTHSCH2, byVal);
    }
}
void DriverChip753::C753SetHBlockBoundaryMatchingCountsThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNHMCNTTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNHMCNTTHCH2, byVal);
    }
}
void DriverChip753::C753SetHBlockBoundaryMatchingCountsOffset(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNHMCNTOFFCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNHMCNTOFFCH2, byVal);
    }
}
void DriverChip753::C753SetVBlockBoundaryMatchingUpperLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNVMTHHCCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNVMTHHCCH2, byVal);
    }
}
void DriverChip753::C753SetVBlockBoundaryMatchingLowerLimitThresholdCenterPixel(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNVMTHLCCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNVMTHLCCH2, byVal);
    }
}
void DriverChip753::C753SetVBlockBoundaryMatchingThresholdPeripheralPixel(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNVMTHSCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNVMTHSCH2, byVal);
    }
}
void DriverChip753::C753SetVBlockBoundaryMatchingCountsThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNVMCNTTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNVMCNTTHCH2, byVal);
    }
}
void DriverChip753::C753SetVBlockBoundaryMatchingCountsOffset(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNVMCNTOFFCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNVMCNTOFFCH2, byVal);
    }
}


void DriverChip753::C753SetBlockNRProjectionControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNPJCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNPJCTCH2, byVal);
    }
}
void DriverChip753::C753SetBlockNRProjectionCoefficient(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNPJCFCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNPJCFCH2, byVal);
    }
}
void DriverChip753::C753SetBlockNRProjectionReadAddress(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNPJRADCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNPJRADCH2, byVal);
    }
}
void DriverChip753::C753SetBlockNRProjectionReadData(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNPJRDTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNPJRDTCH2, byVal);
    }

}

void DriverChip753::C753SetHorizontalBlockBoundaryInitialCoordinateForProjection(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNHINIPOSCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B15_BNHINIPOSCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNHINIPOSCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B16_BNHINIPOSCH2_H, (wVal&0xff00)>>8);
    }

}
void DriverChip753::C753SetHorizontalBlockEnlargementScaleForProjection(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNHSCLCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B15_BNHSCLCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNHSCLCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B16_BNHSCLCH2_H, (wVal&0xff00)>>8);
    }

}
void DriverChip753::C753SetVerticalBlockBoundaryInitialCoordinateForProjection(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNVINIPOSCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B15_BNVINIPOSCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNVINIPOSCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B16_BNVINIPOSCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetVerticalBlockEnlargementScaleForProjection(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_BNVSCLCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B15_BNVSCLCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_BNVSCLCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B16_BNVSCLCH2_H, (wVal&0xff00)>>8);
    }

}
void DriverChip753::C753SetHorizontalVerticalNRControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_HVPXNRCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_HVPXNRCTCH2, byVal);
    }
}
void DriverChip753::C753SetVerticalNRCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_VPXNRCF1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_VPXNRCF1CH2, byVal);
    }
}
void DriverChip753::C753SetVerticalNRCoefficient2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_VPXNRCF2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_VPXNRCF2CH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalNRCoefficient1(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_HPXNRCF1CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_HPXNRCF1CH2, byVal);
    }
}
void DriverChip753::C753SetHorizontalNRCoefficient2(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_HPXNRCF2CH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_HPXNRCF2CH2, byVal);
    }
}
void DriverChip753::C753SetChromaErrorCorrectionControl(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_UVNRCTCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_UVNRCTCH2, byVal);
    }
}
void DriverChip753::C753SetChromaErrorDetectionThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_UVNRTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_UVNRTHCH2, byVal);
    }
}
void DriverChip753::C753SetChromaErrorDetectionCountThreshold(uint32_t iCh, uint16_t wVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_UVNRCNTTHCH1_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B15_UVNRCNTTHCH1_H, (wVal&0xff00)>>8);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_UVNRCNTTHCH2_L, (wVal&0x00ff));
        SPI_Write(0,REG_C753_B16_UVNRCNTTHCH2_H, (wVal&0xff00)>>8);
    }
}
void DriverChip753::C753SetChromaErrorDetectionExclusionThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_UVNREXTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_UVNREXTHCH2, byVal);
    }
}
void DriverChip753::C753SetChromaErrorAutomaticCorrectionThreshold(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_UVNRATTHCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_UVNRATTHCH2, byVal);
    }
}
void DriverChip753::C753SetChromaErrorAutomaticCorrectionCounterUpperLimit(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_UVNRATLIMCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_UVNRATLIMCH2, byVal);
    }
}
void DriverChip753::C753SetChromaErrorCorrectionLowPassFilterCoefficient(uint32_t iCh, uint8_t byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,15);
        SPI_Write(0,REG_C753_B15_UVNRLPCFCH1, byVal);
    }
    else if(iCh == C753_CHANNEL_2)
    {
        SPI_Write(0,REG_C753_BSC_RGBNK,16);
        SPI_Write(0,REG_C753_B16_UVNRLPCFCH2, byVal);
    }
}

void DriverChip753::C753GetInputPortHorizontalSyncFrequency(uint32_t iCh, uint16_t &wVal)
{
	uint8_t byValL = 0;
	uint8_t byValH = 0;
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_IFH1_L,byValL);
    	SPI_Read(0,REG_C753_B17_IFH1_H,byValH);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_IFH2_L,byValL);
    	SPI_Read(0,REG_C753_B17_IFH2_H,byValH);
    }

    wVal = byValH;
    wVal = byValH << 8 |byValL;


}
void DriverChip753::C753GetInputPortVerticalSyncFrequency(uint32_t iCh, uint16_t &wVal)
{
	uint8_t byValL = 0;
	uint8_t byValH = 0;
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_IFV1_L,byValL);
    	SPI_Read(0,REG_C753_B17_IFV1_H,byValH);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_IFV2_L,byValL);
    	SPI_Read(0,REG_C753_B17_IFV2_H,byValH);
    }

    wVal = byValH;
    wVal = byValH << 8 |byValL;
}
void DriverChip753::C753GetInputPortHorizontalSyncPulseWidth(uint32_t iCh, uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_IHW1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_IHW2,byVal);
    }

}

void DriverChip753::C753GetInputPortVerticalSyncPulseWidth(uint32_t iCh, uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_IVW1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_IVW2,byVal);
    }

}

void DriverChip753::C753GetHorizontalAndVerticalSyncPhaseDifference0(uint32_t iCh,uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;


    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_I1HVPHDF0_L,valL);
    	SPI_Read(0,REG_C753_B17_I1HVPHDF0_H,valL);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_I1HVPHDF1_L,valL);
    	SPI_Read(0,REG_C753_B17_I1HVPHDF1_H,valL);
    }

    wVal = valL| ((uint16_t)valH<<8);

}
void DriverChip753::C753GetHorizontalAndVerticalSyncPhaseDifference1(uint32_t iCh,uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;


    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_I2HVPHDF0_L,valL);
    	SPI_Read(0,REG_C753_B17_I2HVPHDF0_H,valL);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_I2HVPHDF1_L,valL);
    	SPI_Read(0,REG_C753_B17_I2HVPHDF1_H,valL);
    }

    wVal = valL| ((uint16_t)valH<<8);
}

void DriverChip753::C753GetStatus(uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;

    SPI_Write(0,REG_C753_BSC_RGBNK,17);
    SPI_Read(0,REG_C753_B17_STATE_L,valL);
   	SPI_Read(0,REG_C753_B17_STATE_H,valL);

   	wVal = valL| ((uint16_t)valH<<8);

}

void DriverChip753::C753GetFieldHistory(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_FLDHIST1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_FLDHIST2,byVal);
    }
}


void DriverChip753::C753GetMeasurementStatusMonitor(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PSTAT1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PSTAT2,byVal);
    }
}

void DriverChip753::C753GetCharacteristicsMeasurementResult0(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PVAL0CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PVAL0CH2,byVal);
    }
}

void DriverChip753::C753GetCharacteristicsMeasurementResult1(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PVAL1CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PVAL1CH2,byVal);
    }
}

void DriverChip753::C753GetCharacteristicsMeasurementResultHorizontalCoordinate0(uint32_t iCh,uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;


    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PH0CH1_L,valL);
    	SPI_Read(0,REG_C753_B17_PH0CH1_H,valH);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PH0CH2_L,valL);
    	SPI_Read(0,REG_C753_B17_PH0CH2_H,valH);
    }

    wVal = valL| ((uint16_t)valH<<8);

}
void DriverChip753::C753GetCharacteristicsMeasurementResultVerticalCoordinate0(uint32_t iCh,uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;


    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PV0CH1_L,valL);
    	SPI_Read(0,REG_C753_B17_PV0CH1_H,valH);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PV0CH2_L,valL);
    	SPI_Read(0,REG_C753_B17_PV0CH2_H,valH);
    }

    wVal = valL| ((uint16_t)valH<<8);

}

void DriverChip753::C753GetCharacteristicsMeasurementResultHorizontalCoordinate1(uint32_t iCh,uint16_t &wVal)
{

    uint8_t valH = 0;
    uint8_t valL = 0;


    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PH1CH1_L,valL);
    	SPI_Read(0,REG_C753_B17_PH1CH1_H,valH);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PH1CH2_L,valL);
    	SPI_Read(0,REG_C753_B17_PH1CH2_H,valH);
    }

    wVal = valL| ((uint16_t)valH<<8);
}
void DriverChip753::C753GetCharacteristicsMeasurementResultVerticalCoordinate1(uint32_t iCh,uint16_t &wVal)
{

    uint8_t valH = 0;
    uint8_t valL = 0;


    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PV1CH1_L,valL);
    	SPI_Read(0,REG_C753_B17_PV1CH1_H,valH);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PV1CH2_L,valL);
    	SPI_Read(0,REG_C753_B17_PV1CH2_H,valH);
    }

    wVal = valL| ((uint16_t)valH<<8);
}

void DriverChip753::C753GetSNHistogramMeasurementResult(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_SNMSHIST1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_SNMSHIST2,byVal);
    }
}

void DriverChip753::C753GetMAXFILTERResult(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_MAXFILTR1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_MAXFILTR2,byVal);
    }
}
void DriverChip753::C753GetMINFILTERResult(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_MINFILTR1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_MINFILTR2,byVal);
    }
}

void DriverChip753::C753GetAverageLuminanceLevelResult(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_APL1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_APL2,byVal);
    }
}

void DriverChip753::C753Get23PulldownSequenceCount1(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT1CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT1CH2,byVal);
    }
}
void DriverChip753::C753Get23PulldownSequenceCount2(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT2CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT2CH2,byVal);
    }
}

void DriverChip753::C753Get23PulldownSequenceCount3(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT3CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT3CH2,byVal);
    }
}

void DriverChip753::C753Get23PulldownSequenceCount4(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT4CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT4CH2,byVal);
    }
}

void DriverChip753::C753Get23PulldownSequenceCount5(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT5CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD23CNT5CH2,byVal);
    }
}

void DriverChip753::C753Get22PulldownSequenceCount1(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD22CNT1CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_PD22CNT1CH2,byVal);
    }
}

void DriverChip753::C753GetOutputPortVerticalSyncFrequency(uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;

    SPI_Write(0,REG_C753_BSC_RGBNK,17);
    SPI_Read(0,REG_C753_B17_OFV_L,valL);
   	SPI_Read(0,REG_C753_B17_OFV_H,valH);

   	wVal = valL| ((uint16_t)valH<<8);

}
void DriverChip753::C753GetPWMLowPulseWidthCounterValue(uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;

    SPI_Write(0,REG_C753_BSC_RGBNK,17);
    SPI_Read(0,REG_C753_B17_PWMLW_L,valL);
   	SPI_Read(0,REG_C753_B17_PWMLW_H,valH);

   	wVal = valL| ((uint16_t)valH<<8);
}
void DriverChip753::C753GetPWMHighPulseWidthCounterValue(uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;

    SPI_Write(0,REG_C753_BSC_RGBNK,17);
    SPI_Read(0,REG_C753_B17_PWMHW_L,valL);
   	SPI_Read(0,REG_C753_B17_PWMHW_H,valH);

   	wVal = valL| ((uint16_t)valH<<8);
}
void DriverChip753::C753GetFlashStatus(uint8_t &byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,17);
    SPI_Read(0,REG_C753_B17_FLSTAT,byVal);

}
void DriverChip753::C753GetInterruptStatus(uint16_t &wVal)
{
    uint8_t valH = 0;
    uint8_t valL = 0;

    SPI_Write(0,REG_C753_BSC_RGBNK,17);
    SPI_Read(0,REG_C753_B17_INTSTAT_L,valL);
   	SPI_Read(0,REG_C753_B17_INTSTAT_H,valH);

   	wVal = valL| ((uint16_t)valH<<8);
}
void DriverChip753::C753GetDPMSInterruptStatus(uint8_t &byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,17);
    SPI_Read(0,REG_C753_B17_DPMSINTSTAT,byVal);
}
void DriverChip753::C753GetDPMSStatus(uint8_t &byVal)
{
    SPI_Write(0,REG_C753_BSC_RGBNK,17);
    SPI_Read(0,REG_C753_B17_DPMSSTAT,byVal);

}

void DriverChip753::C753GetBlockNoiseHMatchingCountsMax(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_HMCNTMAXCH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_HMCNTMAXCH2,byVal);
    }
}
void DriverChip753::C753GetBlockNoiseHMatchingCountsMax2(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_HMCNTMAX2CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_HMCNTMAX2CH2,byVal);
    }
}
void DriverChip753::C753GetBlockNoiseHBoundaryCoordinate(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_HMPOSCH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_HMPOSCH2,byVal);
    }
}
void DriverChip753::C753GetBlockNoiseVMatchingCountsMax(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_VMCNTMAXCH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_VMCNTMAXCH2,byVal);
    }
}
void DriverChip753::C753GetBlockNoiseVMatchingCountsMax2(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_VMCNTMAX2CH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_VMCNTMAX2CH2,byVal);
    }
}
void DriverChip753::C753GetBlockNoiseVBoundaryCoordinate(uint32_t iCh,uint8_t &byVal)
{
    if(iCh == C753_CHANNEL_1)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_VMPOSCH1,byVal);

    }
    else if(iCh == C753_CHANNEL_2)
    {
    	SPI_Write(0,REG_C753_BSC_RGBNK,17);
    	SPI_Read(0,REG_C753_B17_VMPOSCH2,byVal);
    }
}







