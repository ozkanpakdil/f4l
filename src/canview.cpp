/***************************************************************************
              canview.cpp  -  description
                 -------------------
    begin                : Thu May 15 2003
    copyright            : (C) 2003 by root
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

#include "canview.h"
#include "f4lmview.h"
#include "f4lm.h"
#include "cpencilline.h"
#include "canvasItem.h"
#include "ctexteditfortexttool.h"
#include "cbrushtool.h"
#include "timeline.h"
#include "clistboxitem.h"
#include "ccanvasline.h"
#include "ccanvastext.h"
#include "ccanvasellipse.h"
#include "ccanvasrectangle.h"

#include <stdlib.h>
#include <qimage.h>
#include <qwmatrix.h>
#include <qbitmap.h>
#include <qpainter.h>
#include <qpopupmenu.h>

#include "cursor/hand_cursor.xpm"
#include "cursor/hand_cursor_down.xpm"
#include "cursor/arrow_tool.xpm"
#include "cursor/pencil_tool.xpm"
#include "cursor/paint_bucket.xpm"
#include "cursor/ink_bottle.xpm"
#include "cursor/pen_tool.xpm"

#include "cursor/lasso_tool.xpm"
#include "cursor/text_tool.xpm"
#include "cursor/subselection_tool.xpm"
#include "cursor/zoomin.xpm"
#include "cursor/zoomout.xpm"
#include "cursor/eye_dropper_tool.xpm"
#include "cursor/brush_tool.xpm"
#include "cursor/eraser_tool.xpm"

canview::canview (QCanvas * canvas, QWidget * parent, const char *name)
    :QCanvasView (canvas, parent, name)
{
  setFocus ();
  setFocusPolicy (QWidget::StrongFocus);
  dad = (F4lmView *) parent;
  z = 0;

  handCursor = QCursor (QPixmap ((const char **) hand_cursor));
  handCursorDown = QCursor (QPixmap ((const char **) hand_cursor_down));
  arrowToolCursor = QCursor (QPixmap ((const char **) arrow_tool_xpm), 0, 0);
  pencilCursor = QCursor (QPixmap ((const char **) pencil_tool_xpm), 2, 12);
  paintbucketCursor = QCursor (QPixmap ((const char **) paint_bucket), 2, 12);
  inkbottleCursor = QCursor (QPixmap ((const char **) ink_bottle), 2, 12);
  pentoolCursor = QCursor (QPixmap ((const char **) pen_tool_xpm), 2, 0);
  lassotoolCursor = QCursor (QPixmap ((const char **) lasso_tool_xpm), 3, 13);
  texttoolCursor = QCursor (QPixmap ((const char **) text_tool_xpm), 5, 5);
  subselectiontoolCursor =QCursor (QPixmap ((const char **) subselection_tool), 0, 0);
  zoominCursor = QCursor (QPixmap ((const char **) zoomin), 0, 0);
  zoomoutCursor = QCursor (QPixmap ((const char **) zoomout), 0, 0);
  eyedroppertool = QCursor ((const char **) eye_dropper_tool_xpm, 1, 15);
  brushCursor = QCursor ((const char **) brush_tool_xpm, 15, 23);
  eraserCursor = QCursor ((const char **) eraser_tool_xpm, 5, 5);
  selectionRect = NULL;
  selectedRect = NULL;
  penShape = NULL;
  spline = NULL;
  moving = 0;
  textBox = new CTextEditForTextTool (this, "textboxforEnteringText");
  textBox->hide ();
}

canview::~canview ()
{}

void canview::contentsMousePressEvent (QMouseEvent * e)
{
  butPos = true;

  if (e->button () == LeftButton)
  {
    cenX = e->x ();
    cenY = e->y ();
    //qDebug("tikX:%d tikY:%d",cenX,cenY);
    ///Z index(dimension taken from layers up left corner.)
    CListViewItem *tmpListViewItem=(CListViewItem*)dad->dad->tl->timeLineListbox->selectedItem();
    if(dad->dad->tl->timeLineListbox->selectedItem()!=NULL)
    {
      z=-1*tmpListViewItem->m_Row;
    }
    else
    {
      z=-1;
    }
    ///Animation X I mean frame number.
    //CTimeLineDataStructure* sikecemyaw=(CTimeLineDataStructure *)dad->dad->tl->layerFrames->at(tmpListViewItem->m_Row);
    //qDebug("%d",dad->dad->tl->layerFrames->at(0)->name);
    //qDebug("framelistesi countu: %d",dad->dad->tl->layerFrames->at(tmpListViewItem->m_Row)->name);
    int animX=dad->dad->tl->layerFrames->at(tmpListViewItem->m_Row-1)->frames->last ()->tableItemNo;//currentFrameLabel->kutuNo;
    //		qDebug("X: %d",animX);
    switch (dad->defObjID)
    {
    case 1:		//ArrowTool;
      {
        if (selectionRect == NULL)
        {
          QPoint p = inverseWorldMatrix ().map (e->pos ());
          QCanvasItemList l = canvas ()->collisions (p);
          //          qDebug("cou: %d",l.count());

          if (l.count () <= 1)
          {
            for (QCanvasItemList::Iterator mit =
                   mulSelectedRects.begin ();
                 mit != mulSelectedRects.end (); ++mit)
            {
              if (mit != NULL)
              {
                //(*mit)->hide ();      //delete *mit;
                //qDebug("selRTTI : %d",(*mit)->rtti());
              }
            }
            //qDebug("mulr: %d",mulSelectedRects.count());
            mulSelectedRects.clear ();
            mulSelect.clear ();
          }
          if (l.count () <= 1)
          {
            selectionRect = new CSceneRect (QRect (cenX, cenY, 0, 0), canvas ());
            selectionRect->setPen (Qt::black);
            selectionRect->setZ (z);
            selectionRect->show ();
          }
          for (QCanvasItemList::Iterator it = l.begin ();
               it != l.end (); ++it)
          {
            if ((*it)->rtti () == 666 || (*it)->rtti () == 667)
            {		//if user clicked on def. scene rect. then dont select it.
              continue;
            }
            moving = *it;
            /*if( selectedRect==NULL){///*moving->rtti() == QCanvasItem::Rtti_Text &&
            selectedRect=new CSceneRect(moving->boundingRect(),canvas());
            selectedRect->setPen(QColor(0,168,255));
            selectedRect->setZ(z);
            selectedRect->show();
            } */
            //mulSelectedRects.append(selectedRect);
            mulSelect.append (moving);
            moving_start = p;
            //return;
          }
          if (mulSelect.count () >= 1)
            mulSelect.pop_back ();
          //moving = 0;
        }
        break;
      }
    case 2:		//SubSelectionTool;
      break;
    case 3:		//LineTool;
      {
        line = new CCanvasLine (canvas ());
        line->Row=z;
        line->animationX=animX;
        //line->Row=dad->dad->tl->  //selectedItem()->itemPos();
        //qDebug("line row: %d",line->Row);
        line->setPen (dad->defObjCOLOR);
        line->setBrush (QBrush (dad->defObjCOLOR));
        line->setPoints (cenX, cenY, cenX, cenY);
        line->setZ (z);
        line->show ();
        break;
      }
    case 4:		//LassoTool;
      break;
    case 5:		//PenTool;
      {
        static int k = 0;

        if (penShape == NULL)
        {
          penShape = new CPenTool (canvas ());
          penShape->animationX=animX;
          QPen pen (dad->defObjCOLOR);
          pen.setWidth (3);
          penShape->setPen (pen);
          penShape->setBrush (dad->defObjCOLOR);
          penShape->setZ (z);
          penShape->show ();
          spolyline = QPointArray (12);
          //spolyline[0]=spolyline[1]=spolyline[2]=spolyline[3]=/*contentsToViewport*/(e->pos());
          for (int i = 0; i < 12; i++)
            spolyline[i] = e->pos ();
        }
        else
        {
          //    k++;

          spolyline[++k] = e->pos ();
        }
        penShape->setControlPoints (spolyline);
        if (k == 11)
        {
          k = 0;
          penShape = NULL;
        }

        if (spline == NULL)
        {
          /*spline=new QCanvasSpline(canvas());
             QPen pen(dad->defObjCOLOR);pen.setWidth(3);
             spline->setPen(pen);
             spline->setBrush(dad->defObjCOLOR);
             spline->setZ(z);
             spline->show();
             spolyline=QPointArray(4); */
          //spolyline[0]=spolyline[1]=spolyline[2]=spolyline[3]=/*contentsToViewport*/(e->pos());
        }
        else
        {
          //spolyline[++k]=/*contentsToViewport*/(e->pos());
        }
        //spline->setControlPoints (spolyline,false);
        //system("cls");
        //viewport()->update();
        QPainter p (viewport ());

        //QBrush br();
        //p.setBrush(br);
        //                                p.setPen(pen);
        //p.drawEllipse(contentsToViewport(spolyline[k]).x(),contentsToViewport(spolyline[k]).y(),10,10);
        //p.setPen(Qt::blue);
        //p.drawEllipse(spolyline[k].x(),spolyline[k].y(),10,10);
        //p.drawPoints(polyline);
        //p.drawCubicBezier(polyline);
        //if(k==3){k=0;spline=NULL;}
      }
      break;
    case 6:		//TextTool;
      {
        //textBox->show();
        textBox->setFont (textFont);
        textBox->setText ("");
        textBox->resize (20, 20);
        textBox->move (contentsToViewport (e->pos ()));
        textBox->setColor (dad->defObjCOLOR);
        textBox->show ();
        textBox->setFocus ();
        textBox->setSelection (0, 0, 0, 5);
        text = new CCanvasText ("hello world!", canvas ());
        text->animationX=animX;
        text->Row=z;
        text->setColor (dad->defObjCOLOR);
        text->setZ (z);
        text->move (cenX, cenY);
        text->setFont (textFont);
        //text->show();
      }
      break;
    case 7:		//OvalTool;
      {
        //QCanvas* p= QCanvasView::canvas();
        oval = new CCanvasEllipse (1, 1, canvas ());
        oval->animationX=animX;
        oval->Row=z;
        oval->setZ (z);
        oval->setBrush (QBrush (dad->defObjCOLOR));
        //oval->setX(100);
        //oval->setY(100);
        oval->show ();
        oval->setX (cenX);
        oval->setY (cenY);
        //  oval->setPen( QPen(QColor(rand()%32*8,rand()%32*8,rand()%32*8), 6) );
      }
      break;
    case 8:		//RectangleTool;
      {
        rect = new CCanvasRectangle (cenX, cenY, 1, 1, canvas ());
        rect->animationX=animX;
        rect->Row=z;
        rect->setBrush (dad->defObjCOLOR);
        rect->setZ (z);
        rect->show ();
        break;
      }
    case 9:		//PencilTool;
      {
        pPolylineTemp.clear ();

        QPoint *pt = new QPoint ((e->pos ()));
        pPolylineTemp.append (pt);
        pencilline = new CPencilLine (canvas ());
        pencilline->animationX=animX;
        pencilline->setPen (dad->defObjCOLOR);
        pencilline->Row=z;
        //pencilline->setBrush(dad->defObjCOLOR);
        pencilline->setZ (z);


        //                        for(int i=0;i<1000;i++)pencilline->polyline[i] = e->pos();/**/
        //pencilline->
        //pencilline->pPolylineTemp->append(&e->pos());
      }
      break;
    case 10:		//BrushTool;
      {
        pPolylineTemp.clear ();

        QPoint *pt = new QPoint ((e->pos ()));
        pPolylineTemp.append (pt);
        brushline = new CCanvasBrushLine (canvas ());
        brushline->animationX=animX;
        brushline->setPen (dad->defObjCOLOR);
        brushline->setZ (z);
      }
      break;
    case 11:		//FreeTransformTool;
      {
        QPoint p = inverseWorldMatrix ().map (e->pos ());
        QCanvasItemList l = canvas ()->collisions (p);
        for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();
             ++it)
        {
          if ((*it)->rtti () == 666)
          {		//if user clicked on def. scene rect. then dont select it.
            continue;
          }
          moving = *it;
        }
        if (moving)
        {
          //QPainter pnr(viewport());
          /*QRect r=moving->boundingRect();
             QCanvasRectangle *cr=new QCanvasRectangle(r,canvas());
             cr->setPen(Qt::black);
             cr->show(); */
          //pnr.drawRect(r);

        }

      }
      break;
    case 12:		//FillTransformTool;
      break;
    case 13:		//InkBottleTool;
      break;
    case 14:		//PaintBucketTool;
      {
        QPoint p = inverseWorldMatrix ().map (e->pos ());
        QCanvasItemList l = canvas ()->collisions (p);
        //qDebug("eleman sayisi %d",l.count());
        if(l.count()<=1) break;
        for (QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it)
        {
          if(it==NULL) break;
          if ((*it)->rtti () == 666)
          {		//if user clicked on def. scene rect. then dont select it.
            continue;
          }
          moving = *it;
          //qDebug( "bu objeye tikladin %d ",moving->rtti() );
        }
        if (moving)
          if (moving->rtti () == QCanvasItem::Rtti_Ellipse ||
              moving->rtti () == QCanvasItem::Rtti_Line ||
              moving->rtti () == QCanvasItem::Rtti_Polygon ||
              moving->rtti () == QCanvasItem::Rtti_PolygonalItem ||
              moving->rtti () == QCanvasItem::Rtti_Rectangle ||
              moving->rtti () == QCanvasItem::Rtti_Spline)
          {
            ((QCanvasPolygonalItem *) moving)->setPen (dad->defObjCOLOR);
            ((QCanvasPolygonalItem *) moving)->setBrush (dad->defObjCOLOR);
          }
        if (moving->rtti () == QCanvasItem::Rtti_Text)
        {
          ((CCanvasText *) moving)->setColor (dad->defObjCOLOR);
	  //qDebug(((CCanvasText *) moving)->text ());
        }

      }
      break;
    case 15:		//EyedropperTool;
      {
        QPoint p = e->globalPos ();
        QWidget *desktop = QApplication::desktop ();
        QPixmap pm =
          QPixmap::grabWindow (desktop->winId (), p.x (), p.y (), 1, 1);
        QImage i = pm.convertToImage ();

        QRgb px = i.pixel (0, 0);
        QColor color (qRed (px), qGreen (px), qBlue (px));
        dad->dad->setDefObjCOLOR (color);
      }
      break;
    case 16:		//EraserTool;
      {
        //              QKeyEvent *s=new QKeyEvent(QEvent::KeyPress,Qt::Key_Delete,0,0);
        //              keyPressEvent(s);
        QPoint p = inverseWorldMatrix ().map (e->pos ());
        QCanvasItemList l = canvas ()->collisions (p);
        for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();
             ++it)
        {
          if ((*it)->rtti () == 666)
          {		//if user clicked on def. scene rect. then dont select it.
            continue;
          }
          moving = *it;
        }
        if (moving)
        {
          moving->hide ();
          delete moving;
          moving = 0;
        }
      }
      break;
    case 17:		//HandTool;
      moving_start = inverseWorldMatrix ().map (e->pos ());
      setCursor (handCursorDown);
      break;
    case 18:		//ZoomTool;
      QWMatrix m = worldMatrix ();
      m.scale (1.4, 1.4);
      QPoint p = inverseWorldMatrix ().map (e->pos ());
      int x = (p.x ()), y = (p.y ());
      scrollBy (x, y);
      setWorldMatrix (m);
      break;
    }
  }
  if (e->button () == RightButton && dad->defObjID != 18)
  {
    QPopupMenu *renkicin = new QPopupMenu (this);
    /*          renkicin->insertItem ("Color chooser", this, SLOT (finish_element ()));
       renkicin->insertItem ("Red", this, SLOT (makeElementRed ()));
       renkicin->insertItem ("Green", this, SLOT (makeElementGreen ()));
       renkicin->insertItem ("Blue", this, SLOT (makeElementBlue ()));
       renkicin->insertSeparator();
       renkicin->insertItem ("CleaR", this, SLOT (deleteElement ()));       */
    QFont f ("Sans", 8, QFont::Normal);
    renkicin->setFont (f);
    renkicin->insertItem (tr ("Cut"));
    renkicin->insertItem (tr ("Copy"));

    renkicin->insertItem (tr ("Paste"));
    renkicin->insertItem (tr ("Paste in Place"));
    renkicin->insertSeparator ();
    renkicin->insertItem (tr ("Select All"));
    renkicin->insertItem (tr ("Deselect All"));
    renkicin->insertSeparator ();
    renkicin->insertItem (tr ("Free Transform"));
    renkicin->insertItem (tr ("Scale"));
    renkicin->insertItem (tr ("Rotate and Skew"));
    renkicin->insertSeparator ();
    renkicin->insertItem (tr ("Rulers"));
    renkicin->insertItem (tr ("Grid"));
    renkicin->insertItem (tr ("Guides"));
    renkicin->insertSeparator ();
    renkicin->insertItem (tr ("Snap to Objects"));
    renkicin->insertSeparator ();
    renkicin->insertItem (tr ("Document Properties"));
    renkicin->insertItem (tr ("Movie Explorer"));
    renkicin->insertItem (tr ("Scene"));
    renkicin->insertSeparator ();
    renkicin->insertItem (tr ("Convert to Symbol"));
    renkicin->insertSeparator ();
    int id = renkicin->insertItem (tr ("Properties"), (QObject *) dad->dad,
                                   SLOT (slotWindowProperities ()));
    if (dad->dad->propertiesDockableWindow->isVisible ())
      renkicin->setItemChecked (id, true);

    //inverseWorldMatrix().map()
    renkicin->popup (contentsToViewport (e->pos ()));
    renkicin->exec ();
    renkicin->~QPopupMenu ();
  }
  if (e->button () == RightButton)
  {
    switch (dad->defObjID)
    {
    case 18:		//zoom tool selected
      {
        QWMatrix m = worldMatrix ();
        m.scale (0.7, 0.7);

        QPoint p = inverseWorldMatrix ().map (e->pos ());
        int x = (p.x ()), y = (p.y ());

        scrollBy (x, y);
        setWorldMatrix (m);
      }
    }
  }
  canvas ()->update ();

}

