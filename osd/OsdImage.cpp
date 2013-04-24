#include "OsdImage.h"
#include "ui_OsdImage.h"
#include "QPushButton.h"
#include "QSlider.h"
#include "qlineedit.h"
#include <qdebug.h>
#include <sstream>
#include <string>

OsdImage::~OsdImage()
{
	delete ui;
}


OsdImage::OsdImage(QWidget *parent, ResourceID screenid ) :
QWidget(parent),
	ui(new Ui::OsdImage)
	,screenid_(screenid)
	, brightnessRed_(0)
	, brightnessGreen_(0)
	, brightnessBlue_(0)
	, contrastRed_(50)
	, contrastGreen_(50)
	, contrastBlue_(50)
	, dynamicBlack_(0)
	, brilliantColor_(0)
	, horiPos_(0)
	, vertPos_(0)
	, comma_(0)
	, orientation_(01)
{
	ui->setupUi(this);

	QPushButton * initBtn  = findChild<QPushButton*>("btnInit" );
	if ( initBtn) {
		connect( initBtn, SIGNAL( clicked()), this, SLOT( clickinit() ) );
	}

	QSlider * qs  = findChild<QSlider*>("sBrightness" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueBrightnessChanged(int) ) );
	}
	qs  = findChild<QSlider*>("sRedBrightness" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueRedBrightnessChanged(int) ) );
	}
	qs  = findChild<QSlider*>("sGreenBrightness" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueGreenBrightnessChanged(int) ) );
	}
	qs  = findChild<QSlider*>("sBlueBrightness" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueBlueBrightnessChanged(int) ) );
	}

	QLineEdit * le  = findChild<QLineEdit*>("leBrightness" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueBrightnessChangedFinished() ) );
	}
	le  = findChild<QLineEdit*>("leRedBrightness" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueRedBrightnessChangedFinished() ) );
	}
	le  = findChild<QLineEdit*>("leGreenBrightness" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueGreenBrightnessChangedFinished() ) );
	}
	le  = findChild<QLineEdit*>("leBlueBrightness" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueBlueBrightnessChangedFinished() ) );
	}

	qs  = findChild<QSlider*>("sContrast" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueContrastChanged(int) ) );
	}
	qs  = findChild<QSlider*>("sRedContrast" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueRedContrastChanged(int) ) );
	}
	qs  = findChild<QSlider*>("sGreenContrast" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueGreenContrastChanged(int) ) );
	}
	qs  = findChild<QSlider*>("sBlueContrast" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueBlueContrastChanged(int) ) );
	}

	le  = findChild<QLineEdit*>("leContrast" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueContrastChangedFinished() ) );
	}
	le  = findChild<QLineEdit*>("leRedContrast" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueRedContrastChangedFinished() ) );
	}
	le  = findChild<QLineEdit*>("leGreenContrast" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueGreenContrastChangedFinished() ) );
	}
	le  = findChild<QLineEdit*>("leBlueContrast" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueBlueContrastChangedFinished() ) );
	}

	qs  = findChild<QSlider*>("sVertOffset" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueVertOffsetChanged(int) ) );
	}
	qs  = findChild<QSlider*>("sHoriOffset" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueHoriOffsetChanged(int) ) );
	}

	le  = findChild<QLineEdit*>("leHoriOffset" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueHoriOffsetChangedFinished() ) );
	}
	le  = findChild<QLineEdit*>("leVertOffset" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueVertOffsetChangedFinished() ) );
	}

	qs  = findChild<QSlider*>("sDynBlack" );
	if ( qs) {
		connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueDBlackChanged(int) ) );
	}

	le  = findChild<QLineEdit*>("leDynBlack" );
	if ( le) {
		connect( le, SIGNAL( editingFinished  ()), this, SLOT( valueDBlackChangedFinished() ) );
	}

	QPushButton* btn  = findChild<QPushButton*>("btnHoriRevert" );
	if ( btn) {
		connect( btn, SIGNAL( clicked ()), this, SLOT( btnHoriRevert() ) );
	}

	btn  = findChild<QPushButton*>("btnVertRevert" );
	if ( btn) {
		connect( btn, SIGNAL( clicked  ()), this, SLOT( btnVertRevert() ) );
	}

	QComboBox* cb  = findChild<QComboBox*>("cbBrilliantColor" );
	if ( cb) {
		connect( cb, SIGNAL( currentIndexChanged (int)), this, SLOT( currentBrilliantIndexChanged(int) ) );
	}
	cb  = findChild<QComboBox*>("cbColorRegion" );
	if ( cb) {
		connect( cb, SIGNAL( currentIndexChanged (int)), this, SLOT( currentRegionIndexChanged(int) ) );
		cb->setEnabled(false);
	}
	cb  = findChild<QComboBox*>("cbColorOverlap" );
	if ( cb) {
		connect( cb, SIGNAL( currentIndexChanged (int)), this, SLOT( currentOverlapIndexChanged(int) ) );
		cb->setEnabled(false);
	}
	cb  = findChild<QComboBox*>("cbComma" );
	if ( cb) {
		connect( cb, SIGNAL( currentIndexChanged (int)), this, SLOT( currentCommaIndexChanged(int) ) );
	}

}

