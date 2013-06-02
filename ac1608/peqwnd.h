#ifndef PEQWND_H
#define PEQWND_H

#include <QWidget>
#include <Qwt_Plot_Picker.h>
#include <QTextStream>

class OIDStatePushBtn;
class OIDDial;
class QTabWidget;
class QPushButton;
class ACPlot;
struct PEQ;
class QwtPlotCurve;
class QwtPlotMarker;

namespace Ui {
class PEQWnd;
}

class PEQWnd : public QWidget
{
    Q_OBJECT
		private slots:
			void indexChanged(int index);
			void clickch();
			void	valueChanged ( int value );
public:
    explicit PEQWnd(QTabWidget *parent = 0);
    ~PEQWnd();

	void save(QTextStream& stream);
	void load(QString & objName, QString & val);
    
private:
	void select( const QPoint & );
    void move( const QPoint & );
    void moveBy( int dx, int dy );
	void release();

    void showCursor( bool enable );
    void shiftPointCursor( bool up );
    void shiftCurveCursor( bool up );
	virtual bool eventFilter( QObject *, QEvent * );
	virtual bool event( QEvent * );

    Ui::PEQWnd *ui;


	QTabWidget *tab_;
	QList<OIDDial *> qdl_;
	QList<QPushButton *> qpbl_;
	QPushButton * currCHBtn_;
	ACPlot *plot_;
	QwtPlotPicker * picker_;


	OIDDial * bwDl_[5];
	OIDDial * freqDl_[5];
	OIDDial * gainDl_[5];
	std::vector<std::vector<PEQ>> peqs_;

	QwtPlotMarker *selectedMarker_;
    int selectedPoint_;
};

#endif // PEQWND_H
