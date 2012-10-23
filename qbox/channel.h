/*
 * channel.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include "commModel.h"

namespace msg
{

class Channel
:public CommModel
{

public:
	Channel();
	virtual ~Channel();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID);

private:

	void onPSetSwitchInputReq(MsgInfo *msg,uint32_t connID);
	void onPGetSwitchInputReq(MsgInfo *msg,uint32_t connID);
	void onPSetInPutPicReq(MsgInfo *msg,uint32_t connID);
	void onPSetInPutShowAreaReq(MsgInfo *msg,uint32_t connID);



};

};

#endif /* USER_H_ */
