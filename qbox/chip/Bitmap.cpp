/******************************************************************************


  ��������     : bitmapͼ���ļ�

******************************************************************************/

#include "Bitmap.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BI_RGB                  0L
#define BI_RLE8                 1L
#define BI_RLE4                 2L
#define BI_BITFIELDS            3L
#define BM16_565_RED_MASK		0x001F   /*0xF800*/
#define BM16_565_GREEN_MASK		0x07E0
#define BM16_565_BLUE_MASK		0xF800   /*0x001F*/
#define BM16_565_RED_SHIFT		11
#define BM16_565_GREEN_SHIFT	5
#define BM16_565_BLUE_SHIFT		0

#define     FRAME_LINE_WIDTH        (1600*3)
static RGBQUAD bmiColors[256];
static uint8_t *pMapTable[256];

BitmapErrorType BitmapDecode1Bit(uint8_t *pbyImgData, int32_t iWidth, int32_t iHeight, uint8_t *pbyOut)
{
    int32_t i, j, lineWidth, lineAlign;
    uint8_t data;
    uint8_t *pbySrc, *pbyDst;
#if 0
    pbySrc = (uint8_t *)malloc(256*8);
    memset(pbySrc, 0, 256*8);
    for(i = 0; i < 256; i++)
    {
        pMapTable[i] = pbySrc + i*8;
        data = i;
        for(j = 0; j < 8; j++)
        {
            if(data & 0x80)
            {
                pMapTable[i][j] = 0x01;
            }
            data <<= 1;
        }
    }
#endif    
    lineWidth = (iWidth+7)>>3;
    lineAlign = ((iWidth>>3) + 3) & (-4);
    pbyImgData = pbyImgData + lineAlign*(iHeight - 1);
    for(i = 0; i < iHeight; i++)
    {
#if 0
        pbySrc = pbyImgData;
        pbyDst = pbyOut;
        for(j = 0; j < iWidth; j += 8)
        {
            memcpy(pbyDst, pMapTable[*pbySrc++], 8);
            pbyDst += 8;
        }
        pbyImgData -= lineAlign;
        pbyOut += lineWidth;
#else
        memcpy(pbyOut, pbyImgData, lineWidth);
        pbyOut += lineWidth;
        pbyImgData -= lineAlign;
#endif
    }

    //free(pMapTable[0]);

    return BITMAP_ERROR_SUCCESS;
}

BitmapErrorType BitmapDecode8Bits(uint8_t *pbyImgData, int32_t iWidth, int32_t iHeight, uint8_t *pbyOut)
{
    int32_t i, j, lineWidth, lineAlign;
    uint8_t data;
    uint8_t *pbySrc, *pbyDst;

    lineWidth = iWidth;
    lineAlign = (iWidth + 3) & (-4);
    pbyImgData = pbyImgData + lineAlign*(iHeight - 1);
    for(i = 0; i < iHeight; i++)
    {
        memcpy(pbyOut, pbyImgData, lineWidth);
        pbyOut += lineWidth;
        pbyImgData -= lineAlign;
    }

    return BITMAP_ERROR_SUCCESS;
}

BitmapErrorType BitmapDecode24Bits(uint8_t *pbyImgData, int32_t iWidth, int32_t iHeight, uint8_t *pbyOut)
{
    int32_t i, lineWidth, lineAlign;

    lineWidth = iWidth*3;
    lineAlign = (iWidth*3 + 3) & (-4);
    pbyImgData = pbyImgData + lineAlign*(iHeight - 1);
    for(i = 0; i < iHeight; i++)
    {
        memcpy(pbyOut, pbyImgData, lineWidth);
        pbyOut += lineWidth;
        pbyImgData -= lineAlign;
    }

    return BITMAP_ERROR_SUCCESS;
}

