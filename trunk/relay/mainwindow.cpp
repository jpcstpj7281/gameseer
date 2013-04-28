#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include "DevicesWnd.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	QWidget * wdgt = findChild<QWidget*>( "centralWidget");
	if (wdgt){
		QVBoxLayout* layout = new QVBoxLayout();
		layout->addWidget( new  DevicesWnd(wdgt));
		wdgt->setLayout(layout);
	}
	//modules_.push_back( new DevicesWnd(_tab));
	//for (auto it = modules_.begin(); it != modules_.end(); ++it){
	//	_tab->addTab(*it, (*it)->windowTitle() );
	//}

	//this->resize(1024, 768);
}



MainWindow::~MainWindow()
{
    delete ui;
	//for ( auto it = modules_.begin(); it != modules_.end(); ++it){
	//	delete *it;
	//}
}

void MainWindow::closeEvent(QCloseEvent * ){
    QCoreApplication::exit();
}
void MainWindow::resizeEvent(QResizeEvent * event){
	QWidget * wdgt = findChild<QWidget*>( "tableDevices");
	if ( wdgt){
		wdgt->resize(this->width()-20, this->height()-80);
	}

	//wdgt->setGeometry( 0, 0, this->width()-10, this->height()-20);

	//QTableWidget* t = _tab->findChild<QTableWidget* >("tableDevices");
	//if (t){
		//t->setGeometry( 0, 0, this->width()-130, this->height()-45);
		//t->setColumnWidth( 0, 150);
	//}
	//QPushButton* btn = _tab->findChild<QPushButton* >("connAll");
	//if ( btn){
	//	btn->setGeometry(this->width()-120, 210, btn->width(), btn->height() );
	//	btn = _tab->findChild<QPushButton* >("disconnAll");
	//	btn->setGeometry(this->width()-120, 250, btn->width(), btn->height() );

	//	btn = _tab->findChild<QPushButton* >("incrCol");
	//	btn->setGeometry(this->width()-120, 70, btn->width(), btn->height() );

	//	btn = _tab->findChild<QPushButton* >("decrCol");
	//	btn->setGeometry(this->width()-120, 110, btn->width(), btn->height() );
	//}

}

