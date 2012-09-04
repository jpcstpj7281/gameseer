/**----------------------------------------------------------------------------*/
/**         ATMEL Microcontroller Software Support  -  ROUSSET  -*/
/**----------------------------------------------------------------------------*/
/** The software is delivered "AS IS" without warranty or condition of any*/
/** kind, either express, implied or statutory. This includes without*/
/** limitation any warranty or condition with respect to merchantability or*/
/** fitness for any particular purpose, or against the infringements of*/
/** intellectual property rights of others.*/
/**----------------------------------------------------------------------------*/
/** File Name           : main.c*/
/** Object              : main application written in C*/
/** Creation            : FB   13/01/2003*/
/** 1.1 31/03/03 JPP	: Add DBGU message */
/**----------------------------------------------------------------------------*/

#include "vxWorks.h"

#include "ics1523.h"
#include "s1d13806.h"
#include "AT91RM9200.h"
#include "lib_AT91RM9200.h"
#include "drv/display/at91Display.h"
/* Master Clock */
#define MCK_KHz		60000	
 


/**************************************************************************************/
/* Externals*/
/**************************************************************************************/

#include "ics1523.c"
#include "s1d13806.c"
/** Function in init.c*/
typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

typedef struct tagRGBQUAD {
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;

#if 0
#define Transparent 1
typedef struct 
    {
    long  TotalVmem;        // Total video memory on the card.
    int   Width;            // Width (in pixels) of the mode.
    int   Height;           // Height (in pixels) of the mode.
    int   ColorDepth;       // Bits per pixel.
    int   Stride;           // Number of bytes from one line to the next.
    WORD  BytesPerPixel;    // 1,2 for 8BPP,15/16BPP
    } CONTROL_INFO,*LPCONTROL_INFO;
//---------------------------------------------------------------------------
//
//  BLT Info
//
//  The structure sent as an argument to all Blt routines.
//
//---------------------------------------------------------------------------
typedef struct 
    {
    int   ROP;
    int   SrcTop;
    int   SrcLeft;
    int   SrcWidth;
    int   SrcHeight;
    int   DstTop;
    int   DstLeft;
    int   DstWidth;
    int   DstHeight;
    int   PatternX,PatternY;

    int   Attribute;
    DWORD ColorBg;
    DWORD ColorFg;

    } BLT_INFO,*LPBLT_INFO;


static CONTROL_INFO Control;
#endif

#define LCD      0x01
#define CRT      0x02
#define TV       0x04

/**************************************************************************************/
/* Global variables*/
/**************************************************************************************/

/** Image data buffer declaration*/
/*static char		image_buf[ ( H_MAX_RES * V_MAX_RES * 3 ) + BMP_HEADER_SIZE ] ;*/

/** Message buffer*/
char MsgBuffer[256];

int gDisplayDef = Display_Def_0;
int gDisplayCfg = TFT_CRT_Display_Conf;//CRT_Display_Conf;
/**----------------------------------------------------------------------------*/
/** \fn    AT91F_FillDisplayMemory*/
/** \brief Fill display memory by filling 1.25 MB Display Memory*/
/**----------------------------------------------------------------------------*/
__inline void AT91F_FillDisplayMemory(void)
{
	char*					buf ;
	int i;
	short*					disp_mem = (short *) S1D13806_DISP_MEM_BASE ;
	
	/** Fill display memory by filling 1.25 MB Display Memory with 0xFF*/
	buf = ( char * ) S1D13806_DISP_MEM_BASE ;
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 2 ) ; i++, buf++ )
	{
		if ( ( i <  ( int ) ( ( ( display_def_desc.hdw * display_def_desc.vdw * 2 )/2 ) - ( display_def_desc.hdw * 2 * 5 ) ) )
		|| ( i > ( int ) ( ( ( display_def_desc.hdw * display_def_desc.vdw * 2 )/2 ) + ( display_def_desc.hdw * 2 * 5 ) ) ) )
			*buf = 0xFF ;
		else
			*buf = 0x00 ;
	}
	
	/** Fill display memory by filling 1.25 MB Display Memory with Green*/
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 2 )/2 ; i++, disp_mem++ )
		*disp_mem = GREEN_WORD_MASK ;
	disp_mem = ( short * ) S1D13806_DISP_MEM_BASE ;

	/** Fill display memory by filling 1.25 MB Display Memory with Blue*/
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 2 )/2 ; i++, disp_mem++ )
		*disp_mem = BLUE_WORD_MASK ;
	disp_mem = ( short * ) S1D13806_DISP_MEM_BASE ;

	/** Fill display memory by filling 1.25 MB Display Memory with Red*/
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 2 )/2 ; i++, disp_mem++ )
		*disp_mem = RED_WORD_MASK ;
	disp_mem = ( short * ) S1D13806_DISP_MEM_BASE ;

	/** Fill display memory by filling 1.25 MB Display Memory with Green + Blue*/
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 2 )/2 ; i++, disp_mem++ )
		*disp_mem = ( GREEN_WORD_MASK | BLUE_WORD_MASK ) ;
	disp_mem = ( short * ) S1D13806_DISP_MEM_BASE ;

	/** Fill display memory by filling 1.25 MB Display Memory with Red + Blue*/
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 2 )/2 ; i++, disp_mem++ )
		*disp_mem = ( RED_WORD_MASK | BLUE_WORD_MASK ) ;
	disp_mem = ( short * ) S1D13806_DISP_MEM_BASE ;

	/** Fill display memory by filling 1.25 MB Display Memory with Green + Red*/
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 2 )/2 ; i++, disp_mem++ )
		*disp_mem = ( GREEN_WORD_MASK | RED_WORD_MASK ) ;
	buf = ( char * ) S1D13806_DISP_MEM_BASE ;

	/** Clear display memory by filling 1.25 MB Display Memory with 0*/
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 2 ) ; i++, buf++ )
		*buf = 0x00 ;

	buf = ( char * ) S1D13806_DISP_MEM_BASE ;
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 4 ) ; i++, buf++ )
		*buf = 0x00 ;

	buf = ( char * ) S1D13806_DISP_MEM_BASE ;
