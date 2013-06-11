#ifndef WndWnd_H
#define WndWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <wnd.h>

namespace Ui {
class WndWnd;
}

class WndWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit WndWnd(QWidget* parent);
    ~WndWnd();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
private:
    Ui::WndWnd *ui;


};

#endif // WndWnd_H
