#include "matrixmixerwnd.h"
#include "ui_matrixmixerwnd.h"

MatrixMixerWnd::MatrixMixerWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatrixMixerWnd)
{
    ui->setupUi(this);
}

MatrixMixerWnd::~MatrixMixerWnd()
{
    delete ui;
}
