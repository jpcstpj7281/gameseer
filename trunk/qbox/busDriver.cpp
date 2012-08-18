/*
 * busDriver.cpp
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#include <iostream>
#include <stdlib.h>
#include "busDriver.h"
#include "protocol/protocol.h"
#include "msgHandler.h"
#include "toString.h"
#include "entSetting.h"



using namespace msg;
using namespace ent;


BusDriver::BusDriver()
{

}

BusDriver::~BusDriver()
{

}


uint32_t BusDriver::onMsgReq(MsgInfo *msg,uint32_t connID)
{

    switch(msg->msgType)
    {

        default:
        cout<<"URI UNKOWN!"<<" msg->msgType="<<msg->msgType <<endl;
        break;


    }

    return 0;
}


void BusDriver::mifI2CWrite(uint32_t chn,uint32_t addr,uint32_t value)
{
	cout<<"mifI2CWrite"<<" chn="<<chn <<endl;
	//dev_I2C_Write(chn,TYPE_CHIP_5160,addr,value);

}

uint32_t BusDriver::mifI2CRead(uint32_t chn,uint32_t addr)
{
	uint32_t nRtn= 0 ;
	uint8_t value=0;
	cout<<"mifI2CRead"<<" chn="<<chn <<endl;
//	dev_I2C_Read(chn,TYPE_CHIP_5160,addr,value);
	nRtn = nRtn | value;
	return nRtn;
}

void BusDriver::mifSPIWrite(uint32_t chn,uint32_t addr,uint32_t value)
{
	cout<<"mifSPIWrite"<<" chn="<<chn <<endl;
//	dev_SPI_Write(chn,addr,value);
}

uint32_t BusDriver::mifSPIRead(uint32_t chn,uint32_t addr)
{
	cout<<"mifSPIRead"<<" chn="<<chn <<endl;
	uint32_t nRtn= 0 ;
	uint8_t value=0;
//	dev_SPI_Read(chn,addr,value);
	nRtn = nRtn | value;
	return nRtn;
}





