#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "inputGainCtrlWnd.h"
#include "CopyParamWnd.h"
#include "DevicesWnd.h"
#include "GateNOMWnd.h"
#include "HighPassWnd.h"
#include "Level8CHWnd.h"
#include "MatrixMixerWnd.h"
#include "MetersWnd.h"
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
	,homepage_(new HomePage)
	,snmpNetWnd_(new SnmpNetWnd)
	,deviceswnd_(new DevicesWnd)
 //   ,inputGainCtrlWnd_(new InputGainCtrlWnd)
 //   ,gateNOMWnd_(new GateNOMWnd)
 //   ,highPassWnd_(new HighPassWnd)
	//,matrixMixerWnd_(new MatrixMixerWnd)
	//,peqWnd_(new PEQWnd)
	//,nomWnd_(new NOMWnd)
	//,presetWnd_(new PresetWnd)
	//,cobraNetWnd_(new CobraNetWnd)
{
    ui->setupUi(this);

	_tab = findChild<QTabWidget*>( "tabWidget");

	_tab->addTab(deviceswnd_, "Devices" );
	_tab->addTab(homepage_, "Homepage" );
	//_tab->addTab(inputGainCtrlWnd_, "Input" );
	//_tab->addTab(gateNOMWnd_, "Gate" );
	//_tab->addTab(highPassWnd_, "HighPass" );
	//_tab->addTab(peqWnd_, "PEQ" );
	//_tab->addTab(matrixMixerWnd_, "MatrixMixer" );
	//_tab->addTab(nomWnd_, "NOM" );
	//_tab->addTab(presetWnd_, "Preset" );
	//_tab->addTab(cobraNetWnd_, "CobraNet" );
	_tab->addTab(snmpNetWnd_, "SnmpNet" );
	
	deviceswnd_->initAddresses();

	connect( _tab, SIGNAL(currentChanged (int)), this, SLOT(tabChanged(int)));

    connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionCopyParam_clicked(QAction*)));
	connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionEdit_clicked(QAction*)));
}


void MainWindow::tabChanged (int index){
	QWidget* currWidget = _tab->widget( index);
	if ( currWidget == deviceswnd_){
	}
}
MainWindow::~MainWindow()
{
    delete ui;
    //delete inputGainCtrlWnd_;
    //delete gateNOMWnd_;
    //delete highPassWnd_;

	delete snmpNetWnd_;
	delete deviceswnd_;
	delete homepage_;
	//delete matrixMixerWnd_;
	//delete peqWnd_;
	//delete nomWnd_;
	//delete presetWnd_;
	//delete cobraNetWnd_;

}

void MainWindow::closeEvent(QCloseEvent * ){
    QCoreApplication::exit();
}
void MainWindow::resizeEvent(QResizeEvent * event){

	_tab->setGeometry( 0, 0, this->width()+2, this->height()-40);

	QTableWidget* t = _tab->findChild<QTableWidget* >("tableDevices");
	if (t){
		t->setGeometry( 0, 0, this->width()+2, this->height()-40);
		t->setColumnWidth( 0, 150);
		t->setColumnWidth( 2, 100);
		t->setColumnWidth( 3, 100);
		t->setColumnWidth( 4, 100);
		t->setColumnWidth( 5, 100);
		t->setColumnWidth( 1, (int)(t->width() - 600) );
		
	}

	t = _tab->findChild<QTableWidget* >("tableOids");
	if (t){
		t->setColumnWidth( 0, 150);
		t->setColumnWidth( 2, 100);
		t->setColumnWidth( 3, 100);
		t->setColumnWidth( 4, 100);
		t->setColumnWidth( 5, 100);
		t->setColumnWidth( 6, 50);
		t->setColumnWidth( 1, this->width() - 650 );
		t->resize( this->width()+2, this->height()-60);
	}
}

void MainWindow::on_actionCopyParam_clicked(QAction* action){
	if (action->objectName() != "action_copy_param" ) return;
    //sn.snmpmain();
	//SnmpNet::instance()->walk("1.3.6.1.4.1.2680.1.1.3");
	//SnmpNet::instance()->get(".1.3.6.1.4.1.2680.1.1.3.4.0");
	//SnmpNet::instance()->addAsyncGet(".1.3.6.1.4.1.2680.1.1.3.4.0", "192.168.1.100", "public", std::bind<SnmpCallbackFunc>( dispatchFunc, _1, _2, _3, _4));
	//SnmpNet::instance()->addAsyncGet(".1.3.6.1.4.1.2680.1.4.2.1.59.26.36.46.3.2.1.2.4", "192.168.1.100", "public",  std::bind<SnmpCallbackFunc>( dispatchFunc, _1, _2, _3, _4));

	//SnmpNet::instance()->addAsyncGet(".1.3.6.1.2.1.1.3.0", "192.168.1.100", "public",  std::bind<SnmpCallbackFunc >( dispatchFunc, _1, _2, _3, _4));
	//SnmpNet::instance()->listenAddress( "192.168.1.100", std::bind<SnmpCallbackFunc >( dispatchFunc, _1, _2, _3, _4));
	//ConfigMgr::instance();
}
void MainWindow::on_actionEdit_clicked(QAction* action){
	if (action->objectName() != "action_mode_edit" ) return;
	if (action->isChecked()) {
		ConfigMgr::instance()->setOidEditable(true) ;
	}else{
		ConfigMgr::instance()->setOidEditable(false) ;
	}

	
}
