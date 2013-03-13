#include "deviceswnd.h"
#include "ui_deviceswnd.h"

#include <QTableWidgetItem>

#include "snmpnet.h"
#include "configmgr.h"

#include <functional>
#include <qdebug>
#include <QTime>
#include <QDateTime>
 

using namespace std::placeholders;


void Ac1608Address::editingFinished (){
	qDebug()<<"Ac1608Address::editingFinished";
}

DevicesWnd::DevicesWnd(QWidget *parent) :
    QWidget(parent)
	,currConnAddress_(0)
    ,ui(new Ui::DevicesWnd)
{
    ui->setupUi(this);

	//model_   = new QStandardItemModel(0, 4, this); 

	tableDevices_ = findChild<QTableWidget* >("tableDevices");
	tableDevices_->setColumnCount( 6);



	//tableDevices_->setModel(model_);
	QStringList sl;
	sl.push_back( "IP");
	sl.push_back( "Device Location");
	sl.push_back( "Running Time");
	sl.push_back( "Status");
	sl.push_back( "Connection");
	sl.push_back( "Operation");
	tableDevices_->setHorizontalHeaderLabels(sl );

	//newAddress();

	connect( tableDevices_, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(itemClicked(QTableWidgetItem *)));


	connect( tableDevices_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));
	connect( tableDevices_, SIGNAL(cellActivated(int,int)), this, SLOT(cellActivated(int,int)));
	connect( tableDevices_, SIGNAL(cellEntered(int,int)), this, SLOT(cellEntered(int,int)));

	startTimer(1000);
}


DevicesWnd::~DevicesWnd()
{
    delete ui;
}

SnmpCallback::RequestStatus dispatchFunc1(int status, snmp_session *sp, snmp_pdu *pdu, SnmpObj* so){
	const int len = 1024;
	char buf[len];
	memset( buf, 0, 1024);
	snprint_variable( buf, len, pdu->variables->name, pdu->variables->name_length, pdu->variables);
	qDebug()<<buf;
	return SnmpCallback::RequestAgain;
}

void DevicesWnd::refresh(){
	SnmpNet::instance()->addAsyncGet( "1.3.6.1.2.1.1.3.0",  "192.168.1.100" ,  "public" ,  std::bind<SnmpCallbackFunc >( dispatchFunc1, _1, _2, _3, _4 ));
}

void DevicesWnd::initAddresses(){
	if ( addresses_.size() > 0) return;
	QDomElement address = ConfigMgr::instance()->getAddressElem().firstChildElement();
	while (address != QDomElement() ){
		QString ip = address.attribute( "ip");
		if ( addresses_.find( ip) == addresses_.end() ){
			QString loc = address.attribute( "location");
			Ac1608Address * aa = new Ac1608Address(ip, loc );
			newAddress(aa);
		}
		address = address.nextSiblingElement();
	}
}

