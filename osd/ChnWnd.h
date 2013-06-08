#ifndef ChnWnd_H
#define ChnWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <channel.h>

namespace Ui {
class ChnWnd;
}

class ChnWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChnWnd(QWidget* parent);
    ~ChnWnd();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
private:
    Ui::ChnWnd *ui;


};

#endif // ChnWnd_H
