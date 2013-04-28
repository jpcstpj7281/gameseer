#ifndef TIMERWND_H
#define TIMERWND_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <TcpNet.h>


namespace Ui {
class TimerWnd;
}

class TimerWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit TimerWnd( );
    ~TimerWnd();
    

	private slots:
		void sendClicked(bool);
		void clearClicked(bool);
private:
    Ui::TimerWnd *ui;

};

#endif // TIMERWND_H
