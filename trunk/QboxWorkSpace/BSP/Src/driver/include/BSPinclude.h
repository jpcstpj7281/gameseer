/******************************************************************************



******************************************************************************/

#ifndef __BSP_BSPINCLUDE_H__
#define __BSP_BSPINCLUDE_H__
#include "sys_include.h"



/*  ��̫��������ض���*/
#define BSP_ETH_NAME            "eth"
#define BSP_ETH_NAME_LENGTH    strlen(BSP_ETH_NAME)
#define BSP_ETH_UNIT            0
/* 485 ������غ궨��*/
#define BSP_CHANNEL_485         (1)
#define BSP_CHANNEL_ETH         (2)
#define BSP_ETH_NAME_UNIT       (0)
#define BSP_485_MIRR             (0)

/*������ַ*/

#define BSP_BOOTROM_BASE      (0x10000000)
#define BSP_FLASH_BASE        (0x30000000)
#define BSP_FPGA_BASE		    (0x97080000)     

/*I2C ��ַ����*/
#define BSP_AT24C01             (0xA0)
#define BSP_LM73                (0x90)
#define BSP_POWER1014           (0x92)
#define BSP_EPM3064             (0x65)
#define BSP_PCF8563             (0xA2)
#define BSP_SI5326              (0xD0)



/*FPGA ���ֶ���*/

#define  BSP_FPGA_VERSION          (BSP_FPGA_BASE+0)    
#define  vBSP_FPGA_VERSION         (*((volatile BYTE *)(BSP_FPGA_VERSION)))
/* CPLD ���ֶ���*/
#define BSP_CPLD_BORDTYPE       (0x00)
#define BSP_CPLD_HARDVER        (0x01)
#define BSP_CPLD_ONLINE         (0x02)




/* ���������ض���*/
#define BSP_BOOTROM             (BSP_BOOTROM_BASE)
#define BSP_MINSOFT             (BSP_BOOTROM + 512 * 1024)
#define BSP_SYS_PARAM           (BSP_FLASH_BASE)
#define BSP_SYS_FTAB            (BSP_SYS_PARAM + 128 * 1024)
#define BSP_MAINSOFT            (BSP_SYS_FTAB + 128 * 1024)
#define BSP_BACKSOFT            (BSP_MAINSOFT + SOFT_LENGTH)
#define BSP_MAINLOGSOFT1        (BSP_BACKSOFT + SOFT_LENGTH) /* LATTICE FPGA 1*/
#define BSP_MAINLOGSOFT2        (BSP_MAINLOGSOFT1 + LOGSOFT__LA_LENGTH)  /* LATTICE FPGA 2*/
#define BSP_MAINLOGSOFT3        (BSP_MAINLOGSOFT2 + LOGSOFT__LA_LENGTH)	 /* ALTERA  FPGA 1*/
#define BSP_MAINLOGSOFT4        (BSP_MAINLOGSOFT3 + LOGSOFT__AL_LENGTH)  /* ALTERA  FPGA 2*/
#define BSP_BACKLOGSOFT1        (BSP_MAINLOGSOFT4 + LOGSOFT__AL_LENGTH)
#define BSP_BACKLOGSOFT2        (BSP_BACKLOGSOFT1 + LOGSOFT__LA_LENGTH)
#define BSP_BACKLOGSOFT3        (BSP_BACKLOGSOFT2 + LOGSOFT__LA_LENGTH)
#define BSP_BACKLOGSOFT4        (BSP_BACKLOGSOFT3 + LOGSOFT__AL_LENGTH)
#define BSP_FS_BASE             (BSP_BACKLOGSOFT4 + LOGSOFT__AL_LENGTH)
#define BSP_FS_SIZE             (16*1024*1024+BSP_FLASH_BASE-BSP_FS_BASE)
#define BSP_SYS_SRAM_BASE       (0x00200000)
#define BOOTROM_VERSION_ADDR    (BSP_BOOTROM_BASE+32)


#define FILE_LENGTH 	 	 (1024 * 1024 * 10)
#define SOFT_LENGTH      	 (1024 * 1024 * 3)
#define LOGSOFT__LA_LENGTH	 (1024 * 768)
#define LOGSOFT__AL_LENGTH	 (1024 * 512)
#define BSP_DEL_LENGTH	 	 (0x20000)

/*file idex */
#define BSP_MAINSOFT_INDEX		(0x1)
#define BSP_BACKSOFT_INDEX  	(0x2)
#define BSP_MAINLOGSOFT1_INDEX  (0x3)
#define BSP_MAINLOGSOFT2_INDEX  (0x4)
#define BSP_MAINLOGSOFT3_INDEX  (0x5)
#define BSP_MAINLOGSOFT4_INDEX  (0x6)
#define BSP_BACKLOGSOFT1_INDEX  (0x7)
#define BSP_BACKLOGSOFT2_INDEX  (0x8)
#define BSP_BACKLOGSOFT3_INDEX  (0x9)
#define BSP_BACKLOGSOFT4_INDEX  (0xA)







/*����������ض���*/


#define BSP_SOFT_MINSYS			(1)
#define BSP_SOFT_MAINSOFT		(2)
#define RESET_SW				(3)
#define RESET_HW				(2)
#define RESET_PW				(1)

