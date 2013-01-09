#ifndef CHANGEPASSWORDWND_H
#define CHANGEPASSWORDWND_H

#include <QWidget>

namespace Ui {
class ChangePasswordWnd;
}

class ChangePasswordWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit ChangePasswordWnd(QWidget *parent = 0);
    ~ChangePasswordWnd();
    
private:
    Ui::ChangePasswordWnd *ui;
};

#endif // CHANGEPASSWORDWND_H
