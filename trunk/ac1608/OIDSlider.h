#ifndef OIDSlider_H
#define OIDSlider_H

#include <QSlider>
#include <Snmpnet.h>


class OIDSlider : public QSlider{
	Q_OBJECT
	void * inputDialog_;

	volatile int val_;
	volatile bool isRunning_;

	void snmpCallback( SnmpObj*);
	void	timerEvent ( QTimerEvent * e )override;
	bool eventFilter ( QObject * watched, QEvent * event )override;

	size_t lastTimeChanged_;
private slots:
		void fireSnmp(int  );
public:
	OIDSlider( QWidget* w);

	void initSnmp();
	void shutdownSnmp();

};
#endif // OIDSlider_H