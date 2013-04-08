#include "Screen.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Screen::Screen(){
}
Screen::~Screen(){
}


void Screen::osdRequest(ScreenCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( (32<<16)|1, callback, value);
	}
}
void Screen::versionRequest(ScreenCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( PProtocolVersionReq::uri , callback, value);
	}
}
void Screen::inputRequest(ScreenCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( PGetInPutReq::uri , callback, value);
	}
}
void Screen::inputResolutionRequest(ScreenCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( PGetInPutSizeReq::uri, callback, value);
	}
}
void Screen::outputRequest(ScreenCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( PGetOutPutReq::uri, callback, value);
	}
}


bool ScreenMgr::removeScreenCol( ){
	for ( int i = 0; i < rowCount_; ++i){
		if ( screens_[i][colCount_-1]){
			delete screens_[i][colCount_-1];
			screens_[i][colCount_-1] = NULL;
		}else{
			return false;
		}
	}
	--colCount_;
	return true;
}
bool ScreenMgr::addScreenCol( ){
	for ( int i = 0; i < rowCount_; ++i){
		if ( screens_[i][colCount_] == NULL){
			screens_[i][colCount_] = new Screen;
		}else{
			return false;
		}
	}
	++colCount_;
	return true;
}
bool ScreenMgr::removeScreenRow(){
	for ( int i = 0; i < colCount_; ++i){
		if ( screens_[rowCount_-1][i]){
			delete screens_[rowCount_-1][i];
			screens_[rowCount_-1][i] = NULL;
		}else{
			return false;
		}
	}
	--rowCount_;
	return true;
}
bool ScreenMgr::addScreenRow( ){
	for ( int i = 0; i < colCount_; ++i){
		if ( screens_[rowCount_][i] == NULL){
			screens_[rowCount_][i] = new Screen;
		}else{
			return false;
		}
	}
	++rowCount_;
	return true;
}

ScreenMgr* ScreenMgr::inst = 0;
ScreenMgr *ScreenMgr::instance(){
	if ( inst) return inst;
	return inst = new ScreenMgr();
}
ScreenMgr::ScreenMgr()
{
	for( size_t i = 0 ; i < MAXROW; ++i){
		for( size_t j = 0 ; j < MAXCOL; ++j){
			screens_[i][j] = NULL;
		}
	}
}
ScreenMgr::~ScreenMgr()
{
}

void ScreenMgr::timerEvent ( QTimerEvent *  ){
	
}

