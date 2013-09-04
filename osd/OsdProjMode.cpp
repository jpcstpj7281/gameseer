#include "OsdProjMode.h"
#include "ui_OsdProjMode.h"
#include <QtDeclarative/QDeclarativeView>
#include "QPushButton.h"
#include "QSlider.h"
#include "qlineedit.h"
#include <qdebug.h>
#include <ConfigMgr.h>


OsdProjMode::OsdProjMode(QWidget *parent, ResourceID screenid) :
    QWidget(parent),
    ui(new Ui::OsdProjMode)
	,screenid_(screenid)
	,projMode_(0)
	,testPatterns_(0)
	,foreColor_(0)
	,redGain_(0)
    ,redSat_(0)
    ,redHue_(0)
    ,greenGain_(0)
    ,greenSat_(0)
    ,greenHue_(0)
    ,blueGain_(0)
    ,blueSat_(0)
    ,blueHue_(0)
    ,cyanGain_(0)
    ,cyanSat_(0)
    ,cyanHue_(0)
    ,magentaGain_(0)
    ,magentaSat_(0)
    ,magentaHue_(0)
    ,yellowGain_(0)
    ,yellowSat_(0)
    ,yellowHue_(0)
    ,whiteRed_(0)
    ,whiteGreen_(0)
    ,whiteBlue_(0)
{
    ui->setupUi(this);

	QSlider* qs  = findChild<QSlider*>("sHsgRedGain" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgRedGain(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgRedSat" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgRedSat(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgRedHue" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgRedHue(int) ) );
    }

	qs  = findChild<QSlider*>("sHsgGreenGain" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgGreenGain(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgGreenSat" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgGreenSat(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgGreenHue" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgGreenHue(int) ) );
    }

	qs  = findChild<QSlider*>("sHsgBlueGain" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgBlueGain(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgBlueSat" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgBlueSat(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgBlueHue" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgBlueHue(int) ) );
    }

	qs  = findChild<QSlider*>("sHsgCyanGain" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgCyanGain(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgCyanSat" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgCyanSat(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgCyanHue" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgCyanHue(int) ) );
    }

	qs  = findChild<QSlider*>("sHsgMagentaGain" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgMagentaGain(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgMagentaHue" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgMagentaHue(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgMagentaSat" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgMagentaSat(int) ) );
    }

	qs  = findChild<QSlider*>("sHsgYellowGain" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgYellowGain(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgYellowHue" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgYellowHue(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgYellowSat" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgYellowSat(int) ) );
    }

	qs  = findChild<QSlider*>("sHsgWhiteGreen" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgWhiteGreen(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgWhiteRed" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgWhiteRed(int) ) );
    }
	qs  = findChild<QSlider*>("sHsgWhiteBlue" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedHsgWhiteBlue(int) ) );
    }


	QLineEdit* le  = findChild<QLineEdit*>("leHsgRedGain" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgRedGain() ) );
    }
	le  = findChild<QLineEdit*>("leHsgRedSat" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgRedSat() ) );
    }
	le  = findChild<QLineEdit*>("leHsgRedHue" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgRedHue() ) );
    }

	le  = findChild<QLineEdit*>("leHsgGreenGain" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgGreenGain() ) );
    }
	le  = findChild<QLineEdit*>("leHsgGreenSat" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgGreenSat() ) );
    }
	le  = findChild<QLineEdit*>("leHsgGreenHue" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgGreenHue() ) );
    }

	le  = findChild<QLineEdit*>("leHsgBlueGain" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgBlueGain() ) );
    }
	le  = findChild<QLineEdit*>("leHsgBlueSat" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgBlueSat() ) );
    }
	le  = findChild<QLineEdit*>("leHsgBlueHue" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgBlueHue() ) );
    }

	le  = findChild<QLineEdit*>("leHsgCyanGain" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgCyanGain() ) );
    }
	le  = findChild<QLineEdit*>("leHsgCyanSat" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgCyanSat() ) );
    }
	le  = findChild<QLineEdit*>("leHsgCyanHue" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgCyanHue() ) );
    }

	le  = findChild<QLineEdit*>("leHsgMagentaGain" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgMagentaGain() ) );
    }
	le  = findChild<QLineEdit*>("leHsgMagentaHue" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgMagentaHue() ) );
    }
	le  = findChild<QLineEdit*>("leHsgMagentaSat" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgMagentaSat() ) );
    }

	le  = findChild<QLineEdit*>("leHsgYellowGain" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgYellowGain() ) );
    }
	le  = findChild<QLineEdit*>("leHsgYellowHue" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgYellowHue() ) );
    }
	le  = findChild<QLineEdit*>("leHsgYellowSat" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgYellowSat() ) );
    }

	le  = findChild<QLineEdit*>("leHsgWhiteGreen" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgWhiteGreen() ) );
    }
	le  = findChild<QLineEdit*>("leHsgWhiteRed" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgWhiteRed() ) );
    }
	le  = findChild<QLineEdit*>("leHsgWhiteBlue" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedHsgWhiteBlue() ) );
    }



	qs  = findChild<QSlider*>("sFrontGreen" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedFrontGreen(int) ) );
    }
	qs  = findChild<QSlider*>("sFrontRed" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedFrontRed(int) ) );
    }
	qs  = findChild<QSlider*>("sFrontBlue" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedFrontBlue(int) ) );
    }


	le  = findChild<QLineEdit*>("leFrontGreen" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedFrontGreen() ) );
    }
	le  = findChild<QLineEdit*>("leFrontRed" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedFrontRed() ) );
    }
	le  = findChild<QLineEdit*>("leFrontBlue" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedFrontBlue() ) );
    }

	qs  = findChild<QSlider*>("sTestPeriod" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedTestPeriod(int) ) );
    }
	qs  = findChild<QSlider*>("sTestWidth" );
    if ( qs) {
    	connect( qs, SIGNAL( valueChanged (int)), this, SLOT( valueChangedTestWidth(int) ) );
    }


	le  = findChild<QLineEdit*>("leTestPeriod" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedTestPeriod() ) );
    }
	le  = findChild<QLineEdit*>("leTestWidth" );
    if ( le) {
    	connect( le, SIGNAL( editingFinished()), this, SLOT( valueChangefinishedTestWidth() ) );
    }

	QComboBox* cb  = findChild<QComboBox*>("cbProjMode" );
    if ( cb) {
    	connect( cb, SIGNAL( currentIndexChanged (int)), this, SLOT( currentProjModeIndexChanged(int) ) );
    }
	cb  = findChild<QComboBox*>("cbTestPatterns" );
    if ( cb) {
    	connect( cb, SIGNAL( currentIndexChanged (int)), this, SLOT( currentTestPatternsIndexChanged(int) ) );
    }

	QPushButton* btn = findChild<QPushButton*>("btnReadHsg");
	if ( btn) {
    	connect( btn, SIGNAL( clicked ()), this, SLOT( readClicked() ) );
    }

	btn  = findChild<QPushButton*>("btnLoadHsg" );
	if ( btn) {
		connect( btn, SIGNAL( clicked ()), this, SLOT( load() ) );
	}
	btn  = findChild<QPushButton*>("btnSaveHsg" );
	if ( btn) {
		connect( btn, SIGNAL( clicked ()), this, SLOT( save() ) );
	}
}

