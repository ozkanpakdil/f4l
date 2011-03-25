/***************************************************************************
              cproperties.cpp  -  description
                 -------------------
    begin                : Sat Jun 14 2003
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

#include "cproperties.h"
#include <qlayout.h>

CProperties::CProperties (QWidget * parent, const char *name):
        QWidget (parent, name)
{
    QVBoxLayout *topLayout = new QVBoxLayout (this);
    /* txt=new QTextEdit(this);
       txt->append("alo"); */
    fontProperties = new CFontProperties (this);
    fontProperties->hide ();
    brushProperties = new CBrushProperties (this, "brushproperties");
    brushProperties->move (20, 20);
    brushProperties->resize (300, 20);
    brushProperties->hide ();
        //s->show();
        // qDebug("sonuc :"+QString::number(s->isVisible()));
    topLayout->addWidget (fontProperties);
        //topLayout->addWidget(brushProperties);
}

CProperties::~CProperties ()
{}

/** when user clicks on text tool then peoperties widget should show font things and set them when user make any changes on them. */
void CProperties::showFontProperties ()
{
    fontProperties->show ();
        //fontProperties->move(mapToGlobal(QPoint(0,0)));
        //qDebug("x: %d  y: %d",fontProperties->x(),fontProperties->y());
        //resize(size()+QSize(0,20));
}

/** this function hides all font properties elements. when user out of text tool mode. */
void CProperties::hideFontProperties () {
    fontProperties->hide ();
}

void CProperties::showBrushProperties () {
    brushProperties->show ();
}

void CProperties::hideBrushProperties () {
    brushProperties->hide ();
}
