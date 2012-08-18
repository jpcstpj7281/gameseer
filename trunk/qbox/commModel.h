/*
 * commModel.h
 *
 *  Created on: 2012-2-21
 *      Author: icecoffee76
 */

#ifndef COMMMODEL_H_
#define COMMMODEL_H_

#include "msgBase.h"


class ModuleInterface
{
	public:

		//event
		virtual void mifCommonEvent(uint32_t eventId){}
		virtual void mifImportanceEvent(uint32_t eventId){}


		//busDriver
		virtual void mifI2CWrite(uint32_t chn,uint32_t addr,uint32_t value){}
		virtual uint32_t mifI2CRead(uint32_t chn,uint32_t addr){return 0;}
		virtual void mifSPIWrite(uint32_t chn,uint32_t addr,uint32_t value){}
		virtual uint32_t mifSPIRead(uint32_t chn,uint32_t addr){return 0;}


};

class CommModel
:public MsgBase
,public ModuleInterface
{

public:
	CommModel();
	virtual ~CommModel();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID) = 0;


private:

	//uint32_t name;

};



#endif /* COMMMODEL_H_ */
