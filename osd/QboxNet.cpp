#include "QboxNet.h"
#include <QtDebug>
#include <asio.hpp>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;





class QboxObj{
public:
	QboxObj(uint32_t msgtype, QboxCallback callback, QboxDataMap& var ):
	callback_(callback){
		sendmsg_.msgType = msgtype;
		sendmsg_.info = var;
	}
	QboxCallback callback_;
	MsgInfo sendmsg_;
};

struct QboxMgr::Impl{
	
	
	asio::thread* thread_;
	volatile bool running_;
	asio::io_service socketios_;
	asio::io_service mainios_;
	asio::io_service::work* work_;
	typedef std::vector<Qbox*> SocketMap;
	SocketMap qboxes_;
	SocketMap removeQboxs_;
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
			try{
			for ( auto it = qboxes_.begin(); it != qboxes_.end(); ++it){
				(*it)->close();
			}
			delete work_;
			socketios_.stop();
			mainios_.stop();
			thread_->join();
			delete thread_;
			thread_ = 0;
			}catch( std::exception &e){
				qDebug()<<e.what();
			}
		}
	}
};

void QboxMgr::threadRun(){
	try{
		impl_->socketios_.run();
	}catch( std::exception &e){
		qDebug()<<"QboxMgr::threadRun: "<<e.what();
	}
}

bool QboxMgr::hasQbox(const std::string & ip){	
	BOOST_FOREACH( Qbox* q, impl_->qboxes_){
		if ( q->address() == ip){
			return true;
		}
	}
	return false;
}
Qbox* QboxMgr::getQbox(const std::string & ip){	
	BOOST_FOREACH( Qbox* q, impl_->qboxes_){
		if ( q->address() == ip){
			return q;
		}
	}
	return NULL;
}
Qbox* QboxMgr::createQbox(const std::string & ip){	
	BOOST_FOREACH( Qbox* q, impl_->qboxes_){
		if ( q->address() == ip){
			return q;
		}
	}
	Qbox * q;
	if ( impl_->removeQboxs_.empty()){
		q = new Qbox();
	}else{
		q = impl_->removeQboxs_.back();
		impl_->removeQboxs_.pop_back();
	}
	q->setAddress(ip);
	impl_->qboxes_.push_back(q);
	return q;
}

