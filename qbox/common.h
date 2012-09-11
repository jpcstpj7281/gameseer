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


#define test_msg (printf("%s[%d]:", __FILE__,__LINE__), printf)

extern void initOutputModel(uint32_t model);
extern void setInputChannel(uint32_t chn,uint32_t hs,uint32_t vs,uint32_t hOffset,uint32_t vOffset);
extern void setOutputChannel(uint32_t chn,uint32_t hs,uint32_t vs,uint32_t hOffset,uint32_t vOffset);
extern void moveOutputChannel(uint32_t chid,int hPoint,int vPoint);
extern void moveInputChannel(uint32_t chid,int hPoint,int vPoint);
extern void showChannel(uint32_t chn);
extern void hideChannel(uint32_t chn);

}
#endif

#endif /* COMMON_H_ */
