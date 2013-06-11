#ifndef Ring_H
#define Ring_H
#include <QWidget>
#include <map>
#include <list>
#include <QString>
#include <stdint.h>
#include "QboxNet.h"
#include "Screen.h"

class Ring :public QObject {
	
	friend class RingMgr;
	Ring(const std::string & id);
	~Ring();


	//rnodes of a ring.
	std::vector<ResourceID> rnodes_;
	

public:
	std::string id_;
	bool addNode( ResourceID inputid, ResourceID outputid);

	//a rnode only possible to be next by same col or same row of the previous rnode, sure also possible if it is the last what closure ring.
	bool isNextNodePossible( uint32_t row, uint32_t col);
	std::vector<ResourceID> getRnodes(){ return rnodes_;}
	bool removeNode( ResourceID rnode);
	uint32_t size(){ return rnodes_.size();}
};

class RingMgr :public QObject
{

	static  RingMgr* inst;
	RingMgr();


	friend class Ring;
	std::vector<Ring* > rings_;
public:
	~RingMgr();
	static RingMgr *instance();

	Ring* createRing(const std::string & id);
	Ring* createRing();
	void removeRing(Ring*);
	bool hasRing(const std::string & id);
	void removeRing(const std::string & id);
};




#endif // Ring_H
