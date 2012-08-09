/*
 * devC772.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _APP_C753_H_
#define _APP_C753_H_

#include "devC753.h"
#include <vector>

using namespace std;
using namespace chip;


namespace chipApp
{

static const uint8_t s_abyScaleZoomCoefficient4SymbolTable[24] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0xfe, 0xfd, 0xfc, 0xfc, 0xfd, 0x00,
  0x05, 0x0d, 0x18, 0x23, 0x2e, 0x38, 0x3e, 0x40
};

static const uint8_t s_abyScaleShrinkCoefficient4SymbolTable[24] =
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xff, 0xfe, 0xfd, 0xfc, 0xfc, 0xfd, 0x00,
  0x05, 0x0d, 0x18, 0x23, 0x2e, 0x38, 0x3e, 0x40
};


typedef struct
{
	uint16_t    wHorResolution; /*水平分辨率*/
	uint16_t    wVerResolution; /*垂直分辨率*/
	uint16_t    wStartIndex;    /*开始索引*/
	uint16_t    wCount;         /*个数*/

}TimingIndexTableT;

typedef struct
{
    uint16_t    wHorResolution; /*水平分辨率*/
    uint16_t    wVerResolution; /*垂直分辨率*/
    int32_t  	iFrameRate;     /*视频帧率*/
    int32_t  	iClock;         /*时钟频率*/
    uint16_t    wHorTotal;      /*水平总像素数*/
    uint16_t    wHorSync;       /*水平低电平*/
    uint16_t    wHorStart;      /*水平图像起始位置*/
    uint16_t    wVerTotal;      /*垂直总行数*/
    uint16_t    wVerSync;       /*垂直低电平*/
    uint16_t    wVerStart;      /*垂直图像起始位置*/
    int16_t   	sswC753OffsetX; /*C753输出偏移补偿*/
    int16_t   	sswC753OffsetY; /*C753输出偏移补偿*/
}TimingT;

typedef struct{
    uint16_t    wHorResolution;     /*水平分辨率*/
    uint16_t    wVerResolution;     /*垂直分辨率*/
    uint8_t    	byStandardType;     /*标准类型*/
}ScaleConfigT;

typedef struct{
    uint8_t    byAddr;
    uint32_t   dwCoef;
}ScalLUTIPTableT;

static const ScalLUTIPTableT s_sLUTIPTable[] =
{
	{0x00, 0x00042000},  {0x01, 0x00139c01},  {0x02, 0x00139c01},  {0x03, 0x00231802},
	{0x04, 0x00231802},  {0x05, 0x00329403},  {0x06, 0x00329403},  {0x07, 0x00329403},
	{0x08, 0x00421004},  {0x09, 0x00421004},  {0x0a, 0x00421004},  {0x0b, 0x00421004},
	{0x0c, 0x00518c05},  {0x0d, 0x00518c05},  {0x0e, 0x00518c05},  {0x0f, 0x00518c05},
	{0x10, 0x00610806},  {0x11, 0x00610806},  {0x12, 0x00610806},  {0x13, 0x00610806},
	{0x14, 0x00708407},  {0x15, 0x00708407},  {0x16, 0x00708407},  {0x17, 0x00708407},
	{0x18, 0x00800008},  {0x19, 0x00800008},  {0x1a, 0x00800008},  {0x1b, 0x00800008},
	{0x1c, 0x00800008},  {0x1d, 0x00800008},  {0x1e, 0x00800008},  {0x1f, 0x00800008},
	{0x20, 0x00004000},  {0x21, 0x00004000},  {0x22, 0x00004000},  {0x23, 0x00004000},
	{0x24, 0x00004000},  {0x25, 0x00004000},  {0x26, 0x00004000},  {0x27, 0x00004000},
	{0x28, 0x00004000},  {0x29, 0x00004000},  {0x2a, 0x00004000},  {0x2b, 0x00004000},
	{0x2c, 0x00004000},  {0x2d, 0x00004000},  {0x2e, 0x00004000},  {0x2f, 0x00004000},
	{0x30, 0x00004000},  {0x31, 0x00004000},  {0x32, 0x00004000},  {0x33, 0x00004000},
	{0x34, 0x00004000},  {0x35, 0x00004000},  {0x36, 0x00004000},  {0x37, 0x00004000},
	{0x38, 0x00004000},  {0x39, 0x00004000},  {0x3a, 0x00004000},  {0x3b, 0x00004000},
	{0x3c, 0x00004000},  {0x3d, 0x00004000},  {0x3e, 0x00004000},  {0x3f, 0x00004000},
};

class AppC753
:public DriverChip753
{

public:
	AppC753();
	virtual ~AppC753();


	void chipTest();
	void initHardware(uint32_t iChID, ScaleConfigT *pScaleConfig);

private:

	void initTimingIndexTable();
	uint16_t getHorizontalTotal(uint16_t wHorResolution, uint16_t wVerResolution, uint16_t byStandardType);
	uint16_t getHorizontalStart(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);
	int16_t getHorizontalCompensation(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);

	uint16_t getVerticalTotal(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);
	uint16_t getVerticalStart(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);
	int16_t getVerticalCompensation(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);

	vector<TimingIndexTableT> m_asTimingIndexTable;

	vector<TimingT> m_asSignalTiming;

	ScaleConfigT m_asScaleConfig;

};
};

#endif /* USER_H_ */
