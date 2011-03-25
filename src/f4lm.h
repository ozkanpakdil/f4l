/***************************************************************************
              f4lm.h  -  description
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

#ifndef F4LM_H
#define F4LM_H

// include files for QT
#include <qapplication.h>
#include <qmainwindow.h>
#include <qaction.h>
#include <qworkspace.h>
#include <qmenubar.h>
#include <qtoolbar.h>
#include <qstatusbar.h>
#include <qwhatsthis.h>
#include <qpopupmenu.h>
#include <qaccel.h>
#include <qtoolbutton.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <qprinter.h>
#include <qstring.h>
#include <qpixmap.h>
#include "cproperties.h"

// forward declaration of the F4lm classes
class F4lmDoc;
class F4lmView;
class CTools;
class CTimeLine;

/**
  * This Class is the base class for our application. It sets up the main
  * window and providing a menubar, toolbar
  * and statusbar. For the main view, an instance of class F4lmView is
  * created which creates our view.
  * 	
  * @author Özkan Pakdil
  * @version 0.1
  */
class F4lmApp:public QMainWindow
{
    Q_OBJECT
public:
    /** construtor */
    F4lmApp ();

    /** destructor */
    ~F4lmApp ();

    /** opens a file specified by commandline option
     */
    void openDocumentFile (const char *file = 0);

    /** This function makes that toolbar around scene */
    void initDockWindows ();

    void setDefObjID (int);

    void setDefObjCOLOR (QColor);

    /** this return the current view obj*/
    F4lmView * slotCurrentView ();

    CTools * tools;
    CTimeLine * tl;
    CProperties * properties;
    CColorSwatches * pColorSwatches;
    QDockWindow * propertiesDockableWindow;
    QDockWindow * colorDialogDockableWindow;
    QDockWindow * colorSwatchesDockableWindow;
    QDockWindow * toolsDockableWindow;
    QDockWindow * timeLineDockableWindow;
    QMap < int, QString > stringTable;

protected:
        //void mouseMoveEvent(QMouseEvent *e);
        //void mousePressEvent(QMouseEvent*);
    /** overloaded for Message box on last window exit */
    bool queryExit ();

    /** event filter to catch close events for MDI child windows and is installed in createClient() on every child window.
      * Closing a window calls the eventFilter first which removes the view from the connected documents' view list. If the
      * last view is going to be closed, the eventFilter() tests if the document is modified; if yes, it asks the user to
      * save the document. If the document title contains "Untitled", slotFileSaveAs() gets called to get a save name and path.
      */
    virtual bool eventFilter (QObject * object, QEvent * event);

    /** creates a new child window. The document that will be connected to it
     * has to be created before and the instances filled, with e.g. openDocument().
     * Then call createClient() to get a new MDI child window.
     * @see F4lmDoc#addView
     * @see F4lmDoc#openDocument
     * @param doc pointer to the document instance that the view will
     * be connected to.
     */
    void createClient (F4lmDoc * doc);


private slots:

    /** generate a new document in the actual view */
    void slotFileNew ();
    void slotfileOpenAsLibrary ();
    void slotfileSaveAsTemplate ();
    void slotfileRevert ();
    void slotfileImport ();
    void slotfileImportToLibrary ();
    void slotfileExportMovie ();
    void slotfileExportImage ();
    void slotfilePublishSetting ();
    void slotfilePublishPreview_Default ();
    void slotfilePublishPreview_Flash ();
    void slotfilePublishPreview_Html ();
    void slotfilePublishPreview_GIF ();
    void slotfilePublishPreview_JPEG ();
    void slotfilePublishPreview_PNG ();
    void slotfilePublishPreview_Projector ();
    void slotfilePublishPreview_Quicktime ();
    void slotfilePublish ();

    void slotfilePageSetup ();

    void slotfilePrintPreview ();

    void slotfileSend ();

    void slotfileRecentFile ();

    /** open a document */
    void slotFileOpen ();

    /** save a document */
    void slotFileSave ();

    /** save a document under a different filename*/
    void slotFileSaveAs ();

    /** close the actual file */
    void slotFileClose ();

    /** print the actual file */
    void slotFilePrint ();

    /** exits the application */
    void slotFileQuit ();

        /// Makes new document from template (not written so far)
    void slotfileNewFromTemplate ();


    /** reverts the last editing action */
    void slotEditUndo ();

    void sloteditRedo ();

    /** put the marked text/object into the clipboard and remove
     * it from the document */
    void slotEditCut ();

    /** put the marked text/object into the clipboard*/
    void slotEditCopy ();

    /** paste the clipboard into the document*/
    void slotEditPaste ();

