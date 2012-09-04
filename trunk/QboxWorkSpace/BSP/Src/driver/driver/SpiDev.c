/******************************************************************************


******************************************************************************/
#include <semLib.h>
#include <logLib.h>

#include "sys_include.h"
#include "IicDev.h"

#include "driver_interface.h"







#define SPI_CS3  6
#define SPI_CS2  5
#define SPI_CS1  4
#define SPI_CS0  3
#define SPI_CLK 2
#define SPI_DI  0
#define SPI_DO  1

#define SPI_DELAY(n)                delayNSec(n); 
#define SPI_CLOCK_LOW_TIME          (1)
#define SPI_CLOCK_HIGH_TIME         (1)
#define SPI_START_TIME              (1)
#define SPI_STOP_TIME               (1)





SEM_ID semSpiLock = 0;

/*系统延时时间 根据实际情况调试*/
void delayNSec(int iN)
{
 //   BYTE byBase;             /*延时循环参数*/
    while(iN --);
}

/***********************************************

	函数描述: SPI 接口初始化，本系统使用GPIO进行SPI
				   时序模拟
	参数描述:
		无
	函数返回值:
		无
************************************************/
void dev_SpiInit(void)
{
    FAST int iLocKey;
    DWORD dwPinMask = 0;

    semSpiLock = semBCreate( SEM_Q_PRIORITY, SEM_FULL);

    iLocKey = intLock ();
    /* initially at power up SDA has pull down because it is used as strap pin.
     * the PCI_ARB strap pin which is GPIO 2 should be driven high inorder to 
     * have a pull up on SDA line. This is required by this board design
     */
    dwPinMask = DATA(SPI_DO) | DATA(SPI_CLK) | CLOCK(SPI_CS0) | CLOCK(SPI_CS1) | CLOCK(SPI_CS2) | CLOCK(SPI_CS3);

    PIOA_IDR = dwPinMask;                 /*关中断*/

    PIOA_PPUER = dwPinMask;                /*关输出上拉*/

    /*PIOA_MDER = dwPinMask;   */             /*设开漏*/

    PIOA_SODR = dwPinMask;                /*设置输出寄存器*/

    PIOA_OER = dwPinMask;                 /*使能输出*/

    PIOA_PER = dwPinMask;                 /*IO口使能*/
///////////////////////////////////////////////////////////
    PMC_PCER = (DWORD)(0x1 << 2);

    dwPinMask = DATA(SPI_DI);

    PIOA_IDR = dwPinMask;                 /*关中断*/

    PIOA_PPUER = dwPinMask;                /*关输出上拉*/

    /*PIOA_MDER = dwPinMask;   */             /*设开漏*/

    PIOA_SODR = dwPinMask;                /*设置输出寄存器*/

    PIOA_ODR = dwPinMask;                 /*关闭输出*/

    PIOA_PER = dwPinMask;                 /*IO口使能*/
////////////////////////////////////////////////////////////

    intUnlock (iLocKey);
}


LOCAL void PinClkWrite(BYTE byLevel)
{
    switch(byLevel)
    {
        case HIGH:
            PIOA_SODR = DATA(SPI_CLK);   /*置高电平*/
            break;
        case LOW:
            PIOA_CODR = DATA(SPI_CLK);   /*置低电平*/
            break;
        default:
            break;
    }
}

LOCAL void PinCsWrite(BYTE byPort, BYTE byLevel)
{
    byPort += 3; 
    switch(byLevel)
    {
        case HIGH:
            PIOA_SODR = DATA(byPort);   /*置高电平*/
            break;
        case LOW:
            PIOA_CODR = DATA(byPort);   /*置低电平*/
            break;
        default:
            break;
    }
}

/*读取数据管脚状态*/
LOCAL BYTE PinDiRead(void)
{
    DWORD dwPioPdsr;
    PIOA_ODR = DATA(SPI_DI);
    dwPioPdsr = PIOA_PDSR;                        /*获取当前状态*/
/*    return ( dwPioPdsr | DATA(sCurI2cPort.byDataPin) ? 1 : 0);*/
    PIOA_OER = DATA(SPI_DI);    

    return ( (dwPioPdsr & DATA(SPI_DI)) ? 1 : 0);    
}

LOCAL void PinDoWrite(BYTE byLevel)
{    
    switch(byLevel)
    {
        case HIGH:
            PIOA_SODR = DATA(SPI_DO);   /*置高电平*/
            break;
        case LOW:
            PIOA_CODR = DATA(SPI_DO);   /*置低电平*/
            break;
        default:
            break;
    }
}

/*I2C数据信号线控制*/
void PinADo(BYTE x)
{
    int iLocKey;    

    iLocKey = intLock ();

    PinDoWrite(x);
    
    intUnlock (iLocKey); 
}

