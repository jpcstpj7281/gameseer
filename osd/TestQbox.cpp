#include "TestQbox.h"
#include "ui_TestQbox.h"
#include <QtDeclarative/QDeclarativeView>
#include <qdebug.h>
#include <sstream>



QboxComboBox::QboxComboBox(std::string &data, QTableWidgetItem  *item):QComboBox(0){
	item_ = item;
	data_ = data;
	addItem( "String");
	addItem( "Hex Bin");
	addItem( "Dec Int");
	addItem( "Dec UInt");
	if ( item)
		connect( this, SIGNAL(currentIndexChanged (const QString & )), this, SLOT(currentIndexChangedImpl (const QString & )));
}

void QboxComboBox::currentIndexChangedImpl(const QString & text){
	if ( item_ == 0 ) return;
	if ( text == "String"){
		 QString str = QString::fromAscii( data_.c_str() , data_.length() );
		item_->setText( str );
	}else if ( text == "Hex Bin"){
		QString res;
		//for(unsigned int i = 0; i < data_.size() ; i++){
		//	char digit[3];
		//	digit[2] = '\0';
		//	sprintf(digit, "%02x", data_[i]);
		//	//sscanf(data_.data() + (i * 2), "%02x", &digit);
		//	res.append(digit);
		//	res.append(" ");
		//}
		std::stringstream ss;
		static char syms[] = "0123456789ABCDEF";
		for (std::string::iterator it = data_.begin(); it != data_.end(); it++){
			ss << syms[((*it >> 4) & 0xf)] << syms[*it & 0xf] << ' ';
		}
		item_->setText( ss.str().c_str() );
	}else if ( text == "Dec Int"){
		QString res;
		char digit[16];
		sprintf(digit, "%d", *(int*)data_.c_str());
		res.append(digit);
		item_->setText( res);
	}else if ( text == "Dec UInt"){
		QString res;
		char digit[16];
		sprintf(digit, "%u", *(unsigned int*)data_.c_str());
		res.append(digit);
		item_->setText( res);
	}
	//item_->setToolTip( item_->text());
}

TestQbox::TestQbox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestQbox)
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
	std::string str;
	char c = -12;
	str += c;
	str += c;
	str += c;
	str += c;
	addResponseRow( std::string("hello"), str );
	addResponseRow( std::string("hello1"), std::string("test"));
	addResponseRow( std::string("hello2"), std::string("test"));
}

TestQbox::~TestQbox()
{
    delete ui;
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

void TestQbox::addResponseRow( std::string & key, std::string & data ){
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