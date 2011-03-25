/*
 *  FSDefineMorphShape.h
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

#ifndef __FSDefineMorphShape_h__
#define __FSDefineMorphShape_h__ 1

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
 * %FSDefineMorphShape defines a shape that will morph from one form into another. 
 * 
<p>Only the start and end shapes are defined the Flash Player will perform the interpolation that transforms the shape at each staging in the morphing process.</p>

<p>Morphing can be applied to any shape, however there are a few restrictions:</p>

<ul>
<li>The start and end shapes must have the same number of edges (FSLine and FSCurve objects).</li>
<li>The fill style (Solid, Bitmap or Gradient) must be the same in the start and end shape.</li>
<li>If a bitmap fill style is used then the same image must be used in the start and end shapes.</li>
<li>If a gradient fill style is used then the gradient must contain the same number of points in the start and end shape.</li>
<li>The start and end shape must contain the same set of FSShapeStyle objects.</li>
</ul>

<p>To perform the morphing of a shape the shape is placed in the display list using a FSPlaceObject2 object. The ratio attribute in the FSPlaceObject2 object defines the progress of the morphing process. The ratio ranges between 0.0 and 1.0 where 0 represents the start of the morphing process and 1.0, the end.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSDefineMorphShape_0">type</a></td>
<td>Identifies the data structure when it is encoded. The type attribute is read-only and may be used when iterating through the objects in an FSMovie object to identify the object class without using run-time type checking.</td>
</tr>

<tr>
<td><a name="FSDefineMorphShape_1">identifier</a></td>
<td>An unique identifier for this object in the range 1..65535.</td>
</tr>

<tr>
<td><a name="FSDefineMorphShape_2">startBounds</a></td>
<td>A rectangle (FSBounds) defining the bounding area in which the shape is drawn at the start of the morph process.</td>
</tr>

<tr>
<td><a name="FSDefineMorphShape_3">endBounds</a></td>
<td>A rectangle (FSBounds) defining the bounding area in which the shape is drawn at the end of the morph process.</td>
</tr>

<tr><td><a name="FSDefineMorphShape_4">fillStyles</a></td>
<td>An array of fill styles.</td>
</tr>

<tr><td><a name="FSDefineMorphShape_5">lineStyles</a></td>
<td>An array of line styles.</td>
</tr>

<tr><td><a name="FSDefineMorphShape_6">startShape</a></td>
<td>An FSShape object containing the shape records (FSLine, FSCurve and FSShapeStyle objects) that describe the shape at the start of the morphing process.</td>
</tr>

<tr>
<td><a name="FSDefineMorphShape_7">endShape</a></td>
<td>The shape at the end of the morphing process containing the FSLine and FSCurve objects that define the edges of the shape.FSShapeStyle objects may only be included if they are used to move the current point and may <b>not</b> change the style being used to draw the shape.</td>
</tr>
</table>

<p>The edges may change their type when a shape is morphed. Straight edges can become curves and vice versa.</p>

<h1 class="datasheet">Examples</h1>

<p>This simple example morphs a rectangle into a square. While this example is trivial it illustrates how the FSDefineMorphShape class is used.</p>

<p>This rectangle is 200 twips wide and 100 twips high, drawing using a black outline 1 twip wide and filled with a transparent red colour. The square is 150 x 150 twips. The origin of the shape is at the bottom left corner of the rectangle.</p>

<pre>
// Create the bounding rectangle for the start shape (rectangle).
FSBounds startBounds = new FSBounds(0, 0, 200, 100);

// Create the bounding rectangle for the end shape (square).
FSBounds endBounds = new FSBounds(0, 0, 150, 150);

// Define the styles for the shape.

ArrayList fillStyles = new ArrayList();
ArrayList lineStyles = new ArrayList();

fillStyles.push_back(new FSSolidFill(new FSColor((FSColorTable.red)));

lineStyles.push_back(new FSSolidLine(1, FColor.black()));

// Draw the rectangle.

FSShape rectangle = new FSShape();

rectangle.add(new FSShapeStyle(1, 1, 0, 0, 0));
rectangle.add(new FSLine(200,0));
rectangle.add(new FSLine(0,100));
rectangle.add(new FSLine(-200,0));
rectangle.add(new FSLine(0,-100));

// Draw the square.

FSShape square = new FSShape();

square.add(new FSLine(150,0));
square.add(new FSLine(0,150));
square.add(new FSLine(-150,0));
square.add(new FSLine(0,-150));

FSDefineMorphShape shape = FSDefineMorphShape(movie.newIdentifier(), startBounds, endBounds, fillStyles, lineStyles, rectangle, square);

// The morphing process is controlled by the FSPlaceObject2 class using the ratio attribute.
// Place the shape on layer 1 of the display list at coordinates (0,0).

movie.add(new FSPlaceObject2(shape.getIdentifier(), 1, 0.0, 0,0));
movie.add(new FSShowFrame());

// Morph the shape over 5 steps without changing its location.

for (float i=0.2; i&lt;1.0; i+= 0.2)
{
    movie.add(new FSPlaceObject2(1, i, 0,0));
    movie.add(new FSShowFrame());
}
</pre>

<h1 class="datasheet">History</h1>

<p>The FSDefineMorphShape class represents the DefineMorphShape tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSDefineMorphShape : public FSDefineObject
    {
public:
        FSDefineMorphShape(FSInputStream* aStream);

        /** Constructs an FSDefineMorphShape object.

         @param anIdentifier an unique identifier for this object.
         @param aStartBounds the bounding rectangle enclosing the start shape.
         @param anEndBounds the bounding rectangle enclosing the end shape.
         @param fillStyleArray an array of FSMorphSolidFill, FSMorphBitmapFill and FSMorphGradientFill objects.
         @param lineStyleArray an array of FSMorphLineStyle objects.
         @param aStartShape the shape at the start of the morphing process.
         @param anEndShape the shape at the end of the morphing process.
         */
        FSDefineMorphShape(int anIdentifier, const FSBounds& aStartBounds, const FSBounds& anEndBounds, const FSVector<FSFillStyle*>& fillStyleArray, const FSVector<FSLineStyle*>& lineStyleArray, const FSShape& aStartShape, const FSShape& anEndShape) : FSDefineObject(DefineShape3, anIdentifier), startBounds(aStartBounds), endBounds(anEndBounds), fillStyles(fillStyleArray), lineStyles(lineStyleArray), startShape(aStartShape), endShape(anEndShape) {}

        FSDefineMorphShape(const FSDefineMorphShape& rhs);

        ~FSDefineMorphShape();

        FSDefineMorphShape& operator= (const FSDefineMorphShape& rhs);

        FSDefineMorphShape* clone() const { return new FSDefineMorphShape(*this); }

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

        /** Gets the initial bounding rectangle for the shape.

            @return the starting bounding rectangle for the shape.
            */
        FSBounds& getStartBounds() { return startBounds; }

        /** Gets the bounding rectangle for the final shape.

            @return the the bounding rectangle for the end shape.
            */
        FSBounds& getEndBounds() { return endBounds; }

        /** Gets the array fill styles.

            @return the fill styles used in the shape.
            */
        FSVector<FSFillStyle*>& getFillStyles() { return fillStyles; }

        /** Gets the array line styles.

            @return the line styles used in the shape.
            */
        FSVector<FSLineStyle*>& getLineStyles() { return lineStyles; }

        /** Gets the initial shape.

            @return the starting shape to be drawn.
            */
        FSShape& getStartShape() { return startShape; }

        /** Gets the final shape.

            @return the end shape to be drawn.
            */
        FSShape& getEndShape() { return endShape; }

        /** Sets the bounding rectangle for the initial shape.

            @param aBounds set the bounding rectangle for the start shape.
            */
        void setStartBounds(const FSBounds& aBounds) { startBounds = aBounds; }

        /** Sets the bounding rectangle for the final shape.

            @param aBounds set the bounding rectangle for the end shape.
            */
        void setEndBounds(const FSBounds& aBounds) { endBounds = aBounds; }

        /** Sets the fill styles.

            @param anArray set the fill styles for the shape.
            */
        void setFillStyles(const FSVector<FSFillStyle*>& anArray) { fillStyles = anArray; }

        /** Sets the line styles.

            @param anArray set the line styles for the shape.
            */
        void setLineStyles(const FSVector<FSLineStyle*>& anArray) { lineStyles = anArray; }

        /** Sets the initial shape.

            @param aShape set the starting shape to be drawn.
            */
        void setStartShape(const FSShape& aShape) { startShape = aShape; }

        /** Sets the final shape.

            @param aShape set the end shape to be drawn.
            */
        void setEndShape(const FSShape& aShape) { endShape = aShape; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSBounds startBounds;
        FSBounds endBounds;
        
        FSVector<FSFillStyle*> fillStyles;
        FSVector<FSLineStyle*> lineStyles;
        
        FSShape startShape;
        FSShape endShape;
    };
} 

#endif
