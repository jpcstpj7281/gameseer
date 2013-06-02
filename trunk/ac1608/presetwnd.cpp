#include "presetwnd.h"
#include "ui_presetwnd.h"
#include <QPushButton>
#include <qfile.h>
#include <qdebug.h>
#include <QRadioButton>
#include <QFileDialog>
#include <ConfigMgr.h>


void checkIsFileExist( QPushButton* qpb){
	QFile file( qpb->objectName().replace("pbOpen", "Preset") );
	if ( file.exists()){
		qpb->setEnabled(true);
	}else{
		qpb->setEnabled(false);
	}
}


PresetWnd::PresetWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresetWnd)
	,currOperatingTime_(0)
	,currOperatingBtn_(0)
	,currOperatingVal_(0)
{
    ui->setupUi(this);
	currPresetId_ = "0";

	qrbtnl_ = findChildren<QRadioButton*>( );
	if ( !qrbtnl_.isEmpty() ){
		for ( QList<QRadioButton *>::Iterator it = qrbtnl_.begin(); it != qrbtnl_.end(); ++it){
			QRadioButton* qrb = *it;
			QString name = qrb->objectName();
			QString id = name.replace( "rb", "");
			if ( id == currPresetId_){
				qrb->setChecked( true);
			}
			//Preset * p = usePreset(id);
			//p->select_ = qrb;
			connect(qrb, SIGNAL(clicked()), this, SLOT(select()));
		}
	}

	qpbtnl_ = findChildren<QPushButton*>( );
	if ( !qpbtnl_.isEmpty() ){
		for ( QList<QPushButton *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			QPushButton* qpb = *it;
			QString name = qpb->objectName();
			
			if (name.contains("pbSave") ){
				connect(qpb, SIGNAL(clicked()), this, SLOT(save()));
			}else if (name.contains("pbOpen")){
				connect(qpb, SIGNAL(clicked()), this, SLOT(open()));
				checkIsFileExist(qpb);
			}else if(name.contains("pbUpload")){
				connect(qpb, SIGNAL(clicked()), this, SLOT(savedsp()));
				snmpBtn_.push_back(qpb);
			}else if (name.contains("pbDownload")) {
				connect(qpb, SIGNAL(clicked()), this, SLOT(loaddsp()));
				snmpBtn_.push_back(qpb);
			}else if (name.contains("pbDspClear")) {
				connect(qpb, SIGNAL(clicked()), this, SLOT(cleardsp()));
				snmpBtn_.push_back(qpb);
			}
		}
	}

	QPushButton * savebtn = findChild<QPushButton*>("pbSAs" );
	if (savebtn){
		connect(savebtn, SIGNAL(clicked()), this, SLOT(saveAs()));
	}
	QPushButton * openbtn = findChild<QPushButton*>("pbOFrom" );
	if (openbtn){
		connect(openbtn, SIGNAL(clicked()), this, SLOT(openFrom()));
	}
	QString oid = ConfigMgr::instance()->getOid("preset");
	if ( oid.isEmpty()){
		ConfigMgr::instance()->setOid("preset", ".1.3.6.1.4.1.2680.1.4.2.33.32.34.17.45.4.2.1.2.8");
	}
	startTimer(1000);
}

PresetWnd::~PresetWnd()
{
    delete ui;
}

void PresetWnd::setValue( QString &objectname, QString &val){
	for ( auto it = dialList_.begin(); it != dialList_.end(); ++it){
		if ((*it)->objectName() == objectname ){
			(*it)->setValue( val.toInt());
			return ;
		}
	}
	for ( auto it = btnList_.begin(); it != btnList_.end(); ++it){
		if ((*it)->objectName() == objectname ){
			(*it)->setVal( val.toInt());
			return ;
		}
	}
	for ( auto it = sliderList_.begin(); it != sliderList_.end(); ++it){
		if ((*it)->objectName() == objectname ){
			(*it)->setValue( val.toInt());
			return ;
		}
	}
	if ( objectname.left(4) == "peq_"){
		peq_->load( objectname, val);
	}
}

