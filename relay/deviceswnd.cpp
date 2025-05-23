#include "deviceswnd.h"
#include "ui_deviceswnd.h"
#include <QTableWidgetItem>
#include "configmgr.h"
#include <functional>
#include <qdebug>
#include <Windows.h>
#include <boost/foreach.hpp>
#include "TestNet.h"
#include "ui_mainwindow.h"
#include <QComboBox>
#include <qlabel.h>
#include <QVBoxLayout>
#include "TcpNet.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QFile>
#include <QCoreApplication>
#include <QDesktopServices>
#include <QStringRef>
#include <QPlainTextEdit>
#include <log4qt/FileAppender.h>
#include <QDir>
#include <QBuffer>

#undef min
using namespace std::placeholders;
static QString gstyle = "* { background-color: lightGreen }";
static QString rstyle = "* { background-color: red }";

void NetConnBtn::conn(){
	std::string ip = address_->text().toStdString();
	if ( !ip.empty() && !TcpNet::instance()->hasHost( ip)){
		Host* host = TcpNet::instance()->createHost(ip);
		host->connInit();
		setText("Connecting...");
		this->setEnabled(false);
		address_->setEnabled(false);
		testBtn_->setEnabled(false);
		channels_->setEnabled(false);
		
		QDomNodeList items = ConfigMgr::instance()->getDoc()->documentElement().elementsByTagName("psw");
		std::string psw("1");
		if ( items.size() > 0){
			psw = items.at(0).toElement().attribute("val").toStdString();
		}
		host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("Login "+psw+"\r\n")) );
	}
}
void NetConnBtn::disconn(){
	std::string ip = address_->text().toStdString();
	if ( TcpNet::instance()->hasHost( ip)){
		TcpNet::instance()->removeHost(ip);
		testBtn_->setEnabled(false);
		//if (testNet_ && !testNet_->isHidden() ) testNet_->hide();
		setText("Connect");
		address_->setEnabled(true);
		channels_->setEnabled(false);

		status_->setText("Off Line");
		status_->setBackground(QBrush(QColor(Qt::red)));
		this->setEnabled(true);
		testBtn_->setEnabled(false);
		this->address_->setEnabled(true);
		this->loc_->setText("");
		this->desc_->setText("");
		this->runTime_->setText("");
		this->version_->setText("");

		if (testNet_) {
			delete testNet_;
			testNet_ = 0;
		}
		for ( size_t i = 0; i <= ChannelShift::ChannelAllOn; ++i){
			btns_[i]->setStyleSheet("");
		}
	}
}

void NetConnBtn::clickit(){
	//if ( address_->text().isEmpty() ){
	//	address_->setText("127.0.0.1") ;
	//}
	if ( !address_->text().isEmpty() && text() == "Connect"){
		conn();
	}else if (text() == "Disconnect"){
		disconn();
	}
}
void NetConnBtn::clickTest(){
	if (testNet_ == NULL && !address_->text().isEmpty()){
		testNet_ = new TestQbox(address_->text().toStdString() );
		testNet_->resize( 800, 600);
		testNet_->show();
	}else{
		if (testNet_->isHidden()){
			testNet_->show();
		}
	}
}
void NetConnBtn::timerEvent ( QTimerEvent * ){
	if (text() == "Disconnect"){
		if (tickcount_!=0){
			size_t now = GetTickCount();
			if ( now - tickcount_ > 1000 && isReadResponded_ ){
				tickcount_ = now;
                isReadResponded_ = false;
				std::string ip = address_->text().toStdString();
				if ( !ip.empty() && TcpNet::instance()->hasHost( ip)){
					Host* host = TcpNet::instance()->getHost(ip);
					host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("Read\r\n")) );
				}
			}
			if ( now - tickcount_ > 5000 && !isReadResponded_ ){
				this->disconn();
				ongoingCmd_.clear();
				ongoingDelay_.clear();
                return;
			}
			disconnTickCount_ = now;
		}
	}else if (text() == "Connect" && !address_->text().isEmpty()){
		size_t now = GetTickCount();
		if ( now - disconnTickCount_ > 10000){
			conn();
			disconnTickCount_ = now;
		}
	}

	for ( size_t i = 0; i < rTimers_.size(); ++i){
		calcTimer( rTimers_[i]);
	}
	if ( ongoingDelay_.size() > 0 && ongoingDelay_.front() < GetTickCount() ){//exec next ongoing cmd
		Host* host = TcpNet::instance()->getHost(address_->text().toStdString());
		host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(ongoingCmd_.front() ) );
		ongoingCmd_.pop_front();
		ongoingDelay_.pop_front();
	}
}

