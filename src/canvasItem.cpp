#include "canvasItem.h"
#include <qpainter.h>
#include <QList>
#include <QPolygon>

CCanvasItem::CCanvasItem (QGraphicsItem * canvas):QGraphicsItem (canvas)
{}

CCanvasItem::~CCanvasItem ()
{}

CPenTool::CPenTool (QGraphicsItem * canvas):QGraphicsPolygonItem (canvas)
{
    pPolylineTemp = new QList < QPoint >;
        //polyline=QPointArray(1000);
    part1 = QPolygon (4);
    part2 = QPolygon (4);
    part3 = QPolygon (4);
        //bez=QPointArray(20);
}

void CPenTool::drawShape (QPainter & p)
{
        //QCanvasPolygonalItem::drawShape(p);
        //for(QPoint *pint=pPolylineTemp->first();pint;pint=pPolylineTemp->next()){
    /*QPointArray pts;
       pts.setPoints( 4, -20,0,  0,-20, 300,0, 0,20 );
       p.drawConvexPolygon( pts ); */

    /*QRect r=polyline.boundingRect();
       p. */
    p.drawPolygon (polyline);
    p.setPen (Qt::black);
    p.drawPoints (bez);
    /*      part1[0]=polyline[0];
       part1[1]=polyline[1];
       part1[2]=polyline[2];
       part1[3]=polyline[3];
       part2[0]=polyline[4];
       part2[1]=polyline[5];
       part2[2]=polyline[6];
       part2[3]=polyline[7];
       part3[0]=polyline[8];
       part3[1]=polyline[9];
       part3[2]=polyline[10];
       part3[3]=polyline[11];
       p.drawConvexPolygon(part1);
       p.drawConvexPolygon(part2);
       p.drawConvexPolygon(part3);
       /*p.drawCubicBezier(part1);
       p.drawCubicBezier(part2);
       p.drawCubicBezier(part3); */
    /*for(int k=0;k<12-4;k++){
       for(int i=k;i<k+4;i++){
       part1[i]=polyline[i];
       }
       p.drawConvexPolygon(part1);
       } */
        //      p.restore();
        //}
}

QPolygon CPenTool::areaPoints () const
{
    return polyline;
}

void CPenTool::setControlPoints (QPolygon clo, bool cl)
{
    bez = QPolygon (clo.size ());
    bez = clo;
        //polyline=ctrl;
    QList < QPolygon > segs;
    segs.setAutoDelete (true);
    int
    n = 0;
    for (int i = 0; i < (int) bez.count () - 1; i += 3) {
        QPolygon
        ctrl (4);
        ctrl[0] = bez[i + 0];
        ctrl[1] = bez[i + 1];
        ctrl[2] = bez[i + 2];
        if (cl)
            ctrl[3] = bez[(i + 3) % (int) bez.count ()];
        else
            ctrl[3] = bez[i + 3];
        QPolygon *
        seg = new QPolygon (ctrl.cubicBezier ());
        n += seg->count () - 1;
        segs.append (seg);
    }
    QPolygon
    p (n + 1);
    n = 0;
    for (QPolygon * seg = segs.first (); seg; seg = segs.next ()) {
        for (int i = 0; i < (int) seg->count () - 1; i++)
            p[n++] = seg->point (i);
        if (n == (int) p.count () - 1)
            p[n] = seg->point (seg->count () - 1);
    }
        //QCanvasPolygon::setPoints(p);
    polyline = QPolygon (p.size ());
    polyline = p;
}

void CPenTool::moveBy (double dx, double dy)
{
    QGraphicsPolygonItem::moveBy (dx, dy);
    for (int i = 0; i < polyline.size (); i++) {
        polyline[i].setX (polyline[i].x () + (int) dx);
        polyline[i].setY (polyline[i].y () + (int) dy);
    }
}
