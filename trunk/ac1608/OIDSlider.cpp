#include "OIDSlider.h"
#include "OIDInputDlg.h"
#include "ConfigMgr.h"
#include <QDebug>
using namespace std::tr1::placeholders;


OIDSlider::OIDSlider( QWidget* w):QSlider(w){
	connect( this, SIGNAL(valueChanged(int )), this, SLOT(fireSnmp(int )));
	startTimer(1000);
	//SnmpNet::instance()->addAsyncGet( ConfigMgr::instance()->getOid(objectName()).toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDSlider::snmpCallback, this, _1, _2, _3, _4) );
}

void	OIDSlider::timerEvent ( QTimerEvent * e ){
	size_t elapsed = GetTickCount() - lastTimeChanged_;
	if ( elapsed > 2000){
		this->setValue( val_);
	}
}
void OIDSlider::fireSnmp(int val ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		if ( !ConfigMgr::instance()->isOidEditable() ) return;
		OIDInputDlg::getNewOid( this->objectName(), ConfigMgr::instance()->getOid(objectName()), ConfigMgr::instance()->getDefaultOid(objectName()) );
	}else{
		QString oid = ConfigMgr::instance()->getOid(objectName());
		SnmpNet::instance()->addAsyncSet( oid.toStdString().c_str(), "private", std::bind<SnmpCallbackFunc>( &OIDSlider::snmpCallback, this, _1, _2, _3, _4) , val);
		lastTimeChanged_ = GetTickCount();
	}
}

SnmpCallback::RequestStatus OIDSlider::snmpCallback( int , snmp_session*, snmp_pdu* pdu, SnmpObj*){
	if (pdu->variables->type == ASN_INTEGER){
		val_ = *(u_long *) (pdu->variables->val.integer);
		qDebug()<<val_;
	}
	return SnmpCallback::RequestStop;
}
