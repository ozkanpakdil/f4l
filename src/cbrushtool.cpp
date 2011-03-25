/***************************************************************************
              cbrushtool.cpp  -  description
                 -------------------
    begin                : Wed Sep 17 2003
    copyright            : (C) 2003 by Özkan Pakdil
    email                : ozkanpakdil@users.sourceforge.net
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "cbrushtool.h"
#include "f4lm.h"
#include "f4lmview.h"
#include <qpainter.h>
#include <qstring.h>

CCanvasBrushLine::CCanvasBrushLine (QCanvas * canvas):QCanvasPolygonalItem (canvas)
{
        ///default width is 10
    dad = (F4lmView *) canvas->parent ();
}

CCanvasBrushLine::~CCanvasBrushLine ()
{
}

void CCanvasBrushLine::drawShape (QPainter & p)
{
    QPen pen ;
    pen.setWidth (width);
    p.setPen (pen);
        //      for(int i=0;i<polyline.count();i++)
        //      p.drawEllipse(polyline[i].x(),polyline[i].y(),10,10);
    p.drawPolyline (polyline);
        //p.drawPoints(bez);
}

QPointArray CCanvasBrushLine::areaPoints () const
{
    return polyline;
}

void CCanvasBrushLine::setControlPoints (QPointArray clo, bool cl){
    width = dad->dad->properties->brushProperties->textBox1->text ().toInt ();
    polyline = QPointArray (clo.size ());
    polyline = clo;
}

void CCanvasBrushLine::moveBy (double dx, double dy){
        //removeFromChunks();
    QCanvasItem::moveBy (dx, dy);
    int tx, ty;
    for (unsigned int i = 0; i < polyline.size (); i++) {
        tx = (int) polyline[i].x () + (int) dx;
        ty = (int) polyline[i].y () + (int) dy;
        polyline[i].setX (tx);
        polyline[i].setY (ty);
    }
        //addToChunks();
}
