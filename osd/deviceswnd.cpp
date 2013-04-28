#include "deviceswnd.h"
#include "ui_deviceswnd.h"
#include <QTableWidgetItem>
#include "configmgr.h"
#include <functional>
#include <qdebug>
#include <Windows.h>
#include <boost/foreach.hpp>
#include "TestQbox.h"
#include "ui_mainwindow.h"
#include <OsdImage.h>
#include <OsdProjMode.h>

#undef min
using namespace std::placeholders;




OsdWnd::OsdWnd(ResourceID screenid)
:QMainWindow(0)
,screenid_(screenid)
,ui(new Ui::MainWindow)
,osdImage_(new OsdImage(this, screenid))
,osdProjMode_(new OsdProjMode(this, screenid))
{
    ui->setupUi(this);
	_tab = findChild<QTabWidget*>( "tabWidget");
	_tab->addTab(osdImage_, "Image" );
	_tab->addTab(osdProjMode_, "Projection Mode" );
	//connect( _tab, SIGNAL(currentChanged (int)), this, SLOT(tabChanged(int)));
	

}


void OsdWnd::tabChanged (int ){
	//QWidget* currWidget = _tab->widget( index);
}
OsdWnd::~OsdWnd(){
    delete ui;
}
void ScreenConnBtn::conn(){
	Screen* scrn = ScreenMgr::instance()->getScreen(screenid_);
	if ( scrn){
		if ( scrn->setAddress( address_->text().toStdString())){
			scrn->connect();
			setText("Connecting...");
			this->setEnabled(false);
			address_->setEnabled(false);
			osdBtn_->setEnabled(false);
			testBtn_->setEnabled(false);
			scrn->versionRequest( std::bind( &ScreenConnBtn::connectedCallback, this, _1, _2), QboxDataMap() );
		}
	}
}
void ScreenConnBtn::disconn(){
	Screen* scrn = ScreenMgr::instance()->getScreen(screenid_);
	scrn->disconnect();
	osdBtn_->setEnabled(false);
	testBtn_->setEnabled(false);
	if (testQbox_ && !testQbox_->isHidden() ) testQbox_->hide();
	if (osdBtn_ && !osdBtn_->isHidden() ) osdBtn_->hide();
	setText("Connect");
}
void ScreenConnBtn::clickit(){
	if ( address_->text().isEmpty() ){
		address_->setText("127.0.0.1") ;
	}
	if ( !address_->text().isEmpty() && text() == "Connect"){
		conn();
	}else if (text() == "Disconnect"){
		disconn();
	}
}
void ScreenConnBtn::clickOsd(){
	if (osdWnd_ == NULL){
		osdWnd_ = new OsdWnd(screenid_);
		osdWnd_->resize( 800, 600);
		osdWnd_->show();
	}else{
		if (osdWnd_->isHidden()){
			osdWnd_->show();
		}
	}
}
void ScreenConnBtn::clickTest(){
	if (testQbox_ == NULL){
		testQbox_ = new TestQbox(screenid_);
		testQbox_->resize( 800, 600);
		testQbox_->show();
	}else{
		if (testQbox_->isHidden()){
			testQbox_->show();
		}
	}
}

bool ScreenConnBtn::connectedCallback( uint32_t , QboxDataMap){
	setText("Disconnect");
	this->setEnabled(true);
	osdBtn_->setEnabled(true);
	testBtn_->setEnabled(true);
	return true;
}

ScreenConnBtn::ScreenConnBtn( ResourceID screenid, const std::string & ip ):
	QPushButton()
	,osdWnd_(0)
	,testQbox_(0)
	,screenid_(screenid)
	,row_( new QTableWidgetItem)
	,col_(new QTableWidgetItem)
	,address_(new QLineEdit)
	,osdBtn_(new QPushButton)
	,testBtn_(new QPushButton)
{
	this->setText( "Connect");

	row_->setText( QString::number( GetRow(screenid)) );
	row_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	row_->setFlags( Qt::ItemIsEnabled );

	col_->setText(QString::number( GetCol(screenid)));
	col_->setFlags( Qt::ItemIsEnabled );
	col_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);

	osdBtn_->setEnabled(false);
	osdBtn_->setText( "OSD");
	connect( osdBtn_, SIGNAL(clicked()), this, SLOT(clickOsd()) );

	testBtn_->setEnabled(false);
	testBtn_->setText( "Test");
	connect( testBtn_, SIGNAL(clicked()), this, SLOT(clickTest()) );

	QRegExp ipRx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?)");
	QRegExpValidator *pIpValidator = new QRegExpValidator(ipRx);
	address_->setValidator(pIpValidator);
	address_->setAlignment( Qt::AlignVCenter| Qt::AlignHCenter);
	address_->setText( QString::fromStdString( ip) );

	connect( this, SIGNAL(clicked()), this, SLOT(clickit()) );
	
	
	
	
}

ScreenConnBtn::~ScreenConnBtn(){
	if (osdWnd_) delete osdWnd_;
	if (testQbox_) delete testQbox_;
}

