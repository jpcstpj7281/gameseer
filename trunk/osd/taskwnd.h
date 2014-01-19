#ifndef TaskWnd_H
#define TaskWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <task.h>
#include <QPushButton>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <qspinbox.h>
#include <QVBoxLayout>

namespace Ui {
class TaskWnd;
}

class TimerWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();
		void activated ( const QString & text );
		void	gotoValueChanged ( int i );
		void	countValueChanged ( int i );
		void	timeChanged ( const QTime & time );
public:
	Task* task_;
	Timer* timer_;
	QTableWidgetItem* state_;
	QComboBox * mode_;
	QSpinBox * goto_;
	QTimeEdit * timeEdit_;
	QSpinBox * count_;
	QVBoxLayout* layout_;
	QPushButton* add_ ;
	QPushButton* remove_ ;

	TimerWidget(Task* task, Timer* timer);

	void initTable( QTableWidget* table, int row);
	virtual void	timerEvent ( QTimerEvent * event )override;
};

class TaskWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();
		void activeTask();
		void scheduleTask();
		void	dateTimeChanged ( const QDateTime & dateTime );

public:
	Task* task_;
	QTableWidgetItem* id_;
	QPushButton * activate_;
	QPushButton * schedule_;
	QDateTimeEdit * dateTimer_;

	TaskWidget(Task* task);
	virtual void	timerEvent ( QTimerEvent * event )override;
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
		
		void cellChanged(int,int);
private:
	void newTask( const std::wstring &ip);
	void resetTaskTable();
	void resetTimerTable( Task* task);

	virtual void	timerEvent ( QTimerEvent * event )override;

	Task* currTask_;

    Ui::TaskWnd *ui;
	QTableWidget*	taskTable_;
	QTableWidget*	timerTable_;
	
};

#endif // TaskWnd_H

