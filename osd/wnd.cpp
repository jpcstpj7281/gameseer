#include "Wnd.h"
#include<QtDebug>
#include "asio.hpp"
#include "boost/foreach.hpp"
#include "boost/bind.hpp"


#include <protocol/protocol.h>

#include "msgBase.h"

using asio::ip::tcp;

Wnd::Wnd(double xPercent, double yPercent, double wPercent, double hPercent):
xPercent_(xPercent)
,yPercent_(yPercent)
,wPercent_(wPercent)
,hPercent_(hPercent)
{
	x_ = y_ = w_ = h_= ax_ = ay_ = aw_ = ah_ = 0;
}
Wnd::Wnd( uint32_t x, uint32_t y, uint32_t w, uint32_t h):
x_(x)
,y_(y)
,w_(w)
,h_(h){
	ax_ = ay_ = aw_ = ah_ = 0;
}
Wnd::~Wnd(){
}

bool Wnd::resizeWnd(double xPercent, double yPercent, double widthPercent, double heightPercent){
	return false;
}
bool Wnd::moveWnd(double xPercent, double yPercent){
	return false;
}

//=======================================================ScreenMgr===============================================================
WndMgr* WndMgr::inst = 0;
WndMgr *WndMgr::instance(){
	if ( inst) return inst;
	return inst = new WndMgr();
}
WndMgr::WndMgr():currlayer_(0)
{
}
WndMgr::~WndMgr()
{
}
bool WndMgr::hasWnd(const std::string & id){
	return getWnd(id) ;
}
Wnd* WndMgr::getWnd(const std::string &id){
	for ( size_t i = 0 ; i < wnds_.size(); ++i){
		if (wnds_[i]->id_ == id) return wnds_[i];
	}
	return NULL;
}
bool calcScreen(double xPercent, double yPercent, double wPercent, double hPercent, 
	double &xOut, double &yOut, double &wOut, double &hOut, 
	double &leftCut, double &rightCut, double &topCut, double &bottomCut, ResourceID screenid){
		size_t col = ScreenMgr::instance()->getColCount();
		size_t row = ScreenMgr::instance()->getRowCount();
		double screenw= 1.f/col;
		double screenh= 1.f/row;
		double screenx= screenw * (GetCol(screenid)-1);//UI�ϵĴ���X����,����ScreenPlate��Xƫ��
		double screeny= screenh * (GetRow(screenid)-1);//UI�ϵĴ���Y����,����ScreenPlate��Yƫ��
		
		bool isOutOfScreen = false;

		if ( xPercent <screenx ){ 
			if (xPercent + wPercent > screenx ){
				if ( xPercent + wPercent > screenx + screenw){
					wOut = screenw;
				}else{
					wOut =  xPercent + wPercent - screenx ;
				}
				rightCut = xPercent + wPercent - screenx - screenw;//�����Ǹ�
				leftCut =  screenx - xPercent;//һ������
				//���ڵ�X����������,���Դ�0��ʼ;
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
				leftCut = screenx - xPercent; //һ���Ǹ�
				rightCut = xPercent + wPercent - screenx - screenw;//�����Ǹ�
				//���ڵ�X�����ұ�,����X��SCREEX��ƫ��λΪ����Ӵ��ڵ�X
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
				bottomCut= yPercent + hPercent - screeny - screenh;//�����Ǹ�
				topCut= screeny - yPercent;//һ������
				//���ڵ�Y��������ϱ�,���Դ�0��ʼ;
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
				topCut= screeny - yPercent;//һ���Ǹ�
				bottomCut= yPercent + hPercent - screeny - screenh;//�����Ǹ�
				//���ڵ�y�����±�,����y��SCREEY��ƫ��λΪ����Ӵ��ڵ�Y
				yOut = yPercent - screeny;
			}else if(  yPercent >= screeny + screenh){
				isOutOfScreen = true;
				hOut = wOut = 0;
			}
		}
	return isOutOfScreen;
}
Wnd* WndMgr::createWnd( const std::string & id, double xPercent, double yPercent, double widthPercent, double heightPercent, ResourceID inputid, Ring* ring){
	if ( inputid == 0) return NULL;
	
	double xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut;
	if ( ring == NULL){
		calcScreen(xPercent, yPercent, widthPercent, heightPercent, xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut, inputid);
	}else{
		std::vector<ResourceID> rnodes = ring->getRnodes();
		size_t i = 0;
		if (ring->isClosed()){
			i = 1;
		}
		for ( ; i < rnodes.size(); ++i){
			calcScreen(xPercent, yPercent, widthPercent, heightPercent, xOut, yOut, wOut, hOut, leftCut, rightCut, topCut, bottomCut, rnodes[i]);
		}
	}

	wnds_.push_back( new Wnd(xPercent, yPercent, widthPercent, heightPercent));
	wnds_.back()->id_ = id;
	wnds_.back()->layer_ = ++currlayer_;
	return wnds_.back();
}

Wnd* WndMgr::createWnd(double xPercent, double yPercent, double widthPercent, double heightPercent, ResourceID inputid, Ring* ring){
	for ( size_t i = 0 ; i < 0xFFFFFFFF; ++i){
		std::string str = "Wnd";
		std::string num = QString::number(i+1).toStdString();
		if (!hasWnd(str + num)){
			return createWnd( str+num, xPercent, yPercent, widthPercent, heightPercent, inputid, ring);
			break;
		}
	}
	return NULL;
}
bool WndMgr::closeWnd(Wnd* wnd){
	for ( auto i = wnds_.begin() ; i < wnds_.end(); ++i){
		if (*i == wnd) {
			wnds_.erase(i);
			return true;
		}
	}
	return false; 
}