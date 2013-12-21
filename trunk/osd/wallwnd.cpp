#include "WallWnd.h"
#include "ui_WallWnd.h"
#include <QtDeclarative/QDeclarativeView>
#include <qdebug.h>
#include <sstream>
#include "QboxNet.h"
#include "screen.h"
#include "boost/foreach.hpp"

#include <Screen.h>
#include <wnd.h>
#include <Ring.h>
#include <QMessageBox>
#include <boost/bind.hpp>
#include <boost/math/special_functions/round.hpp>

void ScreenRectItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	if ( !cc || !rc ) {return;}
	WallScene* scene = (WallScene*)this->scene();
	QRectF r = scene->sceneRect();
	double screenh  = r.height()/rc;
	double screenw  = r.width()/cc;

	painter->setBrush( Qt::black);
	for ( uint32_t i = 0; i < rc; ++i){
		QPointF start, end;
		start.setX( 0);
		start.setY( screenh*i);
		end.setX(r.width());
		end.setY( screenh*i);
		painter->drawLine(start, end);
	}

	for ( uint32_t i = 0; i < cc; ++i){
		QPointF start, end;
		start.setX( screenw*i);
		start.setY( 0);
		end.setX(screenw*i);
		end.setY(r.height() );
		painter->drawLine(start, end);
	}

	std::vector<QRectF> & rects = scene->getGreenRects();
	painter->setBrush( Qt::green);
	painter->setPen(QPen(Qt::black, 1));

	for (size_t i =0; i < rects.size(); ++i){
		painter->drawRect(rects[i]);
	}
}
//=======================================================================================================================================================================
ResizeItem::ResizeItem(Direction dir):
dir_(dir)
	,isResizing_(false)
{
	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape|ItemSendsScenePositionChanges );
	switch(dir_){
		case Direction::LeftUp:
		case Direction::RightBottom:
			setCursor( Qt::SizeFDiagCursor);
			break;
		case Direction::LeftBottom:
		case Direction::RightUp:
			setCursor( Qt::SizeBDiagCursor);
			break;
	}
}

void ResizeItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget){
	static int size = 2;
	QRectF r;
	switch(dir_){
		case Direction::LeftUp:
			r= QRectF(0,0,size,size); break; 
		case Direction::RightBottom:
			r= QRectF(	((QGraphicsRectItem*)parentItem ())->rect().width()-size,((QGraphicsRectItem*)parentItem ())->rect().height()-size,size,size);   break;
		case Direction::LeftBottom:
			r= QRectF(	0,((QGraphicsRectItem*)parentItem ())->rect().height()-size,size,size);   break;
		case Direction::RightUp:
			r= QRectF(	((QGraphicsRectItem*)parentItem ())->rect().width()-size,0,size,size);   break;
	}

	setRect(r);
	painter->setBrush(QBrush(Qt::yellow));
	painter->drawRect(r);  
}
void ResizeItem::mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event ){
	WndRectItem* item= (WndRectItem*)parentItem();
	WallScene* wallscene = (WallScene*)this->scene();
	QRectF itemrect = item->rect();
	itemrect.translate(item->pos());

	QRectF greenRect = wallscene->getBigGreenRect(itemrect);
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	if ( !cc || !rc ) {return ;}

	QRectF r = wallscene->sceneRect();
	double screenh  = (r.height()/rc);
	double screenw  = (r.width()/cc);
	double x = itemrect.x();
	double y = itemrect.y();

	size_t countright = (int)((x+itemrect.width())/screenw);
	size_t countbottom = (int)((y+itemrect.height())/screenh);

	double offsetright = (x+itemrect.width())/screenw - countright;
	double offsetbottom = (y+itemrect.height())/screenh - countbottom;
	QPointF newPos = item->pos();
	QRectF newRect ;
	if (offsetright > 0){
		++countright;
	}else{
		newRect = QRect( newPos.x(), newPos.y(), (countright+1)*screenw-newPos.x(), (countbottom)*screenh-newPos.y());
		if ( greenRect.contains( newRect)){
			++countright;
		}
	}
	if (offsetbottom > 0){
		++countbottom;
	}else{
		newRect = QRect( newPos.x(), newPos.y(), (countright)*screenw-newPos.x(), (countbottom+1)*screenh-newPos.y());
		if ( greenRect.contains( newRect)){
			++countbottom;
		}
	}
	switch ( dir_){
		case Direction::RightBottom:
			newRect.setX(0);
			newRect.setY(0);
			newRect.setWidth(countright*screenw - newPos.x());
			newRect.setHeight(countbottom*screenh - newPos.y());
			break;
	}
	item->bringFront();

	if ( (newPos.x() + newRect.width()) <= (scene()->sceneRect().width()+1) && (newPos.y() + newRect.height()) <= (scene()->sceneRect().height()+1)){
		item->setPos(  newPos  );
		item->setRect(newRect);
		item->wnd_->resizeWnd( newPos.x()/scene()->sceneRect().width(), newPos.y()/scene()->sceneRect().height(), newRect.width()/scene()->sceneRect().width(), newRect.height()/scene()->sceneRect().height());
		item->areaItem_->resetRect();
	}
}
void ResizeItem::resize( QPointF &curr){
	
	WndRectItem* item= (WndRectItem*)parentItem();
	WallScene* wallscene = (WallScene*)this->scene();

	QPointF curPos = curr;
	QPointF leftup =  item->pos();
	QPointF rightbottom =   QPointF( item->pos().x()+item->rect().width(), item->pos().y()+item->rect().height());
	QPointF rightup =   QPointF( item->pos().x()+item->rect().width(), item->pos().y()) ;
	QPointF leftbottom =  QPointF( item->pos().x(), item->pos().y()+item->rect().height()) ;
	QRectF itemrect = item->rect();
	itemrect.translate(item->pos());
	QRectF greenRect = wallscene->getBigGreenRect(itemrect);

	QPointF newPos;
	QRectF newRect;
	QRectF oldRect;
	switch ( dir_){
		//case Direction::LeftUp:
		//	newPos = curPos;
		//	if ( rightbottom.x() - curPos.x() < 50){
		//		newPos.setX(rightbottom.x()-50);
		//	}
		//	else if (  curPos.x() < greenRect.x()){
		//		newPos.setX(greenRect.x());
		//	}
		//	if ( rightbottom.y() - curPos.y() < 50){
		//		newPos.setY(rightbottom.y()-50);
		//	}
		//	else if ( curPos.y() < greenRect.y()){
		//		newPos.setY(greenRect.y());
		//	}

		//	newRect.setWidth(rightbottom.x() -newPos.x());
		//	newRect.setHeight(rightbottom.y() -newPos.y());
		//	
		//	break;
		case Direction::RightBottom:
			newPos= item->pos();
			newRect = QRectF( 0, 0, curPos.x()-leftup.x(), curPos.y()-leftup.y());
			if ( curPos.x() - leftup.x() < 50){
				newRect.setWidth(50);
			}
			else if (  curPos.x()  > greenRect.right()  ){
				newRect.setWidth(greenRect.right() - leftup.x());
			}
			if ( curPos.y() - leftup.y() < 50){
				newRect.setHeight(50);
			}
			else if (  curPos.y()  > greenRect.bottom() ){
				newRect.setHeight(greenRect.bottom() - leftup.y());
			}
			
			break;
		//case Direction::LeftBottom:
		//	newPos = QPointF(curPos.x(), leftup.y());
		//	if ( rightbottom.x() - curPos.x() < 50 ){
		//		newPos.setX(rightbottom.x() - 50);
		//	}else if (curPos.x() < 0 ){
		//		newPos.setX(0);
		//	}

		//	newRect = QRectF( 0, 0, rightbottom.x() - newPos.x(), curPos.y()-newPos.y());
		//	if ( newRect.height() < 50){
		//		newRect.setHeight(50);
		//	}else if (newRect.height()+newPos.y() > scene()->sceneRect().height()){
		//		newRect.setHeight(scene()->sceneRect().height() -newPos.y());
		//	}

		//	item->setPos(newPos);
		//	item->setRect(newRect);
		//	break;
		//case Direction::RightUp:
		//	newPos = QPointF(leftup.x(), curPos.y());
		//	if ( rightbottom.y() - newPos.y() < 50 ){
		//		newPos.setY(rightbottom.y() - 50);
		//	}else if (newPos.y() < 0 ){
		//		newPos.setY(0);
		//	}

		//	newRect = QRectF( 0, 0, curPos.x() - leftup.x(), rightbottom.y()-newPos.y());
		//	if ( newRect.width() < 50){
		//		newRect.setWidth(50);
		//	}else if (newRect.width()+newPos.x()> scene()->sceneRect().width()){
		//		newRect.setWidth(scene()->sceneRect().width() -newPos.x());
		//	}

		//	item->setPos(newPos);
		//	item->setRect(newRect);
		//	break;
	}
	item->setPos(  newPos  );
	item->setRect(newRect);
	item->areaItem_->resetRect();
	item->bringFront();
	//item->wnd_->resizeWnd( newPos.x()/scene()->sceneRect().width(), newPos.y()/scene()->sceneRect().height(), newRect.width()/scene()->sceneRect().width(), newRect.height()/scene()->sceneRect().height());

}
void ResizeItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseMoveEvent(event);
	//WndRectItem* parent = ((WndRectItem*)parentItem());
	if ( WndMgr::instance()->isWndMovable_){
		if ( isResizing_) resize(event->scenePos());
	}
}
void ResizeItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

	QGraphicsRectItem::mousePressEvent(event);
	//WndRectItem* parent = ((WndRectItem*)parentItem());
	if ( WndMgr::instance()->isWndMovable_){
		pressPos_ = event->pos();
		isResizing_ = true;
	}
}
void ResizeItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	
	if ( isResizing_) {
		WndRectItem* parent = ((WndRectItem*)parentItem());
		WallScene* wallscene = (WallScene*)this->scene();
		parent->wnd_->resizeWnd( parent->pos().x()/wallscene->sceneRect().width()
			,parent->pos().y()/wallscene->sceneRect().height()
			,parent->rect().width()/wallscene->sceneRect().width()
			,parent->rect().height()/wallscene->sceneRect().height()
			);
	}
}
//=======================================================================================================================================================================
ExtentItem::ExtentItem(Direction dir){
	isPressed_ = false;
	dir_ = dir;
	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape );
	setCursor( Qt::PointingHandCursor);
}
//QRectF CloseItem::boundingRect() const  {  return ;} 
void ExtentItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	QRectF r;
	switch ( dir_ ){
	case Direction::Top:
		r = QRectF( ((QGraphicsRectItem*)parentItem())->rect().width() - 30, 0, 10, 10);
		break;
	case Direction::Left:
		r = QRectF( 0, ((QGraphicsRectItem*)parentItem())->rect().height() - 30, 10, 10);
		break;
	case Direction::Right:
		
		r = QRectF( ((QGraphicsRectItem*)parentItem())->rect().width() - 10, 30, 10, 10);
		break;
	case Direction::Bottom:
		r = QRectF( 30, ((QGraphicsRectItem*)parentItem())->rect().height() - 10, 10, 10);
		break;
	case Direction::Full:
		r = QRectF( ((QGraphicsRectItem*)parentItem())->rect().width() - 50, 0, 10, 10);
		break;
	case Direction::Pre:
		r = QRectF( ((QGraphicsRectItem*)parentItem())->rect().width() - 90, 0, 10, 10);
		break;
	case Direction::Next:
		r = QRectF( ((QGraphicsRectItem*)parentItem())->rect().width() - 70, 0, 10, 10);
		break;
	}
	setRect(r);
	painter->setBrush(QBrush(Qt::yellow));
	painter->drawRect(r);
	
	
	switch ( dir_ ){
	case Direction::Top:
		painter->drawLine(QPointF(r.x()+r.width()/2, r.y()), QPointF(r.x()+r.width()/2, r.y()+r.height()));
		painter->drawLine(QPointF(r.x()+r.width()/2, r.y()), QPointF(r.x(), r.y()+r.height()/2));
		painter->drawLine(QPointF(r.x()+r.width()/2, r.y()), QPointF(r.x()+r.width(), r.y()+r.height()/2));
		break;
	case Direction::Left:
		painter->drawLine(QPointF(r.x(), r.y()+r.height()/2), QPointF(r.x()+r.width(), r.y()+r.height()/2));
		painter->drawLine(QPointF(r.x(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()));
		painter->drawLine(QPointF(r.x(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()+r.height()));
		break;
	case Direction::Right:
		painter->drawLine(QPointF(r.x(), r.y()+r.height()/2), QPointF(r.x()+r.width(), r.y()+r.height()/2));
		painter->drawLine(QPointF(r.x()+r.width(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()));
		painter->drawLine(QPointF(r.x()+r.width(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()+r.height()));
		break;
	case Direction::Bottom:
		painter->drawLine(QPointF(r.x()+r.width()/2, r.y()), QPointF(r.x()+r.width()/2, r.y()+r.height()));
		painter->drawLine(QPointF(r.x(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()+r.height()));
		painter->drawLine(QPointF(r.x()+r.width(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()+r.height()));
		break;
	case Direction::Full:
		break;
	case Direction::Pre:
		painter->drawLine(QPointF(r.x()+r.width()/2, r.y()+r.height()/2), QPointF(r.x()+r.width(), r.y()));
		painter->drawLine(QPointF(r.x()+r.width()/2, r.y()+r.height()/2), QPointF(r.x()+r.width(), r.y()+r.height()));
		painter->drawLine(QPointF(r.x(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()));
		painter->drawLine(QPointF(r.x(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()+r.height()));
		break;
	case Direction::Next:
		painter->drawLine(QPointF(r.x()+r.width()/2, r.y()+r.height()/2), QPointF(r.x(), r.y()));
		painter->drawLine(QPointF(r.x()+r.width()/2, r.y()+r.height()/2), QPointF(r.x(), r.y()+r.height()));
		painter->drawLine(QPointF(r.x()+r.width(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()));
		painter->drawLine(QPointF(r.x()+r.width(), r.y()+r.height()/2), QPointF(r.x()+r.width()/2, r.y()+r.height()));
		break;
	}

	QGraphicsRectItem::paint(painter, option, widget);
} 
void ExtentItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	isPressed_ = true;
	QGraphicsRectItem::mousePressEvent(event);
}
void ExtentItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	if (isPressed_ && dir_ < Direction::Pre){
		WndRectItem* item= (WndRectItem*)parentItem();
		WallScene* wallscene = (WallScene*)this->scene();
		QRectF itemrect = item->rect();
		itemrect.translate(item->pos());

		QRectF greenRect = wallscene->getBigGreenRect(itemrect);
		uint32_t cc = ScreenMgr::instance()->getColCount();
		uint32_t rc = ScreenMgr::instance()->getRowCount();
		if ( !cc || !rc ) {return ;}

		QRectF r = wallscene->sceneRect();
		double screenh  = (r.height()/rc);
		double screenw  = (r.width()/cc);
		double x = itemrect.x();
		double y = itemrect.y();

		size_t countright = (int)((x+itemrect.width())/screenw);
		size_t countbottom = (int)((y+itemrect.height())/screenh);

		size_t countleft = (int)((x+itemrect.width()-0.5)/screenw);
		size_t counttop = (int)((y+itemrect.height()-0.5)/screenh);
		

		double offsetright = (x+itemrect.width())/screenw - countright;
		double offsetbottom = (y+itemrect.height())/screenh - countbottom;
		QPointF newPos = item->pos();
		QRectF newRect ;
		if (offsetright > 0){
			++countright;
		}else{
			newRect = QRect( newPos.x(), newPos.y(), (countright+1)*screenw-newPos.x(), (countbottom)*screenh-newPos.y());
			if ( greenRect.contains( newRect)){
				++countright;
			}
		}
		if (offsetbottom > 0){
			++countbottom;
		}else{
			newRect = QRect( newPos.x(), newPos.y(), (countright)*screenw-newPos.x(), (countbottom+1)*screenh-newPos.y());
			if ( greenRect.contains( newRect)){
				++countbottom;
			}
		}
		
		double leftx = countleft * screenw;
		if ( leftx >= newPos.x() && leftx > 0){
			--countleft;
		}
		double topy= counttop * screenh;
		if ( topy >= newPos.y() && topy > 0){
			--counttop;
		}
		switch ( dir_){
		case Direction::Top:
			newPos.setY((counttop)*screenh);
			newRect.setX(0);
			newRect.setY(0);
			newRect.setWidth(itemrect.width());
			newRect.setHeight(itemrect.height()+itemrect.y() - (counttop)*screenh);
			break;
		case Direction::Left:
			newPos.setX((countleft)*screenw);
			newRect.setX(0);
			newRect.setY(0);
			newRect.setWidth(itemrect.width()+itemrect.x() - (countleft)*screenw);
			newRect.setHeight(itemrect.height());
			break;
		case Direction::Right:
			newRect.setX(0);
			newRect.setY(0);
			newRect.setWidth(countright*screenw - newPos.x());
			newRect.setHeight(itemrect.height());
			break;
		case Direction::Bottom:
			newRect.setX(0);
			newRect.setY(0);
			newRect.setWidth(itemrect.width());
			newRect.setHeight(countbottom*screenh - newPos.y());
			break;
		case Direction::Full:
			newPos.setY((counttop)*screenh);
			newPos.setX((countleft)*screenw);
			newRect.setX(0);
			newRect.setY(0);
			newRect.setWidth((countright - countleft)*screenw);
			newRect.setHeight((countbottom - counttop)*screenh );
			break;
		}
		item->bringFront();

		if ( greenRect.contains(newPos)){
		
			if ( (newPos.x() + newRect.width()) <= (scene()->sceneRect().width()+1) && (newPos.y() + newRect.height()) <= (scene()->sceneRect().height()+1)){
				item->setPos(  newPos  );
				item->setRect(newRect);
				double x = newPos.x()/scene()->sceneRect().width();
				double y = newPos.y()/scene()->sceneRect().height();
				double w = newRect.width()/scene()->sceneRect().width();
				double h = newRect.height()/scene()->sceneRect().height();
				item->wnd_->resizeWnd( x,y,w,h);
				item->areaItem_->resetRect();
			}
		}
	}
	else if (isPressed_ ){
		WallScene* wallscene = (WallScene*)this->scene();
		WndRectItem* item= (WndRectItem*)parentItem();
		bool ischanged =  false;
		switch ( dir_){
		case Direction::Pre:
			ischanged = item->wnd_->pre();
			break;
		case Direction::Next:
			ischanged = item->wnd_->next();
			break;

		}
		if(ischanged){
			double x = wallscene->width()*item->wnd_->xPercent_;
			double y = wallscene->height()*item->wnd_->yPercent_;
			double w = wallscene->width()*item->wnd_->wPercent_;
			double h =  wallscene->height()*item->wnd_->hPercent_;
			auto found  = std::find(wallscene->wndItems_.begin(), wallscene->wndItems_.end(), item);
            if ( found != wallscene->wndItems_.end()){
                Wnd* wnd = item->wnd_;
                wallscene->removeItem(*found);
                delete *found;
                wallscene->wndItems_.erase(found);
                wallscene->wndItems_.push_back( new WndRectItem(x, y, w, h, wallscene, wnd));
			}
		}
	}
}
//=======================================================================================================================================================================
CloseItem::CloseItem(){
	isPressed_ = false;
	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape );
	setCursor( Qt::PointingHandCursor);
}
//QRectF CloseItem::boundingRect() const  {  return ;} 
void CloseItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  

	QRectF r = QRectF( ((QGraphicsRectItem*)parentItem())->rect().width() - 10, 0, 10, 10);
	setRect(r);
	painter->setBrush(QBrush(Qt::yellow));
	painter->drawRect(r);
	painter->drawLine(QPointF(r.x(), r.y()), QPointF(r.x()+r.width(), r.y()+r.height()));
	painter->drawLine(QPointF(r.x()+r.width(), r.y()), QPointF(r.x(), r.y()+r.height()));

	QGraphicsRectItem::paint(painter, option, widget);
} 
void CloseItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	isPressed_ = true;
	QGraphicsRectItem::mousePressEvent(event);
}
void CloseItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	if (isPressed_){
		WndRectItem* item = (WndRectItem*)parentItem();
		WallScene *scene = ((WallScene*)item->scene());
		scene->removeItem(item);
		scene->wndItems_.erase(std::find( scene->wndItems_.begin(), scene->wndItems_.end(), item));
		WndMgr::instance()->closeWnd( item->wnd_);
		delete item;
	}
}
//=======================================================================================================================================================================
AreaItem::AreaItem(double x, double y, double w, double h){
	isPressed_ = false;
	setFlags(QGraphicsItem::ItemClipsToShape );
	//setCursor( Qt::PointingHandCursor);
	setX( x);
	setY( y);
	this->setRect( QRectF(0, 0, w, h));
	//setAcceptedMouseButtons( Qt::MouseButton::RightButton);
}

void AreaItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	painter->setBrush(QBrush(Qt::cyan));
	painter->drawRect( rect());

	//QRectF r = rect();
	//QRectF textRect_ = QRectF(r.x()+r.width()/5, r.y(), r.width()+r.width()/5*4, r.height());
	painter->drawText(rect(), wndid_, QTextOption(Qt::Alignment::enum_type::AlignTop|Qt::Alignment::enum_type::AlignHCenter));


	QGraphicsRectItem::paint(painter, option, widget);
} 
void AreaItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsRectItem::mousePressEvent(event);
}
void AreaItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
}
void AreaItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	if (WndMgr::instance()->isWndMovable_ && isMoving_){
		QGraphicsRectItem::mouseMoveEvent(event);
	}
}
void AreaItem::resetRect(){
	WndRectItem* parent = (WndRectItem*)this->parentItem();
	QRectF r = parent->rect();
	setX( parent->wnd_->axPercent_ * r.width());
	setY( parent->wnd_->ayPercent_ * r.height());
	setRect( QRectF(0, 0, parent->wnd_->awPercent_ * r.width(),  parent->wnd_->ahPercent_ * r.height()));
}
//=======================================================================================================================================================================
WndRectItem::WndRectItem(double x, double y, double w, double h, WallScene* wallscene, Wnd* wnd){
	setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape|ItemSendsScenePositionChanges );

	areaItem_ = new AreaItem(wnd->axPercent_*w, wnd->ayPercent_*h, wnd->awPercent_*w, wnd->ahPercent_*h);
	areaItem_->setParentItem(this);
	areaItem_->wndid_ = QString::fromStdWString(wnd->id_);

	ResizeItem *item1 = new ResizeItem( ResizeItem::RightBottom);
	CloseItem *item5 = new CloseItem( );

	ExtentItem *itemup = new ExtentItem( ExtentItem::Top);
	ExtentItem *itemleft = new ExtentItem( ExtentItem::Left);
	ExtentItem *itemright = new ExtentItem( ExtentItem::Right);
	ExtentItem *itembottom = new ExtentItem( ExtentItem::Bottom);
	ExtentItem *itemfull = new ExtentItem( ExtentItem::Full);
	ExtentItem *itempre = new ExtentItem( ExtentItem::Pre);
	ExtentItem *itemnext = new ExtentItem( ExtentItem::Next);

	item1->setParentItem(this);
	item5->setParentItem(this);

	itemup->setParentItem(this);
	itemleft->setParentItem(this);
	itemright->setParentItem(this);
	itembottom->setParentItem(this);
	itemfull->setParentItem(this);
	itempre->setParentItem(this);
	itemnext->setParentItem(this);
	//setCursor( Qt::CrossCursor);

	isMoving_ = false;
	isScaling_=false;
	wallscene->addItem( this);
	setX(x);
	setY(y);
	setRect( QRectF(0, 0, w, h));
	wnd_ = wnd;
	setZValue( wnd_->getLayer());
	setAcceptedMouseButtons( Qt::MouseButton::RightButton|Qt::MouseButton::LeftButton);
}

