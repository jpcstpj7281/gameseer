#ifndef SNMPNET_H
#define SNMPNET_H

#include <map>
#include <QString>
#include <net-snmp/net-snmp-config.h>

#include <net-snmp/types.h>



struct SnmpObj{
	SnmpObj(char* snmpoid, char* ip ="192.168.1.100", char* community = "public" ){
		id.append(snmpoid ).append(ip).append(community);
		snmpoid = snmpoid;
		community = community;
	}
	QString id;
	char* snmpoid;
	char* ip;
	char* community;
	netsnmp_variable_list* vars;
	snmp_session *sess;
};

class SnmpNet
{

	static SnmpNet* inst;
	SnmpNet();
	~SnmpNet();

	std::map<QString*, SnmpObj*> _oids;
public:

	static SnmpNet *instance();
    

    void walk(char* snmpoid, char* ip ="192.168.1.100", char* community = "public" );
	
	void get(char* snmpoid, char* ip ="192.168.1.100", char* community = "public" );

	void addAsyncGet(char* snmpoid, char* ip ="192.168.1.100", char* community = "public");
	void addAsyncWalk(char* snmpoid, char* ip ="192.168.1.100", char* community = "public");
};

#endif // SNMPNET_H
