#ifndef Window_H
#define Window_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"


class Window :public QObject {
	
	friend class WindowMgr;
	Window( uint32_t row, uint32_t col);
	~Window();

	uint32_t col_;
	uint32_t row_;


	virtual void	timerEvent ( QTimerEvent * event )override;
public:

};

class WindowMgr :public QObject
{

	static  WindowMgr* inst;
	WindowMgr();

	virtual void	timerEvent ( QTimerEvent * event )override;
	friend class Window;

public:
	~WindowMgr();
	static WindowMgr *instance();


};




#endif // Window_H
