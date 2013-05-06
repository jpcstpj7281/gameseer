#include "mainwindow.h"
#include "configmgr.h"
#include "TcpNet.h"
#include <QApplication>
#include <qdebug.h>
#include <Windows.h>
#include <qt_ext\qtsingleapplication.h>



int main(int argc, char *argv[])
{

	//qDebug()<<"test";
	//static const size_t size = 8* 8 *8 * 8 * 8;
	//int test[size];
	//qDebug()<<sizeof(test);
	//memset( test, 0, sizeof(test) );
	//size_t pre = GetTickCount();
	//for (size_t j = 0; j < 10000 ; ++j){
	//	for ( size_t i = 0; i < size; i+=8){
	//		test[i] += 1;
	//		test[i+1] += 1;
	//		test[i+2] += 1;
	//		test[i+3] += 1;
	//		test[i+4] += 1;
	//		test[i+5] += 1;
	//		test[i+6] += 1;
	//		test[i+7] += 1;
	//	}
	//}
	//qDebug()<<GetTickCount() - pre;

	int port = 1000;
	QDomNodeList items = ConfigMgr::instance()->getDoc()->documentElement().elementsByTagName("port");
	if (items.size()==1){
		QDomNode node = items.at(0);
		port = node.toElement().attribute("val").toInt();
	}
	TcpNet::instance()->setPort(port );

    QtSingleApplication a(argc, argv);
	if (!a.isRunning()){
		a.setQuitOnLastWindowClosed(false);
		MainWindow w;
		w.show();

		TcpNet::instance()->startThread();

		auto rs = a.exec();
		TcpNet::instance()->stop();
		return rs;
	}else{
		return 0;
	}
}
