/***************************************************************************
              colorpopup.h  -  description
                 -------------------
    begin                : Mon Agu 11 2003
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
#include <qpixmap.h>
#include <qtextedit.h>
#include <qtoolbutton.h>
#include <qlabel.h>

class CColorSwatches;
class CToolButton;

class CColorPopup:public QWidget
{

    Q_OBJECT
public:
    CColorPopup (QWidget * parent = 0, const char *name = 0, WFlags f =0);
    ~CColorPopup ();
    CColorSwatches * s;
    QPixmap strokpix;
    QPixmap fillpix;
    QTextEdit * colorName;
    QLabel * colorShower;
    QPixmap mcursor;

protected:
    void mouseMoveEvent (QMouseEvent * e);
    void mousePressEvent (QMouseEvent *);
    void showEvent (QShowEvent *);
    void hideEvent (QHideEvent *);

public slots:
    void slotColordialog ();
};

#endif	/*

*/
