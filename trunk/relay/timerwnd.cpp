#include "timerwnd.h"
#include "ui_TimerWnd.h"

#include <qdebug.h>

#include <QSpinBox>
#include <QTextCharFormat>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox.h>




DateTimeWidget::DateTimeWidget():
	QDateTimeEdit()
	,channels_(new QPushButton)
	,ctrl_(new QWidget)
	,interval_(new  QSpinBox)
	,frequency_(new QComboBox)
	,loc_( new QTableWidgetItem)
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
	on->setStyleSheet("* { background-color: lightGreen }");
	off->setStyleSheet("* { background-color: red }");
	on->setText("All");
	off->setText("All");
	btn1->setText("1");
	btn2->setText("2");
	btn3->setText("3");
	btn4->setText("4");
	btn5->setText("5");
	btn6->setText("6");
	btn7->setText("7");
	btn8->setText("8");
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


	//connect( this, SIGNAL(clicked()), this, SLOT(clickit()) );
	interval_->setMinimum( 0);
	interval_->setMaximum( 60);

	frequency_->addItem( "Every Day");
	frequency_->addItem( "Every Week");
	frequency_->addItem( "Every Month");
	frequency_->addItem( "Every Year");
}

DateTimeWidget::~DateTimeWidget(){
}

void DateTimeWidget::clickInsert(){
	QTableWidget* table = loc_->tableWidget();
	if ( loc_->row() != table->rowCount()-1 && table){
		DateTimeWidget * rowitem = new DateTimeWidget();
		rowitem->setDate( this->date());
		int row = loc_->row();
		table->insertRow( row);
		rowitem->initTable(table, row);
	}
}
void DateTimeWidget::clickDelete(){
	QTableWidget* table = loc_->tableWidget();
	if ( loc_->row() != table->rowCount()-1 && table){
		table->removeRow( loc_->row());
	}
}
void DateTimeWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, ctrl_);
	table->setCellWidget ( row, 1, this );
	table->setCellWidget ( row, 2, frequency_ );
	table->setCellWidget ( row, 3, interval_ );
	table->setCellWidget ( row, 4, channels_ );
	table->setItem ( row, 5, loc_ );
}

TimerWnd::TimerWnd( ):
    QWidget(0)
	,ui(new Ui::TimerWnd)
{
    ui->setupUi(this);

	caldr_ = findChild<QCalendarWidget*>("calendarWidget");
	if ( caldr_){
		//QDate cdate=QDate::currentDate();   //获取今天的日期
		//QTextCharFormat format;     
		//format.setBackground(Qt::green);  //设置格式，颜色自选
		//caldr_->setDateTextFormat(cdate, format); //生效配置
		//QDate cdate=caldr_->selectedDate();

		connect( caldr_, SIGNAL(	clicked( const QDate&)), this, SLOT(	clickedDate( const QDate&)));
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
		connect( btnAdd, SIGNAL(	clicked( )), this, SLOT(	clickedAdd( )));
	}
	QPushButton* btnClear = findChild<QPushButton*>("btnClear");
	if ( btnClear){
		connect( btnClear, SIGNAL(	clicked()), this, SLOT(	clickedClear( )));
	}
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


void TimerWnd::newDateTime(const QDate &cdate){
	DateTimeWidget* dt = new DateTimeWidget();
	dt->setDate(cdate);
	table_->setRowCount(table_->rowCount()+1);
	dt->initTable( table_, table_->rowCount()-1);
}

void TimerWnd::clickedAdd(){
	QDate cdate=caldr_->selectedDate();
	newDateTime( cdate);
}
void TimerWnd::clickedClear(){
	table_->setRowCount(0);
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