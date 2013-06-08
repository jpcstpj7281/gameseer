#include "ChnWnd.h"
#include "ui_ChnWnd.h"
#include <qdebug.h>
#include "screen.h"


ChnWnd::ChnWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::ChnWnd)
{
    ui->setupUi(this);
}

ChnWnd::~ChnWnd()
{
    delete ui;
}

