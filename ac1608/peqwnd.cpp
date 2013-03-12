#include "peqwnd.h"
#include "ui_peqwnd.h"

#include <qprogressbar>
#include <QSlider>
#include <QList>
#include <QDebug>

PEQWnd::PEQWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PEQWnd)
{
    ui->setupUi(this);

}

PEQWnd::~PEQWnd()
{
    delete ui;
}
