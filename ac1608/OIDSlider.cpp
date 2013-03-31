#include "OIDSlider.h"
#include "OIDInputDlg.h"
#include "ConfigMgr.h"
#include <QDebug>
#include <QEvent>
using namespace std::tr1::placeholders;


OIDSlider::OIDSlider( QWidget* w):
    QSlider(w)
    ,val_(0){
        connect( this, SIGNAL(valueChanged(int )), this, SLOT(fireSnmp(int )));
        startTimer(500);
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
    SnmpNet::instance()->addAsyncGet( objectName().toStdString().c_str(), ConfigMgr::instance()->getOid(objectName()).toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDSlider::snmpCallback, this, _1, _2, _3, _4) );
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
            QString oid = OIDInputDlg::getNewOid( this->objectName());
            if (!oid.isEmpty()){
                SnmpNet::instance()->addAsyncGet(objectName().toStdString().c_str(),  oid.toStdString().c_str(), "public", std::bind<SnmpCallbackFunc>( &OIDSlider::snmpCallback, this, _1, _2, _3, _4) );
            }
        }
        return true;
    }else{
        QSlider::eventFilter(watched, event);
    }
    return false;
}

void	OIDSlider::timerEvent ( QTimerEvent * e ){
    size_t now = GetTickCount();
    size_t elapsed = now - lastTimeChanged_;
    if ( elapsed > 1000 && val_ != this->value() ){
        lastTimeChanged_ = now;
        this->setValue( val_);
        //qDebug()<<"Outside changed value or value snmp delay! OIDSlider::timerEvent";
    }
}

void OIDSlider::fireSnmp(int val ){
    if ( !ConfigMgr::instance()->isOidEditable() ) {
        QString oid = ConfigMgr::instance()->getOid(objectName());
        SnmpNet::instance()->addAsyncSet( objectName().toStdString().c_str(), oid.toStdString().c_str(), "private", std::bind<SnmpCallbackFunc>( &OIDSlider::snmpCallback, this, _1, _2, _3, _4) , val);
        lastTimeChanged_ = GetTickCount();
    }
}

SnmpCallback::RequestStatus OIDSlider::snmpCallback( int , snmp_session*, snmp_pdu* pdu, SnmpObj* so){
    if (pdu->variables->type == ASN_INTEGER){
        val_ = *(u_long *) (pdu->variables->val.integer);
    }
    if ( so->var.type() )
        return SnmpCallback::RequestStop;
    else
        return SnmpCallback::RequestAgain;
}
