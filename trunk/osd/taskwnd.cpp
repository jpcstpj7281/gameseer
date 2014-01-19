#include "TaskWnd.h"
#include "ui_TaskWnd.h"
#include <qdebug.h>
#include "task.h"
#include "ring.h"
#include "mode.h"
#include <QPushButton>
#include <QMessageBox>
#include <qdatetime.h>
#include <Windows.h>

TimerWidget::TimerWidget(Task* task, Timer* timer):QWidget(0),task_(task), timer_(timer)
{
	layout_ = new QVBoxLayout();
	layout_->setMargin(0);
	layout_->setSpacing(0);
	add_ = new  QPushButton;
	remove_ = new  QPushButton;
	add_->setText("+");
	remove_->setText("-");
	layout_->addWidget(add_ );
	layout_->addWidget(remove_ );
	setLayout(layout_);
	connect( add_, SIGNAL(clicked()), this, SLOT(clickInsert()) );
	connect( remove_, SIGNAL(clicked()), this, SLOT(clickDelete()) );
	
	state_= new QTableWidgetItem();


	state_->setFlags( Qt::ItemIsEnabled );
	if ( task_){
		state_->setText("");
	}

	mode_ = new  QComboBox;
	connect( mode_, SIGNAL(activated ( const QString &  )), this, SLOT(activated ( const QString & )) );
	if ( !timer_){
		mode_->setEnabled(false);
	}else{
		auto ms = ModeMgr::instance()->getAllModes();
		for ( size_t i = 0; i < ms.size(); ++i){
			mode_->addItem(QString::fromStdWString(ms[i]->id_));
			if( timer_->modeid_ == ms[i]->id_){
				mode_->setCurrentIndex(i);
			}
		}
		if( mode_->currentText().isEmpty()){
			mode_->setCurrentIndex(0);
		}
	}
	goto_ = new  QSpinBox;
	connect( goto_, SIGNAL(valueChanged ( int  )), this, SLOT(gotoValueChanged ( int  )) );
	if ( !timer_){
		goto_->setEnabled(false);
	}else{
		goto_->setValue(timer->goto_);
	}
	timeEdit_ = new  QTimeEdit;
	connect( timeEdit_, SIGNAL(timeChanged ( const QTime & )), this, SLOT(timeChanged ( const QTime & )) );
	if ( !timer_){
		timeEdit_->setEnabled(false);
	}else{
		size_t h = timer_->second_ /3600;
		size_t m = timer_->second_/60 - h * 60;
		size_t s = timer_->second_ - h *3600 - m * 60;
		timeEdit_->setTime( QTime(h, m, s) );
	}
	count_ = new QSpinBox;
	count_->setMaximum(10000);
	connect( count_, SIGNAL(valueChanged ( int  )), this, SLOT(countValueChanged ( int  )) );
	if ( !timer){
		count_->setEnabled(false);
	}else{
		count_->setValue( timer->counter_);
	}

	this->startTimer(100);
}

void TimerWidget::timeChanged ( const QTime & time ){
	if (! task_->isActivated_)
		timer_->second_ = time.hour()*3600 + time.minute()*60+ time.second();
}

