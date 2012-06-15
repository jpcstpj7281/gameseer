/*
 * bgtest.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef BGTEST_H_
#define BGTEST_H_

#include "commModel.h"

namespace msg
{

class BGTest
:public CommModel
{

public:
	BGTest();
	virtual ~BGTest();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID);

private:

	void onPWriteI2CReq(MsgInfo *msg,uint32_t connID);
	void onPReadI2CReq(MsgInfo *msg,uint32_t connID);
	void onPWriteSPIReq(MsgInfo *msg,uint32_t connID);
	void onPReadSPIReq(MsgInfo *msg,uint32_t connID);


};

};

#endif /* USER_H_ */
