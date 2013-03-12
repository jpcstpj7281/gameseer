#include "snmpnet.h"


#include<QtDebug>

#include <net-snmp/utilities.h>
#include <net-snmp/net-snmp-includes.h>




#include <QMainWindow>


SnmpNet* SnmpNet::inst = 0;
SnmpNet *SnmpNet::instance(){
	if ( inst) return inst;
	return inst = new SnmpNet();
}
SnmpNet::SnmpNet()
{
	SOCK_STARTUP;
	init_snmp("ac1608");
}
SnmpNet::~SnmpNet()
{
	SOCK_CLEANUP;
}

#define NETSNMP_DS_APP_DONT_FIX_PDUS 0

#define NETSNMP_DS_WALK_INCLUDE_REQUESTED	        1
#define NETSNMP_DS_WALK_PRINT_STATISTICS	        2
#define NETSNMP_DS_WALK_DONT_CHECK_LEXICOGRAPHIC	3
#define NETSNMP_DS_WALK_TIME_RESULTS     	        4
#define NETSNMP_DS_WALK_DONT_GET_REQUESTED	        5
#define NETSNMP_DS_WALK_TIME_RESULTS_SINGLE	        6

int asynch_response(int operation, struct snmp_session *sp, int reqid, struct snmp_pdu *pdu, void *magic){
	return SnmpNet::instance()->asynch_response_impl(operation,  sp,  reqid, pdu, magic);
}

void SnmpNet::addAsyncGet(char* snmpoid, char* ip, char* community ,SnmpCallbackFunc callback){
	SnmpObj* so = new SnmpObj( snmpoid, ip, community, callback);
	_oids.push_back(  so );
}
//void SnmpNet::removeAsyncGet(char* snmpoid, char* ip, char* community ,SnmpCallback * callback){
//	_removeList.push_back(  SnmpObj( snmpoid, ip, community, callback));
//}

int SnmpNet::asynch_response_impl(int operation, struct snmp_session *sp, int reqid, snmp_pdu *pdu, void *magic){

	SnmpObj *so = (SnmpObj *)magic;
	//snmp_pdu *req;

	if (operation == NETSNMP_CALLBACK_OP_RECEIVED_MESSAGE) {
		//if (so->callback){
			if( so->callback( STAT_SUCCESS, so->sess, pdu, so) == SnmpCallback::RequestAgain) { //再发一次
				//每个host对应了3个oid，对每个都要发送包
				//asynchronous发送第一个包，这里对其他的oid发送包

				//下面的程序跟asynchronous中处理相同
				//if (host->current_oid->Name) {
				//snmp_pdu *req = snmp_clone_pdu(pdu);
				//snmp_add_null_var(req, , );
				//if (!snmp_send(so->sess, req)){
				//	snmp_perror("snmp_send");
				//	snmp_free_pdu(pdu);
				//	qDebug()<<"Snmp error: SnmpNet::asynch_response_impl!";
				//}
				return 0;
			}
			else{
				_removeList.push_back(so);
			}
		//}
		qDebug()<<"Received message: SnmpNet::asynch_response_impl!";
	}else if(operation == NETSNMP_CALLBACK_OP_TIMED_OUT) {
		qDebug()<<"Time out: SnmpNet::asynch_response_impl!";
		return isConnected() ? 0 :1;
	}
	//else print_result(STAT_TIMEOUT, host->sess, pdu);
	return 1;
}

bool initSession( SnmpObj* so){
	snmp_pdu *req;
	snmp_session sess;

	snmp_sess_init( &sess); 
	sess.version = SNMP_VERSION_1;
	sess.peername = so->ip;
	sess.community = (u_char*)so->community;
	sess.community_len = strlen(so->community);
	sess.callback = asynch_response;
	sess.callback_magic = (void*)so;
	sess.retries = INT_MAX;

	//初始化和打开后返回的session不同
	so->sessp = (snmp_session*)snmp_sess_open(&sess);
	if ( so->sessp )
		so->sess = snmp_sess_session(so->sessp);
	if (!so->sess){
		qDebug()<<"Qession error!";
		return false;
	}

	const	QStringList qsl = QString(so->snmpoid).split( QChar('.'));
	oid		soid[MAX_OID_LEN];
	size_t  soidlen = 0;
	for ( int i = 0; i < qsl.size(); ++i){
		if ( ! qsl[i].isEmpty() ){
			soid[soidlen++] = qsl[i].toInt();
		}
	}

	req = snmp_pdu_create(SNMP_MSG_GET);
	snmp_add_null_var(req, soid, soidlen);

	if (!snmp_sess_send(so->sessp, req)){
	//if (!snmp_sess_async_send(so->sessp, req, asynch_response,(void*)so )){
		snmp_perror("snmp_send");
		snmp_free_pdu(req);
		return false;
	}
	return true;
}

