#include "peqwnd.h"
#include "ui_peqwnd.h"

#include <qlayout.h>
#include <QDebug>
#include "ACPlot.h"

#include <qwt_plot_canvas.h>
#include <qlayout.h>
#include "ACPlot.h"
#include "OIDPushBtn.h"
#include "OidDial.h"
#include <qcombobox.h>
#include <QTabWidget>
#include <QMouseEvent>
#include <QPushButton>
#include <qwhatsthis.h>
#include <qpainter.h>
#include <qwt_plot.h>
#include <qwt_symbol.h>
#include <qwt_scale_map.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_marker.h>
#include <qwt_plot_directpainter.h>
#include <qevent.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_scale_draw.h>
#include <qwt_scale_engine.h>

PEQWnd::PEQWnd(QTabWidget *parent) :
    QWidget(parent),
    ui(new Ui::PEQWnd)
	,tab_(parent)
	,selectedMarker_(0)
{
    ui->setupUi(this);

	for (size_t i =0; i < 21;++i){
		std::vector<PEQ> peq;
		if ( i < 16){
			peq.push_back( PEQ(0.5, 30, 0));
			peq.push_back( PEQ(0.5, 100, 0));
			peq.push_back( PEQ(0.5, 500, 0));
			peq.push_back( PEQ(0.5, 2000, 0));

		}else{
			peq.push_back( PEQ(0.5, 30, 0));
			peq.push_back( PEQ(0.5, 100, 0));
			peq.push_back( PEQ(0.5, 500, 0));
			peq.push_back( PEQ(0.5, 2000, 0));
			peq.push_back( PEQ(0.5, 10000, 0));
		}
		peqs_.push_back(peq);
	}

	QWidget * qw  = findChild<QWidget*>("PEQGraph" );
    if ( qw) {
		plot_ = new ACPlot( this );

		// The canvas picker handles all mouse and key
		// events on the plot_ canvas
		QVBoxLayout *layout = new QVBoxLayout( qw );
		qw->setLayout(layout);
		qw->layout()->addWidget(plot_);

		QwtPlotCanvas *canvas = plot_->canvas();

		canvas->installEventFilter( this );
		canvas->setFocusPolicy( Qt::StrongFocus );
#ifndef QT_NO_CURSOR
		canvas->setCursor( Qt::PointingHandCursor );
#endif
		canvas->setFocusIndicator( QwtPlotCanvas::ItemFocusIndicator );
		canvas->setFocus();

		const char *text =
			"All points can be moved using the left mouse button "
			"or with these keys:\n\n"
			"- Up:\t\tSelect next curve\n"
			"- Down:\t\tSelect previous curve\n"
			"- Left, ??\tSelect next point\n"
			"- Right, ??\tSelect previous point\n"
			"- 7, 8, 9, 4, 6, 1, 2, 3:\tMove selected point";
		canvas->setWhatsThis( text );

    }
	

	qpbl_ = findChildren<QPushButton*>( );
	for ( QList<QPushButton *>::Iterator it = qpbl_.begin(); it != qpbl_.end(); ){
		QPushButton* btn = *it;
		if ( btn->objectName().contains("btnInput") || btn->objectName().contains("btnOutput")){
			it = qpbl_.erase(it);
		}else{
			connect( btn, SIGNAL(clicked()), this, SLOT(clickch()));
			++it;
		}
	}
	

	currCHBtn_ = qpbl_.front();

	qdl_ = findChildren<OIDDial*>( );
	for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
		OIDDial* qs = *it;
		QString name = qs->objectName();
		name.replace( "dial_", "ls");
		QLabel* ql = findChild<QLabel*>(name);
		if (ql)qs->setLabel(ql);
		int index = name.replace("ls", "").toInt() -1;
		if ( index < 5){
			qs->setScale(1000.f);
			bwDl_[index % 5] = qs;
		}else if ( index < 10){
			freqDl_[index % 5] = qs;
		}else{
			qs->setScale(10.f);
			gainDl_[index % 5] = qs;
		}

		qs->setObjectName( "peq_"+qs->objectName() + currCHBtn_->objectName());
		qs->setToolTip(qs->objectName() );

		connect ( qs, SIGNAL(valueChanged ( int )), this, SLOT(valueChanged(int) ) );
	}

	connect ( parent, SIGNAL(currentChanged ( int )), this, SLOT(indexChanged(int) ) );

	currCHBtn_->setEnabled(false);
	currCHBtn_->setStyleSheet("* { background-color: lightGreen }");
}


