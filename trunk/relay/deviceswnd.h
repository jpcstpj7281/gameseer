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
#include "timerwnd.h"
class QSpinBox;
class TestQbox;
class QComboBox;
class QLabel;
namespace Ui {
class DevicesWnd;
class MainWindow;
}

class NetConnBtn: public QPushButton{
	Q_OBJECT

	private slots:
		void clickit();
		void clickTest();
		void clickInsert();
		void clickDelete();
		void clickTimer();
public:
	QTableWidgetItem	*loc_;
	QTableWidgetItem	*desc_;
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

	void conn();
	void disconn();
	NetConnBtn(  const std::string & ip);
	~NetConnBtn();
	bool connectedCallback( const std::string &msg);
	void initTable( QTableWidget* table, int row);
};

class DevicesWnd : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();
	void initAddresses();

private slots:

	void itemClicked(QTableWidgetItem *);
	void cellChanged(int,int);
	void disconnAll();
	void connAll();
	void stateChanged(int);

private:
	void connectImpl( );
	void disconnectImpl( );

	virtual void	timerEvent ( QTimerEvent * event )override;
	void newAddress(const std::string &ip);
	void deleteAddress(); 

	QTableWidget*				tableDevices_;
    Ui::DevicesWnd *ui;

	friend class QboxAddress;

};

#endif // DEVICESWND_H
