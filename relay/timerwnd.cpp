#include "timerwnd.h"
#include "ui_TimerWnd.h"

#include <qdebug.h>


TimerWnd::TimerWnd( ):
    QWidget(0)
	,ui(new Ui::TimerWnd)
{
    ui->setupUi(this);

	QCalendarWidget* caldr = findChild<QCalendarWidget*>("calendarWidget");
	if ( caldr){
		//caldr->paintCell();
	}
}

TimerWnd::~TimerWnd()
{
    delete ui;
}

void TimerWnd::clearClicked(bool){
}
void TimerWnd::sendClicked(bool){
}


