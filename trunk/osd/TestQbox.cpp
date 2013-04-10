#include "TestQbox.h"
#include "ui_TestQbox.h"
#include <QtDeclarative/QDeclarativeView>
#include <qdebug.h>
#include <sstream>
#include "QboxNet.h"
#include "screen.h"
#include "boost/foreach.hpp"

QboxComboBox::QboxComboBox( const std::string &data, QTableWidgetItem  *item):QComboBox(0){
	item_ = item;
	data_ = data;
	addItem( QBOX_VALUE_STRING);
	addItem( QBOX_VALUE_HEX_BIN);
	addItem( QBOX_VALUE_DEC_INT);
	addItem( QBOX_VALUE_DEC_UINT);
	if ( item)
		connect( this, SIGNAL(currentIndexChanged (const QString & )), this, SLOT(currentIndexChangedImpl (const QString & )));
}

void QboxComboBox::currentIndexChangedImpl(const QString & text){
	if ( item_ == 0 ) return;
	if ( text == QBOX_VALUE_STRING){
		item_->setText( QString::fromAscii( data_.c_str() , data_.length() ) );
	}else if ( text ==QBOX_VALUE_HEX_BIN){
		std::stringstream ss;
		static char syms[] = "0123456789ABCDEF";
		for (std::string::iterator it = data_.begin(); it != data_.end(); it++){
			ss << syms[((*it >> 4) & 0xf)] << syms[*it & 0xf] << ' ';
		}
		item_->setText( ss.str().c_str() );
	}else if ( text == QBOX_VALUE_DEC_INT){
		QString res;
		char digit[16];
		sprintf(digit, "%d", *(int*)data_.c_str());
		res.append(digit);
		item_->setText( res);
	}else if ( text ==QBOX_VALUE_DEC_UINT){
		QString res;
		char digit[16];
		sprintf(digit, "%u", *(unsigned int*)data_.c_str());
		res.append(digit);
		item_->setText( res);
	}
	item_->setToolTip( item_->text());
}

TestQbox::TestQbox(ResourceID screenid) :
    QWidget(0)
	,ui(new Ui::TestQbox)
	,screenid_(screenid)
{
    ui->setupUi(this);


	tableRequest_ = findChild<QTableWidget* >("tableRequest");
	tableResponse_ = findChild<QTableWidget* >("tableResponse");

	tableRequest_->setColumnCount(3);
	QStringList sl;
    sl.push_back( "key");
    sl.push_back( "value");
    sl.push_back( "type");
    tableRequest_->setHorizontalHeaderLabels(sl );
	
	tableResponse_->setColumnCount(3);
    tableResponse_->setHorizontalHeaderLabels(sl );

	connect( tableRequest_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));

	newRequestRow();

	QPushButton * btnSend = findChild<QPushButton* >("btnSend");
	connect( btnSend, SIGNAL(clicked(bool)), this, SLOT(sendClicked(bool)));
	QPushButton * btnClear = findChild<QPushButton* >("btnClear");
	connect( btnClear, SIGNAL(clicked(bool)), this, SLOT(clearClicked(bool)));

	QLineEdit * lemsgtype = findChild<QLineEdit* >("leMsgType");
	QLineEdit * lemsgid = findChild<QLineEdit* >("leMsgID");
	lemsgtype->setInputMask("00");
	//lemsgtype->setMaxLength(4);
	lemsgid->setInputMask("00");
	//lemsgid->setMaxLength(4);

	//setCurrQboxAddress(QString("127.0.0.1"));
	
}

TestQbox::~TestQbox()
{
    delete ui;
}

//void TestQbox::setCurrQboxAddress( QString & ip){
//	qboxAddr_= ip;
//}

