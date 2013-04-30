#ifndef TESTQBOX_H
#define TESTQBOX_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <TcpNet.h>



namespace Ui {
class TestNet;
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
    explicit TestQbox(const std::string &ip );
    ~TestQbox();
    

	private slots:
		void sendClicked(bool);
		void clearClicked(bool);
private:
    Ui::TestNet *ui;

	QTableWidget* tableRequest_;
	QTableWidget* tableResponse_;
	std::string address_;
	
	void newRequestRow( );
	bool testDataCallback( const std::string &msg);

	void addResponseRow( const std::string & msg );
};

#endif // TESTQBOX_H