/*I2C数据信号线控制*/
void PinAClk(BYTE x)
{
    int iLocKey;    

    iLocKey = intLock ();

    PinClkWrite(x);
    
    intUnlock (iLocKey); 
}

/*I2C数据信号线控制*/
void PinACs(BYTE byPort, BYTE x)
{
    int iLocKey;    

    iLocKey = intLock();
    PinCsWrite(byPort, x);
    
    intUnlock (iLocKey); 
}

/*I2C读比特位*/
BYTE SpiReadBit(void)
{
    volatile BYTE x;
    FAST int iLocKey;

    PinAClk(LOW);
    SPI_DELAY(SPI_CLOCK_LOW_TIME );
    PinAClk(HIGH);
    SPI_DELAY(SPI_CLOCK_HIGH_TIME);

    iLocKey = intLock ();
    x = PinDiRead();
    intUnlock (iLocKey);
    
    //PinAClk(LOW);
    SPI_DELAY(SPI_CLOCK_LOW_TIME);
    return x;
}

/*I2C读一个字节*/
BYTE SpiReadByte(void)
{
    BYTE bit;
    BYTE data=0x0;

    /*The MSB is read first*/
    for(data=0,bit=0;bit<7;bit++)
    {
        data |= SpiReadBit();
        data <<= 1;
    }

    data |= SpiReadBit();

    return data;
}

/*I2C写比特位*/
void SpiWriteBit(BYTE x)
{
    PinAClk(HIGH);
    SPI_DELAY(SPI_CLOCK_HIGH_TIME/2);
    
    if (x & 0x80) /* the MSB is sent out first*/
        PinADo(HIGH);
    else
        PinADo(LOW);

    SPI_DELAY(SPI_CLOCK_HIGH_TIME);
    PinAClk(LOW);
    SPI_DELAY(SPI_CLOCK_LOW_TIME);
    PinAClk(HIGH);
    SPI_DELAY(SPI_CLOCK_HIGH_TIME);
//    PinADo(HIGH);
}

/*I2C写一个字节*/
void SpiWriteByte(BYTE data)
{
    int i;

    for(i=0;i<8;i++)
    {
        SpiWriteBit(data);
        data<<=1;
    }

	//I2cData(HIGH);/*release SDA*/
}

DWORD SpiWrite(BYTE byPort, BYTE byAddr, BYTE byData)
{
    DWORD dwStatus = 0;
    
    dwStatus = semTake(semSpiLock, NO_WAIT);
    
    if(SYS_ERROR == dwStatus)
    {
        return SYS_ERROR;
    }
    
    byAddr |= 0x80;

if (byPort == 7)
{
    PinACs(0, HIGH);
    PinACs(1, HIGH);
    PinACs(2, HIGH);
    PinACs(3, LOW);
}
    /*PinACs(byPort, LOW);*/
    SPI_DELAY(SPI_START_TIME);
    SpiWriteByte(byAddr);
    SpiWriteByte(byData);
    SPI_DELAY(SPI_STOP_TIME);
    /*PinACs(byPort, HIGH);*/
	if (byPort == 7)
	{
		PinACs(0, LOW);
		PinACs(1, LOW);
		PinACs(2, LOW);
		PinACs(3, HIGH);
	}

    semGive(semSpiLock);
}

DWORD SpiRead(BYTE byPort, BYTE byAddr, BYTE *pbyData)
{
    DWORD dwStatus = 0;
    
    if(NULL == pbyData)
        return;

    dwStatus = semTake(semSpiLock, NO_WAIT);
    
    if(SYS_ERROR == dwStatus)
    {
        return SYS_ERROR;
    }

    *pbyData &= 0x7f;
    SPI_DELAY(SPI_START_TIME);
    /*PinACs(byPort, LOW);*/
	if (byPort == 7)
	{
		PinACs(0, HIGH);
		PinACs(1, HIGH);
		PinACs(2, HIGH);
		PinACs(3, LOW);
	}
	
    SPI_DELAY(SPI_START_TIME);
    SpiWriteByte(0x3);
    SpiWriteByte(0x0);
    SpiWriteByte(0x0);
    SpiWriteByte(byAddr);
    *pbyData = SpiReadByte();
    
    SPI_DELAY(SPI_STOP_TIME);
    
    /*PinACs(byPort, HIGH);*/
	if (byPort == 7)
	{
		PinACs(0, LOW);
		PinACs(1, LOW);
		PinACs(2, LOW);
		PinACs(3, HIGH);
	}

    semGive(semSpiLock);
}

void Spi0Test(void)
{
    BYTE byPrtData = 0;

    dev_SpiInit();

    SpiWrite(7, 0x01, 0x08);
    SpiRead(7, 0x01, &byPrtData);
    printf("byPrtData = 0x%2x\n", byPrtData);
}

