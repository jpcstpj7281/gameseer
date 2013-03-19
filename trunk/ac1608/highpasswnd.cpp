#include "highpasswnd.h"
#include "ui_highpasswnd.h"
#include <QtDeclarative/QDeclarativeView>


HighPassWnd::HighPassWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighPassWnd)
{
    ui->setupUi(this);

    QDeclarativeView * dv  = findChild<QDeclarativeView*>("declarativeView" );
    if ( dv) {
    	dv->setSource(QUrl::fromLocalFile("res/drawGraph.qml"));
    	dv->show();
    }


   
}

HighPassWnd::~HighPassWnd()
{
    delete ui;
}
