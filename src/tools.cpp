/****************************************************************************
** Form implementation generated from reading ui file 'tools.ui'
**
** Created: Mon Jun 9 06:20:51 2003
**      by:  ozkanpakdil@users.sourceforge.net
**
****************************************************************************/

#include "f4lm.h"
#include "tools.h"
#include "colorpopup.h"

#include <qvariant.h>
#include <q3buttongroup.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qimage.h>
#include <q3whatsthis.h>
#include <qlabel.h>
#include <qcolordialog.h>
//Added by qt3to4:
#include <Q3HBoxLayout>
#include <QPixmap>
#include <QEvent>
#include <Q3VBoxLayout>

#include "cursor/arrow_tool.xpm"
#include "cursor/lasso_tool.xpm"
#include "cursor/sub_selection_tool.xpm"
#include "cursor/text_tool.xpm"
#include "cursor/rectangle_tool.xpm"
#include "cursor/paint_bucket_tool.xpm"
#include "cursor/pencil_tool.xpm"
#include "cursor/ink_bottle_tool.xpm"
#include "cursor/oval_tool.xpm"
#include "cursor/pen_tool.xpm"
#include "cursor/line_tool.xpm"
#include "cursor/brush_tool.xpm"
#include "cursor/free_transform_tool.xpm"
#include "cursor/fill_transform_tool.xpm"
#include "cursor/eye_dropper_tool.xpm"
#include "cursor/eraser_tool.xpm"
#include "cursor/hand_tool.xpm"
#include "cursor/zoom_tool.xpm"
#include "./cursor/colorComboBoxButton.xpm"

