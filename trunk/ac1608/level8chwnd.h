#ifndef LEVEL8CHWND_H
#define LEVEL8CHWND_H

#include <QWidget>

namespace Ui {
class Level8CHWnd;
}

class Level8CHWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit Level8CHWnd(QWidget *parent = 0);
    ~Level8CHWnd();
    
private:
    Ui::Level8CHWnd *ui;
};

#endif // LEVEL8CHWND_H
