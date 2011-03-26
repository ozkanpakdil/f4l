/***************************************************************************
              f4lm.cpp  -  description
                 -------------------
    begin                : Sat Jun  7 02:29:46 EEST 2003
    copyright            : (C) 2003 by Özkan pakdil
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

// Qt includes
#include <q3vbox.h>
#include <q3accel.h>
#include <q3dockwindow.h>
#include <qcolor.h>
#include <qimage.h>
#include <q3dockarea.h>
#include <qmap.h>
//#include <qfocusdata.h>
//Added by qt3to4:
#include <QPixmap>
#include <QCloseEvent>
#include <Q3ValueList>
#include <Q3TextStream>
#include <QEvent>
#include <QDebug>
#include <Q3Frame>
#include <Q3PopupMenu>
#include <Q3ActionGroup>
//#include <iostream.h>

// application specific includes
#include "f4lmview.h"
#include "f4lmdoc.h"
#include "f4lm.h"
#include "timeline.h"
#include "tools.h"
#include "ccolordialog.h"

#include "cursor/filenew.xpm"
#include "cursor/fileopen.xpm"
#include "cursor/filesave.xpm"

F4lmApp::F4lmApp ()
{
  setName ("F4lmApp");
  setCaption (tr ("F4lm "));
  printer = new QPrinter;
  untitledCount = 0;
  pDocList = QList < F4lmDoc* > ();
  //pDocList->setAutoDelete (true);

  ///////////////////////////////////////////////////////////////////
  // call inits to invoke all other construction parts
  initView ();
  initActions ();
  initToolBar ();
  initStatusBar ();
  initDockWindows ();
  initMenuBar ();
  //resize( 450, 400 );

  //viewToolBar->setOn(true);
  //  viewStatusBar->setOn(true);
  fileToolbar->hide ();

  QApplication::setGlobalMouseTracking (true);

}

F4lmApp::~F4lmApp ()
{
  delete printer;
}

void F4lmApp::initActions ()
{
  // fillTheStringTable();
  QPixmap openIcon, saveIcon, newIcon;
  newIcon = QPixmap (filenew);
  openIcon = QPixmap (fileopen);
  saveIcon = QPixmap (filesave);

  fileNew = new Q3Action (tr ("New File"), newIcon, tr ("&New"), Q3Accel::stringToKey (tr ("Ctrl+N")), this);
  fileNew->setStatusTip (tr ("Creates a new document"));
  fileNew->setWhatsThis (tr ("New File\n\nCreates a new document"));
  connect (fileNew, SIGNAL (activated ()), this, SLOT (slotFileNew ()));

  fileNewFromTemplate = new Q3Action (tr ("New From Template"), tr ("N&ew From Template"), 0, this);
  fileNewFromTemplate->setStatusTip (tr ("Create a new document from a template"));
  fileNewFromTemplate->setWhatsThis (tr ("New From Template\n\nCreate a new document from a template"));
  connect (fileNewFromTemplate, SIGNAL (activated ()), this, SLOT (slotfileNewFromTemplate ()));

  fileOpen = new Q3Action (tr ("Open File"), openIcon, tr ("&Open..."), 0, this);
  fileOpen->setStatusTip (tr ("Opens an existing document"));
  fileOpen->setWhatsThis (tr ("Open File\n\nOpens an existing document"));
  connect (fileOpen, SIGNAL (activated ()), this, SLOT (slotFileOpen ()));

  fileOpenAsLibrary = new Q3Action (tr ("Open as Library..."), tr ("Open as &Library..."), 0, this);
  fileOpenAsLibrary->setStatusTip (tr ("Open a document as a floating Library window"));
  fileOpenAsLibrary->setWhatsThis (tr ("Open as Library...\n\n Open a document as a floating Library window "));
  connect (fileOpenAsLibrary, SIGNAL (activated ()), this, SLOT (slotfileOpenAsLibrary ()));

  fileSaveAsTemplate = new Q3Action (tr ("Save As Template..."), tr ("Save As &Template..."), 0, this);
  fileSaveAsTemplate->setStatusTip (tr ("Save the active document as a template"));
  fileSaveAsTemplate->setWhatsThis (tr ("Save As Template...\n\n Save the active document as a template "));
  connect (fileSaveAsTemplate, SIGNAL (activated ()), this, SLOT (slotfileSaveAsTemplate ()));

  fileRevert = new Q3Action (tr ("Revert"), tr ("Rever&t"), 0, this);
  fileRevert->setStatusTip (tr ("Revert to the last saved version of the active document"));
  fileRevert->setWhatsThis (tr ("Revert\n\n Revert to the last saved version of the active document "));
  connect (fileRevert, SIGNAL (activated ()), this, SLOT (slotfileRevert ()));

  fileImport = new Q3Action (tr ("Import..."), tr ("&Import..."), 0, this);
  fileImport->setStatusTip (tr ("Import files created in another application"));
  fileImport->setWhatsThis (tr ("Import...\n\n Import files created in another application "));
  connect (fileImport, SIGNAL (activated ()), this, SLOT (slotfileImport ()));

  fileImportToLibrary = new Q3Action (tr ("Import to Library..."), tr ("&Import to Library..."), Q3Accel::stringToKey (tr ("Ctrl+Alt+R")), this);
  fileImportToLibrary->setStatusTip (tr ("Import files created in another application to the document library"));
  fileImportToLibrary->setWhatsThis (tr ("Import to Library...\n\n Import files created in another application to the document library "));
  connect (fileImportToLibrary, SIGNAL (activated ()), this, SLOT (slotfileImportToLibrary ()));

  fileExportMovie = new Q3Action (tr ("Export Movie..."), tr ("Export &Movie..."), Q3Accel::stringToKey (tr ("Ctrl+Alt+Shift+S")), this);
  fileExportMovie->setStatusTip (tr ("Save the document as a movie for use in another application"));
  fileExportMovie->setWhatsThis (tr ("Export Movie...\n\n Save the document as a movie for use in another application "));
  connect (fileExportMovie, SIGNAL (activated ()), this, SLOT (slotfileExportMovie ()));

  fileExportImage = new Q3Action (tr ("Export Image..."), tr ("&Export Image..."), 0, this);
  fileExportImage->setStatusTip (tr ("Save a drawing in a format for use in another application"));
  fileExportImage->setWhatsThis (tr ("Export Image...\n\n Save a drawing in a format for use in another application "));
  connect (fileExportImage, SIGNAL (activated ()), this, SLOT (slotfileExportImage ()));

  filePublishSetting = new Q3Action (tr ("Publish Settings..."), tr ("Publish Settin&gs..."), Q3Accel::stringToKey (tr ("Ctrl+Shift+F12")), this);
  filePublishSetting->setStatusTip (tr ("Modify publish settings\nPublish Settings"));
  filePublishSetting->setWhatsThis (tr ("Publish Settings...\n\n Modify publish settings\nPublish Settings "));
  connect (filePublishSetting, SIGNAL (activated ()), this, SLOT (slotfilePublishSetting ()));

  filePublishPreview_Default = new Q3Action (tr ("Default"), tr ("&Default"), Q3Accel::stringToKey (tr ("Ctrl+F12")), this);
  filePublishPreview_Default->setStatusTip (tr ("Publish and preview the document with the default format"));
  filePublishPreview_Default->setWhatsThis (tr ("Default\n\n Publish and preview the document with the default format "));
  connect (filePublishPreview_Default, SIGNAL (activated ()), this, SLOT (slotfilePublishPreview_Default ()));

  filePublishPreview_Flash = new Q3Action (tr ("Flash"), tr ("&Flash"), 0, this);
  filePublishPreview_Flash->setStatusTip (tr ("Publish and preview the document in the Flash (swf) format"));
  filePublishPreview_Flash->setWhatsThis (tr ("Flash\n\nPublish and preview the document in the Flash (swf) format "));
  connect (filePublishPreview_Flash, SIGNAL (activated ()), this, SLOT (slotfilePublishPreview_Flash ()));

  filePublishPreview_Html = new Q3Action (tr ("HTML"), tr ("&HTML"), 0, this);
  filePublishPreview_Html->setStatusTip (tr ("Publish and preview the document in HTML format"));
  filePublishPreview_Html->setWhatsThis (tr ("HTML\n\n Publish and preview the document in HTML format "));
  connect (filePublishPreview_Html, SIGNAL (activated ()), this, SLOT (slotfilePublishPreview_Html ()));

  filePublishPreview_GIF = new Q3Action (tr ("GIF"), tr ("&GIF"), 0, this);
  filePublishPreview_GIF->setStatusTip (tr ("Publish and preview the document as a GIF image"));
  filePublishPreview_GIF->setWhatsThis (tr ("GIF \n\n Publish and preview the document as a GIF image "));
  connect (filePublishPreview_GIF, SIGNAL (activated ()), this, SLOT (slotfilePublishPreview_GIF ()));

  filePublishPreview_JPEG = new Q3Action (tr ("JPEG"), tr ("&JPEG"), 0, this);
  filePublishPreview_JPEG->setStatusTip (tr ("Publish and preview the document as a JPEG image"));
  filePublishPreview_JPEG->setWhatsThis (tr ("JPEG\n\n Publish and preview the document as a JPEG image "));
  connect (filePublishPreview_JPEG, SIGNAL (activated ()), this, SLOT (slotfilePublishPreview_JPEG ()));

  filePublishPreview_PNG = new Q3Action (tr ("PNG"), tr ("&PNG"), 0, this);
  filePublishPreview_PNG->setStatusTip (tr ("Publish and preview the document as a PNG image"));
  filePublishPreview_PNG->setWhatsThis (tr ("PNG\n\n Publish and preview the document as a PNG image "));
  connect (filePublishPreview_PNG, SIGNAL (activated ()), this, SLOT (slotfilePublishPreview_PNG ()));

  filePublishPreview_Projector = new Q3Action (tr ("Projector"), tr ("P&rojector"), 0, this);
  filePublishPreview_Projector->setStatusTip (tr ("Publish and preview the document as a standalone projector"));
  filePublishPreview_Projector->setWhatsThis (tr ("Projector\n\n Publish and preview the document as a standalone projector "));
  connect (filePublishPreview_Projector, SIGNAL (activated ()), this, SLOT (slotfilePublishPreview_Projector ()));

  filePublishPreview_Quicktime = new Q3Action (tr ("QuickTime"), tr ("&QuickTime"), 0, this);
  filePublishPreview_Quicktime->setStatusTip (tr ("Publish and preview the document as a QuickTime movie"));
  filePublishPreview_Quicktime->setWhatsThis (tr ("QuickTime\n\n Publish and preview the document as a QuickTime movie "));
  connect (filePublishPreview_Quicktime, SIGNAL (activated ()), this, SLOT (slotfilePublishPreview_Quicktime ()));

  filePublish = new Q3Action (tr ("Publish"), tr ("Pu&blish"), Q3Accel::stringToKey (tr ("Shift+F12")), this);
  filePublish->setStatusTip (tr ("Publish document in selected formats\nPublish"));
  filePublish->setWhatsThis (tr ("Publish\n\n Publish document in selected formats\nPublish "));
  connect (filePublish, SIGNAL (activated ()), this, SLOT (slotfilePublish ()));

  filePageSetup = new Q3Action (tr ("Page Setup..."), tr ("Page Set&up..."), 0, this);
  filePageSetup->setStatusTip (tr ("Change the paper type and print margins"));
  filePageSetup->setWhatsThis (tr ("Page Setup...\n\n Change the paper type and print margins "));
  connect (filePageSetup, SIGNAL (activated ()), this, SLOT (slotfilePageSetup ()));

  filePrintPreview = new Q3Action (tr ("Print Preview"), tr ("Print Pre&view"), 0, this);
  filePrintPreview->setStatusTip (tr ("Show pages as they will appear on the printer\nPrint Preview"));
  filePrintPreview->setWhatsThis (tr ("Print Preview\n\n Show pages as they will appear on the printer\nPrint Preview "));
  connect (filePrintPreview, SIGNAL (activated ()), this, SLOT (slotfilePrintPreview ()));


  fileSend = new Q3Action (tr ("Send..."), tr ("Sen&d..."), 0, this);
  fileSend->setStatusTip (tr ("Send a mail message with an attached document"));
  fileSend->setWhatsThis (tr("Send...\n\n Send a mail message with an attached document "));
  connect (fileSend, SIGNAL (activated ()), this, SLOT (slotfileSend ()));

  fileRecentFile = new Q3Action (tr ("Recent File"), tr ("R&ecent File"), 0, this);
  fileRecentFile->setStatusTip (tr ("Open this document"));
  fileRecentFile->setWhatsThis (tr ("Recent File\n\n Open the recen file "));
  connect (fileRecentFile, SIGNAL (activated ()), this, SLOT (slotfileRecentFile ()));

  fileSave = new Q3Action (tr ("Save File"), saveIcon, tr ("&Save"), Q3Accel::stringToKey (tr ("Ctrl+S")), this);
  fileSave->setStatusTip (tr ("Saves the actual document"));
  fileSave->setWhatsThis (tr ("Save File.\n\nSaves the actual document"));
  connect (fileSave, SIGNAL (activated ()), this, SLOT (slotFileSave ()));

  fileSaveAs = new Q3Action (tr ("Save File As"), tr ("Save &as..."), 0, this);
  fileSaveAs->setStatusTip (tr ("Saves the actual document under a new filename"));
  fileSaveAs->setWhatsThis (tr ("Save As\n\nSaves the actual document under a new filename"));
  connect (fileSaveAs, SIGNAL (activated ()), this, SLOT (slotFileSave ()));

  fileClose = new Q3Action (tr ("Close File"), tr ("&Close"), Q3Accel::stringToKey (tr ("Ctrl+W")), this);
  fileClose->setStatusTip (tr ("Closes the actual document"));
  fileClose->setWhatsThis (tr ("Close File\n\nCloses the actual document"));
  connect (fileClose, SIGNAL (activated ()), this, SLOT (slotFileClose ()));

  filePrint = new Q3Action (tr ("Print File"), tr ("&Print"), Q3Accel::stringToKey (tr ("Ctrl+P")), this);
  filePrint->setStatusTip (tr ("Prints out the actual document"));
  filePrint->setWhatsThis (tr ("Print File\n\nPrints out the actual document"));
  connect (filePrint, SIGNAL (activated ()), this, SLOT (slotFilePrint ()));

  fileQuit = new Q3Action (tr ("Exit"), tr ("E&xit"), Q3Accel::stringToKey (tr ("Ctrl+Q")), this);
  fileQuit->setStatusTip (tr ("Quits the application"));
  fileQuit->setWhatsThis (tr ("Exit\n\nQuits the application"));
  connect (fileQuit, SIGNAL (activated ()), this, SLOT (slotFileQuit ()));

  /////////////////////////////////////////////////////////////////////////////////
  editCut = new Q3Action (tr ("Cut"), tr ("Cu&t"), Q3Accel::stringToKey (tr ("Ctrl+X")), this);
  editCut->setStatusTip (tr ("Cuts the selected section and puts it to the clipboard"));
  editCut->setWhatsThis (tr ("Cut\n\nCuts the selected section and puts it to the clipboard"));
  connect (editCut, SIGNAL (activated ()), this, SLOT (slotEditCut ()));

  editCopy =new Q3Action (tr ("Copy"), tr ("&Copy"), Q3Accel::stringToKey (tr ("Ctrl+C")), this);
  editCopy->setStatusTip (tr ("Copies the selected section to the clipboard"));
  editCopy->setWhatsThis (tr ("Copy\n\nCopies the selected section to the clipboard"));
  connect (editCopy, SIGNAL (activated ()), this, SLOT (slotEditCopy ()));

  editUndo = new Q3Action (tr ("Undo"), tr ("&Undo"), Q3Accel::stringToKey (tr ("Ctrl+Z")), this);
  editUndo->setStatusTip (tr ("Reverts the last editing action"));
  editUndo->setWhatsThis (tr ("Undo\n\nReverts the last editing action"));
  connect (editUndo, SIGNAL (activated ()), this, SLOT (slotEditUndo ()));

  editPaste = new Q3Action (tr ("Paste"), tr ("&Paste"),Q3Accel::stringToKey (tr ("Ctrl+V")), this);
  editPaste->setStatusTip (tr ("Pastes the clipboard contents to actual position"));
  editPaste-> setWhatsThis (tr("Paste\n\nPastes the clipboard contents to actual position"));
  connect (editPaste, SIGNAL (activated ()), this, SLOT (slotEditPaste ()));


  editRedo = new Q3Action (tr ("Redo"), tr ("&Redo"),Q3Accel::stringToKey (tr ("Ctrl+Y")), this);
  editRedo->setStatusTip (tr ("Redo the previously undone action\nRedo"));
  editRedo->setWhatsThis (tr ("Redo\n\nRedo the previously undone action\nRedo"));
  connect (editRedo, SIGNAL (activated ()), this, SLOT (sloteditRedo ()));

  editPasteinPlace =new Q3Action (tr ("Paste in Place"), tr ("Paste i&n Place"),Q3Accel::stringToKey (tr ("Ctrl+Shift+V")), this);
  editPasteinPlace->setStatusTip (tr("Insert the Clipboard contents without centering in the window"));
  editPasteinPlace->setWhatsThis (tr("Paste in Place\n\nInsert the Clipboard contents without centering in the window"));
  connect (editPasteinPlace, SIGNAL (activated ()), this,SLOT (sloteditPasteinPlace ()));


  editPasteSpecial =new Q3Action (tr ("Paste Special..."), tr ("Paste &Special..."), 0, this);
  editPasteSpecial->setStatusTip (tr("Insert the Clipboard contents with options"));
  editPasteSpecial->setWhatsThis (tr("Paste Special...\n\nInsert the Clipboard contents with options"));
  connect (editPasteSpecial, SIGNAL (activated ()), this, SLOT (sloteditPasteSpecial ()));

  editClear = new Q3Action (tr ("Clear"), tr ("Cle&ar"),  QKeySequence (Qt::Key_Backspace), this);
  editClear->setStatusTip (tr ("Delete the selection"));
  editClear->setWhatsThis (tr ("Clear\n\nDelete the selection"));
  connect (editClear, SIGNAL (activated ()), this, SLOT (sloteditClear ()));


  editDuplicate = new Q3Action (tr ("Duplicate"), tr ("&Duplicate"), QKeySequence (Qt::CTRL + Qt::Key_D), this);
  editDuplicate->setStatusTip (tr ("Duplicate the selection"));
  editDuplicate->setWhatsThis (tr ("Duplicate\n\nDuplicate the selection"));
  connect (editDuplicate, SIGNAL (activated ()), this,SLOT (sloteditDuplicate ()));

  editSelectAll = new Q3Action (tr ("Select All"), tr ("Select A&ll"), QKeySequence (Qt::CTRL + Qt::Key_A), this);
  editSelectAll->setStatusTip (tr ("Select the entire drawing"));
  editSelectAll->setWhatsThis (tr ("Select All\n\nSelect the entire drawing"));
  connect (editSelectAll, SIGNAL (activated ()), this, SLOT (sloteditSelectAll ()));

  editDeselectAll =new Q3Action (tr ("Deselect All"), tr ("D&eselect All"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_A), this);
  editDeselectAll->setStatusTip (tr ("Deselect all selected elements in the drawing"));
  editDeselectAll->setWhatsThis (tr("Deselect All\n\nDeselect all selected elements in the drawing"));
  connect (editDeselectAll, SIGNAL (activated ()), this,SLOT (sloteditDeselectAll ()));

  editCutFrames =new Q3Action (tr ("Cut Frames"), tr ("Cut Fra&mes"), 0, this);
  editCutFrames->setStatusTip (tr ("Cut the selected frames to the frame clipboard"));
  editCutFrames->setWhatsThis (tr("Cut Frames\n\nCut the selected frames to the frame clipboard"));
  connect (editCutFrames, SIGNAL (activated ()), this,SLOT (sloteditCutFrames ()));

  editCopyFrames =new Q3Action (tr ("Copy Frames"), tr ("C&opy Frames"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_C), this);
  editCopyFrames->setStatusTip (tr ("Copy the selected frames to the frame clipboard"));
  editCopyFrames->setWhatsThis (tr("Copy Frames\n\nCopy the selected frames to the frame clipboard"));
  connect (editCopyFrames, SIGNAL (activated ()), this,SLOT (sloteditCopyFrames ()));

  editPasteFrames =new Q3Action (tr ("Paste Frames"), tr ("Paste &Frames"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_V), this);
  editPasteFrames->setStatusTip (tr ("Paste frames from the frame clipboard"));
  editPasteFrames->setWhatsThis (tr("Paste Frames\n\nPaste frames from the frame clipboard"));
  connect (editPasteFrames, SIGNAL (activated ()), this, SLOT (sloteditPasteFrames ()));

  editClearFrames =new Q3Action (tr ("Clear Frames"), tr ("Clear F&rames"),QKeySequence (Qt::ALT + Qt::Key_Delete), this);
  editClearFrames->setStatusTip (tr ("Delete the selected frames"));
  editClearFrames->setWhatsThis (tr ("Clear Frames\n\nDelete the selected frames"));
  connect (editClearFrames, SIGNAL (activated ()), this,SLOT (sloteditClearFrames ()));

  editSelectAllFrames = new Q3Action (tr ("Select All Frames"), tr ("Select All Fram&es"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_A), this);
  editSelectAllFrames->setStatusTip (tr("Select all the frames in the current scene or symbol"));
  editSelectAllFrames->setWhatsThis (tr("Select All Frames\n\nSelect all the frames in the current scene or symbol"));
  connect (editSelectAllFrames, SIGNAL (activated ()), this, SLOT (sloteditSelectAllFrames ()));

  editEditSymbols = new Q3Action (tr ("Edit Symbols"), tr ("Edit S&ymbols"),QKeySequence (Qt::CTRL + Qt::Key_E), this);
  editEditSymbols->setStatusTip (tr ("Toggle between editing the symbol or movie scenes"));
  editEditSymbols->setWhatsThis (tr("Edit Symbols\n\nToggle between editing the symbol or movie scenes"));
  connect (editEditSymbols, SIGNAL (activated ()), this,SLOT (sloteditEditSymbols ()));

  editEditSelected =new Q3Action (tr ("Edit Selected"), tr ("Ed&it Selected"), 0, this);
  editEditSelected->setStatusTip (tr ("Edit the contents of the selected object"));
  editEditSelected->setWhatsThis (tr("Edit Selected\n\nEdit the contents of the selected object"));
  connect (editEditSelected, SIGNAL (activated ()), this, SLOT (sloteditEditSelected ()));

  editEditInPlace =new Q3Action (tr ("Edit in Place"), tr ("Edit in Place"), 0, this);
  editEditInPlace->setStatusTip (tr ("Edit the symbol in place\nEdit"));
  editEditInPlace->setWhatsThis (tr ("Edit in Place\n\nEdit the symbol in place\nEdit"));
  connect (editEditInPlace, SIGNAL (activated ()), this,SLOT (sloteditEditInPlace ()));

  editEditAll = new Q3Action (tr ("Edit All"), tr ("Edit &All"), 0, this);
  editEditAll->setStatusTip (tr ("Return to editing the entire drawing"));
  editEditAll->setWhatsThis (tr ("Edit All\n\nReturn to editing the entire drawing"));
  connect (editEditAll, SIGNAL (activated ()), this,SLOT (sloteditEditAll ()));


  editPrefences = new Q3Action (tr ("Preferences..."), tr ("Pre&ferences..."), 0, this);
  editPrefences->setStatusTip (tr ("Change various default settings"));
  editPrefences->setWhatsThis (tr ("Preferences...\n\nChange various default settings"));
  connect (editPrefences, SIGNAL (activated ()), this, SLOT (sloteditPrefences ()));

  editKeyboardShourtCuts =new Q3Action (tr ("Keyboard Shortcuts..."), tr ("&Keyboard Shortcuts..."), 0, this);
  editKeyboardShourtCuts->setStatusTip (tr ("Customize keyboard shortcuts for menus and tools"));
  editKeyboardShourtCuts->setWhatsThis (tr("Keyboard Shortcuts...\n\nCustomize keyboard shortcuts for menus and tools"));
  connect (editKeyboardShourtCuts, SIGNAL (activated ()), this,SLOT (sloteditKeyboardShourtCuts ()));

  editFontMapping =new Q3Action (tr ("Font Mapping..."), tr ("Font Mappin&g..."), 0, this);
  editFontMapping->setStatusTip (tr ("Customize font mappings for text with missing font"));
  editFontMapping->setWhatsThis (tr("Font Mapping...\n\nCustomize font mappings for text with missing font"));
  connect (editFontMapping, SIGNAL (activated ()), this, SLOT (sloteditFontMapping ()));

  viewToolBar =  new Q3Action (tr ("Toolbar"), tr ("Tool&bar"), 0, this, 0, true);
  viewToolBar->setStatusTip (tr ("Enables/disables the toolbar"));
  viewToolBar->setWhatsThis (tr ("Toolbar\n\nEnables/disables the toolbar"));
  connect (viewToolBar, SIGNAL (toggled (bool)), this, SLOT (slotViewToolBar (bool)));

  viewStatusBar =new Q3Action (tr ("Statusbar"), tr ("&Statusbar"), 0, this, 0, true);
  viewStatusBar->setStatusTip (tr ("Enables/disables the statusbar"));
  viewStatusBar->setWhatsThis (tr ("Statusbar\n\nEnables/disables the statusbar"));
  connect (viewStatusBar, SIGNAL (toggled (bool)), this,SLOT (slotViewStatusBar (bool)));

  viewFirst = new Q3Action (tr ("First"), tr ("&First"), QKeySequence (Qt::Key_Home),this);
  viewFirst->setStatusTip (tr ("Go to the first scene of the movie"));
  viewFirst->setWhatsThis (tr ("First\n\nGo to the first scene of the movie"));
  connect (viewFirst, SIGNAL (activated ()), this, SLOT (slotviewFirst ()));

  viewPrevious = new Q3Action (tr ("Previous"), tr ("Previous"),QKeySequence (Qt::Key_PageUp), this);
  viewPrevious->setStatusTip (tr ("Go to the previous scene of the movie"));
  viewPrevious->setWhatsThis (tr ("Previous\n\nGo to the previous scene of the movie"));
  connect (viewPrevious, SIGNAL (activated ()), this,SLOT (slotviewPrevious ()));

  viewNext = new Q3Action (tr ("Next"), tr ("&Next"), QKeySequence (Qt::Key_PageDown),this);
  viewNext->setStatusTip (tr ("Go to the next scene of the movie"));
  viewNext->setWhatsThis (tr ("Next\n\nGo to the next scene of the movie"));
  connect (viewNext, SIGNAL (activated ()), this, SLOT (slotviewNext ()));

  viewLast =new Q3Action (tr ("Last"), tr ("&Last"), QKeySequence (Qt::Key_End), this);
  viewLast->setStatusTip (tr ("Go to the last scene of the movie"));
  viewLast->setWhatsThis (tr ("Last\n\nGo to the last scene of the movie"));
  connect (viewLast, SIGNAL (activated ()), this, SLOT (slotviewLast ()));

  viewScenes = new Q3Action (tr ("Scenes"), tr ("&Scenes"), 0, this);
  viewScenes->setStatusTip (tr ("Go to a scene of the movie"));
  viewScenes->setWhatsThis (tr ("Scenes\n\nGo to a scene of the movie"));
  connect (viewScenes, SIGNAL (activated ()), this,SLOT (slotviewScenes ()));


  viewZoomIn =new Q3Action (tr ("Zoom In"), tr ("Zoom &In"),QKeySequence (Qt::CTRL + Qt::Key_Plus), this);
  viewZoomIn->setStatusTip (tr ("Show a smaller area of the drawing with more detail"));
  viewZoomIn->setWhatsThis (tr("Zoom In\n\nShow a smaller area of the drawing with more detail"));
  connect (viewZoomIn, SIGNAL (activated ()), this,SLOT (slotviewZoomIn ()));

  viewZoomOut =new Q3Action (tr ("Zoom Out"), tr ("Zoom &Out"),QKeySequence (Qt::CTRL + Qt::Key_Minus), this);
  viewZoomOut->setStatusTip (tr ("Show a larger area of the drawing with less detail"));
  viewZoomOut->setWhatsThis (tr("Zoom Out\n\nShow a larger area of the drawing with less detail"));
  connect (viewZoomOut, SIGNAL (activated ()), this,SLOT (slotviewZoomOut ()));

  viewMagnification25 = new Q3Action (tr ("25%"), tr ("&25%"), 0, this);
  viewMagnification25->setStatusTip (tr ("Zoom to 25%"));
  viewMagnification25->setWhatsThis (tr ("25%\n\nZoom to 25%"));
  connect (viewMagnification25, SIGNAL (activated ()), this,SLOT (slotviewMagnification25 ()));

  viewMagnification50 = new Q3Action (tr ("50%"), tr ("&50%"), 0, this);
  viewMagnification50->setStatusTip (tr ("Zoom to 50%"));
  viewMagnification50->setWhatsThis (tr ("50%\n\nZoom to 50%"));
  connect (viewMagnification50, SIGNAL (activated ()), this,SLOT (slotviewMagnification50 ()));

  viewMagnification100 =new Q3Action (tr ("100%"), tr ("&100%"),QKeySequence (Qt::CTRL + Qt::Key_1), this);
  viewMagnification100->setStatusTip (tr ("Zoom to 100%"));
  viewMagnification100->setWhatsThis (tr ("100%\n\nZoom to 100%"));
  connect (viewMagnification100, SIGNAL (activated ()), this,SLOT (slotviewMagnification100 ()));

  viewMagnification200 = new Q3Action (tr ("200%"), tr ("&200%"), 0, this);
  viewMagnification200->setStatusTip (tr ("Zoom to 200%"));
  viewMagnification200->setWhatsThis (tr ("200%\n\nZoom to 200%"));
  connect (viewMagnification200, SIGNAL (activated ()), this,SLOT (slotviewMagnification200 ()));

  viewMagnification400 = new Q3Action (tr ("400%"), tr ("&400%"), 0, this);
  viewMagnification400->setStatusTip (tr ("Zoom to 400%"));
  viewMagnification400->setWhatsThis (tr ("400%\n\nZoom to 400%"));
  connect (viewMagnification400, SIGNAL (activated ()), this,SLOT (slotviewMagnification400 ()));

  viewMagnification800 = new Q3Action (tr ("800%"), tr ("&800%"), 0, this);
  viewMagnification800->setStatusTip (tr ("Zoom to 800%"));
  viewMagnification800->setWhatsThis (tr ("800%\n\nZoom to 800%"));
  connect (viewMagnification800, SIGNAL (activated ()), this,SLOT (slotviewMagnification800 ()));


  viewShowFrame =new Q3Action (tr ("Show Frame"), tr ("Show &Frame"),QKeySequence (Qt::CTRL + Qt::Key_2), this);
  viewShowFrame->setStatusTip (tr ("Show the entire frame in the window"));
  viewShowFrame->setWhatsThis (tr ("Show Frame\n\nShow the entire frame in the window"));
  connect (viewShowFrame, SIGNAL (activated ()), this,SLOT (slotviewShowFrame ()));

  viewShowAll =new Q3Action (tr ("Show All"), tr ("Show &All"),QKeySequence (Qt::CTRL + Qt::Key_3), this);
  viewShowAll->setStatusTip (tr("Show the entire contents of the drawing in the window"));
  viewShowAll->setWhatsThis (tr("Show All\n\nShow the entire contents of the drawing in the window"));
  connect (viewShowAll, SIGNAL (activated ()), this,SLOT (slotviewShowAll ()));

  viewOutlines =new Q3Action (tr ("Outlines"), tr ("O&utlines"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_O),this, "Outlines", true);
  viewOutlines->setStatusTip (tr ("Show only the outines of the movie"));
  viewOutlines->setWhatsThis (tr ("Outlines\n\nShow only the outines of the movie"));
  connect (viewOutlines, SIGNAL (activated ()), this,SLOT (slotviewOutlines ()));

  viewFast =new Q3Action (tr ("Fast"), tr ("Fa&st"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_F),this, "Fast", true);
  viewFast->setStatusTip (tr ("Show the fast view of the movie"));
  viewFast->setWhatsThis (tr ("Fast\n\nShow the fast view of the movie"));
  connect (viewFast, SIGNAL (activated ()), this, SLOT (slotviewFast ()));

  viewAntialias =new Q3Action (tr ("Antialias"), tr ("A&ntialias"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_A),this, "Antialias", true);
  viewAntialias->setStatusTip (tr ("Show the edges antialiased in the movie"));
  viewAntialias->setWhatsThis (tr("Antialias\n\nShow the edges antialiased in the movie"));
  connect (viewAntialias, SIGNAL (activated ()), this,SLOT (slotviewAntialias ()));

  viewAntialiasText =new Q3Action (tr ("Antialias Text"), tr ("Antialias &Text"), QKeySequence (Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_T),this, "Antialias_text", true);
  viewAntialiasText->setStatusTip (tr ("Show the edges and text antialiased in the movie"));
  viewAntialiasText->setWhatsThis (tr("Antialias Text\n\nShow the edges and text antialiased in the movie"));
  connect (viewAntialiasText, SIGNAL (activated ()), this,SLOT (slotviewAntialiasText ()));

  viewAction = new Q3ActionGroup (this, 0);
  viewAction->insert (viewOutlines);
  viewAction->insert (viewFast);
  viewAction->insert (viewAntialias);
  viewAction->insert (viewAntialiasText);

  viewTimeline =new Q3Action (tr ("Timeline"), tr ("Time&line"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_T), this,"viewTimeline", true);
  viewTimeline->setStatusTip (tr("Show or hide the animation timeline and layers controls"));
  viewTimeline->setWhatsThis (tr("Timeline\n\nShow or hide the animation timeline and layers controls"));
  connect (viewTimeline, SIGNAL (activated ()), this,SLOT (slotviewTimeline ()));

  viewWorkArea =new Q3Action (tr ("Work Area"), tr ("&Work Area"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_W), this,"viewWorkArea", true);
  viewWorkArea->setStatusTip (tr ("Show or hide the work area that surrounds the document frame"));
  viewWorkArea->setWhatsThis (tr("Work Area\n\nShow or hide the work area that surrounds the document frame"));
  connect (viewWorkArea, SIGNAL (activated ()), this,SLOT (slotviewWorkArea ()));

  viewRulers =new Q3Action (tr ("Rulers"), tr ("&Rulers"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_R), this, "viewRulers", true);
  viewRulers->setStatusTip (tr ("Show or hide the rulers"));
  viewRulers->setWhatsThis (tr ("Rulers\n\nShow or hide the rulers"));
  connect (viewRulers, SIGNAL (activated ()), this,SLOT (slotviewRulers ()));

  viewShowGrid =new Q3Action (tr ("Show Grid"), tr ("Show Gri&d"),QKeySequence (Qt::CTRL + Qt::Key_Apostrophe), this,"viewShowGrid", true);
  viewShowGrid->setStatusTip (tr ("Show or hide the drawing grid"));
  viewShowGrid->setWhatsThis (tr ("Show Grid\n\nShow or hide the drawing grid"));
  connect (viewShowGrid, SIGNAL (activated ()), this,SLOT (slotviewShowGrid ()));

  viewSnaptoGrid =new Q3Action (tr ("Snap to Grid"), tr ("Sna&p to Grid"), QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_Apostrophe),this, "viewShowGrid", true);
  viewSnaptoGrid->setStatusTip (tr ("Show or hide the drawing grid"));
  viewSnaptoGrid->setWhatsThis (tr ("Snap to Grid\n\nShow or hide the drawing grid"));
  connect (viewSnaptoGrid, SIGNAL (activated ()), this,SLOT (slotviewSnaptoGrid ()));

  viewEditGrid =new Q3Action (tr ("Edit Grid..."), tr ("&Edit Grid..."),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_G), this);
  viewEditGrid->setStatusTip (tr ("Open the grid properties dialog"));
  viewEditGrid->setWhatsThis (tr ("Edit Grid...\n\nOpen the grid properties dialog"));
  connect (viewEditGrid, SIGNAL (activated ()), this,SLOT (slotviewEditGrid ()));

  viewShowGuides =new Q3Action (tr ("Show Guides"), tr ("Show G&uides"),QKeySequence (Qt::CTRL + Qt::Key_Semicolon), this);
  viewShowGuides->setStatusTip (tr ("Show or hide the guides"));
  viewShowGuides->setWhatsThis (tr ("Show Guides\n\nShow or hide the guides"));
  connect (viewShowGuides, SIGNAL (activated ()), this, SLOT (slotviewShowGuides ()));

  viewLockGuides =new Q3Action (tr ("Lock Guides"), tr ("Loc&k Guides"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_Semicolon), this);
  viewLockGuides->setStatusTip (tr ("Lock or unlock the guides"));
  viewLockGuides->setWhatsThis (tr ("Lock Guides\n\nLock or unlock the guides"));
  connect (viewLockGuides, SIGNAL (activated ()), this,SLOT (slotviewLockGuides ()));

  viewSnaptoGuides =new Q3Action (tr ("Snap to Guides"), tr ("Snap to Gu&ides"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_Semicolon),this);
  viewSnaptoGuides->setStatusTip (tr ("Turn Snap to Guides on or off"));
  viewSnaptoGuides->setWhatsThis (tr ("Snap to Guides\n\nTurn Snap to Guides on or off"));
  connect (viewSnaptoGuides, SIGNAL (activated ()), this,SLOT (slotviewSnaptoGuides ()));

  viewEditGuides =new Q3Action (tr ("Edit Guides..."), tr ("Edit Guides..."),QKeySequence (Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_G),this);
  viewEditGuides->setStatusTip (tr ("Turn Snap to Guides on or off"));
  viewEditGuides->setWhatsThis (tr ("Edit Guides...\n\nTurn Snap to Guides on or off"));
  connect (viewEditGuides, SIGNAL (activated ()), this,SLOT (slotviewEditGuides ()));

  viewSnaptoPixels =new Q3Action (tr ("Snap to Pixels"), tr ("Snap to Pixels"), 0, this);
  viewSnaptoPixels->setStatusTip (tr ("Turn Snap to Pixels on or off"));
  viewSnaptoPixels->setWhatsThis (tr ("Snap to Pixels\n\nTurn Snap to Pixels on or off"));
  connect (viewSnaptoPixels, SIGNAL (activated ()), this,SLOT (slotviewSnaptoPixels ()));

  viewSnaptoObjects =new Q3Action (tr ("Snap to Objects"), tr ("Snap to O&bjects"), 0, this);
  viewSnaptoObjects->setStatusTip (tr("Turn snap to objects and automatic connection of lines on or off\nSnap to Objects"));
  viewSnaptoObjects->setWhatsThis (tr("Snap to Objects\n\nTurn snap to objects and automatic connection of lines on or off\nSnap to Objects"));
  connect (viewSnaptoObjects, SIGNAL (activated ()), this, SLOT (slotviewSnaptoObjects ()));

  viewShowShapeHints =new Q3Action (tr ("Show Shape Hints"), tr ("Show Sh&ape Hints"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_H), this);
  viewShowShapeHints->setStatusTip (tr ("Show or hide the tweening shape hints"));
  viewShowShapeHints->setWhatsThis (tr("Show Shape Hints\n\nShow or hide the tweening shape hints"));
  connect (viewShowShapeHints, SIGNAL (activated ()), this,SLOT (slotviewShowShapeHints ()));

  viewHideEdges =new Q3Action (tr ("Hide Edges"), tr ("&Hide Edges"),QKeySequence (Qt::CTRL + Qt::Key_H), this);
  viewHideEdges->setStatusTip (tr("When turned on  suppresses hilighting of selected items"));
  viewHideEdges->setWhatsThis (tr("Hide Edges\n\nWhen turned on  suppresses hilighting of selected items"));
  connect (viewHideEdges, SIGNAL (activated ()), this,SLOT (slotviewHideEdges ()));

  viewHidePanels =new Q3Action (tr ("Hide Panels"), tr ("Hide &Panels"), 0, this);
  viewHidePanels->setStatusTip (tr ("Hide or show all panels and tools"));
  viewHidePanels->setWhatsThis (tr ("Hide Panels\n\nHide or show all panels and tools"));
  connect (viewHidePanels, SIGNAL (activated ()), this,SLOT (slotviewHidePanels ()));

  insertConverttoSymbol =new Q3Action (tr ("Convert to Symbol..."), tr ("&Convert to Symbol..."),QKeySequence (Qt::Key_F8), this);
  insertConverttoSymbol->setStatusTip (tr("Create a new symbol from the selection that can be used in multiple places"));
  insertConverttoSymbol->setWhatsThis (tr("Convert to Symbol...\n\nCreate a new symbol from the selection that can be used in multiple places"));
  connect (insertConverttoSymbol, SIGNAL (activated ()), this,SLOT (slotinsertConverttoSymbol ()));

  insertNewSymbol =new Q3Action (tr ("New Symbol..."), tr ("&New Symbol..."),QKeySequence (Qt::CTRL + Qt::Key_F8), this);
  insertNewSymbol->setStatusTip (tr("Create a new symbol that can be used in multiple places"));
  insertNewSymbol->setWhatsThis (tr("New Symbol...\n\nCreate a new symbol that can be used in multiple places"));
  connect (insertNewSymbol, SIGNAL (activated ()), this,SLOT (slotinsertNewSymbol ()));

  insertLayer = new Q3Action (tr ("Layer"), tr ("&Layer"), 0, this);
  insertLayer->setStatusTip (tr ("Insert a new layer in the timeline"));
  insertLayer->setWhatsThis (tr ("Layer\n\nInsert a new layer in the timeline"));
  connect (insertLayer, SIGNAL (activated ()), this,SLOT (slotinsertLayer ()));

  insertLayerFolder =new Q3Action (tr ("Layer Folder"), tr ("Layer F&older"), 0, this);
  insertLayerFolder->setStatusTip (tr ("Insert a new layer folder in the timeline"));
  insertLayerFolder->setWhatsThis (tr("Layer Folder\n\nInsert a new layer folder in the timeline"));
  connect (insertLayerFolder,SIGNAL (activated ()),this,SLOT(slotinsertLayerFolder ()));
  insertMotionGuide =new Q3Action (tr ("Motion Guide"), tr ("&Motion Guide"), 0, this);
  insertMotionGuide->setStatusTip (tr ("Add a motion guide for the current layer"));
  insertMotionGuide->setWhatsThis (tr("Motion Guide\n\nAdd a motion guide for the current layer"));
  connect (insertMotionGuide, SIGNAL (activated ()), this,SLOT (slotinsertMotionGuide ()));

  insertFrame =new Q3Action (tr ("Frame"), tr ("&Frame"), QKeySequence (Qt::Key_F5),this);
  insertFrame->setStatusTip (tr ("Insert frames in the selected layers"));
  insertFrame->setWhatsThis (tr ("Frame\n\nInsert frames in the selected layers"));
  connect (insertFrame, SIGNAL (activated ()), this,SLOT (slotinsertFrame ()));

  insertRemoveFrames =new Q3Action (tr ("Remove Frames"), tr ("R&emove Frames"),QKeySequence (Qt::SHIFT + Qt::Key_F5), this);
  insertRemoveFrames->setStatusTip (tr ("Delete the selected frames"));
  insertRemoveFrames->setWhatsThis (tr ("Remove Frames\n\nDelete the selected frames"));
  connect (insertRemoveFrames, SIGNAL (activated ()), this,SLOT (slotinsertRemoveFrames ()));

  insertKeyframe =new Q3Action (tr ("Keyframe"), tr ("&Keyframe"), QKeySequence (Qt::Key_F6),this);
  insertKeyframe->setStatusTip (tr("Make keyframes with the same contents as the selected frames"));
  insertKeyframe->setWhatsThis (tr("Keyframe\n\nMake keyframes with the same contents as the selected frames"));
  connect (insertKeyframe, SIGNAL (activated ()), this,SLOT (slotinsertKeyframe ()));

  insertBlankKeyframe =new Q3Action (tr ("Blank Keyframe"), tr ("&Blank Keyframe"),QKeySequence (Qt::Key_F7), this);
  insertBlankKeyframe->setStatusTip (tr ("Create blank keyframes at the selected frames"));
  insertBlankKeyframe->setWhatsThis (tr("Blank Keyframe\n\nCreate blank keyframes at the selected frames"));
  connect (insertBlankKeyframe, SIGNAL (activated ()), this,SLOT (slotinsertBlankKeyframe ()));

  insertClearKeyframe =new Q3Action (tr ("Clear Keyframe"), tr ("Cle&ar Keyframe"),QKeySequence (Qt::SHIFT + Qt::Key_F6), this);
  insertClearKeyframe->setStatusTip (tr ("Delete the selected keyframes"));
  insertClearKeyframe->setWhatsThis (tr ("Clear Keyframe\n\nDelete the selected keyframes"));
  connect (insertClearKeyframe, SIGNAL (activated ()), this,SLOT (slotinsertClearKeyframe ()));

  insertCreateMotionTween =new Q3Action (tr ("Create Motion Tween"), tr ("Create Motion &Tween"), 0,this);
  insertCreateMotionTween->setStatusTip (tr ("Set the selected frames to motion tweening"));
  insertCreateMotionTween->setWhatsThis (tr("Create Motion Tween\n\nSet the selected frames to motion tweening"));
  connect (insertCreateMotionTween, SIGNAL (activated ()), this,SLOT (slotinsertCreateMotionTween ()));

  insertScene = new Q3Action (tr ("Scene"), tr ("&Scene"), 0, this);
  insertScene->setStatusTip (tr ("Add a new scene after the current scene"));
  insertScene->setWhatsThis (tr ("Scene\n\nAdd a new scene after the current scene"));
  connect (insertScene, SIGNAL (activated ()), this,SLOT (slotinsertScene ()));

  insertRemoveScene =new Q3Action (tr ("Remove Scene"), tr ("&Remove Scene"), 0, this);
  insertRemoveScene->setStatusTip (tr ("Delete the current scene"));
  insertRemoveScene->setWhatsThis (tr ("Remove Scene\n\nDelete the current scene"));
  connect (insertRemoveScene, SIGNAL (activated ()), this,SLOT (slotinsertRemoveScene ()));

  modifyLayer = new Q3Action (tr ("&Layer..."), tr ("&Layer..."), 0, this);
  modifyLayer->setStatusTip (tr ("Edit the properties of the current layer"));
  modifyLayer->setWhatsThis (tr("&Layer...\n\nEdit the properties of the current layer"));
  connect (modifyLayer, SIGNAL (activated ()), this,SLOT (slotmodifyLayer ()));

  modifyScene = new Q3Action (tr ("&Scene..."), tr ("&Scene..."), 0, this);
  modifyScene->setStatusTip (tr("Show or change a list of the scenes in the current movie"));
  modifyScene->setWhatsThis (tr("&Scene...\n\nShow or change a list of the scenes in the current movie"));
  connect (modifyScene, SIGNAL (activated ()), this,SLOT (slotmodifyScene ()));

  modifyDocument =new Q3Action (tr ("&Document..."), tr ("&Document..."),QKeySequence (Qt::CTRL + Qt::Key_M), this);
  modifyDocument->setStatusTip (tr("Change the size and other attributes of the document"));
  modifyDocument->setWhatsThis (tr("&Document...\n\nChange the size and other attributes of the document"));
  connect (modifyDocument, SIGNAL (activated ()), this,SLOT (slotmodifyDocument ()));

  modifySmooth = new Q3Action (tr ("&Smooth"), tr ("&Smooth"), 0, this);
  modifySmooth->setStatusTip (tr ("Smooth the selected lines\nSmooth"));
  modifySmooth->setWhatsThis (tr ("&Smooth\n\nSmooth the selected lines\nSmooth"));
  connect (modifySmooth, SIGNAL (activated ()), this,SLOT (slotmodifySmooth ()));

  modifyStraighten =new Q3Action (tr ("S&traighten"), tr ("S&traighten"), 0, this);
  modifyStraighten->setStatusTip (tr ("Straighten the selected lines\nStraighten"));
  modifyStraighten->setWhatsThis (tr("S&traighten\n\nStraighten the selected lines\nStraighten"));
  connect (modifyStraighten, SIGNAL (activated ()), this,SLOT (slotmodifyStraighten ()));

  modifyOptimize = new Q3Action (tr ("&Optimize..."), tr ("&Optimize..."),QKeySequence (Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_C), this);
  modifyOptimize->setStatusTip (tr("Smooth the selected curves so that they use less resources"));
  modifyOptimize-> setWhatsThis (tr("&Optimize...\n\nSmooth the selected curves so that they use less resources"));
  connect (modifyOptimize, SIGNAL (activated ()), this,SLOT (slotmodifyOptimize ()));

  modifyConvertLinestoFills =new Q3Action (tr ("&Convert Lines to Fills"), tr ("&Convert Lines to Fills"), 0, this);
  modifyConvertLinestoFills->setStatusTip (tr ("Convert lines to filled areas"));
  modifyConvertLinestoFills->setWhatsThis (tr("&Convert Lines to Fills\n\nConvert lines to filled areas"));
  connect (modifyConvertLinestoFills, SIGNAL (activated ()), this,SLOT (slotmodifyConvertLinestoFills ()));

  modifyExpandFill =new Q3Action (tr ("&Expand Fill..."), tr ("&Expand Fill..."), 0, this);
  modifyExpandFill->setStatusTip (tr ("Expand or inset the edges of the selected shapes"));
  modifyExpandFill->setWhatsThis (tr("&Expand Fill...\n\nExpand or inset the edges of the selected shapes"));
  connect (modifyExpandFill, SIGNAL (activated ()), this,SLOT (slotmodifyExpandFill ()));

  modifySoftenFillEdges =new Q3Action (tr ("So&ften Fill Edges..."), tr ("So&ften Fill Edges..."), 0, this);
  modifySoftenFillEdges->setStatusTip (tr("Blend the edges of the selected shapes to transparent"));
  modifySoftenFillEdges->setWhatsThis (tr("So&ften Fill Edges...\n\nBlend the edges of the selected shapes to transparent"));
  connect (modifySoftenFillEdges, SIGNAL (activated ()), this,SLOT (slotmodifySoftenFillEdges ()));

  modifyAddShapeHint =new Q3Action (tr ("&Add Shape Hint"), tr ("&Add Shape Hint"), QKeySequence (Qt::CTRL + Qt::Key_H), this);
  modifyAddShapeHint->setStatusTip (tr ("Add a tweening shape hint"));
  modifyAddShapeHint->setWhatsThis (tr ("&Add Shape Hint\n\nAdd a tweening shape hint"));
  connect (modifyAddShapeHint, SIGNAL (activated ()), this, SLOT (slotmodifyAddShapeHint ()));

  modifyRemoveAllHints =new Q3Action (tr ("Re&move All Hints"), tr ("Re&move All Hints"), 0, this);
  modifyRemoveAllHints->setStatusTip (tr ("Remove all the tweening shape hints"));
  modifyRemoveAllHints->setWhatsThis (tr("Re&move All Hints\n\nRemove all the tweening shape hints"));
  connect (modifyRemoveAllHints, SIGNAL (activated ()), this,SLOT (slotmodifyRemoveAllHints ()));

  modifySwapSymbol = new Q3Action (tr ("Swap Symbol..."), tr ("Swap Symbol..."), 0, this);
  modifySwapSymbol->setStatusTip (tr ("Replaces an instance with another symbol"));
  modifySwapSymbol->setWhatsThis (tr("Swap Symbol...\n\nReplaces an instance with another symbol"));
  connect (modifySwapSymbol, SIGNAL (activated ()), this,SLOT (slotmodifySwapSymbol ()));

  modifyDuplicateSymbol =new Q3Action (tr ("Duplicate Symbol..."), tr ("Duplicate Symbol..."), 0, this);
  modifyDuplicateSymbol->setStatusTip (tr ("Replaces an instance with a copy of the selected symbol"));
  modifyDuplicateSymbol->setWhatsThis (tr("Duplicate Symbol...\n\nReplaces an instance with a copy of the selected symbol"));
  connect (modifyDuplicateSymbol, SIGNAL (activated ()), this,SLOT (slotmodifyDuplicateSymbol ()));

  modifySwapBitmap =new Q3Action (tr ("Swap Bitmap..."), tr ("Swap Bitmap..."), 0, this);
  modifySwapBitmap->setStatusTip (tr ("Replaces an instance with another bitmap symbol"));
  modifySwapBitmap->setWhatsThis (tr("Swap Bitmap...\n\nReplaces an instance with another bitmap symbol"));
  connect (modifySwapBitmap, SIGNAL (activated ()), this,SLOT (slotmodifySwapBitmap ()));

  modifyTraceBitmap = new Q3Action (tr ("Trace &Bitmap..."), tr ("Trace &Bitmap..."), 0, this);
  modifyTraceBitmap->setStatusTip (tr ("Convert a bitmap object to curves"));
  modifyTraceBitmap->setWhatsThis (tr("Trace &Bitmap...\n\nConvert a bitmap object to curves"));
  connect (modifyTraceBitmap, SIGNAL (activated ()), this,SLOT (slotmodifyTraceBitmap ()));

  modifyFreeTransform =new Q3Action (tr ("&Free Transform"), tr ("&Free Transform"), 0, this);
  modifyFreeTransform->setStatusTip (tr("Show handles to rotate  slant  or skew the selection\nFree Transform"));
  modifyFreeTransform->setWhatsThis (tr("&Free Transform\n\nShow handles to rotate  slant  or skew the selection\nFree Transform"));
  connect (modifyFreeTransform, SIGNAL (activated ()), this,SLOT (slotmodifyFreeTransform ()));

  modifyDistort = new Q3Action (tr ("&Distort"), tr ("&Distort"), 0, this);
  modifyDistort->setStatusTip (tr ("Show handles to distort the selection\nDistort"));
  modifyDistort->setWhatsThis (tr("&Distort\n\nShow handles to distort the selection\nDistort"));
  connect (modifyDistort, SIGNAL (activated ()), this,SLOT (slotmodifyDistort ()));

  modifyEnvelope =new Q3Action (tr ("&Envelope"), tr ("&Envelope"), 0, this);
  modifyEnvelope->setStatusTip (tr ("Show handles to envelope the selection\nEnvelope"));
  modifyEnvelope->setWhatsThis (tr("&Envelope\n\nShow handles to envelope the selection\nEnvelope"));
  connect (modifyEnvelope, SIGNAL (activated ()), this, SLOT (slotmodifyEnvelope ()));

  modifyScale = new Q3Action (tr ("&Scale"), tr ("&Scale"), 0, this);
  modifyScale->setStatusTip (tr("Show handles to enlarge or shrink the selection\nScale"));
  modifyScale->setWhatsThis (tr("&Scale\n\nShow handles to enlarge or shrink the selection\nScale"));
  connect (modifyScale, SIGNAL (activated ()), this,SLOT (slotmodifyScale ()));

  modifyRotateandSkew =new Q3Action (tr ("&Rotate and Skew"), tr ("&Rotate and Skew"), 0, this);
  modifyRotateandSkew->setStatusTip (tr ("Show handles to rotate or slant the selection\nRotate and Skew"));
  modifyRotateandSkew->setWhatsThis (tr ("&Rotate and Skew\n\nShow handles to rotate or slant the selection\nRotate and Skew"));
  connect (modifyRotateandSkew, SIGNAL (activated ()), this,SLOT (slotmodifyRotateandSkew ()));

  modifyScaleandRotate =new Q3Action (tr ("S&cale and Rotate..."), tr ("S&cale and Rotate..."), QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_S), this);
  modifyScaleandRotate->setStatusTip (tr("Scale and/or rotate the selection using numeric values"));
  modifyScaleandRotate->setWhatsThis (tr("S&cale and Rotate...\n\nScale and/or rotate the selection using numeric values"));
  connect (modifyScaleandRotate, SIGNAL (activated ()), this,SLOT (slotmodifyScaleandRotate ()));

  modifyRotate90CW =new Q3Action (tr ("Rotate 9&0 CW"), tr ("Rotate 9&0 CW"), 0, this);
  modifyRotate90CW->setStatusTip (tr ("Rotate the selection 90 degrees to the right"));
  modifyRotate90CW->setWhatsThis (tr("Rotate 9&0 CW\n\nRotate the selection 90 degrees to the right"));
  connect (modifyRotate90CW, SIGNAL (activated ()), this,SLOT (slotmodifyRotate90CW ()));

  modifyRotate90CCW =new Q3Action (tr ("Rotate &90 CCW"), tr ("Rotate &90 CCW"), 0, this);
  modifyRotate90CCW->setStatusTip (tr ("Rotate the selection 90 degrees to the left"));
  modifyRotate90CCW->setWhatsThis (tr("Rotate &90 CCW\n\nRotate the selection 90 degrees to the left"));
  connect (modifyRotate90CCW, SIGNAL (activated ()), this,SLOT (slotmodifyRotate90CCW ()));

  modifyFlipVertical =new Q3Action (tr ("Flip &Vertical"), tr ("Flip &Vertical"), 0, this);
  modifyFlipVertical->setStatusTip (tr ("Flip the selection so it appears upside-down"));
  modifyFlipVertical->setWhatsThis (tr("Flip &Vertical\n\nFlip the selection so it appears upside-down"));
  connect (modifyFlipVertical, SIGNAL (activated ()), this,SLOT (slotmodifyFlipVertical ()));

  modifyFlipHorizontal =new Q3Action (tr ("Flip &Horizontal"), tr ("Flip &Horizontal"), 0, this);
  modifyFlipHorizontal->setStatusTip (tr("Flip the selection so that the left and right sides are reversed"));
  modifyFlipHorizontal->setWhatsThis (tr("Flip &Horizontal\n\nFlip the selection so that the left and right sides are reversed"));
  connect (modifyFlipHorizontal, SIGNAL (activated ()), this,SLOT (slotmodifyFlipHorizontal ()));


  modifyRemoveTransform =new Q3Action (tr ("Remove Trans&form"), tr ("Remove Trans&form"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_Z), this);
  modifyRemoveTransform->setStatusTip (tr("Remove any rotation or scaling from the selected objects"));
  modifyRemoveTransform->setWhatsThis (tr("Remove Trans&form\n\nRemove any rotation or scaling from the selected objects"));
  connect (modifyRemoveTransform, SIGNAL (activated ()), this,SLOT (slotmodifyRemoveTransform ()));

  modifyBringtoFront =new Q3Action (tr ("Bring to &Front"), tr ("Bring to &Front"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_Up), this);
  modifyBringtoFront->setStatusTip (tr("Move the selected objects in to the front of their layer"));
  modifyBringtoFront->setWhatsThis (tr("Bring to &Front\n\nMove the selected objects in to the front of their layer"));
  connect (modifyBringtoFront, SIGNAL (activated ()), this,SLOT (slotmodifyBringtoFront ()));

  modifyBringForward =new Q3Action (tr ("B&ring Forward"), tr ("B&ring Forward"), 0, this);
  modifyBringForward->setStatusTip (tr("Move the selected objects ahead of any overlaping objects"));
  modifyBringForward->setWhatsThis (tr("B&ring Forward\n\nMove the selected objects ahead of any overlaping objects"));
  connect (modifyBringForward, SIGNAL (activated ()), this,SLOT (slotmodifyBringForward ()));

  modifySendBackward =new Q3Action (tr ("S&end Backward"), tr ("S&end Backward"), 0, this);
  modifySendBackward->setStatusTip (tr("Move the selected objects behind any overlaping objects"));
  modifySendBackward->setWhatsThis (tr("S&end Backward\n\nMove the selected objects behind any overlaping objects"));
  connect (modifySendBackward, SIGNAL (activated ()), this,SLOT (slotmodifySendBackward ()));


  modifySendtoBack =new Q3Action (tr ("Send to &Back"), tr ("Send to &Back"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_Down), this);
  modifySendtoBack->setStatusTip (tr("Move the selected objects to the back of their layer"));
  modifySendtoBack->setWhatsThis (tr ("Send to &Back\n\nMove the selected objects to the back of their layer"));
  connect (modifySendtoBack, SIGNAL (activated ()), this,SLOT (slotmodifySendtoBack ()));

  modifyLock =new Q3Action (tr ("&Lock"), tr ("&Lock"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_L), this);
  modifyLock->setStatusTip (tr("Lock the selected objects so that they cannot be accidentally modified"));
  modifyLock->setWhatsThis (tr("&Lock\n\nLock the selected objects so that they cannot be accidentally modified"));
  connect (modifyLock, SIGNAL (activated ()), this,SLOT (slotmodifyLock ()));

  modifyUnlockAll =new Q3Action (tr ("&Unlock All"), tr ("&Unlock All"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::SHIFT + Qt::Key_L),this);
  modifyUnlockAll->setStatusTip (tr ("Unlock all of the locked objects in the drawing"));
  modifyUnlockAll->setWhatsThis (tr("&Unlock All\n\nUnlock all of the locked objects in the drawing"));
  connect (modifyUnlockAll, SIGNAL (activated ()), this,SLOT (slotmodifyUnlockAll ()));

  modifyReverse = new Q3Action (tr ("&Reverse"), tr ("&Reverse"), 0, this);
  modifyReverse->setStatusTip (tr("Reverse selected frames so the animation plays backwards"));
  modifyReverse->setWhatsThis (tr("&Reverse\n\nReverse selected frames so the animation plays backwards"));
  connect (modifyReverse, SIGNAL (activated ()), this,SLOT (slotmodifyReverse ()));

  modifySynchronizeSymbols =new Q3Action (tr ("&Synchronize Symbols"), tr ("&Synchronize Symbols"), 0,this);
  modifySynchronizeSymbols->setStatusTip (tr("Adjust the symbol first frames to loop continuously across keyframes"));
  modifySynchronizeSymbols->setWhatsThis (tr("&Synchronize Symbols\n\nAdjust the symbol first frames to loop continuously across keyframes"));
  connect (modifySynchronizeSymbols, SIGNAL (activated ()), this,SLOT (slotmodifySynchronizeSymbols ()));

  modifyConverttoKeyframes =new Q3Action (tr ("Convert to &Keyframes"), tr ("Convert to &Keyframes"),0, this);
  modifyConverttoKeyframes->setStatusTip (tr ("Convert the selected frames to keyframes"));
  modifyConverttoKeyframes->setWhatsThis (tr("Convert to &Keyframes\n\nConvert the selected frames to keyframes"));
  connect (modifyConverttoKeyframes, SIGNAL (activated ()), this,SLOT (slotmodifyConverttoKeyframes ()));

  modifyConverttoBlankKeyframes =new Q3Action (tr ("Convert to &Blank Keyframes"),tr ("Convert to &Blank Keyframes"), 0, this);
  modifyConverttoBlankKeyframes->setStatusTip (tr ("Convert selected frames to blank keyframes"));
  modifyConverttoBlankKeyframes->setWhatsThis (tr("Convert to &Blank Keyframes\n\nConvert selected frames to blank keyframes"));
  connect (modifyConverttoBlankKeyframes, SIGNAL (activated ()), this,SLOT (slotmodifyConverttoBlankKeyframes ()));

  modifyGroup =new Q3Action (tr ("&Group"), tr ("&Group"), QKeySequence (Qt::CTRL + Qt::Key_G), this);
  modifyGroup->setStatusTip (tr ("Create a new group object"));
  modifyGroup->setWhatsThis (tr ("&Group\n\nCreate a new group object"));
  connect (modifyGroup, SIGNAL (activated ()), this,SLOT (slotmodifyGroup ()));

  modifyUngroup =new Q3Action (tr ("&Ungroup"), tr ("&Ungroup"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_G), this);
  modifyUngroup->setStatusTip (tr ("Ungroup the selected group objects"));
  modifyUngroup->setWhatsThis (tr ("&Ungroup\n\nUngroup the selected group objects"));
  connect (modifyUngroup, SIGNAL (activated ()), this,SLOT (slotmodifyUngroup ()));

  modifyBreakApart =new Q3Action (tr ("Brea&k Apart"), tr ("Brea&k Apart"),QKeySequence (Qt::CTRL + Qt::Key_B), this);
  modifyBreakApart->setStatusTip(tr("Break apart the selected objects into their component pieces"));
  modifyBreakApart->setWhatsThis(tr("Brea&k Apart\n\nBreak apart the selected objects into their component pieces"));
  connect (modifyBreakApart, SIGNAL (activated ()), this,SLOT (slotmodifyBreakApart ()));

  modifyDistributetoLayers =new Q3Action (tr ("Distribute to Layers"), tr ("Distribute to Layers"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_D), this);
  modifyDistributetoLayers->setStatusTip (tr ("Move the selected objects onto their own layers"));
  modifyDistributetoLayers->setWhatsThis (tr("Distribute to Layers\n\nMove the selected objects onto their own layers"));
  connect (modifyDistributetoLayers, SIGNAL (activated ()), this,SLOT (slotmodifyDistributetoLayers ()));

  textFontFace =new Q3Action (tr ("Font Face"), tr ("Font Face"), 0, this);
  textFontFace->setStatusTip (tr ("Select the Font to be used"));
  textFontFace->setWhatsThis (tr ("Font Face\n\nSelect the Font to be used"));
  connect (textFontFace, SIGNAL (activated ()), this,SLOT (slottextFontFace ()));

  text8 = new Q3Action (tr ("&8"), tr ("&8"), 0, this);
  text8->setStatusTip (tr ("Changes text to 8 point font size"));
  text8->setWhatsThis (tr ("&8\n\nChanges text to 8 point font size"));
  connect (text8, SIGNAL (activated ()), this, SLOT (slottext8 ()));

  text9 = new Q3Action (tr ("&9"), tr ("&9"), 0, this);
  text9->setStatusTip (tr ("Changes text to 9 point font size"));
  text9->setWhatsThis (tr ("&9\n\nChanges text to 9 point font size"));
  connect (text9, SIGNAL (activated ()), this, SLOT (slottext9 ()));

  text10 = new Q3Action (tr ("1&0"), tr ("1&0"), 0, this);
  text10->setStatusTip (tr ("Changes text to 10 point font size"));
  text10->setWhatsThis (tr ("1&0\n\nChanges text to 10 point font size"));
  connect (text10, SIGNAL (activated ()), this, SLOT (slottext10 ()));

  text11 = new Q3Action (tr ("1&1"), tr ("1&1"), 0, this);
  text11->setStatusTip (tr ("Changes text to 11 point font size"));
  text11->setWhatsThis (tr ("1&1\n\nChanges text to 11 point font size"));
  connect (text11, SIGNAL (activated ()), this, SLOT (slottext11 ()));

  text12 = new Q3Action (tr ("1&2"), tr ("1&2"), 0, this);
  text12->setStatusTip (tr ("Changes text to 12 point font size"));
  text12->setWhatsThis (tr ("1&2\n\nChanges text to 12 point font size"));
  connect (text12, SIGNAL (activated ()), this, SLOT (slottext12 ()));

  text14 = new Q3Action (tr ("1&4"), tr ("1&4"), 0, this);
  text14->setStatusTip (tr ("Changes text to 14 point font size"));
  text14->setWhatsThis (tr ("1&4\n\nChanges text to 14 point font size"));
  connect (text14, SIGNAL (activated ()), this, SLOT (slottext14 ()));

  text18 = new Q3Action (tr ("1&8"), tr ("1&8"), 0, this);
  text18->setStatusTip (tr ("Changes text to 18 point font size"));
  text18->setWhatsThis (tr ("1&8\n\nChanges text to 18 point font size"));
  connect (text18, SIGNAL (activated ()), this, SLOT (slottext18 ()));

  text24 = new Q3Action (tr ("2&4"), tr ("2&4"), 0, this);
  text24->setStatusTip (tr ("Changes text to 24 point font size"));
  text24->setWhatsThis (tr ("2&4\n\nChanges text to 24 point font size"));
  connect (text24, SIGNAL (activated ()), this, SLOT (slottext24 ()));

  text36 = new Q3Action (tr ("&36"), tr ("&36"), 0, this);
  text36->setStatusTip (tr ("Changes text to 36 point font size"));
  text36->setWhatsThis (tr ("&36\n\nChanges text to 36 point font size"));
  connect (text36, SIGNAL (activated ()), this, SLOT (slottext36 ()));

  text48 = new Q3Action (tr ("&48"), tr ("&48"), 0, this);
  text48->setStatusTip (tr ("Changes text to 48 point font size"));
  text48->setWhatsThis (tr ("&48\n\nChanges text to 48 point font size"));
  connect (text48, SIGNAL (activated ()), this, SLOT (slottext48 ()));

  text72 = new Q3Action (tr ("&72"), tr ("&72"), 0, this);
  text72->setStatusTip (tr ("Changes text to 72 point font size"));
  text72->setWhatsThis (tr ("&72\n\nChanges text to 72 point font size"));
  connect (text72, SIGNAL (activated ()), this, SLOT (slottext72 ()));

  text96 = new Q3Action (tr ("&96"), tr ("&96"), 0, this);
  text96->setStatusTip (tr ("Changes text to 96 point font size"));
  text96->setWhatsThis (tr ("&96\n\nChanges text to 96 point font size"));
  connect (text96, SIGNAL (activated ()), this, SLOT (slottext96 ()));

  text120 = new Q3Action (tr ("&120"), tr ("&120"), 0, this);
  text120->setStatusTip (tr ("Changes text to 120 point font size"));
  text120->setWhatsThis (tr ("&120\n\nChanges text to 120 point font size"));
  connect (text120, SIGNAL (activated ()), this, SLOT (slottext120 ()));

  textPlain =new Q3Action (tr ("&Plain"), tr ("&Plain"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_P), this);
  textPlain->setStatusTip (tr ("Make text plain"));
  textPlain->setWhatsThis (tr ("&Plain\n\nMake text plain"));
  connect (textPlain, SIGNAL (activated ()), this, SLOT (slottextPlain ()));

  textBold =new Q3Action (tr ("&Bold"), tr ("&Bold"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_B), this);
  textBold->setStatusTip (tr ("Make text bold"));
  textBold->setWhatsThis (tr ("&Bold\n\nMake text bold"));
  connect (textBold, SIGNAL (activated ()), this, SLOT (slottextBold ()));

  textItalic = new Q3Action (tr ("&Italic"), tr ("&Italic"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_I), this);
  textItalic->setStatusTip (tr ("Make text italic"));
  textItalic->setWhatsThis (tr ("&Italic\n\nMake text italic"));
  connect (textItalic, SIGNAL (activated ()), this,SLOT (slottextItalic ()));

  textSubscript =new Q3Action (tr ("&Subscript"), tr ("&Subscript"), 0, this);
  textSubscript->setStatusTip (tr ("Make text subscript"));
  textSubscript->setWhatsThis (tr ("&Subscript\n\nMake text subscript"));
  connect (textSubscript, SIGNAL (activated ()), this,SLOT (slottextSubscript ()));

  textSuperscript =new Q3Action (tr ("S&uperscript"), tr ("S&uperscript"), 0, this);
  textSuperscript->setStatusTip (tr ("Make text superscript"));
  textSuperscript->setWhatsThis (tr ("S&uperscript\n\nMake text superscript"));
  connect (textSuperscript, SIGNAL (activated ()), this,SLOT (slottextSuperscript ()));

  textAlignLeft =new Q3Action (tr ("Align &Left"), tr ("Align &Left"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_L), this);
  textAlignLeft->setStatusTip (tr ("Make text flush left"));
  textAlignLeft->setWhatsThis (tr ("Align &Left\n\nMake text flush left"));
  connect (textAlignLeft, SIGNAL (activated ()), this,SLOT (slottextAlignLeft ()));

  textAlignCenter =new Q3Action (tr ("Align &Center"), tr ("Align &Center"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_C), this);
  textAlignCenter->setStatusTip (tr ("Make text aligned center"));
  textAlignCenter->setWhatsThis (tr ("Align &Center\n\nMake text aligned center"));
  connect (textAlignCenter, SIGNAL (activated ()), this,SLOT (slottextAlignCenter ()));

  textAlignRight = new Q3Action (tr ("Align &Right"), tr ("Align &Right"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_R), this);
  textAlignRight->setStatusTip (tr ("Make text flush right"));
  textAlignRight->setWhatsThis (tr ("Align &Right\n\nMake text flush right"));
  connect (textAlignRight, SIGNAL (activated ()), this,SLOT (slottextAlignRight ()));

  textJustify = new Q3Action (tr ("&Justify"), tr ("&Justify"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_J), this);
  textJustify->setStatusTip (tr ("Make text align flush with left and right edges"));
  textJustify->setWhatsThis (tr("&Justify\n\nMake text align flush with left and right edges"));
  connect (textJustify, SIGNAL (activated ()), this,SLOT (slottextJustify ()));

  textIncrease =new Q3Action (tr ("&Increase"), tr ("&Increase"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_Right), this);
  textIncrease->setStatusTip (tr ("Increase the space between letters"));
  textIncrease->setWhatsThis (tr ("&Increase\n\nIncrease the space between letters"));
  connect (textIncrease, SIGNAL (activated ()), this,SLOT (slottextIncrease ()));

  textDecrease =new Q3Action (tr ("&Decrease"), tr ("&Decrease"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_Left), this);
  textDecrease->setStatusTip (tr ("Reduce the space between letters"));
  textDecrease->setWhatsThis (tr ("&Decrease\n\nReduce the space between letters"));
  connect (textDecrease, SIGNAL (activated ()), this,SLOT (slottextDecrease ()));

  textReset =new Q3Action (tr ("&Reset"), tr ("&Reset"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_Up), this);
  textReset->setStatusTip (tr ("Reset the space between letters to the default"));
  textReset->setWhatsThis (tr("&Reset\n\nReset the space between letters to the default"));
  connect (textReset, SIGNAL (activated ()), this, SLOT (slottextReset ()));

  textScrollable =new Q3Action (tr ("Scrollable"), tr ("Scrollable"), 0, this);
  textScrollable->setStatusTip (tr ("Toggle Text Field Scrollable Mode"));
  textScrollable->setWhatsThis (tr ("Scrollable\n\nToggle Text Field Scrollable Mode"));
  connect (textScrollable, SIGNAL (activated ()), this,SLOT (slottextScrollable ()));

  controlPlay =new Q3Action (tr ("&Play"), tr ("&Play"), QKeySequence (Qt::Key_Return),this);
  controlPlay->setStatusTip (tr ("Start playing (or stop) the animation\nPlay"));
  controlPlay->setWhatsThis (tr("&Play\n\nStart playing (or stop) the animation\nPlay"));
  connect (controlPlay, SIGNAL (activated ()), this,SLOT (slotcontrolPlay ()));

  controlRewind =new Q3Action (tr ("&Rewind"), tr ("&Rewind"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_R), this);
  controlRewind->setStatusTip (tr ("Rewind to beginning\nRewind"));
  controlRewind->setWhatsThis (tr ("&Rewind\n\nRewind to beginning\nRewind"));
  connect (controlRewind, SIGNAL (activated ()), this,SLOT (slotcontrolRewind ()));

  controlGoToEnd =new Q3Action (tr ("&Go To End"), tr ("&Go To End"), 0, this);
  controlGoToEnd->setStatusTip (tr ("Fast forward to end\nGo To End"));
  controlGoToEnd->setWhatsThis (tr ("&Go To End\n\nFast forward to end\nGo To End"));
  connect (controlGoToEnd, SIGNAL (activated ()), this,SLOT (slotcontrolGoToEnd ()));

  controlStepForward =new Q3Action (tr ("Step &Forward"), tr ("Step &Forward"),Q3Accel::stringToKey ("Ctrl+>"), this);
  controlStepForward->setStatusTip (tr("Step forward one frame\nStep Forward [>]"));
  controlStepForward->setWhatsThis (tr("Step &Forward\n\nStep forward one frame\nStep Forward [>]"));
  connect (controlStepForward, SIGNAL (activated ()), this, SLOT (slotcontrolStepForward ()));

  controlStepBackward =new Q3Action (tr ("Step &Backward"), tr ("Step &Backward"),Q3Accel::stringToKey ("Ctrl+<"), this);
  controlStepBackward->setStatusTip (tr ("Step back one frame\nStep Back [<]"));
  controlStepBackward->setWhatsThis (tr("Step &Backward\n\nStep back one frame\nStep Back [<]"));
  connect (controlStepBackward, SIGNAL (activated ()), this,SLOT (slotcontrolStepBackward ()));

  controlTestMovie =new Q3Action (tr ("Test &Movie"), tr ("Test &Movie"),QKeySequence (Qt::CTRL + Qt::Key_Return), this);
  controlTestMovie->setStatusTip (tr ("Run the movie in test mode"));
  controlTestMovie->setWhatsThis (tr ("Test &Movie\n\nRun the movie in test mode"));
  connect (controlTestMovie, SIGNAL (activated ()), this,SLOT (slotcontrolTestMovie ()));

  controlDebugMovie =new Q3Action (tr ("&Debug Movie"), tr ("&Debug Movie"),QKeySequence (Qt::CTRL + Qt::SHIFT + Qt::Key_Return), this);
  controlDebugMovie->setStatusTip (tr ("Run the movie in test mode and open the debugger"));
  controlDebugMovie->setWhatsThis (tr("&Debug Movie\n\nRun the movie in test mode and open the debugger"));
  connect (controlDebugMovie, SIGNAL (activated ()), this,SLOT (slotcontrolDebugMovie ()));

  controlTestScene =new Q3Action (tr ("Test &Scene"), tr ("Test &Scene"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_Return), this);
  controlTestScene->setStatusTip (tr ("Run the current scene in test mode"));
  controlTestScene->setWhatsThis (tr ("Test &Scene\n\nRun the current scene in test mode"));
  connect (controlTestScene, SIGNAL (activated ()), this,SLOT (slotcontrolTestScene ()));

  controlLoopPlayback =new Q3Action (tr ("&Loop Playback"), tr ("&Loop Playback"), 0, this);
  controlLoopPlayback->setStatusTip (tr ("Play the animation in a continuous loop"));
  controlLoopPlayback->setWhatsThis (tr("&Loop Playback\n\nPlay the animation in a continuous loop"));
  connect (controlLoopPlayback, SIGNAL (activated ()), this,SLOT (slotcontrolLoopPlayback ()));

  controlPlayAllScenes =new Q3Action (tr ("Play &All Scenes"), tr ("Play &All Scenes"), 0, this);
  controlPlayAllScenes->setStatusTip (tr ("Play all movie scenes as a continous animation"));
  controlPlayAllScenes->setWhatsThis (tr("Play &All Scenes\n\nPlay all movie scenes as a continous animation"));
  connect (controlPlayAllScenes, SIGNAL (activated ()), this,SLOT (slotcontrolPlayAllScenes ()));

  controlEnableSimpleFrameActions =new Q3Action (tr ("Enable Simple Frame Act&ions"),tr ("Enable Simple Frame Act&ions"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_A), this);
  controlEnableSimpleFrameActions->setStatusTip (tr("Perform some frame actions when playing the animation"));
  controlEnableSimpleFrameActions->setWhatsThis (tr("Enable Simple Frame Act&ions\n\nPerform some frame actions when playing the animation"));
  connect (controlEnableSimpleFrameActions, SIGNAL (activated ()), this,SLOT (slotcontrolEnableSimpleFrameActions ()));

  controlEnableSimpleButtons =new Q3Action (tr ("Enable Simple Bu&ttons"), tr ("Enable Simple Bu&ttons"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_B), this);
  controlEnableSimpleButtons->setStatusTip (tr ("Test the action of buttons in the movie"));
  controlEnableSimpleButtons->setWhatsThis (tr("Enable Simple Bu&ttons\n\nTest the action of buttons in the movie"));
  connect (controlEnableSimpleButtons, SIGNAL (activated ()), this,SLOT (slotcontrolEnableSimpleButtons ()));

  controlMuteSounds =new Q3Action (tr ("Mute Sou&nds"), tr ("Mute Sou&nds"),QKeySequence (Qt::CTRL + Qt::ALT + Qt::Key_M), this);
  controlMuteSounds->setStatusTip (tr ("Mute the playing of sounds with the animation\n"));
  controlMuteSounds->setWhatsThis (tr("Mute Sou&nds\n\nMute the playing of sounds with the animation\n"));
  connect (controlMuteSounds, SIGNAL (activated ()), this,SLOT (slotcontrolMuteSounds ()));

  controlEnableLivePreview =new Q3Action (tr ("Enable Live Preview"), tr ("Enable Live Preview"), 0,this);
  controlEnableLivePreview->setStatusTip (tr ("Enable Live Preview of Components"));
  controlEnableLivePreview->setWhatsThis (tr("Enable Live Preview\n\nEnable Live Preview of Components"));
  connect (controlEnableLivePreview, SIGNAL (activated ()), this, SLOT (slotcontrolEnableLivePreview ()));

  /*windowMain = new Q3Action(tr( "&Main"),tr( "&Main"),0,this);
     windowMain->setStatusTip(tr("Show or hide the main toolbar"));
     windowMain->setWhatsThis(tr("&Main\n\nShow or hide the main toolbar"));
     connect(windowMain,SIGNAL(activated()), this, SLOT(slotwindowMain()));

     windowStatus = new Q3Action(tr( "&Status"),tr( "&Status"),0,this);
     windowStatus->setStatusTip(tr("Show or hide the status bar"));
     windowStatus->setWhatsThis(tr("&Status\n\nShow or hide the status bar"));
     connect(windowStatus,SIGNAL(activated()), this, SLOT(slotwindowStatus())); */

  windowController =new Q3Action (tr ("C&ontroller"), tr ("C&ontroller"), 0, this);
  windowController->setStatusTip (tr ("Show or hide the movie playback controller"));
  windowController->setWhatsThis (tr("C&ontroller\n\nShow or hide the movie playback controller"));
  connect (windowController, SIGNAL (activated ()), this,SLOT (slotwindowController ()));

  windowAnswers = new Q3Action (tr ("Answers"), tr ("Answers"), 0, this);
  windowAnswers->setStatusTip (tr("Get answers to technical questions directly from Macromedia on-line"));
  windowAnswers->setWhatsThis (tr("Answers\n\nGet answers to technical questions directly from Macromedia on-line"));
  connect (windowAnswers, SIGNAL (activated ()), this,SLOT (slotwindowAnswers ()));

  windowAlign =new Q3Action (tr ("Ali&gn"), tr ("Ali&gn"),QKeySequence (Qt::CTRL + Qt::Key_K), this);
  windowAlign->setStatusTip (tr ("Align selected objects to each other or the stage"));
  windowAlign->setWhatsThis (tr("Ali&gn\n\nAlign selected objects to each other or the stage"));
  connect (windowAlign, SIGNAL (activated ()), this,SLOT (slotwindowAlign ()));

  windowColorMixer =new Q3Action (tr ("Color Mi&xer"), tr ("Color Mi&xer"), QKeySequence (Qt::SHIFT + Qt::Key_F2), this);
  windowColorMixer->setStatusTip (tr("Change the current color using RGB  HSB or HEX values"));
  windowColorMixer->setWhatsThis (tr("Color Mi&xer\n\nChange the current color using RGB  HSB or HEX values"));
  connect (windowColorMixer, SIGNAL (activated ()), this,SLOT (slotwindowColorMixer ()));

  windowColorSwatches =new Q3Action (tr ("Color S&watches"), tr ("Color S&watches"),QKeySequence (Qt::SHIFT + Qt::Key_F3), this);
  windowColorSwatches->setStatusTip (tr ("Select colors from swatches and manage swatches"));
  windowColorSwatches->setWhatsThis (tr("Color S&watches\n\nSelect colors from swatches and manage swatches"));
  connect (windowColorSwatches, SIGNAL (activated ()), this,SLOT (slotwindowColorSwatches ()));

  windowInfo =new Q3Action (tr ("&Info"), tr ("&Info"),QKeySequence (Qt::CTRL + Qt::Key_I), this);
  windowInfo->setStatusTip (tr("Show or change the properties and position of the selected object"));
  windowInfo->setWhatsThis (tr("&Info\n\nShow or change the properties and position of the selected object"));
  connect (windowInfo, SIGNAL (activated ()), this,SLOT (slotwindowInfo ()));

  windowScene = new Q3Action (tr ("Sc&ene"), tr ("Sc&ene"),QKeySequence (Qt::CTRL + Qt::Key_U), this);
  windowScene->setStatusTip (tr("Show or change a list of the scenes in the current movie"));
  windowScene->setWhatsThis (tr("Sc&ene\n\nShow or change a list of the scenes in the current movie"));
  connect (windowScene, SIGNAL (activated ()), this,SLOT (slotwindowScene ()));

  windowTransform =new Q3Action (tr ("&Transform"), tr ("&Transform"),QKeySequence (Qt::CTRL + Qt::Key_T), this);
  windowTransform->setStatusTip (tr("Scale and/or rotate the selection using numeric values"));
  windowTransform->setWhatsThis (tr("&Transform\n\nScale and/or rotate the selection using numeric values"));
  connect (windowTransform, SIGNAL (activated ()), this,SLOT (slotwindowTransform ()));

  windowActions =new Q3Action (tr ("&Actions"), tr ("&Actions"), QKeySequence (Qt::Key_F2), this);
  windowActions->setStatusTip (tr ("Show or hide the Actions panel"));
  windowActions->setWhatsThis (tr ("&Actions\n\nShow or hide the Actions panel"));
  connect (windowActions, SIGNAL (activated ()), this,SLOT (slotwindowActions ()));

  windowDebugger = new Q3Action (tr ("&Debugger"), tr ("&Debugger"),QKeySequence (Qt::SHIFT + Qt::Key_F4), this);
  windowDebugger->setStatusTip (tr ("Show or hide the Debugger"));
  windowDebugger->setWhatsThis (tr ("&Debugger\n\nShow or hide the Debugger"));
  connect (windowDebugger, SIGNAL (activated ()), this,SLOT (slotwindowDebugger ()));

  windowMovieExplorer =new Q3Action (tr ("&Movie Explorer"), tr ("&Movie Explorer"),QKeySequence (Qt::Key_F4), this);
  windowMovieExplorer->setStatusTip (tr ("Show or hide the Movie Explorer"));
  windowMovieExplorer->setWhatsThis (tr ("&Movie Explorer\n\nShow or hide the Movie Explorer"));
  connect (windowMovieExplorer, SIGNAL (activated ()), this,SLOT (slotwindowMovieExplorer ()));

  windowReference =new Q3Action (tr ("Re&ference"), tr ("Re&ference"),QKeySequence (Qt::SHIFT + Qt::Key_F1), this);
  windowReference->setStatusTip (tr ("Show or hide the Reference panel"));
  windowReference->setWhatsThis (tr ("Re&ference\n\nShow or hide the Reference panel"));
  connect (windowReference, SIGNAL (activated ()), this,SLOT (slotwindowReference ()));

  windowOutput =new Q3Action (tr ("O&utput"), tr ("O&utput"),QKeySequence (Qt::SHIFT + Qt::Key_F9), this);
  windowOutput->setStatusTip (tr ("Display output information when testing a movie"));
  windowOutput->setWhatsThis (tr("O&utput\n\nDisplay output information when testing a movie"));
  connect (windowOutput, SIGNAL (activated ()), this,SLOT (slotwindowOutput ()));

  windowAccessibility =new Q3Action (tr ("Acce&ssibility"), tr ("Acce&ssibility"),QKeySequence (Qt::Key_F9), this);
  windowAccessibility->setStatusTip (tr("Apply accessibility information to selected objects on the stage"));
  windowAccessibility->setWhatsThis (tr("Acce&ssibility\n\nApply accessibility information to selected objects on the stage"));
  connect (windowAccessibility, SIGNAL (activated ()), this,SLOT (slotwindowAccessibility ()));

  windowComponents =new Q3Action (tr ("&Components"), tr ("&Components"),QKeySequence (Qt::Key_F11), this);
  windowComponents->setStatusTip (tr ("Macromedia Component Widgets"));
  windowComponents->setWhatsThis (tr ("&Components\n\nMacromedia Component Widgets"));
  connect (windowComponents, SIGNAL (activated ()), this,SLOT (slotwindowComponents ()));

  windowComponentParameters =new Q3Action (tr ("Component Paramete&rs"), tr ("Component Paramete&rs"),QKeySequence (Qt::SHIFT + Qt::Key_F11), this);
  windowComponentParameters->setStatusTip (tr("Show or change the parameters associated with the selected movie clip"));
  windowComponentParameters->setWhatsThis (tr("Component Paramete&rs\n\nShow or change the parameters associated with the selected movie clip"));
  connect (windowComponentParameters, SIGNAL (activated ()), this,SLOT (slotwindowComponentParameters ()));

  windowLibrary =new Q3Action (tr ("&Library"), tr ("&Library"),QKeySequence (Qt::CTRL + Qt::Key_L), this);
  windowLibrary->setStatusTip (tr ("Show the floating library window for this document"));
  windowLibrary->setWhatsThis (tr("&Library\n\nShow the floating library window for this document"));
  connect (windowLibrary, SIGNAL (activated ()), this,SLOT (slotwindowLibrary ()));

  windowlibraries = new Q3Action (tr ("libraries"), tr ("libraries"), 0, this);
  windowlibraries->setStatusTip (tr ("Open a library window"));
  windowlibraries->setWhatsThis (tr ("libraries\n\nOpen a library window"));
  connect (windowlibraries, SIGNAL (activated ()), this,SLOT (slotwindowlibraries ()));

  windowPanelSets = new Q3Action (tr ("Panel Sets"), tr ("Panel Sets"), 0, this);
  windowPanelSets->setStatusTip (tr ("Open panel set"));
  windowPanelSets->setWhatsThis (tr ("Panel Sets\n\nOpen panel set"));
  connect (windowPanelSets, SIGNAL (activated ()), this,SLOT (slotwindowPanelSets ()));

  windowSavePanelLayout =new Q3Action (tr ("Save Panel Layout..."), tr ("Save Panel Layout..."), 0,this);
  windowSavePanelLayout->setStatusTip (tr ("Saves the current panel layout settings"));
  windowSavePanelLayout->setWhatsThis (tr("Save Panel Layout...\n\nSaves the current panel layout settings"));
  connect (windowSavePanelLayout, SIGNAL (activated ()), this,SLOT (slotwindowSavePanelLayout ()));

  windowCloseAllPanels =new Q3Action (tr ("Close All Panels"), tr ("Close All Panels"), 0, this);
  windowCloseAllPanels->setStatusTip (tr ("Closes all panels"));
  windowCloseAllPanels->setWhatsThis (tr ("Close All Panels\n\nCloses all panels"));
  connect (windowCloseAllPanels, SIGNAL (activated ()), this,SLOT (slotwindowCloseAllPanels ()));

  windowNewWindow =new Q3Action (tr ("New Window"), tr ("&New Window"), 0, this);
  windowNewWindow->setStatusTip (tr ("Opens a new view for the current document"));
  windowNewWindow->setWhatsThis (tr("New Window\n\nOpens a new view for the current document"));
  connect (windowNewWindow, SIGNAL (activated ()), this, SLOT (slotWindowNewWindow ()));

  windowCascade = new Q3Action (tr ("Cascade"), tr ("&Cascade"), 0, this);
  windowCascade->setStatusTip (tr ("Cascades all windows"));
  windowCascade->setWhatsThis (tr ("Cascade\n\nCascades all windows"));
  connect (windowCascade, SIGNAL (activated ()), pWorkspace, SLOT (cascade ()));

  windowTile = new Q3Action (tr ("Tile"), tr ("&Tile"), 0, this);
  windowTile->setStatusTip (tr ("Tiles all windows"));
  windowTile->setWhatsThis (tr ("Tile\n\nTiles all windows"));
  connect (windowTile, SIGNAL (activated ()), pWorkspace, SLOT (tile ()));

  windowProperties =new Q3Action (tr ("Properties"), tr ("&Properties"),Q3Accel::stringToKey (tr ("Ctrl+F3")), this, 0, true);
  windowProperties->setStatusTip (tr ("Show or hide the Property Inspector"));
  windowProperties->setWhatsThis (tr ("Properties\n\nShow or hide the Property Inspector"));
  windowProperties->setOn (true);
  connect (windowProperties, SIGNAL (activated ()), this,SLOT (slotWindowProperities ()));

  windowTimeLine =new Q3Action (tr ("Time Line"), tr ("Time Line"),Q3Accel::stringToKey (tr ("Ctrl+Alt+T")), this, 0, true);
  windowTimeLine->setStatusTip (tr("Show or hide the animation timeline and layers controls"));
  windowTimeLine->setWhatsThis (tr("Time Line\n\nShow or hide the animation timeline and layers controls"));
  windowTimeLine->setOn (true);
  connect (windowTimeLine, SIGNAL (activated ()), this,SLOT (slotWindowTimeLine ()));

  windowTools = new Q3Action (tr ("Tools"), tr ("Tools"), 0, this, 0, true);
  windowTools->setStatusTip (tr ("Show or hide the drawing toolbar"));
  windowTools->setWhatsThis (tr ("Tools\n\nShow or hide the drawing toolbar"));
  windowTools->setOn (true);
  connect (windowTools, SIGNAL (activated ()), this,SLOT (slotWindowTools ()));

  windowAction = new Q3ActionGroup (this, 0, false);
  windowAction->insert (windowNewWindow);
  windowAction->insert (windowCascade);
  windowAction->insert (windowTile);
  helpUsingF4l =new Q3Action (tr ("Using &F4L"), tr ("Using &F4L"), QKeySequence (Qt::Key_F1), this);
  helpUsingF4l->setStatusTip (tr ("Display the help contents"));
  helpUsingF4l->setWhatsThis (tr ("Using &F4L\n\nDisplay the help contents"));
  connect (helpUsingF4l, SIGNAL (activated ()), this,SLOT (slothelpUsingF4l ()));

  helpActionScriptDictionary =new Q3Action (tr ("ActionScript &Dictionary"),tr ("ActionScript &Dictionary"), 0, this);
  helpActionScriptDictionary->setStatusTip (tr ("Display the ActionScript Dictionary"));
  helpActionScriptDictionary->setWhatsThis (tr("ActionScript &Dictionary\n\nDisplay the ActionScript Dictionary"));
  connect (helpActionScriptDictionary, SIGNAL (activated ()), this,SLOT (slothelpActionScriptDictionary ()));

  helpF4lExchange =new Q3Action (tr ("F4L Exchange"), tr ("F4L Exchange"), 0, this);
  helpF4lExchange->setStatusTip (tr ("Go to the F4L Exhange web site."));
  helpF4lExchange->setWhatsThis (tr ("F4L Exchange\n\nGo to the F4L Exhange web site."));
  connect (helpF4lExchange, SIGNAL (activated ()), this,SLOT (slothelpF4lExchange ()));

  helpManageExtensions =new Q3Action (tr ("Manage Extensions..."), tr ("Manage Extensions..."), 0,this);
  helpManageExtensions->setStatusTip (tr ("Manage Extensions"));
  helpManageExtensions->setWhatsThis (tr ("Manage Extensions...\n\nManage Extensions"));
  connect (helpManageExtensions, SIGNAL (activated ()), this,SLOT (slothelpManageExtensions ()));

  helpSamples = new Q3Action (tr ("&Samples"), tr ("&Samples"), 0, this);
  helpSamples->setStatusTip (tr (""));
  helpSamples->setWhatsThis (tr ("&Samples\n\n"));
  connect (helpSamples, SIGNAL (activated ()), this,SLOT (slothelpSamples ()));
  helpF4lSupportCenter = new Q3Action (tr ("F4L Support &Center"), tr ("F4L Support &Center"), 0, this);
  helpF4lSupportCenter->setStatusTip (tr ("Open your web browser to the F4L Developers Center"));
  helpF4lSupportCenter->setWhatsThis (tr("F4L Support &Center\n\nOpen your web browser to the F4L Developers Center"));
  connect (helpF4lSupportCenter, SIGNAL (activated ()), this,SLOT (slothelpF4lSupportCenter ()));

  helpRegisterF4l = new Q3Action (tr ("&Register F4L"), tr ("&Register F4L"), 0, this);
  helpRegisterF4l->setStatusTip (tr ("Register your copy of F4L using your web browser"));
  helpRegisterF4l->setWhatsThis (tr("&Register F4L\n\nRegister your copy of F4L using your web browser"));
  connect (helpRegisterF4l, SIGNAL (activated ()), this,SLOT (slothelpRegisterF4l ()));

  helpAboutApp = new Q3Action (tr ("About"), tr ("&About..."), 0, this);
  helpAboutApp->setStatusTip (tr ("About the application"));
  helpAboutApp->setWhatsThis (tr ("About\n\nAbout the application"));
  connect (helpAboutApp, SIGNAL (activated ()), this,SLOT (slotHelpAbout ()));
}

