
#include "mainwindow.h"
#include "configmgr.h"
#include "snmpnet.h"
#include "tcpnet.h"
#include <QApplication>


int main(int argc, char *argv[])
{
	SnmpNet::instance();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
	SnmpNet::instance()->startThread();
	TcpNet::instance()->startThread();
    auto rs = a.exec();
	SnmpNet::instance()->stop();
	TcpNet::instance()->stop();
	ConfigMgr::instance()->saveAll();
	return rs;

}
