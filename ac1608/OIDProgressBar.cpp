#include "oidprogressbar.h"
#include "OIDInputDlg.h"
#include <QDebug>
#include "ConfigMgr.h"

using namespace std::tr1::placeholders;

OIDProgressBar::OIDProgressBar( QWidget* w):
	QWidget(w)
	,val_(0)
	,ql_(0)
{
}
void OIDProgressBar::initSnmp(){
	//isRunning_ = true;
	QString objname = parent()->objectName();
	//qDebug()<< objname;
	QString oid = ConfigMgr::instance()->getOid(objname);
	if ( ! oid.isEmpty()){
		SnmpNet::instance()->addAsyncGet(
			parent()->objectName().toStdString(), 
			oid.toStdString(), 
			"public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1) , 1
			);
	}
}
void OIDProgressBar::shutdownSnmp(){
	//isRunning_ = false;
	QString objname = parent()->objectName();
	QString oid = ConfigMgr::instance()->getOid(objname);
	SnmpNet::instance()->removeAsyncGet( parent()->objectName().toStdString(), oid.toStdString() , std::string("public"));
}

void OIDProgressBar::snmpCallback( SnmpObj* so){
	setValue( so->rspVar.value<int>());
	if (ql_){
		ql_->setText( QString::number( value()));
	}
}
void OIDProgressBar::mouseReleaseEvent ( QMouseEvent *  ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		QString oldoid = ConfigMgr::instance()->getOid( parent()->objectName());
		QString oid = OIDInputDlg::getNewOid( parent()->objectName() );
		if (!oid.isEmpty() && oid != oldoid){
			if ( !oldoid.isEmpty()){
				SnmpNet::instance()->removeAsyncGet( parent()->objectName().toStdString(), oldoid.toStdString() , std::string("public"));
			}
			SnmpNet::instance()->addAsyncGet(
				parent()->objectName().toStdString(), oid.toStdString(),
				"public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1), 1 );
		}
	}
}

