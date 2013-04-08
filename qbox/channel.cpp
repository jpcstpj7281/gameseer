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
        case PSetSwitchInputReq::uri:
            onPSetSwitchInputReq(msg,connID);
            break;

        case PGetSwitchInputReq::uri:
        	onPGetSwitchInputReq(msg,connID);
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

void Channel::onPSetSwitchInputReq(MsgInfo *msg,uint32_t connID)
{

    uint32_t out = atoi(msg->info["out"].c_str());
    uint32_t input = atoi(msg->info["in"].c_str());

    MsgInfo rsp;
    rsp.msgType = PSetSwitchInputRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
	rsp.info["out"] = tostring(out);
	rsp.info["in"] = tostring(input);

//    if(!EntSetting::Instance()->setInput(out,input))
//    {
//    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
//    	test_msg("onPSetSwitchInputReq  error!out=%d,input=%d",out,input);
//    }
//    else
    {
#ifndef __unix__

		test_msg("onPSetSwitchInputReq  out=%d,input=%d",out,input);
		setChnSignalInput(out,input);

//		taskDelay(10);

	    uint32_t model = 0;
	    uint32_t inputModel = 0;
	    getChnModel(out,model);
		test_msg("setChnModel  out=%d,model:%d  !",out,model);
		setChnModel(out,model);




#endif

    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Channel::onPSetInPutPicReq(MsgInfo *msg,uint32_t connID)
{
	test_msg("onPSetInPutPicReq  connID=%d",connID);

    uint32_t winHandle = atoi(msg->info["out"].c_str());
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

	uint32_t out = atoi(msg->info["out"].c_str());
    uint32_t in = atoi(msg->info["in"].c_str());
    uint32_t width = atoi(msg->info["w"].c_str());
    uint32_t height = atoi(msg->info["h"].c_str());
    uint32_t channelX = atoi(msg->info["x"].c_str());
    uint32_t channelY = atoi(msg->info["y"].c_str());

    test_msg("onPSetInPutShowAreaReq out=%d,in=%d,w=%d,h=%d,x=%d,y=%d",out,in,width,height,channelX,channelY);

    MsgInfo rsp;
    rsp.msgType = PSetOutPutSizeRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);


    EntSetting::Instance()->setWindowInfo(out,channelX,channelY,width,height);

#ifndef __unix__
    moveInputChannel(out,channelX,channelY);
    setInputSize(out,width,height);
#endif

    uint32_t hw = 0;
    uint32_t vw = 0;
    EntSetting::Instance()->getOutputInfoSize(out,hw,vw);
    if(vw ==0 && hw==0)
    {

    }
    else
    {
#ifndef __unix__
    	setOutputSize(out,hw,vw);
#endif
    }


    rsp.info["out"] = tostring(out);
    rsp.info["w"] = tostring(width);
    rsp.info["h"] = tostring(height);
    rsp.info["x"] =tostring(channelX);
    rsp.info["y"] =tostring(channelY);



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Channel::onPGetSwitchInputReq(MsgInfo *msg,uint32_t connID)
{


    MsgInfo rsp;
    rsp.msgType = PSetSwitchInputRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);


#ifndef __unix__
    uint32_t input=0;
    getChnSignalInput(3,input);
    rsp.info["out1"] = tostring(input);
    getChnSignalInput(4,input);
    rsp.info["out2"] = tostring(input);
    getChnSignalInput(1,input);
    rsp.info["out3"] = tostring(input);
    getChnSignalInput(2,input);
    rsp.info["out4"] = tostring(input);


#endif


    MsgHandler::Instance()->sendMsg(connID,&rsp);

}





