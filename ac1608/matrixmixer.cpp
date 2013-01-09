#include "matrixmixer.h"
#include "ui_matrixmixer.h"

MatrixMixer::MatrixMixer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatrixMixer)
{
    ui->setupUi(this);
}

MatrixMixer::~MatrixMixer()
{
    delete ui;
}