void Spi_Read(unsigned int addr, unsigned int len)
{
	unsigned char byte0;
	unsigned int i;
    unsigned char *R_buffer = NULL;

	R_buffer = (unsigned char *)malloc(len);
	memset(R_buffer,0xff,len);

	/* assert the CS */
	SpiCS_ON();
	SPI_DELAY(50);	

	/* send the instruction to rea id */
	SpiWriteByte(0x3);
	SpiWriteByte(addr>>16 & 0xff);
	SpiWriteByte((addr >> 8) & 0xff);
	SpiWriteByte(addr & 0xff);
	for (i=0;i<len;i++)
	{
		R_buffer[i] = SpiReadByte();
	}
	SpiCS_OFF();

	printf("Read: \n");
	for(i=0;i<len;i++)
	{
		printf ("0x%x ",R_buffer[i]);
		if(((i+1)%16 == 0) && (i != 0))
		{
			printf("\n");
		}
	}
	printf("\n");

	free(R_buffer);
}

void Spi_Write(unsigned int offset, unsigned char *data, unsigned int len)
{
	unsigned int i = 0;
	
	SPIFlashEnable(1);
	dev_SpiInit();

	if(len>255)
	{
	    printf("len is too large, please less than 256!\n");
		return;
	}
	
	/* assert the CS */
	PinACs(0, HIGH);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, LOW);
	SPI_DELAY(100);	
	SpiWriteByte(0x6);
	SPI_DELAY(10);

	/* programing the sector */
	/* Set WREN */
	SpiWriteByte(0x6);
	SPI_DELAY(10);
	/* set pp instruction */
	SpiWriteByte(0x2);
	/* the address information */
	SpiWriteByte((offset>> 16) & 0xff);
	SpiWriteByte((offset >> 8) & 0xff);
	SpiWriteByte((offset) & 0xff);

	/* The data information */
	for (i = 0; i < len; i++)
		SpiWriteByte(data[i]);

	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, LOW);
}

void Spi0Test3(void)
{
	unsigned int i;
	unsigned char byte0;
	unsigned char byte1;
	SPIFlashEnable(1);
	dev_SpiInit();

	/* assert the CS */
	PinACs(0, HIGH);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, LOW);
	SPI_DELAY(1);	

	SpiWriteByte(0x06);
	SPI_DELAY(1);	
	
	SpiWriteByte(0x05);
	byte0 = SpiReadByte();
	printf("byte0: 0x%x\n",byte0);
	SPI_DELAY(1);
	
    SpiWriteByte(0x1);
	SpiWriteByte(0);
	SPI_DELAY(1);
	
	SpiWriteByte(0x05);
	byte0 = SpiReadByte();
	byte1 = SpiReadByte();
	printf("byte0: 0x%x\n",byte0);
	SPI_DELAY(1);

	/* send the instruction to rea id */
	SpiWriteByte(0x02);
	for(i=0;i<256;i++)
		SpiWriteByte(0x55);
	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, LOW);
/*	byte0 = SpiReadByte();
	printf ("\r\n byte0 = 0x%0x \n",byte0);
*/
}

void SpiFlashWrite(unsigned int offset, unsigned char *data, unsigned int len)
{
	unsigned char *pbuffer = NULL;
	unsigned int sec_no = 0;
	unsigned int sec_size = 65536;
	unsigned int sec_start = 0;
	unsigned int i = 0;
	
	SPIFlashEnable(1);
	dev_SpiInit();
	
	pbuffer = malloc(512 * 1024);
	if (pbuffer == NULL)
	{
		printf ("\r\n alloc memory failed");
		return;
	}
	
	/* assert the CS */
	PinACs(0, HIGH);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, LOW);
	SPI_DELAY(SPI_START_TIME);	

	/* read the whole sector data and store in the memory */
	/* calculate the address */
	sec_no = (offset & 0xFFFFFF) / sec_size;
	sec_start = sec_no * sec_size;
	
	/* set the read instruction */
	SpiWriteByte(0x3);

	/* set the address */
	SpiWriteByte((sec_start >> 16) & 0xff);
	SpiWriteByte((sec_start >> 8) & 0xff);
	SpiWriteByte((sec_start) & 0xff);

	for (i  = 0; i < 65536; i++)	
		pbuffer[i] = SpiReadByte();

	for (i = 0; i < len; i ++)
		pbuffer[i] = data[i];

	/* erase the sector */
	/* Set WREN */
	SpiWriteByte(0x6);
	SPI_DELAY(1);

	/* set erase instruction */
	SpiWriteByte(0xD8);

	/* set sector address  */
	SpiWriteByte((sec_start >> 16) & 0xff);
	SpiWriteByte((sec_start >> 8) & 0xff);
	SpiWriteByte((sec_start) & 0xff);
	
	/* programing the sector */
	/* Set WREN */
	SpiWriteByte(0x6);
	SPI_DELAY(1);
	/* set pp instruction */
	SpiWriteByte(0x2);
	/* the address information */
	SpiWriteByte((sec_start >> 16) & 0xff);
	SpiWriteByte((sec_start >> 8) & 0xff);
	SpiWriteByte((sec_start) & 0xff);

	/* The data information */
	for (i = 0; i < sec_size; i++)
		SpiWriteByte(pbuffer[i]);

	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, LOW);

}

