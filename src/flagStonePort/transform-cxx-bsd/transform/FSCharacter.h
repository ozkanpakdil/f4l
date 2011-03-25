/*
 *  FSCharacter.h
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

#ifndef __FSCharacter_h__
#define __FSCharacter_h__ 1

#include "FSTransformObject.h"

namespace transform
{
/**
 * The %FSCharacter class is used to identify the glyph that is displayed for a given 
 * character in a line of text. 
 * 
<p>The spacing to the next character is also defined.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSCharacter_0">glyphIndex</a></td>
<td>An index into the array of FSShape objects that define the glyphs for a given font.</td>
</tr>

<tr>
<td><a name="FSCharacter_1">advance</a></td>
<td>The distance, in twips, from the origin of the glyph representing the current character to the next glyph to be displayed.</td>
</tr>
</table>

<p>A single lines of text is displayed using an FSText object which contains an array of FSCharacter objects. Blocks of text can be created by combining one or more FSText objects. The size, colour and relative position of each line within the block is defined by the FSText object. The FSText objects are added to an FSDefineText object or an FSDefineText2 object (which supports transparent colours) which is then used to define the final size and orientation of the text when it is placed on the Display List.</p>

<h1 class="datasheet">Example</h1>

<p>This greatly simplified example illustrates how text strings are created. First the array of glyphs for each character is defined.</p>

<pre>
FSVector<FSShape> alphabet;

$OUT .= "FSShape space(...);  // Glyph for ' '
FSShape a(...);      // Glyph for 'a'
FSShape b(...);      // Glyph for 'b'
...
FSShape z(...);      // Glyph for 'z'

alphabet.push_back(space);
alphabet.push_back(a);
alphabet.push_back(b);
... \n";
alphabet.push_back(z);

// Create the font containing the glyphs for each character

movie.push_back(new FSDefineFont(movie.newIdentifier(), alphabet));

</pre>

<p>Now created the array of FSCharacter objects representing 'a string' Assume the font is a fixed width such as Courier and the spacing between characters is 160 twips - 8 pixels.</p>

<pre>
FSVector<FSCharacter> characters;\n";

characters.push_back(FSCharacter(1, 120));  // 'a'
characters.push_back(FSCharacter(0, 120));  // ' '
characters.push_back(FSCharacter(19, 120)); // 's'
characters.push_back(FSCharacter(10, 120)); // 't'
characters.push_back(FSCharacter(18, 120)); // 'r'
characters.push_back(FSCharacter(9, 120));  // 'i'
characters.push_back(FSCharacter(14, 120)); // 'n'
characters.push_back(FSCharacter(6, 120));  // 'g'

FSText string(characters);
</pre>

<p>It should be immediately clear that creating strings and font definitions from scratch is a huge task requiring knowledge of drawing glyphs and how to layout glyphs to generate aesthetically pleasing text. Transform is a low-level library and such complicated code should be avoided at all costs. Fortunately it is 'relatively' easy to use convert existing font definitions such as those encoded in True Type Font files to into the font and text definition objects that can be used to create Flash files. Another useful approach is to use an existing font definition from a Flash file to obtain the glyph definitions, character codes and advance information.</p>

<p>Creating such font and text definitions is outside the scope of the documentation for this library. However refer to the Transform Utilities framework for Transform available on Flagstone Software's web site for ways to perform these tasks.</p>

<h1 class="datasheet">History</h1>

<p>The FSCharacter class represents the GlyphEntry structure from Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSCharacter : public FSTransformObject
    {
public:
        FSCharacter(FSInputStream* aStream);

        FSCharacter() : glyphIndex(0), advance(0) {}

        /** Constructs an FSCharacter specifying the index of the glyph to be displayed and the spacing to the next glyph.

            @param anIndex the index into the array of FSShapes in an FSDefineFont FSDefineFont2 object that defines the glyph that represents the character to be displayed.
            @param anAdvance the relative position in twips, from the origin of the glyph representing this character to the next glyph to be displayed.
            */
        FSCharacter(int anIndex, int anAdvance) : glyphIndex(anIndex), advance(anAdvance) {}

        FSCharacter* clone() const { return new FSCharacter(*this); }

        const char* className() const;

        /** Gets the index of the glyph, in an FSDefineFont or FSDefineFont2 object, that will displayed to represent this character.

            @return the index of the glyph that represents the character to be displayed.
            */
        int getGlyphIndex() const { return glyphIndex; }

        /** Gets the spacing in twips between the glyph representing this character and the next.

            @return the distance in twips to the next glyph.
            */
        int getAdvance() const { return advance; }

        /** Sets the index of the glyph, in an FSDefineFont or FSDefineFont2 object, that represents the character to be displayed.

            @param anIndex the index of the glyph that represents the character to be displayed.
            */
        void setGlyphIndex(int anIndex) { glyphIndex = anIndex; }

        /** Sets the spacing in twips between the glyph representing this character and the next glyph to be displayed.

            @param aNumber the relative position in twips from the origin of the glyph representing this character to the next glyph.
            */
        void setAdvance(int aNumber) { advance = aNumber; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int glyphIndex;
        int advance;
    };
}
    
#endif
    
