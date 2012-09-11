/*
 * IServer.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */


#include "IServer.h"
#include "msgHandler.h"


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


//void IServer::Run()
//{
//	char buf[MSG_MAX_LENGTH];
//
//    struct sockaddr_in servAddr;
//
//    int listenfd=0;
//
//    bool bReuseaddr = true;
//
//    test_msg("Run Server\n");
//    listenfd = socket(AF_INET, SOCK_STREAM, 0);
//
//    if(listenfd< 0)
//    {
//    	perror("Invalid socket");
//    	return;
//    }
//
////    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &bReuseaddr, sizeof(bool)) == -1) {
////         perror("setsockopt");
////         exit(1);
////     }
//
//
////    bzero(&servAddr, sizeof(servAddr)); // 初始化服务器地址
//    memset(&servAddr,0,sizeof(servAddr));
//    servAddr.sin_family = AF_INET;
//    servAddr.sin_port = htons(m_port);
//    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//
//    test_msg("Binding server to port=%d!\n",m_port);
//
//    if(bind(listenfd, (struct sockaddr*)&servAddr, sizeof(struct sockaddr)) != 0)
//    {
//    	close(listenfd);
//    	perror("binding err!");
//    	return;
//    }
//
//
//    if(listen(listenfd, MAX_CLIENT_ACCEPT) != 0)
//    {
//    	close(listenfd);
//    	perror("listen err!");
//    	return;
//    }
//
//    test_msg("waiting client...\n");
//
//    fd_set fdsr;
//
//
//    char buff[MSG_MAX_LENGTH]={0};
//    size_t buffLen;
//
//
//    int nfds = 0;
//
//    struct timeval tv;
//
//    m_maxsock = listenfd;
//
//    test_msg("while enter...m_maxsock=%d\n",m_maxsock);
//    while(m_serverFlg)
//    {
//        FD_ZERO(&fdsr);
//        FD_SET(listenfd, &fdsr);
//
//
//         // timeout setting
//         tv.tv_sec = 0;
//         tv.tv_usec = 500000;
//
//         test_msg("while 0...\n");
//         // add active connection to fd set
//         for (int i = 0; i < MAX_CLIENT_ACCEPT; i++)
//         {
//             if (m_fd[i] != 0)
//             {
//                 FD_SET(m_fd[i], &fdsr);
//             }
//         }
//
//         test_msg("while select...\n");
//         int ret;
//         ret = select(m_maxsock + 1, &fdsr, NULL, NULL, &tv);
//         if (ret < 0)
//         {
//             perror("select");
//             break;
//         }
//         else if (ret == 0)
//         {
//        	 test_msg("select timeout\n");
//             continue;
//         }
//
//
//         test_msg("while 1...\n");
//         // check every fd in the set
//         for (int i = 0; i < m_conn_amount; i++)
//         {
//             if (FD_ISSET(m_fd[i], &fdsr))
//             {
//            	 buffLen = recv(m_fd[i], buf, sizeof(buf), 0);
//                 if (buffLen <= 0)
//                 {        // client close
//                     printf("client[%d] close\n", i);
//                     close(m_fd[i]);
//                     FD_CLR(m_fd[i], &fdsr);
//                     m_fd[i] = 0;
//                 }
//                 else
//                 {  // receive data
//                	 if (buffLen < MSG_MAX_LENGTH)
//                	 {
//                		 memset(&buf[buffLen], '\0', 1);
//                	 }
//                	 test_msg("client[%d] send:%s\n", i, buf);
//                	 if(m_pMsgHandler == NULL)
//                	 {
//                		 test_msg("ERROR m_pMsgHandler NOT INIT\n");
//
//                	 }
//                	 else
//                	 {
//                		 m_pMsgHandler->netMsgInput((uint32_t)i,buf,(uint32_t)buffLen);
//                	 }
//                 }
//             }
//         }
//
//         test_msg("while 2...\n");
//
//         // check whether a new connection comes
//          if (FD_ISSET(listenfd, &fdsr))
//          {
//        	  int connfd;
//        	  char cliIP[16]; // 用于保存客户端IP地址
//        	  struct sockaddr_in clientAddr;
//        	  int cliAddrLen = sizeof(clientAddr);
//
//        	  connfd = accept(listenfd,(sockaddr *)&clientAddr, &cliAddrLen);
//              if (connfd <= 0)
//              {
//                  perror("accept");
//                  continue;
//              }
//
//              // add to fd queue
//              if (m_conn_amount < MAX_CLIENT_ACCEPT)
//              {
//            	  m_fd[m_conn_amount++] = connfd;
//            	  test_msg("new connection client[%d] %s:%d\n", m_conn_amount,inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
//                  if (connfd > m_maxsock)
//                  {
//                	  m_maxsock = connfd;
//                  }
//              }
//              else
//              {
//            	  test_msg ("max connections arrive, exit\n");
//                  send(connfd, "bye", 4, 0);
//                  close(connfd);
//                  continue;
//              }
//          }
//
//
//          taskDelay(10);
//
//    }
//
//    // close other connections
//    for (int i = 0; i < MAX_CLIENT_ACCEPT; i++)
//    {
//        if (m_fd[i] != 0)
//        {
//            close(m_fd[i]);
//        }
//    }
//
//
//
//
//}


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
			test_msg("new connection client[%d] %s:%d\n", m_conn_amount,inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
			m_server = sd;
			m_fd[sd] = sd;
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
#ifndef __unix__
            //TODO::semTake有锁太长时间的问题
            semTake(Server_SM, WAIT_FOREVER);
#endif
            memset(buffer,0,sizeof(buffer));
            rc = recv(sock,buffer, 8, MSG_PEEK);
            int len = 0;
            if ( rc > 0){
                memcpy((void*)&len,(const void*)(buffer+4),4);
//                test_msg("RecvMsg len:%d\n",len);
            }
            if ( len <12 ) break;
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
#ifndef __unix__
                semGive(Server_SM);
#endif
            }
            else
            {
                test_msg("Socket closed\n");
                close(sock);
                m_server = 0;
                m_fd[sock] = 0;
#ifndef __unix__
                semGive(Server_SM);
#endif
                break;
            }
        }
#ifndef __unix__
        taskDelay(10);
#endif
    }

}