void TestQbox::clearClicked(bool){
	tableResponse_->setRowCount(0);
	tableRequest_->setRowCount(0);
	newRequestRow();
}
void TestQbox::sendClicked(bool){
	QboxDataMap data ;
	uint32_t  msgtype;
	QLineEdit * lemsgtype = findChild<QLineEdit* >("leMsgType");
	QLineEdit * lemsgid = findChild<QLineEdit* >("leMsgID");
	msgtype = (lemsgtype->text().toUInt() << 16 )| lemsgid->text().toUInt();

	for (int i = 0; i < tableRequest_->rowCount()-1; ++i){
		QTableWidgetItem  *item1 = tableRequest_->item( i, 0);
		QTableWidgetItem  *item2 = tableRequest_->item( i, 1);
		QComboBox  *item3 = (QComboBox*)tableRequest_->cellWidget( i, 2);
		QString key = item1->text();
		QString value = item2->text();
		QString type = item3->currentText();

		if ( type == QBOX_VALUE_STRING){
			data.insert( std::make_pair( key.toStdString(), value.toStdString() ) );
		}else if ( type == QBOX_VALUE_HEX_BIN){
			QString currChar;
			static std::string buf;
			buf.clear();
			static QString tmp ;
			tmp = value.simplified().trimmed();
			for ( int i = 0; i < tmp.length(); ){
				if ( i +2 > value.length()){
					currChar = value.mid( i, 1);
				}else{
					currChar = value.mid( i, 2);
				}
				i+=2;

				bool ok;
				uint32_t iVal= currChar.toUInt(&ok,16);
				if(!ok){
					iVal=0;
					break;
				}
				buf += iVal;
			}
			data.insert( std::make_pair( key.toStdString(), buf ) );
		}
	}

	//Qbox * q = QboxMgr::instance()->getQbox( qboxAddr_.toStdString() );
	Screen* s = ScreenMgr::instance()->getScreen(screenid_);
	if ( s){
		Qbox* q = s->getQbox();
		if (q){
			q->addAsyncRequest( msgtype, std::bind(&TestQbox::testDataCallback, this, std::placeholders::_1, std::placeholders::_2), data);
			tableResponse_->setRowCount(0);
		}
	}
}

bool TestQbox::testDataCallback( uint32_t msgtype , QboxDataMap& data){
	for ( auto it = data.begin(); it != data.end(); ++it){
		//qDebug()<< "key: "<<it->first.c_str();
		//qDebug()<< "val: "<<it->second.c_str();
		addResponseRow( it->first, it->second);
	}
	return true;
}

void TestQbox::cellChanged(int row,int col){
	if ( col != 0 ) return;
	QTableWidgetItem  *item = tableRequest_->item( row, col);
	if ( item->text() == "" ){
		if ( tableRequest_->rowCount() > 1 && row < tableRequest_->rowCount() -1 ){
			tableRequest_->removeRow( row);
		}
	}else if ( row == tableRequest_->rowCount() -1 ){
		newRequestRow();
	}
}

void TestQbox::newRequestRow(  ){
 //增加新空行
	QTableWidgetItem  *item1 = new QTableWidgetItem  ();

	item1 = new QTableWidgetItem  ();
	item1->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	item1->setFlags( Qt::ItemIsEnabled|Qt::ItemIsEditable );

	QTableWidgetItem  *item2 = new QTableWidgetItem  ();
	item2->setFlags( Qt::ItemIsEnabled |Qt::ItemIsEditable );
	item2->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);

	QComboBox *cb = new QboxComboBox( std::string(""), NULL);


	tableRequest_->setRowCount(tableRequest_->rowCount()+1);  
	tableRequest_->setItem ( tableRequest_->rowCount()-1, 0, item1 );
	tableRequest_->setItem ( tableRequest_->rowCount()-1, 1, item2 );
	//tableRequest_->setItem ( tableRequest_->rowCount(), 2, item3 );
	tableRequest_->setCellWidget(tableRequest_->rowCount()-1, 2, cb);

}

void TestQbox::addResponseRow( const std::string & key,const std::string & data ){
	QTableWidgetItem  *item1 = new QTableWidgetItem  ();
	item1 = new QTableWidgetItem  ();
	item1->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	item1->setFlags( Qt::ItemIsEnabled|Qt::ItemIsEditable );
	item1->setText(key.c_str());

	QTableWidgetItem  *item2 = new QTableWidgetItem  ();
	item2->setFlags( Qt::ItemIsEnabled |Qt::ItemIsEditable );
	item2->setTextAlignment( Qt::AlignVCenter|Qt::AlignHCenter);
	item2->setText( QString::fromAscii( data.c_str() , data.length() ) );

	QComboBox *cb = new QboxComboBox( data, item2);

	tableResponse_->setRowCount(tableResponse_->rowCount()+1);  
	tableResponse_->setItem ( tableResponse_->rowCount()-1, 0, item1 );
	tableResponse_->setItem ( tableResponse_->rowCount()-1, 1, item2 );
	tableResponse_->setCellWidget(tableResponse_->rowCount()-1, 2, cb);
}