void SnmpNet::run(){

	for ( SnmpMap::iterator it= _oids.begin(); it != _oids.end(); ++it){
		SnmpObj* so = *it;
		if ( !so->sess){
			initSession(so);
		}else{
		}

	}

	while ( !_oids.empty() ) {
		for ( SnmpMap::iterator it = _oids.begin(); it != _oids.end(); ++it){
			void* sessp = (*it)->sessp;
			int fds = 0, block = 1;
			fd_set fdset;
			struct timeval timeout;

			FD_ZERO(&fdset);//把fd_set清零
			snmp_sess_select_info( sessp, &fds, &fdset, &timeout, &block);
			//多路复用，直接这么用就行了
			fds = select(fds, &fdset, NULL, NULL, block ? NULL : &timeout);
			if (fds < 0) {
				perror("select failed");
				exit(1);
			}
			//fds返回的是等待处理的io数目
			if (fds)
				snmp_sess_read(sessp, &fdset);//到这里就会调用callback
			else
				snmp_sess_timeout(sessp);

		}

		for( RemoveList::iterator it = _removeList.begin(); it!=_removeList.end(); ++it){
			SnmpObj* curr = *it;
			SnmpMap::iterator found = std::find(_oids.begin(), _oids.end(), curr );// _oids.find( curr.uniqueId() );
			SnmpObj * so = *found;
			snmp_sess_close(so->sessp);
			if ( found != _oids.end() ) _oids.erase(found );
		}
		_removeList.clear();
	}

}

int netsnmpCallback(int a, netsnmp_session * sess, int b , netsnmp_pdu * pdu, void * val){
	netsnmp_variable_list *vars;

	for (vars = pdu->variables; vars; vars = vars->next_variable){
		print_variable(vars->name, vars->name_length, vars);
		const int len = 1024;
		char buf[len];
		memset( buf, 0, 1024);
		snprint_variable( buf, len, vars->name, vars->name_length, vars);
		qDebug()<< a << " "<<b <<" "<<(char*)val <<" "<<buf;
	}
	
	return 0;
}



void SnmpNet::get( char* snmpoid, char* ip , char* community  ){
	netsnmp_session session, *ss;
	netsnmp_pdu    *pdu;
	netsnmp_pdu    *response;
	netsnmp_variable_list *vars;
	int             status;
	int             failures = 0;
	int             exitval = 0;
	int				count = 0;

	oid             root[MAX_OID_LEN];
	//oid             root[MAX_OID_LEN]= {1,3,6,1,4,1,2680,1,1,3,4,0};
	size_t          rootlen = 0;


	const QStringList qsl = QString(snmpoid).split( QChar('.'));
	
	for ( int i = 0; i < qsl.size(); ++i){
		if ( ! qsl[i].isEmpty() ){
			root[rootlen++] = qsl[i].toInt();
		}
	}
	

	//init_snmp("ac1608");
	snmp_sess_init( &session );
	session.version = SNMP_VERSION_1;
	session.community = (u_char*)community;
	session.community_len = strlen((char*)session.community);
	session.peername = ip;

	//session.callback = asynch_get;


	/*
	* Open an SNMP session.
	*/
	ss = snmp_open(&session);

	/*
	* Create PDU for GET request and add object names to request.
	*/
	pdu = snmp_pdu_create(SNMP_MSG_GET);
	snmp_add_null_var(pdu, root, rootlen);


	/*
	* Perform the request.
	*
	* If the Get Request fails, note the OID that caused the error,
	* "fix" the PDU (removing the error-prone OID) and retry.
	*/
retry:
	status = snmp_synch_response(ss, pdu, &response);

	if (status == STAT_SUCCESS) {
		if (response->errstat == SNMP_ERR_NOERROR) {
			for (vars = response->variables; vars; vars = vars->next_variable){
				//print_variable(vars->name, vars->name_length, vars);
				const int len = 1024;
				char buf[len];
				memset( buf, 0, 1024);
				snprint_variable( buf, len, vars->name, vars->name_length, vars);
				qDebug() << buf;
			}
			if (count < 0){
				count++;
				Sleep(100);
				pdu = snmp_pdu_create(SNMP_MSG_GET);
				snmp_add_null_var(pdu, root, rootlen);
				response = NULL;
				if (pdu != NULL) { 
					goto retry;
				}
			}
		} else {
			fprintf(stderr, "Error in packet\nReason: %s\n", snmp_errstring(response->errstat));
			exitval = 2;

			/*
			* retry if the errored variable was successfully removed 
			*/
			if (!netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_APP_DONT_FIX_PDUS)) {
				pdu = snmp_fix_pdu(response, SNMP_MSG_GET);
				snmp_free_pdu(response);
				response = NULL;
				if (pdu != NULL) { goto retry;}
			}
		}                       /* endif -- SNMP_ERR_NOERROR */

	} else if (status == STAT_TIMEOUT) {
		fprintf(stderr, "Timeout: No Response from %s.\n",
			session.peername);
		exitval = 1;

	} else {                    /* status == STAT_ERROR */
		snmp_sess_perror("snmpget", ss);
		exitval = 1;

	}                           /* endif -- STAT_SUCCESS */


	if (response){
		snmp_free_pdu(response);
	}
	snmp_close(ss);
}