void canview::contentsMouseMoveEvent (QMouseEvent * e)
{
  if (butPos)
  {
    movX = e->x ();
    movY = e->y ();
    switch (dad->defObjID)
    {
    case 1:		//ArrowTool;
      {
        if (selectionRect != NULL && moving == 0)
        {
          selectionRect->setSize ((movX - cenX), (movY - cenY));
        }
        if (mulSelect.count () > 0)
        {
          canvas ()->setChanged (QRect (contentsX (), contentsY (), contentsWidth (), contentsHeight ()));	//////////this line killing the performance!!!!!!!but clearing the scene :)
          QPoint p = inverseWorldMatrix ().map (e->pos ());
          QCanvasItemList l = mulSelect;
          for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();++it)
          {
            if ((*it)->rtti () == 666 || (*it)->rtti () == 667)
            {		//if user clicked on def. scene rect. then dont select it.
              continue;
            }
            moving = *it;
            moving->moveBy (p.x () - moving_start.x (),
                            p.y () - moving_start.y ());
          }
          //moving_start = p;
          l = mulSelectedRects;
          for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();++it)
          {
            moving = *it;
            if ((*it)->rtti () == 667)
              moving->moveBy (p.x () - moving_start.x (),
                              p.y () - moving_start.y ());
          }
          moving_start = p;
        }
        else if (moving)
        {
          //canvas()->setChanged(moving->boundingRect());
          QPoint p = inverseWorldMatrix ().map (e->pos ());
          moving->moveBy (p.x () - moving_start.x (),
                          p.y () - moving_start.y ());

          if (selectedRect != NULL)
            selectedRect->moveBy (p.x () - moving_start.x (),
                                  p.y () - moving_start.y ());
          moving_start = p;
          //viewport()->update();
          //QRect r=;
          //r.moveBy (contentsToViewport(e->pos()).x(),contentsToViewport(e->pos()).y());
          //QPainter pr(viewport());
          //pr.setPen( Qt::blue );
          //pr.drawRect(r);
          //canvas()->update();
        }
        CCanvasEllipse *tmp=(CCanvasEllipse*)moving;
        //if(tmp)qDebug("X: %d row:%d",tmp->animationX,tmp->rtti());
      }
      break;
    case 2:		//SubSelectionTool;
      break;
    case 3:		//LineTool;
      line->setPoints (cenX, cenY, movX, movY);

      break;
    case 4:		//LassoTool;
      break;
    case 5:		//PenTool;
      {
        /*polyline[2] = polyline[1];
           polyline[1] = polyline[0];
           polyline[0] = e->pos();
           spline->setControlPoints (polyline,false); */
      }
      break;
    case 6:		//TextTool;
      {
        //text->move (movX, movY);
      }
      break;
    case 7:		//OvalTool;
      oval->setSize ((21 / 7) * abs (movX - cenX),
                     (21 / 7) * abs (movY - cenY));
      break;
    case 8:		//RectangleTool;
      rect->setSize ((movX - cenX), (movY - cenY));
      break;
    case 9:		//PencilTool;
      {
        /*static int i;
           polyline[i] = e->pos();
           if(i>1000)polyline.resize(i+1); */
        QPainter p1 (viewport ());
        p1.drawPoint (contentsToViewport (e->pos ()).x (),
                      contentsToViewport (e->pos ()).y ());
        QPoint *pt = new QPoint ((e->pos ()));
        pPolylineTemp.append (pt);
        //pencilline->drawShape(p);
        //                                pencilline->drawShape(QPainter());
        //                                pencilline->setPoints(polyline);

        //i++;
        //pencilline->update();
        //polyline[2] = polyline[1];
        //polyline[1] = polyline[0];
        /* int i=polyline.size()-1;

           polyline[i] = e->pos();
         */

        break;
      }
    case 10:		//BrushTool;
      {
        QPainter p1 (viewport ());
        p1.drawPoint (contentsToViewport (e->pos ()).x (),
                      contentsToViewport (e->pos ()).y ());
        QPoint *pt = new QPoint ((e->pos ()));
        pPolylineTemp.append (pt);
      }
      break;
    case 11:		//FreeTransformTool;
      break;
    case 12:		//FillTransformTool;
      break;
    case 13:		//InkBottleTool;
      break;
    case 14:		//PaintBucketTool;
      break;
    case 15:		//EyedropperTool;
      break;
    case 16:		//EraserTool;
      break;
    case 17:		//HandTool;
      {
        QPoint p = inverseWorldMatrix ().map (e->pos ());
        int x = -1 * (p.x () - moving_start.x ()), y =
                  -1 * (p.y () - moving_start.y ());
        scrollBy (x, y);
        // moving_start = p;
      }
      break;

    case 18:		//ZoomTool;
      break;
    }

  }
  canvas ()->update ();
}

