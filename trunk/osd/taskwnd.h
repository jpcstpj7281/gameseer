#ifndef TaskWnd_H
#define TaskWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <task.h>
#include <mode.h>
#include <QPushButton>
#include <QTimeEdit>
#include <QDateTimeEdit>

namespace Ui {
class TaskWnd;
}

class TimerWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();

public:
	//Task* task_;
	//Timer* timer_;
	QTableWidgetItem* state_;
	QComboBox * mode_;
	QComboBox * goto_;
	QTimeEdit * timeEdit_;

	TimerWidget();//Task* task, Timer* timer);

	void initTable( QTableWidget* table, int row);
};

class TaskWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();
		void activeTask();
		void scheduleTask();
public:
	Task* task_;
	QTableWidgetItem* id_;
	QPushButton * activate_;
	QPushButton * schedule_;
	QDateTimeEdit * dateTimer_;

	TaskWidget(Task* task);

	void initTable( QTableWidget* table, int row);
};

class TaskWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void currentTabChanged ( int index );
			void cellClicked (int,int);
public:
    explicit TaskWnd(QWidget* parent);
    ~TaskWnd();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
private:
	void newTask( const std::string &ip);
	//void resetTaskTable();
	void resetTimerTable();

	//Task* currTask_;

    Ui::TaskWnd *ui;
	QTableWidget*	taskTable_;
	QTableWidget*	timerTable_;
	
};

#endif // TaskWnd_H