void SnmpNet::walk( char* snmpoid, char* ip, char* community  )
{
	int             numprinted = 0;
	netsnmp_session session, *ss;
	netsnmp_pdu    *pdu, *response;
	netsnmp_variable_list *vars;
	int             arg;
	oid             name[MAX_OID_LEN];
	size_t          name_length;

	int             count;
	int             running;
	int             status = STAT_ERROR;
	int             check;
	int             exitval = 0;
	struct timeval  tv1, tv2, tv_a, tv_b;

	oid             root[MAX_OID_LEN];//= {1,3,6,1,4,1,2680,1,1,3,4,0};
	size_t          rootlen = 0;
	oid             end_oid[MAX_OID_LEN];// = {1,3,6,1,4,1,2680,1,1,3,4,1};
	size_t          end_len = 0;
	

	const QStringList qsl = QString(snmpoid).split( QChar('.'));
	
	for ( int i = 0; i < qsl.size(); ++i){
		if ( ! qsl[i].isEmpty() ){
			end_oid[end_len++] = root[rootlen++] = qsl[i].toInt();
		}
	}
	end_oid[end_len-1]++;

	//init_snmp("ac1608");
	snmp_sess_init( &session );
	session.version = SNMP_VERSION_1;
	session.community = (u_char*)community;
	session.community_len = strlen((char*)session.community);
	session.peername = ip;

	/*
	* open an SNMP session 
	*/
	ss = snmp_open(&session);
	if (ss == NULL) {
		/*
		* diagnose snmp_open errors with the input netsnmp_session pointer 
		*/
		snmp_sess_perror("snmpwalk", &session);
	}

	/*
	* get first object to start walk 
	*/
	memmove(name, root, rootlen * sizeof(oid));
	name_length = rootlen;

	running = 1;

	//check = !netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID,  NETSNMP_DS_WALK_DONT_CHECK_LEXICOGRAPHIC);
	//if (netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_WALK_INCLUDE_REQUESTED)) {
	//	const int len = 1024;
	//	char buf[len];
	//	memset( buf, 0, 1024);
	//	snmp_get_and_print(ss, root, rootlen, buf, len);
	//	qDebug()<<"unexpected err: " << buf;

	//}
	//用于某种状态下计算时间
	if (netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_WALK_TIME_RESULTS))
		netsnmp_get_monotonic_clock(&tv1);
	while (running) {
		/*
		* create PDU for GETNEXT request and add object name to request 
		*/
		pdu = snmp_pdu_create(SNMP_MSG_GETNEXT);
		snmp_add_null_var(pdu, name, name_length);

		/*
		* do the request 
		*/
		if (netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_WALK_TIME_RESULTS_SINGLE))
			netsnmp_get_monotonic_clock(&tv_a);
		status = snmp_synch_response(ss, pdu, &response);
		if (status == STAT_SUCCESS) {
			if (netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_WALK_TIME_RESULTS_SINGLE))
				netsnmp_get_monotonic_clock(&tv_b);
			if (response->errstat == SNMP_ERR_NOERROR) {
				/*
				* check resulting variables 
				*/
				for (vars = response->variables; vars; vars = vars->next_variable) {
					if (snmp_oid_compare(end_oid, end_len, vars->name, vars->name_length) <= 0) {
						/*
						* not part of this subtree 
						*/
						running = 0;
						continue;
					}
					numprinted++;
					if (netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_WALK_TIME_RESULTS_SINGLE))
						fprintf(stdout, "%f s: ", (double) (tv_b.tv_usec - tv_a.tv_usec)/1000000 + (double) (tv_b.tv_sec - tv_a.tv_sec));

					print_variable(vars->name, vars->name_length, vars);
					
					const int len = 1024;
					char buf[len];
					memset( buf, 0, 1024);
					snprint_variable( buf, len, vars->name, vars->name_length, vars);
					qDebug() << buf;

					if ((vars->type != SNMP_ENDOFMIBVIEW) && (vars->type != SNMP_NOSUCHOBJECT) && (vars->type != SNMP_NOSUCHINSTANCE)) {
						/*
						* not an exception value 
						*/
						if (check && snmp_oid_compare(name, name_length,
							vars->name,
							vars->name_length) >= 0) {
								fprintf(stderr, "Error: OID not increasing: ");
								fprint_objid(stderr, name, name_length);
								fprintf(stderr, " >= ");
								fprint_objid(stderr, vars->name,
									vars->name_length);
								fprintf(stderr, "\n");
								running = 0;
								exitval = 1;
						}
						memmove((char *) name, (char *) vars->name, vars->name_length * sizeof(oid));
						name_length = vars->name_length;
					} else
						/*
						* an exception value, so stop 
						*/
						running = 0;
				}
			} else {
				/*
				* error in response, print it 
				*/
				running = 0;
				if (response->errstat == SNMP_ERR_NOSUCHNAME) {
					printf("End of MIB\n");
				} else {
					fprintf(stderr, "Error in packet.\nReason: %s\n",
						snmp_errstring(response->errstat));
					if (response->errindex != 0) {
						fprintf(stderr, "Failed object: ");
						for (count = 1, vars = response->variables;
							vars && count != response->errindex;
							vars = vars->next_variable, count++)
							/*EMPTY*/;
						if (vars)
							fprint_objid(stderr, vars->name,
							vars->name_length);
						fprintf(stderr, "\n");
					}
					exitval = 2;
				}
			}
		} else if (status == STAT_TIMEOUT) {
			fprintf(stderr, "Timeout: No Response from %s\n",
				session.peername);
			running = 0;
			exitval = 1;
		} else {                /* status == STAT_ERROR */
			snmp_sess_perror("snmpwalk", ss);
			running = 0;
			exitval = 1;
		}
		if (response)
			snmp_free_pdu(response);
	}
	if (netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID,
		NETSNMP_DS_WALK_TIME_RESULTS))
		netsnmp_get_monotonic_clock(&tv2);

	if (numprinted == 0 && status == STAT_SUCCESS) {
		/*
		* no printed successful results, which may mean we were
		* pointed at an only existing instance.  Attempt a GET, just
		* for get measure. 
		*/
		if (!netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_WALK_DONT_GET_REQUESTED)) {
			const int len = 1024;
			char buf[len];
			memset( buf, 0, 1024);
			//snmp_get_and_print(ss, root, rootlen, buf, len);

			netsnmp_pdu    *pdu, *response;
			netsnmp_variable_list *vars;

			pdu = snmp_pdu_create(SNMP_MSG_GET);
			snmp_add_null_var(pdu, root, rootlen);

			if (snmp_synch_response(ss, pdu, &response) == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR) {
				for (vars = response->variables; vars; vars = vars->next_variable) {
					numprinted++;
					snprint_variable( buf, len, vars->name, vars->name_length, vars);
					//print_variable(
				}
			}
			if (response) {
				snmp_free_pdu(response);
			}

			qDebug()<<buf;
		}
	}
	snmp_close(ss);

	if (netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_WALK_PRINT_STATISTICS)) {
		printf("Variables found: %d\n", numprinted);
	}
	if (netsnmp_ds_get_boolean(NETSNMP_DS_APPLICATION_ID, NETSNMP_DS_WALK_TIME_RESULTS)) {
		fprintf (stderr, "Total traversal time = %f seconds\n",
			(double) (tv2.tv_usec - tv1.tv_usec)/1000000 +
			(double) (tv2.tv_sec - tv1.tv_sec));
	}


	//return exitval;
}
