/***************************************************************************
              cbrushtool.h  -  description
                 -------------------
    begin                : Wed Sep 17 2003
    copyright            : (C) 2003 by özkan Pakdil
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

#ifndef CBRUSHTOOL_H
#define CBRUSHTOOL_H

#include <QGraphicsScene>
//Added by qt3to4:
#include <QPolygon>

/**this is canvas item for brush tool
  *@author özkan Pakdil
  */
class F4lmView;

class CCanvasBrushLine:public QGraphicsPolygonItem
{
public:
    CCanvasBrushLine (Q3Canvas * canvas);
    ~CCanvasBrushLine();
    QPolygon polyline;
    void moveBy (double dx, double dy);
    void setControlPoints (QPolygon ctrl, bool close = true);
    QPolygon areaPoints () const;
    void setWidth (int W)
    {
        width = W;
    }
        //int rtti () const { return 1111111; }
		int animationX;
protected:
    void drawShape (QPainter & p);

private:
    int width;
    F4lmView *dad;
};

#endif