void spiFlashRead(unsigned int offset, unsigned int len, unsigned char *buffer)
{
	int i = 0;
	SPIFlashEnable(1);
	dev_SpiInit();

	if (buffer == NULL)
	{
		printf("\r\nbuffer is NULL \n");
		return;
	}

	offset &= 0xFFFFFF;

	/* assert the CS */
	PinACs(0, HIGH);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, LOW);
	SPI_DELAY(SPI_START_TIME);	
	
	/* set the read instruction */
	SpiWriteByte(0x3);

	/* set the address */	
	SpiWriteByte((offset >> 16) & 0xff);
	SpiWriteByte((offset >> 8) & 0xff);
	SpiWriteByte((offset) & 0xff);
	
	for (i = 0; i < len; i++)
		buffer[i] = SpiReadByte();
}


void spiFlashWriteTest(void)
{
	unsigned char *w_buffer = NULL;
	unsigned char *r_buffer = NULL;
	unsigned int i;
	unsigned int len = 32;
	unsigned int offset = 0x0;

	w_buffer = malloc(len);
	if (w_buffer == NULL)
	{
		printf ("\r\n W_buffer is NULL\n");
		return;
	}
	
	for (i = 0; i < len; i++)
			w_buffer[i]=0x5a;


	SpiFlashWrite(offset, w_buffer, len);

	r_buffer = malloc(len);
	if (r_buffer == NULL)
	{
		printf ("\r\n r_buffer is NULL\n");
		return;
	}
	spiFlashRead(offset, len,r_buffer);
	for (i = 0; i < len; i++)
		printf (" 0x%0x,", r_buffer[i]);
	
}

void read_id_register()
{
	unsigned char byte0;
	SPIFlashEnable(1);
	dev_SpiInit();

	/* assert the CS */
	PinACs(0, HIGH);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, LOW);

	SPI_DELAY(100);

	SpiWriteByte(0x9f);
	printf("byte0: 0x%x byte1 :0x%0x\n",SpiReadByte(),SpiReadByte());

	
}

char read_status_register()
{
	char byte0;

	SpiCS_ON();
	SpiWriteByte(0x05);
	byte0 = SpiReadByte();
	SpiCS_OFF();
	return byte0;
}

void write_status_register(unsigned char byte0)
{
	SpiCS_ON();
	SpiWriteByte(0x01);
    SpiWriteByte(byte0);
	SpiCS_OFF();
}

void Wait_For_SPIF(void)   
{   
    int n;   
    unsigned char iTest;   
       
    for(n=0; n<1000; n++)   
    {   
        asm("nop;");   
    }   
       
    while(1)   
    {   
        iTest = read_status_register();
        if(iTest == 0)
        {
            printf("SPIF over! \n");
            break;   
        }
    }   
}   


unsigned int Wait_For_WEL(void)   
{   
    int n, i;   
    char status_register = 0;   
    ERROR_CODE ErrorCode = 0;
       
        for(i = 0; i<35; i++)   
        {   
            status_register = read_status_register();   
            if( (status_register & 0x2) )   
            {   
                ErrorCode = 0;
                break;   
            }   
               
            for(n=0; n<1000; n++)   
                asm("nop;");   
            ErrorCode = 1;   // Time out error   
        };   
    return ErrorCode;   
}   


void Spi_Test( unsigned long ulStartAddr, long len)
{
	unsigned long ulWAddr;
	unsigned char *w_buffer = NULL;
	unsigned long i;

	w_buffer = malloc(len);
	if (w_buffer == NULL)
	{
		printf ("\r\n W_buffer is NULL\n");
		return;
	}
	
	for (i = 0; i < len; i++)
			w_buffer[i]=0x5a;


	SPIFlashEnable(1);
	dev_SpiInit();

	/* CS */
	PinACs(0, HIGH);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, LOW);
	SPI_DELAY(50);	

	/*Write Enable*/
	SpiWriteByte(06);
	if (1 == Wait_For_WEL())
	{
	    printf("WEL time out!\n");
	}
	else
	{
		SpiWriteByte(02);
		Wait_For_SPIF();
		ulWAddr = (ulStartAddr >> 16);
		SpiWriteByte(ulWAddr);
		Wait_For_SPIF();
		ulWAddr = (ulStartAddr >> 8);	
		SpiWriteByte(ulWAddr);	
		Wait_For_SPIF();
		ulWAddr = ulStartAddr;	 
		SpiWriteByte(ulWAddr);	
		Wait_For_SPIF();

		for (i=0; i<len; i++)	 
		{	
			SpiWriteByte(w_buffer[i]);   
			Wait_For_SPIF();
		}	
		Wait_For_SPIF();
	}
	free(w_buffer);
	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, LOW);
}

