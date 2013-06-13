#include "ChnWnd.h"
#include "ui_ChnWnd.h"
#include <qdebug.h>
#include "screen.h"
#include "ring.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>



ChnWidget::ChnWidget(ResourceID inputid):QWidget(0),inputid_(inputid)
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
	connect( add, SIGNAL(clicked()), this, SLOT(clickInsert()) );
	connect( remove, SIGNAL(clicked()), this, SLOT(clickDelete()) );

	id_= new QTableWidgetItem();
	col_= new QTableWidgetItem();
	row_= new QTableWidgetItem();
	width_= new QTableWidgetItem();
	height_= new QTableWidgetItem();
	inport_ = new QTableWidgetItem();

	id_->setFlags( Qt::ItemIsEnabled );
	col_->setFlags( Qt::ItemIsEnabled );
	row_->setFlags( Qt::ItemIsEnabled );
	width_->setFlags( Qt::ItemIsEnabled );
	height_->setFlags( Qt::ItemIsEnabled );
	inport_->setFlags( Qt::ItemIsEnabled );

	id_->setText( QString::fromStdString(ToInputStrID(inputid_)));
	row_->setText( QString::number( GetRow(inputid_)));
	col_->setText( QString::number( GetCol(inputid_)));
	width_->setText( QString::number( GetWidth(ScreenMgr::instance()->getInResolution(inputid_))));
	height_->setText( QString::number( GetHeight(ScreenMgr::instance()->getInResolution(inputid_))));
	inport_->setText(  QString::number( GetInput(inputid_)));

	std::vector<Ring*> rings = RingMgr::instance()->getInputCorrespondRing( inputid_);
	if ( rings.size() >0){
		id_->setBackgroundColor( Qt::lightGray);
		col_->setBackgroundColor( Qt::lightGray);
		row_->setBackgroundColor( Qt::lightGray);
		width_->setBackgroundColor( Qt::lightGray);
		height_->setBackgroundColor( Qt::lightGray);
		inport_->setBackgroundColor( Qt::lightGray);
	}
}
void ChnWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setItem ( row, 1, id_ );
	table->setItem ( row, 2, row_ );
	table->setItem ( row, 3, col_ );
	table->setItem ( row, 4, inport_ );
	table->setItem ( row, 5, width_ );
	table->setItem ( row, 6, height_ );
	

}


//==============================================================================================================================
ChnWnd::ChnWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::ChnWnd)
{
    ui->setupUi(this);

	chnTable_ = findChild<QTableWidget* >("chnTable");
    chnTable_->setColumnCount( 7);
	QStringList sl;
	sl.push_back( "");
	sl.push_back( "ID");
	sl.push_back( "Row");
	sl.push_back( "Col");
	sl.push_back( "Inport");
	sl.push_back( "Width");
	sl.push_back( "Height");
	chnTable_->setHorizontalHeaderLabels(sl );
	chnTable_->setColumnWidth( 0, 0);
	chnTable_->setColumnWidth( 1, 100);
	chnTable_->setColumnWidth( 2, 50);
	chnTable_->setColumnWidth( 3, 50);
	chnTable_->setColumnWidth( 3, 50);
	chnTable_->setColumnWidth( 4, 50);
	chnTable_->setColumnWidth( 5, 50);

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );
}

ChnWnd::~ChnWnd()
{
    delete ui;
}

void ChnWnd::currentTabChanged ( int index ){
	chnTable_->setRowCount(0);
	inputs_ = ScreenMgr::instance()->getAvailableInput();
	for ( size_t i = 0; i < inputs_.size(); ++i){
		ChnWidget* wgt = new ChnWidget(inputs_[i]);
		chnTable_->setRowCount(chnTable_->rowCount()+1);  
		wgt->initTable(chnTable_,  chnTable_->rowCount()-1);
	}

}