#include "copyparamwnd.h"
#include "ui_copyparamwnd.h"

CopyParamWnd::CopyParamWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CopyParamWnd)
{
    ui->setupUi(this);
}

CopyParamWnd::~CopyParamWnd()
{
    delete ui;
}
