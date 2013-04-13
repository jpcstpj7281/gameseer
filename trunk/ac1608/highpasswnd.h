#ifndef HIGHPASSWND_H
#define HIGHPASSWND_H

#include <QWidget>

class OIDStatePushBtn;
class OIDDial;
class QTabWidget;
class QPushButton;

namespace Ui {
class HighPassWnd;
}

class HighPassWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void indexChanged(int index);
			void clickch();
public:
    explicit HighPassWnd(QTabWidget *parent = 0);
    ~HighPassWnd();
    
private:
    Ui::HighPassWnd *ui;

	QTabWidget *tab_;
	QList<OIDDial *> qdl_;
	QList<QPushButton *> qpbl_;
	OIDStatePushBtn * bypass_;
	QPushButton * currCHBtn_;
};

#endif // HIGHPASSWND_H
