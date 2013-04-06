/*
 * msgBase.h
 *
 *  Created on: 2012-1-11
 *      Author: icecoffee
 */

#ifndef MSGBASE_H_
#define MSGBASE_H_

#include <iostream>
#include <map>
#include <string>
#include <stdint.h>

using namespace std;

#define HEAD_SIZE 12

struct NetMsgHead
{
	uint32_t head;
	uint32_t length;
	uint32_t msgCtl;
	uint32_t reserved;

	NetMsgHead():head(0),length(0),msgCtl(0),reserved(0)
	{

		head = 0x6767dfef;
		length = 12;
	};

};

struct NetMsgBody
{
	NetMsgHead msgHead;
	uint32_t msgType;
	string msgData;

	NetMsgBody():msgType(0){};

};

struct MsgInfo
{
	uint32_t msgType;
	map<string,string>  info;
};


class MsgBase
{

public:
	MsgBase();
	virtual ~MsgBase();

	void packMsg(NetMsgBody &netMsg);
	void UnpackMsg(MsgInfo &msgInfo);

	void setMsgInfo(MsgInfo  *pMsgInfo);
	void setNetMsgBody(NetMsgBody  *pMsgInfo);

	void push_string(string data);
	string pop_string();
	void push_u16(uint16_t length);
	uint16_t pop_u16();


private:

	MsgInfo *m_pMsgInfo;
	NetMsgBody *m_pNetMsgBody;

	uint16_t m_nMove;
	uint16_t m_nMax;

};


#endif /* MSGBASE_H_ */
