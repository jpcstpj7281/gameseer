#include "nomwnd.h"
#include "ui_nomwnd.h"

#include <qprogressbar>

#include <QList>
#include <QDebug>
#include "OIDSlider.h"
#include <qtablewidget.h>

NOMWnd::NOMWnd(QTabWidget *parent) :
    QWidget(parent),
    ui(new Ui::NOMWnd)
	,tab_(parent)
{
    ui->setupUi(this);

	qsl_ = findChildren<OIDSlider*>( );
	for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
		OIDSlider* qs = *it;
		QString name = qs->objectName();
		qs->setObjectName( "nom_"+qs->objectName());
		qs->setToolTip(qs->objectName());

		name.replace( "verticalSlider_", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		qs->setLabel(ql);
	}

	connect ( parent, SIGNAL(currentChanged ( int )), this, SLOT(indexChanged(int) ) );
}

NOMWnd::~NOMWnd()
{
    delete ui;
}

void NOMWnd::indexChanged(int index){
	QWidget* maybeThis = tab_->widget( index);
	if ( maybeThis->objectName() == "SnmpNetWnd") {
		return;
	}
	if (maybeThis == this ){
		for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
			(*it)->initSnmp();
		}
	}else{
		for ( QList<OIDSlider *>::Iterator it = qsl_.begin(); it != qsl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
	}
}