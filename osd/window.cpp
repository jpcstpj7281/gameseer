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
	,qbox_(0)
{
	startTimer(100);
}
Window::~Window(){
	disconnect();
	QboxMgr::instance()->removeQbox(qbox_->address());
}


WindowMgr* WindowMgr::inst = 0;
WindowMgr *WindowMgr::instance(){
	if ( inst) return inst;
	return inst = new WindowMgr();
}
WindowMgr::WindowMgr()
	:colCount_(0)
	,rowCount_(0)
{
	for( size_t i = 0 ; i < MAXROW; ++i){
		for( size_t j = 0 ; j < MAXCOL; ++j){
			screens_[i][j] = NULL;
		}
	}
}
WindowMgr::~WindowMgr()
{
}

void WindowMgr::timerEvent ( QTimerEvent *  ){
}

