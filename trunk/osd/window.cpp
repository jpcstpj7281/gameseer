#include "Window.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Window::Window(uint32_t row, uint32_t col)
	:row_(row)
	,col_(col)
{
	startTimer(100);
}
Window::~Window(){
}
void Window::timerEvent ( QTimerEvent *  ){
}


WindowMgr* WindowMgr::inst = 0;
WindowMgr *WindowMgr::instance(){
	if ( inst) return inst;
	return inst = new WindowMgr();
}
WindowMgr::WindowMgr()
{
}
WindowMgr::~WindowMgr()
{
}

void WindowMgr::timerEvent ( QTimerEvent *  ){
}

