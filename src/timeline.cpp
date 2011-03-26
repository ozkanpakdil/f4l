/****************************************************************************
** 
**
** Created: Mon Jun 9 05:33:27 2003
**     copyright            : (C) 2003 by özkan pakdil
**    email                : ozkanpakdil@users.sourceforge.net
**
** 
****************************************************************************/

#include "timeline.h"
#include "clistboxitem.h"
#include "f4lm.h"
#include "f4lmview.h"
#include "cbase.h"
#include "ctableitem.h"
#include "canvasItem.h"
#include "ccanvasellipse.h"
#include "ccanvasline.h"
#include "ccanvastext.h"
#include "ccanvasrectangle.h"
#include "cpencilline.h"
#include "timeline.h"
#include "clistboxitem.h"
#include "ccanvas.h"

#include <qvariant.h>
#include <q3buttongroup.h>
#include <qlabel.h>
#include <q3listbox.h>
#include <qpushbutton.h>
#include <qsplitter.h>
#include <q3table.h>
#include <qtoolbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <q3whatsthis.h>
#include <qpainter.h>
//#include <iostream.h>
#include <q3listview.h>
#include <qimage.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <QPixmap>
#include <Q3PtrList>
#include <Q3VBoxLayout>
#include <QDebug>
#include <iostream>

#include "cursor/new_layer_on_timeline.xpm"
#include "cursor/motion_guide.xpm"
#include "cursor/delete_layer.xpm"
#include "cursor/layer_folder.xpm"
#include "cursor/layer_pic.xpm"
#include "cursor/written_pic.xpm"
#include "cursor/outline_pic.xpm"
#include "cursor/goz_pic.xpm"
#include "cursor/kilit_pic.xpm"
#include "cursor/dot.xpm"

using namespace std;

