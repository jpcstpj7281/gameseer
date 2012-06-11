/*
 * IServer.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef ISERVER_H_
#define ISERVER_H_

#include <iostream>
#include <map>

#include <sys/epoll.h>

#include "msgHandler.h"
using namespace std;


#define MSG_MAX_LENGTH 4*1024
//#define OPEN_MAX 100
#define MAX_CLIENT_ACCEPT 4
#define SERV_DEFINE_PORT 5000
//#define INFTIM 1000


struct NetMsg
{
	uint32_t buffLen;
	string buff;
};

class IServer
{

public:
	IServer();
	virtual ~IServer();

	static IServer* Instance();

	void setServerFlg(bool flg){m_serverFlg=flg;};
	void setPort(uint32_t port){m_port = port;};

	void Run();

	void SendNetMsg(int fd,char* buff,uint32_t buffLen);
	void setMsgHandler(MsgHandler *pMsgHandler){m_pMsgHandler = pMsgHandler;};

private:

	static IServer* m_instance;

	uint32_t  m_port;
	bool m_serverFlg;

	int m_fd[MAX_CLIENT_ACCEPT];

	int m_maxsock;
	int m_conn_amount;

	MsgHandler * m_pMsgHandler;
	map<uint32_t,NetMsg> m_buff;
};



#endif /* ISERVER_H_ */