void NetConnBtn::switchBtn(RelayTimer* rt){
	size_t btnState_ = rt->status >> 8;
	size_t chnState_ = rt->status & 255;

	if ( btnState_ & (1 << ChannelShift::ChannelAllOn) ){
		std::string ip = address_->text().toStdString();
		if ( !ip.empty() && TcpNet::instance()->hasHost( ip)){
			Host* host = TcpNet::instance()->getHost(ip);
			host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("ON [1,2,3,4,5,6,7,8] T["+QString::number(rt->delay).toStdString()+"]\r\n")) );
			waitForState_ = WaitAllOn;
		}
	}
	else if ( btnState_ & (1 << ChannelShift::ChannelAllOff) ){
		std::string ip = address_->text().toStdString();
		if ( !ip.empty() && TcpNet::instance()->hasHost( ip)){
			Host* host = TcpNet::instance()->getHost(ip);
			host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("OFF [1,2,3,4,5,6,7,8] T["+QString::number(rt->delay).toStdString()+"]\r\n")) );
			waitForState_ = WaitAllOff;
		}
	}else{
		std::string ip = address_->text().toStdString();
		Host* host = TcpNet::instance()->getHost(ip);
		
		std::string offdata = "OFF [";
		for ( int i = 0; i < 8; ++i){
			if ( btnState_ & (1<<i)){
				if (! (chnState_ & (1<<i))){
					offdata+=QString::number(i+1).toStdString()+",";
				}
			}
		}
		if (offdata.length() > strlen("OFF [")){
			offdata[offdata.length()-1] = ']';
			offdata += " T["+QString::number(rt->delay).toStdString()+"]\r\n";
			ongoingCmd_.push_back(offdata);
		}

		std::string ondata = "ON [";
		for ( int i = 0; i < 8; ++i){
			if ( btnState_ & (1<<i)){
				if ( chnState_ & (1<<i)){
					ondata+=QString::number(i+1).toStdString()+",";
				}
			}
		}
		if (ondata.length() > strlen("ON [")){
			ondata[ondata.length()-1] = ']';
			ondata += " T["+QString::number(rt->delay).toStdString()+"]\r\n";
			host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(ondata));
		}else{
			if (ongoingCmd_.size()>0){
				host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(ongoingCmd_.front()));
				ongoingCmd_.pop_front();
			}
		}

		if ( ongoingCmd_.size() != ongoingDelay_.size()){
			size_t status = btnState_ & 255;
			size_t count = 0;
			for ( size_t i = 0; i < 8; ++i){
				if ( ((btnState_ >> i) & 1) & ((chnState_>>i)&1) ) {
					++count;
				}
			}
			ongoingDelay_.push_back(GetTickCount()+ rt->delay *1000 * count + 500);
		}

		size_t status = btnState_ & 255;
		size_t count = 0;
		for ( size_t i = 0; i < 8; ++i){
			if ( (btnState_ >> i) & 1){
				++count;
			}
		}
		waitTime_ = GetTickCount()+ rt->delay *1000 * count + 500;
		waitForState_ = WaitTime;
		
	}
	channels_->setEnabled(false);
}

void NetConnBtn::calcTimer( RelayTimer* rt){
	QDateTime dt = QDateTime::fromString(QString::fromStdString(rt->dt), DATETIME_STRING);
	size_t daySec = dt.secsTo(QDateTime::currentDateTime());
	size_t timeSec =  dt.time().secsTo(QTime::currentTime());

	switch( rt->freq){
	case TriggerFreq::OneTime:
		if ( daySec < 2 && daySec > 0){
			switchBtn(rt);
			rt->freq |= (1<<24); //already triggered, stop trigger again with in ten sec
		}
		break;
	case TriggerFreq::EveryDate:
		if(timeSec < 2 && timeSec > 0 ){
			switchBtn(rt);
			rt->freq |= (1<<24);//already triggered, stop trigger again with in ten sec
		}
		break;
	case TriggerFreq::EveryWeek:
		if( timeSec < 2 && timeSec > 0  && dt.date().weekNumber() ==  QDate::currentDate().weekNumber()){
			switchBtn(rt);
			rt->freq |= (1<<24);//already triggered, stop trigger again with in ten sec
		}
		break;
	case TriggerFreq::EveryMonth:
		if( timeSec < 2 && timeSec > 0  && dt.date().daysInMonth() ==  QDate::currentDate().daysInMonth()){
			switchBtn(rt);
			rt->freq |= (1<<24);//already triggered, stop trigger again with in ten sec
		}
		break;
	case TriggerFreq::EveryYear:
		if( timeSec < 2 && timeSec > 0  &&  dt.date().month() ==  QDate::currentDate().month() &&  dt.date().daysInMonth() ==  QDate::currentDate().daysInMonth()){
			switchBtn(rt);
			rt->freq |= (1<<24);//already triggered, stop trigger again with in ten sec
		}
		break;
	default:
		if ( rt->freq >= (1<<24) && timeSec >2){
			rt->freq &= ~(1<<24);
		}
		
	}
}

