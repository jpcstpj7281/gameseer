#include "highpasswnd.h"
#include "ui_highpasswnd.h"


#include <qlayout.h>
#include "ACPlot.h"
#include "OIDPushBtn.h"
#include "OidDial.h"
#include <qcombobox.h>
#include <QTabWidget>
#include <QPushButton>

HighPassWnd::HighPassWnd(QTabWidget *parent) :
    QWidget(parent),
    ui(new Ui::HighPassWnd)
	,tab_(parent)
{
    ui->setupUi(this);

    QWidget * qw  = findChild<QWidget*>("HighPassGraph" );
    if ( qw) {
		ACPlot *plot = new ACPlot( this );

		// The canvas picker handles all mouse and key
		// events on the plot canvas
		QVBoxLayout *layout = new QVBoxLayout( qw );
		qw->setLayout(layout);
		qw->layout()->addWidget(plot);
    }

	qpbl_ = findChildren<QPushButton*>( );
	for ( QList<QPushButton *>::Iterator it = qpbl_.begin(); it != qpbl_.end(); ){
		QPushButton* btn = *it;
		if ( btn->objectName() == "btnBypass" || btn->objectName().contains("pbCopy")|| btn->objectName().contains("pbPaste")|| btn->objectName().contains("pbReset")){
			it = qpbl_.erase( it);
		}else{
			connect( btn, SIGNAL(clicked()), this, SLOT(clickch()));
			++it;
		}
	}

	currCHBtn_ = qpbl_.front();

	bypass_ = findChild<OIDStatePushBtn*>("btnBypass" );
	if ( bypass_ ){
		//QPixmap bypass2Btn("res/BypassBtn.png");
		//QPixmap bypass2Off("res/BypassBtn_off.png");
		//bypass_->setOnOffStateImage( 1, 0, bypass2Btn, bypass2Off);
		bypass_->setObjectName( "highpass_"+ bypass_->objectName() + currCHBtn_->objectName());
		bypass_->setToolTip(bypass_->objectName());
	}

	qdl_ = findChildren<OIDDial*>( );
	for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
		OIDDial* qs = *it;

		QString name = qs->objectName();
		name.replace( "dial_", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		if (ql)qs->setLabel(ql);

		qs->setObjectName( "highpass_"+qs->objectName() + currCHBtn_->objectName());
		qs->setToolTip(qs->objectName() );
	}

	connect ( parent, SIGNAL(currentChanged ( int )), this, SLOT(indexChanged(int) ) );
}

HighPassWnd::~HighPassWnd()
{
    delete ui;
}


void HighPassWnd::indexChanged(int index){
	QWidget* maybeThis = tab_->widget(index);
	if (maybeThis == this){
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			(*it)->initSnmp();
		}
		if ( bypass_) bypass_->initSnmp();
	}else{
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
		if ( bypass_) bypass_->shutdownSnmp();
	}
}


void HighPassWnd::clickch(){
	if ( sender() == currCHBtn_) return;
	currCHBtn_->setEnabled(true);
	currCHBtn_->setStyleSheet("* { background-color: lightGray }");

	if ( bypass_ ){
		bypass_->shutdownSnmp();
		bypass_->setObjectName( bypass_->objectName().replace(  currCHBtn_->objectName(), sender()->objectName() ) );
		bypass_->setToolTip(bypass_->objectName());
		bypass_->initSnmp();
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

