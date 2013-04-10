#ifndef OSDIMAGE_H
#define OSDIMAGE_H

#include <QWidget>

namespace Ui {
class OsdImage;
}

class OsdImage : public QWidget
{
    Q_OBJECT
    
		private slots:
			void clickinit();

public:
    explicit OsdImage(QWidget *parent = 0);
    ~OsdImage();
    
private:
    Ui::OsdImage *ui;
};

#endif // OSDIMAGE_H
