#include "RingWnd.h"
#include "ui_RingWnd.h"
#include <qdebug.h>
#include "screen.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

RingWidget::RingWidget(Ring* ring):QWidget(0),ring_(ring)
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
	if (ring){
		id_->setText( QString::fromStdString(ring->id_));
	}
}
void RingWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setItem ( row, 1, id_ );

}
void RingWidget::clickInsert(){
	QTableWidget* table = id_->tableWidget();
	if (ScreenMgr::instance()->getColCount() <=1 && ScreenMgr::instance()->getRowCount() <=1){
		QMessageBox::warning(this, "Error!", "Ring only support for a wall with multiple screens!");
		return ;
	}
	if (  table  ){
		RingWidget * wgt = new RingWidget( RingMgr::instance()->createRing() );
		int row = id_->row();
		table->insertRow( row);
		wgt->initTable(table, row);
	}
}
void RingWidget::clickDelete(){
	QTableWidget* table = id_->tableWidget();
	if ( id_->row() != table->rowCount()-1 && table){
		RingMgr::instance()->removeRing(ring_);
		table->removeRow( id_->row());
	}
}
//==============================================================================================================================
RnodeWidget::RnodeWidget(Ring* ring, ResourceID rnode):QWidget(0),ring_(ring),rnode_(rnode)
{
	QVBoxLayout* layout = new QVBoxLayout();
	layout->setMargin(0);
	layout->setSpacing(0);
	QPushButton* add = new  QPushButton;
	QPushButton* remove = new  QPushButton;
	add->setText("+");
	add->setEnabled(false);
	remove->setText("-");
	layout->addWidget(add );
	layout->addWidget(remove );
	setLayout(layout);
	connect( add, SIGNAL(clicked()), this, SLOT(clickInsert()) );
	connect( remove, SIGNAL(clicked()), this, SLOT(clickDelete()) );
	this->setEnabled(false);

	hide_ = new QTableWidgetItem();
	col_ = new QComboBox();
	row_ = new QComboBox();
	input_ = new QComboBox();
	output_ = new QComboBox();
	connect( col_, SIGNAL(currentIndexChanged(int)), this, SLOT(currentColIndexChanged(int)) );
	connect( row_, SIGNAL(currentIndexChanged(int)), this, SLOT(currentRowIndexChanged(int)) );
	connect( input_, SIGNAL(currentIndexChanged(int)), this, SLOT(currentInputIndexChanged(int)) );
	connect( output_, SIGNAL(currentIndexChanged(int)), this, SLOT(currentOutputIndexChanged(int)) );

	col_->addItem("-");
	for( size_t i = 0; i < ScreenMgr::instance()->getColCount(); ++i ){
		col_->addItem(QString::number(1+i));
	}
	row_->addItem("-");
	for( size_t i = 0; i < ScreenMgr::instance()->getRowCount(); ++i ){
		row_->addItem(QString::number(1+i));
	}
	input_->addItem("-");
	for( size_t i = 0; i < 6; ++i ){
		input_->addItem(QString::number(1+i));
	}
	output_->addItem("-");
	for( size_t i = 0; i < 2; ++i ){
		output_->addItem(QString::number(1+i));
	}

	if ( rnode ){
		col_->setCurrentIndex( GetCol(rnode) -1);
		row_->setCurrentIndex( GetRow(rnode) -1);
	}else{
		input_->setEnabled(false);
		output_->setEnabled(false);
		col_->setCurrentIndex( 0);
		row_->setCurrentIndex( 0);
	}

}
void RnodeWidget::clickInsert(){
	QTableWidget* table = hide_->tableWidget();
	if (  table){
		RnodeWidget * wgt = new RnodeWidget( ring_ );
		int row = hide_->row();
		table->insertRow( row);
		wgt->initTable(table, row);
		wgt->output_->setCurrentIndex( output_->currentIndex());
	}
}
void RnodeWidget::clickDelete(){
	QTableWidget* table = hide_->tableWidget();
	if ( hide_->row() != table->rowCount()-1 && table){
		if (ring_){
			ring_->removeNode( ToResourceID(input_->currentIndex(), output_->currentIndex(), row_->currentIndex(), col_->currentIndex()) );
		}
		table->removeRow( hide_->row());
	}
}
void RnodeWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setCellWidget ( row, 1, col_ );
	table->setCellWidget ( row, 2, row_ );
	table->setCellWidget ( row, 3, input_ );
	table->setCellWidget ( row, 4, output_ );
	table->setItem(row, 5, hide_);

}
void RnodeWidget::enableRow(){
	if (row_->currentIndex() && col_->currentIndex()){
		input_->setEnabled(true);
		output_->setEnabled(true);
	}
}
void RnodeWidget::newNextRow(){ //after input or output setted, should open another row to setup.
	if ( output_->currentIndex()){
		if ( input_->currentIndex() || hide_->tableWidget()->rowCount()==1){
			
			QTableWidget* table = hide_->tableWidget();
		
			rnode_ = ToResourceID( input_->currentIndex(), output_->currentIndex()+2,  row_->currentIndex(), col_->currentIndex());
			if (ring_->makeNode( rnode_, table->rowCount()-1)){
				if (  table ){
					if (ring_->isNextNodePossible()){
						this->setEnabled(true);
						col_->setEnabled(false);
						row_->setEnabled(false);
						RnodeWidget * wgt = new RnodeWidget( ring_ );
						int row = hide_->row()+1;
						table->insertRow( row);
						wgt->initTable(table, row);
					}
				}
			}
		}
	}
}
void RnodeWidget::currentColIndexChanged ( int index ){
	if(ring_){
		enableRow();
		if (ring_->isNextNodePossible( row_->currentIndex(), index)){
			newNextRow();
		}
	}
}
void RnodeWidget::currentRowIndexChanged ( int index ){
	if(ring_){
		enableRow();
		if (ring_->isNextNodePossible(index , col_->currentIndex())){
			newNextRow();
		}
	}
}
void RnodeWidget::currentInputIndexChanged ( int index ){
	if(ring_){
		if (ScreenMgr::instance()->isInputValid(ToResourceID( index, 0,  row_->currentIndex(), col_->currentIndex()))){
			newNextRow();
		}
	}
}
void RnodeWidget::currentOutputIndexChanged ( int index ){
	if(ring_){
		if (ScreenMgr::instance()->isOutputRingValid(ToResourceID( 0, index+2,  row_->currentIndex(), col_->currentIndex()))){
			newNextRow();
		}
	}
}

