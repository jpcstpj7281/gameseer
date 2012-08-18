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




