/******************************************************************************

******************************************************************************/
#include "sys_include.h"
#include "Pll.h" 

WORD InitSi5326(VOID)
{
    BYTE i = 0;
    
    BYTE byData = 0;

    /* Si5326寄存器地址与初始值表 */
    Si5326RegInitTable Table[43] = {
/*    
    //Si5326寄存器地址宏定义                 Si5326寄存器初始值    
        { SI5326_SPIN_BYPASS_ADDR,         0x15 },
        { SI5326_CK_PRIOR1_ADDR ,          0xe4 },
        { SI5326_BWSEL_REG_ADDR ,          0xa2 },
        { SI5326_CKSEL_REG_ADDR ,          0x05 },
        { SI5326_AUTOSEL_REG_ADDR,         0x92 },
        { SI5326_ICMOS_ADDR ,              0x2d },
        //{ SI5326_SLEEP_ADDR,               0x1b },
        { SI5326_SLEEP_ADDR,               0x2d },
        { SI5326_FOSREFSEL_ADDR,           0x28 },
        { SI5326_HLOG_1_ADDR ,             0x00 },
        { SI5326_HIST_AVG_ADDR,            0xc0 },
        { SI5326_DSBL1_REG_ADDR,           0x08 },  //0x08
        { SI5326_PD_CK_ADDR,               0x48 },
        { SI5326_CLAT_ADDR,                0x00 },
        { SI5326_FLAT_VALID_ADDR ,         0x80 },
        { SI5326_FLAT_ADDR ,               0x00 },
        { SI5326_FOS_EN_ADDR,              0x2c },
        { SI5326_CK_BAD_PIN_ADDR,          0x3e },
        { SI5326_INCDEC_PIN_ADDR,          0xfe },
        { SI5326_CK_ACTV_POL_ADDR,         0xdf },
        { SI5326_LOS_MSK_ADDR ,            0x1f },
        { SI5326_FOS_MSK_ADDR,             0x3f },
        { SI5326_N1_HS_ADDR,               0xc0 },
        { SI5326_NC1_LS1_ADDR,             0x00 },
        { SI5326_NC1_LS2_ADDR,             0x00 },
        { SI5326_NC1_LS3_ADDR,             0x01 },
        { SI5326_NC2_LS1_ADDR,             0x00 },
        { SI5326_NC2_LS2_ADDR,             0x00 },
        { SI5326_NC2_LS3_ADDR,             0x01 },
        { SI5326_N2_HS_ADDR  ,             0xc0 },
        { SI5326_N2_LS2_ADDR ,             0x00 },
        { SI5326_N2_LS3_ADDR ,             0xfb },
        { SI5326_N31_1_ADDR  ,             0x00 },
        { SI5326_N31_2_ADDR  ,             0x00 },
        { SI5326_N31_3_ADDR  ,             0x0d },
        { SI5326_N32_1_ADDR  ,             0x00 },
        { SI5326_N32_2_ADDR  ,             0x00 },
        { SI5326_N32_3_ADDR,               0x0d },
        { SI5326_CLKINRATE_ADDR,           0x09 },
        { SI5326_LOS_FLG_ADDR,             0x1f },
        { SI5326_FOS_FLG_ADDR,             0x02 },       
        { SI5326_INDEPENDENTSKEW1_ADDR,    0x00 },
        { SI5326_INDEPENDENTSKEW2_ADDR,    0x00 },
        { SI5326_RST_REG_ADDR,             0x40 }, 
*/
  {0,0x15},
  {1,0xe4},
  {2,0xa2},
  {3,0x5}, 
  {4,0x92},
  {5,0x2d},
  {6,0x1b},//0x36},//0x1b},//2d
  {7,0x28},
  {8,0x0}, 
  {9,0xc0},
 {10,0x0},//8
 {11,0x48},
 {16,0x0}, 
 {17,0x80},
 {18,0x0}, 
 {19,0x2c},
 {20,0x3e},
 {21,0xfe},
 {22,0xdf},
 {23,0x1f},
 {24,0x3f},
 {25,0xc0},
 {31,0x0}, 
 {32,0x0}, 
 {33,0x1}, 
 {34,0x0}, 
 {35,0x0}, 
 {36,0x1}, 
 {40,0xc0},
 {41,0x0}, 
 {42,0xfb},
 {43,0x0}, 
 {44,0x0}, 
 {45,0xd}, 
 {46,0x0}, 
 {47,0x0}, 
 {48,0xd}, 
 {55,0x9}, 
{131,0x1f},
{132,0x2}, 
{142,0x0}, 
{143,0x0}, 
{136,0x40} 
    };

    /* 对Si5326寄存器进行初始化设置 */
    for(i = 0; i < 43; i ++)
    {
        /* 调用WriteSi5326函数写寄存器 */
        SetSi5326Reg(Table[i].byRegisterAddr, Table[i].byRegisterData);        
    }
    for (i = 0; i< 43; i ++)
    {
        GetSi5326Reg(Table[i].byRegisterAddr, &byData);
        if (Table[i].byRegisterData != byData)
        {
            printf("Addr %3d, InData 0x%02x, OutData 0x%02x\n", Table[i].byRegisterAddr, Table[i].byRegisterData, byData);
        }
    }
}

DWORD SetSi5326Reg(BYTE byRegAddr, BYTE byRegData)
{
    I2cWrite(0, SI5326ID, (DWORD)byRegAddr, byRegData);
}

DWORD GetSi5326Reg(BYTE byRegAddr, BYTE *bypRegData)
{
    I2cRead(0, SI5326ID, (DWORD)byRegAddr, bypRegData);
}
