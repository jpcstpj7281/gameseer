#include "OIDSlider.h"
#include "OIDInputDlg.h"
#include "ConfigMgr.h"
#include <QDebug>
#include <QEvent>

using namespace std::tr1::placeholders;


OIDSlider::OIDSlider( QWidget* w):
    QSlider(w)
    ,val_(0)
	,ql_(0){
        connect( this, SIGNAL(valueChanged(int )), this, SLOT(fireSnmp(int )));
        installEventFilter(this);

        setToolTip( objectName());
        this->setStyleSheet(
                "QSlider { "
                "width: 50px; "
                "height: 50px;"
                "}"
                "QSlider::groove:vertical {"
                //"border: 1px solid #999999;"
                "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
                "height: 150px;"
                "width: 2px;"
                "top: 0px; "
                "bottom: 0px;"
                "border: 1px solid grey;"
                "border-radius: 5px;"
                "margin: 0 0 0 0;}"
                "QSlider::handle:vertical {"
                "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:1 #b4b4b4, stop:0 #8f8f8f);"
                "image:url(res/sliderBtn.png) 0 30 0 30;"
                //"background:url(res/sliderBtn.png) 0 29 0 32;"
                //"border: 0px solid #5c5c5c;"
                //"width: 10px;"
                //"height: 10px;"
                "margin: -15px -15px -15px -15px;"
                //"background:transparent"
                "border-radius: 100px;"
                "}"
                //"QSlider::sub-page:vertical{ "
                //" background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(27, 5, 27, 255), stop:0.25 rgba(99, 20, 102, 255), stop:0.5 rgba(154, 30, 158, 255), stop:1 rgba(173, 57, 176, 255)); "
                //"}"

                );
    }

void OIDSlider::initSnmp(){
	QString oid = ConfigMgr::instance()->getOid(objectName());
	if ( ! oid.isEmpty()){
		SnmpNet::instance()->addAsyncGet(
			objectName().toStdString(), 
			oid.toStdString(), 
			"public", 
			std::bind<SnmpCallbackFunc>( &OIDSlider::snmpCallback, this, _1) 
			);
	}

	
}
void OIDSlider::shutdownSnmp(){
	QString oid = ConfigMgr::instance()->getOid( objectName());
	if (!oid.isEmpty())
		SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oid.toStdString() , std::string("public"));
}

void OIDSlider::setLabel(QLabel *ql){
	ql_ = ql;
}

bool OIDSlider::eventFilter ( QObject * watched, QEvent * event ){
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

			QString oldoid = ConfigMgr::instance()->getOid( objectName());
			QString oid = OIDInputDlg::getNewOid( this->objectName() );
			if (!oid.isEmpty() && oid != oldoid){
				if ( !oldoid.isEmpty()){
					SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oldoid.toStdString() , std::string("public"));
				}
				SnmpNet::instance()->addAsyncGet(objectName().toStdString(), oid.toStdString(), 
					"public", std::bind<SnmpCallbackFunc>( &OIDSlider::snmpCallback, this, _1) );
			}
        }
        return true;
    }else{
        QSlider::eventFilter(watched, event);
    }
    return false;
}


void OIDSlider::fireSnmp(int val ){
    if ( !ConfigMgr::instance()->isOidEditable() ) {
        QString oid = ConfigMgr::instance()->getOid(objectName());
        SnmpNet::instance()->addAsyncSet( objectName().toStdString(), oid.toStdString(), 
			"private", std::bind<SnmpCallbackFunc>( &OIDSlider::snmpCallback, this, _1) , val);
        lastTimeChanged_ = GetTickCount();
		if (ql_){
			ql_->setText( QString::number( val));
		}
    }
}

void OIDSlider::snmpCallback( SnmpObj* so){
    if ( so->setVar.isNull() ){
        this->setValue( so->rspVar.value<int>() );
		if (ql_){
			ql_->setText( QString::number( value()));
		}

		QString oid = ConfigMgr::instance()->getOid( objectName());
		if (!oid.isEmpty())
			SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oid.toStdString() , std::string("public"));
	}
}
