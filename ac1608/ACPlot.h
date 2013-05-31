#ifndef ACPLOT_H
#define ACPLOT_H

#include <qwt_plot.h>
#include <qobject.h>



class QPoint;
class QCustomEvent;
class QwtPlot;
class QwtPlotCurve;
class ColorBar;
class QwtWheel;
class QwtPlotMarker;

static int BitsOfNumber(int val)
{
	//返回数值位数
	if((val/1)<10)
		return 0;	//个
	if((val/10)<10)
		return 1;	//十
	else if((val/100)<10)
		return 2;	//百
	else if((val/1000)<10)
		return 3;	//千
	else if((val/10000)<10)
		return 4;	//万
	else
		return 0;	//无效
}

//int CalcXPos(int sFreq,int eFreq,int freq,CRect *rect)
//{
//	//根据输入的参数计算出在X坐标的位置
//	int step=(int)((rect->right-rect->left)/(log10((float)eFreq)-log10((float)sFreq)))-4;
//	
//	float fLog=(float)(log10((float)freq)-log10((float)sFreq));
//	return (int)(rect->left+fLog*step);
//}

//对double型只取8位有效值,4舍5入
#define	dd2(x)	((double)(((int)(((x)+0.000000005)*100000000)))/100000000)  
#define FREQ_STEP(x)	(int)((std::pow((double)10,BitsOfNumber(x)-1)+1)/2)

struct PEQ{
	double freq;
	double gain;
	double bandwidth;
	PEQ(double bandwidth, double freq, double gain):
	freq(freq)
		,gain(gain)
		,bandwidth(bandwidth)
	{
	}
};

class ACPlot: public QwtPlot
{
    Q_OBJECT

private:

	QwtPlotCurve * curves_[5];
	QwtPlotMarker * markers_[5];
	QwtPlotCurve * redCurves_;
    void insertCurve( Qt::Orientation, const QColor &, double base );
public:
    ACPlot( QWidget *parent = NULL );
	void refreshPEQ(const std::vector<PEQ>& peqs);

	int markerIndex( QwtPlotMarker* marker){
		for ( int i = 0; i < 5; ++i){
			if ( marker == markers_[i]){
				return i;
			}
		}
	}

	
};



#endif //ACPLOT_H