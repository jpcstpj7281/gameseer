#include "Ring.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Ring::Ring(uint32_t row, uint32_t col)
	:row_(row)
	,col_(col)
{
	startTimer(100);
}
Ring::~Ring(){
}
void Ring::timerEvent ( QTimerEvent *  ){
}


RingMgr* RingMgr::inst = 0;
RingMgr *RingMgr::instance(){
	if ( inst) return inst;
	return inst = new RingMgr();
}
RingMgr::RingMgr()
{

}
RingMgr::~RingMgr()
{
}

void RingMgr::timerEvent ( QTimerEvent *  ){
}

