#ifndef Screen_H
#define Screen_H
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"
#include <vector>



typedef uint32_t ResourceID;	// do the ring input << 24 + ring output << 16 + row <<8 + col; id for screen, channel, ringnode, 
								// NOTE: all input output row and col start from 1, not 0; so ResourceID 0 means NULL;
								// which can represent screen id, input id, output id, wnode(for wnd), rnode(for ring), logically all unique

inline uint32_t GetRow(ResourceID id){ return (id >> 8) & 0xFF ;}
inline uint32_t GetCol(ResourceID id){ return id  & 0xFF ;}
inline uint32_t GetInput(ResourceID id){ return (id >> 24) & 0xFF ;}
inline uint32_t GetOutput(ResourceID id){ return (id >> 16) & 0xFF ;}
inline std::string ToStrID(ResourceID id){ return ("("+QString::number( GetInput(id))+")"+QString::number( GetRow(id))+"X"+QString::number( GetCol(id))+"("+QString::number( GetOutput(id))+")").toStdString();}
inline uint32_t ToScreenID( uint32_t row, uint32_t col){  return (row << 8) | col;}
inline ResourceID ToResourceID( uint32_t input, uint32_t output, uint32_t row, uint32_t col){ return (input<<24) | (output<<16) | (row << 8) | col;}

typedef uint32_t Resolution;    // resolution of w << 16 | h.
inline uint32_t GetWidth(Resolution res){ return (res>>12)& 0xfff;}
inline uint32_t GetHeight(Resolution res){ return res & 0xfff;}
inline uint32_t GetFreq(Resolution res){ return (res>>24)&0xff;}
inline Resolution toResolution( uint32_t width, uint32_t height, uint32_t freq){ return (freq<<24)|(width<<12)|height;}

typedef std::function< bool (ResourceID )> ResourceChangedCallback;

class Screen  {
	
	
	friend class ScreenMgr;
	Screen( uint32_t row, uint32_t col);
	~Screen();

	uint32_t col_;//start from 1
	uint32_t row_;//start from 1

	size_t inputCount_;
	Qbox* qbox_;

	//first for 753 out port id, second for Wnode
	std::map<ResourceID, ResourceID> outPort753_;
	//first for ring out port id, second for Rnode
	std::map<ResourceID, ResourceID> outPortRing_;
	//first for in port id, second for w << 16 + h resolution.
	std::map<ResourceID, uint32_t> inPort_;


	//only the inport num.
	std::list<uint32_t> reqInResolutions_;

	
	
	std::string version_;
	
	
	void versionRequest( );
	void inputResolutionRequest();
	void closeAllWndRequest();

	void outputRequest();
	bool inputResolutionCallback( uint32_t , QboxDataMap& );
	bool inputCallback( uint32_t , QboxDataMap& );
	bool outputCallback( uint32_t , QboxDataMap& );
	bool versionCallback( uint32_t , QboxDataMap& );
	std::vector< std::pair< QboxCallback, QboxDataMap> > slowDownCache_;

	void run();
	void reset();

public:
	void inputRequest( );
	void setVideoRequest(int inputNum ,int type, QboxCallback callback);
	void setDlpRequest(int dlpPower ,QboxCallback callback, size_t delay);
	void setLampRequest(int Lamp );
	void getDlpRequest(QboxCallback callback );
	void dlpTempRequest(QboxCallback callback, QboxDataMap &v );

	//bool isInputValid( ResourceID inputid);
	bool isOutputRingValid( ResourceID outputid);

	void versionRequest(QboxCallback callback, QboxDataMap &v );

	bool setWndRequestCB(double x, double y, double w, double h, ResourceID wnode, QboxCallback callback, uint32_t , QboxDataMap &v);
	void setWndRequest(double x, double y, double w, double h, ResourceID wnode, size_t delay);
	bool setWndRequestUintCB(size_t x, size_t y, size_t w, size_t h, ResourceID wnode, size_t delay, QboxCallback callback, uint32_t , QboxDataMap &v);
	void setWndRequestUint(size_t x, size_t y, size_t w, size_t h, ResourceID wnode, size_t delay);

	void setAreaRequest(size_t x, size_t y, size_t w, size_t h, ResourceID wnode, ResourceID inputid, size_t delay);
	bool setAreaRequestCB(size_t x, size_t y, size_t w, size_t h, ResourceID wnode, /*ResourceID inputid,*/ QboxCallback callback, uint32_t , QboxDataMap &v);
	void connInOutRequest(ResourceID inputid, ResourceID wnode);
	bool connInOutRequestCB(ResourceID inputid, ResourceID wnode, QboxCallback callback, uint32_t , QboxDataMap& v);

