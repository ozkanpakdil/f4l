/***************************************************************************
              clistbox.h  -  description
                 -------------------
    begin                : Mon Jun 9 2003
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

#ifndef CLISTVIEW_H
#define CLISTVIEW_H

#include <q3listview.h>
#include <qicon.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QDragMoveEvent>
#include <QDragLeaveEvent>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QPixmap>

class CTimeLine;

///   turkish: bu class sayesinde listbox daki fontun ayarlanmasi ve pixmaplerin yerlestirilmesi islemi
///   yapilacak. click islemleri yakalanip flash da oldugu gibi table in o satirinin secilmesi
///   islemleri yapilacak.
///   english: with this class listbox fonts will be configured and pixmaps will be set.
///   @author özkan pakdil
class CListView:public Q3ListView
{

    Q_OBJECT
public:
    CListView (QWidget * parent = 0, const char *name = 0, Qt::WFlags f =0);
    ~CListView ();
    CTimeLine * dad;

        //void paintEvent( QPaintEvent * );
protected:
    void contentsDragEnterEvent (QDragEnterEvent * e);
    void contentsDragMoveEvent (QDragMoveEvent * e);
    void contentsDragLeaveEvent (QDragLeaveEvent * e);
    void contentsDropEvent (QDropEvent * e);
    void contentsMouseMoveEvent (QMouseEvent * e);
    void contentsMousePressEvent (QMouseEvent * e);
    void contentsMouseReleaseEvent (QMouseEvent * e);
    QPoint presspos;
    bool mousePressed;
    QIcon _0;
    QIcon _1;
    QIcon _2;
    QIcon _3;
    QIcon _4;
    QPixmap pencil;
};

#endif	/*

*/
