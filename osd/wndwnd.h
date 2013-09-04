#ifndef WndWnd_H
#define WndWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <wnd.h>
#include <QSpinBox>
#include <QComboBox.h>
namespace Ui {
class WndWnd;
}
class WnodeWidget:public QWidget{
	Q_OBJECT
	private slots:

public:
	ResourceID wnode_;

	QTableWidgetItem* id_;

	QTableWidgetItem* x_;
	QTableWidgetItem* y_;
	QTableWidgetItem* w_;
	QTableWidgetItem* h_;
	QTableWidgetItem* ax_;
	QTableWidgetItem* ay_;
	QTableWidgetItem* aw_;
	QTableWidgetItem* ah_;
	Wnd* wnd_;
	
	WnodeWidget(Wnd* wnd, ResourceID wnode);

	void initTable( QTableWidget* table, int row);
};
class WndChnQComboBox: public QComboBox{
public:
	bool isPressed_;
	virtual void mousePressEvent ( QMouseEvent * e );
};

class WndWidget:public QWidget{
	Q_OBJECT
	private slots:
		void currentInputIndexChanged (const QString &);
public:
	ResourceID inputid_;
	QTableWidgetItem* id_;

	QTableWidgetItem* x_;
	QTableWidgetItem* y_;
	QTableWidgetItem* w_;
	QTableWidgetItem* h_;
	QTableWidgetItem* ax_;
	QTableWidgetItem* ay_;
	QTableWidgetItem* aw_;
	QTableWidgetItem* ah_;

	WndChnQComboBox* input_;
	Wnd* wnd_;

	WndWidget(Wnd* wnd);

	void initTable( QTableWidget* table, int row);
	bool isPressed();
};

class WndWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void currentTabChanged ( int index );
			void cellClicked ( int row, int column );
			void clickedDirectWndMode();
public:
    explicit WndWnd(QWidget* parent);
    ~WndWnd();

	bool isChnComboBoxPressed();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
		//void currentInputIndexChanged (const QString & inputstr);
private:
	QTableWidget*	wndTable_;
	QTableWidget*	wnodeTable_;

	bool isCurrTab_ ;
	bool isDirectWndMode_;
    Ui::WndWnd *ui;
	bool inputChangedCallback( ResourceID inputid);
	virtual void	timerEvent ( QTimerEvent * event )override;
};

#endif // WndWnd_H
