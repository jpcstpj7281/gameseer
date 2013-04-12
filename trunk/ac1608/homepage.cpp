#include "homepage.h"
#include "ui_homepage.h"


#include <qprogressbar>
#include <QSlider>
#include <QList>
#include <QDebug>
#include "OIDInputDlg.h"
#include "oidprogressbar.h"

#include "OIDProgressBar.h"


HomePage::HomePage(QWidget *parent):
    QWidget(parent)
	,ui(new Ui::HomePage)
{
    ui->setupUi(this);

	QList<OIDSlider *> qsl = findChildren<OIDSlider*>( );
	for ( QList<OIDSlider *>::Iterator it = qsl.begin(); it != qsl.end(); ++it){
		OIDSlider* qs = *it;
		qs->setToolTip( qs->objectName());
		qs->initSnmp();
		QString name = qs->objectName();
		name.replace( "verticalSlider", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		qs->setLabel(ql);
	}

	QList<OIDStatePushBtn *> qpb = findChildren<OIDStatePushBtn*>( );
	if ( !qpb.isEmpty() ){
		QPixmap XpushBtn("res/XpushBtn.png");
		QPixmap XpushBtnOff("res/XpushBtn_off.png");
		QPixmap anpushBtn("res/+-pushBtn.png");
		QPixmap anpushBtnOff("res/+-pushBtn_off.png");
		for ( QList<OIDStatePushBtn *>::Iterator it = qpb.begin(); it != qpb.end(); ++it){
			OIDStatePushBtn* qs = *it;
			qs->initSnmp();
			QString name = qs->objectName();
			if (name.contains("amp") ){
				qs->setOnOffStateImage( 1, 0, anpushBtn, anpushBtnOff);
			}else{
				qs->setOnOffStateImage( 1, 0, XpushBtn, XpushBtnOff);
			}
		}
		//qDebug()<<qpb.size()<<" OIDStatePushBtn";
	}

	QList<QWidget *> qwl  = findChildren<QWidget*>( );
	for ( QList<QWidget *>::Iterator it = qwl.begin(); it != qwl.end();){
		if ( (*it)->objectName().contains( "progressBar")){
			++it;
		}else{
			it = qwl.erase(it);
		}
	}
	for ( QList<QWidget *>::Iterator it = qwl.begin(); it != qwl.end(); ++it){
		QWidget* qw = *it;
		QVBoxLayout *memLayout = new QVBoxLayout( qw );
		Qt::Orientation o = Qt::Vertical;
		OIDProgressBar* qpb = new OIDProgressBar( o, "Used", qw, 0 );
		qw->layout()->addWidget(qpb );
		qw->layout()->setMargin( 0 );
        qw->layout()->setSpacing( 0 );

		qpb->initSnmp();
		qpb->setToolTip( qpb->objectName());
		qpb->setValue(0);
	}
}

HomePage::~HomePage()
{
    delete ui;
}

