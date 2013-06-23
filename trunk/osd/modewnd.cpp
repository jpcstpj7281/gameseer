#include "ModeWnd.h"
#include "ui_ModeWnd.h"
#include <qdebug.h>
#include "mode.h"
#include "ring.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>



ModeWidget::ModeWidget(Mode* mode):QWidget(0),mode_(mode)
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


	id_->setFlags( Qt::ItemIsEnabled );

	if ( mode_){
		id_->setText( QString::fromStdString(mode_->id_));
	}
	save_ = new  QPushButton;
	save_->setText("Save");
	activate_ = new  QPushButton;
	activate_->setText("Activate");
	connect( save_, SIGNAL(clicked()), this, SLOT(saveMode()) );
	connect( activate_, SIGNAL(clicked()), this, SLOT(activeMode()) );
	if ( !mode_){
		save_->setEnabled(false);
		activate_->setEnabled(false);
	}
}
void ModeWidget::saveMode(){
	if ( mode_){
		mode_->save();

	}
}
void ModeWidget::activeMode(){
	if ( mode_){
		mode_->activate();
	}
}

void ModeWidget::initTable( QTableWidget* table, int row){
	table->setCellWidget ( row, 0, this);
	table->setItem ( row, 1, id_ );
	table->setCellWidget ( row, 2, activate_);
	table->setCellWidget ( row, 3, save_);
}
void ModeWidget::clickInsert(){
	QTableWidget* table = id_->tableWidget();
	if (  table){
		Mode* mode = ModeMgr::instance()->createMode();
		ModeWidget * wgt = new ModeWidget(  mode);
		int row = id_->row();
		table->insertRow( row);
		wgt->initTable(table, row);
	}
}
void ModeWidget::clickDelete(){
	QTableWidget* table = id_->tableWidget();
	if ( id_->row() != table->rowCount()-1 && table){
		if (mode_){
			ModeMgr::instance()->removeMode(mode_);
		}
		table->removeRow( id_->row());
	}
}

//==============================================================================================================================
ModeWnd::ModeWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::ModeWnd)
	,currMode_(0)
{
    ui->setupUi(this);

	modeTable_ = findChild<QTableWidget* >("modeTable");
    modeTable_->setColumnCount( 4);
	QStringList sl;
	sl.push_back( "");
	sl.push_back( "ID");
	sl.push_back( "Activate");
	sl.push_back( "Save");

	modeTable_->setHorizontalHeaderLabels(sl );
	modeTable_->setColumnWidth( 0, 20);
	modeTable_->setColumnWidth( 1, 100);

	wndModeTable_ = findChild<QTableWidget* >("wndModeTable");
	wndModeTable_->setColumnCount( 11);
	sl.clear();
	sl.push_back( "X");
	sl.push_back( "Y");
	sl.push_back( "W");
	sl.push_back( "H");
	sl.push_back( "AX");
	sl.push_back( "AY");
	sl.push_back( "AW");
	sl.push_back( "AH");
	sl.push_back( "Wnd");
	sl.push_back( "Input");
	sl.push_back( "Ring");
	wndModeTable_->setColumnWidth( 0, 40);
	wndModeTable_->setColumnWidth( 1, 40);
	wndModeTable_->setColumnWidth( 2, 40);
	wndModeTable_->setColumnWidth( 3, 40);
	wndModeTable_->setColumnWidth( 4, 40);
	wndModeTable_->setColumnWidth( 5, 40);
	wndModeTable_->setColumnWidth( 6, 40);
	wndModeTable_->setColumnWidth( 7, 40);
	wndModeTable_->setColumnWidth( 8, 40);
	wndModeTable_->setColumnWidth( 9, 80);
	wndModeTable_->setColumnWidth( 10, 40);
	wndModeTable_->setHorizontalHeaderLabels(sl);
	

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );

	connect(modeTable_, SIGNAL(cellClicked(int,int)), this, SLOT(cellClicked (int,int)) );
}

