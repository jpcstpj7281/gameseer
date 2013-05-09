#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug.h>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QCloseEvent>
#include <QSpinBox>
#include <QLabel>
#include <QComboBox>

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
	,sp_(ios_)
{
    ui->setupUi(this);
	
	QWidget * wdgt = findChild<QWidget*>( "centralWidget");
	QComboBox* br = findChild<QComboBox*>( "cbBaudRate");
	QComboBox* cs = findChild<QComboBox*>( "cbCharSize");
	QComboBox* port = findChild<QComboBox*>( "cbPort");
	QComboBox* sb = findChild<QComboBox*>( "cbStopBits");
	QPushButton* start = findChild<QPushButton*>( "btnStart");
	QPushButton* load = findChild<QPushButton*>( "btnLoad");
	connect( start, SIGNAL(clicked()), this, SLOT(clickStart()) );
	connect( load, SIGNAL(clicked()), this, SLOT(clickLoad()) );
	path_ = "path://";
	startTimer(10);
}

void MainWindow::clickLoad(){
	path_ = QFileDialog::getOpenFileName(this, "load file...");
	QLabel* path = findChild<QLabel*>( "lPath");
	path->setText( path_);

}
void MainWindow::timerEvent ( QTimerEvent * event ){
	ios_.run();
}
void MainWindow::handleRead(asio::error_code ec, std::size_t bytes_transferred)
{
     //cout.write(buf, bytes_transferred);
	if ( !ec ){
		buf_.size();
		buf_.data();
		buf_.consume(buf_.size());
	}
}
void MainWindow::clickStart(){
	if ( path_ == "path://") {
		QMessageBox::warning(this, "no path!", "please load a valid file path");
		return;
	}

	QComboBox* br = findChild<QComboBox*>( "cbBaudRate");
	QComboBox* cs = findChild<QComboBox*>( "cbCharSize");
	QComboBox* port = findChild<QComboBox*>( "cbPort");
	QComboBox* sb = findChild<QComboBox*>( "cbStopBits");
	QLabel* result = findChild<QLabel*>( "lResult");

	try{
		sp_.open(port->currentText().toStdString());
		sp_.set_option(asio::serial_port::baud_rate(br->currentText().toInt()));
		sp_.set_option(asio::serial_port::flow_control(asio::serial_port::flow_control::none));
		sp_.set_option(asio::serial_port::parity(asio::serial_port::parity::none));
		sp_.set_option(asio::serial_port::stop_bits((asio::serial_port::stop_bits::type)sb->currentIndex()));
		sp_.set_option(asio::serial_port::character_size(cs->currentText().toInt()));
	}catch( std::exception & e){
		result->setText(e.what());
		return;
	}

	asio::async_read_until(sp_, buf_, std::string("\r\n"), std::bind(&MainWindow::handleRead, this, std::placeholders::_1, std::placeholders::_2));

}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent * event){
	//QWidget * wdgt = findChild<QWidget*>( "tableDevices");
	//if ( wdgt){
	//	//wdgt->resize(this->width()-20, this->height()-80);
	//	wdgt->setGeometry( wdgt->x(), wdgt->y(), this->width()-20, this->height()-80);
	//}

}

