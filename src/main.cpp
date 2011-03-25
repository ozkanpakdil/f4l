/***************************************************************************
              main.cpp  -  description
                 -------------------
    begin                : Sat Jun  7 02:29:46 EEST 2003
    copyright            : (C) 2003 by �zkan pakdil
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

#include <qapplication.h>
#include <qfont.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qtranslator.h>
#include <qsplashscreen.h>
#include <qwaitcondition.h>

#include "f4lm.h"
#include "cursor/main_ico.xpm"
#include "cursor/F4L-Logo1.xpm"

int main ( int argc, char *argv[] )
{

	QApplication a ( argc, argv );
	QPixmap pixmap ( ( const char ** ) f4l_splash_xpm );
	QSplashScreen *splash = new QSplashScreen ( pixmap );
	splash->show();
	a.setFont ( QFont ( "sans", 8 ) );
	QTranslator tor ( 0 );

	// set the location where your .qm files are in load() below as the last parameter instead of "."
	// for development, use "/" to use the english original as
	// .qm files are stored in the base project directory.
	if ( argc > 1 )
	{
		QString arg ( argv[1] );
		if ( arg.startsWith ( "-lang:" ) )
		{
			//qDebug (arg);
			if ( arg=="-lang:tr" )
				tor.load ( QString ( "f4lm_tr.qm" ) ,"." );
			if ( arg=="-lang:eo" )
				tor.load ( QString ( "f4lm_eo.qm" ) ,"." );
			if ( arg=="-lang:en" )
				tor.load ( QString ( "f4lm_en.qm" ) ,"." );
		}

		if ( arg == "--help" )
		{
			qDebug ( "\nUsage:f4lm [OPTION]\n\n"
			         "-lang:tr\t\tfor starting f4l in turkish.\n"
			         "-lang:eo\t\tfor starting f4l in esperanto.\n"
			         "-lang:en(default)\t\tfor starting f4l in english.\n" );
			return 0;
		}
	}



	a.installTranslator ( &tor );
	F4lmApp * f4lm = new F4lmApp ();
	f4lm->setIcon ( QPixmap ( ( const char ** ) main_ico_xpm ) );
	a.setMainWidget ( f4lm );
	/*if(argc>1)
	   f4lm->openDocumentFile(argv[1]);
	   else      */
	f4lm->openDocumentFile ();
	f4lm->setMinimumSize ( 640,480 );
	QWaitCondition sleep;
	sleep.wait ( 7000 );   // two seconds
	//f4lm->showMaximized ();
	f4lm->show();

	splash->finish ( f4lm );
	delete splash;
	return a.exec ();
}


