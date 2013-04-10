#ifndef OIDPUSHBTN_H
#define OIDPUSHBTN_H

#include <qpushbutton>
#include "Snmpnet.h"

class OIDPushBtn : public QPushButton{
	void * inputDialog_;

public:
	OIDPushBtn( QWidget* w):QPushButton(w){}

	void setImage(QPixmap & offImage); 

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
};

class OIDStatePushBtn : public QPushButton{
	void * inputDialog_;

	QPixmap onImage_;
	QPixmap offImage_;

	volatile bool val_;
	volatile bool isRunning_;

	bool isImageSetup_;
public:
	OIDStatePushBtn( QWidget* w);

	virtual void	timerEvent ( QTimerEvent * event );

	void setOnOffStateImage(int onState, int offState, QPixmap &onImage, QPixmap &offImage );
	SnmpCallback::RequestStatus snmpCallback( SnmpObj*);
	void initSnmp();
	void shutdownSnmp();

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
};

#endif // OIDPUSHBTN_H