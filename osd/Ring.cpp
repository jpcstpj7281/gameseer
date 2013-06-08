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
	,qbox_(0)
{
	startTimer(100);
}
Ring::~Ring(){
	disconnect();
	QboxMgr::instance()->removeQbox(qbox_->address());
}


RingMgr* RingMgr::inst = 0;
RingMgr *RingMgr::instance(){
	if ( inst) return inst;
	return inst = new RingMgr();
}
RingMgr::RingMgr()
	:colCount_(0)
	,rowCount_(0)
{
	for( size_t i = 0 ; i < MAXROW; ++i){
		for( size_t j = 0 ; j < MAXCOL; ++j){
			screens_[i][j] = NULL;
		}
	}
}
RingMgr::~RingMgr()
{
}

void RingMgr::timerEvent ( QTimerEvent *  ){
}

