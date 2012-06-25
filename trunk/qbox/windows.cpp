/*
 * windows.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "windows.h"
#include "protocol/protocol.h"
#include "msgHandler.h"
#include "toString.h"
#include "entSetting.h"
#include <set>

using namespace msg;
using namespace ent;
using namespace std;

Windows::Windows()
{

}

Windows::~Windows()
{

}


uint32_t Windows::onMsgReq(MsgInfo *msg,uint32_t connID)
{

    switch(msg->msgType)
    {
        case PGetWindowsHandleReq::uri:
            onPGetWindowsHandleReq(msg,connID);
            break;

        case PGetWindowsInfoReq::uri:
        	onPGetWindowsInfoReq(msg,connID);
            break;

        case PCreateWindowsReq::uri:
            onPCreateWindowsReq(msg,connID);
            break;

        case PSetWindowsLayerReq::uri:
        	onPSetWindowsLayerReq(msg,connID);
            break;

        case PSetWindowsShowStateReq::uri:
        	onPSetWindowsShowStateReq(msg,connID);
        	break;

        case PDelWindowsReq::uri:
        	onPDelWindowsReq(msg,connID);
        	break;

        case PMoveWindowsReq::uri:
        	onPMoveWindowsReq(msg,connID);
        	break;

        default:
        	cout<<"URI UNKOWN!"<<" msg->msgType="<<msg->msgType <<endl;
        	break;
    }

    return 0;
}

void Windows::onPGetWindowsHandleReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPGetWindowsHandleReq"<<" connID="<<connID <<endl;
    MsgInfo rsp;
    rsp.msgType = PGetWindowsHandleRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    rsp.info["total"] =  EntSetting::Instance()->getWindowsTotal();

    std::set<uint32_t> handle;
    EntSetting::Instance()->getWindowsHandle(handle);

    uint32_t handleNum=0;
    for(std::set<uint32_t>::iterator it=handle.begin();it!=handle.end();it++)
    {
    	string key = "handleNum" + tostring(handleNum);
    	rsp.info[key] = (*it);
    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onPGetWindowsInfoReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPGetWindowsInfoReq"<<" connID="<<connID <<endl;
    MsgInfo rsp;
    rsp.msgType = PGetWindowsInfoRsp::uri;

    uint32_t winHandle  = atoi(msg->info["winHandle"].c_str());

    WindowInfo info;
    if( EntSetting::Instance()->getWindowsInfo(winHandle,info))
    {
        rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
        rsp.info["winHandle"]  =msg->info["winHandle"];

        rsp.info["x"]  = tostring(info.winX);
        rsp.info["y"]  = tostring(info.winY);
        rsp.info["w"]  = tostring(info.width);
        rsp.info["h"]  = tostring(info.height);
        rsp.info["in"]  = tostring(info.channelIn);
        rsp.info["out"]  = tostring(info.channelOut);
        rsp.info["layer"]  = tostring(info.layer);
    }
    else
    {
        rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
        rsp.info["winHandle"]  =msg->info["winHandle"];
    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);


}

void Windows::onPCreateWindowsReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPCreateWindowsReq"<<" connID="<<connID <<endl;


    uint32_t winX = atoi(msg->info["x"].c_str());
    uint32_t winY = atoi(msg->info["y"].c_str());
    uint32_t winW = atoi(msg->info["w"].c_str());
    uint32_t winH = atoi(msg->info["h"].c_str());
    uint32_t winOut = atoi(msg->info["out"].c_str());

    MsgInfo rsp;
    rsp.msgType = PCreateWindowsRsp::uri;

    uint32_t winHandle = 0;

    winHandle = EntSetting::Instance()->createWindow(winX,winY,winW,winH);

    if(!EntSetting::Instance()->setLayer(winHandle,DEFINE_WINDOW_LAYER))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }

    if(!EntSetting::Instance()->setOutput(winHandle,winOut))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }

    if(!EntSetting::Instance()->setShowStatus(winHandle,TYPE_WINDOW_STATUS_HIDE))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }


    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);
    rsp.info["winHandle"] = tostring(winHandle);



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onPSetWindowsLayerReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPSetWindowsLayerReq"<<" connID="<<connID <<endl;

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    uint32_t layer = atoi(msg->info["layer"].c_str());

    MsgInfo rsp;
    rsp.msgType = PSetWindowsLayerRsp::uri;


    if(!EntSetting::Instance()->setLayer(winHandle,layer))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }
    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onPSetWindowsShowStateReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPSetWindowsShowStateReq"<<" connID="<<connID <<endl;

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());



    MsgInfo rsp;
    rsp.msgType = PSetWindowsShowStateRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    if("show" == msg->info["showState"])
    {
        if(!EntSetting::Instance()->setShowStatus(winHandle,TYPE_WINDOW_STATUS_SHOW))
        {
        	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
        }
    }

    if("hide" == msg->info["showState"])
    {
        if(!EntSetting::Instance()->setShowStatus(winHandle,TYPE_WINDOW_STATUS_HIDE))
        {
        	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
        }
    }




    MsgHandler::Instance()->sendMsg(connID,&rsp);

}

void Windows::onPDelWindowsReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPDelWindowsReq"<<" connID="<<connID <<endl;

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());


    MsgInfo rsp;
    rsp.msgType = PDelWindowsRsp::uri;

    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);


    if(!EntSetting::Instance()->delWindow(winHandle))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }

    MsgHandler::Instance()->sendMsg(connID,&rsp);

}


void Windows::onPMoveWindowsReq(MsgInfo *msg,uint32_t connID)
{
    cout<<"onPMoveWindowsReq"<<" connID="<<connID <<endl;

    uint32_t winHandle = atoi(msg->info["winHandle"].c_str());
    uint32_t winX = atoi(msg->info["x"].c_str());
    uint32_t winY = atoi(msg->info["y"].c_str());
    uint32_t winW = atoi(msg->info["w"].c_str());
    uint32_t winH = atoi(msg->info["h"].c_str());

    MsgInfo rsp;
    rsp.msgType = PMoveWindowsRsp::uri;


    rsp.info["error"] = tostring(ERROR_TYPE_SUCCESS);

    if(EntSetting::Instance()->setWindowPosition(winHandle,winX,winY,winW,winH))
    {
    	rsp.info["error"] = tostring(ERROR_TYPE_FALSE);
    }



    MsgHandler::Instance()->sendMsg(connID,&rsp);

}