BitmapErrorType BitmapDecode2FrameBuffer(uint8_t *pbyImgData, uint16_t wOffsetX, uint16_t wOffsetY, DispBitmapT *BitmapPtr)
{
	BITMAPFILEHEADER biMapFileHeader;
	BITMAPINFOHEADER biMapInfoHeader;
    int32_t width, height;
    int32_t i, j, lineWidth, lineAlign;
    uint8_t *pIn = pbyImgData;
    uint8_t *pOut, *pInPixel, *pOutPixel;

    memcpy(&biMapFileHeader, pIn, sizeof(biMapFileHeader));
    pIn += sizeof(biMapFileHeader);
    memcpy(&biMapInfoHeader, pIn, sizeof(biMapInfoHeader));
    pIn += sizeof(biMapInfoHeader);

    if(biMapFileHeader.bfType != 0x4d42)
    {
        printf("not a bitmap file\n", 0, 0, 0, 0);
        return BITMAP_ERROR_BAD_FILE;
    }
    if((biMapInfoHeader.biBitCount != 24) && (biMapInfoHeader.biBitCount != 8) && 
       (biMapInfoHeader.biBitCount != 1))
    {
    	printf("not support bitmap file\n", 0, 0, 0, 0);
        return BITMAP_ERROR_DEFAULT;       
    }
    if((biMapInfoHeader.biWidth > 1920) || (biMapInfoHeader.biHeight > 1200))
    {
    	printf("too bigger bitmap file\n", 0, 0, 0, 0);
        return BITMAP_ERROR_NO_MEMORY;          
    }
    
    printf("biMapInfoHeader [biWidth:%d biHeight:%d biBitCount:%d]\n",
		biMapInfoHeader.biWidth, biMapInfoHeader.biHeight, biMapInfoHeader.biBitCount, 0);	

    if(biMapInfoHeader.biBitCount != 24)
    {
        memcpy(bmiColors, pIn, (0x04<<biMapInfoHeader.biBitCount));
        BitmapPtr->pPalette = bmiColors;
    }
    
    BitmapPtr->w = wOffsetX + biMapInfoHeader.biWidth;
    BitmapPtr->h = wOffsetY + biMapInfoHeader.biHeight;
    BitmapPtr->BitCount = 24;

    pIn = pbyImgData + biMapFileHeader.bfOffBits;
    pOut = BitmapPtr->Bmp + wOffsetY * FRAME_LINE_WIDTH + wOffsetX * 3;;
    width = biMapInfoHeader.biWidth;
    height = biMapInfoHeader.biHeight;
    lineWidth = (width * biMapInfoHeader.biBitCount + 7) >> 3;
    lineAlign = (lineWidth + 3) & (-4);
    pIn = pIn + lineAlign*(height-1);

    if(biMapInfoHeader.biBitCount == 24)
    {
        for(i = 0; i < height; i++)
        {
            memcpy(pOut, pIn, lineWidth);
            pOut += FRAME_LINE_WIDTH;
            pIn -= lineAlign;
        }
    }
    else if(biMapInfoHeader.biBitCount == 8)
    {
        uint8_t pixel;
        for(i = 0; i < height; i++)
        {
            pOutPixel = pOut;
            pInPixel = pIn;
            for(j = 0; j < width; j++)
            {
                pixel = *pInPixel++;
                *pOutPixel++ = bmiColors[pixel].rgbBlue;
                *pOutPixel++ = bmiColors[pixel].rgbGreen;
                *pOutPixel++ = bmiColors[pixel].rgbRed;
            }
            pOut += FRAME_LINE_WIDTH;
            pIn -= lineAlign;
        }
    }
    else if(biMapInfoHeader.biBitCount == 1)
    {
        uint8_t pixel;
        uint8_t *pTemp;
        int32_t z;
        
        pOutPixel = (uint8_t *)malloc(256*8);
        memset(pOutPixel, 0, 256*8);
        for(i = 0; i < 256; i++)
        {
            pMapTable[i] = pOutPixel + i*8;
            pixel = i;
            for(j = 0; j < 8; j++)
            {
                if(pixel & 0x80)
                {
                    pMapTable[i][j] = 0x01;
                }
                pixel <<= 1;
            }
        }
        
        for(i = 0; i < height; i++)
        {
            pOutPixel = pOut;
            pInPixel = pIn;
            for(j = 0; j < width; j += 8)
            {
                pixel = *pInPixel++;
                pTemp = pMapTable[pixel];
                for(z = 0; z < 8; z++)
                {
                    pixel = *pTemp++;
                    *pOutPixel++ = bmiColors[pixel].rgbBlue;
                    *pOutPixel++ = bmiColors[pixel].rgbGreen;
                    *pOutPixel++ = bmiColors[pixel].rgbRed;
                }
            }
            pOut += FRAME_LINE_WIDTH;
            pIn -= lineAlign;
        }

        free(pMapTable[0]);
    }

    return BITMAP_ERROR_SUCCESS;
}

BitmapErrorType BitmapFormatFrameBuffer(DispBitmapT *BitmapPtr)
{
    uint8_t *pSrc, *pDst;
    int32_t i, width, height;

    BitmapPtr->pPalette = NULL;
    pSrc = BitmapPtr->Bmp;
    pDst = BitmapPtr->Bmp;
    width = BitmapPtr->w * 3;
    height = BitmapPtr->h;
    for(i = 0; i < height; i++)
    {
        memcpy(pDst, pSrc, width);
        pDst += width;
        pSrc += FRAME_LINE_WIDTH;
    }
    
    return BITMAP_ERROR_SUCCESS;
}

