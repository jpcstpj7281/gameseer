#include "inputgainctrlwnd.h"
#include "ui_inputgainctrlwnd.h"

#include <qprogressbar>
#include <QSlider>
#include <QList>
#include <QDebug>
#include "oidpushbtn.h"

InputGainCtrlWnd::InputGainCtrlWnd(QTabWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputGainCtrlWnd)
	,tab_(parent)
{
    ui->setupUi(this);

	qsl_ = findChildren<OIDSlider*>( );
	for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
		OIDSlider* qs = *it;
		QString name = qs->objectName();
		qs->setObjectName( "input_"+qs->objectName());
		qs->setToolTip( qs->objectName());

		name.replace( "verticalSlider_", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		qs->setLabel(ql);
	}

	qpbtnl_ = findChildren<OIDStatePushBtn*>( );
	for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
		OIDStatePushBtn* qs = *it;
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
