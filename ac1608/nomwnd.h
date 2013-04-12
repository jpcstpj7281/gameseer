#ifndef NOMWND_H
#define NOMWND_H

#include <QWidget>

namespace Ui {
class NOMWnd;
}

class OIDSlider;
class OIDStatePushBtn;
class OIDProgressBar;
class QTabWidget;

class NOMWnd : public QWidget
{
    Q_OBJECT
private slots:
			void indexChanged(int);    
public:
    explicit NOMWnd(QTabWidget *parent = 0);
    ~NOMWnd();
    
private:
    Ui::NOMWnd *ui;

	QTabWidget* tab_;
	QList<OIDSlider *> qsl_;
};

#endif // NOMWND_H
