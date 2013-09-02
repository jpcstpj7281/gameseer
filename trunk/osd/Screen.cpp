#include "Screen.h"
#include<QtDebug>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"
#include "boost/math/special_functions/round.hpp"
#include <QMainWindow>
#include "msgBase.h"
#include <protocol/protocol.h>
#include <Windows.h>

static bool ignoreCallback( uint32_t , QboxDataMap& value){
	
	return true;
}

Screen::Screen(uint32_t row, uint32_t col)
	:row_(row)
	,col_(col)
	,qbox_(0)
	,inputCount_(GetTickCount()+10000)
{
	inPort_.insert(std::make_pair(ToResourceID( 1, 0, row, col), -1));
	inPort_.insert(std::make_pair(ToResourceID( 2, 0, row, col), -1));
	inPort_.insert(std::make_pair(ToResourceID( 3, 0, row, col), -1));
	inPort_.insert(std::make_pair(ToResourceID( 4, 0, row, col), -1));
	inPort_.insert(std::make_pair(ToResourceID( 5, 0, row, col), -1));
	inPort_.insert(std::make_pair(ToResourceID( 6, 0, row, col), -1));
	outPort753_.insert(std::make_pair(ToResourceID( 0, 1, row, col), 0));
	outPort753_.insert(std::make_pair(ToResourceID( 0, 2, row, col), 0));
	outPortRing_.insert(std::make_pair(ToResourceID( 0, 3, row, col), 0));
	outPortRing_.insert(std::make_pair(ToResourceID( 0, 4, row, col), 0));

}
Screen::~Screen(){
	disconnect();
	if ( qbox_){
		QboxMgr::instance()->removeQbox(qbox_->address());
	}
}

void Screen::reset(){
}

void Screen::run ( ){
	if ( !qbox_ || !qbox_->isConn() ) return;
	for ( auto it = slowDownCache_.begin(); it != slowDownCache_.end(); ++it){
		qbox_->addAsyncRequest( PDLPCTRLReq::uri, it->first, it->second);// for osd request
	}
	slowDownCache_.clear();

	
	if ( inputCount_ < (GetTickCount()) ){
		inputRequest();
		inputCount_ = GetTickCount()+10000;
	}
}
void Screen::osdRequest(QboxCallback callback, QboxDataMap &value ){
	if ( qbox_){
		slowDownCache_.clear();
		slowDownCache_.push_back( std::make_pair(callback, value) );
	}
}

bool Screen::inputCallback( uint32_t , QboxDataMap& value ){
	if ( value["error"] != "0") return false;
	
	for ( auto it = value.begin(); it != value.end(); ++it){
		if ( it->first.substr(0, 2) == "in"){
			QString in = QString::fromStdString( it->first.substr( 2, it->first.size()) );
			ResourceID inputid = ToResourceID( in.toInt(),0, row_, col_);
			Resolution old = inPort_[inputid];
			if ( it->second=="default"){
				inPort_[ inputid ]= -1 ;
				if (old != -1){
					for ( int j = 0; j < ScreenMgr::instance()->inputChangedCallbacks_.size();++j){ScreenMgr::instance()->inputChangedCallbacks_[j](inputid);}
					return true;
				}
			}else{
				if (old == -1){
					for ( int j = 0; j < ScreenMgr::instance()->inputChangedCallbacks_.size();++j){ScreenMgr::instance()->inputChangedCallbacks_[j](inputid);}
					inPort_[ inputid ]= 0 ;
					inputResolutionRequest();
					return true;
				}
				
			}
		}
	}
	inputResolutionRequest();
	return true;
}