/*	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw * 4 ) ; i++, buf++ )
		image_buf[i] = *buf ;*/
}

/**----------------------------------------------------------------------------*/
/** \fn    main*/
/** \brief */
/**----------------------------------------------------------------------------*/
STATUS at91_s1d1xInit()
{
	char 					message[64];
	int						i,ack ;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
	/* Configure PIO A to periph mode for IrDA problem of consumption*/
	/* Not associated to the configuration of Memory Display Controller*/ 
	AT91F_PIO_CfgPeriph(
		AT91C_BASE_PIOA, /* PIO controller base address*/
		((unsigned int) AT91C_PA23_TXD2), /* Peripheral A */
		0); /* Peripheral B */
 
	/* Disable pullup*/
	AT91F_PIO_CfgOutput(AT91C_BASE_PIOA,AT91C_PA23_TXD2);
	AT91C_BASE_PIOA->PIO_PPUDR =AT91C_PA23_TXD2;

	//////////////////////////////////////////////////////////////////////////////////
		
	/* Init PIO for Memory Display Controller */
	AT91F_PIO_CfgPeriph(
		AT91C_BASE_PIOC,
		((unsigned int) AT91C_PC6_NWAIT) 
		,0 );
	
	/* Init Static Memory Controller SMC2 for Memory Display Controller (EBI->SMC2->NCS2)*/
	/* Setup NCS2 for Memory Display Controller (EBI->SMC2) */

	
/* Specific configuration for AT91RM9200EK */
#ifdef __EK__
  /* Initialization of the Static Memory Controller for Chip Select 3 , ADD WAIT STATE 5 */
  AT91_SYS->EBI_SMC2_CSR[3] = (AT91C_SMC2_NWS & 0x5) | AT91C_SMC2_WSEN |
    (AT91C_SMC2_TDF & 0x100) | AT91C_SMC2_DBW;
#else
  AT91_SYS->EBI_SMC2_CSR[2] = (AT91C_SMC2_NWS & 0x4) | AT91C_SMC2_WSEN |
    (AT91C_SMC2_TDF & 0x100) | AT91C_SMC2_DBW;
#endif	
	
	  
#if 0
	AT91F_DBGU_Printk("\n\r-I- ==================================================\n\r");
	AT91F_DBGU_Printk("-I- AT91RM9200 Epson Embedded Memory Display Controller Test\n\r");
	AT91F_DBGU_Printk("-I- --------------------------------------------------------\n\r");

	/* System Timer initialization*/
	AT91F_ST_SetPeriodIntervalTimer(AT91C_BASE_ST, 0x3);	/* period <=> 100us*/
	AT91F_ST_EnableIt(AT91C_BASE_ST, AT91C_ST_PITS);
	

	AT91F_AIC_ConfigureIt (	AT91C_BASE_AIC,                        /* AIC base address*/
							AT91C_ID_SYS,                          /* System peripheral ID*/
							AT91C_AIC_PRIOR_HIGHEST,               /* Max priority*/
							AT91C_AIC_SRCTYPE_INT_LEVEL_SENSITIVE, /* Level sensitive*/
							AT91F_ST_ASM_HANDLER );						

	
	/* Enable ST interrupt*/
	AT91F_AIC_EnableIt(AT91C_BASE_AIC, AT91C_ID_SYS);
#endif

    /* ICS1523 Clock Generator Initialisation*/
    ack = AT91F_ICS1523_Init ( (unsigned int) Clock_Conf, (unsigned int) MCK_KHz) ;
    if ( ack == (int) ICS1523_ACCESS_OK )
    	sprintf (message, " \n\rICS1523 Clock Generator Init OK\n\r" ) ;
    else 
    	if ( ack == (int) ICS1523_ACCESS_ERROR )
    		sprintf (message, " \n\rICS1523 Clock Generator Init failed\n\r" ) ;
    


	/** Epson S1D13806 Initialisation FOR A CRT Monitor !!!!!!!!!!!*/
	AT91F_S1D13806_Init ( s1d13806_base,
					S1D13806_DISP_MEM_BASE,
					(unsigned int) CRT_Display_Conf,
					(unsigned int) gDisplayDef,
					(unsigned int) Char_Def_0, 
					(unsigned int) MCK_KHz ) ;

    
#if 0
	/** Fill Display Memory*/

	AT91F_FillDisplayMemory();

	/** Display Strings*/
  
	for ( i = 0 ; i < ( ( ( ( ( ( display_def_desc.hdw * display_def_desc.vdw * 2 ) / 16 ) / 16 ) / 8 ) + 2 ) * 4 ) ; i++ )
	{
		sprintf (message," Test OK ! %04d",i);
    	AT91F_S1D13806_16bpp_print_string ( s1d13806_base, message ) ;
	}

	/** Display Last String*/
	sprintf ( message, "          Auto Test Finished           ") ;
   	AT91F_S1D13806_16bpp_print_string ( s1d13806_base, message ) ;
#endif

/*while(1);*/
}

