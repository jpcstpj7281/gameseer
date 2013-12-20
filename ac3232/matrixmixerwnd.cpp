#include "matrixmixerwnd.h"
#include "ui_matrixmixerwnd.h"
#include "OIDPushBtn.h"


MatrixMixerWnd::MatrixMixerWnd(QTabWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatrixMixerWnd)
	,tab_(parent)
{
    ui->setupUi(this);


	qpbtnl_ = findChildren<OIDStatePushBtn*>( );
	if ( !qpbtnl_.isEmpty() ){
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			OIDStatePushBtn* qs = *it;
			QString name = qs->objectName();
			qs->setObjectName( "matrixmix_"+qs->objectName());
			qs->setToolTip(qs->objectName());
		}
	}

	connect ( parent, SIGNAL(currentChanged ( int )), this, SLOT(indexChanged(int) ) );
}

MatrixMixerWnd::~MatrixMixerWnd()
{
    delete ui;
}


void MatrixMixerWnd::indexChanged(int index){
	QWidget* maybeThis = tab_->widget(index);
	if (maybeThis == this){
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			(*it)->initSnmp();
		}
	}else{
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
	}
}
