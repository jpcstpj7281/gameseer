#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include "DevicesWnd.h"
#include <QVBoxLayout>
#include <QCheckBox>

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
		//wdgt->resize(this->width()-20, this->height()-80);
		wdgt->setGeometry( wdgt->x(), wdgt->y(), this->width()-20, this->height()-80);
	}

	//wdgt->setGeometry( 0, 0, this->width()-10, this->height()-20);

	QList<QCheckBox*> list = findChildren<QCheckBox*>();
	for ( auto it = list.begin(); it != list.end(); ++it){
		QCheckBox* b = *it;
		b->setGeometry( b->x(), this->height()-50, b->width(), b->height());
	}

	QPushButton* btn = findChild<QPushButton* >("connAll");
	if ( btn){
		btn->setGeometry(btn->x(), this->height()-70, btn->width(), btn->height() );
		btn = findChild<QPushButton* >("disconnAll");
		btn->setGeometry(btn->x(), this->height()-40, btn->width(), btn->height() );
	}

}