bool OsdImage::osdResponseRead( uint32_t , QboxDataMap& data){
	std::string val;
	val.resize(8);
	initStr_ = data["Data"];
	if ( initStr_.empty()){
		initStr_ = data["data"];
	}
	int step = 0;
	val[0] = initStr_[(step)*8 +0];
	val[1] = initStr_[(step)*8 +1];
	val[2] = initStr_[(step)*8 +2];
	val[3] = initStr_[(step)*8 +3];
	val[4] = initStr_[(step)*8 +4];
	val[5] = initStr_[(step)*8 +5];
	val[6] = initStr_[(step)*8 +6];
	val[7] = initStr_[(step)*8 +7];
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x5e, val, std::bind( &OsdImage::osdResponseRead1, this, std::placeholders::_1, std::placeholders::_2));

	return true;
}
bool OsdImage::osdResponseRead1( uint32_t , QboxDataMap& data){
	std::string val;
	val.resize(8);
	int step = 1;
	val[0] = initStr_[(step)*8 +0];
	val[1] = initStr_[(step)*8 +1];
	val[2] = initStr_[(step)*8 +2];
	val[3] = initStr_[(step)*8 +3];
	val[4] = initStr_[(step)*8 +4];
	val[5] = initStr_[(step)*8 +5];
	val[6] = initStr_[(step)*8 +6];
	val[7] = initStr_[(step)*8 +7];
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x5e, val, std::bind( &OsdImage::osdResponseRead2, this, std::placeholders::_1, std::placeholders::_2));
	return true;
}
bool OsdImage::osdResponseRead2( uint32_t , QboxDataMap& data){
	std::string val;
	val.resize(8);
	int step = 2;
	val[0] = initStr_[(step)*8 +0];
	val[1] = initStr_[(step)*8 +1];
	val[2] = initStr_[(step)*8 +2];
	val[3] = initStr_[(step)*8 +3];
	val[4] = initStr_[(step)*8 +4];
	val[5] = initStr_[(step)*8 +5];
	val[6] = initStr_[(step)*8 +6];
	val[7] = initStr_[(step)*8 +7];
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x5e, val, std::bind( &OsdImage::osdResponseRead3, this, std::placeholders::_1, std::placeholders::_2));
	return true;
}
bool OsdImage::osdResponseRead3( uint32_t , QboxDataMap& data){
	std::string val;
	val.resize(8);
	int step = 3;
	val[0] = initStr_[(step)*8 +0];
	val[1] = initStr_[(step)*8 +1];
	val[2] = initStr_[(step)*8 +2];
	val[3] = initStr_[(step)*8 +3];
	val[4] = initStr_[(step)*8 +4];
	val[5] = initStr_[(step)*8 +5];
	val[6] = initStr_[(step)*8 +6];
	val[7] = initStr_[(step)*8 +7];
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x5e, val, std::bind( &OsdImage::osdResponseRead4, this, std::placeholders::_1, std::placeholders::_2));
	return true;
}
bool OsdImage::osdResponseRead4( uint32_t , QboxDataMap& data){
	std::string val;
	val.resize(8);
	int step = 4;
	val[0] = initStr_[(step)*8 +0];
	val[1] = initStr_[(step)*8 +1];
	val[2] = initStr_[(step)*8 +2];
	val[3] = initStr_[(step)*8 +3];
	val[4] = initStr_[(step)*8 +4];
	val[5] = initStr_[(step)*8 +5];
	val[6] = initStr_[(step)*8 +6];
	val[7] = initStr_[(step)*8 +7];
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x5e, val, std::bind( &OsdImage::osdResponseRead5, this, std::placeholders::_1, std::placeholders::_2));
	return true;
}
bool OsdImage::osdResponseRead5( uint32_t , QboxDataMap& data){
	std::string val;
	val.resize(8);
	int step = 5;
	val[0] = initStr_[(step)*8 +0];
	val[1] = initStr_[(step)*8 +1];
	val[2] = initStr_[(step)*8 +2];
	val[3] = initStr_[(step)*8 +3];
	val[4] = initStr_[(step)*8 +4];
	val[5] = initStr_[(step)*8 +5];
	val[6] = initStr_[(step)*8 +6];
	val[7] = initStr_[(step)*8 +7];
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x5e, val, std::bind( &OsdImage::osdResponseRead6, this, std::placeholders::_1, std::placeholders::_2));
	return true;
}
bool OsdImage::osdResponseRead6( uint32_t , QboxDataMap& data){
	qDebug()<<"done";
	return true;
}

