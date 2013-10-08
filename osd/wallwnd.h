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
#include <QMouseEvent>

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
	virtual void	mouseDoubleClickEvent ( QGraphicsSceneMouseEvent * event );

	void resize( QPointF &curr);
};

class ExtentItem: public QGraphicsRectItem{
public:

	enum Direction{
		Left,
		Top,
		Bottom,
		Right,
		Full,
		Pre,
		Next,
	};
	bool isPressed_;
	Direction dir_;
	ExtentItem(Direction dir);
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void	mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;

	void resize();
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

class AreaItem: public QGraphicsRectItem{
	bool isPressed_;
	bool isMoving_;
	QPointF pressPos_;
	
public:
	QString wndid_;
	AreaItem(double x, double y, double w, double h);
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event )override;
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;
	void resetRect();
};

class WndRectItem: public QGraphicsRectItem{
	//QRectF textRect_;
public:
	AreaItem *areaItem_;
	Wnd* wnd_;
	bool isMoving_;
	bool isScaling_;
	QPointF pressPos_;
	//if you dont offer a wnd arg, then it will create one
	WndRectItem(double x, double y, double w, double h, WallScene* wallscene, Wnd* wnd);
	~WndRectItem();
	//QRectF boundingRect() const;  
	void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);  

	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event )override;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value)override;
	void bringFront();


};
class WallWnd;
class WallScene:public QGraphicsScene{
	bool isCreatingWnd_;
	QPointF pressPos_;
	
	void createWnd( QPointF & releasePos);
	void createWndInGreenRect( QRectF &rect);
	
	
public:
	QRectF getBigGreenRect( QRectF rect);
	bool isInGreenRect( QRectF &rect);
	QRectF adjustInGreenRect( QRectF &rect);
	std::vector<WndRectItem*> wndItems_;
	//Ring* currRing_;
	ResourceID currInput_;
	QString currRingid_;
	//QString currWndid_;
	WallScene();
	
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event )override;
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )override;
	WallWnd * wallWnd_;

	std::vector<QRectF> getGreenRects();
};

class WallWnd : public QWidget
{
    Q_OBJECT
    
		private slots:
			void currentChnIndexChanged ( const QString & text );
			void currentRingIndexChanged ( const QString & text );
			void currentWndIndexChanged ( const QString & text );
			void currentTabChanged ( int index );
			void changed ( const QList<QRectF> & );
			void clickedCloseWnd();
			void clickedActivateRing();
			void clickedResetWnd();
			void	clicked ( bool checked );
public:
    explicit WallWnd( QWidget* parent);
    ~WallWnd();
    
	void resetWnds();
	void resetComboBoxes();
	void refreshWndArgs();
private:

	void refreshWndArgs(Wnd* wnd);
	
	bool isResetting_;
	QComboBox* cbRings_;
	QComboBox* cbChns_;
	QComboBox* cbWnds_;

	ScreenRectItem* screensItem_;
	std::vector<ResourceID> inputs_;

    Ui::WallWnd *ui;

	QGraphicsView* gv_;
	WallScene* scene_;

	void drawScreens();

	bool inChangedCallback(ResourceID input);

};

#endif // WallWnd_H