bool Screen::outputCallback( uint32_t , QboxDataMap& value ){
	if ( value["error"] != "0") return false;
	int half = QString::fromStdString(value["total"]).toInt()/2;
	half = 2;
	for ( auto it = value.begin(); it != value.end(); ++it){
		if ( it->first.substr(0, 3) == "out"){
			QString outstr = QString::fromStdString( it->first.substr( 3, it->first.size()) );
			int out =outstr.toInt();
			if (out <= half){
				outPort753_.insert( std::make_pair( ToResourceID( 0, out, row_, col_) , 0 ) );
			}else{
				outPortRing_.insert( std::make_pair( ToResourceID( 0, out, row_, col_) , 0 ) );
			}
		}
	}

	return true;
}
bool Screen::inputResolutionCallback( uint32_t , QboxDataMap& value ){
	uint32_t in = QString::fromStdString(value["in"]).toInt();
	for ( auto i = reqInResolutions_.begin(); i != reqInResolutions_.end(); ++i){
		if ( in == *i){
			ResourceID id = ToResourceID(in, 0, row_, col_);
			if ( value["error"] == "0"){
				int w = QString::fromStdString(value["w"]).toInt();
				int h = QString::fromStdString(value["h"]).toInt();
			
				uint32_t resolution = inPort_[id];
				uint32_t newResolution = toResolution(w,h);
				if ( resolution != newResolution){
					inPort_[id]= newResolution;
					for ( int j = 0; j < ScreenMgr::instance()->inputChangedCallbacks_.size();++j){ScreenMgr::instance()->inputChangedCallbacks_[j](id);}
				}
			}else{
				inPort_[id]= -1;
			}
			reqInResolutions_.erase(i);
			return true;
		}
	}
	return false;
}

void Screen::inputResolutionRequest(){
	if ( qbox_){
		for ( auto it = inPort_.begin(); it != inPort_.end(); ++it){
			if ( it->second != -1 ){
				uint32_t in = GetInput(it->first);
				for ( auto i = reqInResolutions_.begin(); i != reqInResolutions_.end(); ++i){
					if ( in == *i){//请求分辨率
						in = 0;
					}
				}
				if (in == 0) continue;//已经在请求,跳过
				QboxDataMap value;
				reqInResolutions_.push_back(in);
				value["in"] = QString::number(in ).toStdString();
				qbox_->addAsyncRequest( PGetInPutSizeReq::uri , std::bind( &Screen::inputResolutionCallback, this, std::placeholders::_1, std::placeholders::_2),value);
			}
		}
	}
}

bool Screen::versionCallback( uint32_t , QboxDataMap& value){
	version_ = value["protocol"];
	qDebug()<<"Screen::versionCallback";//<<  m.uniqueKeys();
	return true;
}
void Screen::versionRequest(QboxCallback callback, QboxDataMap &value ){
	if ( qbox_){
		qbox_->addAsyncRequest(PProtocolVersionReq::uri, callback, value );
	}
}
void Screen::versionRequest(){
	if ( qbox_){
		qbox_->addAsyncRequest( PProtocolVersionReq::uri , std::bind( &Screen::versionCallback, this, std::placeholders::_1, std::placeholders::_2), QboxDataMap());
	}
}
void Screen::inputRequest(){
	if ( qbox_){
		qbox_->addAsyncRequest( PGetInPutReq::uri , std::bind( &Screen::inputCallback, this, std::placeholders::_1, std::placeholders::_2), QboxDataMap());
	}
}

