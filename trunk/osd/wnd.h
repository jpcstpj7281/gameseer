#ifndef Wnd_H
#define Wnd_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"
#include "Screen.h"
#include <Ring.h>

class Wnd;

class WndMgr :public QObject
{

	static  WndMgr* inst;
	WndMgr();

	uint32_t currlayer_;


	friend class Wnd;

	std::vector<Wnd* > wnds_;
public:



	~WndMgr();
	static WndMgr *instance();

	//the percentage of wall
	Wnd* createWnd( double xPercent, double yPercent, double widthPercent, double heightPercent, ResourceID inputid, Ring* ring);
	Wnd* createWnd( const std::string & id, double xPercent, double yPercent, double widthPercent, double heightPercent, ResourceID inputid, Ring* ring);
	bool hasWnd(const std::string & id);
	std::vector<Wnd* > getWnds(){ return wnds_;}
	Wnd* getWnd(const std::string &id);
	bool closeWnd(Wnd*);
	uint32_t getCurrLayer(){ return currlayer_;}
	
	std::vector<Wnd* > getAllWnds(){ return wnds_;}
};

class Wnode{
public:
	ResourceID wnodeid_;
	double xp_,yp_,wp_, hp_, axp_, ayp_, awp_, ahp_, leftCut_, rightCut_, topCut_,bottomCut_;
	Wnode(ResourceID wnodeid, double xp,double yp,double wp, double hp, double leftCut, double rightCut, double topCut, double bottomCut):
	wnodeid_(wnodeid),xp_(xp),yp_(yp),wp_(wp), hp_(hp), leftCut_(leftCut), rightCut_(rightCut), topCut_(topCut), bottomCut_(bottomCut){}
	void setArea(double axp,double ayp,double awp, double ahp ){
		axp_=axp;
		ayp_=ayp; 
		awp_=awp; 
		ahp_=ahp;
	}
};

class Wnd {
	
	friend class WndMgr;
	Wnd( uint32_t row, uint32_t col);
	~Wnd();

	uint32_t layer_;
	ResourceID inputid_;
	
	//rnodes of a ring.
	

	Wnd( double xPercent, double yPercent, double wPercent, double hPercent, ResourceID inputid);
	//Wnd( uint32_t x, uint32_t y, uint32_t w, uint32_t h);
public:
	std::vector<Wnode*> wnodes_;
	double xPercent_, yPercent_, wPercent_, hPercent_, axPercent_, ayPercent_, awPercent_, ahPercent_;
	
	size_t getX(){ return xPercent_*ScreenMgr::instance()->getWallWidth();}
	size_t getY(){ return yPercent_*ScreenMgr::instance()->getWallHeight();}
	size_t getW(){ return wPercent_*ScreenMgr::instance()->getWallWidth();}
	size_t getH(){ return hPercent_*ScreenMgr::instance()->getWallHeight();}
	size_t getAX(){ return axPercent_;}
	size_t getAY(){ return ayPercent_;}
	size_t getAW(){ return awPercent_;}
	size_t getAH(){ return ahPercent_;}


	std::string id_;

	uint32_t getLayer(){return layer_;}
	uint32_t bringFront(){ return layer_ == WndMgr::instance()->currlayer_ ? layer_: layer_= ++ WndMgr::instance()->currlayer_;}
	bool resizeWnd(double xPercent, double yPercent, double wPercent, double hPercent);
	bool moveWnd(double xPercent, double yPercent);
	Wnode * getWnode( ResourceID wnode);
};






#endif // Wnd_H
