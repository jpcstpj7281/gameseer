#include "Mode.h"
#include<QtDebug>
#include "boost/foreach.hpp"
#include "boost/bind.hpp"
#include <wnd.h>
#include <ring.h>

#include <windows.h>

Mode::Mode(const std::wstring & id):id_(id)
{
	isActivated_ = false;
}
Mode::~Mode(){
}
void Mode::save(){
	auto wnds = WndMgr::instance()->getAllWnds();
	wnds_.clear();
	wnds_.resize(wnds.size());
	for ( size_t i = 0; i < wnds.size(); ++i){
		wnds_[i].xPercent_ = wnds[i]->xPercent_;
		wnds_[i].yPercent_ = wnds[i]->yPercent_;
		wnds_[i].wPercent_ = wnds[i]->wPercent_;
		wnds_[i].hPercent_ = wnds[i]->hPercent_;
		wnds_[i].axPercent_ = wnds[i]->axPercent_;
		wnds_[i].ayPercent_ = wnds[i]->ayPercent_;
		wnds_[i].awPercent_ = wnds[i]->awPercent_;
		wnds_[i].ahPercent_ = wnds[i]->ahPercent_;
		wnds_[i].inputid_ = wnds[i]->inputid_;
		wnds_[i].ringid_ = (wnds[i]->ring_? wnds[i]->ring_->id_:L"");
		wnds_[i].wndid_ = wnds[i]->id_;
	}
}
bool Mode::activate(){
	bool res = false;
	if ( !isActivated_){
		WndMgr::instance()->closeAll();
		for ( size_t i = 0; i < wnds_.size(); ++i){
			Ring* ring = NULL;
			if(!wnds_[i].ringid_.empty()){
				ring = RingMgr::instance()->getRing(wnds_[i].ringid_);
				if ( ring){
					ring->activate(wnds_[i].inputid_);
					WndMgr::instance()->createWnd(wnds_[i].wndid_, wnds_[i].xPercent_, wnds_[i].yPercent_, wnds_[i].wPercent_, wnds_[i].hPercent_, wnds_[i].inputid_, ring);
					res = true;
				}
			}else{
				WndMgr::instance()->createWnd(wnds_[i].wndid_, wnds_[i].xPercent_, wnds_[i].yPercent_, wnds_[i].wPercent_, wnds_[i].hPercent_, wnds_[i].inputid_, NULL);
				res = true;
			}
		}
	}
	return res;
}
//=================================================================================================================================

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
Mode* ModeMgr::createMode(const std::wstring & id){
	if ( hasMode(id)) return NULL;
	modes_.push_back(new Mode(id));
	return modes_.back();
}
Mode* ModeMgr::createMode(){
	for ( size_t i = 0 ; i < 0xFFFFFFFF; ++i){
		std::wstring str = L"Mode";
		std::wstring num = QString::number(i+1).toStdWString();
		if (!hasMode(str + num)){
			modes_.push_back( new Mode(str+num));
			return modes_.back();
		}
	}
	return NULL;
}
bool ModeMgr::hasMode(const std::wstring & id){
	return getMode(id) ;
}
Mode* ModeMgr::getMode(const std::wstring &id){
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

void ModeMgr::clear(){
	while(modes_.size()){
		delete modes_.back();
		modes_.erase(modes_.end() -1);
	}
}