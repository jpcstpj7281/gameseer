#include "OIDInputDlg.h"
#include "ui_oidinputdlg.h"

#include "configmgr.h"
#include <QList>
#include <QDebug>
#include <QLineEdit>

OIDInputDlg * OIDInputDlg::inst = 0;
OIDInputDlg *OIDInputDlg::instance(){
	if (!inst){
		inst =  new OIDInputDlg;
	}
	return inst;
}

OIDInputDlg::OIDInputDlg(QWidget *parent):
    QDialog(parent)
	,ui(new Ui::OIDInputDlg)
{
    ui->setupUi(this);
	setModal(true);

	QRegExp ipRx("(\\.([0-9]{4}|[0-9]{3}|[0-9]{2}|[0-9]{1})){32}");
	QRegExpValidator *pIpValidator = new QRegExpValidator(ipRx);
	QLineEdit * le = findChild<QLineEdit*>( "oidInput");
	le->setValidator(pIpValidator);
	le->setAlignment( Qt::AlignVCenter| Qt::AlignHCenter);

	QPushButton * okBtn = findChild<QPushButton*>( "okBtn");
	QPushButton * defaultBtn = findChild<QPushButton*>( "defaultBtn");
	QPushButton * cancelBtn = findChild<QPushButton*>( "cancelBtn");

	connect( okBtn, SIGNAL(clicked()), this, SLOT(okClick()));
	connect( defaultBtn, SIGNAL(clicked()), this, SLOT(defaultClick()));
	connect( cancelBtn, SIGNAL(clicked()), this, SLOT(cancelClick()));
}

OIDInputDlg::~OIDInputDlg()
{
    delete ui;
}

QString OIDInputDlg::getNewOid( QString& id){
	OIDInputDlg::instance()->id_ = id;
	OIDInputDlg::instance()->oldOid_ = ConfigMgr::instance()->getOid(id);
	OIDInputDlg::instance()->defaultOid_ =  ConfigMgr::instance()->getDefaultOid(id);
	QLineEdit * le = OIDInputDlg::instance()->findChild<QLineEdit*>( "oidInput");
	le->setText(OIDInputDlg::instance()->oldOid_);
	le->setFocus();
	OIDInputDlg::instance()->exec();
	return le->text();
}

void OIDInputDlg::closeEvent ( QCloseEvent * event ){
	cancelClick();
}

void OIDInputDlg::okClick(){
	QLineEdit * le = findChild<QLineEdit*>( "oidInput");
	QString oid = le->text();
	if ( !oid.isEmpty() ){
		ConfigMgr::instance() ->setOid( id_, oid);
		this->hide();
	}
}
void OIDInputDlg::defaultClick(){
	QLineEdit * le = findChild<QLineEdit*>( "oidInput");
	le->setText(defaultOid_);
}
void OIDInputDlg::cancelClick(){
	QLineEdit * le = findChild<QLineEdit*>( "oidInput");
	le->setText(oldOid_);
	this->hide();
}