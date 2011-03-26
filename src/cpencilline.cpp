#include "cpencilline.h"
#include <qpainter.h>
//Added by qt3to4:
#include <Q3PointArray>
#include <Q3PtrList>

CPencilLine::CPencilLine (Q3Canvas * canvas)
:Q3CanvasPolygonalItem (canvas)
{
    pPolylineTemp = new Q3PtrList < QPoint >;
        //polyline=QPointArray(1000);
}

void CPencilLine::drawShape (QPainter & p){
    p.drawPolyline (polyline);
}

Q3PointArray CPencilLine::areaPoints () const
{
    /* ((CPencilLine*)this)->polyline=QPointArray(pPolylineTemp->count());
       for(int i=0;i<pPolylineTemp->count();i++)
       ((CPencilLine*)this)->polyline[i]=*pPolylineTemp->at(i);
       qDebug("%d",pPolylineTemp->count());    */
    return polyline;
}

void CPencilLine::setControlPoints (Q3PointArray clo, bool cl){
    polyline = Q3PointArray (clo.size ());
    polyline = clo;
}

void CPencilLine::moveBy (double dx, double dy){
        //removeFromChunks();
    Q3CanvasPolygonalItem::moveBy (dx, dy);
    for (unsigned int i = 0; i < polyline.size (); i++) {
        polyline[i].setX (polyline[i].x () + (int) dx);
        polyline[i].setY (polyline[i].y () + (int) dy);
    }
        //addToChunks();
}
