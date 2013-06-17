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
	
	bool isActivate_;
public:
	std::string id_;
	bool isEnable_;
	
	void activate( bool flag);

	bool isActivate(){ return isActivate_;}

	//a rnode only possible to be next by same col or same row of the previous rnode, sure also impossible if it is the last one that closure .
	bool isNextNodePossible( uint32_t row, uint32_t col);
	bool isNextNodePossible( );
	std::vector<ResourceID> getRnodes(){ return rnodes_;}
	bool removeNode( ResourceID rnode);
	uint32_t size(){ return rnodes_.size();}

	bool makeNode( ResourceID rnode, uint32_t index);

	bool isCollided( Ring*);
	bool isClosed(){ return rnodes_.size() > 0 ? (GetRow(rnodes_.front()) ==GetRow(rnodes_.back()) && GetCol(rnodes_.front()) ==GetCol(rnodes_.back()) ? true:false):false;}

	ResourceID getInputRNode(ResourceID inputid);
	ResourceID getOutputRNode(ResourceID outputid);
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
	Ring* getRing(const std::string & id);
	std::vector<Ring* > getRings() { return rings_;}

	std::vector<Ring* > getInputCorrespondRing( ResourceID inputid);
	std::vector<Ring* > getOutputCorrespondRing( ResourceID outputid);
	std::vector<Ring* > getInputCorrespondActivatedRing( ResourceID inputid);
	std::vector<Ring* > getOutputCorrespondActivatedRing( ResourceID outputid);
};




#endif // Ring_H