void PresetWnd::open(){
	QFile file( sender()->objectName().replace("pbOpen", "Preset") );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Truncate ) )return ;
	QString line;
	while( !file.atEnd()){
		line = file.readLine();
		QStringList list = line.trimmed().split("=");
		if ( list.size() == 2){
			setValue(list[0], list[1]);
		}
	}
}
void PresetWnd::save(){
	QFile file( sender()->objectName().replace("pbSave", "Preset") );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;
	QTextStream stream( &file);
	for ( auto it = dialList_.begin(); it != dialList_.end(); ++it){
		stream<<(*it)->objectName()<<"="<<(*it)->value()<<"\n";
	}
	for ( auto it = btnList_.begin(); it != btnList_.end(); ++it){
		stream<<(*it)->objectName()<<"="<<(*it)->getVal()<<"\n";
	}
	for ( auto it = sliderList_.begin(); it != sliderList_.end(); ++it){
		stream<<(*it)->objectName()<<"="<<(*it)->value()<<"\n";
	}
	peq_->save(stream);

	file.flush();
	findChild<QPushButton*>( sender()->objectName().replace("pbSave","pbOpen" ) )->setEnabled(true);
}
void PresetWnd::savedsp(){
	currOperatingBtn_ = (QPushButton*)sender();
	currOperatingTime_ = GetTickCount()+2000;

	currOperatingVal_ = currOperatingBtn_->objectName().replace("pbUpload", "").toInt()+10;
	
	QString oid = ConfigMgr::instance()->getOid("preset");
	SnmpNet::instance()->addAsyncSet( "presetSet", 
			oid.toStdString(), "private", 
			std::bind<SnmpCallbackFunc>( &PresetWnd::snmpCallback, this, std::placeholders::_1) , currOperatingVal_);
	for ( auto it = snmpBtn_.begin(); it != snmpBtn_.end(); ++it){
		(*it)->setEnabled(false);
	}
}
void PresetWnd::loaddsp(){

	currOperatingBtn_ = (QPushButton*)sender();
	currOperatingTime_ = GetTickCount()+2000;

	currOperatingVal_ = currOperatingBtn_->objectName().replace("pbDownload", "").toInt()+50;
	
	QString oid = ConfigMgr::instance()->getOid("preset");
	SnmpNet::instance()->addAsyncSet( "presetSet", 
			oid.toStdString(), "private", 
			std::bind<SnmpCallbackFunc>( &PresetWnd::snmpCallback, this, std::placeholders::_1) , currOperatingVal_);
	for ( auto it = snmpBtn_.begin(); it != snmpBtn_.end(); ++it){
		(*it)->setEnabled(false);
	}
}

void PresetWnd::cleardsp(){

	currOperatingBtn_ = (QPushButton*)sender();
	currOperatingTime_ = GetTickCount()+2000;

	currOperatingVal_ = 80;
	
	QString oid = ConfigMgr::instance()->getOid("preset");
	SnmpNet::instance()->addAsyncSet( "presetSet", 
			oid.toStdString(), "private", 
			std::bind<SnmpCallbackFunc>( &PresetWnd::snmpCallback, this, std::placeholders::_1) , currOperatingVal_);
	for ( auto it = snmpBtn_.begin(); it != snmpBtn_.end(); ++it){
		(*it)->setEnabled(false);
	}
}

void PresetWnd::select(){
	
}

void PresetWnd::saveAs(){
	
	QString name = QFileDialog::getSaveFileName( this, "Save as...");
	QFile file( name );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	file.write( "test");
	file.flush();
}
void PresetWnd::openFrom(){
	QFileDialog::getOpenFileName( this, "Open file...");
}

void PresetWnd::timerEvent ( QTimerEvent *  ){
	size_t now = GetTickCount();
	if ( currOperatingBtn_ && currOperatingTime_ && currOperatingTime_ <= now){
		currOperatingBtn_ =  NULL;

		QString oid = ConfigMgr::instance()->getOid("preset");
		SnmpNet::instance()->addAsyncGet( "presetGet", 
			oid.toStdString(), 
				"public", std::bind<SnmpCallbackFunc>( &PresetWnd::snmpCallback, this, std::placeholders::_1) 
				);
	}
	
	if ( currOperatingTime_ && (int)(now - currOperatingTime_) > 5000 ){
		QString oid = ConfigMgr::instance()->getOid("preset");
		SnmpNet::instance()->removeAsyncGet( "presetGet", 
			oid.toStdString() , 
			std::string("public"));
		for ( auto it = snmpBtn_.begin(); it != snmpBtn_.end(); ++it){
			(*it)->setEnabled(true);
		}
		currOperatingBtn_ =  NULL;
		currOperatingTime_ = 0;
		currOperatingVal_= 0;
	}
}

void PresetWnd::snmpCallback(  SnmpObj* so){
	if ( so->setVar.isNull() ){
		int val = so->rspVar.value<int>();
		if ( val > currOperatingVal_){
			QString oid = ConfigMgr::instance()->getOid("preset");
			SnmpNet::instance()->removeAsyncGet( "presetGet", 
				oid.toStdString() , 
				std::string("public"));
			for ( auto it = snmpBtn_.begin(); it != snmpBtn_.end(); ++it){
				(*it)->setEnabled(true);
			}
			currOperatingVal_= 0;
			currOperatingTime_ = 0;
		}
	}
}