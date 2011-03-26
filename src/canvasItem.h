/***************************************************************************
              ccanvas.h  -  description
                 -------------------
    begin                : Tue Jul 3 2003
    copyright            : (C) 2003 by özkan pakdil
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

#ifndef CCANVASITEM_H
#define CCANVASITEM_H

#include <q3canvas.h>
#include <q3pointarray.h>
//Added by qt3to4:
#include <Q3PtrList>

/**
this class will be used for items inside work area
  *@author özkan pakdil
  */
class CCanvasItem:public Q3CanvasItem	//,public QObject
{
        //      Q_OBJECT
public:
    CCanvasItem (Q3Canvas * canvas);
    virtual ~ CCanvasItem ();
	int animationX;///this is the frame number of object.
	int Row;
};

class CPenTool:public Q3CanvasPolygonalItem
{
public:
    void moveBy (double dx, double dy);
    void setControlPoints (Q3PointArray ctrl, bool close = TRUE);
    CPenTool (Q3Canvas * canvas);
    Q3PtrList < QPoint > *pPolylineTemp;
    Q3PointArray polyline, part1, part2, part3;

    int rtti () const {
        return 1111111;
    }

    Q3PointArray areaPoints () const;
	int animationX;///this is the frame number of object.
	
protected:
    void drawShape (QPainter & p);
    Q3PointArray bez;

};

/// this is the white rectangle middle of workspace's class
class CSceneRect:public Q3CanvasRectangle
{
public:
    CSceneRect (const QRect & r, Q3Canvas * canvas):Q3CanvasRectangle (r, canvas)
    {}
    ;
    int rtti () const  {
        return 666;
    }
};

//this will be used for that blue rectangles around selected objects.
class CtmpRect:public Q3CanvasRectangle
{
public:
    CtmpRect (const QRect & r, Q3Canvas * canvas):Q3CanvasRectangle (r, canvas)
    {}
    ;
    int rtti () const {
        return 667;
    }
};

///this class for next version
/// I thought with this class F4L can have drawing abilities like M.Flash
/*class CPixmap:public QCanvasPixmap
{
public:
  CPixmap (QCanvas * canvas);
};
*/

#endif				// CCANVASITEM_H
