#include "Task.h"
#include<QtDebug>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"
#include <Windows.h>
void Timer::start(){
	destMilliSecond_ = GetTickCount()+second_*1000;
}
size_t Timer::run(size_t timer){
	if ( destMilliSecond_ != 0 ){
		if (destMilliSecond_ >= timer){
			if ( currCounter_ > 0){
				--currCounter_ ;
				return TimerGoto;
			}else{
				return TimerEnd;
			}
		}else{
			return destMilliSecond_ - timer;
		}
	}else{
		return TimerContinue;
	}
}
//=======================================================================================================================
Task::Task(const std::string & id):id_(id)
	,currTimerIndex_(0)
{
}
Task::~Task(){
	for( size_t i = 0 ; i < timers_.size(); ++i){
		delete timers_[i];
	}
}
//void Task::run(size_t timer){
//	if ( isActivated_){
//		timers_[currTimerIndex_]->run(timer);
//	}
//}
void Task::resetTimerCounter(){
	for( size_t i = 0 ; i < timers_.size(); ++i){
		timers_[i]->resetCounter();
	}
}
//=======================================================================================================================
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
	for( size_t i = 0 ; i < tasks_.size(); ++i){
		delete tasks_[i];
	}
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

//void TaskMgr::run(){
//	for ( size_t i = 0; i < tasks_.size(); ++i){
//		tasks_[i]->run(GetTickCount());
//	}
//}