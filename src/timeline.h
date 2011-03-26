/****************************************************************************
**
** Created: Mon Jun 9 05:32:35 2003
**      by:  ozkanpakdil@users.sourceforge.net
**
****************************************************************************/

#ifndef CTimeLine_H
#define CTimeLine_H

#include <qvariant.h>
#include <qdialog.h>
#include <q3valuelist.h>
//Added by qt3to4:
#include <Q3GridLayout>
#include <Q3HBoxLayout>
#include <Q3VBoxLayout>
#include <Q3PtrList>
#include "table.h"
#include "clistbox.h"
#include "clabel.h"

/*
    *@author özkan pakdil
    turkish: bu class in olus sebebi alt da bulunan table listbox gibi widget larin dogru sekilde gosterimini
    saglamak. time line da gorulen button lar burda yazilacak.
    english: buttons at time line will be written here.
*/

class F4lmApp;
class Q3VBoxLayout;
class Q3HBoxLayout;
class Q3GridLayout;
class Q3ButtonGroup;
class Q3ListBox;
class Q3ListBoxItem;
class QSplitter;
class Q3Table;
class QToolButton;
class Q3ListView;
class CBase;

/// table cell's position inside time line
class CTimeLineNodes:public QObject
{
    Q_OBJECT
public:
    CTimeLineNodes (int tabno){
        tableItemNo = tabno;
    }
        int tableItemNo;		//used for tableItem
        bool filled;			//this is true when user draw something on the canvas
        bool ready;			//this is true when canvas is ready to use(but not filled).
        bool empty_keyframe;		//this is true when keyframe is empty
        bool keyFrameStart;		//when keyframe is a start of tween
        bool keyFrameEnd;		//true when frame is end of tween
        bool layerChooser;		//if top right layer choose chosed this column then this true
        unsigned int frameNo;		//holds the frame number.
};

/// used for time line canvas representation datas.
class CTimeLineDataStructure:public QObject
{
    Q_OBJECT
public:
    CTimeLineDataStructure (int isim)
    {
        name = isim;
        frames = new Q3PtrList < CTimeLineNodes >;
        frames->setAutoDelete (true);
    }
    int name;
    Q3PtrList < CTimeLineNodes > *frames;

};



/// collects some other classes and show us flash's time line window
class CTimeLine:public QWidget
{
    Q_OBJECT

public:
    CTimeLine (QWidget * parent = 0, const char *name = 0, bool modal = FALSE, Qt::WFlags fl = 0);
    ~CTimeLine ();
    QSplitter * Splitter1;
    CLabel * timeLineLeftTopLabel;
    /*QListView* */
    CListView * timeLineListbox;
    Q3ButtonGroup * timeLineLeftButtonGroup;
    QToolButton * NewLayer;
    QToolButton * NewWayLayer;
    QToolButton * NewLayerFolder;
    QToolButton * DeleteLayer;
    CLabel * timeLineRightTopLabel;
    CLabel * currentFrameLabel;//timeline's specific label
    CLabel * totalTimeLabel;
    CTable * timeLineTable;
    Q3ButtonGroup * timeLineRightButtonGroup;
    QToolButton * ToolButton6;
    QToolButton * ToolButton7;
    QToolButton * ToolButton8;
    QScrollBar * VScrollBar1;
    QScrollBar * HScrollBar1;
    CBase * baseforleftlabel;
    F4lmApp * dad;
//benimde f4lde bir sat?r?m var..Cem
    Q3PtrList < CTimeLineDataStructure > *layerFrames;
    bool adding;			//if adding happened this is true otherwise false
    int layerNum;		//think this as a row number
    int tableColNum;		//table width or table column number
    int layerMaxColNum;		//this holds left end range for righttoplabel. Can change with just inserting new canvases

protected:
    Q3VBoxLayout * Layout2;
    Q3VBoxLayout * Layout3;

public slots:			// Public slots
    void tableRefresh ();

    /** When click on newlayer button works */
    void slotNewLayer ();

    /** No descriptions */
    void slotTableHscrollmove (int);

    /** No descriptions */
    void slotTableVscrollmove (int);

    void slotLabelclick ();

    /** this works when user click on listView items */
    void slotListViewClicked (Q3ListViewItem *);

    /** this will scroll the left label*/
    void slotLabelMove (int x, int y);

    /** this slot inserts frames into given row*/
        void slotInsertFrame (int row, int col);	//this adds available (ready to write) cells into table.
        void slotRemoveFrame (int row, int col);	//removes selected frame

};
#endif // CTimeLine_H
