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

#ifndef __unix__
        case PDLPCTRLReq::uri:
            onPDLPCTRLReq(msg,connID);
            break;
#endif

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

    MsgHandler::Instance()->broadcastMsg(&rsp);

}

void Event::mifImportanceEvent(uint32_t eventId)
{
    cout<<"mifImportanceEvent"<<" eventId="<<eventId <<endl;

    MsgInfo rsp;

    rsp.msgType = PImportanceEventUpLoadReq::uri;
    rsp.info["event"] = tostring(eventId);
    rsp.info["desc"] = EntSetting::Instance()->getSysIp();

    MsgHandler::Instance()->broadcastMsg(&rsp);

}
#ifndef __unix__
   void Event::onPDLPCTRLReq(MsgInfo *msg,uint32_t connID)
   {
   cout<<"onPDLPCTRLReq"<<" connID="<<connID <<endl;

   uint8_t dwAddr;
   uint8_t dwCount;
   uint8_t byDate[128] = {0};

   dwAddr = atoi(msg->info["addr"].c_str());
   dwCount = atoi(msg->info["len"].c_str());

   cout<<"Date="<<msg->info["value"].c_str() <<endl;

   DLPI2c(dwAddr,dwCount,(uint8_t*)msg->info["value"].c_str());

   MsgInfo rsp;

   rsp.msgType = PDLPCTRLRsp::uri;


   rsp.info["result"] = tostring(0);
   MsgHandler::Instance()->broadcastMsg(&rsp);

   }

#endif