ModeWnd::~ModeWnd()
{
    delete ui;
}
void ModeWnd::resetModeTable(){
	modeTable_->setRowCount(0);
	newMode("");
	std::vector<Mode*> modes = ModeMgr::instance()->getAllModes();
	for ( size_t i = 0 ; i <modes.size(); ++i){
		newMode( modes[i]->id_);
	}
}
void ModeWnd::currentTabChanged ( int index ){
	QTabWidget* tab = (QTabWidget*)sender();
	if (tab->tabText(index) == "Modes"){
		resetModeTable();
		resetWndModeTable(currMode_);
	}
}

void ModeWnd::newMode( const std::string &modeid){
	ModeWidget * wgt = 0;
	if ( modeTable_->rowCount()>0){
		wgt= (ModeWidget*) modeTable_->cellWidget( modeTable_->rowCount()-1, 0);
	}
	int insertRow = 0;
	if ( wgt==0 ){
		insertRow = 1;
	}else if (wgt->id_->text().isEmpty()  ){//最后一行已经是空IP
		if ( modeid.empty() ) return;	//无需操作
		else {
			insertRow = modeTable_->rowCount()-1;//在空行前插入
			modeTable_->insertRow( insertRow);
			++insertRow;
		}
	}else{//最后一行非空IP
		if ( modeid.empty() ) 
			insertRow = modeTable_->rowCount()+1;
		else 
			insertRow = modeTable_->rowCount();
	}

	if (ModeMgr::instance()->hasMode(modeid)){
		wgt = new ModeWidget( ModeMgr::instance()->getMode(modeid) );
	}else if ( !modeid.empty()  ){
		wgt = new ModeWidget( ModeMgr::instance()->createMode(modeid) );
	}else{
		wgt = new ModeWidget(NULL);
	}

	if ( insertRow > modeTable_->rowCount()){
		modeTable_->setRowCount(insertRow);  
	}
	wgt->initTable(modeTable_,  insertRow-1);
}

void ModeWnd::resetWndModeTable( Mode* mode){
	currMode_ = mode;
	wndModeTable_->setRowCount(0);
	if (mode == NULL)return;
	for ( size_t i = 0 ; i <mode->wnds_.size(); ++i){
		newWnd( &mode->wnds_[i]);
	}
}

void ModeWnd::newWnd( WndData* wnd){

	int row = wndModeTable_->rowCount()+1;
	wndModeTable_->setRowCount(row);  
	wndModeTable_->setItem( row - 1, 0, new QTableWidgetItem(QString::number(wnd->xPercent_, 'g', 2)));
	wndModeTable_->setItem( row - 1, 1, new QTableWidgetItem(QString::number(wnd->yPercent_, 'g', 2)));
	wndModeTable_->setItem( row - 1, 2, new QTableWidgetItem(QString::number(wnd->wPercent_, 'g', 2)));
	wndModeTable_->setItem( row - 1, 3, new QTableWidgetItem(QString::number(wnd->hPercent_, 'g', 2)));
	wndModeTable_->setItem( row - 1, 4, new QTableWidgetItem(QString::number(wnd->axPercent_, 'g', 2)));
	wndModeTable_->setItem( row - 1, 5, new QTableWidgetItem(QString::number(wnd->ayPercent_, 'g', 2)));
	wndModeTable_->setItem( row - 1, 6, new QTableWidgetItem(QString::number(wnd->awPercent_, 'g', 2)));
	wndModeTable_->setItem( row - 1, 7, new QTableWidgetItem(QString::number(wnd->ahPercent_, 'g', 2)));
	wndModeTable_->setItem( row - 1, 8, new QTableWidgetItem(QString::fromStdString(wnd->wndid_)));
	wndModeTable_->setItem( row - 1, 9, new QTableWidgetItem(QString::fromStdString(ToStrID(wnd->inputid_))));
	wndModeTable_->setItem( row - 1, 10, new QTableWidgetItem(QString::fromStdString(wnd->ringid_)));
}

void ModeWnd::cellClicked(int row,int col){
	ModeWidget * wgt = 0;
	wndModeTable_->setRowCount(0);
	if ( modeTable_->rowCount()>0){
		wgt= (ModeWidget*) modeTable_->cellWidget( row, 0);
		if ( wgt && wgt->mode_)
			resetWndModeTable( wgt->mode_);
	}
}
