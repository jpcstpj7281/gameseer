#ifndef OsdProjMode_H
#define OsdProjMode_H

#include <QWidget>
#include "Screen.h"

namespace Ui {
class OsdProjMode;
}
typedef std::function< void ()> talkCallback;

class OsdProjMode : public QWidget
{
	private slots:
		void valueChangedHsgRedGain(int);
		void valueChangedHsgRedSat(int);
		void valueChangedHsgRedHue(int);
		void valueChangedHsgGreenGain(int);
		void valueChangedHsgGreenSat(int);
		void valueChangedHsgGreenHue(int);
		void valueChangedHsgBlueGain(int);
		void valueChangedHsgBlueSat(int) ;
		void valueChangedHsgBlueHue(int);
		void valueChangedHsgCyanGain(int);
		void valueChangedHsgCyanSat(int);
		void valueChangedHsgCyanHue(int);
		void valueChangedHsgMagentaGain(int);
		void valueChangedHsgMagentaHue(int);
		void valueChangedHsgMagentaSat(int);
		void valueChangedHsgYellowGain(int);
		void valueChangedHsgYellowHue(int);
		void valueChangedHsgYellowSat(int);
		void valueChangedHsgWhiteGreen(int);
		void valueChangedHsgWhiteRed(int);
		void valueChangedHsgWhiteBlue(int);
		void valueChangefinishedHsgRedGain();
		void valueChangefinishedHsgRedSat();
		void valueChangefinishedHsgRedHue();
		void valueChangefinishedHsgGreenGain();
		void valueChangefinishedHsgGreenSat();
		void valueChangefinishedHsgGreenHue();
		void valueChangefinishedHsgBlueGain();
		void valueChangefinishedHsgBlueSat();
		void valueChangefinishedHsgBlueHue();
		void valueChangefinishedHsgCyanGain();
		void valueChangefinishedHsgCyanSat();
		void valueChangefinishedHsgCyanHue();
		void valueChangefinishedHsgMagentaGain() ;
		void valueChangefinishedHsgMagentaHue();
		void valueChangefinishedHsgMagentaSat();
		void valueChangefinishedHsgYellowGain();
		void valueChangefinishedHsgYellowHue();
		void valueChangefinishedHsgYellowSat();
		void valueChangefinishedHsgWhiteGreen();
		void valueChangefinishedHsgWhiteRed() ;
		void valueChangefinishedHsgWhiteBlue();

		void valueChangedFrontGreen(int);
		void valueChangedFrontRed(int);
		void valueChangedFrontBlue(int);
		void valueChangefinishedFrontGreen();
		void valueChangefinishedFrontRed();
		void valueChangefinishedFrontBlue();

		void currentProjModeIndexChanged(int);
		void currentTestPatternsIndexChanged(int);

		void valueChangedTestPeriod(int);
		void valueChangedTestWidth(int);
		void valueChangefinishedTestPeriod();
		void valueChangefinishedTestWidth();

		void readClicked();
		void load();
		void save();
private:
	Q_OBJECT
	
		
	bool readClickedResponse(uint32_t , QboxDataMap&);

	void dispatchHSG();
	void dispatchFrontColor();
	void dispatchTestPattern();
	ResourceID screenid_;
	
	bool isDispatching_;
	char projMode_;
	unsigned short testPatterns_;
	uint32_t foreColor_;
	size_t readCount_;

	unsigned short redGain_;
    unsigned short redSat_;
    short redHue_;
    unsigned short greenGain_;
    unsigned short greenSat_;
    short greenHue_;
    unsigned short blueGain_;
    unsigned short blueSat_;
    short blueHue_;
    unsigned short cyanGain_;
    unsigned short cyanSat_;
    short cyanHue_;
    unsigned short magentaGain_;
    unsigned short magentaSat_;
    short magentaHue_;
    unsigned short yellowGain_;
    unsigned short yellowSat_;
    short yellowHue_;
    unsigned short whiteRed_;
    unsigned short whiteGreen_;
    unsigned short whiteBlue_;

	std::list<talkCallback> hsgTasks_;
	std::list<talkCallback> testPatternTasks_;
	std::list<talkCallback> frontColorTasks_;
	bool osdTaskResponse(uint32_t , QboxDataMap& data);
	virtual void	timerEvent ( QTimerEvent * event )override;
public:
    explicit OsdProjMode(QWidget *parent , ResourceID screenid);
    ~OsdProjMode();
    
private:
    Ui::OsdProjMode *ui;
};

#endif // OsdProjMode_H
