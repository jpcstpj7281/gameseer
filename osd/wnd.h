#ifndef Wnd_H
#define Wnd_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"
#include "Screen.h"

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
	Wnd* createWnd( double xPercent, double yPercent, double widthPercent, double heightPercent);
	Wnd* createWnd( const std::string & id, double xPercent, double yPercent, double widthPercent, double heightPercent);
	bool hasWnd(const std::string & id);
	std::vector<Wnd* > getWnds(){ return wnds_;}
	bool closeWnd(Wnd*);
	
	std::vector<Wnd* > getAllWnds(){ return wnds_;}
};

class Wnd {
	
	friend class WndMgr;
	Wnd( uint32_t row, uint32_t col);
	~Wnd();

	uint32_t layer_;
	
	

	

	//rnodes of a ring.
	std::list<ResourceID> wnodes_;

	Wnd( double xPercent, double yPercent, double wPercent, double hPercent);
	Wnd( uint32_t x, uint32_t y, uint32_t w, uint32_t h);
public:
	double xPercent_, yPercent_, wPercent_, hPercent_;
	uint32_t x_,y_,w_, h_, ax_, ay_, aw_, ah_;

	std::string id_;

	uint32_t getLayer(){return layer_;}
	uint32_t bringFront(){ return layer_ == WndMgr::instance()->currlayer_ ? layer_: layer_= ++ WndMgr::instance()->currlayer_;}
	bool resizeWnd(double xPercent, double yPercent, double wPercent, double hPercent);
	bool moveWnd(double xPercent, double yPercent);
};






#endif // Wnd_H
