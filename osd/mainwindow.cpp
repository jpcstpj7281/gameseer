#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "DevicesWnd.h"
#include "WallWnd.h"
#include <QGraphicsView>
#include <QTabWidget.h>

#include <QTableView>
#include <boost/math/special_functions/round.hpp>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	_tab = findChild<QTabWidget*>( "tabWidget");
	modules_.push_back( new DevicesWnd(_tab));
	modules_.push_back( new WallWnd(_tab));
	for (auto it = modules_.begin(); it != modules_.end(); ++it){
		_tab->addTab(*it, (*it)->windowTitle() );
	}

	this->resize(1024, 768);
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
void MainWindow::resizeEvent(QResizeEvent * event){

	_tab->setGeometry( 0, 0, this->width()+2, this->height()+2);

	QTableWidget* t = _tab->findChild<QTableWidget* >("tableDevices");
	if (t){
		t->setGeometry( 0, 0, this->width()-230, this->height()-20);
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


	QGraphicsView* gv = _tab->findChild<QGraphicsView* >("wallView");
	if (gv){
		gv->setGeometry( -1, 0, this->width(), this->height()-145);
		gv->scene()->setSceneRect(0, 0,gv->width()-5, gv->height()-2);
		//qDebug()<<gv->scene()->sceneRect();
	}
	QComboBox* ring = _tab->findChild<QComboBox* >("cbRing");
	QComboBox* chn = _tab->findChild<QComboBox* >("cbChn");
	QComboBox* wnd = _tab->findChild<QComboBox* >("cbWnd");

	if (ring && chn&& wnd){
		ring->setGeometry(ring->x(), this->height()-130, ring->width(), ring->height() );
		chn->setGeometry(chn->x(), this->height()-130, chn->width(), chn->height() );
		wnd->setGeometry(wnd->x(), this->height()-130, wnd->width(), wnd->height() );

	}
}

