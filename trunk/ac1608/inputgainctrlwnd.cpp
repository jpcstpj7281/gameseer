#include "inputgainctrlwnd.h"
#include "ui_inputgainctrlwnd.h"

#include <qprogressbar>
#include <QSlider>
#include <QList>
#include <QDebug>
#include "oidpushbtn.h"
#include "ConfigMgr.h"

InputGainCtrlWnd::InputGainCtrlWnd(QTabWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputGainCtrlWnd)
	,tab_(parent)
{
    ui->setupUi(this);

	int max, min, def;
	ConfigMgr::instance()->getSetting( "slider", max, min, def);
	qsl_ = findChildren<OIDSlider*>( );
	for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
		OIDSlider* qs = *it;
		QString name = qs->objectName();
		qs->setObjectName( "input_"+qs->objectName());
		qs->setToolTip( qs->objectName());

		name.replace( "verticalSlider_", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		qs->setLabel(ql);
		qs->setMaximum( max);
		qs->setMinimum( min);
		qs->setValue(def);
	}

	qpbtnl_ = findChildren<OIDStatePushBtn*>( );
	QString val1, val2, val3;
	ConfigMgr::instance()->getValue( "input_btn_1", val1);
	ConfigMgr::instance()->getValue( "input_btn_2", val2);
	ConfigMgr::instance()->getValue( "input_btn_3", val3);
	int v1 = val1.toInt();
	int v2 = val2.toInt();
	int v3 = val3.toInt();
	for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
		OIDStatePushBtn* qs = *it;
		QString name = qs->objectName();
		int id = name.replace( "pushButton_", "").toInt();
		if (id < 17 ){
			qs->setTrueState( v1);
		}else if ( id < 23) {
			qs->setTrueState( v2);
		}else{
			qs->setTrueState( v3);
		}

		qs->setObjectName( "input_"+qs->objectName());
		qs->setToolTip( qs->objectName());
	}

	connect ( parent, SIGNAL(currentChanged ( int )), this, SLOT(indexChanged(int) ) );
}
InputGainCtrlWnd::~InputGainCtrlWnd()
{
    delete ui;
}
void InputGainCtrlWnd::indexChanged(int index){
	QWidget* maybeThis = tab_->widget(index);
	if (maybeThis == this){
		for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
			(*it)->initSnmp();
		}
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			(*it)->initSnmp();
		}
	}else{
		for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
	}
}