/*
*  Constructs the timelinetable which is a child of 'f4lmapp', with the 
*  name 'timeLineTable' and widget flags set to 'f'.
*/
CTimeLine::CTimeLine (QWidget * parent, const char *name, bool modal,Qt::WFlags fl)
        :QWidget (parent, name)
{
    layerFrames = new Q3PtrList < CTimeLineDataStructure >;
    CTimeLineDataStructure * node = new CTimeLineDataStructure (1);
    CTimeLineNodes * tabnode = new CTimeLineNodes (1);
    node->frames->append (tabnode);
    layerFrames->append (node);

    dad = (F4lmApp *) parentWidget ()->parent ()->parent ();

    if (!name)
        setName ("TimeLine");

        //resize( 600, 480 );
    tableColNum = 560;

    setCaption (trUtf8 ("TimeLine"));
    layerNum = 1;
    layerMaxColNum = 1;
    Q3VBoxLayout * topLayout = new Q3VBoxLayout (this);

    Splitter1 = new QSplitter (this, "Splitter1");
    Splitter1->setOrientation (Qt::Horizontal);
    
	QWidget * privateLayoutWidget = new QWidget (Splitter1, "Layout2");

    Layout2 = new Q3VBoxLayout (privateLayoutWidget, 0, 0, "Layout2");
    Splitter1->setResizeMode (privateLayoutWidget, QSplitter::KeepSize);
    timeLineLeftTopLabel =new CLabel (privateLayoutWidget, "timeLineLeftTopLabel");
    timeLineLeftTopLabel->setFixedHeight (23);
    Layout2->addWidget (timeLineLeftTopLabel);
        
	timeLineListbox = new CListView (privateLayoutWidget, "timeLineListView");	//new QListView( privateLayoutWidget, "timeLineListbox" );

    
	int i, j;
    QPixmap kare;		//(16,16,8);
    kare.resize (14, 14);
    kare.fill (Qt::red);
    QImage _kare = kare.convertToImage ();

    for (i = 0; i < 14; i++)
        for (j = 0; j < 14; j++) {
            if (i == 0 || i == 13 || i == 1 || i == 12)
                _kare.setPixel (i, j, qRgb (0, 0, 0));
            if (j == 0 || j == 13 || j == 1 || j == 12)
                _kare.setPixel (i, j, qRgb (0, 0, 0));
        }

    kare.convertFromImage (_kare, QPixmap::Color);

    QPixmap _0 = QPixmap ((const char **) layer_pic_xpm);
    QPixmap _1 = QPixmap ((const char **) written_pic_xpm);
    QPixmap _2 = QPixmap ((const char **) goz_pic_xpm);
    QPixmap _3 = QPixmap ((const char **) kilit_pic_xpm);
    QPixmap _4 = QPixmap ((const char **) outline_pic_xpm);
    QPixmap _5 = QPixmap ((const char **) dot_xpm);

    CListViewItem * it =new CListViewItem (timeLineListbox, "", "Layer " + QString::number (layerNum), "");
	it->m_Row=1;
    it->setPixmap (0, _0);
    it->setPixmap (2, _1);
    it->setPixmap (3, _5);
    it->setPixmap (4, _5);
    it->setPixmap (5, kare);

        //new QListViewItem(timeLineListbox,"","c","");
        //timeLineListbox->insertItem(  );
        //timeLineListbox->insertItem("lay");
        //timeLineListbox->setRowMode(QListBox::FitToHeight);
        //QHeader *h=timeLineListbox->header();
        //h->hide();
        /*QListViewItem *it= */// new QListViewItem(timeLineListbox,"1");
        //it->setText(1,"alo");
        // timeLineListbox->setMinimumSize( QSize( 120, 0 ) );
        // timeLineListbox->setMaximumSize( QSize( 120, 100 ) );
        //connect(timeLineListbox,SIGNAL(clicked(QListViewItem*)),this,SLOT(slotListViewClicked(QListViewItem* )));
    Layout2->addWidget (timeLineListbox);
	timeLineListbox->firstChild()->setSelected(true);

    timeLineLeftButtonGroup = new Q3ButtonGroup (privateLayoutWidget, "timeLineLeftButtonGroup");

        //timeLineLeftButtonGroup->setMinimumSize( QSize( 120, 0 ) );
        //timeLineLeftButtonGroup->setMaximumSize( QSize( 120, 22 ) );
    timeLineLeftButtonGroup->setLineWidth (0);
    timeLineLeftButtonGroup->setFixedSize (190, 20);
    timeLineLeftButtonGroup->setTitle (trUtf8 (""));

    NewLayer = new QToolButton (timeLineLeftButtonGroup, "NewLayer");
    NewLayer->setGeometry (QRect (2, 2, 19, 17));
    NewLayer->setIconSet (QIcon(QPixmap ((const char **) new_layer_on_timeline_xpm)));
    NewLayer->setTextLabel ("Insert Layer");

        //NewLayer->adjustSize();
    connect (NewLayer, SIGNAL (clicked ()), this, SLOT (slotNewLayer ()));

    NewWayLayer = new QToolButton (timeLineLeftButtonGroup, "NewWayLayer");
    NewWayLayer->setGeometry (QRect (22, 2, 19, 17));
    NewWayLayer->setIconSet (QIcon (QPixmap ((const char **) motion_guide_xpm)));
    NewWayLayer->setTextLabel (trUtf8 ("Add motion Guide"));

    NewLayerFolder = new QToolButton (timeLineLeftButtonGroup, "NewLayerFolder");
    NewLayerFolder->setGeometry (QRect (42, 2, 19, 17));
    NewLayerFolder->setIconSet (QIcon (QPixmap ((const char **) layer_folder_xpm)));
    NewLayerFolder->setTextLabel (trUtf8 ("Insert Layer Folder"));

    DeleteLayer = new QToolButton (timeLineLeftButtonGroup, "DeleteLayer");
    DeleteLayer->setGeometry (QRect (92, 2, 19, 17));
    DeleteLayer->setIconSet (QIcon (QPixmap ((const char **) delete_layer_xpm)));
    DeleteLayer->setTextLabel (trUtf8 ("Delete Layer"));

    Layout2->addWidget (timeLineLeftButtonGroup);

    QWidget * privateLayoutWidget_2 = new QWidget (Splitter1, "Layout3");

    Layout3 = new Q3VBoxLayout (privateLayoutWidget_2, 0, 0, "Layout3");

    baseforleftlabel = new CBase (privateLayoutWidget_2, "baseforleftlabel");

    timeLineRightTopLabel = new CLabel (baseforleftlabel, "timeLineRightTopLabel");
    timeLineRightTopLabel->setMinimumHeight (20);
    timeLineRightTopLabel->resize (tableColNum * 8, 20);

    Q3HBoxLayout * Layout9 = new Q3HBoxLayout (Layout3);
    Layout9->addWidget (baseforleftlabel);

    baseforleftlabel->addChild (timeLineRightTopLabel);
    baseforleftlabel->setVScrollBarMode (Q3ScrollView::AlwaysOff);
    baseforleftlabel->setHScrollBarMode (Q3ScrollView::AlwaysOff);
    baseforleftlabel->setFixedHeight (26);

    connect (timeLineRightTopLabel, SIGNAL (valueChanged ()), this,SLOT (slotLabelclick ()));

    Q3HBoxLayout * Layout8 = new Q3HBoxLayout (Layout3);
    VScrollBar1 = new QScrollBar (privateLayoutWidget_2, "Scroll bar V");
    VScrollBar1->setOrientation (Qt::Vertical);
    VScrollBar1->setMinValue (0);
    VScrollBar1->setMaxValue (layerNum + 1);

    connect (VScrollBar1, SIGNAL (sliderMoved (int)), this,SLOT (slotTableVscrollmove (int)));

    timeLineTable = new CTable (1, tableColNum, privateLayoutWidget_2, "timeLineTable");

    for (i = 0; i < tableColNum; i++) {
        CTableItem * tabit = new CTableItem (timeLineTable, Q3TableItem::Never, "");
        if (i == 0) {
            tabit->ready = true;
            tabit->empty_keyframe = true;
            tabit->filled = false;
            tabit->keyFrameStart = true;
            tabit->layerChooser = true;
        }
        tabit->frameNo = i;
        timeLineTable->setItem (layerNum - 1, i, tabit);
    }

    Layout8->addWidget (timeLineTable);
    Layout8->addWidget (VScrollBar1);

    timeLineRightButtonGroup = new Q3ButtonGroup (privateLayoutWidget_2, "timeLineRightButtonGroup");
    timeLineRightButtonGroup->setLineWidth (0);
    timeLineRightButtonGroup->setTitle (trUtf8 (""));

    Q3HBoxLayout * Layout4 = new Q3HBoxLayout (timeLineRightButtonGroup);

    ToolButton6 = new QToolButton (timeLineRightButtonGroup, "ToolButton6");
    ToolButton6->setGeometry (QRect (0, 0, 21, 21));
    ToolButton6->setFixedSize (21, 21);
    ToolButton6->setText (trUtf8 ("..."));

    Layout4->addWidget (ToolButton6);

    ToolButton7 = new QToolButton (timeLineRightButtonGroup, "ToolButton7");
    ToolButton7->setGeometry (QRect (20, 0, 21, 21));
    ToolButton7->setFixedSize (21, 21);
    ToolButton7->setText (trUtf8 ("..."));

    Layout4->addWidget (ToolButton7);

    ToolButton8 = new QToolButton (timeLineRightButtonGroup, "ToolButton8");
    ToolButton8->setGeometry (QRect (40, 0, 21, 21));
    ToolButton8->setFixedSize (21, 21);
    ToolButton8->setText (trUtf8 ("..."));

    Layout4->addWidget (ToolButton8);

    currentFrameLabel = new CLabel (timeLineRightButtonGroup, "currentFrameLabel");
        //      currentFrameLabel->setText(trUtf8("ct"));
    currentFrameLabel->adjustSize ();
    currentFrameLabel->setFixedSize (60, 21);

    Layout4->addWidget (currentFrameLabel);

    totalTimeLabel = new CLabel (timeLineRightButtonGroup, "totalTimeLabel");
    totalTimeLabel->adjustSize ();
    totalTimeLabel->setFixedSize (21, 21);
    Layout4->addWidget (totalTimeLabel);
    
	HScrollBar1 = new QScrollBar (timeLineRightButtonGroup, "Scroll bar");
    HScrollBar1->setOrientation (Qt::Horizontal);
    HScrollBar1->setMinimumWidth (width () - 50);

    connect (HScrollBar1, SIGNAL (valueChanged (int)), this, SLOT (slotTableHscrollmove (int)));

    HScrollBar1->setMinValue (0);
    HScrollBar1->setMaxValue (tableColNum * 10);

    Layout4->addWidget (HScrollBar1);
    Layout3->addWidget (timeLineRightButtonGroup);
    topLayout->addWidget (Splitter1);

    QToolButton * timeLineRightTopLabel_side = new QToolButton (privateLayoutWidget_2, "timeLineRightTopLabel");

    VScrollBar1->show ();
    Layout9->addWidget (timeLineRightTopLabel_side);

    if (VScrollBar1->isVisible ())
        timeLineRightTopLabel_side->setFixedWidth (VScrollBar1->width ());
    else
        timeLineRightTopLabel_side->setFixedWidth (16);

    connect (baseforleftlabel, SIGNAL (contentsMoving (int, int)), this, SLOT (slotLabelMove (int, int)));

}

