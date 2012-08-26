/*
 * devC772.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _APP_SCAL_H_
#define _APP_SCAL_H_

#include "chipCommon.h"
#include "devC753.h"
#include "devICS307.h"
#include <vector>
#include "Bitmap.h"

using namespace std;
using namespace chip;

#define         SCAL_FRAME_LINE_MAX             1024
#define         SCAL_INPUT_HOR_SYNC_MCLK        4390
#define         SCAL_INPUT_VER_SYNC_30          1250
#define         SCAL_INPUT_VER_SYNC_50          750
#define         SCAL_INPUT_VER_SYNC_60          625
#define         SCAL_INPUT_HOR_SYNC_THRESHOLD   4
#define         SCAL_INPUT_VER_SYNC_THRESHOLD   4

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

typedef struct{
	int32_t		iChStatus;	        /*通道状态，-1：关闭通道，0：隐藏通道，1：打开通道*/
    uint8_t   	byContextRegs[4];   /*保存寄存器状态*/
    int32_t  	iImageType;	        /*图像类型，0：RGB, 1：Video, 2：IP field*/
    int32_t  	iFrameRate;	        /*输入图像帧率 （25，30，50，60）*/
	uint16_t    wInputStartX;	    /*输入图像的起始列坐标*/
	uint16_t    wInputStartY;	    /*输入图像的起始行坐标*/
	uint16_t    wInputClipOffsetX;  /*剪切区域的偏移列坐标（相对图像区域）*/
	uint16_t    wInputClipOffsetY;  /*剪切区域的偏移行坐标（相对图像区域）*/
	uint16_t    wInputClipWidth;	/*剪切区域的宽度*/
	uint16_t    wInputClipHeight;	/*剪切区域的高度*/
    int16_t	    sswInputAdjustStartX;/*输入微调列位置*/
    int16_t  	sswInputAdjustStartY;/*输入微调行位置*/
    int16_t   	sswInputAdjustWidth; /*输入微调宽度*/
    int16_t   	sswInputAdjustHeight;/*输入微调高度*/
    uint16_t    wOutputStartX;	    /*背景图像输出的起始列坐标*/
    uint16_t    wOutputStartY;	    /*背景图像输出的起始行坐标*/
    uint16_t    wOutputWidth;	    /*背景图像输出的宽度*/
    uint16_t    wOutputHeight;	    /*背景图像输出的高度*/
    uint16_t    wOutputActOffsetX;	/*输出图像的偏移列坐标（相对背景区域）*/
    uint16_t    wOutputActOffsetY;  /*输出图像的偏移行坐标（相对背景区域）*/
    uint16_t    wOutputActWidth;	/*输出图像的宽度*/
    uint16_t    wOutputActHeight;	/*输出图像的高度*/
    uint16_t    wOutputClipOffsetX;	/*输出剪切图像的偏移列坐标（相对背景区域）*/
    uint16_t    wOutputClipOffsetY; /*输出剪切图像的偏移行坐标（相对背景区域）*/
	uint16_t    wOutputClipWidth;	/*输出剪切图像的宽度*/
	uint16_t    wOutputClipHeight;	/*输出剪切图像的高度*/
	int16_t		sswScaleModeH;	    /*图像的水平缩放模式（-1：缩小，0：不变，1：放大）*/
	int16_t		sswScaleModeV;      /*图像的垂直缩放模式（-1：缩小，0：不变，1：放大）*/
	uint16_t    wScaleFactorUpH;	/*图像水平放大因子*/
	uint16_t    wScaleFactorDownH;	/*图像水平缩小因子*/
	uint16_t    wScaleFactorUpV;	/*图像垂直放大因子*/
	uint16_t    wScaleFactorDownV;		/*图像垂直缩放因子，用16bit小数表示
							        缩小计算公式：
							        (OACT-1)*65536/(ICLP-1)+1
							        放大计算公式：
							        (ICLP-1)*65536/(OACT-1)+1*/
}ScaleChInfoT;

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

