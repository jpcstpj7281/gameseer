#include "highpasswnd.h"
#include "ui_highpasswnd.h"

HighPassWnd::HighPassWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighPassWnd)
{
    ui->setupUi(this);
}

HighPassWnd::~HighPassWnd()
{
    delete ui;
}
