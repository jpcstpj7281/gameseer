#ifndef DEVICESWND_H
#define DEVICESWND_H

#include <QWidget>
#include <map>
#include <QTableWidget>

#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <functional>
#include <Snmpnet.h>

#include <QMutex>


namespace Ui {
class DevicesWnd;
}
class Ac1608Address;

typedef std::function< int (int, int, Ac1608Address*) > AddressCallback;

//static const char* CONNECT_STR = "Connect";
//static const char* DISCONNECT_STR = "Disconnect";

class Ac1608Address: public QObject{
	Q_OBJECT
private slots:
	void editingFinished ();
public:
	Ac1608Address( QString &ip , QString & loc):
	snmpResponseTime(0)
	,row(0),ip(ip)
	,location(loc)
	,startCheckTime(0){
	}

	void init(int row, AddressCallback callback, QLineEdit* lineEdit){ 
		this->callback = callback;
		this->row = row;

		this->lineEdit =  lineEdit;
		connect( lineEdit, SIGNAL(editingFinished ()), this, SLOT(editingFinished ()));
	}
	size_t row;
	volatile size_t snmpResponseTime;
	size_t startCheckTime;
	QString ip;
	QString location;
	char deviceRunTime[32];
	QLineEdit* lineEdit;
	AddressCallback callback;
};


class DevicesWnd : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();


	void refresh();
	void initAddresses();

	typedef std::map< QString, Ac1608Address* > AddressMap;
private slots:
	void editingFinished ();
	void itemClicked(QTableWidgetItem *);
	void cellChanged(int,int);
	void	cellActivated ( int row, int column );
	void	cellEntered ( int row, int column );


private:

	void connectImpl( Ac1608Address*);
	void disconnectImpl( Ac1608Address*);

	virtual void	timerEvent ( QTimerEvent * event );

	QLineEdit * lastLineEdit_;

	void newAddress(Ac1608Address * aa = NULL);

	AddressMap addresses_;
	Ac1608Address* currConnAddress_;

	QTableWidget*				tableDevices_;

    Ui::DevicesWnd *ui;

	SnmpCallback::RequestStatus checkAddressCallback( int , snmp_session*, snmp_pdu*, SnmpObj*);

	QMutex locker_;
};

#endif // DEVICESWND_H
