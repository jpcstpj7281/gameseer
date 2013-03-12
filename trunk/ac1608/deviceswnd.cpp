#include "deviceswnd.h"
#include "ui_deviceswnd.h"

#include <QTableWidgetItem>

#include "snmpnet.h"
#include "configmgr.h"

#include <functional>
#include <qdebug>

using namespace std::placeholders;


void Ac1608Address::editingFinished (){
	qDebug()<<"Ac1608Address::editingFinished";
}

DevicesWnd::DevicesWnd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DevicesWnd)
{
    ui->setupUi(this);

	//model_   = new QStandardItemModel(0, 4, this); 

	tableDevices_ = findChild<QTableWidget* >("tableDevices");
	tableDevices_->setColumnCount( 4);



	//tableDevices_->setModel(model_);
	QStringList sl;
	sl.push_back( "IP");
	sl.push_back( "Device Location");
	sl.push_back( "Running Time");
	sl.push_back( "Status");
	tableDevices_->setHorizontalHeaderLabels(sl );

	//newAddress();

	connect( tableDevices_, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(itemChanged(QTableWidgetItem *)));
	connect( tableDevices_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));
	connect( tableDevices_, SIGNAL(cellActivated(int,int)), this, SLOT(cellActivated(int,int)));
	connect( tableDevices_, SIGNAL(cellEntered(int,int)), this, SLOT(cellEntered(int,int)));


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
		QString loc = address.attribute( "location");
		Ac1608Address * aa = new Ac1608Address(ip, loc );
		newAddress(aa);
		
		address = address.nextSiblingElement();
	}
}

// aa == NULL时, 查看最后一行是否合法,合法就增加新一行
// aa != NULL时, 把最后一行填充,再新建新一行
void DevicesWnd::newAddress( Ac1608Address * aa ){
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

		tableDevices_->setRowCount(tableDevices_->rowCount()+1);  
		tableDevices_->setCellWidget(tableDevices_->rowCount()-1, 0, lastLineEdit_);
		tableDevices_->setItem ( tableDevices_->rowCount()-1, 1, item1 );
		tableDevices_->setItem ( tableDevices_->rowCount()-1, 2, item2 );
		tableDevices_->setItem ( tableDevices_->rowCount()-1, 3, item3 );

		if ( aa == NULL) return;
	}

	if (aa != NULL){
		disconnect( lastLineEdit_, SIGNAL(editingFinished ()), this, SLOT(editingFinished ()));

		lastLineEdit_->setText( aa->ip);
		aa->row = tableDevices_->rowCount();

		QTableWidgetItem  *item1 = tableDevices_->item( tableDevices_->rowCount()-1, 1);
		
		//QTableWidgetItem  *item2 = tableDevices_->item( tableDevices_->rowCount()-1, 2);
		QTableWidgetItem  *item3 = tableDevices_->item( tableDevices_->rowCount()-1, 3);
		item1 ->setToolTip(aa->location);
		item1->setText(aa->location);
		item3->setText("Connecting...");

		addresses_.insert( std::make_pair ( aa->ip,  aa) );
	}
	newAddress();
}

void DevicesWnd::editingFinished (){
	QString ip = lastLineEdit_->text();
	AddressMap::iterator found = addresses_.find( ip);
	if (found == addresses_.end()){
		newAddress(new Ac1608Address(ip, tableDevices_->item( tableDevices_->rowCount()-1, 1)->text() ));
	}
}


bool checkValidIP( QString & ip){
	if ( ip.isEmpty() ) return false;

	return true;
}

	
void DevicesWnd::itemChanged(QTableWidgetItem * item)
{
	//qDebug()<<"DevicesWnd::itemChanged";
	//if (item->column() == 0 && checkValidIP( item->text() )  ){
	//	if ( item->row() == tableDevices_->rowCount()-1 ){ //新增一个IP
	//		//tableDevices_->setRowCount(tableDevices_->rowCount()+1); 
	//		//newAddress();
	//	}
	//}
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