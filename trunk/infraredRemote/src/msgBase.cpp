/*
 * msgBase.cpp
 *
 *  Created on: 2012-1-11
 *      Author: icecoffee
 */
#include "msgBase.h"
#include <iostream>
#include <sstream>
#include <string>


MsgBase::MsgBase()
:m_nMove(0)
,m_nMax(0)
{

}

MsgBase::~MsgBase()
{

}

//--------------------------------------------------------
// moduleInit
//--------------------------------------------------------
void  MsgBase::packMsg(NetMsgBody &netMsg)
{
	netMsg.msgType = m_pMsgInfo->msgType;

	push_u16((uint16_t)m_pMsgInfo->info.size());

	for(map<string,string>::const_iterator it = m_pMsgInfo->info.begin();it!= m_pMsgInfo->info.end();it++)
	{
		push_string(it->first);
		push_string(it->second);

	}

	netMsg.msgHead.length = netMsg.msgData.length() + HEAD_SIZE;

}


void MsgBase::UnpackMsg(MsgInfo &msgInfo)
{
	msgInfo.msgType = m_pNetMsgBody->msgType;

	uint16_t mapSize= pop_u16() ;

	for(uint16_t i=0;i<mapSize;i++)
	{
		string sKey = pop_string();
		string sValue = pop_string();
		msgInfo.info.insert(make_pair(sKey,sValue));
	}

}


void MsgBase::push_string(string data)
{
	uint16_t length = data.size();
	push_u16(length);
	m_pNetMsgBody->msgData.append(data.c_str(),length);

	m_nMove+=length;
	m_nMax+=length;


}


string MsgBase::pop_string()
{
	string data;
	uint16_t length=pop_u16();
	data.append(m_pNetMsgBody->msgData,m_nMove,length);

	m_nMove+=length;
	m_nMax-=length;

	return data;

}

void MsgBase::push_u16(uint16_t length)
{

	m_pNetMsgBody->msgData.append((const char *)&length, 2);

	m_nMove+=2;
	m_nMax+=2;


}


uint16_t MsgBase::pop_u16()
{
	uint16_t length = 0;
	string sString;
	sString.append(m_pNetMsgBody->msgData,m_nMove,2);


	uint16_t i16 = *((uint16_t*)&sString[0]);
	length = i16;

	m_nMove+=2;
	m_nMax-=2;

	return length;


}

void MsgBase::setMsgInfo(MsgInfo *pMsgInfo)
{
	m_pMsgInfo = pMsgInfo;
}


void MsgBase::setNetMsgBody(NetMsgBody *pNetMsgBody)
{
	m_pNetMsgBody =  pNetMsgBody;
	m_nMove = 0;
	m_nMax = pNetMsgBody->msgHead.length - HEAD_SIZE;

}













