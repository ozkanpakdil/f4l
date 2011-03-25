/***************************************************************************
              cfontproperties.h  -  description
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

#ifndef CFONTPROPERTIES_H
#define CFONTPROPERTIES_H

#include <qwidget.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qstringlist.h>
#include <qfontdatabase.h>

/**this class used for properties part of GUI at bottom. when user click on text tool from tools in properties part should show kind of Font peoperties.
  *@author Özkan Pakdil
  */

class CFontProperties:public QWidget
{
Q_OBJECT public:
    CFontProperties (QWidget * parent = 0, const char *name = 0);
    ~CFontProperties ();
    /** this function is used for updating the canvas's text item. */
    void updateCanvasFont ();
    /** this refresh the list of font styles in properties. */
    void updateFontStyleList ();
    /** for standard QT fon selection dialog. */

    QLabel *textLabel1;
    QComboBox *comboBox1;
    QLabel *textLabel4;
    QComboBox *comboBox4;
    QLabel *textLabel2;
    QComboBox *comboBox2;
    QLabel *textLabel5;
    QComboBox *comboBox5;
    QLabel *textLabel3;
    QComboBox *comboBox3;
    QPushButton *pushButton1;
    QLabel *textLabel6;
    QLabel *textLabel7;

    QStringList familyNames;
    QFontDatabase fdb;
    QStringList scriptNames;
    QValueList < int >scriptScripts;
    QStringList scriptSamples;
    bool usingStandardSizes;
    QString family;
    QString script;
    QString style;
    QString size;

protected:
    QHBoxLayout * layout15;
    QVBoxLayout *layout10;
    QVBoxLayout *layout11;
    QVBoxLayout *layout12;
    QVBoxLayout *layout13;

public slots:
    virtual void languageChange ();
    void showQTfontSelection ();
    void slotFontChanged (int);
    void slotFontStyleChanged (int);
    void slotFonSizeChanged (int);
    void slotScriptChanged (int);
    void slotEffectChanged (int);

};

#endif
