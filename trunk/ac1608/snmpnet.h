#ifndef SNMPNET_H
#define SNMPNET_H

#include <map>
#include <vector>
#include <set>
#include <QString>
#include <net-snmp/net-snmp-config.h>

#include <net-snmp/types.h>
#include <functional>

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
	SnmpObj(char* snmpoid, char* ip, char* community,SnmpCallbackFunc callback ):sess(0){
		this->snmpoid = snmpoid;
		this->ip = ip;
		this->community = community;
		this->callback = callback;
	}

	inline bool equal(char* snmpoid, char* ip, char* community )const {
		return strcmp(this->snmpoid, snmpoid)?false:strcmp(this->ip, ip)?false:strcmp(this->community, community)?false:true;
	}
	inline bool equal( const SnmpObj& obj) const {
		return this == &obj ? true :equal( obj.snmpoid, obj.ip, obj.community);
	}
	char* snmpoid;
	char* ip;
	char* community;
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
	~SnmpNet();

	typedef std::vector<SnmpObj*> SnmpMap;
	typedef std::vector<SnmpObj*> RemoveList;

	SnmpMap _oids;
	RemoveList _removeList;
	

	int asynch_response_impl(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);
public:


	static SnmpNet *instance();
    
	void run();

    void walk(char* snmpoid, char* ip ="192.168.1.100", char* community = "public");
	
	void get(char* snmpoid, char* ip ="192.168.1.100", char* community = "public" );

	void addAsyncGet(char* snmpoid, char* ip , char* community  , SnmpCallbackFunc callback );
	//void removeAsyncGet(char* snmpoid, char* ip ="192.168.1.100", char* community = "public" ,SnmpCallback * callback = 0);
	void addAsyncWalk(char* snmpoid, char* ip , char* community , SnmpCallbackFunc callback);
	//void removeAsyncWalk(char* snmpoid, char* ip ="192.168.1.100", char* community = "public" ,SnmpCallback * callback = 0);

	bool isConnected(char* ip ="192.168.1.100"){
		return true;
	}

	friend int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);
};

static int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic);

#endif // SNMPNET_H
