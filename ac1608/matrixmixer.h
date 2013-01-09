#ifndef MATRIXMIXER_H
#define MATRIXMIXER_H

#include <QWidget>

namespace Ui {
class MatrixMixer;
}

class MatrixMixer : public QWidget
{
    Q_OBJECT
    
public:
    explicit MatrixMixer(QWidget *parent = 0);
    ~MatrixMixer();
    
private:
    Ui::MatrixMixer *ui;
};

#endif // MATRIXMIXER_H