/* SPI Flash */
void SpiCS_ON()
{
	PinACs(0, HIGH);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, LOW);
}

void SpiCS_OFF()
{
	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, LOW);
}

void start_spi()
{
	SPIFlashEnable(1);
	dev_SpiInit();
}

void SectorErase(unsigned int addr)
{
	char status = 0xff;

	SpiCS_ON();
	SPI_DELAY(50);	
 	SpiWriteByte(0x6);
	SpiCS_OFF();

	SPI_DELAY(10);	

	SpiCS_ON();
	SpiWriteByte(0xD8);
	SpiWriteByte((addr >> 16) & 0xff);
	SpiWriteByte(0);
	SpiWriteByte(0);
	SpiCS_OFF();
	while(status != 0)
	{
	    status=read_status_register();
	}
}

void BulkErase()
{
	char status=0xff;

 	SpiCS_ON();
	SPI_DELAY(10);	
 	SpiWriteByte(0x6);
	SpiCS_OFF();

	SPI_DELAY(10);	

	SpiCS_ON();
	SpiWriteByte(0xC7);
	SpiCS_OFF();
	while(status != 0)
	{
	    status=read_status_register();
	}
}

void Spi_PP(unsigned long addr, unsigned long len, char value)
{
	unsigned long i = 0;
	char status=0xff;

	SectorErase(addr);

	SpiCS_ON();
	/*SPI_DELAY(10);*/	
	SpiWriteByte(0x6);
	SpiCS_OFF();

	SPI_DELAY(10);

	SpiCS_ON();
	SpiWriteByte(0x2);
	SpiWriteByte((addr>>16) & 0xff);
	SpiWriteByte((addr>>8) & 0xff);
	SpiWriteByte(addr & 0xff);

	for(i=0;i<len;i++)
	{
		SpiWriteByte(value);
	}
	SpiCS_OFF();

	while(status != 0)
	{
	    status=read_status_register();
	}
}

#define C753_READ  0x7f
#define C753_WRITE 0x80

void Spi_C753_ON()
{
	PinACs(0, LOW);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, LOW);
}

void Spi_C753_OFF()
{
	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, LOW);
}

void Spi_C753_Bank_set(unsigned char bankNo)
{
	Spi_C753_ON();
	SpiWriteByte(C753_WRITE | 0x0); /* 0x0: bank register addr*/
	SpiWriteByte(bankNo);
	Spi_C753_OFF();
}

void Spi_C753_Bank_get()
{
	unsigned char bankNo = 0x0;
	Spi_C753_ON();
	SpiWriteByte(0x0); /* 0x0: bank register addr*/
	bankNo = SpiReadByte();
	Spi_C753_OFF();
	printf("Bank No is 0x%x\n",bankNo);
}

void Spi_C753_Read(unsigned char bankNo, unsigned char offset, unsigned char *value)
{
	unsigned char data = 0xff;
	Spi_C753_Bank_set(bankNo);
	Spi_C753_ON();
	SpiWriteByte(offset & C753_READ);
	data = SpiReadByte();
	Spi_C753_OFF();
	*value = data;
	printf("data=0x%x\n",data);
}

void Spi_C753_Write(unsigned char bankNo, unsigned char offset, unsigned char data)
{
	Spi_C753_Bank_set(bankNo);
	Spi_C753_ON();
	SpiWriteByte(offset | C753_WRITE);
	SpiWriteByte(data);
	Spi_C753_OFF();
}


void Spi_753_Read(unsigned char bank, unsigned char offset, unsigned char *value)
{
	Spi_C753_ON();

	/* chose the bank */
	SpiWriteByte(0x80);
	SpiWriteByte(bank & 0xF);  /* only 16 bank */

	/* read the offset register value */
	SpiWriteByte(offset & 0x7f);
	*value = SpiReadByte();

	Spi_C753_OFF();

	printf ("\r\n value = 0x%0x\n",*value);
}


