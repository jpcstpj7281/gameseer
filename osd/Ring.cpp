#include "Ring.h"
#include<QtDebug>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"
#include <QMainWindow>


Ring::Ring(const std::string & id):id_(id),isEnable_(false),isActivate_(false)
{
	
}
Ring::~Ring(){
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
bool Ring::isNextNodePossible(  uint32_t row, uint32_t col){
	if (!ScreenMgr::instance()->isValidScreenId(row,col)) return false;
	if (rnodes_.size() == 0 ) return true;
	
	if ( col== GetCol(rnodes_.back()) && row== GetRow(rnodes_.back())  ){
		return false;
	}
	if ( col== GetCol(rnodes_.front()) && row== GetRow(rnodes_.front())  ){
		return false;
	}
	for( size_t i = 1; i < rnodes_.size();++i){
		if ( col== GetCol(rnodes_[i]) && row== GetRow(rnodes_[i]) ){
			return false;
		}
	}
	return true;
}
bool Ring::isNextNodePossible(  ){
	if ( rnodes_.size()  > 2 && (GetCol(rnodes_.front())== GetCol(rnodes_.back()) && GetRow(rnodes_.front())== GetRow(rnodes_.back()) ) ){
		return false;
	}
	return true;
}
bool Ring::makeNode( ResourceID rnode, uint32_t index){
	if ( index == rnodes_.size()){
		if ( rnodes_.size() >0){
			
			if ( GetCol(rnode )== GetCol(rnodes_.back()) && GetRow(rnode )== GetRow(rnodes_.back())  ){
				return false;
			}
			for( size_t i = 1; i < rnodes_.size();++i){
				if ( GetCol(rnode )== GetCol(rnodes_[i]) && GetRow(rnode )== GetRow(rnodes_[i]) ){
					return false;
				}
			}
			//近邻上一个或同第一个相同的环接才合法.
			if ( GetCol(rnodes_.back()) ==GetCol(rnode) || GetRow(rnodes_.back()) ==GetRow(rnode) || (GetCol(rnodes_.front()) ==GetCol(rnode) && GetRow(rnodes_.front()) ==GetRow(rnode))){
				rnodes_.push_back( rnode);
				return true;
			}else{
				return false;
			}
		}else{
			rnodes_.push_back( rnode);
			return true;
		}
	}
	if ( index < rnodes_.size()){
		if ( rnodes_[index] != rnode){
			rnodes_[index] = rnode;
			return true;
		}
	}
	return false;
}

bool Ring::isCollided( Ring* ring){
	return false;
}

ResourceID Ring::getInputRNode(ResourceID inputid){
	for ( size_t i =0; i < rnodes_.size();++i){
		if (GetRow(inputid )== GetRow(rnodes_[i]) && GetCol(inputid) == GetCol(rnodes_[i])&& GetInput(inputid)==GetInput(rnodes_[i])){
			return rnodes_[i];
		}
	}
	return 0;
}
ResourceID Ring::getOutputRNode(ResourceID outputid){
	for ( size_t i =0; i < rnodes_.size();++i){
		if (GetRow(outputid )== GetRow(rnodes_[i]) && GetCol(outputid) == GetCol(rnodes_[i])&& GetOutput(outputid)==GetOutput(rnodes_[i])){
			return rnodes_[i];
		}
	}
	return 0;
}

void Ring::activate(bool flag){
	isActivate_ = flag;
}
//=======================================================RingMgr===============================================================
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
		}
	}
	return NULL;
}
Ring* RingMgr::getRing(const std::string & id){
	for( auto i = rings_.begin() ; i < rings_.end(); ++i){
		if ( (*i)->id_ == id){
			return *i;
		}
	}
	return NULL;
}

std::vector<Ring* > RingMgr::getInputCorrespondRing( ResourceID inputid){
	std::vector<Ring* > rings;
	for ( size_t i =0; i < rings_.size();++i){
		ResourceID rnode = rings_[i]->getInputRNode(inputid);
		if ( rnode){
			rings.push_back( rings_[i]);
		}
	}
	return rings;
}

std::vector<Ring* > RingMgr::getOutputCorrespondRing( ResourceID outputid){
	std::vector<Ring* > rings;
	for ( size_t i =0; i < rings_.size();++i){
		ResourceID rnode = rings_[i]->getOutputRNode(outputid);
		if ( rnode){
			rings.push_back( rings_[i]);
		}
	}
	return rings;
}

std::vector<Ring* > RingMgr::getInputCorrespondActivatedRing( ResourceID inputid){
	std::vector<Ring* > rings;
	for ( size_t i =0; i < rings_.size();++i){
		if ( rings_[i]->isActivate_){
			ResourceID rnode = rings_[i]->getInputRNode(inputid);
			if ( rnode){
				rings.push_back( rings_[i]);
			}
		}
	}
	return rings;
}

std::vector<Ring* > RingMgr::getOutputCorrespondActivatedRing( ResourceID outputid){
	std::vector<Ring* > rings;
	for ( size_t i =0; i < rings_.size();++i){
		if ( rings_[i]->isActivate_){
			ResourceID rnode = rings_[i]->getOutputRNode(outputid);
			if ( rnode){
				rings.push_back( rings_[i]);
			}
		}
	}
	return rings;
}