void F4lmApp::initMenuBar ()
{

  ///////////////////////////////////////////////////////////////////
  // MENUBAR
  ///////////////////////////////////////////////////////////////////
  // menuBar entry pFileMenu
  pFileMenu = new Q3PopupMenu ();
  fileNew->addTo (pFileMenu);
  fileNewFromTemplate->addTo (pFileMenu);
  fileOpen->addTo (pFileMenu);
  fileOpenAsLibrary->addTo (pFileMenu);
  fileClose->addTo (pFileMenu);
  pFileMenu->insertSeparator ();
  fileSave->addTo (pFileMenu);
  fileSaveAs->addTo (pFileMenu);
  fileSaveAsTemplate->addTo (pFileMenu);
  fileRevert->addTo (pFileMenu);
  pFileMenu->insertSeparator ();
  fileImport->addTo (pFileMenu);
  fileImportToLibrary->addTo (pFileMenu);
  fileExportMovie->addTo (pFileMenu);
  fileExportImage->addTo (pFileMenu);
  pFileMenu->insertSeparator ();
  Q3PopupMenu * pFileMenuPublishPreview = new Q3PopupMenu ();
  filePublishPreview_Default->addTo (pFileMenuPublishPreview);
  filePublishPreview_Flash->addTo (pFileMenuPublishPreview);
  filePublishPreview_GIF->addTo (pFileMenuPublishPreview);
  filePublishPreview_Html->addTo (pFileMenuPublishPreview);
  filePublishPreview_JPEG->addTo (pFileMenuPublishPreview);
  filePublishPreview_PNG->addTo (pFileMenuPublishPreview);
  filePublishPreview_Projector->addTo (pFileMenuPublishPreview);
  filePublishPreview_Quicktime->addTo (pFileMenuPublishPreview);
  pFileMenu->insertItem (tr ("Publish Preview"), pFileMenuPublishPreview);
  filePublish->addTo (pFileMenu);
  pFileMenu->insertSeparator ();
  filePageSetup->addTo (pFileMenu);
  filePrintPreview->addTo (pFileMenu);
  filePrint->addTo (pFileMenu);
  pFileMenu->insertSeparator ();
  fileSend->addTo (pFileMenu);
  pFileMenu->insertSeparator ();
  pFileMenu->insertItem (tr ("burda recent olacak ama nasl?"));
  pFileMenu->insertSeparator ();
  fileQuit->addTo (pFileMenu);

  ///////////////////////////////////////////////////////////////////
  // menuBar entry editMenu
  pEditMenu = new Q3PopupMenu ();
  editUndo->addTo (pEditMenu);
  editRedo->addTo (pEditMenu);
  pEditMenu->insertSeparator ();
  editCut->addTo (pEditMenu);
  editCopy->addTo (pEditMenu);
  editPaste->addTo (pEditMenu);
  editPasteinPlace->addTo (pEditMenu);
  editPasteSpecial->addTo (pEditMenu);
  editClear->addTo (pEditMenu);
  pEditMenu->insertSeparator ();
  editDuplicate->addTo (pEditMenu);
  editSelectAll->addTo (pEditMenu);
  editDeselectAll->addTo (pEditMenu);
  pEditMenu->insertSeparator ();
  editCutFrames->addTo (pEditMenu);
  editCopyFrames->addTo (pEditMenu);
  editPasteFrames->addTo (pEditMenu);
  editClearFrames->addTo (pEditMenu);
  editSelectAllFrames->addTo (pEditMenu);
  pEditMenu->insertSeparator ();
  editEditSymbols->addTo (pEditMenu);
  editEditSelected->addTo (pEditMenu);
  editEditInPlace->addTo (pEditMenu);
  editEditAll->addTo (pEditMenu);
  pEditMenu->insertSeparator ();
  editPrefences->addTo (pEditMenu);
  editKeyboardShourtCuts->addTo (pEditMenu);
  editFontMapping->addTo (pEditMenu);

  ///////////////////////////////////////////////////////////////////
  // menuBar entry viewMenu
  pViewMenu = new Q3PopupMenu ();
  //pViewMenu->setCheckable(true);
  /*viewToolBar->addTo(pViewMenu);
     viewStatusBar->addTo(pViewMenu); */
  Q3PopupMenu * pViewMenuGOTO = new Q3PopupMenu ();
  viewFirst->addTo (pViewMenuGOTO);
  viewPrevious->addTo (pViewMenuGOTO);
  viewNext->addTo (pViewMenuGOTO);
  viewLast->addTo (pViewMenuGOTO);
  pViewMenuGOTO->insertSeparator ();
  viewScenes->addTo (pViewMenuGOTO);
  pViewMenu->insertItem (tr ("&Go To"), pViewMenuGOTO);
  pViewMenu->insertSeparator ();
  viewZoomIn->addTo (pViewMenu);
  viewZoomOut->addTo (pViewMenu);
  Q3PopupMenu * pViewMenuMagnification = new Q3PopupMenu ();
  viewMagnification25->addTo (pViewMenuMagnification);
  viewMagnification50->addTo (pViewMenuMagnification);
  viewMagnification100->addTo (pViewMenuMagnification);
  viewMagnification200->addTo (pViewMenuMagnification);
  viewMagnification400->addTo (pViewMenuMagnification);
  viewMagnification800->addTo (pViewMenuMagnification);
  pViewMenuMagnification->insertSeparator ();
  viewShowFrame->addTo (pViewMenuMagnification);
  viewShowAll->addTo (pViewMenuMagnification);
  pViewMenu->insertItem (tr ("&Magnification"), pViewMenuMagnification);
  pViewMenu->insertSeparator ();
  viewAction->addTo (pViewMenu);
  pViewMenu->insertSeparator ();
  viewTimeline->addTo (pViewMenu);
  viewWorkArea->addTo (pViewMenu);
  pViewMenu->insertSeparator ();
  viewRulers->addTo (pViewMenu);
  Q3PopupMenu * pViewMenuGrid = new Q3PopupMenu ();
  viewShowGrid->addTo (pViewMenuGrid);
  viewSnaptoGrid->addTo (pViewMenuGrid);
  viewEditGrid->addTo (pViewMenuGrid);
  pViewMenu->insertItem (tr ("Gri&d"), pViewMenuGrid);
  Q3PopupMenu * pViewMenuGuides = new Q3PopupMenu ();
  viewShowGuides->addTo (pViewMenuGuides);
  viewLockGuides->addTo (pViewMenuGuides);
  viewSnaptoGuides->addTo (pViewMenuGuides);
  viewEditGuides->addTo (pViewMenuGuides);
  pViewMenu->insertSeparator ();
  viewSnaptoPixels->addTo (pViewMenu);
  viewSnaptoObjects->addTo (pViewMenu);
  pViewMenu->insertSeparator ();
  viewShowShapeHints->addTo (pViewMenu);
  pViewMenu->insertSeparator ();
  viewHideEdges->addTo (pViewMenu);
  viewHidePanels->addTo (pViewMenu);

  ///////////////////////////////////////////////////////////////////
  // EDIT YOUR APPLICATION SPECIFIC MENUENTRIES HERE
  pInsertMenu = new Q3PopupMenu ();
  insertConverttoSymbol->addTo (pInsertMenu);
  insertNewSymbol->addTo (pInsertMenu);
  pInsertMenu->insertSeparator ();
  insertLayer->addTo (pInsertMenu);
  insertLayerFolder->addTo (pInsertMenu);
  insertMotionGuide->addTo (pInsertMenu);
  pInsertMenu->insertSeparator ();
  insertFrame->addTo (pInsertMenu);
  insertRemoveFrames->addTo (pInsertMenu);
  pInsertMenu->insertSeparator ();
  insertKeyframe->addTo (pInsertMenu);
  insertBlankKeyframe->addTo (pInsertMenu);
  insertClearKeyframe->addTo (pInsertMenu);
  pInsertMenu->insertSeparator ();
  insertCreateMotionTween->addTo (pInsertMenu);
  pInsertMenu->insertSeparator ();
  insertScene->addTo (pInsertMenu);
  insertRemoveScene->addTo (pInsertMenu);

  pModifyMenu = new Q3PopupMenu ();
  modifyLayer->addTo (pModifyMenu);
  modifyScene->addTo (pModifyMenu);
  modifyDocument->addTo (pModifyMenu);
  pModifyMenu->insertSeparator ();
  modifySmooth->addTo (pModifyMenu);
  modifyStraighten->addTo (pModifyMenu);
  modifyOptimize->addTo (pModifyMenu);

  Q3PopupMenu * pModifyMenuShape = new Q3PopupMenu ();
  modifyConvertLinestoFills->addTo (pModifyMenuShape);
  modifyExpandFill->addTo (pModifyMenuShape);
  modifySoftenFillEdges->addTo (pModifyMenuShape);
  pModifyMenuShape->insertSeparator ();
  modifyAddShapeHint->addTo (pModifyMenuShape);
  modifyRemoveAllHints->addTo (pModifyMenuShape);
  pModifyMenu->insertItem (tr ("Sha&pe"), pModifyMenuShape);
  pModifyMenu->insertSeparator ();
  modifySwapSymbol->addTo (pModifyMenu);
  modifyDuplicateSymbol->addTo (pModifyMenu);
  pModifyMenu->insertSeparator ();
  modifySwapBitmap->addTo (pModifyMenu);
  modifyTraceBitmap->addTo (pModifyMenu);
  pModifyMenu->insertSeparator ();

  Q3PopupMenu * pModifyMenuTransform = new Q3PopupMenu ();
  modifyFreeTransform->addTo (pModifyMenuTransform);
  modifyDistort->addTo (pModifyMenuTransform);
  modifyEnvelope->addTo (pModifyMenuTransform);
  modifyScale->addTo (pModifyMenuTransform);
  modifyRotateandSkew->addTo (pModifyMenuTransform);
  modifyScaleandRotate->addTo (pModifyMenuTransform);
  pModifyMenuTransform->insertSeparator ();
  modifyRotate90CW->addTo (pModifyMenuTransform);
  modifyRotate90CCW->addTo (pModifyMenuTransform);
  pModifyMenuTransform->insertSeparator ();
  modifyFlipVertical->addTo (pModifyMenuTransform);
  modifyFlipHorizontal->addTo (pModifyMenuTransform);
  pModifyMenuTransform->insertSeparator ();
  modifyRemoveTransform->addTo (pModifyMenuTransform);
  pModifyMenu->insertItem (tr ("&Transform"), pModifyMenuTransform);

  Q3PopupMenu * pModifyMenuArrange = new Q3PopupMenu ();
  modifyBringtoFront->addTo (pModifyMenuArrange);
  modifyBringForward->addTo (pModifyMenuArrange);
  modifySendBackward->addTo (pModifyMenuArrange);
  modifySendtoBack->addTo (pModifyMenuArrange);
  pModifyMenuArrange->insertSeparator ();
  modifyLock->addTo (pModifyMenuArrange);
  modifyUnlockAll->addTo (pModifyMenuArrange);
  pModifyMenuArrange->insertSeparator ();
  pModifyMenu->insertItem (tr ("&Arrange"), pModifyMenuArrange);
  pModifyMenu->insertSeparator ();

  Q3PopupMenu * pModifyMenuFrames = new Q3PopupMenu ();
  modifyReverse->addTo (pModifyMenuFrames);
  modifySynchronizeSymbols->addTo (pModifyMenuFrames);
  modifyConverttoKeyframes->addTo (pModifyMenuFrames);
  modifyConverttoBlankKeyframes->addTo (pModifyMenuFrames);
  pModifyMenu->insertItem (tr ("Fram&es"), pModifyMenuFrames);
  pModifyMenu->insertSeparator ();
  modifyGroup->addTo (pModifyMenu);
  modifyUngroup->addTo (pModifyMenu);
  pModifyMenu->insertSeparator ();
  modifyBreakApart->addTo (pModifyMenu);
  modifyDistributetoLayers->addTo (pModifyMenu);
  pTextMenu = new Q3PopupMenu ();
  Q3PopupMenu * pTextMenuFont = new Q3PopupMenu ();
  //textFontFace->addTo(pTextMenuFont);
  QStringList familyNames;
  QFontDatabase fdb;
  QStringList scriptNames;
  Q3ValueList < int >scriptScripts;
  QStringList scriptSamples;
  QString family;
  QString script;
  QString style;
  QString size;
  familyNames = fdb.families ();
  QStringList newList;
  QString s;
  QStringList::Iterator it = familyNames.begin ();
  int idx = 0;
  for (; it != familyNames.end (); it++)
  {
    s = *it;
#if 0
    if (fdb.isSmoothlyScalable (*it))
      newList.append (s + "(TT)");
    else if (fdb.isBitmapScalable (*it))
      newList.append (s + "(BT)");
    else
#endif	/*
      */
      pTextMenuFont->insertItem ((s), properties->fontProperties,
                                 SLOT (slotFontChanged (int)), 0, idx++);
    newList.append (s);
  }
  //family=pTextMenuFont->currentText();

  pTextMenu->insertItem (tr ("&Font"), pTextMenuFont);
  Q3PopupMenu * pTextMenuSize = new Q3PopupMenu ();
  text8->addTo (pTextMenuSize);
  text9->addTo (pTextMenuSize);
  text10->addTo (pTextMenuSize);
  text11->addTo (pTextMenuSize);
  text12->addTo (pTextMenuSize);
  text14->addTo (pTextMenuSize);
  text18->addTo (pTextMenuSize);
  text24->addTo (pTextMenuSize);
  text36->addTo (pTextMenuSize);
  text48->addTo (pTextMenuSize);
  text72->addTo (pTextMenuSize);
  text96->addTo (pTextMenuSize);
  text120->addTo (pTextMenuSize);

  pTextMenu->insertItem (tr ("&Size"), pTextMenuSize);

  Q3PopupMenu * pTextMenuStyle = new Q3PopupMenu ();
  textPlain->addTo (pTextMenuStyle);

  pTextMenuStyle->insertSeparator ();
  textBold->addTo (pTextMenuStyle);
  textItalic->addTo (pTextMenuStyle);
  pTextMenuStyle->insertSeparator ();

  textSubscript->addTo (pTextMenuStyle);
  textSuperscript->addTo (pTextMenuStyle);
  pTextMenu->insertItem (tr ("St&yle"), pTextMenuStyle);
  Q3PopupMenu * pTextMenuAlign = new Q3PopupMenu ();

  textAlignLeft->addTo (pTextMenuAlign);
  textAlignCenter->addTo (pTextMenuAlign);
  textAlignRight->addTo (pTextMenuAlign);
  textJustify->addTo (pTextMenuAlign);

  pTextMenu->insertItem (tr ("&Align"), pTextMenuAlign);

  Q3PopupMenu * pTextMenuTracking = new Q3PopupMenu ();
  textIncrease->addTo (pTextMenuTracking);
  textDecrease->addTo (pTextMenuTracking);
  pTextMenuTracking->insertSeparator ();
  textReset->addTo (pTextMenuTracking);
  pTextMenu->insertItem (tr ("&Tracking"), pTextMenuTracking);
  pTextMenu->insertSeparator ();
  textScrollable->addTo (pTextMenu);

  pControlMenu = new Q3PopupMenu ();
  controlPlay->addTo (pControlMenu);
  controlRewind->addTo (pControlMenu);
  controlGoToEnd->addTo (pControlMenu);
  pControlMenu->insertSeparator ();
  controlStepForward->addTo (pControlMenu);
  controlStepBackward->addTo (pControlMenu);
  pControlMenu->insertSeparator ();
  controlTestMovie->addTo (pControlMenu);
  controlDebugMovie->addTo (pControlMenu);
  controlTestScene->addTo (pControlMenu);
  pControlMenu->insertSeparator ();
  controlLoopPlayback->addTo (pControlMenu);
  controlPlayAllScenes->addTo (pControlMenu);
  pControlMenu->insertSeparator ();
  controlEnableSimpleFrameActions->addTo (pControlMenu);
  controlEnableSimpleButtons->addTo (pControlMenu);
  controlMuteSounds->addTo (pControlMenu);
  controlEnableLivePreview->addTo (pControlMenu);

  ///////////////////////////////////////////////////////////////////
  // menuBar entry windowMenu
  pWindowMenu = new Q3PopupMenu (this);

  //pWindowMenu->setCheckable(true);


  connect (pWindowMenu, SIGNAL (aboutToShow ()), this,
           SLOT (windowMenuAboutToShow ()));


  ///////////////////////////////////////////////////////////////////
  // menuBar entry helpMenu
  pHelpMenu = new Q3PopupMenu ();

  helpUsingF4l->addTo (pHelpMenu);

  helpActionScriptDictionary->addTo (pHelpMenu);

  pHelpMenu->insertSeparator ();

  helpF4lExchange->addTo (pHelpMenu);
  helpManageExtensions->addTo (pHelpMenu);
  helpSamples->addTo (pHelpMenu);

  pHelpMenu->insertSeparator ();
  helpF4lSupportCenter->addTo (pHelpMenu);
  helpRegisterF4l->addTo (pHelpMenu);
  pHelpMenu->insertSeparator ();
  helpAboutApp->addTo (pHelpMenu);
  pHelpMenu->insertSeparator ();
  pHelpMenu->insertItem (tr ("What's &This"), this, SLOT (whatsThis ()),
                         Qt::SHIFT + Qt::Key_F1);

  menuBar()->insertItem (tr ("&File"), pFileMenu);
  menuBar()->insertItem (tr ("&Edit"), pEditMenu);
  menuBar()->insertItem (tr ("&View"), pViewMenu);
  menuBar()->insertItem (tr ("&Insert"), pInsertMenu);
  menuBar()->insertItem (tr ("&Modify"), pModifyMenu);
  menuBar()->insertItem (tr ("&Text"), pTextMenu);
  menuBar()->insertItem (tr ("&Control"), pControlMenu);
  menuBar()->insertItem (tr ("&Window"), pWindowMenu);
  menuBar()->insertItem (tr ("&Help"), pHelpMenu);
}

