/*
 *  FSMorphSolidFill.h
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

#ifndef __FSMorphSolidFill_h__
#define __FSMorphSolidFill_h__

#include "FSFillStyle.h"

#include "FSColor.h"

namespace transform
{
/**
 * %FSMorphSolidFill defines the solid colours that are used to fill a morphing shape at 
 * the start and end of the morphing process.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSMorphSolidFill_0">type</a></td>
<td>Identifies the data structure when it is encoded.</td>
</tr>

<tr>
<td><a name="FSMorphSolidFill_1">startColor</a></td>
<td>The colour applied to the shape at the start of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphSolidFill_2">startColor</a></td>
<td>The colour applied to the shape at the end of the morphing process.</td>
</tr>

</table>

<p>The parent class, FSFillStyle allows the type to be set. This should only be used for manipulating bitmap and gradient fill styles.</p> 

<p>The FSMorphSolidFill object is added to a FSDefineMorphShape so both the start colour and end colour should have a value specified for the alpha channel that defines how transparent the colour is.</p>

<pre>
FSColor red(255, 0, 0, 128);
FSColor green(0, 255, 0, 128);
FSMorphSolidFill* fill = new FSMorphSolidFill(red, green);
</pre>

<h1 class="datasheet">History</h1>

<p>The FSMorphSolidFill class represents the MorphFillStyle structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSMorphSolidFill : public FSFillStyle
    {
public:
        FSMorphSolidFill(FSInputStream* aStream);
        
        /** Constructs an FSMorphSolidFill object specifying the starting and ending colors.
        
            @param aStartColor the colour at the start of the morphing process.
            @param anEndColor the colour at the end of the morphing process.
            */
        FSMorphSolidFill(const FSColor& aStartColor, const FSColor& anEndColor) : FSFillStyle(Solid), startColor(aStartColor), endColor(anEndColor) {}

        FSMorphSolidFill* clone() const { return new FSMorphSolidFill(*this); }

        const char* className() const;

        /** Gets the colour at the start of the morphing process.

            @return the starting colour.
            */
        FSColor& getStartColor() { return startColor; }

        /** Gets the colour at the end of the morphing process.

            @return the end colour.
            */
        FSColor& getEndColor() { return endColor; }

        /** Sets the colour at the start of the morphing process.

            @param aColor the start colour.
            */
        void setStartColor(const FSColor& aColor) { startColor = aColor; }

        /** Sets the colour at the end of the morphing process.

            @param aColor the end colour.
            */
        void setEndColor(const FSColor& aColor) { endColor = aColor; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSColor startColor;
        FSColor endColor;
    };
}

#endif

