#include "highpasswnd.h"
#include "ui_highpasswnd.h"
#include <QtDeclarative/QDeclarativeView>


#include <qlayout.h>
#include "ACPlot.h"



HighPassWnd::HighPassWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighPassWnd)
{
    ui->setupUi(this);

    QWidget * qw  = findChild<QWidget*>("HighPassGraph" );
    if ( qw) {
		ACPlot *plot = new ACPlot( this );

		// The canvas picker handles all mouse and key
		// events on the plot canvas
		( void ) new CanvasPicker( plot );
		QVBoxLayout *layout = new QVBoxLayout( qw );
		qw->setLayout(layout);
		qw->layout()->addWidget(plot);
    }
}

HighPassWnd::~HighPassWnd()
{
    delete ui;
}
