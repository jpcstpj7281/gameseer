
#include "mainwindow.h"
#include "configmgr.h"
#include "QboxNet.h"
#include <QApplication>
#include <qdebug.h>
#include <Windows.h>
#include <QTextCodec>
#include <QTranslator>

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
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	QTextCodec::setCodecForTr( code);

	QTranslator translator( 0 );
	translator.load( "proj_zh.qm", "." );//要跟刚才得到的qm的文件名对应
	

    QApplication a(argc, argv);
	a.installTranslator( &translator );
    MainWindow w;
    w.show();
	w.setFixedSize( 1024, 768);
    
	QboxMgr::instance()->startThread();
    auto rs = a.exec();
	QboxMgr::instance()->stop();
	delete ConfigMgr::instance();
	delete QboxMgr::instance();
	return rs;

	//return 0;
}
