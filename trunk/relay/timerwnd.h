#ifndef TIMERWND_H
#define TIMERWND_H

#include <QWidget>
#include <QTableWidget>
#include <stdint.h>
#include <TcpNet.h>
#include <QCalendarWidget>
#include <QDateTimeEdit.h>
class QSpinBox;
class QComboBox;

struct TriggerFreq{
	enum Freq{
		EveryDate,
		EveryWeek,
		EveryMonth,
		EveryYear,
	};
};
class DateTimeWidget: public QDateTimeEdit{
	Q_OBJECT

	private slots:
		void clickInsert();
		void clickDelete();
public:

	QWidget				*channels_;
	QComboBox			*frequency_;
	QSpinBox			*interval_;
	QWidget				*ctrl_;
	QTableWidgetItem	*loc_;

	DateTimeWidget();
	~DateTimeWidget();
	void initTable( QTableWidget* table, int row);
};


namespace Ui {
class TimerWnd;
}

class TimerWnd : public QWidget
{
    Q_OBJECT
		private slots:

			void clickedDate ( const QDate & date );
			void clickedAdd();
			void clickedClear();
public:
    explicit TimerWnd( );
    ~TimerWnd();
    void newDateTime(const QDate &cdate);
	void greenDate();
	void whiteDate();

	private slots:
		void sendClicked(bool);
		void clearClicked(bool);
private:
    Ui::TimerWnd *ui;
	QTableWidget* table_;
	QCalendarWidget* caldr_;
};




#endif // TIMERWND_H