void Spi_753_Write(unsigned char bank, unsigned char offset, unsigned char value)
{
	Spi_C753_ON();

	/* chose the bank */
	SpiWriteByte(0x80);
	SpiWriteByte(bank & 0xF); /* only 16 bank */

	/* write the offset register value */
	SpiWriteByte(0x80 | (offset & 0x7f));
	SpiWriteByte(value); 
	Spi_C753_OFF();
}

void Spi_753_Read1(unsigned char bank, unsigned char offset, unsigned char *value)
{
	printf ("\r\n [Spi_753_Read] bank:%d, offset:0x%0x \n", bank, offset);

	Spi_C753_ON();

	/* chose the bank */
	SpiWriteByte(0x80);
	SpiWriteByte(bank & 0xF);  /* only 16 bank */

	/* read the offset register value */
	SpiWriteByte(offset & 0x7f);
	*value = SpiReadByte();

	Spi_C753_OFF();

	/*printf ("\r\n value = 0x%0x\n",*value);*/
}


void Spi_753_Write1(unsigned char bank, unsigned char offset, unsigned char value)
{
	printf ("\r\n [Spi_753_Write] bank:%d, offset:0x%0x, value:0x%0x", bank, offset, value);
	Spi_C753_ON();

	/* chose the bank */
	SpiWriteByte(0x80);
	SpiWriteByte(bank & 0xF); /* only 16 bank */

	/* write the offset register value */
	SpiWriteByte(0x80 | (offset & 0x7f));
	SpiWriteByte(value); 
	Spi_C753_OFF();
}



void Spi_753_test1(void)
{
	unsigned char bank = 0;
	unsigned char offset =  0x7D;  /* test register in 753 is 0x7D */
	unsigned char w_value = 0x5a;
	unsigned char r_value = 0x0;
	
	Spi_753_Write1(bank, offset, w_value);

	Spi_753_Read1(bank, offset, &r_value);

	printf ("\r\n r_value = 0x%0x\n", r_value);
}

/* C772 */
void Spi_C772_ON()
{
	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, LOW);
}

void Spi_C772_OFF()
{
	PinACs(0, HIGH);
	PinACs(1, HIGH);
	PinACs(2, HIGH);
	PinACs(3, HIGH);
}

void Spi_C772_Bank_set(unsigned char bankNo)
{
	Spi_C772_ON();
	SpiWriteByte(C753_WRITE | 0x0); /* 0x0: bank register addr*/
	SpiWriteByte(bankNo);
	Spi_C772_OFF();
}

void Spi_C772_Bank_get()
{
	unsigned char bankNo = 0x0;
	Spi_C772_ON();
	SpiWriteByte(0x0); /* 0x0: bank register addr*/
	bankNo = SpiReadByte();
	Spi_C772_OFF();
	printf("Bank No is 0x%x\n",bankNo);
}

void Spi_C772_Read(unsigned char bankNo, unsigned char offset, unsigned char *value)
{
	unsigned char data = 0xff;
	Spi_C772_Bank_set(bankNo);
	Spi_C772_ON();
	SpiWriteByte(offset & C753_READ);
	data = SpiReadByte();
	Spi_C772_OFF();
	*value = data;
	printf("data=0x%x\n",data);
}

void Spi_C772_Write(unsigned char bankNo, unsigned char offset, unsigned char data)
{
	Spi_C772_Bank_set(bankNo);
	Spi_C772_ON();
	SpiWriteByte(offset | C753_WRITE);
	SpiWriteByte(data);
	Spi_C772_OFF();
}

void Spi_C772_Read1(unsigned char bank, unsigned char offset, unsigned char *value)
{
	printf ("\r\n [Spi_753_Read] bank:%d, offset:0x%0x \n", bank, offset);

	Spi_C772_ON();

	/* chose the bank */
	SpiWriteByte(0x80);
	SpiWriteByte(bank & 0xF);  /* only 16 bank */

	/* read the offset register value */
	SpiWriteByte(offset & 0x7f);
	*value = SpiReadByte();

	Spi_C772_OFF();

	/*printf ("\r\n value = 0x%0x\n",*value);*/
}


void Spi_C772_Write1(unsigned char bank, unsigned char offset, unsigned char value)
{
	printf ("\r\n [Spi_753_Write] bank:%d, offset:0x%0x, value:0x%0x", bank, offset, value);
	Spi_C772_ON();

	/* chose the bank */
	SpiWriteByte(0x80);
	SpiWriteByte(bank & 0xF); /* only 16 bank */

	/* write the offset register value */
	SpiWriteByte(0x80 | (offset & 0x7f));
	SpiWriteByte(value); 
	Spi_C772_OFF();
}



void Spi_C772_test1(void)
{
	unsigned char bank = 0;
	unsigned char offset =  0x57;  /* test register in 753 is 0x7D */
	unsigned char w_value = 0x5a;
	unsigned char r_value = 0x0;
	
	Spi_C772_Write1(bank, offset, w_value);

	Spi_C772_Read1(bank, offset, &r_value);

	printf ("\r\n r_value = 0x%0x\n", r_value);
}

