#include "Task.h"
#include<QtDebug>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

Task::Task(const std::string & id):id_(id)
{
}
Task::~Task(){
}

TaskMgr* TaskMgr::inst = 0;
TaskMgr *TaskMgr::instance(){
	if ( inst) return inst;
	return inst = new TaskMgr();
}
TaskMgr::TaskMgr()
{
}
TaskMgr::~TaskMgr()
{
}
Task* TaskMgr::createTask(const std::string & id){
	if ( hasTask(id)) return NULL;
	tasks_.push_back(new Task(id));
	return tasks_.back();
}
Task* TaskMgr::createTask(){
	for ( size_t i = 0 ; i < 0xFFFFFFFF; ++i){
		std::string str = "Task";
		std::string num = QString::number(i+1).toStdString();
		if (!hasTask(str + num)){
			tasks_.push_back( new Task(str+num));
			return tasks_.back();
		}
	}
	return NULL;
}
bool TaskMgr::hasTask(const std::string & id){
	return getTask(id) ;
}
Task* TaskMgr::getTask(const std::string &id){
	for ( size_t i = 0 ; i < tasks_.size(); ++i){
		if (tasks_[i]->id_ == id) return tasks_[i];
	}
	return NULL;
}
bool TaskMgr::removeTask(Task* mode){
	for ( auto i = tasks_.begin() ; i < tasks_.end(); ++i){
		if (*i == mode) {
			delete mode;
			tasks_.erase(i);
			return true;
		}
	}
	return false; 
}