// aa == NULL时, 查看最后一行是否合法,合法就增加新一行
// aa != NULL时, 把最后一行填充,再新建新一行
void DevicesWnd::newAddress( Ac1608Address * aa ){

	//locker_.lock();

	Ac1608Address * lastSecondLine ;

	if (tableDevices_->rowCount() == 0 || tableDevices_->rowCount()== addresses_.size() ){ //增加新空行
		lastLineEdit_ = new QLineEdit();
		//le->setInputMask( "000.000.000.000");
		QRegExp ipRx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?)");
		QRegExpValidator *pIpValidator = new QRegExpValidator(ipRx);
		lastLineEdit_->setValidator(pIpValidator);
		lastLineEdit_->setAlignment( Qt::AlignVCenter| Qt::AlignHCenter);
		connect( lastLineEdit_, SIGNAL(editingFinished ()), this, SLOT(editingFinished ()));

		QTableWidgetItem  *item1 = new QTableWidgetItem  ();
		
		item1 = new QTableWidgetItem  ();
		item1->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
		item1->setFlags( Qt::ItemIsEnabled|Qt::ItemIsEditable );

		QTableWidgetItem  *item2 = new QTableWidgetItem  ();
		item2->setFlags( Qt::ItemIsEnabled );
		item2->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);

		QTableWidgetItem  *item3 = new QTableWidgetItem  ();
		item3->setFlags( Qt::ItemIsEnabled );
		item3->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
		//item3->setBackground(QBrush(QColor(Qt::gray))); 

		QTableWidgetItem  *item4 = new QTableWidgetItem  ();
		item4->setFlags( Qt::ItemIsEnabled );
		item4->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
		//item4->setBackground(QBrush(QColor(Qt::gray))); 

		QTableWidgetItem  *item5 = new QTableWidgetItem  ();
		item5->setFlags( Qt::ItemIsEnabled );
		item5->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);

		tableDevices_->setRowCount(tableDevices_->rowCount()+1);  
		tableDevices_->setCellWidget(tableDevices_->rowCount()-1, 0, lastLineEdit_);
		tableDevices_->setItem ( tableDevices_->rowCount()-1, 1, item1 );
		tableDevices_->setItem ( tableDevices_->rowCount()-1, 2, item2 );
		tableDevices_->setItem ( tableDevices_->rowCount()-1, 3, item3 );
		tableDevices_->setItem ( tableDevices_->rowCount()-1, 4, item4 );
		tableDevices_->setItem ( tableDevices_->rowCount()-1, 5, item5 );

		if ( aa == NULL) return;
	}

	if (aa != NULL){
		disconnect( lastLineEdit_, SIGNAL(editingFinished ()), this, SLOT(editingFinished ()));

		lastLineEdit_->setText( aa->ip);
		aa->row = tableDevices_->rowCount()-1;

		QTableWidgetItem  *item1 = tableDevices_->item( tableDevices_->rowCount()-1, 1);
		
		//QTableWidgetItem  *item2 = tableDevices_->item( tableDevices_->rowCount()-1, 2);
		QTableWidgetItem  *item3 = tableDevices_->item( tableDevices_->rowCount()-1, 3);
		QTableWidgetItem  *item4 = tableDevices_->item( tableDevices_->rowCount()-1, 4);
		QTableWidgetItem  * item5 = tableDevices_->item( tableDevices_->rowCount()-1,5);
		item1 ->setToolTip(aa->location);
		item1->setText(aa->location);
		item3->setText("Checking...");
		//item4->setText( "Connect");
		//item4->setBackground(QBrush(QColor(Qt::lightGray))); 
		//item5->setBackground(QBrush(QColor(Qt::lightGray))); 

		addresses_.insert( std::make_pair ( aa->ip,  aa) );
		aa->startCheckTime = GetTickCount();
		SnmpNet::instance()->listenAddress((char*) aa->ip.toStdString().c_str() , std::bind<SnmpCallbackFunc >( &DevicesWnd::checkAddressCallback,this, _1, _2, _3, _4));
	}
	//locker_.unlock();
	newAddress();
}


void DevicesWnd::editingFinished (){
	QString ip = lastLineEdit_->text();
	AddressMap::iterator found = addresses_.find( ip);
	if (found == addresses_.end()){
		newAddress(new Ac1608Address(ip, tableDevices_->item( tableDevices_->rowCount()-1, 1)->text() ));

	}
}
Ac1608Address* getAddressByRow( DevicesWnd::AddressMap & addresses , int row){
	for ( DevicesWnd::AddressMap::iterator it = addresses.begin(); it != addresses.end(); ++it){
		Ac1608Address * aa = it->second;
		if (aa->row == row) return aa;
	}
}

