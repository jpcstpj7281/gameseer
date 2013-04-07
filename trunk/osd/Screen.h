#ifndef Screen_H
#define Screen_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <functional>
#include <stdint.h>


#define QBOX_VALUE_STRING "String"
#define QBOX_VALUE_HEX_BIN "Hex Bin"
#define QBOX_VALUE_DEC_INT "Dec Int"
#define QBOX_VALUE_DEC_UINT "Dec Uint"


class ScreenObj;
typedef std::map<std::string, std::string>	ScreenDataMap;
typedef std::function< bool ( uint32_t , ScreenDataMap& )> ScreenCallbackFunc;

class Screen{
	struct Impl;
	Impl *impl_;

	void run();
	friend class ScreenMgr;
	Screen();
	~Screen();
	
public:
};

class ScreenMgr :public QObject 
{

	static  ScreenMgr* inst;
	ScreenMgr();

	virtual void	timerEvent ( QTimerEvent * event )override;

	struct Impl;
	Impl* impl_;
	friend class Screen;
public:
	~ScreenMgr();
	static ScreenMgr *instance();

	bool hasScreen(std::string &ip);
	bool hasScreen( int row, int col);
	Screen* getScreen( std::string &ip);//create one if not there
	Screen* getScreen( int row, int col);//create one if not there
	bool removeScreen( std::string &ip);
	bool removeScreen( int row, int col);
};




#endif // Screen_H
