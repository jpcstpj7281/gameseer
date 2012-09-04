/******************************************************************************

******************************************************************************/
#ifndef _SpiDev_H_
#define _SpiDev_H_

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

#ifndef assert
  #define assert
#endif

/*SPI寄存器映射地址*/
#define SPI_OFFSET		(0xFFFE0000)
#define SPI_CR			(*(volatile unsigned int *)(0x00000000 + SPI_OFFSET)) /* (SPI_CR) Control Register*/
#define   SPI_SPIEN		    (0x1 <<  0) /* (SPI) SPI Enable*/
#define   SPI_SPIDIS	    (0x1 <<  1) /* (SPI) SPI Disable*/
#define   SPI_SWRST		    (0x1 <<  7) /* (SPI) SPI Software reset*/
#define   SPI_LASTXFER	    (0x1 << 24) /* (SPI) SPI Last Transfer*/
#define SPI_MR          (*(volatile unsigned int *)(0x00000004 + SPI_OFFSET)) /* (SPI_MR) Mode Register*/
#define   SPI_MSTR		    (0x1 <<  0) /* (SPI) Master/Slave Mode*/
#define   SPI_PS		    (0x1 <<  1) /* (SPI) Peripheral Select*/
#define   SPI_PS_FIXED	    (0x0 <<  1) /* (SPI) Fixed Peripheral Select*/
#define   SPI_PS_VARIABLE	(0x1 <<  1) /* (SPI) Variable Peripheral Select*/
#define   SPI_PCSDEC	    (0x1 <<  2) /* (SPI) Chip Select Decode*/
#define   SPI_FDIV		    (0x1 <<  3) /* (SPI) Clock Selection*/
#define   SPI_MODFDIS	    (0x1 <<  4) /* (SPI) Mode Fault Detection*/
#define   SPI_LLB           (0x1 <<  7) /* (SPI) Clock Selection*/
#define   SPI_PCS		    (0xF << 16) /* (SPI) Peripheral Chip Select*/
#define   SPI_DLYBCS	    (0xFF << 24) /* (SPI) Delay Between Chip Selects*/
#define SPI_RDR		    (*(volatile unsigned int *)(0x00000008 + SPI_OFFSET)) /* (SPI_RDR) Receive Data Register*/
#define SPI_TDR		    (*(volatile unsigned int *)(0x0000000C + SPI_OFFSET)) /* (SPI_TDR) Transmit Data Register*/
#define SPI_SR		    (*(volatile unsigned int *)(0x00000010 + SPI_OFFSET))/* (SPI_SR) Status Register*/
#define   SPI_RDRF          (0x1 <<  0) /* (SPI) Receive Data Register Full*/
#define   SPI_TDRE          (0x1 <<  1) /* (SPI) Transmit Data Register Empty*/
#define   SPI_MODF          (0x1 <<  2) /* (SPI) Mode Fault Error*/
#define   SPI_OVRES         (0x1 <<  3) /* (SPI) Overrun Error Status*/
#define   SPI_ENDRX         (0x1 <<  4) /* (SPI) End of Receiver Transfer*/
#define   SPI_ENDTX         (0x1 <<  5) /* (SPI) End of Receiver Transfer*/
#define   SPI_RXBUFF        (0x1 <<  6) /* (SPI) RXBUFF Interrupt*/
#define   SPI_TXBUFF        (0x1 <<  7) /* (SPI) TXBUFE Interrupt*/
#define   SPI_NSSR          (0x1 <<  8) /* (SPI) NSSR Interrupt*/
#define   SPI_TXEMPTY       (0x1 <<  9) /* (SPI) TXEMPTY Interrupt*/
#define   SPI_SPIENS        (0x1 << 16) /* (SPI) Enable Status*/
#define SPI_IER		    (*(volatile unsigned int *)(0x00000014 + SPI_OFFSET))/* (SPI_IER) Interrupt Enable Register*/
#define SPI_IDR		    (*(volatile unsigned int *)(0x00000018+ SPI_OFFSET)) /* (SPI_IDR) Interrupt Disable Register*/
#define SPI_IMR		    (*(volatile unsigned int *)(0x0000001C+ SPI_OFFSET)) /* (SPI_IMR) Interrupt Mask Register*/
#define SPI_CSR0		(*(volatile unsigned int *)(0x00000030+ SPI_OFFSET)) /* (SPI_CSR) Chip Select Register*/
#define SPI_CSR1		(*(volatile unsigned int *)(0x00000034+ SPI_OFFSET)) /* (SPI_CSR) Chip Select Register*/
#define SPI_CSR2		(*(volatile unsigned int *)(0x00000038+ SPI_OFFSET)) /* (SPI_CSR) Chip Select Register*/
#define SPI_CSR3		(*(volatile unsigned int *)(0x0000003C+ SPI_OFFSET)) /* (SPI_CSR) Chip Select Register*/
#define   SPI_CPOL          (0x1 <<  0) /* (SPI) Clock Polarity*/
#define   SPI_NCPHA         (0x1 <<  1) /* (SPI) Clock Phase*/
#define   SPI_CSAAT         (0x1 <<  3) /* (SPI) Chip Select Active After Transfer*/
#define   SPI_BITS          (0xF <<  4) /* (SPI) Bits Per Transfer*/

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

