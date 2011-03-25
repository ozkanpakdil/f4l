/***************************************************************************
              canview.h  -  description
                 -------------------
    begin                : Thu May 15 2003
    copyright            : (C) 2003 by root
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

#ifndef CANVIEW_H
#define CANVIEW_H

#include <qcanvas.h>
#include <qcursor.h>

class F4lmView;
class CPencilLine;
class CPenTool;
class CCanvasItem;
class CCanvasBrushLine;
class CSceneRect;
class CTextEditForTextTool;
class CCanvasLine;
class CCanvasText;
class CCanvasEllipse;
class CCanvasRectangle;

/**for showing canvases under F4lView
  *@author ozkan pakdil
  turkish: bu class ortadaki cizim ortamini olusturuyor. bu classin icine mouse event handling
  fonksiyonlari yazilacak.
  english: this class makes aour scene for drawing. mouse events and other stuff will be here.
  */

class canview:public QCanvasView
{
	Q_OBJECT 
public:
    canview (QCanvas * canvas, QWidget * parent, const char *name = 0);
    ~canview ();
    F4lmView *dad;
    bool butPos;
    int movX, cenX, movY, cenY;
    QCanvasPolygonalItem *currentObj;
    CCanvasLine *line;
    QFont textFont;
    CCanvasText *text;
    CTextEditForTextTool *textBox;
    CCanvasEllipse *oval;
    CCanvasRectangle *rect;
    CSceneRect *selectionRect;
    QCanvasRectangle *selectedRect;
    QCanvasSpline *spline;
    CPencilLine *pencilline;
    CCanvasBrushLine *brushline;
    QPtrList < QPoint > pPolylineTemp;
    CPenTool *penShape;

    QCanvasItemList mulSelect;
    QCanvasItemList mulSelectedRects;

    QPointArray polyline;
    QPointArray spolyline;

    QCursor handCursor;
    QCursor handCursorDown;
    QCursor arrowToolCursor;
    QCursor pencilCursor;
    QCursor brushCursor;
    QCursor paintbucketCursor;
    QCursor inkbottleCursor;
    QCursor pentoolCursor;
    QCursor lassotoolCursor;
    QCursor texttoolCursor;
    QCursor subselectiontoolCursor;
    QCursor zoominCursor;
    QCursor zoomoutCursor;
    QCursor eyedroppertool;
    QCursor eraserCursor;

    double z;			//used for z axis for canvas item
    QCanvasItem *moving;
    QPoint moving_start;

protected:
    void contentsMouseMoveEvent (QMouseEvent *);
    void contentsMousePressEvent (QMouseEvent *);
    void contentsMouseReleaseEvent (QMouseEvent *);
    void contentsMouseDoubleClickEvent (QMouseEvent *);
    void paintEvent (QPaintEvent * e);

        //void mousePressEvent ( QMouseEvent * e );
    void contentsDropEvent (QDropEvent *);
    void enterEvent (QEvent *);
    void leaveEvent (QEvent *);
    /** No descriptions */
    void keyPressEvent (QKeyEvent * e);

};

#endif
