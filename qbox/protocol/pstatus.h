/*
 * pstatus.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef PSTATUS_H_
#define PSTATUS_H_


#define STATUS_MSGBASE  0x01


struct PProtocolVersionReq
{
	enum{uri=(STATUS_MSGBASE<<16|1)};

};

struct PProtocolVersionRsp
{
	enum{uri=(STATUS_MSGBASE<<16|2)};
	//error->xxxx | protocal->xxxx //返回协议版本信息
};


struct PGetInPutReq
{
	enum{uri=(STATUS_MSGBASE<<16|3)};

};

struct PGetInPutRsp
{
	enum{uri=(STATUS_MSGBASE<<16|4)};
	//error->xxxx | total->??| in0->?? | in1-> ?? | ... //返回输入口信息
};

struct PGetOutPutReq
{
	enum{uri=(STATUS_MSGBASE<<16|5)};

};

struct PGetOutPutRsp
{
	enum{uri=(STATUS_MSGBASE<<16|6)};
	//error->xxxx | total->??| out0->?? | out1-> ?? | ... //返回输出口信息
};


struct PGetInPutSizeReq
{
	enum{uri=(STATUS_MSGBASE<<16|7)};
	//in->???|//获取某输入口的分辨率

};

struct PGetInPutSizeRsp
{
	enum{uri=(STATUS_MSGBASE<<16|8)};
	//error->xxxx | in->???| w->??? | h->???| ... //返回某输入口的分辨率
};

struct PGetOutPutSizeReq
{
	enum{uri=(STATUS_MSGBASE<<16|9)};

};

struct PGetOutPutSizeRsp
{
	enum{uri=(STATUS_MSGBASE<<16|10)};
	//error->xxxx | total->??| out0->?? | out1-> ?? | ... //返回输出口信息
};


#endif /* PROTOCOL_H_ */
