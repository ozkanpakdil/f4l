#ifndef CTEXTEDITFORTEXTTOOL_H
#define CTEXTEDITFORTEXTTOOL_H

#include <qtextedit.h>

/// when we press inside canview there is a textbox
/// for entering words. it comes from this class.
class CTextEditForTextTool:public QTextEdit
{
Q_OBJECT public:
    CTextEditForTextTool (QWidget * parent = 0, const char *name = 0);
    QPopupMenu *createPopupMenu (const QPoint & pos);
    void keyPressEvent (QKeyEvent * e);
    void paintEvent (QPaintEvent * event);

protected:

public slots:		// Public slots
    /** This function is used for right click menu's last element. Select Font ->slot. */
    void setUserFont ();
};

#endif
