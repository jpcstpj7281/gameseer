/*
 * msgHandler.cpp
 *
 *  Created on: 2012-1-10
 *      Author: icecoffee
 */

#include "msgHandler.h"
#include "IServer.h"
#include <iostream>
#include <string.h>

MsgHandler* MsgHandler::m_instance = 0;
MsgHandler::MsgHandler()
{

}

MsgHandler::~MsgHandler()
{

}

void MsgHandler::netMsgInput(uint32_t connID,char* buff,uint32_t buffLen)
{

	MsgInfo msg;
	NetMsgBody netMsg;

	if(buffLen <20)
	{
		cout << " Buff Error buffLen=" << buffLen <<endl;
		return;
	}

	uint32_t move =  sizeof(netMsg.msgHead);

	memcpy((void*)&netMsg,(const void*)buff,sizeof(netMsg.msgHead));

	memcpy((void*)&netMsg.msgType,(const void*)(buff+move),sizeof(netMsg.msgType));
	move +=  sizeof(netMsg.msgType);

	netMsg.msgData.append((const char*)buff+move,buffLen-move);

	MsgBase msgBase;

	msgBase.setMsgInfo(&msg);
	msgBase.setNetMsgBody(&netMsg);
	msgBase.UnpackMsg(msg);



	for(map<uint32_t,CommModel*>::iterator it=m_model.begin();it!=m_model.end();it++)
	{
		it->second->onMsgReq(&msg,connID);
	}

}


bool MsgHandler::sendMsg(uint32_t connID,MsgInfo *pMsg)
{

	NetMsgBody netMsg;

	MsgBase msgBase;

	msgBase.setMsgInfo(pMsg);
	msgBase.setNetMsgBody(&netMsg);

	msgBase.packMsg(netMsg);



	string sendBuff;
	sendBuff.append((const char* )&netMsg,sizeof(NetMsgHead));
	sendBuff.append((const char* )&netMsg.msgType,sizeof(uint32_t));
	sendBuff.append((const char* )netMsg.msgData.c_str(),netMsg.msgData.size());


	IServer::Instance()->SendNetMsg(connID,(char*)sendBuff.c_str(),sendBuff.size());

	return true;

}

MsgHandler* MsgHandler::Instance()
{
	if(m_instance == NULL)
	{
		m_instance = new MsgHandler();
	}
	return m_instance;
}




void MsgHandler::setModel(uint32_t modelType,CommModel *pModel)
{
	m_model[modelType] = pModel;
}