bool QboxMgr::removeQbox(const  std::string &ip){
	for( auto it = impl_->qboxes_.begin(); it != impl_->qboxes_.end(); ++it ){
		if ( (*it)->address() == ip){
			(*it)->close();
			impl_->removeQboxs_.push_back( *it);
			//delete (*it);
			impl_->qboxes_.erase(it);
			return true;
		}
	}
	return false;
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
	BOOST_FOREACH( Qbox* q, impl_->qboxes_){
		delete q;
	}
	BOOST_FOREACH( Qbox* q, impl_->removeQboxs_){
		delete q;
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
		if ( !socket_.is_open()){
			socket_.open( asio::ip::tcp::v4()  );
		}
		socket_.async_connect( asio::ip::tcp::endpoint(asio::ip::address::from_string(ip_), 5000 ),boost::bind(&Qbox::Impl::handleConnected, this, asio::placeholders::error) );
	}
	void asyncReceive(){
		socket_.async_receive(  asio::buffer(responsed_, CONSTLEN), boost::bind(&Qbox::Impl::handleReceived, this, asio::placeholders::error, asio::placeholders::bytes_transferred) );
	}
	void asyncSend(std::string & data){
				std::stringstream ss;
				static char syms[] = "0123456789ABCDEF";
				for (size_t it = 0; it < data.length(); it++){
					ss << syms[((data[it] >> 4) & 0xf)] << syms[data[it] & 0xf] << ' ';
				}
				qDebug()<<"send: "<< ss.str().c_str();

		socket_.async_send(asio::buffer( data.c_str(), data.length() ) , boost::bind(&Qbox::Impl::handleSent, this, asio::placeholders::error, asio::placeholders::bytes_transferred ) );
	}
	void handleSent( const asio::error_code& err, std::size_t /*bytes_transferred*/ ){
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
			//qDebug()<<"test";
			while( move < bytes_transferred){


				memcpy((void*)&len,(const void*)(responsed_ + move + 4),4);
				memcpy((void*)&msgtype,(const void*)(responsed_ + HEAD_SIZE),sizeof(msgtype));
				MsgInfo msg = decodeData( responsed_ + move, len +8);
				//qDebug()<<"test1";
				//qDebug()<<bytes_transferred;
				std::stringstream ss;
				static char syms[] = "0123456789ABCDEF";
				for (size_t it = move; it < bytes_transferred; it++){
					ss << syms[((responsed_[it] >> 4) & 0xf)] << syms[responsed_[it] & 0xf] << ' ';
				}
				qDebug()<< "receive: "<<ss.str().c_str();
				
				mainios_->post( boost::bind( &Qbox::Impl::dispatchResponse, this, msg) );
				//qDebug()<<"test2";
				move+=len+8;
			}
			memset(responsed_, 0,bytes_transferred);
			//qDebug()<<"test3";
			//到再读一下
			asyncReceive();
		}else{
			qDebug()<<"***Error handleReceived: "<<bytes_transferred;
			isConnected_ = false;
		}
	}

	void dispatchResponse(MsgInfo msg){
		RequestList foundList;
		for( RequestList::iterator it = sentList_.begin(); it != sentList_.end(); ){
			QboxObj* obj = *it;
			if ( obj->sendmsg_.msgType +1 == msg.msgType ){ //要CALLBACK确认是正常才可以删除
				it  = sentList_.erase( it);
				foundList.push_back( obj);
				qDebug()<<"erase send";
			}else{
				++it;
			}
		}
		if (! foundList.empty()){
			for( RequestList::iterator it = foundList.begin(); it != foundList.end();){
				QboxObj* obj = *it;
				if ( obj->callback_( msg.msgType, msg.info)){
					it = foundList.erase( it);
					delete obj;
					qDebug()<<"erase found";
				}
				else{
					++it;
					sentList_.push_back(obj);
				}
			}
		}else{
			return;
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
			//qDebug()<<"handleConnected";
			isConnected_ = true;
			mainios_->post( boost::bind( &Qbox::Impl::asyncRequest, this) );
			asyncReceive();
		}else{
			isConnected_ = false;
		}
	}

	void addAsyncRequest( uint32_t msgtype , QboxCallback callback, QboxDataMap& value ){
		//if ( !isConnected_ ) return false;
		QboxObj * so = new QboxObj( msgtype , callback, value);
		requestList_.push_back(so);
		asyncRequest();
		//return true;
	}

	void connInit(){
		if ( ! isConnected_ && !ip_.empty() ){
			asyncConnect();
			requestList_.clear();
			sentList_.clear();
		}
	}

	Impl():
	socket_( QboxMgr::instance()->impl_->socketios_)
	,ip_()
	,mainios_( &QboxMgr::instance()->impl_->mainios_)
	,receiveLen(0)
	,isConnected_(false){
		
	}
	~Impl(){
		close();
		ip_.clear();
		mainios_ = 0;
	}
	void close(){
		if ( socket_.is_open() ){
			socket_.close();
		}
		if ( isConnected_){
			isConnected_ = false;
		}
		BOOST_FOREACH( QboxObj* obj , requestList_){
			delete obj;
		}
		requestList_.clear();
		BOOST_FOREACH( QboxObj* obj , sentList_){
			delete obj;
		}
		sentList_.clear();
	}
};

void Qbox::close(){
	impl_->close();
}

std::string Qbox::address(){
	return impl_->ip_;
}
void Qbox::setAddress(const std::string& ip){
	impl_->ip_ = ip;
}

Qbox::Qbox()
	:impl_(new Qbox::Impl() )
{
}
Qbox::~Qbox(){
	delete impl_;
}
	

void Qbox::addAsyncRequest( uint32_t msgtype , QboxCallback callback, QboxDataMap& value ){
	impl_->addAsyncRequest(msgtype, callback, value);
}
void Qbox::connInit(){
	impl_->connInit();
}

bool Qbox::isConn(){
	return impl_->isConnected_;
}







