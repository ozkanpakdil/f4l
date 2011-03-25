/***************************************************************************
              f4lmview.cpp  -  description
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

// include files for Qt
#include <qprinter.h>
#include <qpainter.h>
#include <qslider.h>
#include <qpainter.h>
#include <qimage.h>
#include <qbuttongroup.h>
#include <qsizepolicy.h>

// application specific includes
#include "f4lmview.h"
#include "f4lmdoc.h"
#include "f4lm.h"
#include "cursor/main_doc_ico.xpm"
#include "clayer.h"
#include "cbase.h"



F4lmView::F4lmView (F4lmDoc * pDoc, QWidget * parent, const char *name, int wflags)
    :QWidget (parent, name, wflags) {
    setName ("F4lmView");
    dad = (F4lmApp *) parentWidget ()->parent ()->parent ();
    doc = pDoc;
    resize (700, 600);
    setIcon (QPixmap ((const char **) main_doc_ico_xpm));
    layerNum = 1;
    defSceneHeight = 440;
    defSceneWidth = 550;
    defSceneRect = QRect (600, 600, defSceneWidth, defSceneHeight);
    QVBoxLayout * topLayout = new QVBoxLayout (this);
    
	CLayer * layer1 = new CLayer (this, "layer 1");
    mainCanvas = new CCanvas (this, "mc");
    CSceneRect * defrect = new CSceneRect (defSceneRect, mainCanvas);
    defrect->setBrush (QColor (255, 255, 255));
    defrect->setZ (1<<31);//smallest integer.....
	//qDebug("%d",1<<31);
    defrect->show ();
    mainCanvas->resize (defSceneWidth + defSceneWidth + 600,defSceneHeight + defSceneHeight + 600);
    mainCanvas->setBackgroundColor (QColor (208, 208, 208));
    
	doc->pLayerList->append (layer1);
    canvasViewer = new canview (mainCanvas, this, "Canvas viewer");
    
    canvasViewer->scrollBy (550, 550);
    topLayout->addWidget (canvasViewer);
    
    defObjID = 0;
    //this means first color for drawing is black
    defObjCOLOR = QColor (0, 0, 0);
    //qDebug(QString::number(defObjCOLOR.red()));
    /*boundaries=new QValueVector<canvasBoundaries>();
       canvasBoundaries tcanvb;
       tcanvb.canvasLimitsForTable[0][0]=layerNum;
       tcanvb.canvasLimitsForTable[0][1]=0;
       tcanvb.canvasLimitsForTable[0][2]=0;
       boundaries->push_back(tcanvb); */

}

F4lmView::~F4lmView () {
}

F4lmDoc * F4lmView::getDocument () const {
    return doc;
}

void F4lmView::update (F4lmView * pSender) {
    if (pSender != this)
    repaint ();
}

void F4lmView::print (QPrinter * pPrinter) {
    if (pPrinter->setup (this)) {
    QPainter p;
    p.begin (pPrinter);
        ///////////////////////////////
        // TODO: add your printing code here
        ///////////////////////////////
    p.end ();
    }
}

void F4lmView::closeEvent (QCloseEvent *) {
    // LEAVE THIS EMPTY: THE EVENT FILTER IN THE F4lmApp CLASS TAKES CARE FOR CLOSING
    // QWidget closeEvent must be prevented.
}

void F4lmView::slotNewLayer () {
    CLayer * layer = new CLayer (this, "layer" + QString::number (layerNum));
    //CCanvas * main = new CCanvas (this, "m");
    /*CSceneRect * defrect = new CSceneRect(defSceneRect, mainCanvas);
    defrect->setBrush (QColor (255, 255, 255));
    defrect->setZ (-1);
    defrect->show ();*/
    mainCanvas->resize (defSceneWidth + defSceneWidth + 600,defSceneHeight + defSceneHeight + 600);
    mainCanvas->setBackgroundColor (QColor (208, 208, 208));
    //    layer->pCanvasList->append(main);
    doc->pLayerList->append (layer);
}

