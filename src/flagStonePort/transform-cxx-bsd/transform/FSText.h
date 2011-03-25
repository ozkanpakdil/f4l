/*
 *  FSText.h
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

#ifndef __FSText_h__
#define __FSText_h__ 1

#include "FSVector.h"

#include "FSTransformObject.h"

#include "FSColor.h"
#include "FSCharacter.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSCharacter>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{    
/**
 * %FSText is used to display a line of text. 
 * 
<p>It contains an array of FSCharacter 
objects which identify the glyphs that will be displayed along with style information 
that sets the colour of the text, the size of the font and the relative placement 
of the line within a block of text.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSText_0">identifier</a></td>
<td>The identifier, in the range 1..65535, of the font object which contains the 
glyphs representing each character displayed. Optional. Set to 0 if the font is 
not being changed.</td>
</tr>

<tr>
<td><a name="FSText_1">color</a></td>
<td>An FSColor object describing colour of the text. Optional. Set to null if the 
colour is not being changed.</td>
</tr>

<tr>
<td><a name="FSText_2">offsetX</a></td>
<td>The offset, in twips, relative to the left side bounding rectangle of the text 
block where the text will be displayed. Optional. Set to zero if no indent is being 
specified.</td>
</tr>

<tr>
<td><a name="FSText_3">offsetY</a></td>
<td>The offset, in twips, relative to the bottom of the bounding rectangle of the 
text block where the text will be displayed. Optional. Set to the height of the 
font if only a single line of text is being displayed so the characters are placed 
correctly within the bounding rectangle defined for the text object.</td>
</tr>

<tr>
<td><a name="FSText_4">height</a></td>
<td>The height of the font, in twips,  used to render the characters. Optional. 
Set to zero if the font size is not being changed.</td>
</tr>

<tr>
<td><a name="FSText_5">characters</a></td>
<td>An array of FSCharacter objects which identify the glyph that will be displayed 
along with the spacing to the next character in the line of text.</td>
</tr>

</table>

<p>Whether the alpha channel in the colour needs to be specified depends on the 
class the FSText is added to. The FSDefineText2 class supports transparent text 
while FSDefineText class does not.</p>

<p>The x and y offsets are used to control how several FSText objects are laid 
out to create a block of text. The y offset is specified relative to the bottom 
edge of the bounding rectangle, which is actually closer to the top of the screen 
as the direction of the y-axis is from the top to the bottom of the screen. In this 
respect Flash is counter-intuitive. Lines with higher offset values are displayed 
below lines with lower offsets.</p>

<p>When several FSText objects are used to define a block of text using the FSDefineText 
or FSDefineText2 classes the attributes such as the font selected, size and colour 
must be specified in the first FSText object. For the remaining FSText objects 
these may be set to null or zero. The attributes will apply to all following FSText 
object until explicitly changed.</p>

<h1 class="datasheet">Examples</h1>

<p>The creation and layout of the glyphs to create the text is too onerous to 
perform from scratch. It is easier and more convenient to use existing font 
definitions either by parsing an existing Flash file or by converting a font 
definition from a specification such as TrueType in order to obtain the glyphs 
and layout information.</p>

<p>1. Creating a simple string.<br/>
This examples assumes a font definition that contains glyphs for the following 
set of characters ' ', 'a', 'b', 'c' .... 'x', 'y', 'z'. The font used fixed size 
for the spacing between glyphs .e.g. Courier.</p>

<pre>
FSVector&lt;FSCharacter&gt; characters;

characters.push_back(FSCharacter(1, 120));  // 'a'
characters.push_back(FSCharacter(0, 120));  // ' '
characters.push_back(FSCharacter(19, 120)); // 's'
characters.push_back(FSCharacter(10, 120)); // 't'
characters.push_back(FSCharacter(18, 120)); // 'r'
characters.push_back(FSCharacter(9, 120));  // 'i'
characters.push_back(FSCharacter(14, 120)); // 'n'
characters.push_back(FSCharacter(6, 120));  // 'g'

// Create the string setting the height to be 12-point (240 twips) and displaying 
// the characters in black. The text is not indented but is offset from the top
// of the bounding rectangle that encloses the text. The y-offset is set to the
// height of the font so it will leave a little space between the ascent of the
// largest character and the edge of the bounding rectangle so the text will be 
// displayed correctly.

int xOffset = 0;
int yOffset = 240;
int fontSize = 240;

FSText string(font.getIdentifier(), FSColorTable.black(), xOffset, yOffset, fontSize, characters);
</pre>

<p>2. Creating a block of text.<br/>
Again this examples assumes a fixed size font definition that contains glyphs for 
the set of characters.</p>

<pre>
FSVector&lt;FSCharacter&gt; line1;

line1.push_back(FSCharacter(19, 120)); // 's'
line1.push_back(FSCharacter(10, 120)); // 't'
line1.push_back(FSCharacter(18, 120)); // 'r'
line1.push_back(FSCharacter(9, 120));  // 'i'
line1.push_back(FSCharacter(14, 120)); // 'n'
line1.push_back(FSCharacter(6, 120));  // 'g'
line1.push_back(FSCharacter(0, 120));  // ' '
line1.push_back(FSCharacter(28, 120));  // '1'

// Create the string setting the height to be 12-point (240 twips) and 
// displaying the characters in black. The text is not indented.

int fontSize = 240;
int yOffset = 240;

FSText string1(font.getIdentifier(), FSColorTable.black(), 0, yOffset, fontSize, line1);


FSVector&lt;FSCharacter&gt; line2;

line2.push_back(FSCharacter(19, 120)); // 's'
line2.push_back(FSCharacter(10, 120)); // 't'
line2.push_back(FSCharacter(18, 120)); // 'r'
line2.push_back(FSCharacter(9, 120));  // 'i'
line2.push_back(FSCharacter(14, 120)); // 'n'
line2.push_back(FSCharacter(6, 120));  // 'g'
line2.push_back(FSCharacter(0, 120));  // ' '
line2.push_back(FSCharacter(29, 120));  // '2'

// Display the second string 'one line' height (240 twips) below the first. 
// The font size and colour remain unchanged.

yOffset += fontSize;

FSText string2(0, yOffset, line2);
</pre>

<h1 class="datasheet">History</h1>

<p>The FSText class represents both the TextRecordType0 and TextRecordType1 
structures from the Macromedia Flash (SWF) File Format Specification. It was 
introduced in Flash 1.</p> 

 */
    class DLL_DECL FSText : public FSTransformObject
    {
public:
        /** Definition of the different font encoding schemes supported in Flash. */
        enum encodingType { Unicode = 0, ANSI = 1, SJIS = 2 };

        enum languageType { 
            Latin = 1, /**< Identifies the spoken language for Latin fonts. */
            Japanese = 2, /**< Identifies the spoken language for Japanese fonts. */
            Korean = 3, /**< Identifies the spoken language for Japanese fonts. */
            SimplifiedChinese = 4, /**< Identifies the spoken language for simplified Chinese fonts. */
            TraditionalChinese = 5 /**< Identifies the spoken language for traditional Chinese fonts. */
        };

        FSText(FSInputStream* aStream);

        FSText() : identifier(0), color(), xOffset(Transform::VALUE_NOT_SET), yOffset(Transform::VALUE_NOT_SET), height(0), characters() {}

        /** Constructs an FSText object specifying the array of characters to be displayed. The selected font, text colour and height of the text will remain unchanged from previous settings. The x and y offsets default to 0.

            @param anArray an array of FSCharacter objects.
            */
        FSText(const FSVector<FSCharacter>& anArray) : identifier(0), color(), xOffset(Transform::VALUE_NOT_SET), yOffset(Transform::VALUE_NOT_SET), height(0), characters(anArray) {}

        /** Constructs an FSText object specifying the array of characters to be displayed and their relative placement within a block of text. The selected font, colour of the text and height will remain unchanged from previous settings.

            @param x the offset of the text relative to the left edge of the bounding rectangle enclosing the block of text.
            @param y the offset of the text relative to the bottom edge of the bounding rectangle enclosing the block of text.
            @param anArray an array of FSCharacter objects.
            */
        FSText(int x, int y, const FSVector<FSCharacter>& anArray) : identifier(0), color(), xOffset(x), yOffset(y), height(0), characters(anArray) {}

        /** Constructs an FSText object, specifying the colour and position of the following FSText.

            @param anIdentifier the identifier of the font that the text will be rendered in.
            @param aColor the colour of the text.
            @param x the offset of the text relative to the left edge of the bounding rectangle enclosing the text.
            @param y the offset of the text relative to the bottom edge of the bounding rectangle enclosing the text.
            @param aHeight the height of the text in the chosen font.
            @param anArray an array of FSCharacter objects.
            */
        FSText(int anIdentifier, const FSColor& aColor, int x, int y, int aHeight, const FSVector<FSCharacter>& anArray) : identifier(anIdentifier), color(aColor), xOffset(x), yOffset(y), height(0), characters(anArray)
        {
            setHeight(aHeight);
        }

        FSText* clone() const { return new FSText(*this); }

        const char* className() const;

        /** Adds an FSCharacter object to the end of the characters array.

            @param anObject an FSCharacter object.
            */
        void add(const FSCharacter& anObject) {  characters.push_back(anObject); }

        /** Adds all the FSCharacter object in the array to the end of the characters array.

            @param anArray an array of FSCharacter objects.
            */
        void add(const FSVector<FSCharacter>& anArray);

        /** Gets the identifier of the font in which the text will be displayed.

            @return the identifier of the font.
            */
        int getIdentifier() const { return identifier; }

        /** Gets the colour of the font in which the text will be displayed.

            @return the colour of the text.
            */
        FSColor& getColor() { return color; }

        /** Gets the offset of the start of the text relative to the left edge of the bounding rectangle in twips.

            @return the indentation applied to the text.
            */
        int getXOffset() const { return xOffset; }

        /** Gets the offset of the start of the text relative to the bottom edge of the bounding rectangle in twips.

            @return the location of the text relative to the bottom of the bounding rectangle.
            */
        int getYOffset() const { return yOffset; }

        /** Gets the height of the text.

            @return the height of the font used to displayed the text.
            */
        int getHeight() const { return height; }

        /** Gets the array of characters to be displayed.

            @return the array of FSCharacter objects.
            */
        FSVector<FSCharacter>& getCharacters() { return characters; }

        /** Sets the identifier of the font in which the text will be displayed.

            @param anIdentifier the identifier of the font that the text will be rendered in.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the colour of the font in which the text will be displayed.

            @param aColor the colour of the text.
            */
        void setColor(const FSColor& aColor) { color = aColor; }

        /** Sets the offset of the start of the text relative to the left edge of the bounding rectangle in twips.

            @param aNumber the location of the text relative to the left edge of the bounding rectangle enclosing the text.
            */
        void setXOffset(int aNumber) { xOffset = aNumber; }

        /** Sets the offset of the start of the text relative to the bottom edge of the bounding rectangle in twips.

            @param aNumber the location of the text relative to the bottom edge of the bounding rectangle enclosing the text.
            */
        void setYOffset(int aNumber) { yOffset = aNumber; }

        /** Sets the height of the text.

            @param aNumber the height of the text in the chosen font.
            */
        void setHeight(int aNumber) { height = aNumber; }

        /** Sets the array of characters to be displayed.

            @param anArray an array of FSCharacter objects.
            */
        void setCharacters(const FSVector<FSCharacter>& anArray) { characters = anArray; }

        int glyphBits() const;
        int advanceBits() const;

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool containsStyle() const;
        bool containsFont() const;
        bool containsXOffset() const;
        bool containsYOffset() const;

        int identifier;
        FSColor color;
        int xOffset;
        int yOffset;
        int height;

        FSVector<FSCharacter> characters;
    };
}

#endif

