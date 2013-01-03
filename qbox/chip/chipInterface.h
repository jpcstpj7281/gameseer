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
void setScal(uint32_t chid,uint16_t iHw,uint16_t iVw,uint16_t oHw,uint16_t oVw);


void getSignalModel(uint32_t signal,uint32_t &model);

void getChnModel(uint32_t chn,uint32_t &model);
void setChnModel(uint32_t chn,uint32_t model);

void setChnSignalInput(uint32_t out,uint32_t in);
void getChnSignalInput(uint32_t out,uint32_t &in);

void topChannel(uint32_t channel);

void init5160(uint32_t chn);
void init772(uint32_t chn,uint32_t flg);


}

#endif /* __cplusplus */
#endif /* USER_H_ */


