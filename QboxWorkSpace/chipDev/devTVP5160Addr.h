/******************************************************************************

�ļ���          :  CPTVP5160Addr.h
*
******************************************************************************/

#ifndef __CPTVP5160ADDR_H__
#define __CPTVP5160ADDR_H__
    
#ifdef __cplusplus
    extern "C"{
#endif /* __cplusplus */


/*TVP5160оƬ�Ĵ�����ַ�궨��*/

#define CP_TVP5160_STATUS2_ADDR                    0x3b          /*�üĴ����ĵ�8λ��������Ƿ����ź�*/
#define CP_TVP5160_VIDEO_STANDARD_SEL_ADDR         0x02          /*TVP5160��ʽѡ����ƼĴ�����ַ�궨��*/
#define CP_TVP5160_VIDEO_STANDARD_STATUS_ADDR      0x3F          /*TVP5160�ź���ʽ��״̬�Ĵ�����ַ�궨��*/
#define CP_TVP5160_VIDEO_ACUTANCE_ADDR             0x07          /*TVP5160��ȿ��ƼĴ�����ַ�궨��*/
#define CP_TVP5160_LUM_BRIGHTNESS_ADDR             0x09          /*TVP5160���ȿ��ƼĴ�����ַ�궨��*/
#define CP_TVP5160_LUM_CONTRAST_ADDR               0x0A          /*TVP5160�Աȶȿ��ƼĴ�����ַ�궨��*/
#define CP_TVP5160_CHROMA_SATURATION_ADDR          0x0B          /*TVP5160ɫ���Ͷȿ��ƼĴ�����ַ�궨��*/
#define CP_TVP5160_CHROMA_HUE_ADDR                 0x0C          /*TVP5160ɫ����ƼĴ�����ַ�궨��*/
#define CP_TVP5160_AUTO_MANUAL_GAIN_ADDR           0x01          /*TVP5160�Զ����ֶ�ѡ����ƼĴ�����ַ�궨��*/
#define CP_TVP5160_AUTO_GAIN_REG_DATA              0x0F          /*TVP5160�Զ�ѡ����ƼĴ����������õ�ֵ*/
#define CP_TVP5160_MANUAL_GAIN_REG_DATA            0x0E          /*TVP5160�ֶ�ѡ����ƼĴ����������õ�ֵ*/

#define CP_TVP5160_CVBS_COARSE_GAIN_ADDR           0x46          /*TVP5160��CVBS�źŴ־���������ƼĴ�����ַ*/
#define CP_TVP5160_SVIDEO_LUMA_COARSE_GAIN_ADDR    0x47          /*TVP5160��S_VIDEO�źŵ����ȴ־���������ƼĴ�����ַ*/
#define CP_TVP5160_SVIDEO_CHROMA_COARSE_GAIN_ADDR  0x48          /*TVP5160��S_VIDEO�źŵ�ɫ�ȴ־���������ƼĴ�����ַ*/

#define CP_TVP5160_SVIDEO_CHROMA_FINE_GAIN_ADDR1   0x4C          /*TVP5160��S_VIDEO�źŵ�ɫ��ϸ����������ƼĴ���1��ַ*/
#define CP_TVP5160_SVIDEO_CHROMA_FINE_GAIN_ADDR2   0x4D          /*TVP5160��S_VIDEO�źŵ�ɫ��ϸ����������ƼĴ���2��ַ*/
#define CP_TVP5160_LUMA_CVBS_FINE_GAIN_ADDR1       0x50          /*S_VIDEO�źŵ����Ȼ�CVBSϸ����������ƼĴ���1��ַ*/
#define CP_TVP5160_LUMA_CVBS_FINE_GAIN_ADDR2       0x51          /*S_VIDEO�źŵ����Ȼ�CVBSϸ����������ƼĴ���2��ַ*/
#define CP_TVP5160_AGC_GAIN_STATUS_ADDR2           0x3D          /*TVP5160���Զ�����ֵ��ȡ�Ĵ�����ַ�궨��*/
#define CP_TVP5160_STATUS_REQUEST                  0x97          /*TVP5160״̬����״̬�Ĵ���*/



#define CP_TVP5160_STATUS1_ADDR                    0x3A          /*TVP5160��״̬1�Ĵ�����ַ*/ 
 

#define CP_TVP5160_OPERATION_MODE_ADDR             0x03      /*�üĴ����������������е͵�ģʽ,��������ģʽ*/
#define CP_TVP5160_POWER_OPERATION                 0         /*TVP5160����������ģʽ*/
#define CP_TVP5160_POWER_SAVE                      1         /*TVP5160�����ڵ͵�ģʽ*/

#define CP_TVP5160_INPUT_SELECT_ADDR               0x00      /*����ͨ��ѡ��Ĵ�����ַ*/
#define CP_TVP5160_INPUT_SELECT_CVBS               0x00      /*ѡ������ͨ��ΪCVBS�ź� */
#define CP_TVP5160_INPUT_SELECT_SVIDEO             0x40      /*ѡ������ͨ��ΪS_VIDEO�ź� */
#define CP_TVP5160_CHIP_ID_MSB_ADDR                0x80      /*TVP5160оƬID�ĸ��ֽڵ�ַ,Ĭ��ֵΪ0x51*/
#define CP_TVP5160_CHIP_ID_LSB_ADDR                0x81      /*TVP5160оƬID�ĵ��ֽڵ�ַ,Ĭ��ֵΪ0x60*/
#define CP_TVP5160_CHIP_COLOR_SCOPE_ADDR           0x05



#ifdef __cplusplus
}
#endif
    
#endif


