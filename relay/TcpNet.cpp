#include "TcpNet.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>


using asio::ip::tcp;





struct Host::Impl{
	tcp::socket socket_;
	std::string ip_;
	int port_;
	asio::io_service* mainios_;
	volatile bool isConnected_;

	static const uint32_t CONSTLEN = 1024;
	char responsed_[CONSTLEN];
	uint32_t receiveLen ;
	std::string sendBuf;
	typedef std::list<NetObj*> RequestList;
	RequestList requestList_;
	RequestList sentList_;
	RequestList listenList_;
	asio::deadline_timer timer_;
	
	inline std::string encodeData(std::string & data){
		return data;
		
	}
	inline std::string decodeData(char* buf, uint32_t bufsize){
		return std::string( buf, buf+bufsize);
	}

	void handleConnectFailed(){
		if ( !isConnected_){
			if ( socket_.is_open() ){
				qDebug()<<"***Error: handleConnectFailed! "<<this->ip_.c_str();
				socket_.close();
			}
		}
	}

	void asyncConnect(){
		if ( !socket_.is_open()){
			socket_.open( asio::ip::tcp::v4()  );
		}
		socket_.async_connect( asio::ip::tcp::endpoint(asio::ip::address::from_string(ip_), port_ ),boost::bind(&Host::Impl::handleConnected, this, asio::placeholders::error) );
		timer_.expires_from_now(boost::posix_time::seconds(3));  
        timer_.async_wait(boost::bind(&Host::Impl::handleConnectFailed, this));  
	}
	void asyncReceive(){
		socket_.async_receive(  asio::buffer(responsed_, CONSTLEN), boost::bind(&Host::Impl::handleReceived, this, asio::placeholders::error, asio::placeholders::bytes_transferred) );
	}
	void asyncSend(std::string & data){
		socket_.async_send(asio::buffer( data.c_str(), data.length() ) , boost::bind(&Host::Impl::handleSent, this, asio::placeholders::error, asio::placeholders::bytes_transferred ) );
		qDebug()<<"asyncSend: "<<data.c_str();
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
				//std::string msg = decodeData( responsed_ , bytes_transferred);
				//std::stringstream ss;
				//static char syms[] = "0123456789ABCDEF";
				//for (int it = move; it < bytes_transferred; it++){
				//	ss << syms[((responsed_[it] >> 4) & 0xf)] << syms[responsed_[it] & 0xf] << ' ';
				//}
				//qDebug()<< ss.str().c_str();
				std::string msg( responsed_, responsed_+bytes_transferred);
				qDebug()<<"handleReceived: "<<msg.c_str();
				mainios_->post( boost::bind( &Host::Impl::dispatchResponse, this, std::move(msg) ));
				//qDebug()<<"test2";
				move+=bytes_transferred;
			}
			//到再读一下
			asyncReceive();
		}else{
			qDebug()<<"***Error handleReceived: "<<bytes_transferred;
			isConnected_ = false;
            mainios_->post( boost::bind( &Host::Impl::asyncRequest, this) );
		}
	}
#ifdef WIN32
	void dispatchResponse( std::string msg){
		dispatchResponseImpl( &msg);
	}
#else
	void dispatchResponse( std::string&& msg){
		dispatchResponseImpl( &msg);
	}
#endif
	void dispatchResponseImpl( const std::string *msg){

		RequestList tmpList = listenList_;
		listenList_.clear();
		for( RequestList::iterator it = tmpList.begin(); it != tmpList.end(); ){
			NetObj* obj = *it;
			if ( obj->callback_(*msg)){ //要CALLBACK确认是正常才可以删除
				it  = tmpList.erase( it);
				delete obj;
			}else{
				++it;
			}
		}
		listenList_.insert(listenList_.end(), tmpList.begin(), tmpList.end());

		tmpList = sentList_;
		sentList_.clear();
		for( RequestList::iterator it = tmpList.begin(); it != tmpList.end(); ){
			NetObj* obj = *it;
			if ( obj->callback_(*msg)){ //要CALLBACK确认是正常才可以删除
				it  = tmpList.erase( it);
				delete obj;
			}else{
				++it;
			}
		}
		sentList_.insert(sentList_.end(), tmpList.begin(), tmpList.end());
	}

	void asyncRequest(){
		
		if ( isConnected_){
			BOOST_FOREACH( NetObj* obj, requestList_){
				std::string data = encodeData( obj->sendmsg_);
				asyncSend( data);
			}
			sentList_ = requestList_;
			requestList_.clear();
		}else{
			//dont have to release resouces here, callback maybe will delete this host obj by it own.
			RequestList tmpList = requestList_;
			if ( tmpList.size() > 0){
				tmpList.front()->callback_( HOST_CONNECT_FAILED);
			}
		}
	}

	void handleConnected( const asio::error_code& err){
		if ( !err){
			//qDebug()<<"handleConnected";
			isConnected_ = true;
			timer_.cancel();
			mainios_->post( boost::bind( &Host::Impl::asyncRequest, this) );
			asyncReceive();
		}else{
			isConnected_ = false;
			mainios_->post( boost::bind( &Host::Impl::asyncRequest, this) );
		}
	}

	void addAsyncRequest( NetCallback callback, std::string&& data ){
		//if ( !isConnected_ ) return ;
		NetObj * so = new NetObj( callback, std::move(data));
		requestList_.push_back(so);
		if ( isConnected_ )
			asyncRequest();
	}

	void addListener( NetCallback callback){
		//if ( !isConnected_ ) return ;
		NetObj * so = new NetObj( callback, std::move(std::string("")));
		listenList_.push_back(so);
	}

	void connInit(){
		if ( ! isConnected_ && !ip_.empty() ){
			asyncConnect();
			requestList_.clear();
			sentList_.clear();
		}
	}

	Impl():
	socket_( *TcpNet::instance()->getScoketService())//->socketios_)
	,ip_()
	,mainios_( TcpNet::instance()->getMainService() )
	,receiveLen(0)
	,isConnected_(false)
	,port_(1698)
	,timer_(*TcpNet::instance()->getScoketService()){
		
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
		BOOST_FOREACH( NetObj* obj , requestList_){
			delete obj;
		}
		requestList_.clear();
		BOOST_FOREACH( NetObj* obj , sentList_){
			delete obj;
		}
		sentList_.clear();
	}
};

