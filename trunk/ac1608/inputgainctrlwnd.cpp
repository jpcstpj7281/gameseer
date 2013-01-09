#include "inputgainctrlwnd.h"
#include "ui_inputgainctrlwnd.h"

InputGainCtrlWnd::InputGainCtrlWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputGainCtrlWnd)
{
    ui->setupUi(this);
}

InputGainCtrlWnd::~InputGainCtrlWnd()
{
    delete ui;
}
