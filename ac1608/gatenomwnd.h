#ifndef GATENOMWND_H
#define GATENOMWND_H

#include <QWidget>

namespace Ui {
class GateNOMWnd;
}

class OIDDial;
class QTabWidget;
class OIDStatePushBtn;


class GateNOMWnd : public QWidget
{
    Q_OBJECT
    
		private slots:
			void indexChanged(int index);
public:
    explicit GateNOMWnd(QTabWidget *parent = 0);
    ~GateNOMWnd();
    
private:
    Ui::GateNOMWnd *ui;
	QTabWidget* tab_;

	QList<OIDStatePushBtn *> qpbtnl_;
	QList<OIDDial *> qdl_;
};

#endif // GATENOMWND_H
