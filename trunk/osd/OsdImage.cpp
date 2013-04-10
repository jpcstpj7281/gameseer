#include "OsdImage.h"
#include "ui_OsdImage.h"
#include "QPushButton.h"

OsdImage::OsdImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OsdImage)
{
    ui->setupUi(this);

    QPushButton * initBtn  = findChild<QPushButton*>("declarativeView" );
    if ( initBtn) {
    	connect( initBtn, SIGNAL( clicked()), this, SLOT( clickinit() ) );
    }


   
}

void OsdImage::clickinit(){
}

OsdImage::~OsdImage()
{
    delete ui;
}
