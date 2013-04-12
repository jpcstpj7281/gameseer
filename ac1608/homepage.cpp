#include "homepage.h"
#include "ui_homepage.h"
#include <QSlider>
#include <QList>
#include <QDebug>
#include "OIDInputDlg.h"
#include "OIDProgressBar.h"
#include <qtablewidget.h>


HomePage::HomePage(QTabWidget *parent):
    QWidget(parent)
	,ui(new Ui::HomePage)
	,tab_(parent)
{
    ui->setupUi(this);

	qsl_ = findChildren<OIDSlider*>( );
	for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
		OIDSlider* qs = *it;
		qs->setToolTip( qs->objectName());
		QString name = qs->objectName();
		name.replace( "verticalSlider", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		qs->setLabel(ql);
	}

	qpbtnl_ = findChildren<OIDStatePushBtn*>( );
	if ( !qpbtnl_.isEmpty() ){
		QPixmap XpushBtn("res/XpushBtn.png");
		QPixmap XpushBtnOff("res/XpushBtn_off.png");
		QPixmap anpushBtn("res/+-pushBtn.png");
		QPixmap anpushBtnOff("res/+-pushBtn_off.png");
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			OIDStatePushBtn* qs = *it;
			QString name = qs->objectName();
			if (name.contains("amp") ){
				qs->setOnOffStateImage( 1, 0, anpushBtn, anpushBtnOff);
			}else{
				qs->setOnOffStateImage( 1, 0, XpushBtn, XpushBtnOff);
			}
		}
	}

	QList<QWidget *> qwl  = findChildren<QWidget*>( );
	for ( QList<QWidget *>::Iterator it = qwl.begin(); it != qwl.end();){
		if ( (*it)->objectName().contains( "progressBar")){
			++it;
		}else{
			it = qwl.erase(it);
		}
	}
	for ( QList<QWidget *>::Iterator it = qwl.begin(); it != qwl.end(); ++it){
		QWidget* qw = *it;
		new QVBoxLayout( qw );
		Qt::Orientation o = Qt::Vertical;
		OIDProgressBar* qpb = new OIDProgressBar( o, "Used", qw, 0 );
		qw->layout()->addWidget(qpb );
		qw->layout()->setMargin( 0 );
        qw->layout()->setSpacing( 0 );
		qpb->setToolTip( qpb->objectName());
		qpb->setValue(0);
		qpbarl_.push_back(qpb);
	}

	connect ( parent, SIGNAL(currentChanged ( int )), this, SLOT(indexChanged(int) ) );
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::indexChanged(int index){
	QWidget* maybeThis = tab_->widget( index);
	if (maybeThis == this){
		for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
			(*it)->initSnmp();
		}
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			(*it)->initSnmp();
		}
		for ( QList<OIDProgressBar *>::Iterator it = qpbarl_.begin(); it != qpbarl_.end(); ++it){
			(*it)->initSnmp();
		}
	}else{
		for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
		for ( QList<OIDProgressBar *>::Iterator it = qpbarl_.begin(); it != qpbarl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
	}
}

