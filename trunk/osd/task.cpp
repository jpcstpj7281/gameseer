#include "Task.h"
#include<QtDebug>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"
#include <Windows.h>
#include "mode.h"

Timer::Timer():destMilliSecond_(0)
	,second_(10)
	,goto_(0)
	,counter_(0)
	,currCounter_(0)
	
{
	
	auto ms = ModeMgr::instance()->getAllModes();
	if (ms.size()>0){
		modeid_ = ms[0]->id_;
	}
}
void Timer::start(){
	destMilliSecond_ = (GetTickCount()+((second_)*1000));
}
size_t Timer::run(size_t timer){
	if ( destMilliSecond_ != 0 ){
		if (destMilliSecond_ <= timer){
			destMilliSecond_ = 0;
			Mode* m = ModeMgr::instance()->getMode( modeid_);
			if(m){
				m->activate();
			}
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
	,isActivated_(false)
{
}
Task::~Task(){
	for( size_t i = 0 ; i < timers_.size(); ++i){
		delete timers_[i];
	}
}
void Task::run(size_t timer){
	if ( isActivated_){
		if ( timers_[currTimerIndex_]->destMilliSecond_ == 0){
			timers_[currTimerIndex_]->start();
		}
		size_t result = timers_[currTimerIndex_]->run(timer);
		if ( result == TimerGoto){
			currTimerIndex_ = timers_[currTimerIndex_]->goto_-1;
		}else if ( result == TimerEnd){
			if ( ++currTimerIndex_ < timers_.size()){
				while( currTimerIndex_){
					if (timers_[currTimerIndex_]->goto_> 0 ){
						if (timers_[currTimerIndex_]->currCounter_>0){
							break;
						}else{
							++currTimerIndex_;
							if ( currTimerIndex_ >= timers_.size()){
								currTimerIndex_ = 0;
								isActivated_ = false;
								break;
							}
						}
					}else if (timers_[currTimerIndex_]->counter_ > 0 ){
						if (timers_[currTimerIndex_]->currCounter_ ==0){
							++currTimerIndex_;
							if ( currTimerIndex_ >= timers_.size()){
								currTimerIndex_ = 0;
								isActivated_ = false;
								break;
							}
						}else	break;
					}else break;
				}
				
			}else{
				isActivated_ = false;
				currTimerIndex_= 0;
			}
		}
	}
}
void Task::resetTimerCounter(){
	for( size_t i = 0 ; i < timers_.size(); ++i){
		timers_[i]->resetCounter();
		if ( timers_[i]->goto_ > timers_.size()){
			timers_[i]->goto_ = timers_.size();
		}
	}
}
void Task::activate(bool flag){ 
	isActivated_ = flag;
	for( size_t i = 0 ; i < timers_.size(); ++i){
		timers_[i]->resetCounter();
		if ( timers_[i]->goto_ > timers_.size()){
			timers_[i]->goto_ = timers_.size();
		}
		timers_[i]->destMilliSecond_ = 0;
	}
	currTimerIndex_= 0;
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
	clear();
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
void TaskMgr::clear(){
	for ( auto i = tasks_.begin() ; i < tasks_.end(); ++i){
		delete *i;
	}
	tasks_.clear();
}
void TaskMgr::run(){
	for ( size_t i = 0; i < tasks_.size(); ++i){
		if ( tasks_[i]->isActivated_) tasks_[i]->run(GetTickCount());
	}
}