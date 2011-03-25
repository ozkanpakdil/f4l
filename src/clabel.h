/***************************************************************************
              clabel.h  -  description
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

#ifndef CLABEL_H
#define CLABEL_H

#include <qwidget.h>
class CTimeLine;

/**
english: this produced because of mouse click handling. and making same look like
M.flash for time table.
turkish: bu class sayesinde time tabledaki click event leri yakalanacak ve islenecek.
   flash da oldugu gibi layerlar¹n toptan yazmaya kitlenmesi ve benzeri islemler icin.
  *@author özkan pakdil
  */
class CLabel:public QWidget
{
Q_OBJECT public:
        //CLabel (QWidget *buddy,const QString &text, QWidget *parent, const char *name=0, WFlags f= 0);
    CLabel (QWidget * parent, const char *name = 0);
    ~CLabel ();
        //signals: // Signals
    /** No descriptions */
    void paintEvent (QPaintEvent *);
    void mousePressEvent (QMouseEvent * e);
    void mouseReleaseEvent (QMouseEvent * e);
    void mouseMoveEvent (QMouseEvent * e);
    void setText (QString);
    int currentNo ();
    void setNo (int);
    void setWidthMine (int);
    int kutuNo;
    CTimeLine * dad;

protected:
    QString str, nameT;
    bool leftClick;
    unsigned int leftClickX;
    int widthMine;
	
signals:
    void valueChanged ();
};

#endif
