#ifndef PEQ5BANDWND_H
#define PEQ5BANDWND_H

#include <QWidget>

namespace Ui {
class PEQ5BandWnd;
}

class PEQ5BandWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit PEQ5BandWnd(QWidget *parent = 0);
    ~PEQ5BandWnd();
    
private:
    Ui::PEQ5BandWnd *ui;
};

#endif // PEQ5BANDWND_H
