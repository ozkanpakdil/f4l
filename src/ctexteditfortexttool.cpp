#include "ctexteditfortexttool.h"
#include "canview.h"
#include "ccanvastext.h"

#include <qpopupmenu.h>
#include <qfontdialog.h>

CTextEditForTextTool::CTextEditForTextTool (QWidget * parent,
        const char *name):
        QTextEdit (parent, name)
{
    setFrameStyle (QFrame::Box | QFrame::Raised);
    setVScrollBarMode (QScrollView::AlwaysOff);
    setHScrollBarMode (QScrollView::AlwaysOff);
    setResizePolicy (QScrollView::AutoOne);
    setWordWrap (QTextEdit::NoWrap);
    resize (20, 30);
}

void CTextEditForTextTool::keyPressEvent (QKeyEvent * e)
{
    QTextEdit::keyPressEvent (e);
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
    QTextEdit::paintEvent (event);
}

QPopupMenu * CTextEditForTextTool::createPopupMenu (const QPoint & pos)
{
    QPopupMenu *textRightClickMenu = QTextEdit::createPopupMenu (pos);
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