void F4lmApp::initToolBar ()
{
  ///////////////////////////////////////////////////////////////////
  // TOOLBAR
  fileToolbar = new Q3ToolBar (this, "file operations");
  fileNew->addTo (fileToolbar);
  fileOpen->addTo (fileToolbar);
  fileSave->addTo (fileToolbar);
  fileToolbar->addSeparator ();
  Q3WhatsThis::whatsThisButton (fileToolbar);
}

void F4lmApp::initStatusBar ()
{
  ///////////////////////////////////////////////////////////////////
  //STATUSBAR
  statusBar ()->message (tr ("Ready."));
}

void F4lmApp::initView ()
{
  ////////////////////////////////////////////////////////////////////
  // set the main widget here
  Q3VBox * view_back = new Q3VBox (this);
  view_back->setFrameStyle (Q3Frame::StyledPanel | Q3Frame::Sunken);
  pWorkspace = new QWorkspace (view_back);
  setCentralWidget (view_back);
}

void F4lmApp::createClient (F4lmDoc * doc)
{

  F4lmView * w = new F4lmView (doc, pWorkspace, 0, Qt::WDestructiveClose);
  w->installEventFilter (this);

  pWorkspace->addWindow(w,Qt::WDestructiveClose);
  pWorkspace->setActiveWindow(w);
  doc->addView (w);

  if (pWorkspace->windowList ().isEmpty ())	// show the very first window in maximized mode
    w->showMaximized ();
  else
    w->show ();
}