enum SCAL_IMAGE_TYPE
{
    SCAL_IMAGE_RGB   = 0,
    SCAL_IMAGE_VIDEO = 1,
    SCAL_IMAGE_IPFIELD = 2,
};

enum SCAL_STATUS_TYPE
{
    SCAL_STATUS_CLOSE = -1,
    SCAL_STATUS_HIDE = 0,
    SCAL_STATUS_OPEN = 1,
    SCAL_STATUS_REOPEN = 2,
    SCAL_STATUS_FREERUN = 3, /*��������״̬�����Ĭ�ϵ�����*/
};

enum SCAL_MODE_TYPE
{
    SCAL_MODE_SHRINK = -1,
    SCAL_MODE_SAME = 0,
    SCAL_MODE_ZOOM = 1,
    SCAL_MODE_BOTH = 2,
};

enum OUTPUT_MODLE_TYPE
{
    TYPE_OUTPUT_ACT = 0,
    TYPE_OUTPUT_AOI0 = 1,
    TYPE_OUTPUT_AOI1 = 2,
};

enum OUTPUT_SIZE_TYPE
{
    TYPE_OUTPUT_SIZE_1024_768 = 0,
    TYPE_OUTPUT_SIZE_1440_1050 = 1,
};

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

class AppScale
:public DriverChip753
,public DriverChipICS307
{

public:
	AppScale();
	virtual ~AppScale();


	void chipTest();


	void showWnd(uint32_t iChID);
	void hideWnd(uint32_t iChID);
	void pauseChannel(uint32_t iChID);
	void resumeChannel(uint32_t iChID);
	void openChannel(uint32_t iChID);

	void writeBackground(uint32_t iChID, uint16_t wOffsetX, uint16_t wOffsetY, DispBitmapT *BitmapPtr);
	void readBackground(uint32_t iChID, int32_t iIndex, uint16_t wWidth, uint16_t wHeight, uint8_t *pbyBuf);

	void openChannelTest();
	void initTest1024();
	void initTest1400();

	void initScal(uint32_t iChID,uint32_t hInput,uint32_t hOutput,uint32_t vInput,uint32_t vOutput);


	void initHardware();
	void initChipDDR();
	void initCLK();

	void initScaleTable(uint32_t channelID);
	void initMemoryLineFeedWidth(uint32_t channelID);
	void selectOutPutModel(uint32_t model);

	void setOutputBGColor(uint32_t bg0Color,uint32_t bg1Color);
	void setOutputSize(uint32_t type);
	void setOutputImage(uint32_t model,uint32_t size);
	void setOutputChannelACT(uint32_t iChID,uint16_t hw,uint16_t vw,uint16_t hs,uint16_t vs);
	void setInputChannelACT(uint32_t iChID,uint16_t hw,uint16_t vw,uint16_t hs,uint16_t vs);
	void moveChannelInput(uint32_t channel,int hPoint,int vPoint);
	void moveChannelOutput(uint32_t channel,int hPoint,int vPoint);

	void topChannel(uint32_t channel);

private:

	void initChannel(uint32_t iChID, ScaleChInfoT *pScalCh);
	void initTimingIndexTable();
	int32_t calculate6SymbolLUT(float *pfCutoff, float *pfWinfact, uint8_t *pbyLut);

	uint16_t getHorizontalTotal(uint16_t wHorResolution, uint16_t wVerResolution, uint16_t byStandardType);
	uint16_t getHorizontalStart(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);
	int16_t getHorizontalCompensation(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);

	uint16_t getVerticalTotal(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);
	uint16_t getVerticalStart(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);
	int16_t getVerticalCompensation(uint16_t wHorResolution, uint16_t wVerResolution, uint8_t byStandardType);

	vector<TimingIndexTableT> m_asTimingIndexTable;

	vector<TimingT> m_asSignalTiming;

	ScaleConfigT m_asScaleConfig;
	vector<ScaleChInfoT> m_asScaleChInfo;

	uint16_t m_horFp;
	uint16_t m_verFp;

};
};

#endif /* USER_H_ */
