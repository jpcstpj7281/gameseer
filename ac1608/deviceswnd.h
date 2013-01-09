#ifndef DEVICESWND_H
#define DEVICESWND_H

#include <QWidget>

namespace Ui {
class DevicesWnd;
}

class DevicesWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit DevicesWnd(QWidget *parent = 0);
    ~DevicesWnd();
    
private:
    Ui::DevicesWnd *ui;
};

#endif // DEVICESWND_H
