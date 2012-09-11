/*
 * windows.h
 *
 *  Created on: 2012-2-19
 *      Author: icecoffee76
 */

#ifndef WINDOWS_H_
#define WINDOWS_H_

#include "commModel.h"
#include <fstream>

namespace msg
{


#define DEFINE_WINDOW_LAYER   50

class Windows
:public CommModel
{

public:
	Windows();
	virtual ~Windows();

	virtual uint32_t onMsgReq(MsgInfo *msg,uint32_t connID);

private:

	void onPGetWindowsHandleReq(MsgInfo *msg,uint32_t connID);
	void onPGetWindowsInfoReq(MsgInfo *msg,uint32_t connID);
	void onPCreateWindowsReq(MsgInfo *msg,uint32_t connID);
	void onPSetWindowsLayerReq(MsgInfo *msg,uint32_t connID);

	void onPSetWindowsShowStateReq(MsgInfo *msg,uint32_t connID);
	void onPDelWindowsReq(MsgInfo *msg,uint32_t connID);
	void onPMoveWindowsReq(MsgInfo *msg,uint32_t connID);
	void onPUpdateQboxReq(MsgInfo *msg,uint32_t connID);
	void onCloseAllReq(MsgInfo *msg,uint32_t connID);

    std::ofstream   _update;
    uint32_t        _updateid;

};

};

#endif /* USER_H_ */
