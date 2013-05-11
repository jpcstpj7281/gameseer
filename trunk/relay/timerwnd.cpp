#include "timerwnd.h"
#include "ui_TimerWnd.h"

#include <qdebug.h>

#include <QSpinBox>
#include <QTextCharFormat>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox.h>
#include "configmgr.h"


void DateTimeWidget::refreshChannels(){
	for ( size_t i = 0; i < ChannelShift::ChannelAllOff;++i){
		if ( buttonState_ & (1<<i) ){
			if ( channelState_& (1<<i) ){
				btns_[i]->setStyleSheet("* { background-color: lightGreen }");
			}else{
				btns_[i]->setStyleSheet("* { background-color: red }");
			}
		}else{
			btns_[i]->setStyleSheet("");
		}
	}
	if (buttonState_ & (1<<ChannelShift::ChannelAllOff)  ){
		btns_[ChannelShift::ChannelAllOff]->setStyleSheet("* { background-color: red }");
	}else{
		btns_[ChannelShift::ChannelAllOff]->setStyleSheet("");
	}
	if (buttonState_ & (1<<ChannelShift::ChannelAllOn) ){
		btns_[ChannelShift::ChannelAllOn]->setStyleSheet("* { background-color: lightGreen }");
	}else{
		btns_[ChannelShift::ChannelAllOn]->setStyleSheet("");
	}
	rt_->status = ((buttonState_ << 8) | channelState_);
}

void DateTimeWidget::clickOn(){
	buttonState_ = 1 << ChannelShift::ChannelAllOn;
	channelState_ = 0;
	refreshChannels();
}
void DateTimeWidget::clickOff(){
	buttonState_ = 1 << ChannelShift::ChannelAllOff;
	channelState_ = 0;
	refreshChannels();
}
void DateTimeWidget::shiftChannel( size_t chn){
	if ( buttonState_ & (3<<ChannelShift::ChannelAllOff)){
		buttonState_ &= (~(3<<ChannelShift::ChannelAllOff));
	}

	if ( buttonState_ & 1 << chn){//有状态
		if (channelState_ & 1<<chn){//开状态
			channelState_ &= (~(1<<chn));//设为关状态
		}else{
			buttonState_ &= (~(1 << chn));//设为无状态
		}
	}else{
		buttonState_ |= 1 << chn;//设为有状态
		channelState_ |=  1<<chn;//设为开状态
	}

	refreshChannels();
	
}
void DateTimeWidget::click1(){
	shiftChannel(ChannelShift::Channel1);
}
void DateTimeWidget::click2(){
	shiftChannel(ChannelShift::Channel2);
}
void DateTimeWidget::click3(){
	shiftChannel(ChannelShift::Channel3);
}
void DateTimeWidget::click4(){
	shiftChannel(ChannelShift::Channel4);
}
void DateTimeWidget::click5(){
	shiftChannel(ChannelShift::Channel5);
}
void DateTimeWidget::click6(){
	shiftChannel(ChannelShift::Channel6);
}
void DateTimeWidget::click7(){
	shiftChannel(ChannelShift::Channel7);
}
void DateTimeWidget::click8(){
	shiftChannel(ChannelShift::Channel8);
}

