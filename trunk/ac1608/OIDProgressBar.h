#ifndef OIDProgressBar_H
#define OIDProgressBar_H

#include <qprogressbar>
#include <Snmpnet.h>

class OIDProgressBar : public QProgressBar{

	Q_OBJECT

	void * inputDialog_;

	volatile int  val_;
	volatile int  isRunning_;

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
	void snmpCallback(  SnmpObj*);
public:
	OIDProgressBar( QWidget* w);
	void initSnmp();
	void shutdownSnmp();
};
#endif // OIDProgressBar