void canview::contentsMouseReleaseEvent (QMouseEvent * e)
{
  butPos = false;
  switch (dad->defObjID)
  {
  case 1:			//ArrowTool;
    if (selectionRect != NULL)
    {
      /////////////here will be some kind of multiple selection action
      mulSelect = selectionRect->collisions (false);
      QCanvasItemList l = mulSelect;
      for (QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it)
      {
        if ((*it)->rtti () == 666)
        {		//if user clicked on def. scene rect. then dont select it.
          //l.remove(it);
          continue;
        }
        CtmpRect *r = new CtmpRect ((*it)->boundingRect (), canvas ());
        r->setPen (QColor (0, 168, 255));
        r->show ();
        mulSelectedRects.append (r);
      }
      selectionRect->hide ();
      //delete selectionRect;
      selectionRect = NULL;
      moving = 0;
    }
    else
    {
      QCanvasItemList l = canvas ()->allItems ();
      for (QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it)
      {
        if ((*it)->rtti () == 667)
        {
          (*it)->hide ();
          delete *it;
        }
        mulSelect.clear ();
        mulSelectedRects.clear ();
      }
    }
    /*if (selectedRect != NULL) {
       selectedRect->hide ();
               //delete selectedRect;

       selectedRect = NULL;

       } */
    moving = 0;
    break;
  case 2:			//SubSelectionTool;
    break;
  case 3:			//LineTool;

    break;
  case 4:			//LassoTool;
    break;
  case 5:			//PenTool;

    break;
  case 6:			//TextTool;
	
    break;
  case 7:			//OvalTool;

    break;
  case 8:			//RectangleTool;

    break;
  case 9:			//PencilTool;
    {
      QPointArray tempArr = QPointArray (pPolylineTemp.count ());
      int i = 0;
      for (QPoint * it = pPolylineTemp.first (); it;it = pPolylineTemp.next ())
      {
        tempArr[i] = (*it);
        i++;
      }
      pencilline->setControlPoints (tempArr);
      pencilline->show ();
    }
    break;
  case 10:			//BrushTool;
    {
      canvas ()->setAllChanged ();
      QPointArray tempArr = QPointArray (pPolylineTemp.count ());
      int i = 0;
      for (QPoint * it = pPolylineTemp.first (); it;it = pPolylineTemp.next ())
      {
        tempArr[i] = (*it);
        i++;
      }
      brushline->setControlPoints (tempArr);
      brushline->show ();
    }
    break;
  case 11:			//FreeTransformTool;
    break;
  case 12:			//FillTransformTool;
    break;
  case 13:			//InkBottleTool;
    break;
  case 14:			//PaintBucketTool;
    break;
  case 15:			//EyedropperTool;
    break;
  case 16:			//EraserTool;
    break;
  case 17:			//HandTool;
    {
      // QCursor *c=new ;(const)&
      setCursor (handCursor);
      break;
    }
  case 18:			//ZoomTool;
    break;
  default:
    setCursor (Qt::CrossCursor);
    break;
  }
  canvas ()->update ();
  dad->dad->tl->tableRefresh();
}


