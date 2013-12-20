#include "oidprogressbar.h"
#include "OIDInputDlg.h"
#include <QDebug>
#include "ConfigMgr.h"

using namespace std::tr1::placeholders;

OIDProgressBar::OIDProgressBar( Qt::Orientation orientation, QWidget *parent ):
QWidget( parent )
{
	ql_ = new QLabel( "0dB", this );
	ql_->setFont( QFont( "Helvetica", 8 ) );

	d_thermo = new QwtThermo( this );
	//d_thermo->setRange( 0.0, 100.0 );
	d_thermo->setFont( QFont( "Helvetica", 6 ) );
	d_thermo->setPipeWidth( 5 );
	d_thermo->setScaleMaxMajor( 20);
	d_thermo->setScaleMaxMinor( 4);
	d_thermo->setFillBrush( Qt::darkMagenta );

#if 0
	QwtLinearColorMap *colorMap =
		new QwtLinearColorMap( Qt::blue, Qt::red );

	colorMap->addColorStop( 0.2, Qt::yellow );
	colorMap->addColorStop( 0.3, Qt::cyan );
	colorMap->addColorStop( 0.4, Qt::green );
	colorMap->addColorStop( 0.5, Qt::magenta );
	colorMap->setMode( QwtLinearColorMap::FixedColors );
	d_thermo->setColorMap( colorMap );
#endif

	QVBoxLayout *layout = new QVBoxLayout( this );
	layout->setMargin( 0 );
	layout->setSpacing( 0 );

	if ( orientation == Qt::Horizontal )
	{
		ql_->setAlignment( Qt::AlignCenter );
		d_thermo->setOrientation( orientation, QwtThermo::BottomScale );
		layout->addWidget( ql_ );
		layout->addWidget( d_thermo );
	}
	else
	{
		ql_->setAlignment( Qt::AlignRight );
		d_thermo->setOrientation( orientation, QwtThermo::LeftScale );
		layout->addWidget( d_thermo, 10, Qt::AlignHCenter );
		layout->addWidget( ql_, 0 );
	}
}
void OIDProgressBar::initSnmp(){

	QString objname = objectName();

	QString oid = ConfigMgr::instance()->getOid(objname);
	if ( ! oid.isEmpty()){
		SnmpNet::instance()->addAsyncGet(
			objectName().toStdString(), 
			oid.toStdString(), 
			"public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1) , 1
			);
	}
}
void OIDProgressBar::shutdownSnmp(){
	//isRunning_ = false;
	QString objname = objectName();
	QString oid = ConfigMgr::instance()->getOid(objname);
	SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oid.toStdString() , std::string("public"));
}

void OIDProgressBar::snmpCallback( SnmpObj* so){
	setValue( so->rspVar.value<int>());
	if (ql_){
		ql_->setText( QString::number( value())+"dB");
	}
}
void OIDProgressBar::mouseReleaseEvent ( QMouseEvent *  ){
	if ( ConfigMgr::instance()->isOidEditable() ) {
		QString oldoid = ConfigMgr::instance()->getOid( objectName());
		QString oid = OIDInputDlg::getNewOid( objectName() );
		if (!oid.isEmpty() && oid != oldoid){
			if ( !oldoid.isEmpty()){
				SnmpNet::instance()->removeAsyncGet( objectName().toStdString(), oldoid.toStdString() , std::string("public"));
			}
			SnmpNet::instance()->addAsyncGet(
				objectName().toStdString(), oid.toStdString(),
				"public", std::bind<SnmpCallbackFunc>( &OIDProgressBar::snmpCallback, this, _1), 1 );
		}
	}
}

