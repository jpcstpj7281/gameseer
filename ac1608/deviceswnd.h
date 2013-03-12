#ifndef DEVICESWND_H
#define DEVICESWND_H

#include <QWidget>
#include <map>
#include <QTableWidget>

#include <QLineEdit>
#include <QRegExpValidator>
#include <QRegExp>
#include <functional>
namespace Ui {
class DevicesWnd;
}
class Ac1608Address;

typedef std::function< int (int, int, Ac1608Address*) > AddressCallback;


class Ac1608Address: public QObject{
	Q_OBJECT
private slots:
	void editingFinished ();
public:
	Ac1608Address( QString &ip , QString & loc){

		this->ip = ip; this->location = loc; 
		this->row = 0;
	}

	void init(int row, AddressCallback callback, QLineEdit* lineEdit){ 
		this->callback = callback;
		this->row = row;

		this->lineEdit =  lineEdit;
		connect( lineEdit, SIGNAL(editingFinished ()), this, SLOT(editingFinished ()));
	}
	int row;
	QString ip;
	QString location;
	QLineEdit* lineEdit;
	AddressCallback callback;
};


class DevicesWnd : public QWidget
{
    Q_OBJECT

public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();


	void refresh();
	void initAddresses();
private slots:
	void editingFinished ();
	void itemChanged(QTableWidgetItem *);
	void cellChanged(int,int);
	void	cellActivated ( int row, int column );
	void	cellEntered ( int row, int column );

private:


	QLineEdit * lastLineEdit_;

	void newAddress(Ac1608Address * aa = NULL);

	typedef std::map< QString, Ac1608Address* > AddressMap;

	AddressMap addresses_;

	QTableWidget*				tableDevices_;
	//QStandardItemModel *	model_;

    Ui::DevicesWnd *ui;


};

#endif // DEVICESWND_H
