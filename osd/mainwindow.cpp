#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "DevicesWnd.h"

#include <QTabWidget.h>

#include <QTableView>


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
	,devicesWnd_(new DevicesWnd)

{
    ui->setupUi(this);

	_tab = findChild<QTabWidget*>( "tabWidget");
	_tab->addTab(devicesWnd_, "Devices" );
	devicesWnd_->initAddresses();

	connect( _tab, SIGNAL(currentChanged (int)), this, SLOT(tabChanged(int)));
	this->resize(1024, 768);
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

void MainWindow::closeEvent(QCloseEvent * ){
    QCoreApplication::exit();
}
void MainWindow::resizeEvent(QResizeEvent * event){

	_tab->setGeometry( 0, 0, this->width()+2, this->height()-20);

	QTableWidget* t = _tab->findChild<QTableWidget* >("tableDevices");
	if (t){
		t->setGeometry( 0, 0, this->width()-230, this->height()-45);
		//t->setColumnWidth( 0, 150);
	}
	QPushButton* btn = _tab->findChild<QPushButton* >("connAll");
	btn->setGeometry(this->width()-195, 210, btn->width(), btn->height() );
	btn = _tab->findChild<QPushButton* >("disconnAll");
	btn->setGeometry(this->width()-195, 250, btn->width(), btn->height() );

	btn = _tab->findChild<QPushButton* >("incrCol");
	btn->setGeometry(this->width()-195, 70, btn->width(), btn->height() );
	btn = _tab->findChild<QPushButton* >("incrRow");
	btn->setGeometry(this->width()-195, 110, btn->width(), btn->height() );

	btn = _tab->findChild<QPushButton* >("decrCol");
	btn->setGeometry(this->width()-95, 70, btn->width(), btn->height() );
	btn = _tab->findChild<QPushButton* >("decrRow");
	btn->setGeometry(this->width()-95, 110, btn->width(), btn->height() );

}