void Host::close(){
	impl_->close();
}

std::string Host::address(){
	return impl_->ip_;
}
void Host::setAddress(const std::string& ip){
	impl_->ip_ = ip;
}

Host::Host()
	:impl_(new Host::Impl() )
{
}
Host::~Host(){
	delete impl_;
}
	
void Host::addListener( NetCallback callback){
	impl_->addListener(callback);
}

void Host::addAsyncRequest(  NetCallback callback, std::string&& data){
	impl_->addAsyncRequest(callback, std::move(data));
}
void Host::connInit(){
	impl_->connInit();
}

bool Host::isConn(){
	return impl_->isConnected_;
}





struct TcpNet::Impl{
	
	
	asio::thread* thread_;
	volatile bool running_;
	asio::io_service socketios_;
	asio::io_service mainios_;
	asio::io_service::work* work_;
	typedef std::vector<Host*> SocketMap;
	SocketMap qboxes_;
	SocketMap removeHosts_;
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

void TcpNet::threadRun(){
	try{
		impl_->socketios_.run();
	}catch( std::exception &e){
		qDebug()<<"TcpNet::threadRun: "<<e.what();
	}
}

bool TcpNet::hasHost(const std::string & ip){	
	BOOST_FOREACH( Host* q, impl_->qboxes_){
		if ( q->address() == ip){
			return true;
		}
	}
	return false;
}
Host* TcpNet::getHost(const std::string & ip){	
	BOOST_FOREACH( Host* q, impl_->qboxes_){
		if ( q->address() == ip){
			return q;
		}
	}
	return NULL;
}
Host* TcpNet::createHost(const std::string & ip){	
	BOOST_FOREACH( Host* q, impl_->qboxes_){
		if ( q->address() == ip){
			return q;
		}
	}
	Host * q;
	if ( impl_->removeHosts_.empty()){
		q = new Host();
		q->impl_->port_ = port_;
	}else{
		q = impl_->removeHosts_.back();
		impl_->removeHosts_.pop_back();
	}
	q->setAddress(ip);
	impl_->qboxes_.push_back(q);
	return q;
}

bool TcpNet::removeHost(const  std::string &ip){
	for( auto it = impl_->qboxes_.begin(); it != impl_->qboxes_.end(); ++it ){
		if ( (*it)->address() == ip){
			(*it)->close();
			impl_->removeHosts_.push_back( *it);
			//delete (*it);
			impl_->qboxes_.erase(it);
			return true;
		}
	}
	return false;
}


TcpNet* TcpNet::inst = 0;
TcpNet *TcpNet::instance(){
	if ( inst) return inst;
	return inst = new TcpNet();
}
TcpNet::TcpNet():
impl_(new Impl)
{
}
TcpNet::~TcpNet()
{
	BOOST_FOREACH( Host* q, impl_->qboxes_){
		delete q;
	}
	BOOST_FOREACH( Host* q, impl_->removeHosts_){
		delete q;
	}
	delete impl_;
}

static void testCallback( uint32_t , DataMap&){
	qDebug()<<"testCallback";
}

void TcpNet::startThread(){
	impl_->running_ = true;
	startTimer(10);
	impl_->thread_ = new asio::thread( boost::bind(&TcpNet::threadRun, this ) );
}

void TcpNet::timerEvent ( QTimerEvent *  ){
	impl_->mainios_.run_one();
}

void TcpNet::stop(){	
	impl_->stop();
}




asio::io_service * TcpNet::getMainService(){
	return &impl_->mainios_;
}
asio::io_service * TcpNet::getScoketService(){
	return &impl_->socketios_;
}


