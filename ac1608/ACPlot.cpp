#include "ACPlot.h"
#include <qevent.h>
#include <qwhatsthis.h>
#include <qpainter.h>
#include <qwt_plot.h>
#include <qwt_symbol.h>
#include <qwt_scale_map.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_directpainter.h>
#include <qevent.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_engine.h>
#include <qvector.h>
#include <Qwt_Plot_Marker.h>

class RealScaleDraw: public QwtScaleDraw
{
public:
    RealScaleDraw()
    {
    }
    virtual QwtText label(double v) const
    {
        //return QwtScaleDraw::label(v);
		int val = (int)v;
		if (v > 1000){
				return QwtText(QString::number(val/1000)+ "kHz"); 
		}else{
				return QwtText(QString::number(val)+ "Hz");
		}
    }
};

ACPlot::ACPlot( QWidget *parent ):
    QwtPlot( parent )
{
    //setTitle( "Interactive ACPlot" );

	setCanvasBackground( Qt::black );

    QwtPlotGrid *grid = new QwtPlotGrid;
	grid->setMajPen( QPen( Qt::white, 0, Qt::SolidLine ) );
    grid->attach( this );

	QwtScaleEngine *eng = new QwtLog10ScaleEngine();
	setAxisScale( QwtPlot::xBottom, 20, 20000);
	setAxisScaleEngine(QwtPlot::xBottom, eng );
	setAxisScaleDraw(QwtPlot::xBottom, new RealScaleDraw);

    // axes
    setAxisScale( QwtPlot::yLeft, -30.0, 30.0 );

    plotLayout()->setAlignCanvasToScales( true );

	for ( size_t i = 0; i < 5; ++i){
		curves_[i] = new QwtPlotCurve;
		//curves_[i]->setPen( QColor(Qt::green) );
		//curves_[i]->setSymbol( new QwtSymbol( QwtSymbol::Hexagon, Qt::gray, QColor(Qt::green), QSize( 8, 8 ) ) );
		curves_[i]->attach( this );
	}
	curves_[0]->setPen( QColor(Qt::green) );
	curves_[1]->setPen( QColor(Qt::blue) );
	curves_[2]->setPen( QColor(Qt::cyan) );
	curves_[3]->setPen( QColor(Qt::yellow) );
	curves_[4]->setPen( QColor(Qt::darkMagenta) );
	//curves_[0]->setSymbol( new QwtSymbol( QwtSymbol::NoSymbol, Qt::gray, QColor(Qt::green), QSize( 8, 8 ) ) );
	//curves_[1]->setSymbol( new QwtSymbol( QwtSymbol::NoSymbol, Qt::gray, QColor(Qt::blue), QSize( 8, 8 ) ) );
	//curves_[2]->setSymbol( new QwtSymbol( QwtSymbol::NoSymbol, Qt::gray, QColor(Qt::cyan), QSize( 8, 8 ) ) );
	//curves_[3]->setSymbol( new QwtSymbol( QwtSymbol::NoSymbol, Qt::gray, QColor(Qt::yellow), QSize( 8, 8 ) ) );
	//curves_[4]->setSymbol( new QwtSymbol( QwtSymbol::NoSymbol, Qt::gray, QColor(Qt::darkMagenta), QSize( 8, 8 ) ) );

	redCurves_ = new QwtPlotCurve;
	redCurves_->setPen( QColor(Qt::red) );
	redCurves_->setSymbol( new QwtSymbol( QwtSymbol::NoSymbol, Qt::gray, QColor(Qt::red), QSize( 8, 8 ) ) );
	redCurves_->attach( this );

	for ( size_t i = 0; i < 5; ++i){
		markers_[i] = new QwtPlotMarker;
		markers_[i]->attach( this );
	}
	markers_[0]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::green, QColor(Qt::green), QSize( 8, 8 ) ) );
	markers_[1]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::blue, QColor(Qt::blue), QSize( 8, 8 ) ) );
	markers_[2]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::cyan, QColor(Qt::cyan), QSize( 8, 8 ) ) );
	markers_[3]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::yellow, QColor(Qt::yellow), QSize( 8, 8 ) ) );
	markers_[4]->setSymbol( new QwtSymbol( QwtSymbol::Ellipse, Qt::darkMagenta, QColor(Qt::darkMagenta), QSize( 8, 8 ) ) );

}



void ACPlot::refreshPEQ(const std::vector<PEQ>& peqs){
	//for ( size_t i =0; i < peqs.size(); ++i){
	//	qDebug()<<peqs[i].bandwidth;
	//}

	//绘制带通波形
	double y[512],y3[512];
	double pi=3.1415926;
	int i,ny,j,F0,k;

	double C,L,R,XC,XL,XZ;
	static QVector<double> yData;
	static QVector<double> xData;

	memset(y3,0,sizeof(double)*512);
	memset(y,0,sizeof(double)*512);
	j=0;
	C=0.0022;
	double m_QValue;
	for ( size_t k = 0; k < 5; ++k){
		curves_[k]->detach();
	}
	for ( size_t k = 0; k < peqs.size(); ++k){
		F0=peqs[k].freq;
		m_QValue = std::pow( 2, peqs[k].bandwidth / 2 );
		m_QValue = m_QValue / ( m_QValue * m_QValue - 1 );//求出Q值
		//m_QValue=1;

		L=dd2((std::pow(1/(2*pi*F0),2))/C); //取DOUBLE后八8位小数,四舍五入
		R=m_QValue*2*pi*F0*L; 


		j=0;
		for(i=20;i<20000;i+=FREQ_STEP(i))
		{
			XC=1/(2*pi*i*C);
			XL=2*pi*i*L;

			//XZ=(XL*XC)/((XL>XC)?(XL-XC):(XC-XL));
			XZ=(XL*XC)/fabs(XL-XC);
			XZ=(peqs[k].gain*(R*XZ)/(sqrt(R*R+XZ*XZ)))*(4.5/R);
			y[j]=XZ/(27/6.f);

			y3[j]+=y[j];
			j++;
		}

		double Y = 10000000;
		yData.clear();
		xData.clear();
		for(j=0, i=20;i<20000;i+=FREQ_STEP(i)){
			xData.push_back(i);
			yData.push_back(y[j++]);
			if ( Y ==  10000000 && F0 <= i){
				Y = y[j-1];
			}
		}
		
		markers_[k]->setXValue(F0);
		markers_[k]->setYValue(Y);
		markers_[k]->attach(this);
		curves_[k]->setSamples( xData, yData );
		curves_[k]->attach(this);
	}

	yData.clear();
	xData.clear();
	for(j=0,i=20;i<20000;i+=FREQ_STEP(i))
	{
		xData.push_back(i);
		yData.push_back(y3[j++]);
	}
	redCurves_->setSamples( xData, yData );

	replot();
}
