#ifndef WallWnd_H
#define WallWnd_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox.h>
#include <stdint.h>
#include <QboxNet.h>
#include <screen.h>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>


namespace Ui {
class WallWnd;
}


class WndRectItem: public QGraphicsRectItem{
public:

	QRectF boundingRect() const;  
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  
	virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value)override;
};

class WallScene:public QGraphicsScene{
public:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
};


class WallWnd : public QWidget
{
    Q_OBJECT
    
public:
    explicit WallWnd( QWidget* parent);
    ~WallWnd();
    


private:
    Ui::WallWnd *ui;

	QGraphicsView* gv_;
	WallScene* scene_;

	void drawScreens();
	
};

#endif // WallWnd_H
