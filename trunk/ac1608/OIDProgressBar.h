#ifndef OIDProgressBar_H
#define OIDProgressBar_H

#include <qprogressbar>
#include <Snmpnet.h>
#include "qlabel.h"
class OIDProgressBar : public QProgressBar{

	Q_OBJECT

	void * inputDialog_;

	volatile int  val_;
	volatile int  isRunning_;

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
	void snmpCallback(  SnmpObj*);
	QLabel *ql_;
public:
	void setLabel(QLabel *ql);
	OIDProgressBar( QWidget* w);
	void initSnmp();
	void shutdownSnmp();
};
#endif // OIDProgressBar