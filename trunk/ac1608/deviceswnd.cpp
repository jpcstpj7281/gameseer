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



DevicesWnd::DevicesWnd(QWidget *parent) :
    QWidget(parent)
    ,currConnAddress_(0)
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
    connect( tableDevices_, SIGNAL(cellActivated(int,int)), this, SLOT(cellActivated(int,int)));
    connect( tableDevices_, SIGNAL(cellEntered(int,int)), this, SLOT(cellEntered(int,int)));

    startTimer(1000);
}


DevicesWnd::~DevicesWnd()
{
    delete ui;
}

//SnmpCallback::RequestStatus dispatchFunc1(int status, snmp_session *sp, snmp_pdu *pdu, SnmpObj* so){
//    const int len = 128;
//    char buf[len];
//    memset( buf, 0, 1024);
//    snprint_variable( buf, len, pdu->variables->name, pdu->variables->name_length, pdu->variables);
//    qDebug()<<buf;
//    return SnmpCallback::RequestAgain;
//}

//void DevicesWnd::refresh(){
//    SnmpNet::instance()->addAsyncGet( "1.3.6.1.2.1.1.3.0",  "192.168.1.100" ,  "public" ,  std::bind<SnmpCallbackFunc >( dispatchFunc1, _1, _2, _3, _4 ));
//}

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
        connect( lastLineEdit_, SIGNAL(editingFinished ()), this, SLOT(editingNewAddressFinished ()));

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
        disconnect( lastLineEdit_, SIGNAL(editingFinished ()), this, SLOT(editingNewAddressFinished ()));
        connect( lastLineEdit_, SIGNAL(editingFinished ()), this, SLOT(editingAddressFinished ()));

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
        aa->init( lastLineEdit_, this);
    }
    //locker_.unlock();
    newAddress();
}

void Ac1608Address::editingAddressFinished (){
    if ( this->ip == this->lineEdit_->text() ) return;

    if ( this == t_->currConnAddress_){
        this->lineEdit_->setText(this->ip);
        return;
    }
    t_->checkingRefreshed( this);
    DevicesWnd::AddressMap::iterator found = t_->addresses_.find( this->ip);
    if (found != t_->addresses_.end() ){
        this->ip = this->lineEdit_->text();
        t_->addresses_.erase( found);
        t_->addresses_.insert( std::make_pair( this->ip, this) );
        this->startCheckTime = GetTickCount();
        if ( t_->currConnAddress_ == this){
            t_->currConnAddress_ = 0;
        }
        this->snmpResponseTime = 0;
        SnmpNet::instance()->listenAddress((char*) ip.toStdString().c_str() , std::bind<SnmpCallbackFunc >( &DevicesWnd::checkAddressCallback,t_, _1, _2, _3, _4));
		
    }else{
        qDebug()<<"Unexpected Error: Ac1608Address::editingAddressFinished!";
    }
}

void DevicesWnd::editingNewAddressFinished (){
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
        AddressMap::iterator found = addresses_.find( so->ip.c_str());
        if ( found != addresses_.end() ) {
            Ac1608Address * aa = found->second;
            aa->timeticks = *(u_long *) (pdu->variables->val.integer);
            aa->snmpResponseTime = GetTickCount();
        }
		return SnmpCallback::RequestAgain;
    }
	else if (pdu->variables->type == ASN_INTEGER ){
		AddressMap::iterator found = addresses_.find( so->ip.c_str());
        if ( found != addresses_.end() ) {
            Ac1608Address * aa = found->second;
            //aa->timeticks = *(u_long *) (pdu->variables->val.integer);
            //aa->snmpResponseTime = GetTickCount();
			std::string psw(so->snmpoid.c_str() );
			if ( PswOid0 == psw){
				aa->psw_[0] = *(u_long *) (pdu->variables->val.integer);
				aa->pswCount_++;
			}
			else if ( PswOid1 == psw){
				aa->psw_[1] = *(u_long *) (pdu->variables->val.integer);
				aa->pswCount_++;
			}
			else if ( PswOid2 == psw){
				aa->psw_[2] = *(u_long *) (pdu->variables->val.integer);
				aa->pswCount_++;
			}
			else if ( PswOid3 == psw){
				aa->psw_[3] = *(u_long *) (pdu->variables->val.integer);
				aa->pswCount_++;
			}
        }
		return SnmpCallback::RequestStop;
	}
    
}