WndRectItem::~WndRectItem(){
}
void WndRectItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	painter->setBrush(QBrush(Qt::red));
	QRectF r= rect();
	painter->drawRect(r);  
	painter->drawText(r, QString::fromStdWString(wnd_->id_), QTextOption(Qt::Alignment::enum_type::AlignTop|Qt::Alignment::enum_type::AlignHCenter));
	QGraphicsRectItem::paint(painter, option, widget);
}  
void WndRectItem::bringFront(){
	setZValue(wnd_->bringFront());
}

void WndRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	if (WndMgr::instance()->isWndMovable_ && event->button() == Qt::MouseButton::LeftButton){
		isMoving_ = true;
		QGraphicsRectItem::mousePressEvent(event);
		
		//bringFront();
		setCursor( Qt::ClosedHandCursor);
	}

	//if (event->button() == Qt::MouseButton::RightButton){
	//	pressPos_ =  event->pos();
	//	isScaling_ = true;
	//	setCursor( Qt::ArrowCursor);
	//}
}
void	WndRectItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	//setCursor( Qt::OpenHandCursor);
	if (WndMgr::instance()->isWndMovable_ && isMoving_ && !isScaling_){
		WallScene* wallscene = (WallScene*)this->scene();
		isMoving_ = false;
		setZValue( wnd_->layer_);
		wnd_->moveWnd(pos().x()/wallscene->width(), pos().y()/wallscene->height());
	}
	else if (isScaling_){
		isScaling_=false;

		QPointF releasePos = event->pos();
		double width, height;

		QPointF postemp;
		if (releasePos.x() > pressPos_.x() && releasePos.y() > pressPos_.y()){
			width = releasePos.x() - pressPos_.x();
			height = releasePos.y()-pressPos_.y();
			postemp = pressPos_;
		}else if (releasePos.x() < pressPos_.x() && releasePos.y() < pressPos_.y()){
			width = -releasePos.x() + pressPos_.x();
			height = -releasePos.y()+pressPos_.y();
			postemp = releasePos;
		}else if (releasePos.x() > pressPos_.x() && releasePos.y() < pressPos_.y()){
			width = releasePos.x() - pressPos_.x();
			height = -releasePos.y()+pressPos_.y();
			postemp = QPointF( pressPos_.x(), releasePos.y());
		}else if (releasePos.x() < pressPos_.x() && releasePos.y() > pressPos_.y()){
			width = -releasePos.x() + pressPos_.x();
			height = releasePos.y()-pressPos_.y();
			postemp = QPointF( releasePos.x(),  pressPos_.y());
		}
		QRectF r= rect();
		if ( postemp.x() < 0){
			width + postemp.x();
			postemp.setX(0);
		}
		if ( postemp.y() < 0){
			height + postemp.y();
			postemp.setY(0);
		}
		if ( width + postemp.x() > r.width()){
			width = r.width() - postemp.x();
		}
		if ( height + postemp.y() > r.height()){
			height = r.height() - postemp.y();
		}
		double wp = width / r.width();
		double hp = height / r.height();
		if (wp >0.1 && hp > 0.1){ 
			areaItem_->setX( postemp.x());
			areaItem_->setY( postemp.y());
			areaItem_->setRect( QRectF(0, 0, width, height));
			wnd_->axPercent_ = postemp.x() / r.width();
			wnd_->ayPercent_ = postemp.y() / r.height();
			wnd_->awPercent_ = wp;
			wnd_->ahPercent_ = hp;
			WallScene* wallscene = (WallScene*)this->scene();
			wnd_->moveWnd(pos().x()/wallscene->width(), pos().y()/wallscene->height());
		}
		setCursor( Qt::CursorShape::OpenHandCursor);

	}
}
void	WndRectItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	if (WndMgr::instance()->isWndMovable_){
		if ( isMoving_) {
			QGraphicsRectItem::mouseMoveEvent(event);
		}
	}
}
QVariant WndRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{

	if(scene() && (change == ItemPositionChange || change ==ItemMatrixChange ) )
	{
		WallScene* wallscene = (WallScene*)this->scene();
		QPointF newPos = value.toPointF();

		if ( rect().width() == 0 || rect().height() == 0 )return QGraphicsRectItem::itemChange(change, newPos);
		QRectF thisrect = QRectF(pos().x(), pos().y(),rect().width(), rect().height());
		QRectF bigRect = wallscene->getBigGreenRect(thisrect);
		bigRect.setRight(bigRect.right() - rect().right());
		bigRect.setBottom(bigRect.bottom() - rect().bottom());
		if(!bigRect.contains(newPos)){
			newPos.setX(qMin(bigRect.right(), qMax(newPos.x(), bigRect.left())));
			newPos.setY(qMin(bigRect.bottom(), qMax(newPos.y(), bigRect.top())));
			//return newPos;
			return QGraphicsRectItem::itemChange(change, newPos);
		}

	}

	return QGraphicsRectItem::itemChange(change, value);
}

