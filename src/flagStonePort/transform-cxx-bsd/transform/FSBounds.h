/*
 *  FSBounds.h
 *  transform
 * 
 * Copyright (c) 2001-2004 Flagstone Software Ltd.. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *  * Neither the name of Flagstone Software Ltd. nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
#ifndef __FSBounds_h__
#define __FSBounds_h__ 1

#include "FSTransformObject.h"

namespace transform
{
/**
 * The %FSBounds class is used to define the area inside which shapes, text fields and 
 * characters are drawn.
 * 
<p>In Flash the axes are specified relative to the top left corner of the screen and the bounding area is defined by two pairs of coordinates that identify the top left and bottom right corners of a rectangle.</p>

<img src="bounds.gif">

<P><!-- blank paragraph to add space between the image and the next table --></P>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSBounds_0">minX</a></td>
<td>The x-coordinate of the upper left corner of the rectangle.</td>
</tr>

<tr>
<td><a name="FSBounds_1">minY</a></td>
<td>The y-coordinate of the upper left corner of the rectangle.</td>
</tr>

<tr>
<td><a name="FSBounds_2">maxX</a></td>
<td>The x-coordinate of the lower right corner of the rectangle.</td>
</tr>

<tr>
<td><a name="FSBounds_3">maxY</a></td>
<td>The y-coordinate of the lower right corner of the rectangle.</td>
</tr>

</table>

<p>The coordinates for each corner also specify the coordinate range so specifying 
a bounding rectangle with the points (-100,-100) and (100,100) defines a rectangle 
200 twips by 200 twips with the point (0,0) located in the centre. Specifying the 
points (0,0) and (200,200) defines a rectangle with the same size however the centre 
is now located at (100,100).</p>

<p>The bounding rectangle does not clip the object when it is drawn. Lines and curves 
drawn outside of the rectangle will still be displayed. However when the bounding 
rectangle is defined for an FSMovie object then this defines the size of the Flash 
Player screen and shapes drawn outside of the bounding rectangle will not be displayed.</p>

<h1 class="datasheet">Examples</h1>

<p>To create an FSBounds object simply specify the coordinates of the corners of the 
rectangle in the following order: top left x, top left y, bottom right x, bottom 
right y.</p>

<pre>
FSBounds bounds(0, 0, 100, 200);
</pre>

<p>Creates a bounding rectangle for an object which is 100 twips wide and 200 twips high. The coordinate range for the object is from 0..100 along the x-axis and 0..200 along the y-axis. The origin (0,0) will be at the top left corner of the object as it is displayed on the screen.

<pre>
FSBounds bounds (-100, -200, 100, 200);
</pre>

<p>Creates a bounding rectangle for an object which is 200 twips wide and 400 twips high. The coordinate range for the object is from -100..100 along the x-axis and -200..200 along the y-axis. The origin (0,0) will be in the middle of the object as it is displayed on the screen.

<h1 class="datasheet">History</h1>

<p>The FSBounds class corresponds to the RECT data type, in the Macromedia Flash 
(SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSBounds : public FSTransformObject
    {
    public:
        FSBounds(FSInputStream* aStream);

        FSBounds() : minX(0), minY(0), maxX(0), maxY(0) {}

        /** Constructs an FSBounds object representing a rectangle with the top left corner at (xl,yl) and bottom right corner at (xr,yr).

            @param xl x-coordinate of the top left corner.
            @param yl y-coordinate of the top left corner.
            @param xr x-coordinate of bottom right corner.
            @param yr y-coordinate of bottom right corner.
            */
        FSBounds(int xl, int yl, int xr, int yr) : minX(0), minY(0), maxX(0), maxY(0)
        {
            setMinX(xl);
            setMinY(yl);
            setMaxX(xr);
            setMaxY(yr);
        }

        FSBounds* clone() const { return new FSBounds(*this); }

        const char* className() const;

        /** Gets the x-coordinate of the top left corner of the bounding rectangle.
        
            @return the x-coordinate of the top left corner of the bounding rectangle.
            */
        int getMinX() const
        {
            return minX;
        }
    
        /** Sets the x-coordinate of the top left corner of the bounding rectangle.
            
            @param aNumber x-coordinate of the top left corner of the bounding rectangle.
            */
        void setMinX(int aNumber)
        {
            minX = aNumber;
        }
    
        /** Gets the x-coordinate of the bottom right corner of the bounding rectangle. 
            
            @return the x-coordinate of the bottom right corner of the bounding rectangle.
            */
        int getMaxX() const
        {
            return maxX;
        }

        /** Sets the x-coordinate of the bottom right corner of the bounding rectangle.
            
            @param aNumber x-coordinate of the bottom right corner of the bounding rectangle.
            */
        void setMaxX(int aNumber)
        {
            maxX = aNumber;
        }
    
        /** Gets the y-coordinate of the top left corner of the bounding rectangle.

            @return the y-coordinate of the top left corner of the bounding rectangle.
            */
        int getMinY() const
        {
            return minY;
        }

        /** Sets the y-coordinate of the top left corner of the bounding rectangle.
            
            @param aNumber y-coordinate of the top left corner of the bounding rectangle.
            */
        void setMinY(int aNumber)
        {
            minY = aNumber;
        }
    
        /** Gets the y-coordinate of the bottom right corner of the bounding rectangle.

            @return the y-coordinate of the bottom right corner of the bounding rectangle.
            */
        int getMaxY() const
        {
            return maxY;
        }

        /** Sets the y-coordinate of the bottom right corner of the bounding rectangle.
            
            @param aNumber x-coordinate of the bottom right corner of the bounding rectangle.
            */
        void setMaxY(int aNumber)
        {
            maxY = aNumber;
        }

        /** Gets the width of the rectangle.

            @return the width of the rectangle.
            */
        int getWidth() const
        {
            int width = maxX - minX;

            return width;
        }

        /** Gets the height of the rectangle. 

            @return the height of the rectangle.
            */
        int getHeight() const
        {
            int height = maxY - minY;

            return height;
        }        

        /** Sets the x and y coordinates of the lower corner.

            @param xl the x-coordinate of the top left corner point.
            @param yl the y-coordinate of the top left corner point.
            */
        void setMin(int xl, int yl)
        {
            minX = xl;
            minY = yl;
        }

        /** Sets the x and y coordinates of the upper corner.

            @param xr the x-coordinate of the bottom right corner point.
            @param yr the y-coordinate of the bottom right corner point.
            */
        void setMax(int xr, int yr)
        {
            maxX = xr;
            maxY = yr;
        }

        /** Sets the x and y coordinates of the lower and upper corner point.

            @param xl the x-coordinate of the top left corner point.
            @param yl the y-coordinate of the top left corner point.
            @param xr the x-coordinate of the bottom right corner point.
            @param yr the y-coordinate of the bottom right corner point.
            */
        void setPoints(int xl, int yl, int xr, int yr)
        {
            minX = xl;
            minY = yl;
            maxX = xr;
            maxY = yr;
        }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    
    private:
        int fieldSize() const;

        int minX;
        int minY;
        int maxX;
        int maxY;
    };
} 

#endif