void NetConnBtn::initTimer(){
	if (rTimers_.size() == 0){
		QDomNodeList items = ConfigMgr::instance()->getDoc()->elementsByTagName("timer");
		for(size_t i = 0; i <items.length(); ++i){
			QDomNode node = items.at(i);
			QDomElement elem = node.toElement();
			if ( elem.attribute("ip") == address_->text()){
				QString dt = elem.attribute("datetime");
				QString freq = elem.attribute("freq");
				QString status = elem.attribute("status");
				QString delay = elem.attribute("delay");
				QString comm = elem.attribute("comment");
				if (! dt.isEmpty() ){
					RelayTimer* rtp = new RelayTimer;
					RelayTimer &rt = *rtp;
					rt.dt = dt.toStdString();
					rt.freq=(freq.toInt() );
					rt.status=( status.toInt(0, 2) );
					rt.delay=( delay.toInt());
					rt.comment = comm.toStdString();
					rTimers_.push_back(rtp);
				}
			}
		}
	}
}
bool NetConnBtn::incommingCallback( const std::string& msg){
	QString qmsg = QString::fromStdString(msg);
	std::string ip = address_->text().toStdString();
	if ( qmsg.contains( "Manual ON") ){
		Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
		QString tmp = qmsg.left(qmsg.indexOf("]"));
		QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("[") -1);
		QPushButton* btn = channels_->findChild<QPushButton*>(tmp1);
		btn->setChecked(true);
		btn->setStyleSheet(gstyle);
	}else if (qmsg.contains( "Manual OFF" )){
		Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
		QString tmp = qmsg.left(qmsg.indexOf("]"));
		QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("[") -1);
		QPushButton* btn = channels_->findChild<QPushButton*>(tmp1);
		btn->setChecked(false);
		btn->setStyleSheet(rstyle);
	}
	return false;
}
bool NetConnBtn::connectedCallback( const std::string& msg){
	std::string ip = address_->text().toStdString();
	if ( msg == "Login OK."){
		desc_->setFlags( Qt::ItemIsEnabled| Qt::ItemIsEditable );
		loc_->setFlags( Qt::ItemIsEnabled| Qt::ItemIsEditable );
		this->setEnabled(true);
		channels_->setEnabled(true);
		testBtn_->setEnabled(true);
		setText("Disconnect");
		if ( !ip.empty() && TcpNet::instance()->hasHost( ip)){
			Host* host = TcpNet::instance()->getHost(ip);
			host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("Read\r\n")) );
			host->addListener( std::bind( &NetConnBtn::incommingCallback, this, _1));
		}
		status_->setText("Login");
		status_->setBackground(QBrush(QColor(Qt::green)));
		initTimer();
		startTimer(300);
		Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
	}else if ( msg == HOST_CONNECT_FAILED ){
		setText("Connect");
		status_->setText("Off Line");
		status_->setBackground(QBrush(QColor(Qt::red)));
		this->setEnabled(true);
		channels_->setEnabled(false);
		testBtn_->setEnabled(false);
		this->address_->setEnabled(true);
		std::string ip = address_->text().toStdString();
		Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
		desc_->setFlags( Qt::ItemIsEnabled );
		loc_->setFlags( Qt::ItemIsEnabled );
		TcpNet::instance()->removeHost(ip);
	}else if ( msg == "OFF [1,2,3,4,5,6,7,8]"){
		channels_->setEnabled(false);
		Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
	}else if ( msg == "ON [8,7,6,5,4,3,2,1]"){
		channels_->setEnabled(false);
		Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
	}else{
		QString qmsg = QString::fromStdString(msg);


		if ( qmsg.indexOf( "ON [") ==0 ){
			Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
			QString tmp = qmsg.left(qmsg.indexOf("]"));
			QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("[") -1);
			QPushButton* btn = channels_->findChild<QPushButton*>(tmp1);
			if ( btn){
				btn->setChecked(true);
				btn->setStyleSheet(gstyle);
			}

		}else if (qmsg.indexOf( "OFF [" )==0 ){
			Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
			QString tmp = qmsg.left(qmsg.indexOf("]"));
			QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("[") -1);
			QPushButton* btn = channels_->findChild<QPushButton*>(tmp1);
			if ( btn){
				btn->setChecked(false);
				btn->setStyleSheet(rstyle);
			}
		}else if (qmsg.indexOf("Location:") == 0){
			Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
		}
		else if (qmsg.indexOf("Description:") == 0){
			Log4Qt::Logger::logger(ip.c_str())->info(msg.c_str());
		}

		if (qmsg.contains("ON:")){
			QList<QPushButton*> list = channels_->findChildren<QPushButton*>();
			QString tmp = qmsg.left(qmsg.indexOf("]"));
			QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("[") -1);
			QList<QString> chns = tmp1.split(",");

			for (size_t i = 0; i < ChannelShift::ChannelAllOff; ++i){
				btns_[i]->setChecked(false);
				btns_[i]->setStyleSheet(rstyle);
			}
			btns_[ChannelShift::ChannelAllOff]->setChecked(false);
			btns_[ChannelShift::ChannelAllOff]->setStyleSheet(rstyle);
			btns_[ChannelShift::ChannelAllOn]->setChecked(false);
			btns_[ChannelShift::ChannelAllOn]->setStyleSheet(gstyle);
			for ( auto it = chns.begin(); it!= chns.end();++it){
				QPushButton* btn = channels_->findChild<QPushButton*>(*it);
				btn->setChecked(true);
				btn->setStyleSheet(gstyle);
			}

			if(qmsg.contains("Location:") && waitForState_ != WaitNothing){
				QString style;
				bool check;
				if (waitForState_ == WaitAllOff){
					if (chns.size() == 0 || chns[0].isEmpty()){
						waitForState_ = WaitNothing;
						style = rstyle;
						check = false;
					}
				}
				if (waitForState_ == WaitAllOn){
					if (chns.size() == 8){
						waitForState_ = WaitNothing;
						style = gstyle;
						check = true;
					}
				}
				if ( waitForState_ == WaitNothing){
					for (auto it = list.begin(); it != list.end(); ++it){
						if ((*it)->text() != "All"){
							(*it)->setChecked(check);
							(*it)->setStyleSheet(style);
						}
					}
					channels_->setEnabled(true);
				}
				if (waitForState_ == WaitTime){
					if ( GetTickCount() > waitTime_){
						channels_->setEnabled(true);
					}
				}
			}
			if (qmsg.contains("Location:")){
				QString tmp = qmsg.left(qmsg.indexOf("Description"));
				QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("Location: ") - strlen("Location: "));
				QString tmp2 = tmp1.trimmed();
				if (tmp2 != loc_->text()){
					loc_->setText(tmp2);
					loc_->setToolTip(tmp2);
				}
			}
			if (qmsg.contains("Description:")){
				QString tmp = qmsg.left(qmsg.indexOf("RunTime"));
				QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("Description: ") - strlen("Description: "));
				QString tmp2 = tmp1.trimmed();
				if (tmp2 != desc_->text()){
					desc_->setText(tmp2);
					desc_->setToolTip(tmp2);
				}
			}
			if (qmsg.contains("RunTime:")){
				QString tmp = qmsg.left(qmsg.indexOf("Model"));
				QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("RunTime: ") - strlen("RunTime: "));
				runTime_->setText(tmp1);
				runTime_->setToolTip(tmp1);
				tickcount_ = GetTickCount();
                isReadResponded_ = true;
			}
			if (qmsg.contains("Model:")){
				QString tmp = qmsg.left(qmsg.indexOf("Ver"));
				QString tmp1 = tmp.right(tmp.length() - tmp.indexOf("Model: ") - strlen("Model: "));
				QString tmp2 = tmp1.trimmed();
				if ( tmp2 == "M0"){
					channels_->setEnabled(false);
				}else if ( tmp2.trimmed() == "Remote" && waitForState_ == WaitNothing){
					channels_->setEnabled(true);
				}
				model_->setText(tmp2);
				model_->setToolTip(tmp2);
			}
			if (qmsg.contains("Ver:")){
				QString tmp1 = qmsg.right(qmsg.length() - qmsg.indexOf("Ver: ") - strlen("Ver: "));
				version_->setText(tmp1);
				version_->setToolTip(tmp1);
			}
		
		}
		return true;
	}
	return true;
}