void TimerWidget::gotoValueChanged ( int i ){
	timer_->goto_ = i;
}
void TimerWidget::countValueChanged ( int i ){
	timer_->counter_ = i;
}
void TimerWidget::activated ( const QString & text ){
	auto ms = ModeMgr::instance()->getAllModes();
	for ( size_t i = 0; i < ms.size(); ++i){
		if( text.toStdWString() == ms[i]->id_){
			timer_->modeid_ =  ms[i]->id_;
			return;
		}
	}
	mode_->clear();
	for ( size_t i = 0; i < ms.size(); ++i){
		mode_->addItem(QString::fromStdWString(ms[i]->id_));
	}
	if ( ms.size()>0){
		mode_->setCurrentIndex(0);
		timer_->modeid_ = L"";
	}
}
void TimerWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setItem ( row, 1, state_ );
	table->setCellWidget ( row, 2, timeEdit_);
	table->setCellWidget ( row, 3, mode_);
	table->setCellWidget ( row, 4, goto_);
	table->setCellWidget ( row, 5, count_);
}
void TimerWidget::clickInsert(){
	QTableWidget* table = state_->tableWidget();
	if (  table && task_ ){
		int row = state_->row();
		Timer *t = new Timer;
		auto ms = ModeMgr::instance()->getAllModes();
		if ( ms.size() >0){
			t->modeid_ = ms[0]->id_;
		}else{
			t->modeid_ = L"";
		}
		task_->timers_.insert(row+ task_->timers_.begin(), t);
		TimerWidget * wgt = new TimerWidget(task_, t);
		table->insertRow( row);
		wgt->initTable(table, row);
	}
}
void TimerWidget::clickDelete(){
	QTableWidget* table = state_->tableWidget();
	if ( state_->row() != table->rowCount()-1 && table){
		if (task_ && timer_){
			for ( auto  i = task_->timers_.begin() ;  i != task_->timers_.end();++i ){
				if ( (*i) == timer_){
					delete timer_;
					task_->timers_.erase(i);
					table->removeRow( state_->row());
					break;
				}
			}
		}
	}
}
void TimerWidget::timerEvent ( QTimerEvent *  ){
	if ( task_&& timer_ && task_->isActivated_ ){
		mode_->setEnabled(false);
		goto_->setEnabled(false);
		timeEdit_->setEnabled(false);
		count_->setEnabled(false);
		add_->setEnabled(false);
		remove_->setEnabled(false);
		if (timer_ == task_->timers_[task_->currTimerIndex_]){
			if ( timer_->destMilliSecond_ ==0){
				size_t h = timer_->second_ /3600;
				size_t m = timer_->second_/60 - h * 60;
				size_t s = timer_->second_ - h *3600 - m * 60;
				timeEdit_->setTime( QTime(h, m, s) );
				state_->setBackground(Qt::white);
			}else{
				size_t sec = (timer_->destMilliSecond_ - GetTickCount())/1000;
				size_t h = sec /3600;
				size_t m = sec/60 - h * 60;
				size_t s = sec - h *3600 - m * 60;
				timeEdit_->setTime( QTime(h, m, s) );
				state_->setBackground(Qt::green);
			}
		}else{
			state_->setBackground(Qt::white);
		}
		count_->setValue( timer_->currCounter_);
	}else if (task_ &&timer_){
		mode_->setEnabled(true);
		goto_->setEnabled(true);
		timeEdit_->setEnabled(true);
		count_->setEnabled(true);
		add_->setEnabled(true);
		remove_->setEnabled(true);
		count_->setValue( timer_->counter_);
		//state_->setBackground(Qt::white);
	}

	if (task_&& task_->isActivated_){
		add_->setEnabled(false);
		remove_->setEnabled(false);
	}else if (task_){
		add_->setEnabled(true);
		remove_->setEnabled(true);
	}
}
//==============================================================================================================================
TaskWidget::TaskWidget(Task* task):QWidget(0),task_(task)
{
	QVBoxLayout* layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->setSpacing(0);
	QPushButton* add = new  QPushButton;
	QPushButton* remove = new  QPushButton;
	add->setText("+");
	remove->setText("-");
	layout->addWidget(add );
	layout->addWidget(remove );
	setLayout(layout);
	connect( add, SIGNAL(clicked()), this, SLOT(clickInsert()) );
	connect( remove, SIGNAL(clicked()), this, SLOT(clickDelete()) );

	id_= new QTableWidgetItem();


	id_->setFlags( Qt::ItemIsEnabled | Qt::ItemIsEditable);

	if ( task_){
		id_->setText( QString::fromStdWString(task_->id_));
	}

	activate_ = new  QPushButton;
	activate_->setText(tr("Activate"));
	activate_->setStyleSheet("");
	connect( activate_, SIGNAL(clicked()), this, SLOT(activeTask()) );
	if ( !task_){
		activate_->setEnabled(false);
	}
	schedule_ = new  QPushButton;
	schedule_->setText(tr("Schedule"));
	schedule_->setStyleSheet("");
	connect( schedule_, SIGNAL(clicked()), this, SLOT(scheduleTask()) );
	if ( !task_){
		schedule_->setEnabled(false);
	}
	dateTimer_ = new  QDateTimeEdit(QDateTime::currentDateTime().addSecs(3600));
	connect( dateTimer_, SIGNAL(dateTimeChanged( const QDateTime &)), this, SLOT(dateTimeChanged ( const QDateTime & )) );
	if ( !task_){
		dateTimer_->setEnabled(false);
	}
	this->startTimer( 200);
}
void TaskWidget::dateTimeChanged ( const QDateTime & dateTime ){
	task_->schedule_ = dateTime.toString("yyyy.MM.dd-hh:mm:ss").toStdString();
}
void TaskWidget::activeTask(){
	if ( task_){
		if ( task_->isActivated_){
			task_->activate(false);
			activate_->setStyleSheet("");
		}else if( task_->timers_.size() > 0){
			//task_->resetTimerCounter();
			task_->activate(true);
			activate_->setStyleSheet("* { background-color: lightGreen }");
		}
	}
}
void TaskWidget::scheduleTask(){
	if ( task_){
		if ( schedule_->styleSheet().isEmpty()){
			schedule_->setStyleSheet("* { background-color: lightGreen }");
		}else{
			schedule_->setStyleSheet("");
		}
	}
}

void TaskWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setItem ( row, 1, id_ );
	table->setCellWidget ( row, 2, activate_);
	table->setCellWidget ( row, 3, schedule_);
	table->setCellWidget ( row, 4, dateTimer_);
}
void TaskWidget::clickInsert(){
	QTableWidget* table = id_->tableWidget();
	if (  table){
		Task* task = TaskMgr::instance()->createTask();
		QDateTime dt = QDateTime::currentDateTime();
		task->schedule_ = dateTimer_->dateTime().toString("yyyy.MM.dd-hh:mm:ss").toStdString();
		TaskWidget * wgt = new TaskWidget(  task);
		int row = id_->row();
		table->insertRow( row);
		wgt->initTable(table, row);
	}
}
void TaskWidget::clickDelete(){
	QTableWidget* table = id_->tableWidget();
	if ( id_->row() != table->rowCount()-1 && table){
		if (task_){
			TaskMgr::instance()->removeTask(task_);
		}
		table->removeRow( id_->row());
	}
}
void TaskWidget::timerEvent ( QTimerEvent *  ){
	if ( !schedule_->styleSheet().isEmpty() && task_){
		QString sch = QString::fromStdString(task_->schedule_);
		QDateTime dt = QDateTime::currentDateTime();
		if ( dt >= QDateTime::fromString( sch, "yyyy.MM.dd-hh:mm:ss") && dt <= QDateTime::fromString( sch, "yyyy.MM.dd-hh:mm:ss").addSecs(10)){
			schedule_->setStyleSheet("");
			if (!task_->isActivated_){
				task_->activate(true);
			}
			std::vector<Task*> & tasks = TaskMgr::instance()->getAllTasks();
			for ( size_t i = 0; i < tasks.size(); ++i){
				if ( tasks[i] != task_){
					tasks[i]->activate(false);
				}
			}
		}
	}
	
	if ( task_ && !task_->isActivated_ && !activate_->styleSheet().isEmpty() ){
		activate_->setStyleSheet("");
	}
}
//==============================================================================================================================
TaskWnd::TaskWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::TaskWnd)
	,currTask_(0)
{
    ui->setupUi(this);

	taskTable_ = findChild<QTableWidget* >("taskTable");
    taskTable_->setColumnCount( 5);
	QStringList sl;
	sl.push_back( "");
	sl.push_back( "ID");
	sl.push_back( tr("Activate"));
	sl.push_back( tr("Schedule"));
	sl.push_back( tr("Timer"));

	taskTable_->setHorizontalHeaderLabels(sl );
	taskTable_->setColumnWidth( 0, 20);
	taskTable_->setColumnWidth( 1, 80);
	taskTable_->setColumnWidth( 2, 60);
	taskTable_->setColumnWidth( 3, 60);
	taskTable_->setColumnWidth( 4, 150);

	timerTable_ = findChild<QTableWidget* >("timerTable");
    timerTable_->setColumnCount( 6);
	sl.clear();
	sl.push_back( "");
	sl.push_back( tr("State"));
	sl.push_back( tr("Timer"));
	sl.push_back( tr("Mode"));
	sl.push_back( tr("Goto"));
	sl.push_back( tr("Count"));

	timerTable_->setHorizontalHeaderLabels(sl );
	timerTable_->setColumnWidth( 0, 20);
	timerTable_->setColumnWidth( 1, 80);
	timerTable_->setColumnWidth( 2, 80);
	timerTable_->setColumnWidth( 3, 80);
	timerTable_->setColumnWidth( 4, 80);
	timerTable_->setColumnWidth( 5, 80);

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );

	connect(taskTable_, SIGNAL(cellClicked(int,int)), this, SLOT(cellClicked (int,int)) );

	connect(taskTable_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged (int,int)) );
	startTimer(200);
}