/*
*  Destroys the object and frees any allocated resources
*/
CTimeLine::~CTimeLine ()
{
        // no need to delete child widgets, Qt does it all for us
}

/** No descriptions */
void CTimeLine::slotNewLayer ()
{
        //timeLineTable->insertRows (1,1);
        //layerNum++;
    timeLineTable->setNumRows (++layerNum);
        //timeLineTable->setGreyParts();
        //qDebug(QString::number(layerNum));

    int i, j;
    for (i = 0; i < tableColNum; i++) {
        CTableItem * tabit = new CTableItem (timeLineTable, Q3TableItem::Never, "");
        if (i == 0) {
            tabit->ready = true;
            tabit->empty_keyframe = true;
            tabit->filled = false;
            tabit->keyFrameStart = true;
            tabit->layerChooser = true;
        }
        tabit->frameNo = i;
        timeLineTable->setItem (layerNum - 1, i, tabit);
    }
    timeLineTable->updateCell (0, 0);

        //  timeLineListbox->insertItem("Layer "+QString::number(layerNum));
        // CListBoxItem* item=new CListBoxItem(timeLineListbox);
        //item->setText("alo");
        // timeLineListbox->insertItem( item );
        //timeLineListbox->insertItem(
        QPixmap kare;		//(16,16,8);
    kare.resize (14, 14);

    switch (layerNum % 5) {
    case 0:
        kare.fill (Qt::red);
        break;
    case 1:
        kare.fill (Qt::blue);
        break;
    case 2:
        kare.fill (Qt::cyan);
        break;
    case 3:
        kare.fill (Qt::green);
        break;
    case 4:
        kare.fill (Qt::gray);
        break;
    }

    QImage _kare = kare.convertToImage ();

    for (i = 0; i < 14; i++)
        for (j = 0; j < 14; j++) {
            if (i == 0 || i == 13 || i == 1 || i == 12)
                _kare.setPixel (i, j, qRgb (0, 0, 0));
            if (j == 0 || j == 13 || j == 1 || j == 12)
                _kare.setPixel (i, j, qRgb (0, 0, 0));
        }

    kare.convertFromImage (_kare, QPixmap::Color);

    QPixmap _0 = QPixmap ((const char **) layer_pic_xpm);
    QPixmap _1 = QPixmap ((const char **) dot_xpm);
    CListViewItem * it = new CListViewItem (timeLineListbox, "", "Layer " + QString::number (layerNum), "");
	it->m_Row=layerNum;
    it->setPixmap (0, _0);
    it->setPixmap (3, _1);
    it->setPixmap (4, _1);
    it->setPixmap (5, kare);
        //it->setHeight(20);
    VScrollBar1->setMaxValue (layerNum);

    dad->slotCurrentView ()->slotNewLayer ();

    CTimeLineDataStructure * node = new CTimeLineDataStructure (layerNum);
    CTimeLineNodes * tabnode = new CTimeLineNodes (0);
    node->frames->append (tabnode);
    layerFrames->append (node);
}

