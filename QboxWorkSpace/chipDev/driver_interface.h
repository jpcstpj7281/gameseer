/*****************************************************

	Macro Define
	
******************************************************/
/* Macro define for the SPI  */
#define DEV_SPI_FLASH_CHANNEL	0x7   /* 0111'b */
#define DEV_SPI_C753_CHANNEL 	0x6   /* 0110'b */
#define DEV_SPI_C722_CHANNEL	0x0	  /* 0000'b */
#define DEV_SPI_FPGA_CHANNEL    0x8   /* 1000'b */





/***********************************************

	函数描述: SPI 接口初始化，本系统使用GPIO进行SPI
				   时序模拟
	参数描述:
		无
	函数返回值:
		无
************************************************/
void dev_SpiInit(void);


/*********************************************** 
	函数描述: SPI 写操作接口
	参数描述:
		chn:		SPI 通道
		addr: 	SPI 设备寄存器地址
		value:	SPI 写入寄存器的值
	函数返回值:
		无
	
************************************************/
void dev_SPI_Write(uint32_t chn,uint8_t addr,uint8_t value);


/***********************************************

	函数描述: SPI 读接口
	参数描述:
		chn:		SPI 通道
		addr:	SPI 设备寄存器地址
		value:	SPI 寄存器值
	函数返回值:
		无
************************************************/
void dev_SPI_Read(uint32_t chn,uint8_t addr,uint8_t *value);


/***********************************************

	函数描述: FPGA  写 接口(通过SPI 访问)
	参数描述:
		chn:		SPI 通道 (FPGA读写也是经过SPI 所以通道号固定)
		addr:	FPGA 设备寄存器地址
		value:	FPGA 寄存器值
	函数返回值:
		无
************************************************/
void dev_FPGA_Write(uint32_t chn,uint16_t addr,uint16_t value);


/***********************************************

	函数描述: FPGA 读接口
	参数描述:
		chn:		SPI 通道(FPGA读写也是经过SPI 所以通道号固定)
		addr:	FPGA 设备寄存器地址
		value:	FPGA 寄存器值
	函数返回值:
		无
************************************************/
void dev_FPGA_Read(uint32_t chn,uint16_t addr,uint16_t *value);


/***************************************************************

	函数描述: 	I2C 初始化， 本系统使用GPIO 模拟I2C 时序
	
	参数描述:
		无
	函数返回值:
		无

***************************************************************/
void dev_I2cInit(void);



/******************************************************

	函数描述: 	I2C 设备写操作函数
	参数描述: 	
		chn:	
				I2C 通道号, 系统使用两路I2C 通道0 为主控板
				通道1 为远端

		chipType:
				I2C 设备地址，I2C为共享总线，每一个总线上
				的设备都有对应的地址
		addr:
				需要访问的寄存器偏移
		value:
				写入寄存器的值
	函数返回值
		无


*******************************************************/
void dev_I2C_Write(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t value);


/*************************************************************

	函数描述:	I2C 设备读操作函数
	参数描述:    
		chn:
				I2C 通道号，系统 使用两个通道, 通道1为主控板
				通道，通道1为远端访问通道
		chipType:
				I2C 设备地址，I2C为共享式总线，每一个总线上的
				设备都有对应的地址
		addr:
				I2C设备的寄存器偏移地址
		value:
				读取寄存器的值
	函数返回值:
		无

**************************************************************/
void dev_I2C_Read(uint32_t chn,uint32_t chipType,uint8_t addr,uint8_t *value);




