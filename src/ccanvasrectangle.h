/***************************************************************************
 *   Copyright (C) 2005 by Özkan Pakdil                                    *
 *                                                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef CCANVASRECTANGLE_H
#define CCANVASRECTANGLE_H

#include <qcanvas.h>

/**
same with other canvas items

@author Ökan Pakdil
*/
class CCanvasRectangle : public QCanvasRectangle
{
public:
    CCanvasRectangle(int x, int y, int width, int height, QCanvas * canvas);

    ~CCanvasRectangle();
	int Row;///this will be the Z dimension for object
	int Col;///this is frame for object.
	int animationX;///this is the frame number of object.
};

#endif
