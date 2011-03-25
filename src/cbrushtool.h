/***************************************************************************
              cbrushtool.h  -  description
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

#ifndef CBRUSHTOOL_H
#define CBRUSHTOOL_H

#include <qcanvas.h>

/**this is canvas item for brush tool
  *@author Özkan Pakdil
  */
class F4lmView;

class CCanvasBrushLine:public QCanvasPolygonalItem
{
public:
    CCanvasBrushLine (QCanvas * canvas);
    ~CCanvasBrushLine();
    QPointArray polyline;
    void moveBy (double dx, double dy);
    void setControlPoints (QPointArray ctrl, bool close = TRUE);
    QPointArray areaPoints () const;
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
