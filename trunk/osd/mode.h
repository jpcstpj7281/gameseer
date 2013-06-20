#ifndef Mode_H
#define Mode_H
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"
#include <wnd.h>

class Mode {
	
	friend class ModeMgr;
	Mode(const std::string & id);
	~Mode();

	std::vector<Wnd*> wnds_;
public:
	std::string id_;
	
	std::vector<Wnd*> &getWnds(){ return wnds_;}
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
	Mode* createMode(const std::string & id);
	bool hasMode(const std::string & id);
	Mode* getMode(const std::string &id);
	bool removeMode(Mode*);
	std::vector<Mode*> &getAllModes(){ return  modes_;};
};




#endif // Mode_H
