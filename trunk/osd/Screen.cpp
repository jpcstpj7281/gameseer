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
	disconnect();
	QboxMgr::instance()->removeQbox(qbox_->address());
}

void Screen::osdRequestRead(uint32_t addr, const uint32_t len, QboxCallback callback ){
	QboxDataMap datamap;
	datamap["addr"] = QString::number( addr).toStdString();
	datamap["len"] = QString::number(len).toStdString();
	if ( qbox_){
		qbox_->addAsyncRequest( (32<<16)|3, callback, datamap);
	}
}

void Screen::osdRequestUint(uint32_t addr, const uint32_t val, QboxCallback callback ){
	std::string data;
	data.resize(4);
	data[0] = val>>24;
	data[1] = val>>16;
	data[2] = val>>8;
	data[3] = val;
	osdRequest( addr, data, callback);
}

void Screen::osdRequestInt(uint32_t addr, const int val, QboxCallback callback ){
	std::string data;
	data.resize(4);
	data[0] = val>>24;
	data[1] = val>>16;
	data[2] = val>>8;
	data[3] = val;
	osdRequest( addr, data, callback);
}

void Screen::osdRequestShort(uint32_t addr, const short val, QboxCallback callback ){
	std::string data;
	data.resize(2);
	data[0] = val>>8;
	data[1] = val;
	osdRequest( addr, data, callback);
}

void Screen::osdRequestUshort(uint32_t addr, const unsigned short val, QboxCallback callback ){
	std::string data;
	data.resize(2);
	data[0] = val>>8;
	data[1] = val;
	osdRequest( addr, data, callback);
}

void Screen::osdRequestChar(uint32_t addr, const char val, QboxCallback callback ){
	std::string data;
	data.resize(1);
	data[0] = val;
	osdRequest( addr, data, callback);
}

void Screen::osdRequest(uint32_t addr, const std::string &data, QboxCallback callback){
	QboxDataMap datamap;
	datamap["addr"] = QString::number( addr).toStdString();
	datamap["len"] = QString::number( data.length()).toStdString();
	datamap["value"] = data;
	osdRequest( callback, datamap);
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
			scrns.push_back( ToScreenID(i+1, colCount_) );
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
			scrns.push_back( ToScreenID(i+1, colCount_+1) ) ;
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
			scrns.push_back( ToScreenID(rowCount_+1, i+1));
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
			scrns.push_back( ToScreenID(rowCount_, i+1));
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

