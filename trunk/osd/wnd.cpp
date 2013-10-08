#include "Wnd.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"
#include <boost/math/special_functions/round.hpp>

#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

//return false if there is no pixel insight this screen.
bool calcScreen(double xPercent, double yPercent, double wPercent, double hPercent, 
	double &xOut, double &yOut, double &wOut, double &hOut, 
	double &leftCut, double &rightCut, double &topCut, double &bottomCut, ResourceID screenid){
		size_t col = ScreenMgr::instance()->getColCount();
		size_t row = ScreenMgr::instance()->getRowCount();
		double screenw= 1.f/col;
		double screenh= 1.f/row;
		double screenx= screenw * (GetCol(screenid)-1);//UI上的窗口X坐标,加入ScreenPlate的X偏移
		double screeny= screenh * (GetRow(screenid)-1);//UI上的窗口Y坐标,加入ScreenPlate的Y偏移
		
		bool isOutOfScreen = false;

		if ( xPercent <screenx ){ 
			if (xPercent + wPercent > screenx ){
				if ( xPercent + wPercent > screenx + screenw){
					wOut = screenw;
				}else{
					wOut =  xPercent + wPercent - screenx ;
				}
				rightCut = xPercent + wPercent - screenx - screenw;//可能是负
				leftCut =  screenx - xPercent;//一定是正
				//窗口的X在这个屏左边,所以从0开始;
				xOut = 0;
			}else{
				isOutOfScreen = true;
				xOut = wOut = 0;
			}
		}else{
			if ( xPercent >= screenx && xPercent < screenx + screenw) {
				if ( xPercent + wPercent >= screenx + screenw){
					wOut = screenw + screenx - xPercent;
				}else{
					wOut =  wPercent;
				}
				leftCut = screenx - xPercent; //一定是负
				rightCut = xPercent + wPercent - screenx - screenw;//可能是负
				//窗口的X在屏右边,所以X到SCREEX的偏移位为这个子窗口的X
				xOut = xPercent - screenx;
			}else if ( xPercent >= screenx + screenw){
				isOutOfScreen = true;
				hOut = xOut = 0;
			}
		}

		if ( !isOutOfScreen && yPercent <screeny){
			if (yPercent + hPercent > screeny ){
				if ( yPercent+hPercent > screeny+screenh){
					hOut = screenh;
				}else{
					hOut = yPercent + hPercent - screeny;
				}
				bottomCut= yPercent + hPercent - screeny - screenh;//可能是负
				topCut= screeny - yPercent;//一定是正
				//窗口的Y在这个屏上边,所以从0开始;
				yOut = 0;
			}else{
				isOutOfScreen = true;
				screenh = screenw = 0;
			}
		}else if ( !isOutOfScreen){
			if ( yPercent >= screeny && yPercent < screeny + screenh){
				if ( yPercent+hPercent >= screeny+screenh){
					hOut = screenh +screeny -yPercent;
				}else{
					hOut = hPercent;
				}
				topCut= screeny - yPercent;//一定是负
				bottomCut= yPercent + hPercent - screeny - screenh;//可能是负
				//窗口的y在屏下边,所以y到SCREEY的偏移位为这个子窗口的Y
				yOut = yPercent - screeny;
			}else if(  yPercent >= screeny + screenh){
				isOutOfScreen = true;
				hOut = wOut = 0;
			}
		}
	return !isOutOfScreen;
}
std::vector<Wnode*> createWnodes(double xPercent, double yPercent, double widthPercent, double heightPercent, ResourceID inputid, Ring* ring){
	std::vector<Wnode*> wnodes;
	double xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut;
	if ( ring == NULL || !ring->isActivate()){
		ResourceID wnode = 0;
		if ( (wnode = ScreenMgr::instance()->occupyScreenOut(inputid)) && calcScreen(xPercent, yPercent, widthPercent, heightPercent, xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut, inputid)){
			wnodes.push_back( new Wnode( wnode, xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut));
			wnodes.back()->wnodeid_ = wnode;
		}
	}else{
		std::vector<ResourceID> rnodes = ring->getRnodes();
		std::vector<ResourceID> crossRnodes;
		std::vector<ResourceID> wnodesid;
		if (ring->isClosed()){
			rnodes.erase( rnodes.begin());
		}
		for (size_t i = 0; i < rnodes.size(); ++i){
			if ( calcScreen(xPercent, yPercent, widthPercent, heightPercent, xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut, rnodes[i])){
				//store the rnode that under the window
				crossRnodes.push_back( rnodes[i]);
				//precreate Wnode
				wnodes.push_back( new Wnode(  rnodes[i], xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut));
			}
		}
		//occupy the resources, if all available.
		wnodesid = ScreenMgr::instance()->occupyScreensOut(crossRnodes );
		if ( wnodesid.size() == crossRnodes.size()){
			for (size_t i = 0; i < wnodes.size(); ++i){
				wnodes[i]->wnodeid_ = wnodesid[i];
			}
		}else{
			for (size_t i = 0; i < wnodes.size(); ++i){
				delete wnodes[i];
			}
			wnodes.clear();
		}
	}
	return wnodes;
}

