#ifndef TIMERWND_H
#define TIMERWND_H

#include <QWidget>
#include <QTableWidget>
#include <stdint.h>
#include <TcpNet.h>
#include <QCalendarWidget>
#include <QDateTimeEdit.h>
#include <QPushButton>
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
		void clickOn();
		void clickOff();
		void click1();
		void click2();
		void click3();
		void click4();
		void click5();
		void click6();
		void click7();
		void click8();
public:

	QWidget				*channels_;
	QComboBox			*frequency_;
	QSpinBox			*interval_;
	QWidget				*ctrl_;
	QTableWidgetItem	*loc_;

	DateTimeWidget();
	~DateTimeWidget();
	void initTable( QTableWidget* table, int row);
	void refreshChannels();
	void shiftChannel( size_t chn);

	enum{
		Channel1=0,
		Channel2,
		Channel3,
		Channel4,
		Channel5,
		Channel6,
		Channel7,
		Channel8,
		ChannelAllOff,
		ChannelAllOn,
	};
	uint32_t buttonState_;
	uint32_t channelState_;
	QPushButton *btns_[16];
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
