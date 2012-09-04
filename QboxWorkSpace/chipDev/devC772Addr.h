/******************************************************************************


* 功能描述         :  标清板IP00C772芯片头文件
*
******************************************************************************/
    
#ifndef __CPC772ADDR_H__
#define __CPC772ADDR_H__
    
#ifdef __cplusplus
    extern "C"{
#endif /* __cplusplus */





/*IP00C772芯片寄存器地址宏定义*/

#define  CP_IP00C772_RGBNK_ADDR            0x00   /*Register select                                             */ 
#define  CP_IP00C772_MCT_ADDR              0x01   /*Main control                                                */ 
#define  CP_IP00C772_RTCT_ADDR             0x02   /*Register value transfer control                             */ 
#define  CP_IP00C772_MISC_ADDR             0x03   /*MISCELLANEOUS bit                                           */ 
#define  CP_IP00C772_RESERVED_ADDR         0x04   /*Reserved                                                    */ 
#define  CP_IP00C772_MEMCT_ADDR            0x06   /*Memory control                                              */ 
#define  CP_IP00C772_RSTCT_ADDR            0x07   /*Reset                                                       */ 
                                                                                                                   
#define  CP_IP00C772_B0_OSYCT_ADDR         0x08   /*Output port sync signal control                             */ 
#define  CP_IP00C772_B0_OHCYCL_ADDR1       0x09   /*Output port horizontal sync signal cycle                    */
#define  CP_IP00C772_B0_OHCYCL_ADDR2       0x0A   /*Output port horizontal sync signal cycle                    */ 
#define  CP_IP00C772_B0_OVCYCL_ADDR1       0x0B   /*Output port vertical sync signal cycle                      */
#define  CP_IP00C772_B0_OVCYCL_ADDR2       0x0C   /*Output port vertical sync signal cycle                      */
#define  CP_IP00C772_B0_OHSCT_ADDR         0x0D   /*Output port horizontal sync signal control                  */ 
#define  CP_IP00C772_B0_OVSCT_ADDR         0x0E   /*Output port vertical sync signal control                    */ 
#define  CP_IP00C772_B0_SYRDLY_ADDR        0x0F   /*Forced sync reset delay                                     */ 
#define  CP_IP00C772_B0_OVCYCLMIN_ADDR1    0x10   /*Forced sync reset control                                   */ 
#define  CP_IP00C772_B0_OVCYCLMIN_ADDR2    0x11   /*Forced sync reset control                                   */ 
#define  CP_IP00C772_B0_OSWP_ADDR          0x12   /*Output signal swap                                          */ 
#define  CP_IP00C772_B0_OACTHST_ADDR1      0x13   /*Output port ACT horizontal direction start point            */
#define  CP_IP00C772_B0_OACTHST_ADDR2      0x14   /*Output port ACT horizontal direction start point            */ 
#define  CP_IP00C772_B0_OACTHW_ADDR1       0x15   /*Output port ACT horizontal direction width                  */ 
#define  CP_IP00C772_B0_OACTHW_ADDR2       0x16
#define  CP_IP00C772_B0_OACTVST_ADDR1      0x17   /*Output port ACT vertical direction start point              */ 
#define  CP_IP00C772_B0_OACTVST_ADDR2      0x18   /*Output port ACT vertical direction start point              */ 
#define  CP_IP00C772_B0_OACTVW_ADDR1       0x19   /*Output port ACT vertical direction width                    */ 
#define  CP_IP00C772_B0_OACTVW_ADDR2       0x1A   /*Output port ACT vertical direction width                    */ 
#define  CP_IP00C772_B0_OAOI0HST_ADDR      0x1B   /*Output port OAOI0 horizontal direction start point          */ 
#define  CP_IP00C772_B0_OAOI0HEND_ADDR     0x1D   /*Output port OAOI0 horizontal direction end point            */ 
#define  CP_IP00C772_B0_OAOI0VST_ADDR      0x1F   /*Output port OAOI0 vertical direction start point            */ 
#define  CP_IP00C772_B0_OAOI0VEND_ADDR     0x21   /*Output port OAOI0 vertical direction end point              */ 
#define  CP_IP00C772_B0_OAOI1HST_ADDR      0x23   /*Output port OAOI1 horizontal direction start point          */ 
#define  CP_IP00C772_B0_OAOI1HEND_ADDR     0x25   /*Output port OAOI1 horizontal direction end point            */ 
#define  CP_IP00C772_B0_OAOI1VST_ADDR      0x27   /*Output port OAOI1 vertical direction start point            */ 
#define  CP_IP00C772_B0_OAOI1VEND_ADDR     0x29   /*Output port OAOI1 vertical direction end point              */ 
#define  CP_IP00C772_B0_OFILL_RED_ADDR     0x2B   /*Output fill Red                                             */
#define  CP_IP00C772_B0_OFILL_GREEN_ADDR   0x2C   /*Output fill green                                           */
#define  CP_IP00C772_B0_OFILL_BLUE_ADDR    0x2D   /*Output fill Blue                                            */
#define  CP_IP00C772_B0_OBKGD0_ADDR        0x2E   /*Output background 0                                         */ 
#define  CP_IP00C772_B0_OBKGD1_ADDR        0x31   /*Output background 1                                         */ 
#define  CP_IP00C772_B0_OIMGCT_ADDR        0x34   /*Output image control                                        */ 
#define  CP_IP00C772_B0_OCCFTR_ADDR1       0x35   /*Color conversion coefficient 1                              */ 
#define  CP_IP00C772_B0_OCCFTR_ADDR2       0x36   /*Color conversion coefficient 1                              */ 

#define  CP_IP00C772_B0_OCCFTB_ADDR1        0x37   /*Color conversion coefficient 2                              */ 
#define  CP_IP00C772_B0_OCCFTB_ADDR2        0x38   /*Color conversion coefficient 2                              */

#define  CP_IP00C772_B0_OCCFTGR_ADDR1       0x39   /*Color conversion coefficient 3                              */
#define  CP_IP00C772_B0_OCCFTGR_ADDR2       0x3a   /*Color conversion coefficient 3                              */
#define  CP_IP00C772_B0_OCCFTGB_ADDR1      0x3B   /*Color conversion coefficient 4                              */ 
#define  CP_IP00C772_B0_OCCFTGB_ADDR2      0x3C   /*Color conversion coefficient 4                              */ 
#define  CP_IP00C772_B0_OCCFTRB_ADDR1       0x3D   /*Color conversion coefficient 5                              */ 
#define  CP_IP00C772_B0_OCCFTRB_ADDR2       0x3E   /*Color conversion coefficient 5                              */ 

#define  CP_IP00C772_B0_OCCFTBR_ADDR1       0x3F   /*Color conversion coefficient 6                              */ 
#define  CP_IP00C772_B0_OCCFTBR_ADDR2       0x40   /*Color conversion coefficient 6                              */ 

#define  CP_IP00C772_B0_BGCT_ADDR          0x41   /*Bias gain control                                           */ 
#define  CP_IP00C772_B0_GAINR_ADDR         0x42   /*Gain correction (RED)                                       */ 
#define  CP_IP00C772_B0_GAING_ADDR         0x43   /*Gain correction (GREEN)                                     */ 
#define  CP_IP00C772_B0_GAINB_ADDR         0x44   /*Gain correction (BLUE)                                      */ 
#define  CP_IP00C772_B0_BIASR_ADDR         0x45   /*Bias correction (RED)                                       */ 
#define  CP_IP00C772_B0_BIASG_ADDR         0x47   /*Bias correction (GREEN)                                     */ 
#define  CP_IP00C772_B0_BIASB_ADDR         0x49   /*Bias correction (BLUE)                                      */ 
#define  CP_IP00C772_B0_GAIN2R_ADDR        0x4B   /*Second Gain correction (RED)                                */ 
#define  CP_IP00C772_B0_GAIN2G_ADDR        0x4C   /*Second Gain correction (GREEN)                              */ 
#define  CP_IP00C772_B0_GAIN2B_ADDR        0x4D   /*Second Gain correction (BLUE)                               */ 
#define  CP_IP00C772_B0_BIAS2R_ADDR        0x4E   /*Second Bias correction (RED)                                */ 
#define  CP_IP00C772_B0_BIAS2G_ADDR        0x50   /*Second Bias correction (GREEN)                              */ 
#define  CP_IP00C772_B0_BIAS2B_ADDR        0x52   /*Second Bias correction (BLUE)                               */ 
#define  CP_IP00C772_B0_GMCT_ADDR          0x54   /*Gamma table control                                         */ 
#define  CP_IP00C772_B0_GMBNKSEL_ADDR      0x56   /*Gamma table bank select                                     */ 
#define  CP_IP00C772_B0_GMAD_ADDR          0x57   /*Gamma table bank address                                    */ 
#define  CP_IP00C772_B0_GMDT_ADDR          0x58   /*Gamma table bank data                                       */ 
#define  CP_IP00C772_B0_ERDFCT_ADDR        0x59   /*Error diffusion control                                     */ 
#define  CP_IP00C772_B0_ACTCT_ADDR         0x5A   /*Active area selection                                       */ 
#define  CP_IP00C772_B0_HISTGRAMCT_ADDR    0x5B   /*Histogram control register                                  */ 
#define  CP_IP00C772_B0_POCLKOCT_ADDR      0x5C   /*POCLKO control    None                                      */ 
#define  CP_IP00C772_B0_POPLLCT_ADDR       0x5D   /*POCLK system PLL control                                    */ 
#define  CP_IP00C772_B0_POREFDIV_ADDR      0x5E   /*POCLK output dividings                                      */ 
#define  CP_IP00C772_B0_POFBDIV_ADDR       0x5F   /*Number of POCLK feedback dividings                          */ 
#define  CP_IP00C772_B0_GIO1SEL_ADDR       0x60   /*General purpose I/O 1 control                               */ 
#define  CP_IP00C772_B0_GIO1DATA_ADDR      0x61   /*General purpose I/O 1 data                                  */ 
                                                                                                                   
#define  CP_IP00C772_B1_IIMGCT_ADDR        0x08   /*Input format control                                        */ 
#define  CP_IP00C772_B1_ISYCT_ADDR         0x09   /*Input port sync signal control                              */ 
#define  CP_IP00C772_B1_HVPHMSR_ADDR       0x0A   /*HV phase difference measurement                             */ 
#define  CP_IP00C772_B1_IVLNDLY_ADDR1      0x0B   /*Input vertical sync signal line delay                       */ 
#define  CP_IP00C772_B1_IVLNDLY_ADDR2      0x0C   /*Input vertical sync signal line delay                       */ 
#define  CP_IP00C772_B1_IVSKDLY_ADDR1      0x0D   /*Input vertical sync signal CLK delay                        */ 
#define  CP_IP00C772_B1_IVSKDLY_ADDR2      0x0E   /*Input vertical sync signal CLK delay                        */ 
#define  CP_IP00C772_B1_IHSKDLY_ADDR1      0x0F   /*Input horizontal sync signal CLK delay                      */ 
#define  CP_IP00C772_B1_IHSKDLY_ADDR2      0x10   /*Input horizontal sync signal CLK delay                      */ 
#define  CP_IP00C772_B1_AUTOFLD_ADDR       0x11   /*Field recognition control                                   */ 
#define  CP_IP00C772_B1_DIFCT_ADDR         0x12   /*Digital interface control     None                          */ 
#define  CP_IP00C772_B1_DHCYCL_ADDR        0x13   /*Digital interface horizontal sync signal cycle              */ 
#define  CP_IP00C772_B1_DVDLY_ADDR         0x15   /*Digital interface vertical sync signal delay                */ 
#define  CP_IP00C772_B1_ICPNCT_ADDR        0x17   /*Component input control                                     */ 
#define  CP_IP00C772_B1_IACTHST_ADDR1      0x18   /*Input port ACT horizontal direction start point             */ 
#define  CP_IP00C772_B1_IACTHST_ADDR2      0x19   /*Input port ACT horizontal direction start point             */ 
#define  CP_IP00C772_B1_IACTHW_ADDR1       0x1A   /*Input port ACT horizontal direction width                   */
#define  CP_IP00C772_B1_IACTHW_ADDR2       0x1B   /*Input port ACT horizontal direction width                   */
#define  CP_IP00C772_B1_IACTVST_ADDR1      0x1C   /*Input port ACT vertical direction start point               */ 
#define  CP_IP00C772_B1_IACTVST_ADDR2      0x1D   /*Input port ACT vertical direction start point               */ 
#define  CP_IP00C772_B1_IACTVW_ADDR1       0x1E   /*Input port ACT vertical direction width                     */
#define  CP_IP00C772_B1_IACTVW_ADDR2       0x1F   /*Input port ACT vertical direction width                     */
#define  CP_IP00C772_B1_ISWP_ADDR          0x20   /*Input signal swap                                           */ 
#define  CP_IP00C772_B1_ICOLORCT_ADDR      0x21   /*Input image control                                         */ 
#define  CP_IP00C772_B1_IFILL_ADDR         0x22   /*Input fill                                                  */ 
#define  CP_IP00C772_B1_PMODE_ADDR         0x24   /*Input image characteristics measurement control             */ 
#define  CP_IP00C772_B1_PIH0_ADDR          0x25   /*Measurement start horizontal coordinate                     */ 
#define  CP_IP00C772_B1_PIV0_ADDR          0x27   /*Measurement start vertical coordinate                       */ 
#define  CP_IP00C772_B1_PIH1_ADDR          0x29   /*Measurement end horizontal coordinate                       */ 
#define  CP_IP00C772_B1_PIV1_ADDR          0x2B   /*Measurement end vertical coordinate                         */ 
#define  CP_IP00C772_B1_PTH_ADDR           0x2D   /*Characteristics measurement threshold                       */ 
                                                                                                                   
#define  CP_IP00C772_B2_TMPPXNRCT_ADDR     0x08   /*Pixel NR control                                            */ 
#define  CP_IP00C772_B2_TPXNRTH1_ADDR      0x09   /*Pixel NR threshold 1                                        */ 
#define  CP_IP00C772_B2_TPXNRTH2_ADDR      0x0A   /*Pixel NR threshold 2                                        */ 
#define  CP_IP00C772_B2_TPXNRTH3_ADDR      0x0B   /*Pixel NR threshold 3                                        */ 
#define  CP_IP00C772_B2_TPXNRTH4_ADDR      0x0C   /*Pixel NR threshold 4                                        */ 
#define  CP_IP00C772_B2_TPXNRCF1_ADDR      0x0D   /*Pixel temporal NR coefficient 1                             */ 
#define  CP_IP00C772_B2_TPXNRCF2_ADDR      0x0E   /*Pixel temporal NR coefficient 2                             */ 
#define  CP_IP00C772_B2_TPXNRCF3_ADDR      0x0F   /*Pixel temporal NR coefficient 3                             */ 
#define  CP_IP00C772_B2_TPXNRCF4_ADDR      0x10   /*Pixel temporal NR coefficient 4                             */ 
#define  CP_IP00C772_B2_TPXNRCF5_ADDR      0x11   /*Pixel temporal NR coefficient 5                             */ 
#define  CP_IP00C772_B2_TPXNRCF6_ADDR      0x12   /*Pixel temporal NR coefficient 6                             */ 
#define  CP_IP00C772_B2_TPXNRCF7_ADDR      0x13   /*Pixel temporal NR coefficient 7                             */ 
#define  CP_IP00C772_B2_TPXNRCF8_ADDR      0x14   /*Pixel temporal NR coefficient 8                             */ 
#define  CP_IP00C772_B2_HVPXNRCT_ADDR      0x15   /*Horizontal and vertical NR control                          */ 
#define  CP_IP00C772_B2_VPXNRCF1_ADDR      0x16   /*Pixel vertical NR coefficient 1                             */ 
#define  CP_IP00C772_B2_VPXNRCF2_ADDR      0x17   /*Pixel vertical NR coefficient 2                             */ 
#define  CP_IP00C772_B2_HPXNRCF1_ADDR      0x18   /*Pixel horizontal NR coefficient 1                           */ 
#define  CP_IP00C772_B2_HPXNRCF2_ADDR      0x19   /*Pixel horizontal NR coefficient 2                           */ 
#define  CP_IP00C772_B2_MVNRCT_ADDR        0x1A   /*Movement NR control                                         */ 
#define  CP_IP00C772_B2_HMVNRCFA_ADDR      0x1B   /*Horizontal movement value NR coefficient                    */ 
#define  CP_IP00C772_B2_HMVNRCFB_ADDR      0x1C   /*Horizontal movement value NR coefficient                    */ 
#define  CP_IP00C772_B2_HMVNRCFC_ADDR      0x1D   /*Horizontal movement value NR coefficient                    */ 
#define  CP_IP00C772_B2_HMVNRCFD_ADDR      0x1E   /*Horizontal movement value NR coefficient (Center)           */ 
#define  CP_IP00C772_B2_VFILCFA_ADDR       0x1F   /*Vertical movement value gain                                */ 
#define  CP_IP00C772_B2_VFILCFB_ADDR       0x20   /*Vertical movement value gain                                */ 
#define  CP_IP00C772_B2_VFILCFC_ADDR       0x21   /*Vertical movement value gain                                */ 
#define  CP_IP00C772_B2_VFILCFD_ADDR       0x22   /*Vertical movement value gain (Center)                       */ 
#define  CP_IP00C772_B2_HFILCFA_ADDR       0x23   /*Horizontal movement value gain                              */ 
#define  CP_IP00C772_B2_HFILCFB_ADDR       0x24   /*Horizontal movement value gain                              */ 
#define  CP_IP00C772_B2_HFILCFC_ADDR       0x25   /*Horizontal movement value gain )                            */ 
#define  CP_IP00C772_B2_HFILCFD_ADDR      0x26   /*Horizontal movement value gain (Center)                     */ 
#define  CP_IP00C772_B2_XVFILMD_ADDR       0x27   /*Vertical MAX filter                                         */ 
#define  CP_IP00C772_B2_XNRCUT_ADDR        0x28   /*Movement coefficient NR                                     */ 
#define  CP_IP00C772_B2_LUTWAD_ADDR        0x29   /*LUT write address                                           */ 
#define  CP_IP00C772_B2_LUTCOEF_ADDR       0x2A   /*LUT coefficient                                             */ 
#define  CP_IP00C772_B2_LUTWR_ADDR         0x2E   /*LUT write enable                                            */                                                     */ 
#define  CP_IP00C772_B2_IPTEST_ADDR        0x30   /*IP test                                                     */ 
#define  CP_IP00C772_B2_OADJCT_ADDR        0x31   /*Image adjustment control                                    */ 
#define  CP_IP00C772_B2_PDCTRL_ADDR        0x32   /*Pulldown control                                            */ 
#define  CP_IP00C772_B2_PDMV22TH_ADDR      0x33   /*2-2 Pulldown movement detect threshold                      */ 
#define  CP_IP00C772_B2_PD23RSTTH_ADDR     0x34   /*2-3 Pulldown reset detect index                             */ 
#define  CP_IP00C772_B2_PDSQTH_ADDR        0x35   /*Pulldown sequence threshold                                 */ 
#define  CP_IP00C772_B2_MVACCSEL_ADDR      0x36   /*Pulldown area width select                                  */ 
#define  CP_IP00C772_B2_PDACTSEL_ADDR      0x37   /*Pulldown detect area select                                 */ 
#define  CP_IP00C772_B2_PD22RSTCT_ADDR     0x38   /*2-2 Pulldown reset detect index                             */ 
#define  CP_IP00C772_B2_PDMV23TH_ADDR      0x39   /*2-3 Pulldown movement detect threshold                      */ 
#define  CP_IP00C772_B2_DIAGCT1_ADDR        0x3A   /*Diagonal interpolation control*/
#define  CP_IP00C772_B2_DIAGCT2_ADDR        0x3b   /*Diagonal interpolation control*/     
#define  CP_IP00C772_B2_DIAGCT3_ADDR        0x3c   /*Diagonal interpolation control*/
               
#define  CP_IP00C772_B2_DIAGTH0_ADDR        0x3D   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH1_ADDR        0x3E   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH2_ADDR        0x3F   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH3_ADDR        0x40   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH4_ADDR        0x41   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH5_ADDR        0x42   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH6_ADDR        0x43   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH7_ADDR        0x44   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH8_ADDR        0x45   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH9_ADDR        0x46   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH10_ADDR        0x47   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH11_ADDR        0x48   /*Diagonal interpolation threshold                            */ 
#define  CP_IP00C772_B2_DIAGTH12_ADDR        0x49   /*Diagonal interpolation threshold                            */ 





                                                                                                                   
#define  CP_IP00C772_B3_IPOSFLD0_ADDR1      0x08   /*IP conversion field 0 memory read start address             */ 
#define  CP_IP00C772_B3_IPOSFLD0_ADDR2      0x09
#define  CP_IP00C772_B3_IPOSFLD0_ADDR3      0x0a
#define  CP_IP00C772_B3_IPOSFLD1_ADDR1      0x0B   /*IP conversion field 1 memory read start address             */ 
#define  CP_IP00C772_B3_IPOSFLD1_ADDR2      0x0c
#define  CP_IP00C772_B3_IPOSFLD1_ADDR3      0x0d
#define  CP_IP00C772_B3_IPISFLD0_ADDR1      0x0E   /*IP conversion field 0 memory write start address            */ 
#define  CP_IP00C772_B3_IPISFLD0_ADDR2      0x0f
#define  CP_IP00C772_B3_IPISFLD0_ADDR3      0x10

#define  CP_IP00C772_B3_IPISFLD1_ADDR1      0x11   /*IP conversion field 1 memory write start address            */ 
#define  CP_IP00C772_B3_IPISFLD1_ADDR2      0x12
#define  CP_IP00C772_B3_IPISFLD1_ADDR3      0x13
#define  CP_IP00C772_B3_IPISFLD2_ADDR1      0x14   /*IP conversion field 2 memory write start address            */ 
#define  CP_IP00C772_B3_IPISFLD2_ADDR2      0x15
#define  CP_IP00C772_B3_IPISFLD2_ADDR3      0x16
#define  CP_IP00C772_B3_IPISFLD3_ADDR1      0x17   /*IP conversion field 3 memory write start address            */ 
#define  CP_IP00C772_B3_IPISFLD3_ADDR2      0x18
#define  CP_IP00C772_B3_IPISFLD3_ADDR3      0x19

#define  CP_IP00C772_B3_IPMWI_ADDR         0x1A   /*IP conversion memory line feed width                        */ 
#define  CP_IP00C772_B3_MVFLD_ADDR1         0x1B   /*IP conversion movement value/read start address             */ 
#define  CP_IP00C772_B3_MVFLD_ADDR2        0x1c
#define  CP_IP00C772_B3_MVFLD_ADDR3         0x1d
#define  CP_IP00C772_B3_TMSASEL_ADDR       0x1E   /*Temporal filter read start address select                   */ 
                                                                                                                   
#define  CP_IP00C772_B4_IFH_ADDR1          0x08   /*Input port horizontal sync signal cycle monitor             */ 
#define  CP_IP00C772_B4_IFH_ADDR2          0x09   /*Input port horizontal sync signal cycle monitor             */ 
#define  CP_IP00C772_B4_IFV_ADDR1          0x0A   /*Input port vertical sync signal cycle monitor               */ 
#define  CP_IP00C772_B4_IFV_ADDR2          0x0B   /*Input port vertical sync signal cycle monitor               */ 
#define  CP_IP00C772_B4_IHW_ADDR           0x0C   /*Input port horizontal sync signal pulse width               */ 
#define  CP_IP00C772_B4_IVW_ADDR           0x0D   /*Input port vertical sync signal pulse width                 */ 
#define  CP_IP00C772_B4_HVPHDF0_ADDR       0x0E   /*Horizontal and vertical sync signal phase difference 0      */ 
#define  CP_IP00C772_B4_HVPHDF1_ADDR       0x10   /*Horizontal and vertical sync signal phase difference 1      */ 
#define  CP_IP00C772_B4_STATE_ADDR         0x12   /*Status                                                      */ 
#define  CP_IP00C772_B4_FLDHIST_ADDR       0x13   /*Field history                                               */ 
#define  CP_IP00C772_B4_PSTAT_ADDR         0x14   /*Measurement status monitor                                  */ 
#define  CP_IP00C772_B4_PVAL0_ADDR         0x15   /*Characteristics measurement result 0                        */ 
#define  CP_IP00C772_B4_PVAL1_ADDR         0x16   /*Characteristics measurement result 1                        */ 
#define  CP_IP00C772_B4_PH0_ADDR           0x17   /*Characteristics measurement result horizontal coordinate 0  */ 
#define  CP_IP00C772_B4_PV0_ADDR           0x19   /*Characteristics measurement result vertical coordinate 0    */ 
#define  CP_IP00C772_B4_PH1_ADDR           0x1B   /*Characteristics measurement result horizontal coordinate 1  */ 
#define  CP_IP00C772_B4_PV1_ADDR           0x1D   /*Characteristics measurement result vertical coordinate 1    */ 
#define  CP_IP00C772_B4_HISTGRAM_ADDR      0x1F   /*Histogram result                                            */ 
#define  CP_IP00C772_B4_MAXFILTR_ADDR      0x27   /*MAXFILTER result                                            */ 
#define  CP_IP00C772_B4_MINFILTR_ADDR      0x28   /*MINFILTER result                                            */ 
#define  CP_IP00C772_B4_APL_ADDR           0x29   /*Average luminance level result 1                            */ 
#define  CP_IP00C772_B4_PD23CNT1_ADDR      0x2A   /*2-3 Pulldown sequence count 1                               */ 
#define  CP_IP00C772_B4_PD23CNT2_ADDR      0x2B   /*2-3 Pulldown sequence count 2                               */ 
#define  CP_IP00C772_B4_PD23CNT3_ADDR      0x2C   /*2-3 Pulldown sequence count 3                               */ 
#define  CP_IP00C772_B4_PD23CNT4_ADDR      0x2D   /*2-3 Pulldown sequence count 4                               */ 
#define  CP_IP00C772_B4_PD23CNT5_ADDR      0x2E   /*2-3 Pulldown sequence count 5                               */ 
#define  CP_IP00C772_B4_PD22CNT1_ADDR      0x2F   /*2-2 Pulldown sequence count 1                               */ 
#define  CP_IP00C772_B4_OFV_ADDR           0x30   /*Output port vertical sync signal cycle monitor              */ 


// 补充的IP00C772寄存器地址宏定义
#define  CP_IP00C772_MISC_ADDR                0x03           /*MISCELLANEOUS bit*/
#define  CP_IP00C772_LUTCOEF_a                  0x2a
#define  CP_IP00C772_LUTCOEF_b                  0x2b   
#define  CP_IP00C772_LUTCOEF_c                  0x2c  
#define  CP_IP00C772_LUTCOEF_d                  0x2d 
#define  CP_IP00C772_LUTWAD                     0x29
#define  CP_IP00C772_LUTWR                      0x2e


#ifdef __cplusplus
}
#endif
    
#endif