    void sloteditPasteinPlace ();
    void sloteditPasteSpecial ();
    void sloteditClear ();
    void sloteditDuplicate ();
    void sloteditSelectAll ();
    void sloteditDeselectAll ();
    void sloteditCutFrames ();
    void sloteditCopyFrames ();
    void sloteditPasteFrames ();
    void sloteditClearFrames ();
    void sloteditSelectAllFrames ();
    void sloteditEditSymbols ();
    void sloteditEditSelected ();
    void sloteditEditInPlace ();
    void sloteditEditAll ();
    void sloteditPrefences ();
    void sloteditKeyboardShourtCuts ();
    void sloteditFontMapping ();

    /** toggle the toolbar*/
    void slotViewToolBar (bool toggle);

    /** toggle the statusbar*/
    void slotViewStatusBar (bool toggle);

    void slotviewFirst ();
    void slotviewPrevious ();
    void slotviewNext ();
    void slotviewLast ();
    void slotviewScenes ();
    void slotviewZoomIn ();
    void slotviewZoomOut ();
    void slotviewMagnification25 ();
    void slotviewMagnification50 ();
    void slotviewMagnification100 ();
    void slotviewMagnification200 ();
    void slotviewMagnification400 ();
    void slotviewMagnification800 ();
    void slotviewShowFrame ();
    void slotviewShowAll ();
    void slotviewOutlines ();
    void slotviewFast ();
    void slotviewAntialias ();
    void slotviewAntialiasText ();
    void slotviewTimeline ();
    void slotviewWorkArea ();
    void slotviewRulers ();
    void slotviewShowGrid ();
    void slotviewSnaptoGrid ();
    void slotviewEditGrid ();
    void slotviewShowGuides ();
    void slotviewLockGuides ();
    void slotviewSnaptoGuides ();
    void slotviewEditGuides ();
    void slotviewSnaptoPixels ();
    void slotviewSnaptoObjects ();
    void slotviewShowShapeHints ();
    void slotviewHideEdges ();
    void slotviewHidePanels ();
    void slotviewToolBar ();
    void slotviewStatusBar ();

    void slotinsertConverttoSymbol ();
    void slotinsertNewSymbol ();
    void slotinsertLayer ();
    void slotinsertLayerFolder ();
    void slotinsertMotionGuide ();
    void slotinsertFrame ();
    void slotinsertRemoveFrames ();
    void slotinsertKeyframe ();
    void slotinsertBlankKeyframe ();
    void slotinsertClearKeyframe ();
    void slotinsertCreateMotionTween ();
    void slotinsertScene ();
    void slotinsertRemoveScene ();

    void slotmodifyLayer ();
    void slotmodifyScene ();
    void slotmodifyDocument ();
    void slotmodifySmooth ();
    void slotmodifyStraighten ();
    void slotmodifyOptimize ();
    void slotmodifyConvertLinestoFills ();
    void slotmodifyExpandFill ();
    void slotmodifySoftenFillEdges ();
    void slotmodifyAddShapeHint ();
    void slotmodifyRemoveAllHints ();
    void slotmodifySwapSymbol ();
    void slotmodifyDuplicateSymbol ();
    void slotmodifySwapBitmap ();
    void slotmodifyTraceBitmap ();
    void slotmodifyFreeTransform ();
    void slotmodifyDistort ();
    void slotmodifyEnvelope ();
    void slotmodifyScale ();
    void slotmodifyRotateandSkew ();
    void slotmodifyScaleandRotate ();
    void slotmodifyRotate90CW ();
    void slotmodifyRotate90CCW ();
    void slotmodifyFlipVertical ();
    void slotmodifyFlipHorizontal ();
    void slotmodifyRemoveTransform ();
    void slotmodifyBringtoFront ();
    void slotmodifyBringForward ();
    void slotmodifySendBackward ();
    void slotmodifySendtoBack ();
    void slotmodifyLock ();
    void slotmodifyUnlockAll ();
    void slotmodifyReverse ();
    void slotmodifySynchronizeSymbols ();
    void slotmodifyConverttoKeyframes ();
    void slotmodifyConverttoBlankKeyframes ();
    void slotmodifyGroup ();
    void slotmodifyUngroup ();
    void slotmodifyBreakApart ();
    void slotmodifyDistributetoLayers ();

