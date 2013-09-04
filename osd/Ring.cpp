#include "Ring.h"
#include<QtDebug>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"
#include <QMainWindow>
#include "boost/lexical_cast.hpp"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <windows.h>

Ring::Ring(const std::string & id):id_(id),isEnable_(false)
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
			return false;
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

void Ring::activate(ResourceID inputid){
	//isActivate_ = flag;
	for ( size_t i = 0 ; i < rnodes_.size(); ++i){
		Screen* scrn = ScreenMgr::instance()->getScreen( rnodes_[i]);
		scrn->connInOutRingRequest( inputid, rnodes_[i]);
		Sleep(100);
	}
}

bool Ring::isActivate(){
	bool isactivate=true;
	for ( size_t i = 0 ; i < rnodes_.size(); ++i){
		Screen* scrn = ScreenMgr::instance()->getScreen( rnodes_[i]);
		if ( !scrn->hasRnode( rnodes_[i])){
			isactivate = false;
		}
	}
	return isactivate;
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
		if ( rings_[i]->isActivate()){
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
		if ( rings_[i]->isActivate()){
			ResourceID rnode = rings_[i]->getOutputRNode(outputid);
			if ( rnode){
				rings.push_back( rings_[i]);
			}
		}
	}
	return rings;
}

std::string RingMgr::toString(){
	std::stringstream ss;
	for ( auto rit = rings_.begin(); rit != rings_.end() ; ++rit){
		Ring*  ring = *rit;
		ss<<ring->id_<<":";
		for ( auto nit = ring->rnodes_.begin(); nit != ring->rnodes_.end() ; ++nit){
			//saveStr+=boost::lexical_cast<std::string>( *nit);
			ss<<*nit;
			ss<<">";
		}
		ss<<";";
	}
	qDebug()<<QString::fromStdString(ss.str());
	return ss.str();
}
void RingMgr::fromString(const std::string & rings){

	while (rings_.size()){
		this->removeRing( rings_.back());
	}

	std::vector<std::string> vRing;
	boost::split( vRing, rings, boost::is_any_of( ";" ) );
	for( std::vector<std::string>::iterator rit = vRing.begin(); rit != vRing.end(); ++rit ){
		if ( !rit->empty()){
			std::vector<std::string> vID;
			boost::split( vID, *rit, boost::is_any_of( ":" ) );
			if ( vID.size() == 2){
				Ring* ring = createRing(vID[0]);
				std::vector<std::string> vNode;
				boost::split( vNode, vID[1], boost::is_any_of( ">" ) );
				qDebug()<< QString::fromStdString( vID[0]);
				size_t index = 0;
				for( std::vector<std::string>::iterator nit = vNode.begin(); nit != vNode.end(); ++nit ){
					size_t rnode = boost::lexical_cast<size_t>(*nit);
					qDebug()<< rnode;
					ring->makeNode( rnode, index);
				}
			}
		}
	}
}