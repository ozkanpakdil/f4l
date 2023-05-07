#ifndef CCANVASITEM_H
#define CCANVASITEM_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainterPath>
#include <QList>

/**
this class will be used for items inside work area
  *@author özkan pakdil
  */
class CCanvasItem : public QGraphicsItem //,public QObject
{
    //      Q_OBJECT
public:
    CCanvasItem(QGraphicsItem *canvas);
    virtual ~CCanvasItem();
    int animationX; /// this is the frame number of object.
    int Row;
};

class CPenTool : public QGraphicsPolygonItem
{
public:
    void moveBy(double dx, double dy);
    void setControlPoints(QPolygon ctrl, bool close = true);
    CPenTool(QGraphicsScene *canvas);
    QList<QPoint> *pPolylineTemp;
    QPolygon polyline, part1, part2, part3;

    int rtti() const
    {
        return 1111111;
    }

    QPolygon areaPoints() const;
    int animationX; /// this is the frame number of object.

protected:
    void drawShape(QPainter &p);
    QPolygon bez;
};

/// this is the white rectangle middle of workspace's class
class CSceneRect : public QGraphicsRectItem
{
public:
    CSceneRect(const QRect &r, QGraphicsItem *canvas) : QGraphicsRectItem(r, canvas){};
    int rtti() const
    {
        return 666;
    }
};

// this will be used for that blue rectangles around selected objects.
class CtmpRect : public QGraphicsRectItem
{
public:
    CtmpRect(const QRect &r, QGraphicsItem *canvas) : QGraphicsRectItem(r, canvas){};
    int rtti() const
    {
        return 667;
    }
};

#endif // CCANVASITEM_H
