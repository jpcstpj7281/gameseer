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
	setStyleSheet("* { background-color: lightGray }");
}

void OIDStatePushBtn::initSnmp(){
	QString oid = ConfigMgr::instance()->getOid(objectName());
	if ( ! oid.isEmpty()){
		SnmpNet::instance()->addAsyncGet(
			objectName().toStdString(), 
			oid.toStdString(), 
			"public", 
			std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1) 
			);
	}
}
void OIDStatePushBtn::shutdownSnmp(){
	QString oid = ConfigMgr::instance()->getOid( objectName());
	if (!oid.isEmpty())
		SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oid.toStdString() , std::string("public"));
}
void OIDStatePushBtn::snmpCallback( SnmpObj* so){

	if ( so->setVar.isNull() ){
		val_ = so->rspVar.value<int>();
		refreshStatus();

		QString oid = ConfigMgr::instance()->getOid( objectName());
		if (!oid.isEmpty())
			SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oid.toStdString() , std::string("public"));
	}
}

void OIDStatePushBtn::refreshStatus(){
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

void OIDStatePushBtn::mouseReleaseEvent ( QMouseEvent * event ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		QString oldoid = ConfigMgr::instance()->getOid( objectName());
		QString oid = OIDInputDlg::getNewOid( this->objectName() );
		if (!oid.isEmpty() && oid != oldoid){
			if ( !oldoid.isEmpty()){
				SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oldoid.toStdString() , std::string("public"));
			}
			SnmpNet::instance()->addAsyncGet(objectName().toStdString(), oid.toStdString(), 
				"public", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1) );
		}
	}else{
		val_=!val_;
		refreshStatus();
		QString  oid = ConfigMgr::instance()->getOid( objectName());
		if (! oid.isEmpty() ){
			SnmpNet::instance()->addAsyncSet( objectName().toStdString(), oid.toStdString(),	
				"private", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1) , (int)val_);
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