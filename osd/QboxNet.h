#ifndef QBOXNET_H
#define QBOXNET_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <functional>
#include <stdint.h>


#define QBOX_VALUE_STRING "String"
#define QBOX_VALUE_HEX_BIN "Hex Bin"
#define QBOX_VALUE_DEC_INT "Dec Int"
#define QBOX_VALUE_DEC_UINT "Dec Uint"



typedef std::map<std::string, std::string>	QboxDataMap;
typedef std::function< bool ( uint32_t , QboxDataMap& )> QboxCallback;

class Qbox{
	struct Impl;
	Impl *impl_;

	void mainThreadRun();
	friend class QboxMgr;
	Qbox();
	~Qbox();
	
public:
	void setAddress(const std::string & ip);
	std::string address();
	void addAsyncRequest( uint32_t msgtype ,QboxCallback callback, QboxDataMap &value );
	void addAsyncRequest( uint32_t msgtype ,QboxCallback callback, QboxDataMap &value, size_t delay );
	//void addAsyncRequestVersion( QboxCallback callback, QboxDataMap &value );
	void connInit();
	bool isConn();
	void close();
};

class QboxMgr :public QObject 
{

	static  QboxMgr* inst;
	QboxMgr();

	virtual void	timerEvent ( QTimerEvent * event )override;

	struct Impl;
	Impl* impl_;
	friend class Qbox;
public:
	~QboxMgr();
	static QboxMgr *instance();
	void startThread();
	void stop();

	void threadRun();

	bool hasQbox(const std::string &ip);
	Qbox* getQbox(const  std::string &ip);
	Qbox* createQbox(const  std::string &ip);//return the one found if already there
	bool removeQbox(const  std::string &ip);
};




#endif // QBOXNET_H
