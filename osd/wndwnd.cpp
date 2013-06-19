#include "WndWnd.h"
#include "ui_WndWnd.h"
#include <qdebug.h>
#include "screen.h"
#include "ring.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

WnodeWidget::WnodeWidget(Wnd* wnd, ResourceID wnode):QWidget(0),wnd_(wnd),wnode_(wnode)
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

	Wnode * wn = wnd_->getWnode( wnode_);

	id_->setText( QString::fromStdString(ToStrID(wnode_)));
	x_->setText( QString::number( wn->xp_));
	y_->setText( QString::number( wn->yp_));
	w_->setText( QString::number( wn->wp_));
	h_->setText( QString::number( wn->hp_));
	ax_->setText( QString::number( wn->axp_));
	ay_->setText( QString::number( wn->ayp_));
	aw_->setText( QString::number( wn->awp_));
	ah_->setText( QString::number( wn->ahp_));
	
}
void WnodeWidget::initTable( QTableWidget* table, int row){
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

	id_->setText( QString::fromStdString(wnd_->id_));
	x_->setText( QString::number( wnd_->getX()));
	y_->setText( QString::number( wnd_->getY()));
	w_->setText( QString::number( wnd_->getW()));
	h_->setText( QString::number( wnd_->getH()));
	ax_->setText( QString::number( wnd_->getAX()));
	ay_->setText( QString::number( wnd_->getAY()));
	aw_->setText( QString::number( wnd_->getAW()));
	ah_->setText( QString::number( wnd_->getAH()));
	
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
	wndTable_->setColumnWidth( 1, 80);
	wndTable_->setColumnWidth( 2, 35);
	wndTable_->setColumnWidth( 3, 35);
	wndTable_->setColumnWidth( 3, 35);
	wndTable_->setColumnWidth( 4, 35);
	wndTable_->setColumnWidth( 5, 35);
	wndTable_->setColumnWidth( 6, 35);
	wndTable_->setColumnWidth( 7, 35);
	wndTable_->setColumnWidth( 8, 35);
	wndTable_->setColumnWidth( 9, 35);

	wnodeTable_ = findChild<QTableWidget* >("wnodeTable");
    wnodeTable_->setColumnCount( 10);
	sl.clear();
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

	wnodeTable_->setHorizontalHeaderLabels(sl );
	wnodeTable_->setColumnWidth( 0, 0);
	wnodeTable_->setColumnWidth( 1, 80);
	wnodeTable_->setColumnWidth( 2, 35);
	wnodeTable_->setColumnWidth( 3, 35);
	wnodeTable_->setColumnWidth( 3, 35);
	wnodeTable_->setColumnWidth( 4, 35);
	wnodeTable_->setColumnWidth( 5, 35);
	wnodeTable_->setColumnWidth( 6, 35);
	wnodeTable_->setColumnWidth( 7, 35);
	wnodeTable_->setColumnWidth( 8, 35);
	wnodeTable_->setColumnWidth( 9, 35);

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );
	connect(wndTable_, SIGNAL(cellClicked(int,int)), this, SLOT(cellClicked (int,int)) );
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
void WndWnd::cellClicked ( int row, int column ){
	WndWidget* wgt = (WndWidget* )wndTable_->cellWidget( row, 0);
	if ( wgt){
		wnodeTable_->setRowCount(0);
		for ( size_t i = 0; i < wgt->wnd_->wnodes_.size();++i){
			WnodeWidget* wngt = new WnodeWidget(wgt->wnd_, wgt->wnd_->wnodes_[i]->wnodeid_);
			wnodeTable_->setRowCount(wnodeTable_->rowCount()+1);  
			wngt->initTable(wnodeTable_,  wnodeTable_->rowCount()-1);
		}
	}
}
