#include "PswInputDlg.h"
#include "ui_PswInputDlg.h"
#include "deviceswnd.h"
#include "configmgr.h"
#include <QList>
#include <QDebug>
#include <QLineEdit>
#include <QCryptographicHash>
#include <functional>
using namespace std::placeholders;
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
	newPsw_ = new int[4];

	QPushButton * okBtn = findChild<QPushButton*>( "ok");
	QPushButton * defaultBtn = findChild<QPushButton*>( "change");
	QPushButton * cancelBtn = findChild<QPushButton*>( "cancel");

	connect( okBtn, SIGNAL(clicked()), this, SLOT(okClick()));
	connect( defaultBtn, SIGNAL(clicked()), this, SLOT(changeClick()));
	connect( cancelBtn, SIGNAL(clicked()), this, SLOT(cancelClick()));
	isPasswordChanging_ = false;
	this->startTimer( 1000);
}

PswInputDlg::~PswInputDlg()
{
    delete ui;
}

bool PswInputDlg::getNewPsw( Ac1608Address* oldp){
	//PswInputDlg::instance()->id_ = id;
	//PswInputDlg::instance()->oldPsw_ = ConfigMgr::instance()->getOid(id);
	//PswInputDlg::instance()->newOid_ =  ConfigMgr::instance()->getDefaultOid(id);
	isChangeMode_ = false;
	isPasswordChanging_ = false;
	memset( newPsw_, 0, 16);
	pswCount_ = 0;
	oldPsw_ = oldp->psw_;
	if ( oldp->pswCount_ >= 4){
		QLineEdit * le = findChild<QLineEdit*>( "oldpsw");
		le->setText(OldPswStr);
	}
	currConnAddress_ = oldp;

	QLineEdit * le2 = findChild<QLineEdit*>( "newpsw");
	QLineEdit * le3 = findChild<QLineEdit*>( "repeatpsw");
	le2->setEnabled(false);
	le3->setEnabled(false);
	this->exec();

	return true;
}

bool PswInputDlg::changePsw( Ac1608Address* oldp){
	//PswInputDlg::instance()->id_ = id;
	//PswInputDlg::instance()->oldPsw_ = ConfigMgr::instance()->getOid(id);
	//PswInputDlg::instance()->newOid_ =  ConfigMgr::instance()->getDefaultOid(id);
	isChangeMode_ = false;
	isPasswordChanging_ = false;
	memset( newPsw_, 0, 16);
	pswCount_ = 0;
	oldPsw_ = oldp->psw_;
	QLineEdit * le = findChild<QLineEdit*>( "oldpsw");
	le->setEnabled(true);
	if ( oldp->pswCount_ >= 4){
		le->setText(OldPswStr);
	}
	currConnAddress_ = oldp;

	QLineEdit * le2 = findChild<QLineEdit*>( "newpsw");
	QLineEdit * le3 = findChild<QLineEdit*>( "repeatpsw");
	le2->setEnabled(true);
	le3->setEnabled(true);
	QPushButton * changeBtn = findChild<QPushButton*>( "change");
	changeBtn->setEnabled(false);
	QPushButton * okBtn = findChild<QPushButton*>( "ok");
	okBtn->setEnabled(true);
	QPushButton * cancelBtn = findChild<QPushButton*>( "cancel");
	cancelBtn->setEnabled(true);

	changeClick();
	this->exec();

	return true;
}

void PswInputDlg::closeEvent ( QCloseEvent * event ){
	isChangeMode_ = false;
	isPasswordChanging_ = true;
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
				qDebug()<<"error old new psw no diff!";
			}else{
				if( memcmp(oldPsw_, olda.data(), 16)){
					memcpy( newPsw_, newa.data(), 16);
					setAllEnabled(false);
					isPasswordChanging_ = true;

					QLineEdit * le1 = findChild<QLineEdit*>( "oldpsw");
					QLineEdit * le2 = findChild<QLineEdit*>( "newpsw");
					QLineEdit * le3 = findChild<QLineEdit*>( "repeatpsw");
					le1->setEnabled(false);
					le2->setEnabled(false);
					le3->setEnabled(false);

					SnmpNet::instance()->addAsyncSetWithIP("setPSW0", PswOid0,currConnAddress_->ip.toStdString(), 
						"private", std::bind<SnmpCallbackFunc >( &PswInputDlg::setAddressCallback,this, _1), newPsw_[0]);
					SnmpNet::instance()->addAsyncSetWithIP("setPSW1", PswOid1,currConnAddress_->ip.toStdString(), 
						"private", std::bind<SnmpCallbackFunc >( &PswInputDlg::setAddressCallback,this, _1), newPsw_[1]);
					SnmpNet::instance()->addAsyncSetWithIP("setPSW2", PswOid2,currConnAddress_->ip.toStdString(), 
						"private", std::bind<SnmpCallbackFunc >( &PswInputDlg::setAddressCallback,this, _1), newPsw_[2]);
					SnmpNet::instance()->addAsyncSetWithIP("setPSW3", PswOid3,currConnAddress_->ip.toStdString(), 
						"private", std::bind<SnmpCallbackFunc >( &PswInputDlg::setAddressCallback,this, _1), newPsw_[3]);
				}
			}
		}
	}else if ( !oldpsw.isEmpty() && oldpsw != OldPswStr ){
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
	}else{
		this->hide();
	}
}

SnmpCallback::RequestStatus PswInputDlg::setAddressCallback( SnmpObj* so){


	if ( currConnAddress_ ) {
		if ( PswOid0 == so->snmpoid){
			newPsw_[0] = so->rspVar.value<int>();
			pswCount_++;
		}
		else if ( PswOid1 == so->snmpoid){
			newPsw_[1] = so->rspVar.value<int>();
			pswCount_++;
		}
		else if ( PswOid2 == so->snmpoid){
			newPsw_[2] = so->rspVar.value<int>();
			pswCount_++;
		}
		else if ( PswOid3 == so->snmpoid){
			newPsw_[3] = so->rspVar.value<int>();
			pswCount_++;
		}

	}
	return SnmpCallback::RequestStop;

    
}

void PswInputDlg::setAllEnabled( bool flag){
	QPushButton * okBtn = findChild<QPushButton*>( "ok");
	okBtn->setEnabled(flag);
	QPushButton * cancelBtn = findChild<QPushButton*>( "cancel");
	cancelBtn->setEnabled(flag);
	QPushButton * changeBtn = findChild<QPushButton*>( "change");
	changeBtn->setEnabled(flag);
}

void PswInputDlg::changeClick(){
	if (isPasswordChanging_ ) return;
	isChangeMode_ = !isChangeMode_;
	QLineEdit * le1 = findChild<QLineEdit*>( "newpsw");
	QLineEdit * le2 = findChild<QLineEdit*>( "repeatpsw");
	QPushButton * okBtn = findChild<QPushButton*>( "ok");
	le1->setEnabled(isChangeMode_);
	le1->setText("");
	le2->setEnabled(isChangeMode_);
	le2->setText("");
	if (isChangeMode_){
		okBtn->setText(tr("Modify"));
	}else{
		okBtn->setText(tr("Connect"));
	}
}
void PswInputDlg::cancelClick(){
	if (isPasswordChanging_ ) return;
	this->hide();
}

void	PswInputDlg::timerEvent ( QTimerEvent * event ){
	if (!isPasswordChanging_ ) return;
	
	if ( pswCount_ >= 4){
		isPasswordChanging_ = false;
		this->hide();
	}
}
