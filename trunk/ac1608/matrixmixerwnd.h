#ifndef MATRIXMIXERWND_H
#define MATRIXMIXERWND_H

#include <QWidget>

namespace Ui {
class MatrixMixerWnd;
}

class MatrixMixerWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit MatrixMixerWnd(QWidget *parent = 0);
    ~MatrixMixerWnd();
    
private:
    Ui::MatrixMixerWnd *ui;
};

#endif // MATRIXMIXERWND_H
