/***************************************************************************
              csmalcolorboxes.h  -  description
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

#ifndef CSMALCOLORBOXES_H
#define CSMALCOLORBOXES_H

#include <qwidget.h>

class CColorSwatches;
/// this is using for that small boxes in color swatches.
/// @author özkan pakdil
class CSmalColorBoxes:public QWidget
{
Q_OBJECT public:
    CSmalColorBoxes (QWidget * parent = 0, const char *name = 0, QColor r =
                 QColor (0, 0, 0), CColorSwatches * rp = 0);
    ~CSmalColorBoxes ();
    CColorSwatches *realp;

protected:
    void enterEvent (QEvent *);
    void leaveEvent (QEvent *);
        //void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent (QMouseEvent *);
        //QColor c;
};

#endif
