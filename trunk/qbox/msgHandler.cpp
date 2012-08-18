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

static void showData( const char* buf , bool isSend = false)
{
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


	if(buffLen <20)
	{
		cout << " Buff Error buffLen=" << buffLen <<endl;
		return;
	}

	uint32_t move = 0;
    while ( move < buffLen )
    {
    	showData( buff + move);


    	test_msg("netMsgInput\n");

        memcpy((void*)&netMsg,(const void*)(buff + move),sizeof(netMsg.msgHead));
        move += sizeof(netMsg.msgHead);

        test_msg("netMsgInput\n");
        memcpy((void*)&netMsg.msgType,(const void*)(buff+move),sizeof(netMsg.msgType));
        move +=  sizeof(netMsg.msgType);

        test_msg("netMsgInput netMsg.msgType=%x,len=%d\n",netMsg.msgType,netMsg.msgHead.length);

        uint32_t datalen = netMsg.msgHead.length - 12;//map data length!
        //std::cout<<"test2:"<< buffLen <<std::endl;
        //netMsg.msgData.append((const char*)buff+move,buffLen-move);
        if ( datalen > 0 )
        {
            netMsg.msgData.append((const char*)buff+move, datalen);
            move += datalen;
        }

        test_msg("netMsgInput\n");

        MsgBase msgBase;
        test_msg("netMsgInput\n");
        msgBase.setMsgInfo(&msg);
        test_msg("netMsgInput\n");
        msgBase.setNetMsgBody(&netMsg);
        test_msg("netMsgInput\n");
       	msgBase.UnpackMsg(msg);


        test_msg("sendto model size=%d\n",m_model.size());
        for(map<uint32_t,CommModel*>::iterator it=m_model.begin();it!=m_model.end();it++)
        {
        	test_msg("sendto model %d\n",it->first);
            it->second->onMsgReq(&msg,connID);
        }
        test_msg("onMsgReq OK\n");

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
    sendBuff.reserve( sizeof (NetMsgHead) + sizeof(uint32_t) + netMsg.msgData.size() ) ;
    sendBuff.append((const char* )&netMsg,sizeof(NetMsgHead));
    sendBuff.append((const char* )&netMsg.msgType,sizeof(uint32_t));
    sendBuff.append((const char* )netMsg.msgData.c_str(),netMsg.msgData.size());

    showData( sendBuff.c_str() , true);

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
    m_model.insert(make_pair(modelType,pModel));
}



CommModel* MsgHandler::getModule( uint32_t type )
{
    std::map< uint32_t, CommModel* >::iterator it = m_model.find(type);
    if( it == m_model.end() )
    {
    	test_msg("can't find module instance. type=%u", type);
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