CTools::CTools (QWidget * parent, const char *name, Qt::WFlags fl,
        F4lmApp * realp)
        :
        QWidget (parent, name, fl)
{
    if (!name)
        setName ("Tools");
    resize (600, 480);
    setCaption (trUtf8 ("Tools"));
    dad = (F4lmApp *) realp;
    Q3VBoxLayout * topLayout = new Q3VBoxLayout (this);
        //QVBoxLayout *layer1=new QVBoxLayout(this);
    ToolsButtonGroup = new Q3ButtonGroup (this, "ToolsButtonGroup");
        //ToolsButtonGroup->setGeometry( QRect( 150, 70, 71, 291 ) );
    ToolsButtonGroup->setLineWidth (2);
    ToolsButtonGroup->setTitle (trUtf8 (""));
    ToolsButtonGroup->setExclusive (true);

        //      DeleteLayer->setIconSet(QIconSet( QPixmap (( const char** ) delete_layer_xpm)));
        //  DeleteLayer->setTextLabel( trUtf8( "Delete Layer" ) );

    Q3VBoxLayout * layer1 = new Q3VBoxLayout (ToolsButtonGroup);
    QLabel * toolsLabel = new QLabel (ToolsButtonGroup, "Tools");
    toolsLabel->setText (tr ("   Tools"));
    layer1->addWidget (toolsLabel);
    Q3HBoxLayout * layer2 = new Q3HBoxLayout (layer1);
    ArrowTool =new CToolButton (ToolsButtonGroup,tr("Use the Arrow to select  drag and reshape the drawing"));
    ArrowTool->setIconSet (QIcon (QPixmap ((const char **) arrow_tool_xpm)));
    ArrowTool->setTextLabel (trUtf8 ("Arrow Tool"));
    SubSelectionTool =new CToolButton (ToolsButtonGroup,tr("Use the Subselect tool to select  drag and reshape the drawing using handles"));
    SubSelectionTool->setIconSet (QIcon (QPixmap ((const char **) sub_selection_tool_xpm)));
    SubSelectionTool->setTextLabel (trUtf8 ("Subselection Tool"));
    layer2->addWidget (ArrowTool);
    layer2->addWidget (SubSelectionTool);

    Q3HBoxLayout * layer3 = new Q3HBoxLayout (layer1);
    LineTool =new CToolButton (ToolsButtonGroup,tr ("Use the Line tool  to draw lines"));
    LineTool->setIconSet (QIcon (QPixmap ((const char **) line_tool_xpm)));
    LineTool->setTextLabel (trUtf8 ("Line Tool"));
    LassoTool =new CToolButton (ToolsButtonGroup,tr ("Use the Lasso to select areas of the drawing"));
    LassoTool->setIconSet (QIcon (QPixmap ((const char **) lasso_tool_xpm)));
    LassoTool->setTextLabel (trUtf8 ("Lasso Tool"));
	
    layer3->addWidget (LineTool);
    layer3->addWidget (LassoTool);

    Q3HBoxLayout * layer4 = new Q3HBoxLayout (layer1);
    PenTool =new CToolButton (ToolsButtonGroup,tr ("Use the Pen tool to draw lines and curves"));
    PenTool->setIconSet (QIcon (QPixmap ((const char **) pen_tool_xpm)));
    PenTool->setTextLabel (trUtf8 ("Pen Tool"));
    TextTool =new CToolButton (ToolsButtonGroup,tr("Use the Text tool to create and edit formated text"));
    TextTool->setIconSet (QIcon (QPixmap ((const char **) text_tool_xpm)));
    TextTool->setTextLabel (trUtf8 ("Text Tool"));
    layer4->addWidget (PenTool);
    layer4->addWidget (TextTool);

    Q3HBoxLayout * layer5 = new Q3HBoxLayout (layer1);
    OvalTool =new CToolButton (ToolsButtonGroup,tr ("Use the Oval  tool  to draw oval shapes"));
    OvalTool->setIconSet (QIcon (QPixmap ((const char **) oval_tool_xpm)));
    OvalTool->setTextLabel (trUtf8 ("Oval Tool"));
    RectangleTool =new CToolButton (ToolsButtonGroup,tr("Use the Rectangle tool to draw rectangles and rounded rectangles"));
    RectangleTool->setIconSet (QIcon (QPixmap ((const char **) rectangle_tool_xpm)));
    RectangleTool->setTextLabel (trUtf8 ("Rectangle Tool"));
    layer5->addWidget (OvalTool);
    layer5->addWidget (RectangleTool);

    Q3HBoxLayout * layer6 = new Q3HBoxLayout (layer1);
    PencilTool =new CToolButton (ToolsButtonGroup,tr ("Use the Pencil to draw lines and shapes"));
    PencilTool->setIconSet (QIcon (QPixmap ((const char **) pencil_tool_xpm)));
    PencilTool->setTextLabel (trUtf8 ("Pencil Tool"));
    BrushTool =new CToolButton (ToolsButtonGroup,tr ("Use the Brush to paint filled areas"));
    BrushTool->setIconSet (QIcon (QPixmap ((const char **) brush_tool_xpm)));
    BrushTool->setTextLabel (trUtf8 ("Brush Tool"));
    layer6->addWidget (PencilTool);
    layer6->addWidget (BrushTool);

    Q3HBoxLayout * layer7 = new Q3HBoxLayout (layer1);

    FreeTransformTool =new CToolButton (ToolsButtonGroup,tr("Use Free Transform to select  drag and reshape the drawing"));

    FreeTransformTool->setIconSet (QIcon (QPixmap ((const char **) free_transform_tool_xpm)));
    FreeTransformTool->setTextLabel (trUtf8 ("Free Transform Tool"));
    FillTransformTool =new CToolButton (ToolsButtonGroup,tr("Fill Transform shows handles to adjust the angle  position and size of a gradient or bitmap fill"));

    FillTransformTool->setIconSet (QIcon (QPixmap ((const char **) fill_transform_tool_xpm)));
    FillTransformTool->setTextLabel (trUtf8 ("Fill Transform Tool"));
	
    layer7->addWidget (FreeTransformTool);
    layer7->addWidget (FillTransformTool);

        /////////////////////tansformatin tools waiting for future works :)///////////////////////
    FreeTransformTool->hide ();
    FillTransformTool->hide ();

    Q3HBoxLayout * layer8 = new Q3HBoxLayout (layer1);
    InkBottleTool =new CToolButton (ToolsButtonGroup,tr("Use the Ink Bottle to apply line color and thickness to the drawing"));

    InkBottleTool->setIconSet (QIcon (QPixmap ((const char **) ink_bottle_tool_xpm)));
    InkBottleTool->setTextLabel (trUtf8 ("Ink Bottle Tool"));
    PaintBucketTool =new CToolButton (ToolsButtonGroup,tr("Use the Paint Bucket to fill enclosed areas of the drawing with color"));

    PaintBucketTool->setIconSet (QIcon (QPixmap ((const char **) paint_bucket_tool_xpm)));
    PaintBucketTool->setTextLabel (trUtf8 ("Paint Bucket Tool"));
    layer8->addWidget (InkBottleTool);
    layer8->addWidget (PaintBucketTool);

    Q3HBoxLayout * layer9 = new Q3HBoxLayout (layer1);
    EyedropperTool =new CToolButton (ToolsButtonGroup,tr("Use the Dropper to pick up line  fill and text styles from the drawing"));

    EyedropperTool->setIconSet (QIcon (QPixmap ((const char **) eye_dropper_tool_xpm)));
    EyedropperTool->setTextLabel (trUtf8 ("Eye Dropper Tool"));
    EraserTool =new CToolButton (ToolsButtonGroup,tr("Use the Eraser to erase lines and fills in the drawing"));
    EraserTool->setIconSet (QIcon (QPixmap ((const char **) eraser_tool_xpm)));
    EraserTool->setTextLabel (trUtf8 ("Eraser Tool"));
    layer9->addWidget (EyedropperTool);
    layer9->addWidget (EraserTool);

        //ToolsViewGroup = new QButtonGroup( this, "ToolsButtonGroup" );
        //ToolsViewGroup->setExclusive(true);
    QLabel * viewLabel = new QLabel (ToolsButtonGroup, "View");
    viewLabel->setText (tr ("   View"));
    Q3VBoxLayout * layer10 = new Q3VBoxLayout (layer1);
    layer10->addWidget (viewLabel);
    HandTool =new CToolButton (ToolsButtonGroup,tr ("Use the Hand  to move the view of the drawing"));
    HandTool->setIconSet (QIcon (QPixmap ((const char **) hand_tool_xpm)));
    HandTool->setTextLabel (trUtf8 ("Hand Tool"));
	
    ZoomTool =new CToolButton (ToolsButtonGroup,tr("Use the Magnifer to enlarge or reduce the view of the drawing"));
    ZoomTool->setIconSet (QIcon (QPixmap ((const char **) zoom_tool_xpm)));
    ZoomTool->setTextLabel (trUtf8 ("Zoom Tool"));
	
    Q3HBoxLayout * layer11 = new Q3HBoxLayout (layer10);
    layer11->addWidget (HandTool);
    layer11->addWidget (ZoomTool);

    ToolsColorsGroup = new Q3ButtonGroup (this, "ToolsColorsGroup");
    ToolsColorsGroup->setExclusive (true);
    QLabel * colorsLabel = new QLabel (ToolsColorsGroup, "Colors");
    colorsLabel->setText ("   Colors");
    Q3VBoxLayout * layer12 = new Q3VBoxLayout (ToolsColorsGroup);
    layer12->addWidget (colorsLabel);
    StrokeColor = new CToolButton (ToolsColorsGroup);
    /*strokpix.resize(16,16);
       strokpix.load("./cursor/colorComboBoxButton.xpm");
       strokpix.fill(QColor(0,0,0)); */
    QImage * str = new QImage ((const char **) colorComboBoxButton);
    strokpix.convertFromImage (*str);
    fillpix.resize (16, 16);
    fillpix.fill (QColor (0, 0, 0));
    StrokeColor->setIconSet (QIcon (strokpix));
    StrokeColor->setTextLabel (trUtf8 ("Stroke Color"));
    FillColor = new CToolButton (ToolsColorsGroup);
    FillColor->setIconSet (QIcon (fillpix));
    FillColor->setTextLabel (trUtf8 ("Fill Color"));
        //QHBoxLayout *layer13=new QHBoxLayout(layer12);
    layer12->addWidget (StrokeColor);
    layer12->addWidget (FillColor);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////burdaki buttonlar henüz iþlenmemiþtir. kafadan yazýldý o kadar.//////////////////////////////////////////////////////
    Q3ButtonGroup * ToolsOptionsGroup =new Q3ButtonGroup (this, "ToolsOptionsGroup");
    ToolsOptionsGroup->setExclusive (true);
    QLabel * optionsLabel = new QLabel (ToolsOptionsGroup, "Colors");
    optionsLabel->setText (tr ("   Options"));
    Q3VBoxLayout * layer13 = new Q3VBoxLayout (ToolsOptionsGroup);
    layer13->addWidget (optionsLabel);
    /*    QToolButton *_StrokeColor= new CToolButton( ToolsOptionsGroup);
    	strokpix.resize(16,16);
    	strokpix.fill(QColor(0,0,0));
    	fillpix.resize(16,16);
    	fillpix.fill(QColor(0,0,0));
    	_StrokeColor->setIconSet(QIconSet( strokpix));
    	_StrokeColor->setTextLabel( trUtf8( "Stroke Color" ) );
        QToolButton *_FillColor= new CToolButton( ToolsOptionsGroup);
        _FillColor->setIconSet(QIconSet( fillpix));
    	_FillColor->setTextLabel( trUtf8( "Fill Color" ) );
    	_StrokeColor->setToggleButton(true);
    	_FillColor->setToggleButton(true);
        	//QHBoxLayout *layer13=new QHBoxLayout(layer12);
    	layer13->addWidget(_StrokeColor);
    	layer13->addWidget(_FillColor); */

    topLayout->addWidget (ToolsButtonGroup);
    topLayout->addWidget (ToolsColorsGroup);
    topLayout->addWidget (ToolsOptionsGroup);

    connect (ArrowTool, SIGNAL (clicked ()), this, SLOT (slotArrowTool ()));
    connect (SubSelectionTool, SIGNAL (clicked ()), this,SLOT (slotSubSelectionTool ()));
    connect (LineTool, SIGNAL (clicked ()), this, SLOT (slotLineTool ()));
    connect (LassoTool, SIGNAL (clicked ()), this, SLOT (slotLassoTool ()));
    connect (PenTool, SIGNAL (clicked ()), this, SLOT (slotPenTool ()));
    connect (TextTool, SIGNAL (clicked ()), this, SLOT (slotTextTool ()));
    connect (OvalTool, SIGNAL (clicked ()), this, SLOT (slotOvalTool ()));
    connect (RectangleTool, SIGNAL (clicked ()), this,SLOT (slotRectangleTool ()));
    connect (PencilTool, SIGNAL (clicked ()), this, SLOT (slotPencilTool ()));
    connect (BrushTool, SIGNAL (clicked ()), this, SLOT (slotBrushTool ()));
    connect (FreeTransformTool, SIGNAL (clicked ()), this,SLOT (slotFreeTransformTool ()));
    connect (FillTransformTool, SIGNAL (clicked ()), this,SLOT (slotFillTransformTool ()));
    connect (InkBottleTool, SIGNAL (clicked ()), this,SLOT (slotInkBottleTool ()));
    connect (PaintBucketTool, SIGNAL (clicked ()), this,SLOT (slotPaintBucketTool ()));
    connect (EyedropperTool, SIGNAL (clicked ()), this,SLOT (slotEyedropperTool ()));
    connect (EraserTool, SIGNAL (clicked ()), this, SLOT (slotEraserTool ()));
    connect (HandTool, SIGNAL (clicked ()), this, SLOT (slotHandTool ()));
    connect (ZoomTool, SIGNAL (clicked ()), this, SLOT (slotZoomTool ()));
    connect (StrokeColor, SIGNAL (clicked ()), this,SLOT (slotStrokeColor ()));
    connect (FillColor, SIGNAL (clicked ()), this, SLOT (slotFillColor ()));

        ////down part for buttons can toggle
    ArrowTool->setToggleButton (true);
    SubSelectionTool->setToggleButton (true);
    LineTool->setToggleButton (true);
    LassoTool->setToggleButton (true);
    PenTool->setToggleButton (true);
    TextTool->setToggleButton (true);
    OvalTool->setToggleButton (true);
    RectangleTool->setToggleButton (true);
    PencilTool->setToggleButton (true);
    BrushTool->setToggleButton (true);
    FreeTransformTool->setToggleButton (true);
    FillTransformTool->setToggleButton (true);
    InkBottleTool->setToggleButton (true);
    PaintBucketTool->setToggleButton (true);
    EyedropperTool->setToggleButton (true);
    EraserTool->setToggleButton (true);
    HandTool->setToggleButton (true);
    ZoomTool->setToggleButton (true);
    StrokeColor->setToggleButton (true);
    FillColor->setToggleButton (true);

    swatchesCarrier =new CColorPopup (this, "Color swatches Carrier",Qt::WType_Popup | Qt::WStyle_DialogBorder);
    swatchesCarrier->hide ();
    swatchesCarrier->setFocus ();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CTools::~CTools (){
        // no need to delete child widgets, Qt does it all for us
}

void CTools::slotArrowTool ()
{
    dad->setDefObjID (1);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotSubSelectionTool ()
{
    dad->setDefObjID (2);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotLineTool ()
{
    dad->setDefObjID (3);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotLassoTool ()
{
    dad->setDefObjID (4);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotPenTool ()
{
    dad->setDefObjID (5);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotTextTool ()
{
    dad->setDefObjID (6);
    dad->properties->hideBrushProperties ();
    dad->properties->showFontProperties ();
}

void CTools::slotOvalTool ()
{
    dad->setDefObjID (7);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotRectangleTool ()
{
    dad->setDefObjID (8);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotPencilTool ()
{
    dad->setDefObjID (9);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotBrushTool ()
{
    dad->setDefObjID (10);
    dad->properties->hideFontProperties ();
    dad->properties->showBrushProperties ();
}

void CTools::slotFreeTransformTool ()
{
    dad->setDefObjID (11);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotFillTransformTool ()
{
    dad->setDefObjID (12);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotInkBottleTool ()
{
    dad->setDefObjID (13);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotPaintBucketTool ()
{
    dad->setDefObjID (14);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotEyedropperTool ()
{
    dad->setDefObjID (15);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotEraserTool ()
{
    dad->setDefObjID (16);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotHandTool ()
{
    dad->setDefObjID (17);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotZoomTool ()
{
    dad->setDefObjID (18);
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotStrokeColor ()
{
    /*QPopupMenu* renkicin = new QPopupMenu (this);
       renkicin->insertItem ("Create Motion Tween");
       renkicin->insertItem(swatchesCarrier);
       renkicin->insertSeparator(); */
    swatchesCarrier->move (mapToGlobal (StrokeColor->pos () * 5));
    swatchesCarrier->resize (230, 170);
    swatchesCarrier->show ();
        //grabMouse();
        //releaseMouse();
        //      grabKeyboard();
        //renkicin->exec();
        //qDebug("stroke button y: %d",StrokeColor->y());
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

void CTools::slotFillColor ()
{
    swatchesCarrier->move (mapToGlobal (FillColor->pos () * 3));
    swatchesCarrier->resize (230, 170);
    swatchesCarrier->show ();
    dad->properties->hideFontProperties ();
    dad->properties->hideBrushProperties ();
}

/////////////////////////////////////////////////////////////
CToolButton::CToolButton (QWidget * parent, const char *name):
        QToolButton (parent, name){
    dad = (CTools *) parent->parent ();
}

void CToolButton::enterEvent (QEvent *){
    dad->dad->statusBar ()->message (name ());
}

void CToolButton::leaveEvent (QEvent *){
    dad->dad->statusBar ()->message ("Ready.");
}






