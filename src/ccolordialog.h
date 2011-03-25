/***************************************************************************
              ccolordialog.h  -  description
                 -------------------
    begin                : Wed Jun 11 2003
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

#ifndef CCOLORDIALOG_H
#define CCOLORDIALOG_H

#include <qwidget.h>
#include <qdialog.h>

class F4lmApp;
/**Color Mixer
turkish: bu sinif flash da bulunan color mixer özelligini bizim f4l de gostermemizi saglayacak.
english: this class makes color mixer same as in macromedia flash.
  *@author özkan pakdil
  */
class CColorDialog:public QWidget
{
Q_OBJECT public:
    CColorDialog (QWidget * parent = 0, const char *name = 0, F4lmApp * p =
                  0);
    ~CColorDialog ();
    F4lmApp *realp;
	
public slots:			// Public slots
    /** No descriptions */
    void slotColorChooser ();
    /** No descriptions */
    void slotsetDefColor (QColor);
};

#endif
