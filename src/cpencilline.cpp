#include "cpencilline.h"
#include <qpainter.h>
//Added by qt3to4:
#include <QPolygon>
#include <QList>

CPencilLine::CPencilLine (Q3Canvas * canvas)
:QGraphicsPolygonItem (canvas)
{
    pPolylineTemp = new QList < QPoint >;
        //polyline=QPointArray(1000);
}

void CPencilLine::drawShape (QPainter & p){
    p.drawPolyline (polyline);
}

QPolygon CPencilLine::areaPoints () const
{
    /* ((CPencilLine*)this)->polyline=QPointArray(pPolylineTemp->count());
       for(int i=0;i<pPolylineTemp->count();i++)
       ((CPencilLine*)this)->polyline[i]=*pPolylineTemp->at(i);
       qDebug("%d",pPolylineTemp->count());    */
    return polyline;
}

void CPencilLine::setControlPoints (QPolygon clo, bool cl){
    polyline = QPolygon (clo.size ());
    polyline = clo;
}

void CPencilLine::moveBy (double dx, double dy){
        //removeFromChunks();
    QGraphicsPolygonItem::moveBy (dx, dy);
    for (unsigned int i = 0; i < polyline.size (); i++) {
        polyline[i].setX (polyline[i].x () + (int) dx);
        polyline[i].setY (polyline[i].y () + (int) dy);
    }
        //addToChunks();
}