DateTimeWidget::DateTimeWidget(std::vector<RelayTimer> &rTimers):
	QDateTimeEdit()
	,channels_(new QPushButton)
	,ctrl_(new QWidget)
	,interval_(new  QSpinBox)
	,frequency_(new QComboBox)
	,loc_( new QTableWidgetItem)
	,buttonState_(0)
	,channelState_(0)
	,rTimers_(rTimers)
	,rt_(0)
{
	//this->setText( "Connect");

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
	//on->setStyleSheet("* { background-color: lightGreen }");
	//off->setStyleSheet("* { background-color: red }");
	on->setText("All");btns_[ChannelShift::ChannelAllOn] = on;
	off->setText("All");btns_[ChannelShift::ChannelAllOff] = off;
	btn1->setText("1");btns_[ChannelShift::Channel1] = btn1;
	btn2->setText("2");btns_[ChannelShift::Channel2] = btn2;
	btn3->setText("3");btns_[ChannelShift::Channel3] = btn3;
	btn4->setText("4");btns_[ChannelShift::Channel4] = btn4;
	btn5->setText("5");btns_[ChannelShift::Channel5] = btn5;
	btn6->setText("6");btns_[ChannelShift::Channel6] = btn6;
	btn7->setText("7");btns_[ChannelShift::Channel7] = btn7;
	btn8->setText("8");btns_[ChannelShift::Channel8] = btn8;
	for ( size_t i = 0; i <= ChannelShift::ChannelAllOn;++i){
		btns_[i]->setStyleSheet("");
	}
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
	channels_->setEnabled(true);


	//connect( this, SIGNAL(clicked()), this, SLOT(clickit()) );
	interval_->setMinimum( 0);
	interval_->setMaximum( 60);
	interval_->setValue(2);
	connect( interval_, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)) );

	frequency_->addItem( "Once");
	frequency_->addItem( "Every Day");
	frequency_->addItem( "Every Week");
	frequency_->addItem( "Every Month");
	frequency_->addItem( "Every Year");

	connect( frequency_, SIGNAL(currentIndexChanged(int)), this, SLOT(currentIndexChanged(int)) );

	connect( this, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(dateTimeChanged(const QDateTime &)) );
}

void	DateTimeWidget::dateTimeChanged ( const QDateTime & datetime ){
	if (rt_)rt_->dt = datetime;
}
void	DateTimeWidget::valueChanged ( int i ){
	if (rt_)rt_->delay = i;
}
void	DateTimeWidget::currentIndexChanged ( int index ){
	if (rt_) rt_->freq = index;
}

DateTimeWidget::~DateTimeWidget(){
}

void DateTimeWidget::clickInsert(){
	QTableWidget* table = loc_->tableWidget();
	//if ( loc_->row() != table->rowCount()-1 && table){
		DateTimeWidget * rowitem = new DateTimeWidget(rTimers_);
		rowitem->setDate( this->date());
		int row = loc_->row();
		table->insertRow( row);
		RelayTimer rt = *rt_;
		rTimers_.push_back(rt);
		rowitem->initTable(table, row, &rTimers_.back());
	//}
}
void DateTimeWidget::clickDelete(){
	QTableWidget* table = loc_->tableWidget();
	table->removeRow( loc_->row());
	for ( auto it = rTimers_.begin(); it!=rTimers_.end(); ++it){
		if ( rt_ == &(*it)){
			rTimers_.erase(it);
			break;
		}
	}
}
void DateTimeWidget::initTable( QTableWidget* table, int row, RelayTimer* rt){
	table->setCellWidget ( row, 0, ctrl_);
	table->setCellWidget ( row, 1, this );
	table->setCellWidget ( row, 2, frequency_ );
	table->setCellWidget ( row, 3, interval_ );
	table->setCellWidget ( row, 4, channels_ );
	table->setItem ( row, 5, loc_ );
	rt_ = rt;
	frequency_->setCurrentIndex(rt->freq);
	interval_->setValue( rt->delay);
	buttonState_ = rt->status >> 8;
	channelState_ = rt->status & 255;
	refreshChannels();
}

