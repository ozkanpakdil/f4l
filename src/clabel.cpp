/***************************************************************************
              clabel.cpp  -  description
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

#include "clabel.h"
//#include <iostream.h>
#include "timeline.h"
#include "f4lmview.h"
#include "f4lm.h"
#include <qpainter.h>
#include <qsize.h>
#include <qpixmap.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QPaintEvent>
#include "cursor/outline_pic.xpm"
#include "cursor/goz_pic.xpm"
#include "cursor/kilit_pic.xpm"
//#include "ctimeline.h"

/*CLabel::CLabel (QWidget *buddy,const QString &text,QWidget *parent,const char *name,WFlags f)
   : QLabel (buddy,text,parent,name,f){
     setFocusPolicy(QWidget::ClickFocus);
     cout<<width();
 
}     */
CLabel::CLabel (QWidget * parent, const char *name)
        :QWidget (parent, name)
{

        //    setFocusPolicy(QWidget::StrongFocus);
        //qDebug(QFont::styleHint().toString()) ;
        //QFont f( "Helvetica", 8, QFont::Normal );
        //f.setPixelSize(12);
        //f.setPointSize(16);
        //f.setWeight(20);
        //      timeLineRightTopLabel->setAutoResize(true);
        //setFont( f );
        //setGlobalMouseTracking(TRUE);
        // setMouseTracking(true);

        //setBaseSize(50,50);
        //   setMinimumWidth(200);
        //  setMinimumHeight(20);
    nameT = name;
    leftClick = false;
    leftClickX = 0;
    kutuNo = 1;
    widthMine = 560 * 9;
    dad = (CTimeLine *) parentWidget ()->parent ()->parent ()->parent ();
}

CLabel::~CLabel ()
{

}

void CLabel::paintEvent (QPaintEvent *)
{
    if (nameT == "timeLineRightTopLabel") {
                //              qDebug(QString::number(width()));
        QPainter p (this);
        p.setPen (Qt::black);
        QFont f ("Courier", 8, QFont::Normal);
        p.setFont (f);

                //setFocusPolicy(QWidget::StrongFocus); cout<<width();    qDebug("paint");

        bool kutuCizildi = true;
        bool cizgiCizildi = true;
        int j = 1, i;
        for (i = 0; i < 560 * 9; i = i + 8, j++) {
            p.drawLine (i, 0, i, 2);
            if (dad->layerMaxColNum >= j) {
                if ((leftClickX <= i || leftClickX <= i + 8) &&
                        (leftClickX >= i || leftClickX >= i + 8)) {
                    if (kutuCizildi && !leftClick) {
                        QBrush brush (QColor (255, 153, 153),Qt::SolidPattern);
                        p.fillRect (i, 0, 8, height (), brush);
                        p.setPen (QColor (204, 0, 0));
                        p.drawRect (i, 0, 8, height ());
                        kutuNo = j;
                                                //cout<<j<<endl;
                    }

                    if (leftClick && cizgiCizildi) {
                        p.setPen (Qt::black);
                        p.drawRect (i + 3, 0, 2, height ());
                        kutuNo = j;
                        cizgiCizildi = false;
                    }

                                        //cout<<"i:"<<i<<"leftX:"<<leftClickX<<endl;
                    p.setPen (Qt::black);
                    kutuCizildi = false;
                }
            } else {
                j = dad->layerMaxColNum;
                if (kutuCizildi) {
                    QBrush brush (QColor (255, 153, 153), Qt::SolidPattern);
                    p.fillRect (i - 8, 0, 8, height (), brush);
                    p.setPen (QColor (204, 0, 0));
                    p.drawRect (i - 8, 0, 8, height ());
                    kutuNo = j;
                }
                kutuCizildi = false;
            }
            p.setPen (Qt::black);
            p.drawLine (i, height (), i, height () - 2);
        }

        j = 1;
        for (i = 0; i < widthMine; i = i + 8, j++)
            if (!(j % 5)) {
                p.setPen (Qt::black);
                p.drawText (i, height () - 5, QString::number (j));
            }

                //cout<<"paintEvent"<<endl;
    }

    if (nameT == "currentFrameLabel") {
        QPainter p (this);
        p.setPen (Qt::black);
        QFont f ("Helvetica", 8, QFont::Normal);
        p.setFont (f);
        p.drawText (5, height () - 5, QString::number (kutuNo));
    }

    if (nameT == "timeLineLeftTopLabel") {
        QPainter p (this);
        QPixmap _1 = QPixmap ((const char **) goz_pic_xpm);
        QPixmap _2 = QPixmap ((const char **) kilit_pic_xpm);
        QPixmap _3 = QPixmap ((const char **) outline_pic_xpm);
        p.drawPixmap (width () - 45 - _3.width () - _2.width () - _1.width (),0, _1);
        p.drawPixmap (width () - 45 - _3.width () - _2.width () + 4, 0, _2);
        p.drawPixmap (width () - 45 - _3.width () + 14, 0, _3);
        p.setPen (Qt::black);
        QFont f ("Helvetica", 8, QFont::Normal);
        p.setFont (f);
        p.drawText (5, height () - 5, QString::number (width ()));
    }
    valueChanged ();
}

void CLabel::mousePressEvent (QMouseEvent * e)
{
        //cout<<e->x()<<endl;    setFocusPolicy(QWidget::StrongFocus);
        // qDebug(QString::number(e->x()));
    valueChanged ();
    if (e->button () == Qt::LeftButton)
        if (nameT == "timeLineRightTopLabel") {
            leftClick = true;
            leftClickX = e->x ();
            update ();
            if (leftClickX / 8 < dad->layerMaxColNum)
                dad->dad->slotCurrentView ()->slotShowCanvas (0, leftClickX / 8);
                }			//cout<<"kut no"<<kutuNo<<endl;
}

void
CLabel::mouseReleaseEvent (QMouseEvent * e)
{
        //cout<<e->x()<<endl;  setFocusPolicy(QWidget::StrongFocus);  qDebug(QString::number(e->x()));
    valueChanged ();
    if (e->button () == Qt::LeftButton)
        if (nameT == "timeLineRightTopLabel") {
            leftClick = false;
            /*if(e->x()/8<dad->layerMaxColNum) */
            update ();
        }
}

void CLabel::mouseMoveEvent (QMouseEvent * e)
{
        // cout<<endl;
        // cout<<""<<e->x()<<endl;  setFocusPolicy(QWidget::StrongFocus);  qDebug(QString::number(e->x()));
    valueChanged ();
    if (leftClick && !(e->x () > width ()) && !(e->x () < 0))
        leftClickX = e->x ();
        //qDebug("%d",dad->layerMaxColNum);
        //cout<<parent()->parent()->parent()->name()<<endl;
    if (nameT == "timeLineRightTopLabel"&& leftClickX / 8 < dad->layerMaxColNum) {
        update ();
        if (leftClickX / 8 < dad->layerMaxColNum)
            dad->dad->slotCurrentView ()->slotShowCanvas (0, leftClickX / 8);
    }
}

void CLabel::setText (QString cstr){
    str += cstr;
}

int CLabel::currentNo (){
    return kutuNo;
}

void CLabel::setNo (int k){
        //this function called by current frameLabel
    kutuNo = k;
}

void CLabel::setWidthMine (int w){
    widthMine = w;
}

