#include "Screen.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;





class ScreenObj{
public:
	ScreenObj(uint32_t msgtype, ScreenCallbackFunc callback, ScreenDataMap& var ):
	callback_(callback){
		sendmsg_.msgType = msgtype;
		sendmsg_.info = var;
	}
	ScreenCallbackFunc callback_;
	MsgInfo sendmsg_;
};

struct ScreenMgr::Impl{

	Impl(){
	}
	~Impl(){
	}
};

bool ScreenMgr::hasScreen(std::string & ip){	
	//return impl_->qboxes_.find(ip)!= impl_->qboxes_.end();
	return true;
}
Screen* ScreenMgr::getScreen(std::string & ip){	
	//auto found = impl_->qboxes_.find(ip);
	//if ( found == impl_->qboxes_.end() ){
	//	Screen * q = new Screen();
	//	impl_->qboxes_.insert( std::make_pair( ip, q));
	//	return q;
	//}
	//return found->second;
	return NULL;
}
bool ScreenMgr::removeScreen( std::string &ip){
	//auto found = impl_->qboxes_.find(ip);
	//if ( found == impl_->qboxes_.end() ){
	//	return false;
	//}
	//delete found->second;
	//impl_->qboxes_.erase(found);
	return true;
}


ScreenMgr* ScreenMgr::inst = 0;
ScreenMgr *ScreenMgr::instance(){
	if ( inst) return inst;
	return inst = new ScreenMgr();
}
ScreenMgr::ScreenMgr():
impl_(new Impl)
{
}
ScreenMgr::~ScreenMgr()
{
	
	delete impl_;
}

static void testCallback( uint32_t , ScreenDataMap&){
	qDebug()<<"testCallback";
}


void ScreenMgr::timerEvent ( QTimerEvent *  ){
	
}

