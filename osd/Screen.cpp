#include "Screen.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Screen::Screen(uint32_t row, uint32_t col)
	:row_(row)
	,col_(col)
	,qbox_(0)
{
}
Screen::~Screen(){
}


void Screen::osdRequest(QboxCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( (32<<16)|1, callback, value);
	}
}
void Screen::versionRequest(QboxCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( PProtocolVersionReq::uri , callback, value);
	}
}
void Screen::inputRequest(QboxCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( PGetInPutReq::uri , callback, value);
	}
}
void Screen::inputResolutionRequest(QboxCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( PGetInPutSizeReq::uri, callback, value);
	}
}
void Screen::outputRequest(QboxCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest( PGetOutPutReq::uri, callback, value);
	}
}
bool Screen::setAddress( const std::string & ip){
	if ( qbox_){
		if ( qbox_->isConn() ){
			return false;
		}else{
			qbox_->setAddress(ip);
		}
	}else{
		if ( QboxMgr::instance()->hasQbox(ip)) {
			return false;
		}else {
			qbox_ = QboxMgr::instance()->createQbox(ip);
		}
	}
	return true;
}
void Screen::connect( ){
	if ( qbox_ ){
		//QboxMgr::instance()->removeQbox(qbox_->address());
		qbox_->close();
		qbox_->connInit();
	}
}
void Screen::disconnect( ){
	if ( qbox_){
		//QboxMgr::instance()->removeQbox(qbox_->address()); qbox_ = NULL;
		qbox_->close();
	}
}


std::vector<ResourceID> ScreenMgr::removeScreenCol( ){
	std::vector<ResourceID> scrns ;
	for ( size_t i = 0; i < rowCount_; ++i){
		if ( screens_[i][colCount_-1]){
			scrns.push_back( ((i+1) << 8) | colCount_);
			delete screens_[i][colCount_-1];
			screens_[i][colCount_-1] = NULL;
		}else{
			scrns.clear();
			return scrns;
		}
	}
	--colCount_;
	if ( colCount_ == 0 ) rowCount_ = 0;
	return scrns;
}
std::vector<ResourceID> ScreenMgr::addScreenCol( ){
	std::vector<ResourceID> scrns ;
	if ( rowCount_ == 0 ) ++rowCount_;
	for ( size_t  i = 0; i < rowCount_; ++i){
		if ( screens_[i][colCount_] == NULL){
			screens_[i][colCount_] = new Screen( i+1, colCount_+1);
			scrns.push_back( ((i+1 )<<8)| (colCount_+1)) ;
		}else{
			scrns.clear();
			return scrns;
		}
	}
	++colCount_;
	return scrns;
}
std::vector<ResourceID> ScreenMgr::addScreenRow( ){
	std::vector<ResourceID> scrns ;
	if ( colCount_ == 0 ) ++colCount_;
	for ( size_t  i = 0; i < colCount_; ++i){
		if ( screens_[rowCount_][i] == NULL){
			screens_[rowCount_][i] = new Screen( rowCount_+1, i+1);
			scrns.push_back( ((rowCount_+1)<<8) | (i+1));
		}else{
			scrns.clear();
			return scrns;
		}
	}
	++rowCount_;
	
	return scrns;
}

std::vector<ResourceID> ScreenMgr::removeScreenRow(){
	std::vector<ResourceID> scrns ;
	for ( size_t  i = 0; i < colCount_; ++i){
		if ( screens_[rowCount_-1][i]){
			scrns.push_back( (rowCount_ << 8) | (i+1));
			delete screens_[rowCount_-1][i];
			screens_[rowCount_-1][i] = NULL;
		}else{
			scrns.clear();
			return scrns;
		}
	}
	--rowCount_;
	if ( rowCount_ == 0 ) colCount_ = 0;
	return scrns;
}


ScreenMgr* ScreenMgr::inst = 0;
ScreenMgr *ScreenMgr::instance(){
	if ( inst) return inst;
	return inst = new ScreenMgr();
}
ScreenMgr::ScreenMgr()
	:colCount_(0)
	,rowCount_(0)
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