void F4lmView::slotInsertFrame (int row, int col) {
////////buraya matrixde yer acma mantigi getirilecek ve tek canvasdan calismaya devam edecek.

/*    if (CLayer * l = doc->pLayerList->at (row)) {
        for (int i = l->pCanvasList->count (); i < col; i++) {
            CCanvas * main = new CCanvas (this, "mc " + QString::number (i));
            CSceneRect * defrect = new CSceneRect (defSceneRect, main);
            defrect->setBrush (QColor (255, 255, 255));
            defrect->setZ (-1);
            defrect->show ();
            main->resize (defSceneWidth + defSceneWidth + 600,defSceneHeight + defSceneHeight + 600);
            main->setBackgroundColor (QColor (208, 208, 208));
            l->pCanvasList->append (main);
        }
    qDebug ("orda layer yok");

>>>>>>> 1.7
*/
CListViewItem *tmpListViewItem=(CListViewItem*)dad->tl->timeLineListbox->selectedItem();
int animX=dad->tl->layerFrames->at(tmpListViewItem->m_Row-1)->frames->last ()->tableItemNo;
int z=-1*tmpListViewItem->m_Row;
	QCanvasItemList l=mainCanvas->allItems();
	 for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();++it) {
				 if ((*it)->rtti () == 666 || (*it)->rtti () == 667) {		//if user clicked on def. scene rect. then dont select it.
                        continue;
		}
		switch((*it)->rtti()){
			case QCanvasItem::Rtti_Ellipse:
			{
				CCanvasEllipse *oval=(CCanvasEllipse*)(*it);
				if(oval->Row==z){
					oval->animationX=animX;
				}
			}
			break;
			case QCanvasItem::Rtti_Line:
			{
				CCanvasLine *line=(CCanvasLine*)(*it);
				if(line->Row==z)
					line->animationX=animX;
			}
			break;
			case QCanvasItem::Rtti_Polygon:
				
			break;
			case QCanvasItem::Rtti_PolygonalItem:
			{
				CPencilLine *poly=(CPencilLine*)(*it);
				if(poly->Row==z)
					poly->animationX=animX;
			}
			break;
			case QCanvasItem::Rtti_Rectangle:
			{
				CCanvasRectangle *rect=(CCanvasRectangle*)(*it);
				if(rect->Row==z)
					rect->animationX=animX;
			}
			break;
			case QCanvasItem::Rtti_Spline:
			break;
			case QCanvasItem::Rtti_Sprite:
			break;
			case QCanvasItem::Rtti_Text:
			{
				CCanvasText *text=(CCanvasText*)(*it);
				if(text->Row==z)
					text->animationX=animX;
			}
			break;
	}
}
}

void F4lmView::slotShowCanvas (int row, int col) {
////////burada matrixdeki bölgede secili yerin show edilmesi saglanacak.
/////// bu durumda insert frame de matrix degisiklikleri yapilacak.
    //qDebug("row:%d col:%d listNum:%d",row,col);
/*    CLayer * l;
    CCanvas *curCan = NULL;

    if (row < doc->pLayerList->count ())
    l = doc->pLayerList->at (row);

    if (col < l->pCanvasList->count () && l)
    curCan = l->pCanvasList->at (col);

    if (curCan && curCan != canvasViewer->canvas ())
<<<<<<< f4lmview.cpp
        canvasViewer->setCanvas (curCan);
*/
	CCanvasItem *Object;
	QCanvasItemList l=mainCanvas->allItems();
	 for (QCanvasItemList::Iterator it = l.begin (); it != l.end ();++it) {
		 if ((*it)->rtti () == 666 || (*it)->rtti () == 667) {		//if user clicked on def. scene rect. then dont select it.
                        continue;
		}
		switch((*it)->rtti()){
			case QCanvasItem::Rtti_Ellipse:
			{
				CCanvasEllipse *oval=(CCanvasEllipse*)(*it);
				if(oval->animationX>=col){
					oval->show();
					//qDebug("oval show edildi");
				}
				else{
					oval->hide();
					//qDebug("oval hide edildi");
				}
			}
			break;
			case QCanvasItem::Rtti_Line:
			{	CCanvasLine *line=(CCanvasLine*)(*it);
				if(line->animationX>=col)
					line->show();
				else
					line->hide();
			}
			break;
			case QCanvasItem::Rtti_Polygon:
				
			break;
			case QCanvasItem::Rtti_PolygonalItem:
			{
				CPencilLine *poly=(CPencilLine*)(*it);
				if(poly->animationX>=col)
					poly->show();
				else
					poly->hide();
			}
			break;
			case QCanvasItem::Rtti_Rectangle:
			{
				CCanvasRectangle *rect=(CCanvasRectangle*)(*it);
				if(rect->animationX>=col)
					rect->show();
				else
					rect->hide();
			}
			break;
			case QCanvasItem::Rtti_Spline:
			break;
			case QCanvasItem::Rtti_Sprite:
			break;
			case QCanvasItem::Rtti_Text:
			{
				CCanvasText *text=(CCanvasText*)(*it);
				if(text->animationX>=col)
					text->show();
				else
					text->hide();
			}
			break;
		}
		//mainCanvas->setChanged(QRect (canvasViewer->contentsX (), canvasViewer->contentsY (), canvasViewer->contentsWidth (), canvasViewer->contentsHeight ()));
		mainCanvas->update();
		//canvasViewer->repaint();
		/*Object= dynamic_cast<CCanvasItem*> (*it);
//qDebug("animationx im : %d" , Object->animationX);
		if(Object->animationX>=col)
			Object->hide();
		else
			Object->show();*/
	
}
	

}

void F4lmView::mouseMoveEvent (QMouseEvent * e) {
    QWidget::mouseMoveEvent (e);
}


