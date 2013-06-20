#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include "DevicesWnd.h"
#include "WallWnd.h"
#include <QGraphicsView>
#include <QTabWidget.h>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include <boost/math/special_functions/round.hpp>

#include <wndwnd.h>
#include <chnwnd.h>
#include <ringwnd.h>
#include <taskwnd.h>
#include <modewnd.h>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	_tab = findChild<QTabWidget*>( "tabWidget");
	modules_.push_back( new DevicesWnd(_tab));
	modules_.push_back( new WallWnd(_tab));
	modules_.push_back( new WndWnd(_tab));
	modules_.push_back( new ChnWnd(_tab));
	modules_.push_back( new RingWnd(_tab));
	modules_.push_back( new ModeWnd(_tab));
	modules_.push_back( new TaskWnd(_tab));
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
void MainWindow::resizeEvent(QResizeEvent * ){

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

	t = _tab->findChild<QTableWidget* >("wndTable");
	if (t){
		t->setGeometry( 0, 0, this->width()-2, (this->height()-20)/2);
	}
	t = _tab->findChild<QTableWidget* >("wnodeTable");
	if (t){
		t->setGeometry( 0, (this->height()-20)/2, this->width()-2, (this->height()-20)/2);
	}
	t = _tab->findChild<QTableWidget* >("chnTable");
	if (t){
		t->setGeometry( 0, 0, this->width()-2, this->height()-20);
	}
	t = _tab->findChild<QTableWidget* >("ringTable");
	if (t){
		t->setGeometry( 0, 0, 400, this->height()-20);
	}
	t = _tab->findChild<QTableWidget* >("rnodeTable");
	if (t){
		t->setGeometry( 400, 0, this->width()-302, this->height()-20);
	}
	t = _tab->findChild<QTableWidget* >("modeTable");
	if (t){
		t->setGeometry( 0, 0, 400, this->height()-20);
	}
	t = _tab->findChild<QTableWidget* >("wndModeTable");
	if (t){
		t->setGeometry( 400, 0, this->width()-302, this->height()-20);
	}
	t = _tab->findChild<QTableWidget* >("taskTable");
	if (t){
		t->setGeometry( 0, 0, 400, this->height()-20);
	}
	t = _tab->findChild<QTableWidget* >("timerTable");
	if (t){
		t->setGeometry( 400, 0, this->width()-302, this->height()-20);
	}

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

	QPushButton* pb = _tab->findChild<QPushButton* >("pbActivateRing");
	if (pb){
		pb->setGeometry(pb->x(), this->height()-100, pb->width(), pb->height() );
	}
	pb = _tab->findChild<QPushButton* >("pbCloseWnd");
	if (pb){
		pb->setGeometry(pb->x(), this->height()-100, pb->width(), pb->height() );
	}

	QList<QLabel*> listl = _tab->findChildren<QLabel* >();
	QList<QLineEdit*> listle = _tab->findChildren<QLineEdit* >();

	for ( int i = 0 ; i < listl.size(); ++i){
		listl[i]->setGeometry(listl[i]->x(), this->height()-130, listl[i]->width(), listl[i]->height() );
	}
	for ( int i = 0 ; i < listle.size(); ++i){
		listle[i]->setGeometry(listle[i]->x(), this->height()-130, listle[i]->width(), listle[i]->height() );
	}
}

