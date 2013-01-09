#include "presetwnd.h"
#include "ui_presetwnd.h"

PresetWnd::PresetWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresetWnd)
{
    ui->setupUi(this);
}

PresetWnd::~PresetWnd()
{
    delete ui;
}
