#include "TestNet.h"
#include "ui_TestNet.h"

#include <qdebug.h>
#include <sstream>
#include "TcpNet.h"
#include "boost/foreach.hpp"


TestQbox::TestQbox( const std::string &ip) :
    QWidget(0)
	,ui(new Ui::TestNet)
	,address_(ip)
{
    ui->setupUi(this);


	tableRequest_ = findChild<QTableWidget* >("tableRequest");
	tableResponse_ = findChild<QTableWidget* >("tableResponse");

	tableRequest_->setColumnCount(1);
	QStringList sl;
    sl.push_back( "msg");
    tableRequest_->setHorizontalHeaderLabels(sl );
	tableRequest_->setColumnWidth(0, 350);
	
	tableResponse_->setColumnCount(1);
    tableResponse_->setHorizontalHeaderLabels(sl );
	tableResponse_->setColumnWidth(0, 350);

	//connect( tableRequest_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));

	newRequestRow();

	QPushButton * btnSend = findChild<QPushButton* >("btnSend");
	connect( btnSend, SIGNAL(clicked(bool)), this, SLOT(sendClicked(bool)));
	QPushButton * btnClear = findChild<QPushButton* >("btnClear");
	connect( btnClear, SIGNAL(clicked(bool)), this, SLOT(clearClicked(bool)));

}

TestQbox::~TestQbox()
{
    delete ui;
}

void TestQbox::clearClicked(bool){
	tableResponse_->setRowCount(0);
	tableRequest_->setRowCount(0);
	newRequestRow();
}
void TestQbox::sendClicked(bool){
	Host* host = TcpNet::instance()->getHost( address_);

	QTableWidgetItem  *item1 = tableRequest_->item( 0, 0);
	QString msg = item1->text() + "\r\n";
	if ( host){
		host->addAsyncRequest( std::bind( &TestQbox::testDataCallback, this, std::placeholders::_1), std::move(msg.toStdString() ) );
	}

	tableResponse_->setRowCount(0);
}

bool TestQbox::testDataCallback( const std::string& msg){
	addResponseRow(msg);
	return true;
}

void TestQbox::newRequestRow(  ){
 //增加新空行
	QTableWidgetItem  *item1 = new QTableWidgetItem  ();

	item1 = new QTableWidgetItem  ();
	item1->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	item1->setFlags( Qt::ItemIsEnabled|Qt::ItemIsEditable );
	tableRequest_->setRowCount(tableRequest_->rowCount()+1);  
	tableRequest_->setItem ( tableRequest_->rowCount()-1, 0, item1 );
}

void TestQbox::addResponseRow( const std::string & msg ){
	QTableWidgetItem  *item1 = new QTableWidgetItem  ();
	item1 = new QTableWidgetItem  ();
	item1->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	item1->setFlags( Qt::ItemIsEnabled|Qt::ItemIsEditable );
	item1->setText(msg.c_str());

	tableResponse_->setRowCount(tableResponse_->rowCount()+1);  
	tableResponse_->setItem ( tableRequest_->rowCount()-1, 0, item1 );

}