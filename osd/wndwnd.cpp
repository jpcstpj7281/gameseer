#include "WndWnd.h"
#include "ui_WndWnd.h"
#include <qdebug.h>
#include "screen.h"
#include "ring.h"
#include "wnd.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <boost/math/special_functions/round.hpp>
using namespace std::placeholders;

WnodeWidget::WnodeWidget(Wnd* wnd, ResourceID wnode):QWidget(0)
	,wnd_(wnd)
	,wnode_(wnode)
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
	x_->setText( QString::number(boost::math::round( wn->xp_ * ScreenMgr::instance()->getWallWidth())));
	y_->setText( QString::number(boost::math::round( wn->yp_* ScreenMgr::instance()->getWallHeight())));
	w_->setText( QString::number(boost::math::round( wn->wp_* ScreenMgr::instance()->getWallWidth())));
	h_->setText( QString::number(boost::math::round( wn->hp_* ScreenMgr::instance()->getWallHeight())));
	ax_->setText( QString::number( wn->axr_));
	ay_->setText( QString::number( wn->ayr_));
	aw_->setText( QString::number( wn->awr_));
	ah_->setText( QString::number( wn->ahr_));
	
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
void WndChnQComboBox::mousePressEvent ( QMouseEvent * e ){
	isPressed_ = true;
	QComboBox::mousePressEvent(e);
}
//==============================================================================================================================
bool WndWidget::isPressed(){
	return input_->isPressed_;
}
WndWidget::WndWidget(Wnd* wnd):QWidget(0),wnd_(wnd)
	,input_(new WndChnQComboBox)
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

	input_->setEnabled(true);
	input_->addItem( QString::fromStdString(ToStrID( wnd_->inputid_)));
	input_->isPressed_ = false;
	std::vector<ResourceID> inputs = ScreenMgr::instance()->getAvailableInput();
	for( auto it = inputs.begin(); it != inputs.end(); ++it){
		if ( GetRow(wnd_->inputid_) == GetRow(*it) && GetCol(wnd_->inputid_) == GetCol(*it)){
			if ( wnd_->inputid_ != *it){
				input_->addItem( QString::fromStdString(ToStrID( *it)));
			}
		}
	}
	connect(input_, SIGNAL(activated(const QString &)), this, SLOT(currentInputIndexChanged (const QString &)) );
}
void WndWidget::currentInputIndexChanged (const QString & inputstr){
	std::vector<ResourceID> inputs = ScreenMgr::instance()->getAvailableInput();
	for( auto it = inputs.begin(); it != inputs.end(); ++it){
		if ( GetRow(wnd_->inputid_) == GetRow(*it) && GetCol(wnd_->inputid_) == GetCol(*it)){
			if ( wnd_->inputid_ != *it && inputstr.toStdString() == ToStrID(*it) ){
				double x = wnd_->xPercent_;
				double y = wnd_->yPercent_;
				double w = wnd_->wPercent_;
				double h = wnd_->hPercent_;
				double ax = wnd_->axPercent_;
				double ay = wnd_->ayPercent_;
				double aw = wnd_->awPercent_;
				double ah = wnd_->ahPercent_;
				Ring* ring = wnd_->ring_;
				WndMgr::instance()->closeWnd(wnd_);
				if ( ring){
					ring->activate( *it);
				}
				WndMgr::instance()->createWnd( x, y, w, h, *it, ring);
			}
		}
	}
	input_->isPressed_ = false;
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
	table->setCellWidget(row, 10, input_);

}


//==============================================================================================================================

WndWnd::WndWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::WndWnd)
	,isCurrTab_(false)
	,isDirectWndMode_(false)
{
    ui->setupUi(this);
	startTimer(1000);
	wndTable_ = findChild<QTableWidget* >("wndTable");
    wndTable_->setColumnCount( 11);
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
	sl.push_back( "Input");

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
	wndTable_->setColumnWidth( 10, 80);

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

	QPushButton* pbDirectWndMode = this->findChild<QPushButton* >("pbDirectWndMode");
	connect(pbDirectWndMode, SIGNAL(clicked()), this, SLOT(clickedDirectWndMode()) );

	ScreenMgr::instance()->onInputChanged( std::bind( &WndWnd::inputChangedCallback, this, _1) );

	//QComboBox* comboBox = findChild<QComboBox* >("comboBox");
	//connect(comboBox, SIGNAL(activated (const QString &)), this, SLOT(currentInputIndexChanged (const QString &)) );
}

