/*
 *  FSDefineFont2.h
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

#ifndef __FSDefineFont2_h__
#define __FSDefineFont2_h__

#include "FSDefineObject.h"

#include "FSString.h"
#include "FSVector.h"
#include "FSShape.h"
#include "FSBounds.h"
#include "FSText.h"
#include "FSKerning.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<int>;
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSBounds>;
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSKerning>;
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSShape>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSDefineFont2 defines the shapes and layout of the glyphs used in a font. 
 * 
<p>It extends the functionality provided by the FSDefineFont class by:</p>

<ul>
<li>allowing more than 65535 glyphs in a particular font.</li>
<li>including the functionality provided by the FontInfo class.</li>
<li>specifying ascent, descent and leading layout information for the font.</li>
<li>specifying advances for each glyph.</li>
<li>specifying bounding rectangles for each glyph.</li>
<li>specifying kerning pairs defining the distance between pairs of glyphs.</li>
</ul>

<p>The FSDefineFont2 class combines the attributes of the FSFontInfo and FSDefineFont classes:</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSDefineFont2_0">type</a></td>
<td>Identifies the data structure when it is encoded. The type attribute is read-only and may be used when iterating through the objects in an FSMovie object to identify the object class without using run-time type checking.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_1">identifier</a></td>
<td>The unique identifier for this object.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_2">encoding</a></td>
<td>Specifies whether the font codes are ANSI, SJIS or Unicode.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_3">language</a></td>
<td>Identifies the spoken language for the font, either FSText.Japanese, FSText.Korean, 
FSText.Latin, FSText.SimplifiedChinese, FSText.TraditionalChinese. This attribute 
is used when displaying text fields and assists in determining language-appropriate
line breaks.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_4">italic</a></td>
<td>Whether the font is italicised.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_5">bold</a></td>
<td>Whether the font is bold.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_6">small</a></td>
<td>Small point size fonts will be drawn aligned to pixel boundaries to improve rendering.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_7">name</a></td>
<td>The name of the font.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_8">shapes</a></td>
<td>An array of FSShape objects that define the outline for each glyph.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_9">codes</a></td>
<td>An array mapping a glyph index to a particular character code in the font.</td>
</tr>

</table>

<p>Additional layout information for the glyphs in the font can also be specified through the following set of attributes:</p>

<table class="datasheet">

<tr>
<td><a name="FSDefineFont2_10">ascent</a></td>
<td>The maximum ascent for the font in twips.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_11">descent</a></td>
<td>The maximum descent for the font in twips.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_12">leading</a></td>
<td>The leading for the font.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_13">advances</a></td>
<td>An array of integers that define the advance for each glyph in the font.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_14">bounds</a></td>
<td>An array of FSBounds object that define the bounding rectangle for each glyph in the font.</td>
</tr>

<tr>
<td><a name="FSDefineFont2_15">kernings</a></td>
<td>An array of FSKerning objects that define adjustment to the advance for particular pairs of glyphs in the font.</td>
</tr>
</table>

<p>The default values for the ascent, descent and leading attributes is zero and the arrays containing the advances, bounds and kernings are empty. If the attributes all set to their default values then the layout information will not be encoded. All the values must be set and the arrays must contain the same number of entries as there are glyphs before the layout information will be encoded.</p>

<h1 class="datasheet">History</h1>

<p>The FSDefineFont2 class represents the DefineFont2 structure from the Macromedia 
Flash (SWF) File Format Specification. It was introduced in Flash 2. Support for
spoken languages was added in Flash 6. Support for small point size fonts was 
added in Flash 7.</p>

 */
    class DLL_DECL FSDefineFont2 : public FSDefineObject
    {
public:
        FSDefineFont2(FSInputStream* aStream);
        
        /** 
         * Constructs an FSDefineFont2 object specifying only the name of the font. 
         *
         * If none of the remaining attributes are set the Flash Player will load the font from the system
         * on which it is running or substitute a suitable font if the specified font cannot be found. This 
         * is particularly useful when defining fonts that will be used to display text in FSDefineTextField 
         * objects.
         *
         * The font will be defined to use Unicode encoding. The flags which define the font's face will be 
         * set to false. The arrays  of glyphs which define the shapes and the code which map the character 
         * codes to a particular glyph will remain empty since the font is loaded from the system on which 
         * it is displayed.
         *
         * @param anIdentifier the unique identifier for this object.
          * @param fontName the name of the font.
         */
        FSDefineFont2(int anIdentifier, const char* fontName) : 
            FSDefineObject(DefineFont2, anIdentifier),
            wideOffsets(false),
            encoding(FSText::Unicode), 
            small(false), 
            italic(false), 
            bold(false),
            language(1),
            name(fontName), 
            shapes(), 
            codes(), 
            ascent(0), 
            descent(0), 
            leading(0), 
            advances(), 
            bounds(), 
            kernings() 
            {}
    
        FSDefineFont2* clone() const { return new FSDefineFont2(*this); }

        const char* className() const;

        /** Add a shape to the array of shapes.

            @param anObject a shape.
            */
        void add(const FSShape& anObject) { shapes.push_back(anObject); }

        /** Add all the shapes in the array to the end of the shapes array.

            @param anArray an array of shapes.
            */
        void add(const FSVector<FSShape>& anArray);

        /** Add a code to the array of codes.

            @param aCode a code for a glyph.
            */
        void addCode(int aCode) { codes.push_back(aCode); }

        /** Add all the codes in the array to the end of the codes array.

            @param anArray an array of shapes.
            */
        void addCode(const FSVector<int>& anArray);

        /** Add an advance to the array of advances.

            @param anAdvance an advance for a glyph.
            */
        void addAdvance(int anAdvance) { advances.push_back(anAdvance); }

        /** Add all the advances in the array to the end of the advances array.

            @param anArray an array of shapes.
            */
        void addAdvance(const FSVector<int>& anArray);

        /** Add a bounds object to the array of bounds for each glyph.

            @param anObject an FSBounds.
            */
        void add(const FSBounds& anObject) { bounds.push_back(anObject); }

        /** Add all the FSBounds objects in the array to the end of the bounds array.

            @param anArray an array of FSBounds objects.
            */
        void add(const FSVector<FSBounds>& anArray);

        /** Add a kerning object to the array of kernings for pairs of glyphs.

            @param anObject an FSKerning.
            */
        void add(const FSKerning& anObject) { kernings.push_back(anObject); }

        /** Add all the FSKerning objects in the array to the end of the kernings array.

            @param anArray an array of FSKerning objects.
            */
        void add(const FSVector<FSKerning>& anArray);

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

        /**
         * Gets the language code identifying the type of spoken language for the font
         * either FSText::Japanese, FSText::Korean, FSText::Latin, FSText::SimplifiedChinese 
         * or FSText::TraditionalChinese.
         * 
         * @return the language code used to determine how line-breaks are inserted 
         * into text rendered using the font. Returns 0 if the object was decoded 
         *  from a movie contains Flash 5 or less.
         */
        int getLanguage() { return language; }

        /** Gets the name of the font family.

            @return the name of the font.
            */
        const char* getName() { return name.c_str(); }

        /** Gets the array of shapes used to define the outlines of each font glyph.

            @return an array of FSShape objects
            */
        FSVector<FSShape>& getShapes() { return shapes; }

        /** Gets the array of codes used to identify each glyph in the font. The ordinal position of each int representing a code identifies a particular glyph in the shapes array.

            @return an array of integers that contain the character codes for each glyph in the font.
            */
        FSVector<int>& getCodes() { return codes; }

        /** Gets the ascent for the font in twips.

            @return the ascent for the font.
            */
        int getAscent() const { return ascent; }

        /** Gets the descent for the font in twips. 

            @return the descent for the font.
            */
        int getDescent() const { return descent; }

        /** Gets the leading for the font in twips.

            @return the leading for the font.
            */
        int getLeading() const { return leading; }

        /** Gets the array of advances defined for each glyph in the font. 

            @return an array of integers that contain the advance for each glyph in the font.
            */
        FSVector<int>& getAdvances() { return advances; }

        /** Gets the array of bounding rectangles defined for each glyph in the font. 

            @return an array of FSBounds objects.
            */
        FSVector<FSBounds>& getBounds() { return bounds; }

        /** Gets the array of kerning records that define the spacing between glyph pairs.

            @return an array of FSKerning objects that define the spacing adjustment between pairs of glyphs.
            */
        FSVector<FSKerning>& getKernings() { return kernings; }

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

        /**
         * Sets the language code used to determine the position of line-breaks in 
         * text rendered using the font.
         * 
         * NOTE: The language attribute is ignored if the object is encoded in a Flash 5 movie.
         * 
         * @param code the code identifying the spoken language either FSText::Japanese, 
         * FSText::Korean, FSText::Latin, FSText::SimplifiedChinese or FSText.TraditionalChinese.
         */
        void setLanguage(int code) { language = code; }

        /** Set the name of the font.

            @param aString the name assigned to the font, identifying the font family.
            */
        void setName(const char* aString) { name = aString; }

        /** Set the array of shape records that define the outlines of the characters used from the font.

            @param anArray an array of FSShape objects that define the glyphs for the font.
            */
        void setShapes(const FSVector<FSShape>& anArray) { shapes = anArray; }

        /** Sets the codes used to identify each glyph in the font.

            @param anArray an array of int mapping a particular glyph to a character code.
            */
        void setCodes(const FSVector<int>& anArray) { codes = anArray; }

        /** Sets the ascent for the font in twips.

            @param aNumber the ascent for the font.
            */
        void setAscent(int aNumber) { ascent = aNumber; }

        /** Sets the descent for the font in twips.

            @param aNumber the descent for the font.
            */
        void setDescent(int aNumber) { descent = aNumber; }

        /** Sets the leading for the font in twips.

            @param aNumber the leading for the font.
            */
        void setLeading(int aNumber) { leading = aNumber; }

        /** Sets the array of advances for each glyph in the font.

            @param anArray of integers that define the spacing between glyphs.
            */
        void setAdvances(const FSVector<int>& anArray) { advances = anArray; }

        /** Sets the array of bounding rectangles for each glyph in the font.

            @param anArray an array of FSBounds objects that define the bounding rectangles that enclose each glyph in the font.
            */
        void setBounds(const FSVector<FSBounds>& anArray) { bounds = anArray; }

            /** Sets the array of kerning records for pairs of glyphs in the font.

            @param anArray an array of FSKerning objects that define an adjustment applied to the spacing between pairs of glyphs.
            */
        void setKernings(const FSVector<FSKerning>& anArray) { kernings = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool containsLayoutInfo() const;

        bool wideOffsets;

        int encoding;
        bool small;
        bool italic;
        bool bold;

        int language;
        
        FSString name;
        
        FSVector<FSShape> shapes;
        FSVector<int> codes;
        
        int ascent;
        int descent;
        int leading;
        
        FSVector<int> advances;
        FSVector<FSBounds> bounds;
        FSVector<FSKerning> kernings;
    };
}

#endif

