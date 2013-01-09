#ifndef HIGHPASSWND_H
#define HIGHPASSWND_H

#include <QWidget>

namespace Ui {
class HighPassWnd;
}

class HighPassWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit HighPassWnd(QWidget *parent = 0);
    ~HighPassWnd();
    
private:
    Ui::HighPassWnd *ui;
};

#endif // HIGHPASSWND_H
