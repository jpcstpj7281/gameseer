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
#include <wnd.h>

namespace Ui {
class WallWnd;
}
class WallScene;
class Ring;

class ScreenRectItem: public QGraphicsRectItem{
public:
	//QRectF boundingRect() const;  
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  
};

class ResizeItem: public QGraphicsRectItem{
public:

	enum Direction{
		LeftUp,
		RightUp,
		LeftBottom,
		RightBottom,
	};
	bool isResizing_;
	QPointF pressPos_;
	Direction dir_;
	ResizeItem(Direction dir);
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  
	virtual void	mouseMoveEvent ( QGraphicsSceneMouseEvent * event )override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void	mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;

	void resize( QPointF &curr);
};

class MoveItem: public QGraphicsRectItem{
public:
	MoveItem();
	//QRectF boundingRect() const;  
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  
	virtual void	mouseMoveEvent ( QGraphicsSceneMouseEvent * event )override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void	mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;
};

class CloseItem: public QGraphicsRectItem{
	bool isPressed_;
public:
	CloseItem();
	//QRectF boundingRect() const;  
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;
};

class WndRectItem: public QGraphicsRectItem{


	QRectF areaRect_;
	
public:
	Wnd* wnd_;
	bool isMoving_;
	WndRectItem(double x, double y, double w, double h, WallScene* wallscene);
	~WndRectItem();
	//QRectF boundingRect() const;  
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  

	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event )override;
	virtual void hoverMoveEvent ( QGraphicsSceneHoverEvent * event )override;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value)override;
	void bringFront();
};

class WallScene:public QGraphicsScene{
	bool isCreatingWnd_;
	QPointF pressPos_;
	
	void createWnd( QPointF & releasePos);
public:
	Ring* currRing_;
	ResourceID currInput_;
	WallScene();
	
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event )override;
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;
};


class WallWnd : public QWidget
{
    Q_OBJECT
    
		private slots:
			void currentTabChanged ( int index );
			void	changed ( const QList<QRectF> & );
public:
    explicit WallWnd( QWidget* parent);
    ~WallWnd();
    


private:

	QComboBox* cbRings_;
	QComboBox* cbChns_;
	QComboBox* cbWnds_;
	QString currRingid_;
	QString currWndid_;
	std::vector<ResourceID> inputs_;

    Ui::WallWnd *ui;

	QGraphicsView* gv_;
	WallScene* scene_;

	void drawScreens();
	
};

#endif // WallWnd_H
