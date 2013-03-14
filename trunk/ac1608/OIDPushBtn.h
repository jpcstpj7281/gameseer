#ifndef OIDPUSHBTN_H
#define OIDPUSHBTN_H

#include <qpushbutton>
#include "Snmpnet.h"

class OIDPushBtn : public QPushButton{
	void * inputDialog_;

	QString oid_;
	QString defaultOid_;
public:
	OIDPushBtn( QWidget* w):QPushButton(w){}
	inline void setOid( QString & oid, QString defaultOid){
		oid_ = oid;
		defaultOid_ = defaultOid;
	}
	inline void setOid( QString & oid){ setOid( oid, oid);}

	void setImage(QPixmap & offImage); 

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
};

class OIDStatePushBtn : public QPushButton{
	void * inputDialog_;

	QString oid_;
	QString defaultOid_;
	QPixmap onImage_;
	QPixmap offImage_;

	volatile int val_;

public:
	OIDStatePushBtn( QWidget* w);
	inline void setOid( QString & oid, QString defaultOid){
		oid_ = oid;
		defaultOid_ = defaultOid;
	}
	inline void setOid( QString & oid){ setOid( oid, oid);}

	virtual void	timerEvent ( QTimerEvent * event );

	void setOnOffStateImage(int onState, int offState, QPixmap &onImage, QPixmap &offImage );
	SnmpCallback::RequestStatus snmpCallback( int , snmp_session*, snmp_pdu* pdu, SnmpObj*);

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
};

#endif // OIDPUSHBTN_H