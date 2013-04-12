#ifndef MATRIXMIXERWND_H
#define MATRIXMIXERWND_H

#include <QWidget>

namespace Ui {
class MatrixMixerWnd;
}

class OIDStatePushBtn;
class QTabWidget;

class MatrixMixerWnd : public QWidget
{
    Q_OBJECT
private slots:
	void indexChanged(int index);
public:
    explicit MatrixMixerWnd(QTabWidget *parent = 0);
    ~MatrixMixerWnd();
    
private:

	QTabWidget* tab_;

	QList<OIDStatePushBtn *> qpbtnl_;


    Ui::MatrixMixerWnd *ui;
};

#endif // MATRIXMIXERWND_H
