/******************************************************************************

******************************************************************************/

#ifndef _IicDev_H_
#define _IicDev_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#define DATA(pin) 	(0x1 << (pin))                /*数据线*/
#define CLOCK(pin)	(0x1 << (pin))                /*时钟线*/

#define IICDATA0    (5)                          /*数据线0管脚号*/
#define IICCLK0     (6)                          /*时钟线0管脚号*/
#define IICDATA1    (3)                          /*数据线1管脚号*/
#define IICCLK1     (4)                          /*时钟线1管脚号*/
#define IICDATA2    (7)                          /*数据线2管脚号*/
#define IICCLK2     (8)                          /*时钟线2管脚号*/

#define LOW         (0)                           /*低电平*/
#define HIGH        (1)                           /*高电平*/

#define I2C_READ    (0x1)                         /*读命令*/
#define I2C_WRITE   (0x0)                         /*写命令*/

#define I2C_W0_ADDR(a)   ( (a) & 0x00FF )         /*转换字地址*/

extern  void delayUSec(int iN);

#define I2C_DELAY(n)                delayUSec(n); 
#define CLOCK_LOW_TIME	            (1) /*us*/ 
#define CLOCK_HIGH_TIME	            (1) /*us*/
#define START_CONDITION_HOLD_TIME   (7)/*us*/
#define STOP_CONDITION_HOLD_TIME    (2)/*us*/

#define I2C_CPLDID   0xca
#define I2C_CPLDPORT 0

/*电源控制器*/
#define PMC_OFFSET		(0xfffffc00)
#define PMC_SCER		(*(volatile unsigned int *)(0x00000000 + PMC_OFFSET)) /* (PMC_SCER) System Clock Enable Register*/
#define PMC_SCDR		(*(volatile unsigned int *)(0x00000004 + PMC_OFFSET)) /* (PMC_SCDR) System Clock Disable Register*/
#define PMC_SCSR        (*(volatile unsigned int *)(0x00000008 + PMC_OFFSET)) /* (PMC_SCSR) System Clock Status Register*/
#define PMC_PCER        (*(volatile unsigned int *)(0x00000010 + PMC_OFFSET)) /* (PMC_PCER) Peripheral Clock Enable Register*/
#define PMC_PCDR        (*(volatile unsigned int *)(0x00000014 + PMC_OFFSET)) /* (PMC_PCDR) Peripheral Clock Disable Register*/
#define PMC_PCSR        (*(volatile unsigned int *)(0x00000018 + PMC_OFFSET)) /* (PMC_PCSR) Peripheral Clock Status Register*/
#define PMC_MCKR       	(*(volatile unsigned int *)(0x00000030 + PMC_OFFSET)) /* (PMC_MCKR) Master Clock Register*/
#define PMC_PCKR        (*(volatile unsigned int *)(0x00000040 + PMC_OFFSET)) /* (PMC_PCKR) Programmable Clock Register*/
#define PMC_IER         (*(volatile unsigned int *)(0x00000060 + PMC_OFFSET)) /* (PMC_IER) Interrupt Enable Register*/
#define PMC_IDR         (*(volatile unsigned int *)(0x00000064 + PMC_OFFSET)) /* (PMC_IDR) Interrupt Disable Register*/
#define PMC_SR          (*(volatile unsigned int *)(0x00000068 + PMC_OFFSET)) /* (PMC_SR) Status Register*/
#define PMC_IMR         (*(volatile unsigned int *)(0x0000006C + PMC_OFFSET)) /* (PMC_IMR) Interrupt Mask Register*/


#define PIOA_OFFSET    (0xFFFFF400)
#define PIOA_PER    (*(volatile unsigned int *)(0x0000 + PIOA_OFFSET))
#define PIOA_PDR	(*(volatile unsigned int *)(0x0004 + PIOA_OFFSET))
#define PIOA_PSR	(*(volatile unsigned int *)(0x0008 + PIOA_OFFSET))
#define PIOA_ODR	(*(volatile unsigned int *)(0x0014 + PIOA_OFFSET))
#define PIOA_OER    (*(volatile unsigned int *)(0x0010 + PIOA_OFFSET))
#define PIOA_OSR	(*(volatile unsigned int *)(0x0018 + PIOA_OFFSET))
#define PIOA_SODR   (*(volatile unsigned int *)(0x0030 + PIOA_OFFSET))
#define PIOA_CODR   (*(volatile unsigned int *)(0x0034 + PIOA_OFFSET))
#define PIOA_ODSR   (*(volatile unsigned int *)(0x0038 + PIOA_OFFSET))
#define PIOA_PDSR   (*(volatile unsigned int *)(0x003C + PIOA_OFFSET))
#define PIOA_IDR    (*(volatile unsigned int *)(0x0044 + PIOA_OFFSET))
#define PIOA_MDER	(*(volatile unsigned int *)(0x0050 + PIOA_OFFSET))
#define PIOA_PUDR   (*(volatile unsigned int *)(0x0060 + PIOA_OFFSET))
#define PIOA_PPUER  (*(volatile unsigned int *)(0x0064 + PIOA_OFFSET))
#define PIOA_BSR    (*(volatile unsigned int *)(0x0074 + PIOA_OFFSET))