void DevicesWnd::timerEvent ( QTimerEvent * event ){
    size_t t = GetTickCount();
    for (AddressMap::iterator it = addresses_.begin(); it != addresses_.end(); ++it){
        Ac1608Address * aa = it->second;
        size_t elapsedCheckTime = t - aa->startCheckTime;
        if ( aa->snmpResponseTime == 0 &&  elapsedCheckTime < 2000 ) 
            continue;
        size_t elapsed = t - aa->snmpResponseTime;
        if (elapsed > 2000 && elapsedCheckTime >=2000){
            offlineRefreshed(aa);
        }else{
            onlineRefreshed(aa);
			if ( aa->pswCount_ == 0 && aa->psw_[0] == 0 && aa->psw_[1] == 0 && aa->psw_[2] == 0 && aa->psw_[3] == 0){ //检查是否已经开始读PSW
				aa->psw_[0] = 1;//标记已经开始读PSW
				SnmpNet::instance()->addAsyncGetWithIP("PSW0", PswOid0.c_str(),(char*) aa->ip.toStdString().c_str() , "public", std::bind<SnmpCallbackFunc >( &DevicesWnd::checkAddressCallback,this, _1, _2, _3, _4));
				SnmpNet::instance()->addAsyncGetWithIP("PSW1", PswOid1.c_str(),(char*) aa->ip.toStdString().c_str() , "public", std::bind<SnmpCallbackFunc >( &DevicesWnd::checkAddressCallback,this, _1, _2, _3, _4));
				SnmpNet::instance()->addAsyncGetWithIP("PSW2", PswOid2.c_str(),(char*) aa->ip.toStdString().c_str() , "public", std::bind<SnmpCallbackFunc >( &DevicesWnd::checkAddressCallback,this, _1, _2, _3, _4));
				SnmpNet::instance()->addAsyncGetWithIP("PSW3", PswOid3.c_str(),(char*) aa->ip.toStdString().c_str() , "public", std::bind<SnmpCallbackFunc >( &DevicesWnd::checkAddressCallback,this, _1, _2, _3, _4));
			}
        }
    }
}
void DevicesWnd::checkingRefreshed(Ac1608Address * aa){
    QTableWidgetItem  * item2 = tableDevices_->item( aa->row, 2);
    item2->setText("");
    if ( aa != currConnAddress_){
        QTableWidgetItem  * item3 = tableDevices_->item( aa->row, 3);
        item3->setBackground(QBrush(QColor(Qt::white))); 
        item3->setText("Checking...");
        QTableWidgetItem  * item4 = tableDevices_->item( aa->row, 4);
        item4->setText( "");
        item4->setBackground(QBrush(QColor(Qt::white))); 
        QTableWidgetItem  * item5 = tableDevices_->item( aa->row, 5);
        item5->setBackground(QBrush(QColor(Qt::white))); 
    }
}

bool Ac1608Address::valiatePassword( ){
	if ( this->psw_[0] == this->inputPsw_[0] && this->psw_[1] == this->inputPsw_[1] && this->psw_[2] == this->inputPsw_[2] && this->psw_[3] == this->inputPsw_[3]){
		return true;
	}
	return false;
}

void DevicesWnd::onlineRefreshed(Ac1608Address * aa){
    QTableWidgetItem  * item2 = tableDevices_->item( aa->row, 2);
    item2->setText(timeticksToString(aa->timeticks ) );
    if ( aa != currConnAddress_){
        QTableWidgetItem  * item3 = tableDevices_->item( aa->row, 3);
        item3->setBackground(QBrush(QColor(Qt::green))); 
        item3->setText("Online");

		if ( aa->pswCount_ >=4 && aa->valiatePassword( ) ){
			QTableWidgetItem  * item4 = tableDevices_->item( aa->row, 4);
			item4->setText( "Connect");
			item4->setBackground(QBrush(QColor(Qt::lightGray))); 
		}else{
			QTableWidgetItem  * item4 = tableDevices_->item( aa->row, 4);
			item4->setText( "Password");
			item4->setBackground(QBrush(QColor(Qt::lightGray))); 
		}

		if ( aa->pswCount_ == 4){
			QTableWidgetItem  * item5 = tableDevices_->item( aa->row, 5);
			item5->setBackground(QBrush(QColor(Qt::lightGray))); 
			item5->setText( "Password");
		}
    }
}

void DevicesWnd::offlineRefreshed(Ac1608Address * aa){
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
}

void DevicesWnd::connectImpl( Ac1608Address* aa){
    if (aa != currConnAddress_){ //切换当前连接的IP
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
    if (item->column() == 4 ){
        if(item->text() == "Connect" ){
		//if(item->text() == "" ){
            Ac1608Address* aa = getAddressByRow( addresses_ , item->row());
			int newPsw[4];
			if ( inputDlg_->getNewPsw( aa)){
				connectImpl(aa);
			}
        }
		if(item->text() == "Password" ){
            Ac1608Address* aa = getAddressByRow( addresses_ , item->row());
            connectImpl(aa);
        }
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
