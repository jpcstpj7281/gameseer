/*
 * busDriver.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef BUSDRIVER_H_
#define BUSDRIVER_H_

#include "commModel.h"

namespace msg
{

class BusDriver
:public CommModel
{

public:
	BusDriver();
	virtual ~BusDriver();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID);

	virtual void mifI2CWrite(uint32_t chn,uint32_t addr,uint32_t value);
	virtual uint32_t mifI2CRead(uint32_t chn,uint32_t addr);
	virtual void mifSPIWrite(uint32_t chn,uint32_t addr,uint32_t value);
	virtual uint32_t mifSPIRead(uint32_t chn,uint32_t addr);

private:




};

};

#endif /* USER_H_ */