Wnd::Wnd(double xPercent, double yPercent, double wPercent, double hPercent, ResourceID inputid):
xPercent_(xPercent)
,yPercent_(yPercent)
,wPercent_(wPercent)
,hPercent_(hPercent)
,inputid_(inputid)
,currRecordNum_(0)
{
	axPercent_=ayPercent_=0;
	awPercent_= ahPercent_ = 1;
}
Wnd::~Wnd(){
	clearWnodes();
}
void Wnd::clearWnodes(){
	for ( size_t i = 0; i < wnodes_.size(); ++i){
		ScreenMgr::instance()->freeScreenOut(wnodes_[i]->wnodeid_);
		delete wnodes_[i];
	}
	wnodes_.clear();
}

bool Wnd::closeWnodes(){
	for ( size_t i = 0; i < wnodes_.size(); ++i){
		ScreenMgr::instance()->freeScreenOut(wnodes_[i]->wnodeid_);
		delete wnodes_[i];
	}
	wnodes_.clear();
	return true;
}
uint32_t Wnd::bringFront(){ 
	layer_ == WndMgr::instance()->currlayer_ ==layer_? layer_: layer_= ++ WndMgr::instance()->currlayer_;
	for ( size_t i = 0 ; i < wnodes_.size(); ++i){
		Screen* scrn = ScreenMgr::instance()->getScreen( wnodes_[i]->wnodeid_);
		scrn->setLayerRequest( layer_, wnodes_[i]->wnodeid_);
	}
	return layer_;
}

