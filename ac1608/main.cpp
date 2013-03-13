#include "mainwindow.h"
#include "configmgr.h"
#include "snmpnet.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    auto rs = a.exec();
	SnmpNet::instance()->stop();
	delete ConfigMgr::instance();
	delete SnmpNet::instance();
	return rs;
}
