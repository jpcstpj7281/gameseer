#ifndef ModeWnd_H
#define ModeWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <mode.h>
#include <QPushButton>

namespace Ui {
class ModeWnd;
}


class ModeWidget:public QWidget{
	Q_OBJECT
	private slots:
		void clickInsert();
		void clickDelete();
		void saveMode();
		void activeMode();
public:
	Mode* mode_;
	QTableWidgetItem* id_;

	QPushButton * save_;
	QPushButton * activate_;

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
		void cellClicked(int,int);
		
		void cellChanged(int,int);
private:
	void newMode( const std::wstring &ip);
	void ModeWnd::newWnd( WndData* wnd);
	void resetModeTable();
	void resetWndModeTable( Mode* mode);

	Mode* currMode_;

    Ui::ModeWnd *ui;
	QTableWidget*	modeTable_;
	QTableWidget*	wndModeTable_;
	
};

#endif // ModeWnd_H

