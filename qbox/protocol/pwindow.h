/*
 * pwindows.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef PWINDOWS_H_
#define PWINDOWS_H_

/*
//操作窗口协议
2|1: //获取窗口句柄
2|2: error->???| total->?? | winHandle0->???| winHandle1->???|...
2|3: winHandle->???//获取窗口信息
2|4: error->???| winHandle->??? | x->??? | y ->??? | w->??? | h->??? | in->?? | out->?? | layer->??|//返回窗口信息
2|5: x->???| y->??? | w->??? | h->??? | out->??? | //设置窗口
2|6: error->???| winHandle-> ???//设置窗口后返回结果,如果成功返回句柄
2|7: winHandle->???|layer->??| //设置窗口层次
2|8: error->???
2|9: winHandle-> ??? | showState->???| //显示窗口
2|10: error->???
2|11: winHandle-> ??? | //删除窗口
2|12: error->???
2|13: winHandle->???| x->??? | y->???| w->??? | h->???| //移动窗口
2|14: error->???
*/

#define WINDOWS_MSGBASE  2


struct PGetWindowsHandleReq
{
	enum{uri=(WINDOWS_MSGBASE<<16|1)};

};

struct PGetWindowsHandleRsp
{
	enum{uri=(WINDOWS_MSGBASE<<16|2)};
	//error->???| total->?? | winHandle0->???| winHandle1->???|...
};


struct PGetWindowsInfoReq
{
	enum{uri=(WINDOWS_MSGBASE<<16|3)};
	//winHandle->???//获取窗口信息
};

struct PGetWindowsInfoRsp
{
	enum{uri=(WINDOWS_MSGBASE<<16|4)};
	//error->???| winHandle->??? | x->??? | y ->??? | w->??? | h->??? | in->?? | out->?? | layer->??|//返回窗口信息
};

struct PCreateWindowsReq
{
	enum{uri=(WINDOWS_MSGBASE<<16|5)};
	// x->???| y->??? | w->??? | h->??? | out->??? | //设置窗口

};

struct PCreateWindowsRsp
{
	enum{uri=(WINDOWS_MSGBASE<<16|6)};
	//error->???| winHandle-> ???//设置窗口后返回结果,如果成功返回句柄
};


struct PSetWindowsLayerReq
{
	enum{uri=(WINDOWS_MSGBASE<<16|7)};
	//winHandle->???|layer->??| //设置窗口层次

};

struct PSetWindowsLayerRsp
{
	enum{uri=(WINDOWS_MSGBASE<<16|8)};
	//error->???
};

struct PSetWindowsShowStateReq
{
	enum{uri=(WINDOWS_MSGBASE<<16|9)};
	//winHandle-> ??? | showState->???| //显示窗口

};

struct PSetWindowsShowStateRsp
{
	enum{uri=(WINDOWS_MSGBASE<<16|10)};
	//error->???
};

struct PDelWindowsReq
{
	enum{uri=(WINDOWS_MSGBASE<<16|11)};
	//winHandle-> ??? | //删除窗口

};

struct PDelWindowsRsp
{
	enum{uri=(WINDOWS_MSGBASE<<16|12)};
	//error->???
};


struct PMoveWindowsReq
{
	enum{uri=(WINDOWS_MSGBASE<<16|13)};
	// winHandle->???| x->??? | y->???| w->??? | h->???| //移动窗口

};

struct PMoveWindowsRsp
{
	enum{uri=(WINDOWS_MSGBASE<<16|14)};
	//error->???
};


#endif /* PROTOCOL_H_ */
