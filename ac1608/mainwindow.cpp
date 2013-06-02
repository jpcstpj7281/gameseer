#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "inputGainCtrlWnd.h"
#include "DevicesWnd.h"
#include "GateNOMWnd.h"
#include "HighPassWnd.h"
#include "MatrixMixerWnd.h"
#include "PresetWnd.h"
#include "homepage.h"
#include "peqwnd.h"
#include "nomwnd.h"
#include <QAction.h>
#include <QLineEdit.h>
#include <QTabWidget.h>
#include <CobraNetWnd.h>
#include "SnmpNetWnd.h"


#include "configmgr.h"


#include <functional>

#include <QTableView>


using namespace std::placeholders;

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	tab_ = findChild<QTabWidget*>( "tabWidget");


	PresetWnd *preset = new PresetWnd(tab_);
	PEQWnd *peq = new PEQWnd(tab_);
	modules_.push_back(new DevicesWnd(tab_));
	modules_.push_back(new HomePage(tab_));
	modules_.push_back(new InputGainCtrlWnd(tab_));
	modules_.push_back(new GateNOMWnd(tab_));
	modules_.push_back(new HighPassWnd(tab_));
	modules_.push_back(peq);
	modules_.push_back(new MatrixMixerWnd(tab_));
	modules_.push_back(new NOMWnd(tab_));
	modules_.push_back(preset);
	modules_.push_back(new CobraNetWnd(tab_));
	modules_.push_back(new SnmpNetWnd(tab_));

	tab_ = findChild<QTabWidget*>( "tabWidget");

	for (auto it = modules_.begin(); it != modules_.end(); ++it){
		tab_->addTab(*it, (*it)->windowTitle() );
	}
	preset->peq_ = peq;
	preset->dialList_ = tab_->findChildren<OIDDial*>();
	preset->btnList_ = tab_->findChildren<OIDStatePushBtn*>();
	preset->sliderList_ = tab_->findChildren<OIDSlider*>();
	
	for ( auto it = preset->dialList_.begin(); it != preset->dialList_.end(); ){
		if ( ! ConfigMgr::instance()->getOid((*it)->objectName()).isEmpty() && (*it)->objectName().left(4) != "peq_" ){
			//qDebug()<<(*it)->objectName();
			++it;
		}else{
			it = preset->dialList_.erase( it);
		}
	}
	for ( auto it = preset->btnList_.begin(); it != preset->btnList_.end();){
		if ( ! ConfigMgr::instance()->getOid((*it)->objectName()).isEmpty() ){
			++it;
		}else{
			it = preset->btnList_.erase( it);
		}
	}
	for ( auto it = preset->sliderList_.begin(); it != preset->sliderList_.end();){
		if ( ! ConfigMgr::instance()->getOid((*it)->objectName()).isEmpty() ){
			++it;
		}else{
			it = preset->sliderList_.erase( it);
		}
	}


    connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionCopyParam_clicked(QAction*)));
	connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionEdit_clicked(QAction*)));
}


MainWindow::~MainWindow()
{
    delete ui;
	for ( auto it = modules_.begin(); it != modules_.end(); ++it){
		delete *it;
	}

}

void MainWindow::closeEvent(QCloseEvent * ){
    QCoreApplication::exit();
}
void MainWindow::resizeEvent(QResizeEvent * ){

	tab_->setGeometry( 0, 0, this->width()+2, this->height()-40);

	QTableWidget* t = tab_->findChild<QTableWidget* >("tableDevices");
	if (t){
		t->setGeometry( 0, 0, this->width()+2, this->height()-40);
		t->setColumnWidth( 0, 150);
		t->setColumnWidth( 2, 100);
		t->setColumnWidth( 3, 100);
		t->setColumnWidth( 4, 100);
		t->setColumnWidth( 5, 100);
		t->setColumnWidth( 1, (int)(t->width() - 600) );
		
	}

	t = tab_->findChild<QTableWidget* >("tableOids");
	if (t){
		t->setColumnWidth( 0, 150);
		t->setColumnWidth( 2, 100);
		t->setColumnWidth( 3, 100);
		t->setColumnWidth( 4, 100);
		t->setColumnWidth( 5, 100);
		t->setColumnWidth( 6, 50);
		t->setColumnWidth( 1, this->width() - 650 );
		t->resize( this->width()-5, this->height()-80);
	}
}

void MainWindow::on_actionCopyParam_clicked(QAction* action){
	if (action->objectName() != "action_copy_param" ) return;
}
void MainWindow::on_actionEdit_clicked(QAction* action){
	if (action->objectName() != "action_mode_edit" ) return;
	if (action->isChecked()) {
		ConfigMgr::instance()->setOidEditable(true) ;
	}else{
		ConfigMgr::instance()->setOidEditable(false) ;
	}

	
}
