#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "DevicesWnd.h"
#include "TestQbox.h"
#include <QAction.h>
#include <QLineEdit.h>
#include <QTabWidget.h>

#include "configmgr.h"
#include <functional>
#include <QTableView>

#include <OsdImage.h>
#include <OsdProjMode.h>


using namespace std::placeholders;

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
	,devicesWnd_(new DevicesWnd)
	,osdImage_(new OsdImage)
	,osdProjMode_(new OsdProjMode)
	,testQbox_(new TestQbox)
	//,snmpNetWnd_(new SnmpNetWnd)

{
    ui->setupUi(this);

	_tab = findChild<QTabWidget*>( "tabWidget");

	
	_tab->addTab(devicesWnd_, "Devices" );
	_tab->addTab(osdImage_, "Image" );
	_tab->addTab(osdProjMode_, "Projection Mode" );
	_tab->addTab(testQbox_, "Test" );
	//_tab->addTab(snmpNetWnd_, "SnmpNet" );
	
	devicesWnd_->initAddresses();

	connect( _tab, SIGNAL(currentChanged (int)), this, SLOT(tabChanged(int)));

    connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionChangePsw_clicked(QAction*)));
    connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionCopyParam_clicked(QAction*)));
	connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionEdit_clicked(QAction*)));
}


void MainWindow::tabChanged (int index){
	QWidget* currWidget = _tab->widget( index);
	if ( currWidget == devicesWnd_){
	}
}
MainWindow::~MainWindow()
{
    delete ui;
	delete devicesWnd_;
	//delete snmpNetWnd_;
}

void MainWindow::on_inputGainControl_clicked()
{
}

void MainWindow::on_highPass_clicked(){
}


void MainWindow::on_gateNom_clicked()
{
}

void MainWindow::on_actionChangePsw_clicked( QAction* action){
    if (action->objectName() != "actionChangePsw" ) return;

}

void MainWindow::closeEvent(QCloseEvent * ){
    QCoreApplication::exit();
}
void MainWindow::resizeEvent(QResizeEvent * event){

	_tab->setGeometry( 0, 0, this->width()+2, this->height()-40);

	//QTableWidget* t = _tab->findChild<QTableWidget* >("tableDevices");
	//if (t){
	//t->setGeometry( 0, 0, this->width()+2, this->height()-40);
	//t->setColumnWidth( 0, 150);
	//t->setColumnWidth( 2, 100);
	//t->setColumnWidth( 3, 100);
	//t->setColumnWidth( 4, 100);
	//t->setColumnWidth( 5, 100);
	//t->setColumnWidth( 1, (int)(t->width() - 600) );
	//}

	//t = _tab->findChild<QTableWidget* >("tableOids");
	//if (t){
	//	t->setGeometry( 0, 0, this->width()+2, this->height()-40);
	//t->setColumnWidth( 0, 150);
	//t->setColumnWidth( 2, 100);
	//t->setColumnWidth( 3, 100);
	//t->setColumnWidth( 4, 100);
	//t->setColumnWidth( 5, 100);
	//t->setColumnWidth( 1, (int)(t->width() - 600) );
	//}


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
