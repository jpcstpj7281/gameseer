#include "deviceswnd.h"
#include "ui_deviceswnd.h"

#include <QTableWidgetItem>

#include "snmpnet.h"
#include "configmgr.h"

#include <functional>
#include <qdebug>
#include <QTime>
#include <PswInputDlg.h>
#undef min


using namespace std::placeholders;


Ac1608Address::Ac1608Address( DevicesWnd* parent, const QString & ip, const QString & loc):
	QPushButton()
	,snmpResponseTime(0)
	,startCheckTime(0)
	,t_(parent->tableDevices_)
	,ip_(0)
	,pswCount_(0)
	,wnd_(parent)
{
	memset(psw_, 0, 16);
	memset(inputPsw_, 0, 16);
	ip_ = new QLineEdit();
	ip_->setText(ip);
	loc_ = new QTableWidgetItem  ();
	loc_->setText(loc);
	runTime_ = new QTableWidgetItem  ();
	status_ = new QTableWidgetItem  ();
	//connect_ = new QTableWidgetItem  ();
	operation_ = new QTableWidgetItem  ();
	QRegExp ipRx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?)|");
	QRegExpValidator *pIpValidator = new QRegExpValidator(ipRx);
	ip_->setValidator(pIpValidator);
	ip_->setAlignment( Qt::AlignVCenter| Qt::AlignHCenter);
	loc_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	loc_->setFlags( Qt::ItemIsEnabled|Qt::ItemIsEditable );
	runTime_->setFlags( Qt::ItemIsEnabled );
	runTime_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	status_->setFlags( Qt::ItemIsEnabled );
	status_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	//connect_->setFlags( Qt::ItemIsEnabled );
	//this->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	operation_->setFlags( Qt::ItemIsEnabled );
	operation_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	connect( ip_, SIGNAL(editingFinished ()), this, SLOT(editingAddressFinished ()));
	connect( this, SIGNAL(clicked ()), this, SLOT(connectClicked ()));

	this->setEnabled(false);
	t_->setRowCount(t_->rowCount()+1);  
	t_->setCellWidget(t_->rowCount()-1, 0, this->ip_);
	t_->setItem ( t_->rowCount()-1, 1, this->loc_ );
	t_->setItem ( t_->rowCount()-1, 2, this->runTime_ );
	t_->setItem ( t_->rowCount()-1, 3, this->status_ );
	t_->setCellWidget ( loc_->row() , 4, this );
	t_->setItem ( t_->rowCount()-1, 5, this->operation_ );
	
}
Ac1608Address::~Ac1608Address(){
}

void Ac1608Address::connectClicked(){
	if(this->text() == "Connect" ){
		if ( wnd_->inputDlg_->getNewPsw( this)){
			wnd_->connectImpl(this);
		}
	}
	if(this->text() == "Change Psw" ){
		wnd_->inputDlg_->changePsw( this);
	}
}

void Ac1608Address::startCheckAddress(){
    status_->setText("Checking...");
	startCheckTime = GetTickCount();
	checkingIP_ = ip_->text();
	SnmpNet::instance()->listenAddress(ip_->text().toStdString(), std::bind<SnmpCallbackFunc >( &Ac1608Address::checkAddressCallback,this, _1));
}

bool Ac1608Address::isExisted( const QString& ip){
	for ( size_t i = 0; i < t_->rowCount(); ++i){
		Ac1608Address* aa = (Ac1608Address*) t_->cellWidget( i , 4);
		if ( aa  != this && aa->ip_->text() == ip){
			return true;
		}
	}
	return false;
}

void Ac1608Address::editingAddressFinished (){
	if (checkingIP_ == this->ip_->text()) return; //已经在读
	if (this->ip_->text().isEmpty() && this != wnd_->lastLineAddress_){ //要删除这行了
		if (  !checkingIP_.isEmpty()){
			ConfigMgr::instance()->removeIP(checkingIP_ );
			SnmpNet::instance()->removeListenAddress(this->checkingIP_.toStdString() );
		}
		t_->removeRow( loc_->row() );
	}else{
		if ( isExisted(ip_->text() )){
			ip_->setText( checkingIP_);
		}else{
			checkingRefreshed();
			if (!checkingIP_.isEmpty()){
				ConfigMgr::instance()->removeIP(checkingIP_ );
				SnmpNet::instance()->removeListenAddress(checkingIP_.toStdString() );
			}
			startCheckTime = GetTickCount();
			snmpResponseTime = 0;
			SnmpNet::instance()->listenAddress(this->ip_->text().toStdString(), std::bind<SnmpCallbackFunc >( &Ac1608Address::checkAddressCallback,this, _1));
			ConfigMgr::instance()->setIP(this->ip_->text(), this->loc_->text());
			checkingIP_ = ip_->text();

			if (  wnd_->lastLineAddress_ == this){
				wnd_->lastLineAddress_ = NULL;
				wnd_->newAddress();
			}
		}
	}
}



void Ac1608Address::checkAddressCallback( SnmpObj* so){
	timeticks = so->rspVar.value<int>();
	snmpResponseTime = GetTickCount();
	
	onlineRefreshed();
}

