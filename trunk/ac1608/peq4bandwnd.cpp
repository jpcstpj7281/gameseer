#include "peq4bandwnd.h"
#include "ui_peq4bandwnd.h"

PEQ4BandWnd::PEQ4BandWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PEQ4BandWnd)
{
    ui->setupUi(this);
}

PEQ4BandWnd::~PEQ4BandWnd()
{
    delete ui;
}
