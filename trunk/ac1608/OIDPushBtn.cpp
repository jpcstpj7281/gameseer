#include "OIDPushBtn.h"
#include "OIDInputDlg.h"
#include <QDebug>
#include "ConfigMgr.h"


using namespace std::tr1::placeholders;

void OIDPushBtn::mouseReleaseEvent ( QMouseEvent *  ){
	if ( !ConfigMgr::instance()->isOidEditable() ) return;
	OIDInputDlg::getNewOid( this->objectName() );

	setBackgroundRole( QPalette::Base);
}

void OIDPushBtn::setImage(QPixmap &offImage){
	QIcon ButtonIcon(offImage);
	setIcon(ButtonIcon);
	setIconSize(QSize(offImage.rect().size()));
}

OIDStatePushBtn::OIDStatePushBtn( QWidget* w):
QPushButton(w)
,val_(0)
,isImageSetup_(false)
{
	setToolTip(objectName() );
	startTimer(500);
	//SnmpNet::instance()->addAsyncGet( oid_.toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1, _2, _3, _4) );
	//setStyleSheet("* { background-color: green }");
	setStyleSheet("* { background-color: lightGray }");
}

void OIDStatePushBtn::timerEvent ( QTimerEvent *  ){
	if ( val_ != this->isChecked() ){
		this->toggle();
		if ( val_){
			if( isImageSetup_){
				QIcon buttonIcon(onImage_);
				setIcon(buttonIcon);
				setIconSize(QSize(onImage_.rect().size()));
			}else{
				setStyleSheet("* { background-color: green }");
			}
		}else{
			if( isImageSetup_){
				QIcon buttonIcon(offImage_);
				setIcon(buttonIcon);
				setIconSize(QSize(offImage_.rect().size()));
			}else{
				setStyleSheet("* { background-color: lightGray }");
			}
		}
	}
}

void OIDStatePushBtn::initSnmp(){
	SnmpNet::instance()->addAsyncGet(objectName().toStdString().c_str(), ConfigMgr::instance()->getOid(objectName()).toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1, _2, _3, _4) );
}

SnmpCallback::RequestStatus OIDStatePushBtn::snmpCallback( int status, snmp_session* sess, snmp_pdu* pdu, SnmpObj* so){
	if (pdu->variables->type == ASN_INTEGER){
		val_ = *(u_long *) (pdu->variables->val.integer);
	}
	if ( so->var.type()){
		return SnmpCallback::RequestStop;
	}else{
		return SnmpCallback::RequestAgain;
	}
}

void OIDStatePushBtn::mouseReleaseEvent ( QMouseEvent * event ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		QString oid = OIDInputDlg::getNewOid( this->objectName() );
		if (!oid.isEmpty() ){
			SnmpNet::instance()->addAsyncGet(objectName().toStdString().c_str(), oid.toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1, _2, _3, _4) );
		}
	}else{
		if ( this->isChecked()){
			QString  oid = ConfigMgr::instance()->getOid( objectName());
			if (! oid.isEmpty() ){
				SnmpNet::instance()->addAsyncSet( objectName().toStdString().c_str(), oid.toStdString().c_str() ,	"private", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1, _2, _3, _4) , 0);
			}
		}else{
			QString  oid = ConfigMgr::instance()->getOid( objectName());
			if (! oid.isEmpty() ){
				SnmpNet::instance()->addAsyncSet( objectName().toStdString().c_str(), oid.toStdString().c_str(), "private", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this,_1, _2, _3, _4) , 1);
			}
		}
	}
	QPushButton::mouseReleaseEvent(event);
}
void OIDStatePushBtn::setOnOffStateImage(int onState, int offState, QPixmap &onImage, QPixmap &offImage ){
	onImage_ =onImage;
	offImage_ =offImage;
	isImageSetup_ = true;
	QIcon buttonIcon(offImage);
	setIcon(buttonIcon);
	setIconSize(QSize(offImage.rect().size()));
}