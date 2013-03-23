#include "inputgainctrlwnd.h"
#include "ui_inputgainctrlwnd.h"

#include <qprogressbar>
#include <QSlider>
#include <QList>
#include <QDebug>
#include "oidpushbtn.h"

InputGainCtrlWnd::InputGainCtrlWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputGainCtrlWnd)
{
    ui->setupUi(this);

	QList<OIDSlider *> qsl = findChildren<OIDSlider*>( );
	for ( QList<OIDSlider *>::Iterator it = qsl.begin(); it != qsl.end(); ++it){
		OIDSlider* qs = *it;
		qs->initSnmp();

	}

	QList<OIDStatePushBtn *> qpb = findChildren<OIDStatePushBtn*>( );
	if ( !qpb.isEmpty() ){
		for ( QList<OIDStatePushBtn *>::Iterator it = qpb.begin(); it != qpb.end(); ++it){
			OIDStatePushBtn* qs = *it;
			qs->initSnmp();
		}
	}
}

InputGainCtrlWnd::~InputGainCtrlWnd()
{
    delete ui;
}
