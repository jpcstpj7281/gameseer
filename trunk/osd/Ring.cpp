#include "Ring.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

#include <QMainWindow>
#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Ring::Ring(const std::string & id):id_(id)
{
	
}
Ring::~Ring(){
}
bool Ring::isNextNodePossible(  uint32_t row, uint32_t col){
	if (!ScreenMgr::instance()->isValidScreenId(row,col)) return false;
	if (rnodes_.size() == 0 ) return true;
	
	ResourceID rnode = rnodes_.back();
	if ( GetRow(rnode) == row || GetCol(rnode) == col){
		return true;
	}
	rnode = rnodes_.front();
	if ( GetRow(rnode) == row && GetCol(rnode) == col){
		return true;
	}
	return false;
}
bool Ring::addNode( ResourceID inputid, ResourceID outputid){
	if ( GetRow(inputid) == GetRow(outputid) && GetCol(inputid) ==GetCol(outputid)){
		ResourceID rnode = inputid | outputid;
		for ( size_t i = 0; i < rnodes_.size(); ++i){
			if ( rnodes_[i] == rnode){
				return false;
			}
		}
		rnodes_.push_back(rnode);
		return true;
	}
	return false;
}
bool Ring::removeNode( ResourceID rnode){
	for ( auto i = rnodes_.begin(); i < rnodes_.end(); ++i){
		if ( *i == rnode){
			rnodes_.erase(i);
			return true;
		}
	}
	return false;
}


RingMgr* RingMgr::inst = 0;
RingMgr *RingMgr::instance(){
	if ( inst) return inst;
	return inst = new RingMgr();
}
RingMgr::RingMgr()
{

}
RingMgr::~RingMgr()
{
}
bool RingMgr::hasRing(const std::string & id){
	for( size_t i = 0 ; i < rings_.size(); ++i){
		if ( rings_[i]->id_ == id){
			return true;
		}
	}
	return false;
}
void RingMgr::removeRing(const std::string & id){
	for( auto i = rings_.begin() ; i < rings_.end(); ++i){
		if ( (*i)->id_ == id){
			rings_.erase(i);
		}
	}
}
void RingMgr::removeRing(Ring* r){
	for( auto i = rings_.begin() ; i < rings_.end(); ++i){
		if ( (*i) == r){
			rings_.erase(i);
			return;
		}
	}
}

Ring* RingMgr::createRing(const std::string & id){
	if ( hasRing(id)) return NULL;
	rings_.push_back(new Ring(id));
	return rings_.back();
}

Ring* RingMgr::createRing(){
	for ( size_t i = 0 ; i < 0xFFFFFFFF; ++i){
		std::string str = "Ring";
		std::string num = QString::number(i+1).toStdString();
		if (!hasRing(str + num)){
			return createRing( str+num);
			break;
		}
	}
	return NULL;
}