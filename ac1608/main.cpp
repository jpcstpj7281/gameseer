
#include "mainwindow.h"
#include "configmgr.h"
#include "snmpnet.h"
#include <QApplication>


int main(int argc, char *argv[])
{
	SnmpNet::instance();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
	SnmpNet::instance()->startThread();
    auto rs = a.exec();
	SnmpNet::instance()->stop();
	ConfigMgr::instance()->saveAll();
	return rs;

}
