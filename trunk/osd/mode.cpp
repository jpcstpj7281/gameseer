#include "Mode.h"
#include<QtDebug>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"

Mode::Mode(const std::string & id):id_(id)
{
}
Mode::~Mode(){
}

ModeMgr* ModeMgr::inst = 0;
ModeMgr *ModeMgr::instance(){
	if ( inst) return inst;
	return inst = new ModeMgr();
}
ModeMgr::ModeMgr()
{
}
ModeMgr::~ModeMgr()
{
}
Mode* ModeMgr::createMode(const std::string & id){
	if ( hasMode(id)) return NULL;
	modes_.push_back(new Mode(id));
	return modes_.back();
}
Mode* ModeMgr::createMode(){
	for ( size_t i = 0 ; i < 0xFFFFFFFF; ++i){
		std::string str = "Mode";
		std::string num = QString::number(i+1).toStdString();
		if (!hasMode(str + num)){
			modes_.push_back( new Mode(str+num));
			return modes_.back();
		}
	}
	return NULL;
}
bool ModeMgr::hasMode(const std::string & id){
	return getMode(id) ;
}
Mode* ModeMgr::getMode(const std::string &id){
	for ( size_t i = 0 ; i < modes_.size(); ++i){
		if (modes_[i]->id_ == id) return modes_[i];
	}
	return NULL;
}
bool ModeMgr::removeMode(Mode* mode){
	for ( auto i = modes_.begin() ; i < modes_.end(); ++i){
		if (*i == mode) {
			delete mode;
			modes_.erase(i);
			return true;
		}
	}
	return false; 
}