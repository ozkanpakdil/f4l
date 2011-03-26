/***************************************************************************
              clayer.cpp  -  description
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

#include "clayer.h"
#include "ccanvas.h"
#include "canvasItem.h"
//Added by qt3to4:
#include <Q3PtrList>

CLayer::CLayer(QWidget *parent, const char *name) : QObject (parent, name)
{
    pCanvasItemList = new Q3PtrList < CCanvasItem >;
    pCanvasList = new Q3PtrList < CCanvas >;
}

CLayer::~CLayer ()
{}
