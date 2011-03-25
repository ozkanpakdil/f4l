/***************************************************************************
              ccolorswatches.cpp  -  description
                 -------------------
    begin                : Tue Jul 1 2003
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

#include "ccolorswatches.h"
#include "f4lm.h"
#include <qlayout.h>

#include "cursor/eye_dropper_tool.xpm"

CColorSwatches::CColorSwatches (QWidget * parent, const char *name,F4lmApp * rp)
:QWidget (parent, name)
{
    realp = rp;
    setBackgroundColor (QColor (0, 0, 0));
    QPixmap mcursor = QPixmap ((const char **) eye_dropper_tool_xpm);
    setCursor (QCursor (mcursor, 1, 15));
    CSmalColorBoxes * renkDizisi[21][12];
        //QVBoxLayout *topLayout=new QVBoxLayout(this);
    
	for (int j = 0; j < 12; j++)
        for (int i = 0; i < 21; i++) {
            renkDizisi[i][j] =new CSmalColorBoxes (this, "kutu", QColor (0, 0, 0), this);
            renkDizisi[i][j]->move (i * 10 + 1, j * 10 + 1);
            renkDizisi[i][j]->setMinimumSize (9, 9);
            renkDizisi[i][j]->setMaximumSize (9, 9);
                        //renkDizisi[i][j]->setBackgroundColor(QColor(rand()%32*8,rand()%32*8,rand()%32*8));
            if (i == 0 && j <= 5)
                renkDizisi[i][j]->setBackgroundColor (QColor ((j * 51), (j * 51), (j * 51)));
            if (i == 0 && j == 6)
                renkDizisi[i][j]->setBackgroundColor (QColor (255, 0, 0));
            if (i == 0 && j == 7)
                renkDizisi[i][j]->setBackgroundColor (QColor (0, 255, 0));
            if (i == 0 && j == 8)
                renkDizisi[i][j]->setBackgroundColor (QColor (0, 0, 255));
            if (i == 0 && j == 9)
                renkDizisi[i][j]->setBackgroundColor (QColor (255, 255, 0));
            if (i == 0 && j == 10)
                renkDizisi[i][j]->setBackgroundColor (QColor (0, 255, 255));
            if (i == 0 && j == 11)
                renkDizisi[i][j]->setBackgroundColor (QColor (255, 0, 255));
            if (i == 1)
                renkDizisi[i][j]->setBackgroundColor (QColor (0, 0, 0));
            if (i == 20)
                renkDizisi[i][j]->setBackgroundColor (QColor (0, 0, 0));
                        //if(i==2 && j<6)renkDizisi[i][j]->setBackgroundColor(QColor(0,0,(j*51)));
            if (i >= 2 && i <= 7 && j >= 0 && j <= 5)
                renkDizisi[i][j]->setBackgroundColor (QColor (0, ((i - 2) * 51), j * 51));
            if (i >= 2 && i <= 7 && j >= 6 && j <= 11)
                renkDizisi[i][j]->setBackgroundColor (QColor (153, ((i - 2) * 51), (j - 6) * 51));
            if (i >= 8 && i <= 13 && j >= 0 && j <= 5)
                renkDizisi[i][j]->setBackgroundColor (QColor (51, ((i - 8) * 51), j * 51));
            if (i >= 8 && i <= 13 && j >= 6 && j <= 11)
                renkDizisi[i][j]->setBackgroundColor (QColor (204, ((i - 8) * 51), (j - 6) * 51));
            if (i >= 14 && i <= 19 && j >= 0 && j <= 5)
                renkDizisi[i][j]->setBackgroundColor (QColor (102, ((i - 14) * 51), j * 51));
            if (i >= 14 && i <= 19 && j >= 6 && j <= 11)
                renkDizisi[i][j]->setBackgroundColor (QColor (255, ((i - 14) * 51), (j - 6) * 51));
            
			renkDizisi[i][j]->show ();
                        //topLayout->addWidget(renkDizisi[i][j]);
        }
    show ();
}

CColorSwatches::~CColorSwatches ()
{
}

/** this carries the color we have click on it */
void CColorSwatches::slotClick (QColor r){
    realp->setDefObjCOLOR (r);
}
