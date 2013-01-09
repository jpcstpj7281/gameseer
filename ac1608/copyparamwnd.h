#ifndef COPYPARAMWND_H
#define COPYPARAMWND_H

#include <QWidget>

namespace Ui {
class CopyParamWnd;
}

class CopyParamWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit CopyParamWnd(QWidget *parent = 0);
    ~CopyParamWnd();
    
private:
    Ui::CopyParamWnd *ui;
};

#endif // COPYPARAMWND_H
