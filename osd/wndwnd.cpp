#include "WndWnd.h"
#include "ui_WndWnd.h"
#include <qdebug.h>
#include "screen.h"


WndWnd::WndWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::WndWnd)
{
    ui->setupUi(this);
}

WndWnd::~WndWnd()
{
    delete ui;
}

