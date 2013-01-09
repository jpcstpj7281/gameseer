#ifndef GATENOMWND_H
#define GATENOMWND_H

#include <QWidget>

namespace Ui {
class GateNOMWnd;
}

class GateNOMWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit GateNOMWnd(QWidget *parent = 0);
    ~GateNOMWnd();
    
private:
    Ui::GateNOMWnd *ui;
};

#endif // GATENOMWND_H
