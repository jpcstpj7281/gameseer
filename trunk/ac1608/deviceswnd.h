#ifndef DEVICESWND_H
#define DEVICESWND_H

#include <QWidget>
#include <map>
#include <QTableWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QRegExpValidator>
#include <QRegExp>
#include <functional>
#include <Snmpnet.h>



namespace Ui {
class DevicesWnd;
}
class Ac1608Address;
class DevicesWnd;
class PswInputDlg;

typedef std::function< int (int, int, Ac1608Address*) > AddressCallback;

static std::string PswOid0 = "1.3.6.1.4.1.2680.1.4.2.1.59.26.36.46.3.4.1.2.9";
static std::string PswOid1 = "1.3.6.1.4.1.2680.1.4.2.1.59.26.36.46.3.4.1.2.10";
static std::string PswOid2 = "1.3.6.1.4.1.2680.1.4.2.1.59.26.36.46.3.4.1.2.11";
static std::string PswOid3 = "1.3.6.1.4.1.2680.1.4.2.1.59.26.36.46.3.4.1.2.12";

class Ac1608Address: public QPushButton{
	Q_OBJECT
private slots:
	void editingAddressFinished ();
	void connectClicked();
public:
	Ac1608Address(DevicesWnd* parent, const QString & ip, const QString & loc);
	~Ac1608Address();
	size_t snmpResponseTime;
	size_t startCheckTime;
	QLineEdit* ip_;
	QTableWidgetItem* loc_;
	QTableWidgetItem* runTime_;
	QTableWidgetItem* status_;
	QTableWidgetItem* operation_;
	
	QTableWidget* t_;
	DevicesWnd* wnd_;
	QString checkingIP_;
	int psw_[4];
	int inputPsw_[4];
	int pswCount_;
	size_t timeticks;

	bool isExisted( const QString& ip);
	void startCheckAddress( );
	void checkAddressCallback( SnmpObj* so);
	void onlineRefreshed();
	void offlineRefreshed();
	void checkingRefreshed();
	inline const QString getIP(){ return ip_->text();}

	void timerEvent(size_t t);
};


class DevicesWnd : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();

	void initAddresses();
	
private slots:
	void cellChanged(int,int);

private:

	void connectImpl( Ac1608Address*);
	void disconnectImpl( Ac1608Address*);
	virtual void	timerEvent ( QTimerEvent * event )override;
	void newAddress(const QString  ip = "", const QString loc = "");

	Ac1608Address* currConnAddress_;
	Ac1608Address* lastLineAddress_;

	QTableWidget*				tableDevices_;

    Ui::DevicesWnd *ui;

	QMutex locker_;
	PswInputDlg* inputDlg_;

	friend class Ac1608Address;

};

#endif // DEVICESWND_H
