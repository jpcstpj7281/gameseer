#ifndef SNMPNET_H
#define SNMPNET_H
#define NOMINMAX 
#include <QWidget>
#include <map>
#include <vector>
#include <list>
#include <QString>
#include <net-snmp/net-snmp-config.h>

#include <net-snmp/types.h>
#include <functional>
#include <QMutex>
#include <QFuture>

class SnmpObj;

typedef std::function< void (SnmpObj*)> SnmpCallbackFunc;


inline static QString timeticksToString( size_t timeticks){
	int    centisecs, seconds, minutes, hours, days;
	centisecs = timeticks % 100;
	timeticks /= 100;
	days = timeticks / (60 * 60 * 24);
	timeticks %= (60 * 60 * 24);

	hours = timeticks / (60 * 60);
	timeticks %= (60 * 60);

	minutes = timeticks / 60;
	seconds = timeticks % 60;
	char deviceRunTime[16];
	snprintf(deviceRunTime, 32, "%d:%d:%02d:%02d",days, hours, minutes, seconds);
	return deviceRunTime;
}


class SnmpObj{
public:
	SnmpObj( const std::string &obj,const  std::string &snmpoid,const  std::string & ip,const  
		std::string & community,SnmpCallbackFunc callback, QVariant setVar = QVariant(), 
		snmp_session *sess = 0, void* sessp=0, snmp_pdu* pdu = 0, size_t interval = 50 ):
	obj(obj)
	,snmpoid(snmpoid)
	,ip(ip)
	,community(community)
	,callback(callback)
	,setVar(setVar)
	,sess(sess)
	,sessp(sessp)
	,pdu(pdu)
	,interval(interval){
	}

	std::string obj;
	std::string snmpoid;
	std::string ip;
	std::string community;
	SnmpCallbackFunc callback;
	QVariant setVar;
	QVariant rspVar;
	size_t interval;
	size_t lastTimeReq;

	snmp_session *sess;//dont use it during dispatch in mainthread
	void* sessp;//dont use it during dispatch in mainthread
	snmp_pdu *pdu;//dont use it during dispatch in mainthread
};

class SnmpNet :public QObject
{
	static  SnmpNet* inst;
	SnmpNet();
	

	typedef std::list<SnmpObj*> AddressList;
	typedef std::map<std::string, SnmpObj*> AddressSetMap;

	AddressList rspList_;
	AddressList getList_;
	AddressList removeList_;

	AddressSetMap setMap_;
	
	std::string switchToAddress_;
	std::string currAddress_;

	int asynch_response_impl(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);

	QMutex getLock_;
	QMutex rspLock_;

	static void run();
	volatile bool running_;
	QFuture<void>  future_;

	std::function< void (  SnmpObj*)> beforeSentCallback_;
	std::function< void (  SnmpObj*)> afterResponsedCallback_;
	std::function< void (  SnmpObj*)> befereRemovedCallback_;

	virtual void timerEvent ( QTimerEvent *  )override;
	bool isExisted(const std::string& obj, const std::string& snmpoid, const std::string& ip, const std::string& community, QVariant value );
	void delayIfRemoving(const std::string& obj, const std::string& snmpoid, const std::string& ip, const std::string& community , QVariant value);
public:
	~SnmpNet();
	static SnmpNet *instance();
		void startThread();
	void stop();
	void listenAddress( const std::string& ip , SnmpCallbackFunc callback);
	void removeListenAddress( const std::string& ip );
	inline std::string getCurrAddress(){ return currAddress_;}

	bool switchAsyncSnmpAddress(const std::string& ip);

	void addAsyncGetWithIP(const std::string& obj, const std::string& snmpoid, const std::string& ip , 
		const std::string& community  , SnmpCallbackFunc callback, size_t interval/*interval time of every request*/ );
	void addAsyncGetWithIP(const std::string& obj, const std::string& snmpoid, const std::string& ip , 
		const std::string& community  , SnmpCallbackFunc callback);/*interval time of every request default to 1000 minisec */
	void addAsyncSetWithIP(const std::string& obj, const std::string& snmpoid, const std::string& ip , 
		const std::string& community  , SnmpCallbackFunc callback, QVariant value );
	//void addAsyncWalkWithIP(const std::string& obj, const std::string& snmpoid, const std::string& ip , const std::string& community , SnmpCallbackFunc callback);

	//for current listening address
	void addAsyncGet(const std::string& obj, const std::string& snmpoid, const std::string& community  , SnmpCallbackFunc callback ); 
	void addAsyncGet(const std::string& obj, const std::string& snmpoid, const std::string& community  , SnmpCallbackFunc callback, size_t interval/*interval time of every request*/ );
	void addAsyncSet(const std::string& obj, const std::string& snmpoid, const std::string& community  , SnmpCallbackFunc callback , QVariant value ); 

	void removeAsyncGet(const std::string& obj, const std::string& snmpoid, const std::string& community );
	void removeAsyncGetWithIP(const std::string& obj, const std::string& snmpoid, const std::string& ip, const std::string& community );
	

	inline void listenOidBeforeSent(std::function< void (  SnmpObj*) > callback ){//callback will invoke by snmp thread
		beforeSentCallback_ = callback;
	}
	inline void listenOidAfterResponsed(std::function< void (  SnmpObj*)> callback ){//callback will invoke by snmp thread
		afterResponsedCallback_ = callback;
	}
	inline void listenOidBeforeRemoved(std::function< void (  SnmpObj*)> callback ){//callback will invoke by snmp thread
		befereRemovedCallback_ = callback;
	}


	friend int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);

	//test purpose
	//void walk(std::string& snmpoid, std::string& ip ="192.168.1.100", std::string& community = "public");
	//void get(std::string& snmpoid, std::string& ip ="192.168.1.100", std::string& community = "public" );
};

static int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);




#endif // SNMPNET_H
