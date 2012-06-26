/*
 * IServer.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */


#include "IServer.h"
#include "msgHandler.h"


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

IServer* IServer::m_instance = 0;


IServer::IServer()
:m_serverFlg(false)
,m_port(5000)
,m_conn_amount(0)
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


void IServer::Run()
{
	char buf[MSG_MAX_LENGTH];

    struct sockaddr_in servAddr;

    int listenfd=0;

    bool bReuseaddr = true;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenfd< 0)
    {
    	perror("Invalid socket");
    	return;
    }

//    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &bReuseaddr, sizeof(bool)) == -1) {
//         perror("setsockopt");
//         exit(1);
//     }


    bzero(&servAddr, sizeof(servAddr)); // 初始化服务器地址
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(m_port);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    cout<<"Binding server to port=" <<m_port<<"!"<<endl;

    if(bind(listenfd, (struct sockaddr*)&servAddr, sizeof(struct sockaddr)) != 0)
    {
    	close(listenfd);
    	perror("binding err!");
    	return;
    }


    if(listen(listenfd, MAX_CLIENT_ACCEPT) != 0)
    {
    	close(listenfd);
    	perror("listen err!");
    	return;
    }

    cout<<"waiting client..."<<endl;

    fd_set fdsr;


    char buff[MSG_MAX_LENGTH]={0};
    size_t buffLen;


    int nfds = 0;

    struct timeval tv;

    m_maxsock = listenfd;

    while(m_serverFlg)
    {
        FD_ZERO(&fdsr);
        FD_SET(listenfd, &fdsr);


         // timeout setting
         tv.tv_sec = 30;
         tv.tv_usec = 0;


         // add active connection to fd set
         for (int i = 0; i < MAX_CLIENT_ACCEPT; i++)
         {
             if (m_fd[i] != 0)
             {
                 FD_SET(m_fd[i], &fdsr);
             }
         }

         int ret;
         ret = select(m_maxsock + 1, &fdsr, NULL, NULL, &tv);
         if (ret < 0)
         {
             perror("select");
             break;
         }
         else if (ret == 0)
         {
//             printf("timeout\n");
             continue;
         }



         // check every fd in the set
         for (int i = 0; i < m_conn_amount; i++)
         {
             if (FD_ISSET(m_fd[i], &fdsr))
             {
            	 buffLen = recv(m_fd[i], buf, sizeof(buf), 0);
                 if (buffLen <= 0)
                 {        // client close
                     printf("client[%d] close\n", i);
                     close(m_fd[i]);
                     FD_CLR(m_fd[i], &fdsr);
                     m_fd[i] = 0;
                 }
                 else
                 {  // receive data
                	 if (buffLen < MSG_MAX_LENGTH)
                	 {
                		 memset(&buf[buffLen], '\0', 1);
                	 }
                     printf("client[%d] send:%s\n", i, buf);
                     m_pMsgHandler->netMsgInput((uint32_t)i,buf,(uint32_t)buffLen);
                 }
             }
         }

         // check whether a new connection comes
          if (FD_ISSET(listenfd, &fdsr))
          {
        	  int connfd;
        	  char cliIP[INET_ADDRSTRLEN]; // 用于保存客户端IP地址
        	  struct sockaddr_in clientAddr;
        	  size_t cliAddrLen = sizeof(clientAddr);

        	  connfd = accept(listenfd,(sockaddr *)&clientAddr, (socklen_t*)&cliAddrLen);
              if (connfd <= 0)
              {
                  perror("accept");
                  continue;
              }

              // add to fd queue
              if (m_conn_amount < MAX_CLIENT_ACCEPT)
              {
            	  m_fd[m_conn_amount++] = connfd;
                  printf("new connection client[%d] %s:%d\n", m_conn_amount,inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
                  if (connfd > m_maxsock)
                  {
                	  m_maxsock = connfd;
                  }
              }
              else
              {
                  printf("max connections arrive, exit\n");
                  send(connfd, "bye", 4, 0);
                  close(connfd);
                  continue;
              }
          }

    }

    // close other connections
    for (int i = 0; i < MAX_CLIENT_ACCEPT; i++)
    {
        if (m_fd[i] != 0)
        {
            close(m_fd[i]);
        }
    }




}


void IServer::SendNetMsg(int fd,char* buff,uint32_t buffLen)
{
	m_buff[fd].buff.append(buff,buffLen);
	m_buff[fd].buffLen = buffLen;

	if(m_fd[fd] > 0)
	{
		write(m_fd[fd],m_buff[fd].buff.c_str(),m_buff[fd].buffLen);
	}
	else
	{
		printf("Send error socket %d Error!",m_fd[fd]);
	}
}

void IServer::BroadcastMsg(char* buff,uint32_t buffLen)
{
	for(int i=0;i<MAX_CLIENT_ACCEPT;i++)
	{
		if(m_fd[i] >0)
		{
			m_buff[i].buff.append(buff,buffLen);
			m_buff[i].buffLen = buffLen;

			write(m_fd[i],m_buff[i].buff.c_str(),m_buff[i].buffLen);

		}
	}
}