//=======================================================================================================================================================================
WallScene::WallScene(){
	isCreatingWnd_ = false;
	currInput_ = 0;
}
void WallScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	if ( event->button() != Qt::MouseButton::RightButton) {
		pressPos_ = event->scenePos();
		QList<QGraphicsItem *>  list;
		if ( WndMgr::instance()->isWndMovable_){
			list = items( pressPos_, Qt::ItemSelectionMode::IntersectsItemShape, Qt::SortOrder::AscendingOrder);
		}
		if ( currInput_ == 0){
			QMessageBox::warning(0, "Wanning", "There is no input signal has been selected!");
			return;
		}

		if ( !WndMgr::instance()->isWndMovable_ ){//Into create wnd mode
			isCreatingWnd_ = true;
		}
		if (list.size() == 0){
			isCreatingWnd_ = true;
		}
	}
	QGraphicsScene::mousePressEvent(event);
}
void WallScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsScene::mouseMoveEvent(event);
}

void WallScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	if ( isCreatingWnd_){
		createWnd(event->scenePos());
		isCreatingWnd_ = false;
	}
	QGraphicsScene::mouseReleaseEvent(event);
	wallWnd_->refreshWndArgs();
}

void WallScene::createWnd( QPointF & releasePos){
	size_t height = 50, width = 50;
	QPointF pos;
	if (releasePos.x() > pressPos_.x() && releasePos.y() > pressPos_.y()){
		width = releasePos.x() - pressPos_.x();
		height = releasePos.y()-pressPos_.y();
		pos = pressPos_;
	}else if (releasePos.x() >= 0 && releasePos.y() >= 0 && releasePos.x() < pressPos_.x() && releasePos.y() < pressPos_.y()){
		width = -releasePos.x() + pressPos_.x();
		height = -releasePos.y()+pressPos_.y();
		pos = releasePos;
	}else if (releasePos.x() >= 0 && releasePos.y() >= 0 && releasePos.x() > pressPos_.x() && releasePos.y() < pressPos_.y()){
		width = releasePos.x() - pressPos_.x();
		height = -releasePos.y()+pressPos_.y();
		pos = QPointF( pressPos_.x(), releasePos.y());
	}else if (releasePos.x() >= 0 && releasePos.y() >= 0 && releasePos.x() < pressPos_.x() && releasePos.y() > pressPos_.y()){
		width = -releasePos.x() + pressPos_.x();
		height = releasePos.y()-pressPos_.y();
		pos = QPointF( releasePos.x(),  pressPos_.y());
	}
	if ( width > 50 && height > 50){
		//if ( currRing_== NULL ){
		//	QMessageBox::warning(0, "Wanning", "There is no Ring has been selected!");
		//	return;
		//}
		//if ( currRing_->isActivate_){
		//	QMessageBox::warning(0, "Wanning", "The Ring is not yet been activated!");
		//	return;
		//}
		createWndInGreenRect(QRectF(pos.x(), pos.y(), width, height));
	}
}
QRectF WallScene::getBigGreenRect( QRectF rect){
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	if ( !cc || !rc ) {return this->sceneRect();}

	QRectF r = this->sceneRect();
	double screenh  = (r.height()/rc);
	double screenw  = (r.width()/cc);
	double x = rect.x();
	double y = rect.y();

	//当前窗所在屏的位置
	size_t countleft = (int)(x/screenw);
	size_t counttop = (int)(y/screenh);
	size_t countright = (int)((x+rect.width())/screenw);
	size_t countbottom = (int)((y+rect.height())/screenh);

	double offsetleft = (x/screenw) - countleft;
	double offsettop = (y/screenh) - counttop;
	double offsetright = (x+rect.width())/screenw - countright;
	double offsetbottom = (y+rect.height())/screenh - countbottom;

	QPointF rightbottom( (countright+1)*screenw,  (countbottom+1)*screenh);
	QPointF lefttop ( countleft*screenw, counttop*screenh);



	std::vector<QRectF> rects = getGreenRects();
	double growingWidth = screenw;
	double growingHeight = screenh;
	for ( size_t i = 0 ; i < rects.size(); ++i){
		if (lefttop.x()> rects[i].x()){
			lefttop.setX(rects[i].x());
			growingWidth = rects[i].x()+screenw;
		}
		if (lefttop.y()> rects[i].y()){
			lefttop.setY(rects[i].y());
			growingHeight = rects[i].y()+screenh;
		}
	}
	//qDebug()<<"rects.size: "<<rects.size();

	QRectF growingRect(lefttop.x(), lefttop.y(), growingWidth, growingHeight);
	//qDebug()<<"growing rect: "<<growingRect << "x: "<<lefttop.x()<<" y: "<<lefttop.y()<<" w: "<<screenw<<" h: "<<screenh;

	size_t colCount = boost::math::round((double)(rightbottom.x() - (double)lefttop.x()) / screenw);
	size_t rowCount = boost::math::round((double)(rightbottom.y() - (double)lefttop.y()) / screenh);
	size_t rectCount = colCount*rowCount;

	size_t ic= 1;
	size_t ir= 1;
	for ( ; ic <= colCount; ++ic){
		int count = 0;
		growingRect.setWidth( screenw * ic);
		growingRect.setHeight( screenh * ir);
		for ( size_t ig= 0;  ig<rects.size();++ig){
			if ( growingRect.contains(rects[ig])){
				++count;
			}
		}
		if ( count != ir*ic){
			--ic;
			break;;
		}else if (ic == colCount){
			break;
		}
	}
	for ( ; ir <= rowCount; ++ir){
		int count = 0;
		growingRect.setWidth( screenw * ic);
		growingRect.setHeight( screenh * ir);
		for ( size_t ig= 0;  ig<rects.size();++ig){
			if ( growingRect.contains(rects[ig])){
				++count;
			}
		}
		if ( count != ir*ic){
			--ir;
			break;
		}else if (ir == rowCount){
			break;
		}
	}
	//qDebug()<<"ic: "<<ic << " ir: "<<ir;
	growingRect.setWidth( screenw * ic);
	growingRect.setHeight( screenh * ir);
	//qDebug()<<rect;
	//qDebug()<<growingRect;
	return growingRect;// a big rect that can contains the win rect which organized by screen rects.
}

