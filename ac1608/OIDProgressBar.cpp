#include "oidprogressbar.h"
#include "OIDInputDlg.h"
#include <QDebug>
#include "ConfigMgr.h"
using namespace std::tr1::placeholders;

OIDProgressBar::OIDProgressBar( QWidget* w):
	QProgressBar(w)
	,val_(0)
{
	startTimer(500);
	//SnmpNet::instance()->addAsyncGet( ConfigMgr::instance()->getOid(objectName()).toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1, _2, _3, _4) );
}

void OIDProgressBar::timerEvent ( QTimerEvent * e ){
	setValue( val_);
}

void OIDProgressBar::initSnmp(){
	SnmpNet::instance()->addAsyncGet( objectName().toStdString().c_str(),  ConfigMgr::instance()->getOid(objectName()).toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1, _2, _3, _4) );
}

SnmpCallback::RequestStatus OIDProgressBar::snmpCallback( int , snmp_session*, snmp_pdu* pdu, SnmpObj* so){
	if (pdu->variables->type == ASN_INTEGER){
		val_ = *(u_long *) (pdu->variables->val.integer);
	}
	if ( so->var.type() )
		return SnmpCallback::RequestStop;
	else{
		return SnmpCallback::RequestAgain;
	}
}

void OIDProgressBar::mouseReleaseEvent ( QMouseEvent * event ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		QString oid = OIDInputDlg::getNewOid( this->objectName() );
		if (!oid.isEmpty() ){
			SnmpNet::instance()->addAsyncGet(objectName().toStdString().c_str(), oid.toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1, _2, _3, _4) );
		}
	}
}

