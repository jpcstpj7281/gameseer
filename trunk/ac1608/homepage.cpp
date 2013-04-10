#include "homepage.h"
#include "ui_homepage.h"


#include <qprogressbar>
#include <QSlider>
#include <QList>
#include <QDebug>
#include "OIDInputDlg.h"
#include "oidprogressbar.h"




HomePage::HomePage(QWidget *parent):
    QWidget(parent)
	,ui(new Ui::HomePage)
{
    ui->setupUi(this);
	QList<OIDProgressBar *> qpl  = findChildren<OIDProgressBar*>( );
	for ( QList<OIDProgressBar *>::Iterator it = qpl.begin(); it != qpl.end(); ++it){
		OIDProgressBar * qpb = *it;
		//qDebug()<<qpb->objectName();
		qpb->initSnmp();
		qpb->setToolTip( qpb->objectName());
		if (qpb){
		qpb->setValue(-100);
		//qpb->setStyleSheet(
		//	" QProgressBar:vertical {"
		//	"width:100px;"
		//	"height:100px;"
		//	"border: 1px solid grey;"
		//	"border-radius: 3px;"
		//	//"background: white;"
		//	"text-align: bottom;"
		//	"margin-bottom: 20px;"
		//	"background-color: #ffffff;"
		//	"}"
		//	"QProgressBar::chunk:vertical{ "
		//	"width: 100px;"
		//	"}"
		//	);
		}
	}
	

	QList<OIDSlider *> qsl = findChildren<OIDSlider*>( );
	for ( QList<OIDSlider *>::Iterator it = qsl.begin(); it != qsl.end(); ++it){
		OIDSlider* qs = *it;
		qs->setToolTip( qs->objectName());
		qs->initSnmp();
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
		qDebug()<<qpb.size()<<" OIDStatePushBtn";
	}
}

HomePage::~HomePage()
{
    delete ui;
}