    void slottextFontFace ();
    void slottext8 ();
    void slottext9 ();
    void slottext10 ();
    void slottext11 ();
    void slottext12 ();
    void slottext14 ();
    void slottext18 ();
    void slottext24 ();
    void slottext36 ();
    void slottext48 ();
    void slottext72 ();
    void slottext96 ();
    void slottext120 ();
    void slottextPlain ();
    void slottextBold ();
    void slottextItalic ();
    void slottextSubscript ();
    void slottextSuperscript ();
    void slottextAlignLeft ();
    void slottextAlignCenter ();
    void slottextAlignRight ();
    void slottextJustify ();
    void slottextIncrease ();
    void slottextDecrease ();
    void slottextReset ();
    void slottextScrollable ();

       ///////control menu
    void slotcontrolPlay ();
    void slotcontrolRewind ();
    void slotcontrolGoToEnd ();
    void slotcontrolStepForward ();
    void slotcontrolStepBackward ();
    void slotcontrolTestMovie ();
    void slotcontrolDebugMovie ();
    void slotcontrolTestScene ();
    void slotcontrolLoopPlayback ();
    void slotcontrolPlayAllScenes ();
    void slotcontrolEnableSimpleFrameActions ();
    void slotcontrolEnableSimpleButtons ();
    void slotcontrolMuteSounds ();
    void slotcontrolEnableLivePreview ();

       //window menu
    void slotwindowTile ();
    void slotwindowCascade ();
    void slotwindowMain ();
    void slotwindowStatus ();
    void slotwindowController ();
    void slotwindowAnswers ();
    void slotwindowAlign ();
    void slotwindowColorMixer ();
    void slotwindowColorSwatches ();
    void slotwindowInfo ();
    void slotwindowScene ();
    void slotwindowTransform ();
    void slotwindowActions ();
    void slotwindowDebugger ();
    void slotwindowMovieExplorer ();
    void slotwindowReference ();
    void slotwindowOutput ();
    void slotwindowAccessibility ();
    void slotwindowComponents ();
    void slotwindowComponentParameters ();
    void slotwindowLibrary ();
    void slotwindowlibraries ();
    void slotwindowPanelSets ();
    void slotwindowSavePanelLayout ();
    void slotwindowCloseAllPanels ();

        //////////help menu
    void slothelpUsingF4l ();
    void slothelpActionScriptDictionary ();
    void slothelpF4lExchange ();
    void slothelpManageExtensions ();
    void slothelpSamples ();
    void slothelpF4lSupportCenter ();
    void slothelpRegisterF4l ();

    /** creates a new view for the current document */
    void slotWindowNewWindow ();

    /** shows an about dlg*/
    void slotHelpAbout ();

    /** change the status message of the whole statusbar temporary */
    void slotStatusHelpMsg (const QString & text);

    /** gets called when the window menu is activated; recreates the window menu with all opened window titles. */
    void windowMenuAboutToShow ();

    /** activates the MDI child widget when it gets selected from the window menu. */
    void windowMenuActivated (int id);
    void slotWindowProperities ();
    void slotWindowTools ();
    void slotWindowTimeLine ();


private:
        /// This function fills stringTable with integer and strings
    void fillTheStringTable ();


    /** initializes all QActions of the application */
    void initActions ();

    /** initMenuBar creates the menu_bar and inserts the menuitems */
    void initMenuBar ();

    /** this creates the toolbars. Change the toobar look and add new toolbars in this
     * function */
    void initToolBar ();

    /** setup the statusbar */
    void initStatusBar ();

    /** setup the mainview*/
    void initView ();


    /** file_menu contains all items of the menubar entry "File" */
    QPopupMenu * pFileMenu;

    /** edit_menu contains all items of the menubar entry "Edit" */
    QPopupMenu * pEditMenu;

    /** view_menu contains all items of the menubar entry "View" */
    QPopupMenu * pViewMenu;

    /** view_menu contains all items of the menubar entry "Help" */
    QPopupMenu * pHelpMenu;

    /** the window menu */
    QPopupMenu * pWindowMenu;

    /** Flash specific menus*/
    QPopupMenu * pInsertMenu;
    QPopupMenu * pModifyMenu;
    QPopupMenu * pTextMenu;
    QPopupMenu * pControlMenu;

    QToolBar * fileToolbar;

    /** pWorkspace is the MDI frame widget that handles MDI child widgets. Inititalized in
      * initView()
      */
    QWorkspace * pWorkspace;

    /** the printer instance */
    QPrinter * printer;

    /** a counter that gets increased each time the user creates a new document with "File"->"New" */
    int untitledCount;

    /** a list of all open documents. If the last window of a document gets closed, the installed eventFilter
     * removes this document from the list. The document list is checked for modified documents when the user
     * is about to close the application. */
    QList < F4lmDoc > *pDocList;

