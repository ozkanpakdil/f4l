/***************************************************************************
              clayer.h  -  description
                 -------------------
    begin                : Mon Jun 30 2003
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

#ifndef CLAYER_H
#define CLAYER_H

#include <qwidget.h>
#include <qcanvas.h>
#include <qptrlist.h>

class CCanvas;
class CCanvasItem;

/**this is the layer class for objects and canvases
  *@author özkan pakdil
  */
class CLayer:public QObject
{
    Q_OBJECT
public:
    CLayer (QWidget * parent = 0, const char *name = 0);
    ~CLayer ();

    QPtrList < CCanvasItem > *pCanvasItemList;
		
		///this list holds all canvases
    QPtrList < CCanvas > *pCanvasList;
};

#endif
