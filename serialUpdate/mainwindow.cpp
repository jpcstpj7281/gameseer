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
	,ios_()
	//,sp_(ios_)
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
	sp_ = new asio::serial_port( ios_);
}

void MainWindow::clickLoad(){
	path_ = QFileDialog::getOpenFileName(this, "load file...");
	QLabel* path = findChild<QLabel*>( "lPath");
	path->setText( path_);

}
void MainWindow::timerEvent ( QTimerEvent * event ){
	ios_.run();
}
void MainWindow::handleWritePing(asio::error_code ec, std::size_t bytes_transferred){
	QPushButton* ping = findChild<QPushButton*>( "btnPing");
	if (!ec){
		buf_.prepare(1024);
		asio::async_read_until(*sp_, buf_, std::string("\r\n"), std::bind(&MainWindow::handleRead, this, std::placeholders::_1, std::placeholders::_2));
		
	}else{
		QMessageBox::warning(this, "failed!", "Ping指令写失败.");
		ping->setStyleSheet("* { background-color: red }");
	}
}
void MainWindow::handleRead(asio::error_code ec, std::size_t bytes_transferred)
{
     //cout.write(buf, bytes_transferred);
	if ( !ec ){
		buf_.commit(bytes_transferred);
		std::istream is(&buf_);
		std::string data;
		is >> data;
		size_t pos = 0;
		if ( data[pos++]== 0x55 && data[pos++] == 0xaa && data[pos++] == 0x55 && data[pos++] == 0xaa){
			size_t len = (data[pos] << 8) | data[pos+1];
			pos+=2;
			size_t cmd = (data[pos] << 8) | data[pos+1];
			pos+=2;
			if ( data[pos++] == 0x01 && data[pos++] ==0x01){
				pos+=16;//reserved
				switchCmd( cmd, data, len, pos);
			}
		}
	}
}
void MainWindow::switchCmd( size_t cmd, const std::string &data, size_t len, size_t pos){ //start at result position
	size_t result = data[pos];
	switch( cmd){
	case 0x03:
		if ( result == 0){
			QPushButton* ping = findChild<QPushButton*>( "btnPing");
			ping->setStyleSheet("* { background-color: lightGreen }");
		}
	case 0x05:
	case 0x07:
	case 0x09:
		if ( result != 0){
			QMessageBox::warning(this, "unknow result!", "返回指令: "+QString::number(cmd)+" ,结果返回:"+QString::number(result));
		}
		break;
	default:
		QMessageBox::warning(this, "unknow command!", "返回未知指令: "+QString::number(cmd));
	}
}

std::string header(){
	std::string data;
	data.resize(4);
	data[0]=0x55;data[1]=0xaa;data[2]=0x55;data[3]=0xaa;
}


std::string ping(){
	std::string data;
	data.resize(40);
	unsigned short len = 40;
	data[0] = len >>8;
	data[1] = len ;
	data[2] = 0xff;
	data[3] = 0x02;
	data[4] = 0x01;
	data[5] = 0x01;
	data[38] = '\r';
	data[39] = '\n';
	return header()+data;
}
std::string start(){
	std::string data;
	data.resize(40);
	unsigned short len = 40;
	data[0] = len >>8;
	data[1] = len ;
	data[2] = 0xff;
	data[3] = 0x04;
	data[4] = 0x01;
	data[5] = 0x01;
	data[38] = '\r';
	data[39] = '\n';
	return header()+data;
}
std::string data(unsigned short index, unsigned short total, const std::string pack){
	std::string data;
	data.resize(22);
	std::string reserved;
	reserved.resize(26);
	unsigned short len = 256+28;
	data[0] = len >>8;
	data[1] = len ;
	data[2] = 0xff;
	data[3] = 0x06;
	data[4] = 0x01;
	data[5] = 0x01;
	data[22] = index >>8;
	data[23] = index;
	data[24] = total >>8;
	data[25] = total;
	return header()+data+pack+"\r\n";
}
std::string end(const std::string &md5){
	std::string data;
	std::string reserved;
	reserved.resize(16);
	data.resize(6);
	unsigned short len = 56;
	data[0] = len >>8;
	data[1] = len ;
	data[2] = 0xff;
	data[3] = 0x08;
	data[4] = 0x01;
	data[5] = 0x01;
	return header()+data+reserved+md5+reserved+"\r\n";
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
		sp_->open(port->currentText().toStdString());
		sp_->set_option(asio::serial_port::baud_rate(br->currentText().toInt()));
		sp_->set_option(asio::serial_port::flow_control(asio::serial_port::flow_control::none));
		sp_->set_option(asio::serial_port::parity(asio::serial_port::parity::none));
		sp_->set_option(asio::serial_port::stop_bits((asio::serial_port::stop_bits::type)sb->currentIndex()));
		sp_->set_option(asio::serial_port::character_size(cs->currentText().toInt()));
	}catch( std::exception & e){
		result->setText(e.what());
		return;
	}
	
	asio::async_write(*sp_, ping(), std::bind(&MainWindow::handleWritePing, this, std::placeholders::_1, std::placeholders::_2));
	
}



MainWindow::~MainWindow()
{
	delete sp_;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent * event){
	//QWidget * wdgt = findChild<QWidget*>( "tableDevices");
	//if ( wdgt){
	//	//wdgt->resize(this->width()-20, this->height()-80);
	//	wdgt->setGeometry( wdgt->x(), wdgt->y(), this->width()-20, this->height()-80);
	//}

}

