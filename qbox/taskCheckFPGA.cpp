/*
 * event.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "taskCheckFPGA.h"
#include "msgHandler.h"
#include "toString.h"
#include "entSetting.h"

using namespace msg;
using namespace ent;

TaskCheckFPGA::TaskCheckFPGA()
{

}

TaskCheckFPGA::~TaskCheckFPGA()
{

}


uint32_t TaskCheckFPGA::onMsgReq(MsgInfo *msg,uint32_t connID)
{

    switch(msg->msgType)
    {

        default:
        	cout<<"URI UNKOWN!"<<" msg->msgType="<<msg->msgType <<endl;
        	break;


    }

    return 0;
}

void TaskCheckFPGA::taskMain()
{
	uint32_t nInputUseCount = 0;

	for(uint32_t inputPort = 0;inputPort<5;inputPort++)
	{
		//取FPGA通道
	}
}



