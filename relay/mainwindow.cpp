#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include "DevicesWnd.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include <QCloseEvent>
#include <QSpinBox>
#include <QLabel>
#include <QPlainTextEdit>

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


	trayiconMenu = new QMenu(this);  
	QAction * showAction = new QAction(tr("&Show"), this);
	QObject::connect(showAction, SIGNAL(triggered()), this, SLOT(actionShow()));
	QAction * exitAction = new QAction(tr("&Exit"), this);
	QObject::connect(exitAction, SIGNAL(triggered()), this, SLOT(actionExit()));
	trayiconMenu->addAction(showAction);
	trayiconMenu->addAction(exitAction);
	
	
	trayicon = new QSystemTrayIcon(this);  
	QIcon icon("res/BypassBtn.png"); 
	trayicon->setIcon(icon);  
	trayicon->setContextMenu( trayiconMenu);
	trayicon->show();
	connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));  
}

void MainWindow::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason){
	actionShow();
}

void MainWindow::actionShow(){
	show();
}

void MainWindow::actionExit(){
	QCoreApplication::exit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent * event){


	bool isLogShow = false;

	QList<QCheckBox*> list = findChildren<QCheckBox*>();
	for ( auto it = list.begin(); it != list.end(); ++it){
		QCheckBox* b = *it;
		if ( b->objectName().contains("checkBox_")){
			b->setGeometry( b->x(), this->height()-65, b->width(), b->height());
		}else{
			b->setGeometry( b->x(), this->height()-35, b->width(), b->height());
			if ( b->objectName() == "showLog"){
				isLogShow = b->isChecked();
			}
		}
	}

	QWidget * wdgt = findChild<QWidget*>( "tableDevices");
	if ( wdgt){
		if ( isLogShow){
			wdgt->setGeometry( wdgt->x(), wdgt->y(), this->width()-20, this->height()-280);
		}else{
			wdgt->setGeometry( wdgt->x(), wdgt->y(), this->width()-20, this->height()-80);
		}
	}
	QPlainTextEdit * pte = findChild<QPlainTextEdit*>( "log");
	if ( pte){
		pte->setVisible(isLogShow);
		pte->setGeometry( pte->x(), this->height()-280, this->width()-20, 200);
	}

	QPushButton* btn = findChild<QPushButton* >("connAll");
	if ( btn){
		btn->setGeometry(btn->x(), this->height()-70, btn->width(), btn->height() );
		btn = findChild<QPushButton* >("disconnAll");
		btn->setGeometry(btn->x(), this->height()-40, btn->width(), btn->height() );
	}

	btn = findChild<QPushButton* >("onAll");
	btn->setGeometry(btn->x(), this->height()-40, btn->width(), btn->height() );
	btn = findChild<QPushButton* >("offAll");
	btn->setGeometry(btn->x(), this->height()-40, btn->width(), btn->height() );

	QSpinBox *sb = findChild<QSpinBox* >("spinBox");
	sb->setGeometry(sb->x(), this->height()-40, sb->width(), sb->height() );

	QLabel *ll = findChild<QLabel* >("label");
	ll->setGeometry(ll->x(), this->height()-38, ll->width(), ll->height() );
}

