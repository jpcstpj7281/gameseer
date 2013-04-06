#ifndef QBOXNET_H
#define QBOXNET_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <functional>
#include <stdint.h>



class QboxObj;
typedef std::map<std::string, std::string>	QboxDataMap;
typedef std::function< bool ( uint32_t , QboxDataMap& )> QboxCallbackFunc;

class Qbox{
	struct Impl;
	Impl *impl_;

	void mainThreadRun();
	friend class QboxMgr;
	Qbox();

	
public:
	std::string address();
	void addAsyncRequest( uint32_t msgtype ,QboxCallbackFunc callback, QboxDataMap &value );
	void connInit(std::string & ip);
};

class QboxMgr :public QObject 
{

	static  QboxMgr* inst;
	QboxMgr();

	virtual void	timerEvent ( QTimerEvent * event )override;

	struct Impl;
	Impl* impl_;
	friend struct Qbox;
public:
	~QboxMgr();
	static QboxMgr *instance();
	void startThread();
	void stop();

	bool hasQbox(std::string &ip);
	Qbox* getQbox( std::string &ip);//create one if not there
	bool removeQbox( std::string &ip);
};




#endif // QBOXNET_H
