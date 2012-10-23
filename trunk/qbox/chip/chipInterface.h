#ifndef _CHIP_INTERFACE_H_
#define _CHIP_INTERFACE_H_

#ifdef __cplusplus
    extern "C"{
enum OUTPUT_MODEL
{
	TYPE_MODEL_1024_768 = 0,
	TYPE_MODEL_1440_1050 = 1,
};

void initOutputModel(uint32_t model);
void setInputChannel(uint32_t chn,uint32_t hs,uint32_t vs,uint32_t hOffset,uint32_t vOffset);
void setOutputChannel(uint32_t chn,uint32_t hs,uint32_t vs,uint32_t hOffset,uint32_t vOffset);
void moveOutputChannel(uint32_t chid,int hPoint,int vPoint);

void moveInputChannel(uint32_t chid,int hPoint,int vPoint);
void showChannel(uint32_t chn);
void hideChannel(uint32_t chn);

void setInputSize(uint32_t chid,uint16_t hw,uint16_t vw);
void setOutputSize(uint32_t chid,uint16_t hw,uint16_t vw);

void getSignalModel(uint32_t chn,uint32_t &model);
void setChnSignalModel(uint32_t chn,uint32_t model);

void setChnSignalInput(uint32_t out,uint32_t in);
void getChnSignalInput(uint32_t out,uint32_t &in);

}

#endif /* __cplusplus */
#endif /* USER_H_ */