//==============================================================================================================================
RingWnd::RingWnd(QTabWidget* parent) :
    QWidget(parent)
	,ui(new Ui::RingWnd)
	,currRing_(0)
{
    ui->setupUi(this);

	ringTable_ = findChild<QTableWidget* >("ringTable");
    ringTable_->setColumnCount( 4);
	QStringList sl;
	sl.push_back( "");
	sl.push_back( "Ring");
	sl.push_back( "Compatible");
	sl.push_back( "Collided");
	ringTable_->setHorizontalHeaderLabels(sl );
	ringTable_->setColumnWidth( 0, 20);
	ringTable_->setColumnWidth( 1, 100);
	ringTable_->setColumnWidth( 2, 100);
	ringTable_->setColumnWidth( 2, 100);

	connect( ringTable_, SIGNAL(cellChanged(int,int)), this, SLOT(cellChanged(int,int)));
	connect( ringTable_, SIGNAL(cellClicked(int,int)), this, SLOT(cellClicked(int,int)));
	newRing("");

	rnodeTable_ = findChild<QTableWidget* >("rnodeTable");
    rnodeTable_->setColumnCount( 6);
	sl.clear();
	sl.push_back( "");
	sl.push_back( "Col");
	sl.push_back( "Row");
	sl.push_back( "Input");
	sl.push_back( "Output");
	sl.push_back( "");
	rnodeTable_->setHorizontalHeaderLabels(sl );
	rnodeTable_->setColumnWidth( 0, 20);
	rnodeTable_->setColumnWidth( 1, 100);
	rnodeTable_->setColumnWidth( 2, 100);
	rnodeTable_->setColumnWidth( 3, 100);
	rnodeTable_->setColumnWidth( 4, 100);
	rnodeTable_->setColumnWidth( 5, 0);
	//newRnode();

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );
}

