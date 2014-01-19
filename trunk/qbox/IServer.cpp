

/*
 * IServer.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */


#include "IServer.h"
#include "msgHandler.h"
#include "entSetting.h"


//#include "fioLib.h"
//#include "stdio.h"
//#include "string.h"
//#include "usrLib.h"
//#include "errnoLib.h"
//#include "hostLib.h"
#ifndef __unix__
#include "socket.h"
#else
#include <sys/socket.h>
#endif
//#include "inetLib.h"
//#include "in.h"
//#include "assert.h"
#include "netinet/tcp.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "common.h"

using namespace ent;

IServer* IServer::m_instance = 0;
#ifndef __unix__
SEM_ID Server_SM;
#endif

IServer::IServer()
:m_serverFlg(false)
,m_port(5000)
,m_conn_amount(0)
,m_pMsgHandler(NULL)
{
}

IServer::~IServer()
{

}

IServer* IServer::Instance()
{
	if(m_instance == NULL)
	{
		m_instance = new IServer();
	}
	return m_instance;
}




void IServer::SendNetMsg(int fd,char* buff,uint32_t buffLen)
{
//	test_msg("sock:%d,buffLen=%d",fd,buffLen);
	send(fd,buff,buffLen,0);
//    m_buff[fd].buff.assign(buff,buffLen);
//    m_buff[fd].buffLen = buffLen;
//
//    if(m_fd[fd] > 0)
//    {
//        //write(m_fd[fd],m_buff[fd].buff.c_str(),m_buff[fd].buffLen);
//    	send(m_fd[fd],m_buff[fd].buff.c_str(),m_buff[fd].buffLen,0);
//    }
//    else
//    {
//        printf("Send error socket %d Error!",m_fd[fd]);
//    }
}





void IServer::BroadcastMsg(char* buff,uint32_t buffLen)
{
    for(int i=0;i<MAX_CLIENT_ACCEPT;i++)
    {
        if(m_fd[i] >0)
        {
            m_buff[i].buff.append(buff,buffLen);
            m_buff[i].buffLen = buffLen;

            //write(m_fd[i],m_buff[i].buff.c_str(),m_buff[i].buffLen);
            send(m_fd[i],m_buff[i].buff.c_str(),m_buff[i].buffLen,0);

        }
    }
}

int IServer::Server()
{
    int rc = 0,sd = 0;
    int addr_len = 0;
    int server_sock = 0;
    struct sockaddr_in server_addr,client_addr;

    memset(&server_addr,0,sizeof(struct sockaddr_in));
    memset(&client_addr,0,sizeof(struct sockaddr_in));
    server_sock = socket(AF_INET,SOCK_STREAM,0);
    if(server_sock < 0)
    {
    	test_msg("Failed to create Socket.\n");
        return 0;
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(m_port);
    rc = bind(server_sock,(struct sockaddr *)&server_addr,sizeof(struct sockaddr_in));
    if(rc == -1)
    {
		close(server_sock);
		test_msg("Failed to bind socket\n");
		return 0;
    }
    rc = listen(server_sock,2);
    if(rc == -1)
    {
    	test_msg("socket listen error\n");
		return 0;
    }
    test_msg("TCP server is ready for receive connection request IP:%s Port:%d\n",inet_ntoa(server_addr.sin_addr),m_port);

    while(1)
    {
        addr_len = sizeof(struct sockaddr_in);
        sd = accept(server_sock,(struct sockaddr *)&client_addr,&addr_len);
		if(sd <= 0)
		{
			test_msg("socket accept error\n");
			return 0;
		}
		else
		{
			EntSetting::Instance()->setConnectFlg(true);
			test_msg("new connection client[%d] %s:%d\n", m_conn_amount,inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			m_server = sd;

			m_fd[sd%MAX_CLIENT_ACCEPT] = sd;
			server_proc(sd);
		}
    }

    return 0;
}

void IServer::server_proc(int sock)
{
    int rc = 0;
    char buffer[1024];
    fd_set socket;
    struct timeval wait;

    wait.tv_sec = 0;
    wait.tv_usec = 500000;

    while(m_server > 0)
    {
        FD_ZERO(&socket);
        FD_SET(sock,&socket);

        rc = select(FD_SETSIZE,&socket,(fd_set *)0,(fd_set *)0,&wait);
        if(rc == 0)
            continue;
        if(FD_ISSET(sock,&socket))
        {
            //TODO::semTake有锁太长时间的问题
            semTake(Server_SM, WAIT_FOREVER);

            memset(buffer,0,sizeof(buffer));
            rc = recv(sock,buffer, 8, MSG_PEEK);
            int len = 0;
            if ( rc > 0){
                memcpy((void*)&len,(const void*)(buffer+4),4);
//                test_msg("RecvMsg len:%d\n",len);
            }
            if ( len <12 )
            {
            	semGive(Server_SM);
            	m_server = 0;
            	m_fd[sock] = 0;
            	close(sock);
            	EntSetting::Instance()->setConnectFlg(false);
            	break;
            }
            rc = recv(sock,buffer,len+8,0);
            if(rc > 0)
            {
                /* you can add your application specific code here */
//                test_msg("RecvMsg:%s\n",buffer);
                if(m_pMsgHandler == NULL)
                {
                    test_msg("ERROR m_pMsgHandler NOT INIT\n");
                }
                else
                {
                    m_pMsgHandler->netMsgInput((uint32_t)sock,buffer,(uint32_t)rc);
                }

               semGive(Server_SM);

            }
            else
            {
                test_msg("Socket closed\n");
                close(sock);
                m_server = 0;
                m_fd[sock] = 0;
                semGive(Server_SM);
                EntSetting::Instance()->setConnectFlg(false);
                break;
            }
        }

        taskDelay(10);

    }

}




