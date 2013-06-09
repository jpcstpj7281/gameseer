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

{
	startTimer(100);
}
Channel::~Channel(){
}
void Channel::timerEvent ( QTimerEvent *  ){
}

ChannelMgr* ChannelMgr::inst = 0;
ChannelMgr *ChannelMgr::instance(){
	if ( inst) return inst;
	return inst = new ChannelMgr();
}
ChannelMgr::ChannelMgr()
{
}
ChannelMgr::~ChannelMgr()
{
}

void ChannelMgr::timerEvent ( QTimerEvent *  ){
}

