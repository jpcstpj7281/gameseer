#include "mainwindow.h"
#include "configmgr.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    auto rs = a.exec();

	delete ConfigMgr::instance();
	return rs;
}
