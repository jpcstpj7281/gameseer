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
    private slots:
		void tabChanged (int);
    private:
		QTabWidget* _tab;
        Ui::MainWindow *ui;
		OsdImage *osdImage_;
		OsdProjMode * osdProjMode_;
		ResourceID screenid_;
};



class ScreenConnBtn: public QPushButton{
	Q_OBJECT

	ResourceID  screenid_;
	private slots:
		void clickit();
		void clickOsd();
		void clickTest();
		void addressEditFinished();
public:
	QTableWidgetItem	*row_;
	QTableWidgetItem	*col_;
	QLineEdit			*address_;
	QPushButton			*osdBtn_;
	QPushButton			*testBtn_;

	OsdWnd				*osdWnd_;
	TestQbox			*testQbox_;

	void conn();
	void disconn();
	ScreenConnBtn( ResourceID screenid, const std::string & ip);
	~ScreenConnBtn();
	bool connectedCallback( uint32_t , QboxDataMap);
};

class DevicesWnd : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();


	void initAddresses();
	
	//typedef std::map< QString, QboxAddress* > AddressMap;
private slots:

	void itemClicked(QTableWidgetItem *);
	void cellChanged(int,int);
	void incrCol();
	void incrRow();
	void clearWall();
	void decrCol();
	void decrRow();
	void disconnAll();
	void connAll();

	void setupTestClick();

	void clickedLoad();
	void clickedSave();
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