void F4lmApp::openDocumentFile (const char *file)
{
  statusBar ()->message (tr ("Opening file..."));

  F4lmDoc* doc;
  // check, if document already open. If yes, set the focus to the first view
  foreach (doc , pDocList)
  {
    if (doc->pathName () == file)
    {
      F4lmView * view = doc->firstView ();
      view->setFocus ();
      return;
    }
  }

  doc = new F4lmDoc ();
  pDocList.append (doc);
  doc->newDocument ();

  // Creates an untitled window if file is 0
  if (!file)
  {
    untitledCount += 1;
    QString fileName = QString (tr ("Untitled%1")).arg (untitledCount);
    doc->setPathName (fileName);
    doc->setTitle (fileName);
  }
  // Open the file
  else
  {
    if (!doc->openDocument (file))
    {
      QMessageBox::critical (this, tr ("Error !"),
                             tr ("Could not open document !"));
      delete doc;
      return;
    }
  }
  // create the window
  createClient (doc);

  statusBar ()->message (tr ("Ready."));
}

bool F4lmApp::queryExit ()
{
  int
  exit = QMessageBox::information (this, tr ("Quit..."),
                                   tr ("Do your really want to quit?"),
                                   QMessageBox::Ok, QMessageBox::Cancel);

  if (exit == 1)
  {}
  else
  {}
  ;

  return (exit == 1);
}

