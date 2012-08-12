/******************************************************************************


* ��������         :  �����IP00C772оƬͷ�ļ�
*
******************************************************************************/
    
#ifndef __FPGAADDR_H__
#define __FPGAADDR_H__
    
#ifdef __cplusplus
    extern "C"{
#endif /* __cplusplus */


    /*FPGA 芯片寄存器地址宏定义*/
    // FPGA版本寄存器

    #define FPGA_TEST_REGISTER_ADDR_RW                0x0000      /*R*/
	#define FPGA_USER_VERSION_ADDR_R                  0x0001
    #define FPGA_TEST_VERSION_ADDR_R                  0x0002
    #define FPGA_BOARD_TYPE_ADDR_R                    0x0003      /*单板类型地址R*/
    #define FPGA_DATE_REGISTER_ADDR_R                 0x0004      /*时间寄存器地址*/


    /*测试图寄存器*/
	#define FPGA_TEST_HST_ADDR_RW               	0x000c
	#define FPGA_TEST_VST_ADDR_RW             		0x000d
    #define FPGA_TEST_DEW_ADDR_RW                   0x000e     /*FPGA测试图有效宽度*/
    #define FPGA_TEST_DEH_ADDR_RW                   0x000f
	#define FPGA_TEST_EPY_ADDR_R             		0x0010
	#define FPGA_TEST_FUL_ADDR_R             		0x0011


    #define FPGA_IMG_CTL_ADDR_RW		            0x0020

    #define FPGA_HS_FREQ_1_ADDR                  0x0021
    #define FPGA_VS_FREQ_1_ADDR                  0x0022
    #define FPGA_PIXEL_FREQ_1_ADDR               0x0023
    #define FPGA_HS_REGISTER_1_ADDR              0x0024
    #define FPGA_VS_REGISTER_1_ADDR              0x0025
    #define FPGA_IMG_POL_1_ADDR                  0x0026

	#define FPGA_HS_FREQ_2_ADDR                  0x0027
	#define FPGA_VS_FREQ_2_ADDR                  0x0028
	#define FPGA_PIXEL_FREQ_2_ADDR               0x0029
	#define FPGA_HS_REGISTER_2_ADDR              0x002a
	#define FPGA_VS_REGISTER_2_ADDR              0x002b
	#define FPGA_IMG_POL_2_ADDR                  0x002c

	#define FPGA_HS_FREQ_3_ADDR                  0x002d
	#define FPGA_VS_FREQ_3_ADDR                  0x002e
	#define FPGA_PIXEL_FREQ_3_ADDR               0x002f
	#define FPGA_HS_REGISTER_3_ADDR              0x0030
	#define FPGA_VS_REGISTER_3_ADDR              0x0031
	#define FPGA_IMG_POL_3_ADDR                  0x0032

	#define FPGA_HS_FREQ_4_ADDR                  0x0033
	#define FPGA_VS_FREQ_4_ADDR                  0x0034
	#define FPGA_PIXEL_FREQ_4_ADDR               0x0035
	#define FPGA_HS_REGISTER_4_ADDR              0x0036
	#define FPGA_VS_REGISTER_4_ADDR              0x0037
	#define FPGA_IMG_POL_4_ADDR                  0x0038

	#define FPGA_HS_FREQ_5_ADDR                  0x0039
	#define FPGA_VS_FREQ_5_ADDR                  0x003a
	#define FPGA_PIXEL_FREQ_5_ADDR               0x003b
	#define FPGA_HS_REGISTER_5_ADDR              0x003c
	#define FPGA_VS_REGISTER_5_ADDR              0x003d
	#define FPGA_IMG_POL_5_ADDR                  0x003e

	#define FPGA_HS_FREQ_6_ADDR                  0x003f
	#define FPGA_VS_FREQ_6_ADDR                  0x0040
	#define FPGA_PIXEL_FREQ_6_ADDR               0x0041
	#define FPGA_HS_REGISTER_6_ADDR              0x0042
	#define FPGA_VS_REGISTER_6_ADDR              0x0043
	#define FPGA_IMG_POL_6_ADDR                  0x0044

    /*图象剪切功能*/
    #define FPGA_HOR_SYNC_1_ADDR                  0x0070
	#define FPGA_VER_SYNC_1_ADDR                  0x0071
	#define FPGA_HOR_FP_1_ADDR                    0x0072
	#define FPGA_HOR_BP_1_ADDR                    0x0073
	#define FPGA_VER_FP_1_ADDR                    0x0074
	#define FPGA_VER_BP_1_ADDR                    0x0075

	#define FPGA_HOR_SYNC_2_ADDR                  0x0076
	#define FPGA_VER_SYNC_2_ADDR                  0x0077
	#define FPGA_HOR_FP_2_ADDR                    0x0078
	#define FPGA_HOR_BP_2_ADDR                    0x0079
	#define FPGA_VER_FP_2_ADDR                    0x007a
	#define FPGA_VER_BP_2_ADDR                    0x007b

	#define FPGA_HOR_SYNC_3_ADDR                  0x007c
	#define FPGA_VER_SYNC_3_ADDR                  0x007d
	#define FPGA_HOR_FP_3_ADDR                    0x007e
	#define FPGA_HOR_BP_3_ADDR                    0x007f
	#define FPGA_VER_FP_3_ADDR                    0x0080
	#define FPGA_VER_BP_3_ADDR                    0x0081

	#define FPGA_HOR_SYNC_4_ADDR                  0x0082
	#define FPGA_VER_SYNC_4_ADDR                  0x0083
	#define FPGA_HOR_FP_4_ADDR                    0x0084
	#define FPGA_HOR_BP_4_ADDR                    0x0085
	#define FPGA_VER_FP_4_ADDR                    0x0086
	#define FPGA_VER_BP_4_ADDR                    0x0087

	#define FPGA_HOR_SYNC_5_ADDR                  0x0088
	#define FPGA_VER_SYNC_5_ADDR                  0x0089
	#define FPGA_HOR_FP_5_ADDR                    0x008a
	#define FPGA_HOR_BP_5_ADDR                    0x008b
	#define FPGA_VER_FP_5_ADDR                    0x008c
	#define FPGA_VER_BP_5_ADDR                    0x008d

	#define FPGA_HOR_SYNC_6_ADDR                  0x008f
	#define FPGA_VER_SYNC_6_ADDR                  0x0090
	#define FPGA_HOR_FP_6_ADDR                    0x0091
	#define FPGA_HOR_BP_6_ADDR                    0x0092
	#define FPGA_VER_FP_6_ADDR                    0x0093
	#define FPGA_VER_BP_6_ADDR                    0x0094



    /*图象偏移*/

    #define FPGA_SEL_1_ADDR                 0x00a0
	#define FPGA_SEL_2_ADDR                 0x00a1
	#define FPGA_SEL_3_ADDR                 0x00a2
	#define FPGA_SEL_4_ADDR                 0x00a3
	#define FPGA_SEL_5_ADDR                 0x00a4
	#define FPGA_SEL_6_ADDR                 0x00a5

	#define FPGA_RDEN_ADDR					0x00a6
	#define FPGA_WREN_ADDR					0x00a7










#ifdef __cplusplus
}
#endif
    
#endif

