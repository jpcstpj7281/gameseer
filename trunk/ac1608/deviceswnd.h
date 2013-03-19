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
class DevicesWnd;

typedef std::function< int (int, int, Ac1608Address*) > AddressCallback;

//static const char* CONNECT_STR = "Connect";
//static const char* DISCONNECT_STR = "Disconnect";

class Ac1608Address: public QObject{
	Q_OBJECT
private slots:
	void editingAddressFinished ();
public:
	Ac1608Address( QString &ip , QString & loc):
	snmpResponseTime(0)
	,row(0),ip(ip)
	,location(loc)
	,startCheckTime(0)
	,t_(0)
	,lineEdit_(0){
	}

	void init(QLineEdit* lineEdit, DevicesWnd* t){ 
		this->t_ = t;
		this->lineEdit_ = lineEdit;
		connect( lineEdit, SIGNAL(editingFinished ()), this, SLOT(editingAddressFinished ()));
	}
	size_t row;
	volatile size_t snmpResponseTime;
	size_t startCheckTime;
	QString ip;
	QString location;
	QLineEdit* lineEdit_;
	DevicesWnd* t_;

	int psw_[4];
	QString pswOid_[4];
	int pswCount_;

	volatile size_t timeticks;
	char deviceRunTime[32];
	
	//AddressCallback callback;
};


class DevicesWnd : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();


	//void refresh();
	void initAddresses();
	
	typedef std::map< QString, Ac1608Address* > AddressMap;
private slots:
	void editingNewAddressFinished ();
	void itemClicked(QTableWidgetItem *);
	void cellChanged(int,int);
	void	cellActivated ( int row, int column );
	void	cellEntered ( int row, int column );


private:

	void connectImpl( Ac1608Address*);
	void disconnectImpl( Ac1608Address*);

	virtual void	timerEvent ( QTimerEvent * event )override;

	QLineEdit * lastLineEdit_;

	void newAddress(Ac1608Address * aa = NULL);

	AddressMap addresses_;
	Ac1608Address* currConnAddress_;

	QTableWidget*				tableDevices_;

    Ui::DevicesWnd *ui;

	SnmpCallback::RequestStatus checkAddressCallback( int , snmp_session*, snmp_pdu*, SnmpObj*);
	void onlineRefreshed(Ac1608Address * aa);
	void offlineRefreshed(Ac1608Address * aa);
	void checkingRefreshed(Ac1608Address * aa);
	QMutex locker_;

	friend class Ac1608Address;
};

#endif // DEVICESWND_H