/*void canview::mousePressEvent ( QMouseEvent * e ){
	if (e->button () == RightButton)
	{
		QPopupMenu* renkicin = new QPopupMenu (this);
 
		
		QFont f( "Sans", 8, QFont::Normal );
		renkicin->setFont(f);
		renkicin->insertItem ("Cut");
		renkicin->insertItem ("Copy");
 
		renkicin->insertItem ("Paste");
		renkicin->insertItem ("Paste in Place");
		renkicin->insertSeparator();
		renkicin->insertItem ("Select All");
		renkicin->insertItem ("Deselect All");
		renkicin->insertSeparator();
 
		renkicin->insertItem ("Free Transform");
		renkicin->insertItem ("Scale");
		renkicin->insertItem ("Rotate and Skew");
		renkicin->insertSeparator();
		renkicin->insertItem ("Rulers");
		renkicin->insertItem ("Grid");
		renkicin->insertItem ("Guides");
		renkicin->insertSeparator();
		renkicin->insertItem ("Snap to Objects");
		renkicin->insertSeparator();
		renkicin->insertItem ("Document Properties");
		renkicin->insertItem ("Movie Explorer");
		renkicin->insertItem ("Scene");
		renkicin->insertSeparator();
		renkicin->insertItem ("Convert to Symbol");
		renkicin->insertSeparator();
		int id=renkicin->insertItem ("Properties",(QObject*)dad->dad,SLOT(slotWindowProperities()));
		if(dad->dad->propertiesDockableWindow->isVisible())
		renkicin->setItemChecked(id,true);
 
		//inverseWorldMatrix().map()
 
		renkicin->popup (mapToGlobal(e->pos()));
		renkicin->exec ();
		renkicin->~QPopupMenu() ;
	}
} */

