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
								// which can represent screen id, input id, output id, wnode(for wnd), rnode(for ring), logically all unique

inline uint32_t GetRow(ResourceID id){ return (id >> 8) & 0xFF ;}
inline uint32_t GetCol(ResourceID id){ return id  & 0xFF ;}
inline uint32_t GetInput(ResourceID id){ return (id >> 24) & 0xFF ;}
inline uint32_t GetOutput(ResourceID id){ return (id >> 16) & 0xFF ;}
inline uint32_t ToScreenID( uint32_t row, uint32_t col){  return (row << 8) | col;}
inline ResourceID ToResourceID( uint32_t input, uint32_t output, uint32_t row, uint32_t col){ return (input<<24) | (output<<16) | (row << 8) | col;}

typedef uint32_t Resolution;    // resolution of w << 16 | h.
inline uint32_t GetWidth(Resolution res){ return res>>16;}
inline uint32_t GetHeight(Resolution res){ return res & 0xffff;}
inline Resolution toResolution( uint32_t width, uint32_t height){ return (width<<16)|height;}

typedef std::function< bool (ResourceID )> ResourceChangedCallback;

class Screen  {
	
	
	friend class ScreenMgr;
	Screen( uint32_t row, uint32_t col);
	~Screen();

	uint32_t col_;//start from 1
	uint32_t row_;//start from 1
	Qbox* qbox_;

	//first for 753 out port id, second for Wnode
	std::map<ResourceID, ResourceID> outPort753_;
	//first for ring out port id, second for Rnode
	std::map<ResourceID, ResourceID> outPortRing_;
	//first for in port id, second for w << 16 + h resolution.
	std::map<ResourceID, ResourceID> inPort_;


	//only the inport num.
	std::list<uint32_t> reqInResolutions_;

	
	
	std::string version_;
	
	void inputRequest( );
	void versionRequest( );
	void inputResolutionRequest();
	
	void outputRequest();
	bool inputResolutionCallback( uint32_t , QboxDataMap& );
	bool inputCallback( uint32_t , QboxDataMap& );
	bool outputCallback( uint32_t , QboxDataMap& );
	bool versionCallback( uint32_t , QboxDataMap& );
	std::vector< std::pair< QboxCallback, QboxDataMap> > slowDownCache_;

	void run();

public:
	//bool isInputValid( ResourceID inputid);
	bool isOutputRingValid( ResourceID outputid);

	void versionRequest(QboxCallback callback, QboxDataMap &value );

	bool setAddress( const std::string & ip);
	void connect();
	void disconnect();
	Qbox* getQbox(){ return qbox_;}

	inline ResourceID getResourceID(){ return (row_<< 8) + col_;}
	inline Resolution getInResolution(ResourceID input){ Resolution res= inPort_[input]; return res==-1?0:res;}
	inline uint32_t getCol() { return col_;}
	inline uint32_t getRow() { return row_;}

	ResourceID getAvailable753Resource( void * handle);
	ResourceID getAvailableRingOutResource( void * handle);
	std::vector<ResourceID> getAvailableInput();
	//std::vector<ResourceID> getValidChnInResources();

	
//=======================================================OSD===============================================================
	void osdRequest(QboxCallback callback, QboxDataMap &value );
	void osdRequest(uint32_t addr, const std::string &data, QboxCallback callback );
	void osdRequestChar(uint32_t addr, const char val, QboxCallback callback );
	void osdRequestShort(uint32_t addr, const short val, QboxCallback callback );
	void osdRequestUshort(uint32_t addr, const unsigned short val, QboxCallback callback );
	void osdRequestInt(uint32_t addr, const int val, QboxCallback callback );
	void osdRequestUint(uint32_t addr, const uint32_t val, QboxCallback callback );
	void osdRequestRead(uint32_t addr, const uint32_t len, QboxCallback callback, uint32_t device);
//=======================================================FOR TEST===============================================================
	void setupTestResource();
	void ajustResolution();
	void ajustInput();
};

class ScreenMgr 
{

	static  ScreenMgr* inst;
	ScreenMgr();

	friend class Screen;

	uint32_t colCount_;
	uint32_t rowCount_;
	static const uint32_t MAXCOL = 64;
	static const uint32_t MAXROW = 8;

	uint32_t screenWidth_;
	uint32_t screenHeight_;


	Screen* screens_[MAXROW][MAXCOL];

	std::vector<ResourceChangedCallback> inputChangedCallbacks_;
public:
	~ScreenMgr();
	static ScreenMgr *instance();

	bool isValidScreenId( uint32_t row, uint32_t col){ return (row<=rowCount_&&row>0 && col<=colCount_&&col>0)?true:false;}
	void onInputChanged(ResourceChangedCallback callback);

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

	//loop this, if you want this all work.
	void run();
	uint32_t getColCount(){ return colCount_;}
	uint32_t getRowCount(){ return rowCount_;}

	uint32_t getScreenWidth(){ return screenWidth_;}
	uint32_t getScreenHeight(){ return screenHeight_;}
	uint32_t getWallWidth(){ return screenWidth_ * colCount_;}
	uint32_t getWallHeight(){ return screenHeight_ * rowCount_;}

	bool isInputValid( ResourceID inputid);
	bool isOutputRingValid( ResourceID outputid);

	//get all that Input what with signal.
	std::vector<ResourceID> getAvailableInput();

	void setupTest();
};




#endif // Screen_H

