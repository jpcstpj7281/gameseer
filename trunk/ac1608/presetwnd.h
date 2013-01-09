#ifndef PRESETWND_H
#define PRESETWND_H

#include <QWidget>

namespace Ui {
class PresetWnd;
}

class PresetWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit PresetWnd(QWidget *parent = 0);
    ~PresetWnd();
    
private:
    Ui::PresetWnd *ui;
};

#endif // PRESETWND_H
