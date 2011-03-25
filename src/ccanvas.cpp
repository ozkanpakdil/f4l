/***************************************************************************
              ccanvas.cpp  -  description
                 -------------------
    begin                : Thu Jul 3 2003
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

#include "ccanvas.h"

CCanvas::CCanvas (QWidget * parent, const char *name)
:QCanvas (parent, name)
{
    setDoubleBuffering (true);
}

CCanvas::~CCanvas ()
{
}