TaskWnd::~TaskWnd()
{
    delete ui;
}

void TaskWnd::cellClicked(int row,int ){
	TaskWidget * wgt = 0;
	timerTable_->setRowCount(0);
	if ( taskTable_->rowCount()>0){
		wgt= (TaskWidget*) taskTable_->cellWidget( row, 0);
		if ( wgt && wgt->task_)
			resetTimerTable( wgt->task_);
	}
}


void TaskWnd::resetTaskTable(){
	taskTable_->setRowCount(0);
	newTask(L"");
	std::vector<Task*> tasks = TaskMgr::instance()->getAllTasks();
	for ( size_t i = 0 ; i <tasks.size(); ++i){
		newTask( tasks[i]->id_);
	}
}
void TaskWnd::resetTimerTable( Task* task){
	currTask_ = task;
	timerTable_->setRowCount(0);
	if ( !currTask_) return;
	
	timerTable_->setRowCount(currTask_->timers_.size()+1);
	for ( size_t i = 0 ; i <currTask_->timers_.size(); ++i){
		TimerWidget* wgt = new TimerWidget(currTask_, currTask_->timers_[i]);
		wgt->initTable( timerTable_, i);
	}
	TimerWidget* wgt = new TimerWidget(currTask_, NULL);
	wgt->initTable(timerTable_, currTask_->timers_.size());
}
void TaskWnd::currentTabChanged ( int index ){
	QTabWidget* tab = (QTabWidget*)sender();
	if (tab->tabText(index) == tr("Tasks")){
		resetTaskTable();
		resetTimerTable(currTask_);
	}
}

void TaskWnd::newTask( const std::wstring &taskid){
	TaskWidget * wgt = 0;
	if ( taskTable_->rowCount()>0){
		wgt= (TaskWidget*) taskTable_->cellWidget( taskTable_->rowCount()-1, 0);
	}
	int insertRow = 0;
	if ( wgt==0 ){
		insertRow = 1;
	}else if (wgt->id_->text().isEmpty()  ){
		if ( taskid.empty() ) return;	//无需操作
		else {
			insertRow = taskTable_->rowCount()-1;//在空行前插入
			taskTable_->insertRow( insertRow);
			++insertRow;
		}
	}else{//最后一行非空IP
		if ( taskid.empty() ) 
			insertRow = taskTable_->rowCount()+1;
		else 
			insertRow = taskTable_->rowCount();
	}

	if (TaskMgr::instance()->hasTask(taskid)){
		wgt = new TaskWidget( TaskMgr::instance()->getTask(taskid) );
	}else if ( !taskid.empty()  ){
		wgt = new TaskWidget( TaskMgr::instance()->createTask(taskid) );
	}else{
		wgt = new TaskWidget(NULL);
	}

	if ( insertRow > taskTable_->rowCount()){
		taskTable_->setRowCount(insertRow);  
	}
	wgt->initTable(taskTable_,  insertRow-1);
}

void TaskWnd::timerEvent ( QTimerEvent *  ){
	TaskMgr::instance()->run();
}

void TaskWnd::cellChanged(int row,int col){
	if ( col == 1){
		TaskWidget * wgt = (TaskWidget*)taskTable_->cellWidget( row, 0);
		if ( wgt->task_){
			wgt->task_->id_ = wgt->id_->text().toStdWString();
			return;
		}
	}
}