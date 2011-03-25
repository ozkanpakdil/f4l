/***************************************************************************
              ccanvas.h  -  description
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

#ifndef CCANVAS_H
#define CCANVAS_H

#include <qwidget.h>
#include <qcanvas.h>

/**we may or will need some other functionality from canvas class
  *@author özkan pakdil
  */
class CCanvas:public QCanvas
{
Q_OBJECT public:
    CCanvas (QWidget * parent = 0, const char *name = 0);
    ~CCanvas ();
};

#endif
