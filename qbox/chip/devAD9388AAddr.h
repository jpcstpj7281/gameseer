/******************************************************************************

 文件名          :  CPFPGA.h

******************************************************************************/

#ifndef __CPAD9388AADDR_H_
#define __CPAD9388AADDR_H_
    
#ifdef __cplusplus
    extern "C"{
#endif /* __cplusplus */



/***********************************************************************************************
*			AD9388A Registers Define
***********************************************************************************************/
/*I2C Address*/
#define		I2C_ADDR_USER_MAP			0x40
#define		I2C_ADDR_USER_SUB_MAP_1		0x44
#define		I2C_ADDR_USER_SUB_MAP_2		0x60
#define		I2C_ADDR_USER_SUB_MAP_3		0x48
#define		I2C_ADDR_HDMI_MAP			0x68




/*User Map*/
#define	    AD9388_USER_TOD				0x03  /*Tristate Output Drivers rw*/
#define     AD9388_USER_EXT_OUT_CTRL    0x04  /*Extended Output Control rw*/
#define     AD9388_USER_PRIM_MODE       0x05  /*Primary Mode rw*/
#define     AD9388_USER_VID_STD         0x06  /*Video Standard rw*/
#define     AD9388_USER_USS2_ADDR       0x0E  /*uss2_slave_address rw*/
#define     AD9388_USER_PWR_MANAGE      0x0F  /*Power Management rw*/
#define     AD9388_USER_IDENT           0x11  /*Ident r*/
#define     AD9388_USER_STATUS_2        0x12  /*Status 2 r*/
#define     AD9388_USER_VER_SCAL_VAL    0x1D  /*Vertical Scale Value 1 rw*/
#define		AD9388_USER_TLLC_POLARITY	0x37  /*PCLK output polarrty*/
#define     AD9388_USER_ADC_CTRL        0x3A  /*ADC Control rw*/
#define     AD9388_USER_BIAS_CTRL       0x3B  /*Bias Control rw*/
#define     AD9388_USER_TLLC_CTRL       0x3C  /*TLLC Control Analogue rw*/
#define		AD9388_USER_PLL_QPUMP_CTRL	0x47  /*PLL charge pump current setting rw*/
#define     AD9388_USER_CSC_1           0x52  /*rw*/
#define     AD9388_USER_CSC_2           0x53  /*rw*/
#define     AD9388_USER_CSC_3           0x54  /*rw*/
#define     AD9388_USER_CSC_4           0x55  /*rw*/
#define     AD9388_USER_CSC_5           0x56  /*rw*/
#define     AD9388_USER_CSC_6           0x57  /*rw*/
#define     AD9388_USER_CSC_7           0x58  /*rw*/
#define     AD9388_USER_CSC_8           0x59  /*rw*/
#define     AD9388_USER_CSC_9           0x5A  /*rw*/
#define     AD9388_USER_CSC_10          0x5B  /*rw*/
#define     AD9388_USER_CSC_11          0x5C  /*rw*/
#define     AD9388_USER_CSC_12          0x5D  /*rw*/
#define     AD9388_USER_CSC_13          0x5E  /*rw*/
#define     AD9388_USER_CSC_14          0x5F  /*rw*/
#define     AD9388_USER_CSC_15          0x60  /*rw*/
#define     AD9388_USER_CSC_16          0x61  /*rw*/
#define     AD9388_USER_CSC_17          0x62  /*rw*/
#define     AD9388_USER_CSC_18          0x63  /*rw*/
#define     AD9388_USER_CSC_19          0x64  /*rw*/
#define     AD9388_USER_CSC_20          0x65  /*rw*/
#define     AD9388_USER_CSC_21          0x66  /*rw*/
#define     AD9388_USER_CSC_22          0x67  /*rw*/
#define     AD9388_USER_CSC_23          0x68  /*rw*/
#define     AD9388_USER_CONFIG_1        0x69  /*Config 1 rw*/
#define     AD9388_USER_TLLC_PHS_ADJ    0x6A  /*TLLC Phase Adjust rw*/
#define     AD9388_USER_CP_OUT_SEL      0x6B  /*CP Output Selection rw*/
#define     AD9388_USER_CP_CLAMP_1      0x6C  /*CP Clamp 1 rw*/
#define     AD9388_USER_CP_CLAMP_2      0x6D  /*CP Clamp 2 rw*/
#define     AD9388_USER_CP_CLAMP_3      0x6E  /*CP Clamp 3 rw*/
#define     AD9388_USER_CP_CLAMP_4      0x6F  /*CP Clamp 4 rw*/
#define     AD9388_USER_CP_CLAMP_5      0x70  /*CP Clamp 5 rw*/
#define     AD9388_USER_CP_AGC_1        0x71  /*CP AGC 1 rw*/
#define     AD9388_USER_CP_AGC_2        0x72  /*CP AGC 2 rw*/
#define     AD9388_USER_CP_AGC_3        0x73  /*CP AGC 3 rw*/
#define     AD9388_USER_CP_AGC_4        0x74  /*CP AGC 4 rw*/
#define     AD9388_USER_CP_AGC_5        0x75  /*CP AGC 5 rw*/
#define     AD9388_USER_CP_AGC_6        0x76  /*CP AGC 6 rw*/
#define     AD9388_USER_CP_OFFSET_1     0x77  /*CP Offset 1 rw*/
#define     AD9388_USER_CP_OFFSET_2     0x78  /*CP Offset 2 rw*/
#define     AD9388_USER_CP_OFFSET_3     0x79  /*CP Offset 3 rw*/
#define     AD9388_USER_CP_OFFSET_4     0x7A  /*CP Offset 4 rw*/
#define     AD9388_USER_CP_AV_CTRL      0x7B  /*CP AV Control rw*/
#define     AD9388_USER_CP_HVF_CTRL_1   0x7C  /*CP HVF Control 1 rw*/
#define     AD9388_USER_CP_HVF_CTRL_2   0x7D  /*CP HVF Control 2 rw*/
#define     AD9388_USER_CP_HVF_CTRL_3   0x7E  /*CP HVF Control 3 rw*/
#define     AD9388_USER_CP_HVF_CTRL_4   0x7F  /*CP HVF Control 4 rw*/
#define     AD9388_USER_CP_HVF_CTRL_5   0x80  /*CP HVF Control 5 rw*/
#define     AD9388_USER_CP_CR_AV_BL      0x81  /*CP   disable or enable embeded time codes blanking insertion rw*/
#define     AD9388_USER_CP_MEAS_CTRL_3  0x83  /*CP Measure Control 3 rw*/
#define     AD9388_USER_CP_MEAS_CTRL_4  0x84  /*CP Measure Control 4 rw*/
#define     AD9388_USER_CP_DTCT_CTRL_1  0x85  /*CP Detection Control 1 rw*/
#define     AD9388_USER_CP_MISC_CTRL_1  0x86  /*CP Misc Control 1 rw*/
#define     AD9388_USER_CP_TLLC_CTRL_1  0x87  /*CP TLLC Control 1 rw*/
#define     AD9388_USER_CP_TLLC_CTRL_2  0x88  /*CP TLLC Control 2 rw*/
#define     AD9388_USER_CP_TLLC_CTRL_3  0x89  /*CP TLLC Control 3 rw*/
#define     AD9388_USER_CP_TLLC_CTRL_4  0x8A  /*CP TLLC Control 4 rw*/
#define     AD9388_USER_CP_DE_CTRL_1    0x8B  /*CP DE Ctrl 1 _58 rw*/
#define     AD9388_USER_CP_DE_CTRL_2    0x8C  /*CP DE Ctrl 2 _59 rw*/
#define     AD9388_USER_CP_DE_CTRL_3    0x8D  /*CP DE Ctrl 3 _60 rw*/
#define     AD9388_USER_CP_DE_CTRL_4    0x8E  /*CP DE Ctrl 4 _61 rw*/
#define     AD9388_USER_FR_LL_1         0x8F  /*Free Run Line Length 1 w*/
#define     AD9388_USER_FR_LL_2         0x90  /*Free Run Line Length 2 w*/
#define     AD9388_USER_DPP_CP_64       0x91  /*DPP_CP_64 w*/
#define     AD9388_USER_RB_CP_AGC_1     0xA0  /*RB CP AGC 1 r*/
#define     AD9388_USER_RB_CP_AGC_2     0xA1  /*RB CP AGC 2 r*/
#define     AD9388_USER_RB_CP_MEAS_1   0xA2  /*RB CP Measure 1 r*/
#define     AD9388_USER_RB_CP_MEAS_2    0xA3  /*RB CP Measure 2 r*/
#define     AD9388_USER_RB_CP_MEAS_3    0xA4  /*RB CP Measure 3 r*/
#define     AD9388_USER_RB_CP_MEAS_4    0xA5  /*RB CP Measure 4 r*/
#define     AD9388_USER_RB_CP_HS_DEP_1  0xA7  /*RB CP HSync Depth 1 r*/

/*这几个地址参看7441的DATASHEET，AD9388A是没有开放的*/
#define     AD9388_USER_RB_CP_START_SAV    		 0xA2 /*SAV Height 8bit  w*/
#define     AD9388_USER_RB_CP_START_SAV_EAV     0xA3  /*SAV Low 4bit and EAV Height 4bit w*/
#define     AD9388_USER_RB_CP_START_EAV    		 0xA4  /*EAV Low 8bit  w*/
#define     AD9388_USER_RB_CP_START_VBI   		 0xA5  /*VBI start Height 8bit  w*/
#define     AD9388_USER_RB_CP_START_END_VBI 	 0xA6  /*VBI start  Low 4bit and VBI END Height 4bit w*/
#define     AD9388_USER_RB_CP_END_VBI   			 0xA7  /*VBI END Low 8bit  w*/

#define     AD9388_USER_RB_CP_HS_DEP_2  0xA8  /*RB CP HSync Depth 2 r*/
#define     AD9388_USER_RB_CP_HS_DEP_3  0xA9  /*RB CP HSync Depth 3 r*/
#define     AD9388_USER_RB_CP_HS_DEP_4  0xAA  /*RB CP HSync Depth 4 r*/
#define     AD9388_USER_RB_CP_HS_DEP_5  0xAB  /*RB CP HSync Depth 5 r*/
#define     AD9388_USER_RB_CP_HS_DEP_6  0xAC  /*RB CP HSync Depth 6 r*/
#define     AD9388_USER_DPP_CP_90       0xAB  /*DPP_CP_90 w*/
#define     AD9388_USER_DPP_CP_91       0xAC  /*DPP_CP_91 w*/
#define     AD9388_USER_RB_CP_PK_VD_1   0xAD  /*RB CP Peak Video 1 r*/
#define     AD9388_USER_RB_CP_PK_VD_2   0xAE  /*RB CP Peak Video 2 r*/
#define     AD9388_USER_RB_CP_PK_VD_3   0xAF  /*RB CP Peak Video 3 r*/
#define     AD9388_USER_RB_CP_PK_VD_4   0xB0  /*RB CP Peak Video 4 r*/
#define     AD9388_USER_RB_STD_ID_1     0xB1  /*RB Standard Ident 1 r*/
#define     AD9388_USER_RB_STD_ID_2     0xB2  /*RB Standard Ident 2 r*/
#define     AD9388_USER_RB_STD_ID_3     0xB3  /*RB Standard Ident 3 r*/
#define     AD9388_USER_RB_STD_ID_4     0xB4  /*RB Standard Ident 4 r*/
#define     AD9388_USER_RB_STD_ID_5     0xB5  /*RB Standard Ident 5 r*/
#define     AD9388_USER_DPP_CP_97       0xB2  /*DPP_CP_97 w*/
#define     AD9388_USER_DPP_CP_98       0xB3  /*DPP_CP_98 w*/
#define     AD9388_USER_HDMI_CTRL       0xBA  /*HDMI w*/
#define     AD9388_USER_DPP_CP_107      0xBC  /*DPP_CP_107 r*/
#define     AD9388_USER_CP_DEF_COL_1    0xBF  /*CP DEF COL 1 rw*/
#define     AD9388_USER_CP_DEF_COL_2    0xC0  /*CP DEF COL 2 rw*/
#define     AD9388_USER_CP_DEF_COL_3    0xC1  /*CP DEF COL 3 rw*/
#define     AD9388_USER_CP_DEF_COL_4    0xC2  /*CP DEF COL 4 rw*/
#define     AD9388_USER_ADC_SW_1        0xC3  /*ADC Switch 1 rw*/
#define     AD9388_USER_ADC_SW_2        0xC4  /*ADC Switch 2 rw*/
#define     AD9388_USER_CP_CPHS_CTRL_1  0xC5  /*CP Clamp Pos HS Ctrl 1 rw*/
#define     AD9388_USER_DPP_CP_118      0xC9  /*DPP_CP_118 rw*/
#define     AD9388_USER_FCL_1           0xCA  /*Field Length Count 1 r*/
#define     AD9388_USER_FCL_2           0xCB  /*Field Length Count 2 r*/
#define     AD9388_USER_AFE_CTRL_1      0xF3  /*AFE_CONTROL 1 rw*/
#define     AD9388_USER_DRIVE_STR       0xF4  /*Drive Strength rw*/
#define     AD9388_USER_VS_MOD_CTRL     0xF9  /*VS Mode Control rw*/
#define     AD9388_USER_GCCTL           0xFD  /*general_chip_ctl rw*/
#define     AD9388_USER_PIN_CHK_OP      0xFE  /*Pin_Checker_Op rw*/
/*User Sub Map 1*/
#define     AD9388_SUB1_INT_CONFIG_0    0x40 /*Interrupt Configuration 0 rw*/
#define     AD9388_SUB1_INT_CONFIG_1    0x41 /*Interrupt Configuration 1 rw*/
#define     AD9388_SUB1_INT_STATUS_1    0x42 /*Interrupt Status 1 r*/
#define     AD9388_SUB1_INT_CLEAR_1     0x42 /*Interrupt Clear 1 w*/
#define     AD9388_SUB1_INT2_MASK_1     0x43 /*Interrupt 2 Maskb 1 rw*/
#define     AD9388_SUB1_INT_MASK_1      0x44 /*Interrupt Maskb 1 rw*/
#define     AD9388_SUB1_RAW_STATUS_2    0x45 /*Raw Status 2 r*/
#define     AD9388_SUB1_INT_STATUS_2    0x46 /*Interrupt Status 2 r*/
#define     AD9388_SUB1_INT_CLEAR_2     0x46 /*Interrupt Clear 2 w*/
#define     AD9388_SUB1_INT2_MASK_2     0x47 /*Interrupt 2 Maskb 2 rw*/
#define     AD9388_SUB1_INT_MASK_2      0x48 /*Interrupt Maskb 2 rw*/
#define     AD9388_SUB1_RAW_STATUS_3    0x49 /*Raw Status 3 r*/
#define     AD9388_SUB1_INT_STATUS_3    0x4A /*Interrupt Status 3 r*/
#define     AD9388_SUB1_INT_CLEAR_3     0x4A /*Interrupt Clear 3 w*/
#define     AD9388_SUB1_INT2_MASK_3     0x4B /*Interrupt 2 Maskb 3 rw*/
#define     AD9388_SUB1_INT_MASK_3      0x4C /*Interrupt Maskb 3 rw*/
#define     AD9388_SUB1_RAW_STATUS_4    0x4D /*Raw Status 4 r*/
#define     AD9388_SUB1_INT_STATUS_4    0x4E /*Interrupt Status 4 r*/
#define     AD9388_SUB1_INT_CLEAR_4     0x4E /*Interrupt Clear 4 w*/
#define     AD9388_SUB1_INT2_MASK_4     0x4F /*Interrupt 2 Maskb 4 rw*/
#define     AD9388_SUB1_INT_MASK_4      0x50 /*Interrupt Maskb 4 rw*/
#define     AD9388_SUB1_HDMI_RAW_ST_1   0x60 /*HDMI_Raw_Status_1 r*/
#define     AD9388_SUB1_HDMI_INT_ST_1   0x61 /*HDMI_Int_Status_1 r*/
#define     AD9388_SUB1_HDMI_INT_CLR_1  0x61 /*HDMI_Int_Clr_1 w*/
#define     AD9388_SUB1_HDMI_INT2_MK_1  0x62 /*HDMI_Int2_Maskb_1 rw*/
#define     AD9388_SUB1_HDMI_INT_MK_1   0x63 /*HDMI_Int_Maskb_1 rw*/
#define     AD9388_SUB1_HDMI_RAW_ST_2   0x64 /*HDMI_Raw_Status_2 r*/
#define     AD9388_SUB1_HDMI_INT_ST_2   0x65 /*HDMI_Int_Status_2 r*/
#define     AD9388_SUB1_HDMI_INT_CLR_2  0x65 /*HDMI_Int_Clr_2 w*/
#define     AD9388_SUB1_HDMI_INT2_MK_2  0x66 /*HDMI_Int2_Maskb_2 rw*/
#define     AD9388_SUB1_HDMI_INT_MK_2   0x67 /*HDMI_Int_Maskb_2 rw*/
#define     AD9388_SUB1_HDMI_RAW_ST_3   0x68 /*HDMI_Raw_Status_3 r*/
#define     AD9388_SUB1_HDMI_INT_ST_3   0x69 /*HDMI_Int_Status_3 r*/
#define     AD9388_SUB1_HDMI_INT_CLR_3  0x69 /*HDMI_Int_Clr_3 w*/
#define     AD9388_SUB1_HDMI_INT2_MK_3  0x6A /*HDMI_Int2_Maskb_3 rw*/
#define     AD9388_SUB1_HDMI_INT_MK_3   0x6B /*HDMI_Int_Maskb_3 rw*/
#define     AD9388_SUB1_HDMI_INT_ST_4   0x6C /*HDMI_Int_Status_4 r*/
#define     AD9388_SUB1_HDMI_INT_CLR_4  0x6C /*HDMI_Int_Clr_4 w*/
#define     AD9388_SUB1_HDMI_INT2_MK_4  0x6D /*HDMI_Int2_Maskb_4 rw*/
#define     AD9388_SUB1_HDMI_INT_MK_4   0x6E /*HDMI_Int_Maskb_4 rw*/
#define     AD9388_SUB1_HDMI_INT_ST_5   0x6F /*HDMI_Int_Status_5 r*/
#define     AD9388_SUB1_HDMI_INT_CLR_5  0x6F /*HDMI_Int_Clr_5 w*/
#define     AD9388_SUB1_HDMI_INT2_MK_5  0x70 /*HDMI_Int2_Maskb_5 rw*/
#define     AD9388_SUB1_HDMI_INT_MK_5   0x71 /*HDMI_Int_Maskb_5 rw*/
#define     AD9388_SUB1_HDMI_INT_ST_6   0x72 /*HDMI_Status_6 r*/
#define     AD9388_SUB1_HDMI_INT_CLR_6  0x72 /*HDMI_Int_Clr_6 w*/
#define     AD9388_SUB1_HDMI_INT2_MK_6  0x73 /*HDMI_Int2_Maskb_6 rw*/
#define     AD9388_SUB1_HDMI_INT_MK_6   0x74 /*HDMI_Int_Maskb_6 rw*/
#define     AD9388_SUB1_DLL_ON_LLC      0x75 /*DLL_on_LLC_path rw*/

#define     AD9388_SUB1_CP_CONTRAST     0x9A
#define     AD9388_SUB1_CP_SATURATION   0x9B
#define     AD9388_SUB1_CP_BRIGHTNESS   0x9C
#define     AD9388_SUB1_CP_HUE          0x9D

#define     AD9388_SUB1_HDMI_FLG_CLR_4  0xAC /*HDMI_flag_Clr_4 w*/
#define     AD9388_SUB1_HDMI_FLG_CLR_5  0xAF /*HDMI_flag_Clr_5 w*/
#define     AD9388_SUB1_HDMI_FLG_CLR_6  0xB2 /*HDMI_flag_Clr_6 w*/
/*HDMI Map*/
#define     AD9388_HDMI_REG_00          0x00 /*REGISTER_00H rw*/
#define     AD9388_HDMI_REG_01          0x01 /*REGISTER_01H rw*/
#define     AD9388_HDMI_REG_02          0x02 /*REGISTER_02H rw*/
#define     AD9388_HDMI_REG_03          0x03 /*REGISTER_03H rw*/
#define     AD9388_HDMI_REG_04          0x04 /*REGISTER_04H r*/
#define     AD9388_HDMI_REG_05          0x05 /*REGISTER_05H r*/
#define     AD9388_HDMI_TMDSFREQ        0x06 /*TMDSFREQ r*/
#define     AD9388_HDMI_REG_07          0x07 /*REGISTER_07H r*/
#define     AD9388_HDMI_LINE_WIDTH      0x08 /*LINE WIDTH r*/
#define     AD9388_HDMI_FLD_0_HT_H      0x09 /*FIELD 0 HEIGHT MSB r*/
#define     AD9388_HDMI_FLD_0_HT_L      0x0A /*FIELD 0 HEIGHT r*/
#define     AD9388_HDMI_REG_0B          0x0B /*REGISTER_0BH r*/
#define     AD9388_HDMI_FLD_1_HT        0x0C /*FIELD 1 HEIGHT r*/
#define     AD9388_HDMI_REG_0D          0x0D /*REGISTER_0DH rw*/
#define     AD9388_HDMI_AMS             0x0F /*AUDIO MUTE SPEED rw*/
#define     AD9388_HDMI_REG_10          0x10 /*REGISTER_10H rw*/
#define     AD9388_HDMI_AFAF            0x11 /*AUDIO FIFO ALMOST FULL T rw*/
#define     AD9388_HDMI_AFAE            0x12 /*AUDIO FIFO ALMOST EMPTY rw*/
#define     AD9388_HDMI_ACM             0x13 /*AUDIO COAST MASK rw*/
#define     AD9388_HDMI_MT_MASK_H       0x14 /*MUTE MASK 19_16 rw*/
#define     AD9388_HDMI_MT_MASK_M       0x15 /*MUTE MASK 15_8 rw*/
#define     AD9388_HDMI_MT_MASK_L       0x16 /*MUTE MASK 7_0 rw*/
#define     AD9388_HDMI_PKT_DET_H       0x17 /*PACKETS DETECTED MSB r*/
#define     AD9388_HDMI_PKT_DET_L       0x18 /*PACKETS DETECTED r*/
#define     AD9388_HDMI_PKT_ST_FLG_H    0x19 /*PACKET STATUS FLAGS 20_16 r*/
#define     AD9388_HDMI_PKT_ST_FLG_M    0x1A /*PACKET STATUS FLAGS 15_8 r*/
#define     AD9388_HDMI_PKT_ST_FLG_L    0x1B /*PACKET STATUS FLAGS 7_0 r*/
#define     AD9388_HDMI_REG_1C          0x1C /*REGISTER_1CH rw*/
#define     AD9388_HDMI_REG_1D          0x1D /*REGISTER_1DH rw*/
#define     AD9388_HDMI_TLW_H           0x1E /*TOTAL_LINE_WIDTH_MSB r*/
#define     AD9388_HDMI_TLW_L           0x1F /*TOTAL_LINE_WIDTH r*/
#define     AD9388_HDMI_HS_FP_H         0x20 /*HSYNC_FRONT_PORCH_MSB r*/
#define     AD9388_HDMI_HS_FP_L         0x21 /*HSYNC_FRONT_PORCH r*/
#define     AD9388_HDMI_HS_PW_H         0x22 /*HSYNC_PULSE_WIDTH_MSB r*/
#define     AD9388_HDMI_HS_PW_L         0x23 /*HSYNC_PULSE_WIDTH r*/
#define     AD9388_HDMI_HS_BP_H         0x24 /*HSYNC_BACK_PORCH_MSB r*/
#define     AD9388_HDMI_HS_BP_L         0x25 /*HSYNC_BACK_PORCH r*/
#define     AD9388_HDMI_FLD0_TTHT_H     0x26 /*FIELD0_TOTAL_HEIGHT_MSB r*/
#define     AD9388_HDMI_FLD0_TTHT_L     0x27 /*FIELD0_TOTAL_HEIGHT r*/
#define     AD9388_HDMI_FLD1_TTHT_H     0x28 /*FIELD1_TOTAL_HEIGHT_MSB r*/
#define     AD9388_HDMI_FLD1_TTHT_L     0x29 /*FIELD1_TOTAL_HEIGHT r*/
#define     AD9388_HDMI_FLD0_VS_FP_H    0x2A /*FIELD0_VS_FRONT_PORCH_MSB r*/
#define     AD9388_HDMI_FLD0_VS_FP_L    0x2B /*FIELD0_VS_FRONT_PORCH r*/
#define     AD9388_HDMI_FLD1_VS_FP_H    0x2C /*FIELD1_VS_FRONT_PORCH_MSB r*/
#define     AD9388_HDMI_FLD1_VS_FP_L    0x2D /*FIELD1_VS_FRONT_PORCH r*/
#define     AD9388_HDMI_FLD0_VS_PW_H    0x2E /*FIELD0_VS_PULSE_WIDTH_MSB r*/
#define     AD9388_HDMI_FLD0_VS_PW_L    0x2F /*FIELD0_VS_PULSE_WIDTH r*/
#define     AD9388_HDMI_FLD1_VS_PW_H    0x30 /*FIELD1_VS_PULSE_WIDTH_MSB r*/
#define     AD9388_HDMI_FLD1_VS_PW_L    0x31 /*FIELD1_VS_PULSE_WIDTH r*/
#define     AD9388_HDMI_FLD0_VS_BP_H    0x32 /*FIELD0_VS_BACK_PORCH_MSB r*/
#define     AD9388_HDMI_FLD0_VS_BP_L    0x33 /*FIELD0_VS_BACK_PORCH r*/
#define     AD9388_HDMI_FLD1_VS_BP_H    0x34 /*FIELD1_VS_BACK_PORCH_MSB r*/
#define     AD9388_HDMI_FLD1_VS_BP_L    0x35 /*FIELD1_VS_BACK_PORCH r*/
#define     AD9388_HDMI_CHAN_ST_DATA_0  0x36 /*CHANNEL STATUS DATA 0 r*/
#define     AD9388_HDMI_CHAN_ST_DATA_1  0x37 /*CHANNEL STATUS DATA 1 r*/
#define     AD9388_HDMI_CHAN_ST_DATA_2  0x38 /*CHANNEL STATUS DATA 2 r*/
#define     AD9388_HDMI_CHAN_ST_DATA_3  0x39 /*CHANNEL STATUS DATA 3 r*/
#define     AD9388_HDMI_CHAN_ST_DATA_4  0x3A /*CHANNEL STATUS DATA 4 r*/
#define     AD9388_HDMI_PLL_DIV         0x3C /*PLL DIVIDER rw*/
#define     AD9388_HDMI_REG_48          0x48 /*REGISTER_48H rw*/
#define     AD9388_HDMI_REG_5A          0x5A /*REGISTER_5A w*/
#define     AD9388_HDMI_CTS_REG1        0x5B /*CTS_REG1 r*/
#define     AD9388_HDMI_CTS_REG2        0x5C /*CTS_REG2 r*/
#define     AD9388_HDMI_CTS_REG3        0x5D /*CTS_REG3_N_REG r*/
#define     AD9388_HDMI_N_REG1          0x5D /*CTS_REG3_N_REG r*/
#define     AD9388_HDMI_N_REG2          0x5E /*N_REG2 r*/
#define     AD9388_HDMI_N_REG3          0x5F /*N_REG2 r*/




#ifdef __cplusplus
}
#endif
    
#endif


