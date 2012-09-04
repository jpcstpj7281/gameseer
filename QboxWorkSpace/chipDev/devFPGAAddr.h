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

    #define FPGA_USER_VERSION_ADDR_R                  0x0000      /*R*/
    #define FPGA_TEST_VERSION_ADDR_R                  0x0002

    #define FPGA_BOARD_TYPE_ADDR_R                    0x0004      /*单板类型地址R*/

    #define FPGA_DATE_REGISTER_ADDR_R                 0x0006      /*时间寄存器地址*/


    /*控制寄存器RW,BIT0: POWR1014A_RST, 0为有效，1为无效；(上电复位)
                   BIT1: Si5326_RST, 0为有效，1为无效；*/
    #define FPGA_TEST_REGISTER_ADDR_RW                 0x0008      /*测试用*/




    /*测试图寄存器*/
    #define FPGA_TEST_DEW_ADDR_RW                   0x0020     /*FPGA测试图有效宽度*/
    #define FPGA_TEST_DEH_ADDR_RW                   0x0022
    #define FPGA_TEST_HST_ADDR_RW               	0x0024
    #define FPGA_TEST_VST_ADDR_RW             		0x0026
	#define FPGA_TEST_EPY_ADDR_R             		0x0028
	#define FPGA_TEST_FUL_ADDR_R             		0x002a


    #define FPGA_IMG_CTL_ADDR_RW		            0x0030

    #define CP_FPGA_STATE_1_ADDR                    0x0026

    #define CP_FPGA_HS_FREQ_2_ADDR                  0x0027
    #define CP_FPGA_VS_FREQ_2_ADDR                  0x0028
    #define CP_FPGA_PIXEL_FREQ_2_ADDR               0x0029
    #define CP_FPGA_HS_REGISTER_2_ADDR              0x002a
    #define CP_FPGA_VS_REGISTER_2_ADDR              0x002b
    #define CP_FPGA_STATE_2_ADDR                    0x002c


    #define CP_FPGA_HS_FREQ_3_ADDR                  0x002d
    #define CP_FPGA_VS_FREQ_3_ADDR                  0x002e
    #define CP_FPGA_PIXEL_FREQ_3_ADDR               0x002f
    #define CP_FPGA_HS_REGISTER_3_ADDR              0x0030
    #define CP_FPGA_VS_REGISTER_3_ADDR              0x0031
    #define CP_FPGA_STATE_3_ADDR                    0x0032


    #define CP_FPGA_HS_FREQ_4_ADDR                  0x0033
    #define CP_FPGA_VS_FREQ_4_ADDR                  0x0034
    #define CP_FPGA_PIXEL_FREQ_4_ADDR               0x0035
    #define CP_FPGA_HS_REGISTER_4_ADDR              0x0036
    #define CP_FPGA_VS_REGISTER_4_ADDR              0x0037
    #define CP_FPGA_STATE_4_ADDR                    0x0038


    #define CP_FPGA_HS_FREQ_5_ADDR                  0x0039
    #define CP_FPGA_VS_FREQ_5_ADDR                  0x003a
    #define CP_FPGA_PIXEL_FREQ_5_ADDR               0x003b
    #define CP_FPGA_HS_REGISTER_5_ADDR              0x003c
    #define CP_FPGA_VS_REGISTER_5_ADDR              0x003d
    #define CP_FPGA_STATE_5_ADDR                    0x003e

    #define CP_FPGA_HS_FREQ_6_ADDR                  0x003f
    #define CP_FPGA_VS_FREQ_6_ADDR                  0x0040
    #define CP_FPGA_PIXEL_FREQ_6_ADDR               0x0041
    #define CP_FPGA_HS_REGISTER_6_ADDR              0x0042
    #define CP_FPGA_VS_REGISTER_6_ADDR              0x0043
    #define CP_FPGA_STATE_6_ADDR                    0x0044


    /*图象剪切功能*/
    #define CP_FPGA_CLIP_EN_ADDR                    0x0050

    #define CP_FPGA_CLIP_XFIRST_1_ADDR              0x0051
    #define CP_FPGA_CLIP_YFIRST_1_ADDR              0x0052
    #define CP_FPGA_CLIP_XLAST_1_ADDR               0x0053
    #define CP_FPGA_CLIP_YLAST_1_ADDR               0x0054

    #define CP_FPGA_CLIP_XFIRST_2_ADDR              0x0055
    #define CP_FPGA_CLIP_YFIRST_2_ADDR              0x0056
    #define CP_FPGA_CLIP_XLAST_2_ADDR               0x0057
    #define CP_FPGA_CLIP_YLAST_2_ADDR               0x0058

    #define CP_FPGA_CLIP_XFIRST_3_ADDR              0x0059
    #define CP_FPGA_CLIP_YFIRST_3_ADDR              0x005a
    #define CP_FPGA_CLIP_XLAST_3_ADDR               0x005b
    #define CP_FPGA_CLIP_YLAST_3_ADDR               0x005c

    #define CP_FPGA_CLIP_XFIRST_4_ADDR              0x005d
    #define CP_FPGA_CLIP_YFIRST_4_ADDR              0x005e
    #define CP_FPGA_CLIP_XLAST_4_ADDR               0x005f
    #define CP_FPGA_CLIP_YLAST_4_ADDR               0x0060

    #define CP_FPGA_CLIP_XFIRST_5_ADDR              0x0061
    #define CP_FPGA_CLIP_YFIRST_5_ADDR              0x0062
    #define CP_FPGA_CLIP_XLAST_5_ADDR               0x0063
    #define CP_FPGA_CLIP_YLAST_5_ADDR               0x0064

    #define CP_FPGA_CLIP_XFIRST_6_ADDR              0x0065
    #define CP_FPGA_CLIP_YFIRST_6_ADDR              0x0066
    #define CP_FPGA_CLIP_XLAST_6_ADDR               0x0067
    #define CP_FPGA_CLIP_YLAST_6_ADDR               0x0068

    /*图象偏移*/

    #define CP_FPGA_INPUT_TYPE_ADDR                 0x0070

    #define CP_FPGA_HDE_1_ADDR                      0x0071
    #define CP_FPGA_VDE_1_ADDR                     0x0072
    #define CP_FPGA_HDIS_1_ADDR                    0x0073
    #define CP_FPGA_VDIS_1_ADDR                    0x0074

    #define CP_FPGA_HDE_2_ADDR                     0x0075
    #define CP_FPGA_VDE_2_ADDR                     0x0076
    #define CP_FPGA_HDIS_2_ADDR                    0x0077
    #define CP_FPGA_VDIS_2_ADDR                    0x0078

    #define CP_FPGA_HDE_3_ADDR                     0x0079
    #define CP_FPGA_VDE_3_ADDR                     0x007a
    #define CP_FPGA_HDIS_3_ADDR                    0x007b
    #define CP_FPGA_VDIS_3_ADDR                    0x007c

    #define CP_FPGA_HDE_4_ADDR                     0x007d
    #define CP_FPGA_VDE_4_ADDR                     0x007e
    #define CP_FPGA_HDIS_4_ADDR                    0x007f
    #define CP_FPGA_VDIS_4_ADDR                    0x0080

    #define CP_FPGA_HDE_5_ADDR                 0x0081
    #define CP_FPGA_VDE_5_ADDR                 0x0082
    #define CP_FPGA_HDIS_5_ADDR                 0x0083
    #define CP_FPGA_VDIS_5_ADDR                 0x0084

    #define CP_FPGA_HDE_6_ADDR                 0x0085
    #define CP_FPGA_VDE_6_ADDR                 0x0086
    #define CP_FPGA_HDIS_6_ADDR                 0x0087
    #define CP_FPGA_VDIS_6_ADDR                 0x0088


    /*自动白平衡*/
    #define CP_FPGA_AUTOGAIN_EN_ADDR           0X0090

    #define CP_FPGA_RED_1_ADDR                 0x0091

    #define CP_FPGA_GREEN_1_ADDR                 0x0092
    #define CP_FPGA_BLUE_1_ADDR                 0x0093



    #define CP_FPGA_RED_2_ADDR                 0x0094
    #define CP_FPGA_GREEN_2_ADDR                 0x0095
    #define CP_FPGA_BLUE_2_ADDR                 0x0096

    #define CP_FPGA_RED_3_ADDR                 0x0097
    #define CP_FPGA_GREEN_3_ADDR                 0x0098
    #define CP_FPGA_BLUE_3_ADDR                 0x0099

    #define CP_FPGA_RED_4_ADDR                 0x009a
    #define CP_FPGA_GREEN_4_ADDR                 0x009b
    #define CP_FPGA_BLUE_4_ADDR                 0x009c

    #define CP_FPGA_RED_5_ADDR                 0x009d
    #define CP_FPGA_GREEN_5_ADDR                 0x009e
    #define CP_FPGA_BLUE_5_ADDR                 0x009f

    #define CP_FPGA_RED_6_ADDR                 0x00a0
    #define CP_FPGA_GREEN_6_ADDR                 0x00a1
    #define CP_FPGA_BLUE_6_ADDR                 0x00a2




    /*同步*/
    #define CP_FPGA_SYNC_ADDR                  0x00b1


    /*背景图*/
    #define CP_FPGA_IMG_DEWIDTH					0x00b2
    #define CP_FPGA_IMG_DEHEIGH					0x00b3
    #define CP_FPGA_IMG_CTRL					0x00e0
    #define CP_FPGA_IMG_ENABLE					0x00e1
    #define CP_FPGA_IMG_DATA					0x00e2











#ifdef __cplusplus
}
#endif
    
#endif

