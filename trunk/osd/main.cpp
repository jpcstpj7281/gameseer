
#include "mainwindow.h"
#include "configmgr.h"
#include "QboxNet.h"
#include <QApplication>
#include <qdebug.h>
#include <Windows.h>
#include <QTextCodec>
#include <QTranslator>

#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#undef ABSOLUTE
#undef RELATIVE
#include "log4qt/TTCCLayout.h"
#include "log4qt/LogManager.h"
#include "log4qt/FileAppender.h"
using namespace Log4Qt;

#include <qdatetime.h> 
#include <qt_ext\qtsingleapplication.h>

int main(int argc, char *argv[])
{

    Log4Qt::LogManager::rootLogger();
	TTCCLayout *p_layout = new TTCCLayout();
	p_layout->setName(QLatin1String("My Layout"));
	p_layout->setDateFormat("ISO8601");
	p_layout->setThreadPrinting(false);
	p_layout->activateOptions();
	FileAppender *p_appender = new FileAppender(p_layout, QDateTime::currentDateTime().toString("./log/yyyy.MM.dd.hh.mm.ss")+".log");

	p_appender->setName(QLatin1String("Relay Appender"));
	p_appender->activateOptions();
	Log4Qt::Logger::rootLogger()->addAppender(p_appender); 
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
	
    QtSingleApplication a(argc, argv);
    //QApplication a(argc, argv);
    if (!a.isRunning()){
		//a.setQuitOnLastWindowClosed(false);//点关闭不退出程序
		a.installTranslator( &translator );
		MainWindow w;
		w.show();
		w.setFixedSize( 1024, 768);

		QboxMgr::instance()->startThread();
		auto rs = a.exec();
		QboxMgr::instance()->stop();
		delete ConfigMgr::instance();
		delete QboxMgr::instance();
	}else{
		return 0;
	}
	//return 0;
}