/*SPI的DMA控制器*/
#define SPI_PDC_OFFSET  (SPI_OFFSET + 0x100)
#define SPI_RPR         (*(volatile unsigned int *)(0x00000000 + SPI_PDC_OFFSET)) /* (PDC_RPR) Receive Pointer Register*/
#define SPI_RCR         (*(volatile unsigned int *)(0x00000004 + SPI_PDC_OFFSET)) /* (PDC_RCR) Receive Counter Register*/
#define SPI_TPR         (*(volatile unsigned int *)(0x00000008 + SPI_PDC_OFFSET)) /* (PDC_TPR) Transmit Pointer Register*/
#define SPI_TCR         (*(volatile unsigned int *)(0x0000000C + SPI_PDC_OFFSET)) /* (PDC_TCR) Transmit Counter Register*/
#define SPI_RNPR        (*(volatile unsigned int *)(0x00000010 + SPI_PDC_OFFSET)) /* (PDC_RNPR) Receive Next Pointer Register*/
#define SPI_RNCR        (*(volatile unsigned int *)(0x00000014 + SPI_PDC_OFFSET)) /* (PDC_RNCR) Receive Next Counter Register*/
#define SPI_TNPR        (*(volatile unsigned int *)(0x00000018 + SPI_PDC_OFFSET)) /* (PDC_TNPR) Transmit Next Pointer Register*/
#define SPI_TNCR        (*(volatile unsigned int *)(0x0000001C + SPI_PDC_OFFSET)) /* (PDC_TNCR) Transmit Next Counter Register*/
#define SPI_PTCR        (*(volatile unsigned int *)(0x00000020 + SPI_PDC_OFFSET)) /* (PDC_PTCR) PDC Transfer Control Register*/
#define SPI_PTSR        (*(volatile unsigned int *)(0x00000024 + SPI_PDC_OFFSET)) /* (PDC_PTSR) PDC Transfer Status Register*/
#define   PDC_RXTEN         (0x1 <<  0) /* (PDC) Receiver Transfer Enable*/
#define   PDC_RXTDIS        (0x1 <<  1) /* (PDC) Receiver Transfer Disable*/
#define   PDC_TXTEN         (0x1 <<  8) /* (PDC) Transmitter Transfer Enable*/
#define   PDC_TXTDIS        (0x1 <<  9) /* (PDC) Transmitter Transfer Disable*/

/*端口控制器*/
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
#define PIOA_ASR    (*(volatile unsigned int *)(0x0070 + PIOA_OFFSET))
#define PIOA_BSR    (*(volatile unsigned int *)(0x0074 + PIOA_OFFSET))
#define PIOA_ABSR   (*(volatile unsigned int *)(0x0078 + PIOA_OFFSET))


