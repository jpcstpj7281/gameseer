#ifndef TaskWnd_H
#define TaskWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <task.h>

namespace Ui {
class TaskWnd;
}


class TaskWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();
public:
	Task* task_;
	QTableWidgetItem* id_;

	TaskWidget(Task* task);

	void initTable( QTableWidget* table, int row);
};

class TaskWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void currentTabChanged ( int index );
public:
    explicit TaskWnd(QWidget* parent);
    ~TaskWnd();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
private:
	void newTask( const std::string &ip);
	void resetTaskTable();
	void resetTimerTable( Task* task);

	Task* currTask_;

    Ui::TaskWnd *ui;
	QTableWidget*	taskTable_;
	QTableWidget*	timerTable_;
	
};

#endif // TaskWnd_H

