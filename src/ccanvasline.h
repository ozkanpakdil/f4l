#ifndef CCANVASLINE_H
#define CCANVASLINE_H

#include <qobject.h>
#include <q3canvas.h>

/**
using for setVisible(FALSE) in some frame object should be unvisible.

@author Özkan Pakdil
*/
class CCanvasLine:public Q3CanvasLine 
{
public:
    CCanvasLine(Q3Canvas *canvas);

    ~CCanvasLine();
	
			
	int Row;///this will be the Z dimension for object
	int Col;///this is frame for object.
	int animationX;///this is the frame number of object.
};

#endif
