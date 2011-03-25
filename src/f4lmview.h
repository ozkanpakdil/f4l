/***************************************************************************
f4lmview.h  -  description
-------------------
begin                : Sat Jun  7 02:29:46 EEST 2003
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

#ifndef F4LMVIEW_H
#define F4LMVIEW_H

// include files for Qt
#include <qwidget.h>
//#include <qtable.h>
#include <qlayout.h>
#include <qsplitter.h>
#include <qpushbutton.h>
#include <qlistbox.h>
#include <qlabel.h>
#include <qvaluevector.h>

#include "canview.h"
#include "ccanvas.h"
#include "tools.h"
#include "canvasItem.h"
#include "ccanvasellipse.h"
#include "ccanvasline.h"
#include "ccanvastext.h"
#include "ccanvasrectangle.h"
#include "cpencilline.h"
#include "timeline.h"
#include "clistboxitem.h"

class F4lmDoc;
class F4lmApp;

typedef struct _canvasBoundaries {
    int canvasLimitsForTable[1][3];
}
canvasBoundaries;

/**
* This class provides base for our application view.
* 	
* @author Özkan Pakdil
* @version 0.1
*/
class F4lmView:public QWidget {

    Q_OBJECT

    friend class F4lmDoc;

public:
    /** Constructor for the view
    * @param pDoc  our document instance that the view represents. Create a document before calling the constructor
    	* or connect an already existing document to a new MDI child widget.*/
    F4lmView (F4lmDoc * pDoc, QWidget * parent, const char *name, int wflags);

    /** Destructor for the main view */
    ~F4lmView ();

    /** returns a pointer to the document connected to the view*/
    F4lmDoc * getDocument ()const;

    /** gets called to redraw the document contents if it has been modified */
    void update (F4lmView * pSender);

    /** contains the implementation for printing functionality and gets called by F4lmApp::slotFilePrint() */
    void print (QPrinter * pPrinter);

    /** this holds the ID of default object for drawing*/
    int defObjID;

    /** this holds the default color for drawing*/
    QColor defObjCOLOR;

    /** this holds the default white rectangle used for real canvas */
    QRect defSceneRect;

    /** this is the scene width and height*/
    int defSceneWidth, defSceneHeight;

    /** this variable gonna holds total layer number this view has*/
    int layerNum;
    F4lmApp * dad;
    canview * canvasViewer;
	CCanvas* mainCanvas;

protected:
    virtual void closeEvent (QCloseEvent *);
    void mouseMoveEvent (QMouseEvent * e);
    F4lmDoc * doc;
    QValueVector < canvasBoundaries > *boundaries;
	

public slots:		// Public slots
    void slotNewLayer ();
	
	///Does inserting frame into scene really other reference this function.
    void slotInsertFrame (int row, int col);
    void slotShowCanvas (int row, int col);
};
#endif	/*

*/
