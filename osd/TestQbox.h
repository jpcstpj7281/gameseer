#ifndef TESTQBOX_H
#define TESTQBOX_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>

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
	QboxComboBox(std::string &data, QTableWidgetItem  *item);
};

class TestQbox : public QWidget
{
    Q_OBJECT
    
public:
    explicit TestQbox(QWidget *parent = 0);
    ~TestQbox();
    
	private slots:
		void cellChanged(int,int);
private:
    Ui::TestQbox *ui;

	QTableWidget* tableRequest_;
	QTableWidget* tableResponse_;

	
	void newRequestRow( );

	void addResponseRow( std::string & key, std::string & data );
};

#endif // TESTQBOX_H
