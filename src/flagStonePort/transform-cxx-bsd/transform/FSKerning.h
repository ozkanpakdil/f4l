/*
 *  FSKerning.h
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

#ifndef __FSKerning_h__
#define __FSKerning_h__ 1

#include "FSTransformObject.h"

namespace transform
{
/**
 * %FSKerning describes the spacing between a pair of glyphs. 
 * 
<p>The kerning is used to fine-tune the spacing between specific pairs of characters to make them visually more appealing. The glyphs are identified by an index into the glyph table for the font. The adjustment is specified relative to the advance define for the left glyph.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSKerning_0">leftGlyphIndex</a></td>
<td>The index into the code table that identifies the glyph on the left side of the pair.</td>
</tr>

<tr>
<td><a name="FSKerning_1">rightGlyphIndex</a></td>
<td>The index into a code table that identifies the glyph on the right side of the pair.</td>
</tr>

<tr>
<td><a name="FSKerning_2">adjustment</a></td>
<td>The adjustment in twips that will be added to the advance for the glyph on the left side of the pair to obtain the final spacing between the glyphs.</td>
</tr>

</table>

<p>FSKerning objects are only used within FSDefineFont2 objects and provide more precise control over the layout of a font's glyph than was possible using the FSDefineFont and FSFontInfo objects.</p>

<h1 class="datasheet">History</h1>

<p>FSKerning class represents the KerningRecord from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 2.</p>

 */
    class DLL_DECL FSKerning : public FSTransformObject
    {
public:
        FSKerning(FSInputStream* aStream);

        FSKerning() : leftGlyphIndex(0), rightGlyphIndex(0), adjustment(0) {}

        /** Constructs an FSKerning object specifying the glyph indexes and adjustment. The value for the adjustment must be specified in twips.
    
            @param leftIndex the index in a code table for the glyph on the left side of the pair.
            @param rightIndex the index in a code table for the glyph on the right side of the pair.
            @param adjust the adjustment that will be added to the advance defined for the left glyph.
            */
        FSKerning(int leftIndex, int rightIndex, int adjust) : leftGlyphIndex(leftIndex), rightGlyphIndex(rightIndex), adjustment(adjust) {}

        FSKerning* clone() const { return new FSKerning(*this); }

        const char* className() const;

        /** Gets the index of the left glyph in the kerning pair.

            @return the index in a code table for the glyph on the left side of the pair.
            */
        int getLeftGlyphIndex() const { return leftGlyphIndex; }

        /** Gets the index of the right glyph in the kerning pair.

            @return the index in a code table for the glyph on the right side of the pair.
            */
        int getRightGlyphIndex() const { return rightGlyphIndex; }

        /** Gets the adjustment, in twips, to the advance of the left glyph.

            @return the adjustment that will be added to the advance defined for the left glyph.
            */
        int getAdjustment() const { return adjustment; }

        /** Sets the index of the left glyph in the kerning pair.

            @param anIndex the index in a code table for the glyph on the left side of the pair.
            */
        void setLeftGlyphIndex(int anIndex) { leftGlyphIndex = anIndex; }

        /** Sets the index of the right glyph in the kerning pair.

            @param anIndex the index in a code table for the glyph on the right side of the pair.
            */
        void setRightGlyphIndex(int anIndex) { rightGlyphIndex = anIndex; }

        /** Sets the adjustment, in twips, to the advance of the left glyph.

            @param aNumber the adjustment that will be added to the advance defined for the left glyph.
            */
        void setAdjustment(int aNumber) { adjustment = aNumber; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int leftGlyphIndex;
        int rightGlyphIndex;
        int adjustment;
    };
}

#endif
