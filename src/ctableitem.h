/***************************************************************************
              ctableitem.h  -  description
                 -------------------
    begin                : Sat Jun 28 2003
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

#ifndef CTABLEITEM_H
#define CTABLEITEM_H

#include <qtable.h>

/**for canvas status representation
  *@author özkan pakdil
  */
class CTableItem:public QTableItem
{
public:
        CTableItem (QTable * parent, EditType et, const QString & txt);	//:QTableItem(parent,et,txt){}
    ~CTableItem ();

    void paint (QPainter * p, const QColorGroup & cg, const QRect & cr,
            bool selected);
        bool filled;		//this is true when user draw something on the canvas
        bool ready;			//this is true when canvas is ready to use(but not filled).
        bool empty_keyframe;		//this is true when keyframe is empty
        bool keyFrameStart;		//when keyframe is a start
        bool keyFrameEnd;		//true when frame is end
        bool layerChooser;		//if top right layer choose chosed this column then this true
		bool motionTween;		//if layer choosed for motion tween
        unsigned int frameNo;		//holds the frame number.
};

#endif
