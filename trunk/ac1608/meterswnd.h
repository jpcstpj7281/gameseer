#ifndef METERSWND_H
#define METERSWND_H

#include <QWidget>

namespace Ui {
class MetersWnd;
}

class MetersWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit MetersWnd(QWidget *parent = 0);
    ~MetersWnd();
    
private:
    Ui::MetersWnd *ui;
};

#endif // METERSWND_H
