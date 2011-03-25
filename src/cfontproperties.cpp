/***************************************************************************
              cfontproperties.cpp  -  description
                 -------------------
    begin                : Wed Sep 17 2003
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

#include "cfontproperties.h"
#include "f4lm.h"
#include "f4lmview.h"
#include "ctexteditfortexttool.h"
#include <qfontdialog.h>
#include <qevent.h>

CFontProperties::CFontProperties (QWidget * parent, const char *name):
        QWidget (parent, name)
{
    QVBoxLayout *topLayout = new QVBoxLayout (this);
    QWidget *privateLayoutWidget = new QWidget (this, "layout15");
        //privateLayoutWidget->setGeometry( QRect( 0, 0, 510, 100 ) );
    layout15 = new QHBoxLayout (privateLayoutWidget, 11, 6, "layout15");
    layout10 = new QVBoxLayout (0, 0, 6, "layout10");
    textLabel1 = new QLabel (privateLayoutWidget, "textLabel1");
	
    layout10->addWidget (textLabel1);
    comboBox1 = new QComboBox (FALSE, privateLayoutWidget, "comboBox1");
    comboBox1->setMaximumHeight (20);
    layout10->addWidget (comboBox1);
    textLabel4 = new QLabel (privateLayoutWidget, "textLabel4");
    layout10->addWidget (textLabel4);

    comboBox4 = new QComboBox (FALSE, privateLayoutWidget, "comboBox4");
    comboBox4->setMaximumHeight (20);
    layout10->addWidget (comboBox4);
    layout15->addLayout (layout10);

    layout11 = new QVBoxLayout (0, 0, 6, "layout11");
    textLabel2 = new QLabel (privateLayoutWidget, "textLabel2");
    layout11->addWidget (textLabel2);
    comboBox2 = new QComboBox (FALSE, privateLayoutWidget, "comboBox2");
    comboBox2->setMaximumHeight (20);
    layout11->addWidget (comboBox2);

    textLabel5 = new QLabel (privateLayoutWidget, "textLabel5");
    layout11->addWidget (textLabel5);
    comboBox5 = new QComboBox (FALSE, privateLayoutWidget, "comboBox5");
    comboBox5->setMaximumHeight (20);
    layout11->addWidget (comboBox5);
    layout15->addLayout (layout11);

    layout12 = new QVBoxLayout (0, 0, 6, "layout12");

    textLabel3 = new QLabel (privateLayoutWidget, "textLabel3");
    textLabel3->setMaximumSize (QSize (32767, 20));
    layout12->addWidget (textLabel3);

    comboBox3 = new QComboBox (FALSE, privateLayoutWidget, "comboBox3");
    comboBox3->setMaximumHeight (20);
    layout12->addWidget (comboBox3);

    pushButton1 = new QPushButton (privateLayoutWidget, "pushButton1");
    layout12->addWidget (pushButton1);
    layout15->addLayout (layout12);

    layout13 = new QVBoxLayout (0, 0, 6, "layout13");

    textLabel6 = new QLabel (privateLayoutWidget, "textLabel6");
    textLabel6->setMaximumSize (QSize (32767, 20));
    layout13->addWidget (textLabel6);

    textLabel7 = new QLabel (privateLayoutWidget, "textLabel7");
    layout13->addWidget (textLabel7);
    layout15->addLayout (layout13);
    languageChange ();
        //resize( QSize(400, 100).expandedTo(minimumSizeHint()) );

    topLayout->addWidget (privateLayoutWidget);
        //////////////font names listing///////////////////////////////////////////
    familyNames = fdb.families ();
    QStringList newList;
    QString s;
    QStringList::Iterator it = familyNames.begin ();
    int idx = 0;
    for (; it != familyNames.end (); it++) {
        s = *it;

#if 0

        if (fdb.isSmoothlyScalable (*it))
            newList.append (s + "(TT)");
        else if (fdb.isBitmapScalable (*it))
            newList.append (s + "(BT)");
        else
#endif
            comboBox1->insertItem ((s), idx++);
         newList.append (s);
    }
    family = comboBox1->currentText ();
        ///////////////////font scripts listing///////////////////////////////////////////////////////////
    comboBox4->clear ();
    scriptNames.clear ();
    scriptScripts.clear ();

    QString scriptname;
    for (int i = 0; i < QFont::NScripts; i++) {
        scriptname = QFontDatabase::scriptName ((QFont::Script) i);
        if (!scriptname.isEmpty ()) {
            scriptNames += scriptname;
            scriptScripts += i;
        }
    }

    if (scriptNames.isEmpty ()) {
#ifndef QT_NO_DEBUG
        qWarning ("QFontDialog::updateScripts: Internal error, "
              "no scripts for family \"%s\"", (const char *) family);
#endif

    }

    it = scriptNames.begin ();
    for (; it != scriptNames.end (); ++it)
        comboBox4->insertItem (*it);
        //////////////////font styles listings/////////////////////////////////////////////////
    updateFontStyleList ();
        ////////////////////////////////////////////////////////////
    comboBox3->clear ();
    QValueList < int >sizes = fdb.pointSizes (family, style);

    if (sizes.isEmpty ()) {
#ifndef QT_NO_DEBUG
        qWarning ("QFontDialog::updateSizes: Internal error, "
              "no pointsizes for family \"%s\" with script \"%s\"\n"
              "and style \"%s\"",
              (const char *) family, (const char *) script,
              (const char *) style);
#endif
                //      return;
    }
    int i;
    QString tmp;
    for (i = 0; (uint) i < sizes.count (); i++) {
        tmp.sprintf ("%i", sizes[i]);
        comboBox3->insertItem (tmp);
    }

    comboBox5->insertItem ("None");
    comboBox5->insertItem ("Strikeout");
    comboBox5->insertItem ("Underline");

    /*comboBox5->setEditable(true);
       comboBox5->setEditable(true);
       comboBox5->setEditable(true);
       comboBox5->setEditable(true);
       comboBox5->setEditable(true);
       comboBox1->setAutoCompletion(true);
       comboBox2->setAutoCompletion(true);
       comboBox3->setAutoCompletion(true);
       comboBox4->setAutoCompletion(true);
       comboBox5->setAutoCompletion(true); */

    connect (pushButton1, SIGNAL (clicked ()), this,SLOT (showQTfontSelection ()));
    connect (comboBox1, SIGNAL (activated (int)), this,SLOT (slotFontChanged (int)));
    connect (comboBox2, SIGNAL (activated (int)), this,SLOT (slotFontStyleChanged (int)));
    connect (comboBox3, SIGNAL (activated (int)), this,SLOT (slotFonSizeChanged (int)));
    connect (comboBox4, SIGNAL (activated (int)), this,SLOT (slotScriptChanged (int)));
    connect (comboBox5, SIGNAL (activated (int)), this,SLOT (slotEffectChanged (int)));
}

