#include "peqwnd.h"
#include "ui_peqwnd.h"

#include <qlayout.h>
#include <QDebug>
#include "ACPlot.h"


#include <qlayout.h>
#include "ACPlot.h"
#include "OIDPushBtn.h"
#include "OidDial.h"
#include <qcombobox.h>
#include <QTabWidget>
#include <QPushButton>

PEQWnd::PEQWnd(QTabWidget *parent) :
    QWidget(parent),
    ui(new Ui::PEQWnd)
	,tab_(parent)
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
	

	qpbl_ = findChildren<QPushButton*>( );
	for ( QList<QPushButton *>::Iterator it = qpbl_.begin(); it != qpbl_.end(); ){
		QPushButton* btn = *it;
		if ( btn->objectName().contains("btnInput") || btn->objectName().contains("btnOutput")){
			it = qpbl_.erase(it);
		}else{
			connect( btn, SIGNAL(clicked()), this, SLOT(clickch()));
			++it;
		}
	}
	

	currCHBtn_ = qpbl_.front();

	qdl_ = findChildren<OIDDial*>( );
	for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
		OIDDial* qs = *it;
		QString name = qs->objectName();
		name.replace( "dial_", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		if (ql)qs->setLabel(ql);

		qs->setObjectName( "peq_"+qs->objectName() + currCHBtn_->objectName());
		qs->setToolTip(qs->objectName() );
	}

	connect ( parent, SIGNAL(currentChanged ( int )), this, SLOT(indexChanged(int) ) );

	currCHBtn_->setEnabled(false);
}

PEQWnd::~PEQWnd()
{
    delete ui;
}

void PEQWnd::indexChanged(int index){
	QWidget* maybeThis = tab_->widget(index);
	if (maybeThis == this){
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			(*it)->initSnmp();
		}
	}else{
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
	}
}


void PEQWnd::clickch(){
	if ( sender() == currCHBtn_) return;
	currCHBtn_->setEnabled(true);
	currCHBtn_->setStyleSheet("* { background-color: lightGray }");

	if ( sender()->objectName().contains("Input")){
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			OIDDial* qs = *it;
			if (qs->objectName().contains("dial_5") || qs->objectName().contains("dial_10")|| qs->objectName().contains("dial_15")){
				qs->setEnabled(false);
			}
		}
	}else{
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			OIDDial* qs = *it;
			qs->setEnabled(true);
		}
	}

	qdl_ = findChildren<OIDDial*>( );
	for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
		OIDDial* qs = *it;
		qs->shutdownSnmp();
		qs->setObjectName( qs->objectName().replace(  currCHBtn_->objectName(), sender()->objectName() ));
		qs->setToolTip(qs->objectName());
		qs->initSnmp();
	}

	currCHBtn_ = (QPushButton*)sender();

	currCHBtn_->setEnabled(false);
	currCHBtn_->setStyleSheet("* { background-color: lightGreen }");
}

