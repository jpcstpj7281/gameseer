#ifndef INPUTGAINCTRLWND_H
#define INPUTGAINCTRLWND_H

#include <QWidget>

namespace Ui {
class InputGainCtrlWnd;
}

class OIDSlider;
class OIDStatePushBtn;
class QTabWidget;

class InputGainCtrlWnd : public QWidget
{
    Q_OBJECT
    private slots:
			void indexChanged(int);
public:
    explicit InputGainCtrlWnd(QTabWidget *parent = 0);
    ~InputGainCtrlWnd();
    
private:
	QTabWidget* tab_;
    Ui::InputGainCtrlWnd *ui;

	QList<OIDSlider *> qsl_;
	QList<OIDStatePushBtn *> qpbtnl_;
};

#endif // INPUTGAINCTRLWND_H
