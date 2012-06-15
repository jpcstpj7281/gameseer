/*
 * status.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "commModel.h"

namespace msg
{

class Event
:public CommModel
{

public:
	Event();
	virtual ~Event();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID);
	virtual void mifCommonEvent(uint32_t eventId);
	virtual void mifImportanceEvent(uint32_t eventId);

private:

	void onPCommonEventUpLoadRsp(MsgInfo *msg,uint32_t connID);
	void onPImportanceEventUpLoadRsp(MsgInfo *msg,uint32_t connID);


};

};

#endif /* USER_H_ */