    QAction * fileNew;
    QAction * fileNewFromTemplate;
    QAction * fileOpen;
    QAction * fileOpenAsLibrary;
    QAction * fileSave;
    QAction * fileSaveAs;
    QAction * fileSaveAsTemplate;
    QAction * fileRevert;
    QAction * fileImport;
    QAction * fileImportToLibrary;
    QAction * fileExportMovie;
    QAction * fileExportImage;
    QAction * filePublishSetting;
    QAction * filePublishPreview_Default;
    QAction * filePublishPreview_Flash;
    QAction * filePublishPreview_Html;
    QAction * filePublishPreview_GIF;
    QAction * filePublishPreview_JPEG;
    QAction * filePublishPreview_PNG;
    QAction * filePublishPreview_Projector;
    QAction * filePublishPreview_Quicktime;
    QAction * filePublish;
    QAction * filePageSetup;
    QAction * filePrintPreview;
    QAction * fileRecentFile;
    QAction * fileClose;
    QAction * filePrint;
    QAction * fileSend;
    QAction * fileQuit;

     /////////////////Edit Menu
    QAction * editUndo;
    QAction * editRedo;
        //seperator
    QAction * editCut;
    QAction * editCopy;
    QAction * editPaste;
    QAction * editPasteinPlace;
    QAction * editPasteSpecial;
    QAction * editClear;
        //seperator
    QAction * editDuplicate;
    QAction * editSelectAll;
    QAction * editDeselectAll;
        //seperator
    QAction * editCutFrames;
    QAction * editCopyFrames;
    QAction * editPasteFrames;
    QAction * editClearFrames;
    QAction * editSelectAllFrames;
        //seperator
    QAction * editEditSymbols;
    QAction * editEditSelected;
    QAction * editEditInPlace;
    QAction * editEditAll;
        //seperator
    QAction * editPrefences;
    QAction * editKeyboardShourtCuts;
    QAction * editFontMapping;
        
	////////////////View Menu
    //Goto;
    QAction * viewFirst;
    QAction * viewPrevious;
    QAction * viewNext;
    QAction * viewLast;
        //SEPARATOR
    QAction * viewScenes;
        //SEPARATOR
    QAction * viewZoomIn;
    QAction * viewZoomOut;
        //Magnification;
    QAction * viewMagnification25;
    QAction * viewMagnification50;
    QAction * viewMagnification100;
    QAction * viewMagnification200;
    QAction * viewMagnification400;
    QAction * viewMagnification800;
        //SEPARATOR
    QAction * viewShowFrame;
    QAction * viewShowAll;
        //SEPARATOR
    QActionGroup * viewAction;
    QAction * viewOutlines;
    QAction * viewFast;
    QAction * viewAntialias;
    QAction * viewAntialiasText;
        //SEPARATOR
    QAction * viewTimeline;
    QAction * viewWorkArea;
        //SEPARATOR
    QAction * viewRulers;
        //Grid;
    QAction * viewShowGrid;
    QAction * viewSnaptoGrid;
    QAction * viewEditGrid;
        //Guides;
    QAction * viewShowGuides;
    QAction * viewLockGuides;
    QAction * viewSnaptoGuides;
    QAction * viewEditGuides;
        //SEPARATOR
    QAction * viewSnaptoPixels;
    QAction * viewSnaptoObjects;
        //SEPARATOR
    QAction * viewShowShapeHints;
        //SEPARATOR
    QAction * viewHideEdges;
    QAction * viewHidePanels;
    QAction * viewToolBar;
    QAction * viewStatusBar;

        ////////////////////insert Menu
    QAction * insertConverttoSymbol;
    QAction * insertNewSymbol;
        //SEPARATOR
    QAction * insertLayer;
    QAction * insertLayerFolder;
    QAction * insertMotionGuide;
        //SEPARATOR
    QAction * insertFrame;
    QAction * insertRemoveFrames;
        //SEPARATOR
    QAction * insertKeyframe;
    QAction * insertBlankKeyframe;
    QAction * insertClearKeyframe;
        //SEPARATOR
    QAction * insertCreateMotionTween;
        //SEPARATOR
    QAction * insertScene;
    QAction * insertRemoveScene;