/* FPGA SPI*/
void Spi_FPGA_ON()
{
	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, HIGH);
}

void Spi_FPGA_OFF()
{
	PinACs(0, LOW);
	PinACs(1, LOW);
	PinACs(2, LOW);
	PinACs(3, LOW);
}

void Spi_FPGA_Read(unsigned short offset, unsigned short *value)
{
	unsigned char data = 0xff;
	unsigned short rdData = 0x0;
	Spi_FPGA_ON();
	SpiWriteByte(offset & 0xff);
	SpiWriteByte((offset >> 8) & 0x7f);
	data = SpiReadByte();
	/**value = data;*/
	rdData = data;
	data = SpiReadByte();
	/**value = (*value << 8) | data;*/
	rdData = (rdData << 8) | data;
	Spi_FPGA_OFF();
	printf("rdData=0x%x\n",rdData);
}

void Spi_FPGA_Write(unsigned short offset, unsigned short data)
{
	Spi_FPGA_ON();
	SpiWriteByte(offset & 0xff);
	SpiWriteByte((offset >> 8) | 0x80);
	SpiWriteByte(data & 0xff);
	SpiWriteByte(data >> 8);
	Spi_FPGA_OFF();
}

/***********************************************

	函数描述: 打开SPI 通道 CS (内部函数)
	参数描述:
		channnel:	SPI 通道
	函数返回值:
		无
		

***********************************************/
void dev_SpiCsOn(unsigned int channel)
{
	/* only support 16 channel at most */
	unsigned char	tmp = (channel & 0xF);
	unsigned char	i;


	/* Assert the CS for the spi device*/
	for (i = 0; i < 4; i++)
	{	
		PinACs(i, (tmp & 0x1));
		tmp >>= 1;
	}
	
}

/***********************************************

	函数描述:关闭SPI 通道 CS (内部函数)
	参数描述:
		channnel:	SPI 通道
	函数返回值:
		无
		

***********************************************/
void dev_SpiCsOff(void)
{
	unsigned char	i;

	/* De-assert the CS for the spi device */
	for (i = 0; i < 4; i++)
	{	
		PinACs(i, HIGH);
	}	
}


/*********************************************** 
	函数描述: SPI 写操作接口
	参数描述:
		chn:		SPI 通道
		addr: 	SPI 设备寄存器地址
		value:	SPI 写入寄存器的值
	函数返回值:
		无
	
************************************************/
void dev_SPI_Write(uint32_t chn,uint8_t addr,uint8_t value)
{
	if ((chn != DEV_SPI_C753_CHANNEL) &&
		(chn !=	DEV_SPI_C722_CHANNEL))
	{
		printf ("\r\n the spi channel error! the value is 0x% \n", chn);
		return;
	}

	/* enable the CS for accordinary channel */
	dev_SpiCsOn(chn);

	/* different spi device should need different timing operation */
	switch (chn)
	{			
		case DEV_SPI_C753_CHANNEL:
			/* Write the data to the C753 */
			SpiWriteByte(0x80 | (addr & 0x7f));
			SpiWriteByte(value);
			break;
				
		case DEV_SPI_C722_CHANNEL:			
			/* Write the data to the C722 */
			SpiWriteByte(0x80 | (addr & 0x7f));
			SpiWriteByte(value);
			break;
	}
	
	/* De-assert the CS for the spi device */
	dev_SpiCsOff();
	return;
}


/***********************************************

	函数描述: SPI 读接口
	参数描述:
		chn:		SPI 通道
		addr:	SPI 设备寄存器地址
		value:	SPI 寄存器值
	函数返回值:
		无
************************************************/
void dev_SPI_Read(uint32_t chn,uint8_t addr,uint8_t *value)
{

	if ((chn != DEV_SPI_C753_CHANNEL) &&
		(chn !=	DEV_SPI_C722_CHANNEL))
	{
		printf ("\r\n the spi channel error! the value is 0x% \n", chn);
		return;
	}

	/* enable the CS for accordinary channel */
	dev_SpiCsOn(chn);

	/* different spi device should need different timing operation */
	switch (chn)
	{			
		case DEV_SPI_C753_CHANNEL:
			/* Write the data to the C753 */
			SpiWriteByte(addr & 0x7f);
			*value = SpiReadByte();
			break;
				
		case DEV_SPI_C722_CHANNEL:			
			/* Write the data to the C722 */
			SpiWriteByte(addr & 0x7f);
			*value = SpiReadByte();
			break;
	}
	
	/* De-assert the CS for the spi device */
	dev_SpiCsOff();
}



