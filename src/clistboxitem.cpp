/***************************************************************************
              clistboxitem.cpp  -  description
                 -------------------
    begin                : Mon Jun 9 2003
    copyright            : (C) 2003 by �zkan pakdil
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

#include "clistboxitem.h"
#include <qpainter.h>
#include <qstyle.h>
//#include <iostream.h>
#include <qnamespace.h>

CListViewItem::CListViewItem (Q3ListView * parent, QString label1,
                  QString label2, QString label3, QString label4, QString label5,
                  QString label6, QString label7, QString label8)
        :
        Q3ListViewItem (parent, label1, label2, label3, label4, label5, label6, label7,
                   label8)
{
        //      cout<<listBox()->name()<<endl;
        //        cout<<"alo"<<endl;
        //paint(new QPainter(this));
        //listBox()->repaint();
}

//CListBoxItem::CListBoxItem():QListBoxItem(){setCustomHighlighting( true );}

CListViewItem::~CListViewItem ()
{
}

/*
void CListViewItem::paint(QPainter *painter){
	//painter->setBackgroundMode( Qt::OpaqueMode );
 painter->setBackgroundColor(QColor(212,207,201));
painter->setPen(Qt::black);
painter->setBrush(QBrush (QColor(100,100,100)) );
        //painter->drawLine( 0,0,100,100 );      // drawing code
QFont f( "Helvetica", 8, QFont::Normal );
  painter->setFont(f);
  int j=1,i;
//for(i=0;i<width(listBox());i=i+1,j++)
		painter->drawText(0,0,"asa");
//painter->drawRect(0,0,5,5);
 
   bool in_list_box = listBox() && listBox()->viewport() == painter->device();
 
    QRect r ( 0, 0, width( listBox() ), height( listBox() ) );
	//painter->drawText(r, Qt::AlignCenter , "hadi");
    if ( in_list_box && isSelected() ){
    painter->eraseRect( r );
		for(i=0;i<width(listBox());i=i+1,j++)
		painter->drawText(i,height(listBox())-5,QString::number(j));
	}
    //painter->fillRect( 0, 0, width( listBox() ) , height( listBox() ) , Qt::red );
    if ( in_list_box && isCurrent() ){
		painter->eraseRect( r );
    listBox()->style().drawPrimitive( QStyle::PE_FocusRect, painter, r, listBox()->colorGroup() );
		for(i=0;i<width(listBox());i=i+1,j++)
		painter->drawText(i,height(listBox())-5,QString::number(j));
	}      
     //cout<<indis()<<endl;
	
//QListBoxItem::paint(painter);
} */
/*
   int CListViewItem::width( const QListBox* ){
   return 50;//listBox()->maxItemWidth();
   }
   int CListViewItem::height( const QListBox* ){
   return 10;//listBox()->itemHeight ();
   }
   
   
   int CListViewItem::indis(){
   return 10;//listBox()->itemHeight ();
   }
 */





