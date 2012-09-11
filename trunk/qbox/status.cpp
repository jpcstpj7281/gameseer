/*
 * status.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "status.h"
#include "protocol/protocol.h"
#include "msgHandler.h"
#include "toString.h"
#include "entSetting.h"

#include "common.h"

using namespace msg;
using namespace ent;

Status::Status()
{

}

Status::~Status()
{

}


uint32_t Status::onMsgReq(MsgInfo *msg,uint32_t connID)
{

//	test_msg("m_model connID=%d,msgType=%d\n",connID,msg->msgType);
    switch(msg->msgType)
    {
        case PProtocolVersionReq::uri:
            onProtocolVersionReq(msg,connID);
            break;

        case PGetInPutReq::uri:
            onGetInPutReq(msg,connID);
            break;

        case PGetOutPutReq::uri:
            onGetOutPutReq(msg,connID);
            break;

        case PGetInPutSizeReq::uri:
            onGetInPutSizeReq(msg,connID);
            break;

        case PGetOutPutSizeReq::uri:
            onGetOutPutSizeReq(msg,connID);
            break;

        default:
            //cout<<"URI UNKOWN!"<<" msg->msgType="<<msg->msgType <<endl;

        	break;


    }

    return 0;
}

void Status::onProtocolVersionReq(MsgInfo *msg,uint32_t connID)
{
	test_msg("onProtocolVersionReq connID=%d\n",connID);

    MsgInfo rsp;
    rsp.msgType = PProtocolVersionRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
    rsp.info["protocol"] = EntSetting::Instance()->getVersion();



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Status::onGetInPutReq(MsgInfo *msg,uint32_t connID)
{
	test_msg("onGetInPutReq connID=%d\n",connID);


    MsgInfo rsp;

    rsp.msgType = PGetInPutRsp::uri;
    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    uint32_t iTotal = EntSetting::Instance()->getInputTotal();

    rsp.info["in0"] = EntSetting::Instance()->getInputInfoType(0);
    rsp.info["in1"] = EntSetting::Instance()->getInputInfoType(1);
    rsp.info["in2"] = EntSetting::Instance()->getInputInfoType(2);
    rsp.info["in3"] = EntSetting::Instance()->getInputInfoType(3);
    rsp.info["in4"] = EntSetting::Instance()->getInputInfoType(4);
    rsp.info["in5"] = EntSetting::Instance()->getInputInfoType(5);
    if ( iTotal == 0 ) iTotal = 6;
    rsp.info["total"] = tostring(iTotal);

    test_msg("onGetInPutReq Done\n",connID);
    MsgHandler::Instance()->sendMsg(connID,&rsp);

}


void Status::onGetOutPutReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onGetOutPutReq"<<" connID="<<connID <<endl;

    MsgInfo rsp;

    rsp.msgType = PGetOutPutRsp::uri;
    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    uint32_t iTotal = EntSetting::Instance()->getOutputTotal();

    rsp.info["out0"] = EntSetting::Instance()->getOutputInfoType(0);
    rsp.info["out1"] = EntSetting::Instance()->getOutputInfoType(1);
    rsp.info["out2"] = EntSetting::Instance()->getOutputInfoType(2);
    if ( iTotal == 0 ) iTotal = 3;
    rsp.info["total"] = tostring(iTotal);


    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Status::onGetInPutSizeReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onGetInPutSizeReq"<<" connID="<<connID << "in="<<atoi(msg->info["in"].c_str()) <<endl;

    string a;


    MsgInfo rsp;
    rsp.msgType = PGetInPutSizeRsp::uri;
    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
    rsp.info["in"] = msg->info["in"];
    rsp.info["w"] = tostring(1024);
    rsp.info["h"] = tostring(768);


    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Status::onGetOutPutSizeReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onUserLogin"<<" connID="<<connID <<"out="<<atoi(msg->info["out"].c_str()) <<endl;

    MsgInfo rsp;

    rsp.msgType = PGetOutPutSizeRsp::uri;
    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    rsp.info["out"] = msg->info["out"];
    rsp.info["w"] = tostring(1024);
    rsp.info["h"] = tostring(768);

    MsgHandler::Instance()->sendMsg(connID,&rsp);

}