void canview::enterEvent (QEvent * e)
{
  switch (dad->defObjID)
  {
  case 1:			//ArrowTool;
    {
      setCursor (arrowToolCursor);
      break;
    }
  case 2:			//SubSelectionTool;
    setCursor (subselectiontoolCursor);
    break;
  case 3:			//LineTool;
    setCursor (Qt::CrossCursor);
    break;
  case 4:			//LassoTool;
    setCursor (lassotoolCursor);
    break;
  case 5:			//PenTool;
    setCursor (pentoolCursor);
    break;
  case 6:			//TextTool;
    setCursor (texttoolCursor);
    break;
  case 7:			//OvalTool;
    setCursor (Qt::CrossCursor);
    break;
  case 8:			//RectangleTool;
    setCursor (Qt::CrossCursor);
    break;
  case 9:			//PencilTool;
    setCursor (pencilCursor);
    break;
  case 10:			//BrushTool;
    setCursor (brushCursor);
    break;
  case 11:			//FreeTransformTool;
    break;
  case 12:			//FillTransformTool;
    break;
  case 13:			//InkBottleTool;
    setCursor (inkbottleCursor);
    break;

  case 14:			//PaintBucketTool;
    setCursor (paintbucketCursor);
    break;

  case 15:			//EyedropperTool;
    setCursor (eyedroppertool);
    break;
  case 16:			//EraserTool;
    setCursor (eraserCursor);
    break;
  case 17:			//HandTool;
    {
      // QCursor *c=new ;(const)&
      setCursor (QCursor (handCursor));
      break;
    }
  case 18:			//ZoomTool;
    setCursor (zoominCursor);

    break;
  default:
    setCursor (Qt::CrossCursor);
    break;

  }
}