void NetConnBtn::onAll(int interval){
	if ( waitForState_ != WaitNothing) return;
	std::string ip = address_->text().toStdString();
	if ( !ip.empty() && TcpNet::instance()->hasHost( ip)){
		Host* host = TcpNet::instance()->getHost(ip);
		host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("ON [1,2,3,4,5,6,7,8] T["+QString::number(interval).toStdString()+"]\r\n")) );
		waitForState_ = WaitAllOn;
	}
}
void NetConnBtn::offAll(int interval){
	if ( waitForState_ != WaitNothing) return;
	std::string ip = address_->text().toStdString();
	if ( !ip.empty() && TcpNet::instance()->hasHost( ip)){
		Host* host = TcpNet::instance()->getHost(ip);
		host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("OFF [8,7,6,5,4,3,2,1] T["+QString::number(interval).toStdString()+"]\r\n")) );
		waitForState_ = WaitAllOff;
	}
}
void NetConnBtn::clickOn(){
	onAll(interval_->text().toInt());
}
void NetConnBtn::clickOff(){
	offAll(interval_->text().toInt());
}
void NetConnBtn::channelChange(const std::string& chn, QPushButton* btn){
	if ( waitForState_ != WaitNothing) return;
	std::string ip = address_->text().toStdString();
	if ( !ip.empty() && TcpNet::instance()->hasHost( ip)){
		Host* host = TcpNet::instance()->getHost(ip);
		if ( btn->isChecked()){
			host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("ON ["+chn+"]\r\n")) );
			btn->setStyleSheet("* { background-color: lightGreen }");
		}else{
			
			host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, this, _1), std::move(std::string("OFF ["+chn+"]\r\n")) );
			btn->setStyleSheet("* { background-color: red }");
		}
	}
}
void NetConnBtn::click1(){
	channelChange("1", (QPushButton*)sender());
}
void NetConnBtn::click2(){
	channelChange("2", (QPushButton*)sender());
}
void NetConnBtn::click3(){
	channelChange("3", (QPushButton*)sender());
}
void NetConnBtn::click4(){
	channelChange("4", (QPushButton*)sender());
}
void NetConnBtn::click5(){
	channelChange("5", (QPushButton*)sender());
}
void NetConnBtn::click6(){
	channelChange("6", (QPushButton*)sender());
}
void NetConnBtn::click7(){
	channelChange("7", (QPushButton*)sender());
}
void NetConnBtn::click8(){
	channelChange("8", (QPushButton*)sender());
}

