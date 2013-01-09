#ifndef INPUTGAINCTRLWND_H
#define INPUTGAINCTRLWND_H

#include <QWidget>

namespace Ui {
class InputGainCtrlWnd;
}

class InputGainCtrlWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit InputGainCtrlWnd(QWidget *parent = 0);
    ~InputGainCtrlWnd();
    
private:
    Ui::InputGainCtrlWnd *ui;
};

#endif // INPUTGAINCTRLWND_H