/*-------------------------------------------------------------------------*/

/*
** _DisplayFifo()
** 
** Description: Turns display FIFO on or off
*/
static void _DisplayFifo(BOOL activate)
   {
   unsigned val;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
   BYTE byte = s1d13806_base->S1D13806_OnChipReg.OCR_DM&0x7;
if (byte == 0x00 || byte == 0x01)  
   //if (_ActiveImageSurface->DisplayMode & LCD)
      {
      val = s1d13806_base->S1D13806_OnChipReg.OCR_LCDDM ;//seReadRegByte(REG_LCD_DISPLAY_MODE);

      if (activate)
         val &= ~0x80;
      else
         val |= 0x80;

      s1d13806_base->S1D13806_OnChipReg.OCR_LCDDM = val; //seWriteRegByte(REG_LCD_DISPLAY_MODE, val);
      }


   else //if (_ActiveImageSurface->DisplayMode & (CRT | TV))
      {
      val = s1d13806_base->S1D13806_OnChipReg.OCR_CRTDM ;//seReadRegByte(REG_CRTTV_DISPLAY_MODE);

      if (activate)
         val &= ~0x80;
      else
         val |= 0x80;

      s1d13806_base->S1D13806_OnChipReg.OCR_CRTDM = val ; //seWriteRegByte(REG_CRTTV_DISPLAY_MODE, val);
      }
   }

void seDisplayBlank(BOOL activate)
   {
   _DisplayFifo(!activate);
   }

