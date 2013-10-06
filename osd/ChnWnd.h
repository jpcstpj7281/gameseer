#ifndef ChnWnd_H
#define ChnWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>


namespace Ui {
class ChnWnd;
}


class ChnWidget:public QWidget{
	Q_OBJECT
	private slots:

public:
	ResourceID inputid_;
	QTableWidgetItem* id_;
	QTableWidgetItem* col_;
	QTableWidgetItem* row_;
	QTableWidgetItem* width_;
	QTableWidgetItem* height_;
	QTableWidgetItem* freq_;
	QTableWidgetItem* inport_;

	ChnWidget(ResourceID inputid);

	void initTable( QTableWidget* table, int row);
};

class ChnWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void currentTabChanged ( int index );
			void clickedSetVideo ();
public:
    explicit ChnWnd(QWidget* parent);
    ~ChnWnd();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
private:
	bool setVideoCallback( uint32_t , QboxDataMap);
    Ui::ChnWnd *ui;
	QTableWidget*	chnTable_;
	std::vector<ResourceID> inputs_;
	bool isCurrTab_ ;
	virtual void	timerEvent ( QTimerEvent * event )override;
};

#endif // ChnWnd_H

