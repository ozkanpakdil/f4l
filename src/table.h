/***************************************************************************
              table.h  -  description
                 -------------------
    begin                : Sat Jun 7 2003
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

#ifndef CTABLE_H
#define CTABLE_H

#include <qwidget.h>
#include <q3table.h>
//Added by qt3to4:
#include <QMouseEvent>

class CTimeLine;

/**this is our table class. I made this beacuse we want to handle mouse clicks and something like that.
  *@author özkan pakdil
  bu table class i sayesinde table daki secim islemleri ayarlanacak. click eventleri yakalanip
  flash daki benzeri sekile donusturulecek. toplu secim ve toplu move islemleri buradan islenecek
  */
class CTable:public Q3Table
{
    Q_OBJECT
public:
    //  CTable(){};
    CTable (int numR, int numC, QWidget * parent, const char *name);
    ~CTable ();

protected:
    void contentsMousePressEvent (QMouseEvent *);
    void contentsMouseReleaseEvent (QMouseEvent * e);
    void contentsMouseMoveEvent (QMouseEvent * e);
    void clicked (int row, int col, int button, const QPoint & mousePos);
    void contextMenuRequested (int row, int col, const QPoint & pos);
    void pressed (int row, int col, int button, const QPoint & mousePos);
        //QDragObject * dragObject () ;

public:
        //if selection has made multiple then we should initialize
        //that 2 down variables one by one and refresh between steps.
        int selectedLastColNum;	//this holds selected or not last col num in selected area.
        int selectedLastRowNum;	//this holds selectedLastColNum's row.
    CTimeLine *dad;
    bool LeftClick;

protected:
    int defColumnWidth;
    int defRowHeight;
	
public slots:
    void slotInsertFrame ();
    void slotRemoveFrame ();
    void slotCreateMotionTween();
};

#endif	

