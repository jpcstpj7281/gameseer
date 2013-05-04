#ifndef Screen_H
#define Screen_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"


typedef uint32_t ResourceID;	// do the ring input << 24 + ring output << 16 + row <<8 + col; id for screen, channel, ringnode, 
								// NOTE: all input output row and col start from 1, not 0; so ResourceID 0 means NULL;

inline uint32_t GetRow(ResourceID id){ return (id >> 8) & 0xFF ;}
inline uint32_t GetCol(ResourceID id){ return id  & 0xFF ;}
inline uint32_t GetInput(ResourceID id){ return (id >> 24) & 0xFF ;}
inline uint32_t GetOutput(ResourceID id){ return (id >> 16) & 0xFF ;}
inline uint32_t ToScreenID( uint32_t row, uint32_t col){  return (row << 8) | col;}
inline uint32_t ToResourceID( uint32_t input, uint32_t output, uint32_t row, uint32_t col){ return (input<<24) | (output<<16) | (row << 8) | col;}

typedef std::function< bool (ResourceID )> ResourceChangedCallback;

class Screen :public QObject {
	
	void run();
	friend class ScreenMgr;
	Screen( uint32_t row, uint32_t col);
	~Screen();

	uint32_t col_;
	uint32_t row_;
	Qbox* qbox_;

	std::map<uint32_t, void* > resources_;

	
	void inputRequest(QboxCallback callback, QboxDataMap &value );
	void inputResolutionRequest(QboxCallback callback, QboxDataMap &value );
	void outputRequest(QboxCallback callback, QboxDataMap &value );

	std::vector< std::pair< QboxCallback, QboxDataMap> > slowDownCache_;

	virtual void	timerEvent ( QTimerEvent * event )override;
public:
	void versionRequest(QboxCallback callback, QboxDataMap &value );

	bool setAddress( const std::string & ip);
	void connect();
	void disconnect();
	Qbox* getQbox(){ return qbox_;}

	inline ResourceID getResourceID(){ return (row_<< 8) + col_;}
	inline uint32_t getCol() { return col_;}
	inline uint32_t getRow() { return row_;}

	ResourceID getAvailable753Resource( void * handle);
	ResourceID getAvailableRingOutResource( void * handle);
	std::vector<ResourceID> getValidChnInResources();

	void osdRequest(QboxCallback callback, QboxDataMap &value );
	void osdRequest(uint32_t addr, const std::string &data, QboxCallback callback );
	void osdRequestChar(uint32_t addr, const char val, QboxCallback callback );
	void osdRequestShort(uint32_t addr, const short val, QboxCallback callback );
	void osdRequestUshort(uint32_t addr, const unsigned short val, QboxCallback callback );
	void osdRequestInt(uint32_t addr, const int val, QboxCallback callback );
	void osdRequestUint(uint32_t addr, const uint32_t val, QboxCallback callback );
	void osdRequestRead(uint32_t addr, const uint32_t len, QboxCallback callback, uint32_t device);

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
		int row = (id >> 8) & 0xFF - 1;//start from 1, not 0
		int col = (id & 0xFF) - 1; //start from 1, not 0
		return screens_[row][col];
	}
	std::vector<ResourceID> addScreenCol();
	std::vector<ResourceID> addScreenRow();
	std::vector<ResourceID> addScreens( uint32_t rowCount, uint32_t colCount);
	std::vector<ResourceID> removeScreenCol();
	std::vector<ResourceID> removeScreenRow();
};




#endif // Screen_H
