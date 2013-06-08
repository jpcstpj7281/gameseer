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
void ResizeItem::resize( QPointF &curr){
	
	WndRectItem* item= (WndRectItem*)parentItem();
	QPointF curPos = this->mapToScene(curr);

	QPointF leftup =  item->mapToItem(this, item->pos());
	QPointF rightbottom =  item->mapToItem(this, QPointF( item->pos().x()+item->rect().width(), item->pos().y()+item->rect().height()) );
	QPointF rightup =  item->mapToItem(this, QPointF( item->pos().x()+item->rect().width(), item->pos().y()) );
	QPointF leftbottom =  item->mapToItem(this, QPointF( item->pos().x(), item->pos().y()+item->rect().height()) );

	QPointF newPos;
	QRectF newRect;
	QRectF oldRect;
	switch ( dir_){
		case Direction::LeftUp:
			newPos = curPos;
			if ( rightbottom.x() - curPos.x() < 50){
				newPos.setX(rightbottom.x()-50);
			}
			else if (  curPos.x() < 0){
				newPos.setX(0);
			}
			if ( rightbottom.y() - curPos.y() < 50){
				newPos.setY(rightbottom.y()-50);
			}
			else if ( curPos.y() < 0){
				newPos.setY(0);
			}

			newRect.setWidth(rightbottom.x() -newPos.x());
			newRect.setHeight(rightbottom.y() -newPos.y());
			item->setRect(newRect);
			item->setPos(  newPos  );
			break;
		case Direction::RightBottom:
			newRect = QRectF( 0, 0, curPos.x()-leftup.x(), curPos.y()-leftup.y());
			if ( curPos.x() - leftup.x() < 50){
				newRect.setWidth(50);
			}
			else if (  curPos.x()  > scene()->sceneRect().width()  ){
				newRect.setWidth(scene()->sceneRect().width() - leftup.x());
			}
			if ( curPos.y() - leftup.y() < 50){
				newRect.setHeight(50);
			}
			else if (  curPos.y()  > scene()->sceneRect().height() ){
				newRect.setHeight(scene()->sceneRect().height() - leftup.y());
			}
			item->setRect(newRect);
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
//QRectF MoveItem::boundingRect() const  {  
//	
//} 
void MoveItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	QRectF r= ((QGraphicsRectItem*)parentItem())->rect();
	setRect(QRectF(r.x()+r.width()/5*2, r.y()+r.height()/5*2, r.width()/5, r.height()/5));
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
	((WndRectItem*)parentItem())->mousePressEvent(event);
	setCursor( Qt::ClosedHandCursor);
}
void MoveItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
	((WndRectItem*)parentItem())->isMoving_ = false;
	setCursor( Qt::OpenHandCursor);
}
//=======================================================================================================================================================================
CloseItem::CloseItem(){
	isPressed_ = false;
	setFlags(QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape );
	setCursor( Qt::PointingHandCursor);
}
//QRectF CloseItem::boundingRect() const  {  return ;} 
void CloseItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  

	QRectF r = QRectF( ((QGraphicsRectItem*)parentItem())->rect().width() - 20, 0, 10, 10);
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
		item->scene()->removeItem(item);
		delete item;
	}
}
//=======================================================================================================================================================================
WndRectItem::WndRectItem(){
	setFlags(QGraphicsItem::ItemIsMovable |QGraphicsItem::ItemClipsToShape|ItemSendsScenePositionChanges );
	//ResizeItem *item = new ResizeItem( ResizeItem::RightUp);
	ResizeItem *item1 = new ResizeItem( ResizeItem::RightBottom);
	//ResizeItem *item2 = new ResizeItem( ResizeItem::LeftBottom);
	ResizeItem *item3 = new ResizeItem( ResizeItem::LeftUp);
	MoveItem *item4 = new MoveItem( );
	CloseItem *item5 = new CloseItem( );
	//item->setParentItem(this);
	item1->setParentItem(this);
	//item2->setParentItem(this);
	item3->setParentItem(this);
	item4->setParentItem(this);
	item5->setParentItem(this);

	setCursor( Qt::CrossCursor);
	isMoving_ = false;
}

//QRectF WndRectItem::boundingRect() const  {  
//	QRectF r = rect();
//	r.setX( pos().x());
//	r.setY( pos().y());
//	return r;
//}  

void WndRectItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  {  
	painter->setBrush(QBrush(Qt::red));
	QRectF r= rect();
	areaRect_ = QRectF(r.x()+r.width()/5*1, r.y()+r.height()/5*1, r.width()/5*3, r.height()/5*3);
	painter->drawRect(r);  
	painter->setBrush(QBrush(Qt::green));
	painter->drawRect(areaRect_);  
	//qDebug()<<r;
	//qDebug()<< this->x();
	//qDebug()<< this->y();
	QGraphicsRectItem::paint(painter, option, widget);
}  


void WndRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	//qDebug()<<"WndRectItem mousePressEvent"<<this;
	QGraphicsRectItem::mousePressEvent(event);
	setZValue(zValue()+1);
}
void	WndRectItem::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event ){
	QGraphicsRectItem::mouseReleaseEvent(event);
}
void	WndRectItem::mouseMoveEvent ( QGraphicsSceneMouseEvent * event ){
	if (isMoving_) {
		QGraphicsRectItem::mouseMoveEvent(event);
	}
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
	pressPos_ = event->scenePos();
	QList<QGraphicsItem *>  list = items( pressPos_, Qt::ItemSelectionMode::IntersectsItemShape, Qt::SortOrder::AscendingOrder);
	if ( list.size() == 0){//Into create wnd mode
		isCreatingWnd_ = true;
	}
	//qDebug()<<list.size();
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
}

void WallScene::createWnd( QPointF & releasePos){
	size_t height = 50, width = 50;
	QPointF pos;
	if (releasePos.x() > pressPos_.x() && releasePos.y() > pressPos_.y()){
		width = releasePos.x() - pressPos_.x();
		height = releasePos.y()-pressPos_.y();
		pos = pressPos_;
	}else if (releasePos.x() < pressPos_.x() && releasePos.y() < pressPos_.y()){
		width = -releasePos.x() + pressPos_.x();
		height = -releasePos.y()+pressPos_.y();
		pos = releasePos;
	}else if (releasePos.x() > pressPos_.x() && releasePos.y() < pressPos_.y()){
		width = releasePos.x() - pressPos_.x();
		height = -releasePos.y()+pressPos_.y();
		pos = QPointF( pressPos_.x(), releasePos.y());
	}else if (releasePos.x() < pressPos_.x() && releasePos.y() > pressPos_.y()){
		width = -releasePos.x() + pressPos_.x();
		height = releasePos.y()-pressPos_.y();
		pos = QPointF( releasePos.x(),  pressPos_.y());
	}
	if ( width > 50 && height > 50){
		QRectF r( 0,0, width, height );
		WndRectItem *item=new WndRectItem;  
		item->setRect(r);
		addItem(item);
		item->setPos(pos);
	}
}
WallScene::WallScene(){
	isCreatingWnd_ = false;
}
//=======================================================================================================================================================================
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
	WndRectItem *item1=new WndRectItem;  
	item1->setRect( QRect(0, 0, 200, 200));
	ScreenRectItem* item2 = new ScreenRectItem;

	scene_->addItem(item2);
    scene_->addItem(item);
	scene_->addItem(item1);
  
	gv_->setScene(scene_);
    gv_->setRenderHint(QPainter::Antialiasing);  
    gv_->setCacheMode(QGraphicsView::CacheBackground);  
    gv_->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  
	gv_->setDragMode(QGraphicsView::RubberBandDrag);  

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