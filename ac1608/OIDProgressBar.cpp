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
}

void OIDProgressBar::timerEvent ( QTimerEvent * e ){
	setValue( val_);
}

void OIDProgressBar::initSnmp(){
	isRunning_ = true;
	QString oid = ConfigMgr::instance()->getOid(objectName());
	if ( ! oid.isEmpty()){
		SnmpNet::instance()->addAsyncGet(
			objectName().toStdString(), 
			oid.toStdString(), 
			"public", 
			std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1) 
			);
	}
}
void OIDProgressBar::shutdownSnmp(){
	isRunning_ = false;
}

SnmpCallback::RequestStatus OIDProgressBar::snmpCallback( SnmpObj* so){
	val_ = so->rspVar.value<int>();
	if ( so->setVar.type() )
		return SnmpCallback::RequestStop;
	else{
		return SnmpCallback::RequestAgain;
	}
}

void OIDProgressBar::mouseReleaseEvent ( QMouseEvent * event ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		QString oid = OIDInputDlg::getNewOid( this->objectName() );
		if (!oid.isEmpty() ){
			SnmpNet::instance()->addAsyncGet(
				objectName().toStdString(), oid.toStdString(),
				"public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1) );
		}
	}
}

