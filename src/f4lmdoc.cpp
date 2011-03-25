/***************************************************************************
              f4lmdoc.cpp  -  description
                 -------------------
    begin                : Sat Jun  7 02:29:46 EEST 2003
    copyright            : (C) 2003 by �kan pakdil
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

// include files for Qt
#include <qdir.h>
#include <qfileinfo.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfiledialog.h>
#include <iostream.h>
#include <qfiledialog.h>
#include <qprocess.h> // reading ttf files
#include <qimage.h>
#include <qbuffer.h>

// application specific includes
#include "f4lmdoc.h"
#include "f4lm.h"
#include "f4lmview.h"

#include "transform/transform.h"
#include "transform-util/transformutil.h"
#include <string>


using namespace transform;
using namespace std;

F4lmDoc::F4lmDoc ()
{
  setName ("F4lmDoc");
  pViewList = new QList < F4lmView >;
  pLayerList = new QPtrList < CLayer >;
  pViewList->setAutoDelete (false);
}

F4lmDoc::~F4lmDoc ()
{
  delete pViewList;
}

void F4lmDoc::addView (F4lmView * view)
{
  pViewList->append (view);
  changedViewList ();
}

void F4lmDoc::removeView (F4lmView * view)
{
  pViewList->remove
  (view);
  if (!pViewList->isEmpty ())
    changedViewList ();
  else
    deleteContents ();
}

void F4lmDoc::changedViewList ()
{
  F4lmView *w;
  if ((int) pViewList->count () == 1)
  {
    w = pViewList->first ();
    w->setCaption (m_title);
  }
  else
  {
    int i;
    for (i = 1, w = pViewList->first (); w != 0;
         i++, w = pViewList->next ())
      w->setCaption (QString (m_title + ":%1").arg (i));
  }
}

bool F4lmDoc::isLastView ()
{
  return ((int) pViewList->count () == 1);
}

void F4lmDoc::updateAllViews (F4lmView * sender)
{
  F4lmView *w;
  for (w = pViewList->first (); w != 0; w = pViewList->next ())
  {
    w->update (sender);
  }
}

void F4lmDoc::setPathName (const QString & name)
{
  m_filename = name;
  m_title = QFileInfo (name).fileName ();
}

const QString & F4lmDoc::pathName () const
{
  return m_filename;
}

void F4lmDoc::setTitle (const QString & title)
{
  m_title = title;
}

const QString & F4lmDoc::title () const
{
  return m_title;
}

void F4lmDoc::closeDocument ()
{
  F4lmView *w;
  if (!isLastView ())
  {
    for (w = pViewList->first (); w != 0; w = pViewList->next ())
    {
      if (!w->close ())
        break;
    }
  }
  if (isLastView ())
  {
    w = pViewList->first ();
    w->close ();
  }
}

bool F4lmDoc::newDocument ()
{
  /////////////////////////////////////////////////
  // TODO: Add your document initialization code here
  /////////////////////////////////////////////////
  modified = false;
  return true;
}

bool F4lmDoc::openDocument (const QString & filename, const char *format /*=0*/ )
{
  QFile f (filename);
  if (!f.open (IO_ReadOnly))
    return false;
  /////////////////////////////////////////////////
  // TODO: Add your document opening code here
  /////////////////////////////////////////////////
  f.close ();
  modified = false;
  m_filename = filename;
  m_title = QFileInfo (f).fileName ();
  return true;
}

bool F4lmDoc::saveDocument (const QString & filename, const char *format /*=0*/ )
{
  F4lmView* tmp= (F4lmView* )pViewList->at(0);
  canview *viving=tmp->canvasViewer;
  QCanvasItemList canvItmList;


  /*QCanvasItemList l = canvas ()->allItems ();
  			for (QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it) {
  					if ((*it)->rtti () == 667) {
     (*it)->hide ();
     delete *it;
  					}
  					mulSelect.clear ();
  					mulSelectedRects.clear ();
  			}*/

  QFile f (filename);
  if (!f.open (IO_WriteOnly))
    return false;

  /////////////////////////////////////////////////
  // TODO: Add your document saving code here
  /////////////////////////////////////////////////

  f.close ();

  modified = false;
  m_filename = filename;
  m_title = QFileInfo (f).fileName ();
  return true;
}

void F4lmDoc::deleteContents ()
{
  /////////////////////////////////////////////////
  // TODO: Add implementation to delete the document contents
  /////////////////////////////////////////////////

}

