#include "TaskWnd.h"
#include "ui_TaskWnd.h"
#include <qdebug.h>
#include "task.h"
#include "ring.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>



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
}
void TaskWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setItem ( row, 1, id_ );
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
{
    ui->setupUi(this);

	taskTable_ = findChild<QTableWidget* >("taskTable");
    taskTable_->setColumnCount( 4);
	QStringList sl;
	sl.push_back( "");
	sl.push_back( "ID");
	sl.push_back( "Activate");
	sl.push_back( "Save");

	taskTable_->setHorizontalHeaderLabels(sl );
	taskTable_->setColumnWidth( 0, 20);
	taskTable_->setColumnWidth( 1, 100);

	timerTable_ = findChild<QTableWidget* >("timerTable");

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );
}

TaskWnd::~TaskWnd()
{
    delete ui;
}
void TaskWnd::resetTaskTable(){
	taskTable_->setRowCount(0);
	newTask("");
	std::vector<Task*> tasks = TaskMgr::instance()->getAllTasks();
	for ( size_t i = 0 ; i <tasks.size(); ++i){
		newTask( tasks[i]->id_);
	}
}
void TaskWnd::currentTabChanged ( int index ){
	QTabWidget* tab = (QTabWidget*)sender();
	if (tab->tabText(index) == "Tasks"){
		resetTaskTable();
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

void TaskWnd::resetTimerTable( Task* task){
	currTask_ = task;
	timerTable_->setRowCount(0);
	if (task == NULL)return;

}