int displayClear()
{
	DWORD*	buf ;
	int i;  
	//DOWRD*	disp_mem = (short *) S1D13806_DISP_MEM_BASE ;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
    int lcd_start_address = 0,	crt_start_address = 0;
	s1d13806_base->S1D13806_OnChipReg.OCR_LCDDBA_2 = ( char ) ( lcd_start_address >> 16 ) ;
	s1d13806_base->S1D13806_OnChipReg.OCR_LCDDBA_1 = ( char ) ( lcd_start_address >> 8 ) ;
	s1d13806_base->S1D13806_OnChipReg.OCR_LCDDBA_0 = ( char ) lcd_start_address ;
	s1d13806_base->S1D13806_OnChipReg.OCR_CRTDBA_2 = ( char ) ( crt_start_address >> 16 ) ;
	s1d13806_base->S1D13806_OnChipReg.OCR_CRTDBA_1 = ( char ) ( crt_start_address >> 8 ) ;
	s1d13806_base->S1D13806_OnChipReg.OCR_CRTDBA_0 = ( char ) crt_start_address ;
	
	/** Fill display memory by filling 1.25 MB Display Memory with 0xFF*/
	buf = ( DWORD * ) S1D13806_DISP_MEM_BASE ;
	for ( i = 0 ; i < ( int ) ( display_def_desc.hdw * display_def_desc.vdw )/2 ; i++, buf++ )
	{
		*buf = 0x0000 ;
	}	
}
void _WriteLut(int DisplayMode, BYTE *pLUT, int count)
{
   int idx, rgb;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
   if (DisplayMode == LCD)
      s1d13806_base->S1D13806_OnChipReg.OCR_LUTM = 1;//  seWriteRegByte(REG_LUT_MODE, 0x01); /* write to LCD LUT */
   else if ((DisplayMode == CRT) || (DisplayMode == TV))
      s1d13806_base->S1D13806_OnChipReg.OCR_LUTM = 2; //seWriteRegByte(REG_LUT_MODE, 0x02); /* write to CRT/TV LUT */
   else
      s1d13806_base->S1D13806_OnChipReg.OCR_LUTM = 0 ;//seWriteRegByte(REG_LUT_MODE, 0x00); /* write to LCD and CRT/TV LUT */


    s1d13806_base->S1D13806_OnChipReg.OCR_LUTBA = 0 ;//seWriteRegByte( REG_LUT_ADDR, 0 );

   for (idx = 0; idx < count; idx++)
      {
      for (rgb = 0; rgb < 3; rgb++)
         s1d13806_base->S1D13806_OnChipReg.OCR_LUTD = *pLUT++ ;//seWriteRegByte( REG_LUT_DATA, *pLUT++ );
      }
}


void WriteLut(unsigned surface, BYTE *pLUT, int count)
{
   unsigned regDisplayMode;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
   regDisplayMode =s1d13806_base->S1D13806_OnChipReg.OCR_DM&0x7;

    if(regDisplayMode<=1)
    {
         if (surface == 0)
            _WriteLut(LCD, pLUT, count); //seWriteLcdLut(pLut, count);
    
	}else if((regDisplayMode&1)==0 )
	{
    
         if (surface == 0)
            {
            if (regDisplayMode & TV)
               _WriteLut(TV, pLUT, count); // seWriteTvLut(pLut, count);
            else
               _WriteLut(CRT, pLUT, count); //seWriteCrtLut(pLut, count);
            }
    
	}else
    {
         if (surface == 0)
            {
            _WriteLut(LCD, pLUT, count); //seWriteLcdLut(pLut, count);
            _WriteLut(CRT, pLUT, count); //seWriteCrtLut(pLut, count);
            }
    
    }
}
int displayString(char* message )
{
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
	AT91F_S1D13806_16bpp_print_string ( s1d13806_base, message ) ;
	return 0;
}

