#include "mainwindow.h"
#include "configmgr.h"
#include "TcpNet.h"
#include <QApplication>
#include <qdebug.h>
#include <Windows.h>
#include <qt_ext\qtsingleapplication.h>
#include <QDateTime>

#include "log4qt/consoleappender.h"
#include "log4qt/logger.h"
#undef ABSOLUTE
#undef RELATIVE
#include "log4qt/TTCCLayout.h"
#include "log4qt/LogManager.h"
#include "log4qt/FileAppender.h"

#include <QBuffer>
#include <QSplashScreen>
using namespace Log4Qt;

int main(int argc, char *argv[])
{

	

	Log4Qt::LogManager::rootLogger();
	TTCCLayout *p_layout = new TTCCLayout();
	p_layout->setName(QLatin1String("My Layout"));
	p_layout->setDateFormat("ISO8601");
	p_layout->setThreadPrinting(false);
	p_layout->activateOptions();
	FileAppender *p_appender = new FileAppender(p_layout, QDateTime::currentDateTime().toString("./log/yyyy.MM.dd.hh.mm.ss")+".log");

	//QBuffer * buf = new QBuffer;
	//QTextStream * stream = new QTextStream(buf);
	//WriterAppender *p_wappender = new WriterAppender(p_layout);
	//p_wappender->setName("Writer Appender");
	//p_wappender->activateOptions();
	//p_wappender->setWriter(stream);
	//Log4Qt::Logger::rootLogger()->addAppender(p_wappender);

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

	int port = 1000;
	QDomNodeList items = ConfigMgr::instance()->getDoc()->documentElement().elementsByTagName("port");
	if (items.size()==1){
		QDomNode node = items.at(0);
		port = node.toElement().attribute("val").toInt();
	}
	TcpNet::instance()->setPort(port );

    QtSingleApplication a(argc, argv);

	items = ConfigMgr::instance()->getDoc()->documentElement().elementsByTagName("splash");
	QString path ;
	size_t time = 0;
	if (items.size()==1){
		QDomNode node = items.at(0);
		QDomElement elm = node.toElement();
		path = elm.attribute("imagePath");
		time = elm.attribute("time").toInt();
	}
	QPixmap pixmap(path);
    QSplashScreen splash(pixmap);
	splash.show();

	a.processEvents();

	Sleep(time);

	if (!a.isRunning()){
		a.setQuitOnLastWindowClosed(false);
		MainWindow w;
		w.show();
		splash.finish(&w);
		TcpNet::instance()->startThread();

		auto rs = a.exec();
		TcpNet::instance()->stop();
		return rs;
	}else{
		return 0;
	}
}
