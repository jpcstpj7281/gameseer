#include "QboxNet.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;





class QboxObj{
public:
	QboxObj(uint32_t msgtype, QboxCallbackFunc callback, QboxDataMap& var ):
	callback_(callback){
		sendmsg_.msgType = msgtype;
		sendmsg_.info = var;
	}
	QboxCallbackFunc callback_;
	MsgInfo sendmsg_;
};

struct QboxMgr::Impl{
	
	
	asio::thread* thread_;
	volatile bool running_;
	asio::io_service socketios_;
	asio::io_service mainios_;
	asio::io_service::work* work_;
	typedef std::map<std::string, Qbox*> SocketMap;
	SocketMap qboxes_;
	Impl():thread_(0)
	,socketios_()
	,work_( new asio::io_service::work(socketios_)){
		
	}
	~Impl(){
		stop();
	}
	void stop(){
		running_ = false;
		if (thread_){
			for ( auto it = qboxes_.begin(); it != qboxes_.end(); ++it){
				it->second->close();

			}
			delete work_;
			socketios_.stop();
			mainios_.stop();
			thread_->join();
			delete thread_;
			thread_ = 0;
		}
	}
};

void QboxMgr::threadRun(){
	try{
		impl_->socketios_.run();
	}catch( std::exception &e){
		qDebug()<<e.what();
	}
}

bool QboxMgr::hasQbox(const std::string & ip){	
	return impl_->qboxes_.find(ip)!= impl_->qboxes_.end();
}
Qbox* QboxMgr::getQbox(const std::string & ip){	
	auto found = impl_->qboxes_.find(ip);
	if ( found == impl_->qboxes_.end() ){
		Qbox * q = new Qbox(ip);
		impl_->qboxes_.insert( std::make_pair( ip, q));
		return q;
	}
	return found->second;
}
bool QboxMgr::removeQbox(const  std::string &ip){
	auto found = impl_->qboxes_.find(ip);
	if ( found == impl_->qboxes_.end() ){
		return false;
	}
	delete found->second;
	impl_->qboxes_.erase(found);
	return true;
}


QboxMgr* QboxMgr::inst = 0;
QboxMgr *QboxMgr::instance(){
	if ( inst) return inst;
	return inst = new QboxMgr();
}
QboxMgr::QboxMgr():
impl_(new Impl)
{
}
QboxMgr::~QboxMgr()
{
	for ( auto it = impl_->qboxes_.begin(); it != impl_->qboxes_.end(); ++it){
		delete it->second;
	}
	delete impl_;
}

static void testCallback( uint32_t , QboxDataMap&){
	qDebug()<<"testCallback";
}

void QboxMgr::startThread(){
	impl_->running_ = true;
	startTimer(10);
	impl_->thread_ = new asio::thread( boost::bind(&QboxMgr::threadRun, this ) );

	//connect( std::string("127.0.0.1"), boost::bind( testCallback, _1, _2), QboxDataMap() );
}

void QboxMgr::timerEvent ( QTimerEvent *  ){
	impl_->mainios_.run_one();
}

void QboxMgr::stop(){	
	impl_->stop();
}


struct Qbox::Impl{
	tcp::socket socket_;
	std::string ip_;
	asio::io_service* mainios_;
	volatile bool isConnected_;

	static const uint32_t CONSTLEN = 1024;
	char responsed_[CONSTLEN];
	uint32_t receiveLen ;
	std::string sendBuf;
	typedef std::list<QboxObj*> RequestList;
	RequestList requestList_;
	RequestList sentList_;
	
	inline std::string encodeData(MsgInfo & msg){
		NetMsgBody netMsg;
		MsgBase msgBase;
		msgBase.setMsgInfo(&msg);
		msgBase.setNetMsgBody(&netMsg);
		msgBase.packMsg(netMsg);
		string sendBuff;
		sendBuff.append((const char* )&netMsg,sizeof(NetMsgHead));
		sendBuff.append((const char* )&netMsg.msgType,sizeof(uint32_t));
		sendBuff.append((const char* )netMsg.msgData.c_str(),netMsg.msgData.size());
		return sendBuff;
	}
	inline MsgInfo decodeData(char* buf, uint32_t bufsize){
		MsgInfo inmsg;
		NetMsgBody netMsg;
		const char * buff = buf;
		uint32_t buffLen = bufsize;
		uint32_t move =  sizeof(netMsg.msgHead);
		memcpy((void*)&netMsg,(const void*)buff,sizeof(netMsg.msgHead));
		memcpy((void*)&netMsg.msgType,(const void*)(buff+move),sizeof(netMsg.msgType));
		move +=  sizeof(netMsg.msgType);
		netMsg.msgData.append((const char*)buff+move,buffLen-move);
		MsgBase msgBase;
		msgBase.setMsgInfo(&inmsg);
		msgBase.setNetMsgBody(&netMsg);
		msgBase.UnpackMsg(inmsg);
		return inmsg;
	}

