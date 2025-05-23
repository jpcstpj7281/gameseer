#ifndef DEVICESWND_H
#define DEVICESWND_H

#include <QWidget>
#include <map>
#include <QTableWidget>

#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <functional>
#include <QPushButton.h>
#include "Screen.h"
#include "Task.h"
#include <QMainWindow>
class OsdImage;
class OsdProjMode;
class TestQbox;

namespace Ui {
class DevicesWnd;
class MainWindow;
}

class OsdWnd: public QMainWindow
{
    Q_OBJECT
    public:
		explicit OsdWnd(ResourceID screenid);
        ~OsdWnd();
		OsdImage *osdImage_;
		OsdProjMode * osdProjMode_;
    private slots:
		void tabChanged (int);
    private:
		QTabWidget* _tab;
        Ui::MainWindow *ui;
		
		ResourceID screenid_;
};



class ScreenConnBtn: public QPushButton{
	Q_OBJECT

	ResourceID  screenid_;
	private slots:
		void clickit();
		void clickOsd();
		void clickTest();
		void clickDlp();
		void addressEditFinished();
public:
	QTableWidgetItem	*row_;
	QTableWidgetItem	*col_;
	QWidget				*temp_;
	QPushButton			*rTemp_;
	QPushButton			*gTemp_;
	QPushButton			*bTemp_;

	QLineEdit			*address_;
	QPushButton			*osdBtn_;
	QPushButton			*testBtn_;
	QPushButton			*dlpBtn_;


	OsdWnd				*osdWnd_;
	TestQbox			*testQbox_;

	bool isFanCheck_;
	bool isTempCheck_;

	void conn();
	void disconn();
	void turnOnDlp();
	void turnOffDlp();
	ScreenConnBtn( ResourceID screenid, const std::string & ip);
	~ScreenConnBtn();
	bool connectedCallback( uint32_t , QboxDataMap);
	bool dlpStatusCallback( uint32_t , QboxDataMap);
	bool turnonDlpCallback( uint32_t , QboxDataMap);
	bool turnoffDlpCallback( uint32_t , QboxDataMap);

	size_t currColorTemp_;
	bool tempdlpCallback( uint32_t , QboxDataMap);

	std::string initStr_;
	bool osdResponseRead( uint32_t , QboxDataMap& data, int);
	virtual void	timerEvent ( QTimerEvent * event )override;
	size_t fanTimerErrorCount_;
	size_t dlpRunTimerCount_;
};

class DevicesWnd : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();


	void initAddresses();
	
	QPushButton* pbFanCheck_;
	QPushButton* pbTempCheck_;
private slots:

	void itemClicked(QTableWidgetItem *);
	void cellChanged(int,int);
	void incrCol();
	void incrRow();
	void colEditFinished();
	void rowEditFinished();

	void clearWall();
	void decrCol();
	void decrRow();
	void disconnAll();
	void connAll();
	void turnOnAllDlp();
	void turnOffAllDlp();

	void setupTestClick();

	void clickedLoad();
	void clickedSave();
	
	void clickedFanCheck();
	void clickedTempCheck();

	void	destroyedNow ();
private:

	

	void connectImpl( );
	void disconnectImpl( );

	virtual void	timerEvent ( QTimerEvent * event )override;

	void newAddress(ResourceID screenid, const std::string &ip);
	void deleteAddress(ResourceID screenid);

	//AddressMap addresses_;

	QTableWidget*				tableDevices_;
	
    Ui::DevicesWnd *ui;

	friend class QboxAddress;

};

#endif // DEVICESWND_H
