#include "WallWnd.h"
#include "ui_WallWnd.h"
#include <QtDeclarative/QDeclarativeView>
#include <qdebug.h>
#include <sstream>
#include "QboxNet.h"
#include "screen.h"
#include "boost/foreach.hpp"


#include <Screen.h>


QRectF WndRectItem::boundingRect() const  
{  
	//qreal adjust=0.5;  
	
	return QRectF(0,0,200,200);  
}  

void WndRectItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)  
{  
	painter->setBrush(QBrush(Qt::red));
	setRect(boundingRect());
	painter->drawRect(boundingRect());  
	QGraphicsRectItem::paint(painter, option, widget);
}  

void WndRectItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event){
	qDebug()<<"WndRectItem dragEnterEvent";
	QGraphicsRectItem::dragEnterEvent(event);
}
void WndRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
	qDebug()<<"WndRectItem mousePressEvent"<<this;
	QGraphicsRectItem::mousePressEvent(event);
	setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable|QGraphicsItem::ItemClipsToShape|ItemSendsScenePositionChanges );

}

QVariant WndRectItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(scene() &&change == ItemPositionChange )
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


void WallScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
	qDebug()<<"WallScene mousePressEvent";
	QGraphicsScene::mousePressEvent(event);
	
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
	WndRectItem *item1=new WndRectItem;  
	
    scene_->addItem(item);
	scene_->addItem(item1);
	
  
	gv_->setScene(scene_);
    gv_->setRenderHint(QPainter::Antialiasing);  
    gv_->setCacheMode(QGraphicsView::CacheBackground);  
    gv_->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);  
	gv_->setDragMode(QGraphicsView::ScrollHandDrag);  

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