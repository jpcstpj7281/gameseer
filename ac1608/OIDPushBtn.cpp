#include "OIDPushBtn.h"
#include "OIDInputDlg.h"
#include <QDebug>
#include "ConfigMgr.h"


using namespace std::tr1::placeholders;

void OIDPushBtn::mouseReleaseEvent ( QMouseEvent * event ){
	if ( !ConfigMgr::instance()->isOidEditable() ) return;
	OIDInputDlg::getNewOid( this->objectName(), oid_, defaultOid_ );
}

void OIDPushBtn::setImage(QPixmap &offImage){
	QIcon ButtonIcon(offImage);
	setIcon(ButtonIcon);
	setIconSize(QSize(offImage.rect().size()));
}

OIDStatePushBtn::OIDStatePushBtn( QWidget* w):
QPushButton(w)
,val_(0)
{
	setToolTip(objectName() );
	startTimer(500);
	//SnmpNet::instance()->addAsyncGet( oid_.toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1, _2, _3, _4) );
}

void OIDStatePushBtn::timerEvent ( QTimerEvent * event ){
	setChecked(val_);
	if ( val_){
		QIcon buttonIcon(onImage_);
		setIcon(buttonIcon);
		setIconSize(QSize(onImage_.rect().size()));
	}else{
		QIcon buttonIcon(offImage_);
		setIcon(buttonIcon);
		setIconSize(QSize(offImage_.rect().size()));
	}
}
SnmpCallback::RequestStatus OIDStatePushBtn::snmpCallback( int , snmp_session*, snmp_pdu* pdu, SnmpObj*){
	if (pdu->variables->type == ASN_INTEGER){
		val_ = *(u_long *) (pdu->variables->val.integer);
	}
	return SnmpCallback::RequestStop;
}


void OIDStatePushBtn::mouseReleaseEvent ( QMouseEvent * event ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		if ( !ConfigMgr::instance()->isOidEditable() ) return;
		OIDInputDlg::getNewOid( this->objectName(), oid_, defaultOid_ );
	}else{
		this->toggle();
		if ( this->isChecked()){
			SnmpNet::instance()->addAsyncSet(  oid_.toStdString().c_str(), "private", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this, _1, _2, _3, _4) , 1);
		}else{
			SnmpNet::instance()->addAsyncSet(  oid_.toStdString().c_str(), "private", std::bind<SnmpCallbackFunc>( &OIDStatePushBtn::snmpCallback, this,_1, _2, _3, _4) , 0);
		}
	}
}
void OIDStatePushBtn::setOnOffStateImage(int onState, int offState, QPixmap &onImage, QPixmap &offImage ){
	onImage_ =onImage;
	offImage_ =offImage;
	QIcon buttonIcon(offImage);
	setIcon(buttonIcon);
	setIconSize(QSize(offImage.rect().size()));
}