#include "WallWnd.h"
#include "ui_WallWnd.h"
#include <QtDeclarative/QDeclarativeView>
#include <qdebug.h>
#include <sstream>
#include "QboxNet.h"
#include "screen.h"
#include "boost/foreach.hpp"

#include <Screen.h>

void ScreenRectItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	uint32_t cc = ScreenMgr::instance()->getColCount();
	uint32_t rc = ScreenMgr::instance()->getRowCount();

	if ( !cc || !rc ) {return;}

	for ( uint32_t i = 0; i < rc; ++i){
		QRectF r = scene()->sceneRect();
		QPointF start, end;
		start.setX( 0);
		start.setY( r.height()/rc*i);
		end.setX(r.width());
		end.setY( r.height()/rc*i);
		painter->drawLine(start, end);
	}

	for ( uint32_t i = 0; i < cc; ++i){
		QRectF r = scene()->sceneRect();
		QPointF start, end;
		start.setX( r.width()/cc*i);
		start.setY( 0);
		end.setX(r.width()/cc*i);
		end.setY(r.height() );
		painter->drawLine(start, end);
	}

}
//=======================================================================================================================================================================
ResizeItem::ResizeItem(Direction dir):
dir_(dir)
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

QRectF ResizeItem::boundingRect() const{
	static int size = 2;
	switch(dir_){
		case Direction::LeftUp:
			return QRectF(0,0,size,size);  
		case Direction::RightBottom:
			return QRectF(	parentItem ()->boundingRect().width()-size,parentItem ()->boundingRect().height()-size,size,size);  
		case Direction::LeftBottom:
			return QRectF(	0,parentItem ()->boundingRect().height()-size,size,size);  
		case Direction::RightUp:
			return QRectF(	parentItem ()->boundingRect().width()-size,0,size,size);  
	}
}

void ResizeItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget){
	QRectF r= boundingRect();
	setRect(r);
	painter->setBrush(QBrush(Qt::yellow));
	painter->drawRect(r);  
}
void ResizeItem::resize( QPointF &curr){
	QPointF & cur = this->mapToScene(curr);
	WndRectItem* item= (WndRectItem*)parentItem();
	QPointF itempos =  item->pos();
	
	QPointF oldPos, newPos;
	QPointF ajustPos ;
	QPointF dis;
	QRectF newRect;
	QRectF oldRect = item->rect();
	switch ( dir_){
		case Direction::LeftUp:
			oldPos = itempos;
			item->setPos( cur  );
			dis = item->pos() - oldPos;

			newRect.setWidth(oldRect.width() -dis.x());
			newRect.setHeight(oldRect.height() - dis.y());
			newRect.width() < 50 ?newRect.setWidth(50):void();
			newRect.height() < 50 ?	newRect.setHeight(50):void();
			item->setRect(newRect);
			break;
		case Direction::RightBottom:
			oldPos =  QPointF( oldRect.width(), oldRect.height());
			newRect.setWidth(curr.x());
			newRect.setHeight(curr.y());
			newRect.width() < 50 ?newRect.setWidth(50):void();
			newRect.height() < 50 ?	newRect.setHeight(50):void();
			newRect.width() +itempos.x()> scene()->sceneRect().width()?newRect.setWidth(scene()->sceneRect().width() - itempos.x()):void();
			newRect.height() +itempos.y()> scene()->sceneRect().height()?newRect.setHeight(scene()->sceneRect().height() - itempos.y()):void();
			item->setRect(newRect);
			break;
		case Direction::LeftBottom:
			oldPos = itempos;
			item->setX( cur.x() );
			dis = item->pos() - oldPos;
			newRect.setHeight(curr.y());
			newRect.setWidth(oldRect.width() - dis.x());
			newRect.width() < 50 ?newRect.setWidth(50):void();
			newRect.height() < 50 ?	newRect.setHeight(50):void();
			newRect.width() > scene()->sceneRect().width()?newRect.setWidth(scene()->sceneRect().width() ):void();
			newRect.height() +itempos.y()> scene()->sceneRect().height()?newRect.setHeight(scene()->sceneRect().height()  - itempos.y()):void();
			item->setRect(newRect);
			break;
		case Direction::RightUp:
			oldPos = itempos;
			item->setY( cur.y() );
			dis = item->pos() - oldPos;
			newRect.setWidth(curr.x());
			newRect.setHeight(oldRect.height() - dis.y());
			newRect.width() < 50 ?newRect.setWidth(50):void();
			newRect.height() < 50 ?	newRect.setHeight(50):void();
			newRect.width() +itempos.x()> scene()->sceneRect().width()?newRect.setWidth(scene()->sceneRect().width() - itempos.x()):void();
			newRect.height() +itempos.y()> scene()->sceneRect().height()?newRect.setHeight(scene()->sceneRect().height() - itempos.y()):void();
			item->setRect(newRect);
			break;
	}


}
void ResizeItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseMoveEvent(event);
	WndRectItem* parent = ((WndRectItem*)parentItem());
	if ( isResizing_) resize(event->pos());
}
void ResizeItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

	QGraphicsRectItem::mousePressEvent(event);
	WndRectItem* parent = ((WndRectItem*)parentItem());
	pressPos_ = event->pos();
	isResizing_ = true;
}
void ResizeItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	WndRectItem* parent = ((WndRectItem*)parentItem());

}
//=======================================================================================================================================================================
MoveItem::MoveItem(){
	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape|ItemSendsScenePositionChanges );
	setCursor( Qt::OpenHandCursor);
}
QRectF MoveItem::boundingRect() const  {  
	QRectF r= parentItem()->boundingRect();
	return QRectF(r.x()+r.width()/5*2, r.y()+r.height()/5*2, r.width()/5, r.height()/5);;
} 
void MoveItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  

	QRectF r = boundingRect();
	setRect(r);
	painter->setBrush(QBrush(Qt::cyan));
	painter->drawRect(r);
	painter->drawText(r, QString::number((int)1), QTextOption(Qt::Alignment::enum_type::AlignHCenter|Qt::Alignment::enum_type::AlignVCenter));
	QGraphicsRectItem::paint(painter, option, widget);
} 
void MoveItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	
	QGraphicsRectItem::mouseMoveEvent(event);
	((WndRectItem*)parentItem())->mouseMoveEvent(event);
}
void MoveItem::mousePressEvent(QGraphicsSceneMouseEvent *event){

	QGraphicsRectItem::mousePressEvent(event);
	((WndRectItem*)parentItem())->isMoving_ = true;
	setCursor( Qt::ClosedHandCursor);
}
void MoveItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	((WndRectItem*)parentItem())->isMoving_ = false;
	setCursor( Qt::OpenHandCursor);
}
//=======================================================================================================================================================================
CloseItem::CloseItem(){
	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape );
	setCursor( Qt::PointingHandCursor);
}
QRectF CloseItem::boundingRect() const  {  return QRectF( parentItem()->boundingRect().width() - 20, 0, 10, 10);} 
void CloseItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  

	QRectF r = boundingRect();
	setRect(r);
	painter->setBrush(QBrush(Qt::yellow));
	painter->drawRect(r);
	painter->drawLine(QPointF(r.x(), r.y()), QPointF(r.x()+r.width(), r.y()+r.height()));
	painter->drawLine(QPointF(r.x()+r.width(), r.y()), QPointF(r.x(), r.y()+r.height()));
	
	QGraphicsRectItem::paint(painter, option, widget);
} 
//=======================================================================================================================================================================
WndRectItem::WndRectItem(){
	setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape|ItemSendsScenePositionChanges );
	ResizeItem *item = new ResizeItem( ResizeItem::RightUp);
	ResizeItem *item1 = new ResizeItem( ResizeItem::RightBottom);
	ResizeItem *item2 = new ResizeItem( ResizeItem::LeftBottom);
	ResizeItem *item3 = new ResizeItem( ResizeItem::LeftUp);
	MoveItem *item4 = new MoveItem( );
	CloseItem *item5 = new CloseItem( );
	item->setParentItem(this);
	item1->setParentItem(this);
	item2->setParentItem(this);
	item3->setParentItem(this);
	item4->setParentItem(this);
	item5->setParentItem(this);

	setCursor( Qt::CrossCursor);
}

QRectF WndRectItem::boundingRect() const  {  
	return rect();
}  

void WndRectItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	painter->setBrush(QBrush(Qt::red));
	QRectF r= boundingRect();
	//moveRect_= QRectF(r.x()+r.width()/5*2, r.y()+r.height()/5*2, r.width()/5, r.height()/5);
	areaRect_ = QRectF(r.x()+r.width()/5*1, r.y()+r.height()/5*1, r.width()/5*3, r.height()/5*3);
	painter->drawRect(boundingRect());  
	painter->setBrush(QBrush(Qt::green));
	painter->drawRect(areaRect_);  
	//qDebug()<<r;
	//qDebug()<< this->x();
	//qDebug()<< this->y();
	//painter->setBrush(QBrush(Qt::cyan));
	//painter->drawRect(moveRect_);
	//painter->drawText(moveRect_, QString::number((int)1), QTextOption(Qt::Alignment::enum_type::AlignHCenter|Qt::Alignment::enum_type::AlignVCenter));
	QGraphicsRectItem::paint(painter, option, widget);
}  


void WndRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	//qDebug()<<"WndRectItem mousePressEvent"<<this;
	QGraphicsRectItem::mousePressEvent(event);
	

	setZValue(zValue()+1);
	//if ( rect().contains( event->pos())){
	//	if (moveRect_.contains(event->pos()) ) {
	//		isMoving_ = true;
	//		setCursor( Qt::ClosedHandCursor);
	//	}else{
	//		isMoving_ = false;
	//		setCursor( Qt::OpenHandCursor);
	//	}
	//}
}
void	WndRectItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	//isMoving_ = false;
	//setCursor( Qt::OpenHandCursor);
}
void	WndRectItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	if (isMoving_) {
		QGraphicsRectItem::mouseMoveEvent(event);
	}
	//if (moveRect_.contains(event->pos()) ) {
	//	if ( isMoving_){
	//		setCursor( Qt::ClosedHandCursor);
	//	}else{
	//		setCursor( Qt::ArrowCursor);
	//	}
	//}else{
	//	setCursor( Qt::ArrowCursor);
	//}
}
void	WndRectItem::hoverMoveEvent ( QGraphicsSceneHoverEvent * event ){
	qDebug()<<"WndRectItem::hoverMoveEvent";
}


QVariant WndRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(scene() && (change == ItemPositionChange || change ==ItemMatrixChange ) )
    {
        QPointF newPos = value.toPointF();
        QRectF r = scene()->sceneRect();
		r.setRight(r.right() - rect().right());
		r.setBottom(r.bottom() - rect().bottom());
        if(!r.contains(newPos))
        {
            newPos.setX(qMin(r.right(), qMax(newPos.x(), r.left())));
            newPos.setY(qMin(r.bottom(), qMax(newPos.y(), r.top())));
            return newPos;
        }
    }
 
    return QGraphicsRectItem::itemChange(change, value);
}

//=======================================================================================================================================================================
void WallScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	QGraphicsScene::mousePressEvent(event);
	//QList<QGraphicsItem *>  list = items( event->pos(), Qt::ItemSelectionMode::IntersectsItemBoundingRect, Qt::SortOrder::AscendingOrder);
	//if (list.size()>0){
	//	
	//}
}
void WallScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsScene::mouseMoveEvent(event);
	//QList<QGraphicsItem *>  list = items( event->pos(), Qt::ItemSelectionMode::IntersectsItemBoundingRect, Qt::SortOrder::AscendingOrder);
	//if (list.size()>0){
	//	//if (sceneRect().contains(event->pos()) ) {
	//	views()[0]->setCursor( Qt::ArrowCursor);
	//	//}
	//}else{
	//	views()[0]->setCursor( Qt::ArrowCursor);
	//}

	
}

WallWnd::WallWnd(QWidget* parent) :
    QWidget(parent)
	,ui(new Ui::WallWnd)
{
    ui->setupUi(this);


	gv_ = findChild<QGraphicsView* >("wallView");

	QGraphicsScene *scene_ = new WallScene;  
    scene_->setItemIndexMethod(QGraphicsScene::NoIndex);  

    WndRectItem *item=new WndRectItem;  
	item->setRect( QRect(0, 0, 200, 200));
	//WndRectItem *item1=new WndRectItem;  
	ScreenRectItem* item2 = new ScreenRectItem;

	scene_->addItem(item2);
    scene_->addItem(item);
	//scene_->addItem(item1);
  
	gv_->setScene(scene_);
    gv_->setRenderHint(QPainter::Antialiasing);  
    gv_->setCacheMode(QGraphicsView::CacheBackground);  
    gv_->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  
	gv_->setDragMode(QGraphicsView::NoDrag);  

	gv_->setBackgroundBrush(QBrush(Qt::lightGray));
	gv_->setInteractive(true);
    gv_->show();  
}



WallWnd::~WallWnd()
{
    delete ui;
}



void WallWnd::drawScreens(){
	uint32_t col = ScreenMgr::instance()->getColCount();
	uint32_t row = ScreenMgr::instance()->getRowCount();
}