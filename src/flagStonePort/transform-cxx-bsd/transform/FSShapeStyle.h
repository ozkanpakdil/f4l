/*
 *  FSShapeStyle.h
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

#ifndef __FSShapeStyle_h__
#define __FSShapeStyle_h__ 1

#include "FSVector.h"

#include "FSShapeObject.h"
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
 * %FSShapeStyle is used to change the drawing environment when a shape is drawn. 
 * 
<p>Three operations can be performed:</p>

<ul>
<li>Select a line style or fill style.</li>
<li>Move the current drawing point.</li>
<li>Define a new set of line and fill styles.</li>
</ul>

<p>An FSShapeStyle object can specify one or more of the operations rather than specifying them in separate FSShapeStyle objects - compacting the size of the binary data when the object is encoded. Conversely if an operation is not defined then the values may be omitted.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSShapeStyle_0">lineStyle</a></td>
<td>The index of the line style in the parent shape's line style array. Optional. May be set to the framework constant Transform.VALUE_NOT_SET if no style is selected.</td>
</tr>

<tr>
<td><a name="FSShapeStyle_1">fillStyle</a></td>
<td>The index of the fill style in the parent shape's fill style array. Optional. May be set to the framework constant Transform.VALUE_NOT_SET if no style is selected.</td>
</tr>

<tr>
<td><a name="FSShapeStyle_2">altFillStyle</a></td>
<td>The index of the alternate fill style in the parent shape's fill style array. Optional. May be set to the framework constant Transform.VALUE_NOT_SET if no style is selected.</td>
</tr>

<tr>
<td><a name="FSShapeStyle_3">moveX</a></td>
<td>The absolute x-coordinate of the new drawing point. Optional. May be set to the framework constant Transform.VALUE_NOT_SET if the drawing point is not being moved.</td>
</tr>

<tr>
<td><a name="FSShapeStyle_4">moveY</a></td>
<td>The absolute y-coordinate of the new drawing point. Optional. May be set to the framework constant Transform.VALUE_NOT_SET if the drawing point is not being moved.</td>
</tr>

<tr>
<td><a name="FSShapeStyle_5">lineStyles</a></td>
<td>An array of new line styles for the parent shape. Optional. May be set to null or an empty array if no line or fill styles are being added.</td>
</tr>

<tr>
<td><a name="FSShapeStyle_6">fillStyles</a></td>
<td>An array of new fill styles for the parent shape. Optional. May be set to null or an empty array if no line or fill styles are being added.</td>
</tr>

</table>

<p>Line and Fill styles are selected by the index position, starting at 1, of the style in an array of styles. An index of zero means that no style is selected. Using the constant Transform.VALUE_NOT_SET means that the current style is unchanged. Two types of fill style are supported: fillStyle is used where a shape does not contain overlapping areas and altFillStyle is used where areas overlap. This differs from graphics environments that only support one fill style as the overlapping area would form a hole in the shape and not be filled.</p>

<p>In the following example, when a shape is drawn the fillStyle defines the style to the left of the line drawing the outline while the altFillStyle defines the style applied to the right of the outline.</p>

<img src="fillStyles.gif">

<p>New fill and line styles can be added to the FSShapeStyle object to change the way shapes are drawn.</p>

<p>A new drawing point is specified using the absolute x and y coordinates. If an FSShapeStyle object is the first in a shape then the current drawing point is the origin of the shape (0,0).</p>

<h1 class="datasheet">Optional Attributes</h1>

<p>Since the FSShapeStyle object can encode three different types of operation, the unused attributes are optional. Setting line or fill styles to the framework constant Transform.VALUE_NOT_SET omits the attribute when the object is encoded - reduced the size.</p>

<p>For the line and fill styles setting the respective attribute to Transform.VALUE_NOT_SET is different from setting to zero. When the attribute is set to Transform.VALUE_NOT_SET attribute is not encoded. When the attribute is set to zero then that instructs the Flash Player that no current line or fill style is selected. The latter is important when filling areas of a shape that overlap - the altFillStyle attribute will be set to the desired style while the lineStyle and fillStyle attributes are set to zero.</p>

<p>Similarly moveX and moveY may be set to Transform.VALUE_NOT_SET to indicate that the current drawing point will not be changed.  This can also be achieved by setting moveX and moveY to zero. However using Transform.VALUE_NOT_SET means that the attributes are not encoded reducing the binary representation. For large files the savings can be significant.</p>

<p>The line or fill style arrays May be empty if no new styles are being specified.</p>

<p>Note that the values for the moveX and moveY attributes and the line and fill styles arrays are defined in pairs and are optional only if both are set to zero or NULL respectively.</p>

<h1 class="datasheet">Examples</h1>

<p>The class provides a range of constructors which define different subsets of the attributes according to the type of operation that will be performed. If an attribute is not specified in a constructor then it will be assigned the default value of Transform.VALUE_NOT_SET and will be omitted when the object is encoded.</p>

<p>1. Select line and fill styles.</p>

<pre>
FSDefineShape* shape = new FSDefineShape(movie.newIdentifier(), ...);

// Add fill styles to the shape definition

shape-&gt;push_back(new FSSolidFill(FSColor(0, 0, 255)));
shape-&gt;push_back(new FSBitmapFill(FSFillStyle::Tiled, imageId, transform));

// Add a line styles to the shape definition

shape-&gt;push_back(new FSSolidLine(20, FSColor(0, 0, 0)));

// Select the solid line style and the bitmap fill style. Note that the
// ordinal position of the styles is used. A style index of 0 means that
// style is not set.

shape-&gt;push_back(new FSShapeStyle(1, 2, 0));
</pre>

<p>2. Move the current drawing point.</p>

<p>The drawing point is changed by specifying the position from the current drawing point:</p>

<pre>
FSShapeStyle* style = new FSShapeStyle(x, y);
</pre>

<p>3. Specifying New Styles.</p>

<p>Adding a new set of styles to an FSShapeStyle object will replace the existing set of styles defined for the shape.</p>

<pre>
FSDefineShape* shape = new FSDefineShape(movie.newIdentifier(), bounds, fillStyles, lineStyles, shape);

// Replace the existing set of fill and line styles in the shape definition

FSVector&lt;FSFillStyle*&gt; fillStyles;
FSVector&lt;FSLineStyle*&gt; lineStyles;

fillStyles.push_back(new FSSolidFill(FSColor(255, 0, 0)));
fillStyles.push_back(new FSSolidFill(FSColor(0, 255, 0)));
fillStyles.push_back(new FSSolidFill(FSColor(0, 0, 255)));

lineStyles.push_back(new FSSolidLine(1, FSColor(0, 0, 0)));

shape-&gt;push_back(new FSShapeStyle(lineStyles, fillStyles));
</pre>

<p>4. Creating an overlapping shape.</p>

<pre>
// Create the bounding rectangle for the shape. Two rectangles 100 x 100 pixels 
// are drawn. The area overlap area is 50 x 50 pixels.

FSBounds bounds(0, -50, 150, 100);

// Define the styles for the shape.

FSVector&lt;FSFillStyle*&gt; fillStyles;
FSVector&lt;FSLineStyle*&gt; lineStyles;

fillStyles.push_back(new FSSolidFill(FSColor(255, 0, 0)));
fillStyles.push_back(new FSSolidFill(FSColor(255, 255, 0)));
fillStyles.push_back(new FSSolidFill(FSColor(16, 123, 255)));

lineStyles.push_back(new FSSolidLine(20, FSColor(0, 0, 0)));

FSDefineShape* shape = new FSDefineShape(movie.newIdentifier, bounds, fillStyles, lineStyles, FSShape());
</pre>

// To create the overlapping shape shown above the following styles 
// selections are made while the shape is drawn.

shape-&gt;push_back(new FSShapeStyle(1, 1, 0, 0, 0));
shape-&gt;push_back(new FSLine(50,0));
shape-&gt;push_back(new FSShapeStyle(1, 1, 3));
shape-&gt;push_back(new FSLine(0,50));
shape-&gt;push_back(new FSLine(50,0));
shape-&gt;push_back(new FSShapeStyle(1, 0, 2));
shape-&gt;push_back(new FSLine(50,0));
shape-&gt;push_back(new FSLine(0,-100));
shape-&gt;push_back(new FSLine(-100,0));
shape-&gt;push_back(new FSLine(0,50));
shape-&gt;push_back(new FSShapeStyle(1, 3, 2));
shape-&gt;push_back(new FSLine(50,0));
shape-&gt;push_back(new FSLine(0,50));
shape-&gt;push_back(new FSShapeStyle(1, 1, 0));
shape-&gt;push_back(new FSLine(0,50));
shape-&gt;push_back(new FSLine(-100,0));
shape-&gt;push_back(new FSLine(0,-100));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSShapeStyle class represents the StyleChange record from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSShapeStyle : public FSShapeObject
    {
public:
        FSShapeStyle(FSInputStream* aStream);
        
        /** Constructs an FSShapeStyle object, selecting the line and fill styles.

        @param lineStyleIndex selects the line style at lineStyleIndex in the line styles array of the parent FSShape object.
        @param fillStyleIndex selects the fill style at fillStyleIndex in the fill styles array of the parent FSShape object.
        @param altFillStyleIndex selects the alternate fill style at altFillStyleIndex in the fill styles array of the parent FSShape object.
        */
        FSShapeStyle(int lineStyleIndex, int fillStyleIndex, int altFillStyleIndex) : FSShapeObject(Style), moveX(Transform::VALUE_NOT_SET), moveY(Transform::VALUE_NOT_SET), fillStyle(fillStyleIndex), altFillStyle(altFillStyleIndex), lineStyle(lineStyleIndex), fillStyles(), lineStyles() {}

        /** Constructs an FSShapeStyle object, selecting the new drawing point. 

            @param x move the current point to the x coordinate.
            @param y move the current point to the y coordinate.
            */
        FSShapeStyle(int x, int y) : FSShapeObject(Style), moveX(0), moveY(0), fillStyle(Transform::VALUE_NOT_SET), altFillStyle(Transform::VALUE_NOT_SET), lineStyle(Transform::VALUE_NOT_SET), fillStyles(), lineStyles()
        {
            setMoveX(x);
            setMoveY(y);
        }

        /** Constructs an FSShapeStyle object, specifying the new set of line and fill styles for the parent shape. The fill and line styles are owned by the object.

            @param lineStylesArray an array of FSLineStyle objects.
            @param fillStylesArray an array of fill style objects.
            */
        FSShapeStyle(const FSVector<FSLineStyle*>& lineStylesArray, const FSVector<FSFillStyle*>& fillStylesArray) : FSShapeObject(Style) , moveX(Transform::VALUE_NOT_SET), moveY(Transform::VALUE_NOT_SET), fillStyle(Transform::VALUE_NOT_SET), altFillStyle(Transform::VALUE_NOT_SET), lineStyle(Transform::VALUE_NOT_SET), fillStyles(fillStylesArray), lineStyles(lineStylesArray) {}

        /** Constructs an FSShapeStyle object, selecting the line and fill styles and drawing point. 
    
            @param lineStyleIndex selects the line style at lineStyleIndex in the line styles array of the parent FSShape object.
            @param fillStyleIndex selects the fill style at fillStyleIndex in the fill styles array of the parent FSShape object.
            @param altFillStyleIndex selects the alternate fill style at altFillStyleIndex in the fill styles array of the parent FSShape object.
            @param x move the current point to the x-coordinate.
            @param y move the current point to the y-coordinate.
            */
        FSShapeStyle(int lineStyleIndex, int fillStyleIndex, int altFillStyleIndex, int x, int y) : FSShapeObject(Style), moveX(0), moveY(0), fillStyle(fillStyleIndex), altFillStyle(altFillStyleIndex), lineStyle(lineStyleIndex), fillStyles(), lineStyles()
        {
            setMoveX(x);
            setMoveY(y);
        }

        /** Constructs an FSShapeStyle object, selecting the line and fill styles and specifying new sets of line and fill styles. The object assumes ownership of the new fill and line styles.
    
            @param lineStyleIndex selects the line style at lineStyleIndex in the line styles array of the parent FSShape object.
            @param fillStyleIndex selects the fill style at fillStyleIndex in the fill styles array of the parent FSShape object.
            @param altFillStyleIndex selects the alternate fill style at altFillStyleIndex in the fill styles array of the parent FSShape object.
            @param lineStylesArray an array of FSLineStyle objects.
            @param fillStylesArray an array of fill style objects.
            */
        FSShapeStyle(int lineStyleIndex, int fillStyleIndex, int altFillStyleIndex, const FSVector<FSLineStyle*>& lineStylesArray, const FSVector<FSFillStyle*>& fillStylesArray) : FSShapeObject(Style), moveX(Transform::VALUE_NOT_SET), moveY(Transform::VALUE_NOT_SET), fillStyle(fillStyleIndex), altFillStyle(altFillStyleIndex), lineStyle(lineStyleIndex), fillStyles(fillStylesArray), lineStyles(lineStylesArray) {}

        /** Constructs an FSShapeStyle object, selecting the line and fill styles, drawing point, new line and new fill styles. The object assumes ownership of the new fill and line styles.
    
            @param lineStyleIndex selects the line style at lineStyleIndex in the line styles array of the parent FSShape object.
            @param fillStyleIndex selects the fill style at fillStyleIndex in the fill styles array of the parent FSShape object.
            @param altFillStyleIndex selects the alternate fill style at altFillStyleIndex in the fill styles array of the parent FSShape object.
            @param x move the current point to the x-coordinate.
            @param y move the current point to the y-coordinate.
            @param lineStylesArray an array of FSLineStyle objects.
            @param fillStylesArray an array of fill style objects.
            */
        FSShapeStyle(int lineStyleIndex, int fillStyleIndex, int altFillStyleIndex, int x, int y, const FSVector<FSLineStyle*>& lineStylesArray, const FSVector<FSFillStyle*>& fillStylesArray) : FSShapeObject(Style), moveX(0), moveY(0), fillStyle(fillStyleIndex), altFillStyle(altFillStyleIndex), lineStyle(lineStyleIndex), fillStyles(fillStylesArray), lineStyles(lineStylesArray)
        {
            setMoveX(x);
            setMoveY(y);
        }

        FSShapeStyle(const FSShapeStyle& rhs);

        ~FSShapeStyle();

        FSShapeStyle& operator= (const FSShapeStyle& rhs);

        FSShapeStyle* clone() const { return new FSShapeStyle(*this); }

        const char* className() const;

        /** Add a fill style object to the array of fill styles. The object assumes ownership of the style.

            @param aStyle a fill style object.
            */
        void add(FSFillStyle* aStyle) { fillStyles.push_back(aStyle); }

        /** Add all the fill style objects to the array of fill styles. The object assumes ownership of the styles.

            @param anArray an array of fill style objects.
            */
        void add(const FSVector<FSFillStyle*>& anArray);

        /** Add a line style object to the array of line styles. The object assumes ownership of the style.

            @param aStyle a line style object.
            */
        void add(FSLineStyle* aStyle) { lineStyles.push_back(aStyle); }

        /** Add all the line style objects to the array of line styles.  object assumes ownership of the styles.

            @param anArray an array of line style objects.
            */
        void add(const FSVector<FSLineStyle*>& anArray);

        /** Gets the x-coordinate of any move specified.

            @return the x-coordinate of the move.
            */
        int getMoveX() const
        {
            return moveX;
        }
    
        /** Gets the y-coordinate of any move specified.

            @return the y-coordinate of the move.
            */
        int getMoveY() const
        {
            return moveY;
        }

        /** Gets the index of the line style that will be applied to any line drawn. Returns the value Transform::VALUE_NOT_SET if no line style is defined.

            @return the index of the selected line style.
            */
        int getLineStyle() const { return lineStyle; }

        /** Gets the index of the fill style that will be applied to any area filled. Returns the value Transform::VALUE_NOT_SET if no fill style is defined.

            @return the index of the selected fill style.
            */
        int getFillStyle() const { return fillStyle; }

        /** Gets the index of the fill style that will be applied to any overlapping area filled. Returns the value Transform::VALUE_NOT_SET if no alternate fill style is defined.

            @return the index of the selected alternate style.
            */
        int getAltFillStyle() const { return altFillStyle; }

        /** Gets the array of new line styles.

            @return the array of FSLineStyle objects.
            */
        FSVector<FSLineStyle*>& getLineStyles() { return lineStyles; }

        /** Gets the array of new fill styles.

            @return the array of fill style objects.
            */
        FSVector<FSFillStyle*>& getFillStyles() { return fillStyles; }

        /** Sets the x-coordinate of the new drawing point. 

            @param x the x-coordinate of the drawing point.
            */
        void setMoveX(int x)
        {
            moveX = x;
        }        
    
        /** Sets the y-coordinate of the new drawing point.

            @param y the y-coordinate of the drawing point.
            */
        void setMoveY(int y)
        {
            moveY = y;
        }        

        /** Sets the drawing point.

            @param x the x-coordinate of the drawing point.
            @param y the y-coordinate of the drawing point.
            */
        void setMove(int x, int y)
        {
            moveX = x;
            moveY = y;
        }

        /**    Sets the index of the fill style that will be applied to any area filled. May be set to zero if no style is selected or Transform::VALUE_NOT_SET if the attribute should not be encoded.

            @param anIndex selects the fill style at anIndex in the fill styles array of the parent FSShape object.
            */
        void setFillStyle(int anIndex) { fillStyle = anIndex; }

        /** Sets the index of the fill style that will be applied to any overlapping area filled. May be set to zero if no style is selected or Transform::VALUE_NOT_SET if the attribute should not be encoded.

            @param anIndex selects the alternate fill style at anIndex in the fill styles array of the parent FSShape object.
            */
        void setAltFillStyle(int anIndex) { altFillStyle = anIndex; }

        /** Sets the index of the line style that will be applied to any line drawn. May be set to zero if no style is selected or Transform::VALUE_NOT_SET if the attribute should not be encoded.

            @param anIndex selects the line style at anIndex in the line styles array of the parent FSShape object.
            */
        void setLineStyle(int anIndex) { lineStyle = anIndex; }

        /** Sets the array of new line styles. May be set to empty if no styles are being defined. The object assumes ownership of the styles.

            @param anArray an array of FSLineStyle objects.
            */
        void setLineStyles(const FSVector<FSLineStyle*>& anArray) { lineStyles = anArray; }

        /** Sets the array of new fill styles. May be set to empty if no styles are being defined. The object assumes ownership of the styles.

            @param anArray an array of fill style objects.
            */
        void setFillStyles(const FSVector<FSFillStyle*>& anArray) { fillStyles = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool containsStyles() const;
        bool containsLineStyle() const;
        bool containsAltFillStyle() const;
        bool containsFillStyle() const;
        bool containsMove() const;
        int fieldSize() const;

        int moveX;
        int moveY;
        
        int fillStyle;
        int altFillStyle;
        int lineStyle;
        
        FSVector<FSFillStyle*> fillStyles;
        FSVector<FSLineStyle*> lineStyles;
    };
} 

#endif