TimerWnd::TimerWnd(std::vector<RelayTimer> &rTimers, QString ip  ):
    QWidget(0)
	,ui(new Ui::TimerWnd)
	,rTimers_(rTimers)
	,ip_(ip)
{
    ui->setupUi(this);

	caldr_ = findChild<QCalendarWidget*>("calendarWidget");
	if ( caldr_){
		//QDate cdate=QDate::currentDate();   //获取今天的日期
		//QTextCharFormat format;     
		//format.setBackground(Qt::green);  //设置格式，颜色自选
		//caldr_->setDateTextFormat(cdate, format); //生效配置
		//QDate cdate=caldr_->selectedDate();

		connect( caldr_, SIGNAL(clicked( const QDate&)), this, SLOT(clickedDate( const QDate&)));
	}

	QPushButton *btnSave = findChild<QPushButton*>("btnSave");
	if ( btnSave){
		connect( btnSave, SIGNAL(clicked( )), this, SLOT(clickedSave()));
	}

	table_ = findChild<QTableWidget* >("tableWidget");
    table_->setColumnCount(6);

    QStringList sl;
	sl.push_back( "");
	sl.push_back( "Date Time");
	sl.push_back( "Frequency");
	sl.push_back( "SEQ Delay");
	sl.push_back( "Channels");
	sl.push_back( "");

    table_->setHorizontalHeaderLabels(sl );
	table_->setColumnWidth( 0, 20);
	table_->setColumnWidth( 1, 200);
	table_->setColumnWidth( 2, 100);
	table_->setColumnWidth( 3, 70);
	table_->setColumnWidth( 4, 300);
	table_->setColumnWidth( 5, 10);
	table_->hideColumn(5);

	QPushButton* btnAdd = findChild<QPushButton*>("btnAdd");
	if ( btnAdd){
		connect( btnAdd, SIGNAL(clicked()), this, SLOT(clickedAdd()));
	}
	QPushButton* btnClear = findChild<QPushButton*>("btnClear");
	if ( btnClear){
		connect( btnClear, SIGNAL(clicked()), this, SLOT(clickedClear()));
	}

	for ( auto it = rTimers_.begin(); it != rTimers_.end(); ++it){
		newDateTime( &(*it));
	}
}

void TimerWnd::clickedSave(){
	QDomElement root = ConfigMgr::instance()->getDoc()->documentElement();
	QDomNode timers = root.elementsByTagName("timers").at(0);
	QDomNodeList items = root.elementsByTagName("timer");
	while(items.size()>0){
		QDomNode node = items.at(0);
		QDomElement elem = node.toElement();
		if ( elem.attribute("ip") == ip_){
			timers.removeChild(node);
		}
	}

	for ( auto it = rTimers_.begin(); it!= rTimers_.end(); ++it){
		QDomElement elm = ConfigMgr::instance()->getDoc()->createElement( "timer");
		elm.setAttribute ("ip", ip_);
		elm.setAttribute( "delay", QString::number((*it).delay));
		elm.setAttribute( "freq", QString::number((*it).freq & ~(1<<24 /*以防把无关状态保存*/) ));
		elm.setAttribute( "datetime", (*it).dt.toString("yyyy.MM.dd hh:mm:ss") );
		elm.setAttribute( "status", QString::number((*it).status, 2) );
		timers.insertAfter( elm, QDomElement());
	}
	ConfigMgr::instance()->save();
}

void TimerWnd::clickedDate ( const QDate & date ){
	//qDebug()<<date;
}

TimerWnd::~TimerWnd()
{
    delete ui;
}

void TimerWnd::clearClicked(bool){
}
void TimerWnd::sendClicked(bool){
}


void TimerWnd::newDateTime(RelayTimer * rt){
	
	DateTimeWidget* dt = new DateTimeWidget(rTimers_);
	dt->setDateTime(rt->dt);
	table_->setRowCount(table_->rowCount()+1);
	dt->initTable( table_, table_->rowCount()-1, rt);
}

void TimerWnd::clickedAdd(){
	QDate cdate=caldr_->selectedDate();
	QDateTime dt;
	dt.setDate(cdate);
	RelayTimer rt ;
	rt.dt = dt;
	rt.freq = TriggerFreq::OneTime;
	rt.delay = 2;
	rt.status = 0;
	rTimers_.push_back(rt);

	newDateTime( &rTimers_.back() );
}
void TimerWnd::clickedClear(){
	table_->setRowCount(0);
	rTimers_.clear();
}
void TimerWnd::greenDate(){
	for ( int i = 0; i < table_->rowCount(); ++i){
		DateTimeWidget* dtw = (DateTimeWidget* )table_->cellWidget( i, 1);
		QDate dt= dtw->date();
		int freq = dtw->frequency_->currentIndex();
	}
}

void TimerWnd::whiteDate(){
	for ( int i = 0; i < table_->rowCount(); ++i){
		DateTimeWidget* dtw = (DateTimeWidget* )table_->cellWidget( i, 1);
		QDate dt= dtw->date();
		int freq = dtw->frequency_->currentIndex();
	}
}