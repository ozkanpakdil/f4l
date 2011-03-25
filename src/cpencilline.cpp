#include "cpencilline.h"
#include <qpainter.h>

CPencilLine::CPencilLine (QCanvas * canvas)
:QCanvasPolygonalItem (canvas)
{
    pPolylineTemp = new QPtrList < QPoint >;
        //polyline=QPointArray(1000);
}

void CPencilLine::drawShape (QPainter & p){
    p.drawPolyline (polyline);
}

QPointArray CPencilLine::areaPoints () const
{
    /* ((CPencilLine*)this)->polyline=QPointArray(pPolylineTemp->count());
       for(int i=0;i<pPolylineTemp->count();i++)
       ((CPencilLine*)this)->polyline[i]=*pPolylineTemp->at(i);
       qDebug("%d",pPolylineTemp->count());    */
    return polyline;
}

void CPencilLine::setControlPoints (QPointArray clo, bool cl){
    polyline = QPointArray (clo.size ());
    polyline = clo;
}

void CPencilLine::moveBy (double dx, double dy){
        //removeFromChunks();
    QCanvasPolygonalItem::moveBy (dx, dy);
    for (unsigned int i = 0; i < polyline.size (); i++) {
        polyline[i].setX (polyline[i].x () + (int) dx);
        polyline[i].setY (polyline[i].y () + (int) dy);
    }
        //addToChunks();
}
