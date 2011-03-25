/***************************************************************************
              cbrushproperties.cpp  -  description
                 -------------------
    begin                : Thu Sep 18 2003
    copyright            : (C) 2003 by Özkan Pakdil
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

#include "cbrushproperties.h"
#include <qlayout.h>
#include <qlabel.h>

CBrushProperties::CBrushProperties (QWidget * parent, const char *name):
        QWidget (parent, name)
{
    QHBoxLayout *topLayout = new QHBoxLayout (this);
    QLabel *title = new QLabel (this);
    title->setText ("Brush width :");
    topLayout->addWidget (title);

    textBox1 = new QLineEdit (this, "brustoolsizechooser");
    textBox1->setText ("10");
    textBox1->show ();
    textBox1->setMaximumWidth (50);

    topLayout->addWidget (textBox1);

    QLabel *label1 = new QLabel (this);
    label1->setText (" just enter width walue end start to draw.");
    label1->adjustSize ();
    topLayout->addWidget (label1);
        //  QPushButton *pushButton1=new QPushButton(this);
        //  pushButton1->setText("Set width");

        //  connect(pushButton1,SLOT(clicked()),this,SIGNAL());

}

CBrushProperties::~CBrushProperties ()
{}
