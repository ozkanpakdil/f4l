/***************************************************************************
              clistboxitem.h  -  description
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

#ifndef CLISTVIEWITEM_H
#define CLISTVIEWITEM_H

#include <q3listview.h>

/** used for showing pixmaps in items inside timeLine's listview.
  *@author özkan pakdil
  */
class CListViewItem:public /*QObject, */ Q3ListViewItem
{
        //Q_OBJECT
public:
    CListViewItem (Q3ListView * parent = 0, QString label1 = QString::null,
               QString label2 = QString::null, QString label3 =
                   QString::null, QString label4 =
                   QString::null, QString label5 =
                   QString::null, QString label6 =
                   QString::null, QString label7 =
                   QString::null, QString label8 = QString::null);

        // CListViewItem( QListView * parent = 0,QString label1=NULL ):
        // QListViewItem(parent,label1){setHeight(15);}
        //CListBoxItem();
    ~CListViewItem ();

    void setup (){
        setExpandable (TRUE);
        setHeight (20);
                //qDebug("%d",height());
                //QListViewItem::setup();
    }
	
	int m_Row;

        //    int width( const QListBox* ) ;
        //    int height( const QListBox* ) ;
        //    void paint( QPainter * );

};
#endif	/*

*/
