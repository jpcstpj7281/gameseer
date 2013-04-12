#ifndef OIDProgressBar_H
#define OIDProgressBar_H

#include <QWidget>
#include <Snmpnet.h>
#include "qlabel.h"

#include <qlayout.h>
#include <qwt_thermo.h>
#include <qwt_color_map.h>



class OIDProgressBar: public QWidget
{
public:
    OIDProgressBar( Qt::Orientation orientation,
              const QString &text, QWidget *parent, double value = 0.0 ):
        QWidget( parent )
    {
        ql_ = new QLabel( text, this );
        ql_->setFont( QFont( "Helvetica", 8 ) );

        d_thermo = new QwtThermo( this );
        d_thermo->setRange( 0.0, 100.0 );
        d_thermo->setValue( value );
        d_thermo->setFont( QFont( "Helvetica", 7 ) );
        d_thermo->setPipeWidth( 6 );
        d_thermo->setScaleMaxMajor( 6 );
        d_thermo->setScaleMaxMinor( 5 );
        d_thermo->setFillBrush( Qt::darkMagenta );

#if 0
        QwtLinearColorMap *colorMap =
            new QwtLinearColorMap( Qt::blue, Qt::red );

        colorMap->addColorStop( 0.2, Qt::yellow );
        colorMap->addColorStop( 0.3, Qt::cyan );
        colorMap->addColorStop( 0.4, Qt::green );
        colorMap->addColorStop( 0.5, Qt::magenta );
        colorMap->setMode( QwtLinearColorMap::FixedColors );
        d_thermo->setColorMap( colorMap );
#endif

        QVBoxLayout *layout = new QVBoxLayout( this );
        layout->setMargin( 0 );
        layout->setSpacing( 0 );

        if ( orientation == Qt::Horizontal )
        {
            ql_->setAlignment( Qt::AlignCenter );
            d_thermo->setOrientation( orientation, QwtThermo::BottomScale );
            layout->addWidget( ql_ );
            layout->addWidget( d_thermo );
        }
        else
        {
            ql_->setAlignment( Qt::AlignRight );
            d_thermo->setOrientation( orientation, QwtThermo::LeftScale );
            layout->addWidget( d_thermo, 10, Qt::AlignHCenter );
            layout->addWidget( ql_, 0 );
        }
    }

    void setValue( double value )
    {
        d_thermo->setValue( value );
    }
	int value(){
		return d_thermo->value();
	}
private:
    QLabel *ql_;
    QwtThermo *d_thermo;


	void * inputDialog_;

	volatile int  val_;
	volatile int  isRunning_;

	virtual void	mouseReleaseEvent  ( QMouseEvent * event )override;
	void snmpCallback(  SnmpObj*);
public:

	OIDProgressBar( QWidget* w);
	void initSnmp();
	void shutdownSnmp();
};

#endif // OIDProgressBar