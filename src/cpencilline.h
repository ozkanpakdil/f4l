#ifndef CPENCILLINE_H
#define CPENCILLINE_H

#include <q3canvas.h>
#include <q3pointarray.h>
//Added by qt3to4:
#include <Q3PtrList>

class CPencilLine:public Q3CanvasPolygonalItem
{
public:
    void moveBy (double dx, double dy);
    CPencilLine (Q3Canvas * canvas);
    Q3PtrList < QPoint > *pPolylineTemp;
    Q3PointArray polyline;
    void setControlPoints (Q3PointArray ctrl, bool close = TRUE);
    Q3PointArray areaPoints ()const;
	int Row;///this will be the Z dimension for object
	int Col;///this is frame for object.
	int animationX;///this is the frame number of object.
protected:
    void drawShape (QPainter & p);

};
#endif	/*

*/
