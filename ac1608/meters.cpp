#include "meters.h"
#include "ui_meters.h"

Meters::Meters(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Meters)
{
    ui->setupUi(this);
}

Meters::~Meters()
{
    delete ui;
}
