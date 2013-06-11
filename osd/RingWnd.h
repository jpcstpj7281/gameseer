#ifndef RingWnd_H
#define RingWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <Ring.h>

namespace Ui {
class RingWnd;
}

class RingWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();
public:
	QTableWidgetItem* id_;
	RingWidget(Ring* ring);
	Ring* ring_;
	void initTable( QTableWidget* table, int row);
};

class RnodeWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();
		void currentColIndexChanged ( int  );
		void currentRowIndexChanged ( int  );
		void currentInputIndexChanged ( int  );
		void currentOutputIndexChanged ( int  );
private:
	ResourceID rnode_;
	void enableRow();
	void newNextRow();
public:
	QTableWidgetItem* hide_;
	QComboBox* col_;
	QComboBox* row_;
	QComboBox* input_;
	QComboBox* output_;
	RnodeWidget(Ring* ring, ResourceID rnode = 0);
	Ring* ring_;
	void initTable( QTableWidget* table, int row);
};

class RingWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit RingWnd(QTabWidget* parent);
    ~RingWnd();

	private slots:
		void cellChanged(int,int);
		void cellClicked(int,int);
		void currentTabChanged ( int index );

private:
    Ui::RingWnd *ui;
	QTableWidget*	ringTable_;
	QTableWidget*	rnodeTable_;

	Ring * currRing_;
	void newRing( const std::string &ip);
	//void newRnode();

	void resetRnodeTable( Ring* ring);
};

#endif // RingWnd_H