RingWnd::~RingWnd()
{
    delete ui;
}
void RingWnd::currentTabChanged ( int index ){
	
	QTabWidget* tab = (QTabWidget*)sender();
	if (tab->tabText(index) == "Rings"){
		resetRingTable();
		resetRnodeTable( currRing_);
	}
}
void RingWnd::resetRingTable(){
	ringTable_->setRowCount(0);
	newRing("");
	std::vector<Ring*> rings = RingMgr::instance()->getRings();
	for ( size_t i = 0 ; i <rings.size(); ++i){
		newRing( rings[i]->id_);
	}
}
//clear the list of rnodes, and restore the new sets.
void RingWnd::resetRnodeTable( Ring* ring){
	currRing_ = ring;
	rnodeTable_->setRowCount(0);
	if (ring == NULL)return;
	std::vector<ResourceID> nodes = ring->getRnodes();
	if ( nodes.size() == 0){
		RnodeWidget* wgt = new RnodeWidget( currRing_ );
		rnodeTable_->setRowCount(rnodeTable_->rowCount()+1);  
		wgt->initTable(rnodeTable_,  rnodeTable_->rowCount()-1);
		return;
	}else{

		for ( size_t i = 0; i < nodes.size(); ++i){
			RnodeWidget* wgt = new RnodeWidget( currRing_ );
			rnodeTable_->setRowCount(rnodeTable_->rowCount()+1);  
			wgt->initTable(rnodeTable_,  rnodeTable_->rowCount()-1);
			wgt->col_->setCurrentIndex(GetCol(nodes[i]));
			wgt->row_->setCurrentIndex(GetRow(nodes[i]));
			wgt->input_->setCurrentIndex(GetInput(nodes[i]));
			wgt->output_->setCurrentIndex(GetOutput(nodes[i])>2?GetOutput(nodes[i])-2:0);
		}
		if ( currRing_->isNextNodePossible()){
			RnodeWidget* wgt = new RnodeWidget( currRing_ );
			rnodeTable_->setRowCount(rnodeTable_->rowCount()+1);  
			wgt->initTable(rnodeTable_,  rnodeTable_->rowCount()-1);
		}
	}
}

void RingWnd::cellClicked(int row,int col){
	RingWidget * wgt = (RingWidget*)ringTable_->cellWidget( row, 0);
	if ( wgt->ring_){
		resetRnodeTable(wgt->ring_);
	}else{
		rnodeTable_->setRowCount(0);
	}
}
void RingWnd::cellChanged(int row,int col){
	if ( col == 1){
		RingWidget * wgt = (RingWidget*)ringTable_->cellWidget( row, 0);
		if ( wgt->ring_){
			wgt->ring_->id_ = wgt->id_->text().toStdString();
			return;
		}
		if (!wgt->id_->text().isEmpty()){
			if ( !RingMgr::instance()->hasRing(wgt->id_->text().toStdString())){
				wgt->ring_ = RingMgr::instance()->createRing(wgt->id_->text().toStdString());
				newRing("");
			}else{
				wgt->id_->setText("");
			}
		}
	}
}

void RingWnd::newRing( const std::string &ringid){
	RingWidget * wgt = 0;
	if ( ringTable_->rowCount()>0){
		wgt= (RingWidget*) ringTable_->cellWidget( ringTable_->rowCount()-1, 0);
	}
	int insertRow = 0;
	if ( wgt==0 ){
		insertRow = 1;
	}else if (wgt->id_->text().isEmpty()  ){//最后一行已经是空IP
		if ( ringid.empty() ) return;	//无需操作
		else {
			insertRow = ringTable_->rowCount()-1;//在空行前插入
			ringTable_->insertRow( insertRow);
			++insertRow;
		}
	}else{//最后一行非空IP
		if ( ringid.empty() ) 
			insertRow = ringTable_->rowCount()+1;
		else 
			insertRow = ringTable_->rowCount();
	}

	if (RingMgr::instance()->hasRing(ringid)){
		wgt = new RingWidget( RingMgr::instance()->getRing(ringid) );
	}else if ( !ringid.empty()  ){
		wgt = new RingWidget( RingMgr::instance()->createRing(ringid) );
	}else{
		wgt = new RingWidget(NULL);
	}

	if ( insertRow > ringTable_->rowCount()){
		ringTable_->setRowCount(insertRow);  
	}
	wgt->initTable(ringTable_,  insertRow-1);
}

