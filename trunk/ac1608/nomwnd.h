#ifndef NOMWND_H
#define NOMWND_H

#include <QWidget>

namespace Ui {
class NOMWnd;
}

class NOMWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit NOMWnd(QWidget *parent = 0);
    ~NOMWnd();
    
private:
    Ui::NOMWnd *ui;
};

#endif // NOMWND_H