NetConnBtn::NetConnBtn( const std::string & ip ):
	QPushButton()
	,testNet_(0)
	,loc_( new QTableWidgetItem)
	,desc_(new QTableWidgetItem)
	,version_(new QTableWidgetItem)
	,runTime_(new QTableWidgetItem)
	,status_(new QTableWidgetItem)
	,model_(new QTableWidgetItem)
	,address_(new QLineEdit)
	,channels_(new QPushButton)
	,testBtn_(new QPushButton)
	,timer_(new QPushButton)
	,timerwnd_(0)
	,ctrl_(new QWidget)
	,interval_(new  QSpinBox)
	,tickcount_(0)
	,waitForState_(WaitNothing)
	,disconnTickCount_ ( GetTickCount())
	,isReadResponded_(true)
{

	this->setText( "Connect");

	QVBoxLayout* layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->setSpacing(0);
	QPushButton* add = new  QPushButton;
	QPushButton* remove = new  QPushButton;
	add->setText("+");
	remove->setText("-");
	layout->addWidget(add );
	layout->addWidget(remove );
	ctrl_->setLayout(layout);
	connect( add, SIGNAL(clicked()), this, SLOT(clickInsert()) );
	connect( remove, SIGNAL(clicked()), this, SLOT(clickDelete()) );

	QHBoxLayout* chnLayout = new QHBoxLayout();
	chnLayout->setMargin(2);
	chnLayout->setSpacing(1);
	QPushButton* on = new  QPushButton;
	QPushButton* off = new  QPushButton;
	QPushButton* btn1 = new  QPushButton;
	QPushButton* btn2 = new  QPushButton;
	QPushButton* btn3 = new  QPushButton;
	QPushButton* btn4 = new  QPushButton;
	QPushButton* btn5 = new  QPushButton;
	QPushButton* btn6 = new  QPushButton;
	QPushButton* btn7 = new  QPushButton;
	QPushButton* btn8 = new  QPushButton;
	btn1->setCheckable(true);
	btn2->setCheckable(true);
	btn3->setCheckable(true);
	btn4->setCheckable(true);
	btn5->setCheckable(true);
	btn6->setCheckable(true);
	btn7->setCheckable(true);
	btn8->setCheckable(true);
	on->setStyleSheet("");
	off->setStyleSheet("");
	on->setText("All");
	off->setText("All");
	btn1->setText("1");btn1->setObjectName("1");btn1->setStyleSheet("");btn1->setChecked(false);
	btn2->setText("2");btn2->setObjectName("2");btn2->setStyleSheet("");btn2->setChecked(false);
	btn3->setText("3");btn3->setObjectName("3");btn3->setStyleSheet("");btn3->setChecked(false);
	btn4->setText("4");btn4->setObjectName("4");btn4->setStyleSheet("");btn4->setChecked(false);
	btn5->setText("5");btn5->setObjectName("5");btn5->setStyleSheet("");btn5->setChecked(false);
	btn6->setText("6");btn6->setObjectName("6");btn6->setStyleSheet("");btn6->setChecked(false);
	btn7->setText("7");btn7->setObjectName("7");btn7->setStyleSheet("");btn7->setChecked(false);
	btn8->setText("8");btn8->setObjectName("8");btn8->setStyleSheet("");btn8->setChecked(false);
	btns_[ChannelShift::Channel1] = btn1;
	btns_[ChannelShift::Channel2] = btn2;
	btns_[ChannelShift::Channel3] = btn3;
	btns_[ChannelShift::Channel4] = btn4;
	btns_[ChannelShift::Channel5] = btn5;
	btns_[ChannelShift::Channel6] = btn6;
	btns_[ChannelShift::Channel7] = btn7;
	btns_[ChannelShift::Channel8] = btn8;
	btns_[ChannelShift::ChannelAllOn] = on;
	btns_[ChannelShift::ChannelAllOff] = off;
	connect( on, SIGNAL(clicked()), this, SLOT(clickOn()) );
	connect( off, SIGNAL(clicked()), this, SLOT(clickOff()) );
	connect( btn1, SIGNAL(clicked()), this, SLOT(click1()) );
	connect( btn2, SIGNAL(clicked()), this, SLOT(click2()) );
	connect( btn3, SIGNAL(clicked()), this, SLOT(click3()) );
	connect( btn4, SIGNAL(clicked()), this, SLOT(click4()) );
	connect( btn5, SIGNAL(clicked()), this, SLOT(click5()) );
	connect( btn6, SIGNAL(clicked()), this, SLOT(click6()) );
	connect( btn7, SIGNAL(clicked()), this, SLOT(click7()) );
	connect( btn8, SIGNAL(clicked()), this, SLOT(click8()) );
	chnLayout->addWidget(on );
	chnLayout->addWidget(off );
	chnLayout->addWidget(btn1 );
	chnLayout->addWidget(btn2 );
	chnLayout->addWidget(btn3 );
	chnLayout->addWidget(btn4 );
	chnLayout->addWidget(btn5 );
	chnLayout->addWidget(btn6 );
	chnLayout->addWidget(btn7 );
	chnLayout->addWidget(btn8 );
	channels_->setLayout(chnLayout);
	channels_->setEnabled(false);

	loc_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	loc_->setFlags( Qt::ItemIsEnabled );

	desc_->setFlags( Qt::ItemIsEnabled );
	desc_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);

	version_->setFlags( Qt::ItemIsEnabled );
	version_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);

	status_->setFlags( Qt::ItemIsEnabled );
	status_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);

	runTime_->setFlags( Qt::ItemIsEnabled );
	runTime_->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);


	testBtn_->setEnabled(false);
	testBtn_->setText( "Test");
	connect( testBtn_, SIGNAL(clicked()), this, SLOT(clickTest()) );

	QRegExp ipRx("((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-4]|[01]?\\d\\d?)");
	QRegExpValidator *pIpValidator = new QRegExpValidator(ipRx);
	address_->setValidator(pIpValidator);
	address_->setAlignment( Qt::AlignVCenter| Qt::AlignHCenter);
	address_->setText( QString::fromStdString( ip) );
	connect( address_, SIGNAL(editingFinished()), this, SLOT(editFinished()));

	connect( this, SIGNAL(clicked()), this, SLOT(clickit()) );
	
	
	timer_->setText( "Edit");
	connect( timer_, SIGNAL(clicked()), this, SLOT(clickTimer()) );

	
	interval_->setMinimum( 0);
	interval_->setMaximum( 60);
	interval_->setValue(2);

	startTimer(300);
	
}

