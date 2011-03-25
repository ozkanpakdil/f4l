/*
 *  FSSolidLine.h
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

#ifndef __FSSolidLine_h__
#define __FSSolidLine_h__ 1

#include "FSLineStyle.h"

#include "FSColor.h"

namespace transform
{
/**
 * %FSSolidLine defines the width and colour of a line that is used when drawing the outline of a shape.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSSolidLine_0">width</a></td>
<td>The width of the line drawn in twips.</td>
</tr>

<tr><td><a name="FSSolidLine_1">color</a></td>
<td>The colour used to draw the line.</td>
</tr>

</table>

<p>All lines are drawn with rounded corners and end caps. Different join and line end styles can be created by drawing line segments as a sequence of filled shapes. With 1 twip equal to 1/20th of a pixel this technique can easily be used to draw the narrowest of visible lines.</p>

<p>Whether the alpha channel in the colour is used is determined by the class used to define the shape. Transparent colours are only supported from Flash 3 onwards. Simply specifying the level of transparency in the FSColor object is not sufficient.</p>

<h1 class="datasheet">Examples</h1>

<pre>
FSSolidLine* lineStyle = new FSSolidLine(20, FSColor(0, 0, 0));
</pre>

<p>Draws a black line, 1 pixel wide.</p>

<pre>
FSSolidLine* lineStyle = new FSSolidLine(20, FSColor(255, 0, 0, 128));
</pre>

<p>Draws a transparent red line, 1 pixel wide. If the alpha channel is not specified then the value defaults to 255 generating a completely opaque colour.</p>

<p>Flash only supports contiguous lines. Dashed line styles can be created by drawing the line as a series of short line segments by interspersing FSShapeStyle objects to move the current point in between the FSLine objects that draw the line segments.</p>

<pre>
// define the line style
lineStyles.push_back(new FSSolidLine(20, FSColor(0, 0, 0)));

// Select the line style
shape.push_back(new FSShapeStyle(1, 0, 0));

// Draw the dashed line with lines and gaps each 5 pixels long
shape.push_back(new FSShapeStyle(1, 0, 0));

for (int i=0; i&lt;10; i++)
{
    shape.push_back(new FSLine(100, 0));
    shape.push_back(new FSShapeStyle(0, 0, 0));
    shape.push_back(new FSLine(100, 0));
}
</pre>

<h1 class="datasheet">History</h1>

<p>The FSSolidLine class represents the LineStyle structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1. Support for transparent colours was added in Flash 3.</p>

 */
    class DLL_DECL FSSolidLine : public FSLineStyle
    {
public:
        FSSolidLine(FSInputStream* aStream);

        /** Constructs an FSSolidLine, specifying the width and colour of the line. 

            @param aWidth the width of the line.
            @param aColor the colour of the line.
        */
        FSSolidLine(int aWidth, const FSColor& aColor) : width(0), color(aColor)
        {
            setWidth(aWidth);
        }

        FSSolidLine* clone() const { return new FSSolidLine(*this); }

        const char* className() const;

        /**  Gets the width of the line. 

            @return the width of the line.
            */
        int getWidth() const
        {
            return width;
        }

        /** Gets the colour of the line.

            @return the colour for the line.
            */
        FSColor& getColor() { return color; }

        /**  Sets the width of the line.

            @param aNumber the width of the line.
            */
        void setWidth(int aNumber)
        {
            width = aNumber;
        } 

        /** Sets the colour of the line.

            @param aColor the colour of the line.
            */
        void setColor(const FSColor& aColor) { color = aColor; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int width;
        
        FSColor color;
    };
} 

#endif
