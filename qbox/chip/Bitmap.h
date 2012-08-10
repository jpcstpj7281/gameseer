/******************************************************************************


  ��������     : bitmapͼ���ļ�
 
******************************************************************************/
#ifndef _BITMAP_H_
#define _BITMAP_H_

#define     PACKED      __attribute__((packed))
typedef int LONG;
#include <stdint.h>

struct tagBITMAPFILEHEADER{ 
	uint16_t	bfType;   	// 位图文件的类型，必须为BM
	uint32_t    bfSize;   	// 位图文件的大小，以字节为单位
	uint16_t	bfReserved1;// 位图文件保留字，必须为0
	uint16_t	bfReserved2;// 位图文件保留字，必须为0
	uint32_t    bfOffBits; 		// 位图数据的起始位置，以相对于位图 // 文件头的偏移量表示，以字节为单位
} PACKED;

typedef struct tagBITMAPFILEHEADER BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{    
	uint32_t	biSize; 	// 本结构所占用字节数
	LONG	biWidth;  	// 位图的宽度，以像素为单位
	LONG	biHeight; 	// 位图的高度，以像素为单位
	uint16_t   	biPlanes; 	// 目标设备的级别，必须为1
	uint16_t   	biBitCount;	// 每个像素所需的位数，必须是1(双色),   // 4(16色)，8(256色)或24(真彩色)之一
	uint32_t  	biCompression;	// 位图压缩类型，必须是 0(不压缩),   // 1(BI_RLE8压缩类型)或2(BI_RLE4压缩类型)之一
	uint32_t  	biSizeImage; 	// 位图的大小，以字节为单位
	LONG	biXPelsPerMeter;// 位图水平分辨率，每米像素数
	LONG	biYPelsPerMeter;// 位图垂直分辨率，每米像素数
	uint32_t  	biClrUsed;		// 位图实际使用的颜色表中的颜色数
	uint32_t  	biClrImportant;	// 位图显示过程中重要的颜色数
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD { 
    uint8_t    rgbBlue;    // 蓝色的亮度(值范围为0-255)
    uint8_t    rgbGreen;   // 绿色的亮度(值范围为0-255)
    uint8_t    rgbRed;     // 红色的亮度(值范围为0-255)
    uint8_t    rgbReserved;// 保留，必须为0
} RGBQUAD; 

typedef struct tagDispBitmapT{
	uint16_t    w;
	uint16_t    h;
    RGBQUAD *pPalette;
    uint8_t    BitCount;
	uint8_t   *Bmp;
}DispBitmapT;

typedef enum {
	BITMAP_ERROR_SUCCESS = 0,
	BITMAP_ERROR_NO_MEMORY,
	BITMAP_ERROR_NO_FILE,
	BITMAP_ERROR_BAD_FILE,
	BITMAP_ERROR_DEFAULT
}BitmapErrorType;

BitmapErrorType BitmapDecode2FrameBuffer(uint8_t *pbyImgData, uint16_t wOffsetX, uint16_t wOffsetY, DispBitmapT *BitmapPtr);
BitmapErrorType BitmapFormatFrameBuffer(DispBitmapT *BitmapPtr);
BitmapErrorType BitmapCopy(DispBitmapT *DstPtr, uint16_t OffsetX, uint16_t OffsetY, DispBitmapT *SrcPtr);
BitmapErrorType BitmapDecode(uint8_t *pbyImgData, uint32_t dwuint8_ts, DispBitmapT *BitmapPtr);
BitmapErrorType BitmapEncode(DispBitmapT *BitmapPtr, uint8_t *pbyImgData, uint32_t *pdwuint8_ts);
#endif /*Bitmap.h*/
