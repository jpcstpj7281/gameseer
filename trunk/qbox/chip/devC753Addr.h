/******************************************************************************
*                    IP00C753  Registers Define
******************************************************************************/

#ifndef _DEV_C753_ADDRH_
#define _DEV_C753_ADDRH_

#ifdef __cplusplus
    extern "C"{


/*Basic setting register*/
#define         REG_C753_BSC_RGBNK          0x00    /*Register select*/
#define         REG_C753_BSC_MCT_L          0x01    /*Main control*/
#define         REG_C753_BSC_MCT_H          0x02    /*Main control*/
#define         REG_C753_BSC_DDRCT          0x03    /*DDR control*/
#define         REG_C753_BSC_RTCT_L         0x04    /*Register value transfer control*/
#define         REG_C753_BSC_RTCT_H         0x05    /*Register value transfer control*/
#define         REG_C753_BSC_MEMCT          0x06    /*Memory control*/
#define         REG_C753_BSC_RSTCT          0x07    /*Reset*/
 /*Bank 0 register*/
#define         REG_C753_B0_OSYCT_L         0x08    /*Output port sync signal control*/
#define         REG_C753_B0_OSYCT_H         0x09    /*Output port sync signal control*/
#define         REG_C753_B0_OHCYCL_L        0x0A    /*Output port horizontal sync signal cycle*/
#define         REG_C753_B0_OHCYCL_H        0x0B    /*Output port horizontal sync signal cycle*/
#define         REG_C753_B0_OVCYCL_L        0x0C    /*Output port vertical sync signal cycle*/
#define         REG_C753_B0_OVCYCL_H        0x0D    /*Output port vertical sync signal cycle*/
#define         REG_C753_B0_OHSCT           0x0E    /*Output port horizontal sync signal control*/
#define         REG_C753_B0_OVSCT           0x0F    /*Output port vertical sync signal control*/
#define         REG_C753_B0_SYRDLY          0x10    /*Forced sync reset delay*/
#define         REG_C753_B0_OVCYCLMIN_L     0x11    /*Forced sync reset control*/
#define         REG_C753_B0_OVCYCLMIN_H     0x12    /*Forced sync reset control*/
#define         REG_C753_B0_FLDRTCT         0x13    /*Field interlock transfer control*/
#define         REG_C753_B0_FLDDLY1         0x14    /*Field propagation delay 1*/
#define         REG_C753_B0_FLDDLY2         0x15    /*Field propagation delay 2*/
#define         REG_C753_B0_OSWP            0x16    /*Output signal swap*/
#define         REG_C753_B0_POCLKCT         0x17    /*POCLK control*/
#define         REG_C753_B0_SCWCT           0x18    /*Scaling width control*/
#define         REG_C753_B0_OINTCT          0x19    /*Interlace output control*/
#define         REG_C753_B0_KCTRL_L         0x1B    /*Keystone correction control*/
#define         REG_C753_B0_KCTRL_H         0x1C    /*Keystone correction control*/
#define         REG_C753_B0_KSCL_L          0x1D    /*Keystone correction initial scaling factor*/
#define         REG_C753_B0_KSCL_H          0x1E    /*Keystone correction initial scaling factor*/
#define         REG_C753_B0_KDLY_L          0x1F    /*Keystone correction delay control*/
#define         REG_C753_B0_KDLY_H          0x20    /*Keystone correction delay control*/
#define         REG_C753_B0_KST_L           0x21    /*Keystone correction start point*/
#define         REG_C753_B0_KST_H           0x22    /*Keystone correction start point*/
#define         REG_C753_B0_KDST_L          0x23    /*Keystone correction start point difference*/
#define         REG_C753_B0_KDST_H          0x24    /*Keystone correction start point difference*/
#define         REG_C753_B0_KDSCL_L         0x25    /*Keystone correction factor difference*/
#define         REG_C753_B0_KDSCL_H         0x26    /*Keystone correction factor difference*/
#define         REG_C753_B0_KGAIN           0x27    /*Keystone correction gang gain adjustment*/
#define         REG_C753_B0_KVCOEFF         0x28    /*Keystone correction interpolation coefficient select*/
#define         REG_C753_B0_KLUT_0          0x29    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_1          0x2A    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_2          0x2B    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_3          0x2C    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_4          0x2D    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_5          0x2E    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_6          0x2F    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_7          0x30    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_8          0x31    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_9          0x32    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_10         0x33    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_11         0x34    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_12         0x35    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_13         0x36    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_14         0x37    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_KLUT_15         0x38    /*Keystone correction interpolation coefficient lookup table*/
#define         REG_C753_B0_OVLYCTL         0x39    /*Overlay control*/
#define         REG_C753_B0_GAIN3           0x3A    /*2-screen blending β coefficient*/
#define         REG_C753_B0_GAIN4           0x3B    /*2-screen blending α coefficient*/
#define         REG_C753_B0_OSDMODE         0x3C    /*OSD mode*/
#define         REG_C753_B0_OSDCT           0x3D    /*OSD control*/
#define         REG_C753_B0_BOTRANS         0x3E    /*OSD penetration color*/
#define         REG_C753_B0_BOWIHN          0x3F    /*OSD write-inhibit color*/
#define         REG_C753_B0_OSDFILL         0x40    /*OSD fill color*/
#define         REG_C753_B0_BLINKTIME       0x41    /*Blinking time*/
#define         REG_C753_B0_BLINKCYCL       0x42    /*Blink cycle*/
#define         REG_C753_B0_OSDACTHST_L     0x43    /*OSDACT horizontal direction start point*/
#define         REG_C753_B0_OSDACTHST_H     0x44    /*OSDACT horizontal direction start point*/
#define         REG_C753_B0_OSDACTHW_L      0x45    /*OSDACT horizontal direction width*/
#define         REG_C753_B0_OSDACTHW_H      0x46    /*OSDACT horizontal direction width*/
#define         REG_C753_B0_OSDACTVST_L     0x47    /*OSDACT vertical direction start point*/
#define         REG_C753_B0_OSDACTVST_H     0x48    /*OSDACT vertical direction start point*/
#define         REG_C753_B0_OSDACTVW_L      0x49    /*OSDACT vertical direction width*/
#define         REG_C753_B0_OSDACTVW_H      0x4A    /*OSDACT vertical direction width*/
#define         REG_C753_B0_OSDSAD_0        0x4B    /*OSD start address*/
#define         REG_C753_B0_OSDSAD_1        0x4C    /*OSD start address*/
#define         REG_C753_B0_OSDSAD_2        0x4D    /*OSD start address*/
#define         REG_C753_B0_OSDSAD_3        0x4E    /*OSD start address*/
#define         REG_C753_B0_OSDMWI          0x4F    /*OSD memory linefeed width*/
#define         REG_C753_B0_CBUFHST         0x50    /*Character buffer horizontal direction start point*/
#define         REG_C753_B0_CBUFHW          0x51    /*Character buffer horizontal direction width*/
#define         REG_C753_B0_CBUFVST         0x52    /*Character buffer vertical direction start point*/
#define         REG_C753_B0_CBUFVW          0x53    /*Character buffer vertical direction width*/
#define         REG_C753_B0_BBACTHW_L       0x54    /*BitBLT horizontal direction width*/
#define         REG_C753_B0_BBACTHW_H       0x55    /*BitBLT horizontal direction width*/
#define         REG_C753_B0_BBACTVW_L       0x56    /*BitBLT vertical direction width*/
#define         REG_C753_B0_BBACTVW_H       0x57    /*BitBLT vertical direction width*/
#define         REG_C753_B0_CPURAD_0        0x58    /*CPU read address*/
#define         REG_C753_B0_CPURAD_1        0x59    /*CPU read address*/
#define         REG_C753_B0_CPURAD_2        0x5A    /*CPU read address*/
#define         REG_C753_B0_CPURAD_3        0x5B    /*CPU read address*/
#define         REG_C753_B0_CPUWAD_0        0x5C    /*CPU write address*/
#define         REG_C753_B0_CPUWAD_1        0x5D    /*CPU write address*/
#define         REG_C753_B0_CPUWAD_2        0x5E    /*CPU write address*/
#define         REG_C753_B0_CPUWAD_3        0x5F    /*CPU write address*/
#define         REG_C753_B0_CPUDT           0x60    /*CPU data*/
#define         REG_C753_B0_CBUFAD_L        0x61    /*Character buffer address*/
#define         REG_C753_B0_CBUFAD_H        0x62    /*Character buffer address*/
#define         REG_C753_B0_CBUFDT          0x63    /*Character buffer data*/
#define         REG_C753_B0_PLTAD           0x64    /*Palette address*/
#define         REG_C753_B0_PLTDT           0x65    /*Palette data*/
#define         REG_C753_B0_BOSTAT          0x66    /*Bitmap OSD status*/
#define         REG_C753_B0_OSDGAINR        0x67    /*OSD gain compensation (RED)*/
#define         REG_C753_B0_OSDGAING        0x68    /*OSD gain compensation (GREEN)*/
#define         REG_C753_B0_OSDGAINB        0x69    /*OSD gain compensation (BLUE)*/
#define         REG_C753_B0_OSDBIASR        0x6A    /*OSD bias compensation (RED)*/
#define         REG_C753_B0_OSDBIASG        0x6B    /*OSD bias compensation (GREEN)*/
#define         REG_C753_B0_OSDBIASB        0x6C    /*OSD bias compensation (BLUE)*/
#define         REG_C753_B0_BOROT           0x6D    /*Bitmap QSD 90-degree rotation*/
#define         REG_C753_B0_BBWMWI          0x6E    /*BitBLT write linefeed width*/
#define         REG_C753_B0_BBRMWI          0x6F    /*BitBLT read linefeed width*/
#define         REG_C753_B0_BOACCT          0x70    /*Bitmap OSD access control*/
#define         REG_C753_B0_MPROTECT_L      0x71    /*Memory protect*/
#define         REG_C753_B0_MPROTECT_H      0x72    /*Memory protect*/
#define         REG_C753_B0_BBVDLY          0x73    /*BitBLT trigger VS delay*/
#define         REG_C753_B0_INTEN_L         0x77    /*Interrupt enable*/
#define         REG_C753_B0_INTEN_H         0x78    /*Interrupt enable*/
#define         REG_C753_B0_INTRST_L        0x79    /*Interrupt reset*/
#define         REG_C753_B0_INTRST_H        0x7A    /*Interrupt reset*/
#define         REG_C753_B0_TESTDT          0x7D    /*TESTDT*/
#define         REG_C753_B0_TESTAD          0x7E    /*TESTAD*/
#define         REG_C753_B0_TESTG           0x7F    /*Test G*/
 /*Bank 1 register*/
#define         REG_C753_B1_OAOI0HST_L      0x08    /*Output port OAOI0 horizontal direction start point*/
#define         REG_C753_B1_OAOI0HST_H      0x09    /*Output port OAOI0 horizontal direction start point*/
#define         REG_C753_B1_OAOI0HEND_L     0x0A    /*Output port OAOI0 horizontal direction end point*/
#define         REG_C753_B1_OAOI0HEND_H     0x0B    /*Output port OAOI0 horizontal direction end point*/
#define         REG_C753_B1_OAOI0VST_L      0x0C    /*Output port OAOI0 vertical direction start point*/
#define         REG_C753_B1_OAOI0VST_H      0x0D    /*Output port OAOI0 vertical direction start point*/
#define         REG_C753_B1_OAOI0VEND_L     0x0E    /*Output port OAOI0 vertical direction end point*/
#define         REG_C753_B1_OAOI0VEND_H     0x0F    /*Output port OAOI0 vertical direction end point*/
#define         REG_C753_B1_OAOI1HST_L      0x10    /*Output port OAOI1 horizontal direction start point*/
#define         REG_C753_B1_OAOI1HST_H      0x11    /*Output port OAOI1 horizontal direction start point*/
#define         REG_C753_B1_OAOI1HEND_L     0x12    /*Output port OAOI1 horizontal direction end point*/
#define         REG_C753_B1_OAOI1HEND_H     0x13    /*Output port OAOI1 horizontal direction end point*/
#define         REG_C753_B1_OAOI1VST_L      0x14    /*Output port OAOI1 vertical direction start point*/
#define         REG_C753_B1_OAOI1VST_H      0x15    /*Output port OAOI1 vertical direction start point*/
#define         REG_C753_B1_OAOI1VEND_L     0x16    /*Output port OAOI1 vertical direction end point*/
#define         REG_C753_B1_OAOI1VEND_H     0x17    /*Output port OAOI1 vertical direction end point*/
#define         REG_C753_B1_OAOI2HST_L      0x18    /*Output port OAOI2 horizontal direction start point*/
#define         REG_C753_B1_OAOI2HST_H      0x19    /*Output port OAOI2 horizontal direction start point*/
#define         REG_C753_B1_OAOI2HEND_L     0x1A    /*Output port OAOI2 horizontal direction end point*/
#define         REG_C753_B1_OAOI2HEND_H     0x1B    /*Output port OAOI2 horizontal direction end point*/
#define         REG_C753_B1_OAOI2VST_L      0x1C    /*Output port OAOI2 vertical direction start point*/
#define         REG_C753_B1_OAOI2VST_H      0x1D    /*Output port OAOI2 vertical direction start point*/
#define         REG_C753_B1_OAOI2VEND_L     0x1E    /*Output port OAOI2 vertical direction end point*/
#define         REG_C753_B1_OAOI2VEND_H     0x1F    /*Output port OAOI2 vertical direction end point*/
#define         REG_C753_B1_OAOI3HST_L      0x20    /*Output port OAOI3 horizontal direction start point*/
#define         REG_C753_B1_OAOI3HST_H      0x21    /*Output port OAOI3 horizontal direction start point*/
#define         REG_C753_B1_OAOI3HEND_L     0x22    /*Output port OAOI3 horizontal direction end point*/
#define         REG_C753_B1_OAOI3HEND_H     0x23    /*Output port OAOI3 horizontal direction end point*/
#define         REG_C753_B1_OAOI3VST_L      0x24    /*Output port OAOI3 vertical direction start point*/
#define         REG_C753_B1_OAOI3VST_H      0x25    /*Output port OAOI3 vertical direction start point*/
#define         REG_C753_B1_OAOI3VEND_L     0x26    /*Output port OAOI3 vertical direction end point*/
#define         REG_C753_B1_OAOI3VEND_H     0x27    /*Output port OAOI3 vertical direction end point*/
#define         REG_C753_B1_BKGDCT          0x28    /*Background control*/
#define         REG_C753_B1_OBKGD0_R        0x29    /*Output background 0*/
#define         REG_C753_B1_OBKGD0_G        0x2A    /*Output background 0*/
#define         REG_C753_B1_OBKGD0_B        0x2B    /*Output background 0*/
#define         REG_C753_B1_OBKGD1_R        0x2C    /*Output background 1*/
#define         REG_C753_B1_OBKGD1_G        0x2D    /*Output background 1*/
#define         REG_C753_B1_OBKGD1_B        0x2E    /*Output background 1*/
#define         REG_C753_B1_BGCT            0x2F    /*Bias gain control*/
#define         REG_C753_B1_GAIN2R          0x30    /*Second gain compensation (RED)*/
#define         REG_C753_B1_GAIN2G          0x31    /*Second gain compensation (GREEN)*/
#define         REG_C753_B1_GAIN2B          0x32    /*Second gain compensation (BLUE)*/
#define         REG_C753_B1_BIAS2R_L        0x33    /*Second bias compensation (RED)*/
#define         REG_C753_B1_BIAS2R_H        0x34    /*Second bias compensation (RED)*/
#define         REG_C753_B1_BIAS2G_L        0x35    /*Second bias compensation (GREEN)*/
#define         REG_C753_B1_BIAS2G_H        0x36    /*Second bias compensation (GREEN)*/
#define         REG_C753_B1_BIAS2B_L        0x37    /*Second bias compensation (BLUE)*/
#define         REG_C753_B1_BIAS2B_H        0x38    /*Second bias compensation (BLUE)*/
#define         REG_C753_B1_GMCT_L          0x39    /*Gamma table control*/
#define         REG_C753_B1_GMCT_H          0x3A    /*Gamma table control*/
#define         REG_C753_B1_GMBNKSEL        0x3B    /*Gamma table bank select*/
#define         REG_C753_B1_GMAD            0x3C    /*Gamma table bank address*/
#define         REG_C753_B1_GMDT            0x3D    /*Gamma table bank data*/
#define         REG_C753_B1_ERDFCT          0x3E    /*Error diffusion control*/
#define         REG_C753_B1_OYUVCT          0x40    /*Output port YUV gain bias control*/
#define         REG_C753_B1_OPBWIDTH        0x41    /*Output pattern bar width*/
#define         REG_C753_B1_OPBRATE         0x42    /*Output pattern speed*/
#define         REG_C753_B1_OPBPERIOD_L     0x43    /*Output pattern cycle*/
#define         REG_C753_B1_OPBPERIOD_H     0x44    /*Output pattern cycle*/
#define         REG_C753_B1_XPGCTRL         0x45    /*Pattern generator control*/
#define         REG_C753_B1_XRAMPCNT        0x46    /*RAMP counter step setting*/
#define         REG_C753_B1_XHLIMIT_L       0x47    /*Horizontal RAMP counter limit value*/
#define         REG_C753_B1_XHLIMIT_H       0x48    /*Horizontal RAMP counter limit value*/
#define         REG_C753_B1_XVLIMIT_L       0x49    /*Vertical RAMP counter limit value*/
#define         REG_C753_B1_XVLIMIT_H       0x4A    /*Vertical RAMP counter limit value*/
#define         REG_C753_B1_XCLBWIDTH       0x4B    /*Color bar width setting*/
#define         REG_C753_B1_LVDSCT          0x50    /*LVDS control*/
#define         REG_C753_B1_LVDSCT2         0x51    /*LVDS control 2*/
#define         REG_C753_B1_TTLPOSYCT       0x52    /*TTL image output timing signal control*/
#define         REG_C753_B1_OFPWMA_L        0x53    /*PWM control 0*/
#define         REG_C753_B1_OFPWMA_H        0x54    /*PWM control 0*/
#define         REG_C753_B1_OFPWMB_L        0x55    /*PWM control 1*/
#define         REG_C753_B1_OFPWMB_H        0x56    /*PWM control 1*/
#define         REG_C753_B1_OFPWMC_L        0x57    /*PWM control 2*/
#define         REG_C753_B1_OFPWMC_H        0x58    /*PWM control 2*/
#define         REG_C753_B1_OFPWMD_L        0x59    /*PWM control 3*/
#define         REG_C753_B1_OFPWMD_H        0x5A    /*PWM control 3*/
#define         REG_C753_B1_IPPLLCT         0x68    /*IPCLK PLL control*/
#define         REG_C753_B1_IPREFDIV        0x69    /*IPCLK reference dividing*/
#define         REG_C753_B1_IPFBDIV         0x6A    /*IPCLK feedback dividing*/
#define         REG_C753_B1_POPLLCT         0x6B    /*POCLK PLL control*/
#define         REG_C753_B1_POREFDIV        0x6C    /*POCLK reference dividing*/
#define         REG_C753_B1_POFBDIV         0x6D    /*POCLK feedback dividing*/
#define         REG_C753_B1_DLLCT0          0x6E    /*DLL control 0*/
#define         REG_C753_B1_DLLCT1          0x6F    /*DLL control 1*/
#define         REG_C753_B1_DLLCT2          0x70    /*DLL control 2*/
#define         REG_C753_B1_DLLCT3          0x71    /*DLL control 3*/
#define         REG_C753_B1_DLLCT4          0x72    /*DLL control 4*/
#define         REG_C753_B1_DLLCT5          0x73    /*DLL control 5*/
#define         REG_C753_B1_DLLCT6          0x74    /*DLL control 6*/
#define         REG_C753_B1_DLLCT7          0x75    /*DLL control 7*/
#define         REG_C753_B1_DLLCT8          0x76    /*DLL control 8*/
 /*Bank 2 register*/
#define         REG_C753_B2_O1ACTHST_L      0x08    /*Output channel 1 output port ACT horizontal direction start point*/
#define         REG_C753_B2_O1ACTHST_H      0x09    /*Output channel 1 output port ACT horizontal direction start point*/
#define         REG_C753_B2_O1ACTHW_L       0x0A    /*Output channel 1 output port ACT horizontal direction width*/
#define         REG_C753_B2_O1ACTHW_H       0x0B    /*Output channel 1 output port ACT horizontal direction width*/
#define         REG_C753_B2_O1ACTVST_L      0x0C    /*Output channel 1 output port ACT vertical direction start point*/
#define         REG_C753_B2_O1ACTVST_H      0x0D    /*Output channel 1 output port ACT vertical direction start point*/
#define         REG_C753_B2_O1ACTVW_L       0x0E    /*Output channel 1 output port ACT vertical direction width*/
#define         REG_C753_B2_O1ACTVW_H       0x0F    /*Output channel 1 output port ACT vertical direction width*/
#define         REG_C753_B2_HEGCTCH1        0x10    /*Output channel 1 post-enlargement-circuit horizontal edge emphasis control*/
#define         REG_C753_B2_HEGCRLLCH1      0x11    /*Output channel 1 post-enlargement-circuit horizontal edge emphasis coring low level*/
#define         REG_C753_B2_HEGCRULCH1      0x12    /*Output channel 1 post-enlargement-circuit horizontal edge emphasis coring high level*/
#define         REG_C753_B2_HEGCOEFCH1_0    0x13    /*Output channel 1 post-enlargement-circuit horizontal edge emphasis coefficient 0-3*/
#define         REG_C753_B2_HEGCOEFCH1_1    0x14    /*Output channel 1 post-enlargement-circuit horizontal edge emphasis coefficient 0-3*/
#define         REG_C753_B2_HEGCOEFCH1_2    0x15    /*Output channel 1 post-enlargement-circuit horizontal edge emphasis coefficient 0-3*/
#define         REG_C753_B2_HEGCOEFCH1_3    0x16    /*Output channel 1 post-enlargement-circuit horizontal edge emphasis coefficient 0-3*/
#define         REG_C753_B2_HEGACTCH1       0x17    /*Output channel 1 post-enlargement-circuit horizontal edge area select*/
#define         REG_C753_B2_VEGCTCH1        0x18    /*Output channel 1 post-enlargement-circuit vertical edge emphasis control*/
#define         REG_C753_B2_VEGCRLLCH1      0x19    /*Output channel 1 post-enlargement-circuit vertical edge emphasis coring L*/
#define         REG_C753_B2_VEGCRULCH1      0x1A    /*Output channel 1 post-enlargement-circuit vertical edge emphasis coring H*/
#define         REG_C753_B2_VEGCOEFCH1_0    0x1B    /*Output channel 1 post-enlargement-circuit vertical edge emphasis coefficient 0-3*/
#define         REG_C753_B2_VEGCOEFCH1_1    0x1C    /*Output channel 1 post-enlargement-circuit vertical edge emphasis coefficient 0-3*/
#define         REG_C753_B2_VEGCOEFCH1_2    0x1D    /*Output channel 1 post-enlargement-circuit vertical edge emphasis coefficient 0-3*/
#define         REG_C753_B2_VEGCOEFCH1_3    0x1E    /*Output channel 1 post-enlargement-circuit vertical edge emphasis coefficient 0-3*/
#define         REG_C753_B2_VEGACTCH1       0x1F    /*Output channel 1 post-enlargement-circuit vertical edge area select*/
#define         REG_C753_B2_VEGCT2CH1       0x20    /*Output channel 1 post-enlargement-circuit vertical edge emphasis control 2*/
#define         REG_C753_B2_GAINRCH1_L      0x21    /*Output channel 1 gain compensation (RED)*/
#define         REG_C753_B2_GAINRCH1_H      0x22    /*Output channel 1 gain compensation (RED)*/
#define         REG_C753_B2_GAINGCH1_L      0x23    /*Output channel 1 gain compensation (GREEN)*/
#define         REG_C753_B2_GAINGCH1_H      0x24    /*Output channel 1 gain compensation (GREEN)*/
#define         REG_C753_B2_GAINBCH1_L      0x25    /*Output channel 1 gain compensation (BLUE)*/
#define         REG_C753_B2_GAINBCH1_H      0x26    /*Output channel 1 gain compensation (BLUE)*/
#define         REG_C753_B2_BIASRCH1_L      0x27    /*Output channel 1 bias compensation (RED)*/
#define         REG_C753_B2_BIASRCH1_H      0x28    /*Output channel 1 bias compensation (RED)*/
#define         REG_C753_B2_BIASGCH1_L      0x29    /*Output channel 1 bias compensation (GREEN)*/
#define         REG_C753_B2_BIASGCH1_H      0x2A    /*Output channel 1 bias compensation (GREEN)*/
#define         REG_C753_B2_BIASBCH1_L      0x2B    /*Output channel 1 bias compensation (BLUE)*/
#define         REG_C753_B2_BIASBCH1_H      0x2C    /*Output channel 1 bias compensation (BLUE)*/
#define         REG_C753_B2_O1FILL_R        0x2D    /*Output channel 1 output fill*/
#define         REG_C753_B2_O1FILL_G        0x2E    /*Output channel 1 output fill*/
#define         REG_C753_B2_O1FILL_B        0x2F    /*Output channel 1 output fill*/
#define         REG_C753_B2_O1IMGCT         0x30    /*Output channel 1 output image control*/
#define         REG_C753_B2_ACTCTCH1        0x31    /*Output channel 1 active area select*/
#define         REG_C753_B2_HISTGRAMCTCH1   0x32    /*Output channel 1 histogram control*/
#define         REG_C753_B2_FCGCTCH1        0x33    /*Output channel 1 full color gamma control*/
#define         REG_C753_B2_FCGADCH1        0x34    /*Output channel 1 full color gamma address*/
#define         REG_C753_B2_FCGDTCH1        0x35    /*Output channel 1 full color gamma data*/
#define         REG_C753_B2_YCMPCH1_0       0x36    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_YCMPCH1_1       0x37    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_YCMPCH1_2       0x38    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_YCMPCH1_3       0x39    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_YCMPCH1_4       0x3A    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_YCMPCH1_5       0x3B    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_YCMPCH1_6       0x3C    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_YCMPCH1_7       0x3D    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_YCMPCH1_8       0x3E    /*Output channel 1 full color gamma luminance compensation*/
#define         REG_C753_B2_ZHEGCTRLCH1     0x3F    /*Output channel 1 horizontal edge emphasis control*/
#define         REG_C753_B2_ZHEGCRLLCH1     0x40    /*Output channel 1 horizontal edge emphasis coring L*/
#define         REG_C753_B2_ZHEGCRULCH1     0x41    /*Output channel 1 horizontal edge emphasis coring H*/
#define         REG_C753_B2_ZHEGHGAINOCH1   0x42    /*Output channel 1 horizontal edge emphasis overshoot filter coefficient*/
#define         REG_C753_B2_ZHEGHGAINUCH1   0x43    /*Output channel 1 horizontal edge emphasis undershoot filter coefficient*/
#define         REG_C753_B2_HZOOMCTCH1      0x48    /*Output channel 1 horizontal enlargement control*/
#define         REG_C753_B2_HZINITCH1       0x49    /*Output channel 1 horizontal enlargement initial value*/
#define         REG_C753_B2_HZSCLCH1_L      0x4A    /*Output channel 1 horizontal zoom scale*/
#define         REG_C753_B2_HZSCLCH1_H      0x4B    /*Output channel 1 horizontal zoom scale*/
#define         REG_C753_B2_VZOOMCTCH1      0x4C    /*Output channel 1 vertical enlargement control*/
#define         REG_C753_B2_VZINITCH1       0x4D    /*Output channel 1 vertical enlargement initial value*/
#define         REG_C753_B2_VZSCLCH1_L      0x4E    /*Output channel 1 vertical zoom scale*/
#define         REG_C753_B2_VZSCLCH1_H      0x4F    /*Output channel 1 vertical zoom scale*/
#define         REG_C753_B2_HZLUTCH1_0      0x50    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_1      0x51    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_2      0x52    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_3      0x53    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_4      0x54    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_5      0x55    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_6      0x56    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_7      0x57    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_8      0x58    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_9      0x59    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_10     0x5A    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_11     0x5B    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_12     0x5C    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_13     0x5D    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_14     0x5E    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_15     0x5F    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_16     0x60    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_17     0x61    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_18     0x62    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_19     0x63    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_20     0x64    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_21     0x65    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_22     0x66    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_HZLUTCH1_23     0x67    /*Output channel 1 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_0      0x68    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_1      0x69    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_2      0x6A    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_3      0x6B    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_4      0x6C    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_5      0x6D    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_6      0x6E    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_7      0x6F    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_8      0x70    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_9      0x71    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_10     0x72    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_11     0x73    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_12     0x74    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_13     0x75    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_14     0x76    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_15     0x77    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_16     0x78    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_17     0x79    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_18     0x7A    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_19     0x7B    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_20     0x7C    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_21     0x7D    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_22     0x7E    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B2_VZLUTCH1_23     0x7F    /*Output channel 1 vertical enlargement interpolation coefficient lookup table*/
 /*Bank 4 register*/
#define         REG_C753_B4_O2ACTHST_L      0x08    /*Output channel 2 output port ACT horizontal direction start point*/
#define         REG_C753_B4_O2ACTHST_H      0x09    /*Output channel 2 output port ACT horizontal direction start point*/
#define         REG_C753_B4_O2ACTHW_L       0x0A    /*Output channel 2 output port ACT horizontal direction width*/
#define         REG_C753_B4_O2ACTHW_H       0x0B    /*Output channel 2 output port ACT horizontal direction width*/
#define         REG_C753_B4_O2ACTVST_L      0x0C    /*Output channel 2 output port ACT vertical direction start point*/
#define         REG_C753_B4_O2ACTVST_H      0x0D    /*Output channel 2 output port ACT vertical direction start point*/
#define         REG_C753_B4_O2ACTVW_L       0x0E    /*Output channel 2 output port ACT vertical direction width*/
#define         REG_C753_B4_O2ACTVW_H       0x0F    /*Output channel 2 output port ACT vertical direction width*/
#define         REG_C753_B4_HEGCTCH2        0x10    /*Output channel 2 post-enlargement-circuit horizontal edge emphasis control*/
#define         REG_C753_B4_HEGCRLLCH2      0x11    /*Output channel 2 post-enlargement-circuit horizontal edge emphasis coring low level*/
#define         REG_C753_B4_HEGCRULCH2      0x12    /*Output channel 2 post-enlargement-circuit horizontal edge emphasis coring high level*/
#define         REG_C753_B4_HEGCOEFCH2_0    0x13    /*Output channel 2 post-enlargement-circuit horizontal edge emphasis coefficient 0-3*/
#define         REG_C753_B4_HEGCOEFCH2_1    0x14    /*Output channel 2 post-enlargement-circuit horizontal edge emphasis coefficient 0-3*/
#define         REG_C753_B4_HEGCOEFCH2_2    0x15    /*Output channel 2 post-enlargement-circuit horizontal edge emphasis coefficient 0-3*/
#define         REG_C753_B4_HEGCOEFCH2_3    0x16    /*Output channel 2 post-enlargement-circuit horizontal edge emphasis coefficient 0-3*/
#define         REG_C753_B4_HEGACTCH2       0x17    /*Output channel 2 post-enlargement-circuit horizontal edge area select*/
#define         REG_C753_B4_VEGCTCH2        0x18    /*Output channel 2 post-enlargement-circuit vertical edge emphasis control*/
#define         REG_C753_B4_VEGCRLLCH2      0x19    /*Output channel 2 post-enlargement-circuit vertical edge emphasis coring L*/
#define         REG_C753_B4_VEGCRULCH2      0x1A    /*Output channel 2 post-enlargement-circuit vertical edge emphasis coring H*/
#define         REG_C753_B4_VEGCOEFCH2_0    0x1B    /*Output channel 2 post-enlargement-circuit vertical edge emphasis coefficient 0-3*/
#define         REG_C753_B4_VEGCOEFCH2_1    0x1C    /*Output channel 2 post-enlargement-circuit vertical edge emphasis coefficient 0-3*/
#define         REG_C753_B4_VEGCOEFCH2_2    0x1D    /*Output channel 2 post-enlargement-circuit vertical edge emphasis coefficient 0-3*/
#define         REG_C753_B4_VEGCOEFCH2_3    0x1E    /*Output channel 2 post-enlargement-circuit vertical edge emphasis coefficient 0-3*/
#define         REG_C753_B4_VEGACTCH2       0x1F    /*Output channel 2 post-enlargement-circuit vertical edge area select*/
#define         REG_C753_B4_VEGCT2CH2       0x20    /*Output channel 2 post-enlargement-circuit vertical edge emphasis control 2*/
#define         REG_C753_B4_GAINRCH2_L      0x21    /*Output channel 2 gain compensation (RED)*/
#define         REG_C753_B4_GAINRCH2_H      0x22    /*Output channel 2 gain compensation (RED)*/
#define         REG_C753_B4_GAINGCH2_L      0x23    /*Output channel 2 gain compensation (GREEN)*/
#define         REG_C753_B4_GAINGCH2_H      0x24    /*Output channel 2 gain compensation (GREEN)*/
#define         REG_C753_B4_GAINBCH2_L      0x25    /*Output channel 2 gain compensation (BLUE)*/
#define         REG_C753_B4_GAINBCH2_H      0x26    /*Output channel 2 gain compensation (BLUE)*/
#define         REG_C753_B4_BIASRCH2_L      0x27    /*Output channel 2 bias compensation (RED)*/
#define         REG_C753_B4_BIASRCH2_H      0x28    /*Output channel 2 bias compensation (RED)*/
#define         REG_C753_B4_BIASGCH2_L      0x29    /*Output channel 2 bias compensation (GREEN)*/
#define         REG_C753_B4_BIASGCH2_H      0x2A    /*Output channel 2 bias compensation (GREEN)*/
#define         REG_C753_B4_BIASBCH2_L      0x2B    /*Output channel 2 bias compensation (BLUE)*/
#define         REG_C753_B4_BIASBCH2_H      0x2C    /*Output channel 2 bias compensation (BLUE)*/
#define         REG_C753_B4_O2FILL_R        0x2D    /*Output channel 2 output fill*/
#define         REG_C753_B4_O2FILL_G        0x2E    /*Output channel 2 output fill*/
#define         REG_C753_B4_O2FILL_B        0x2F    /*Output channel 2 output fill*/
#define         REG_C753_B4_O2IMGCT         0x30    /*Output channel 2 output image control*/
#define         REG_C753_B4_ACTCTCH2        0x31    /*Output channel 2 active area select*/
#define         REG_C753_B4_HISTGRAMCTCH2   0x32    /*Output channel 2 histogram control*/
#define         REG_C753_B4_FCGCTCH2        0x33    /*Output channel 2 full color gamma control*/
#define         REG_C753_B4_FCGADCH2        0x34    /*Output channel 2 full color gamma address*/
#define         REG_C753_B4_FCGDTCH2        0x35    /*Output channel 2 full color gamma data*/
#define         REG_C753_B4_YCMPCH2_0       0x36    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_YCMPCH2_1       0x37    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_YCMPCH2_2       0x38    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_YCMPCH2_3       0x39    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_YCMPCH2_4       0x3A    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_YCMPCH2_5       0x3B    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_YCMPCH2_6       0x3C    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_YCMPCH2_7       0x3D    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_YCMPCH2_8       0x3E    /*Output channel 2 full color gamma luminance compensation*/
#define         REG_C753_B4_ZHEGCTRLCH2     0x3F    /*Output channel 2 horizontal edge emphasis control*/
#define         REG_C753_B4_ZHEGCRLLCH2     0x40    /*Output channel 2 horizontal edge emphasis coring L*/
#define         REG_C753_B4_ZHEGCRULCH2     0x41    /*Output channel 2 horizontal edge emphasis coring H*/
#define         REG_C753_B4_ZHEGHGAINOCH2   0x42    /*Output channel 2 horizontal edge emphasis overshoot filter coefficient*/
#define         REG_C753_B4_ZHEGHGAINUCH2   0x43    /*Output channel 2 horizontal edge emphasis undershoot filter coefficient*/
#define         REG_C753_B4_ADPHZCH2        0x46    /*Output channel 2 adaptive horizontal enlargement control*/
#define         REG_C753_B4_ADPVZCH2        0x47    /*Output channel 2 adaptive vertical enlargement control*/
#define         REG_C753_B4_HZOOMCTCH2      0x48    /*Output channel 2 horizontal enlargement control*/
#define         REG_C753_B4_HZINITCH2       0x49    /*Output channel 2 horizontal enlargement initial value*/
#define         REG_C753_B4_HZSCLCH2_L      0x4A    /*Output channel 2 horizontal zoom scale*/
#define         REG_C753_B4_HZSCLCH2_H      0x4B    /*Output channel 2 horizontal zoom scale*/
#define         REG_C753_B4_VZOOMCTCH2      0x4C    /*Output channel 2 vertical enlargement control*/
#define         REG_C753_B4_VZINITCH2       0x4D    /*Output channel 2 vertical enlargement initial value*/
#define         REG_C753_B4_VZSCLCH2_L      0x4E    /*Output channel 2 vertical zoom scale*/
#define         REG_C753_B4_VZSCLCH2_H      0x4F    /*Output channel 2 vertical zoom scale*/
#define         REG_C753_B4_HZLUTCH2_0      0x50    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_1      0x51    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_2      0x52    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_3      0x53    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_4      0x54    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_5      0x55    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_6      0x56    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_7      0x57    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_8      0x58    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_9      0x59    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_10     0x5A    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_11     0x5B    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_12     0x5C    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_13     0x5D    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_14     0x5E    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_15     0x5F    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_16     0x60    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_17     0x61    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_18     0x62    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_19     0x63    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_20     0x64    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_21     0x65    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_22     0x66    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_HZLUTCH2_23     0x67    /*Output channel 2 horizontal enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_0      0x68    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_1      0x69    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_2      0x6A    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_3      0x6B    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_4      0x6C    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_5      0x6D    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_6      0x6E    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_7      0x6F    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_8      0x70    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_9      0x71    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_10     0x72    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_11     0x73    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_12     0x74    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_13     0x75    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_14     0x76    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_15     0x77    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_16     0x78    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_17     0x79    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_18     0x7A    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_19     0x7B    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_20     0x7C    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_21     0x7D    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_22     0x7E    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
#define         REG_C753_B4_VZLUTCH2_23     0x7F    /*Output channel 2 vertical enlargement interpolation coefficient lookup table*/
 /*Bank 6 register*/
#define         REG_C753_B6_I1IMGCT         0x08    /*Input channel 1 input format control*/
#define         REG_C753_B6_I1SYCT          0x09    /*Input channel 1 input port sync signal control*/
#define         REG_C753_B6_HVPHMSRCH1      0x0A    /*Input channel 1 HV phase difference measurement*/
#define         REG_C753_B6_I1VLNDLY_L      0x0B    /*Input channel 1 input V sync signal line delay*/
#define         REG_C753_B6_I1VLNDLY_H      0x0C    /*Input channel 1 input V sync signal line delay*/
#define         REG_C753_B6_I1VSKDLY_L      0x0D    /*Input channel 1 input V sync signal CLK delay*/
#define         REG_C753_B6_I1VSKDLY_H      0x0E    /*Input channel 1 input V sync signal CLK delay*/
#define         REG_C753_B6_I1HSKDLY_L      0x0F    /*Input channel 1 input H sync signal CLK delay*/
#define         REG_C753_B6_I1HSKDLY_H      0x10    /*Input channel 1 input H sync signal CLK delay*/
#define         REG_C753_B6_AUTOFLDCH1      0x11    /*Input channel 1 field recognition control*/
#define         REG_C753_B6_DIFCTCH1        0x12    /*Input channel 1 digital interface control*/
#define         REG_C753_B6_DHCYCLCH1_L     0x13    /*Input channel 1 digital interface H sync signal cycle*/
#define         REG_C753_B6_DHCYCLCH1_H     0x14    /*Input channel 1 digital interface H sync signal cycle*/
#define         REG_C753_B6_DVDLYCH1_L      0x15    /*Input channel 1 digital interface V sync signal delay*/
#define         REG_C753_B6_DVDLYCH1_H      0x16    /*Input channel 1 digital interface V sync signal delay*/
#define         REG_C753_B6_I1CPNCT         0x17    /*Input channel 1 component input control*/
#define         REG_C753_B6_I1ACTHST_L      0x18    /*Input channel 1 input port ACT H direction start point*/
#define         REG_C753_B6_I1ACTHST_H      0x19    /*Input channel 1 input port ACT H direction start point*/
#define         REG_C753_B6_I1ACTHW_L       0x1A    /*Input channel 1 input port ACT H direction width*/
#define         REG_C753_B6_I1ACTHW_H       0x1B    /*Input channel 1 input port ACT H direction width*/
#define         REG_C753_B6_I1ACTVST_L      0x1C    /*Input channel 1 input port ACT V direction start point*/
#define         REG_C753_B6_I1ACTVST_H      0x1D    /*Input channel 1 input port ACT V direction start point*/
#define         REG_C753_B6_I1ACTVW_L       0x1E    /*Input channel 1 input port ACT V direction width*/
#define         REG_C753_B6_I1ACTVW_H       0x1F    /*Input channel 1 input port ACT V direction width*/
#define         REG_C753_B6_I1SWP           0x20    /*Input channel 1 input signal swap*/
#define         REG_C753_B6_I1COLORCT       0x21    /*Input channel 1 input image control*/
#define         REG_C753_B6_I1FILL_R        0x22    /*Input channel 1 input fill*/
#define         REG_C753_B6_I1FILL_G        0x23    /*Input channel 1 input fill*/
#define         REG_C753_B6_I1FILL_B        0x24    /*Input channel 1 input fill*/
#define         REG_C753_B6_I1GAINY         0x25    /*Input channel 1 gain compensation (Y)*/
#define         REG_C753_B6_I1GAINU         0x26    /*Input channel 1 gain compensation (U)*/
#define         REG_C753_B6_I1GAINV         0x27    /*Input channel 1 gain compensation (V)*/
#define         REG_C753_B6_I1BIASY_L       0x28    /*Input channel 1 bias compensation (Y)*/
#define         REG_C753_B6_I1BIASY_H       0x29    /*Input channel 1 bias compensation (Y)*/
#define         REG_C753_B6_I1BIASU_L       0x2A    /*Input channel 1 bias compensation (U)*/
#define         REG_C753_B6_I1BIASU_H       0x2B    /*Input channel 1 bias compensation (U)*/
#define         REG_C753_B6_I1BIASV_L       0x2C    /*Input channel 1 bias compensation (V)*/
#define         REG_C753_B6_I1BIASV_H       0x2D    /*Input channel 1 bias compensation (V)*/
#define         REG_C753_B6_UVLPCOEFCH1_0   0x2E    /*Input channel 1 UV low pass filter coefficient*/
#define         REG_C753_B6_UVLPCOEFCH1_1   0x2F    /*Input channel 1 UV low pass filter coefficient*/
#define         REG_C753_B6_UVLPCOEFCH1_2   0x30    /*Input channel 1 UV low pass filter coefficient*/
#define         REG_C753_B6_XCOEFRYCH1_L    0x31    /*Input channel 1 RGBYUV color conversion coefficient (RY)*/
#define         REG_C753_B6_XCOEFRYCH1_H    0x32    /*Input channel 1 RGBYUV color conversion coefficient (RY)*/
#define         REG_C753_B6_XCOEFGYCH1_L    0x33    /*Input channel 1 RGBYUV color conversion coefficient (GY)*/
#define         REG_C753_B6_XCOEFGYCH1_H    0x34    /*Input channel 1 RGBYUV color conversion coefficient (GY)*/
#define         REG_C753_B6_XCOEFBYCH1_L    0x35    /*Input channel 1 RGBYUV color conversion coefficient (BY)*/
#define         REG_C753_B6_XCOEFBYCH1_H    0x36    /*Input channel 1 RGBYUV color conversion coefficient (BY)*/
#define         REG_C753_B6_XCOEFRUCH1_L    0x37    /*Input channel 1 RGBYUV color conversion coefficient (RU)*/
#define         REG_C753_B6_XCOEFRUCH1_H    0x38    /*Input channel 1 RGBYUV color conversion coefficient (RU)*/
#define         REG_C753_B6_XCOEFGUCH1_L    0x39    /*Input channel 1 RGBYUV color conversion coefficient (GU)*/
#define         REG_C753_B6_XCOEFGUCH1_H    0x3A    /*Input channel 1 RGBYUV color conversion coefficient (GU)*/
#define         REG_C753_B6_XCOEFBUCH1_L    0x3B    /*Input channel 1 RGBYUV color conversion coefficient (BU)*/
#define         REG_C753_B6_XCOEFBUCH1_H    0x3C    /*Input channel 1 RGBYUV color conversion coefficient (BU)*/
#define         REG_C753_B6_XCOEFRVCH1_L    0x3D    /*Input channel 1 RGBYUV color conversion coefficient (RV)*/
#define         REG_C753_B6_XCOEFRVCH1_H    0x3E    /*Input channel 1 RGBYUV color conversion coefficient (RV)*/
#define         REG_C753_B6_XCOEFGVCH1_L    0x3F    /*Input channel 1 RGBYUV color conversion coefficient (GV)*/
#define         REG_C753_B6_XCOEFGVCH1_H    0x40    /*Input channel 1 RGBYUV color conversion coefficient (GV)*/
#define         REG_C753_B6_XCOEFBVCH1_L    0x41    /*Input channel 1 RGBYUV color conversion coefficient (BV)*/
#define         REG_C753_B6_XCOEFBVCH1_H    0x42    /*Input channel 1 RGBYUV color conversion coefficient (BV)*/
#define         REG_C753_B6_XIERDFCTCH1     0x43    /*Input channel 1 input error diffusion control*/
#define         REG_C753_B6_SHRNKADJCH1     0x45    /*Input channel 1 shrink compensation control*/
#define         REG_C753_B6_HSHRNKCTCH1     0x46    /*Input channel 1 horizontal shrink control*/
#define         REG_C753_B6_HSINITCH1       0x47    /*Input channel 1 horizontal shrink initial value*/
#define         REG_C753_B6_HSSCLCH1_L      0x48    /*Input channel 1 horizontal shrink scale*/
#define         REG_C753_B6_HSSCLCH1_H      0x49    /*Input channel 1 horizontal shrink scale*/
#define         REG_C753_B6_VSHRNKCTCH1     0x4A    /*Input channel 1 vertical shrink control*/
#define         REG_C753_B6_VSINITCH1       0x4B    /*Input channel 1 vertical shrink initial value*/
#define         REG_C753_B6_VSSCLCH1_L      0x4C    /*Input channel 1 vertical shrink scale*/
#define         REG_C753_B6_VSSCLCH1_H      0x4D    /*Input channel 1 vertical shrink scale*/
#define         REG_C753_B6_I1HSHCMP        0x4E    /*Input channel 1 horizontal shrink compensation*/
#define         REG_C753_B6_I1VSHCMP        0x4F    /*Input channel 1 vertical shrink compensation*/
#define         REG_C753_B6_HSLUTCH1_0      0x50    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_1      0x51    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_2      0x52    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_3      0x53    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_4      0x54    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_5      0x55    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_6      0x56    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_7      0x57    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_8      0x58    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_9      0x59    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_10     0x5A    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_11     0x5B    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_12     0x5C    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_13     0x5D    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_14     0x5E    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_15     0x5F    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_16     0x60    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_17     0x61    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_18     0x62    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_19     0x63    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_20     0x64    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_21     0x65    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_22     0x66    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_HSLUTCH1_23     0x67    /*Input channel 1 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_0      0x68    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_1      0x69    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_2      0x6A    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_3      0x6B    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_4      0x6C    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_5      0x6D    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_6      0x6E    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_7      0x6F    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_8      0x70    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_9      0x71    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_10     0x72    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_11     0x73    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_12     0x74    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_13     0x75    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_14     0x76    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_15     0x77    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_16     0x78    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_17     0x79    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_18     0x7A    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_19     0x7B    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_20     0x7C    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_21     0x7D    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_22     0x7E    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B6_VSLUTCH1_23     0x7F    /*Input channel 1 vertical reduction interpolation coefficient lookup table*/
 /*Bank 7 register*/
#define			REG_C753_B7_PMODECH1 		0x62	/*Input channel 1 input image characteristics measurement control*/
#define			REG_C753_B7_PI1H0_L 		0x63 	/*Input channel 1 measurement horizontal start position coordinate*/
#define			REG_C753_B7_PI1H0_H 		0x64 	/*Input channel 1 measurement horizontal start position coordinate*/
#define			REG_C753_B7_PI1V0_L 		0x65 	/*Input channel 1 measurement vertical start position coordinate*/
#define			REG_C753_B7_PI1V0_H 		0x66 	/*Input channel 1 measurement vertical start position coordinate*/
#define			REG_C753_B7_PI1H1_L 		0x67 	/*Input channel 1 measurement horizontal end position coordinate*/
#define			REG_C753_B7_PI1H1_H 		0x68 	/*Input channel 1 measurement horizontal end position coordinate*/
#define			REG_C753_B7_PI1V1_L 		0x69 	/*Input channel 1 measurement vertical end position coordinate*/
#define			REG_C753_B7_PI1V1_H 		0x6A 	/*Input channel 1 measurement vertical end position coordinate*/
#define			REG_C753_B7_PTHCH1 			0x6B	/*Input channel 1 characteristics measurement threshold*/
 /*Bank 8 register*/
#define         REG_C753_B8_I2IMGCT         0x08    /*Input channel 2 input format control*/
#define         REG_C753_B8_I2SYCT          0x09    /*Input channel 2 input port sync signal control*/
#define         REG_C753_B8_HVPHMSRCH2      0x0A    /*Input channel 2 HV phase difference measurement*/
#define         REG_C753_B8_I2VLNDLY_L      0x0B    /*Input channel 2 input V sync signal line delay*/
#define         REG_C753_B8_I2VLNDLY_H      0x0C    /*Input channel 2 input V sync signal line delay*/
#define         REG_C753_B8_I2VSKDLY_L      0x0D    /*Input channel 2 input V sync signal CLK delay*/
#define         REG_C753_B8_I2VSKDLY_H      0x0E    /*Input channel 2 input V sync signal CLK delay*/
#define         REG_C753_B8_I2HSKDLY_L      0x0F    /*Input channel 2 input H sync signal CLK delay*/
#define         REG_C753_B8_I2HSKDLY_H      0x10    /*Input channel 2 input H sync signal CLK delay*/
#define         REG_C753_B8_AUTOFLDCH2      0x11    /*Input channel 2 field recognition control*/
#define         REG_C753_B8_DIFCTCH2        0x12    /*Input channel 2 digital interface control*/
#define         REG_C753_B8_DHCYCLCH2_L     0x13    /*Input channel 2 digital interface H sync signal period*/
#define         REG_C753_B8_DHCYCLCH2_H     0x14    /*Input channel 2 digital interface H sync signal period*/
#define         REG_C753_B8_DVDLYCH2_L      0x15    /*Input channel 2 digital interface V sync signal delay*/
#define         REG_C753_B8_DVDLYCH2_H      0x16    /*Input channel 2 digital interface V sync signal delay*/
#define         REG_C753_B8_I2CPNCT         0x17    /*Input channel 2 component input control*/
#define         REG_C753_B8_I2ACTHST_L      0x18    /*Input channel 2 input port ACT H direction start point*/
#define         REG_C753_B8_I2ACTHST_H      0x19    /*Input channel 2 input port ACT H direction start point*/
#define         REG_C753_B8_I2ACTHW_L       0x1A    /*Input channel 2 input port ACT H direction width*/
#define         REG_C753_B8_I2ACTHW_H       0x1B    /*Input channel 2 input port ACT H direction width*/
#define         REG_C753_B8_I2ACTVST_L      0x1C    /*Input channel 2 input port ACT V direction start point*/
#define         REG_C753_B8_I2ACTVST_H      0x1D    /*Input channel 2 input port ACT V direction start point*/
#define         REG_C753_B8_I2ACTVW_L       0x1E    /*Input channel 2 input port ACT V direction width*/
#define         REG_C753_B8_I2ACTVW_H       0x1F    /*Input channel 2 input port ACT V direction width*/
#define         REG_C753_B8_I2SWP           0x20    /*Input channel 2 input signal swap*/
#define         REG_C753_B8_I2COLORCT       0x21    /*Input channel 2 input image control*/
#define         REG_C753_B8_I2FILL_R        0x22    /*Input channel 2 input fill*/
#define         REG_C753_B8_I2FILL_G        0x23    /*Input channel 2 input fill*/
#define         REG_C753_B8_I2FILL_B        0x24    /*Input channel 2 input fill*/
#define         REG_C753_B8_I2GAINY         0x25    /*Input channel 2 gain compensation (Y)*/
#define         REG_C753_B8_I2GAINU         0x26    /*Input channel 2 gain compensation (U)*/
#define         REG_C753_B8_I2GAINV         0x27    /*Input channel 2 gain compensation (V)*/
#define         REG_C753_B8_I2BIASY_L       0x28    /*Input channel 2 bias compensation (Y)*/
#define         REG_C753_B8_I2BIASY_H       0x29    /*Input channel 2 bias compensation (Y)*/
#define         REG_C753_B8_I2BIASU_L       0x2A    /*Input channel 2 bias compensation (U)*/
#define         REG_C753_B8_I2BIASU_H       0x2B    /*Input channel 2 bias compensation (U)*/
#define         REG_C753_B8_I2BIASV_L       0x2C    /*Input channel 2 bias compensation (V)*/
#define         REG_C753_B8_I2BIASV_H       0x2D    /*Input channel 2 bias compensation (V)*/
#define         REG_C753_B8_UVLPCOEFCH2_0   0x2E    /*Input channel 2 UV low pass filter coefficient*/
#define         REG_C753_B8_UVLPCOEFCH2_1   0x2F    /*Input channel 2 UV low pass filter coefficient*/
#define         REG_C753_B8_UVLPCOEFCH2_2   0x30    /*Input channel 2 UV low pass filter coefficient*/
#define         REG_C753_B8_XCOEFRYCH2_L    0x31    /*Input channel 2 RGBYUV color conversion coefficient (RY)*/
#define         REG_C753_B8_XCOEFRYCH2_H    0x32    /*Input channel 2 RGBYUV color conversion coefficient (RY)*/
#define         REG_C753_B8_XCOEFGYCH2_L    0x33    /*Input channel 2 RGBYUV color conversion coefficient (GY)*/
#define         REG_C753_B8_XCOEFGYCH2_H    0x34    /*Input channel 2 RGBYUV color conversion coefficient (GY)*/
#define         REG_C753_B8_XCOEFBYCH2_L    0x35    /*Input channel 2 RGBYUV color conversion coefficient (BY)*/
#define         REG_C753_B8_XCOEFBYCH2_H    0x36    /*Input channel 2 RGBYUV color conversion coefficient (BY)*/
#define         REG_C753_B8_XCOEFRUCH2_L    0x37    /*Input channel 2 RGBYUV color conversion coefficient (RU)*/
#define         REG_C753_B8_XCOEFRUCH2_H    0x38    /*Input channel 2 RGBYUV color conversion coefficient (RU)*/
#define         REG_C753_B8_XCOEFGUCH2_L    0x39    /*Input channel 2 RGBYUV color conversion coefficient (GU)*/
#define         REG_C753_B8_XCOEFGUCH2_H    0x3A    /*Input channel 2 RGBYUV color conversion coefficient (GU)*/
#define         REG_C753_B8_XCOEFBUCH2_L    0x3B    /*Input channel 2 RGBYUV color conversion coefficient (BU)*/
#define         REG_C753_B8_XCOEFBUCH2_H    0x3C    /*Input channel 2 RGBYUV color conversion coefficient (BU)*/
#define         REG_C753_B8_XCOEFRVCH2_L    0x3D    /*Input channel 2 RGBYUV color conversion coefficient (RV)*/
#define         REG_C753_B8_XCOEFRVCH2_H    0x3E    /*Input channel 2 RGBYUV color conversion coefficient (RV)*/
#define         REG_C753_B8_XCOEFGVCH2_L    0x3F    /*Input channel 2 RGBYUV color conversion coefficient (GV)*/
#define         REG_C753_B8_XCOEFGVCH2_H    0x40    /*Input channel 2 RGBYUV color conversion coefficient (GV)*/
#define         REG_C753_B8_XCOEFBVCH2_L    0x41    /*Input channel 2 RGBYUV color conversion coefficient (BV)*/
#define         REG_C753_B8_XCOEFBVCH2_H    0x42    /*Input channel 2 RGBYUV color conversion coefficient (BV)*/
#define         REG_C753_B8_XIERDFCTCH2     0x43    /*Input channel 2 input error diffusion control*/
#define         REG_C753_B8_SHRNKADJCH2     0x45    /*Input channel 2 shrink compensation control*/
#define         REG_C753_B8_HSHRNKCTCH2     0x46    /*Input channel 2 horizontal shrink control*/
#define         REG_C753_B8_HSINITCH2       0x47    /*Input channel 2 horizontal shrink initial value*/
#define         REG_C753_B8_HSSCLCH2_L      0x48    /*Input channel 2 horizontal shrink scale*/
#define         REG_C753_B8_HSSCLCH2_H      0x49    /*Input channel 2 horizontal shrink scale*/
#define         REG_C753_B8_VSHRNKCTCH2     0x4A    /*Input channel 2 vertical shrink control*/
#define         REG_C753_B8_VSINITCH2       0x4B    /*Input channel 2 vertical shrink initial value*/
#define         REG_C753_B8_VSSCLCH2_L      0x4C    /*Input channel 2 vertical shrink scale*/
#define         REG_C753_B8_VSSCLCH2_H      0x4D    /*Input channel 2 vertical shrink scale*/
#define         REG_C753_B8_I2HSHCMP        0x4E    /*Input channel 2 horizontal shrink compensation*/
#define         REG_C753_B8_I2VSHCMP        0x4F    /*Input channel 2 vertical shrink compensation*/
#define         REG_C753_B8_HSLUTCH2_0      0x50    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_1      0x51    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_2      0x52    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_3      0x53    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_4      0x54    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_5      0x55    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_6      0x56    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_7      0x57    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_8      0x58    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_9      0x59    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_10     0x5A    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_11     0x5B    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_12     0x5C    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_13     0x5D    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_14     0x5E    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_15     0x5F    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_16     0x60    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_17     0x61    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_18     0x62    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_19     0x63    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_20     0x64    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_21     0x65    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_22     0x66    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_HSLUTCH2_23     0x67    /*Input channel 2 horizontal reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_0      0x68    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_1      0x69    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_2      0x6A    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_3      0x6B    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_4      0x6C    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_5      0x6D    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_6      0x6E    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_7      0x6F    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_8      0x70    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_9      0x71    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_10     0x72    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_11     0x73    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_12     0x74    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_13     0x75    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_14     0x76    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_15     0x77    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_16     0x78    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_17     0x79    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_18     0x7A    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_19     0x7B    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_20     0x7C    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_21     0x7D    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_22     0x7E    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
#define         REG_C753_B8_VSLUTCH2_23     0x7F    /*Input channel 2 vertical reduction interpolation coefficient lookup table*/
 /*Bank 9 register*/
#define			REG_C753_B9_PMODECH2 		0x62 	/*Input channel 2 input image characteristics measurement control*/
#define			REG_C753_B9_PI1H0_L 		0x63 	/*Input channel 2 measurement horizontal start position coordinate*/
#define			REG_C753_B9_PI1H0_H 		0x64 	/*Input channel 2 measurement horizontal start position coordinate*/
#define			REG_C753_B9_PI1V0_L 		0x65 	/*Input channel 2 measurement vertical start position coordinate*/
#define			REG_C753_B9_PI1V0_H 		0x66 	/*Input channel 2 measurement vertical start position coordinate*/
#define			REG_C753_B9_PI1H1_L 		0x67 	/*Input channel 2 measurement horizontal end position coordinate*/
#define			REG_C753_B9_PI1H1_H 		0x68 	/*Input channel 2 measurement horizontal end position coordinate*/
#define			REG_C753_B9_PI1V1_L 		0x69 	/*Input channel 2 measurement vertical end position coordinate*/
#define			REG_C753_B9_PI1V1_H 		0x6A 	/*Input channel 2 measurement vertical end position coordinate*/
#define			REG_C753_B9_PTHCH2 			0x6B	/*Input channel 2 characteristics measurement threshold*/
 /*Bank 10 register*/
#define         REG_C753_B10_IPOHCYCLCH1_L  0x08    /*Channel 1 IP conversion output port horizontal sync signal cycle*/
#define         REG_C753_B10_IPOHCYCLCH1_H  0x09    /*Channel 1 IP conversion output port horizontal sync signal cycle*/
#define         REG_C753_B10_IPOVCYCLCH1_L  0x0A    /*Channel 1 IP conversion output port vertical sync signal cycle*/
#define         REG_C753_B10_IPOVCYCLCH1_H  0x0B    /*Channel 1 IP conversion output port vertical sync signal cycle*/
#define         REG_C753_B10_IPSYRDLYCH1    0x0C    /*Channel 1 IP conversion forced sync reset delay*/
#define         REG_C753_B10_IPOACTHSTCH1_L 0x0D    /*Channel 1 IP conversion output port active area horizontal start point*/
#define         REG_C753_B10_IPOACTHSTCH1_H 0x0E    /*Channel 1 IP conversion output port active area horizontal start point*/
#define         REG_C753_B10_IPOACTHWCH1_L  0x0F    /*Channel 1 IP conversion output port active area horizontal width*/
#define         REG_C753_B10_IPOACTHWCH1_H  0x10    /*Channel 1 IP conversion output port active area horizontal width*/
#define         REG_C753_B10_IPOACTVSTCH1_L 0x11    /*Channel 1 IP conversion output port active area vertical start point*/
#define         REG_C753_B10_IPOACTVSTCH1_H 0x12    /*Channel 1 IP conversion output port active area vertical start point*/
#define         REG_C753_B10_IPOACTVWCH1_L  0x13    /*Channel 1 IP conversion output port active area vertical width*/
#define         REG_C753_B10_IPOACTVWCH1_H  0x14    /*Channel 1 IP conversion output port active area vertical width*/
#define         REG_C753_B10_MVNRCTCH1      0x15    /*Channel 1 movement NR control*/
#define         REG_C753_B10_HMVNRCFACH1    0x16    /*Channel 1 horizontal movement value NR coefficient (Left and right third pixels from the center)*/
#define         REG_C753_B10_HMVNRCFBCH1    0x17    /*Channel 1 horizontal movement value NR coefficient (Left and right second pixels from the center)*/
#define         REG_C753_B10_HMVNRCFCCH1    0x18    /*Channel 1 horizontal movement value NR coefficient (Left and right first pixels from the center)*/
#define         REG_C753_B10_HMVNRCFDCH1    0x19    /*Channel 1 horizontal movement value NR coefficient (Center)*/
#define         REG_C753_B10_VFILCFACH1     0x1A    /*Channel 1 vertical movement value gain (Upper and lower third pixels from the center)*/
#define         REG_C753_B10_VFILCFBCH1     0x1B    /*Channel 1 vertical movement value gain (Upper and lower second pixels from the center)*/
#define         REG_C753_B10_VFILCFCCH1     0x1C    /*Channel 1 vertical movement value gain (Upper and lower first pixels from the center)*/
#define         REG_C753_B10_VFILCFDCH1     0x1D    /*Channel 1 vertical movement value gain (Center)*/
#define         REG_C753_B10_HFILCFACH1     0x1E    /*Channel 1 horizontal movement value gain (Left and right third pixels from the center)*/
#define         REG_C753_B10_HFILCFBCH1     0x1F    /*Channel 1 horizontal movement value gain (Left and right second pixels from the center)*/
#define         REG_C753_B10_HFILCFCCH1     0x20    /*Channel 1 horizontal movement value gain (Left and right first pixels from the center)*/
#define         REG_C753_B10_HFILCFDCH1     0x21    /*Channel 1 horizontal movement value gain (Center)*/
#define         REG_C753_B10_XVFILMDCH1     0x22    /*Channel 1 vertical direction MAX filter*/
#define         REG_C753_B10_XNRCUTCH1      0x23    /*Channel 1 movement coefficient NR*/
#define         REG_C753_B10_LUTWADCH1      0x24    /*Channel 1 LUT write address*/
#define         REG_C753_B10_LUTCOEFCH1_0   0x25    /*Channel 1 LUT coefficient*/
#define         REG_C753_B10_LUTCOEFCH1_1   0x26    /*Channel 1 LUT coefficient*/
#define         REG_C753_B10_LUTCOEFCH1_2   0x27    /*Channel 1 LUT coefficient*/
#define         REG_C753_B10_LUTCOEFCH1_3   0x28    /*Channel 1 LUT coefficient*/
#define         REG_C753_B10_LUTWRCH1       0x29    /*Channel 1 LUT write enable*/
#define         REG_C753_B10_IPADJCTCH1     0x2A    /*Channel 1 IP image adjustment*/
#define         REG_C753_B10_IPTESTCH1      0x2B    /*Channel 1 IP test*/
#define         REG_C753_B10_PDCTRL1CH1     0x2C    /*Channel 1 pulldown control 1*/
#define         REG_C753_B10_PDCTRL2CH1     0x2D    /*Channel 1 pulldown control 2*/
#define         REG_C753_B10_PDMV22THCH1    0x2E    /*Channel 1 2-2 pulldown movement detect threshold*/
#define         REG_C753_B10_PDMV23THCH1    0x2F    /*Channel 1 2-3 pulldown movement detect threshold*/
#define         REG_C753_B10_PDSQTHCH1      0x30    /*Channel 1 pulldown sequence threshold*/
#define         REG_C753_B10_MVACCSELCH1    0x31    /*Channel 1 pulldown area width select*/
#define         REG_C753_B10_PDACTSELCH1    0x32    /*Channel 1 pulldown detect area select*/
#define         REG_C753_B10_PD22RSTCTCH1   0x33    /*Channel 1 2-2 pulldown reset detect index*/
#define         REG_C753_B10_PD23RSTTHCH1   0x34    /*Channel 1 2-3 pulldown reset detect index*/
#define         REG_C753_B10_COMBCTCH1      0x35    /*Channel 1 combing process control*/
#define         REG_C753_B10_COMBLTHCH1     0x36    /*Channel 1 combing process control low level threshold*/
#define         REG_C753_B10_COMBHTHCH1     0x37    /*Channel 1 combing process control high level threshold*/
#define         REG_C753_B10_DIAGCTCH1_0    0x38    /*Channel 1 diagonal interpolation control*/
#define         REG_C753_B10_DIAGCTCH1_1    0x39    /*Channel 1 diagonal interpolation control*/
#define         REG_C753_B10_DIAGCTCH1_2    0x3A    /*Channel 1 diagonal interpolation control*/
#define         REG_C753_B10_DIAGTHCH1_0    0x3B    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_1    0x3C    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_2    0x3D    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_3    0x3E    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_4    0x3F    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_5    0x40    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_6    0x41    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_7    0x42    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_8    0x43    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_9    0x44    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_10   0x45    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_11   0x46    /*Channel 1 diagonal interpolation threshold*/
#define         REG_C753_B10_DIAGTHCH1_12   0x47    /*Channel 1 diagonal interpolation threshold*/
 /*Bank 11 register*/
#define         REG_C753_B11_IPOHCYCLCH2_L  0x08    /*Channel 2 IP conversion output port horizontal sync signal cycle*/
#define         REG_C753_B11_IPOHCYCLCH2_H  0x09    /*Channel 2 IP conversion output port horizontal sync signal cycle*/
#define         REG_C753_B11_IPOVCYCLCH2_L  0x0A    /*Channel 2 IP conversion output port vertical sync signal cycle*/
#define         REG_C753_B11_IPOVCYCLCH2_H  0x0B    /*Channel 2 IP conversion output port vertical sync signal cycle*/
#define         REG_C753_B11_IPSYRDLYCH2    0x0C    /*Channel 2 IP conversion forced sync reset delay*/
#define         REG_C753_B11_IPOACTHSTCH2_L 0x0D    /*Channel 2 IP conversion output port active area horizontal start point*/
#define         REG_C753_B11_IPOACTHSTCH2_H 0x0E    /*Channel 2 IP conversion output port active area horizontal start point*/
#define         REG_C753_B11_IPOACTHWCH2_L  0x0F    /*Channel 2 IP conversion output port active area horizontal width*/
#define         REG_C753_B11_IPOACTHWCH2_H  0x10    /*Channel 2 IP conversion output port active area horizontal width*/
#define         REG_C753_B11_IPOACTVSTCH2_L 0x11    /*Channel 2 IP conversion output port active area vertical start point*/
#define         REG_C753_B11_IPOACTVSTCH2_H 0x12    /*Channel 2 IP conversion output port active area vertical start point*/
#define         REG_C753_B11_IPOACTVWCH2_L  0x13    /*Channel 2 IP conversion output port active area vertical width*/
#define         REG_C753_B11_IPOACTVWCH2_H  0x14    /*Channel 2 IP conversion output port active area vertical width*/
#define         REG_C753_B11_MVNRCTCH2      0x15    /*Channel 2 movement NR control*/
#define         REG_C753_B11_HMVNRCFACH2    0x16    /*Channel 2 horizontal movement value NR coefficient (Left and right third pixels from the center)*/
#define         REG_C753_B11_HMVNRCFBCH2    0x17    /*Channel 2 horizontal movement value NR coefficient (Left and right second pixels from the center)*/
#define         REG_C753_B11_HMVNRCFCCH2    0x18    /*Channel 2 horizontal movement value NR coefficient (Left and right first pixels from the center)*/
#define         REG_C753_B11_HMVNRCFDCH2    0x19    /*Channel 2 horizontal movement value NR coefficient (Center)*/
#define         REG_C753_B11_VFILCFACH2     0x1A    /*Channel 2 vertical movement value gain (Upper and lower third pixels from the center)*/
#define         REG_C753_B11_VFILCFBCH2     0x1B    /*Channel 2 vertical movement value gain (Upper and lower second pixels from the center)*/
#define         REG_C753_B11_VFILCFCCH2     0x1C    /*Channel 2 vertical movement value gain (Upper and lower first pixels from the center)*/
#define         REG_C753_B11_VFILCFDCH2     0x1D    /*Channel 2 vertical movement value gain (Center)*/
#define         REG_C753_B11_HFILCFACH2     0x1E    /*Channel 2 horizontal movement value gain (Left and right third pixels from the center)*/
#define         REG_C753_B11_HFILCFBCH2     0x1F    /*Channel 2 horizontal movement value gain (Left and right second pixels from the center)*/
#define         REG_C753_B11_HFILCFCCH2     0x20    /*Channel 2 horizontal movement value gain (Left and right first pixels from the center)*/
#define         REG_C753_B11_HFILCFDCH2     0x21    /*Channel 2 horizontal movement value gain (Center)*/
#define         REG_C753_B11_XVFILMDCH2     0x22    /*Channel 2 vertical direction MAX filter*/
#define         REG_C753_B11_XNRCUTCH2      0x23    /*Channel 2 movement coefficient NR*/
#define         REG_C753_B11_LUTWADCH2      0x24    /*Channel 2 LUT write address*/
#define         REG_C753_B11_LUTCOEFCH2_0   0x25    /*Channel 2 LUT coefficient*/
#define         REG_C753_B11_LUTCOEFCH2_1   0x26    /*Channel 2 LUT coefficient*/
#define         REG_C753_B11_LUTCOEFCH2_2   0x27    /*Channel 2 LUT coefficient*/
#define         REG_C753_B11_LUTCOEFCH2_3   0x28    /*Channel 2 LUT coefficient*/
#define         REG_C753_B11_LUTWRCH2       0x29    /*Channel 2 LUT write enable*/
#define         REG_C753_B11_IPADJCTCH2     0x2A    /*Channel 2 IP image adjustment*/
#define         REG_C753_B11_IPTESTCH2      0x2B    /*Channel 2 IP test*/
#define         REG_C753_B11_PDCTRL1CH2     0x2C    /*Channel 2 pulldown control 1*/
#define         REG_C753_B11_PDCTRL2CH2     0x2D    /*Channel 2 pulldown control 2*/
#define         REG_C753_B11_PDMV22THCH2    0x2E    /*Channel 2 2-2 pulldown movement detect threshold*/
#define         REG_C753_B11_PDMV23THCH2    0x2F    /*Channel 2 2-3 pulldown movement detect threshold*/
#define         REG_C753_B11_PDSQTHCH2      0x30    /*Channel 2 pulldown sequence threshold*/
#define         REG_C753_B11_MVACCSELCH2    0x31    /*Channel 2 pulldown area width select*/
#define         REG_C753_B11_PDACTSELCH2    0x32    /*Channel 2 pulldown detect area select*/
#define         REG_C753_B11_PD22RSTCTCH2   0x33    /*Channel 2 2-2 pulldown reset detect index*/
#define         REG_C753_B11_PD23RSTTHCH2   0x34    /*Channel 2 2-3 pulldown reset detect index*/
#define         REG_C753_B11_COMBCTCH2      0x35    /*Channel 2 combing process control*/
#define         REG_C753_B11_COMBLTHCH2     0x36    /*Channel 2 combing process control low level threshold*/
#define         REG_C753_B11_COMBHTHCH2     0x37    /*Channel 2 combing process control high level threshold*/
#define         REG_C753_B11_DIAGCTCH2_0    0x38    /*Channel 2 diagonal interpolation control*/
#define         REG_C753_B11_DIAGCTCH2_1    0x39    /*Channel 2 diagonal interpolation control*/
#define         REG_C753_B11_DIAGCTCH2_2    0x3A    /*Channel 2 diagonal interpolation control*/
#define         REG_C753_B11_DIAGTHCH2_0    0x3B    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_1    0x3C    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_2    0x3D    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_3    0x3E    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_4    0x3F    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_5    0x40    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_6    0x41    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_7    0x42    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_8    0x43    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_9    0x44    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_10   0x45    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_11   0x46    /*Channel 2 diagonal interpolation threshold*/
#define         REG_C753_B11_DIAGTHCH2_12   0x47    /*Channel 2 diagonal interpolation threshold*/
 /*Bank 12 register*/
#define         REG_C753_B12_O1SFLD0_0      0x08    /*Output channel 1 field 0 memory read start address*/
#define         REG_C753_B12_O1SFLD0_1      0x09    /*Output channel 1 field 0 memory read start address*/
#define         REG_C753_B12_O1SFLD0_2      0x0A    /*Output channel 1 field 0 memory read start address*/
#define         REG_C753_B12_O1SFLD0_3      0x0B    /*Output channel 1 field 0 memory read start address*/
#define         REG_C753_B12_O1SFLD1_0      0x0C    /*Output channel 1 field 1 memory read start address*/
#define         REG_C753_B12_O1SFLD1_1      0x0D    /*Output channel 1 field 1 memory read start address*/
#define         REG_C753_B12_O1SFLD1_2      0x0E    /*Output channel 1 field 1 memory read start address*/
#define         REG_C753_B12_O1SFLD1_3      0x0F    /*Output channel 1 field 1 memory read start address*/
#define         REG_C753_B12_O1SFLD2_0      0x10    /*Output channel 1 field 2 memory read start address*/
#define         REG_C753_B12_O1SFLD2_1      0x11    /*Output channel 1 field 2 memory read start address*/
#define         REG_C753_B12_O1SFLD2_2      0x12    /*Output channel 1 field 2 memory read start address*/
#define         REG_C753_B12_O1SFLD2_3      0x13    /*Output channel 1 field 2 memory read start address*/
#define         REG_C753_B12_O1SFLD3_0      0x14    /*Output channel 1 field 3 memory read start address*/
#define         REG_C753_B12_O1SFLD3_1      0x15    /*Output channel 1 field 3 memory read start address*/
#define         REG_C753_B12_O1SFLD3_2      0x16    /*Output channel 1 field 3 memory read start address*/
#define         REG_C753_B12_O1SFLD3_3      0x17    /*Output channel 1 field 3 memory read start address*/
#define         REG_C753_B12_I1SFLD0_0      0x18    /*Input channel 1 field 0 memory write start address*/
#define         REG_C753_B12_I1SFLD0_1      0x19    /*Input channel 1 field 0 memory write start address*/
#define         REG_C753_B12_I1SFLD0_2      0x1A    /*Input channel 1 field 0 memory write start address*/
#define         REG_C753_B12_I1SFLD0_3      0x1B    /*Input channel 1 field 0 memory write start address*/
#define         REG_C753_B12_I1SFLD1_0      0x1C    /*Input channel 1 field 1 memory write start address*/
#define         REG_C753_B12_I1SFLD1_1      0x1D    /*Input channel 1 field 1 memory write start address*/
#define         REG_C753_B12_I1SFLD1_2      0x1E    /*Input channel 1 field 1 memory write start address*/
#define         REG_C753_B12_I1SFLD1_3      0x1F    /*Input channel 1 field 1 memory write start address*/
#define         REG_C753_B12_I1SFLD2_0      0x20    /*Input channel 1 field 2 memory write start address*/
#define         REG_C753_B12_I1SFLD2_1      0x21    /*Input channel 1 field 2 memory write start address*/
#define         REG_C753_B12_I1SFLD2_2      0x22    /*Input channel 1 field 2 memory write start address*/
#define         REG_C753_B12_I1SFLD2_3      0x23    /*Input channel 1 field 2 memory write start address*/
#define         REG_C753_B12_I1SFLD3_0      0x24    /*Input channel 1 field 3 memory write start address*/
#define         REG_C753_B12_I1SFLD3_1      0x25    /*Input channel 1 field 3 memory write start address*/
#define         REG_C753_B12_I1SFLD3_2      0x26    /*Input channel 1 field 3 memory write start address*/
#define         REG_C753_B12_I1SFLD3_3      0x27    /*Input channel 1 field 3 memory write start address*/
#define         REG_C753_B12_O1MWI          0x28    /*Channel 1 memory read linefeed width*/
#define         REG_C753_B12_I1MWI          0x29    /*Channel 1 memory write linefeed width*/
#define         REG_C753_B12_IPOSFLD0CH1_0  0x2A    /*Channel 1 IP conversion field 0 memory read start address*/
#define         REG_C753_B12_IPOSFLD0CH1_1  0x2B    /*Channel 1 IP conversion field 0 memory read start address*/
#define         REG_C753_B12_IPOSFLD0CH1_2  0x2C    /*Channel 1 IP conversion field 0 memory read start address*/
#define         REG_C753_B12_IPOSFLD0CH1_3  0x2D    /*Channel 1 IP conversion field 0 memory read start address*/
#define         REG_C753_B12_IPOSFLD1CH1_0  0x2E    /*Channel 1 IP conversion field 1 memory read start address*/
#define         REG_C753_B12_IPOSFLD1CH1_1  0x2F    /*Channel 1 IP conversion field 1 memory read start address*/
#define         REG_C753_B12_IPOSFLD1CH1_2  0x30    /*Channel 1 IP conversion field 1 memory read start address*/
#define         REG_C753_B12_IPOSFLD1CH1_3  0x31    /*Channel 1 IP conversion field 1 memory read start address*/
#define         REG_C753_B12_IPISFLD0CH1_0  0x32    /*Channel 1 IP conversion field 0 memory write start address*/
#define         REG_C753_B12_IPISFLD0CH1_1  0x33    /*Channel 1 IP conversion field 0 memory write start address*/
#define         REG_C753_B12_IPISFLD0CH1_2  0x34    /*Channel 1 IP conversion field 0 memory write start address*/
#define         REG_C753_B12_IPISFLD0CH1_3  0x35    /*Channel 1 IP conversion field 0 memory write start address*/
#define         REG_C753_B12_IPISFLD1CH1_0  0x36    /*Channel 1 IP conversion field 1 memory write start address*/
#define         REG_C753_B12_IPISFLD1CH1_1  0x37    /*Channel 1 IP conversion field 1 memory write start address*/
#define         REG_C753_B12_IPISFLD1CH1_2  0x38    /*Channel 1 IP conversion field 1 memory write start address*/
#define         REG_C753_B12_IPISFLD1CH1_3  0x39    /*Channel 1 IP conversion field 1 memory write start address*/
#define         REG_C753_B12_IPISFLD2CH1_0  0x3A    /*Channel 1 IP conversion field 2 memory write start address*/
#define         REG_C753_B12_IPISFLD2CH1_1  0x3B    /*Channel 1 IP conversion field 2 memory write start address*/
#define         REG_C753_B12_IPISFLD2CH1_2  0x3C    /*Channel 1 IP conversion field 2 memory write start address*/
#define         REG_C753_B12_IPISFLD2CH1_3  0x3D    /*Channel 1 IP conversion field 2 memory write start address*/
#define         REG_C753_B12_IPISFLD3CH1_0  0x3E    /*Channel 1 IP conversion field 3 memory write start address*/
#define         REG_C753_B12_IPISFLD3CH1_1  0x3F    /*Channel 1 IP conversion field 3 memory write start address*/
#define         REG_C753_B12_IPISFLD3CH1_2  0x40    /*Channel 1 IP conversion field 3 memory write start address*/
#define         REG_C753_B12_IPISFLD3CH1_3  0x41    /*Channel 1 IP conversion field 3 memory write start address*/
#define         REG_C753_B12_IPMWICH1       0x42    /*Channel 1 IP conversion memory linefeed width*/
#define         REG_C753_B12_MVFLDCH1_0     0x43    /*Channel 1 IP conversion movement value read start address*/
#define         REG_C753_B12_MVFLDCH1_1     0x44    /*Channel 1 IP conversion movement value read start address*/
#define         REG_C753_B12_MVFLDCH1_2     0x45    /*Channel 1 IP conversion movement value read start address*/
#define         REG_C753_B12_MVFLDCH1_3     0x46    /*Channel 1 IP conversion movement value read start address*/
#define         REG_C753_B12_TMSASELCH1     0x47    /*Channel 1 temporal NR read start address select*/
#define         REG_C753_B12_MRTOSFLD0CH1_0 0x48    /*Channel 1 90-degree rotation field 0 memory read start address*/
#define         REG_C753_B12_MRTOSFLD0CH1_1 0x49    /*Channel 1 90-degree rotation field 0 memory read start address*/
#define         REG_C753_B12_MRTOSFLD0CH1_2 0x4A    /*Channel 1 90-degree rotation field 0 memory read start address*/
#define         REG_C753_B12_MRTOSFLD0CH1_3 0x4B    /*Channel 1 90-degree rotation field 0 memory read start address*/
#define         REG_C753_B12_MRTOSFLD1CH1_0 0x4C    /*Channel 1 90-degree rotation field 1 memory read start address*/
#define         REG_C753_B12_MRTOSFLD1CH1_1 0x4D    /*Channel 1 90-degree rotation field 1 memory read start address*/
#define         REG_C753_B12_MRTOSFLD1CH1_2 0x4E    /*Channel 1 90-degree rotation field 1 memory read start address*/
#define         REG_C753_B12_MRTOSFLD1CH1_3 0x4F    /*Channel 1 90-degree rotation field 1 memory read start address*/
#define         REG_C753_B12_MRTOSFLD2CH1_0 0x50    /*Channel 1 90-degree rotation field 2 memory read start address*/
#define         REG_C753_B12_MRTOSFLD2CH1_1 0x51    /*Channel 1 90-degree rotation field 2 memory read start address*/
#define         REG_C753_B12_MRTOSFLD2CH1_2 0x52    /*Channel 1 90-degree rotation field 2 memory read start address*/
#define         REG_C753_B12_MRTOSFLD2CH1_3 0x53    /*Channel 1 90-degree rotation field 2 memory read start address*/
#define         REG_C753_B12_MRTOSFLD3CH1_0 0x54    /*Channel 1 90-degree rotation field 3 memory read start address*/
#define         REG_C753_B12_MRTOSFLD3CH1_1 0x55    /*Channel 1 90-degree rotation field 3 memory read start address*/
#define         REG_C753_B12_MRTOSFLD3CH1_2 0x56    /*Channel 1 90-degree rotation field 3 memory read start address*/
#define         REG_C753_B12_MRTOSFLD3CH1_3 0x57    /*Channel 1 90-degree rotation field 3 memory read start address*/
#define         REG_C753_B12_MRTISFLD0CH1_0 0x58    /*Channel 1 90-degree rotation field 0 memory write start address*/
#define         REG_C753_B12_MRTISFLD0CH1_1 0x59    /*Channel 1 90-degree rotation field 0 memory write start address*/
#define         REG_C753_B12_MRTISFLD0CH1_2 0x5A    /*Channel 1 90-degree rotation field 0 memory write start address*/
#define         REG_C753_B12_MRTISFLD0CH1_3 0x5B    /*Channel 1 90-degree rotation field 0 memory write start address*/
#define         REG_C753_B12_MRTISFLD1CH1_0 0x5C    /*Channel 1 90-degree rotation field 1 memory write start address*/
#define         REG_C753_B12_MRTISFLD1CH1_1 0x5D    /*Channel 1 90-degree rotation field 1 memory write start address*/
#define         REG_C753_B12_MRTISFLD1CH1_2 0x5E    /*Channel 1 90-degree rotation field 1 memory write start address*/
#define         REG_C753_B12_MRTISFLD1CH1_3 0x5F    /*Channel 1 90-degree rotation field 1 memory write start address*/
#define         REG_C753_B12_MRTISFLD2CH1_0 0x60    /*Channel 1 90-degree rotation field 2 memory write start address*/
#define         REG_C753_B12_MRTISFLD2CH1_1 0x61    /*Channel 1 90-degree rotation field 2 memory write start address*/
#define         REG_C753_B12_MRTISFLD2CH1_2 0x62    /*Channel 1 90-degree rotation field 2 memory write start address*/
#define         REG_C753_B12_MRTISFLD2CH1_3 0x63    /*Channel 1 90-degree rotation field 2 memory write start address*/
#define         REG_C753_B12_MRTISFLD3CH1_0 0x64    /*Channel 1 90-degree rotation field 3 memory write start address*/
#define         REG_C753_B12_MRTISFLD3CH1_1 0x65    /*Channel 1 90-degree rotation field 3 memory write start address*/
#define         REG_C753_B12_MRTISFLD3CH1_2 0x66    /*Channel 1 90-degree rotation field 3 memory write start address*/
#define         REG_C753_B12_MRTISFLD3CH1_3 0x67    /*Channel 1 90-degree rotation field 3 memory write start address*/
#define         REG_C753_B12_MRTOMWICH1     0x68    /*Channel 1 90-degree rotation memory read linefeed width*/
#define         REG_C753_B12_MRTIMWICH1     0x69    /*Channel 1 90-degree rotation memory write linefeed width*/
 /*Bank 13 register*/
#define         REG_C753_B13_O2SFLD0_0      0x08    /*Output channel 2 field 0 memory read start address*/
#define         REG_C753_B13_O2SFLD0_1      0x09    /*Output channel 2 field 0 memory read start address*/
#define         REG_C753_B13_O2SFLD0_2      0x0A    /*Output channel 2 field 0 memory read start address*/
#define         REG_C753_B13_O2SFLD0_3      0x0B    /*Output channel 2 field 0 memory read start address*/
#define         REG_C753_B13_O2SFLD1_0      0x0C    /*Output channel 2 field 1 memory read start address*/
#define         REG_C753_B13_O2SFLD1_1      0x0D    /*Output channel 2 field 1 memory read start address*/
#define         REG_C753_B13_O2SFLD1_2      0x0E    /*Output channel 2 field 1 memory read start address*/
#define         REG_C753_B13_O2SFLD1_3      0x0F    /*Output channel 2 field 1 memory read start address*/
#define         REG_C753_B13_O2SFLD2_0      0x10    /*Output channel 2 field 2 memory read start address*/
#define         REG_C753_B13_O2SFLD2_1      0x11    /*Output channel 2 field 2 memory read start address*/
#define         REG_C753_B13_O2SFLD2_2      0x12    /*Output channel 2 field 2 memory read start address*/
#define         REG_C753_B13_O2SFLD2_3      0x13    /*Output channel 2 field 2 memory read start address*/
#define         REG_C753_B13_O2SFLD3_0      0x14    /*Output channel 2 field 3 memory read start address*/
#define         REG_C753_B13_O2SFLD3_1      0x15    /*Output channel 2 field 3 memory read start address*/
#define         REG_C753_B13_O2SFLD3_2      0x16    /*Output channel 2 field 3 memory read start address*/
#define         REG_C753_B13_O2SFLD3_3      0x17    /*Output channel 2 field 3 memory read start address*/
#define         REG_C753_B13_I2SFLD0_0      0x18    /*Input channel 2 field 0 memory write start address*/
#define         REG_C753_B13_I2SFLD0_1      0x19    /*Input channel 2 field 0 memory write start address*/
#define         REG_C753_B13_I2SFLD0_2      0x1A    /*Input channel 2 field 0 memory write start address*/
#define         REG_C753_B13_I2SFLD0_3      0x1B    /*Input channel 2 field 0 memory write start address*/
#define         REG_C753_B13_I2SFLD1_0      0x1C    /*Input channel 2 field 1 memory write start address*/
#define         REG_C753_B13_I2SFLD1_1      0x1D    /*Input channel 2 field 1 memory write start address*/
#define         REG_C753_B13_I2SFLD1_2      0x1E    /*Input channel 2 field 1 memory write start address*/
#define         REG_C753_B13_I2SFLD1_3      0x1F    /*Input channel 2 field 1 memory write start address*/
#define         REG_C753_B13_I2SFLD2_0      0x20    /*Input channel 2 field 2 memory write start address*/
#define         REG_C753_B13_I2SFLD2_1      0x21    /*Input channel 2 field 2 memory write start address*/
#define         REG_C753_B13_I2SFLD2_2      0x22    /*Input channel 2 field 2 memory write start address*/
#define         REG_C753_B13_I2SFLD2_3      0x23    /*Input channel 2 field 2 memory write start address*/
#define         REG_C753_B13_I2SFLD3_0      0x24    /*Input channel 2 field 3 memory write start address*/
#define         REG_C753_B13_I2SFLD3_1      0x25    /*Input channel 2 field 3 memory write start address*/
#define         REG_C753_B13_I2SFLD3_2      0x26    /*Input channel 2 field 3 memory write start address*/
#define         REG_C753_B13_I2SFLD3_3      0x27    /*Input channel 2 field 3 memory write start address*/
#define         REG_C753_B13_O2MWI          0x28    /*Channel 2 memory read linefeed width*/
#define         REG_C753_B13_I2MWI          0x29    /*Channel 2 memory write linefeed width*/
#define         REG_C753_B13_IPOSFLD0CH2_0  0x2A    /*Channel 2 IP conversion field 0 memory read start address*/
#define         REG_C753_B13_IPOSFLD0CH2_1  0x2B    /*Channel 2 IP conversion field 0 memory read start address*/
#define         REG_C753_B13_IPOSFLD0CH2_2  0x2C    /*Channel 2 IP conversion field 0 memory read start address*/
#define         REG_C753_B13_IPOSFLD0CH2_3  0x2D    /*Channel 2 IP conversion field 0 memory read start address*/
#define         REG_C753_B13_IPOSFLD1CH2_0  0x2E    /*Channel 2 IP conversion field 1 memory read start address*/
#define         REG_C753_B13_IPOSFLD1CH2_1  0x2F    /*Channel 2 IP conversion field 1 memory read start address*/
#define         REG_C753_B13_IPOSFLD1CH2_2  0x30    /*Channel 2 IP conversion field 1 memory read start address*/
#define         REG_C753_B13_IPOSFLD1CH2_3  0x31    /*Channel 2 IP conversion field 1 memory read start address*/
#define         REG_C753_B13_IPISFLD0CH2_0  0x32    /*Channel 2 IP conversion field 0 memory write start address*/
#define         REG_C753_B13_IPISFLD0CH2_1  0x33    /*Channel 2 IP conversion field 0 memory write start address*/
#define         REG_C753_B13_IPISFLD0CH2_2  0x34    /*Channel 2 IP conversion field 0 memory write start address*/
#define         REG_C753_B13_IPISFLD0CH2_3  0x35    /*Channel 2 IP conversion field 0 memory write start address*/
#define         REG_C753_B13_IPISFLD1CH2_0  0x36    /*Channel 2 IP conversion field 1 memory write start address*/
#define         REG_C753_B13_IPISFLD1CH2_1  0x37    /*Channel 2 IP conversion field 1 memory write start address*/
#define         REG_C753_B13_IPISFLD1CH2_2  0x38    /*Channel 2 IP conversion field 1 memory write start address*/
#define         REG_C753_B13_IPISFLD1CH2_3  0x39    /*Channel 2 IP conversion field 1 memory write start address*/
#define         REG_C753_B13_IPISFLD2CH2_0  0x3A    /*Channel 2 IP conversion field 2 memory write start address*/
#define         REG_C753_B13_IPISFLD2CH2_1  0x3B    /*Channel 2 IP conversion field 2 memory write start address*/
#define         REG_C753_B13_IPISFLD2CH2_2  0x3C    /*Channel 2 IP conversion field 2 memory write start address*/
#define         REG_C753_B13_IPISFLD2CH2_3  0x3D    /*Channel 2 IP conversion field 2 memory write start address*/
#define         REG_C753_B13_IPISFLD3CH2_0  0x3E    /*Channel 2 IP conversion field 3 memory write start address*/
#define         REG_C753_B13_IPISFLD3CH2_1  0x3F    /*Channel 2 IP conversion field 3 memory write start address*/
#define         REG_C753_B13_IPISFLD3CH2_2  0x40    /*Channel 2 IP conversion field 3 memory write start address*/
#define         REG_C753_B13_IPISFLD3CH2_3  0x41    /*Channel 2 IP conversion field 3 memory write start address*/
#define         REG_C753_B13_IPMWICH2       0x42    /*Channel 2 IP conversion memory linefeed width*/
#define         REG_C753_B13_MVFLDCH2_0     0x43    /*Channel 2 IP conversion movement value read start address*/
#define         REG_C753_B13_MVFLDCH2_1     0x44    /*Channel 2 IP conversion movement value read start address*/
#define         REG_C753_B13_MVFLDCH2_2     0x45    /*Channel 2 IP conversion movement value read start address*/
#define         REG_C753_B13_MVFLDCH2_3     0x46    /*Channel 2 IP conversion movement value read start address*/
#define         REG_C753_B13_TMSASELCH2     0x47    /*Channel 2 temporal NR read start address select*/
#define         REG_C753_B13_MRTOSFLD0CH2_0 0x48    /*Channel 2 90-degree rotation field 0 memory read start address*/
#define         REG_C753_B13_MRTOSFLD0CH2_1 0x49    /*Channel 2 90-degree rotation field 0 memory read start address*/
#define         REG_C753_B13_MRTOSFLD0CH2_2 0x4A    /*Channel 2 90-degree rotation field 0 memory read start address*/
#define         REG_C753_B13_MRTOSFLD0CH2_3 0x4B    /*Channel 2 90-degree rotation field 0 memory read start address*/
#define         REG_C753_B13_MRTOSFLD1CH2_0 0x4C    /*Channel 2 90-degree rotation field 1 memory read start address*/
#define         REG_C753_B13_MRTOSFLD1CH2_1 0x4D    /*Channel 2 90-degree rotation field 1 memory read start address*/
#define         REG_C753_B13_MRTOSFLD1CH2_2 0x4E    /*Channel 2 90-degree rotation field 1 memory read start address*/
#define         REG_C753_B13_MRTOSFLD1CH2_3 0x4F    /*Channel 2 90-degree rotation field 1 memory read start address*/
#define         REG_C753_B13_MRTOSFLD2CH2_0 0x50    /*Channel 2 90-degree rotation field 2 memory read start address*/
#define         REG_C753_B13_MRTOSFLD2CH2_1 0x51    /*Channel 2 90-degree rotation field 2 memory read start address*/
#define         REG_C753_B13_MRTOSFLD2CH2_2 0x52    /*Channel 2 90-degree rotation field 2 memory read start address*/
#define         REG_C753_B13_MRTOSFLD2CH2_3 0x53    /*Channel 2 90-degree rotation field 2 memory read start address*/
#define         REG_C753_B13_MRTOSFLD3CH2_0 0x54    /*Channel 2 90-degree rotation field 3 memory read start address*/
#define         REG_C753_B13_MRTOSFLD3CH2_1 0x55    /*Channel 2 90-degree rotation field 3 memory read start address*/
#define         REG_C753_B13_MRTOSFLD3CH2_2 0x56    /*Channel 2 90-degree rotation field 3 memory read start address*/
#define         REG_C753_B13_MRTOSFLD3CH2_3 0x57    /*Channel 2 90-degree rotation field 3 memory read start address*/
#define         REG_C753_B13_MRTISFLD0CH2_0 0x58    /*Channel 2 90-degree rotation field 0 memory write start address*/
#define         REG_C753_B13_MRTISFLD0CH2_1 0x59    /*Channel 2 90-degree rotation field 0 memory write start address*/
#define         REG_C753_B13_MRTISFLD0CH2_2 0x5A    /*Channel 2 90-degree rotation field 0 memory write start address*/
#define         REG_C753_B13_MRTISFLD0CH2_3 0x5B    /*Channel 2 90-degree rotation field 0 memory write start address*/
#define         REG_C753_B13_MRTISFLD1CH2_0 0x5C    /*Channel 2 90-degree rotation field 1 memory write start address*/
#define         REG_C753_B13_MRTISFLD1CH2_1 0x5D    /*Channel 2 90-degree rotation field 1 memory write start address*/
#define         REG_C753_B13_MRTISFLD1CH2_2 0x5E    /*Channel 2 90-degree rotation field 1 memory write start address*/
#define         REG_C753_B13_MRTISFLD1CH2_3 0x5F    /*Channel 2 90-degree rotation field 1 memory write start address*/
#define         REG_C753_B13_MRTISFLD2CH2_0 0x60    /*Channel 2 90-degree rotation field 2 memory write start address*/
#define         REG_C753_B13_MRTISFLD2CH2_1 0x61    /*Channel 2 90-degree rotation field 2 memory write start address*/
#define         REG_C753_B13_MRTISFLD2CH2_2 0x62    /*Channel 2 90-degree rotation field 2 memory write start address*/
#define         REG_C753_B13_MRTISFLD2CH2_3 0x63    /*Channel 2 90-degree rotation field 2 memory write start address*/
#define         REG_C753_B13_MRTISFLD3CH2_0 0x64    /*Channel 2 90-degree rotation field 3 memory write start address*/
#define         REG_C753_B13_MRTISFLD3CH2_1 0x65    /*Channel 2 90-degree rotation field 3 memory write start address*/
#define         REG_C753_B13_MRTISFLD3CH2_2 0x66    /*Channel 2 90-degree rotation field 3 memory write start address*/
#define         REG_C753_B13_MRTISFLD3CH2_3 0x67    /*Channel 2 90-degree rotation field 3 memory write start address*/
#define         REG_C753_B13_MRTOMWICH2     0x68    /*Channel 2 90-degree rotation memory read linefeed width*/
#define         REG_C753_B13_MRTIMWICH2     0x69    /*Channel 2 90-degree rotation memory write linefeed width*/
 /*Bank 14 register*/
#define         REG_C753_B14_FLAD_L         0x08    /*Flash memory address*/
#define         REG_C753_B14_FLAD_H         0x09    /*Flash memory address*/
#define         REG_C753_B14_FLDT_L         0x0A    /*Flash memory data*/
#define         REG_C753_B14_FLDT_H         0x0B    /*Flash memory data*/
#define         REG_C753_B14_FLSPG_L        0x0C    /*Flash memory page control*/
#define         REG_C753_B14_FLSPG_H        0x0D    /*Flash memory page control*/
#define         REG_C753_B14_GIOC           0x10    /*General purpose port I/O control*/
#define         REG_C753_B14_GIOCBIT        0x11    /*General purpose port (GIO[55:48]) I/O control*/
#define         REG_C753_B14_GIOO_0         0x12    /*General purpose port I/O output*/
#define         REG_C753_B14_GIOO_1         0x13    /*General purpose port I/O output*/
#define         REG_C753_B14_GIOO_2         0x14    /*General purpose port I/O output*/
#define         REG_C753_B14_GIOO_3         0x15    /*General purpose port I/O output*/
#define         REG_C753_B14_GIOO_4         0x16    /*General purpose port I/O output*/
#define         REG_C753_B14_GIOO_5         0x17    /*General purpose port I/O output*/
#define         REG_C753_B14_GIOO_6         0x18    /*General purpose port I/O output*/
#define         REG_C753_B14_GIOI_0         0x19    /*General purpose port I/O input*/
#define         REG_C753_B14_GIOI_1         0x1A    /*General purpose port I/O input*/
#define         REG_C753_B14_GIOI_2         0x1B    /*General purpose port I/O input*/
#define         REG_C753_B14_GIOI_3         0x1C    /*General purpose port I/O input*/
#define         REG_C753_B14_GIOI_4         0x1D    /*General purpose port I/O input*/
#define         REG_C753_B14_GIOI_5         0x1E    /*General purpose port I/O input*/
#define         REG_C753_B14_GIOI_6         0x1F    /*General purpose port I/O input*/
#define         REG_C753_B14_GIOS_0         0x20    /*General purpose port I/O select*/
#define         REG_C753_B14_GIOS_1         0x21    /*General purpose port I/O select*/
#define         REG_C753_B14_GIOS_2         0x22    /*General purpose port I/O select*/
#define         REG_C753_B14_GIOS_3         0x23    /*General purpose port I/O select*/
#define         REG_C753_B14_GIOS_4         0x24    /*General purpose port I/O select*/
#define         REG_C753_B14_GIOS_5         0x25    /*General purpose port I/O select*/
#define         REG_C753_B14_GIOS_6         0x26    /*General purpose port I/O select*/
#define         REG_C753_B14_GIPPUCT        0x27    /*GIO pin pull-up control*/
#define         REG_C753_B14_CH1TXD_L       0x29    /*Serial communication channel 1 transmission data*/
#define         REG_C753_B14_CH1TXD_H       0x2A    /*Serial communication channel 1 transmission data*/
#define         REG_C753_B14_CH1RXD_L       0x2B    /*Serial communication channel 1 receive data*/
#define         REG_C753_B14_CH1RXD_H       0x2C    /*Serial communication channel 1 receive data*/
#define         REG_C753_B14_CH1CTL         0x2D    /*Serial communication channel 1 communication control*/
#define         REG_C753_B14_CH1DIV         0x2E    /*Serial communication channel 1 clock dividing*/
#define         REG_C753_B14_CH2TXD_L       0x2F    /*Serial communication channel 2 transmission data*/
#define         REG_C753_B14_CH2TXD_H       0x30    /*Serial communication channel 2 transmission data*/
#define         REG_C753_B14_CH2RXD_L       0x31    /*Serial communication channel 2 receive data*/
#define         REG_C753_B14_CH2RXD_H       0x32    /*Serial communication channel 2 receive data*/
#define         REG_C753_B14_CH2CTL         0x33    /*Serial communication channel 2 communication control*/
#define         REG_C753_B14_CH2DIV         0x34    /*Serial communication channel 2 clock dividing*/
#define         REG_C753_B14_ADCT           0x35    /*AD control*/
#define         REG_C753_B14_ADSTC          0x36    /*AD conversion start*/
#define         REG_C753_B14_ADEOC          0x37    /*AD conversion end*/
#define         REG_C753_B14_ADDT           0x38    /*AD data*/
#define         REG_C753_B14_DACT           0x39    /*DA control*/
#define         REG_C753_B14_DADT0          0x3A    /*DA data 0*/
#define         REG_C753_B14_DADT1          0x3B    /*DA data 1*/
#define         REG_C753_B14_DADT2          0x3C    /*DA data 2*/
#define         REG_C753_B14_DADT3          0x3D    /*DA data 3*/
#define         REG_C753_B14_SELCOEFSET     0x3E    /*LUTROM interpolation coefficient select*/
#define         REG_C753_B14_SELLUT         0x3F    /*LUTROM control*/
#define         REG_C753_B14_MRTCTCH1       0x40    /*Channel 1 image 90-degree rotation control*/
#define         REG_C753_B14_MRTACTHWCH1_L  0x41    /*Channel 1 image 90-degree rotation horizontal active area width*/
#define         REG_C753_B14_MRTACTHWCH1_H  0x42    /*Channel 1 image 90-degree rotation horizontal active area width*/
#define         REG_C753_B14_MRTACTVWCH1_L  0x43    /*Channel 1 image 90-degree rotation vertical active area width*/
#define         REG_C753_B14_MRTACTVWCH1_H  0x44    /*Channel 1 image 90-degree rotation vertical active area width*/
#define         REG_C753_B14_MRTVDLYCH1_L   0x45    /*Channel 1 image 90-degree rotation vertical sync signal delay*/
#define         REG_C753_B14_MRTVDLYCH1_H   0x46    /*Channel 1 image 90-degree rotation vertical sync signal delay*/
#define         REG_C753_B14_MRTCTCH2       0x47    /*Channel 2 image 90-degree rotation control*/
#define         REG_C753_B14_MRTACTHWCH2_L  0x48    /*Channel 2 image 90-degree rotation horizontal active area width*/
#define         REG_C753_B14_MRTACTHWCH2_H  0x49    /*Channel 2 image 90-degree rotation horizontal active area width*/
#define         REG_C753_B14_MRTACTVWCH2_L  0x4A    /*Channel 2 image 90-degree rotation vertical active area width*/
#define         REG_C753_B14_MRTACTVWCH2_H  0x4B    /*Channel 2 image 90-degree rotation vertical active area width*/
#define         REG_C753_B14_MRTVDLYCH2_L   0x4C    /*Channel 2 image 90-degree rotation vertical sync signal delay*/
#define         REG_C753_B14_MRTVDLYCH2_H   0x4D    /*Channel 2 image 90-degree rotation vertical sync signal delay*/
#define         REG_C753_B14_HSLLD_L        0x4E    /*Horizontal sync signal absence judgment value*/
#define         REG_C753_B14_HSLLD_H        0x4F    /*Horizontal sync signal absence judgment value*/
#define         REG_C753_B14_HSHLD_L        0x50    /*Horizontal sync signal presence judgment value*/
#define         REG_C753_B14_HSHLD_H        0x51    /*Horizontal sync signal presence judgment value*/
#define         REG_C753_B14_VSLLD          0x52    /*Vertical sync signal absence judgment value*/
#define         REG_C753_B14_VSHLD          0x53    /*Vertical sync signal presence judgment value*/
#define         REG_C753_B14_1MPLSCT        0x54    /*1 MHz pulse generation control*/
#define         REG_C753_B14_DPMSCT         0x55    /*DPMS control*/
#define         REG_C753_B14_DPMSINTRST     0x56    /*DPMS interrupt reset*/
 /*Bank 15 register*/
#define         REG_C753_B15_TMPPXNRCTCH1   0x08    /*Channel 1 temporal NR control*/
#define         REG_C753_B15_TPXNRTH1CH1    0x09    /*Channel 1 temporal NR threshold 1*/
#define         REG_C753_B15_TPXNRTH2CH1    0x0A    /*Channel 1 temporal NR threshold 2*/
#define         REG_C753_B15_TPXNRTH3CH1    0x0B    /*Channel 1 temporal NR threshold 3*/
#define         REG_C753_B15_TPXNRTH4CH1    0x0C    /*Channel 1 temporal NR threshold 4*/
#define         REG_C753_B15_TPXNRCF1CH1    0x0D    /*Channel 1 temporal NR coefficient 1*/
#define         REG_C753_B15_TPXNRCF2CH1    0x0E    /*Channel 1 temporal NR coefficient 2*/
#define         REG_C753_B15_TPXNRCF3CH1    0x0F    /*Channel 1 temporal NR coefficient 3*/
#define         REG_C753_B15_TPXNRCF4CH1    0x10    /*Channel 1 temporal NR coefficient 4*/
#define         REG_C753_B15_TPXNRCF5CH1    0x11    /*Channel 1 temporal NR coefficient 5*/
#define         REG_C753_B15_TPXNRCF6CH1    0x12    /*Channel 1 temporal NR coefficient 6*/
#define         REG_C753_B15_TPXNRCF7CH1    0x13    /*Channel 1 temporal NR coefficient 7*/
#define         REG_C753_B15_TPXNRCF8CH1    0x14    /*Channel 1 temporal NR coefficient 8*/
#define         REG_C753_B15_MSQENCH1       0x15    /*Channel 1 mosquito NR control*/
#define         REG_C753_B15_MSQLPF5H0CH1   0x16    /*Channel 1 mosquito NR blend low pass filter H direction coefficient 0*/
#define         REG_C753_B15_MSQLPF5H1CH1   0x17    /*Channel 1 mosquito NR blend low pass filter H direction coefficient 1*/
#define         REG_C753_B15_MSQLPF5H2CH1   0x18    /*Channel 1 mosquito NR blend low pass filter H direction coefficient 2*/
#define         REG_C753_B15_MSQLPF5V0CH1   0x19    /*Channel 1 mosquito NR blend low pass filter V direction coefficient 0*/
#define         REG_C753_B15_MSQLPF5V1CH1   0x1A    /*Channel 1 mosquito NR blend low pass filter V direction coefficient 1*/
#define         REG_C753_B15_MSQLPF5V2CH1   0x1B    /*Channel 1 mosquito NR blend low pass filter V direction coefficient 2*/
#define         REG_C753_B15_MSQVEGLPF0CH1  0x1C    /*Channel 1 mosquito NR V direction coefficient 0*/
#define         REG_C753_B15_MSQVEGLPF1CH1  0x1D    /*Channel 1 mosquito NR V direction coefficient 1*/
#define         REG_C753_B15_MSQVEGLPF2CH1  0x1E    /*Channel 1 mosquito NR V direction coefficient 2*/
#define         REG_C753_B15_MSQVEGLPF3CH1  0x1F    /*Channel 1 mosquito NR V direction coefficient 3*/
#define         REG_C753_B15_MSQVEGLPF4CH1  0x20    /*Channel 1 mosquito NR V direction coefficient 4*/
#define         REG_C753_B15_MSQVEGLPF5CH1  0x21    /*Channel 1 mosquito NR V direction coefficient 5*/
#define         REG_C753_B15_MSQHEGLPF0CH1  0x22    /*Channel 1 mosquito NR H direction coefficient 0*/
#define         REG_C753_B15_MSQHEGLPF1CH1  0x23    /*Channel 1 mosquito NR H direction coefficient 1*/
#define         REG_C753_B15_MSQHEGLPF2CH1  0x24    /*Channel 1 mosquito NR H direction coefficient 2*/
#define         REG_C753_B15_MSQHEGLPF3CH1  0x25    /*Channel 1 mosquito NR H direction coefficient 3*/
#define         REG_C753_B15_MSQHEGLPF4CH1  0x26    /*Channel 1 mosquito NR H direction coefficient 4*/
#define         REG_C753_B15_MSQHEGLPF5CH1  0x27    /*Channel 1 mosquito NR H direction coefficient 5*/
#define         REG_C753_B15_BLENDBIASCH1   0x28    /*Channel 1 mosquito NR blend coefficient bias*/
#define         REG_C753_B15_BLENDGAINCH1   0x29    /*Channel 1 mosquito NR blend coefficient gain*/
#define         REG_C753_B15_MSQMAXBIASCH1  0x2A    /*Channel 1 mosquito NR noise bias*/
#define         REG_C753_B15_MSQSUBGAINCH1  0x2B    /*Channel 1 mosquito NR subtraction blend coefficient gain*/
#define         REG_C753_B15_MSQYTH0CH1     0x2C    /*Channel 1 mosquito NR threshold 0*/
#define         REG_C753_B15_MSQYTH1CH1     0x2D    /*Channel 1 mosquito NR threshold 1*/
#define         REG_C753_B15_MSQYTH2CH1     0x2E    /*Channel 1 mosquito NR threshold 2*/
#define         REG_C753_B15_MSQYTH3CH1     0x2F    /*Channel 1 mosquito NR threshold 3*/
#define         REG_C753_B15_MSQYTH4CH1     0x30    /*Channel 1 mosquito NR threshold 4*/
#define         REG_C753_B15_MSQYTH5CH1     0x31    /*Channel 1 mosquito NR threshold 5*/
#define         REG_C753_B15_MSQYTH6CH1     0x32    /*Channel 1 mosquito NR threshold 6*/
#define         REG_C753_B15_MSQYTH7CH1     0x33    /*Channel 1 mosquito NR threshold 7*/
#define         REG_C753_B15_MSQYSUB0CH1    0x34    /*Channel 1 mosquito NR threshold bias 0*/
#define         REG_C753_B15_MSQYSUB1CH1    0x35    /*Channel 1 mosquito NR threshold bias 1*/
#define         REG_C753_B15_MSQYSUB2CH1    0x36    /*Channel 1 mosquito NR threshold bias 2*/
#define         REG_C753_B15_MSQYSUB3CH1    0x37    /*Channel 1 mosquito NR threshold bias 3*/
#define         REG_C753_B15_MSQYSUB4CH1    0x38    /*Channel 1 mosquito NR threshold bias 4*/
#define         REG_C753_B15_MSQYSUB5CH1    0x39    /*Channel 1 mosquito NR threshold bias 5*/
#define         REG_C753_B15_MSQYSUB6CH1    0x3A    /*Channel 1 mosquito NR threshold bias 6*/
#define         REG_C753_B15_MSQYSUB7CH1    0x3B    /*Channel 1 mosquito NR threshold bias 7*/
#define         REG_C753_B15_EPNRCTCH1      0x40    /*Channel 1 adaptive NR control*/
#define         REG_C753_B15_EPNRTHCH1_0    0x41    /*Channel 1 adaptive NR threshold*/
#define         REG_C753_B15_EPNRTHCH1_1    0x42    /*Channel 1 adaptive NR threshold*/
#define         REG_C753_B15_EPNRTHCH1_2    0x43    /*Channel 1 adaptive NR threshold*/
#define         REG_C753_B15_EPNRTHCH1_3    0x44    /*Channel 1 adaptive NR threshold*/
#define         REG_C753_B15_EPNRCFCH1_0    0x45    /*Channel 1 adaptive NR coefficient*/
#define         REG_C753_B15_EPNRCFCH1_1    0x46    /*Channel 1 adaptive NR coefficient*/
#define         REG_C753_B15_EPNRCFCH1_2    0x47    /*Channel 1 adaptive NR coefficient*/
#define         REG_C753_B15_EPNRCFCH1_3    0x48    /*Channel 1 adaptive NR coefficient*/
#define         REG_C753_B15_BNRCTCH1_L     0x49    /*Channel 1 block NR control*/
#define         REG_C753_B15_BNRCTCH1_H     0x4A    /*Channel 1 block NR control*/
#define         REG_C753_B15_BNTESTCH1      0x4B    /*Channel 1 block NR test*/
#define         REG_C753_B15_BNEGTH0CH1     0x4C    /*Channel 1 block noise edge level threshold 0*/
#define         REG_C753_B15_BNEGTH1CH1     0x4D    /*Channel 1 block noise edge level threshold 1*/
#define         REG_C753_B15_BNEGTH2CH1     0x4E    /*Channel 1 block noise edge level threshold 2*/
#define         REG_C753_B15_BNEGTH3CH1     0x4F    /*Channel 1 block noise edge level threshold 3*/
#define         REG_C753_B15_BNRABLCF0CH1   0x50    /*Channel 1 block NR α blend coefficient 0*/
#define         REG_C753_B15_BNRABLCF1CH1   0x51    /*Channel 1 block NR α blend coefficient 1*/
#define         REG_C753_B15_BNLPCF0CH1     0x52    /*Channel 1 block NR low pass filter coefficient 0*/
#define         REG_C753_B15_BNLPCF1CH1     0x53    /*Channel 1 block NR low pass filter coefficient 1*/
#define         REG_C753_B15_BNAMVTHCH1     0x54    /*Channel 1 block boundary peripheral movement value threshold*/
#define         REG_C753_B15_BNAEGTHCH1     0x55    /*Channel 1 block boundary peripheral edge level threshold*/
#define         REG_C753_B15_BNHPOSCH1      0x56    /*Channel 1 horizontal block boundary coordinate*/
#define         REG_C753_B15_BNVPOSCH1      0x57    /*Channel 1 vertical block boundary coordinate*/
#define         REG_C753_B15_BNDETCTCH1     0x58    /*Channel 1 block NR detect control*/
#define         REG_C753_B15_BNLFCYCLCH1    0x59    /*No. of long frames register for channel 1 block boundary auto detect*/
#define         REG_C753_B15_BNHMTHHCCH1    0x5A    /*Channel 1 H block boundary matching upper limit threshold (center pixel)*/
#define         REG_C753_B15_BNHMTHLCCH1    0x5B    /*Channel 1 H block boundary matching lower limit threshold (center pixel)*/
#define         REG_C753_B15_BNHMTHSCH1     0x5C    /*Channel 1 H block boundary matching threshold (peripheral pixel)*/
#define         REG_C753_B15_BNHMCNTTHCH1   0x5D    /*Channel 1 H block boundary matching counts threshold*/
#define         REG_C753_B15_BNHMCNTOFFCH1  0x5E    /*Channel 1 H block boundary matching counts offset*/
#define         REG_C753_B15_BNVMTHHCCH1    0x5F    /*Channel 1 V block boundary matching upper limit threshold (center pixel)*/
#define         REG_C753_B15_BNVMTHLCCH1    0x60    /*Channel 1 V block boundary matching lower limit threshold (center pixel)*/
#define         REG_C753_B15_BNVMTHSCH1     0x61    /*Channel 1 V block boundary matching threshold (peripheral pixel)*/
#define         REG_C753_B15_BNVMCNTTHCH1   0x62    /*Channel 1 V block boundary matching counts threshold*/
#define         REG_C753_B15_BNVMCNTOFFCH1  0x63    /*Channel 1 V block boundary matching counts offset*/
#define         REG_C753_B15_BNPJCTCH1      0x64    /*Channel 1 block NR projection control*/
#define         REG_C753_B15_BNPJCFCH1      0x65    /*Channel 1 block NR projection coefficient*/
#define         REG_C753_B15_BNPJRADCH1     0x66    /*Channel 1 block NR projection read address*/
#define         REG_C753_B15_BNPJRDTCH1     0x67    /*Channel 1 block NR projection read data*/
#define         REG_C753_B15_BNHINIPOSCH1_L 0x68    /*Channel 1 horizontal block boundary initial coordinate (for projection)*/
#define         REG_C753_B15_BNHINIPOSCH1_H 0x69    /*Channel 1 horizontal block boundary initial coordinate (for projection)*/
#define         REG_C753_B15_BNHSCLCH1_L    0x6A    /*Channel 1 horizontal block enlargement scale (for projection)*/
#define         REG_C753_B15_BNHSCLCH1_H    0x6B    /*Channel 1 horizontal block enlargement scale (for projection)*/
#define         REG_C753_B15_BNVINIPOSCH1_L 0x6C    /*Channel 1 vertical block boundary initial coordinate (for projection)*/
#define         REG_C753_B15_BNVINIPOSCH1_H 0x6D    /*Channel 1 vertical block boundary initial coordinate (for projection)*/
#define         REG_C753_B15_BNVSCLCH1_L    0x6E    /*Channel 1 vertical block enlargement scale (for projection)*/
#define         REG_C753_B15_BNVSCLCH1_H    0x6F    /*Channel 1 vertical block enlargement scale (for projection)*/
#define         REG_C753_B15_HVPXNRCTCH1    0x71    /*Channel 1 horizontal/vertical NR control*/
#define         REG_C753_B15_VPXNRCF1CH1    0x72    /*Channel 1 vertical NR coefficient 1*/
#define         REG_C753_B15_VPXNRCF2CH1    0x73    /*Channel 1 vertical NR coefficient 2*/
#define         REG_C753_B15_HPXNRCF1CH1    0x74    /*Channel 1 horizontal NR coefficient 1*/
#define         REG_C753_B15_HPXNRCF2CH1    0x75    /*Channel 1 horizontal NR coefficient 2*/
#define         REG_C753_B15_UVNRCTCH1      0x76    /*Channel 1 chroma error correction control*/
#define         REG_C753_B15_UVNRTHCH1      0x77    /*Channel 1 chroma error detection threshold*/
#define         REG_C753_B15_UVNRCNTTHCH1_L 0x78    /*Channel 1 chroma error detection count threshold*/
#define         REG_C753_B15_UVNRCNTTHCH1_H 0x79    /*Channel 1 chroma error detection count threshold*/
#define         REG_C753_B15_UVNREXTHCH1    0x7A    /*Channel 1 chroma error detection exclusion threshold*/
#define         REG_C753_B15_UVNRATTHCH1    0x7B    /*Channel 1 chroma error automatic correction threshold*/
#define         REG_C753_B15_UVNRATLIMCH1   0x7C    /*Channel 1 chroma error automatic correction counter upper limit*/
#define         REG_C753_B15_UVNRLPCFCH1    0x7D    /*Channel 1 chroma error correction low pass filter coefficient*/
 /*Bank 16 register*/
#define         REG_C753_B16_TMPPXNRCTCH2   0x08    /*Channel 2 temporal NR control*/
#define         REG_C753_B16_TPXNRTH1CH2    0x09    /*Channel 2 temporal NR threshold 1*/
#define         REG_C753_B16_TPXNRTH2CH2    0x0A    /*Channel 2 temporal NR threshold 2*/
#define         REG_C753_B16_TPXNRTH3CH2    0x0B    /*Channel 2 temporal NR threshold 3*/
#define         REG_C753_B16_TPXNRTH4CH2    0x0C    /*Channel 2 temporal NR threshold 4*/
#define         REG_C753_B16_TPXNRCF1CH2    0x0D    /*Channel 2 temporal NR coefficient 1*/
#define         REG_C753_B16_TPXNRCF2CH2    0x0E    /*Channel 2 temporal NR coefficient 2*/
#define         REG_C753_B16_TPXNRCF3CH2    0x0F    /*Channel 2 temporal NR coefficient 3*/
#define         REG_C753_B16_TPXNRCF4CH2    0x10    /*Channel 2 temporal NR coefficient 4*/
#define         REG_C753_B16_TPXNRCF5CH2    0x11    /*Channel 2 temporal NR coefficient 5*/
#define         REG_C753_B16_TPXNRCF6CH2    0x12    /*Channel 2 temporal NR coefficient 6*/
#define         REG_C753_B16_TPXNRCF7CH2    0x13    /*Channel 2 temporal NR coefficient 7*/
#define         REG_C753_B16_TPXNRCF8CH2    0x14    /*Channel 2 temporal NR coefficient 8*/
#define         REG_C753_B16_MSQENCH2       0x15    /*Channel 2 mosquito NR control*/
#define         REG_C753_B16_MSQLPF5H0CH2   0x16    /*Channel 2 mosquito NR blend low pass filter H direction coefficient 0*/
#define         REG_C753_B16_MSQLPF5H1CH2   0x17    /*Channel 2 mosquito NR blend low pass filter H direction coefficient 1*/
#define         REG_C753_B16_MSQLPF5H2CH2   0x18    /*Channel 2 mosquito NR blend low pass filter H direction coefficient 2*/
#define         REG_C753_B16_MSQLPF5V0CH2   0x19    /*Channel 2 mosquito NR blend low pass filter V direction coefficient 0*/
#define         REG_C753_B16_MSQLPF5V1CH2   0x1A    /*Channel 2 mosquito NR blend low pass filter V direction coefficient 1*/
#define         REG_C753_B16_MSQLPF5V2CH2   0x1B    /*Channel 2 mosquito NR blend low pass filter V direction coefficient 2*/
#define         REG_C753_B16_MSQVEGLPF0CH2  0x1C    /*Channel 2 mosquito NR V direction coefficient 0*/
#define         REG_C753_B16_MSQVEGLPF1CH2  0x1D    /*Channel 2 mosquito NR V direction coefficient 1*/
#define         REG_C753_B16_MSQVEGLPF2CH2  0x1E    /*Channel 2 mosquito NR V direction coefficient 2*/
#define         REG_C753_B16_MSQVEGLPF3CH2  0x1F    /*Channel 2 mosquito NR V direction coefficient 3*/
#define         REG_C753_B16_MSQVEGLPF4CH2  0x20    /*Channel 2 mosquito NR V direction coefficient 4*/
#define         REG_C753_B16_MSQVEGLPF5CH2  0x21    /*Channel 2 mosquito NR V direction coefficient 5*/
#define         REG_C753_B16_MSQHEGLPF0CH2  0x22    /*Channel 2 mosquito NR H direction coefficient 0*/
#define         REG_C753_B16_MSQHEGLPF1CH2  0x23    /*Channel 2 mosquito NR H direction coefficient 1*/
#define         REG_C753_B16_MSQHEGLPF2CH2  0x24    /*Channel 2 mosquito NR H direction coefficient 2*/
#define         REG_C753_B16_MSQHEGLPF3CH2  0x25    /*Channel 2 mosquito NR H direction coefficient 3*/
#define         REG_C753_B16_MSQHEGLPF4CH2  0x26    /*Channel 2 mosquito NR H direction coefficient 4*/
#define         REG_C753_B16_MSQHEGLPF5CH2  0x27    /*Channel 2 mosquito NR H direction coefficient 5*/
#define         REG_C753_B16_BLENDBIASCH2   0x28    /*Channel 2 mosquito NR blend coefficient bias*/
#define         REG_C753_B16_BLENDGAINCH2   0x29    /*Channel 2 mosquito NR blend coefficient gain*/
#define         REG_C753_B16_MSQMAXBIASCH2  0x2A    /*Channel 2 mosquito NR noise bias*/
#define         REG_C753_B16_MSQSUBGAINCH2  0x2B    /*Channel 2 mosquito NR subtraction blend coefficient gain*/
#define         REG_C753_B16_MSQYTH0CH2     0x2C    /*Channel 2 mosquito NR threshold 0*/
#define         REG_C753_B16_MSQYTH1CH2     0x2D    /*Channel 2 mosquito NR threshold 1*/
#define         REG_C753_B16_MSQYTH2CH2     0x2E    /*Channel 2 mosquito NR threshold 2*/
#define         REG_C753_B16_MSQYTH3CH2     0x2F    /*Channel 2 mosquito NR threshold 3*/
#define         REG_C753_B16_MSQYTH4CH2     0x30    /*Channel 2 mosquito NR threshold 4*/
#define         REG_C753_B16_MSQYTH5CH2     0x31    /*Channel 2 mosquito NR threshold 5*/
#define         REG_C753_B16_MSQYTH6CH2     0x32    /*Channel 2 mosquito NR threshold 6*/
#define         REG_C753_B16_MSQYTH7CH2     0x33    /*Channel 2 mosquito NR threshold 7*/
#define         REG_C753_B16_MSQYSUB0CH2    0x34    /*Channel 2 mosquito NR threshold bias 0*/
#define         REG_C753_B16_MSQYSUB1CH2    0x35    /*Channel 2 mosquito NR threshold bias 1*/
#define         REG_C753_B16_MSQYSUB2CH2    0x36    /*Channel 2 mosquito NR threshold bias 2*/
#define         REG_C753_B16_MSQYSUB3CH2    0x37    /*Channel 2 mosquito NR threshold bias 3*/
#define         REG_C753_B16_MSQYSUB4CH2    0x38    /*Channel 2 mosquito NR threshold bias 4*/
#define         REG_C753_B16_MSQYSUB5CH2    0x39    /*Channel 2 mosquito NR threshold bias 5*/
#define         REG_C753_B16_MSQYSUB6CH2    0x3A    /*Channel 2 mosquito NR threshold bias 6*/
#define         REG_C753_B16_MSQYSUB7CH2    0x3B    /*Channel 2 mosquito NR threshold bias 7*/
#define         REG_C753_B16_EPNRCTCH2      0x40    /*Channel 2 adaptive NR control*/
#define         REG_C753_B16_EPNRTHCH2_0    0x41    /*Channel 2 adaptive NR threshold*/
#define         REG_C753_B16_EPNRTHCH2_1    0x42    /*Channel 2 adaptive NR threshold*/
#define         REG_C753_B16_EPNRTHCH2_2    0x43    /*Channel 2 adaptive NR threshold*/
#define         REG_C753_B16_EPNRTHCH2_3    0x44    /*Channel 2 adaptive NR threshold*/
#define         REG_C753_B16_EPNRCFCH2_0    0x45    /*Channel 2 adaptive NR coefficient*/
#define         REG_C753_B16_EPNRCFCH2_1    0x46    /*Channel 2 adaptive NR coefficient*/
#define         REG_C753_B16_EPNRCFCH2_2    0x47    /*Channel 2 adaptive NR coefficient*/
#define         REG_C753_B16_EPNRCFCH2_3    0x48    /*Channel 2 adaptive NR coefficient*/
#define         REG_C753_B16_BNRCTCH2_L     0x49    /*Channel 2 block NR control*/
#define         REG_C753_B16_BNRCTCH2_H     0x4A    /*Channel 2 block NR control*/
#define         REG_C753_B16_BNTESTCH2      0x4B    /*Channel 2 block NR test*/
#define         REG_C753_B16_BNEGTH0CH2     0x4C    /*Channel 2 block noise edge level threshold 0*/
#define         REG_C753_B16_BNEGTH1CH2     0x4D    /*Channel 2 block noise edge level threshold 1*/
#define         REG_C753_B16_BNEGTH2CH2     0x4E    /*Channel 2 block noise edge level threshold 2*/
#define         REG_C753_B16_BNEGTH3CH2     0x4F    /*Channel 2 block noise edge level threshold 3*/
#define         REG_C753_B16_BNRABLCF0CH2   0x50    /*Channel 2 block NR α blend coefficient 0*/
#define         REG_C753_B16_BNRABLCF1CH2   0x51    /*Channel 2 block NR α blend coefficient 1*/
#define         REG_C753_B16_BNLPCF0CH2     0x52    /*Channel 2 block NR low pass filter coefficient 0*/
#define         REG_C753_B16_BNLPCF1CH2     0x53    /*Channel 2 block NR low pass filter coefficient 1*/
#define         REG_C753_B16_BNAMVTHCH2     0x54    /*Channel 2 block boundary peripheral movement value threshold*/
#define         REG_C753_B16_BNAEGTHCH2     0x55    /*Channel 2 block boundary peripheral edge level threshold*/
#define         REG_C753_B16_BNHPOSCH2      0x56    /*Channel 2 horizontal block boundary coordinate*/
#define         REG_C753_B16_BNVPOSCH2      0x57    /*Channel 2 vertical block boundary coordinate*/
#define         REG_C753_B16_BNDETCTCH2     0x58    /*Channel 2 block NR detect control*/
#define         REG_C753_B16_BNLFCYCLCH2    0x59    /*No. of long frames register for channel 1 block boundary auto detect*/
#define         REG_C753_B16_BNHMTHHCCH2    0x5A    /*Channel 2 H block boundary matching upper limit threshold (center pixel)*/
#define         REG_C753_B16_BNHMTHLCCH2    0x5B    /*Channel 2 H block boundary matching lower limit threshold (center pixel)*/
#define         REG_C753_B16_BNHMTHSCH2     0x5C    /*Channel 2 H block boundary matching threshold (peripheral pixel)*/
#define         REG_C753_B16_BNHMCNTTHCH2   0x5D    /*Channel 2 H block boundary matching counts threshold*/
#define         REG_C753_B16_BNHMCNTOFFCH2  0x5E    /*Channel 2 H block boundary matching counts offset*/
#define         REG_C753_B16_BNVMTHHCCH2    0x5F    /*Channel 2 V block boundary matching upper limit threshold (center pixel)*/
#define         REG_C753_B16_BNVMTHLCCH2    0x60    /*Channel 2 V block boundary matching lower limit threshold (center pixel)*/
#define         REG_C753_B16_BNVMTHSCH2     0x61    /*Channel 2 V block boundary matching threshold (peripheral pixel)*/
#define         REG_C753_B16_BNVMCNTTHCH2   0x62    /*Channel 2 V block boundary matching counts threshold*/
#define         REG_C753_B16_BNVMCNTOFFCH2  0x63    /*Channel 2 V block boundary matching counts offset*/
#define         REG_C753_B16_BNPJCTCH2      0x64    /*Channel 2 block NR projection control*/
#define         REG_C753_B16_BNPJCFCH2      0x65    /*Channel 2 block NR projection coefficient*/
#define         REG_C753_B16_BNPJRADCH2     0x66    /*Channel 2 block NR projection read address*/
#define         REG_C753_B16_BNPJRDTCH2     0x67    /*Channel 2 block NR projection read data*/
#define         REG_C753_B16_BNHINIPOSCH2_L 0x68    /*Channel 2 horizontal block boundary initial coordinate (for projection)*/
#define         REG_C753_B16_BNHINIPOSCH2_H 0x69    /*Channel 2 horizontal block boundary initial coordinate (for projection)*/
#define         REG_C753_B16_BNHSCLCH2_L    0x6A    /*Channel 2 horizontal block enlargement scale (for projection)*/
#define         REG_C753_B16_BNHSCLCH2_H    0x6B    /*Channel 2 horizontal block enlargement scale (for projection)*/
#define         REG_C753_B16_BNVINIPOSCH2_L 0x6C    /*Channel 2 vertical block boundary initial coordinate (for projection)*/
#define         REG_C753_B16_BNVINIPOSCH2_H 0x6D    /*Channel 2 vertical block boundary initial coordinate (for projection)*/
#define         REG_C753_B16_BNVSCLCH2_L    0x6E    /*Channel 2 vertical block enlargement scale (for projection)*/
#define         REG_C753_B16_BNVSCLCH2_H    0x6F    /*Channel 2 vertical block enlargement scale (for projection)*/
#define         REG_C753_B16_HVPXNRCTCH2    0x71    /*Channel 2 horizontal/vertical NR control*/
#define         REG_C753_B16_VPXNRCF1CH2    0x72    /*Channel 2 vertical NR coefficient 1*/
#define         REG_C753_B16_VPXNRCF2CH2    0x73    /*Channel 2 vertical NR coefficient 2*/
#define         REG_C753_B16_HPXNRCF1CH2    0x74    /*Channel 2 horizontal NR coefficient 1*/
#define         REG_C753_B16_HPXNRCF2CH2    0x75    /*Channel 2 horizontal NR coefficient 2*/
#define         REG_C753_B16_UVNRCTCH2      0x76    /*Channel 2 chroma error correction control*/
#define         REG_C753_B16_UVNRTHCH2      0x77    /*Channel 2 chroma error detection threshold*/
#define         REG_C753_B16_UVNRCNTTHCH2_L 0x78    /*Channel 2 chroma error detection count threshold*/
#define         REG_C753_B16_UVNRCNTTHCH2_H 0x79    /*Channel 2 chroma error detection count threshold*/
#define         REG_C753_B16_UVNREXTHCH2    0x7A    /*Channel 2 chroma error detection exclusion threshold*/
#define         REG_C753_B16_UVNRATTHCH2    0x7B    /*Channel 2 chroma error automatic correction threshold*/
#define         REG_C753_B16_UVNRATLIMCH2   0x7C    /*Channel 2 chroma error automatic correction counter upper limit*/
#define         REG_C753_B16_UVNRLPCFCH2    0x7D    /*Channel 2 chroma error correction low pass filter coefficient*/
 /*Bank 17 register*/
#define         REG_C753_B17_IFH1_L         0x08    /*Channel 1 input port horizontal sync signal frequency*/
#define         REG_C753_B17_IFH1_H         0x09    /*Channel 1 input port horizontal sync signal frequency*/
#define         REG_C753_B17_IFV1_L         0x0A    /*Channel 1 input port vertical sync signal frequency*/
#define         REG_C753_B17_IFV1_H         0x0B    /*Channel 1 input port vertical sync signal frequency*/
#define         REG_C753_B17_IHW1           0x0C    /*Channel 1 input port horizontal sync signal pulse width*/
#define         REG_C753_B17_IVW1           0x0D    /*Channel 1 input port vertical sync signal pulse width*/
#define         REG_C753_B17_IFH2_L         0x0E    /*Channel 2 input port horizontal sync signal frequency*/
#define         REG_C753_B17_IFH2_H         0x0F    /*Channel 2 input port horizontal sync signal frequency*/
#define         REG_C753_B17_IFV2_L         0x10    /*Channel 2 input port vertical sync signal frequency*/
#define         REG_C753_B17_IFV2_H         0x11    /*Channel 2 input port vertical sync signal frequency*/
#define         REG_C753_B17_IHW2           0x12    /*Channel 2 input port horizontal sync signal pulse width*/
#define         REG_C753_B17_IVW2           0x13    /*Channel 2 input port vertical sync signal pulse width*/
#define         REG_C753_B17_I1HVPHDF0_L    0x14    /*Channel 1 horizontal and vertical sync signal phase difference 0*/
#define         REG_C753_B17_I1HVPHDF0_H    0x15    /*Channel 1 horizontal and vertical sync signal phase difference 0*/
#define         REG_C753_B17_I1HVPHDF1_L    0x16    /*Channel 1 horizontal and vertical sync signal phase difference 1*/
#define         REG_C753_B17_I1HVPHDF1_H    0x17    /*Channel 1 horizontal and vertical sync signal phase difference 1*/
#define         REG_C753_B17_I2HVPHDF0_L    0x18    /*Channel 2 horizontal and vertical sync signal phase difference 0*/
#define         REG_C753_B17_I2HVPHDF0_H    0x19    /*Channel 2 horizontal and vertical sync signal phase difference 0*/
#define         REG_C753_B17_I2HVPHDF1_L    0x1A    /*Channel 2 horizontal and vertical sync signal phase difference 1*/
#define         REG_C753_B17_I2HVPHDF1_H    0x1B    /*Channel 2 horizontal and vertical sync signal phase difference 1*/
#define         REG_C753_B17_STATE_L        0x1C    /*Status*/
#define         REG_C753_B17_STATE_H        0x1D    /*Status*/
#define         REG_C753_B17_FLDHIST1       0x1F    /*Channel 1 field history*/
#define         REG_C753_B17_FLDHIST2       0x20    /*Channel 2 field history*/
#define         REG_C753_B17_PSTAT1         0x21    /*Channel 1 measurement status monitor*/
#define         REG_C753_B17_PVAL0CH1       0x22    /*Channel 1 characteristics measurement result 0*/
#define         REG_C753_B17_PVAL1CH1       0x23    /*Channel 1 characteristics measurement result 1*/
#define         REG_C753_B17_PH0CH1_L       0x24    /*Channel 1 characteristics measurement result horizontal coordinate 0*/
#define         REG_C753_B17_PH0CH1_H       0x25    /*Channel 1 characteristics measurement result horizontal coordinate 0*/
#define         REG_C753_B17_PV0CH1_L       0x26    /*Channel 1 characteristics measurement result vertical coordinate 0*/
#define         REG_C753_B17_PV0CH1_H       0x27    /*Channel 1 characteristics measurement result vertical coordinate 0*/
#define         REG_C753_B17_PH1CH1_L       0x28    /*Channel 1 characteristics measurement result horizontal coordinate 1*/
#define         REG_C753_B17_PH1CH1_H       0x29    /*Channel 1 characteristics measurement result horizontal coordinate 1*/
#define         REG_C753_B17_PV1CH1_L       0x2A    /*Channel 1 characteristics measurement result vertical coordinate 1*/
#define         REG_C753_B17_PV1CH1_H       0x2B    /*Channel 1 characteristics measurement result vertical coordinate 1*/
#define         REG_C753_B17_SNMSHIST1      0x2C    /*Channel 1 SN histogram measurement result*/
#define         REG_C753_B17_PSTAT2         0x2D    /*Channel 2 measurement status monitor*/
#define         REG_C753_B17_PVAL0CH2       0x2E    /*Channel 2 characteristics measurement result 0*/
#define         REG_C753_B17_PVAL1CH2       0x2F    /*Channel 2 characteristics measurement result 1*/
#define         REG_C753_B17_PH0CH2_L       0x30    /*Channel 2 characteristics measurement result horizontal coordinate 0*/
#define         REG_C753_B17_PH0CH2_H       0x31    /*Channel 2 characteristics measurement result horizontal coordinate 0*/
#define         REG_C753_B17_PV0CH2_L       0x32    /*Channel 2 characteristics measurement result vertical coordinate 0*/
#define         REG_C753_B17_PV0CH2_H       0x33    /*Channel 2 characteristics measurement result vertical coordinate 0*/
#define         REG_C753_B17_PH1CH2_L       0x34    /*Channel 2 characteristics measurement result horizontal coordinate 1*/
#define         REG_C753_B17_PH1CH2_H       0x35    /*Channel 2 characteristics measurement result horizontal coordinate 1*/
#define         REG_C753_B17_PV1CH2_L       0x36    /*Channel 2 characteristics measurement result vertical coordinate 1*/
#define         REG_C753_B17_PV1CH2_H       0x37    /*Channel 2 characteristics measurement result vertical coordinate 1*/
#define         REG_C753_B17_SNMSHIST2      0x38    /*Channel 2 SN histogram measurement result*/
#define         REG_C753_B17_HISTGRAM1_0    0x39    /*Channel 1 histogram result*/
#define         REG_C753_B17_HISTGRAM1_1    0x3A    /*Channel 1 histogram result*/
#define         REG_C753_B17_HISTGRAM1_2    0x3B    /*Channel 1 histogram result*/
#define         REG_C753_B17_HISTGRAM1_3    0x3C    /*Channel 1 histogram result*/
#define         REG_C753_B17_HISTGRAM1_4    0x3D    /*Channel 1 histogram result*/
#define         REG_C753_B17_HISTGRAM1_5    0x3E    /*Channel 1 histogram result*/
#define         REG_C753_B17_HISTGRAM1_6    0x3F    /*Channel 1 histogram result*/
#define         REG_C753_B17_HISTGRAM1_7    0x40    /*Channel 1 histogram result*/
#define         REG_C753_B17_HISTGRAM2_0    0x41    /*Channel 2 histogram result*/
#define         REG_C753_B17_HISTGRAM2_1    0x42    /*Channel 2 histogram result*/
#define         REG_C753_B17_HISTGRAM2_2    0x43    /*Channel 2 histogram result*/
#define         REG_C753_B17_HISTGRAM2_3    0x44    /*Channel 2 histogram result*/
#define         REG_C753_B17_HISTGRAM2_4    0x45    /*Channel 2 histogram result*/
#define         REG_C753_B17_HISTGRAM2_5    0x46    /*Channel 2 histogram result*/
#define         REG_C753_B17_HISTGRAM2_6    0x47    /*Channel 2 histogram result*/
#define         REG_C753_B17_HISTGRAM2_7    0x48    /*Channel 2 histogram result*/
#define         REG_C753_B17_MAXFILTR1      0x49    /*Channel 1 MAXFILTER result*/
#define         REG_C753_B17_MINFILTR1      0x4A    /*Channel 1 MINFILTER result*/
#define         REG_C753_B17_MAXFILTR2      0x4B    /*Channel 2 MAXFILTER result*/
#define         REG_C753_B17_MINFILTR2      0x4C    /*Channel 2 MINFILTER result*/
#define         REG_C753_B17_APL1           0x4D    /*Channel 1 average luminance level result*/
#define         REG_C753_B17_APL2           0x4E    /*Channel 2 average luminance level result*/
#define         REG_C753_B17_PD23CNT1CH1    0x4F    /*Channel 1 2-3 pulldown sequence count 1*/
#define         REG_C753_B17_PD23CNT2CH1    0x50    /*Channel 1 2-3 pulldown sequence count 2*/
#define         REG_C753_B17_PD23CNT3CH1    0x51    /*Channel 1 2-3 pulldown sequence count 3*/
#define         REG_C753_B17_PD23CNT4CH1    0x52    /*Channel 1 2-3 pulldown sequence count 4*/
#define         REG_C753_B17_PD23CNT5CH1    0x53    /*Channel 1 2-3 pulldown sequence count 5*/
#define         REG_C753_B17_PD22CNT1CH1    0x54    /*Channel 1 2-2 pulldown sequence count 1*/
#define         REG_C753_B17_PD23CNT1CH2    0x55    /*Channel 2 2-3 pulldown sequence count 1*/
#define         REG_C753_B17_PD23CNT2CH2    0x56    /*Channel 2 2-3 pulldown sequence count 2*/
#define         REG_C753_B17_PD23CNT3CH2    0x57    /*Channel 2 2-3 pulldown sequence count 3*/
#define         REG_C753_B17_PD23CNT4CH2    0x58    /*Channel 2 2-3 pulldown sequence count 4*/
#define         REG_C753_B17_PD23CNT5CH2    0x59    /*Channel 2 2-3 pulldown sequence count 5*/
#define         REG_C753_B17_PD22CNT1CH2    0x5A    /*Channel 2 2-2 pulldown sequence count 1*/
#define         REG_C753_B17_OFV_L          0x5B    /*Output port vertical sync signal frequency*/
#define         REG_C753_B17_OFV_H          0x5C    /*Output port vertical sync signal frequency*/
#define         REG_C753_B17_PWMLW_L        0x5D    /*PWM low pulse width counter value*/
#define         REG_C753_B17_PWMLW_H        0x5E    /*PWM low pulse width counter value*/
#define         REG_C753_B17_PWMHW_L        0x5F    /*PWM high pulse width counter value*/
#define         REG_C753_B17_PWMHW_H        0x60    /*PWM high pulse width counter value*/
#define         REG_C753_B17_FLSTAT         0x61    /*Flash status*/
#define         REG_C753_B17_INTSTAT_L      0x62    /*Interrupt status*/
#define         REG_C753_B17_INTSTAT_H      0x63    /*Interrupt status*/
#define         REG_C753_B17_DPMSINTSTAT    0x64    /*DPMS interrupt status*/
#define         REG_C753_B17_DPMSSTAT       0x65    /*DPMS status*/
#define         REG_C753_B17_HMCNTMAXCH1    0x66    /*Channel 1 block noise H matching counts Max.*/
#define         REG_C753_B17_HMCNTMAX2CH1   0x67    /*Channel 1 block noise H matching counts Max. 2*/
#define         REG_C753_B17_HMPOSCH1       0x68    /*Channel 1 block noise H boundary coordinate*/
#define         REG_C753_B17_VMCNTMAXCH1    0x69    /*Channel 1 block noise V matching counts Max.*/
#define         REG_C753_B17_VMCNTMAX2CH1   0x6A    /*Channel 1 block noise V matching counts Max. 2*/
#define         REG_C753_B17_VMPOSCH1       0x6B    /*Channel 1 block noise V boundary coordinate*/
#define         REG_C753_B17_HMCNTMAXCH2    0x6C    /*Channel 2 block noise H matching counts Max.*/
#define         REG_C753_B17_HMCNTMAX2CH2   0x6D    /*Channel 2 block noise H matching counts Max. 2*/
#define         REG_C753_B17_HMPOSCH2       0x6E    /*Channel 2 block noise H boundary coordinate*/
#define         REG_C753_B17_VMCNTMAXCH2    0x6F    /*Channel 2 block noise V matching counts Max.*/
#define         REG_C753_B17_VMCNTMAX2CH2   0x70    /*Channel 2 block noise V matching counts Max. 2*/
#define         REG_C753_B17_VMPOSCH2       0x71    /*Channel 2 block noise V boundary coordinate*/
#define         REG_C753_B17_CRERRST        0x72    /*Chroma error status*/
#define         REG_C753_B17_I1MYCNTL       0x73    /*Channel 1 left side movement/luminance measurements*/
#define         REG_C753_B17_I1MYCNTR       0x74    /*Channel 1 right side movement/luminance measurements*/
#define         REG_C753_B17_I1MYCNTT       0x75    /*Channel 1 upper side movement/luminance measurements*/
#define         REG_C753_B17_I1MYCNTB       0x76    /*Channel 1 lower side movement/luminance measurements*/
#define         REG_C753_B17_I2MYCNTL       0x77    /*Channel 2 left side movement/luminance measurements*/
#define         REG_C753_B17_I2MYCNTR       0x78    /*Channel 2 right side movement/luminance measurements*/
#define         REG_C753_B17_I2MYCNTT       0x79    /*Channel 2 upper side movement/luminance measurements*/
#define         REG_C753_B17_I2MYCNTB       0x7A    /*Channel 2 lower side movement/luminance measurements*/


}
#endif

#endif
