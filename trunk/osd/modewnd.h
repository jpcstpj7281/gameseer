#ifndef ModeWnd_H
#define ModeWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <mode.h>

namespace Ui {
class ModeWnd;
}


class ModeWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();
public:
	Mode* mode_;
	QTableWidgetItem* id_;

	ModeWidget(Mode* mode);

	void initTable( QTableWidget* table, int row);
};

class ModeWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void currentTabChanged ( int index );
public:
    explicit ModeWnd(QWidget* parent);
    ~ModeWnd();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
private:
	void newMode( const std::string &ip);
	void resetModeTable();
	void resetWndModeTable( Mode* mode);

	Mode* currMode_;

    Ui::ModeWnd *ui;
	QTableWidget*	modeTable_;
	QTableWidget*	wndModeTable_;
	
};

#endif // ModeWnd_H

