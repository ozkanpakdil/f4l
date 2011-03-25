/***************************************************************************
              cbrushproperties.h  -  description
                 -------------------
    begin                : Thu Sep 18 2003
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

#ifndef CBRUSHPROPERTIES_H
#define CBRUSHPROPERTIES_H

#include <qwidget.h>
#include <qlineedit.h>

/**this class holds a textbox for entering brush tolls brush size.
  *@author Özkan Pakdil
  */
//class QLineEdit;

class CBrushProperties:public QWidget
{
Q_OBJECT public:
    CBrushProperties (QWidget * parent = 0, const char *name = 0);
    ~CBrushProperties ();
    QLineEdit *textBox1;
};

#endif
