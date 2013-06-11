#include "Wnd.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"


#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Wnd::Wnd(double xPercent, double yPercent, double widthPercent, double heightPercent)
{

}
Wnd::Wnd( uint32_t x, uint32_t y, uint32_t width, uint32_t height){
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



Wnd* WndMgr::createWnd(double xPercent, double yPercent, double widthPercent, double heightPercent){
	wnds_.push_back( new Wnd(xPercent, yPercent, widthPercent, heightPercent));
	wnds_.back()->layer_ = ++currlayer_;
	return wnds_.back();
}