BitmapErrorType BitmapCopy(DispBitmapT *DstPtr, uint16_t OffsetX, uint16_t OffsetY, DispBitmapT *SrcPtr)
{
    int32_t width, height;
    int32_t i, j;
    uint8_t *pSrc, *pDst;
    
    if((SrcPtr->BitCount != 8) && (SrcPtr->BitCount != 24))
    {
        return BITMAP_ERROR_DEFAULT;
    }
    
    if(DstPtr->BitCount != SrcPtr->BitCount)
    {
        return BITMAP_ERROR_DEFAULT;
    }

    if((OffsetX > DstPtr->w) || (OffsetY > DstPtr->h))
    {
        return BITMAP_ERROR_DEFAULT;
    }

    if((OffsetX + SrcPtr->w) > DstPtr->w)
    {
        width = DstPtr->w - OffsetX;
    }
    else
    {
        width = SrcPtr->w;
    }

    if((OffsetY + SrcPtr->h) > DstPtr->h)
    {
        height = DstPtr->h - OffsetY;
    }
    else
    {
        height = SrcPtr->h;
    }

    if(SrcPtr->BitCount == 8)
    {
        for(i = 0; i < height; i++)
        {
            pDst = DstPtr->Bmp + (DstPtr->w * (OffsetY + i) + OffsetX) * 1;
            pSrc = SrcPtr->Bmp + SrcPtr->w * i * 1;
            memcpy(pDst, pSrc, width);
        }
    }
    else if(SrcPtr->BitCount == 24)
    {
        for(i = 0; i < height; i++)
        {
            pDst = DstPtr->Bmp + (DstPtr->w * (OffsetY + i) + OffsetX) * 3;
            pSrc = SrcPtr->Bmp + SrcPtr->w * i * 3;
            memcpy(pDst, pSrc, width*3);
        }
    }

    return BITMAP_ERROR_SUCCESS;
}

BitmapErrorType BitmapDecode(uint8_t *pbyImgData, uint32_t dwBytes, DispBitmapT *BitmapPtr)
{
	BITMAPFILEHEADER biMapFileHeader;
	BITMAPINFOHEADER biMapInfoHeader;
    int32_t width, height;
    int32_t i, lineWidth, lineAlign;
    uint8_t *pIn = pbyImgData;
    uint8_t *pOut;

    memcpy(&biMapFileHeader, pIn, sizeof(biMapFileHeader));
    pIn += sizeof(biMapFileHeader);
    memcpy(&biMapInfoHeader, pIn, sizeof(biMapInfoHeader));
    pIn += sizeof(biMapInfoHeader);

    if(biMapFileHeader.bfType != 0x4d42)
    {
        printf("not a bitmap file\n", 0, 0, 0, 0);
        return BITMAP_ERROR_BAD_FILE;
    }
    if((biMapInfoHeader.biBitCount != 24) && (biMapInfoHeader.biBitCount != 8) && 
       (biMapInfoHeader.biBitCount != 1))
    {
    	printf("not support bitmap file\n", 0, 0, 0, 0);
        return BITMAP_ERROR_DEFAULT;       
    }
    if((biMapInfoHeader.biWidth > 1920) || (biMapInfoHeader.biHeight > 1200))
    {
    	printf("too bigger bitmap file\n", 0, 0, 0, 0);
        return BITMAP_ERROR_NO_MEMORY;          
    }
    
    printf("biMapInfoHeader [biWidth:%d biHeight:%d biBitCount:%d]\n",
		biMapInfoHeader.biWidth, biMapInfoHeader.biHeight, biMapInfoHeader.biBitCount, 0);	

    if(biMapInfoHeader.biBitCount != 24)
    {
        memcpy(bmiColors, pIn, (0x04<<biMapInfoHeader.biBitCount));
        BitmapPtr->pPalette = bmiColors;
    }
    
    BitmapPtr->w = biMapInfoHeader.biWidth;
    BitmapPtr->h = biMapInfoHeader.biHeight;
    BitmapPtr->BitCount = biMapInfoHeader.biBitCount;

    pIn = pbyImgData + biMapFileHeader.bfOffBits;
    pOut = BitmapPtr->Bmp;
    width = biMapInfoHeader.biWidth;
    height = biMapInfoHeader.biHeight;
    lineWidth = (width * biMapInfoHeader.biBitCount + 7) >> 3;
    lineAlign = (lineWidth + 3) & (-4);
    pIn = pIn + lineAlign*(height-1);
    
    for(i = 0; i < height; i++)
    {
        memcpy(pOut, pIn, lineWidth);
        pOut += lineWidth;
        pIn -= lineAlign;
    }

    return BITMAP_ERROR_SUCCESS;
}