SnmpCallback::RequestStatus DevicesWnd::checkAddressCallback(int status, snmp_session *sp, snmp_pdu *pdu, SnmpObj* so){

	if (pdu->variables->type == ASN_TIMETICKS){
		int             centisecs, seconds, minutes, hours, days;
		u_long timeticks= 0;
		size_t len = sizeof(timeticks);
		timeticks = *(u_long *) (pdu->variables->val.integer);
		centisecs = timeticks % 100;
		timeticks /= 100;
		days = timeticks / (60 * 60 * 24);
		timeticks %= (60 * 60 * 24);

		hours = timeticks / (60 * 60);
		timeticks %= (60 * 60);

		minutes = timeticks / 60;
		seconds = timeticks % 60;

		AddressMap::iterator found = addresses_.find( so->ip.c_str());
		if ( found != addresses_.end() ) {
			Ac1608Address * aa = found->second;

			snprintf(aa->deviceRunTime, 32, "%d:%d:%02d:%02d",days, hours, minutes, seconds);

			aa->snmpResponseTime = GetTickCount();
		}
	}
	//const int len = 1024;
	//char buf[len];
	//memset( buf, 0, 1024);
	//snprint_variable( buf, len, pdu->variables->name, pdu->variables->name_length, pdu->variables);
	//qDebug()<<buf;
	//qDebug()<<so->ip.c_str();
	return SnmpCallback::RequestAgain;
}
void DevicesWnd::timerEvent ( QTimerEvent * event ){
	size_t t = GetTickCount();
	for (AddressMap::iterator it = addresses_.begin(); it != addresses_.end(); ++it){
		Ac1608Address * aa = it->second;
		size_t elapsedCheckTime = t - aa->startCheckTime;
		if ( aa->snmpResponseTime == 0 &&  elapsedCheckTime < 2000 ) continue;

		size_t elapsed = t - aa->snmpResponseTime;
		if (elapsed > 2000 && elapsedCheckTime >=2000){

			QTableWidgetItem  * item2 = tableDevices_->item( aa->row, 2);
			item2->setText( "");

			QTableWidgetItem  * item3 = tableDevices_->item( aa->row, 3);
			item3->setBackground(QBrush(QColor(Qt::red))); 
			item3->setText("Offline");

			QTableWidgetItem  * item4 = tableDevices_->item( aa->row, 4);
			item4->setText( "");
			item4->setBackground(QBrush(QColor(Qt::white))); 
			QTableWidgetItem  * item5 = tableDevices_->item( aa->row, 5);
			item5->setBackground(QBrush(QColor(Qt::white))); 

		}else{
			QTableWidgetItem  * item2 = tableDevices_->item( aa->row, 2);
			item2->setText( aa->deviceRunTime);

			if ( aa != currConnAddress_){
				QTableWidgetItem  * item3 = tableDevices_->item( aa->row, 3);
				item3->setBackground(QBrush(QColor(Qt::green))); 
				item3->setText("Online");
				QTableWidgetItem  * item4 = tableDevices_->item( aa->row, 4);
				item4->setText( "Connect");
				item4->setBackground(QBrush(QColor(Qt::lightGray))); 
				QTableWidgetItem  * item5 = tableDevices_->item( aa->row, 5);
				item5->setBackground(QBrush(QColor(Qt::lightGray))); 
			}
		}
	}
}

void DevicesWnd::connectImpl( Ac1608Address* aa){
	if (aa != currConnAddress_){
		SnmpNet::instance()->switchAsyncSnmpAddress( aa->ip.toStdString().c_str() );
		
		QTableWidgetItem  * item4;
		if ( currConnAddress_ != 0){
			item4 = tableDevices_->item( currConnAddress_->row, 4);
			item4->setText( "Connect");
			item4->setBackground(QBrush(QColor(Qt::lightGray))); 
		}

		item4 = tableDevices_->item( aa->row, 4);
		item4->setText( "");
		item4->setBackground(QBrush(QColor(Qt::green))); 
		currConnAddress_ = aa;
	}
}

void DevicesWnd::itemClicked(QTableWidgetItem * item)
{
	//qDebug()<<"DevicesWnd::itemClicked";
	if (item->column() == 4 ){
		if(item->text() == "Connect" ){
			qDebug()<<"connect "<<item->row();
			Ac1608Address* aa = getAddressByRow( addresses_ , item->row());
			connectImpl(aa);
		}
		//if( item->text() == DIS"Connect" ){
		//	qDebug()<<"disconnect "<<item->row();
		//	Ac1608Address* aa = getAddressByRow( addresses_ , item->row());
		//}
	}
}

void DevicesWnd::cellChanged(int row,int col){
	//qDebug()<<"DevicesWnd::cellChanged";
	//if (col == 0  ){
	//	if ( row == tableDevices_->rowCount()-1 ){ //新增一个IP
	//		//tableDevices_->setRowCount(tableDevices_->rowCount()+1); 
	//		//newAddress();
	//	}

	//}
}

void DevicesWnd::cellActivated(int row,int col){
		qDebug()<<"DevicesWnd::cellActivated";
}
void DevicesWnd::cellEntered(int row,int col){
		qDebug()<<"DevicesWnd::cellEntered";
}