/*
 * common.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>


#ifdef __cplusplus
    extern "C"{
#define DEVICE_TYPE   101;

enum Model_TYPE
{
	TYPE_MODEL_STATUS =10001,
	TYPE_MODEL_WINDOWS =10002,
	TYPE_MODEL_EVENT =10003,
	TYPE_MODEL_CHANNEL =10004,

	TYPE_MODEL_BUSDRIVER =20001,

};

enum OUTPUT_MODEL
{
	TYPE_MODEL_1024_768 = 0,
	TYPE_MODEL_1440_1050 = 1,
};


enum INPUT_SIZE_TYPE
{
    TYPE_INPUT_SIZE_702_480 = 0,

    TYPE_INPUT_SIZE_800_600 = 2,
    TYPE_INPUT_SIZE_1024_768_60 = 3,
    TYPE_INPUT_SIZE_1280_1024_60 = 4,
    TYPE_INPUT_SIZE_1600_1200_60 = 5,

    TYPE_INPUT_SIZE_DEFAULT = 255,

};



#define test_msg (printf("\n%s[%d]:", __FILE__,__LINE__), printf)


const uint32_t USE_FLG_OFFLINE = 0;
const uint32_t USE_FLG_ONLINE = 1;

const string VIDEO_TYPE_DEFAULT	 = 	"default";
const string VIDEO_TYPE_CVBS	 = 	"cvbs";
const string VIDEO_TYPE_RGB		 = 	"rgb";

const string VIDEO_TYPE_RING	 = 	"ring";



extern void initOutputModel(uint32_t model);
extern void setInputChannel(uint32_t chn,uint32_t hs,uint32_t vs,uint32_t hOffset,uint32_t vOffset);
extern void setOutputChannel(uint32_t chn,uint32_t hs,uint32_t vs,uint32_t hOffset,uint32_t vOffset);
extern void moveOutputChannel(uint32_t chid,int hPoint,int vPoint);
extern void moveInputChannel(uint32_t chid,int hPoint,int vPoint);
extern void showChannel(uint32_t chn);
extern void hideChannel(uint32_t chn);

extern void setInputSize(uint32_t chid,uint16_t hw,uint16_t vw);
extern void setOutputSize(uint32_t chid,uint16_t hw,uint16_t vw);
extern void setScal(uint32_t chid,uint16_t iHw,uint16_t iVw,uint16_t oHw,uint16_t oVw);

extern void getSignalModel(uint32_t signal,uint32_t &model);

extern void getChnModel(uint32_t chn,uint32_t &model);
extern void setChnModel(uint32_t chn,uint32_t model);

extern void setChnSignalInput(uint32_t out,uint32_t in);
extern void getChnSignalInput(uint32_t out,uint32_t &in);

extern void topChannel(uint32_t channel);
extern void init5160(uint32_t chn);
extern void init772(uint32_t chn,uint32_t flg);

}
#endif

#endif /* COMMON_H_ */
