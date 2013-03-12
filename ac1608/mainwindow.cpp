#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "inputGainCtrlWnd.h"
#include "ChangePasswordWnd.h"
#include "CopyParamWnd.h"
#include "DevicesWnd.h"
#include "GateNOMWnd.h"
#include "HighPassWnd.h"
#include "Level8CHWnd.h"
#include "MatrixMixerWnd.h"
#include "MetersWnd.h"
#include "PEQ4BandWnd.h"
#include "PEQ5BandWnd.h"
#include "PresetWnd.h"
#include <QAction.h>
#include <QLineEdit.h>
#include <QTabWidget.h>

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
    ,inputGainCtrlWnd_(new InputGainCtrlWnd)
    ,gateNOMWnd_(new GateNOMWnd)
    ,highPassWnd_(new HighPassWnd)
    ,peq4BandWnd_(new PEQ4BandWnd)
    ,changePasswordWnd_(new ChangePasswordWnd)
	,deviceswnd_(new DevicesWnd)
{
    ui->setupUi(this);

	_tab = findChild<QTabWidget*>( "tabWidget");

	_tab->addTab(deviceswnd_, "Devices" );

	connect( _tab, SIGNAL(currentChanged (int)), this, SLOT(tabChanged(int)));

    //connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionChangePsw_clicked(QAction*)));
    //connect( menuBar(), SIGNAL(triggered(QAction*)), this, SLOT(on_actionCopyParam_clicked(QAction*)));
}


void MainWindow::tabChanged (int index){
	QWidget* currWidget = _tab->widget( index);
	if ( currWidget == deviceswnd_){
		deviceswnd_->initAddresses();
	}
}
MainWindow::~MainWindow()
{
    delete ui;
    delete inputGainCtrlWnd_;
    delete gateNOMWnd_;
    delete highPassWnd_;
    delete peq4BandWnd_;
    delete changePasswordWnd_;
}

void MainWindow::on_inputGainControl_clicked()
{
    if ( inputGainCtrlWnd_->isVisible()){
        inputGainCtrlWnd_->hide();
    }else{
        inputGainCtrlWnd_->show();
    }
}

void MainWindow::on_highPass_clicked(){
    if ( highPassWnd_->isVisible()){
        highPassWnd_->hide();
    }else{
        highPassWnd_->show();
    }

}


void MainWindow::on_gateNom_clicked()
{

    if ( gateNOMWnd_->isVisible()){
        gateNOMWnd_->hide();
    }else{
        gateNOMWnd_->show();
    }
}

void MainWindow::on_peq4Band_clicked()
{
    if ( peq4BandWnd_->isVisible()){
        peq4BandWnd_->hide();
    }else{
        peq4BandWnd_->show();
    }

}
void MainWindow::on_actionChangePsw_clicked( QAction* action){
    if (action->objectName() != "actionChangePsw" ) return;


    if ( changePasswordWnd_->isVisible()){
        changePasswordWnd_->raise();
    }else{
        changePasswordWnd_->show();
    }
}

void MainWindow::closeEvent(QCloseEvent * ){
    QCoreApplication::exit();
}
void MainWindow::resizeEvent(QResizeEvent * event){

	_tab->setGeometry( 0, 0, this->width()+2, this->height()-40);

	QTableWidget* t = _tab->findChild<QTableWidget* >("tableDevices");
	t->setGeometry( 0, 0, this->width()+2, this->height()-40);
	t->setColumnWidth( 0, 150);
	t->setColumnWidth( 2, 100);
	t->setColumnWidth( 3, 100);
	t->setColumnWidth( 1, (int)(t->width() - 400) );


}

SnmpCallback::RequestStatus dispatchFunc(int status, snmp_session *sp, snmp_pdu *pdu, SnmpObj* so){
	//netsnmp_variable_list *vars;
	//for (vars = pdu->variables; vars; vars = vars->next_variable){
	//print_variable(pdu->variables->name, pdu->variables->name_length, vars);
	const int len = 1024;
	char buf[len];
	memset( buf, 0, 1024);
	snprint_variable( buf, len, pdu->variables->name, pdu->variables->name_length, pdu->variables);
	qDebug()<<buf;

	//}
	return SnmpCallback::RequestAgain;
}

void MainWindow::on_actionCopyParam_clicked(QAction* action){

    //sn.snmpmain();
	//SnmpNet::instance()->walk("1.3.6.1.4.1.2680.1.1.3");
	//SnmpNet::instance()->get(".1.3.6.1.4.1.2680.1.1.3.4.0");
	//SnmpNet::instance()->addAsyncGet(".1.3.6.1.4.1.2680.1.1.3.4.0", "192.168.1.100", "public", std::bind<SnmpCallbackFunc>( dispatchFunc, _1, _2, _3, _4));
	//SnmpNet::instance()->addAsyncGet(".1.3.6.1.4.1.2680.1.4.2.1.59.26.36.46.3.2.1.2.4", "192.168.1.100", "public",  std::bind<SnmpCallbackFunc>( dispatchFunc, _1, _2, _3, _4));
	SnmpNet::instance()->addAsyncGet(".1.3.6.1.2.1.1.3.0", "192.168.1.100", "public",  std::bind<SnmpCallbackFunc >( dispatchFunc, _1, _2, _3, _4));
	SnmpNet::instance()->run();
	//ConfigMgr::instance();
}