void NetConnBtn::editFinished(){
	QLineEdit* le = (QLineEdit*)sender();
	if ( le->text().isEmpty() ){
		clickDelete();
		return;
	}

	QTableWidget* table = loc_->tableWidget();
	if ( loc_->row() == table->rowCount()-1 && table){
		NetConnBtn * connBtn = new NetConnBtn( "" );
		table->setRowCount( table->rowCount()+1);
		connBtn->initTable(table,  table->rowCount()-1);
	}
}
NetConnBtn::~NetConnBtn(){
	if (testNet_) delete testNet_;
	if (timerwnd_) delete timerwnd_;
}

void NetConnBtn::clickTimer(){
	initTimer();
	if ( !timerwnd_)  timerwnd_ = new TimerWnd(&rTimers_, address_->text());
	timerwnd_->show();
}

void NetConnBtn::clickInsert(){
	QTableWidget* table = loc_->tableWidget();
	if ( loc_->row() != table->rowCount()-1 && table){
		NetConnBtn * connBtn = new NetConnBtn( "" );
		int row = loc_->row();
		table->insertRow( row);
		connBtn->initTable(table, row);
	}
}
void NetConnBtn::clickDelete(){
	QTableWidget* table = loc_->tableWidget();
	if ( loc_->row() != table->rowCount()-1 && table){
		table->removeRow( loc_->row());
	}
}
void NetConnBtn::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, ctrl_);
	table->setCellWidget ( row, 1, address_);
	table->setItem ( row, 2, loc_ );
	table->setItem ( row, 3, desc_ );
	table->setItem ( row, 4, version_ );
	table->setItem ( row, 5, model_ );
	table->setItem ( row, 6, runTime_ );
	table->setItem ( row, 7, status_ );
	table->setCellWidget ( row, 8, this );
	table->setCellWidget ( row, 9, interval_ );
	table->setCellWidget ( row, 10, channels_ );
	table->setCellWidget ( row, 11, timer_ );
	table->setCellWidget ( row, 12, testBtn_ );
}


