#ifndef QBOXNET_H
#define QBOXNET_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <functional>
#include <stdint.h>



#define HOST_CONNECT_FAILED "Connect Failed!"




typedef std::map<std::string, std::string>	DataMap;
typedef std::function< bool ( const std::string &)> NetCallback;
struct NetObj{
	NetObj(NetCallback callback, std::string && sendMsg):
	callback_(callback)
	,sendmsg_(std::move(sendMsg)){

	}
	NetCallback callback_;
	std::string sendmsg_;
};

class Host{
	struct Impl;
	Impl *impl_;

	void mainThreadRun();
	friend class TcpNet;
	Host();
	~Host();
	
public:
	void setAddress(const std::string & ip);
	std::string address();
	void addAsyncRequest( NetCallback callback, std::string&& data);
	void connInit();
	bool isConn();
	void close();
};

namespace asio{
class io_service;
};

class TcpNet :public QObject 
{

	static  TcpNet* inst;
	TcpNet();

	virtual void	timerEvent ( QTimerEvent * event )override;

	struct Impl;
	Impl* impl_;
	friend class Host;
	int port_;
public:
	~TcpNet();
	static TcpNet *instance();
	void startThread();
	void stop();

	void threadRun();

	void setPort(int port){ port_ = port;}
	bool hasHost(const std::string &ip);
	Host* getHost(const  std::string &ip);
	Host* createHost(const  std::string &ip);//return the one found if already there
	bool removeHost(const  std::string &ip);

	asio::io_service * getMainService();
	asio::io_service * getScoketService();
};




#endif // QBOXNET_H
