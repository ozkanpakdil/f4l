/***************************************************************************
              ctableitem.cpp  -  description
                 -------------------
    begin                : Sat Jun 28 2003
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

#include "ctableitem.h"
#include <qpainter.h>

CTableItem::CTableItem (QTable * parent, EditType et, const QString & text):
        QTableItem (parent, et, text)
{
    layerChooser = filled = empty_keyframe = ready = keyFrameEnd =
                    keyFrameStart = false;
}

CTableItem::~CTableItem ()
{
}

void CTableItem::paint (QPainter * p, const QColorGroup & cg, const QRect & cr,bool selected)
{
    QTableItem::paint (p, cg, cr, selected);
        // QColorGroup g( cg );
        //p->setBrush(QColor(255,0,0));
        //      p->setBackgroundColor(QColor(255,0,0));

        //p->drawRect(0,0,table()->columnWidth(0),table()->rowHeight(0));
    if (ready) {
        if (keyFrameStart) {
            p->drawEllipse (table ()->columnWidth (0) - 3,
                    table ()->rowHeight (0) - 5, -5, -5);
        }
        else if (keyFrameEnd) {
            p->drawRect (table ()->columnWidth (0) - 3,
                     table ()->rowHeight (0) - 3, -5, -8);
            p->setPen (Qt::black);
            p->drawLine (table ()->columnWidth (0) - 1, 0,
                     table ()->columnWidth (0) - 1,
                     table ()->rowHeight (0));
        }

        if (filled) {//when user draw something on selected layer.
			p->setBrush (QColor (234, 232, 228));
			p->setPen (QColor (234, 232, 228));
			p->drawRect (0, 0, table ()->columnWidth (0), table ()->rowHeight (0));
        }
        p->setPen (QColor (212, 208, 200));
        p->drawLine (0, 0, 0, 2);
        p->drawLine (0, table ()->rowHeight (0), 0,
                 table ()->rowHeight (0) - 2);
        p->setPen (Qt::black);
        p->drawLine (0, 0, table ()->columnWidth (0), 0);
        p->drawLine (0, table ()->rowHeight (0) - 1, table ()->columnWidth (0),
                 table ()->rowHeight (0) - 1);
    }
    else if ((frameNo % 5 == 4)) {
        p->setBrush (QColor (234, 232, 228));
        p->drawRect (0, 0, table ()->columnWidth (0) + 1,
                 table ()->rowHeight (0) + 1);
                //212,208,200
        p->setPen (QColor (212, 208, 200));
        p->drawRect (0, 0, table ()->columnWidth (0), table ()->rowHeight (0));
    } else {
                //draws normal border for all cells
        QPen cp (QColor (212, 208, 200));
        cp.setWidth (0);
        p->setPen (cp);
        p->drawLine (table ()->columnWidth (0) - 1, 0,
                 table ()->columnWidth (0) - 1, table ()->rowHeight (0));
        p->drawLine (0, table ()->rowHeight (0) - 1,
                 table ()->columnWidth (0) - 1,
                 table ()->rowHeight (0) - 1);
    }

        //if layer chooser on me then I should draw middle line inside the cell
    if (layerChooser) {
        p->setPen (QColor (255, 0, 0));
        p->drawLine (table ()->columnWidth (0) / 2, 0,
                 table ()->columnWidth (0) / 2, table ()->rowHeight (0));
    }
}
