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

class RingWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit RingWnd(QWidget* parent);
    ~RingWnd();

	private slots:
		//void cellChanged(int,int);
		//void sendClicked(bool);
		//void clearClicked(bool);
private:
    Ui::RingWnd *ui;


};

#endif // RingWnd_H
