#ifndef CTEXTEDITFORTEXTTOOL_H
#define CTEXTEDITFORTEXTTOOL_H

#include <q3textedit.h>
//Added by qt3to4:
#include <QPaintEvent>
#include <QKeyEvent>
#include <Q3PopupMenu>

/// when we press inside canview there is a textbox
/// for entering words. it comes from this class.
class CTextEditForTextTool:public Q3TextEdit
{
Q_OBJECT public:
    CTextEditForTextTool (QWidget * parent = 0, const char *name = 0);
    Q3PopupMenu *createPopupMenu (const QPoint & pos);
    void keyPressEvent (QKeyEvent * e);
    void paintEvent (QPaintEvent * event);

protected:

public slots:		// Public slots
    /** This function is used for right click menu's last element. Select Font ->slot. */
    void setUserFont ();
};

#endif
