#ifndef OIDSlider_H
#define OIDSlider_H

#include <QSlider>
#include <Snmpnet.h>


class OIDSlider : public QSlider{
	Q_OBJECT
	void * inputDialog_;

	volatile int val_;

	SnmpCallback::RequestStatus snmpCallback( int , snmp_session*, snmp_pdu*, SnmpObj*);
	void	timerEvent ( QTimerEvent * e )override;
	bool eventFilter ( QObject * watched, QEvent * event )override;

	size_t lastTimeChanged_;
private slots:
		void fireSnmp(int  );
public:
	OIDSlider( QWidget* w);

	void initSnmp();

};
#endif // MyProgressBar_H