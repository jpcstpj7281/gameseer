/*
 * main.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <stdlib.h>
#include "IServer.h"
#include "msgHandler.h"
#include "status.h"
#include "windows.h"
#include "event.h"
#include "channel.h"
#include "common.h"
#include "windows.h"


using namespace msg;

void testMenu()
{
	cout<<"1: runServer  Para[Port]"<<endl;

	return ;
}



void runService(int port)
{
	Status status;
	Windows windows;
	Event evt;
	Channel channel;

	MsgHandler::Instance()->setModel(TYPE_MODEL_STATUS,(CommModel*)(&status));
	MsgHandler::Instance()->setModel(TYPE_MODEL_WINDOWS,(CommModel*)(&windows));
	MsgHandler::Instance()->setModel(TYPE_MODEL_EVENT,(CommModel*)(&evt));
	MsgHandler::Instance()->setModel(TYPE_MODEL_CHANNEL,(CommModel*)(&channel));

	IServer::Instance()->setPort(port);
	IServer::Instance()->setServerFlg(true);

	IServer::Instance()->setMsgHandler(MsgHandler::Instance());


	IServer::Instance()->Run();
}




int main(int argc,char*argv[])
{

	cout<<"run test  0 for help!"<<endl;

	int para0 = 0;
	int para1 = 0;

	if(argc == 2)
	{
		para0 = atoi( argv[1]);

	}
	else if(argc == 3)
	{
		para0 = atoi( argv[1]);
		para1 = atoi( argv[2]);
	}
	else
	{
		cout<<"please enter  para!"<<endl;
		return 0;
	}

	switch(para0)
	{
		case 0:
			testMenu();
			break;

		case 1:
			runService(para1);
			break;



		default:
			cout<<"Unkonw enter  para!"<<endl;
			return 0;

	}

	return 0;
}



