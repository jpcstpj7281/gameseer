#include "gatenomwnd.h"
#include "ui_gatenomwnd.h"

#include "OidDial.h"

GateNOMWnd::GateNOMWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GateNOMWnd)
{
    ui->setupUi(this);


	QList<OIDDial *> qsl = findChildren<OIDDial*>( );
	for ( QList<OIDDial *>::Iterator it = qsl.begin(); it != qsl.end(); ++it){
		OIDDial* qs = *it;
		qs->initSnmp();

	}
}

GateNOMWnd::~GateNOMWnd()
{
    delete ui;
}
