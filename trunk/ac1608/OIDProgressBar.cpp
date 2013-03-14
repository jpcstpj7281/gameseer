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

SnmpCallback::RequestStatus OIDProgressBar::snmpCallback( int , snmp_session*, snmp_pdu* pdu, SnmpObj*){
	if (pdu->variables->type == ASN_INTEGER){
		val_ = *(u_long *) (pdu->variables->val.integer);
	}
	return SnmpCallback::RequestStop;
}

void OIDProgressBar::mouseReleaseEvent ( QMouseEvent * event ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		if ( !ConfigMgr::instance()->isOidEditable() ) return;
		OIDInputDlg::getNewOid( this->objectName(), ConfigMgr::instance()->getOid(objectName()), ConfigMgr::instance()->getDefaultOid(objectName()) );
	}
}

