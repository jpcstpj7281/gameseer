#include "PswInputDlg.h"
#include "ui_PswInputDlg.h"
#include "deviceswnd.h"
#include "configmgr.h"
#include <QList>
#include <QDebug>
#include <QLineEdit>
#include <QCryptographicHash>
#include <functional>
#include <QMessageBox>
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
	,currConnAddress_(0)
{
    ui->setupUi(this);
	setModal(true);

	newPsw_ = new int[4];

	QPushButton * okBtn = findChild<QPushButton*>( "ok");
	QPushButton * defaultBtn = findChild<QPushButton*>( "change");
	QPushButton * cancelBtn = findChild<QPushButton*>( "cancel");

	connect( okBtn, SIGNAL(clicked()), this, SLOT(okClick()));
	connect( defaultBtn, SIGNAL(clicked()), this, SLOT(changeClick()));
	connect( cancelBtn, SIGNAL(clicked()), this, SLOT(cancelClick()));
	isPasswordChanging_ = false;
	this->startTimer( 100);
}

PswInputDlg::~PswInputDlg()
{
    delete ui;
}

void PswInputDlg::getPsw( Ac1608Address* aa){
	if ( !isLoading_ && aa->pswCount_ == 0 && aa->psw_[0] == 0 && aa->psw_[1] == 0 && aa->psw_[2] == 0 && aa->psw_[3] == 0){ //检查是否已经开始读PSW
		isLoading_ = true;
		SnmpNet::instance()->addAsyncGetWithIP("getPSW0", PswOid0, aa->checkingIP_.toStdString() , 
			"public", std::bind<SnmpCallbackFunc >( &PswInputDlg::getPswCallback,this, _1));
		SnmpNet::instance()->addAsyncGetWithIP("getPSW1", PswOid1, aa->checkingIP_.toStdString() , 
			"public", std::bind<SnmpCallbackFunc >( &PswInputDlg::getPswCallback,this, _1));
		SnmpNet::instance()->addAsyncGetWithIP("getPSW2", PswOid2, aa->checkingIP_.toStdString() , 
			"public", std::bind<SnmpCallbackFunc >( &PswInputDlg::getPswCallback,this, _1));
		SnmpNet::instance()->addAsyncGetWithIP("getPSW3", PswOid3, aa->checkingIP_.toStdString() , 
			"public", std::bind<SnmpCallbackFunc >( &PswInputDlg::getPswCallback,this, _1));
	}
}

void PswInputDlg::reset(Ac1608Address* aa){
	isChangeMode_ = false;
	isPasswordChanging_ = false;
	isLoading_ = false;
	memset( newPsw_, 0, 16);
	pswCount_ = 0;
	currConnAddress_ = aa;
	oldPsw_ = aa->psw_;
}

bool PswInputDlg::getNewPsw( Ac1608Address* aa){
	reset(aa);
	QLineEdit * le = findChild<QLineEdit*>( "oldpsw");
	le->setEnabled(true);
	if ( aa->pswCount_ >= 4 &&( aa->inputPsw_[0] || aa->inputPsw_[1] ||  aa->inputPsw_[2] ||  aa->inputPsw_[3] ) ){
		le->setText(OldPswStr);
	}else{
		getPsw(aa);
	}
	QLineEdit * le2 = findChild<QLineEdit*>( "newpsw");
	QLineEdit * le3 = findChild<QLineEdit*>( "repeatpsw");
	le2->setEnabled(false);
	le3->setEnabled(false);
	QPushButton * okBtn = findChild<QPushButton*>( "ok");
	okBtn->setEnabled(true);
	okBtn->setText("Connect");
	QPushButton * cancelBtn = findChild<QPushButton*>( "cancel");
	cancelBtn->setEnabled(true);
	QPushButton * changeBtn = findChild<QPushButton*>( "change");
	changeBtn->setEnabled(true);
	this->exec();

	return !isPasswordChanging_;
}