void Ac1608Address::checkingRefreshed(){//把这行更新为开始检查状态
	runTime_->setText("");
	status_->setBackground(QBrush(QColor(Qt::white))); 
	status_->setText("Checking...");
	this->setEnabled(false);
}


void Ac1608Address::onlineRefreshed(){
    runTime_->setText(timeticksToString(timeticks ) );
    if ( this != wnd_->currConnAddress_){
        status_->setBackground(QBrush(QColor(Qt::green))); 
        status_->setText("Online");
		this->setText( "Connect");
		this->setEnabled(true);
    }else{
		this->setText( "Change Psw");
		status_->setBackground(QBrush(QColor(Qt::blue))); 
	}
}

void Ac1608Address::offlineRefreshed(){
    runTime_->setText( "");
    status_->setBackground(QBrush(QColor(Qt::red))); 
    status_->setText("Offline");
    this->setText( "");
	this->setEnabled(false);
    operation_->setBackground(QBrush(QColor(Qt::white))); 
}

void Ac1608Address::timerEvent(size_t t){
	size_t elapsedCheckTime = t - startCheckTime;
	if ( snmpResponseTime > 0 ) {
		size_t elapsed = t - snmpResponseTime;
		if (elapsed > 5000 ){
			offlineRefreshed();
		}
	}else{
		if (  elapsedCheckTime > 5000 ){
			offlineRefreshed();
		}
	}
}

DevicesWnd::DevicesWnd(QWidget *parent) :
    QWidget(parent)
    ,currConnAddress_(0)
	,lastLineAddress_(0)
    ,ui(new Ui::DevicesWnd)
{
    ui->setupUi(this);
	inputDlg_ = new PswInputDlg;

    tableDevices_ = findChild<QTableWidget* >("tableDevices");
    tableDevices_->setColumnCount( 6);

    QStringList sl;
    sl.push_back( "IP");
    sl.push_back( "Device Location");
    sl.push_back( "Running Time");
    sl.push_back( "Status");
    sl.push_back( "Connection");
    sl.push_back( "Operation");
    tableDevices_->setHorizontalHeaderLabels(sl );

    connect( tableDevices_, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(itemClicked(QTableWidgetItem *)));
    connect( tableDevices_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));

	initAddresses();
    startTimer(1000);
}


DevicesWnd::~DevicesWnd()
{
    delete ui;
}

void DevicesWnd::initAddresses(){
    //if ( addresses_.size() > 0) return;
    QDomElement address = ConfigMgr::instance()->getAddressElem().firstChildElement();
    while (address != QDomElement() ){
        QString ip = address.attribute( "ip");
		bool found = false;
		for ( size_t i = 0; i < tableDevices_->rowCount(); ++i){
			QLineEdit* t = (QLineEdit*)tableDevices_->cellWidget( i, 0);
			if ( ip == t->text()){
				found  = true;
				break;
			}
		}
		if (! found){
			newAddress(ip , address.attribute( "location"));
		}
        address = address.nextSiblingElement();
    }
}

// aa == NULL时, 查看最后一行是否合法,合法就增加新一行
// aa != NULL时, 把最后一行填充,再新建新一行
void DevicesWnd::newAddress( const QString  ip , const QString loc  ){
	if ( ip.isEmpty() ){ //增加新空行
		if (lastLineAddress_ == NULL){
			lastLineAddress_ = new Ac1608Address(this, "", "");
		}
    }else{
		if (lastLineAddress_ == NULL){
			lastLineAddress_ = new Ac1608Address(this, ip, loc);
		}else{
			lastLineAddress_->ip_->setText(ip);
			lastLineAddress_->loc_->setText(loc);
		}
		lastLineAddress_->startCheckAddress();
		lastLineAddress_ = NULL;
		newAddress();
	}
 
}


void DevicesWnd::timerEvent ( QTimerEvent * event ){
    size_t t = GetTickCount();
	for (size_t  it = 0; it != tableDevices_->rowCount(); ++it){
		Ac1608Address * aa = (Ac1608Address*) tableDevices_->cellWidget( it, 4);
		if (aa != lastLineAddress_){
			aa->timerEvent( t);
		}
    }
}


void DevicesWnd::connectImpl( Ac1608Address* aa){
    if (aa != currConnAddress_){ //切换当前连接的IP
		if (currConnAddress_) currConnAddress_->ip_->setEnabled(true);
		aa->ip_->setEnabled(false);
        SnmpNet::instance()->switchAsyncSnmpAddress( aa->ip_->text().toStdString() );

        QTableWidgetItem  * conn;
        if ( currConnAddress_ != 0){
			currConnAddress_->setText( "Connect");
			currConnAddress_->status_->setBackground(QBrush(QColor(Qt::green))); 
        }
		aa->setText("");
		aa->status_->setBackground(QBrush(QColor(Qt::blue))); 
        currConnAddress_ = aa;
    }
}


void DevicesWnd::cellChanged(int row,int col){
    if (col == 1  ){
		QLineEdit* addr = (QLineEdit*)tableDevices_->cellWidget(row, 0); 
		QTableWidgetItem* loc = (QTableWidgetItem*)tableDevices_->item(row, 1); 
		if ( !addr->text().isEmpty() && !loc->text().isEmpty())
			ConfigMgr::instance()->setIP( addr->text(), loc->text() );
    }
}

