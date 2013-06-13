#include "WndWnd.h"
#include "ui_WndWnd.h"
#include <qdebug.h>
#include "screen.h"
#include "ring.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>


WndWidget::WndWidget(Wnd* wnd):QWidget(0),wnd_(wnd)
{
	QVBoxLayout* layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->setSpacing(0);
	QPushButton* add = new  QPushButton;
	QPushButton* remove = new  QPushButton;
	add->setText("+");
	remove->setText("-");
	layout->addWidget(add );
	layout->addWidget(remove );
	setLayout(layout);
	//connect( add, SIGNAL(clicked()), this, SLOT(clickInsert()) );
	//connect( remove, SIGNAL(clicked()), this, SLOT(clickDelete()) );

	id_= new QTableWidgetItem();
	x_= new QTableWidgetItem();
	y_= new QTableWidgetItem();
	w_= new QTableWidgetItem();
	h_= new QTableWidgetItem();
	ax_= new QTableWidgetItem();
	ay_= new QTableWidgetItem();
	aw_= new QTableWidgetItem();
	ah_= new QTableWidgetItem();
	

	id_->setFlags( Qt::ItemIsEnabled );
	x_->setFlags( Qt::ItemIsEnabled );
	y_->setFlags( Qt::ItemIsEnabled );
	w_->setFlags( Qt::ItemIsEnabled );
	h_->setFlags( Qt::ItemIsEnabled );
	ax_->setFlags( Qt::ItemIsEnabled );
	ay_->setFlags( Qt::ItemIsEnabled );
	aw_->setFlags( Qt::ItemIsEnabled );
	ah_->setFlags( Qt::ItemIsEnabled );

	id_->setText( QString::fromStdString(ToInputStrID(inputid_)));
	
}
void WndWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setItem ( row, 1, id_ );
	table->setItem ( row, 2, x_ );
	table->setItem ( row, 3, y_ );
	table->setItem ( row, 4, w_ );
	table->setItem ( row, 5, h_ );
	table->setItem ( row, 6, ax_ );
	table->setItem ( row, 7, ay_ );
	table->setItem ( row, 8, aw_ );
	table->setItem ( row, 9, ah_ );
	

}


//==============================================================================================================================

WndWnd::WndWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::WndWnd)
{
    ui->setupUi(this);

	wndTable_ = findChild<QTableWidget* >("wndTable");
    wndTable_->setColumnCount( 10);
	QStringList sl;
	sl.push_back( "");
	sl.push_back( "ID");
	sl.push_back( "X");
	sl.push_back( "Y");
	sl.push_back( "W");
	sl.push_back( "H");
	sl.push_back( "AX");
	sl.push_back( "AY");
	sl.push_back( "AW");
	sl.push_back( "AH");

	wndTable_->setHorizontalHeaderLabels(sl );
	wndTable_->setColumnWidth( 0, 0);
	wndTable_->setColumnWidth( 1, 100);
	wndTable_->setColumnWidth( 2, 50);
	wndTable_->setColumnWidth( 3, 50);
	wndTable_->setColumnWidth( 3, 50);
	wndTable_->setColumnWidth( 4, 50);
	wndTable_->setColumnWidth( 5, 50);
	wndTable_->setColumnWidth( 6, 50);
	wndTable_->setColumnWidth( 7, 50);
	wndTable_->setColumnWidth( 8, 50);
	wndTable_->setColumnWidth( 9, 50);

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );
}

WndWnd::~WndWnd()
{
    delete ui;
}

void WndWnd::currentTabChanged ( int index ){
	wndTable_->setRowCount(0);
	std::vector<Wnd*> wnds = WndMgr::instance()->getAllWnds();
	for ( size_t i = 0; i < wnds.size(); ++i){
		WndWidget* wgt = new WndWidget(wnds[i]);
		wndTable_->setRowCount(wndTable_->rowCount()+1);  
		wgt->initTable(wndTable_,  wndTable_->rowCount()-1);
	}

}