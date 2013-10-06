/*
 * pchannel.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef PCHANNEL_H_
#define PCHANNEL_H_


#define CHANNEL_MSGBASE  3


struct PSetSwitchInputReq
{
	enum{uri=(CHANNEL_MSGBASE<<16|1)};
	//winHandle->??? | in->???| out->???|//设置窗口输入讯号

};

struct PSetSwitchInputRsp
{
	enum{uri=(CHANNEL_MSGBASE<<16|2)};
	//error->??? | in->???| out->???| //返回设置窗口输入讯号结果
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

struct PGetSwitchInputReq
{
	enum{uri=(CHANNEL_MSGBASE<<16|5)};
	//  //设置窗口显示图像

};

struct PGetSwitchInputRsp
{
	enum{uri=(CHANNEL_MSGBASE<<16|6)};
	//error->??? | out0->???| out1->???| out2->???| out3->???|//返回设置窗口显示图像结果
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


struct PInitSDChannelReq
{
	enum{uri=(CHANNEL_MSGBASE<<16|13)};
	//channel->??? //设置输出通道分辩率
};

struct PInitSDChannelRsp
{
	enum{uri=(CHANNEL_MSGBASE<<16|14)};
	//error->???
};



#endif /* PROTOCOL_H_ */
