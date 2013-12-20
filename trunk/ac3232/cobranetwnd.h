#ifndef CobraNetWnd_H
#define CobraNetWnd_H

#include <QWidget>

namespace Ui {
class CobraNetWnd;
}

class CobraNetWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit CobraNetWnd(QWidget *parent = 0);
    ~CobraNetWnd();
    
private:
    Ui::CobraNetWnd *ui;
};

#endif // CobraNetWnd_H
