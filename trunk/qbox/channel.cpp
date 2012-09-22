/*
 * channel.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "channel.h"
#include "protocol/protocol.h"
#include "msgHandler.h"
#include "toString.h"
#include "entSetting.h"
#include "common.h"

using namespace msg;
using namespace ent;



Channel::Channel()
{

}

Channel::~Channel()
{

}


uint32_t Channel::onMsgReq(MsgInfo *msg,uint32_t connID)
{

    switch(msg->msgType)
    {
        case PChangeInputReq::uri:
            onPChangeInputReq(msg,connID);
            break;

        case PSetInPutPicReq::uri:
        	onPSetInPutPicReq(msg,connID);
            break;

        case PSetOutPutSizeReq::uri:
        	onPSetInPutShowAreaReq(msg,connID);
            break;


        default:
            //cout<<"CHANNEL URI UNKOWN!"<<" msg->msgType="<<msg->msgType <<endl;
        	break;
    }

    return 0;
}

void Channel::onPChangeInputReq(MsgInfo *msg,uint32_t connID)
{

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    uint32_t input = atoi(msg->info["in"].c_str());

    MsgInfo rsp;
    rsp.msgType = PChangeInputRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    if(!EntSetting::Instance()->setInput(winHandle,input))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }

#ifndef __unix__
    if(winHandle==1 || winHandle==2)
    {
    	uint32_t model = 0;
    	getSignalModel(winHandle,model);

    	if(TYPE_INPUT_SIZE_DEFAULT != model)
    	{
    		setChnSignalModel(winHandle,model);
    	}
    	else
    	{
    		rsp.info["error"] = tostring(ERROR_TYPE_NOSIGNAL);
    	}
    }


#endif


    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Channel::onPSetInPutPicReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPSetInPutPicReq"<<" connID="<<connID <<endl;

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    uint32_t pic = atoi(msg->info["pic"].c_str());

    MsgInfo rsp;
    rsp.msgType = PSetInPutPicRsp::uri;


    pic = pic + 100;

    if(!EntSetting::Instance()->setInput(winHandle,pic))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }



    MsgHandler::Instance()->sendMsg(connID,&rsp);


}

void Channel::onPSetInPutShowAreaReq(MsgInfo *msg,uint32_t connID)
{

	uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    uint32_t output = atoi(msg->info["in"].c_str());
    uint32_t width = atoi(msg->info["w"].c_str());
    uint32_t height = atoi(msg->info["h"].c_str());
    uint32_t channelX = atoi(msg->info["x"].c_str());
    uint32_t channelY = atoi(msg->info["y"].c_str());

    test_msg("onPSetInPutShowAreaReq in=%d,w=%d,h=%d,x=%d,y=%d",output,width,height,channelX,channelY);

    MsgInfo rsp;
    rsp.msgType = PSetOutPutSizeRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);


    EntSetting::Instance()->setOutputInfoSize(output,width,height);

    rsp.info["out"] = tostring(output);
    rsp.info["w"] = tostring(width);
    rsp.info["h"] = tostring(height);
    rsp.info["x"] =tostring(channelX);
    rsp.info["y"] =tostring(channelY);



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}