bool WallScene::isInGreenRect( QRectF &rect){
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	if ( !cc || !rc ) {return false;}

	QRectF r = this->sceneRect();
	double screenh  = r.height()/rc;
	double screenw  = r.width()/cc;

	size_t countleft = (int)(rect.x()/screenw);
	size_t counttop = (int)(rect.y()/screenh);
	size_t countright = (int)((rect.x()+rect.width())/screenw);
	size_t countbottom = (int)((rect.y()+rect.height())/screenh);

	double offsetleft = (rect.x()/screenw) - countleft;
	double offsettop = (rect.y()/screenh) - counttop;
	double offsetright = (rect.x()+rect.width()) - countright;
	double offsetbottom = (rect.y()+rect.height()) - countbottom;

	QPointF rightbottom( offsetright>0 ? (countright+1)*screenw:countright*screenw , offsetbottom>0 ? (countbottom+1)*screenh:countbottom*screenh);
	QPointF lefttop ( countleft*screenw, counttop*screenh);
	QRectF bigRect( lefttop, rightbottom);// a big rect that can contains the win rect which organized by screen rects.
	size_t colCount = (size_t)((rightbottom.x() - lefttop.x()) / screenw);
	size_t rowCount = (size_t)((rightbottom.y() - lefttop.y()) / screenh);
	size_t rectCount = colCount*rowCount;

	std::vector<QRectF> rects = getGreenRects();
	std::vector<QRectF> inRects ;
	for ( size_t i = 0; i <rects.size();++i){//calculate how many screen rect insight the bigRect.
		if (bigRect.contains( rects[i])){
			inRects.push_back( rects[i]);
		}
	}
	if ( inRects.size() < rectCount){
		//not enough screen to create this window! logically should be the same.
		return false;
	}
	return true;
}
void WallScene::createWndInGreenRect( QRectF &rect){
	if (isInGreenRect(rect)){
		Ring* ring = NULL;
		if ( !this->currRingid_.isEmpty()){
			ring = RingMgr::instance()->getRing(currRingid_.toStdWString());
		}
		Wnd * wnd = WndMgr::instance()->createWnd(rect.x()/sceneRect().width(), rect.y()/sceneRect().height(),rect.width()/sceneRect().width(), rect.height()/sceneRect().height(), this->currInput_, ring );
		if (wnd){
			wndItems_.push_back(new WndRectItem(rect.x(), rect.y(),rect.width(), rect.height(), this, wnd));
		}
	}
}
std::vector<QRectF> WallScene::getGreenRects(){
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();
	std::vector<QRectF> rects;
	if ( !cc || !rc ) {return rects;}

	QRectF r = this->sceneRect();
	double screenh  = r.height()/rc;
	double screenw  = r.width()/cc;
	QRectF screenRect = QRectF( 0, 0, screenw, screenh);

	Ring* ring = RingMgr::instance()->getRing(this->currRingid_.toStdWString());
	if (ring && ring->isActivate()){ //draw rect for each rnode in activated ring
		std::vector<ResourceID> nodes = ring->getRnodes();
		size_t i = 0;
		if (nodes.size() >2  && GetRow(nodes.front()) == GetRow(nodes.back()) && GetCol(nodes.front()) == GetCol(nodes.back())){
			i = 1;
		}
		for ( ; i < nodes.size(); ++i){
			uint32_t row = GetRow(nodes[i]);
			uint32_t col = GetCol(nodes[i]);
			rects.push_back(QRectF((col -1) *screenw, (row -1) *screenh, screenw, screenh));

		}
	}else if (currInput_){//draw rect for chn
		uint32_t row = GetRow(currInput_);
		uint32_t col = GetCol(currInput_);
		rects.push_back(QRectF ((col -1) *screenw, (row -1) *screenh, screenRect.width(), screenRect.height()));
	}
	return rects;
}