/** No descriptions */
void CTimeLine::slotTableHscrollmove (int mov)
{
        //asagidaki yapi scroll islemini iki adimda tamamliyor.
        //bunun kisa yolu bulunmali
    timeLineTable->scrollBy (-timeLineTable->numCols () *  timeLineTable->columnWidth (0), 0);
    timeLineTable->scrollBy (mov * timeLineTable->columnWidth (0), 0);
    baseforleftlabel->scrollBy (-timeLineRightTopLabel->width (), 0);
    baseforleftlabel->scrollBy (mov * 8, 0);

        //timeLineRightTopLabel->repaint();
//    qDebug ("mov : %d", mov);
        //cout<<"mov :"<<mov<<endl;
}

/** No descriptions */
void CTimeLine::slotTableVscrollmove (int mov)
{
    int a = -mov + timeLineTable->numRows ();
    timeLineTable->scrollBy (0, mov);
        //qDebug(QString::number(a));
}


/**
 * This Function works when user clicks on the timeline grey place at above of qtable.
 */
void CTimeLine::slotLabelclick ()
{
//qDebug("slotLabelClick : %d",currentFrameLabel->kutuNo);
    int ti = currentFrameLabel->kutuNo;
    for (int j = 0; j < layerNum; j++) {
        CTableItem *tc = (CTableItem *) timeLineTable->item (j, ti - 1);
        tc->layerChooser = false;
        timeLineTable->updateCell (j, ti - 1);
    }
    currentFrameLabel->setNo (timeLineRightTopLabel->currentNo ());
    currentFrameLabel->update ();

    for (int i = 0; i < layerNum; i++) {
        CTableItem * c = (CTableItem *) timeLineTable->item (i, timeLineRightTopLabel->currentNo () - 1);
        if (c) {
            c->layerChooser = true;
        }
                //              else c->layerChooser=false;
        timeLineTable->updateCell (i, timeLineRightTopLabel->currentNo () - 1);
    }
}

