/***************************************************************************
              csmalcolorboxes.cpp  -  description
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

#include "csmalcolorboxes.h"
#include "ccolorswatches.h"
#include <qpainter.h>
#include <qpen.h>
#include <qcolor.h>
#include "f4lm.h"
#include "tools.h"
#include "colorpopup.h"

CSmalColorBoxes::CSmalColorBoxes (QWidget * parent, const char *name,
                  QColor r, CColorSwatches * rp):
        QWidget (parent, name)
{
        //setFocusPolicy(QWidget::StrongFocus);
    realp = rp;
        //    c=r;

}

CSmalColorBoxes::~CSmalColorBoxes ()
{}

/*void CSmalColorBoxes::mouseMoveEvent(QMouseEvent *e){
  if(e->x()<width() && e->x()>0 && e->y()<height() && e->y()>0){
 
  }
}*/

void CSmalColorBoxes::mousePressEvent (QMouseEvent * e)
{
        realp->slotClick (backgroundColor ());	//  ->slotsetDefColor(c);
    if (realp->realp->tools->swatchesCarrier->isVisible ()) {
                //              grabMouse();
        realp->realp->tools->swatchesCarrier->hide ();
    }
    /*qDebug("r="+QString::number(backgroundColor().red())+
       " g="+QString::number(backgroundColor().green()) +
       " b="+QString::number(backgroundColor().blue()) ); */
        //qDebug(QString::number(qAlpha((backgroundColor().rgb()))));
}

void CSmalColorBoxes::enterEvent (QEvent *)
{
    QPainter p (this);
    p.end ();
    p.begin (this);
    QPen pen = QPen (QColor (255, 255, 255));
    pen.setWidth (2);
    p.setPen (pen);
        p.drawLine (0, 0, 0, 9);	// drawing code
        p.drawLine (0, 9, 9, 9);	// drawing code
        p.drawLine (9, 9, 9, 0);	// drawing code
        p.drawLine (9, 0, 0, 0);	// drawing code
    p.end ();

    if (realp->realp->tools->swatchesCarrier->colorShower->isVisible ())
        realp->realp->tools->swatchesCarrier->colorShower->
        setPaletteBackgroundColor (backgroundColor ());

    if (realp->realp->tools->swatchesCarrier->colorName->isVisible ()) {
                //QPixmap p=QPixmap::grabWindow( QApplication::desktop()->winId(),  e->x(),e->y(), 1, 1 );
                //QImage image = p.convertToImage();
        QString tmp;
                QRgb px = backgroundColor ().rgb ();	//image.pixel(0,0);
        tmp.sprintf ("#%02x%02x%02x",qRed (px), qGreen (px), qBlue (px));
        realp->realp->tools->swatchesCarrier->colorName->setText (tmp.upper ());
    }
}

void CSmalColorBoxes::leaveEvent (QEvent *){
    update ();
}