void OsdImage::clickinit(){
	//ScreenMgr::instance()->getScreen( screenid_)->osdRequestRead( 0xd0, 8, std::bind( &osdResponseRead, std::placeholders::_1, std::placeholders::_2));
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestRead( 0xa0d0, 48, std::bind( &OsdImage::osdResponseRead, this, std::placeholders::_1, std::placeholders::_2));
}
static bool osdResponse(uint32_t , QboxDataMap&){
	qDebug()<<"osdResponse";
	return true;
}
void OsdImage::dispatchBrightness(){
	short shiftr = brightnessRed_ << 2;
	short shiftg = brightnessGreen_ << 2;
	short shiftb = brightnessBlue_ << 2;

	std::string data;
	data.resize(6);
	data[0] = shiftg >> 8;
	data[1] =shiftg;
	data[2] = shiftr >> 8;
	data[3] =shiftr;
	data[4] = shiftb >> 8;
	data[5] =shiftb;
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x0a, data, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}

void	OsdImage::valueBrightnessChangedFinished (  ){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	int currBrightness = (brightnessRed_+brightnessGreen_+brightnessBlue_) /3;
	if ( currBrightness == val ) return ;
	valueBrightnessChanged(val);
}
void	OsdImage::valueRedBrightnessChangedFinished (  ){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( brightnessRed_ == val ) return ;
	valueRedBrightnessChanged(val);
}
void	OsdImage::valueGreenBrightnessChangedFinished ( ){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( brightnessGreen_ == val ) return ;
	valueGreenBrightnessChanged(val);
}
void	OsdImage::valueBlueBrightnessChangedFinished ( ){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( brightnessBlue_ == val ) return ;
	valueBlueBrightnessChanged(val);
}
void OsdImage::adjustAllBrightness(){
	findChild<QSlider*>("sRedBrightness" )->setValue(brightnessRed_);
	findChild<QSlider*>("sGreenBrightness" )->setValue(brightnessGreen_);
	findChild<QSlider*>("sBlueBrightness" )->setValue(brightnessBlue_);
	findChild<QSlider*>("sBrightness" )->setValue((brightnessRed_+brightnessGreen_+brightnessBlue_) /3);
	findChild<QLineEdit*>("leRedBrightness" )->setText(QString::number(brightnessRed_));
	findChild<QLineEdit*>("leGreenBrightness" )->setText(QString::number(brightnessGreen_));
	findChild<QLineEdit*>("leBlueBrightness" )->setText(QString::number(brightnessBlue_));
	findChild<QLineEdit*>("leBrightness" )->setText(QString::number( (brightnessRed_+brightnessGreen_+brightnessBlue_) /3));
}
void OsdImage::valueBrightnessChanged(int val){
	if (val > 255) val = 255;else if (val < -255) val = -255;

	int currBrightness = (brightnessRed_+brightnessGreen_+brightnessBlue_) /3;
	if ( currBrightness == val ) return ;
	int diff = val - currBrightness;
	brightnessRed_ += diff;
	brightnessGreen_ += diff;
	brightnessBlue_ += diff;
	adjustAllBrightness();
	dispatchBrightness();
}
void OsdImage::valueRedBrightnessChanged(int val){
	if (val > 255) val = 255;else if (val < -255) val = -255;
	if (val == brightnessRed_) return;
	brightnessRed_ = val;
	adjustAllBrightness();
	dispatchBrightness();
}
void OsdImage::valueGreenBrightnessChanged(int val){
	if (val > 255) val = 255;else if (val < -255) val = -255;
	if (val == brightnessGreen_) return;
	brightnessGreen_ = val;
	adjustAllBrightness();
	dispatchBrightness();
}
void OsdImage::valueBlueBrightnessChanged(int val){
	if (val > 255) val = 255;else if (val < -255) val = -255;
	if (val == brightnessBlue_) return;
	brightnessBlue_ = val;
	adjustAllBrightness();
	dispatchBrightness();
}