#define PIOB_OFFSET    (0xFFFFF600)
#define PIOB_PER    (*(volatile unsigned int *)(0x0000 + PIOB_OFFSET))
#define PIOB_PDR	(*(volatile unsigned int *)(0x0004 + PIOB_OFFSET))
#define PIOB_PSR	(*(volatile unsigned int *)(0x0008 + PIOB_OFFSET))
#define PIOB_ODR	(*(volatile unsigned int *)(0x0014 + PIOB_OFFSET))
#define PIOB_OER    (*(volatile unsigned int *)(0x0010 + PIOB_OFFSET))
#define PIOB_OSR	(*(volatile unsigned int *)(0x0018 + PIOB_OFFSET))
#define PIOB_SODR   (*(volatile unsigned int *)(0x0030 + PIOB_OFFSET))
#define PIOB_CODR   (*(volatile unsigned int *)(0x0034 + PIOB_OFFSET))
#define PIOB_ODSR   (*(volatile unsigned int *)(0x0038 + PIOB_OFFSET))
#define PIOB_PDSR   (*(volatile unsigned int *)(0x003C + PIOB_OFFSET))
#define PIOB_IDR    (*(volatile unsigned int *)(0x0044 + PIOB_OFFSET))
#define PIOB_MDER	(*(volatile unsigned int *)(0x0050 + PIOB_OFFSET))
#define PIOB_PUDR   (*(volatile unsigned int *)(0x0060 + PIOB_OFFSET))
#define PIOB_PPUER  (*(volatile unsigned int *)(0x0064 + PIOB_OFFSET))
#define PIOB_BSR    (*(volatile unsigned int *)(0x0074 + PIOB_OFFSET))

#define PIOC_OFFSET    (0xFFFFF800)
#define PIOC_PER    (*(volatile unsigned int *)(0x0000 + PIOC_OFFSET))
#define PIOC_PDR	(*(volatile unsigned int *)(0x0004 + PIOC_OFFSET))
#define PIOC_PSR	(*(volatile unsigned int *)(0x0008 + PIOC_OFFSET))
#define PIOC_ODR	(*(volatile unsigned int *)(0x0014 + PIOC_OFFSET))
#define PIOC_OER    (*(volatile unsigned int *)(0x0010 + PIOC_OFFSET))
#define PIOC_OSR	(*(volatile unsigned int *)(0x0018 + PIOC_OFFSET))
#define PIOC_SODR   (*(volatile unsigned int *)(0x0030 + PIOC_OFFSET))
#define PIOC_CODR   (*(volatile unsigned int *)(0x0034 + PIOC_OFFSET))
#define PIOC_ODSR   (*(volatile unsigned int *)(0x0038 + PIOC_OFFSET))
#define PIOC_PDSR   (*(volatile unsigned int *)(0x003C + PIOC_OFFSET))
#define PIOC_IDR    (*(volatile unsigned int *)(0x0044 + PIOC_OFFSET))
#define PIOC_MDER	(*(volatile unsigned int *)(0x0050 + PIOC_OFFSET))
#define PIOC_PUDR   (*(volatile unsigned int *)(0x0060 + PIOC_OFFSET))
#define PIOC_PPUER  (*(volatile unsigned int *)(0x0064 + PIOC_OFFSET))
#define PIOC_BSR    (*(volatile unsigned int *)(0x0074 + PIOC_OFFSET))

/*I2C通道口信息*/
typedef struct _I2CPORT
{
    BYTE byDataPin;
    BYTE byClkPin;
}I2CPORT;

LOCAL BYTE PinDataRead(void);
LOCAL void PinDataWrite(BYTE byLevel);
LOCAL void PinClkWrite(BYTE byLevel);
void I2cClk(BYTE x);
void I2cData(BYTE x);
void i2cStart(void);
void I2cStop(void);
BYTE I2cReadBit(void);
void I2cWriteBit(BYTE x);
void I2cWriteByte(BYTE data);
BYTE I2cReadByte(void);
BYTE  I2cDeviceBusy(BYTE bySlave);
extern void I2cClkCycles(int j);
/*
extern void I2cInit(void);
extern SDWORD I2cRead(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData);
extern SDWORD I2cReadSeq(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData, DWORD dwCount);
extern SDWORD I2cWrite(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE byData);
extern SDWORD I2cWritePage(BYTE byIicPort, BYTE bySlave, DWORD dwAddr, BYTE *pbyData, DWORD dwCount);
*/
extern SEM_ID semI2cLock;                 /*i2c同步信号量*/

/*当前I2C通道口*/
extern I2CPORT sCurI2cPort;

/*作为I2C状态的检测*/
extern BYTE ack1, ack2;        /*对应应答位*/
extern BYTE i2c_ack_stat;              /*状态记录*/


#ifdef __cplusplus
}
#endif

#endif