#define SPI_ID 		    (13)              /*SPI设备ID号*/
#define SPI_MAX_NUM     (4)               /*支持最多SPI数*/

#define SPI_SCBR        (0xFF <<  8) /* (SPI) Serial Clock Baud Rate*/
#define SPI_DLYBS       (0xFF << 16) /* (SPI) Delay Before SPCK*/
#define SPI_DLYBCT      (0xFF << 24) /* (SPI) Delay Between Consecutive Transfers*/

#define SPICMD_TIME_OUT (1000)           /*命令超时时间*/

#define PIN_SPI_MASK    (0x00000007)         /*SPI0 设备管脚*/

#define BOARD_MAINOSC   (18452660)                        /*板上晶振频率*/
#define BOARD_MCK       ((BOARD_MAINOSC * 110 / 9) / 2) /*主时钟频率*/

#define AT45_SPI_CLK    (1000000)                         /*SPI时钟频率*/

#define SPID_CSR_SCBR(mck, spck)    ((((mck) / (spck)) << 8) & SPI_SCBR)

/*// Calculates the value of the DLYBS field of the Chip Select Register given*/
/*// the delay in ns and MCK.*/
#define SPID_CSR_DLYBS(mck, delay) \
    (((((delay) * ((mck) / 1000000)) / 1000) << 16) & SPI_DLYBS)

/*// Calculates the value of the DLYBCT field of the Chip Select Register given*/
/*// the delay in ns and MCK.*/
#define SPID_CSR_DLYBCT(mck, delay) \
    (((((delay) / 32 * ((mck) / 1000000)) / 1000) << 24) & SPI_DLYBCT)

#define CALCULATE_CSR(mck, spck) \
    (SPID_CSR_DLYBCT(mck, 250) \
     | SPID_CSR_DLYBS(250, mck) | SPID_CSR_SCBR(mck, spck))
    //(SPI_CPOL | SPI_NCPHA | SPID_CSR_DLYBCT(mck, 250) \

#define SPICMDTIMEOUT      (100)			/*命令发送超时*/
#define SPICMDINTTIMEOUT   (100000)           /*命令等待响应超时*/

#define OPEN               (1)
#define CLOSE              (0)

/*SPI命令格式*/
typedef struct _SPICMD
{
    BYTE *pbyCmd;           /*命令*/
    BYTE byCmdSize;         /*命令长度*/
    BYTE *pbyData;          /*数据*/
    WORD wDataSize;         /*数据长度*/
    BYTE bySpiCs;           /*SPI通道*/
}SPICMD;

typedef struct _SPIDEV
{
    BYTE    byIsSpiPortOpen[SPI_MAX_NUM];       /*当前通道号*/
    BYTE    byCurSpiPortOpen;                   /*用于中断鉴别*/
    SEM_ID  semIsSpiUsing;                      /*SPI同步信号量，同一时间只能使用一个通道*/
    SEM_ID  semCmdSending;                      /*SPI命令发送同步信号*/
    SEM_ID  semIsCmdComplete;                   /*中断信号量*/
    SPICMD  *psSpiCmd;                          /*命令*/
}SPIDEV;

extern VOID   CS_SpiCreate(void);
extern SDWORD CS_SpiOpen(BYTE bySpiPortNum);
extern SDWORD CS_SpiClose(BYTE bySpiPortNum);
extern SDWORD CS_SpiCmd(BYTE bySpiPortNum, BYTE *pbyCmd, BYTE byCmdSize, BYTE *pbyData, WORD wDataSize);
VOID   SpiHandler(void);
LOCAL  SDWORD SpiIsrInstall(void);
LOCAL  SDWORD SpiPioConfig(BYTE bySpiPortNum);
LOCAL  SDWORD IsCmdSend(void);

#ifdef __cplusplus
}
#endif

#endif