/** this works when user click on listbox items */
void CTimeLine::slotListViewClicked (Q3ListViewItem * item)
{
        //QHeader* hed=timeLineTable->horizontalHeader ();//(,true);
        //hed->sectionClicked (0);
        //CListBoxItem *p=(CListBoxItem*)item;
        //cout<<p->indis()<<endl;
        // CListBoxItem* item1=(CListBoxItem*) timeLineListbox->firstItem ();

        //      for ( unsigned int i = 0; i < timeLineListbox->count(); i++ ){
        //      CListBoxItem *item =(CListBoxItem *) timeLineListbox->item( i );
        //QPainter pai(/*dynamic_cast<QListBoxItem*>*/(QPaintDevice *)timeLineListbox);
    /*if ( item->isSelected() ) {
           //   cout<<i<<" "<<item->rtti()<<endl;
       } */
        //timeLineListbox->updateItem(item);
        //cout<<item->height (timeLineListbox)<<endl;
        //item->paint(&pai);
        //      }
        //timeLineListbox->triggerUpdate(true);
        //timeLineListbox->updateItem();
        //      cout<<timeLineListbox->itemHeight (0)<<endl;
        //timeLineListbox->repaint();
}

void CTimeLine::slotLabelMove (int x, int y)
{
        //if(x%8)timeLineRightTopLabel->setWidthMine((x%8));
        //timeLineRightTopLabel->setWidthMine(baseforleftlabel->viewport()->width());
        //qDebug(QString::number(baseforleftlabel->size().width()));
        //timeLineRightTopLabel->update();
}

void CTimeLine::slotInsertFrame (int row, int col)
{
//        qDebug("layernum: %d row: %d col: %d",layerNum,row,col);
    CTimeLineDataStructure * temp = layerFrames->at (row);
    if (temp->name == row + 1) {
        if (temp->frames->last ()->tableItemNo <= col) {
            if (temp->frames->last ()->tableItemNo == col) {
                CTimeLineNodes * _new = new CTimeLineNodes (temp->frames->last ()->tableItemNo + 1);
                temp->frames->append (_new);
            } else {
                CTimeLineNodes * tab = temp->frames->last ();
                for (int i = tab->tableItemNo; i <= col; i++) {
                    CTimeLineNodes * _new = new CTimeLineNodes (i);
                    temp->frames->append (_new);
                }
            }
        } else {
            CTimeLineNodes * _new = new CTimeLineNodes (temp->frames->last ()->tableItemNo + 1);
            temp->frames->append (_new);
        }
        if (temp->frames->last ()->tableItemNo >= layerMaxColNum)
            layerMaxColNum = temp->frames->last ()->tableItemNo + 1;
        adding = true;
        dad->slotCurrentView ()->slotInsertFrame (row, col);
        tableRefresh ();
    }
}

