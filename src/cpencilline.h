#ifndef CPENCILLINE_H
#define CPENCILLINE_H

#include <qcanvas.h>
#include <qpointarray.h>

class CPencilLine:public QCanvasPolygonalItem
{
public:
    void moveBy (double dx, double dy);
    CPencilLine (QCanvas * canvas);
    QPtrList < QPoint > *pPolylineTemp;
    QPointArray polyline;
    void setControlPoints (QPointArray ctrl, bool close = TRUE);
    QPointArray areaPoints ()const;
	int Row;///this will be the Z dimension for object
	int Col;///this is frame for object.
	int animationX;///this is the frame number of object.
protected:
    void drawShape (QPainter & p);

};
#endif	/*

*/
