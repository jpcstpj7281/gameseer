#ifndef OsdProjMode_H
#define OsdProjMode_H

#include <QWidget>

namespace Ui {
class OsdProjMode;
}

class OsdProjMode : public QWidget
{
    Q_OBJECT
    
public:
    explicit OsdProjMode(QWidget *parent = 0);
    ~OsdProjMode();
    
private:
    Ui::OsdProjMode *ui;
};

#endif // OsdProjMode_H
