/***************************************************************************
              colorpopup.cpp  -  description
                 -------------------
    begin                :  2003
    copyright            : (C) 2003 by özkan pakdil
    email                : ozkanpakdil@users.sourceforge.net
 ***************************************************************************/

#include "colorpopup.h"
#include "tools.h"
#include "ccolorswatches.h"
#include "f4lm.h"
#include <qcolordialog.h>
#include <qimage.h>
#include "cursor/eye_dropper_tool.xpm"

CColorPopup::CColorPopup (QWidget * parent, const char *name, WFlags f)
:QWidget (parent, name, f)
{
    colorShower = new QLabel (this, "color shower");
    colorShower->setFrameStyle (QFrame::WinPanel | QFrame::Sunken);
    colorShower->setLineWidth (2);
    colorShower->setMidLineWidth (1);
    colorShower->resize (37, 20);
    colorShower->setPaletteBackgroundColor (QColor (0, 0, 0));
    colorShower->move (5, 2);
    colorName = new QTextEdit (this);
    colorName->resize (55, 20);
    colorName->move (50, 2);
    colorName->setHScrollBarMode (QScrollView::AlwaysOff);
    colorName->setVScrollBarMode (QScrollView::AlwaysOff);
    
	QFont f1 ("Times", 8, QFont::Light);
    colorName->setFont (f1);
    colorName->clearFocus ();
    s = new CColorSwatches (this, "", ((CTools *) parent)->dad);
    s->resize (210, 125);
    s->move (2, 29);
    
	QToolButton * colordialog =new CToolButton (this, tr ("Open color dialog"));
    colordialog->move (180, 3);
    colordialog->resize (20, 20);
    colordialog->setIconSet (QIconSet (QPixmap ("colordialogBut.png")));
    colordialog->setTextLabel (trUtf8 ("Open Color Dialog"));
    connect (colordialog, SIGNAL (clicked ()), this,SLOT (slotColordialog ()));

        //setFocusPolicy (QWidget::StrongFocus);
    setMouseTracking (true);
    mcursor = QPixmap ((const char **) eye_dropper_tool_xpm);
    setCursor (QCursor (mcursor, 1, 15));
}

CColorPopup::~CColorPopup ()
{
}

void CColorPopup::slotColordialog ()
{
    QColor c = QColorDialog::getColor ();
    ((CTools *) parent ())->dad->setDefObjCOLOR (c);
}

void CColorPopup::mouseMoveEvent (QMouseEvent * e)
{
    QPoint p = e->globalPos ();
    QWidget * desktop = QApplication::desktop ();
    QPixmap pm = QPixmap::grabWindow (desktop->winId (), p.x (), p.y (), 1, 1);
    QImage i = pm.convertToImage ();
    QRgb px = i.pixel (0, 0);
    QColor color (qRed (px), qGreen (px), qBlue (px));
    colorShower->setPaletteBackgroundColor (color);
    QString tmp;
    tmp.sprintf ("#%02x%02x%02x",qRed (px), qGreen (px), qBlue (px));
    colorName->setText (tmp.upper ());
}

void CColorPopup::mousePressEvent (QMouseEvent * e)
{
    ((CTools *) parent ())->dad->setDefObjCOLOR (colorShower->backgroundColor ());
    hide ();
}

void CColorPopup::showEvent (QShowEvent *)
{
    grabMouse (QCursor (mcursor, 1, 15));
}

void CColorPopup::hideEvent (QHideEvent *)
{
    releaseMouse ();
}
