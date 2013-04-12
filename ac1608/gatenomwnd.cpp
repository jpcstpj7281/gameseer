#include "gatenomwnd.h"
#include "ui_gatenomwnd.h"

#include "OidDial.h"
#include "OIDPushBtn.h"

GateNOMWnd::GateNOMWnd(QTabWidget *parent) :
    QWidget(parent),
    ui(new Ui::GateNOMWnd)
	,tab_(parent)
{
    ui->setupUi(this);

	qdl_ = findChildren<OIDDial*>( );
	for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
		OIDDial* qs = *it;

		QString name = qs->objectName();
		name.replace( "dial_", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		if (ql)qs->setLabel(ql);

		qs->setObjectName( "gate_"+qs->objectName());
		qs->setToolTip(qs->objectName());
	}

	qpbtnl_ = findChildren<OIDStatePushBtn*>( );
	if ( !qpbtnl_.isEmpty() ){
		QPixmap bypass2Btn("res/BypassBtn2.png");
		QPixmap bypass2Off("res/BypassBtn2_off.png");
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			OIDStatePushBtn* qs = *it;
			QString name = qs->objectName();
			if (name.contains("bypass") ){
				qs->setOnOffStateImage( 1, 0, bypass2Btn, bypass2Off);
			}
			qs->setObjectName( "gate_"+qs->objectName());
			qs->setToolTip(qs->objectName());
		}
	}

	connect ( parent, SIGNAL(currentChanged ( int )), this, SLOT(indexChanged(int) ) );
}

GateNOMWnd::~GateNOMWnd()
{
    delete ui;
}
void GateNOMWnd::indexChanged(int index){
	QWidget* maybeThis = tab_->widget(index);
	if (maybeThis == this){
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			(*it)->initSnmp();
		}
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			(*it)->initSnmp();
		}
	}else{
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
		for ( QList<OIDStatePushBtn *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
	}
}
