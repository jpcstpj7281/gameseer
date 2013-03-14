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
	QList<QProgressBar *> qpl  = findChildren<QProgressBar*>( );
	for ( QList<QProgressBar *>::Iterator it = qpl.begin(); it != qpl.end(); ++it){
		QProgressBar * qpb = *it;
		qDebug()<<qpb->objectName();
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
		qs->setStyleSheet(
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

	QList<OIDStatePushBtn *> qpb = findChildren<OIDStatePushBtn*>( );
	if ( !qpb.isEmpty() ){
		QPixmap XpushBtn("res/XpushBtn.png");
		QPixmap XpushBtnOff("res/XpushBtn_off.png");
		QPixmap anpushBtn("res/+-pushBtn.png");
		QPixmap anpushBtnOff("res/+-pushBtn_off.png");
		for ( QList<OIDStatePushBtn *>::Iterator it = qpb.begin(); it != qpb.end(); ++it){
			OIDStatePushBtn* qs = *it;
			
			QString name = qs->objectName();
			if (name.contains("amp") ){
				qs->setOnOffStateImage( 1, 0, anpushBtn, anpushBtnOff);
			}else{
				qs->setOnOffStateImage( 1, 0, XpushBtn, XpushBtnOff);
			}
		}
	}
}

HomePage::~HomePage()
{
    delete ui;
}