//=======================================================================================================================================================================
WallWnd::WallWnd(QWidget* parent) :
QWidget(parent)
	,ui(new Ui::WallWnd)
	,isResetting_(false)
{
	ui->setupUi(this);

	gv_ = findChild<QGraphicsView* >("wallView");

	scene_ = new WallScene; 
	scene_->wallWnd_ = this;
	scene_->setItemIndexMethod(QGraphicsScene::NoIndex);  

	screensItem_ = new ScreenRectItem;
	scene_->addItem(screensItem_);

	connect(scene_, SIGNAL(changed(const QList<QRectF>&)), this, SLOT(changed(const QList<QRectF> &)));

	gv_->setScene(scene_);
	gv_->setRenderHint(QPainter::Antialiasing);  
	gv_->setCacheMode(QGraphicsView::CacheBackground);  
	gv_->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  
	gv_->setDragMode(QGraphicsView::RubberBandDrag);  

	gv_->setBackgroundBrush(QBrush(Qt::lightGray));
	gv_->setInteractive(true);
	gv_->show();  

	cbRings_ = findChild<QComboBox* >("cbRing");
	cbChns_ = findChild<QComboBox* >("cbChn");
	cbWnds_ = findChild<QComboBox* >("cbWnd");
	connect(cbWnds_, SIGNAL(activated(const QString &)), this, SLOT(currentWndIndexChanged (const QString &)) );
	connect(cbChns_, SIGNAL(activated(const QString &)), this, SLOT(currentChnIndexChanged (const QString &)) );
	connect(cbRings_, SIGNAL(activated(const QString &)), this, SLOT(currentRingIndexChanged (const QString &)) );

	connect(parent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged (int)) );

	QPushButton* pbClose = findChild<QPushButton* >("pbCloseWnd");
	if (pbClose){
		connect(pbClose, SIGNAL(clicked()), this, SLOT(clickedCloseWnd()) );
	}
	QPushButton* pbActivateRing = findChild<QPushButton* >("pbActivateRing");
	if (pbActivateRing){
		connect(pbActivateRing, SIGNAL(clicked()), this, SLOT(clickedActivateRing()) );
	}

	QPushButton* pbResetWnd = findChild<QPushButton* >("pbResetWnd");
	if (pbResetWnd){
		connect(pbResetWnd, SIGNAL(clicked()), this, SLOT(clickedResetWnd()) );
	}

	QCheckBox *cb = findChild<QCheckBox*>("cbDragWnd");
	if (cb){
		connect(cb, SIGNAL(clicked(bool)), this, SLOT(clicked(bool)) );
	}

	ScreenMgr::instance()->onInputChanged( boost::bind( &WallWnd::inChangedCallback, this, _1) );

	QLineEdit* pbAX = findChild<QLineEdit* >("ax");
	QLineEdit* pbAY = findChild<QLineEdit* >("ay");
	QLineEdit* pbAW = findChild<QLineEdit* >("aw");
	QLineEdit* pbAH = findChild<QLineEdit* >("ah");
	pbAX->hide();
	pbAY->hide();
	pbAW->hide();
	pbAH->hide();
}

