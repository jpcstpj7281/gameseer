#ifndef Screen_H
#define Screen_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <functional>
#include <stdint.h>
#include "QboxNet.h"


typedef uint32_t ResourceID; // do the ring input << 24 + ring output << 16 + row <<8 + col; id for screen, channel, ringnode

typedef std::function< bool (QboxDataMap& )> ScreenCallback;
typedef std::function< bool (ResourceID )> ResourceChangedCallback;

class Screen{
	void run();
	friend class ScreenMgr;
	Screen();
	~Screen();

	uint32_t col_;
	uint32_t row_;
	
	Qbox* qbox_;

	std::map<uint32_t, void* > resources_;

	void versionRequest(ScreenCallback callback, QboxDataMap &value );
	void inputRequest(ScreenCallback callback, QboxDataMap &value );
	void inputResolutionRequest(ScreenCallback callback, QboxDataMap &value );
	void outputRequest(ScreenCallback callback, QboxDataMap &value );

public:
	inline ResourceID getResourceID(){ return row_<<8+col_;}
	inline uint32_t getCol() { return col_;}
	inline uint32_t getRow() { return row_;}

	ResourceID getAvailable753Resource( void * handle);
	ResourceID getAvailableRingOutResource( void * handle);
	std::vector<ResourceID> getValidChnInResources();

	void osdRequest(ScreenCallback callback, QboxDataMap &value );

	void onInputChanged(ResourceChangedCallback callback);
	void onInputResolutionChanged(ResourceChangedCallback callback);
};

class ScreenMgr :public QObject
{

	static  ScreenMgr* inst;
	ScreenMgr();

	virtual void	timerEvent ( QTimerEvent * event )override;
	friend class Screen;

	uint32_t colCount_;
	uint32_t rowCount_;
	static const uint32_t MAXCOL = 64;
	static const uint32_t MAXROW = 8;

	Screen* screens_[MAXROW][MAXCOL];
public:
	~ScreenMgr();
	static ScreenMgr *instance();

	inline Screen* getScreen(ResourceID id){	
		int row = (id >> 8) & 0xFF;
		int col = id & 0xFF;
		return screens_[row][col];
	}
	bool addScreenCol( );
	bool addScreenRow(  );
	bool removeScreenCol( );
	bool removeScreenRow(  );
};




#endif // Screen_H
