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


const static char* DATETIME_STRING = "yyyy.MM.dd hh:mm:ss";

struct TriggerFreq{
	enum Freq{
		OneTime,
		EveryDate,
		EveryWeek,
		EveryMonth,
		EveryYear,
	};
};

struct ChannelShift{
enum {
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
};

struct RelayTimer{
	RelayTimer():
		delay(0)
		,freq(0)
		,status(0)
	{}
	RelayTimer(const RelayTimer &rt):
	dt(rt.dt)
		,delay(rt.delay)
		,freq(rt.freq)
		,status(rt.status)
		,comment(rt.comment)
	{}
	std::string dt;
	size_t delay;
	size_t freq;
	size_t status;
	std::string comment;
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
		void	currentIndexChanged ( int index );
		void	valueChanged ( int i );
		void	dateTimeChanged ( const QDateTime & datetime );
public:

	QWidget				*channels_;
	QComboBox			*frequency_;
	QSpinBox			*interval_;
	QWidget				*ctrl_;
	QTableWidgetItem	*comm_;

	DateTimeWidget(std::vector<RelayTimer*> *rTimers);
	~DateTimeWidget();
	void initTable( QTableWidget* table, int row, RelayTimer* rt);
	void refreshChannels();
	void shiftChannel( size_t chn);

	
	uint32_t buttonState_;
	uint32_t channelState_;
	QPushButton *btns_[16];
	RelayTimer* rt_;
	std::vector<RelayTimer*> *rTimers_;
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
			void clickedSave();
			void cellChanged(int,int);

public:
	explicit TimerWnd(std::vector<RelayTimer*> *rTimers, QString ip );
	~TimerWnd();
	void newDateTime(RelayTimer * rt);
	void greenDate();
	void whiteDate();

	std::vector<RelayTimer*> *rTimers_;
	QString ip_;

	private slots:
		void sendClicked(bool);
		void clearClicked(bool);
private:
    Ui::TimerWnd *ui;
	QTableWidget* table_;
	QCalendarWidget* caldr_;

	
};




#endif // TIMERWND_H