void canview::leaveEvent (QEvent * e)
{}

void canview::contentsMouseDoubleClickEvent (QMouseEvent * e)
{
  //qDebug("�ft tklayanda g�yor :)");
  if (dad->defObjID == 1)
  {
    moving = 0;
    QPoint p = inverseWorldMatrix ().map (e->pos ());
    QCanvasItemList l = canvas ()->collisions (p);
    for (QCanvasItemList::Iterator it = l.begin (); it != l.end (); ++it)
    {
      if ((*it)->rtti () == QCanvasItem::Rtti_Text)
      {
        moving = *it;
      }
    }
    if (moving != NULL && moving->rtti () == QCanvasItem::Rtti_Text)
    {
      //moving->hide();
      text = (CCanvasText *) moving;
      textBox->show ();
      //textBox=new CTextEditForTextTool(this,"textboxforEnteringText");
      textBox->move (contentsToViewport (e->pos ()));
      textBox->setColor (((QCanvasText *) moving)->color ());
      textBox->setText (((QCanvasText *) moving)->text ());

      //textBox->adjustSize();
      textBox->setFocus ();
      //textBox->setSelection(0,0,0,5);
      moving->show ();
      canvas ()->update ();
    }
    canvas ()->update ();
  }
}

void canview::contentsDropEvent (QDropEvent *)
{}

/** No descriptions */
void canview::keyPressEvent (QKeyEvent * e)
{
  switch (e->key ())
  {
  case Qt::Key_Delete:
    if (dad->defObjID)
    {
      QCanvasItemList l = mulSelect;
      for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();++it)
      {
        if ((*it)->rtti () == 666 || (*it)->rtti () == 667)
        {		//if user clicked on def. scene rect. then dont select it.
          continue;
        }
        moving = *it;
        moving->hide ();
        delete moving;
      }
      //moving_start = p;
      l = mulSelectedRects;
      for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();++it)
      {
        moving = *it;
        if ((*it)->rtti () == 667)
        {
          moving->hide ();
          delete moving;
        }
      }
      canvas ()->update ();
      moving = 0;
    }
    break;
  }

}

void canview::paintEvent (QPaintEvent * e)
{
  QCanvasView::paintEvent (e);
}
