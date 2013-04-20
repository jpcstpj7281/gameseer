#ifndef OIDPUSHBTN_H
#define OIDPUSHBTN_H

#include <qpushbutton>
#include "Snmpnet.h"



class OIDStatePushBtn : public QPushButton{
	void * inputDialog_;

	QPixmap onImage_;
	QPixmap offImage_;
	

	bool isImageSetup_;
protected:
	bool val_;
	virtual void refreshStatus();
public:
	OIDStatePushBtn( QWidget* w);

	void setOnOffStateImage(int onState, int offState, QPixmap &onImage, QPixmap &offImage );
	void snmpCallback( SnmpObj*);
	void initSnmp();
	void shutdownSnmp();
	virtual void clickChanged();

	virtual void afterCallback();

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
};


class OIDStatus :public OIDStatePushBtn{
public:
	OIDStatus(QWidget* w);
	void refreshStatus() override;
	virtual void afterCallback() override{};
	virtual void clickChanged()override{};
};



#endif // OIDPUSHBTN_H