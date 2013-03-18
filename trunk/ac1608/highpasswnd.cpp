#include "highpasswnd.h"
#include "ui_highpasswnd.h"
#include <QDeclarativeView>

HighPassWnd::HighPassWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighPassWnd)
{
    ui->setupUi(this);

	QDeclarativeView * dv  = findChild<QDeclarativeView*>("declarativeView" );
	if ( dv) {
		dv->setSource(QUrl::fromLocalFile("res/graph.qml"));
		dv->show();
	}
}

HighPassWnd::~HighPassWnd()
{
    delete ui;
}