void OsdImage::dispatchContrast(){
	short shiftr = contrastRed_ +50;
	short shiftg = contrastGreen_  +50;
	short shiftb = contrastBlue_ +50;

	std::string data;
	data.resize(3);
	data[0] = shiftg ;
	data[1] = shiftr;
	data[2] = shiftb ;
	qDebug()<<data.length();
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x1, data, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}
void	OsdImage::valueContrastChangedFinished (  ){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	int currContrast = (contrastRed_+contrastGreen_+contrastBlue_) /3;
	if ( currContrast == val ) return ;
	valueContrastChanged(val);
}
void	OsdImage::valueRedContrastChangedFinished (  ){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( contrastRed_ == val ) return ;
	valueRedContrastChanged(val);
}
void	OsdImage::valueGreenContrastChangedFinished ( ){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( contrastGreen_ == val ) return ;
	valueGreenContrastChanged(val);
}
void	OsdImage::valueBlueContrastChangedFinished ( ){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( contrastBlue_ == val ) return ;
	valueBlueContrastChanged(val);
}
void OsdImage::adjustAllContrast(){
	findChild<QSlider*>("sRedContrast" )->setValue(contrastRed_);
	findChild<QSlider*>("sGreenContrast" )->setValue(contrastGreen_);
	findChild<QSlider*>("sBlueContrast" )->setValue(contrastBlue_);
	findChild<QSlider*>("sContrast" )->setValue((contrastRed_+contrastGreen_+contrastBlue_) /3);
	findChild<QLineEdit*>("leRedContrast" )->setText(QString::number(contrastRed_));
	findChild<QLineEdit*>("leGreenContrast" )->setText(QString::number(contrastGreen_));
	findChild<QLineEdit*>("leBlueContrast" )->setText(QString::number(contrastBlue_));
	findChild<QLineEdit*>("leContrast" )->setText(QString::number( (contrastRed_+contrastGreen_+contrastBlue_) /3));
}
void OsdImage::valueContrastChanged(int val){
	if (val > 100) val = 100;else if (val < 0) val = 0;

	int currContrast = (contrastRed_+contrastGreen_+contrastBlue_) /3;
	if ( currContrast == val ) return ;
	int diff = val - currContrast;
	contrastRed_ += diff;
	contrastGreen_ += diff;
	contrastBlue_ += diff;
	adjustAllContrast();
	dispatchContrast();
}
void OsdImage::valueRedContrastChanged(int val){
	if (val > 100) val = 100;else if (val < 0) val = 0;
	if (val == contrastRed_) return;
	contrastRed_ = val;
	adjustAllContrast();
	dispatchContrast();
}
void OsdImage::valueGreenContrastChanged(int val){
	if (val > 100) val = 100;else if (val < 0) val = 0;
	if (val == contrastGreen_) return;
	contrastGreen_ = val;
	adjustAllContrast();
	dispatchContrast();
}
void OsdImage::valueBlueContrastChanged(int val){
	if (val > 100) val = 100;else if (val < 0) val = 0;
	if (val == contrastBlue_) return;
	contrastBlue_ = val;
	adjustAllContrast();
	dispatchContrast();
}


