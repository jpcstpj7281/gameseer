#include "Wnd.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"


#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Wnd::Wnd(double xPercent, double yPercent, double wPercent, double hPercent):
xPercent_(xPercent)
,yPercent_(yPercent)
,wPercent_(wPercent)
,hPercent_(hPercent)
{
	x_ = y_ = w_ = h_= ax_ = ay_ = aw_ = ah_ = 0;
}
Wnd::Wnd( uint32_t x, uint32_t y, uint32_t w, uint32_t h):
x_(x)
,y_(y)
,w_(w)
,h_(h){
	ax_ = ay_ = aw_ = ah_ = 0;
}
Wnd::~Wnd(){
}

bool Wnd::resizeWnd(double xPercent, double yPercent, double widthPercent, double heightPercent){
	return false;
}
bool Wnd::moveWnd(double xPercent, double yPercent){
	return false;
}

//=======================================================ScreenMgr===============================================================
WndMgr* WndMgr::inst = 0;
WndMgr *WndMgr::instance(){
	if ( inst) return inst;
	return inst = new WndMgr();
}
WndMgr::WndMgr():currlayer_(0)
{
}
WndMgr::~WndMgr()
{
}
bool WndMgr::hasWnd(const std::string & id){
	for ( size_t i = 0 ; i < wnds_.size(); ++i){
		if (wnds_[i]->id_ == id) return true;
	}
	return false;
}
Wnd* WndMgr::createWnd( const std::string & id, double xPercent, double yPercent, double widthPercent, double heightPercent){
	wnds_.push_back( new Wnd(xPercent, yPercent, widthPercent, heightPercent));
	wnds_.back()->id_ = id;
	wnds_.back()->layer_ = ++currlayer_;
	return wnds_.back();
}

Wnd* WndMgr::createWnd(double xPercent, double yPercent, double widthPercent, double heightPercent){
	for ( size_t i = 0 ; i < 0xFFFFFFFF; ++i){
		std::string str = "Wnd";
		std::string num = QString::number(i+1).toStdString();
		if (!hasWnd(str + num)){
			return createWnd( str+num, xPercent, yPercent, widthPercent, heightPercent);
			break;
		}
	}
	return NULL;
}
bool WndMgr::closeWnd(Wnd* wnd){
	for ( auto i = wnds_.begin() ; i < wnds_.end(); ++i){
		if (*i == wnd) {
			wnds_.erase(i);
			return true;
		}
	}
	return false; 
}