#include "peqwnd.h"
#include "ui_peqwnd.h"

#include <qlayout.h>
#include <QDebug>
#include "ACPlot.h"

PEQWnd::PEQWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PEQWnd)
{
    ui->setupUi(this);


	QWidget * qw  = findChild<QWidget*>("PEQGraph" );
    if ( qw) {
		ACPlot *plot = new ACPlot( this );

		// The canvas picker handles all mouse and key
		// events on the plot canvas
		( void ) new CanvasPicker( plot );
		QVBoxLayout *layout = new QVBoxLayout( qw );
		qw->setLayout(layout);
		qw->layout()->addWidget(plot);
    }
	qw  = findChild<QWidget*>("Band4PEQ" );
	if ( qw){
		qw->setHidden(true);
	}
}

PEQWnd::~PEQWnd()
{
    delete ui;
}
