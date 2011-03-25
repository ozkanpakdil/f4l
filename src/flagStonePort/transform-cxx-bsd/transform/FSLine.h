/*
 *  FSLine.h
 *  Transform SWF
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

#ifndef __FSLine_h__
#define __FSLine_h__ 1

#include "FSShapeObject.h"

namespace transform
{
/**
 * %FSLine defines a straight line. 
 * 
<p>The line is drawn from the current drawing point to the end point specified in the FSLine object which is specified relative to the current drawing point. Once the line is drawn, the end of the line is now the current drawing point.</P>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSLine_0">x</a></td>
<td>The x-coordinate of the end point of the line, relative to the current drawing point.</td>
</tr>

<tr>
<td><a name="FSLine_1">y</a></td>
<td>The y-coordinate of the end point of the line, relative to the current drawing point.</td>
</tr>

</table>

<p>The relative coordinates are specified in twips (where 20 twips = 1 pixel) and must be in the range -65536..65535.</p>

<p>Lines are drawn with rounded corners and line ends. Different join and line end styles can be created by drawing line segments as a sequence of filled shapes. With 1 twip equal to 1/20th of a pixel this technique can easily be used to draw the narrowest of visible lines.</p>

<h1 class="datasheet">History</h1>

<p>The FSLine class represents the StraightEdge record from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSLine : public FSShapeObject
    {
public:
        FSLine(FSInputStream* aStream);
        
        /** Constructs an FSLine with the specified coordinates relative to the current drawing point.

        @param xValue the x-coordinate of the end point, specified relative to the current drawing point.
        @param yValue the y-coordinate of the end point, specified relative to the current drawing point.
        */
        FSLine(int xValue, int yValue) : FSShapeObject(Line), x(0), y(0)
        {
            setX(xValue);
            setY(yValue);
        }

        FSLine* clone() const { return new FSLine(*this); }

        const char* className() const;

        /** Gets the relative x-coordinate. 

            @return the x-coordinate of the end point.
            */
        int getX() const
        {
            return x;
        }

        /** Gets the relative y-coordinate.

            @return the y-coordinate of the end point.
            */
        int getY() const
        {
            return y;
        }

        /** Sets the relative x-coordinate. 
        
            @param aNumber the x-coordinate of the end point.
            */
        void setX(int aNumber)
        {
            x = aNumber;
        }
    
        /** Sets the relative y-coordinate.
    
            @param aNumber the y-coordinate of the end point.
            */
        void setY(int aNumber)
        {
            y = aNumber;
        }

        /** Sets the relative x and y coordinates.

            @param xValue the x-coordinate of the end point.
            @param yValue the y-coordinate of the end point.
            */
        void setPoint(int xValue, int yValue)
        {
            x = xValue;
            y = yValue;
        }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool containsGeneralLine() const;
        bool containsVerticalLine() const;
        int fieldSize() const;

        int x;
        int y;
    };
} 

#endif