/***********************************************

	函数描述: FPGA  写 接口(通过SPI 访问)
	参数描述:
		chn:		SPI 通道 (FPGA读写也是经过SPI 所以通道号固定)
		addr:	FPGA 设备寄存器地址
		value:	FPGA 寄存器值
	函数返回值:
		无
************************************************/

void dev_FPGA_Write(uint32_t chn,uint16_t addr,uint16_t value)
{
	/* enable the CS for the FPGA */
	dev_SpiCsOn(DEV_SPI_FPGA_CHANNEL);

	SpiWriteByte((addr >> 8) | 0x80);
	SpiWriteByte(addr & 0xff);
	SpiWriteByte(value >> 8);
	SpiWriteByte(value & 0xff);

	/* disable the CS for FPGA */
	dev_SpiCsOff();
}


/***********************************************

	函数描述: FPGA 读接口
	参数描述:
		chn:		SPI 通道(FPGA读写也是经过SPI 所以通道号固定)
		addr:	FPGA 设备寄存器地址
		value:	FPGA 寄存器值
	函数返回值:
		无
************************************************/

void dev_FPGA_Read(uint32_t chn,uint16_t addr,uint16_t *value)
{
	unsigned char data = 0xff;
	unsigned short rdData = 0x0;

	/* enable the CS for FPGA  */
	dev_SpiCsOn(DEV_SPI_FPGA_CHANNEL);

	/* send address (16bit) */
	SpiWriteByte((addr >> 8) & 0x7f);
	SpiWriteByte(addr & 0xff);

	/* read the first byte */
	data = SpiReadByte();
	rdData = data;

	/* read the second byte */
	data = SpiReadByte();
	rdData = (rdData << 8) | data;

	/* disable the CS for FPGA */
	dev_SpiCsOff();

	*value = rdData;		
}


/********************************************
	函数描述:	SPI 读操作测试函数

*********************************************/
void dev_spi_test(void)
{

	unsigned char bank = 0;
	unsigned char offset =  0x7D;  /* test register in 753 is 0x7D */
	unsigned char w_value = 0x5a;
	unsigned char r_value = 0x0;

	unsigned short offset_fpga = 0x0E; /* This register is W/R in FPGA */
	unsigned short w_fpgaReg = 0x1234;
	unsigned short r_fpgaReg = 0x0;

	
	printf ("\r\n [Spi_753_Write test] bank:%d, offset:0x%0x w_value:0x%0x",
			bank, offset,w_value);
	/* write the bank select register */
	dev_SPI_Write(DEV_SPI_C753_CHANNEL,0x0, 0x0);
	/* Write the value to register */
	dev_SPI_Write(DEV_SPI_C753_CHANNEL, offset, w_value);
	
	/* write the bank select register */
	dev_SPI_Write(DEV_SPI_C753_CHANNEL,0x0, 0x0);
	/* read the register  */
	dev_SPI_Read(DEV_SPI_C753_CHANNEL, offset, &r_value);
	printf ("\r\n [Spi_753_Read test] bank:0x%0x offset:0x%0x r_value:0x%0x",
								bank, offset,r_value);

	printf ("\r\n ============================================\n");

	bank = 0;
	offset = 0x57;  /* test register in 753 is 0x7D */
	w_value = 0x5a;
	r_value = 0x0;
	printf ("\r\n [Spi_722_Write test] bank:%d, offset:0x%0x w_value:0x%0x",
			 bank, offset,w_value);
	/* write the bank select register */
	dev_SPI_Write(DEV_SPI_C722_CHANNEL,0x0, 0x0);
	/* Write the value to register */
	dev_SPI_Write(DEV_SPI_C722_CHANNEL, offset, w_value);

	/* write the bank select register */
	dev_SPI_Write(DEV_SPI_C722_CHANNEL,0x0, 0x0);
	/* read the register  */
	dev_SPI_Read(DEV_SPI_C722_CHANNEL, offset, &r_value);
	printf ("\r\n [Spi_722_Read test] bank:0x%0x offset:0x%0x r_value:0x%0x",
								bank, offset,r_value);	
	printf ("\r\n ============================================\n");


	printf ("\r\n [Spi_FPGA_Write test]offset:0x%0x w_value:0x%0x",
			offset_fpga,w_fpgaReg);
	dev_FPGA_Write(DEV_SPI_FPGA_CHANNEL, offset_fpga, w_fpgaReg);
	dev_FPGA_Read(DEV_SPI_FPGA_CHANNEL, offset_fpga, &r_fpgaReg);
	printf ("\r\n [Spi_FPGA_Write test] offset:0x%0x r_value:0x%0x",
								offset_fpga,r_fpgaReg);	
	printf ("\r\n ============================================\n");
}


