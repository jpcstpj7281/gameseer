#ifndef Task_H
#define Task_H
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"
#include <wnd.h>


static size_t TimerEnd = 0xffffffff;
static size_t TimerGoto = 0xfffffffe;
static size_t TimerContinue = 0xfffffffd;


class Timer{
public:

	std::string modeid_;
	size_t second_;
	size_t counter_;
	size_t goto_;

	size_t currCounter_;
	size_t destMilliSecond_;

	void start();
	size_t run(size_t timer);
	void resetCounter(){ currCounter_=counter_;}
};

class Task {
	
	friend class TaskMgr;
	Task(const std::string & id);
	~Task();

	//void run( size_t timer);
	size_t currTimerIndex_;
public:
	std::vector<Timer*> timers_;
	std::string id_;
	std::string schedule_;
	bool isActivated_;

	void activate(bool flag){ isActivated_ = flag;}
	void resetTimerCounter();


};

class TaskMgr
{

	static  TaskMgr* inst;
	TaskMgr();

	friend class Task;
	std::vector<Task* > tasks_;
public:
	~TaskMgr();
	static TaskMgr *instance();

	//void run();
	Task* createTask();
	Task* createTask(const std::string & id);
	bool hasTask(const std::string & id);
	Task* getTask(const std::string &id);
	bool removeTask(Task*);
	std::vector<Task*> &getAllTasks(){ return  tasks_;};
};




#endif // Task_H
