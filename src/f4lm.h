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
#include <q3mainwindow.h>
#include <Q3Action>
#include <qworkspace.h>
#include <qmenubar.h>
#include <q3toolbar.h>
#include <qstatusbar.h>
#include <q3whatsthis.h>
#include <q3popupmenu.h>
#include <q3accel.h>
#include <qtoolbutton.h>
#include <qmessagebox.h>
#include <q3filedialog.h>
#include <qprinter.h>
#include <qstring.h>
#include <qpixmap.h>
//Added by qt3to4:
#include <QLabel>
#include <QEvent>
#include <Q3ActionGroup>
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
class F4lmApp:public Q3MainWindow
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
    Q3DockWindow * propertiesDockableWindow;
    Q3DockWindow * colorDialogDockableWindow;
    Q3DockWindow * colorSwatchesDockableWindow;
    Q3DockWindow * toolsDockableWindow;
    Q3DockWindow * timeLineDockableWindow;
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


    /** initializes all Q3Actions of the application */
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
    Q3PopupMenu * pFileMenu;

    /** edit_menu contains all items of the menubar entry "Edit" */
    Q3PopupMenu * pEditMenu;

    /** view_menu contains all items of the menubar entry "View" */
    Q3PopupMenu * pViewMenu;

    /** view_menu contains all items of the menubar entry "Help" */
    Q3PopupMenu * pHelpMenu;

    /** the window menu */
    Q3PopupMenu * pWindowMenu;

    /** Flash specific menus*/
    Q3PopupMenu * pInsertMenu;
    Q3PopupMenu * pModifyMenu;
    Q3PopupMenu * pTextMenu;
    Q3PopupMenu * pControlMenu;

    Q3ToolBar * fileToolbar;

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
    QList < F4lmDoc* > pDocList;

    Q3Action * fileNew;
    Q3Action * fileNewFromTemplate;
    Q3Action * fileOpen;
    Q3Action * fileOpenAsLibrary;
    Q3Action * fileSave;
    Q3Action * fileSaveAs;
    Q3Action * fileSaveAsTemplate;
    Q3Action * fileRevert;
    Q3Action * fileImport;
    Q3Action * fileImportToLibrary;
    Q3Action * fileExportMovie;
    Q3Action * fileExportImage;
    Q3Action * filePublishSetting;
    Q3Action * filePublishPreview_Default;
    Q3Action * filePublishPreview_Flash;
    Q3Action * filePublishPreview_Html;
    Q3Action * filePublishPreview_GIF;
    Q3Action * filePublishPreview_JPEG;
    Q3Action * filePublishPreview_PNG;
    Q3Action * filePublishPreview_Projector;
    Q3Action * filePublishPreview_Quicktime;
    Q3Action * filePublish;
    Q3Action * filePageSetup;
    Q3Action * filePrintPreview;
    Q3Action * fileRecentFile;
    Q3Action * fileClose;
    Q3Action * filePrint;
    Q3Action * fileSend;
    Q3Action * fileQuit;

     /////////////////Edit Menu
    Q3Action * editUndo;
    Q3Action * editRedo;
        //seperator
    Q3Action * editCut;
    Q3Action * editCopy;
    Q3Action * editPaste;
    Q3Action * editPasteinPlace;
    Q3Action * editPasteSpecial;
    Q3Action * editClear;
        //seperator
    Q3Action * editDuplicate;
    Q3Action * editSelectAll;
    Q3Action * editDeselectAll;
        //seperator
    Q3Action * editCutFrames;
    Q3Action * editCopyFrames;
    Q3Action * editPasteFrames;
    Q3Action * editClearFrames;
    Q3Action * editSelectAllFrames;
        //seperator
    Q3Action * editEditSymbols;
    Q3Action * editEditSelected;
    Q3Action * editEditInPlace;
    Q3Action * editEditAll;
        //seperator
    Q3Action * editPrefences;
    Q3Action * editKeyboardShourtCuts;
    Q3Action * editFontMapping;
        
	////////////////View Menu
    //Goto;
    Q3Action * viewFirst;
    Q3Action * viewPrevious;
    Q3Action * viewNext;
    Q3Action * viewLast;
        //SEPARATOR
    Q3Action * viewScenes;
        //SEPARATOR
    Q3Action * viewZoomIn;
    Q3Action * viewZoomOut;
        //Magnification;
    Q3Action * viewMagnification25;
    Q3Action * viewMagnification50;
    Q3Action * viewMagnification100;
    Q3Action * viewMagnification200;
    Q3Action * viewMagnification400;
    Q3Action * viewMagnification800;
        //SEPARATOR
    Q3Action * viewShowFrame;
    Q3Action * viewShowAll;
        //SEPARATOR
    Q3ActionGroup * viewAction;
    Q3Action * viewOutlines;
    Q3Action * viewFast;
    Q3Action * viewAntialias;
    Q3Action * viewAntialiasText;
        //SEPARATOR
    Q3Action * viewTimeline;
    Q3Action * viewWorkArea;
        //SEPARATOR
    Q3Action * viewRulers;
        //Grid;
    Q3Action * viewShowGrid;
    Q3Action * viewSnaptoGrid;
    Q3Action * viewEditGrid;
        //Guides;
    Q3Action * viewShowGuides;
    Q3Action * viewLockGuides;
    Q3Action * viewSnaptoGuides;
    Q3Action * viewEditGuides;
        //SEPARATOR
    Q3Action * viewSnaptoPixels;
    Q3Action * viewSnaptoObjects;
        //SEPARATOR
    Q3Action * viewShowShapeHints;
        //SEPARATOR
    Q3Action * viewHideEdges;
    Q3Action * viewHidePanels;
    Q3Action * viewToolBar;
    Q3Action * viewStatusBar;

        ////////////////////insert Menu
    Q3Action * insertConverttoSymbol;
    Q3Action * insertNewSymbol;
        //SEPARATOR
    Q3Action * insertLayer;
    Q3Action * insertLayerFolder;
    Q3Action * insertMotionGuide;
        //SEPARATOR
    Q3Action * insertFrame;
    Q3Action * insertRemoveFrames;
        //SEPARATOR
    Q3Action * insertKeyframe;
    Q3Action * insertBlankKeyframe;
    Q3Action * insertClearKeyframe;
        //SEPARATOR
    Q3Action * insertCreateMotionTween;
        //SEPARATOR
    Q3Action * insertScene;
    Q3Action * insertRemoveScene;

        ////////////////////////modify menu
    Q3Action * modifyLayer;
    Q3Action * modifyScene;
    Q3Action * modifyDocument;
        //seperator
    Q3Action * modifySmooth;
    Q3Action * modifyStraighten;
    Q3Action * modifyOptimize;
        // Shape
    Q3Action * modifyConvertLinestoFills;
    Q3Action * modifyExpandFill;
    Q3Action * modifySoftenFillEdges;
        //seperator
    Q3Action * modifyAddShapeHint;
    Q3Action * modifyRemoveAllHints;
        //seperator
    Q3Action * modifySwapSymbol;
    Q3Action * modifyDuplicateSymbol;
        //seperator
    Q3Action * modifySwapBitmap;
    Q3Action * modifyTraceBitmap;
        //seperator
        // Transform
    Q3Action * modifyFreeTransform;
    Q3Action * modifyDistort;
    Q3Action * modifyEnvelope;
    Q3Action * modifyScale;
    Q3Action * modifyRotateandSkew;
    Q3Action * modifyScaleandRotate;
        //seperator
    Q3Action * modifyRotate90CW;
    Q3Action * modifyRotate90CCW;
        //seperator
    Q3Action * modifyFlipVertical;
    Q3Action * modifyFlipHorizontal;
        //seperator
    Q3Action * modifyRemoveTransform;
        // Arrange
    Q3Action * modifyBringtoFront;
    Q3Action * modifyBringForward;
    Q3Action * modifySendBackward;
    Q3Action * modifySendtoBack;
        //seperator
    Q3Action * modifyLock;
    Q3Action * modifyUnlockAll;
        //seperator
        // Frames
    Q3Action * modifyReverse;
    Q3Action * modifySynchronizeSymbols;
    Q3Action * modifyConverttoKeyframes;
    Q3Action * modifyConverttoBlankKeyframes;
        //seperator
    Q3Action * modifyGroup;
    Q3Action * modifyUngroup;
        //seperator
    Q3Action * modifyBreakApart;
    Q3Action * modifyDistributetoLayers;

     ///////////////////////text menu
     // Font
    Q3Action * textFontFace;
        // Size
    Q3Action * text8;
    Q3Action * text9;
    Q3Action * text10;
    Q3Action * text11;
    Q3Action * text12;
    Q3Action * text14;
    Q3Action * text18;
    Q3Action * text24;
    Q3Action * text36;
    Q3Action * text48;
    Q3Action * text72;
    Q3Action * text96;
    Q3Action * text120;
        // Style
    Q3Action * textPlain;
        //seperator
    Q3Action * textBold;
    Q3Action * textItalic;
        //seperator
    Q3Action * textSubscript;
    Q3Action * textSuperscript;
        //seperator
        // Align
    Q3Action * textAlignLeft;
    Q3Action * textAlignCenter;
    Q3Action * textAlignRight;
    Q3Action * textJustify;
        // Tracking
    Q3Action * textIncrease;
    Q3Action * textDecrease;
        //seperator
    Q3Action * textReset;
        //seperator
    Q3Action * textScrollable;

     ////////////////////control menu
    Q3Action * controlPlay;
    Q3Action * controlRewind;
    Q3Action * controlGoToEnd;
        //seperator
    Q3Action * controlStepForward;
    Q3Action * controlStepBackward;
        //seperator
    Q3Action * controlTestMovie;
    Q3Action * controlDebugMovie;
    Q3Action * controlTestScene;
        //seperator
    Q3Action * controlLoopPlayback;
    Q3Action * controlPlayAllScenes;
        //seperator
    Q3Action * controlEnableSimpleFrameActions;
    Q3Action * controlEnableSimpleButtons;
    Q3Action * controlMuteSounds;
    Q3Action * controlEnableLivePreview;

     ///////////////window menu
    Q3ActionGroup * windowAction;
    Q3Action * windowNewWindow;
    Q3Action * windowTile;
    Q3Action * windowCascade;
    Q3Action * windowProperties;
    Q3Action * windowTimeLine;
    Q3Action * windowTools;
        //seperator
        // Toolbars
        //Q3Action *windowMain;   |these two option taken from view actions
        //Q3Action *windowStatus; |
    Q3Action * windowController;
    Q3Action * windowAnswers;
        //seperator
    Q3Action * windowAlign;
    Q3Action * windowColorMixer;
    Q3Action * windowColorSwatches;
    Q3Action * windowInfo;
    Q3Action * windowScene;
    Q3Action * windowTransform;
        //seperator
    Q3Action * windowActions;
    Q3Action * windowDebugger;
    Q3Action * windowMovieExplorer;
    Q3Action * windowReference;
    Q3Action * windowOutput;
        //seperator
    Q3Action * windowAccessibility;
    Q3Action * windowComponents;
    Q3Action * windowComponentParameters;
    Q3Action * windowLibrary;
        // Common Libraries
    Q3Action * windowlibraries;
        //seperator
        // Panel Sets
    Q3Action * windowPanelSets;
    Q3Action * windowSavePanelLayout;
    Q3Action * windowCloseAllPanels;

        ///////////////////////help menu
    Q3Action * helpUsingF4l;
    Q3Action * helpActionScriptDictionary;
        //seperator
    Q3Action * helpF4lExchange;
    Q3Action * helpManageExtensions;
    Q3Action * helpSamples;
        //seperator
    Q3Action * helpF4lSupportCenter;
    Q3Action * helpRegisterF4l;
        //seperator
    Q3Action * helpAboutApp;

};

class CFilePreview:public QLabel, public Q3FilePreview
{
public:
    CFilePreview (QWidget * parent = 0):QLabel (parent)
    {}

    void previewUrl (const Q3Url & u);
};

#endif