        ////////////////////////modify menu
    QAction * modifyLayer;
    QAction * modifyScene;
    QAction * modifyDocument;
        //seperator
    QAction * modifySmooth;
    QAction * modifyStraighten;
    QAction * modifyOptimize;
        // Shape
    QAction * modifyConvertLinestoFills;
    QAction * modifyExpandFill;
    QAction * modifySoftenFillEdges;
        //seperator
    QAction * modifyAddShapeHint;
    QAction * modifyRemoveAllHints;
        //seperator
    QAction * modifySwapSymbol;
    QAction * modifyDuplicateSymbol;
        //seperator
    QAction * modifySwapBitmap;
    QAction * modifyTraceBitmap;
        //seperator
        // Transform
    QAction * modifyFreeTransform;
    QAction * modifyDistort;
    QAction * modifyEnvelope;
    QAction * modifyScale;
    QAction * modifyRotateandSkew;
    QAction * modifyScaleandRotate;
        //seperator
    QAction * modifyRotate90CW;
    QAction * modifyRotate90CCW;
        //seperator
    QAction * modifyFlipVertical;
    QAction * modifyFlipHorizontal;
        //seperator
    QAction * modifyRemoveTransform;
        // Arrange
    QAction * modifyBringtoFront;
    QAction * modifyBringForward;
    QAction * modifySendBackward;
    QAction * modifySendtoBack;
        //seperator
    QAction * modifyLock;
    QAction * modifyUnlockAll;
        //seperator
        // Frames
    QAction * modifyReverse;
    QAction * modifySynchronizeSymbols;
    QAction * modifyConverttoKeyframes;
    QAction * modifyConverttoBlankKeyframes;
        //seperator
    QAction * modifyGroup;
    QAction * modifyUngroup;
        //seperator
    QAction * modifyBreakApart;
    QAction * modifyDistributetoLayers;

     ///////////////////////text menu
     // Font
    QAction * textFontFace;
        // Size
    QAction * text8;
    QAction * text9;
    QAction * text10;
    QAction * text11;
    QAction * text12;
    QAction * text14;
    QAction * text18;
    QAction * text24;
    QAction * text36;
    QAction * text48;
    QAction * text72;
    QAction * text96;
    QAction * text120;
        // Style
    QAction * textPlain;
        //seperator
    QAction * textBold;
    QAction * textItalic;
        //seperator
    QAction * textSubscript;
    QAction * textSuperscript;
        //seperator
        // Align
    QAction * textAlignLeft;
    QAction * textAlignCenter;
    QAction * textAlignRight;
    QAction * textJustify;
        // Tracking
    QAction * textIncrease;
    QAction * textDecrease;
        //seperator
    QAction * textReset;
        //seperator
    QAction * textScrollable;

     ////////////////////control menu
    QAction * controlPlay;
    QAction * controlRewind;
    QAction * controlGoToEnd;
        //seperator
    QAction * controlStepForward;
    QAction * controlStepBackward;
        //seperator
    QAction * controlTestMovie;
    QAction * controlDebugMovie;
    QAction * controlTestScene;
        //seperator
    QAction * controlLoopPlayback;
    QAction * controlPlayAllScenes;
        //seperator
    QAction * controlEnableSimpleFrameActions;
    QAction * controlEnableSimpleButtons;
    QAction * controlMuteSounds;
    QAction * controlEnableLivePreview;

     ///////////////window menu
    QActionGroup * windowAction;
    QAction * windowNewWindow;
    QAction * windowTile;
    QAction * windowCascade;
    QAction * windowProperties;
    QAction * windowTimeLine;
    QAction * windowTools;
        //seperator
        // Toolbars
        //QAction *windowMain;   |these two option taken from view actions
        //QAction *windowStatus; |
    QAction * windowController;
    QAction * windowAnswers;
        //seperator
    QAction * windowAlign;
    QAction * windowColorMixer;
    QAction * windowColorSwatches;
    QAction * windowInfo;
    QAction * windowScene;
    QAction * windowTransform;
        //seperator
    QAction * windowActions;
    QAction * windowDebugger;
    QAction * windowMovieExplorer;
    QAction * windowReference;
    QAction * windowOutput;
        //seperator
    QAction * windowAccessibility;
    QAction * windowComponents;
    QAction * windowComponentParameters;
    QAction * windowLibrary;
        // Common Libraries
    QAction * windowlibraries;
        //seperator
        // Panel Sets
    QAction * windowPanelSets;
    QAction * windowSavePanelLayout;
    QAction * windowCloseAllPanels;

        ///////////////////////help menu
    QAction * helpUsingF4l;
    QAction * helpActionScriptDictionary;
        //seperator
    QAction * helpF4lExchange;
    QAction * helpManageExtensions;
    QAction * helpSamples;
        //seperator
    QAction * helpF4lSupportCenter;
    QAction * helpRegisterF4l;
        //seperator
    QAction * helpAboutApp;

};

class CFilePreview:public QLabel, public QFilePreview
{
public:
    CFilePreview (QWidget * parent = 0):QLabel (parent)
    {}

    void previewUrl (const QUrl & u);
};

#endif


