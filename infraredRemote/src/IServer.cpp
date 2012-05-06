/*
 * IServer.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */


#include "IServer.h"
#include "msgHandler.h"


#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

IServer* IServer::m_instance = 0;


    IServer::IServer()
    :m_serverFlg(false)
     ,m_port(5000)
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


    //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
    //   struct epoll_event ev,events[20];

    //生成用于处理accept的epoll专用的文件描述符
    m_epfd=epoll_create(256);

    struct sockaddr_in servAddr;

    int listenfd=0;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenfd< 0)
    {
        perror("Invalid socket");
        return;
    }

    //把socket设置为非阻塞方式
    //setnonblocking(listenfd);

    //设置与要处理的事件相关的文件描述符
    m_ev.data.fd=listenfd;

    //设置要处理的事件类型
    m_ev.events=EPOLLIN|EPOLLET;
    //ev.events=EPOLLIN;

    //注册epoll事件
    epoll_ctl(m_epfd,EPOLL_CTL_ADD,listenfd,&m_ev);


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


    int  sockfd;
    char buff[MSG_MAX_LENGTH]={0};
    size_t buffLen;

    int maxi = 0;

    int nfds = 0;

    while(m_serverFlg)
    {
        //等待epoll事件的发生
        nfds=epoll_wait(m_epfd,m_events,20,500);

        //处理所发生的所有事件
        for(int i=0;i<nfds;++i)
        {
            if(m_events[i].data.fd==listenfd)//如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
            {
                int connfd;
                char cliIP[INET_ADDRSTRLEN]; // 用于保存客户端IP地址
                struct sockaddr_in clientAddr;
                size_t cliAddrLen = sizeof(clientAddr);

                connfd = accept(listenfd,(sockaddr *)&clientAddr, &cliAddrLen);
                if(connfd<0)
                {
                    close(connfd);
                    perror("connfd<0");
                    return ;
                }
                //setnonblocking(connfd);

                inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, cliIP, INET_ADDRSTRLEN);
                cout << "accapt a connection from: " << cliIP << endl;
                //设置用于读操作的文件描述符

                m_ev.data.fd=connfd;
                //设置用于注测的读操作事件

                m_ev.events=EPOLLIN|EPOLLET;
                //ev.events=EPOLLIN;

                //注册ev

                epoll_ctl(m_epfd,EPOLL_CTL_ADD,connfd,&m_ev);
            }


            else if(m_events[i].events&EPOLLIN)//如果是已经连接的用户，并且收到数据，那么进行读入。
            {
                cout << "EPOLLIN" << endl;
                if ( (sockfd =m_events[i].data.fd) < 0)
                    continue;


                if ( (buffLen = read(sockfd, buff, MSG_MAX_LENGTH)) < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        close(sockfd);
                        m_events[i].data.fd = -1;
                    }
                    else
                        std::cout<<"readline error"<<std::endl;
                }
                else if (buffLen == 0)
                {
                    close(sockfd);
                    m_events[i].data.fd = -1;
                }
                //buff[n] = '/0';
                //cout << "read " << buff << endl;

                m_pMsgHandler->netMsgInput((uint32_t)sockfd,buff,(uint32_t)buffLen);
                //设置用于写操作的文件描述符

                //    			m_ev.data.fd=sockfd;
                //                  //设置用于注测的写操作事件
                //                m_ev.events=EPOLLOUT|EPOLLET;
                //                  //修改sockfd上要处理的事件为EPOLLOUT
                //                epoll_ctl(m_epfd,EPOLL_CTL_MOD,sockfd,&m_ev);

            }
            else if(m_events[i].events&EPOLLOUT) // 如果有数据发送
            {

                int fd = m_events[i].data.fd;
                string & data = m_buff[fd].buff;
                uint32_t & len= m_buff[fd].buffLen ;
                write(fd,data.c_str(),len);
                //write(fd,m_buff[fd].buff.c_str(),m_buff[fd].buffLen);
                //设置用于读操作的文件描述符

                m_ev.data.fd=fd;
                //设置用于注测的读操作事件

                m_ev.events=EPOLLIN|EPOLLET;
                //修改sockfd上要处理的事件为EPOLIN

                epoll_ctl(m_epfd,EPOLL_CTL_MOD,sockfd,&m_ev);
                data.clear();
                len = 0;
            }
        }
    }

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

void IServer::SendNetMsg(int fd,char* buff,uint32_t buffLen)
{
    m_buff[fd].buff.append(buff,buffLen);
    m_buff[fd].buffLen += buffLen;
    //showData( m_buff[fd].buff.c_str(), true);
    m_ev.data.fd = fd;

    m_ev.events=EPOLLOUT|EPOLLET;
    //修改sockfd上要处理的事件为EPOLLOUT
    epoll_ctl(m_epfd,EPOLL_CTL_MOD,fd,&m_ev);

}


