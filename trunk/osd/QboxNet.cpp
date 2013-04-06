#include "QboxNet.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>


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
	typedef std::map<std::string, Qbox*> SocketMap;
	SocketMap sockets_;
	Impl():thread_(0){
	}
	~Impl(){
		if ( thread_){
			thread_->join();
			delete thread_;
		}
	}

};
bool QboxMgr::hasQbox(std::string & ip){	
	return impl_->sockets_.find(ip)!= impl_->sockets_.end();
}
Qbox* QboxMgr::getQbox(std::string & ip){	
	auto found = impl_->sockets_.find(ip);
	if ( found == impl_->sockets_.end() ){
		Qbox * q = new Qbox();
		impl_->sockets_.insert( std::make_pair( ip, q));
		return q;
	}
	return found->second;
}
bool QboxMgr::removeQbox( std::string &ip){
	auto found = impl_->sockets_.find(ip);
	if ( found == impl_->sockets_.end() ){
		return false;
	}
	delete found->second;
	impl_->sockets_.erase(found);
	return true;
}
  
void QboxMgr::stop(){	
	impl_->running_ = false;
	if (impl_->thread_){
		impl_->thread_->join();
		delete impl_->thread_;
		impl_->thread_ = 0;
	}
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
	
	delete impl_;
}

static void testCallback( uint32_t , QboxDataMap&){
	qDebug()<<"testCallback";
}

void QboxMgr::startThread(){
	impl_->running_ = true;
	startTimer(10);
	impl_->thread_ = new asio::thread( boost::bind(&asio::io_service::run, &impl_->socketios_ ) );

	//connect( std::string("127.0.0.1"), boost::bind( testCallback, _1, _2), QboxDataMap() );
}

//bool QboxMgr::isConnected( std::string &ip){
//	Impl::SocketMap::iterator found = impl_->sockets_.find( ip);
//	if ( found != impl_->sockets_.end()){
//		tcp::socket * s = found->second;
//	}
//}



void QboxMgr::timerEvent ( QTimerEvent *  ){

	//static RequestList doingList;
	//doingList.clear();
	//{
	//	if ( ! impl_->responsedList_.empty()){
	//		QMutexLocker lk(&impl_->getLock_);
	//		doingList.assign( impl_->responsedList_.begin(), impl_->responsedList_.end() );
	//		impl_->responsedList_.clear();
	//	}
	//}
	//BOOST_FOREACH( QboxObj* obj, doingList){
	//	if ( !obj->responsed.empty()){
	//		obj->callback( obj->msg.msgType, obj->msg.info);
	//	}
	//}
	//for ( auto it = impl_->sockets_.begin(); it != impl_->sockets_.end(); ++it){
	//	it->second->mainThreadRun();
	//}
	impl_->mainios_.run_one();
}

//void QboxMgr::addAsyncRequestMulticast( uint32_t msgtype ,/* QboxCallbackFunc callback,*/ QboxDataMap &value ){
	//if ( strlen( objid) ){
	//	QboxObj* so = new QboxObj(  std::string(obj), currAddress_, callback);
	//	so->var = value;
	//	QMutexLocker lk(&getLock_);

	//	RequestMap::iterator found = requestMap_.find( so->snmpoid );
	//	if ( found != requestMap_.end()  ){
	//		requestMap_.erase(found);
	//	}
	//	requestMap_.insert( std::make_pair( so->snmpoid,  so));
	//}
//}





struct Qbox::Impl{
	tcp::socket socket_;
	std::string ip_;
	asio::io_service* mainios_;
	bool isConnected_;

	static const uint32_t CONSTLEN = 1024;
	char responsed_[CONSTLEN];
	uint32_t receiveLen ;
	std::string sendBuf;
	typedef std::list<QboxObj*> RequestList;
	RequestList requestList_;
	
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

	inline void asyncConnect(){
		socket_.async_connect( asio::ip::tcp::endpoint(asio::ip::address::from_string(ip_), 5000 ),boost::bind(&Qbox::Impl::handleConnected, this, asio::placeholders::error) );
	}
	inline void asyncReceive(){
		socket_.async_receive(  asio::buffer(responsed_, CONSTLEN), boost::bind(&Qbox::Impl::handleRead, this, asio::placeholders::error, asio::placeholders::bytes_transferred) );
	}
	inline void asyncSend(std::string & data){
		socket_.async_send(asio::buffer( data) , boost::bind(&Qbox::Impl::handleWrite, this, asio::placeholders::error, asio::placeholders::bytes_transferred, data.length() ) );
	}
	void handleWrite( const asio::error_code& err, std::size_t bytes_transferred, size_t requestSize ){
		if ( !err  ){
			if ( requestSize != bytes_transferred){
				qDebug()<<"***Error: handleWrite: no all of data send out!";
				return;
			}
			qDebug()<<"handleWrite: "<<bytes_transferred;
			asyncReceive();
		}else{
			
			isConnected_ = false;
		}
	}
	void handleRead( const asio::error_code& err, std::size_t bytes_transferred ){
		if ( !err){
			qDebug()<<"handleRead: "<<bytes_transferred;
			uint32_t len = 0, move = 0, msgtype = 0;
			
			while( move < bytes_transferred){
				memcpy((void*)&len,(const void*)(responsed_ + move + 4),4);
				memcpy((void*)&msgtype,(const void*)(responsed_ + HEAD_SIZE),sizeof(msgtype));
				MsgInfo msg = decodeData( responsed_ + move, len +8);
				mainios_->post( boost::bind( &Qbox::Impl::dispatchResponse, this, msg) );
				move+=len+8;
			}
			//没找到再读一下
			asyncReceive();
		}else{
			isConnected_ = false;
		}
	}

	void dispatchResponse(MsgInfo msg){

		for( RequestList::iterator it = requestList_.begin(); it != requestList_.end(); ){
			QboxObj* obj = *it;
			if ( obj->sendmsg_.msgType +1 == msg.msgType && obj->callback_ (msg.msgType, msg.info)){ //要CALLBACK确认是正常才可以删除
				delete obj;
				it  = requestList_.erase( it);
			}else{
				++it;
			}
		}

	}
	void loopAsyncRequest(){
		BOOST_FOREACH( QboxObj* obj, requestList_){
			std::string data = encodeData( obj->sendmsg_);
			asyncSend( data);
		}
	}

	void handleConnected( const asio::error_code& err){
		if ( !err){
			qDebug()<<"handleConnected";
			isConnected_ = true;
			mainios_->post( boost::bind( &Qbox::Impl::loopAsyncRequest, this) );
		}else{
			isConnected_ = false;
		}
	}

	void addAsyncRequest( uint32_t msgtype , QboxCallbackFunc callback, QboxDataMap& value ){
		QboxObj * so = new QboxObj( msgtype , callback, value);
		requestList_.push_back(so);
	}

	void connInit(std::string & ip){
		ip_ = ip;
		if ( ! isConnected_){
			asyncConnect();
		}
	}

	Impl():
	socket_( QboxMgr::instance()->impl_->socketios_)
	,mainios_( &QboxMgr::instance()->impl_->mainios_)
	,receiveLen(0)
	,isConnected_(false){
	}
};

std::string Qbox::address(){
	return impl_->ip_;
}

Qbox::Qbox():
impl_(new Qbox::Impl)
{}
	

void Qbox::addAsyncRequest( uint32_t msgtype , QboxCallbackFunc callback, QboxDataMap& value ){
	impl_->addAsyncRequest(msgtype, callback, value);
}
void Qbox::connInit(std::string & ip){
	impl_->connInit(ip);
}
