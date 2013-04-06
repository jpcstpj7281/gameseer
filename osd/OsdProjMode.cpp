#include "OsdProjMode.h"
#include "ui_OsdProjMode.h"
#include <QtDeclarative/QDeclarativeView>


OsdProjMode::OsdProjMode(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OsdProjMode)
{
    ui->setupUi(this);

    //QDeclarativeView * dv  = findChild<QDeclarativeView*>("declarativeView" );
    //if ( dv) {
    //	dv->setSource(QUrl::fromLocalFile("res/drawGraph.qml"));
    //	dv->show();
    //}


   
}

OsdProjMode::~OsdProjMode()
{
    delete ui;
}
