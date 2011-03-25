/*
 *  FSDefineText2.h
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

#ifndef __FSDefineText2_h__
#define __FSDefineText2_h__ 1

#include "FSDefineObject.h"

#include "FSVector.h"
#include "FSBounds.h"
#include "FSCoordTransform.h"
#include "FSText.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSText>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSDefineText2 defines one or more lines of transparent text. 
 *  
<p>It extends the functionality provided by the FSDefineText class by supporting transparent colours. The characters, style and layout information is defined using FSText objects. The FSDefineText2 class acts as a container for the text, defining the bounding rectangle that encloses the text along with a coordinate transform that can be used to change the size and orientation of the text when it is displayed.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSDefineText2_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineText2_1">identifier</a></td>
<td>An unique identifier for this object in the range 1..65535.</td>
</tr>

<tr>
<td><a name="FSDefineText2_2">bounds</a></td>
<td>A bounding rectangle for the entire block of text defined in the object.</td>
</tr>

<tr>
<td><a name="FSDefineText2_3">transform</a></td>
<td>A coordinate transform describing the placement, size and rotation of the text block.</td>
</tr>

<tr>
<td><a name="FSDefineText2_4">objects</a></td>
<td>An array of FSText objects describing the characters to be displayed and their attributes.</td>
</tr>
</table>

<p>The bounding rectangle and transform controls how the text is laid out. Each FSText object in the textRecords array specifies an offset from the left and bottom edges of the bounding rectangle, allowing successive lines of text to be arranged as a block or paragraph. The coordinate transform can be used to control the size and orientation of the text when it is displayed.</p>

<h1 class="datasheet">Examples</h1>

<p>Creating a simple string. The creation and layout of the glyphs to create the text is too onerous to perform from scratch. It is easier and more convenient to use existing font definitions either by parsing an existing Flash file or by converting a font definition from a specification such as TrueType in order to obtain the glyphs and layout information.</p>

<p>This examples assumes a font definition that contains glyphs for the following set of characters ' ', 'a', 'b', 'c' .... 'x', 'y', 'z'. The font used fixed size for the spacing between glyphs .e.g. Courier.</p>

<pre>
int fontSize = 240;
int leading = 80;

FSVector<FSCharacter> characters;

characters.push_back(FSCharacter(1, 120));  // 'a'
characters.push_back(FSCharacter(0, 120));  // ' '
characters.push_back(FSCharacter(19, 120)); // 's'
characters.push_back(FSCharacter(10, 120)); // 't'
characters.push_back(FSCharacter(18, 120)); // 'r'
characters.push_back(FSCharacter(9, 120));  // 'i'
characters.push_back(FSCharacter(14, 120)); // 'n'
characters.push_back(FSCharacter(6, 120));  // 'g'

// Create the string setting the height to be 12-point (240 twips) and 
// displaying the characters in black. The text is not indented or offset.

FSVector<FSText> lines;

lines.push_back(FSText(font->getIdentifier(), FSColor(0, 0, 0)), 0, 0, fontSize, characters);

// Calculate the bounding rectangle that encloses the text.
// The width of the text by summing all the advances.

int width = 0;
int height = fontSize + leading;

for (Iterator i = characters.iterator(); i.hasNext();)
    width += (*i).getAdvance();

FSBounds bounds(0, 0, width, height);

// Define the text with no coordinate transformation (use the default unity 
// transform which leaves the text unchanged.

FSDefineText text = new FSDefineText(movie.newIdentifier(), bounds, FSCoordTransform(), lines);

</pre>

<h1 class="datasheet">History</h1>

<p>The FSDefineText2 class represents the DefineText2 tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSDefineText2 : public FSDefineObject
    {
public:
        FSDefineText2(FSInputStream* aStream);
        
        /** Constructs an FSDefineText2 object with the specified bounding rectangle, coordinate transform and text records.

            @param anIdentifier the unique identifier for this object.
            @param aBounds the bounding rectangle enclosing the text.
            @param aTransform an FSCoordTransform to change the size and orientation of the text.
            @param textRecordArray an array of text record (FSTextStyle and FSText) object that define the text to be displayed.
            */
        FSDefineText2(int anIdentifier, const FSBounds& aBounds, const FSCoordTransform& aTransform, const FSVector<FSText>& textRecordArray) : FSDefineObject(DefineText2, anIdentifier), bounds(aBounds), transform(aTransform), textRecords(textRecordArray) {}

        FSDefineText2* clone() const { return new FSDefineText2(*this); }

        const char* className() const;

        /** Adds an FSText object to the end of the textRecords array.

            @param anObject an FSText object.
            */
        void add(const FSText& anObject) {  textRecords.push_back(anObject); }

        /** Adds all the FSText object in the array to the end of the textRecords array.

            @param anArray an array of FSText objects.
            */
        void add(const FSVector<FSText>& anArray);

        /** Gets the bounding rectangle that completely encloses the text to be displayed.

            @return the bounding rectangle of the text.
            */
        FSBounds& getBounds() { return bounds; }

        /** Gets the coordinate transform that controls how the text is displayed.

            @return the coordinate transform.
            */
        FSCoordTransform& getTransform() { return transform; }

        /** Gets the array of text records that define the text to be displayed as its attributes.

            @return the array of text records (FSTextStyle and FSText objects).
            */
        FSVector<FSText>& getTextRecords() { return textRecords; }

        /** Sets the bounding rectangle that encloses the text being displayed.

            @param aBounds the bounding rectangle enclosing the text.
            */
        void setBounds(const FSBounds& aBounds) { bounds = aBounds; }

        /** Sets the coordinate transform that changes the orientation and size of the text displayed.

            @param aTransform an FSCoordTransform to change the size and orientation of the text.
            */
        void setTransform(const FSCoordTransform& aTransform) { transform = aTransform; }

        /** Sets the array of text records that define the text to be displayed.

            @param anArray an array of text record (FSTextStyle and FSText) object that define the text to be displayed.
            */
        void setTextRecords(const FSVector<FSText>& anArray) { textRecords = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int glyphBits() const;
        int advanceBits() const;
        
        FSBounds bounds;
        FSCoordTransform transform;
        FSVector<FSText> textRecords;
    };
}

#endif
