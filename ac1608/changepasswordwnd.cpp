#include "changepasswordwnd.h"
#include "ui_changepasswordwnd.h"

ChangePasswordWnd::ChangePasswordWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChangePasswordWnd)
{
    ui->setupUi(this);
}

ChangePasswordWnd::~ChangePasswordWnd()
{
    delete ui;
}
