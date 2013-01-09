#include "meterswnd.h"
#include "ui_meterswnd.h"

MetersWnd::MetersWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetersWnd)
{
    ui->setupUi(this);
}

MetersWnd::~MetersWnd()
{
    delete ui;
}
