/*
 * bgtest.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "bgtest.h"
#include "protocol/protocol.h"
#include "msgHandler.h"
#include "toString.h"
#include "entSetting.h"

using namespace msg;
using namespace ent;

BGTest::BGTest()
{

}

BGTest::~BGTest()
{

}


uint32_t BGTest::onMsgReq(MsgInfo *msg,uint32_t connID)
{

    switch(msg->msgType)
    {
        case PWriteI2CReq::uri:
            onPWriteI2CReq(msg,connID);
            break;

        case PReadI2CReq::uri:
        	onPReadI2CReq(msg,connID);
            break;

        case PWriteSPIReq::uri:
            onPWriteSPIReq(msg,connID);
            break;

        case PReadSPIReq::uri:
        	onPReadSPIReq(msg,connID);
            break;

        default:
        	cout<<"URI UNKOWN!"<<" msg->msgType="<<msg->msgType <<endl;
        	break;
    }

    return 0;
}

void BGTest::onPWriteI2CReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPWriteI2CReq"<<" connID="<<connID <<endl;
    MsgInfo rsp;
    rsp.msgType = PWriteI2CRsp::uri;

    uint32_t chn = atoi(msg->info["chn"].c_str());
    uint32_t addr = atoi(msg->info["addr"].c_str());
    uint32_t value = atoi(msg->info["value"].c_str());



    cout<<"onPWriteI2CReq"<<" chn="<<chn<<",addr="<<addr<<",value="<<value <<endl;

    if(CommModel* module = MsgHandler::Instance()->getModule(TYPE_MODEL_BUSDRIVER))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
    	module->mifI2CWrite(chn,addr,value);
    }
    else
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void BGTest::onPReadI2CReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPReadI2CReq"<<" connID="<<connID <<endl;
    MsgInfo rsp;
    rsp.msgType = PReadI2CRsp::uri;

    uint32_t chn = atoi(msg->info["chn"].c_str());
    uint32_t addr = atoi(msg->info["addr"].c_str());


    cout<<"onPReadI2CReq"<<" chn="<<chn<<",addr="<<addr<<endl;



    if(CommModel* module = MsgHandler::Instance()->getModule(TYPE_MODEL_BUSDRIVER))
    {
    	  rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
    	  rsp.info["value"] = tostring(module->mifI2CRead(chn,addr));
    }
    else
    {
    	  rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    	  rsp.info["value"] = tostring(0);

    }



    MsgHandler::Instance()->sendMsg(connID,&rsp);


}

void BGTest::onPWriteSPIReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPWriteSPIReq"<<" connID="<<connID <<endl;




    MsgInfo rsp;
    rsp.msgType = PWriteSPIReq::uri;

    uint32_t chn = atoi(msg->info["chn"].c_str());
    uint32_t addr = atoi(msg->info["addr"].c_str());
    uint32_t value = atoi(msg->info["value"].c_str());


    cout<<"onPWriteSPIReq"<<" chn="<<chn<<",addr="<<addr<<",value="<<value<<endl;

    if(CommModel* module = MsgHandler::Instance()->getModule(TYPE_MODEL_BUSDRIVER))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
    	module->mifSPIWrite(chn,addr,value);
    }
    else
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    	rsp.info["value"] = tostring(0);
    }



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void BGTest::onPReadSPIReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPReadSPIReq"<<" connID="<<connID <<endl;

    uint32_t chn = atoi(msg->info["chn"].c_str());
    uint32_t addr = atoi(msg->info["addr"].c_str());



    MsgInfo rsp;
    rsp.msgType = PReadSPIRsp::uri;
    cout<<"onPReadI2CReq"<<" chn="<<chn<<",addr="<<addr<<endl;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    if(CommModel* module = MsgHandler::Instance()->getModule(TYPE_MODEL_BUSDRIVER))
    {
    	  rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
    	  rsp.info["value"] = tostring(module->mifSPIRead(chn,addr));
    }
    else
    {
    	  rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    	  rsp.info["value"] = tostring(0);
    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);

}





