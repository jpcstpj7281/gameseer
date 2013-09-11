#include "TaskWnd.h"
#include "ui_TaskWnd.h"
#include <qdebug.h>
#include "task.h"
#include "ring.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

TimerWidget::TimerWidget(Task* task, Timer* timer):QWidget(0),task_(task), timer_(timer)
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

	state_= new QTableWidgetItem();


	state_->setFlags( Qt::ItemIsEnabled );
	if ( task_){
		state_->setText("");
	}

	mode_ = new  QComboBox;
	//connect( activate_, SIGNAL(clicked()), this, SLOT(activeTask()) );
	if ( !timer_){
		mode_->setEnabled(false);
	}
	goto_ = new  QComboBox;
	//connect( schedule_, SIGNAL(clicked()), this, SLOT(scheduleTask()) );
	if ( !timer_){
		goto_->setEnabled(false);
	}
	timeEdit_ = new  QTimeEdit;
	if ( !timer_){
		timeEdit_->setEnabled(false);
	}
}
void TimerWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setItem ( row, 1, state_ );
	table->setCellWidget ( row, 2, timeEdit_);
	table->setCellWidget ( row, 3, mode_);
	table->setCellWidget ( row, 4, goto_);
}
void TimerWidget::clickInsert(){
	QTableWidget* table = state_->tableWidget();
	if (  table && task_ ){
		int row = state_->row();
		Timer *t = new Timer;
		t->modeid_ = "-";
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
			//TaskMgr::instance()->removeTask(task_);
			for ( auto  i = task_->timers_.begin() ;  i != task_->timers_.end(); ++i){
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


	id_->setFlags( Qt::ItemIsEnabled );

	if ( task_){
		id_->setText( QString::fromStdString(task_->id_));
	}

	activate_ = new  QPushButton;
	activate_->setText("Activate");
	connect( activate_, SIGNAL(clicked()), this, SLOT(activeTask()) );
	if ( !task_){
		activate_->setEnabled(false);
	}
	schedule_ = new  QPushButton;
	schedule_->setText("Schedule");
	connect( schedule_, SIGNAL(clicked()), this, SLOT(scheduleTask()) );
	if ( !task_){
		schedule_->setEnabled(false);
	}
	dateTimer_ = new  QDateTimeEdit;
	//connect( dateTimer_, SIGNAL(clicked()), this, SLOT(scheduleTask()) );
	if ( !task_){
		dateTimer_->setEnabled(false);
	}
}

void TaskWidget::activeTask(){
	if ( task_){
		task_->activate();
	}
}
void TaskWidget::scheduleTask(){
	if ( task_){
		task_->schedule();
		schedule_->setStyleSheet("* { background-color: lightGreen }");
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
	sl.push_back( "Activate");
	sl.push_back( "Schedule");
	sl.push_back( "Timer");

	taskTable_->setHorizontalHeaderLabels(sl );
	taskTable_->setColumnWidth( 0, 20);
	taskTable_->setColumnWidth( 1, 80);
	taskTable_->setColumnWidth( 2, 60);
	taskTable_->setColumnWidth( 3, 60);
	taskTable_->setColumnWidth( 4, 150);

	timerTable_ = findChild<QTableWidget* >("timerTable");
    timerTable_->setColumnCount( 5);
	sl.clear();
	sl.push_back( "");
	sl.push_back( "State");
	sl.push_back( "Timer");
	sl.push_back( "Mode");
	sl.push_back( "Goto");

	timerTable_->setHorizontalHeaderLabels(sl );
	timerTable_->setColumnWidth( 0, 20);
	timerTable_->setColumnWidth( 1, 80);
	timerTable_->setColumnWidth( 2, 80);
	timerTable_->setColumnWidth( 3, 80);
	timerTable_->setColumnWidth( 4, 150);


	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );

	connect(taskTable_, SIGNAL(cellClicked(int,int)), this, SLOT(cellClicked (int,int)) );
}

TaskWnd::~TaskWnd()
{
    delete ui;
}

void TaskWnd::cellClicked(int row,int col){
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
	newTask("");
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
	if (tab->tabText(index) == "Tasks"){
		resetTaskTable();
		resetTimerTable(currTask_);
	}
}

void TaskWnd::newTask( const std::string &taskid){
	TaskWidget * wgt = 0;
	if ( taskTable_->rowCount()>0){
		wgt= (TaskWidget*) taskTable_->cellWidget( taskTable_->rowCount()-1, 0);
	}
	int insertRow = 0;
	if ( wgt==0 ){
		insertRow = 1;
	}else if (wgt->id_->text().isEmpty()  ){//最后一行已经是空IP
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