PEQWnd::~PEQWnd()
{
    delete ui;
}

void PEQWnd::valueChanged ( int value ){
	std::vector<PEQ> * peq;
	if ( currCHBtn_->objectName().contains("Input")){
		int index= currCHBtn_->objectName().replace( "Inputpb", "").toInt() -1;
		peq = & peqs_[index];
	}else{
		int index= currCHBtn_->objectName().replace( "Outputpb", "").toInt() -1;
		peq = & peqs_[index+16];
	}
	int index= sender()->objectName().replace(currCHBtn_->objectName(), "").replace("peq_dial_", "").toInt()-1;
	if ( index < 5){
		peq->at(index).bandwidth = value/1000.f;
	}else if ( index <10){
		peq->at(index%5).freq= value;
	}else {
		peq->at(index%5).gain= value/10.f;
	}
	plot_->refreshPEQ(*peq);
}

void PEQWnd::save(QTextStream& stream){
	for ( size_t i = 0; i < peqs_.size(); ++i){
		for ( size_t j = 0; j < peqs_[i].size(); ++j){
			stream<< "peq_dial_"<<j+1;
			if ( i < 16){
				stream<< "Inputpb"<<i+1;
			}else{
				stream<< "Outputpb"<<i+1 - 16;
			}
			stream<<"="<<peqs_[i][j].bandwidth;

			stream<<";\n";
			stream<< "peq_dial_"<<j+1+5;
			if ( i < 16){
				stream<< "Inputpb"<<i+1;
			}else{
				stream<< "Outputpb"<<i+1 - 16;
			}
			stream<<"="<<peqs_[i][j].freq;
			stream<<";\n";

			stream<< "peq_dial_"<<j+1+10;
			if ( i < 16){
				stream<< "Inputpb"<<i+1;
			}else{
				stream<< "Outputpb"<<i+1 - 16;
			}
			stream<<"="<<peqs_[i][j].gain;
			stream<<";\n";
			
		}
	}
}
void PEQWnd::load(QString & objName, QString & val){
	std::vector<PEQ> * peq;
	QString temp ;
	int chindex;
	if ( objName.contains("Inputpb")){
		temp = objName.right(objName.size() - objName.indexOf("Inputpb"));
		int index= temp.right( temp.size() - 7).toInt() -1;
		peq = & peqs_[index];
		temp = objName.left(objName.indexOf("Inputpb"));
		chindex = temp.right(temp.size() - 9).toInt()-1;
	}else{
		temp = objName.right(objName.size() - objName.indexOf("Outputpb"));
		int index= temp.right( temp.size() - 8).toInt() -1;
		peq = & peqs_[index+16];
		temp = objName.left(objName.indexOf("Outputpb"));
		chindex = temp.right(temp.size() - 9).toInt()-1;
	}


	if ( chindex < 5){
		peq->at(chindex).bandwidth = val.toDouble();
	}else if ( chindex <10){
		peq->at(chindex%5).freq= val.toDouble();
	}else {
		peq->at(chindex%5).gain= val.toDouble();
	}
}

void PEQWnd::indexChanged(int index){
	QWidget* maybeThis = tab_->widget(index);

	if (maybeThis == this){
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			(*it)->initSnmp();
		}
	}else{
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			(*it)->shutdownSnmp();
		}
	}

	std::vector<PEQ> * peq;
	if ( currCHBtn_->objectName().contains("Input")){
		int index= currCHBtn_->objectName().replace( "Inputpb", "").toInt() -1;
		peq = & peqs_[index];
	}else{
		int index= currCHBtn_->objectName().replace( "Outputpb", "").toInt() -1;
		peq = & peqs_[index+16];
	}
	plot_->refreshPEQ(*peq);
}


