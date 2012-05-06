/*
 * user.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef USER_H_
#define USER_H_

#include "commModel.h"
#include "msgHandler.h"

void response(uint32_t connID, MsgInfo* rsp){ MsgHandler::Instance()->sendMsg(connID,rsp); }

class User
:public CommModel
{

public:
	User();
	virtual ~User();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID);


private:


	uint32_t name;

    struct Impl;
    Impl *_impl;
};


#endif /* USER_H_ */
