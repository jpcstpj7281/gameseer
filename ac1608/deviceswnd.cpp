#include "deviceswnd.h"
#include "ui_deviceswnd.h"

DevicesWnd::DevicesWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevicesWnd)
{
    ui->setupUi(this);
}

DevicesWnd::~DevicesWnd()
{
    delete ui;
}