DevicesWnd::DevicesWnd(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::DevicesWnd)
{
    ui->setupUi(this);

    tableDevices_ = findChild<QTableWidget* >("tableDevices");
    tableDevices_->setColumnCount( 6);

    QStringList sl;
	sl.push_back( "Row");
	sl.push_back( "Col");
	sl.push_back( "IP");
    sl.push_back( "OSD");
    sl.push_back( "Connection");
	sl.push_back( "Test");
    tableDevices_->setHorizontalHeaderLabels(sl );
	tableDevices_->setColumnWidth( 0, 35);
	tableDevices_->setColumnWidth( 1, 35);

    connect( tableDevices_, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(itemClicked(QTableWidgetItem *)));
    connect( tableDevices_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));

    startTimer(1000);

	QPushButton * incrCol = findChild<QPushButton* >("incrCol");
	connect( incrCol, SIGNAL( clicked()), this, SLOT(incrCol()) );
	QPushButton * incrRow = findChild<QPushButton* >("incrRow");
	connect( incrRow, SIGNAL( clicked()), this, SLOT(incrRow()) );
	QPushButton * decrCol = findChild<QPushButton* >("decrCol");
	connect( decrCol, SIGNAL( clicked()), this, SLOT(decrCol()) );
	QPushButton * decrRow = findChild<QPushButton* >("decrRow");
	connect( decrRow, SIGNAL( clicked()), this, SLOT(decrRow()) );

	QPushButton * connAll = findChild<QPushButton* >("connAll");
	connect( connAll, SIGNAL( clicked()), this, SLOT(connAll()) );
	QPushButton * disconnAll = findChild<QPushButton* >("disconnAll");
	connect( disconnAll, SIGNAL( clicked()), this, SLOT(disconnAll()) );

	initAddresses();
}


DevicesWnd::~DevicesWnd()
{
    delete ui;
}

void DevicesWnd::incrCol(){
	auto ss = ScreenMgr::instance()->addScreenCol();
	BOOST_FOREACH( uint32_t srn, ss){
		newAddress( srn, std::string());
	}
}
void DevicesWnd::incrRow(){
	auto ss = ScreenMgr::instance()->addScreenRow();
	BOOST_FOREACH( uint32_t srn, ss){
		newAddress( srn, std::string());
	}
}

void DevicesWnd::decrCol(){
	auto ss = ScreenMgr::instance()->removeScreenCol();
	BOOST_FOREACH( uint32_t srn, ss){
		deleteAddress( srn);
	}
}
void DevicesWnd::decrRow(){
	auto ss = ScreenMgr::instance()->removeScreenRow();
	BOOST_FOREACH( uint32_t srn, ss){
		deleteAddress( srn);
	}
}

void DevicesWnd::disconnAll(){
	for ( uint32_t i = 0; i < tableDevices_->rowCount(); ++i){
		ScreenConnBtn* t = (ScreenConnBtn*)tableDevices_->cellWidget( i, 4);
		if ( t->text() == "Disconnect"){
			t->disconn();
		}
	}
}
void DevicesWnd::connAll(){
	for ( uint32_t i = 0; i < tableDevices_->rowCount(); ++i){
		ScreenConnBtn* t = (ScreenConnBtn*)tableDevices_->cellWidget( i, 4);
		if ( t->text() == "Connect"){
			t->conn();
		}
	}
}

//load addresses from configuration
void DevicesWnd::initAddresses(){
    //if ( addresses_.size() > 0) return;
    //QDomElement address = ConfigMgr::instance()->getAddressElem().firstChildElement();
    //while (address != QDomElement() ){
    //    QString ip = address.attribute( "ip");
    //    if ( addresses_.find( ip) == addresses_.end() ){
    //        QboxAddress * aa = new QboxAddress(ip );
    //        newAddress(aa);
    //    }
    //    address = address.nextSiblingElement();
    //}
}

void DevicesWnd::newAddress( ResourceID screenid, const std::string &ip){

	ScreenConnBtn * connBtn = new ScreenConnBtn( screenid , ip );
	tableDevices_->setRowCount(tableDevices_->rowCount()+1);  
	tableDevices_->setItem ( tableDevices_->rowCount()-1, 0, connBtn->row_ );
	tableDevices_->setItem ( tableDevices_->rowCount()-1, 1, connBtn->col_ );
	tableDevices_->setCellWidget(tableDevices_->rowCount()-1, 2, connBtn->address_);
	tableDevices_->setCellWidget ( tableDevices_->rowCount()-1, 3, connBtn->osdBtn_ );
	tableDevices_->setCellWidget ( tableDevices_->rowCount()-1, 4, connBtn );
	tableDevices_->setCellWidget ( tableDevices_->rowCount()-1, 5, connBtn->testBtn_ );
	
}
void DevicesWnd::deleteAddress( ResourceID screenid){
	uint32_t row = GetRow(screenid );
	uint32_t col = GetCol(screenid );

	for ( size_t i = 0; i < tableDevices_->rowCount() ; ++i){
		QTableWidgetItem * rowitem = tableDevices_->item( i, 0);
		QTableWidgetItem * colitem = tableDevices_->item( i, 1);
		if (rowitem->text().toUInt() ==row  && colitem->text().toUInt() == col){
			tableDevices_->removeRow( i);
			break;
		}
	}
}

void DevicesWnd::timerEvent ( QTimerEvent * event ){

}




void DevicesWnd::connectImpl( ){

}

void DevicesWnd::itemClicked(QTableWidgetItem * item)
{
    if (item->column() == 4 ){
        if(item->text() == "Connect" ){

        }
		if(item->text() == "Disconnect" ){

        }
    }
}

void DevicesWnd::cellChanged(int row,int col){
}

