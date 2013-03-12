#ifndef PEQWND_H
#define PEQWND_H

#include <QWidget>

namespace Ui {
class PEQWnd;
}

class PEQWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit PEQWnd(QWidget *parent = 0);
    ~PEQWnd();
    
private:
    Ui::PEQWnd *ui;
};

#endif // PEQWND_H
