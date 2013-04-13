#ifndef PEQWND_H
#define PEQWND_H

#include <QWidget>


class OIDStatePushBtn;
class OIDDial;
class QTabWidget;
class QPushButton;

namespace Ui {
class PEQWnd;
}

class PEQWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void indexChanged(int index);
			void clickch();
public:
    explicit PEQWnd(QTabWidget *parent = 0);
    ~PEQWnd();
    
private:
    Ui::PEQWnd *ui;


	QTabWidget *tab_;
	QList<OIDDial *> qdl_;
	QList<QPushButton *> qpbl_;
	QPushButton * currCHBtn_;
};

#endif // PEQWND_H
