#include "RingWnd.h"
#include "ui_RingWnd.h"
#include <qdebug.h>
#include "screen.h"


RingWnd::RingWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::RingWnd)
{
    ui->setupUi(this);
}

RingWnd::~RingWnd()
{
    delete ui;
}

