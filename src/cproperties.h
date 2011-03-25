/***************************************************************************
              cproperties.h  -  description
                 -------------------
    begin                : Sat Jun 14 2003
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

#ifndef CPROPERTIES_H
#define CPROPERTIES_H

#include <qwidget.h>
#include <qtextedit.h>
#include "ccolorswatches.h"
#include "cfontproperties.h"
#include "cbrushproperties.h"

/**for bottom dockable part
turkish: bu class cizilmekte olan veya secilmis olan objeye ait propertiesin altdaki dock windowda
gosterilmesini saglayacak. bu durumda cizilen objelerin burda gosterilen propertiese sahip
olmasi gerek.
english: for properties window down there.
  *@author özkan pakdil
  */
class CProperties:public QWidget
{
Q_OBJECT public:
    CProperties (QWidget * parent = 0, const char *name = 0);
    ~CProperties ();
    /** when user clicks on text tool then peoperties widget should show font things and set them when user make any changes on them. */
    void showFontProperties ();
    /** this function hides all font properties elements. when user out of text tool mode. */
    void hideFontProperties ();
    void showBrushProperties ();
    void hideBrushProperties ();

    CFontProperties *fontProperties;
    CBrushProperties *brushProperties;
};

#endif
