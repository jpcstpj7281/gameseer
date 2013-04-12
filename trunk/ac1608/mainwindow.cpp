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
	//,homepage_(new HomePage)
	//,snmpNetWnd_(new SnmpNetWnd)
	//,deviceswnd_(new DevicesWnd)

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

	modules_.push_back( new DevicesWnd(_tab));
	modules_.push_back(new HomePage(_tab));
	modules_.push_back(new InputGainCtrlWnd(_tab));
	modules_.push_back(new GateNOMWnd(_tab));
	modules_.push_back(new HighPassWnd(_tab));
	modules_.push_back(new PEQWnd(_tab));
	modules_.push_back(new MatrixMixerWnd(_tab));
	modules_.push_back(new NOMWnd(_tab));
	modules_.push_back(new PresetWnd(_tab));
	modules_.push_back(new CobraNetWnd(_tab));
	modules_.push_back(new SnmpNetWnd(_tab));

	_tab = findChild<QTabWidget*>( "tabWidget");

	for (auto it = modules_.begin(); it != modules_.end(); ++it){
		_tab->addTab(*it, (*it)->windowTitle() );
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
