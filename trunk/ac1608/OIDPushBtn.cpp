#include "OIDPushBtn.h"
#include "OIDInputDlg.h"
#include <QDebug>
#include "ConfigMgr.h"


using namespace std::tr1::placeholders;



OIDStatePushBtn::OIDStatePushBtn( QWidget* w):
QPushButton(w)
,val_(0)
,isImageSetup_(false)
,trueState_(1)
{
	setToolTip(objectName() );
	setStyleSheet("");
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
		this->setEnabled(true);
	}
}
void OIDStatePushBtn::afterCallback(){
	QString oid = ConfigMgr::instance()->getOid( objectName());
	if (!oid.isEmpty())
		SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oid.toStdString() , std::string("public"));
}

void OIDStatePushBtn::refreshStatus(){
	if ( val_ == trueState_){
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
			setStyleSheet("");
		}
	}
}

void OIDStatePushBtn::clickChanged(){
	val_==trueState_? val_ = 0: val_=trueState_;
	//refreshStatus();
	QString  oid = ConfigMgr::instance()->getOid( objectName());
	if (! oid.isEmpty() ){
		SnmpNet::instance()->addAsyncSet( objectName().toStdString(), oid.toStdString(),	
				"private", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1) , (int)val_);
	}
	this->setEnabled(false);
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
		clickChanged();
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



OIDStatus::OIDStatus(QWidget* w):
OIDStatePushBtn(w)
{
	refreshStatus();
}

void OIDStatus::refreshStatus(){
	if ( val_){
			setStyleSheet(	"background-color: green;"
								 "border-style: solid;"
								 "border-width:1px;"
								 "border-radius:5px;"
								 "border-color: gray;"
								 "max-width:10px;"
								 "max-height:10px;"
								 "min-width:10px;"
								 "min-height:10px;"
								 );
	}else{
			setStyleSheet(	"background-color: lightgray;"
								 "border-style: solid;"
								 "border-width:1px;"
								 "border-radius:5px;"
								 "border-color: gray;"
								 "max-width:10px;"
								 "max-height:10px;"
								 "min-width:10px;"
								 "min-height:10px;"
								 );
	}
}