	bool showRequestCB(ResourceID wnode, size_t delay, QboxCallback callback, uint32_t , QboxDataMap &v);
	void showRequest(ResourceID wnode, size_t delay);
	void hideRequest(ResourceID wnode, size_t delay);
	bool hideRequestCB(ResourceID wnode, size_t delay, QboxCallback cb, uint32_t , QboxDataMap &v);

	void setLayerRequest(size_t layer, ResourceID wnode, size_t delay);
	bool setLayerRequestCB(size_t layer, ResourceID wnode, size_t delay, QboxCallback callback, uint32_t , QboxDataMap &v);

	bool connInOutRingRequest(ResourceID inputid, ResourceID rnode);
	bool freeRingRequest(ResourceID inputid, ResourceID rnode);
	
	bool hasRnode( ResourceID rnode);

	bool setAddress( const std::string & ip);
	std::string getAddress(){ return qbox_?qbox_->address():std::string("");}
	void connect();
	void disconnect();
	Qbox* getQbox(){ return qbox_;}

	inline ResourceID getResourceID(){ return ToScreenID(row_, col_);}
	inline Resolution getInResolution(ResourceID input){ Resolution res= inPort_[input]; return res==-1?0:res;}
	inline uint32_t getCol() { return col_;}
	inline uint32_t getRow() { return row_;}

	ResourceID getAvailable753Resource( void * handle);
	ResourceID getAvailableRingOutResource( void * handle);
	std::vector<ResourceID> getAvailableInput();
	//std::vector<ResourceID> getValidChnInResources();

	
//=======================================================OSD===============================================================
	//void osdRequest(QboxCallback callback, QboxDataMap &v );
	//void osdRequest(uint32_t addr, const std::string &data, QboxCallback callback );
	//void osdRequestChar(uint32_t addr, const char val, QboxCallback callback );
	//void osdRequestShort(uint32_t addr, const short val, QboxCallback callback );
	//void osdRequestUshort(uint32_t addr, const unsigned short val, QboxCallback callback );
	//void osdRequestInt(uint32_t addr, const int val, QboxCallback callback );
	//void osdRequestUint(uint32_t addr, const uint32_t val, QboxCallback callback );

	void osdRequestUncache(QboxCallback callback, QboxDataMap &v, size_t delay );
	void osdRequestUncache(uint32_t addr, const std::string &data, QboxCallback callback, size_t delay );
	void osdRequestCharUncache(uint32_t addr, const char val, QboxCallback callback, size_t delay );
	void osdRequestShortUncache(uint32_t addr, const short val, QboxCallback callback, size_t delay );
	void osdRequestUshortUncache(uint32_t addr, const unsigned short val, QboxCallback callback, size_t delay );
	void osdRequestIntUncache(uint32_t addr, const int val, QboxCallback callback, size_t delay );
	void osdRequestUintUncache(uint32_t addr, const uint32_t val, QboxCallback callback, size_t delay );

	void osdRequestRead(uint32_t addr, const uint32_t len, QboxCallback callback, uint32_t device, size_t delay);
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

	size_t areaDelay_;
	size_t layerDelay_;
	size_t setWndDelay_;
	size_t showDelay_;

	~ScreenMgr();
	static ScreenMgr *instance();

	//check whether insight of the wall.
	bool isValidScreenId( uint32_t row, uint32_t col){ return (row<=rowCount_&&row>0 && col<=colCount_&&col>0)?true:false;}
	void onInputChanged(ResourceChangedCallback callback);

	Screen* getScreen(ResourceID id);
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

	std::vector<ResourceID> clearWall();

	bool isInputValid( ResourceID inputid);
	bool isOutputRingValid( ResourceID outputid);

	//return wnode if there is 753port available
	ResourceID occupyScreenOut( ResourceID inputid);
	//return wnodes if there is 753port available
	std::vector<ResourceID> occupyScreensOut( std::vector<ResourceID> &rnodes);

	void freeScreensOut(std::vector<ResourceID> &wnodes);
	void ScreenMgr::freeScreenOut(ResourceID wnode);

	//get all that Input what with signal.
	std::vector<ResourceID> getAvailableInput();

	bool hasAvailableInput(ResourceID inputid);
	
	inline Resolution getInResolution(ResourceID input){ Resolution res= screens_[GetRow(input)-1][GetCol(input)-1]->inPort_[input]; return res==-1?0:res;}
	void setupTest();


	void closeAllWnds();
};




#endif // Screen_H

