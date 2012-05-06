/*
 * main.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include "IServer.h"
#include "msgHandler.h"
#include "user.h"
#include "common.h"
#include "exception"

int main(int argc,char*argv[])
{




	User user;

	MsgHandler::Instance()->setModel(TYPE_MODEL_USER,(CommModel*)(&user));


	IServer::Instance()->setPort(8000);
	IServer::Instance()->setServerFlg(true);

	IServer::Instance()->setMsgHandler(MsgHandler::Instance());


    IServer::Instance()->Run();

	return 0;
}

