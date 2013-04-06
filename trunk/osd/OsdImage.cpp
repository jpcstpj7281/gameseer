#include "OsdImage.h"
#include "ui_OsdImage.h"
#include <QtDeclarative/QDeclarativeView>


OsdImage::OsdImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OsdImage)
{
    ui->setupUi(this);

    //QDeclarativeView * dv  = findChild<QDeclarativeView*>("declarativeView" );
    //if ( dv) {
    //	dv->setSource(QUrl::fromLocalFile("res/drawGraph.qml"));
    //	dv->show();
    //}


   
}

OsdImage::~OsdImage()
{
    delete ui;
}