bool Wnd::resetInput(ResourceID inputid){
	inputid_= inputid;
	return resizeWnd(xPercent_,  yPercent_,  wPercent_,  hPercent_);
}
bool Wnd::resizeWnd(double xPercent, double yPercent, double wPercent, double hPercent,double axPercent, double ayPercent, double awPercent, double ahPercent){
	axPercent_  = axPercent;
	ayPercent_  = ayPercent;
	awPercent_  = awPercent;
	ahPercent_  = ahPercent;
	return resizeWnd(xPercent,  yPercent,  wPercent,  hPercent);
}
bool Wnd::hasPre(){ 
    return currRecordNum_>0;
}
bool Wnd::hasNext(){ 
	return currRecordNum_ < wndRecords_.size() - 1;
}
bool Wnd::pre(){ 
	if ( currRecordNum_ <=0){
        return false;
	}
    WndData& wd = wndRecords_[--currRecordNum_];
	inputid_ = wd.inputid_;
	axPercent_  = wd.axPercent_;
	ayPercent_  = wd.ayPercent_;
	awPercent_  = wd.awPercent_;
	ahPercent_  = wd.ahPercent_;
	resizeWnd( wd.xPercent_, wd.yPercent_, wd.wPercent_, wd.hPercent_, false);
    return true;
}
bool Wnd::next(){ 
	if ( currRecordNum_ >= wndRecords_.size() - 1){
        return false;
	}
    WndData& wd = wndRecords_[++currRecordNum_];
	inputid_ = wd.inputid_;
	axPercent_  = wd.axPercent_;
	ayPercent_  = wd.ayPercent_;
	awPercent_  = wd.awPercent_;
	ahPercent_  = wd.ahPercent_;
	resizeWnd( wd.xPercent_, wd.yPercent_, wd.wPercent_, wd.hPercent_, false);
    return true;
}
void Wnd::save(){
	WndData wd;
	wd.inputid_ = inputid_;
	wd.ahPercent_ = ahPercent_;
	wd.awPercent_ = awPercent_;
	wd.axPercent_ = axPercent_;
	wd.ayPercent_ = ayPercent_;
	wd.hPercent_ = hPercent_;
	wd.wPercent_ = wPercent_;
	wd.xPercent_ = xPercent_;
	wd.yPercent_ = yPercent_;

	if ( currRecordNum_ == wndRecords_.size() -1){
		wndRecords_.push_back(wd);
	}else{
        if ( wndRecords_.size() > 1 && currRecordNum_ < wndRecords_.size() -1 )
            wndRecords_.erase( wndRecords_.begin()+currRecordNum_+1, wndRecords_.end());
		wndRecords_.push_back(wd);
	}
	currRecordNum_ = wndRecords_.size() -1;
}
bool Wnd::resizeWnd(double xPercent, double yPercent, double wPercent, double hPercent, bool isSave){
	xPercent_  = xPercent;
	yPercent_  = yPercent;
	wPercent_  = wPercent;
	hPercent_  = hPercent;
	if ( isSave){
        save();
	}
	std::vector<Wnode*> wnodes;
	if ( ring_ == NULL){
		wnodes_.back()->xp_ = xPercent;
		wnodes_.back()->yp_  = yPercent;
		wnodes_.back()->wp_  = wPercent_;
		wnodes_.back()->hp_  = hPercent_;
		for ( size_t i = 0 ; i < wnodes.size(); ++i){
			Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
			scrn->connInOutRequest( inputid_, wnodes_[i]->wnodeid_);
		}
	}else{

		double xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut;
		std::vector<ResourceID> rnodes = ring_->getRnodes();
		std::vector<ResourceID> crossRnodes;
		std::vector<ResourceID> wnodesid;
		if (ring_->isClosed()){
			rnodes.erase( rnodes.begin());
		}
		for (size_t i = 0; i < rnodes.size(); ++i){
			if ( calcScreen(xPercent, yPercent, wPercent, hPercent, xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut, rnodes[i])){
				//precreate Wnode
				wnodes.push_back( new Wnode(  rnodes[i], xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut));
			}
		}


		std::vector<ResourceID> unusedWnodes;//these wnodes should be close.
		for (auto i = wnodes_.begin(); i != wnodes_.end(); ){
			bool isUsed = false;
			for (auto j = wnodes.begin(); j != wnodes.end(); ){
				if ( ( (*i)->wnodeid_ & 0xFFFF ) == ((*j)->wnodeid_ & 0xFFFF )){
					isUsed = true;
					(*i)->xp_ = (*j)->xp_;
					(*i)->yp_ = (*j)->yp_;
					(*i)->wp_ = (*j)->wp_;
					(*i)->hp_ = (*j)->hp_;
					(*i)->leftCut_ = (*j)->leftCut_;
					(*i)->rightCut_ = (*j)->rightCut_;
					(*i)->topCut_ = (*j)->topCut_;
					(*i)->bottomCut_ = (*j)->bottomCut_;
					delete *j;
					j = wnodes.erase(j);
				}else{
					++j;
				}
			}
			if ( !isUsed){
				unusedWnodes.push_back((*i)->wnodeid_);
				i = wnodes_.erase(i);
			}else{
				++i;
			}
		}
		ScreenMgr::instance()->freeScreensOut( unusedWnodes);

		if ( wnodes.size() >0){
			//store the rnode that under the window
			for ( size_t i = 0; i < wnodes.size(); ++i){
				crossRnodes.push_back( wnodes[i]->wnodeid_);
			}
			wnodesid = ScreenMgr::instance()->occupyScreensOut( crossRnodes);
			if ( wnodesid.size() == crossRnodes.size()){
				for (size_t i = 0; i < wnodes.size(); ++i){
					wnodes[i]->wnodeid_ = wnodesid[i];
				}
				wnodes_.insert( wnodes_.end(), wnodes.begin(), wnodes.end());
			}else{
				for (size_t i = 0; i < wnodes.size(); ++i){
					delete wnodes[i];
				}
				wnodes.clear();
				return false;
			}
		}
	}
	this->recalcArea();
	//for ( size_t i = 0 ; i < wnodes_.size(); ++i){
	//	Screen* scrn = ScreenMgr::instance()->getScreen( wnodes_[i]->wnodeid_);
	//	scrn->hideRequest(wnodes_[i]->wnodeid_ );
	//}
	//for ( size_t i = 0 ; i < wnodes.size(); ++i){
	//	Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
	//	scrn->connInOutRequest( inputid_, wnodes_[i]->wnodeid_);
	//}
	//for ( size_t i = 0 ; i < wnodes.size(); ++i){
	//	Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
	//	scrn->connInOutRequest( inputid_, wnodes[i]->wnodeid_);
	//}
	//for ( size_t i = 0 ; i < wnodes.size(); ++i){
	//	Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
	//	scrn->hideRequest(wnodes[i]->wnodeid_ );
	//}

	for ( size_t i = 0 ; i < wnodes_.size(); ++i){
		Screen* scrn = ScreenMgr::instance()->getScreen( wnodes_[i]->wnodeid_);
		scrn->setAreaRequest( wnodes_[i]->axr_, wnodes_[i]->ayr_, wnodes_[i]->awr_, wnodes_[i]->ahr_, wnodes_[i]->wnodeid_, inputid_);
	}
	/*for ( size_t i = 0 ; i < wnodes_.size(); ++i){
	Screen* scrn = ScreenMgr::instance()->getScreen( wnodes_[i]->wnodeid_);
	scrn->setLayerRequest( layer_, wnodes_[i]->wnodeid_);
	}*/
	//bringFront();
	for ( size_t i = 0 ; i < wnodes_.size(); ++i){
		Screen* scrn = ScreenMgr::instance()->getScreen( wnodes_[i]->wnodeid_);
		scrn->setWndRequest( wnodes_[i]->xp_, wnodes_[i]->yp_, wnodes_[i]->wp_, wnodes_[i]->hp_, wnodes_[i]->wnodeid_);
	}
	for ( size_t i = 0 ; i < wnodes_.size(); ++i){
		Screen* scrn = ScreenMgr::instance()->getScreen( wnodes_[i]->wnodeid_);
		scrn->showRequest(wnodes_[i]->wnodeid_ );
	}

	return true;
}
bool Wnd::moveWnd(double xPercent, double yPercent){
	return this->resizeWnd( xPercent, yPercent, wPercent_, hPercent_);
}

