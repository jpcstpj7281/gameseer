/*
 * commModel.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef COMMMODEL_H_
#define COMMMODEL_H_

#include "msgBase.h"

class CommModel
:public MsgBase
{

public:
	CommModel();
	virtual ~CommModel();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID) = 0;


private:

	uint32_t name;

};



#endif /* COMMMODEL_H_ */
