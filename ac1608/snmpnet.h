#ifndef SNMPNET_H
#define SNMPNET_H

#include <map>
#include <vector>
#include <set>
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

class SnmpObj{
public:
	SnmpObj(std::string &snmpoid, std::string & ip, std::string & community,SnmpCallbackFunc callback ):
	  sess(0)
	  ,snmpoid(snmpoid)
	  ,ip(ip)
	  ,community(community)
	  ,callback(callback){
		//this->snmpoid = snmpoid;
		//this->ip = ip;
		//this->community = community;
		//this->callback = callback;
	}

	inline bool equal(std::string& snmpoid, std::string& ip, std::string& community )const {
		return this->snmpoid==snmpoid?false:this->ip==ip?false:this->community==community?false:true;
	}
	inline bool equal( SnmpObj& obj) const {
		return this == &obj ? true :equal( obj.snmpoid, obj.ip, obj.community);
	}

	std::string snmpoid;
	std::string ip;
	std::string community;
	SnmpCallbackFunc callback;
	netsnmp_variable_list* vars;
	snmp_session *sess;
	void* sessp;
//private:
//	QString uniqueid;
};



class SnmpNet
{

	static SnmpNet* inst;
	SnmpNet();
	

	typedef std::vector<SnmpObj*> AddressList;


	AddressList snmpList_;

	AddressList removeList_;
	
	std::string switchToAddress_;

	int asynch_response_impl(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);

	QMutex snmpLock_;
	static void run();
	volatile bool running_;
	QFuture<void>  future_;
public:
	~SnmpNet();
	static SnmpNet *instance();

	void stop();
	void listenAddress( const char * ip , SnmpCallbackFunc callback);

	bool switchAsyncSnmpAddress(const  char * ip);

	void addAsyncGet(const char* snmpoid, const char* ip , const char* community  , SnmpCallbackFunc callback );
	void addAsyncWalk(const char* snmpoid, const char* ip , const char* community , SnmpCallbackFunc callback);


	//for current listening address
	void addAsyncGet(const char* snmpoid, const char* community  , SnmpCallbackFunc callback ); 

	bool isConnected(const char* ip ="192.168.1.100"){
		return true;
	}

	friend int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);

	//test purpose
	void walk(char* snmpoid, char* ip ="192.168.1.100", char* community = "public");
	void get(char* snmpoid, char* ip ="192.168.1.100", char* community = "public" );
};

static int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);

#endif // SNMPNET_H
