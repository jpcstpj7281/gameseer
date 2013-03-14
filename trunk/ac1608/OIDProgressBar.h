#ifndef OIDProgressBar_H
#define OIDProgressBar_H

#include <qprogressbar>
#include <Snmpnet.h>

class OIDProgressBar : public QProgressBar{

	Q_OBJECT

	void * inputDialog_;

	volatile int  val_;

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
	virtual void	timerEvent ( QTimerEvent * e )override;
	SnmpCallback::RequestStatus snmpCallback( int , snmp_session*, snmp_pdu*, SnmpObj*);
public:
	OIDProgressBar( QWidget* w);
	
};
#endif // OIDProgressBar