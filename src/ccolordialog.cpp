/***************************************************************************
              ccolordialog.cpp  -  description
                 -------------------
    begin                : Wed Jun 11 2003
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

#include "ccolordialog.h"
#include "f4lm.h"
#include <qcolordialog.h>
#include <qbuttongroup.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include "csmalcolorboxes.h"

CColorDialog::CColorDialog (QWidget * parent, const char *name, F4lmApp * p):
        QWidget (parent, name)
{
        //QColor renk;
        //renk=QColorDialog::getColor(renk,this);
    realp = p;

    QVBoxLayout *topLayout = new QVBoxLayout (this);

    QButtonGroup *ToolsButtonGroup =new QButtonGroup (this, "ToolsButtonGroup");
    ToolsButtonGroup->setGeometry (QRect (150, 70, 71, 291));
    ToolsButtonGroup->setLineWidth (0);
    ToolsButtonGroup->setTitle (trUtf8 (""));

    QToolButton *ToolButton1 =new QToolButton (ToolsButtonGroup, "ToolButton1");
    ToolButton1->setGeometry (QRect (0, 10, 30, 30));
    ToolButton1->setText (trUtf8 ("CC"));
    connect (ToolButton1, SIGNAL (clicked ()), this,SLOT (slotColorChooser ()));

    QToolButton *ToolButton2 =new QToolButton (ToolsButtonGroup, "ToolButton2");
    ToolButton2->setGeometry (QRect (30, 10, 30, 30));
    ToolButton2->setText (trUtf8 ("..."));

        //CColorSwatches* s=new CColorSwatches(this,"color_swatches",p);
    topLayout->addWidget (ToolsButtonGroup);
        //topLayout->addWidget(s);
}

CColorDialog::~CColorDialog ()
{}

/** No descriptions */
void
CColorDialog::slotColorChooser ()
{
    QColor renk;
    renk = QColorDialog::getColor (renk, this);
    realp->setDefObjCOLOR (renk);
}

/** No descriptions */
void
CColorDialog::slotsetDefColor (QColor r)
{
    realp->setDefObjCOLOR (r);
}
