/*
 *  FSSolidFill.h
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

#ifndef __FSSolidFill_h__
#define __FSSolidFill_h__ 1

#include "FSFillStyle.h"

#include "FSColor.h"

namespace transform
{
/**
 * %FSSolidFill defines a solid colour that is used to fill an enclosed area in a shape.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSSolidFill_0">type</a></td>
<td>Identifies the data structure when it is encoded.</td>
</tr>

<tr><td><a name="FSSolidFill_1">color</a></td>
<td>The colour used to fill the area of the shape.</td>
</tr>

</table>

<p>The parent class, FSFillStyle allows the type to be set. This should only be used for manipulating bitmap and gradient fill styles.</p> 

<p>Fill styles are selected using the FSShapeStyle class and are referenced by their ordinal position in the array of available styles. The ordinal position in the array is used rather than the index (which starts at 0). An index of 0 is used to specify that a fill style is not selected.</p>

<h1 class="datasheet">Examples</h1>

<p>An FSSolidFill object is created by specifying the colour to fill the shape:</p>

<pre>
FSColor red(255, 0, 0);
FSSolidFill* fill = new FSSolidFill(red);
</pre>

<p>Shapes can be filled with transparent colours - rather than specifying that the entire shape is transparent when adding it to the display list using the FSPlaceObject2 class:

<pre>

FSColor transparentRed(255, 0, 0, 128);
FSSolidFill* transparentFill = new FSSolidFill(transparentRed);
</pre>

<p>Note however that the object used to create the shape definition determines whether the alpha channel is encoded. Simply specifying the level of transparency in the FSColor object is not sufficient. Transparent colours are only supports in Flash 3 onwards.</p>

<p>To reference different colours to fill a shape use the ordinal position of the FSSolidFill object in the array of fill styles defined in the shape:</p>

<pre>
FSVector$lt;FSFillStyle*$lt; fillStyles;

fillStyles.push_back(new FSSolidFill(FSColor(255, 0, 0))); // red 
fillStyles.push_back(new FSSolidFill(FSColor(0, 255, 0))); // green

FSShape shape();

// The fill styles are referenced by their ordinal position in the 
// array of styles.

int redStyle = 1; 
int greenStyle = 2; 

// fill the enclosed area with red.
shape.push_back(new FSShapeStyle(0, redStyle, 0));
...
// now fill the remaining area with green.
shape.push_back(new FSShapeStyle(0, greenStyle, 0));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSSolidFill class represents the FillStyle structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSSolidFill : public FSFillStyle
    {
public:
        FSSolidFill(FSInputStream* aStream);
        
        /** Constructs an FSSolidFill object of the specified colour.

            @param aColor an FSColor object that defines the colour that the area will be filled with.
            */
        FSSolidFill(const FSColor& aColor) : FSFillStyle(Solid), color(aColor) {}

        FSSolidFill* clone() const { return new FSSolidFill(*this); }

        const char* className() const;

        /** Gets the colour of the fill style.

            @return the colour defined for the solid fill.
            */
        FSColor& getColor() { return color; }
        
        /** Sets the colour of the fill style.

            @param aColor an FSColor object that defines the colour that the area will be filled with.
            */
        void setColor(const FSColor& aColor) { color = aColor; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSColor color;
    };
} 

#endif

