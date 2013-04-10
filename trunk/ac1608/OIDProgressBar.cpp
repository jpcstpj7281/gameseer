#include "oidprogressbar.h"
#include "OIDInputDlg.h"
#include <QDebug>
#include "ConfigMgr.h"
using namespace std::tr1::placeholders;

OIDProgressBar::OIDProgressBar( QWidget* w):
	QProgressBar(w)
	,val_(0)
{
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

void OIDProgressBar::snmpCallback( SnmpObj* so){
	setValue( so->rspVar.value<int>());
}

void OIDProgressBar::mouseReleaseEvent ( QMouseEvent * event ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		QString oldoid = ConfigMgr::instance()->getOid( objectName());
		QString oid = OIDInputDlg::getNewOid( this->objectName() );
		if (!oid.isEmpty() && oid != oldoid){
			if ( !oldoid.isEmpty()){
				SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oldoid.toStdString() , std::string("public"));
			}
			SnmpNet::instance()->addAsyncGet(
				objectName().toStdString(), oid.toStdString(),
				"public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1) );
		}
	}
}

