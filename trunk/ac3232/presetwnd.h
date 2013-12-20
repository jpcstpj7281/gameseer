#ifndef PRESETWND_H
#define PRESETWND_H

#include <QWidget>
#include <map>

#include <OIDDial.h>
#include <OIDPushBtn.h>
#include <OIDSlider.h>
#include <PEQWnd.h>

namespace Ui {
class PresetWnd;
}

class QPushButton;
class QRadioButton;

//class Preset : public QObject{
//	Q_OBJECT
//
//public:
//	QPushButton * open_;
//	QPushButton * save_;
//	QPushButton * upload_;
//	QPushButton * download_;
//	QRadioButton* select_;
//	private slots:
//	void save();
//	void open();
//	void savedsp();
//	void loaddsp();
//	void select();
//};

class PresetWnd : public QWidget
{
    Q_OBJECT
    private slots:
	void saveAs();
	void openFrom();
	void save();
	void open();
	void savedsp();
	void loaddsp();
	void cleardsp();
	void select();

public:
    explicit PresetWnd(QWidget *parent = 0);
    ~PresetWnd();
    
	QList<OIDDial*>			dialList_;
	QList<OIDStatePushBtn*> btnList_;
	QList<OIDSlider*>		sliderList_;

	PEQWnd * peq_;
private:
    Ui::PresetWnd *ui;
	QList<QPushButton *> qpbtnl_;
	QList<QRadioButton *> qrbtnl_;
	QString currPresetId_;

	void setValue( QString &objectname, QString &val);

	QPushButton* currOperatingBtn_;
	size_t currOperatingTime_;
	int currOperatingVal_;
	virtual void	timerEvent ( QTimerEvent * event )override;

	QList<QPushButton*> snmpBtn_;
	void snmpCallback(  SnmpObj* so);

	
};

#endif // PRESETWND_H
