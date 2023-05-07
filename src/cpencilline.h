#ifndef CPENCILLINE_H
#define CPENCILLINE_H

#include <QGraphicsScene>
#include <QPainterPath>
//Added by qt3to4:
#include <QList>

class CPencilLine:public QGraphicsPolygonItem
{
public:
    void moveBy (double dx, double dy);
    CPencilLine (Q3Canvas * canvas);
    QList < QPoint > *pPolylineTemp;
    QPolygon polyline;
    void setControlPoints (QPolygon ctrl, bool close = true);
    QPolygon areaPoints ()const;
	int Row;///this will be the Z dimension for object
	int Col;///this is frame for object.
	int animationX;///this is the frame number of object.
protected:
    void drawShape (QPainter & p);

};
#endif	/*

*/
