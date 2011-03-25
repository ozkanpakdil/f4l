/***************************************************************************
              table.cpp  -  description
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

#include "table.h"
#include "timeline.h"
#include "f4lm.h"
#include "f4lmview.h"
#include <qpainter.h>
#include <qpopupmenu.h>
//#include "defcel5.xpm"

CTable::CTable (int numR, int numC, QWidget * parent = 0, const char *name = 0)
:QTable (numR, numC, parent,name)
{
    setFocusPolicy (QWidget::StrongFocus);


        // QFont f( "SansSerif", 6, QFont::Normal );
        //f.setPixelSize(12);
        //f.setPointSize(10);
        //f.setWeight(1);
        // setFont( f );
    setHScrollBarMode (QScrollView::AlwaysOff);
    setVScrollBarMode (QScrollView::AlwaysOff);
    setReadOnly (true);

    /* QPainter paint=new QPainter( this );
       paint->setPen( Qt::blue );
       QColorGroup cg=new QColorGroup (); */
    QHeader * hor = horizontalHeader ();
    QHeader * ver = verticalHeader ();
    hor->hide ();
    ver->hide ();
    setLeftMargin (0);
    setTopMargin (0);
    for (int i = 0; i < numC; i++) {
        setColumnWidth (i, 8);
    }
    setRowHeight (0, 20);
    setShowGrid (false);

        //setGreyParts();
    dad = (CTimeLine *) parentWidget ()->parentWidget ()->parentWidget ();
    setDragEnabled (true);
    setMouseTracking (true);
        //setFocus();
}

CTable::~CTable ()
{
}

void CTable::contentsMousePressEvent (QMouseEvent * e)
{
    QTable::contentsMousePressEvent (e);
    dad->timeLineRightTopLabel->mousePressEvent (e);
    if (e->button () == RightButton){
        QPopupMenu * timeLineRightClickMenu = new QPopupMenu (this);
        /*		renkicin->insertItem ("Color chooser", this, SLOT (finish_element ()));
        		renkicin->insertItem ("Red", this, SLOT (makeElementRed ()));
        		renkicin->insertItem ("Green", this, SLOT (makeElementGreen ()));
        		renkicin->insertItem ("Blue", this, SLOT (makeElementBlue ()));
        		renkicin->insertSeparator();
        		renkicin->insertItem ("CleaR", this, SLOT (deleteElement ()));	*/
        /*		QFont f( "Sans", 8, QFont::Normal );
        		renkicin->setFont(f); */
        timeLineRightClickMenu->insertItem (tr ("Create Motion Tween"),this,SLOT (slotCreateMotionTween ()));
        timeLineRightClickMenu->insertSeparator ();
        timeLineRightClickMenu->insertItem (tr ("Insert Frame"), this,SLOT (slotInsertFrame ()));
        timeLineRightClickMenu->insertItem (tr ("Remove Frames"), this,SLOT (slotRemoveFrame ()));
        timeLineRightClickMenu->insertSeparator ();
        timeLineRightClickMenu->insertItem (tr ("Insert Keyframe"));
        timeLineRightClickMenu->insertItem (tr ("Insert Blank Keyframe"));
        timeLineRightClickMenu->insertItem (tr ("Clear Keyframe"));
        timeLineRightClickMenu->insertItem (tr ("Convert to Keyframe"));
        timeLineRightClickMenu->insertItem (tr ("Convert to Blank Keyframe"));
        timeLineRightClickMenu->insertSeparator ();
        timeLineRightClickMenu->insertItem (tr ("Cut Frames"));
        timeLineRightClickMenu->insertItem (tr ("Copy Frames"));
        timeLineRightClickMenu->insertItem (tr ("Paste Frames"));
        timeLineRightClickMenu->insertItem (tr ("Clear Frames"));
        timeLineRightClickMenu->insertItem (tr ("Select All Frames"));
        timeLineRightClickMenu->insertSeparator ();
        timeLineRightClickMenu->insertItem (tr ("Reverse Frames"));
        timeLineRightClickMenu->insertItem (tr ("Synchronize Symbols"));
        timeLineRightClickMenu->insertSeparator ();
        timeLineRightClickMenu->insertItem (tr ("Actions"));
        timeLineRightClickMenu->insertSeparator ();
        int id =timeLineRightClickMenu->insertItem (tr ("Properties"), (QObject *) dad->dad,SLOT (slotWindowProperities ()));
        if (dad->dad->propertiesDockableWindow->isVisible ())
            timeLineRightClickMenu->setItemChecked (id, true);

        timeLineRightClickMenu->popup (mapToGlobal (e->pos ()));
        timeLineRightClickMenu->exec ();
        timeLineRightClickMenu->~QPopupMenu ();
    }


    if (e->button () == LeftButton) {
                //QPoint p=mapToGlobal (e->pos());
                //      dad->timeLineRightTopLabel->mousePressEvent(e);
        dad->dad->slotCurrentView ()->slotShowCanvas (currentRow (),currentColumn ());
        QPoint p = e->pos ();
        p.setX (dad->timeLineListbox->x () + 10);
        dad->timeLineListbox->setSelected (dad->timeLineListbox->itemAt (p),true);
        LeftClick = true;
    }

}

void CTable::clicked (int row, int col, int button, const QPoint & mousePos)
{
    QTable::clicked (row, col, button, mousePos);
    QMouseEvent * e =new QMouseEvent (QEvent::MouseButtonPress, mousePos, button, 0);
    dad->timeLineRightTopLabel->mousePressEvent (e);
}

void CTable::contextMenuRequested (int row, int col, const QPoint & pos)
{
    QTable::contextMenuRequested (row, col, pos);
    QMouseEvent * e = new QMouseEvent (QEvent::MouseButtonPress, pos, 0, 0);
    dad->timeLineRightTopLabel->mousePressEvent (e);
}

void CTable::pressed (int row, int col, int button, const QPoint & mousePos)
{
    QMouseEvent * e =new QMouseEvent (QEvent::MouseButtonPress, mousePos, button, 0);
    dad->timeLineRightTopLabel->mousePressEvent (e);
}

void CTable::slotInsertFrame (){
    dad->slotInsertFrame (currentRow (), currentColumn ());
}

void CTable::contentsMouseReleaseEvent (QMouseEvent * e){
    QTable::contentsMouseReleaseEvent (e);
    dad->timeLineRightTopLabel->mouseReleaseEvent (e);
    LeftClick = false;
}

void CTable::contentsMouseMoveEvent (QMouseEvent * e){
    QTable::contentsMouseMoveEvent (e);
    dad->timeLineRightTopLabel->mouseMoveEvent (e);
    if (LeftClick) {
        dad->dad->slotCurrentView ()->slotShowCanvas (currentRow (),currentColumn ());
    }
}

void CTable::slotRemoveFrame (){
    dad->slotRemoveFrame (currentRow (), currentColumn ());
}

/*QDragObject * CTable::dragObject () {
	return 0;
} */


/*!
    \fn CTable::slotCreateMotionTween()
 */
void CTable::slotCreateMotionTween()
{
    /// @todo implement me
}
