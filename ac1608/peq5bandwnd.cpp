#include "peq5bandwnd.h"
#include "ui_peq5bandwnd.h"

PEQ5BandWnd::PEQ5BandWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PEQ5BandWnd)
{
    ui->setupUi(this);
}

PEQ5BandWnd::~PEQ5BandWnd()
{
    delete ui;
}
