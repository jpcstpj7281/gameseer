#include "PswInputDlg.h"
#include "ui_PswInputDlg.h"

#include "configmgr.h"
#include <QList>
#include <QDebug>
#include <QLineEdit>
#include <QCryptographicHash>

//PswInputDlg * PswInputDlg::inst = 0;
//PswInputDlg *PswInputDlg::instance(){
//	if (!inst){
//		inst =  new PswInputDlg;
//	}
//	return inst;
//}

PswInputDlg::PswInputDlg(QWidget *parent):
    QDialog(parent)
	,ui(new Ui::PswInputDlg)
{
    ui->setupUi(this);
	setModal(true);

	//QRegExp ipRx("(\\.([0-9]{4}|[0-9]{3}|[0-9]{2}|[0-9]{1})){32}");
	//QRegExpValidator *pIpValidator = new QRegExpValidator(ipRx);
	//QLineEdit * le = findChild<QLineEdit*>( "oldpsw");
	//le->setValidator(pIpValidator);
	//le->setAlignment( Qt::AlignVCenter| Qt::AlignHCenter);

	QPushButton * okBtn = findChild<QPushButton*>( "ok");
	QPushButton * defaultBtn = findChild<QPushButton*>( "change");
	QPushButton * cancelBtn = findChild<QPushButton*>( "cancel");

	connect( okBtn, SIGNAL(clicked()), this, SLOT(okClick()));
	connect( defaultBtn, SIGNAL(clicked()), this, SLOT(changeClick()));
	connect( cancelBtn, SIGNAL(clicked()), this, SLOT(cancelClick()));
}

PswInputDlg::~PswInputDlg()
{
    delete ui;
}

bool PswInputDlg::getNewPsw( int* oldp, int *newp){
	//PswInputDlg::instance()->id_ = id;
	//PswInputDlg::instance()->oldPsw_ = ConfigMgr::instance()->getOid(id);
	//PswInputDlg::instance()->newOid_ =  ConfigMgr::instance()->getDefaultOid(id);
	isChangeMode_ = false;
	isPasswordChanged_ = false;
	newPsw_ = newp;
	oldPsw_ = oldp;
	this->exec();
	QLineEdit * le = findChild<QLineEdit*>( "oldpsw");
	le->text();
	//le->setText(PswInputDlg::instance()->oldPsw_);
	//le->setFocus();
	//PswInputDlg::instance()->exec();
	//return 
	return true;
}

void PswInputDlg::closeEvent ( QCloseEvent * event ){
	cancelClick();
}

void PswInputDlg::okClick(){
	QLineEdit * le1 = findChild<QLineEdit*>( "oldpsw");
	QString oldpsw = le1->text();
	if (isChangeMode_){
		QLineEdit * le2 = findChild<QLineEdit*>( "newpsw");
		QLineEdit * le3 = findChild<QLineEdit*>( "repeatpsw");
		QString newpsw = le1->text();
		QString repeatpsw = le1->text();
		if (newpsw == repeatpsw){
			//QString md5;  
			QByteArray newb,newa, oldb, olda;  
			QCryptographicHash newmd(QCryptographicHash::Md5);  
			QCryptographicHash oldmd(QCryptographicHash::Md5);  
			newb.append(newpsw);  
			oldb.append(oldpsw);
			newmd.addData(newb);  
			newa = newmd.result();
			oldmd.addData(oldb);
			olda = oldmd.result();
			//char* buf = bb.data();
			//md5.append();   
			//qDebug()<<"md5: " << *(int*)buf<<*(int*)(buf+4)<<*(int*)(buf+8)<<*(int*)(buf+16);
			if (memcmp( newa.data(), olda.data(), 16)){
				qDebug()<<"error!";
			}else{
				if( memcmp(oldPsw_, olda.data(), 16)){
					memcpy( newPsw_, newa.data(), 16);
					QPushButton * okBtn = findChild<QPushButton*>( "ok");
					okBtn->setText("确认连接");
				}
			}
		}
	}else if ( !oldpsw.isEmpty()){
		QByteArray oldb, olda;  
		QCryptographicHash oldmd(QCryptographicHash::Md5);  
		oldb.append(oldpsw);
		oldmd.addData(oldb);
		olda = oldmd.result();
		if( memcmp(oldPsw_, olda.data(), 16)){
			qDebug()<<"pass";
		}else{
			qDebug()<<"no pass";
		}
	}
}
void PswInputDlg::changeClick(){
	QLineEdit * le1 = findChild<QLineEdit*>( "newpsw");
	QLineEdit * le2 = findChild<QLineEdit*>( "repeatpsw");
	QPushButton * okBtn = findChild<QPushButton*>( "ok");
	le1->setEnabled(isChangeMode_);
	le2->setEnabled(isChangeMode_);
	if (isChangeMode_){
		okBtn->setText("确认修改");
	}else{
		okBtn->setText("确认连接");
	}
}
void PswInputDlg::cancelClick(){
	this->hide();
}