#ifndef OIDDial_H
#define OIDDial_H

#include <QDial>
#include <Snmpnet.h>
#include <QLabel>

class OIDDial : public QDial{
	Q_OBJECT
	void * inputDialog_;

	void snmpCallback(SnmpObj*);
	bool eventFilter ( QObject * watched, QEvent * event )override;

	size_t lastTimeChanged_;
	QLabel *ql_;
	double scale_;
private slots:
		void fireSnmp(int  );
public:
	OIDDial( QWidget* w);
	void setLabel(QLabel *ql);
	void initSnmp();
	void shutdownSnmp();
	void setScale( double scale){ scale_ = scale;}
	void refreshLabel();

};
#endif // OIDDial_H