DevicesWnd::DevicesWnd(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::DevicesWnd)
	,interval_(2)
{

    ui->setupUi(this);

    tableDevices_ = findChild<QTableWidget* >("tableDevices");
    tableDevices_->setColumnCount( 13);

    QStringList sl;
	sl.push_back( "");
	sl.push_back( "IP");
	sl.push_back( "Location");
	sl.push_back( "Description");
	sl.push_back( "Version");
	sl.push_back( "Model");
	sl.push_back( "Run Time");
	sl.push_back( "Status");
    sl.push_back( "Connection");
	sl.push_back( "SEQ Delay");
	sl.push_back( "Channels");
	sl.push_back( "Timer");
	sl.push_back( "Test");
    tableDevices_->setHorizontalHeaderLabels(sl );
	tableDevices_->setColumnWidth( 0, 20);
	tableDevices_->setColumnWidth( 1, 100);
	tableDevices_->setColumnWidth( 2, 100);
	tableDevices_->setColumnWidth( 3, 100);
	tableDevices_->setColumnWidth( 4, 100);
	tableDevices_->setColumnWidth( 5, 100);
	tableDevices_->setColumnWidth( 6, 100);
	tableDevices_->setColumnWidth( 7, 80);
	tableDevices_->setColumnWidth( 8, 80);
	tableDevices_->setColumnWidth( 9, 70);
	tableDevices_->setColumnWidth( 10, 300);
	tableDevices_->setColumnWidth( 11, 80);
	tableDevices_->setColumnWidth( 12, 50);

    //connect( tableDevices_, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(itemClicked(QTableWidgetItem *)));

    startTimer(1000);
	initAddresses();

	QPushButton *conn = findChild<QPushButton* >("connAll");
	QPushButton *disconn = findChild<QPushButton* >("disconnAll");
	if ( conn){
		connect( conn, SIGNAL(clicked()), this, SLOT(connAll()));
	}
	if ( disconn){
		connect( disconn, SIGNAL(clicked()), this, SLOT(disconnAll()));
	}

	QList<QCheckBox *> list = findChildren<QCheckBox* >();
	for ( auto it = list.begin(); it != list.end(); ++it){
		
		QCheckBox * ch= *it;
		if ( ch->objectName().contains("checkBox_")){
			connect( ch, SIGNAL(stateChanged(int)), this, SLOT(stateChanged(int)));
			if ( !ch->isChecked()){
				QString name = ch->objectName();
				name = name.replace( "checkBox_", "");
				int col = name.toInt();
				tableDevices_->hideColumn( col);
			}
		}else if ( ch->objectName() == "runOnStartup"){
			if ( QFile::exists(QDesktopServices::storageLocation(QDesktopServices::ApplicationsLocation)+"/Startup/relay.exe.lnk") ){
				ch->setChecked(true);
			}
			connect( ch, SIGNAL(stateChanged(int)), this, SLOT(runOnStartup(int)));
		}else if ( ch->objectName() == "showLog"){
			connect( ch, SIGNAL(stateChanged(int)), this, SLOT(showLog(int)));
		}
	}

	QSpinBox* spin= findChild<QSpinBox* >("spinBox");
	connect( spin, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
	QPushButton* all= findChild<QPushButton* >("onAll");
	connect( all, SIGNAL(clicked()), this, SLOT(onAll()));
	all= findChild<QPushButton* >("offAll");
	connect( all, SIGNAL(clicked()), this, SLOT(offAll()));

	QDomNodeList items = ConfigMgr::instance()->getDoc()->documentElement().elementsByTagName("autoconn");
	if ( items.size() > 0){
		QString autoconn = items.at(0).toElement().attribute("val");
		if ( autoconn == "1"){
			this->connAll();
		}
	}

	logWnd_ = findChild<QPlainTextEdit*>("log");
    connect( tableDevices_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));
}



void DevicesWnd::valueChanged( int i ){
	interval_ = i;
}
void DevicesWnd::onAll(){
	for ( int i = 0; i < tableDevices_->rowCount(); ++i){
		NetConnBtn* t = (NetConnBtn*)tableDevices_->cellWidget( i, 8);
		t->onAll(interval_);
	}
}
void DevicesWnd::offAll(){
	for ( int i = 0; i < tableDevices_->rowCount(); ++i){
		NetConnBtn* t = (NetConnBtn*)tableDevices_->cellWidget( i, 8);
		t->offAll(interval_);
	}
}
void DevicesWnd::closeEvent(QCloseEvent * ){

	//QDomNode addrs = ConfigMgr::instance()->getAddressNode();
	QDomElement root = ConfigMgr::instance()->getDoc()->documentElement();
	QDomNode addrs = root.elementsByTagName(XML_ADDRESSES).at(0);
	QDomNodeList items = root.elementsByTagName(XML_ADDRESS);
	while(items.size()){
		QDomNode node = items.at(0);
		QDomElement elem = node.toElement();
		addrs.removeChild(node);
	}
	for ( int i = 0; i < tableDevices_->rowCount(); ++i){
		NetConnBtn* t = (NetConnBtn*)tableDevices_->cellWidget( i, 8);
		if ( !t->address_->text().isEmpty()){
			QDomElement addr = ConfigMgr::instance()->getDoc()->createElement(XML_ADDRESS);
			addr.setAttribute("ip", t->address_->text());
			addrs.insertAfter( addr, QDomElement());
		}
	}
	ConfigMgr::instance()->save();
}
DevicesWnd::~DevicesWnd()
{
	closeEvent(NULL);
    delete ui;
}

void DevicesWnd::runOnStartup(int state){
	if (state){
		QFile::link( QCoreApplication::instance()->applicationFilePath(), QDesktopServices::storageLocation(QDesktopServices::ApplicationsLocation)+"/Startup/relay.exe.lnk");
	}else{
		QFile::remove(QDesktopServices::storageLocation(QDesktopServices::ApplicationsLocation)+"/Startup/relay.exe.lnk");
	}
}

