#ifndef METERS_H
#define METERS_H

#include <QWidget>

namespace Ui {
class Meters;
}

class Meters : public QWidget
{
    Q_OBJECT
    
public:
    explicit Meters(QWidget *parent = 0);
    ~Meters();
    
private:
    Ui::Meters *ui;
};

#endif // METERS_H