WndWnd::~WndWnd()
{
    delete ui;
}
//void WndWnd::currentInputIndexChanged (const QString & inputstr){
//	qDebug()<<inputstr;
//}
void WndWnd::currentTabChanged ( int index ){
	QTabWidget* tab = (QTabWidget*)sender();
	isCurrTab_ = false;
	if ( tab->tabText(index) == "Wall" && tab->tabText(index) != this->windowTitle()) {
		if ( isDirectWndMode_){
			//QMessageBox::question(0, "Direct Window", "Have to turn off the direct window", QMessageBox::Ok, QMessageBox::Cancel);
			//clickedDirectWndMode();
		}
		return ;
	}
	isCurrTab_ = true;

	wndTable_->setRowCount(0);
	std::vector<Wnd*> wnds = WndMgr::instance()->getAllWnds();
	for ( size_t i = 0; i < wnds.size(); ++i){
		WndWidget* wgt = new WndWidget(wnds[i]);
		wndTable_->setRowCount(wndTable_->rowCount()+1);  
		wgt->initTable(wndTable_,  wndTable_->rowCount()-1);
	}

}
bool WndWnd::isChnComboBoxPressed(){
	bool result = false;
	for ( size_t i = 0; i < wndTable_->rowCount();++i){
		WndWidget* ww = (WndWidget*)wndTable_->cellWidget ( i, 0);
		if ( ww->isPressed()){
			result = true;
			break;
		}
	}
	return result;
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

static Wnd* createWnd(ResourceID inputid){
	double sWidth = ScreenMgr::instance()->getScreenWidth();
		double sHeight = ScreenMgr::instance()->getScreenHeight();
		double wWidth = ScreenMgr::instance()->getWallWidth();
		double wHeight = ScreenMgr::instance()->getWallHeight();
		size_t row = GetRow( inputid);
		size_t col = GetCol( inputid);
		double x =  sWidth * (col-1) / wWidth;
		double y =  sHeight * (row-1) / wHeight;
		double w =  sWidth  / wWidth;
		double h =  sHeight  / wHeight;
		Wnd *wnd = WndMgr::instance()->createWnd( x,y,w,h,inputid, NULL);
		return wnd;
}
void WndWnd::clickedDirectWndMode(){
	isDirectWndMode_ = !isDirectWndMode_;
	QPushButton* pbDirectWndMode = (QPushButton* )sender();
	if (isDirectWndMode_){
		pbDirectWndMode->setStyleSheet("* { background-color: lightGreen }");

		WndMgr::instance()->closeAll();

		std::vector<ResourceID> inputs = ScreenMgr::instance()->getAvailableInput();
		std::vector<ResourceID> uniqueInputs;
		for( auto it = inputs.begin(); it != inputs.end(); ++it){ //unique the screen input
			bool hasit = false;
			for( auto uit = uniqueInputs.begin(); uit != uniqueInputs.end(); ++uit ){
				if ( GetRow(*it) == GetRow(*uit) && GetCol(*it) == GetCol(*uit) ){
					hasit = true;
				}
			}
			if ( !hasit && GetInput(*it) < 5 ){
				uniqueInputs.push_back(*it);
			}
		}
		for( auto uit = uniqueInputs.begin(); uit != uniqueInputs.end(); ++uit ){//create wnd for unique input
			createWnd( *uit);
		}

	}else{
		pbDirectWndMode->setStyleSheet("");
		WndMgr::instance()->closeAll();
	}
}
void WndWnd::timerEvent ( QTimerEvent * event ){
	if (!isCurrTab_) return;
	
	if ( isChnComboBoxPressed()) return;

	wndTable_->setRowCount(0);
	std::vector<Wnd*> wnds = WndMgr::instance()->getAllWnds();
	for ( size_t i = 0; i < wnds.size(); ++i){
		WndWidget* wgt = new WndWidget(wnds[i]);
		wndTable_->setRowCount(wndTable_->rowCount()+1);  
		wgt->initTable(wndTable_,  wndTable_->rowCount()-1);
	}
}
bool WndWnd::inputChangedCallback( ResourceID inputid){
	if ( !isDirectWndMode_) return true;

	std::vector<Wnd* > wnds = WndMgr::instance()->getWnds();
	Wnd* getWnd = NULL;
	bool isOpenScreenWnd = false;
	for ( size_t i = 0; i < wnds.size(); ++i){
		Wnd* wnd = wnds[i];
		if ( GetRow(inputid) == GetRow( wnd->inputid_) && GetCol(inputid) == GetCol( wnd->inputid_) ){
			isOpenScreenWnd = true;
			if ( inputid == wnd->inputid_) getWnd = wnd;
			break;
		}
	}

	if (isOpenScreenWnd){
		if ( getWnd){
			uint32_t res = ScreenMgr::instance()->getInResolution( inputid);
			if ( res == 0 || res == -1){
				WndMgr::instance()->closeWnd(getWnd);
				return true;
			}
		}
	}else{
		uint32_t res = ScreenMgr::instance()->getInResolution( inputid);
		size_t input = GetInput(inputid);
		if ( res == 0 || res == -1 || input >=5) return true;
		return createWnd(inputid);
	}
	return true;
}