void PEQWnd::clickch(){
	if ( sender() == currCHBtn_) return;
	currCHBtn_->setEnabled(true);
	currCHBtn_->setStyleSheet("");

	if ( sender()->objectName().contains("Input")){
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			OIDDial* qs = *it;
			if (qs->objectName().contains("dial_5") || qs->objectName().contains("dial_10")|| qs->objectName().contains("dial_15")){
				qs->setEnabled(false);
			}
		}
		int index= sender()->objectName().replace( "Inputpb", "").toInt() -1;
		plot_->refreshPEQ( peqs_[index]);
	}else{
		for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
			OIDDial* qs = *it;
			qs->setEnabled(true);
		}
		int index= sender()->objectName().replace( "Outputpb", "").toInt() -1;
		plot_->refreshPEQ( peqs_[index+16]);
	}

	qdl_ = findChildren<OIDDial*>( );
	for ( QList<OIDDial *>::Iterator it = qdl_.begin(); it != qdl_.end(); ++it){
		OIDDial* qs = *it;
		qs->shutdownSnmp();
		qs->setObjectName( qs->objectName().replace(  currCHBtn_->objectName(), sender()->objectName() ));
		qs->setToolTip(qs->objectName());
		qs->initSnmp();
	}

	currCHBtn_ = (QPushButton*)sender();

	currCHBtn_->setEnabled(false);
	currCHBtn_->setStyleSheet("* { background-color: lightGreen }");
}

bool PEQWnd::eventFilter( QObject *object, QEvent *event )
{
    if ( plot_ == NULL || object != plot_->canvas() )
        return false;

    switch( event->type() )
    {
        case QEvent::FocusIn:
        {
            showCursor( true );
            break;
        }
        case QEvent::FocusOut:
        {
            showCursor( false );
            break;
        }
        //case QEvent::Paint:
        //{
        //    QApplication::postEvent( this, new QEvent( QEvent::User ) );
        //    break;
        //}
        case QEvent::MouseButtonPress:
        {
            select( ( ( QMouseEvent * )event )->pos() );
            return true;
        }
        case QEvent::MouseMove:
        {
            move( ( ( QMouseEvent * )event )->pos() );
            return true;
        }
        case QEvent::KeyPress:
        {
            const int delta = 5;
            switch( ( ( const QKeyEvent * )event )->key() )
            {
                case Qt::Key_Up:
                {
                    shiftCurveCursor( true );
                    return true;
                }
                case Qt::Key_Down:
                {
                    shiftCurveCursor( false );
                    return true;
                }
                case Qt::Key_Right:
                case Qt::Key_Plus:
                {
                    if ( selectedMarker_ )
                        shiftPointCursor( true );
                    else
                        shiftCurveCursor( true );
                    return true;
                }
                case Qt::Key_Left:
                case Qt::Key_Minus:
                {
                    if ( selectedMarker_ )
                        shiftPointCursor( false );
                    else
                        shiftCurveCursor( true );
                    return true;
                }

                // The following keys represent a direction, they are
                // organized on the keyboard.

                case Qt::Key_1:
                {
                    moveBy( -delta, delta );
                    break;
                }
                case Qt::Key_2:
                {
                    moveBy( 0, delta );
                    break;
                }
                case Qt::Key_3:
                {
                    moveBy( delta, delta );
                    break;
                }
                case Qt::Key_4:
                {
                    moveBy( -delta, 0 );
                    break;
                }
                case Qt::Key_6:
                {
                    moveBy( delta, 0 );
                    break;
                }
                case Qt::Key_7:
                {
                    moveBy( -delta, -delta );
                    break;
                }
                case Qt::Key_8:
                {
                    moveBy( 0, -delta );
                    break;
                }
                case Qt::Key_9:
                {
                    moveBy( delta, -delta );
                    break;
                }
                default:
                    break;
            }
        }
        default:
            break;
    }

    return QObject::eventFilter( object, event );
}

// Select the point at a position. If there is no point
// deselect the selected point