void OsdImage::valueVertOffsetChanged(int val){
	if (val > 255) val = 255;else if (val < -255) val = -255;
	if (val == vertPos_) return;
	vertPos_ = val;
	findChild<QLineEdit*>("leVertOffset" )->setText(QString::number(val));

	std::string data;
	data.resize(2);
	if ( val < 0){
		data[0] = 1 <<7;
	}else data[0] = 0;
	data[1] = std::abs(val);
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x05, data, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}
void OsdImage::valueVertOffsetChangedFinished(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( vertPos_ == val ) return ;
	findChild<QSlider*>("sVertOffset" )->setValue(val);
}
void OsdImage::valueHoriOffsetChanged(int val){
	if (val > 384) val = 384;else if (val < -384) val = -384;
	if (val == horiPos_) return;
	horiPos_ = val;
	findChild<QLineEdit*>("leHoriOffset" )->setText(QString::number(val));

	std::string data;
	data.resize(2);
	if ( val < 0){
		data[0] = 1 <<7;
	}else data[0] = 0;
	data[1] = std::abs(val);
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x04, data, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}
void OsdImage::valueHoriOffsetChangedFinished(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( horiPos_ == val ) return ;
	findChild<QSlider*>("sHoriOffset" )->setValue(val);
}


void OsdImage::valueDBlackChanged(int val){
	if (val > 254) val = 254;else if (val < 1) val = 1;
	if (val == dynamicBlack_) return;
	dynamicBlack_ = val;
	findChild<QLineEdit*>("leDynBlack" )->setText(QString::number(val));

	std::string data;
	data.resize(2);
	data[0] = 0 ;
	data[1] = val;
	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x4a, data, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}
void OsdImage::valueDBlackChangedFinished(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( dynamicBlack_ == val ) return ;
	findChild<QSlider*>("sDynBlack" )->setValue(val);
}

void OsdImage::btnHoriRevert(){
	QPushButton* btn = (QPushButton*)sender();
	if ( btn->text() == tr("no") ){
		btn->setText( tr("yes"));
		orientation_|=0x2;
	}else{
		btn->setText( tr("no"));
		orientation_&=0x1;
	}
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestChar( 0x3, orientation_, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}
void OsdImage::btnVertRevert(){
	QPushButton* btn = (QPushButton*)sender();
	if ( btn->text() == tr("yes") ){
		btn->setText( tr("no"));
		orientation_|=0x1;
	}else{
		btn->setText( tr("yes"));
		orientation_&=0x2;
	}
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestChar( 0x3, orientation_, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}

void OsdImage::currentBrilliantIndexChanged(int val){
	int overlap = findChild<QComboBox*>("cbColorOverlap" )->currentIndex();
	int region = findChild<QComboBox*>("cbColorRegion" )->currentIndex();
	if (val > 0){
		findChild<QComboBox*>("cbColorRegion" )->setEnabled(true);
		findChild<QComboBox*>("cbColorOverlap" )->setEnabled(true);
		val -=1;
	}else{
		findChild<QComboBox*>("cbColorRegion" )->setEnabled(false);
		findChild<QComboBox*>("cbColorOverlap" )->setEnabled(false);
		ScreenMgr::instance()->getScreen( screenid_)->osdRequestChar( 0xd, brilliantColor_&=0x7F, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
		return;
	}

	brilliantColor_ = 0x80 + val + ( overlap*12) +  (region*4);
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestChar( 0xd, brilliantColor_, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}
void OsdImage::currentRegionIndexChanged(int ){
	currentBrilliantIndexChanged( findChild<QComboBox*>("cbBrilliantColor" )->currentIndex());
}
void OsdImage::currentOverlapIndexChanged(int ){
	currentBrilliantIndexChanged( findChild<QComboBox*>("cbBrilliantColor" )->currentIndex());
}
void OsdImage::currentCommaIndexChanged(int index){
	index == 0 ? comma_ |= 0xc000 : comma_ = 0x4000 + (index -1);
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestShort( 0xd, comma_, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}