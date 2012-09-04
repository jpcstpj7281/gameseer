/******************************************************************************

******************************************************************************/

#define SI5326_SPIN_BYPASS_ADDR       0x00
#define SI5326_CK_PRIOR1_ADDR         0x01
#define SI5326_BWSEL_REG_ADDR         0x02
#define SI5326_CKSEL_REG_ADDR         0x03
#define SI5326_AUTOSEL_REG_ADDR       0x04
#define SI5326_ICMOS_ADDR             0x05
#define SI5326_SLEEP_ADDR             0x06
#define SI5326_FOSREFSEL_ADDR         0x07
#define SI5326_HLOG_1_ADDR            0x08
#define SI5326_HIST_AVG_ADDR          0x09
#define SI5326_DSBL1_REG_ADDR         0x0a
#define SI5326_PD_CK_ADDR             0x0b
#define SI5326_CLAT_ADDR              0x10
#define SI5326_FLAT_VALID_ADDR        0x11
#define SI5326_FLAT_ADDR              0x12
#define SI5326_FOS_EN_ADDR            0x13
#define SI5326_CK_BAD_PIN_ADDR        0x14
#define SI5326_INCDEC_PIN_ADDR        0x15
#define SI5326_CK_ACTV_POL_ADDR       0x16
#define SI5326_LOS_MSK_ADDR           0x17
#define SI5326_FOS_MSK_ADDR           0x18
#define SI5326_N1_HS_ADDR             0x19
#define SI5326_NC1_LS1_ADDR           0x1f
#define SI5326_NC1_LS2_ADDR           0x20
#define SI5326_NC1_LS3_ADDR           0X21
#define SI5326_NC2_LS1_ADDR           0x22
#define SI5326_NC2_LS2_ADDR           0x23
#define SI5326_NC2_LS3_ADDR           0X24
#define SI5326_N2_HS_ADDR             0x28
#define SI5326_N2_LS2_ADDR            0x29
#define SI5326_N2_LS3_ADDR            0X2a
#define SI5326_N31_1_ADDR             0x2b
#define SI5326_N31_2_ADDR             0x2c
#define SI5326_N31_3_ADDR             0x2d
#define SI5326_N32_1_ADDR             0x2e
#define SI5326_N32_2_ADDR             0x2f
#define SI5326_N32_3_ADDR             0x30
#define SI5326_CLKINRATE_ADDR         0x37
#define SI5326_CK_ACTV_REG_ADDR       0x80
#define SI5326_LOS_INT_ADDR           0x81
#define SI5326_CLATPROGRESS_ADDR      0x82
#define SI5326_LOS_FLG_ADDR           0x83
#define SI5326_FOS_FLG_ADDR           0x84
#define SI5326_NVM_REV_ADDR           0x86
#define SI5326_REVID_RO_ADDR          0x87
#define SI5326_RST_REG_ADDR           0x88
#define SI5326_INDEPENDENTSKEW1_ADDR  0x8e  
#define SI5326_INDEPENDENTSKEW2_ADDR  0x8f 

#define SI5326ID  0xD0        /*Id:1101 0000*/

/* Si5326寄存器初始化结构体 */
typedef struct _Si5326RegInitTable
{    
    BYTE byRegisterAddr;
    BYTE byRegisterData;

}Si5326RegInitTable;

DWORD SetSi5326Reg(BYTE byRegAddr, BYTE byRegData);
DWORD GetSi5326Reg(BYTE byRegAddr, BYTE *bypRegData);