long __pow(int x,int y)
{
	int i=0;
	long s=1;
	if(y>0)
	{
		for(i=0;i<y;i++)
		{
			s*=x;
		}	
	}
	return s;
}
int displayBmp(int x, int y, char* szfile)
{
	char buf[BMP_HEADER_SIZE+2]; 
	
	AT91S_S1D13806_BitmapDesc  bmp;
	AT91PS_S1D13806_BitmapDesc  pBmp=&bmp;
	int   i, j, k ;
	char  *display_mem ;
	char  *disp_src,*disp_buf;
	int 	dataSize=0;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
    int lcd_start_address = 0,	crt_start_address = 0;
    BYTE LUT[256*3];
    FILE *f = fopen(szfile,"r");
    if(!f) return -1;
    fread((char*)&bmp.type ,1, 2,f);
    fread((char*)&bmp.FileSize ,1, BMP_HEADER_SIZE-2,f);
 
    dataSize = pBmp->width*(pBmp->BitsPerPixel/8 );
	disp_buf= (char*)malloc(dataSize);


	s1d13806_base->S1D13806_OnChipReg.OCR_LCDDBA_2 = ( char ) ( lcd_start_address >> 16 ) ;
	s1d13806_base->S1D13806_OnChipReg.OCR_LCDDBA_1 = ( char ) ( lcd_start_address >> 8 ) ;
	s1d13806_base->S1D13806_OnChipReg.OCR_LCDDBA_0 = ( char ) lcd_start_address ;
	s1d13806_base->S1D13806_OnChipReg.OCR_CRTDBA_2 = ( char ) ( crt_start_address >> 16 ) ;
	s1d13806_base->S1D13806_OnChipReg.OCR_CRTDBA_1 = ( char ) ( crt_start_address >> 8 ) ;
	s1d13806_base->S1D13806_OnChipReg.OCR_CRTDBA_0 = ( char ) crt_start_address ;

   seDisplayBlank(TRUE);	
   
   if (pBmp->BitsPerPixel <= 8)  /* no DAC for 16 Bpp */
   {
      /* Init LUT entries */
      RGBQUAD rgbQ;
      BYTE* pLut = &LUT[0];
      
      for ( i=0; i<__pow(2,(double)pBmp->BitsPerPixel); i++ )
      {
         fread(&rgbQ,1,sizeof(RGBQUAD),f);
         
         *pLut++ = rgbQ.rgbRed;
         *pLut++ = rgbQ.rgbGreen;
         *pLut++ = rgbQ.rgbBlue;
      }
   }   
   
   	fseek(f,pBmp->ImageOffset,SEEK_SET);
	for (i=pBmp->height-1;i>=0;i--)
	{	
	    disp_src = disp_buf;
	    
	    display_mem = (char*) (s1d13806_display_desc.s1d13806_disp_mem_base_add);
	    display_mem +=  ((y+i)*display_def_desc.hdw*2);

	    fread((char*)(disp_src) ,1, dataSize,f);	
	    for	(j=0;j<pBmp->width;j++)
	    {
	    	if(pBmp->BitsPerPixel==8)
	    	{
	    		*(short*)(display_mem+(x+j)*2) = *(short*)disp_src;
	    		disp_src+=2;
	    	}else if(pBmp->BitsPerPixel==16)
	    	{
	    		*(short*)(display_mem+(x+j)*2) = *(short*)disp_src;
	    		disp_src+=2;
	    	}else if(pBmp->BitsPerPixel==24)
	    	{
			unsigned b, g, r;
		        b = (*disp_src++) >>3;
  		        g = (*disp_src++) <<3 & 0x07e0;
    		    	r = (*disp_src++) <<8 & 0xf800;
	    		*(short*)(display_mem+(x+j)*2) = (WORD) (b|g|r);
	    	}
	    }
	}
	free(disp_buf);
    if (pBmp->BitsPerPixel <= 8)  /* no DAC for 16 Bpp */
      WriteLut( 0, LUT, (int) __pow(2, (double)pBmp->BitsPerPixel) );
      	
   seDisplayBlank(FALSE);
	fclose(f);
	return 0;
}

#if 0