Wnode * Wnd::getWnode( ResourceID wnode){
	for ( auto it = wnodes_.begin(); it != wnodes_.end(); ++it){
		if ( (*it)->wnodeid_ == wnode){
			return (*it);
		}
	}
	return NULL;
}
void Wnd::recalcArea(){
	if ( inputid_ == 0) return;
	Resolution res = ScreenMgr::instance()->getInResolution(inputid_);
	size_t width = GetWidth(res);
	size_t height= GetHeight(res);
	//double pw = width/wPercent_;
	//double ph = height/hPercent_;
	size_t rx = boost::math::round(axPercent_*width);
	size_t ry = boost::math::round(ayPercent_*height); 
	size_t rw = boost::math::round(awPercent_*width);
	size_t rh = boost::math::round(ahPercent_*height);
	double rpw = rw / wPercent_;
	double rph = rh / hPercent_;

	for ( size_t i = 0 ; i < wnodes_.size(); ++i){
		if ( wnodes_[i]->leftCut_>0){
			wnodes_[i]->axr_ = rx + boost::math::round( wnodes_[i]->leftCut_ * rpw);
			wnodes_[i]->awr_ = boost::math::round(wnodes_[i]->wp_ * rpw);
		}else{
			wnodes_[i]->axr_ = rx;
			wnodes_[i]->awr_ = boost::math::round(wnodes_[i]->wp_ * rpw);
		}
		if ( wnodes_[i]->topCut_>0){
			wnodes_[i]->ayr_ = ry + boost::math::round( wnodes_[i]->topCut_ * rph);
			wnodes_[i]->ahr_ = boost::math::round(wnodes_[i]->hp_ * rph);
		}else{
			wnodes_[i]->ayr_ = ry;
			wnodes_[i]->ahr_ = boost::math::round(wnodes_[i]->hp_ * rph);
		}
	}
}

