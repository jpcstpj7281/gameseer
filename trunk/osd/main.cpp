
#include "mainwindow.h"
#include "configmgr.h"
#include "QboxNet.h"
#include <QApplication>


int main(int argc, char *argv[])
{




    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
	QboxMgr::instance()->startThread();
    auto rs = a.exec();
	QboxMgr::instance()->stop();
	delete ConfigMgr::instance();
	delete QboxMgr::instance();
	return rs;

}
