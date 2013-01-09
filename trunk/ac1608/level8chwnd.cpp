#include "level8chwnd.h"
#include "ui_level8chwnd.h"

Level8CHWnd::Level8CHWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Level8CHWnd)
{
    ui->setupUi(this);
}

Level8CHWnd::~Level8CHWnd()
{
    delete ui;
}