void WallWnd::clicked ( bool checked ){
	WndMgr::instance()->isWndMovable_ = checked;
	if (checked){
		for ( auto i = scene_->wndItems_.begin() ; i < scene_->wndItems_.end(); ++i){
			(*i)->setCursor( Qt::OpenHandCursor);
		}
	}else{
		for ( auto i = scene_->wndItems_.begin() ; i < scene_->wndItems_.end(); ++i){
			(*i)->setCursor( Qt::ArrowCursor);
		}
	}

}

void WallWnd::changed ( const QList<QRectF> & region ){
	resetComboBoxes();
	//if ( cbWnds_ && !cbWnds_->currentText().isEmpty()){
	//	refreshWndArgs(WndMgr::instance()->getWnd(cbWnds_->currentText().toStdString()));
	//}else{
	//	refreshWndArgs(NULL);
	//}

	//qDebug()<<"testttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt";
}
void WallWnd::clickedResetWnd(){

	QString wndstr = cbWnds_->currentText();
	if ( !wndstr.isEmpty()){
		QLineEdit* lex = findChild<QLineEdit* >("x");
		QLineEdit* ley = findChild<QLineEdit* >("y");
		QLineEdit* lew = findChild<QLineEdit* >("w");
		QLineEdit* leh = findChild<QLineEdit* >("h");
		QLineEdit* leax = findChild<QLineEdit* >("ax");
		QLineEdit* leay = findChild<QLineEdit* >("ay");
		QLineEdit* leaw = findChild<QLineEdit* >("aw");
		QLineEdit* leah = findChild<QLineEdit* >("ah");
		double x = lex->text().toLong();
		double y = ley->text().toLong();
		double w = lew->text().toLong();
		double h = leh->text().toLong();
		double ax = leax->text().toLong();
		double ay = leay->text().toLong();
		double aw = leaw->text().toLong();
		double ah = leah->text().toLong();
		Wnd* wnd = WndMgr::instance()->getWnd(wndstr.toStdWString() );
		wnd->resizeWnd(x/ScreenMgr::instance()->getWallWidth(), 
			y/ScreenMgr::instance()->getWallHeight(), 
			w/ScreenMgr::instance()->getWallWidth(), 
			h/ScreenMgr::instance()->getWallHeight(),
			ax/GetWidth(ScreenMgr::instance()->getInResolution(scene_->currInput_)), 
			ay/GetHeight(ScreenMgr::instance()->getInResolution(scene_->currInput_)), 
			aw/GetWidth(ScreenMgr::instance()->getInResolution(scene_->currInput_)), 
			ah/GetHeight(ScreenMgr::instance()->getInResolution(scene_->currInput_))
			);
		resetWnds();
	}
}
void WallWnd::clickedCloseWnd(){
	int index = cbWnds_->currentIndex();
	std::vector<Wnd*> wnds = WndMgr::instance()->getWnds();
	if ( index >= 0 && wnds.size()){
		for ( auto i = scene_->wndItems_.begin() ; i < scene_->wndItems_.end(); ){
			if ( wnds[index] == (*i)->wnd_){
				WndMgr::instance()->closeWnd((*i)->wnd_);
				(*i)->wnd_ = NULL;
				scene_->removeItem(*i);
				delete *i;
				i = scene_->wndItems_.erase(i);
			}else ++i;
		}
	}
}
void WallWnd::clickedActivateRing(){
	if ( !scene_->currRingid_.isEmpty() ){
		QPushButton* pb = (QPushButton*) sender();

		Ring * ring = RingMgr::instance()->getRing(scene_->currRingid_.toStdWString());
		//if ( !ring->isActivate()){
		//	pb->setStyleSheet("{color:red；background:yellow}");
		ring->activate(scene_->currInput_);
		//}
		screensItem_->update();
	}
}

