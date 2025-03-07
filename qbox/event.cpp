/*
 * event.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "event.h"
#include "protocol/protocol.h"
#include "msgHandler.h"
#include "toString.h"
#include "entSetting.h"

#include "common.h"

using namespace msg;
using namespace ent;

Event::Event()
{

}

Event::~Event()
{

}


uint32_t Event::onMsgReq(MsgInfo *msg,uint32_t connID)
{

    switch(msg->msgType)
    {
        case PCommonEventUpLoadRsp::uri:
            onPCommonEventUpLoadRsp(msg,connID);
            break;

        case PImportanceEventUpLoadRsp::uri:
        	onPImportanceEventUpLoadRsp(msg,connID);
            break;

        case PDLPCTRLReq::uri:
            onPDLPCTRLReq(msg,connID);
            break;

        case PDLPReadReq::uri:
        	onPDLPReadReq(msg,connID);
        	break;


        default:
            //cout<<"URI UNKOWN!"<<" msg->msgType="<<msg->msgType <<endl;
            break;


    }

    return 0;
}

void Event::onPCommonEventUpLoadRsp(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPCommonEventUpLoadRsp"<<" connID="<<connID <<endl;


}

void Event::onPImportanceEventUpLoadRsp(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPImportanceEventUpLoadRsp"<<" connID="<<connID <<endl;

}


void Event::mifCommonEvent(uint32_t eventId)
{
    cout<<"PCommonEventUpLoadReq"<<" eventId="<<eventId <<endl;

    MsgInfo rsp;

    rsp.msgType = PCommonEventUpLoadReq::uri;
    rsp.info["event"] = tostring(eventId);
    rsp.info["desc"] = EntSetting::Instance()->getSysIp();

//    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Event::mifImportanceEvent(uint32_t eventId)
{
    cout<<"mifImportanceEvent"<<" eventId="<<eventId <<endl;


    MsgInfo rsp;

    rsp.msgType = PImportanceEventUpLoadReq::uri;
    rsp.info["event"] = tostring(eventId);
    rsp.info["desc"] = EntSetting::Instance()->getSysIp();

//    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Event::onPDLPCTRLReq(MsgInfo *msg,uint32_t connID)
{

   test_msg("onPDLPCTRLReq  connID=%d",connID );

   uint8_t dwAddr;
   uint8_t dwCount;
   uint8_t byDate[128] = {0};

   dwAddr = atoi(msg->info["addr"].c_str());
   dwCount = atoi(msg->info["len"].c_str());

//   test_msg("addr = %02X",dwAddr );
//   test_msg("dwCount = %d",dwCount );

#ifndef __unix__
   DLPI2c(dwAddr,dwCount,(uint8_t*)msg->info["value"].c_str());
#endif

   MsgInfo rsp;

   rsp.msgType = PDLPCTRLRsp::uri;


   rsp.info["error"] = tostring(0);


   test_msg("rsp  =%x",rsp.msgType );


   MsgHandler::Instance()->sendMsg(connID,&rsp);

 }


 void Event::onPDLPReadReq(MsgInfo *msg,uint32_t connID)
 {
   test_msg("onPDLPReadReq  connID=%d",connID );

   uint8_t dwAddr;
   uint8_t dwCount;
   uint8_t type;
   uint8_t byDate[128] = {0};

   type = atoi(msg->info["device"].c_str());
   dwAddr = atoi(msg->info["addr"].c_str());
   dwCount = atoi(msg->info["len"].c_str());
   test_msg("addr:0x%x,len:%d\n", dwAddr,dwCount);

   DLPI2cR(type,dwAddr,dwCount,(uint8_t*)&byDate[0]);

   MsgInfo rsp;
   rsp.msgType = PDLPReadRsp::uri;
   rsp.info["data"].append((const char *)&byDate[0],dwCount) ;
   rsp.info["len"] = tostring(dwCount);

   rsp.info["error"] = tostring(0);

   MsgHandler::Instance()->sendMsg(connID,&rsp);
  }