bool F4lmDoc::canCloseFrame (F4lmView * pFrame)
{
  if (!isLastView ())
    return true;

  bool ret = false;
  if (isModified ())
  {
    QString saveName;
    switch (QMessageBox::
            information (pFrame, title (),
                         tr ("The current file has been modified.\n"
                             "Do you want to save it?"), QMessageBox::Yes,
                         QMessageBox::No, QMessageBox::Cancel))
    {
    case QMessageBox::Yes:
      if (title ().contains (tr ("Untitled")))
      {
        saveName = QFileDialog::getSaveFileName (0, 0, pFrame);
        if (saveName.isEmpty ())
          return false;
      }
      else
        saveName = pathName ();

      if (!saveDocument (saveName))
      {
        switch (QMessageBox::
                critical (pFrame, tr ("I/O Error !"),
                          tr ("Could not save the current document !\n"
                              "Close anyway ?"), QMessageBox::Yes,
                          QMessageBox::No))
        {
        case QMessageBox::Yes:
          ret = true;
        case QMessageBox::No:
          ret = false;
        }
      }
      else
        ret = true;
      break;
    case QMessageBox::No:
      ret = true;
      break;
    case QMessageBox::Cancel:
    default:
      ret = false;
      break;
    }
  }
  else
    ret = true;

  return ret;
}


/*!
    \fn F4lmDoc::slotfileExportMovie()
 */