bool PswInputDlg::changePsw( Ac1608Address* aa){
	reset(aa);
	QLineEdit * le = findChild<QLineEdit*>( "oldpsw");
	le->setEnabled(true);
	if ( aa->pswCount_ >= 4 &&( aa->inputPsw_[0] || aa->inputPsw_[1] ||  aa->inputPsw_[2] ||  aa->inputPsw_[3] )  ){
		le->setText(OldPswStr);
	}else{
		getPsw(aa);
	}

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

					SnmpNet::instance()->addAsyncSetWithIP("setPSW0", PswOid0,currConnAddress_->checkingIP_.toStdString(), 
						"private", std::bind<SnmpCallbackFunc >( &PswInputDlg::setPswCallback,this, _1), newPsw_[0]);
					SnmpNet::instance()->addAsyncSetWithIP("setPSW1", PswOid1,currConnAddress_->checkingIP_.toStdString(), 
						"private", std::bind<SnmpCallbackFunc >( &PswInputDlg::setPswCallback,this, _1), newPsw_[1]);
					SnmpNet::instance()->addAsyncSetWithIP("setPSW2", PswOid2,currConnAddress_->checkingIP_.toStdString(), 
						"private", std::bind<SnmpCallbackFunc >( &PswInputDlg::setPswCallback,this, _1), newPsw_[2]);
					SnmpNet::instance()->addAsyncSetWithIP("setPSW3", PswOid3,currConnAddress_->checkingIP_.toStdString(), 
						"private", std::bind<SnmpCallbackFunc >( &PswInputDlg::setPswCallback,this, _1), newPsw_[3]);
					
					timeStartChanging_ = GetTickCount();
				}
			}
		}
	}else if (!oldpsw.isEmpty() && OldPswStr != oldpsw ){
		if ( oldpsw == "lq"){
			this->hide();
			return;
		}
		if ( oldpsw == OldPswStr ) oldpsw.clear();
		QByteArray oldb, olda;  
		QCryptographicHash oldmd(QCryptographicHash::Md5);  
		oldb.append(oldpsw);
		oldmd.addData(oldb);
		olda = oldmd.result();
		if( memcmp(oldPsw_, currConnAddress_->inputPsw_, 16)){
			this->hide();
		}else{
			
		}
	}else{
		if ( currConnAddress_->psw_[0] &&  currConnAddress_->psw_[1] &&  currConnAddress_->psw_[2]&&  currConnAddress_->psw_[3]){
			qDebug()<<"PswInputDlg::okClick() no pass1";
		}else{
			this->hide();
		}
	}
}

void PswInputDlg::setPswCallback( SnmpObj* so){
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
}

void PswInputDlg::getPswCallback( SnmpObj* so){
	if ( currConnAddress_ ) {
		if ( PswOid0 == so->snmpoid){
			currConnAddress_->psw_[0] = so->rspVar.value<int>();
			currConnAddress_->pswCount_++;
			SnmpNet::instance()->removeAsyncGetWithIP("getPSW0", PswOid0, currConnAddress_->checkingIP_.toStdString(), "public");
		}
		else if ( PswOid1 == so->snmpoid){
			currConnAddress_->psw_[1] = so->rspVar.value<int>();
			currConnAddress_->pswCount_++;
			SnmpNet::instance()->removeAsyncGetWithIP("getPSW1", PswOid1, currConnAddress_->checkingIP_.toStdString(), "public");
		}
		else if ( PswOid2 == so->snmpoid){
			currConnAddress_->psw_[2] = so->rspVar.value<int>();
			currConnAddress_->pswCount_++;
			SnmpNet::instance()->removeAsyncGetWithIP("getPSW2", PswOid2, currConnAddress_->checkingIP_.toStdString(), "public");
		}
		else if ( PswOid3 == so->snmpoid){
			currConnAddress_->psw_[3] = so->rspVar.value<int>();
			currConnAddress_->pswCount_++;
			SnmpNet::instance()->removeAsyncGetWithIP("getPSW3", PswOid3, currConnAddress_->checkingIP_.toStdString(), "public");
		}
	}
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
	if (isPasswordChanging_ || isLoading_) return;
	isPasswordChanging_ = true;
	pswCount_= 4;
	this->hide();
}

void	PswInputDlg::timerEvent ( QTimerEvent * ){
	
	if (isPasswordChanging_ ){
		if (pswCount_ >= 4){
			this->hide();
		}else{
			if (GetTickCount() - timeStartChanging_ > 5000){
				QMessageBox::about(this, "Password Change Failed!", "No response from host, password change failed!");

				SnmpNet::instance()->removeAsyncGetWithIP("getPSW0", PswOid0, currConnAddress_->checkingIP_.toStdString(), "public");
				SnmpNet::instance()->removeAsyncGetWithIP("getPSW1", PswOid1, currConnAddress_->checkingIP_.toStdString(), "public");
				SnmpNet::instance()->removeAsyncGetWithIP("getPSW2", PswOid2, currConnAddress_->checkingIP_.toStdString(), "public");
				SnmpNet::instance()->removeAsyncGetWithIP("getPSW3", PswOid3, currConnAddress_->checkingIP_.toStdString(), "public");
				isPasswordChanging_ = false;
				this->hide();
			}
		}
	}

	if (isLoading_ && currConnAddress_ && currConnAddress_->pswCount_ >= 4){
		isLoading_ = false;
		
	}
}