CFontProperties::~CFontProperties ()
{}

void CFontProperties::languageChange ()
{
    textLabel1->setText (tr ("Font:"));
    textLabel4->setText (tr ("Script"));
    textLabel2->setText (tr ("Font style"));
    textLabel5->setText (tr ("Effects"));
    textLabel3->setText (tr ("Size"));
    pushButton1->setText (tr ("Select Font"));
    textLabel6->setText (tr (""));
    textLabel7->
    setText (tr
         ("This tool can change the font.\nBut dont forget for 1 text there could be 1 font."));
}

/** for standard QT font selection dialog. */
void CFontProperties::showQTfontSelection ()
{
    bool ok;
    QFont f = QFontDialog::getFont (&ok);
        //    setCurrentFont(f);
    updateCanvasFont ();
}

void CFontProperties::slotFontChanged (int idx)
{
    family = comboBox1->text (idx);
    updateCanvasFont ();
    updateFontStyleList ();
}

void CFontProperties::slotFontStyleChanged (int idx)
{
    style = comboBox2->text (idx);
    updateCanvasFont ();
}

void CFontProperties::slotFonSizeChanged (int idx){
    size = comboBox3->text (idx);
    updateCanvasFont ();
}

void CFontProperties::slotScriptChanged (int idx){
    script = comboBox4->text (idx);
    updateCanvasFont ();
}

void CFontProperties::slotEffectChanged (int idx){
    updateCanvasFont ();
}

/** this function is used for updating the canvas's text item. */
void
CFontProperties::updateCanvasFont ()
{
    int pSize = size.toInt ();
    if (pSize == 0)
        pSize = 12;
    QFont f = fdb.font (family, style, pSize);
    if (comboBox5->currentItem () == 1)
        f.setStrikeOut (true);
    if (comboBox5->currentItem () == 2)
        f.setUnderline (true);

    F4lmApp *dad = (F4lmApp *) parent ()->parent ()->parent ()->parent ();
    if (dad->slotCurrentView ()->canvasViewer->textBox->isVisible ()) {
        dad->slotCurrentView ()->canvasViewer->textBox->setCurrentFont (f);
        QKeyEvent *k = new QKeyEvent (QEvent::None, 0, 0, 0);
        dad->slotCurrentView ()->canvasViewer->textBox->keyPressEvent (k);
    } else {
        dad->slotCurrentView ()->canvasViewer->textFont = f;
    }
}

/** this refresh the list of font styles in properties. */
void
CFontProperties::updateFontStyleList ()
{
    comboBox2->clear ();
    QStringList styles = fdb.styles (family);
    if (styles.isEmpty ()) {
#ifndef QT_NO_DEBUG
        qWarning ("QFontDialog::updateStyles: Internal error, "
              "no styles for family \"%s\" with script \"%s\"",
              (const char *) family, (const char *) script);
#endif
        return;
    }
    comboBox2->insertStringList (styles);
    style = comboBox2->currentText ();
}
