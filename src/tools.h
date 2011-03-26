/****************************************************************************
** Form interface generated from reading ui file 'tools.ui'
**
** Created: Mon Jun 9 06:20:30 2003
**      by:  The User Interface Compiler (uic)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/
#ifndef CTools_H
#define CTools_H

#include <qvariant.h>
#include <qwidget.h>
#include <qpixmap.h>
#include <q3textedit.h>
#include <qtoolbutton.h>
#include <qlabel.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <QEvent>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
/*
    *@author �zkan pakdil
  turkish: bu class sagdaki tools dockable windowunu olusturmak. buttonlar bu class da tasiniyor.
  english: for making tools window.
*/

class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class Q3ButtonGroup;
class CColorSwatches;
class CToolButton;
class CColorPopup;
class F4lmApp;

/// Collects button for tools
/// left sided tools in left dockarea
class CTools:public QWidget
{
Q_OBJECT public:
    CTools (QWidget * parent, const char *name = 0, Qt::WFlags fl =
            0, F4lmApp * realp = 0);
    ~CTools ();

    F4lmApp *dad;
    Q3ButtonGroup *ToolsButtonGroup;
    Q3ButtonGroup *ToolsViewGroup;
    Q3ButtonGroup *ToolsColorsGroup;
    Q3ButtonGroup *ToolsOptionsGroup;

    CToolButton * ArrowTool;
    CToolButton *SubSelectionTool;
    CToolButton *LineTool;
    CToolButton *LassoTool;
    CToolButton *PenTool;
    CToolButton *TextTool;
    CToolButton *OvalTool;
    CToolButton *RectangleTool;
    CToolButton *PencilTool;
    CToolButton *BrushTool;
    CToolButton *FreeTransformTool;
    CToolButton *FillTransformTool;
    CToolButton *InkBottleTool;
    CToolButton *PaintBucketTool;
    CToolButton *EyedropperTool;
    CToolButton *EraserTool;
    CToolButton *HandTool;
    CToolButton *ZoomTool;
    CToolButton * StrokeColor;
    CToolButton * FillColor;
    CColorPopup * swatchesCarrier;
    CColorSwatches * s;
    QPixmap strokpix;
    QPixmap fillpix;
    Q3TextEdit * colorName;
    QLabel * colorShower;

public slots:			// Public slots
    void slotArrowTool ();
    void slotSubSelectionTool ();
    void slotLineTool ();
    void slotLassoTool ();
    void slotPenTool ();
    void slotTextTool ();
    void slotOvalTool ();
    void slotRectangleTool ();
    void slotPencilTool ();
    void slotBrushTool ();
    void slotFreeTransformTool ();
    void slotFillTransformTool ();
    void slotInkBottleTool ();
    void slotPaintBucketTool ();
    void slotEyedropperTool ();
    void slotEraserTool ();
    void slotHandTool ();
    void slotZoomTool ();
    void slotStrokeColor ();
    void slotFillColor ();
};


/// this is our tool buttons main class
/// used for to handle the enter and leave events of tool button
/// for statusbar message
class CToolButton:public QToolButton
{

    Q_OBJECT
public:
    CTools * dad;
    CToolButton (QWidget * parent = 0, const char *name = 0);

protected:
    void enterEvent (QEvent *);
    void leaveEvent (QEvent *);

};

#endif //
