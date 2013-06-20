#ifndef Task_H
#define Task_H
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"
#include <wnd.h>

class Task {
	
	friend class TaskMgr;
	Task(const std::string & id);
	~Task();

public:
	std::string id_;
	
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

	Task* createTask();
	Task* createTask(const std::string & id);
	bool hasTask(const std::string & id);
	Task* getTask(const std::string &id);
	bool removeTask(Task*);
	std::vector<Task*> &getAllTasks(){ return  tasks_;};
};




#endif // Task_H