void PEQWnd::select( const QPoint &pos )
{
    QwtPlotMarker *marker = NULL;

    double dist = 10e10;
    int index = -1;

    const QwtPlotItemList& itmList = plot_->itemList();
    for ( QwtPlotItemIterator it = itmList.begin(); it != itmList.end(); ++it )
    {
		if ( ( *it )->rtti() == QwtPlotItem::Rtti_PlotMarker )
        {
            QwtPlotMarker *c = ( QwtPlotMarker* )( *it );

            double d;
            //int idx = c->closestPoint( pos, &d );
			//picker_->transform(c->value());
			
			double cx= plot_->transform( c->xAxis(), c->value().x());
			double cy= plot_->transform( c->yAxis(), c->value().y());
			d = (pos - QPoint(cx, cy)).manhattanLength();

            if ( d < dist )
            {
                marker = c;
                dist = d;
            }
        }
    }

    showCursor( false );
    selectedMarker_ = NULL;
    selectedPoint_ = -1;

    if ( marker && dist < 10 ) // 10 pixels tolerance
    {
        selectedMarker_ = marker;
        //selectedPoint_ = index;
        showCursor( true );
    }
}



// Move the selected point
void PEQWnd::moveBy( int dx, int dy )
{
    if ( dx == 0 && dy == 0 )
        return;

    if ( !selectedMarker_ )
        return;

    //const QPointF sample =selectedMarker_->sample( selectedPoint_ );

    //const double x = plot_->transform(selectedMarker_->xAxis(), sample.x() );
    //const double y = plot_->transform(selectedMarker_->yAxis(), sample.y() );

    //move( QPoint( qRound( x + dx ), qRound( y + dy ) ) );
}

// Move the selected point
void PEQWnd::move( const QPoint &pos )
{
    if ( !selectedMarker_ )
        return;

	double cx= plot_->invTransform( selectedMarker_->xAxis(), pos.x());
	double cy= plot_->invTransform( selectedMarker_->yAxis(), pos.y());
	selectedMarker_->setValue( cx, cy);
	int index  = plot_->markerIndex( selectedMarker_);
	freqDl_[index]->setValue( cx);
	gainDl_[index]->setValue( cy *10);
	//plot_->replot();

    showCursor( true );
}

// Hightlight the selected point
void PEQWnd::showCursor( bool showIt )
{
    if ( !selectedMarker_ )
        return;

    //QwtSymbol *symbol = const_cast<QwtSymbol *>( selectedMarker_->symbol() );

    //const QBrush brush = symbol->brush();
    //if ( showIt )
    //    symbol->setBrush( symbol->brush().color().dark( 180 ) );

    //QwtPlotDirectPainter directPainter;
    //directPainter.drawSeries( selectedMarker_, selectedPoint_, selectedPoint_ );

    //if ( showIt )
    //    symbol->setBrush( brush ); // reset brush
}

// Select the next/previous curve
void PEQWnd::shiftCurveCursor( bool up )
{
    QwtPlotItemIterator it;

    //const QwtPlotItemList &itemList = plot_->itemList();

    //QwtPlotItemList curveList;
    //for ( it = itemList.begin(); it != itemList.end(); ++it )
    //{
    //    if ( ( *it )->rtti() == QwtPlotItem::Rtti_PlotCurve )
    //        curveList += *it;
    //}
    //if ( curveList.isEmpty() )
    //    return;

    //it = curveList.begin();

    //if ( selectedMarker_ )
    //{
    //    for ( it = curveList.begin(); it != curveList.end(); ++it )
    //    {
    //        if ( selectedMarker_ == *it )
    //            break;
    //    }
    //    if ( it == curveList.end() ) // not found
    //        it = curveList.begin();

    //    if ( up )
    //    {
    //        ++it;
    //        if ( it == curveList.end() )
    //            it = curveList.begin();
    //    }
    //    else
    //    {
    //        if ( it == curveList.begin() )
    //            it = curveList.end();
    //        --it;
    //    }
    //}

    //showCursor( false );
    //selectedPoint_ = 0;
    //selectedMarker_ = ( QwtPlotMarker * ) * it;
    //showCursor( true );
}

// Select the next/previous neighbour of the selected point
void PEQWnd::shiftPointCursor( bool up )
{
    if ( !selectedMarker_ )
        return;

    //int index = selectedPoint_ + ( up ? 1 : -1 );
    //index = ( index + selectedMarker_->dataSize() ) % selectedMarker_->dataSize();

    //if ( index != selectedPoint_ )
    //{
    //    showCursor( false );
    //    selectedPoint_ = index;
    //    showCursor( true );
    //}
}


bool PEQWnd::event( QEvent *ev )
{
    if ( ev->type() == QEvent::User )
    {
        showCursor( true );
        return true;
    }
    return QObject::event( ev );
}