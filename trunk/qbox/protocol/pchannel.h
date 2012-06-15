/*
 * pchannel.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef PCHANNEL_H_
#define PCHANNEL_H_


#define CHANNEL_MSGBASE  3


struct PChangeInputReq
{
	enum{uri=(CHANNEL_MSGBASE<<16|1)};
	//winHandle->??? | in->???| //设置窗口输入讯号

};

struct PChangeInputRsp
{
	enum{uri=(CHANNEL_MSGBASE<<16|2)};
	//error->??? //返回设置窗口输入讯号结果
};


struct PSetInPutPicReq
{
	enum{uri=(CHANNEL_MSGBASE<<16|3)};
	//winHandle->??? | pic->???| //设置窗口显示图像

};

struct PSetInPutPicRsp
{
	enum{uri=(CHANNEL_MSGBASE<<16|4)};
	//error->??? //返回设置窗口显示图像结果
};

struct PSetOutPutSizeReq
{
	enum{uri=(CHANNEL_MSGBASE<<16|11)};
	//out->???| w->??? | h->??? | //设置输出通道分辩率
};

struct PSetOutPutSizeRsp
{
	enum{uri=(CHANNEL_MSGBASE<<16|12)};
	//error->??? | w->??? | h->??? | //返回设置输出通道分辩率
};



#endif /* PROTOCOL_H_ */