/*�����Ͷ���*/
#define BSP_BOARD_TYPE_CS        0
#define BSP_BOARD_TYPE_HD        1
#define BSP_BOARD_TYPE_SD        2
#define BSP_BOARD_TYPE_OP        3

/*������Ϣ��ض���*/
#define BSP_TM_LENGTH			  36
#define BSP_AREA_LENGTH			  30
#define BSP_VENDER_LENGTH		  30
#define BSP_SEQ_LENGTH			  30




/*�����鲥��*/
#define BSP_OP_PKG               34

typedef struct Boot_param_data
	{
		/* �����־*/
		DWORD dwHWReset;
		/*��λ���ͣ����縴λ,2 Ӳ��λ,3 ��λ */
        DWORD dwRsetType;                   
        /*��λ����*/
        DWORD dwResetCont;
        SDWORD dwMinResult;
        SDWORD dwBKResult;
        DWORD dwBoardType;                   
		DWORD dwBoardSlot;
		/* ���״̬ BSP_SOFT_MINSYS  ��Сϵͳ  BSP_SOFT_MAINSOFT �������*/
		DWORD dwSoftState;
		
		/* ����������״̬1:�������״̬ 0:����״̬*/
		DWORD dwVxworksDebuger;
 	} BOOT_PARAM_DATA;


/*�����ز���*/

/*
�����ļ��ṹ���£�
У����|�ļ���־|�汾��|�ļ���ʼƫ��|�ļ�����|
Ӳ���汾�Ÿ���|Ӳ���汾��1|Ӳ���汾��2|Ӳ���汾��N|
 PCB�汾�Ÿ���| PCB�汾��1| PCB�汾��2| PCB�汾��N|
PCBA�汾�Ÿ���|PCBA�汾��1|PCBA�汾��2|PCBA�汾��N|
�ļ�����|�������
*/
#define FILE_FLG  (0x4)
#define FILE_VER  (0x8)
#define FILE_OFF  (0xC)
#define FILE_LEN  (0x10)
#define FELE_HVER (0x14)

#define FILE_TYPE_MAINSOFT          (0x12345678)
#define FILE_TYPE_MINISYS           (0x23456789)
#define FILE_TYPE_LOGIC             (0x34567891)


#define FILE_START_VALUE(value)     ((volatile DWORD *)value)
#define FILE_CHECKSUM_START(value)     ((volatile DWORD *)(value+FILE_FLG))

#define FILE_SUM_VALUE(value)       (*((volatile DWORD *)(value)))
#define FILE_FLG_VALUE(value)       (*((volatile DWORD *)((value)+FILE_FLG)))
#define FILE_VER_VALUE(value)       (*((volatile DWORD *)((value)+FILE_VER)))
#define FILE_OFF_VALUE(value)       (*((volatile DWORD *)((value)+FILE_OFF)))
#define FILE_LEN_VALUE(value)       (*((volatile DWORD *)((value)+FILE_LEN)))
#define FELE_HVER_VALUE(value)       (*((volatile DWORD *)((value)+FELE_HVER)))
/* LED ��ض���*/
#define LED_ON   (1)
#define LED_OFF  (2)
#define LED_SIK  (3)

#define LED_DIV_DEF  (0x5)
#define LED_SIK_SLOW (0x5)
#define LED_SIK_FAST (0x1)
/* WATCH DOG ����*/

/*Ӳ��ι��ʱ�䵥λ(10 ����)*/
#define BSP_HARD_FEED_TIME    (100 )
#define BSP_HW_RESET          (0x55AA5414)
/* ���ι��ʱ��(��ι����λʱ��)����λBSP_HARD_FEED_TIME */
#define BSP_SOFT_FEED_TIME    (600)
#define BSP_TASK_CUNT         (1024)
#define BSP_DOG_TASKLEV_H     (10)
#define BSP_DOG_TASKLEV_L     (250)
#define BSP_LED_TASK          (25)

/*���ƶ���*/
/*1:����2:����3:����4:����*/
#define BSP_LED_SLOW    (2)
#define BSP_LED_OFF     (3)
#define BSP_LED_ON      (4)
#define BSP_LED_FAST	(1)







/* �������*/
#define BSP_VXWORKS_DEBUG     (0x55AA5414)

#define BSP_SPI_FLASH_CS      (22)/*PA22*/

/* IO ��ض���*/
#define BSP_DOG_EN_BIO              (2)
#define BSP_DOG_FEED_BIO            (1)
#define BSP_ALARMLED_CIO            (0)	  /**/
#define BSP_RUNLED_CIO              (27)   /* PA27*/
#define BSP_CLOCK_CIO               (27)   /* PB27*/

#define BSP_CPLD_RESET				(13) /*PC13*/
#define BSP_CPLD_DOG_OPEN			(28) /*PA28*/

#define BSP_R_FPGA					(15) /*PC15*/
#define BSP_R_PCIE					(2)  /*PC2*/


#define BSP_PIOD      (0xFFFFFA00) /* (PIOD) Base Address*/
#define BSP_PIOC      (0xFFFFF800) /* (PIOC) Base Address*/
#define BSP_PIOB      (0xFFFFF600) /* (PIOB) Base Address*/
#define BSP_PIOA      (0xFFFFF400) /* (PIOA) Base Address*/
#define BSP_MACADD		(0xFFFBC000)

#endif /* __BSP_BSPINCLUDE_H__ */



