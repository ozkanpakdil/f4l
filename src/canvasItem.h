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

#include <qcanvas.h>
#include <qpointarray.h>

/**
this class will be used for items inside work area
  *@author özkan pakdil
  */
class CCanvasItem:public QCanvasItem	//,public QObject
{
        //      Q_OBJECT
public:
    CCanvasItem (QCanvas * canvas);
    virtual ~ CCanvasItem ();
	int animationX;///this is the frame number of object.
	int Row;
};

class CPenTool:public QCanvasPolygonalItem
{
public:
    void moveBy (double dx, double dy);
    void setControlPoints (QPointArray ctrl, bool close = TRUE);
    CPenTool (QCanvas * canvas);
    QPtrList < QPoint > *pPolylineTemp;
    QPointArray polyline, part1, part2, part3;

    int rtti () const {
        return 1111111;
    }

    QPointArray areaPoints () const;
	int animationX;///this is the frame number of object.
	
protected:
    void drawShape (QPainter & p);
    QPointArray bez;

};

/// this is the white rectangle middle of workspace's class
class CSceneRect:public QCanvasRectangle
{
public:
    CSceneRect (const QRect & r, QCanvas * canvas):QCanvasRectangle (r, canvas)
    {}
    ;
    int rtti () const  {
        return 666;
    }
};

//this will be used for that blue rectangles around selected objects.
class CtmpRect:public QCanvasRectangle
{
public:
    CtmpRect (const QRect & r, QCanvas * canvas):QCanvasRectangle (r, canvas)
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
