#ifndef _DEV_H_
#define _DEV_H_


#ifdef __cplusplus
    extern "C"{



/*****************************************************

	Macro Define
	
******************************************************/
/* Macro define for the SPI  */
#define DEV_SPI_FLASH_CHANNEL	0x7   /* 0111'b */
#define DEV_SPI_C753_CHANNEL 	0x6   /* 0110'b */
#define DEV_SPI_C772_CHANNEL_1	0x0	  /* 0000'b */
#define DEV_SPI_C772_CHANNEL_2	0x1	  /* 0001'b */
#define DEV_SPI_C772_CHANNEL_3	0x2	  /* 0010'b */
#define DEV_SPI_C772_CHANNEL_4  0x3   /* 0011'b */
#define DEV_SPI_C772_CHANNEL_5	0x4	  /* 0100'b */
#define DEV_SPI_C772_CHANNEL_6	0x5	  /* 0101'b */
#define DEV_SPI_FPGA_CHANNEL    0x8   /* 1000'b */

#define DEV_5160_CHANNEL_1	0x1
#define DEV_5160_CHANNEL_2	0x2
#define DEV_5160_CHANNEL_3	0x3
#define DEV_5160_CHANNEL_4  0x4
#define DEV_5160_CHANNEL_5	0x5
#define DEV_5160_CHANNEL_6	0x6

extern void dev_SpiInit(void);
extern void dev_SPI_Write(uint32_t chn,uint8_t addr,uint8_t value);
extern void dev_SPI_Read(uint32_t chn,uint8_t addr,uint8_t *value);
extern void dev_FPGA_Write(uint32_t chn,uint16_t addr,uint16_t value);
extern void dev_FPGA_Read(uint32_t chn,uint16_t addr,uint16_t *value);
extern void dev_I2cInit(void);
extern void dev_5160_Write(uint32_t chn,uint8_t addr,uint8_t value);
extern void dev_5160_Read(uint32_t chn,uint8_t addr,uint8_t *value);
extern void dev_DLP_Write(uint8_t addr,uint8_t value);
extern void dev_DLP_Read(uint8_t addr,uint8_t *value);

extern void ICS307_config(unsigned long  val);
extern unsigned char GpioValGet_Slot0();
extern unsigned char GpioValGet_Slot1();
extern unsigned char GpioValGet_Slot2();


extern unsigned char Get_Asic_Ready();
extern unsigned char Get_Fan_Locked();
extern unsigned char Get_Lamp_Status();

extern void Set_PowerGood(unsigned long val);
extern void Set_Lamp_Ctrl(unsigned long val);

extern void DLPI2cWritePage(uint8_t dwAddr, uint8_t dwCount,uint8_t *byDate);
extern void DLPI2cReadData(uint8_t addr,uint8_t sub2,uint8_t dwCount,uint8_t *byDate);



//void ICS307_config(unsigned long val);

};


#endif

#endif

