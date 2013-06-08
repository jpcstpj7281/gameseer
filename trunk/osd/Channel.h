#ifndef Channel_H
#define Channel_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"


class Channel :public QObject {
	
	friend class ChannelMgr;
	Channel( uint32_t row, uint32_t col);
	~Channel();

	uint32_t col_;
	uint32_t row_;


	virtual void	timerEvent ( QTimerEvent * event )override;
public:

};

class ChannelMgr :public QObject
{

	static  ChannelMgr* inst;
	ChannelMgr();

	virtual void	timerEvent ( QTimerEvent * event )override;
	friend class Channel;

public:
	~ChannelMgr();
	static ChannelMgr *instance();


};




#endif // Channel_H
