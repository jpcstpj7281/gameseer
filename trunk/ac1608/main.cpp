
#include "mainwindow.h"
#include "configmgr.h"
#include "snmpnet.h"
#include <QApplication>
#include <QCryptographicHash>

int main(int argc, char *argv[])
{


	QString pwd="12345641324141241214134";  
	QString md5;  
	QByteArray ba,bb;  
	QCryptographicHash md(QCryptographicHash::Md5);  
	ba.append(pwd);  
	md.addData(ba);  
	bb = md.result();
	char* buf = bb.data();
	//md5.append();   
	qDebug()<<"md5: " << *(int*)buf<<*(int*)(buf+4)<<*(int*)(buf+8)<<*(int*)(buf+16);


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    auto rs = a.exec();
	SnmpNet::instance()->stop();
	delete ConfigMgr::instance();
	delete SnmpNet::instance();
	return rs;

}