bool F4lmApp::eventFilter (QObject * object, QEvent * event)
{
  if ((event->type () == QEvent::Close) && ((F4lmApp *) object != this))
  {
    QCloseEvent * e = (QCloseEvent *) event;
    F4lmView * pView = (F4lmView *) object;

    F4lmDoc * pDoc = pView->getDocument ();
    if (pDoc->canCloseFrame (pView))
    {
      pDoc->removeView (pView);
      if (!pDoc->firstView ())
        pDocList.remove
        (pDoc);
      e->accept ();
    }
    else
      e->ignore ();
  }

  return QWidget::eventFilter (object, event);	// standard event processing
}



/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////


void F4lmApp::slotFileNew ()
{
  statusBar ()->message (tr ("Creating new file..."));
  openDocumentFile ();
  statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotfileNewFromTemplate (void) {}

void F4lmApp::slotFileOpen ()
{
  statusBar ()->message (tr ("Opening file..."));

  QString fileName = Q3FileDialog::getOpenFileName (0, 0, this);
  if (!fileName.isEmpty ())
  {
    openDocumentFile (fileName);
  }

  statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotFileSave ()
{
  statusBar ()->message (tr ("Saving file..."));

  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
  {
    F4lmDoc * doc = m->getDocument ();
    if (doc->title ().contains (tr ("Untitled")))
      slotFileSaveAs ();
    else
      if (!doc->saveDocument (doc->pathName ()))
        QMessageBox::critical (this, tr ("I/O Error !"),
                               tr ("Could not save the current document !"));
  }

  statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotFileSaveAs ()
{
  statusBar ()->message (tr ("Saving file under new filename..."));

  QString fn = Q3FileDialog::getSaveFileName (0, 0, this);
  if (!fn.isEmpty ())
  {
    F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
    if (m)
    {
      F4lmDoc * doc = m->getDocument ();
      if (!doc->saveDocument (fn))
      {
        QMessageBox::critical (this, tr ("I/O Error !"),
                               tr
                               ("Could not save the current document !"));
        return;
      }
      doc->changedViewList ();
    }
  }

  statusBar ()->message (tr ("Ready."));
}


void F4lmApp::slotFileClose ()
{
  statusBar ()->message (tr ("Closing file..."));

  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
  {
    F4lmDoc * doc = m->getDocument ();
    doc->closeDocument ();
  }

  statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotFilePrint ()
{
  statusBar ()->message (tr ("Printing..."));

  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
    m->print (printer);

  statusBar ()->message (tr ("Ready."));
}


void F4lmApp::slotFileQuit ()
{

  statusBar ()->message (tr ("Exiting application..."));

  ///////////////////////////////////////////////////////////////////
  // exits the Application
  //  if(doc->isModified())
  //  {
  //    if(queryExit())
  //    {
  //      qApp->quit();
  //    }
  //    else
  //    {
  //
  //    };
  //  }
  //  else
  //  {
  qApp->quit ();

  //  };

  statusBar ()->message (tr ("Ready."));

}

void F4lmApp::slotEditUndo ()
{
  statusBar ()->message (tr ("Reverting last action..."));

  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
    //   m->undo();
    statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotEditCut ()
{
  statusBar ()->message (tr ("Cutting selection..."));

  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
    //  m->cut();
    statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotEditCopy ()
{
  statusBar ()->message (tr ("Copying selection to clipboard..."));

  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
    //  m->copy();
    statusBar ()->message (tr ("Ready."));
}


void F4lmApp::slotEditPaste ()
{
  statusBar ()->message (tr ("Inserting clipboard contents..."));

  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
    //   m->paste();
    statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotViewToolBar (bool toggle)
{
  statusBar ()->message (tr ("Toggle toolbar..."));
  ///////////////////////////////////////////////////////////////////
  // turn Toolbar on or off
  if (toggle == false)
  {
    fileToolbar->hide ();
  }
  else
  {
    fileToolbar->show ();
  };

  statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotViewStatusBar (bool toggle)
{
  statusBar ()->message (tr ("Toggle statusbar..."));
  ///////////////////////////////////////////////////////////////////
  //turn Statusbar on or off
  if (toggle == false)
  {
    statusBar ()->hide ();
  }
  else
  {
    statusBar ()->show ();
  }

  statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotWindowNewWindow ()
{
  statusBar ()->message (tr ("Opening new document view..."));
  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
  {
    F4lmDoc * doc = m->getDocument ();
    createClient (doc);
  }
  statusBar ()->message (tr ("Ready."));
}

void F4lmApp::slotHelpAbout ()
{
  QMessageBox::about (this, tr ("About..."),
                      tr ("F4lm\nVersion BETA"
                          "\n(c) 2005 by �kan Pakdil"));
}

void F4lmApp::slotStatusHelpMsg (const QString & text)
{
  ///////////////////////////////////////////////////////////////////
  // change status message of whole statusbar temporary (text, msec)
  statusBar ()->message (text, 2000);
}

void F4lmApp::windowMenuAboutToShow ()
{
  pWindowMenu->clear ();
  windowNewWindow->addTo (pWindowMenu);
  pWindowMenu->insertSeparator ();

  Q3PopupMenu * pWindowMenuToolbars = new Q3PopupMenu ();
  viewToolBar->addTo (pWindowMenuToolbars);
  viewStatusBar->addTo (pWindowMenuToolbars);
  windowController->addTo (pWindowMenuToolbars);
  pWindowMenu->insertItem ("T&oolbars", pWindowMenuToolbars);
  windowTools->addTo (pWindowMenu);
  windowTimeLine->addTo (pWindowMenu);
  windowProperties->addTo (pWindowMenu);
  windowAnswers->addTo (pWindowMenu);
  pWindowMenu->insertSeparator ();
  windowAlign->addTo (pWindowMenu);
  windowColorMixer->addTo (pWindowMenu);
  windowColorSwatches->addTo (pWindowMenu);
  windowInfo->addTo (pWindowMenu);
  windowScene->addTo (pWindowMenu);
  windowTransform->addTo (pWindowMenu);
  pWindowMenu->insertSeparator ();
  windowActions->addTo (pWindowMenu);
  windowDebugger->addTo (pWindowMenu);
  windowMovieExplorer->addTo (pWindowMenu);
  windowReference->addTo (pWindowMenu);
  windowOutput->addTo (pWindowMenu);
  windowAccessibility->addTo (pWindowMenu);
  windowComponents->addTo (pWindowMenu);
  windowComponentParameters->addTo (pWindowMenu);
  windowLibrary->addTo (pWindowMenu);

  Q3PopupMenu * pWindowMenuLibraries = new Q3PopupMenu ();
  windowlibraries->addTo (pWindowMenuLibraries);
  pWindowMenu->insertItem ("Common Li&braries", pWindowMenuLibraries);
  pWindowMenu->insertSeparator ();

  Q3PopupMenu * pWindowMenuPanelSets = new Q3PopupMenu ();
  windowPanelSets->addTo (pWindowMenuPanelSets);
  pWindowMenu->insertItem ("Panel Sets", pWindowMenuPanelSets);
  windowSavePanelLayout->addTo (pWindowMenu);
  windowCloseAllPanels->addTo (pWindowMenu);
  pWindowMenu->insertSeparator ();
  windowCascade->addTo (pWindowMenu);
  windowTile->addTo (pWindowMenu);
  if (pWorkspace->windowList ().isEmpty ())
  {
    windowAction->setEnabled (false);
  }
  else
  {
    windowAction->setEnabled (true);
  }
  pWindowMenu->insertSeparator ();

  Q3PopupMenu * pWindowMenuWindowList = new Q3PopupMenu ();
  QWidgetList windows = pWorkspace->windowList ();
  for (int i = 0; i < int (windows.count ()); ++i)
  {
    int id = pWindowMenuWindowList->insertItem (QString ("&%1 ").arg (i + 1) +
             windows.at (i)->caption (), this,
             SLOT (windowMenuActivated (int)));
    pWindowMenuWindowList->setItemParameter (id, i);
    pWindowMenuWindowList->setItemChecked (id,
                                           pWorkspace->activeWindow () ==
                                           windows.at (i));

  }
  pWindowMenu->insertItem ("Window list", pWindowMenuWindowList);
}

void F4lmApp::windowMenuActivated (int id)
{
  QWidget * w = pWorkspace->windowList ().at (id);
  if (w)
    w->setFocus ();
}



/** This function makes that toolbar around scene */
void F4lmApp::initDockWindows ()
{
  //setRightJustification(false);
  timeLineDockableWindow = new Q3DockWindow (Q3DockWindow::InDock, this);
  timeLineDockableWindow->setResizeEnabled (true);
  timeLineDockableWindow->setHorizontalStretchable (true);
  timeLineDockableWindow->setVerticalStretchable (true);
  timeLineDockableWindow->setCaption ("Time Line");

  tl = new CTimeLine (timeLineDockableWindow, "Time Line");
  //tl->removeEventFilter(timeLineDockableWindow);
  tl->resize (width (), 150);
  tl->setMinimumHeight (150);
  //tl->setMaximumHeight(150);
  //tl->setMaximumWidth(500);
  //tl->setMinimumWidth(100);
  /*dtl->setMinimumHeight(200);
     dtl->setMaximumHeight(200);
     dtl->setMaximumWidth(10);
     dtl->setMinimumWidth(10); */
  //dtl->setFixedExtentHeight(150);
  timeLineDockableWindow->setMinimumHeight (150);
  timeLineDockableWindow->resize (width (), 150);
  timeLineDockableWindow->setWidget (tl);

  addDockWindow (timeLineDockableWindow, Qt::DockTop);

  Q3DockArea * areaFotTimeLine = timeLineDockableWindow->area ();

  areaFotTimeLine->moveDockWindow (timeLineDockableWindow, QPoint (0, 0),
                                   QRect (0, 0, width (), 150), false);

  //areaFotTimeLine->setMaximumWidth (width()-200);
  toolsDockableWindow = new Q3DockWindow (Q3DockWindow::InDock, this);
  toolsDockableWindow->setResizeEnabled (true);
  toolsDockableWindow->setHorizontalStretchable (true);
  toolsDockableWindow->setVerticalStretchable (true);
  toolsDockableWindow->setCaption ("Tools");

  tools = new CTools (toolsDockableWindow, "Tools", 0, this);
  /*tools->setMinimumHeight(300);
     tools->setMaximumHeight(300);
     tools->setMaximumWidth(60);
     tools->setMinimumWidth(60);
     dtools->setMinimumHeight(300);
     dtools->setMaximumHeight(300);
     dtools->setMaximumWidth(60);
     dtools->setMinimumWidth(60); */
  toolsDockableWindow->setWidget (tools);

  addDockWindow (toolsDockableWindow, Qt::DockLeft);

  colorSwatchesDockableWindow = new Q3DockWindow (Q3DockWindow::InDock, this);
  //colorSwatche->setResizeEnabled(true);
  colorSwatchesDockableWindow->setCaption ("Color Swatches");
  pColorSwatches =
    new CColorSwatches (colorSwatchesDockableWindow, "color_swatches", this);

  pColorSwatches->setMinimumHeight (125);	//130
  pColorSwatches->setMaximumHeight (125);

  pColorSwatches->setMaximumWidth (210);	//210
  pColorSwatches->setMinimumWidth (210);

  colorSwatchesDockableWindow->setWidget (pColorSwatches);

  addDockWindow (colorSwatchesDockableWindow, Qt::DockRight);

  colorDialogDockableWindow = new Q3DockWindow (Q3DockWindow::InDock, this);
  colorDialogDockableWindow->setResizeEnabled (true);
  colorDialogDockableWindow->setCaption ("Color Mixer");

  CColorDialog * colordia = new CColorDialog (colorDialogDockableWindow, "Color Mixer", this);

  /*colordia->setMinimumHeight(300);
     colordia->setMaximumHeight(300);
     colordia->setMaximumWidth(60);
     colordia->setMinimumWidth(60);
     color->setMinimumHeight(300);
     color->setMaximumHeight(300);
     color->setMaximumWidth(60);
     color->setMinimumWidth(60); */
  colorDialogDockableWindow->setWidget (colordia);


  addDockWindow (colorDialogDockableWindow, Qt::DockRight);
  propertiesDockableWindow = new Q3DockWindow (Q3DockWindow::InDock, this);
  propertiesDockableWindow->setResizeEnabled (true);
  propertiesDockableWindow->setCaption ("Properties");

  properties = new CProperties (propertiesDockableWindow, "Properties");
  properties->setMinimumHeight (80);
  /* //prop->setMinimumHeight(300);
     properties->setMaximumHeight(300);
     properties->setMaximumWidth(60);
     properties->setMinimumWidth(60);
     //prop->setMaximumWidth(400);
     properties->setMinimumHeight(100); */
  //prop->setMinimumHeight(100);
  //properties->resize(80,100);
  propertiesDockableWindow->setWidget (properties);

  addDockWindow (propertiesDockableWindow, Qt::DockBottom);
}

/** sets the ID of default object for drawing. */
void F4lmApp::setDefObjID (int ID)
{
  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
    m->defObjID = ID;
  //qDebug(QString::number(m->defObjID));
}


void F4lmApp::setDefObjCOLOR (QColor color)
{
  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if (m)
    m->defObjCOLOR = color;

  if (tools->StrokeColor->isOn ())
  {
    tools->strokpix.fill (color);
    tools->StrokeColor->setIconSet (QIcon (tools->strokpix));
  }

  if (tools->FillColor->isOn ())
  {
    //tools->FillColor->setOn(false);
    tools->fillpix.fill (color);
    tools->FillColor->setIconSet (QIcon (tools->fillpix));
  }
}

F4lmView * F4lmApp::slotCurrentView ()
{
  F4lmView * m = (F4lmView *) pWorkspace->activeWindow ();
  if(m==0){
      qDebug()<<"bos geldi:size:"<<pWorkspace->windowList().size();
      return (F4lmView *)pWorkspace->windowList().at(0);
  }
  if (m)
    return m;
}

void F4lmApp::slotWindowProperities ()
{
  if (propertiesDockableWindow->isVisible ())
    propertiesDockableWindow->hide ();
  else
    propertiesDockableWindow->show ();
}

void F4lmApp::slotWindowTools ()
{
  if (toolsDockableWindow->isVisible ())
    toolsDockableWindow->hide ();
  else
    toolsDockableWindow->show ();
}

void F4lmApp::slotWindowTimeLine ()
{
  if (timeLineDockableWindow->isVisible ())
    timeLineDockableWindow->hide ();
  else
    timeLineDockableWindow->show ();
}

void F4lmApp::fillTheStringTable ()
{
  //stringTable=new QMap<int,QString>;
  //stringTable[int]=QString

  QFile f ("string_table.txt");
  if (!f.open (QIODevice::ReadOnly))
    return;
  Q3TextStream t (&f);

  int i;
  QString s, temp;
  while (!t.eof ())
  {
    //t>>i>>s;
    s = t.readLine ();
    temp = s.section ('\t', 0, 0);
    i = temp.toInt ();
    s = s.section ('\t', 1, 1);
    s = s.remove (0, 1);
    s = s.remove (s.length () - 1, 1);
    //stringTable->insert(i, s);
    stringTable[i] = s;
    //      qDebug(QString::number(i)+" "+stringTable[i]);
    //cout<<i<<" "<<stringTable[i]<<endl;
  }
}

void F4lmApp::slotviewFirst () {}
void F4lmApp::slotviewPrevious () {}
void F4lmApp::slotviewNext () {}
void F4lmApp::slotviewLast () {}
void F4lmApp::slotviewScenes () {}
void F4lmApp::slotviewZoomIn () {}
void F4lmApp::slotviewZoomOut () {}
void F4lmApp::slotviewMagnification25 () {}
void F4lmApp::slotviewMagnification50 () {}
void F4lmApp::slotviewMagnification100 () {}
void F4lmApp::slotviewMagnification200 () {}
void F4lmApp::slotviewMagnification400 () {}
void F4lmApp::slotviewMagnification800 () {}
void F4lmApp::slotviewShowFrame () {}
void F4lmApp::slotviewShowAll () {}
void F4lmApp::slotviewOutlines () {}
void F4lmApp::slotviewFast () {}
void F4lmApp::slotviewAntialias () {}
void F4lmApp::slotviewAntialiasText () {}
void F4lmApp::slotviewTimeline () {}
void F4lmApp::slotviewWorkArea () {}
void F4lmApp::slotviewRulers () {}
void F4lmApp::slotviewShowGrid () {}
void F4lmApp::slotviewSnaptoGrid () {}
void F4lmApp::slotviewEditGrid () {}
void F4lmApp::slotviewShowGuides () {}
void F4lmApp::slotviewLockGuides () {}
void F4lmApp::slotviewSnaptoGuides () {}
void F4lmApp::slotviewEditGuides () {}
void F4lmApp::slotviewSnaptoPixels () {}
void F4lmApp::slotviewSnaptoObjects () {}
void F4lmApp::slotviewShowShapeHints () {}
void F4lmApp::slotviewHideEdges () {}
void F4lmApp::slotviewHidePanels () {}
void F4lmApp::slotviewToolBar () {}
void F4lmApp::slotviewStatusBar () {}
void F4lmApp::slotinsertConverttoSymbol () {}
void F4lmApp::slotinsertNewSymbol () {}
void F4lmApp::slotinsertLayer () {}
void F4lmApp::slotinsertLayerFolder () {}
void F4lmApp::slotinsertMotionGuide () {}
void F4lmApp::slotinsertFrame ()
{
  tl->slotInsertFrame (tl->timeLineTable->currentRow (),
                       tl->timeLineTable->currentColumn ());
}

void F4lmApp::slotinsertRemoveFrames () {}
void F4lmApp::slotinsertKeyframe () {}
void F4lmApp::slotinsertBlankKeyframe () {}
void F4lmApp::slotinsertClearKeyframe () {}
void F4lmApp::slotinsertCreateMotionTween ()
{
  ///TODO:set frame as motionTween true.
}
void F4lmApp::slotinsertScene () {}
void F4lmApp::slotinsertRemoveScene () {}
void F4lmApp::slotmodifyLayer () {}
void F4lmApp::slotmodifyScene () {}
void F4lmApp::slotmodifyDocument () {}
void F4lmApp::slotmodifySmooth () {}
void F4lmApp::slotmodifyStraighten () {}
void F4lmApp::slotmodifyOptimize () {}
void F4lmApp::slotmodifyConvertLinestoFills () {}
void F4lmApp::slotmodifyExpandFill () {}
void F4lmApp::slotmodifySoftenFillEdges () {}
void F4lmApp::slotmodifyAddShapeHint () {}
void F4lmApp::slotmodifyRemoveAllHints () {}
void F4lmApp::slotmodifySwapSymbol () {}
void F4lmApp::slotmodifyDuplicateSymbol () {}
void F4lmApp::slotmodifySwapBitmap () {}
void F4lmApp::slotmodifyTraceBitmap () {}
void F4lmApp::slotmodifyFreeTransform () {}
void F4lmApp::slotmodifyDistort () {}
void F4lmApp::slotmodifyEnvelope () {}
void F4lmApp::slotmodifyScale () {}
void F4lmApp::slotmodifyRotateandSkew () {}
void F4lmApp::slotmodifyScaleandRotate () {}
void F4lmApp::slotmodifyRotate90CW () {}
void F4lmApp::slotmodifyRotate90CCW () {}
void F4lmApp::slotmodifyFlipVertical () {}
void F4lmApp::slotmodifyFlipHorizontal () {}
void F4lmApp::slotmodifyRemoveTransform () {}
void F4lmApp::slotmodifyBringtoFront () {}
void F4lmApp::slotmodifyBringForward () {}
void F4lmApp::slotmodifySendBackward () {}
void F4lmApp::slotmodifySendtoBack () {}
void F4lmApp::slotmodifyLock () {}
void F4lmApp::slotmodifyUnlockAll () {}
void F4lmApp::slotmodifyReverse () {}
void F4lmApp::slotmodifySynchronizeSymbols () {}
void F4lmApp::slotmodifyConverttoKeyframes () {}
void F4lmApp::slotmodifyConverttoBlankKeyframes () {}
void F4lmApp::slotmodifyGroup () {}
void F4lmApp::slotmodifyUngroup () {}
void F4lmApp::slotmodifyBreakApart () {}
void F4lmApp::slotmodifyDistributetoLayers () {}
void F4lmApp::slottextFontFace () {}
void F4lmApp::slottext8 ()
{
  properties->fontProperties->size = "8";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext9 ()
{
  properties->fontProperties->size = "9";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext10 ()
{
  properties->fontProperties->size = "10";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext11 ()
{
  properties->fontProperties->size = "11";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext12 ()
{
  properties->fontProperties->size = "12";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext14 ()
{
  properties->fontProperties->size = "14";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext18 ()
{
  properties->fontProperties->size = "18";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext24 ()
{
  properties->fontProperties->size = "24";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext36 ()
{
  properties->fontProperties->size = "36";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext48 ()
{
  properties->fontProperties->size = "48";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext72 ()
{
  properties->fontProperties->size = "72";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext96 ()
{
  properties->fontProperties->size = "96";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottext120 ()
{
  properties->fontProperties->size = "120";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottextPlain ()
{
  properties->fontProperties->style = "Normal";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottextBold ()
{
  properties->fontProperties->style = "Bold";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottextItalic ()
{
  properties->fontProperties->style = "Italic";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottextSubscript ()
{
  properties->fontProperties->style = "Underline";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottextSuperscript ()
{
  properties->fontProperties->style = "Strikeout";
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottextAlignLeft () {}
void F4lmApp::slottextAlignCenter () {}
void F4lmApp::slottextAlignRight () {}
void F4lmApp::slottextJustify () {}
void F4lmApp::slottextIncrease ()
{
  int i = properties->fontProperties->size.toInt () + 1;
  QString s = QString::number (i);

  properties->fontProperties->size = s;
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottextDecrease ()
{
  int i = properties->fontProperties->size.toInt () - 1;
  QString s = QString::number (i);

  properties->fontProperties->size = s;
  properties->fontProperties->updateCanvasFont ();
}

void F4lmApp::slottextReset () {}
void F4lmApp::slottextScrollable () {}

///////control menu
void F4lmApp::slotcontrolPlay ()
{
  for(int i=0;i<tl->layerMaxColNum;i++)
  {
  }
}
void F4lmApp::slotcontrolRewind () {}
void F4lmApp::slotcontrolGoToEnd () {}
void F4lmApp::slotcontrolStepForward () {}
void F4lmApp::slotcontrolStepBackward () {}
void F4lmApp::slotcontrolTestMovie () {}
void F4lmApp::slotcontrolDebugMovie () {}
void F4lmApp::slotcontrolTestScene () {}
void F4lmApp::slotcontrolLoopPlayback () {}
void F4lmApp::slotcontrolPlayAllScenes () {}
void F4lmApp::slotcontrolEnableSimpleFrameActions () {}
void F4lmApp::slotcontrolEnableSimpleButtons () {}
void F4lmApp::slotcontrolMuteSounds () {}
void F4lmApp::slotcontrolEnableLivePreview () {}

//window menu

void F4lmApp::slotwindowTile () {}
void F4lmApp::slotwindowCascade () {}
void F4lmApp::slotwindowMain () {}
void F4lmApp::slotwindowStatus () {}
void F4lmApp::slotwindowController () {}
void F4lmApp::slotwindowAnswers () {}
void F4lmApp::slotwindowAlign () {}
void F4lmApp::slotwindowColorMixer () {}
void F4lmApp::slotwindowColorSwatches () {}
void F4lmApp::slotwindowInfo () {}
void F4lmApp::slotwindowScene () {}
void F4lmApp::slotwindowTransform () {}
void F4lmApp::slotwindowActions () {}
void F4lmApp::slotwindowDebugger () {}
void F4lmApp::slotwindowMovieExplorer () {}
void F4lmApp::slotwindowReference () {}
void F4lmApp::slotwindowOutput () {}
void F4lmApp::slotwindowAccessibility () {}
void F4lmApp::slotwindowComponents () {}
void F4lmApp::slotwindowComponentParameters () {}
void F4lmApp::slotwindowLibrary () {}
void F4lmApp::slotwindowlibraries () {}
void F4lmApp::slotwindowPanelSets () {}
void F4lmApp::slotwindowSavePanelLayout () {}
void F4lmApp::slotwindowCloseAllPanels () {}

//////////help menu
void F4lmApp::slothelpUsingF4l () {}
void F4lmApp::slothelpActionScriptDictionary () {}
void F4lmApp::slothelpF4lExchange () {}
void F4lmApp::slothelpManageExtensions () {}
void F4lmApp::slothelpSamples () {}
void F4lmApp::slothelpF4lSupportCenter () {}

void F4lmApp::slothelpRegisterF4l ()
{
  QMessageBox::about (this, tr ("Regsiter..."),
                      tr ("I will happy if u send me that u compiled f4l and tried it out."
                          "\nozkanpakdil@users.sourceforge.net"));
}

void F4lmApp::slotfileOpenAsLibrary () {}
void F4lmApp::slotfileSaveAsTemplate () {}
void F4lmApp::slotfileRevert () {}
void F4lmApp::slotfileImport ()
{

  CFilePreview * p = new CFilePreview;
  Q3FileDialog * fd = new Q3FileDialog (this);

  fd->setContentsPreviewEnabled (TRUE);
  fd->setContentsPreview (p, p);
  fd->setPreviewMode (Q3FileDialog::Contents);

  QString fileName1;

  if (fd->exec () == QDialog::Accepted)
    fileName1 = fd->selectedFile ();

  //QString choosen = fd->selectedFile();

  //qDebug(fileName1);
  Q3CanvasSprite * s1 =
    new Q3CanvasSprite (new Q3CanvasPixmapArray ((const QString) fileName1),
                       slotCurrentView ()->canvasViewer->canvas ());

  s1->moveBy (slotCurrentView ()->canvasViewer->canvas ()->width () / 2,
              slotCurrentView ()->canvasViewer->canvas ()->height () / 2);
  s1->show ();
}

void F4lmApp::slotfileImportToLibrary () {}
void F4lmApp::slotfileExportMovie ()
{
  /// @todo selected should be exported not first change line below.
  pDocList.first()->slotfileExportMovie();
}
void F4lmApp::slotfileExportImage () {}
void F4lmApp::slotfilePublishSetting () {}
void F4lmApp::slotfilePublishPreview_Default () {}
void F4lmApp::slotfilePublishPreview_Flash () {}
void F4lmApp::slotfilePublishPreview_Html () {}
void F4lmApp::slotfilePublishPreview_GIF () {}
void F4lmApp::slotfilePublishPreview_JPEG () {}
void F4lmApp::slotfilePublishPreview_PNG () {}
void F4lmApp::slotfilePublishPreview_Projector () {}
void F4lmApp::slotfilePublishPreview_Quicktime () {}
void F4lmApp::slotfilePublish () {}
void F4lmApp::slotfilePageSetup () {}
void F4lmApp::slotfilePrintPreview () {}
void F4lmApp::slotfileSend () {}
void F4lmApp::slotfileRecentFile () {}
void F4lmApp::sloteditRedo () {}
void F4lmApp::sloteditPasteinPlace () {}
void F4lmApp::sloteditPasteSpecial () {}
void F4lmApp::sloteditClear () {}
void F4lmApp::sloteditDuplicate () {}
void F4lmApp::sloteditSelectAll () {}
void F4lmApp::sloteditDeselectAll () {}
void F4lmApp::sloteditCutFrames () {}
void F4lmApp::sloteditCopyFrames () {}
void F4lmApp::sloteditPasteFrames () {}
void F4lmApp::sloteditClearFrames () {}
void F4lmApp::sloteditSelectAllFrames () {}
void F4lmApp::sloteditEditSymbols () {}
void F4lmApp::sloteditEditSelected () {}
void F4lmApp::sloteditEditInPlace () {}
void F4lmApp::sloteditEditAll () {}
void F4lmApp::sloteditPrefences () {}
void F4lmApp::sloteditKeyboardShourtCuts () {}
void F4lmApp::sloteditFontMapping () {}

/*void F4lmApp::mouseMoveEvent(QMouseEvent *e){
	QWidget::mouseMoveEvent(e);
 
	int x=mapToGlobal(e->pos()).x()
		,y=mapToGlobal(e->pos()).y();
    QPixmap p = QPixmap::grabWindow( QApplication::desktop()->winId(),  x, y, 2, 2 );
    QImage image = p.convertToImage();
 
 
	grabMouse();
	QPoint p=e->globalPos();
     QWidget *desktop = QApplication::desktop();
     QPixmap pm = QPixmap::grabWindow( desktop->winId(), p.x(), p.y(), 1, 1);
     QImage i = pm.convertToImage();
      i.pixel(0,0);
	QRgb px = i.pixel(0,0);
	qDebug(" %3d,%3d,%3d  #%02x%02x%02x",
		qRed(px), qGreen(px), qBlue(px),
		qRed(px), qGreen(px), qBlue(px));
 
}
 
void F4lmApp::mousePressEvent(QMouseEvent* e){
	//releaseMouse();
	//grabMouse();
}*/

void CFilePreview::previewUrl (const Q3Url & u)
{
  QString path = u.path ();
  QPixmap pix (path);
  if (pix.isNull ())
    setText ("This is not a image");
  else
  {
    pix.resize (width (), height ());
    setPixmap (pix);
  }
}
