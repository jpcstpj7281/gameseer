#ifndef SnmpNetWnd_H
#define SnmpNetWnd_H

#include <QWidget>
#include <QTableWidget>
#include <Snmpnet.h>

#include <QMutex>


namespace Ui {
class SnmpNetWnd;
};

struct ObservedOid{
	QString obj;
	QString oid;
	QString ip;
	QString rsp;
	QString community;
};



class SnmpNetWnd : public QWidget
{
    Q_OBJECT

public:
    explicit SnmpNetWnd(QWidget *parent = 0);
    ~SnmpNetWnd();

private slots:
private:

	std::map<QString, ObservedOid > oidMap_;


	QTableWidget*				tableOids_;

    Ui::SnmpNetWnd *ui;

	QMutex locker_;

	void afterResponsed(SnmpObj*);
	void beforeSent(SnmpObj*);

	virtual void	timerEvent ( QTimerEvent * event ) override;
};

#endif // SnmpNetWnd_H
