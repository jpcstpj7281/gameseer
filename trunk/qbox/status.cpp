/*
 * user.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include "status.h"
#include "protocol.h"
#include "msgHandler.h"

Status::Status()
{

}

Status::~Status()
{

}


uint32_t Status::onMsgReq(MsgInfo *msg,uint32_t connID)
{

	switch(msg->msgType)
	{
		case PUserLoginReq::uri:
			onUserLogin(msg,connID);
			break;

		case PUserPingReq::uri:
			onUserPing(msg,connID);
			break;

	}

	return 0;
}

void Status::onUserLogin(MsgInfo *msg,uint32_t connID)
{
	cout<<"onUserLogin"<<" connID="<<connID <<endl;

//	cout<<"user="<<msg->info["user"] <<endl;
//	cout<<"psw="<<msg->info["psw"] <<endl;



	MsgInfo req;
	req.msgType = PUserLoginRsp::uri;

	if(msg->info["user"] == "admin" && msg->info["psw"]=="admin" )
	{
		req.info["result"] = "true";
	}
	else
	{
		req.info["result"] = "false";
	}

	MsgHandler::Instance()->sendMsg(connID,&req);

}

void Status::onUserPing(MsgInfo *msg,uint32_t connID)
{
	cout<<"onUserLogin"<<" connID="<<connID <<endl;

	MsgInfo req;

	req.msgType = PUserPingReq::uri;
	req.info["ping"] = "HELLO!";


	MsgHandler::Instance()->sendMsg(connID,&req);

}




