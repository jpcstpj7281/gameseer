#ifndef SNMPNET_H
#define SNMPNET_H
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

struct SnmpCallback{
enum RequestStatus { 
	RequestStop, 
	RequestAgain 

};
};
typedef std::function< SnmpCallback::RequestStatus ( int , snmp_session*, snmp_pdu*, SnmpObj*)> SnmpCallbackFunc;


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
	SnmpObj(std::string &obj, std::string &snmpoid, std::string & ip, std::string & community,SnmpCallbackFunc callback, QVariant var = QVariant(), snmp_session *sess = 0, void* sessp=0, snmp_pdu* pdu = 0 ):
	  obj(obj)
	,snmpoid(snmpoid)
	  ,ip(ip)
	  ,community(community)
	  ,callback(callback)
	  ,var(var)
	  ,sess(sess)
	  ,sessp(sessp)
	  ,pdu(pdu){
		//this->snmpoid = snmpoid;
		//this->ip = ip;
		//this->community = community;
		//this->callback = callback;
	}



	inline bool equal(std::string& obj, std::string& snmpoid, std::string& ip, std::string& community )const {
		return this->obj==obj ? (this->snmpoid==snmpoid? (this->ip==ip?(this->community==community?true:false):false):false):false;
	}
	inline bool equal( SnmpObj& obj) const {
		return this == &obj ? true :equal( obj.obj, obj.snmpoid, obj.ip, obj.community);
	}
	std::string obj;
	std::string snmpoid;
	std::string ip;
	std::string community;
	SnmpCallbackFunc callback;
	snmp_session *sess;
	void* sessp;
	QVariant var;
	snmp_pdu *pdu;
//private:
//	QString uniqueid;
};

namespace Ui {
class SnmpNet;
}

class SnmpNet 
{

	static  SnmpNet* inst;
	SnmpNet();
	

	typedef std::list<SnmpObj*> AddressList;
	typedef std::map<std::string, SnmpObj*> AddressSetMap;

	AddressList snmpList_;

	AddressList removeList_;

	AddressSetMap setMap_;
	
	std::string switchToAddress_;
	std::string currAddress_;

	int asynch_response_impl(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);

	QMutex getLock_;

	static void run();
	volatile bool running_;
	QFuture<void>  future_;

	std::function< void (  SnmpObj*)> beforeSentCallback_;
	std::function< void (  SnmpObj*)> afterResponsedCallback_;
public:
	~SnmpNet();
	static SnmpNet *instance();
		void startThread();
	void stop();
	void listenAddress( const char * ip , SnmpCallbackFunc callback);
	inline std::string getCurrAddress(){ return currAddress_;}

	bool switchAsyncSnmpAddress(const  char * ip);

	void addAsyncGetWithIP(const char* obj, const char* snmpoid, const char* ip , const char* community  , SnmpCallbackFunc callback );
	void addAsyncSetWithIP(const char* obj, const char* snmpoid, const char* ip , const char* community  , SnmpCallbackFunc callback, QVariant value );

	void addAsyncWalkWithIP(const char* obj, const char* snmpoid, const char* ip , const char* community , SnmpCallbackFunc callback);

	//for current listening address
	void addAsyncGet(const char* obj, const char* snmpoid, const char* community  , SnmpCallbackFunc callback ); 
	void addAsyncSet(const char* obj, const char* snmpoid, const char* community  , SnmpCallbackFunc callback , QVariant value ); 

	inline void listenOidBeforeSent(std::function< void (  SnmpObj*) > callback ){
		beforeSentCallback_ = callback;
	}
	inline void listenOidAfterResponsed(std::function< void (  SnmpObj*)> callback ){
		afterResponsedCallback_ = callback;
	}


	friend int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);

	//test purpose
	void walk(char* snmpoid, char* ip ="192.168.1.100", char* community = "public");
	void get(char* snmpoid, char* ip ="192.168.1.100", char* community = "public" );
};

static int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);




#endif // SNMPNET_H