void DevicesWnd::stateChanged(int state){
	QCheckBox * ch = (QCheckBox*)sender();
	QString name = ch->objectName();
	name = name.replace( "checkBox_", "");
	int col = name.toInt();
	if ( state ){
		tableDevices_->showColumn( col);
	}else{
		tableDevices_->hideColumn( col);
	}
}

void DevicesWnd::disconnAll(){
	for ( int i = 0; i < tableDevices_->rowCount(); ++i){
		NetConnBtn* t = (NetConnBtn*)tableDevices_->cellWidget( i, 8);
		if ( t->text() == "Disconnect"){
			t->disconn();
		}
	}
}
void DevicesWnd::connAll(){
	for ( int i = 0; i < tableDevices_->rowCount(); ++i){
		NetConnBtn* t = (NetConnBtn*)tableDevices_->cellWidget( i, 8);
		
		if ( !t->address_->text().isEmpty() && t->text() == "Connect"){
			t->conn();
		}
	}
}

//load addresses from configuration
void DevicesWnd::initAddresses(){

	QDomNodeList items = ConfigMgr::instance()->getDoc()->elementsByTagName("address");
	QString oid;
	for(size_t i = 0; i <items.length(); ++i){
		QDomNode node = items.at(i);
		QDomElement elem = node.toElement();
		newAddress(elem.attribute("ip").toStdString() );
	}
}

void DevicesWnd::newAddress( const std::string &ip){
	QLineEdit * le = 0;
	if ( tableDevices_->rowCount()>0){
		le= (QLineEdit*) tableDevices_->cellWidget( tableDevices_->rowCount()-1, 1);
	}
	int insertRow = 0;
	if ( le==0 ){
		insertRow = 1;
	}else if (le->text().isEmpty()  ){//最后一行已经是空IP
		if ( ip.empty() ) return;	//无需操作
		else {
			insertRow = tableDevices_->rowCount()-1;//在空行前插入
			tableDevices_->insertRow( insertRow);
			++insertRow;
		}
	}else{//最后一行非空IP
		if ( ip.empty() ) 
			insertRow = tableDevices_->rowCount()+1;
		else 
			insertRow = tableDevices_->rowCount();
	}
	NetConnBtn * connBtn = new NetConnBtn( ip );
	if ( insertRow > tableDevices_->rowCount()){
		tableDevices_->setRowCount(insertRow);  
	}
	connBtn->initTable(tableDevices_,  insertRow-1);
	newAddress("");
}

void DevicesWnd::deleteAddress( ){
}

void DevicesWnd::timerEvent ( QTimerEvent *  ){

	if ( logWnd_ && logWnd_->isVisible()){
		QDir dir("./log");
		QStringList list = dir.entryList();
		QBuffer buf;
		QTextStream stream(&buf);
		int start = 0;
		if (list.size() > 10){
			start = list.size() - 10;
		}
		QString text ;
		
		for ( size_t i = start; i < list.size(); ++i){
			QString & name = list[i];
			if ( name[0] != '.'){
				text.append(loadLog(name));
			}else{
				continue;
			}
		}
		text.replace("\r\n", "\n");

		if ( logtext_.size() != text.size() && logtext_ != text){
			logWnd_->clear();
			logWnd_->appendPlainText(text);
			logtext_ = text;
		}
	}
}
QString DevicesWnd::loadLog(QString &name){
	QFile file("./log/"+name);
	if ( file.open( QIODevice::ReadOnly)){
		return "======================================="+name+"=======================================\n"+file.readAll();
	}
}

void DevicesWnd::showLog(int val){
	QWidget * wdgt = findChild<QWidget*>( "tableDevices");
	if ( wdgt){
		if ( val){
			wdgt->setGeometry( wdgt->x(), wdgt->y(), this->width()-20, this->height()-280);
		}else{
			wdgt->setGeometry( wdgt->x(), wdgt->y(), this->width()-20, this->height()-80);
		}
	}
	QPlainTextEdit * pte = findChild<QPlainTextEdit*>( "log");
	if ( pte){
		pte->setVisible(val);
	}
}

void DevicesWnd::connectImpl( ){
}


void DevicesWnd::cellChanged(int row,int col){
	NetConnBtn* t = (NetConnBtn*)tableDevices_->cellWidget( row, 8);
	if ( !t) return;
	if (t->address_->text().isEmpty()){
		t->loc_->setText("");
		t->version_->setText("");
		t->desc_->setText("");
	}
	std::string ip = t->address_->text().toStdString();
	if ( t->text()=="Disconnect" && !ip.empty() && TcpNet::instance()->hasHost( ip)){
		Host* host = TcpNet::instance()->getHost(ip);
		switch(col){
		case 2:
			host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, t, _1), std::move(std::string("Set_Location ["+t->loc_->text().toStdString()+"]\r\n")) );
			break;
		case 3:
			host->addAsyncRequest( std::bind( &NetConnBtn::connectedCallback, t, _1), std::move(std::string("Set_Description ["+t->desc_->text().toStdString()+"]\r\n")) );
			break;
		}
	}
}

