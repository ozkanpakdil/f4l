#include "ctexteditfortexttool.h"
#include "canview.h"
#include "ccanvastext.h"

#include <q3popupmenu.h>
#include <qfontdialog.h>
//Added by qt3to4:
#include <QPaintEvent>
#include <Q3Frame>
#include <QKeyEvent>

CTextEditForTextTool::CTextEditForTextTool (QWidget * parent,
        const char *name):
        Q3TextEdit (parent, name)
{
    setFrameStyle (Q3Frame::Box | Q3Frame::Raised);
    setVScrollBarMode (Q3ScrollView::AlwaysOff);
    setHScrollBarMode (Q3ScrollView::AlwaysOff);
    setResizePolicy (Q3ScrollView::AutoOne);
    setWordWrap (Q3TextEdit::NoWrap);
    resize (20, 30);
}

void CTextEditForTextTool::keyPressEvent (QKeyEvent * e)
{
    Q3TextEdit::keyPressEvent (e);
    if (contentsHeight () > visibleHeight ()
            || contentsWidth () > visibleWidth ())
        resize (contentsWidth () + 10, contentsHeight () + 10);
    if (e->key () == Qt::Key_Escape) {
        ((canview *) parent ())->text->setFont (currentFont ());
        ((canview *) parent ())->text->setText (text ());
        ((canview *) parent ())->text->show ();
        ((canview *) parent ())->setFocus ();
//qDebug(((canview *) parent ())->text->text ());
        close ();
    }

    /*	if(e->key()==Qt::Key_Backspace)
    		resize(contentsWidth (),contentsHeight ());*/

}

void CTextEditForTextTool::paintEvent (QPaintEvent * event)
{
    Q3TextEdit::paintEvent (event);
}

Q3PopupMenu * CTextEditForTextTool::createPopupMenu (const QPoint & pos)
{
    Q3PopupMenu *textRightClickMenu = Q3TextEdit::createPopupMenu (pos);
    textRightClickMenu->insertSeparator ();
    textRightClickMenu->insertItem ("Select font", this, SLOT (setUserFont ()));
    return textRightClickMenu;
}


/** No descriptions */
void CTextEditForTextTool::setUserFont ()
{
        //  if(selectedText()!=""){
    bool ok;
    QFont f = QFontDialog::getFont (&ok);
    setCurrentFont (f);
        //  }
}
