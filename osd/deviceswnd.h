#ifndef DEVICESWND_H
#define DEVICESWND_H

#include <QWidget>
#include <map>
#include <QTableWidget>

#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <functional>

#include <QMutex>


namespace Ui {
class DevicesWnd;
}
class QboxAddress;
class DevicesWnd;

typedef std::function< int (int, int, QboxAddress*) > AddressCallback;

class QboxAddress: public QObject{
	Q_OBJECT
private slots:
	void editingAddressFinished ();
public:
	QboxAddress( QString &ip , QString & loc):
	snmpResponseTime(0)
	,row(0),ip(ip)
	,location(loc)
	,startCheckTime(0)
	,t_(0)
	,lineEdit_(0)
	,pswCount_(0){
		memset(psw_, 0, 16);
		memset(inputPsw_, 0, 16);
	}

	void init(QLineEdit* lineEdit, DevicesWnd* t){ 
		this->t_ = t;
		this->lineEdit_ = lineEdit;
		connect( lineEdit, SIGNAL(editingFinished ()), this, SLOT(editingAddressFinished ()));
	}
	bool valiatePassword();
	size_t row;
	volatile size_t snmpResponseTime;
	size_t startCheckTime;
	QString ip;
	QString location;
	QLineEdit* lineEdit_;
	DevicesWnd* t_;

	int psw_[4];
	int inputPsw_[4];
	volatile int pswCount_;

	volatile size_t timeticks;
	//char deviceRunTime[32];
	
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
	
	typedef std::map< QString, QboxAddress* > AddressMap;
private slots:
	void editingNewAddressFinished ();
	void itemClicked(QTableWidgetItem *);
	void cellChanged(int,int);


private:

	void connectImpl( QboxAddress*);
	void disconnectImpl( QboxAddress*);

	virtual void	timerEvent ( QTimerEvent * event )override;

	QLineEdit * lastLineEdit_;

	void newAddress(QboxAddress * aa = NULL);

	AddressMap addresses_;
	QboxAddress* currConnAddress_;

	QTableWidget*				tableDevices_;

    Ui::DevicesWnd *ui;

	//SnmpCallback::RequestStatus checkAddressCallback( int , snmp_session*, snmp_pdu*, SnmpObj*);
	void onlineRefreshed(QboxAddress * aa);
	void offlineRefreshed(QboxAddress * aa);
	void checkingRefreshed(QboxAddress * aa);
	QMutex locker_;


	friend class QboxAddress;

};

#endif // DEVICESWND_H