WallWnd::~WallWnd(){
	delete ui;
}
void WallWnd::resetWnds(){
	std::vector<Wnd*> wnds = WndMgr::instance()->getWnds();
	screensItem_->update();
	for ( size_t i = 0 ; i < scene_->wndItems_.size(); ++i){
		scene_->removeItem(scene_->wndItems_[i]);
		delete scene_->wndItems_[i];
	}
	scene_->wndItems_.clear();
	for ( size_t i = 0; i < wnds.size();++i){
		double x = scene_->width()*wnds[i]->xPercent_;
		double y = scene_->height()*wnds[i]->yPercent_;
		double w = scene_->width()*wnds[i]->wPercent_;
		double h =  scene_->height()*wnds[i]->hPercent_;
		scene_->wndItems_.push_back( new WndRectItem(x, y, w, h, scene_, wnds[i]));
	}
}
void WallWnd::resetComboBoxes(){
	cbWnds_->setEnabled(false);
	cbRings_->setEnabled(false);
	cbChns_->setEnabled(false);

	std::vector<Ring*> rings = RingMgr::instance()->getRings();
	cbRings_->clear();
	cbRings_->addItem("");
	for ( size_t i = 0; i < rings.size();++i){
		if ( rings[i]->size() >=2){
			cbRings_->addItem( QString::fromStdWString(rings[i]->id_));
			if ( scene_->currRingid_.toStdWString() == rings[i]->id_){//only the one currently referred, set to current index.
				cbRings_->setCurrentIndex( cbRings_->count()-1);
			}
		}
	}
	//the the top to be current
	//if ( scene_->currRingid_.isEmpty() && cbRings_->count() )scene_->currRingid_ = cbRings_->currentText();

	std::vector<Wnd*> wnds = WndMgr::instance()->getWnds();
	cbWnds_->clear();
	for ( size_t i = 0; i < wnds.size();++i){
		cbWnds_->addItem( QString::fromStdWString(wnds[i]->id_));//add all wnd to combox
		if ( WndMgr::instance()->getCurrLayer() == wnds[i]->getLayer()){//only the one currently referred, set to current index.
			cbWnds_->setCurrentIndex( cbWnds_->count()-1);
			refreshWndArgs(wnds[i]);
		}
	}


	cbChns_->clear();
	inputs_ = ScreenMgr::instance()->getAvailableInput();
	for ( auto i = inputs_.begin(); i != inputs_.end();){
		if ( GetInput(*i) >=5){
			i = inputs_.erase(i);
		}else{
			++i;
		}
	}
	for ( size_t i = 0; i < inputs_.size();++i){
		std::vector<Ring*> rs = RingMgr::instance()->getInputCorrespondActivatedRing(inputs_[i]);
		if ( rs.size()==0){
			cbChns_->addItem( QString::fromStdString(ToStrID(inputs_[i])));
			if ( scene_->currInput_ == inputs_[i]){//only the one currently referred, set to current index.
				cbChns_->setCurrentIndex( cbChns_->count()-1);
			}
		}
	}
	//the the top to be current
	if ( inputs_.size() >0 && scene_->currInput_==0 )scene_->currInput_ = inputs_.front();
	cbWnds_->setEnabled(true);
	cbRings_->setEnabled(true);
	cbChns_->setEnabled(true);
}
void WallWnd::currentTabChanged ( int index ){
	QTabWidget* tab = (QTabWidget*)sender();
	if (tab->tabText(index) == tr("Wall")){
		resetComboBoxes();
		resetWnds();
	}
}

void WallWnd::drawScreens(){
	uint32_t col = ScreenMgr::instance()->getColCount();
	uint32_t row = ScreenMgr::instance()->getRowCount();
}

void WallWnd::currentChnIndexChanged ( const QString & text ){
	for ( size_t i = 0; i < inputs_.size();++i){
		if ( ToStrID(inputs_[i]) == text.toStdString()){
			scene_->currInput_ = inputs_[i];
			screensItem_->update();
			break;
		}
	}
}
void WallWnd::currentRingIndexChanged ( const QString & text ){
	scene_->currRingid_ = text;
	screensItem_->update();
}
void WallWnd::currentWndIndexChanged ( const QString & text ){
	Wnd * wnd = WndMgr::instance()->getWnd(text.toStdWString());
	wnd->bringFront();

	for ( size_t i = 0 ; i < scene_->wndItems_.size(); ++i){
		if (scene_->wndItems_[i]->wnd_ == wnd){
			scene_->wndItems_[i]->setZValue(wnd->getLayer());
			break;
		}
	}
}
void WallWnd::refreshWndArgs(){
	refreshWndArgs(WndMgr::instance()->getWnd(cbWnds_->currentText().toStdWString()));
}
void WallWnd::refreshWndArgs(Wnd* wnd){
	QLineEdit* lex = findChild<QLineEdit* >("x");
	QLineEdit* ley = findChild<QLineEdit* >("y");
	QLineEdit* lew = findChild<QLineEdit* >("w");
	QLineEdit* leh = findChild<QLineEdit* >("h");
	QLineEdit* leax = findChild<QLineEdit* >("ax");
	QLineEdit* leay = findChild<QLineEdit* >("ay");
	QLineEdit* leaw = findChild<QLineEdit* >("aw");
	QLineEdit* leah = findChild<QLineEdit* >("ah");
	if ( wnd){

		lex->setText(QString::number(wnd->getX()));
		ley->setText(QString::number(wnd->getY()));
		lew->setText(QString::number(wnd->getW()));
		leh->setText(QString::number(wnd->getH()));
		leax->setText(QString::number(wnd->getAX()));
		leay->setText(QString::number(wnd->getAY()));
		leaw->setText(QString::number(wnd->getAW()));
		leah->setText(QString::number(wnd->getAH()));
	}else{
		lex->setText("");
		ley->setText("");
		lew->setText("");
		leh->setText("");
		leax->setText("");
		leay->setText("");
		leaw->setText("");
		leah->setText("");
	}
}
bool WallWnd::inChangedCallback(ResourceID inputid){
	resetComboBoxes();
	if ( cbChns_->currentText().isEmpty()){
		scene_->currInput_ = 0;
	}
	Wnd* wnd = WndMgr::instance()->getWnds(inputid);
	while ( wnd){
		WndMgr::instance()->closeWnd(wnd);
		wnd = WndMgr::instance()->getWnds(inputid);
	}

	screensItem_->update();
	resetWnds();
	return true;
}
