/*
 * pevent.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef PEVENT_H_
#define PEVENT_H_


#define EVENT_MSGBASE  9


struct PCommonEventUpLoadReq
{
	enum{uri=(EVENT_MSGBASE<<16|3)};
	//event->??| desc->???| //普通事件上报

};

struct PCommonEventUpLoadRsp
{
	enum{uri=(EVENT_MSGBASE<<16|4)};
	//error->xxx | desc->???///普通事件回应
};


struct PImportanceEventUpLoadReq
{
	enum{uri=(EVENT_MSGBASE<<16|5)};
	// event->??| desc->???| //重要事件上报

};

struct PImportanceEventUpLoadRsp
{
	enum{uri=(EVENT_MSGBASE<<16|6)};
	//error->xxx | desc->???//重要事件回应
};




#endif /* PROTOCOL_H_ */
