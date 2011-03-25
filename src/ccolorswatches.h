/***************************************************************************
              ccolorswatches.h  -  description
                 -------------------
    begin                : Tue Jul 1 2003
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

#ifndef CCOLORSWATCHES_H
#define CCOLORSWATCHES_H

#include "csmalcolorboxes.h"
#include <qwidget.h>

class F4lmApp;
/**this is color swatches from flash that has same title in GUI
  *@author özkan pakdil
  */
class CColorSwatches:public QWidget
{
Q_OBJECT public:
    F4lmApp * realp;
    CColorSwatches (QWidget * parent = 0, const char *name = 0, F4lmApp * rp =0);
    ~CColorSwatches ();

public slots:			// Public slots
    /** this carries the color we have click on it */
    void slotClick (QColor);
};

#endif
