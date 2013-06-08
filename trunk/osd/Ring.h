#ifndef Ring_H
#define Ring_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"


class Ring :public QObject {
	
	friend class RingMgr;
	Ring( uint32_t row, uint32_t col);
	~Ring();

	uint32_t col_;
	uint32_t row_;


	virtual void	timerEvent ( QTimerEvent * event )override;
public:

};

class RingMgr :public QObject
{

	static  RingMgr* inst;
	RingMgr();

	virtual void	timerEvent ( QTimerEvent * event )override;
	friend class Ring;

public:
	~RingMgr();
	static RingMgr *instance();


};




#endif // Ring_H
