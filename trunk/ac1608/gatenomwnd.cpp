#include "gatenomwnd.h"
#include "ui_gatenomwnd.h"

GateNOMWnd::GateNOMWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GateNOMWnd)
{
    ui->setupUi(this);
}

GateNOMWnd::~GateNOMWnd()
{
    delete ui;
}