BitmapErrorType BitmapEncode(DispBitmapT *BitmapPtr, uint8_t *pbyImgData, uint32_t *pdwBytes)
{
 	BITMAPFILEHEADER biMapFileHeader;
	BITMAPINFOHEADER biMapInfoHeader;
    uint8_t *pIn, *pOut;
    int32_t i, line, imgSize;

    line = BitmapPtr->w;
    line = (line*3 + 3) & (-4);
    imgSize = line * BitmapPtr->h;
    biMapFileHeader.bfType = 0x4d42;
    biMapFileHeader.bfSize = imgSize + sizeof(biMapFileHeader) + sizeof(biMapInfoHeader);
    biMapFileHeader.bfReserved1 = 0;
    biMapFileHeader.bfReserved2 = 0;
    biMapFileHeader.bfOffBits = sizeof(biMapFileHeader) + sizeof(biMapInfoHeader);

    biMapInfoHeader.biSize = sizeof(biMapInfoHeader);
    biMapInfoHeader.biWidth = BitmapPtr->w;
    biMapInfoHeader.biHeight = BitmapPtr->h;
    biMapInfoHeader.biPlanes = 1;
    biMapInfoHeader.biBitCount = 24;
    biMapInfoHeader.biCompression = 0;
    biMapInfoHeader.biSizeImage = imgSize;
    biMapInfoHeader.biXPelsPerMeter = 0;
    biMapInfoHeader.biYPelsPerMeter = 0;
    biMapInfoHeader.biClrUsed = 0;
    biMapInfoHeader.biClrImportant = 0;

    pOut = pbyImgData;
    memcpy(pOut, &biMapFileHeader, sizeof(biMapFileHeader));
    pOut += sizeof(biMapFileHeader);
    memcpy(pOut, &biMapInfoHeader, sizeof(biMapInfoHeader));
    pOut += sizeof(biMapInfoHeader);
    
    pIn = BitmapPtr->Bmp;
    pIn += line*(BitmapPtr->h - 1);    
    for(i = 0; i < BitmapPtr->h; i++)
    {
        memcpy(pOut, pIn, line);
        pOut += line;
        pIn -= line;
    }
    *pdwBytes = biMapFileHeader.bfSize;

    return BITMAP_ERROR_SUCCESS;
}

BitmapErrorType BitmapEncode16Bit(DispBitmapT *BitmapPtr, uint8_t *pbyImgData, uint32_t *pdwBytes)
{
 	BITMAPFILEHEADER biMapFileHeader;
	BITMAPINFOHEADER biMapInfoHeader;
    uint32_t            quadRGB[3];
    uint8_t *pIn, *pOut;
    int32_t i, line, imgSize;

    line = BitmapPtr->w;
    line = (line*2 + 3) & (-4);
    imgSize = line * BitmapPtr->h;
    biMapFileHeader.bfType = 0x4d42;
    biMapFileHeader.bfSize = imgSize + sizeof(biMapFileHeader) + sizeof(biMapInfoHeader) + sizeof(quadRGB);
    biMapFileHeader.bfReserved1 = 0;
    biMapFileHeader.bfReserved2 = 0;
    biMapFileHeader.bfOffBits = sizeof(biMapFileHeader) + sizeof(biMapInfoHeader) + sizeof(quadRGB);

    biMapInfoHeader.biSize = sizeof(biMapInfoHeader);
    biMapInfoHeader.biWidth = BitmapPtr->w;
    biMapInfoHeader.biHeight = BitmapPtr->h;
    biMapInfoHeader.biPlanes = 1;
    biMapInfoHeader.biBitCount = 16;
    biMapInfoHeader.biCompression = BI_BITFIELDS;
    biMapInfoHeader.biSizeImage = imgSize;
    biMapInfoHeader.biXPelsPerMeter = 0;
    biMapInfoHeader.biYPelsPerMeter = 0;
    biMapInfoHeader.biClrUsed = 0;
    biMapInfoHeader.biClrImportant = 0;

    quadRGB[0] = BM16_565_RED_MASK;
    quadRGB[1] = BM16_565_GREEN_MASK;
    quadRGB[2] = BM16_565_BLUE_MASK;
    
    pOut = pbyImgData;
    memcpy(pOut, &biMapFileHeader, sizeof(biMapFileHeader));
    pOut += sizeof(biMapFileHeader);
    memcpy(pOut, &biMapInfoHeader, sizeof(biMapInfoHeader));
    pOut += sizeof(biMapInfoHeader);
    memcpy(pOut, &quadRGB, sizeof(quadRGB));
    pOut += sizeof(quadRGB);
    
    pIn = BitmapPtr->Bmp;
    pIn += line*(BitmapPtr->h - 1);    
    for(i = 0; i < BitmapPtr->h; i++)
    {
        memcpy(pOut, pIn, line);
        pOut += line;
        pIn -= line;
    }
    *pdwBytes = biMapFileHeader.bfSize;

    return BITMAP_ERROR_SUCCESS;
}