void Screen::connInOutRequest(ResourceID inputid, ResourceID wnode){
	if ( qbox_){
		QboxDataMap value;
		value["out"] = QString::number(GetOutput(wnode) ).toStdString();
		if ( GetCol(inputid) == GetCol(wnode) && GetRow(inputid) == GetRow(wnode)){
			value["in"] = QString::number(GetInput(inputid) ).toStdString();
		}else{
			value["in"] = QString::number(GetInput(wnode) ).toStdString();
		}
		qbox_->addAsyncRequest( PSetSwitchInputReq::uri , std::bind( /*&Screen::inputCallback, this*/ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
	}
}
bool Screen::connInOutRingRequest(ResourceID inputid, ResourceID rnode){
	if ( qbox_){
		//for( auto it = outPortRing_.begin(); it != outPortRing_.end(); ++it){
		//	if ( ToResourceID(0, GetOutput(rnode), row_, col_) == it->first){
		//		it->second = rnode;
		//		QboxDataMap value;
		//		value["out"] = QString::number(GetOutput(rnode) ).toStdString();
		//		value["in"] = QString::number(GetInput(rnode) ).toStdString();
		//		qbox_->addAsyncRequest( PSetSwitchInputReq::uri , std::bind( /*&Screen::inputCallback, this,*/ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
		//		break;
		//	}
		//}
		auto found = outPortRing_.find( ToResourceID(0, GetOutput(rnode), row_, col_));
		if ( found != outPortRing_.end()){
			found->second = rnode;
			QboxDataMap value;
			value["out"] = QString::number(GetOutput(rnode) ).toStdString();
			if ( GetCol(inputid) == GetCol(rnode) && GetRow(inputid) == GetRow(rnode)){
				value["in"] = QString::number(GetInput(inputid) ).toStdString();
			}else{
				value["in"] = QString::number(GetInput(rnode) ).toStdString();
			}
			qbox_->addAsyncRequest( PSetSwitchInputReq::uri , std::bind( /*&Screen::inputCallback, this,*/ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
			return true;
		}
	}
	return false;
}
bool Screen::hasRnode( ResourceID rnode){
	if ( qbox_){
		auto found = outPortRing_.find( ToResourceID(0, GetOutput(rnode), row_, col_));
		if (found != outPortRing_.end() && found->second == rnode){
			return true;
		}
	}
	return false;
}
void Screen::showRequest(ResourceID wnode){
	if ( qbox_){
		QboxDataMap value;
		value["out"] = QString::number(GetOutput(wnode) ).toStdString();
		value["showState"] = "show";
		qbox_->addAsyncRequest( PSetWindowsShowStateReq::uri , std::bind( /*&Screen::inputCallback, this*/ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
	}
}
void Screen::hideRequest(ResourceID wnode){
	if ( qbox_){
		QboxDataMap value;
		value["out"] = QString::number(GetOutput(wnode) ).toStdString();
		value["showState"] = "hide";
		qbox_->addAsyncRequest( PSetWindowsShowStateReq::uri , std::bind( /*&Screen::inputCallback, this*/ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
	}
}
void Screen::setWndRequest(double x, double y, double w, double h, ResourceID wnode){
	setWndRequest( (size_t)boost::math::round(x* ScreenMgr::instance()->screenWidth_*ScreenMgr::instance()->colCount_), 
		(size_t)boost::math::round(y* ScreenMgr::instance()->screenHeight_*ScreenMgr::instance()->rowCount_),
		(size_t)boost::math::round(w* ScreenMgr::instance()->screenWidth_*ScreenMgr::instance()->colCount_),
		(size_t)boost::math::round(h* ScreenMgr::instance()->screenHeight_*ScreenMgr::instance()->rowCount_), 
		wnode);
}
void Screen::setWndRequest(size_t x, size_t y, size_t w, size_t h, ResourceID wnode){
	if ( qbox_){
		for( auto it = outPort753_.begin(); it != outPort753_.end(); ++it){
			if ( wnode == it->second){
				QboxDataMap value;
				value["x"] = QString::number(x ).toStdString();
				value["y"] = QString::number(y ).toStdString();
				value["w"] = QString::number(w+1 ).toStdString();//这里先在这里调整,嵌入式将需DEBUG
				value["h"] = QString::number(h ).toStdString();
				value["out"] = QString::number(GetOutput(wnode) ).toStdString();
				qbox_->addAsyncRequest( PCreateWindowsReq::uri , std::bind( /*&Screen::inputCallback, this,*/ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
				break;
			}
		}
	}
}
void Screen::setAreaRequest(size_t x, size_t y, size_t w, size_t h, ResourceID wnode, ResourceID inputid){
	if ( qbox_){
		for( auto it = outPort753_.begin(); it != outPort753_.end(); ++it){
			if ( wnode == it->second){
				QboxDataMap value;
				value["x"] = QString::number(x ).toStdString();
				value["y"] = QString::number(y ).toStdString();
				value["w"] = QString::number(w ).toStdString();
				value["h"] = QString::number(h ).toStdString();
				value["out"] = QString::number(GetOutput(wnode) ).toStdString();
				//int input = GetInput(wnode) ;
				//if ( input ==0){
				//	input = GetInput(inputid);
				//}
				//value["in"] = QString::number(input).toStdString();
				qbox_->addAsyncRequest( PSetOutPutSizeReq::uri , std::bind( /*&Screen::inputCallback, this,*/ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
				break;
			}
		}
	}
}
void Screen::setLayerRequest(size_t layer, ResourceID wnode){
	if ( qbox_){
		for( auto it = outPort753_.begin(); it != outPort753_.end(); ++it){
			if ( wnode == it->second){
				QboxDataMap value;
				value["layer"] = QString::number( 0xFFFFFFFF - layer ).toStdString();
				value["out"] = QString::number(GetOutput(wnode) ).toStdString();
				qbox_->addAsyncRequest( PSetWindowsLayerReq::uri , std::bind( /*&Screen::inputCallback, this,*/ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
				break;
			}
		}
	}
}
void Screen::setVideoRequest(int inputNum ,QboxCallback callback){
	if ( !qbox_) return;
	QboxDataMap value;
	value["channel"] = QString::number( inputNum ).toStdString();
	qbox_->addAsyncRequest( PInitSDChannelReq::uri , std::bind( callback,  std::placeholders::_1, std::placeholders::_2), value);
}
void dlpTempRequest(QboxCallback callback, QboxDataMap &value ){
}
void Screen::setDlpRequest(int dlpPower ,QboxCallback callback ){
	if ( !qbox_) return;
	QboxDataMap value;
	value["POWER"] = QString::number( dlpPower ).toStdString();
	qbox_->addAsyncRequest( PSetDLPPinReq::uri , std::bind( callback,  std::placeholders::_1, std::placeholders::_2), value);
}
void Screen::setLampRequest(int lamp ){
	if ( !qbox_) return;
	QboxDataMap value;
	value["LAMP"] = QString::number( lamp ).toStdString();
	qbox_->addAsyncRequest( PSetDLPPinReq::uri , std::bind( ignoreCallback,  std::placeholders::_1, std::placeholders::_2), QboxDataMap());
}
void Screen::getDlpRequest(QboxCallback callback){
	if ( !qbox_) return;
	qbox_->addAsyncRequest( PGetDLPPinReq::uri , std::bind( callback,  std::placeholders::_1, std::placeholders::_2), QboxDataMap());
}

void Screen::closeAllWndRequest(){
	if ( qbox_){
		qbox_->addAsyncRequest( PCloseAllReq::uri , std::bind( ignoreCallback,  std::placeholders::_1, std::placeholders::_2), QboxDataMap());
	}
}
void Screen::outputRequest( ){
	if ( qbox_){
		qbox_->addAsyncRequest( PGetOutPutReq::uri , std::bind( &Screen::outputCallback, this, std::placeholders::_1, std::placeholders::_2), QboxDataMap());
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
		//versionRequest();
		this->closeAllWndRequest();
		inputRequest();
		outputRequest();
	}
}
void Screen::disconnect( ){
	if ( qbox_){
		//QboxMgr::instance()->removeQbox(qbox_->address()); qbox_ = NULL;
		qbox_->close();
	}
}
//bool Screen::isInputValid( ResourceID inputid){ 
//	auto found = inPort_.find(inputid) ;
//	if (  found == inPort_.end()  || (found->second != 0 && found->second != -1)){
//		return false;
//	}else return true;
//}
bool Screen::isOutputRingValid( ResourceID outputid){ 
	auto found = outPortRing_.find(outputid) ;
	if (  found == outPortRing_.end()  ||  (found->second != 0 && found->second != -1)){
		return false;
	}else return true;
}
std::vector<ResourceID> Screen::getAvailableInput(){
	std::vector<ResourceID> inputs;
	for ( auto it = inPort_.begin(); it != inPort_.end(); ++it){
		if ( it->second != 0 && it->second != -1){
			inputs.push_back( it->first);
		}
	}
	return inputs;
}
//=======================================================TEST===============================================================
void Screen::setupTestResource(){
	inPort_[ ToResourceID( 1, 0, row_, col_)] = (1024 << 16) | 768;
	inPort_[ ToResourceID( 2, 0, row_, col_)] = (1024 << 16) | 768;
	inPort_[ ToResourceID( 3, 0, row_, col_)] = (1024 << 16) | 768;
	inPort_[ ToResourceID( 4, 0, row_, col_)] = (1024 << 16) | 768;
}
void Screen::ajustResolution(){
	inPort_[ ToResourceID( 1, 0, row_, col_)] = (800 << 16) | 600;
	inPort_[ ToResourceID( 2, 0, row_, col_)] = (800 << 16) | 600;
}
void Screen::ajustInput(){
	inPort_[ ToResourceID( 1, 0, row_, col_)] = 0;

}
//=======================================================OSD===============================================================
void Screen::osdRequestRead(uint32_t addr, const uint32_t len, QboxCallback callback, uint32_t device){
	QboxDataMap datamap;
	datamap["addr"] = QString::number( addr).toStdString();
	datamap["len"] = QString::number(len).toStdString();
	datamap["device"] = QString::number(device).toStdString();
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


//=======================================================ScreenMgr===============================================================

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
	screenWidth_ = 1024;
	screenHeight_ = 768;


	for( size_t i = 0 ; i < MAXROW; ++i){
		for( size_t j = 0 ; j < MAXCOL; ++j){
			screens_[i][j] = NULL;
		}
	}
}
ScreenMgr::~ScreenMgr()
{
}

void ScreenMgr::run(){
	for( size_t i = 0 ; i < rowCount_; ++i){
		for( size_t j = 0 ; j < colCount_; ++j){
			screens_[i][j]->run();
		}
	}
}

void ScreenMgr::onInputChanged(ResourceChangedCallback callback){
	inputChangedCallbacks_.push_back(callback);
}

bool ScreenMgr::isInputValid( ResourceID inputid){ 
	uint32_t row, col, input;
	row = GetRow(inputid);
	col = GetCol(inputid);
	input = GetInput(inputid);
	if ( row <=0) return false;
	else if ( col <=0) return false;
	else if ( input <=0) return false;
	else if ( input <=6) return true;
	else return false;
}
bool ScreenMgr::isOutputRingValid( ResourceID outputid){ 
	uint32_t row, col, output;
	row = GetRow(outputid);
	col = GetCol(outputid);
	output = GetOutput(outputid);
	if ( row <=0) return false;
	if ( col <=0) return false;
	if ( output <=0) return false;
	Screen* s = screens_[row-1][col-1];
	if (s == NULL) return false;
	return s->isOutputRingValid(outputid); 
}

std::vector<ResourceID> ScreenMgr::getAvailableInput(){
	std::vector<ResourceID> inputs, tmp;
	for( size_t i = 0 ; i < rowCount_; ++i){
		for( size_t j = 0 ; j < colCount_; ++j){
			tmp = screens_[i][j]->getAvailableInput();
			inputs.insert( inputs.end(), tmp.begin(), tmp.end());
		}
	}
	return inputs;
}
bool ScreenMgr::hasAvailableInput(ResourceID inputid){
	std::vector<ResourceID> inputs = getAvailableInput();
	for( size_t i = 0 ; i < inputs.size(); ++i){
		if ( inputs[i] == inputid){
			return true;
		}
	}
	return false;
}
void ScreenMgr::closeAllWnds(){
	for( size_t i = 0 ; i < rowCount_; ++i){
		for( size_t j = 0 ; j < colCount_; ++j){
			Screen * scrn = screens_[i][j];
			if (scrn){
				scrn->closeAllWndRequest();
			}
		}
	}
}

void ScreenMgr::setupTest(){

	for( size_t i = 0 ; i < rowCount_; ++i){
		for( size_t j = 0 ; j < colCount_; ++j){
			screens_[i][j]->setupTestResource();
		}
	}
}
std::vector<ResourceID> ScreenMgr::clearWall(){

	std::vector<ResourceID> scrns ;
	for( size_t i = 0 ; i < MAXROW; ++i){
		for( size_t j = 0 ; j < MAXCOL; ++j){
			if ( screens_[i][j]){
				scrns.push_back(ToScreenID(i+1, j+1));
				delete screens_[i][j];
			}
			screens_[i][j] = NULL;
		}
	}
	colCount_ = rowCount_ =0;
	return scrns;
}


ResourceID ScreenMgr::occupyScreenOut( ResourceID inputid){
	Screen* screen = screens_[GetRow(inputid)-1][GetCol(inputid)-1];
	for ( auto it = screen->outPort753_.begin(); it != screen->outPort753_.end(); ++it){
		if ( it->second == 0){
			ResourceID wnode = ToResourceID( GetInput(inputid), GetOutput(it->first), GetRow(inputid), GetCol(inputid));
			it->second = wnode;
			return wnode;
		}
	}
}

std::vector<ResourceID> ScreenMgr::occupyScreensOut( std::vector<ResourceID> &rnodes){
	std::vector<ResourceID> outputs ;
	std::vector<ResourceID> wnodes ;
	for ( int i = 0; i < rnodes.size(); ++i){
		Screen* screen = screens_[GetRow(rnodes[i])-1][GetCol(rnodes[i])-1];
		for ( auto it = screen->outPort753_.begin(); it != screen->outPort753_.end(); ++it){
			if ( it->second == 0){
				outputs.push_back( it->first);
				break;
			}
		}
	}
	if (outputs.size() != rnodes.size() ){
		return wnodes;
	}
	for ( int i = 0; i < outputs.size(); ++i){
		Screen* screen = screens_[GetRow(outputs[i])-1][GetCol(outputs[i])-1];
		wnodes.push_back(ToResourceID( GetInput(rnodes[i]), GetOutput(outputs[i]), GetRow(rnodes[i]), GetCol(rnodes[i])));
		screen->outPort753_[outputs[i]] = wnodes[i];
	}

	return wnodes;
}

void ScreenMgr::freeScreensOut(std::vector<ResourceID> &wnodes){
	for ( int i = 0; i < wnodes.size(); ++i){
		Screen* screen = screens_[GetRow(wnodes[i])-1][GetCol(wnodes[i])-1];
		for ( auto it = screen->outPort753_.begin(); it != screen->outPort753_.end(); ++it){
			if ( it->second == wnodes[i]){
				if ( screen->qbox_){
					QboxDataMap value;
					value["out"] = QString::number(GetOutput(wnodes[i]) ).toStdString();
					screen->qbox_->addAsyncRequest( PDelWindowsReq::uri , std::bind( ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
				}
				it->second = 0;
				break;
			}
		}
	}
}
void ScreenMgr::freeScreenOut(ResourceID wnode){

	Screen* screen = screens_[GetRow(wnode)-1][GetCol(wnode)-1];
	for ( auto it = screen->outPort753_.begin(); it != screen->outPort753_.end(); ++it){
		if ( it->second == wnode){
			if ( screen->qbox_){
				QboxDataMap value;
				value["out"] = QString::number(GetOutput(wnode) ).toStdString();
				screen->qbox_->addAsyncRequest( PDelWindowsReq::uri , std::bind( ignoreCallback, std::placeholders::_1, std::placeholders::_2), value);
			}
			it->second = 0;
			break;
		}
	}
}