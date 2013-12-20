#include "OIDDial.h"
#include "OIDInputDlg.h"
#include "ConfigMgr.h"
#include <QDebug>
#include <QEvent>
using namespace std::tr1::placeholders;


OIDDial::OIDDial( QWidget* w):
QDial(w)
,ql_(0)
,scale_(0.f){
	connect( this, SIGNAL(valueChanged(int )), this, SLOT(fireSnmp(int )));
	installEventFilter(this);
	setToolTip( objectName());
	installEventFilter(this);
}
void OIDDial::setLabel(QLabel *ql){
	ql_ = ql;
}

void OIDDial::initSnmp(){
	QString oid = ConfigMgr::instance()->getOid( objectName());
	if (!oid.isEmpty())
		SnmpNet::instance()->addAsyncGet( objectName().toStdString(), 
			oid.toStdString(), 
			"public", std::bind<SnmpCallbackFunc>( &OIDDial::snmpCallback, this, _1) 
			);
}
void OIDDial::shutdownSnmp(){
	QString oid = ConfigMgr::instance()->getOid( objectName());
	if (!oid.isEmpty())
		SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oid.toStdString() , std::string("public"));
}

bool OIDDial::eventFilter ( QObject * watched, QEvent * event ){
	if (ConfigMgr::instance()->isOidEditable() &&
		(event->type() == event->MouseButtonPress ||
		event->type() == event->MouseButtonRelease ||
		event->type() == event->MouseButtonDblClick ||
		event->type() == event->MouseMove ||
		event->type() == event->MouseTrackingChange||
		event->type() == event->Enter||
		event->type() == event->Leave
		)
		
		){
			if (event->type() == event->MouseButtonRelease){
				QString oid = OIDInputDlg::getNewOid( this->objectName());
				if (!oid.isEmpty()){
					SnmpNet::instance()->addAsyncGet(objectName().toStdString(),  
						oid.toStdString(), "public", 
						std::bind<SnmpCallbackFunc>( &OIDDial::snmpCallback, this, _1) );
				}
			}
			return true;
	}else{
		QDial::eventFilter(watched, event);
	}
    return false;
}

void OIDDial::refreshLabel(){
	if (ql_){
		if ( scale_ == 0.f){
			ql_->setText( QString::number( value()));
		}else{
			ql_->setText( QString::number( value()/scale_));
		}
	}
}

void OIDDial::fireSnmp(int val ){
	if ( !ConfigMgr::instance()->isOidEditable() ) {
		refreshLabel();
		QString oid = ConfigMgr::instance()->getOid(objectName());
		SnmpNet::instance()->addAsyncSet( objectName().toStdString(), 
			oid.toStdString(), "private", 
			std::bind<SnmpCallbackFunc>( &OIDDial::snmpCallback, this, _1) , val);
		lastTimeChanged_ = GetTickCount();
		
	}
}

void OIDDial::snmpCallback(  SnmpObj* so){
	
	if ( so->setVar.isNull() ){
		setValue( so->rspVar.value<int>());
		refreshLabel();
		QString oid = ConfigMgr::instance()->getOid( objectName());
		if (!oid.isEmpty())
			SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oid.toStdString() , std::string("public"));
	}
}
