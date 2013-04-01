#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "DevicesWnd.h"
#include <QAction.h>
#include <QLineEdit.h>
#include <QTabWidget.h>
#include "SnmpNetWnd.h"

#include "snmpnet.h"
#include "configmgr.h"
#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <functional>

#include <QTableView>


using namespace std::placeholders;

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
	,deviceswnd_(new DevicesWnd)
	,snmpNetWnd_(new SnmpNetWnd)

{
    ui->setupUi(this);

	_tab = findChild<QTabWidget*>( "tabWidget");

	
	_tab->addTab(deviceswnd_, "Devices" );
	_tab->addTab(snmpNetWnd_, "SnmpNet" );
	
	deviceswnd_->initAddresses();

	connect( _tab, SIGNAL(currentChanged (int)), this, SLOT(tabChanged(int)));

    connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionChangePsw_clicked(QAction*)));
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
	delete deviceswnd_;
	delete snmpNetWnd_;
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
		t->setGeometry( 0, 0, this->width()+2, this->height()-40);
	t->setColumnWidth( 0, 150);
	t->setColumnWidth( 2, 100);
	t->setColumnWidth( 3, 100);
	t->setColumnWidth( 4, 100);
	t->setColumnWidth( 5, 100);
	t->setColumnWidth( 1, (int)(t->width() - 600) );
	}


}

//SnmpCallback::RequestStatus dispatchFunc(int status, snmp_session *sp, snmp_pdu *pdu, SnmpObj* so){
//	//netsnmp_variable_list *vars;
//	//for (vars = pdu->variables; vars; vars = vars->next_variable){
//	//print_variable(pdu->variables->name, pdu->variables->name_length, vars);
//	const int len = 1024;
//	char buf[len];
//	memset( buf, 0, 1024);
//	snprint_variable( buf, len, pdu->variables->name, pdu->variables->name_length, pdu->variables);
//	qDebug()<<buf;
//
//	//}
//	return SnmpCallback::RequestAgain;
//}

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
