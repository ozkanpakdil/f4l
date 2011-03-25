/***************************************************************************
              cbase.h  -  description
                 -------------------
    begin                : Wed Jul 2 2003
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

#ifndef CBASE_H
#define CBASE_H

#include <qscrollview.h>

/**this is the class used for scroll jobs
tabletopRightLable
  *@author özkan pakdil
  */
class CBase:public QScrollView
{
public:
    CBase (QWidget * parent = 0, const char *name = 0, WFlags f = 0);
    ~CBase ();
};

#endif
