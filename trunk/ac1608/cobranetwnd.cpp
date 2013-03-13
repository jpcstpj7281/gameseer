#include "CobraNetWnd.h"
#include "ui_CobraNetWnd.h"


#include <qprogressbar>
#include <QSlider>
#include <QList>
#include <QDebug>

CobraNetWnd::CobraNetWnd(QWidget *parent):
    QWidget(parent)
	,ui(new Ui::CobraNetWnd)
{
    ui->setupUi(this);
}

CobraNetWnd::~CobraNetWnd()
{
    delete ui;
}