void InitModeInfo()
    {
    unsigned byte,colordepth;
    LPCONTROL_INFO lpInfo = &Control;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;

/*    lpInfo->TotalVmem = seGetAvailableMemorySize();*/

    // Crack the active display
	byte = s1d13806_base->S1D13806_OnChipReg.OCR_DM&0x7;
//    byte = seReadRegByte(0x1fc) & 0x7;
    if (byte == 0x00 || byte == 0x01)   // No display or LCD only...
        {
        lpInfo->Width = ((s1d13806_base->S1D13806_OnChipReg.OCR_LCDHDW+1)*8);
        lpInfo->Height= ( s1d13806_base->S1D13806_OnChipReg.OCR_LCDVDH) +1;
        colordepth =  s1d13806_base->S1D13806_OnChipReg.OCR_LCDDM; //seReadRegByte(0x40);
        }
    else // CRT or CRT+LCD, TV etc...
        {
        lpInfo->Width = ((s1d13806_base->S1D13806_OnChipReg.OCR_CRTHDW+1)*8);
        lpInfo->Height= ( s1d13806_base->S1D13806_OnChipReg.OCR_CRTVDH) +1;
        colordepth = s1d13806_base->S1D13806_OnChipReg.OCR_CRTDM; //seReadRegByte(0x60);
        }

    switch (colordepth & 0x7)
        {
        case 3: lpInfo->ColorDepth =  8; break;
        case 4: lpInfo->ColorDepth = 15; break;
        case 5: lpInfo->ColorDepth = 16; break;
        default:
            
        }
    
    switch (lpInfo->ColorDepth)
        {
        case 8:
            s1d13806_base->S1D13806_OnChipReg.OCR_BBLTC=0; //seWriteRegByte(0x101, 0x00);    //8BPP blit
            lpInfo->BytesPerPixel = 1;
            break;   

        case 15:
        case 16:
            s1d13806_base->S1D13806_OnChipReg.OCR_BBLTC=1;//seWriteRegByte(0x101, 0x01);    //15/16BPP blit
            lpInfo->BytesPerPixel = 2;
            break;
        }

    lpInfo->Stride = lpInfo->BytesPerPixel * lpInfo->Width;
    s1d13806_base->S1D13806_OnChipReg.OCR_LCDMAO = lpInfo->Stride/2;//seWriteRegWord(0x46,lpInfo->Stride/2);
    s1d13806_base->S1D13806_OnChipReg.OCR_CRTMAO = lpInfo->Stride/2;//seWriteRegWord(0x66,lpInfo->Stride/2);
    }

//---------------------------------------------------------------------------
// WaitForBltEnd()
//---------------------------------------------------------------------------
//
// Purpose: 
//
// Returns: 
//          
//
//---------------------------------------------------------------------------
static void WaitForBltEnd(void)
    {
    WORD tmp;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
    // wait until the Blt Engine is idle and Command Queue is empty
	while( s1d13806_base->S1D13806_OnChipReg.OCR_BBLTC&0x80);
    //while (seReadRegByte(0x100) & 0x80);

    // When MCLK != BUSCLK, the BLT will not start unless the BLT region
    // is read to help get the internal clocking state synchronized.
	tmp = *((volatile WORD*)(0x100000 + s1d13806_display_desc.s1d13806_disp_mem_base_add));
//    tmp  = *((volatile WORD*)gLinBltAddr);
    }
static void SolidFillBlt(LPBLT_INFO lpBlt)
    {
    WORD BytesPerPixel;
    DWORD dstAddr;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
    if (lpBlt->DstWidth == 0 || lpBlt->DstHeight == 0)
        return;

    BytesPerPixel = Control.BytesPerPixel;

    // wait for any pending blits to end

    WaitForBltEnd();

    // set Fill Blt

    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTO  = 0x0c; //seWriteRegByte(0x103, 0x0c);

    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTMAO =  Control.Stride/2 ;//seWriteRegWord(0x10c,	 Control.Stride/2);

    dstAddr = lpBlt->DstLeft*BytesPerPixel + lpBlt->DstTop * Control.Stride;
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTDSA_0 = dstAddr ; //seWriteRegByte(0x108, dstAddr);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTDSA_1 = dstAddr>>8 ; //seWriteRegByte(0x109, dstAddr>>8);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTDSA_2 = dstAddr>>16 ; // seWriteRegByte(0x10a, dstAddr>>16);

    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTW =lpBlt->DstWidth-1;//seWriteRegWord(0x110, lpBlt->DstWidth-1);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTH = lpBlt->DstHeight-1;// seWriteRegWord(0x112, lpBlt->DstHeight-1);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTBC = lpBlt->ColorFg;// seWriteRegWord(0x118, lpBlt->ColorFg);

    // Engage the blt engine.

    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTC = 0x80 ;//seWriteRegByte(0x100,0x80);
    }