void F4lmDoc::slotfileExportMovie()
{
  F4lmView *view=pViewList->first();
  CListViewItem *tmpListViewItem=(CListViewItem*)view->dad->tl->timeLineListbox->selectedItem();
  int animX=view->dad->tl->layerFrames->at(tmpListViewItem->m_Row-1)->frames->last ()->tableItemNo;
  int z=-1*tmpListViewItem->m_Row;



  int xLower = 000;
  int yLower = 000;
  int xUpper = view->defSceneRect.x()*2+600;
  int yUpper = view->defSceneRect.y()*2+600;

  FSMovie movie;
  movie.setFrameSize(FSBounds(xLower, yLower, xUpper, yUpper));
  /*
  * Set the frame rate at which the movie will be played.
  */
  float framesPerSecond = 25.0f;

  movie.setFrameRate(framesPerSecond);
  /*
  * Set the movie's background colour to light blue. The background colour
  * only be set once and should be the first object added to a movie. If no
  * background colour is specified then the Flash Player will set it to white.
  */
  /// TODO:defscenerect should be color here.
  movie.add(new FSSetBackgroundColor(FSColorTable::white()));


  for(int i=0;i<=view->dad->tl->layerMaxColNum;i++)
  {
    QCanvasItemList l=view->mainCanvas->allItems();
    for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();++it)
    {
      if ((*it)->rtti () == 666 || (*it)->rtti () == 667)
      {		//should not be output object types.
        continue;
      }
      switch((*it)->rtti())
      {
      case QCanvasItem::Rtti_Ellipse:
        {
          CCanvasEllipse *oval=(CCanvasEllipse*)(*it);
          if(oval->animationX>=i)continue;
          FSShapeConstructor* path = ShapeConstructor(); //buundan circle cikar
          //path->COORDINATES_ARE_PIXELS = true;
          int width = oval->width();
          int height = oval->height();
          int identifier = movie.newIdentifier();

          QColor PenColor=oval->pen().color();
          QColor BrushColor=oval->brush().color();
          FSSolidLine* lineStyle = new FSSolidLine(1,  FSColor(PenColor.red(),PenColor.green(),PenColor.blue()));
          FSSolidFill* fillStyle =new FSSolidFill(FSColor(BrushColor.red(),BrushColor.green(),BrushColor.blue()));
          path->addLineStyle(lineStyle);
          path->addFillStyle(fillStyle);

          //delete lineStyle;
          //delete fillStyle;
          //path->newPath();                   // start a new path
          //path->selectStyle(1, 1);       // select the first line and fill style objects
          //path->move(-width/2, -height/2);
          //path->closePath();
          path->ellipse(-width/2, -height/2, width/2, height/2);
          movie.add(path->defineShape(identifier));
          movie.add(new FSPlaceObject(identifier, oval->Row, oval->x(), oval->y()));

          movie.add(new FSShowFrame());
        }
        break;
      case QCanvasItem::Rtti_Line:
        {
          CCanvasLine *line=(CCanvasLine*)(*it);
          //qDebug("frame %d",i);
          if(line->animationX>=i)continue;

          int identifier = movie.newIdentifier();

          int width = (line->startPoint().x()-line->endPoint().x());
          int height = (line->startPoint().y()-line->endPoint().y());
          //qDebug("startX: %d height: %d",line->startPoint().x(),line->endPoint().x());
          FSBounds bounds(-width, -height, width, height);
          //qDebug("width: %d height: %d",width,height);
          FSVector<FSLineStyle*> lineStyles(1);
          FSVector<FSFillStyle*> fillStyles(1);

          QColor PenColor=line->pen().color();
          QColor BrushColor=line->brush().color();
          //qDebug("renk ismi %d %d %d",BrushColor.red(),BrushColor.green(),BrushColor.blue());
          lineStyles[0] = new FSSolidLine(1, FSColor(PenColor.red(),PenColor.green(),PenColor.blue()));
          fillStyles[0] = new FSSolidFill( FSColor(BrushColor.red(),BrushColor.green(),BrushColor.blue()));

          FSShape shape;
          shape.add(new FSShapeStyle(1, 1, 0,-width/2,-height/2));
          //shape.add(new FSShapeStyle(line->startPoint().x(), line->startPoint().y()));
          //shape.add(new FSLine(line->startPoint().x(),line->startPoint().y()));
          //shape.add(new FSLine(line->endPoint().x(),line->endPoint().y()));
          shape.add(new FSLine(-width, -height));
          shape.add(new FSLine(width, height));
          /*shape.add(new FSLine(-width, 0));
          shape.add(new FSLine(0, -height));*/
          FSDefineShape* Line = new FSDefineShape(identifier, bounds, fillStyles, lineStyles, shape);

          movie.add(Line);

          movie.add(new FSPlaceObject(identifier, line->Row, line->startPoint().x(), line->startPoint().y()));

          movie.add(new FSShowFrame());
        }
        break;
      case QCanvasItem::Rtti_Polygon:

        break;
      case QCanvasItem::Rtti_PolygonalItem:
        {
          CPencilLine *poly=(CPencilLine*)(*it);
        }

        break;
      case QCanvasItem::Rtti_Rectangle:
        {
          CCanvasRectangle *rect=(CCanvasRectangle*)(*it);
          //qDebug("rect animx : %d colon numaramiz: %d",rect->animationX,i);
          if(rect->animationX>=i)continue;

          int identifier = movie.newIdentifier();

          int width = rect->width();
          int height =rect->height();

          FSBounds bounds(-width,-height, width, height);

          FSVector<FSLineStyle*> lineStyles(1);
          FSVector<FSFillStyle*> fillStyles(1);

          QColor PenColor=rect->pen().color();
          QColor BrushColor=rect->brush().color();
          lineStyles[0] = new FSSolidLine(1, FSColor(PenColor.red(),PenColor.green(),PenColor.blue()));
          fillStyles[0] = new FSSolidFill( FSColor(BrushColor.red(),BrushColor.green(),BrushColor.blue()));
          /*
          * Create the outline of the shape. All drawing is performed using a series
          * of line an curve objects. The FSShapeStyle class is used to select the 
          * current line and fill styles and to perform absolute moves within the 
          * coordinate space of the shape (relative moves can be performed by drawing
          * line when no line style is selected - set the line style to 0).
          */

          FSShape shape;

          shape.add(new FSShapeStyle(0, 1, 0,-width/2,-height/2));
          //qDebug("width %d height %d baslangicX:%d baslangicY:%d",width,height,rect->rect().x() - view->defSceneWidth,rect->rect().y()-view->defSceneHeight);
          //shape.add(new FSShapeStyle(0,0));
          shape.add(new FSLine(width, 0));
          shape.add(new FSLine(0, height));
          shape.add(new FSLine(-width, 0));
          shape.add(new FSLine(0, -height));

          /*shape.add(new FSShapeStyle(1, 1, 0,-50,-50));
          shape.add(new FSLine(100,0));
          shape.add(new FSLine(0,100));
          shape.add(new FSLine(-100,0));
          shape.add(new FSLine(0,-100));*/

          FSDefineShape* rectangle = new FSDefineShape(identifier, bounds, fillStyles, lineStyles, shape);

          /*
          * Add the rectangle to the movie. All shapes and objects must be defined before
          * they can be placed on the display list and rendered on the Flash Player's
          * screen.
          */
          movie.add(rectangle);

          /*
          * for layers and object place.
          */
          movie.add(new FSPlaceObject(identifier, rect->Row, rect->rect().x(), rect->rect().y()));

          /*
          * Show the contents of the display list. Frames are delimited by successive
          * FSShowFrame objects.
          */
          movie.add(new FSShowFrame());
        }
        break;
      case QCanvasItem::Rtti_Spline:
        break;
      case QCanvasItem::Rtti_Sprite:
        {
          QCanvasSprite *sprite=(QCanvasSprite*)(*it);
          QByteArray ba;
          QBuffer buffer( ba );
          buffer.open( IO_WriteOnly );
sprite->image()->convertToImage().save( &buffer, "BMP" ); // writes image into ba in BMP format
          FSImageConstructor* imageGenerator = ImageConstructor();
          int status = TransformUtil::OK;
int boyutu=ba.size();
qDebug("%d",boyutu);
          //if ((status = imageGenerator->setImageFromFile(imageFile.c_str())) != TransformUtil::OK)(  const unsigned char *)
          //if ((status = imageGenerator->setImage(sprite->image()->convertToImage ().bits(),sizeof(sprite->image()->convertToImage ().bits()))) != TransformUtil::OK)
if ((status = imageGenerator->setImage((const unsigned char*)buffer.buffer().data(),sizeof(char)*boyutu)) != TransformUtil::OK)
          {
            switch (status)
            {
            case TransformUtil::FileNotFound:
              cout << "Could not find image" << endl; break;
            case TransformUtil::ReadError:
              cout << "Could not read image" << endl; break;
            case TransformUtil::FormatError:
              cout << "Could not read image" << endl; break;
            }
          }
          if (status == TransformUtil::OK)
          {
            /*
            * Create the FSImageConstructor object used to generate the object
            * containing the image definition. Initialize it using the name of 
            * the image file passed on the command line when the example was run.
            */

            int imageId = movie.newIdentifier();
            int shapeId = movie.newIdentifier();

            int xOrigin = imageGenerator->getWidth()/2;
            int yOrigin = imageGenerator->getHeight()/2;

            FSDefineObject* image = imageGenerator->defineImage(imageId);

            /*
            * All images must be displayed as a bitmap fill inside a shape. The 
            * FSImageConstructor class generates the shape enclosing the image.
            * If no border is required then the line style may be set to null.
            */
            int borderWidth = 20;
            FSColor black = FSColorTable::black();

            FSDefineShape3* shape = imageGenerator->defineShape(shapeId, imageId,
                                    -xOrigin, -yOrigin, borderWidth, &black);

            /*
            * Add all the objects together to create the movie.
            */
            movie.setFrameRate(1.0f);
            movie.setFrameSize(shape->getBounds());
            movie.add(image);
            movie.add(shape);
            movie.add(new FSPlaceObject2(shapeId, 1, 0, 0));
            movie.add(new FSShowFrame());

          }

        }
        break;
      case QCanvasItem::Rtti_Text:
        {
          CCanvasText *canvasText=(CCanvasText*)(*it);
          if(canvasText->animationX>=i)continue;
          FSTextConstructor* textGenerator = TextConstructor();
          int status = TransformUtil::OK;
          proc = new QProcess();
          proc->addArgument( "locate");
          proc->addArgument("*.ttf");
          QString buf;
          //proc->launch(buf);
          connect( proc, SIGNAL(readyReadStdout()),
                   this, SLOT(readFromStdout()) );

          if ( !proc->start() )
          {
            // error handling
            qDebug("process could not started.");
            return;
          }
          while(proc->isRunning()==TRUE){qApp->processEvents(5000);}
          /*QByteArray bufByte=proc->readStdout();
          if(!proc->normalExit())
          	qDebug("%d",proc->exitStatus ());
          QString sttir(bufByte);
          QStringList sittirList;*/
          QString ttfFileName="";
          qDebug(canvasText->font().family().stripWhiteSpace ());
          procOut = procOut.split("\n",procOut.join("\n"));
          qDebug("%d",procOut.count());
          for(int ttfIndis=0;ttfIndis<procOut.count();ttfIndis++)
          {
            if(procOut[ttfIndis].right(4)==".ttf")
            {
              //qDebug(procOut[ttfIndis]);
              if(procOut[ttfIndis].contains(canvasText->font().family().stripWhiteSpace (),false))
              {
                //qDebug("burasi ana yer");
                ttfFileName=procOut[ttfIndis];
                break;
              }
            }
            //qDebug("%d",ttfIndis);
            //qDebug(procOut[ttfIndis]);
          }
          if(ttfFileName=="")
          {
            qDebug("we could not find ttf file.");
            //TODO: for default font make an options dialog.
            qDebug("Default Font Selected.");
            for(int ttfIndis=0;ttfIndis<procOut.count();ttfIndis++)
            {
              if(procOut[ttfIndis].right(4)==".ttf")
              {
                //qDebug(procOut[ttfIndis]);
                //TODO:when you done option dialog for default font change the "arial" from down line.
                if(procOut[ttfIndis].contains("arial",false))
                {
                  ttfFileName=procOut[ttfIndis];
                  break;
                }
              }
            }
          }
          qDebug(ttfFileName);

          if ((status = textGenerator->setFontFromFile(ttfFileName)) != TransformUtil::OK)
          {
            switch (status)
            {
            case TransformUtil::FileNotFound:
              cout << "Could not find font file" << endl; break;
            case TransformUtil::ReadError:
              cout << "Could not read font file" << endl; break;
            case TransformUtil::FormatError:
              cout << "Could not read font file" << endl; break;
            }
          }
          int layer = 0;                // Starting layer for objects in the display list.
          int fontSize = canvasText->boundingRect().height(); // 280;           // Font size in twips 1 point = 20 twips
          int lineSpacing = fontSize;   // The font size defines a suitable line spacing

          /*
          * The movie will be sized to match the block of text generated.
          * The margins are defined so the text is displayed without touching
          * the edge of the Flash Player screen.
          */
          int leftMargin = fontSize;
          int rightMargin = fontSize;
          int topMargin = fontSize;
          int bottomMargin = fontSize;

          FSColor textColor(canvasText->color().red(),canvasText->color().green(),canvasText->color().blue());

          textGenerator->setIdentifier(movie.newIdentifier());
          textGenerator->setSize(fontSize);
          textGenerator->setColor(&textColor);

          /*
          * The block of text is generated before the font definition. This ensures
          * that only the characters displayed will be included in the font. Unused
          * characters will be omitted, greatly reducing the size of the Flash file
          * generated. Once the FSDefineFont2 object has been generated any text 
          * objects created with characters not previously used, will not be 
          * displayed correctly - a new font definition would need to be generated
          * to include the new characters.
          * 
          * The FSDefineText2 object contains an array of FSText objects, each
          * specifying an offset relative to the origin of the entire block. These
          * can easily be changed if a line needs to be indented or the line spacing
          * adjusted. 
          */
          //FSDefineText2* text = textGenerator->defineWideTextBlock(movie.newIdentifier(),
          //	(const wchar_t **)lines, 32, lineSpacing);
          FSDefineText2* text = textGenerator->defineText(movie.newIdentifier(),canvasText->text());

          FSDefineFont2* font = textGenerator->defineFont();

          /*
          * Define the size of the Flash Player screen using the bounding 
          * rectangle defined for the block of text plus a suitable margin so 
          * the text does not touch the edge of the screen.
          */
          int screenWidth = text->getBounds().getWidth() + leftMargin + rightMargin;
          int screenHeight = text->getBounds().getHeight() + topMargin + bottomMargin;

          movie.add(font);
          movie.add(text);
          movie.add(new FSPlaceObject2(text->getIdentifier(), canvasText->Row, canvasText->boundingRect ().x() , canvasText->boundingRect ().y()));
          movie.add(new FSShowFrame());

        }
        break;
      }
    }
  }
  try
  {
    QString fileName = QFileDialog::getSaveFileName( );
    movie.encodeToFile(fileName);

  }
  catch (FSException e)
  {
    /*
     * Several exceptions could be thrown to get to this point. FSMovie will 
     * throw an FSFileOpenException, FSAccessException or FSFormatException 
     * if the file cannot be opened for writing, an error occurs while writing
     * to the file or if an error occurs while encoding the Flash data, respectively.
     * 
     * All the exceptions thrown contain a message which describes why the
     * exception was thrown so handling them all in the same way is sufficient
     * for the purposes of the examples.
     */
    cerr << e.what();
  }
}


void F4lmDoc::readFromStdout()
{
  // Read and process the data.
  // Bear in mind that the data might be output in chunks.
  procOut.append( proc->readStdout() );
  //qDebug(procOut.last());
}