OsdProjMode::~OsdProjMode()
{
    delete ui;
}
bool OsdProjMode::readClickedResponse(uint32_t , QboxDataMap& data){
	std::string val = data["Data"];
	if ( val.empty() ){
		val = data["data"];
	}
	if ( val.length() == 42){
		redGain_ =(val[0] << 8 ) + val[1];
		redSat_=(val[2] << 8 ) + val[3];
		redHue_=(val[4] << 8 ) + val[5];
		greenGain_=(val[6] << 8 ) + val[7];
		greenSat_=(val[8] << 8 ) + val[9];
		greenHue_=(val[10] << 8 ) + val[11];
		blueGain_=(val[12] << 8 ) + val[13];
		blueSat_=(val[14] << 8 ) + val[15];
		blueHue_=(val[16] << 8 ) + val[17];
		cyanGain_=(val[18] << 8 ) + val[19];
		cyanSat_=(val[20] << 8 ) + val[21];
		cyanHue_=(val[22] << 8 ) + val[23];
		magentaGain_=(val[24] << 8 ) + val[25];
		magentaSat_=(val[26] << 8 ) + val[27];
		magentaHue_=(val[28] << 8 ) + val[29];
		yellowGain_=(val[30] << 8 ) + val[31];
		yellowSat_=(val[32] << 8 ) + val[33];
		yellowHue_=(val[34] << 8 ) + val[35];
		whiteRed_=(val[36] << 8 ) + val[37];
		whiteGreen_=(val[38] << 8 ) + val[39];
		whiteBlue_=(val[40] << 8 ) + val[41];

		findChild<QSlider*>("sHsgRedGain" )->setValue( redGain_);
		findChild<QSlider*>("sHsgRedSat" )->setValue( redSat_);
		findChild<QSlider*>("sHsgRedHue" )->setValue( redHue_);
		findChild<QSlider*>("sHsgGreenGain" )->setValue( greenGain_);
		findChild<QSlider*>("sHsgGreenSat" )->setValue( greenSat_);
		findChild<QSlider*>("sHsgGreenHue" )->setValue( greenHue_);
		findChild<QSlider*>("sHsgBlueGain" )->setValue( blueGain_);
		findChild<QSlider*>("sHsgBlueSat" )->setValue( blueSat_);
		findChild<QSlider*>("sHsgBlueHue" )->setValue( blueHue_);
		findChild<QSlider*>("sHsgCyanGain" )->setValue( cyanGain_);
		findChild<QSlider*>("sHsgCyanSat" )->setValue( cyanSat_);
		findChild<QSlider*>("sHsgCyanHue" )->setValue( cyanHue_);
		findChild<QSlider*>("sHsgMagentaGain" )->setValue( magentaGain_);
		findChild<QSlider*>("sHsgMagentaHue" )->setValue( magentaHue_);
		findChild<QSlider*>("sHsgMagentaSat" )->setValue( magentaSat_);
		findChild<QSlider*>("sHsgYellowGain" )->setValue( yellowGain_);
		findChild<QSlider*>("sHsgYellowHue" )->setValue( yellowHue_);
		findChild<QSlider*>("sHsgYellowSat" )->setValue( yellowSat_);
		findChild<QSlider*>("sHsgWhiteGreen" )->setValue(whiteGreen_ );
		findChild<QSlider*>("sHsgWhiteRed" )->setValue( whiteRed_);
		findChild<QSlider*>("sHsgWhiteBlue" )->setValue( whiteBlue_);
		findChild<QLineEdit*>("leHsgRedGain" )->setText( QString::number( redGain_));
		findChild<QLineEdit*>("leHsgRedSat" )->setText( QString::number( redSat_));
		findChild<QLineEdit*>("leHsgRedHue" )->setText( QString::number( redHue_));
		findChild<QLineEdit*>("leHsgGreenGain" )->setText( QString::number( greenGain_));
		findChild<QLineEdit*>("leHsgGreenSat" )->setText( QString::number( greenSat_));
		findChild<QLineEdit*>("leHsgGreenHue" )->setText( QString::number( greenHue_));
		findChild<QLineEdit*>("leHsgBlueGain" )->setText( QString::number( blueGain_));
		findChild<QLineEdit*>("leHsgBlueSat" )->setText( QString::number( blueSat_));
		findChild<QLineEdit*>("leHsgBlueHue" )->setText( QString::number( blueHue_));
		findChild<QLineEdit*>("leHsgCyanGain" )->setText( QString::number( cyanGain_));
		findChild<QLineEdit*>("leHsgCyanSat" )->setText( QString::number( cyanSat_));
		findChild<QLineEdit*>("leHsgCyanHue" )->setText( QString::number( cyanHue_));
		findChild<QLineEdit*>("leHsgMagentaGain" )->setText( QString::number( magentaGain_));
		findChild<QLineEdit*>("leHsgMagentaHue" )->setText( QString::number( magentaHue_));
		findChild<QLineEdit*>("leHsgMagentaSat" )->setText( QString::number( magentaSat_));
		findChild<QLineEdit*>("leHsgYellowGain" )->setText( QString::number( yellowGain_));
		findChild<QLineEdit*>("leHsgYellowHue" )->setText( QString::number( yellowHue_));
		findChild<QLineEdit*>("leHsgYellowSat" )->setText( QString::number( yellowSat_));
		findChild<QLineEdit*>("leHsgWhiteGreen" )->setText( QString::number( whiteGreen_));
		findChild<QLineEdit*>("leHsgWhiteRed" )->setText( QString::number(whiteRed_ ));
		findChild<QLineEdit*>("leHsgWhiteBlue" )->setText( QString::number( whiteBlue_));
	}
	return true;
}