//---------------------------------------------------------------------------
// PatternFillBlt()
//---------------------------------------------------------------------------
//
// Purpose: Performs Pattern Fill Blit with ROP or Transparent.
//
// Source :
//      PatStart : video memory offset to the start of the pattern.
//                 
//      Pattern Phase:
//          lpBlt->PatternX : x - coord of the first pattern pixel  
//          lpBlt->PatternY : y - coord of the first pattern pixel  
//
// Destination rectangle:
//      lpBlt->DstLeft
//      lpBlt->DstTop
//      lpBlt->DstWidth  
//      lpBlt->DstHeight 
//      
//  Transparent Pattern Fill Blt:
//  - transparent color in lpBlt->ColorBg
//  Solid Pattern Fill Blt:
//  - ROP in lpBlt->ROP
// 
//  Note:
//  Some cases cannot be handled by hardware.    
//  PatStart is assumed to be aligned on 64 byte boundary for 8 Bpp mode,
//  on 128 boundary for 15/16 Bpp modes
//---------------------------------------------------------------------------
static void PatternFillBlt(LPBLT_INFO lpBlt,DWORD PatStart)
    {
    int BytesPerPixel;
    DWORD dstAddr;
	AT91PS_S1D13806_Desc	s1d13806_base = (AT91PS_S1D13806_Desc) S1D13806_BASE;
    if (lpBlt->DstWidth == 0 || lpBlt->DstHeight == 0)
        return;

    BytesPerPixel = Control.BytesPerPixel;

    // eliminate cases we cannot do in hardware

    if ((lpBlt->Attribute & 1/*Transparent*/) || lpBlt->ROP == 0x0c || lpBlt->ROP == 0x03)
        {
        if (lpBlt->DstWidth == 1 || (lpBlt->DstWidth == 2 && BytesPerPixel == 1))
            return;
        }

    // The pattern is 8pixels*8lines.
    // Adjust pattern start for x,y start phases
    // add 8*PhaseY*BytesPerPixel + PhaseX*BytesPerPixel

    PatStart += lpBlt->PatternY*BytesPerPixel*8 + 
                    lpBlt->PatternX*BytesPerPixel;

    // Wait for any pending blit to end

    WaitForBltEnd();

    // program relevant blt registers

    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTSSA_0 = PatStart;//seWriteRegByte(0x104,PatStart);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTSSA_1 = PatStart >> 8;//seWriteRegByte(0x105,PatStart >> 8);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTSSA_2 = PatStart >> 16; //seWriteRegByte(0x106,PatStart >> 16);

    if (lpBlt->Attribute & Transparent)
        {
        s1d13806_base->S1D13806_OnChipReg.OCR_BBLTBC = lpBlt->ColorBg;//seWriteRegWord(0x114, lpBlt->ColorBg);
        s1d13806_base->S1D13806_OnChipReg.OCR_BBLTO = 0x07; //seWriteRegByte(0x103, 0x07);
        }
    else
        {
        s1d13806_base->S1D13806_OnChipReg.OCR_BBLTRCCE =lpBlt->ROP ; //seWriteRegByte(0x102, lpBlt->ROP);
        s1d13806_base->S1D13806_OnChipReg.OCR_BBLTO = 0x06;	 	//seWriteRegByte(0x103, 0x06);
        }

    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTMAO = Control.Stride/2 ; //seWriteRegWord(0x10c, Control.Stride/2);

    dstAddr = lpBlt->DstLeft*BytesPerPixel + lpBlt->DstTop * Control.Stride;
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTDSA_0 = dstAddr ; //seWriteRegByte(0x108, dstAddr);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTDSA_1 = dstAddr>>8 ; //seWriteRegByte(0x109, dstAddr>>8);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTDSA_2 = dstAddr>>16 ; // seWriteRegByte(0x10a, dstAddr>>16);

    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTW =lpBlt->DstWidth-1;//seWriteRegWord(0x110, lpBlt->DstWidth-1);
    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTH = lpBlt->DstHeight-1;// seWriteRegWord(0x112, lpBlt->DstHeight-1);

    // Engage the blt engine.

    s1d13806_base->S1D13806_OnChipReg.OCR_BBLTC = 0x80 ;//seWriteRegByte(0x100,0x80);
}


void DrawRect(int x,int y,int width,int height,DWORD color)
    {
    BLT_INFO Blt;
    Blt.DstWidth = width;
    Blt.DstHeight = height;
    Blt.DstTop = y;
    Blt.DstLeft = x;
    Blt.Attribute = 0;  
    Blt.ColorFg = color;
    SolidFillBlt(&Blt);
    }
static WORD rand16(void)
    {
    // Bit 15 of MS rand() is always 0. We want full 16 bit range.

    return ((rand() << 1) | (rand() & 1)); 
    }

