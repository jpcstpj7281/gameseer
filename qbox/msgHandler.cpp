/*
 * msgHandler.cpp
 *
 *  Created on: 2012-1-10
 *      Author: icecoffee
 */

#include "msgHandler.h"
#include "IServer.h"
#include <iostream>
#include <stdio.h>
#include <string.h>

MsgHandler* MsgHandler::m_instance = 0;
MsgHandler::MsgHandler()
{

}

MsgHandler::~MsgHandler()
{

}

static void showData( const char* buf , bool isSend = false){
    unsigned char* rb = (unsigned char* )buf;

    if ( isSend ) printf("send str to client: ");
    else printf("got str from client: ");
    int i  = 0;
    while( i < 4 ){
        unsigned char show = 0 | rb[i];
        printf( "|%x", show);
        ++i;
    }
    unsigned int len = 0;
    while( i < 8 ){
        len |= (rb[i] << ( i -4 ) );
        printf( "|%2x", rb[i]);
        ++i;
    }

    len += 8;
    while( i < len ){
        printf( "|%2x", rb[i]);
        ++i;
    }
    printf( "\nlen: %d\n", len);
    printf( "\n");
}
void MsgHandler::netMsgInput(uint32_t connID,char* buff,uint32_t buffLen)
{

	MsgInfo msg;
	NetMsgBody netMsg;

//    showData( buff);

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

//    showData( sendBuff.c_str() , true);

	IServer::Instance()->SendNetMsg(connID,(char*)sendBuff.c_str(),sendBuff.size());

	return true;

}

bool MsgHandler::broadcastMsg(MsgInfo *pMsg)
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


	IServer::Instance()->BroadcastMsg((char*)sendBuff.c_str(),sendBuff.size());

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



CommModel* MsgHandler::getModule( uint32_t type )
{
	std::map< uint32_t, CommModel* >::iterator it = m_model.find(type);
	if( it == m_model.end() )
	{
		//logth(Debug, "can't find module instance. type=%u", type);
		return NULL;
	}

	if( it->second  )
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}
