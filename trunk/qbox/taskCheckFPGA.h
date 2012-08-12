/*
 * status.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef _TASK_CHECK_FPGA_H_
#define _TASK_CHECK_FPGA_H_

#include "commModel.h"

namespace msg
{

class TaskCheckFPGA
:public CommModel
{

public:
	TaskCheckFPGA();
	virtual ~TaskCheckFPGA();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID);

	void taskMain();


private:




};

};

#endif /* USER_H_ */