//=======================================================ScreenMgr===============================================================
WndMgr* WndMgr::inst = 0;
WndMgr *WndMgr::instance(){
	if ( inst) return inst;
	return inst = new WndMgr();
}
WndMgr::WndMgr():currlayer_(0),isWndMovable_(false)
{
}
WndMgr::~WndMgr()
{
}
bool WndMgr::hasWnd(const std::wstring & id){
	return getWnd(id) ;
}
Wnd* WndMgr::getWnd(const std::wstring &id){
	for ( size_t i = 0 ; i < wnds_.size(); ++i){
		if (wnds_[i]->id_ == id) return wnds_[i];
	}
	return NULL;
}
Wnd* WndMgr::getWnds(ResourceID inputid){
	for ( size_t i = 0 ; i < wnds_.size(); ++i){
		if (wnds_[i]->inputid_ == inputid) return wnds_[i];
	}
	return NULL;
}

Wnd* WndMgr::createWnd( const std::wstring & id, double xPercent, double yPercent, double widthPercent, double heightPercent, ResourceID inputid, Ring* ring){
	if ( inputid == 0) return NULL;

	std::vector<Wnode*> wnodes = createWnodes(xPercent, yPercent, widthPercent, heightPercent, inputid, ring);
	if ( wnodes.size()>0){
		wnds_.push_back( new Wnd(xPercent, yPercent, widthPercent, heightPercent, inputid));
		wnds_.back()->id_ = id;
		wnds_.back()->ring_ = ring;
		wnds_.back()->layer_ = ++currlayer_;
		wnds_.back()->wnodes_ = wnodes;
		wnds_.back()->recalcArea();
		//for ( size_t i = 0 ; i < wnodes.size(); ++i){
		//	Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
		//	scrn->hideRequest(wnodes[i]->wnodeid_ );
		//}
		for ( size_t i = 0 ; i < wnodes.size(); ++i){
			Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
			scrn->connInOutRequest( inputid, wnodes[i]->wnodeid_);
		}
		for ( size_t i = 0 ; i < wnodes.size(); ++i){
			Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
			scrn->hideRequest(wnodes[i]->wnodeid_ );
		}
		for ( size_t i = 0 ; i < wnodes.size(); ++i){
			Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
			scrn->setAreaRequest( wnodes[i]->axr_, wnodes[i]->ayr_, wnodes[i]->awr_, wnodes[i]->ahr_, wnodes[i]->wnodeid_, inputid);
		}
		for ( size_t i = 0 ; i < wnodes.size(); ++i){
			Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
			scrn->setLayerRequest( currlayer_, wnodes[i]->wnodeid_);
		}
		for ( size_t i = 0 ; i < wnodes.size(); ++i){
			Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
			scrn->setWndRequest( wnodes[i]->xp_, wnodes[i]->yp_, wnodes[i]->wp_, wnodes[i]->hp_, wnodes[i]->wnodeid_);
		}
		for ( size_t i = 0 ; i < wnodes.size(); ++i){
			Screen* scrn = ScreenMgr::instance()->getScreen( wnodes[i]->wnodeid_);
			scrn->showRequest(wnodes[i]->wnodeid_ );
		}
        wnds_.back()->save();
		return wnds_.back();
	}else{
		return NULL;
	}
}

Wnd* WndMgr::createWnd(double xPercent, double yPercent, double widthPercent, double heightPercent, ResourceID inputid, Ring* ring){
	for ( size_t i = 0 ; i < 0xFFFFFFFF; ++i){
		std::wstring str = L"Wnd";
		std::wstring num = QString::number(i+1).toStdWString();
		if (!hasWnd(str + num)){
			return createWnd( str+num, xPercent, yPercent, widthPercent, heightPercent, inputid, ring);
		}
	}
	return NULL;
}
bool WndMgr::closeWnd(Wnd* wnd){
	for ( auto i = wnds_.begin() ; i < wnds_.end(); ++i){
		if (*i == wnd) {
			delete wnd;
			wnds_.erase(i);
			return true;
		}
	}
	return false; 
}
void WndMgr::closeAll(){
	while( wnds_.size()){
		delete wnds_.back();
		wnds_.erase( wnds_.end() -1);
	}
}
