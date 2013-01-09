#ifndef PEQ4BANDWND_H
#define PEQ4BANDWND_H

#include <QWidget>

namespace Ui {
class PEQ4BandWnd;
}

class PEQ4BandWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit PEQ4BandWnd(QWidget *parent = 0);
    ~PEQ4BandWnd();
    
private:
    Ui::PEQ4BandWnd *ui;
};

#endif // PEQ4BANDWND_H
