/*
 * main.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */
#ifndef __unix__
#include <vxworks.h>
#include <taskLib.h>
#endif

#include <stdlib.h>
#include "IServer.h"
#include "msgHandler.h"
#include "status.h"
#include "windows.h"
#include "event.h"
#include "channel.h"
#include "common.h"

#include "vxWorks.h"
#include "stdio.h"
#include "netinet/in.h"
#include "net/if.h"
#include "netinet/if_ether.h"
#include "sys/ioctl.h"
#include "ioLib.h"
#include "inetLib.h"
#include "string.h"
#include "netinet/in_var.h"
#include "ipProto.h"
#include "end.h"
#include "private/muxLibP.h"
extern struct in_ifaddr* in_ifaddr;

#ifdef __cplusplus
    extern "C"{

using namespace msg;




int
getmac()
{
  struct in_ifaddr* ia;
  for (ia = in_ifaddr; ia != 0; ia = ia->ia_next)
    {
      struct ifnet* ifp = ia->ia_ifa.ifa_ifp;
      if (ifp != 0)
        {
          int level;
          IP_DRV_CTRL *pDrvCtrl;
          END_OBJ *pEnd;
          char PhyAddr[10];

          if(ifp->if_type != M2_ifType_ethernetCsmacd)
            {
               continue;
            }
          //level = intLock();

          pDrvCtrl = (IP_DRV_CTRL *)ifp->pCookie;

          pEnd = PCOOKIE_TO_ENDOBJ(pDrvCtrl->pIpCookie);

          pEnd->pFuncTable->ioctl(pEnd, EIOCGADDR, PhyAddr);
          printf("%x:%x:%x:%x:%x:%x\n", PhyAddr[0], PhyAddr[1], PhyAddr[2], PhyAddr[3], PhyAddr[4], PhyAddr[5]);

         // intUnlock(level);
        }
    }
}

void testMenu()
{
	cout<<"1: runServer  Para[Port]"<<endl;

	return ;
}



//void runService(int port)
//{
//	Status status;
//	Windows windows;
//	Event evt;
//	Channel channel;
//
//	MsgHandler::Instance()->setModel(TYPE_MODEL_STATUS,(CommModel*)(&status));
//	MsgHandler::Instance()->setModel(TYPE_MODEL_WINDOWS,(CommModel*)(&windows));
//	MsgHandler::Instance()->setModel(TYPE_MODEL_EVENT,(CommModel*)(&windows));
//	MsgHandler::Instance()->setModel(TYPE_MODEL_CHANNEL,(CommModel*)(&windows));
//
//	IServer::Instance()->setPort(port);
//	IServer::Instance()->setServerFlg(true);
//
//	IServer::Instance()->setMsgHandler(MsgHandler::Instance());
//
//
//	IServer::Instance()->Run();
//}

void runServer(int port)
{
	Status status;
	Windows windows;
	Event evt;
	Channel channel;



	MsgHandler::Instance()->setModel(TYPE_MODEL_STATUS,(CommModel*)(&status));
	MsgHandler::Instance()->setModel(TYPE_MODEL_WINDOWS,(CommModel*)(&windows));
	MsgHandler::Instance()->setModel(TYPE_MODEL_EVENT,(CommModel*)(&evt));
	MsgHandler::Instance()->setModel(TYPE_MODEL_CHANNEL,(CommModel*)(&channel));

	MsgHandler::Instance()->getModule(TYPE_MODEL_STATUS);
	MsgHandler::Instance()->getModule(TYPE_MODEL_WINDOWS);
	MsgHandler::Instance()->getModule(TYPE_MODEL_EVENT);
	MsgHandler::Instance()->getModule(TYPE_MODEL_CHANNEL);



	IServer::Instance()->setPort(port);


#ifndef __unix__
	taskDelay(100);
	initOutputModel(TYPE_MODEL_1024_768);
#else
#endif

	IServer::Instance()->setMsgHandler(MsgHandler::Instance());
	IServer::Instance()->Server();



}

#ifndef __unix__
void enterApp()
{
	int ret = 0;
	ret = taskSpawn("tServer", 165, 0x0002, 16*1024,(FUNCPTR) runServer,5000,0,0,0,0,0,0,0,0,0);

}
#endif






int main(int argc,char*argv[])
{
#ifdef __unix__
    cout<<"unix!"<<endl;
#else
    cout<<"vxWork!"<<endl;
#endif

    cout<<"run test  0 for help!"<<endl;

    int para0 = 0;
    int para1 = 0;

    if(argc == 2)
    {
        para0 = atoi( argv[1]);

    }
    else if(argc == 3)
    {
        para0 = atoi( argv[1]);
        para1 = atoi( argv[2]);
    }
    else
    {
        cout<<"please enter  para!"<<endl;
        return 0;
    }

    switch(para0)
    {
        case 0:
            testMenu();
            break;

        case 1:
            runServer(para1);
            break;



        default:
            cout<<"Unkonw enter  para!"<<endl;
            return 0;

    }

    return 0;
}


}
#endif /* __cplusplus */


