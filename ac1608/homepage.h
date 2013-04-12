#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>



namespace Ui {
class HomePage;
}

class OIDSlider;
class OIDStatePushBtn;
class OIDProgressBar;
class QTabWidget;

class HomePage : public QWidget
{
    Q_OBJECT
    
		private slots:
			void indexChanged(int);
public:
    explicit HomePage(QTabWidget *parent );
    ~HomePage();


private:
	QTabWidget* tab_;
    Ui::HomePage *ui;

	QList<OIDSlider *> qsl_;
	QList<OIDStatePushBtn *> qpbtnl_;
	QList<OIDProgressBar *> qpbarl_;
};

#endif // HOMEPAGE_H
