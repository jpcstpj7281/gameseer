#include "presetwnd.h"
#include "ui_presetwnd.h"
#include <QPushButton>
#include <qfile.h>
#include <qdebug.h>
#include <QRadioButton>
#include <QFileDialog>


void checkIsFileExist( QPushButton* qpb){
	QFile file( qpb->objectName().replace("pbOpen", "Preset") );
	if ( file.exists()){
		qpb->setEnabled(true);
	}else{
		qpb->setEnabled(false);
	}
}

Preset* PresetWnd::usePreset( const QString & id){
	Preset * preset = presets_[id];
	if (preset == NULL){
		preset = new Preset();
		presets_[id] = preset;
	}
	return preset;
}
PresetWnd::PresetWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PresetWnd)
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
			Preset * p = usePreset(id);
			p->select_ = qrb;
			connect(qrb, SIGNAL(clicked()), p, SLOT(select()));
		}
	}
	qpbtnl_ = findChildren<QPushButton*>( );
	if ( !qpbtnl_.isEmpty() ){
		for ( QList<QPushButton *>::Iterator it = qpbtnl_.begin(); it != qpbtnl_.end(); ++it){
			QPushButton* qpb = *it;
			QString name = qpb->objectName();
			
			if (name.contains("pbSave") ){
				QString presetid = name.replace( "pbSave", "");
				Preset * p = usePreset(presetid);
				p->save_ = qpb;
				connect(qpb, SIGNAL(clicked()), p, SLOT(save()));
			}else if (name.contains("pbOpen")){
				QString presetid = name.replace( "pbOpen", "");
				Preset * p = usePreset(presetid);
				p->open_ = qpb;
				connect(qpb, SIGNAL(clicked()), p, SLOT(open()));
				checkIsFileExist(qpb);
			}else if(name.contains("pbUpload")){
				QString presetid = name.replace( "pbUpload", "");
				Preset * p = usePreset(presetid);
				p->upload_ = qpb;
				connect(qpb, SIGNAL(clicked()), p, SLOT(upload()));
			}else if (name.contains("pbDownload")) {
				QString presetid = name.replace( "pbDownload", "");
				Preset * p = usePreset(presetid);
				p->download_ = qpb;
				connect(qpb, SIGNAL(clicked()), p, SLOT(download()));
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
}

PresetWnd::~PresetWnd()
{
    delete ui;
}

void Preset::open(){
	
}
void Preset::save(){
	QFile file( save_->objectName().replace("pbSave", "Preset") );
    if ( !file.open( QIODevice::WriteOnly | QIODevice::Truncate ) )return ;

	file.write( "test");
	file.flush();
	open_->setEnabled(true);
}
void Preset::upload(){
	
}
void Preset::download(){
	
}
void Preset::select(){
	
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