#ifndef OIDDial_H
#define OIDDial_H

#include <QDial>
#include <Snmpnet.h>


class OIDDial : public QDial{
	Q_OBJECT
	void * inputDialog_;

	volatile int val_;

	SnmpCallback::RequestStatus snmpCallback(SnmpObj*);
	void	timerEvent ( QTimerEvent * e )override;
	bool eventFilter ( QObject * watched, QEvent * event )override;

	size_t lastTimeChanged_;
private slots:
		void fireSnmp(int  );
public:
	OIDDial( QWidget* w);

	void initSnmp();

};
#endif // OIDDial_H