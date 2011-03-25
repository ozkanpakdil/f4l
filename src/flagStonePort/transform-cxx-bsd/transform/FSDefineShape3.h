/*
 *  FSDefineShape3.h
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

#ifndef __FSDefineShape3_h__
#define __FSDefineShape3_h__ 1

#include "FSVector.h"

#include "FSDefineObject.h"

#include "FSBounds.h"
#include "FSShape.h"
#include "FSFillStyle.h"
#include "FSLineStyle.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSFillStyle*>;
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSLineStyle*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSDefineShape3 defines a transparent shape to be displayed. 
 * 
<p>It extends the functionality of the FSDefineShape2 class by supporting transparent colours.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSDefineShape3_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineShape3_1">identifier</a></td>
<td>An unique identifier for this object, in the range 1..65535.</td>
</tr>

<tr>
<td><a name="FSDefineShape3_2">bounds</a></td>
<td>The bounding area inside which the shape is drawn.</td>
</tr>

<tr>
<td><a name="FSDefineShape3_3">fillStyles</a></td>
<td>An array of fill styles used to fill the area enclosed by the shape.</td></tr>

<tr>
<td><a name="FSDefineShape3_4">lineStyles</a></td>
<td>An array of line styles used to draw the outline of the shape.</td>
</tr>

<tr>
<td><a name="FSDefineShape3_5">shape</a></td>
<td>An FSShape object containing the shape records (FSLine, FSCurve and FSShapeStyle objects) that describe how the shape is drawn and filled shape.</td>
</tr>
</table>

<p>The shape defines a path containing a mix of straight and curved edges and pen move actions. A path need not be contiguous. When the shape is drawn the FSShapeStyle object selects the line and fill styles, from the respective array, to be used. FSShapeStyle objects can be defined in the shape at any time to change the styles being used. The fill style used can either be an area of pure colour, a bitmap image or a gradient. The line style specifies the colour and thickness of the line drawn around the shape outline. For both line and fill styles the selected style may be undefined, allowing the shape to be drawn without an outline or left unfilled.</p>

<h1 class="datasheet">Examples</h1>

<p>This example creates a simple rectangle, 200 twips wide and 100 twips high, drawing using a black outline 1 twip wide and filled with a transparent red colour. The origin of the shape is at the bottom left corner of the rectangle.</p>

<pre>
// Create the bounding rectangle for the shape. The values also specify
// the coordinate range of the shape.

FSBounds bounds = new FSBounds(0, 0, 200, 100);

// Define the styles for the shape.

FSVector&lt;FSFillStyle*&gt; fillStyles;
FSVector&lt;FSLineStyle*&gt; lineStyles;

fillStyles.push_back(new FSSolidFill(FSColor(255, 0, 0, 128)));
lineStyles.push_back(new FSSolidLine(1, FSColor(0, 0, 0, 128)));

// Draw the shape.

FSShape shape;

// Define the line, fill styles and move to the shape's origin.

shape.push_back(new FSShapeStyle(1, 1, 0, 0, 0));
shape.push_back(new FSLine(200,0));
shape.push_back(new FSLine(0,100));
shape.push_back(new FSLine(-200,0));
shape.push_back(new FSLine(0,-100));

FSDefineShape3* shape = new FSDefineShape3(movie.newIdentifier(), bounds, fillStyles, lineStyles, shape);
</pre>

<h1 class="datasheet">History</h1>

<p>The FSDefineShape3 class represents the DefineShape3 tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSDefineShape3 : public FSDefineObject
    {
public:
        FSDefineShape3(FSInputStream* aStream);

        /** Constructs an FSDefineShape3 object.

            @param anIdentifier the unique identifier for the shape.
            @param aBounds the bounding rectangle for the shape.
            @param fillStyleArray the array of fill styles used in the shape.
            @param lineStyleArray the array of line styles used in the shape.
            @param aShape the shape to be drawn.
            */
        FSDefineShape3(int anIdentifier, const FSBounds& aBounds, const FSVector<FSFillStyle*>& fillStyleArray, const FSVector<FSLineStyle*>& lineStyleArray, const FSShape& aShape) : FSDefineObject(DefineShape3, anIdentifier), bounds(aBounds), fillStyles(fillStyleArray), lineStyles(lineStyleArray), shape(aShape) {}

        FSDefineShape3(const FSDefineShape3& rhs);

        ~FSDefineShape3();

        FSDefineShape3& operator= (const FSDefineShape3& rhs);

        FSDefineShape3* clone() const { return new FSDefineShape3(*this); }

        const char* className() const;

        /** Add a fill style object to the array of fill styles. The shape assumes ownership of the fill style object.

            @param aStyle a fill style object.
            */
        void add(FSFillStyle* aStyle) { fillStyles.push_back(aStyle); }

        /** Add all the fill style objects to the array of fill styles. The shape assumes ownership of the fill style objects in the array.
            
            @param anArray an array of fill style objects.
            */
        void add(const FSVector<FSFillStyle*>& anArray);

        /** Add a line style object to the array of line styles. The shape assumes ownership of the line style object.

            @param aStyle a line style object.
            */
        void add(FSLineStyle* aStyle) { lineStyles.push_back(aStyle); }

        /** Add all the line style objects to the array of line styles. The shape assumes ownership of the line style objects in the array.

            @param anArray an array of line style objects.
            */
        void add(const FSVector<FSLineStyle*>& anArray);

        /** Gets the bounding rectangle for the shape.

            @return the bounding rectangle for the shape.
            */
        FSBounds& getBounds() { return bounds; }

        /** Gets the array fill styles.

            @return the fill styles used in the shape.
            */
        FSVector<FSFillStyle*>& getFillStyles() { return fillStyles; }

        /** Gets the array line styles.

            @return the line styles used in the shape.
            */
        FSVector<FSLineStyle*>& getLineStyles() { return lineStyles; }

        /** Gets the shape.

            @return the shape to be drawn.
            */
        FSShape& getShape() { return shape; }

        /** Sets the bounding rectangle.

            @param aBounds set the bounding rectangle for the shape.
            */
        void setBounds(const FSBounds& aBounds) { bounds = aBounds; }

        /** Sets the fill styles.

            @param anArray set the fill styles for the shape.
            */
        void setFillStyles(const FSVector<FSFillStyle*>& anArray) { fillStyles = anArray; }

        /** Sets the line styles.

            @param anArray set the line styles for the shape.
            */
        void setLineStyles(const FSVector<FSLineStyle*>& anArray) { lineStyles = anArray; }

        /** Sets the shape.

            @param aShape set the shape to be drawn.
            */
        void setShape(const FSShape& aShape) { shape = aShape; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

protected:
        FSBounds bounds;
        FSVector<FSFillStyle*> fillStyles;
        FSVector<FSLineStyle*> lineStyles;
        FSShape shape;
    };
} 

#endif