void OsdProjMode::readClicked(){
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestRead( 0x1516, 42, std::bind( &OsdProjMode::readClickedResponse, this,std::placeholders::_1, std::placeholders::_2), 0x34);
}

static bool osdResponse(uint32_t , QboxDataMap&){
	qDebug()<<"osdResponse";
	return true;
}

void OsdProjMode::dispatchHSG(){
	std::string data;
	data.resize(42);
	data[0] = redGain_ >>8;
	data[1] = redGain_ ;
	data[2] = redSat_ >>8;
	data[3] = redSat_ ;
	data[4] = redHue_ >>8;
	data[5] = redHue_ ;

	data[6] = greenGain_ >>8;
	data[7] = greenGain_ ;
	data[8] = greenSat_ >>8;
	data[9] = greenSat_ ;
	data[10] = greenHue_ >>8;
	data[11] = greenHue_ ;

	data[12] = blueGain_ >>8;
	data[13] = blueGain_ ;
	data[14] = blueSat_ >>8;
	data[15] = blueSat_ ;
	data[16] = blueHue_ >>8;
	data[17] = blueHue_ ;

	data[18] = magentaGain_ >>8;
	data[19] = magentaGain_ ;
	data[20] = magentaSat_ >>8;
	data[21] = magentaSat_ ;
	data[22] = magentaHue_ >>8;
	data[23] = magentaHue_ ;

	data[24] = cyanGain_ >>8;
	data[25] = cyanGain_ ;
	data[26] = cyanSat_ >>8;
	data[27] = cyanSat_ ;
	data[28] = cyanHue_ >>8;
	data[29] = cyanHue_ ;

	data[30] = yellowGain_ >>8;
	data[31] = yellowGain_ ;
	data[32] = yellowSat_ >>8;
	data[33] = yellowSat_ ;
	data[34] = yellowHue_ >>8;
	data[35] = yellowHue_ ;

	data[36] = whiteRed_ >>8;
	data[37] = whiteRed_ ;
	data[38] = whiteGreen_ >>8;
	data[39] = whiteGreen_ ;
	data[40] = whiteBlue_ >>8;
	data[41] = whiteBlue_ ;

	ScreenMgr::instance()->getScreen( screenid_)->osdRequest( 0x13, data, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}

void OsdProjMode::valueChangedHsgRedGain(int val){
	if ( redGain_ == val  )return;
	redGain_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgRedGain" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgRedSat(int val){
	if ( redSat_ == val  )return;
	redSat_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgRedSat" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgRedHue(int val){
	if ( redHue_ == val  )return;
	redHue_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgRedHue" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgGreenGain(int val){
	if ( greenGain_ == val  )return;
	greenGain_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgGreenGain" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgGreenSat(int val){
	if ( greenSat_ == val  )return;
	greenSat_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgGreenSat" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgGreenHue(int val){
	if ( greenHue_ == val  )return;
	greenHue_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgGreenHue" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgBlueGain(int val){
	if ( blueGain_ == val  )return;
	blueGain_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgBlueGain" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgBlueSat(int val) {
	if ( blueSat_ == val  )return;
	blueSat_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgBlueSat" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgBlueHue(int val){
	if ( blueHue_ == val  )return;
	blueHue_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgBlueHue" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgCyanGain(int val){
	if ( cyanGain_ == val  )return;
	cyanGain_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgCyanGain" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgCyanSat(int val){
	if ( cyanSat_ == val  )return;
	cyanSat_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgCyanSat" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgCyanHue(int val){
	if ( cyanHue_ == val  )return;
	cyanHue_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgCyanHue" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgMagentaGain(int val){
	if ( magentaGain_ == val  )return;
	magentaGain_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgMagentaGain" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgMagentaHue(int val){
	if ( magentaHue_ == val  )return;
	magentaHue_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgMagentaHue" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgMagentaSat(int val){
	if ( magentaSat_ == val  )return;
	magentaSat_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgMagentaSat" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgYellowGain(int val){
	if ( yellowGain_ == val  )return;
	yellowGain_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgYellowGain" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgYellowHue(int val){
	if ( yellowHue_ == val  )return;
	yellowHue_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgYellowHue" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgYellowSat(int val){
	if ( yellowSat_ == val  )return;
	yellowSat_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgYellowSat" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgWhiteGreen(int val){
	if ( whiteGreen_ == val  )return;
	whiteGreen_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgWhiteGreen" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgWhiteRed(int val){
	if ( whiteRed_ == val  )return;
	whiteRed_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgWhiteRed" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedHsgWhiteBlue(int val){
	if ( whiteBlue_ == val  )return;
	whiteBlue_ = val;
	dispatchHSG();
	findChild<QLineEdit*>("leHsgWhiteBlue" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangefinishedHsgRedGain(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == redGain_ )return;
	//valueChangedHsgRedGain(val);
	findChild<QSlider*>("sHsgRedGain" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgRedSat(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == redSat_ )return;
	valueChangedHsgRedSat(val);
	findChild<QSlider*>("sHsgRedSat" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgRedHue(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == redHue_ )return;
	//valueChangedHsgRedHue(val);
	findChild<QSlider*>("sHsgRedHue" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgGreenGain(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == greenGain_ )return;
	//valueChangedHsgGreenGain(val);
	findChild<QSlider*>("sHsgGreenGain" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgGreenSat(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == greenSat_ )return;
	//valueChangedHsgGreenSat(val);
	findChild<QSlider*>("sHsgGreenSat" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgGreenHue(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == greenHue_ )return;
	//valueChangedHsgGreenHue(val);
	findChild<QSlider*>("sHsgGreenHue" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgBlueGain(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == blueGain_ )return;
	//valueChangedHsgBlueGain(val);
	findChild<QSlider*>("sHsgBlueGain" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgBlueSat(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == blueSat_ )return;
	//valueChangedHsgBlueSat(val);
	findChild<QSlider*>("sHsgBlueSat" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgBlueHue(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == blueHue_ )return;
	//valueChangedHsgBlueHue(val);
	findChild<QSlider*>("sHsgBlueHue" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgCyanGain(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == cyanGain_ )return;
	//valueChangedHsgCyanGain(val);
	findChild<QSlider*>("sHsgCyanGain" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgCyanSat(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == cyanSat_ )return;
	//valueChangedHsgCyanSat(val);
	findChild<QSlider*>("sHsgCyanSat" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgCyanHue(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == cyanHue_ )return;
	//valueChangedHsgCyanHue(val);
	findChild<QSlider*>("sHsgCyanHue" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgMagentaGain() {
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == magentaGain_ )return;
	//valueChangedHsgMagentaGain(val);
	findChild<QSlider*>("sHsgMagentaGain" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgMagentaHue(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == magentaHue_ )return;
	//valueChangedHsgMagentaHue(val);
	findChild<QSlider*>("sHsgMagentaHue" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgMagentaSat(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == magentaSat_ )return;
	//valueChangedHsgMagentaSat(val);
	findChild<QSlider*>("sHsgMagentaSat" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgYellowGain(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == yellowGain_ )return;
	//valueChangedHsgYellowGain(val);
	findChild<QSlider*>("sHsgYellowGain" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgYellowHue(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == yellowHue_ )return;
	//valueChangedHsgYellowHue(val);
	findChild<QSlider*>("sHsgYellowHue" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgYellowSat(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == yellowSat_ )return;
	//valueChangedHsgYellowSat(val);
	findChild<QSlider*>("sHsgYellowSat" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgWhiteGreen(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == whiteGreen_ )return;
	//valueChangedHsgWhiteGreen(val);
	findChild<QSlider*>("sHsgWhiteGreen" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgWhiteRed() {
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == whiteRed_ )return;
	//valueChangedHsgWhiteRed(val);
	findChild<QSlider*>("sHsgWhiteRed" )->setValue( val);
}
void OsdProjMode::valueChangefinishedHsgWhiteBlue(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == whiteBlue_ )return;
	//valueChangedHsgWhiteBlue(val);
	findChild<QSlider*>("sHsgWhiteBlue" )->setValue( val);
}

void OsdProjMode::valueChangedFrontGreen(int val){
	int red = findChild<QSlider*>("sFrontRed" )->value();
	int blue = findChild<QSlider*>("sFrontBlue" )->value();
	int newval = (val<<16) | (red <<8) | blue;
	if ( foreColor_ == newval  )return;
	foreColor_ = newval;
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestUint( 0x12, foreColor_, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
	findChild<QLineEdit*>("leFrontGreen" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedFrontRed(int val){
	if ( val == ( (foreColor_ >> 8) & 0xff ) )return;
	valueChangedFrontGreen(findChild<QSlider*>("sFrontGreen" )->value());
	findChild<QLineEdit*>("leFrontRed" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedFrontBlue(int val){
	if ( val == ( foreColor_ & 0xff ) )return;
	valueChangedFrontGreen(findChild<QSlider*>("sFrontGreen" )->value());
	findChild<QLineEdit*>("leFrontBlue" )->setText( QString::number( val) );
}

void OsdProjMode::valueChangefinishedFrontGreen(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == ( foreColor_ >> 16 ) )return;
	//valueChangedFrontGreen(val);
	findChild<QSlider*>("sFrontGreen" )->setValue( val);
}
void OsdProjMode::valueChangefinishedFrontRed(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == ( (foreColor_ >> 8) & 0xff ) )return;
	//valueChangedFrontRed(val);
	findChild<QSlider*>("sFrontRed" )->setValue( val);
}
void OsdProjMode::valueChangefinishedFrontBlue(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == ( foreColor_ & 0xff ) )return;
	//valueChangedFrontBlue(val);
	findChild<QSlider*>("sFrontBlue" )->setValue( val);
}

void OsdProjMode::currentProjModeIndexChanged(int index){
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestChar( 0x2, index<<5, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}

void OsdProjMode::currentTestPatternsIndexChanged(int index){
	int period = findChild<QSlider*>("sTestPeriod" )->value();
	int width = findChild<QSlider*>("sTestWidth" )->value();
	unsigned short val = (index << 8) | (period << 4) | width;
	if ( val == testPatterns_) return;
	testPatterns_ = val;
	ScreenMgr::instance()->getScreen( screenid_)->osdRequestUshort( 0x33, testPatterns_, std::bind( &osdResponse, std::placeholders::_1, std::placeholders::_2));
}

void OsdProjMode::valueChangedTestPeriod(int val){
	if ( val == ((testPatterns_>>4) & 0xf) ) return;
	currentTestPatternsIndexChanged(findChild<QComboBox*>("cbTestPatterns" )->currentIndex() );
	findChild<QLineEdit*>("leTestPeriod" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangedTestWidth(int val){
	if ( val == (testPatterns_ & 0xf) ) return;
	currentTestPatternsIndexChanged(findChild<QComboBox*>("cbTestPatterns" )->currentIndex() );
	findChild<QLineEdit*>("leTestWidth" )->setText( QString::number( val) );
}
void OsdProjMode::valueChangefinishedTestPeriod(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == ((testPatterns_>>4) & 0xf) ) return;
	valueChangedTestPeriod(val);
}
void OsdProjMode::valueChangefinishedTestWidth(){
	QLineEdit* le = (QLineEdit*)sender();
	int val = le->text().toInt();
	if ( val == (testPatterns_ & 0xf) ) return;
	valueChangedTestWidth(val);
}


void OsdProjMode::load(){
	QDomElement root = ConfigMgr::instance()->getDoc()->documentElement();
	QDomNodeList items = root.elementsByTagName("OsdPM");
	items = root.elementsByTagName("PMScreen");
	for (size_t i = 0; i < items.size();++i){
		QDomElement elm = items.at(i).toElement();
		if ( elm.attribute("id").toLong() ==screenid_){

			redGain_ = elm.attribute("sHsgRedGain", QString::number(redGain_)).toLong();
			redSat_ = elm.attribute("sHsgRedSat", QString::number(redSat_)).toLong();
			redHue_ = elm.attribute("sHsgRedHue", QString::number(redHue_)).toLong();

			greenGain_ = elm.attribute("sHsgGreenGain", QString::number(greenGain_)).toLong();
			greenSat_ = elm.attribute("sHsgGreenSat", QString::number(greenSat_)).toLong();
			greenHue_ = elm.attribute("sHsgGreenHue", QString::number(greenHue_)).toLong();

			blueGain_ = elm.attribute("sHsgBlueGain", QString::number(blueGain_)).toLong();
			blueSat_ = elm.attribute("sHsgBlueSat", QString::number(blueSat_)).toLong();
			blueHue_ = elm.attribute("sHsgBlueHue", QString::number(blueHue_)).toLong();

			cyanGain_ = elm.attribute("sHsgCyanGain", QString::number(cyanGain_)).toLong();
			cyanSat_ = elm.attribute("sHsgCyanSat", QString::number(cyanSat_)).toLong();
			cyanHue_ = elm.attribute("sHsgCyanHue", QString::number(cyanHue_)).toLong();

			magentaGain_ = elm.attribute("sHsgMagentGain", QString::number(magentaGain_)).toLong();
			magentaSat_ = elm.attribute("sHsgMagentSat", QString::number(magentaSat_)).toLong();
			magentaHue_ = elm.attribute("sHsgMagentHue", QString::number(magentaHue_)).toLong();

			yellowGain_ = elm.attribute("sHsgYellowGain", QString::number(yellowGain_)).toLong();
			yellowSat_ = elm.attribute("sHsgYellowSat", QString::number(yellowSat_)).toLong();
			yellowHue_ = elm.attribute("sHsgYellowHue", QString::number(yellowHue_)).toLong();

			whiteRed_ = elm.attribute("sHsgWhiteRed", QString::number(whiteRed_)).toLong();
			whiteGreen_ = elm.attribute("sHsgWhiteGreen", QString::number(whiteGreen_)).toLong();
			whiteBlue_ = elm.attribute("sHsgWhiteBlue", QString::number(whiteBlue_)).toLong();

			findChild<QSlider*>("sHsgRedGain" )->setValue(redGain_);
			findChild<QLineEdit*>("leHsgRedGain" )->setText(QString::number(redGain_));

			dispatchHSG();
			//tasks_.push_back( std::bind( &OsdImage::dispatchContrast , this) );

			break;
		}
	}
}
void OsdProjMode::save(){
	QDomElement root = ConfigMgr::instance()->getDoc()->documentElement();
	QDomNodeList items = root.elementsByTagName("OsdPM");
	QDomElement osdElm;
	if ( items.size() >0 ){
		osdElm = items.at(0).toElement();
	}else{
		osdElm = ConfigMgr::instance()->getDoc()->createElement("OsdPM");
		root.appendChild(osdElm);
	}

	items = osdElm.elementsByTagName("PMScreen");
	QDomElement currosdElm;
	for (size_t i =0; i <items.count(); ++i){
		QDomElement iselm = items.at(i).toElement();
		if ( iselm.attribute("id").toLong() == screenid_){
			currosdElm = iselm;
			break;
		}
	}

	if ( currosdElm == QDomElement()){
		currosdElm = ConfigMgr::instance()->getDoc()->createElement("PMScreen");
		osdElm.appendChild(currosdElm);
	}
	currosdElm.setAttribute("id", QString::number(screenid_));
	currosdElm.setAttribute("sHsgRedGain", QString::number(redGain_));
	currosdElm.setAttribute("sHsgRedSat", QString::number(redSat_));
	currosdElm.setAttribute("sHsgRedHue", QString::number(redHue_));

	currosdElm.setAttribute("sHsgGreenGain", QString::number(greenGain_));
	currosdElm.setAttribute("sHsgGreenSat", QString::number(greenSat_));
	currosdElm.setAttribute("sHsgGreenHue", QString::number(greenHue_));

	currosdElm.setAttribute("sHsgBlueGain", QString::number(blueGain_));
	currosdElm.setAttribute("sHsgBlueSat", QString::number(blueSat_));
	currosdElm.setAttribute("sHsgBlueHue", QString::number(blueHue_));

	currosdElm.setAttribute("sHsgCyanGain", QString::number(cyanGain_));
	currosdElm.setAttribute("sHsgCyanSat", QString::number(cyanSat_));
	currosdElm.setAttribute("sHsgCyanHue", QString::number(cyanHue_));

	currosdElm.setAttribute("sHsgMagentGain", QString::number(magentaGain_));
	currosdElm.setAttribute("sHsgMagentSat", QString::number(magentaSat_));
	currosdElm.setAttribute("sHsgMagentHue", QString::number(magentaHue_));

	currosdElm.setAttribute("sHsgYellowGain", QString::number(yellowGain_));
	currosdElm.setAttribute("sHsgYellowSat", QString::number(yellowSat_));
	currosdElm.setAttribute("sHsgYellowHue", QString::number(yellowHue_));

	currosdElm.setAttribute("sHsgWhiteRed", QString::number(whiteRed_));
	currosdElm.setAttribute("sHsgWhiteGreen", QString::number(whiteGreen_));
	currosdElm.setAttribute("sHsgWhiteBlue", QString::number(whiteBlue_));
}