	void asyncConnect(){
		socket_.async_connect( asio::ip::tcp::endpoint(asio::ip::address::from_string(ip_), 5000 ),boost::bind(&Qbox::Impl::handleConnected, this, asio::placeholders::error) );
	}
	void asyncReceive(){
		socket_.async_receive(  asio::buffer(responsed_, CONSTLEN), boost::bind(&Qbox::Impl::handleReceived, this, asio::placeholders::error, asio::placeholders::bytes_transferred) );
	}
	void asyncSend(std::string & data){
		socket_.async_send(asio::buffer( data.c_str(), data.length() ) , boost::bind(&Qbox::Impl::handleSent, this, asio::placeholders::error, asio::placeholders::bytes_transferred ) );
	}
	void handleSent( const asio::error_code& err, std::size_t bytes_transferred ){
		if ( !err  ){
			//qDebug()<<"handleSent: "<<bytes_transferred;
		}else{
			qDebug()<<"***Error: handleSent: " << err.value();
			isConnected_ = false;
		}
	}
	void handleReceived( const asio::error_code& err, std::size_t bytes_transferred ){
		if ( !err){
			//qDebug()<<"handleReceived: "<<bytes_transferred;
			uint32_t len = 0, move = 0, msgtype = 0;
			
			while( move < bytes_transferred){
				memcpy((void*)&len,(const void*)(responsed_ + move + 4),4);
				memcpy((void*)&msgtype,(const void*)(responsed_ + HEAD_SIZE),sizeof(msgtype));
				MsgInfo msg = decodeData( responsed_ + move, len +8);
				mainios_->post( boost::bind( &Qbox::Impl::dispatchResponse, this, msg) );
				move+=len+8;
			}
			//到再读一下
			asyncReceive();
		}else{
			qDebug()<<"***Error handleReceived: "<<bytes_transferred;
			isConnected_ = false;
		}
	}

	void dispatchResponse(MsgInfo msg){
		for( RequestList::iterator it = sentList_.begin(); it != sentList_.end(); ){
			QboxObj* obj = *it;
			if ( obj->sendmsg_.msgType +1 == msg.msgType && obj->callback_ (msg.msgType, msg.info)){ //要CALLBACK确认是正常才可以删除
				delete obj;
				it  = sentList_.erase( it);
			}else{
				++it;
			}
		}
	}

	void asyncRequest(){
		if ( !isConnected_  ) return;
		if (requestList_.size() > 0){
			BOOST_FOREACH( QboxObj* obj, requestList_){
				std::string data = encodeData( obj->sendmsg_);
				asyncSend( data);
			}
			sentList_ = requestList_;
			requestList_.clear();
		}
	}

	void handleConnected( const asio::error_code& err){
		if ( !err){
			qDebug()<<"handleConnected";
			isConnected_ = true;
			mainios_->post( boost::bind( &Qbox::Impl::asyncRequest, this) );
			asyncReceive();
		}else{
			isConnected_ = false;
		}
	}

	void addAsyncRequest( uint32_t msgtype , QboxCallbackFunc callback, QboxDataMap& value ){
		//if ( !isConnected_ ) return false;
		QboxObj * so = new QboxObj( msgtype , callback, value);
		requestList_.push_back(so);
		asyncRequest();
		//return true;
	}

	void connInit(){
		if ( ! isConnected_){
			asyncConnect();
		}
	}

	Impl( const std::string & ip):
	socket_( QboxMgr::instance()->impl_->socketios_)
	,ip_(ip)
	,mainios_( &QboxMgr::instance()->impl_->mainios_)
	,receiveLen(0)
	,isConnected_(false){
		
	}

	
};
void Qbox::close(){
	impl_->socket_.close();
}
std::string Qbox::address(){
	return impl_->ip_;
}

Qbox::Qbox(const std::string &ip)
	:impl_(new Qbox::Impl(ip) )
{
	connInit();
}
Qbox::~Qbox(){
	delete impl_;
}
	

void Qbox::addAsyncRequest( uint32_t msgtype , QboxCallbackFunc callback, QboxDataMap& value ){
	impl_->addAsyncRequest(msgtype, callback, value);
}
void Qbox::connInit(){
	impl_->connInit();
}

bool Qbox::isConn(){
	return impl_->isConnected_;
}







