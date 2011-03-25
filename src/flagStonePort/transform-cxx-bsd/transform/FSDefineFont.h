/*
 *  FSDefineFont.h
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

#ifndef __FSDefineFont_h__
#define __FSDefineFont_h__

#include "FSDefineObject.h"

#include "FSVector.h"
#include "FSShape.h"
#include "FSBounds.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSShape>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSDefineFont defines the glyphs that are drawn when text characters are rendered in a particular font.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSDefineFont_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineFont_1">identifier</a></td>
<td>An unique identifier for this object in the range 1..65535.</td>
</tr>

<tr>
<td><a name="FSDefineFont_2">shapes</a></td>
<td>An array of FSShape objects contain the sequences of FSLine, FSCurve and FSShapeStyle objects used to trace the outlines for each glyph.</td>
</tr>

</table>

<p>A complete definition of a font is created using the FSDefineFont object for the glyphs along with an FSFontInfo object which contains the name of the font, whether the font face is bold or italics and a table that maps character codes to the glyphs that is drawn to represent the character.</p>

<p>When defining a font only the glyphs used from a particular font are included. Unused glyphs can be omitted greatly reducing the amount of information that is encoded.</p>

<h2 class="datasheet">History</h1>

<p>The FSDefineFont class represents the DefineFont structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSDefineFont : public FSDefineObject
    {
public:
        FSDefineFont(FSInputStream* aStream);
        
        /** Constructs an FSDefineFont object setting the unique identifier for the object and the array of glyphs used to render the characters used from the font.
        
            @param anIdentifier the unique identifier for this object.
            @param glyphArray an array of FSShape objects that define the outlines of the glyphs.
            */
        FSDefineFont(int anIdentifier, const FSVector<FSShape>& glyphArray) : FSDefineObject(DefineFont, anIdentifier), shapes(glyphArray) {}

        FSDefineFont* clone() const { return new FSDefineFont(*this); }

        const char* className() const;

        /** Add a shape to the array of shapes.

            @param anObject a shape.
            */
        void add(const FSShape& anObject) { shapes.push_back(anObject); }

        /** Add all the shapes in the array to the end of the shapes array.

            @param anArray an array of shapes.
            */
        void add(const FSVector<FSShape>& anArray);

        /** Gets the array of shapes used to define the outlines of each font glyph.

            @return an array of FSShape objects
            */
        FSVector<FSShape>& getShapes() { return shapes; }

        /** Set the array of shape records that define the outlines of the characters used from the font.

            @param anArray an array of FSShape objects that define the glyphs for the font.
            */
        void setShapes(const FSVector<FSShape>& anArray) { shapes = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSVector<FSShape> shapes;
    };
}

#endif

