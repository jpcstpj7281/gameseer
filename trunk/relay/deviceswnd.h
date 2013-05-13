#ifndef DEVICESWND_H
#define DEVICESWND_H


#include <QWidget>
#include <map>
#include <QTableWidget>

#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <functional>
#include <QPushButton.h>
#include <QMainWindow>
#include <vector>
#include "timerwnd.h"
#include "log4qt/logger.h"
class QSpinBox;
class TestQbox;
class QComboBox;
class QLabel;
namespace Ui {
class DevicesWnd;
class MainWindow;
}

struct Logger{
};

class NetConnBtn: public QPushButton{
	Q_OBJECT

		void channelChange(const std::string& chn, QPushButton*);
	virtual void	timerEvent ( QTimerEvent * event )override;

	
	enum WaitForState{
		WaitNothing,
		WaitAllOff,
		WaitAllOn,
		WaitTime,
	};
	WaitForState waitForState_;
	private slots:
		void clickit();
		void clickTest();
		void clickInsert();
		void clickDelete();
		void clickTimer();
		void editFinished();
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

	void onAll(int interval);
	void offAll(int interval);

	QTableWidgetItem	*loc_;
	QTableWidgetItem	*desc_;
	QTableWidgetItem	*version_;
	QTableWidgetItem	*runTime_;
	QTableWidgetItem	*status_;
	QTableWidgetItem	*model_;
	QLineEdit			*address_;
	QWidget				*channels_;
	QPushButton			*testBtn_;
	QPushButton			*timer_;
	QSpinBox			*interval_;
	QWidget				*ctrl_;

	TestQbox			*testNet_;
	TimerWnd			*timerwnd_;

	QPushButton			*btns_[16];

	size_t				tickcount_;
	size_t				disconnTickCount_;
	size_t				waitTime_;

	void conn();
	void disconn();
	NetConnBtn(  const std::string & ip);
	~NetConnBtn();
	bool connectedCallback( const std::string &msg);
	bool incommingCallback( const std::string& msg);
	void initTable( QTableWidget* table, int row);

	//std::vector<QDateTime> dTimes_;
	//std::vector<int> triggerFreqs_;
	//std::vector<size_t> btnStatus_;
	//std::vector<size_t> delays_;
	std::vector<RelayTimer> rTimers_;
	void initTimer();
	void calcTimer(RelayTimer* rt);
	void switchBtn(RelayTimer* rt);

	std::list<std::string> ongoingCmd_;
	std::list<size_t> ongoingDelay_;
};

class DevicesWnd : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();
	void initAddresses();

private slots:

	//void itemClicked(QTableWidgetItem *);
	void cellChanged(int,int);
	void disconnAll();
	void connAll();
	void stateChanged(int);
	void runOnStartup(int);

	void valueChanged( int i );
	void onAll();
	void offAll();

private:
	void connectImpl( );
	void disconnectImpl( );
	void closeEvent(QCloseEvent * event)override;
	virtual void	timerEvent ( QTimerEvent * event )override;
	void newAddress(const std::string &ip);
	void deleteAddress(); 

	QTableWidget*				tableDevices_;
    Ui::DevicesWnd *ui;

	size_t	interval_;

	friend class QboxAddress;

};

#endif // DEVICESWND_H