void CTimeLine::tableRefresh ()
{
    CTimeLineDataStructure * p = layerFrames->first ();
    if (adding) {
        for (; p; p = layerFrames->next ()) {
                        CTimeLineNodes * tab;	//=p->frames->first();
            for (int i = 0; i <= p->frames->count () - 1; i++) {
                tab = p->frames->at (i);
                if (tab != NULL) {
                    CTableItem * c = (CTableItem *) timeLineTable->item (p->name - 1, tab->tableItemNo);
                                        //if(c->ready) col++; else
                    tab->ready = true;
                    c->ready = tab->ready;
                    /*if(c->keyFrameEnd){
                       CTableItem* t=(CTableItem*)timeLineTable->item(row,i+1);
                                           //t->keyFrameStart=true;
                       c->keyFrameEnd=false;
                       } */
                    if (c->keyFrameEnd == true)
                        c->keyFrameEnd = false;
                    if (p->frames->at (tab->tableItemNo) != 0
                            && tab->tableItemNo == p->frames->last ()->tableItemNo) {
                        tab->keyFrameEnd = true;
                        c->keyFrameEnd = tab->keyFrameEnd;
//qDebug("frame no: %d",c->frameNo);
                    }
                    timeLineTable->updateCell (p->name - 1, tab->tableItemNo);
                }
                                //qDebug("%d",tab->tableItemNo);
            }
        }
    } else {
        CTableItem * c = (CTableItem *) timeLineTable->item (p->name - 1,p->frames->last ()->tableItemNo +1);
        c->ready = false;
        c->keyFrameEnd = false;
        timeLineTable->updateCell (p->name - 1, p->frames->last ()->tableItemNo + 1);
        CTableItem * d = (CTableItem *) timeLineTable->item (p->name - 1, p->frames->last ()->tableItemNo);
        d->ready = true;
        d->keyFrameEnd = true;
//qDebug("frame no: %d",d->frameNo);
        timeLineTable->updateCell (p->name - 1, p->frames->last ()->tableItemNo);
    }
	bool layerChanged=false;
	CListViewItem *tmpListViewItem=(CListViewItem*)timeLineListbox->selectedItem();
	int animX=dad->tl->layerFrames->at(tmpListViewItem->m_Row-1)->frames->last ()->tableItemNo;
	int z=-1*tmpListViewItem->m_Row;

        Q3CanvasItemList l=dad->slotCurrentView()->mainCanvas->allItems();
            for (Q3CanvasItemList::Iterator it = l.begin (); it != l.end ();++it) {
                if ((*it)->rtti () == 666 || (*it)->rtti () == 667) {		//if user clicked on def. scene rect. then dont select it.
                    continue;
                }
                switch((*it)->rtti()){
                case Q3CanvasItem::Rtti_Ellipse:
                    {
                        CCanvasEllipse *oval=(CCanvasEllipse*)(*it);
                        if(oval->Row==z){
                            layerChanged=true;
                        }
                    }
                    break;
                case Q3CanvasItem::Rtti_Line:
                    {
                        CCanvasLine *line=(CCanvasLine*)(*it);
                        if(line->Row==z)
                            layerChanged=true;
                    }
                    break;
                case Q3CanvasItem::Rtti_Polygon:

                    break;
                case Q3CanvasItem::Rtti_PolygonalItem:
                    {
                        CPencilLine *poly=(CPencilLine*)(*it);
                        if(poly->Row==z)
                            layerChanged=true;
                    }
                    break;
                case Q3CanvasItem::Rtti_Rectangle:
                    {
                        CCanvasRectangle *rect=(CCanvasRectangle*)(*it);
                        if(rect->Row==z)
                            layerChanged=true;
                    }
                    break;
                case Q3CanvasItem::Rtti_Spline:
                    break;
                case Q3CanvasItem::Rtti_Sprite:
                    break;
                case Q3CanvasItem::Rtti_Text:
                    {
                        CCanvasText *text=(CCanvasText*)(*it);
                        if(text->Row==z)
                            layerChanged=true;
                    }
                    break;
		}
            }

	if(layerChanged){
		for(int i=0;i<animX;i++){
			CTableItem *d = (CTableItem *) timeLineTable->item (tmpListViewItem->m_Row-1,i);
			d->filled=true;
		}
	}

}

void CTimeLine::slotRemoveFrame (int row, int col)
{
    CTimeLineDataStructure * temp = layerFrames->at (row);
    if (temp->name == row + 1) {
        if (temp->frames->last ()->tableItemNo >= col) {
            if (temp->frames->last ()->tableItemNo == col) {
                temp->frames->removeLast ();
            } else {
                temp->frames->removeLast ();
            }
        }
                //if(temp->frames->last()->tableItemNo<=layerMaxColNum)layerMaxColNum--;
                //adding=false;
                //tableRefresh();
        CTableItem * c =(CTableItem *) timeLineTable->item (temp->name - 1, temp->frames->last ()->tableItemNo + 1);
        c->ready = false;
        c->keyFrameEnd = false;

        timeLineTable->updateCell (temp->name - 1,temp->frames->last ()->tableItemNo + 1);

        CTableItem * d =(CTableItem *) timeLineTable->item (temp->name - 1,temp->frames->last ()->tableItemNo);
        d->ready = true;
        d->keyFrameEnd = true;
        timeLineTable->updateCell (temp->name - 1,temp->frames->last ()->tableItemNo);

        int a = temp->frames->last ()->tableItemNo;
        for (temp = layerFrames->first (); temp; temp = layerFrames->next ()) {
            if (temp->frames->last ()->tableItemNo >= a) {
                a = temp->frames->last ()->tableItemNo;
            }
        }
        layerMaxColNum = a + 1;
    }
}


