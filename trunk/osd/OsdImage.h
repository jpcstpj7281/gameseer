#ifndef OSDIMAGE_H
#define OSDIMAGE_H

#include <QWidget>
#include "Screen.h"

namespace Ui {
class OsdImage;
}
typedef std::function< void ()> talkCallback;

class OsdImage : public QWidget
{
    Q_OBJECT
    
		private slots:
			void clickinit();

			void	valueBrightnessChanged ( int  );
			void	valueRedBrightnessChanged ( int  );
			void	valueGreenBrightnessChanged ( int  );
			void	valueBlueBrightnessChanged ( int  );

			void	valueBrightnessChangedFinished (  );
			void	valueRedBrightnessChangedFinished (  );
			void	valueGreenBrightnessChangedFinished ( );
			void	valueBlueBrightnessChangedFinished ( );

			void	valueContrastChanged ( int  );
			void	valueRedContrastChanged ( int  );
			void	valueGreenContrastChanged ( int  );
			void	valueBlueContrastChanged ( int  );

			void	valueContrastChangedFinished ();
			void	valueRedContrastChangedFinished ();
			void	valueGreenContrastChangedFinished ();
			void	valueBlueContrastChangedFinished ();

			void valueVertOffsetChanged(int);
			void valueHoriOffsetChanged(int);
			void valueHoriOffsetChangedFinished();
			void valueVertOffsetChangedFinished();
			void dispatchVertOffset();
			void dispatchHoriOffset();

			void valueDBlackChanged(int);
			void valueDBlackChangedFinished();
			void dispatchDBlack();

			void valueFanCtrlChangedFinished();
			void valueFanCtrlChanged(int);
			void dispatchFanCtrl();

			void btnHoriRevert();
			void btnVertRevert();

			void currentBrilliantIndexChanged(int) ;
			void currentRegionIndexChanged(int) ;
			void currentOverlapIndexChanged(int);
			void currentCommaIndexChanged(int);

			void reset();
			void load();
			void save();
private:
	void adjustAllBrightness();
	void dispatchBrightness();

	void adjustAllContrast();
	void dispatchContrast();

	ResourceID screenid_;

	uint32_t fanCtrl_;

	short brightnessRed_;
	short brightnessGreen_;
	short brightnessBlue_;

	short contrastRed_;
	short contrastGreen_;
	short contrastBlue_;

	
	short brilliantColor_;
	short dynamicBlack_;
	short horiPos_;
	short vertPos_;
	char orientation_;

	short comma_;

	std::string initStr_;

	bool osdResponseRead( uint32_t , QboxDataMap& data, int);

	bool osdTaskResponse(uint32_t , QboxDataMap& data);

	std::list<talkCallback> tasks_;
public:
    explicit OsdImage(QWidget *parent , ResourceID screenid );
    ~OsdImage();
    
private:
    Ui::OsdImage *ui;
};

#endif // OSDIMAGE_H
