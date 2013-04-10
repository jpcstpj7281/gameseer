#ifndef TESTQBOX_H
#define TESTQBOX_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>

namespace Ui {
class TestQbox;
}

class QboxComboBox: public QComboBox{
	Q_OBJECT
	QTableWidgetItem  *item_;
	std::string data_;

	private slots:
		void currentIndexChangedImpl(const QString & text);
public:
	QboxComboBox( const std::string &data, QTableWidgetItem  *item);
};

class TestQbox : public QWidget
{
    Q_OBJECT
    
public:
    explicit TestQbox(ResourceID screenid);
    ~TestQbox();
    
	void setCurrQboxAddress( QString & ip);
	private slots:
		void cellChanged(int,int);
		void sendClicked(bool);
		void clearClicked(bool);
private:
    Ui::TestQbox *ui;

	QTableWidget* tableRequest_;
	QTableWidget* tableResponse_;
	//QString qboxAddr_;
	ResourceID screenid_;
	
	void newRequestRow( );
	bool testDataCallback( uint32_t , QboxDataMap& );

	void addResponseRow( const std::string & key,const std::string & data );
};

#endif // TESTQBOX_H
