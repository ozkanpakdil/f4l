/***************************************************************************
              clistbox.cpp  -  description
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

#include "clistbox.h"
#include "timeline.h"
#include <qpainter.h>
#include <qheader.h>
#include <qtable.h>
#include "cursor/layer_pic.xpm"
#include "cursor/written_pic.xpm"
#include "cursor/outline_pic.xpm"
#include "cursor/goz_pic.xpm"
#include "cursor/kilit_pic.xpm"

CListView::CListView (QWidget * parent, const char *name, WFlags f)
:QListView (parent, name, f)
{
        //alttaki satir bütün satirin secilmesini sagliyor diger sekilde
        //sadece ilk kolondaki elemani secer.
    dad = (CTimeLine *) parentWidget ()->parent ()->parent ();

        //qDebug(dad->name());
    setAllColumnsShowFocus (TRUE);

    /*QFont fa( "SansSerif", 10, QFont::Normal );
           //f.setPixelSize(12);
           //f.setPointSize(10);
           //f.setWeight(1);
       setFont( fa );   */
        //    setScrollBar(false);
    setHScrollBarMode (QScrollView::AlwaysOff);

        //setVariableHeight(true);
        //setVariableWidth ( true );

        //setRowMode(QListBox::FitToHeight);

    _0 = QIconSet (QPixmap ((const char **) layer_pic_xpm));
    _1 = QIconSet (QPixmap ((const char **) written_pic_xpm));
    _2 = QIconSet (QPixmap ((const char **) goz_pic_xpm));
    _3 = QIconSet (QPixmap ((const char **) kilit_pic_xpm));
    _4 = QIconSet (QPixmap ((const char **) outline_pic_xpm));
    pencil = QPixmap ((const char **) written_pic_xpm);
    addColumn (_0, "");
    addColumn ("");
    addColumn (_1, "");
    addColumn (_2, "");
    addColumn (_3, "");
    addColumn (_4, "");

    setColumnWidth (0, _0.pixmap ().width () + 1);
    setColumnWidth (2, _0.pixmap ().width () + 7);
    setColumnWidth (3, _0.pixmap ().width () + 7);
    setColumnWidth (4, _0.pixmap ().width () + 7);
    setColumnWidth (5, _0.pixmap ().width () + 7);

    setColumnWidthMode (0, QListView::Manual);
    setColumnWidthMode (2, QListView::Manual);
    setColumnWidthMode (3, QListView::Maximum);
    setColumnWidthMode (4, QListView::Maximum);
    setColumnWidthMode (5, QListView::Maximum);

    setResizeMode (QListView::LastColumn);
    QHeader * h = header ();
        //h->setMinimumHeight(_0.pixmap().height()+10);
    h->hide ();
	
}

CListView::~CListView ()
{
}

/*void CListView::paintEvent(QPaintEvent *){
  QPainter p(this);
  p.setPen(Qt::black);
  QFont f( "Helvetica", 8, QFont::Normal );
  p.setFont(f);
  p.drawLine(0,0,100,100);
for ( unsigned int i = 0; i < count(); i++ ){
paintCell (  &p,i, 0);
}
 
}     */

void CListView::contentsDragEnterEvent (QDragEnterEvent * e)
{}

void CListView::contentsDragMoveEvent (QDragMoveEvent * e)
{}

void CListView::contentsDragLeaveEvent (QDragLeaveEvent * e)
{}

void CListView::contentsDropEvent (QDropEvent * e)
{}

void CListView::contentsMouseMoveEvent (QMouseEvent * e)
{}

void CListView::contentsMousePressEvent (QMouseEvent * e)
{
        //this clear all pencil pixmaps from items then write the clicked
        //pencil pixmap
    QPoint k (contentsToViewport (e->pos ()));
    QListViewItem * tempit = itemAt (k);
    if (tempit) {
        QListViewItem * item = firstChild ();
        for (; item; item = item->nextSibling ()) {
            item->setPixmap (2, NULL);
        }
        QPoint p (contentsToViewport (e->pos ()));
        QListView::contentsMousePressEvent (e);
        QListViewItem * i = itemAt (p);
        if (i) {
                        // if the user clicked into the root decoration of the item, don't try to start a drag!
            if (p.x () >header ()->cellPos (header ()->mapToActual (0)) +
                    treeStepSize () * (i->depth () +(rootIsDecorated ()? 1 : 0)) +
                    itemMargin ()
                    ||
                    p.x () < header ()->cellPos (header ()->mapToActual (0))) {
                presspos = e->pos ();
                mousePressed = TRUE;
            }
			
            i->setPixmap (2, pencil);
            int j = 0;
            QListViewItem * item = firstChild ();
            for (int counter = 0; item; item = item->nextSibling (), counter++) {
                if (i == item) {
                    j = counter;
                    break;
                }
            }
			
            dad->timeLineTable->clearSelection (true);
            QTableSelection sel;
            sel.init (j, 0);
                        //CTimeLineDataStructure *temp=
            sel.expandTo (j,dad->layerFrames->at (j)->frames->last ()->tableItemNo);
            dad->timeLineTable->addSelection (sel);
                        //              dad->timeLineTable->update();
        }
                //qDebug(QString::number(i->height()));
    }
}

void CListView::contentsMouseReleaseEvent (QMouseEvent * e)
{}
