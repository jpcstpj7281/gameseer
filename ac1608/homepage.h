#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include <qprogressbar>

class MyProgressBar : public QProgressBar{
public:
	MyProgressBar( QWidget* w):QProgressBar(w){}
	virtual void	mouseDoubleClickEvent ( QMouseEvent * event ) override;
};


namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT
    
public:
    explicit HomePage(QWidget *parent = 0);
    ~HomePage();
private slots:    
	void progressBarClicked();
private:
    Ui::HomePage *ui;
};

#endif // HOMEPAGE_H
