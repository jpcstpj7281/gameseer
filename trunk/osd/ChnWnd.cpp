#include "ChnWnd.h"
#include "ui_ChnWnd.h"
#include <qdebug.h>
#include "screen.h"
#include "ring.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <functional>
#include <qdebug.h>
#include <Windows.h>
using namespace std::placeholders;

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
	//connect( add, SIGNAL(clicked()), this, SLOT(clickInsert()) );
	//connect( remove, SIGNAL(clicked()), this, SLOT(clickDelete()) );

	id_= new QTableWidgetItem();
	col_= new QTableWidgetItem();
	row_= new QTableWidgetItem();
	width_= new QTableWidgetItem();
	height_= new QTableWidgetItem();
	freq_ = new QTableWidgetItem(); 
	inport_ = new QTableWidgetItem();

	id_->setFlags( Qt::ItemIsEnabled );
	col_->setFlags( Qt::ItemIsEnabled );
	row_->setFlags( Qt::ItemIsEnabled );
	width_->setFlags( Qt::ItemIsEnabled );
	height_->setFlags( Qt::ItemIsEnabled );
	freq_->setFlags( Qt::ItemIsEnabled );
	inport_->setFlags( Qt::ItemIsEnabled );

	id_->setText( QString::fromStdString(ToStrID(inputid_)));
	row_->setText( QString::number( GetRow(inputid_)));
	col_->setText( QString::number( GetCol(inputid_)));
	width_->setText( QString::number( GetWidth(ScreenMgr::instance()->getInResolution(inputid_))));
	height_->setText( QString::number( GetHeight(ScreenMgr::instance()->getInResolution(inputid_))));
	freq_->setText( QString::number( GetFreq(ScreenMgr::instance()->getInResolution(inputid_))));
	inport_->setText(  QString::number( GetInput(inputid_)));

	std::vector<Ring*> rings = RingMgr::instance()->getInputCorrespondRing( inputid_);
	if ( rings.size() >0){
		id_->setBackgroundColor( Qt::lightGray);
		col_->setBackgroundColor( Qt::lightGray);
		row_->setBackgroundColor( Qt::lightGray);
		width_->setBackgroundColor( Qt::lightGray);
		height_->setBackgroundColor( Qt::lightGray);
		freq_->setBackgroundColor( Qt::lightGray);
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
	table->setItem ( row, 7, freq_ );
}


//==============================================================================================================================
ChnWnd::ChnWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::ChnWnd)
	,isCurrTab_(false)
{
    ui->setupUi(this);
	startTimer(3000);
	chnTable_ = findChild<QTableWidget* >("chnTable");
    chnTable_->setColumnCount( 8);
	QStringList sl;
	sl.push_back( "");
	sl.push_back( "ID");
	sl.push_back( tr("Row"));
	sl.push_back( tr("Col"));
	sl.push_back( tr("Inport"));
	sl.push_back( tr("Width"));
	sl.push_back( tr("Height"));
	sl.push_back( tr("Freq"));
	chnTable_->setHorizontalHeaderLabels(sl );
	chnTable_->setColumnWidth( 0, 0);
	chnTable_->setColumnWidth( 1, 100);
	chnTable_->setColumnWidth( 2, 50);
	chnTable_->setColumnWidth( 3, 50);
	chnTable_->setColumnWidth( 3, 50);
	chnTable_->setColumnWidth( 4, 50);
	chnTable_->setColumnWidth( 5, 50);
	chnTable_->setColumnWidth( 6, 50);
	chnTable_->setColumnWidth( 7, 50);

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );

	QPushButton* setVideo = this->findChild<QPushButton* >("pbSetVideo");
	if ( setVideo){
		connect(setVideo, SIGNAL(clicked()), this, SLOT(clickedSetVideo ()) );
	}
}
bool ChnWnd::setVideoCallback( uint32_t , QboxDataMap data){
	if ( data["error"] == "0"){
	}
	return true;
}
void ChnWnd::clickedSetVideo (){
	QSpinBox* chncol = this->findChild<QSpinBox* >("sbChnCol");
	chncol->setMaximum(ScreenMgr::instance()->getColCount() );
	QSpinBox* chnrow = this->findChild<QSpinBox* >("sbChnRow");
	chnrow->setMaximum(ScreenMgr::instance()->getRowCount() );
	QSpinBox* chninput = this->findChild<QSpinBox* >("sbChnInput");
	size_t row = chnrow->value();
	size_t col = chncol->value();
	size_t input = chninput->value();

	//bool existed = ScreenMgr::instance()->hasAvailableInput( ToResourceID( input, 0, row, col) );
	//if ( existed ){
	//	QMessageBox::warning(0, "Wanning", "Input Channel already existed!");
	//}else{
		Screen* srn = ScreenMgr::instance()->getScreen(ToResourceID(0, 0, row, col) );
		if (srn){
			int type = this->findChild<QComboBox* >("cbVideoType")->currentIndex();
			srn->setVideoRequest(input, type, std::bind( &ChnWnd::setVideoCallback, this, _1, _2));
			srn->inputRequest();
		}
	//}
}

ChnWnd::~ChnWnd()
{
    delete ui;
}

void ChnWnd::currentTabChanged ( int index ){
	QTabWidget* tab = (QTabWidget*)sender();
	isCurrTab_ = false;
	if ( tab->tabText(index) != this->windowTitle()) return ;
	isCurrTab_ = true;
	chnTable_->setRowCount(0);
	inputs_ = ScreenMgr::instance()->getAvailableInput();
	for ( size_t i = 0; i < inputs_.size(); ++i){
		ChnWidget* wgt = new ChnWidget(inputs_[i]);
		chnTable_->setRowCount(chnTable_->rowCount()+1);  
		wgt->initTable(chnTable_,  chnTable_->rowCount()-1);
	}
	QSpinBox* chncol = this->findChild<QSpinBox* >("sbChnCol");
	QSpinBox* chnrow = this->findChild<QSpinBox* >("sbChnRow");
	QSpinBox* chninput = this->findChild<QSpinBox* >("sbChnInput");
	if ( ScreenMgr::instance()->getColCount()  > 0 && ScreenMgr::instance()->getColCount() >0){
		chncol->setEnabled(true);
		chncol->setEnabled(true);
		chncol->setEnabled(true);
		chncol->setMaximum(1 );
		chncol->setMaximum(ScreenMgr::instance()->getColCount() );
		chnrow->setMaximum(1 );
		chnrow->setMaximum(ScreenMgr::instance()->getRowCount() );
	}else{
		chncol->setEnabled(false);
		chncol->setEnabled(false);
		chncol->setEnabled(false);
	}

}

void ChnWnd::timerEvent ( QTimerEvent *  ){
	if (!isCurrTab_) return;
	chnTable_->setRowCount(0);
	inputs_ = ScreenMgr::instance()->getAvailableInput();
	for ( size_t i = 0; i < inputs_.size(); ++i){
		ChnWidget* wgt = new ChnWidget(inputs_[i]);
		chnTable_->setRowCount(chnTable_->rowCount()+1);  
		wgt->initTable(chnTable_,  chnTable_->rowCount()-1);
	}
}