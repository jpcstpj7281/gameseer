/******************************************************************************

文件名          :  CPTVP5160Addr.h
*
******************************************************************************/

#ifndef __CPTVP5160ADDR_H__
#define __CPTVP5160ADDR_H__
    
#ifdef __cplusplus
    extern "C"{
#endif /* __cplusplus */


/*TVP5160芯片寄存器地址宏定义*/

#define CP_TVP5160_STATUS2_ADDR                    0x3b          /*该寄存器的第8位用来检测是否有信号*/
#define CP_TVP5160_VIDEO_STANDARD_SEL_ADDR         0x02          /*TVP5160制式选择控制寄存器地址宏定义*/
#define CP_TVP5160_VIDEO_STANDARD_STATUS_ADDR      0x3F          /*TVP5160信号制式的状态寄存器地址宏定义*/
#define CP_TVP5160_VIDEO_ACUTANCE_ADDR             0x07          /*TVP5160锐度控制寄存器地址宏定义*/
#define CP_TVP5160_LUM_BRIGHTNESS_ADDR             0x09          /*TVP5160亮度控制寄存器地址宏定义*/
#define CP_TVP5160_LUM_CONTRAST_ADDR               0x0A          /*TVP5160对比度控制寄存器地址宏定义*/
#define CP_TVP5160_CHROMA_SATURATION_ADDR          0x0B          /*TVP5160色饱和度控制寄存器地址宏定义*/
#define CP_TVP5160_CHROMA_HUE_ADDR                 0x0C          /*TVP5160色相控制寄存器地址宏定义*/
#define CP_TVP5160_AUTO_MANUAL_GAIN_ADDR           0x01          /*TVP5160自动或手动选择控制寄存器地址宏定义*/
#define CP_TVP5160_AUTO_GAIN_REG_DATA              0x0F          /*TVP5160自动选择控制寄存器所需设置的值*/
#define CP_TVP5160_MANUAL_GAIN_REG_DATA            0x0E          /*TVP5160手动选择控制寄存器所需设置的值*/

#define CP_TVP5160_CVBS_COARSE_GAIN_ADDR           0x46          /*TVP5160中CVBS信号粗精度增益控制寄存器地址*/
#define CP_TVP5160_SVIDEO_LUMA_COARSE_GAIN_ADDR    0x47          /*TVP5160中S_VIDEO信号的亮度粗精度增益控制寄存器地址*/
#define CP_TVP5160_SVIDEO_CHROMA_COARSE_GAIN_ADDR  0x48          /*TVP5160中S_VIDEO信号的色度粗精度增益控制寄存器地址*/

#define CP_TVP5160_SVIDEO_CHROMA_FINE_GAIN_ADDR1   0x4C          /*TVP5160中S_VIDEO信号的色度细精度增益控制寄存器1地址*/
#define CP_TVP5160_SVIDEO_CHROMA_FINE_GAIN_ADDR2   0x4D          /*TVP5160中S_VIDEO信号的色度细精度增益控制寄存器2地址*/
#define CP_TVP5160_LUMA_CVBS_FINE_GAIN_ADDR1       0x50          /*S_VIDEO信号的亮度或CVBS细精度增益控制寄存器1地址*/
#define CP_TVP5160_LUMA_CVBS_FINE_GAIN_ADDR2       0x51          /*S_VIDEO信号的亮度或CVBS细精度增益控制寄存器2地址*/
#define CP_TVP5160_AGC_GAIN_STATUS_ADDR2           0x3D          /*TVP5160中自动增益值读取寄存器地址宏定义*/
#define CP_TVP5160_STATUS_REQUEST                  0x97          /*TVP5160状态请求状态寄存器*/



#define CP_TVP5160_STATUS1_ADDR                    0x3A          /*TVP5160中状态1寄存器地址*/ 
 

#define CP_TVP5160_OPERATION_MODE_ADDR             0x03      /*该寄存器用来设置是运行低电模式,还是正常模式*/
#define CP_TVP5160_POWER_OPERATION                 0         /*TVP5160工作于正常模式*/
#define CP_TVP5160_POWER_SAVE                      1         /*TVP5160工作于低电模式*/

#define CP_TVP5160_INPUT_SELECT_ADDR               0x00      /*输入通道选择寄存器地址*/
#define CP_TVP5160_INPUT_SELECT_CVBS               0x00      /*选择输入通道为CVBS信号 */
#define CP_TVP5160_INPUT_SELECT_SVIDEO             0x40      /*选择输入通道为S_VIDEO信号 */
#define CP_TVP5160_CHIP_ID_MSB_ADDR                0x80      /*TVP5160芯片ID的高字节地址,默认值为0x51*/
#define CP_TVP5160_CHIP_ID_LSB_ADDR                0x81      /*TVP5160芯片ID的低字节地址,默认值为0x60*/
#define CP_TVP5160_CHIP_COLOR_SCOPE_ADDR           0x05



#ifdef __cplusplus
}
#endif
    
#endif