static void RandomBltValues(LPBLT_INFO lpBlt)
    {
    WORD nMaxX = Control.Width;
    WORD nMaxY = Control.Height;

    lpBlt->ColorFg = rand16();
    lpBlt->ColorBg = rand16();

    lpBlt->ROP = rand() & 0xF;

    lpBlt->PatternX = rand() & 0x7;
    lpBlt->PatternY = rand() & 0x7;

    // Make sure the foreground and background colors are different.
    
    if ((lpBlt->ColorBg & 0xFF) == (lpBlt->ColorFg & 0xFF))
        lpBlt->ColorBg ^= 0xFF;

    lpBlt->Attribute = rand() & Transparent;

    //
    // Dst location and size.
    //

    do
        {
        lpBlt->DstTop = (WORD)(rand() % nMaxY-10);
        } while (lpBlt->DstTop >= nMaxY - 1);

    do
        {
        lpBlt->DstLeft = (WORD)(rand() & 0x07FF);
        } while (lpBlt->DstLeft +8 >= nMaxX - 1);

    do
        {
        lpBlt->DstWidth = (WORD)(rand() % nMaxX);
        if (!lpBlt->DstWidth)
            lpBlt->DstWidth++;          //width cannot be 0

        } while (lpBlt->DstLeft + lpBlt->DstWidth >= nMaxX);

    do
        {
        lpBlt->DstHeight = (WORD)(rand() & 0x1FF);
        if (!lpBlt->DstHeight)
            lpBlt->DstHeight++;          //height cannot be 0
        } while (lpBlt->DstTop + lpBlt->DstHeight >= nMaxY-2);
    }

DWORD rotl(DWORD data,int n)
{
	return data<<n;
}
DWORD CreateRandomPattern(LPBLT_INFO lpBlt)
    {
    int i;
    DWORD PatternAddress;
    WORD  pattern[8*8];
    DWORD data = rand16();

    // generate the 8x8 pattern 

    for (i = 0; i < (8*8*Control.BytesPerPixel)/2 ;i++)
        {
        pattern[i] = (WORD)data;
        data = rotl(data,1);
        }

    // for transparent fills, paste in transparent pixels

    if (lpBlt->Attribute & Transparent)
        {
        data = rand16();
        if (Control.BytesPerPixel == 2)
            {
            WORD *ptrw = (WORD*)pattern;

            // paste in randomly transparent pixels

            for (i = 0; i < 36; i++, data >>= 1, ptrw++)
                {
                if (i == 32)
                    data = lpBlt->ColorFg;
                
                if (data & 1)
                    *ptrw = (WORD)lpBlt->ColorBg;
                }
            }
        else
            {
            BYTE *ptrb = (BYTE*)pattern;

            // paste in randomly transparent pixels

            for (i = 0; i < 36; i++, data >>= 1, ptrb++)
                {
                if (i == 32)
                    data = lpBlt->ColorFg;
                
                if (data & 1)
                    *ptrb = (BYTE)lpBlt->ColorBg;
                }
            }
        }

    // Copy the pattern in the video memory. Here we place it in the
    // first 128 byte aligned address in the offscreen memory.

   // PatternAddress = (gOffscreenOffset+127) & 0xffffff80L; 
    PatternAddress = ( Control.Height * Control.Stride+127) & 0xffffff80L; 
    memcpy((DWORD*)( s1d13806_display_desc.s1d13806_disp_mem_base_add+PatternAddress),pattern,(8*8*Control.BytesPerPixel));
    return PatternAddress;
    }
//---------------------------------------------------------------------------
//
// Demonstrate Pattern Fill Blt.
//
//---------------------------------------------------------------------------
 void ShowPatternFillBlt(void)
    {
    BLT_INFO Blt;
    DWORD pattaddress;
    int count = 100;
//    ClearVideoMemory();

    while (count--)
        {
        RandomBltValues(&Blt);

        // eliminate cases hardware cannot handle

        if ((Blt.Attribute & Transparent) || Blt.ROP == 0x0c || Blt.ROP == 0x03)
            {
            if (Blt.DstWidth == 1 || (Blt.DstWidth == 2 && Control.BytesPerPixel == 1))
                continue;
            }

        pattaddress = CreateRandomPattern(&Blt);
        PatternFillBlt(&Blt,pattaddress);
        }
    }




#endif



