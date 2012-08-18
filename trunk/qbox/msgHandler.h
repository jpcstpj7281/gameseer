/*
 * msgHandler.h
 *
 *  Created on: 2012-1-10
 *      Author: icecoffee
 */

#ifndef MSGHANDLER_H_
#define MSGHANDLER_H_

#include "msgCommon.h"
//#include <stdint.h>
#include "msgBase.h"
#include "commModel.h"
#include "common.h"

class MsgHandler
{

public:
	MsgHandler();
	virtual ~MsgHandler();

	static MsgHandler* m_instance;
	static MsgHandler* Instance();

//	virtual uint32_t onMsgReq(MsgBase *msg,uint32_t connID) = 0;

//	void setServer(IServer server){m_pServer = &server;};

	bool sendMsg(uint32_t connID,MsgInfo *pMsg);
	bool broadcastMsg(MsgInfo *pMsg);

	void netMsgInput(uint32_t connID,char* buff,uint32_t buffLen);
	void setModel(uint32_t modelType,CommModel *pModel);
	CommModel* getModule( uint32_t type );

protected:

	uint32_t m_type;
private:

//	IServer *m_pServer;

	map<uint32_t,CommModel*> m_model;


};


#endif /* MSGHANDLER_H_ */
