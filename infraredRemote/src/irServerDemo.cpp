#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

using namespace std;

#define MSG_MAX_LENGTH 4*1024
//#define OPEN_MAX 100
#define MAX_CLIENT_ACCEPT 64
#define SERV_DEFINE_PORT 5000
//#define INFTIM 1000

void setnonblocking(int sock)
{
    int opts;
    opts=fcntl(sock,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        exit(1);
    }
    opts = opts|O_NONBLOCK;
    if(fcntl(sock,F_SETFL,opts)<0)
    {
        perror("fcntl(sock,SETFL,opts)");
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    int i, maxi, listenfd,epfd,nfds, port;
    ssize_t n;

    socklen_t clilen;


    if ( 2 == argc )
    {
        if( (port = atoi(argv[1])) < 0 )
        {
            fprintf(stderr,"Usage:%s port/a/n",argv[0]);
            return 1;
        }
    }
    else
    {
        fprintf(stderr,"Usage:%s port/a/n",argv[0]);
        return 1;
    }



    //声明epoll_event结构体的变量,ev用于注册事件,数组用于回传要处理的事件
    struct epoll_event ev,events[20];

    //生成用于处理accept的epoll专用的文件描述符
    epfd=epoll_create(256);

    struct sockaddr_in servAddr;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenfd< 0)
    {
    	perror("Invalid socket");
    	exit(1);
    }


    //把socket设置为非阻塞方式
    //setnonblocking(listenfd);

    //设置与要处理的事件相关的文件描述符
    ev.data.fd=listenfd;

    //设置要处理的事件类型
    ev.events=EPOLLIN|EPOLLET;
    //ev.events=EPOLLIN;

    //注册epoll事件
    epoll_ctl(epfd,EPOLL_CTL_ADD,listenfd,&ev);


    bzero(&servAddr, sizeof(servAddr)); // 初始化服务器地址
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    cout<<"Binding server to port=" <<port<<"!"<<endl;

    if(bind(listenfd, (struct sockaddr*)&servAddr, sizeof(struct sockaddr)) != 0)
    {
    	close(listenfd);
        perror("binding err!");
        exit(1);
    }


    if(listen(listenfd, MAX_CLIENT_ACCEPT) != 0)
    {
    	close(listenfd);
        perror("listen err!");
        exit(1);
    }

    cout<<"waiting client..."<<endl;


    int  sockfd;
    char buff[MSG_MAX_LENGTH]={0};
    size_t buffLen;

    maxi = 0;
    while(1)
    {
        //等待epoll事件的发生
        nfds=epoll_wait(epfd,events,20,500);

        //处理所发生的所有事件
        for(i=0;i<nfds;++i)
        {
            if(events[i].data.fd==listenfd)//如果新监测到一个SOCKET用户连接到了绑定的SOCKET端口，建立新的连接。
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
                    exit(1);
                }
                //setnonblocking(connfd);

                inet_ntop(AF_INET, &clientAddr.sin_addr.s_addr, cliIP, INET_ADDRSTRLEN);
                cout << "accapt a connection from: " << cliIP << endl;
                //设置用于读操作的文件描述符

                ev.data.fd=connfd;
                //设置用于注测的读操作事件

                ev.events=EPOLLIN|EPOLLET;
                //ev.events=EPOLLIN;

                //注册ev

                epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&ev);
            }


            else if(events[i].events&EPOLLIN)//如果是已经连接的用户，并且收到数据，那么进行读入。

            {

                cout << "EPOLLIN" << endl;
                if ( (sockfd = events[i].data.fd) < 0)
                    continue;


                if ( (buffLen = read(sockfd, buff, MSG_MAX_LENGTH)) < 0)
                {
                    if (errno == ECONNRESET)
                    {
                        close(sockfd);
                        events[i].data.fd = -1;
                    }
                    else
                        std::cout<<"readline error"<<std::endl;
                }
                else if (buffLen == 0)
                {
                    close(sockfd);
                    events[i].data.fd = -1;
                }
                //buff[n] = '/0';
                cout << "read " << buff << endl;
                //设置用于写操作的文件描述符

                ev.data.fd=sockfd;
                //设置用于注测的写操作事件

                ev.events=EPOLLOUT|EPOLLET;
                //修改sockfd上要处理的事件为EPOLLOUT

                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);

            }
            else if(events[i].events&EPOLLOUT) // 如果有数据发送

            {

                sockfd = events[i].data.fd;
                write(sockfd, buff, buffLen);
                //设置用于读操作的文件描述符

                ev.data.fd=sockfd;
                //设置用于注测的读操作事件

                ev.events=EPOLLIN|EPOLLET;
                //修改sockfd上要处理的事件为EPOLIN

                epoll_ctl(epfd,EPOLL_CTL_MOD,sockfd,&ev);
            }
        }
    }
    return 0;
}
