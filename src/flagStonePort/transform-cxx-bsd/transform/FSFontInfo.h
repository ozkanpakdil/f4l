/*
 *  FSFontInfo.h
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

#ifndef __FSFontInfo_h__
#define __FSFontInfo_h__

#include "FSMovieObject.h"

#include "FSString.h"
#include "FSVector.h"
#include "FSShape.h"
#include "FSBounds.h"
#include "FSText.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<int>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSFontInfo defines the name and face of a font and maps the codes for a given character 
 * set to the glyphs that are drawn to represent each character.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSFontInfo_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSFontInfo_1">identifier</a></td>
<td>The unique identifier, in the range 1..65535, for the FSDefineFont object that contains the glyphs for the font.</td>
</tr>

<tr>
<td><a name="FSFontInfo_2">name</a></td>
<td>The name of the font.</td>
</tr>

<tr>
<td><a name="FSFontInfo_3">encoding</a></td>
<td>Specifies whether the codes for the character set are represented using ANSI (ASCII), SJIS or Unicode.</td>
</tr>

<tr>
<td><a name="FSFontInfo_4">bold</a></td><td>Indicates the font is small enough to align to pixel boundaries.</td>
</tr>

<tr>
<td><a name="FSFontInfo_5">bold</a></td><td>Whether the font is bold.</td>
</tr>

<tr>
<td><a name="FSFontInfo_6">italic</a></td><td>Whether the font is rendered in italics.</td>
</tr>

<tr>
<td><a name="FSFontInfo_7">isSmall</a></td>
<td>Indicates the font is small enough to align to pixel boundaries.</td>
</tr>

<tr>
<td><a name="FSFontInfo_8">codes</a></td>
<td>An array mapping a glyph index to a particular character code in the font.</td>
</tr>
</table>

<p>The ANSI character set is used for Latin languages, SJIS is used for Japanese 
language characters and Unicode is used for any character set. The encoding 
attributes uses the constants FSText.ANSI, FSText.SJIS or FSText.Unicode 
for each character set type.</p>

<p>The index of each entry in the codes array matches the index in the corresponding 
glyph in the shapes array of an FSDefineFont object, allowing a given character 
code to be mapped to a given glyph.</p>

<p>The class allows the font associated with a Flash file to be mapped to a font 
installed on the device where the Flash Player displaying the file is hosted. 
The use of a font from a device is not automatic but is determined by the HTML 
tag option <i>deviceFont</i> which is passed to the Flash Player when it is first 
started. If a device does not support a given font then the glyphs in the FSDefineFont 
class are used to render the characters.</p>

<p>An important distinction between the host device to specify the font and using 
the glyphs in an FSDefineFont object is that the device is not anti-aliased and 
the rendering is dependent on the host device. The glyphs in an FSDefineFont 
object are anti-aliased and are guaranteed to look identical on every device the 
text is displayed.</p>

<h1 class="datasheet">History</h1>

<p>The FSFontInfo class represents the DefineFontInfo data structure from the 
Flash specification. It was introduced in Flash 1. Support for small fonts was 
added in Flash 7.</p>

 */
    class DLL_DECL FSFontInfo : public FSMovieObject
    {
public:
        FSFontInfo(FSInputStream* aStream);

        /** Constructs an FSFontInfo object.

         @param anIdentifier the unique identifier of the FSDefineFont that contains the glyphs for the font.
         @param fontName the name assigned to the font, identifying the font family.
         */
        FSFontInfo(int anIdentifier, const char* fontName) : 
            FSMovieObject(FontInfo), 
            identifier(anIdentifier),
            name(fontName), 
            encoding(FSText::Unicode),
            small(false),
            italic(false), 
            bold(false), 
            codes() {} 

        FSFontInfo* clone() const { return new FSFontInfo(*this); }

        const char* className() const;

        /** Gets the identifier of the font that this font information is for.

            @return the identifier of the FSDefineFont object that contains the glyphs for the font.
            */
        int getIdentifier() const { return identifier; }

        /** Gets the name of the font family.

            @return the name of the font.
            */
        const char* getName() { return name.c_str(); }

        /** Gets the encoding used for the font codes, either Unicode, ShiftJIS or ASCII.

            @return the encoding used to represent characters rendered in the font.
            */
        int getEncoding() const { return encoding; }

        /** Does the font have a small point size. This is used only with a Unicode font encoding.

            @return a boolean indicating whether the font will be aligned on pixel boundaries.
            */
        bool isSmall() { return small; }

        /** Is the font italicized.

            @return a bool indicating whether the font is rendered in italics.
            */
        bool isItalic() const { return italic; }

        /** Is the font bold.

            @return a bool indicating whether the font is rendered in a bold face.
            */
        bool isBold() const { return bold; }

        /** Gets the array of codes used to identify each glyph in the font. The ordinal position of each int representing a code identifies a particular glyph in the shapes array.

            @return an array of integers that contain the character codes for each glyph in the font.
            */
        FSVector<int>& getCodes() { return codes; }

        /** Sets the identifier of the font that this font information is for.

            @param anIdentifier the unique identifier of the FSDefineFont that contains the glyphs for the font.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Set the name of the font.

            @param aString the name assigned to the font, identifying the font family.
            */
        void setName(const char* aString) { name = aString; }

        /** Sets the encoding for the font character codes.

            @param aType the encoding scheme used to denote characters, either Unicode, ShiftJIS or ASCII.
            */
        void setEncoding(int aType) { encoding = aType; }

        /** Sets the font is small. Used only with Unicode fonts.

            @param aBool a boolean flag indicating the font will be aligned on pixel boundaries.
            */
        void setSmall(bool aBool) { small = aBool; }

        /** Set the font is italicized.

            @param aBool a bool flag indicating whether the font will be rendered in italics.
            */
        void setItalic(bool aBool) { italic = aBool; }

        /** Set the font is bold. 

            @param aBool a bool flag indicating whether the font will be rendered in bold face.
            */
        void setBold(bool aBool) { bold = aBool; }

        /** Sets the codes used to identify each glyph in the font.

            @param anArray an array of int mapping a particular glyph to a character code.
            */
        void setCodes(const FSVector<int>& anArray) { codes = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
        
        FSString name;
        
        int encoding;
        bool small;
        bool italic;
        bool bold;
        
        FSVector<int> codes;
    };
}

#endif

