#include "Channel.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Channel::Channel(uint32_t row, uint32_t col)
	:row_(row)
	,col_(col)
	,qbox_(0)
{
	startTimer(100);
}
Channel::~Channel(){
	disconnect();
	QboxMgr::instance()->removeQbox(qbox_->address());
}


ChannelMgr* ChannelMgr::inst = 0;
ChannelMgr *ChannelMgr::instance(){
	if ( inst) return inst;
	return inst = new ChannelMgr();
}
ChannelMgr::ChannelMgr()
	:colCount_(0)
	,rowCount_(0)
{
	for( size_t i = 0 ; i < MAXROW; ++i){
		for( size_t j = 0 ; j < MAXCOL; ++j){
			screens_[i][j] = NULL;
		}
	}
}
ChannelMgr::~ChannelMgr()
{
}

void ChannelMgr::timerEvent ( QTimerEvent *  ){
}

