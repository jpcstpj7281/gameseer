#include "nomwnd.h"
#include "ui_nomwnd.h"

#include <qprogressbar>
#include <QSlider>
#include <QList>
#include <QDebug>

NOMWnd::NOMWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NOMWnd)
{
    ui->setupUi(this);

	QList<QSlider *> qsl = findChildren<QSlider*>( );
	for ( QList<QSlider *>::Iterator it = qsl.begin(); it != qsl.end(); ++it){
		QSlider* qs = *it;
		//qDebug()<<qs->objectName();
		qs->setValue( 80);
		qs->setStyleSheet(
			"QSlider { "
			"width: 50px; "
			"height: 50px;"
			"}"
			"QSlider::groove:vertical {"
			//"border: 1px solid #999999;"
			"background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #B1B1B1, stop:1 #c4c4c4);"
			"height: 170px;"
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
}

NOMWnd::~NOMWnd()
{
    delete ui;
}
