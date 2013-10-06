#ifndef Mode_H
#define Mode_H
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"
#include <wnd.h>

struct WndData{
	std::wstring wndid_;
	ResourceID inputid_;
	std::wstring ringid_;
	double xPercent_, yPercent_, wPercent_, hPercent_, axPercent_, ayPercent_, awPercent_, ahPercent_;
};

class Mode {
	
	friend class ModeMgr;
	Mode(const std::wstring & id);
	~Mode();

	
public:
	std::wstring id_;
	std::vector<WndData> wnds_;
	bool isActivated_;
	void save();
	bool activate();
};

class ModeMgr
{

	static  ModeMgr* inst;
	ModeMgr();

	friend class Mode;
	std::vector<Mode* > modes_;
public:
	~ModeMgr();
	static ModeMgr *instance();

	Mode* createMode();
	Mode* createMode(const std::wstring & id);
	bool hasMode(const std::wstring & id);
	Mode* getMode(const std::wstring &id);
	bool removeMode(Mode*);
	void clear();
	std::vector<Mode*> &getAllModes(){ return  modes_;};
};




#endif // Mode_H
