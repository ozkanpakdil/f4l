/*
 *  FSMorphSolidLine.h
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

#ifndef __FSMorphSolidLine_h__
#define __FSMorphSolidLine_h__

#include "FSLineStyle.h"

#include "FSColor.h"

namespace transform
{
/**
 * %FSMorphSolidLine defines the width and colour of a line drawn for a morphing shape. 
 * 
<p>It specifies the width and colour of the line at the start and end of the morphing process. The transparency value for the colour should also be specified. As with the FSSolidLine class all lines are drawn with rounded corners and end caps. Different join and line end styles can be created by drawing very narrow shapes.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSMorphSolidLine_0">startWidth</a></td>
<td>The width of the line at the start of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphSolidLine_1">startColor</a></td>
<td>The colour applied to the line at the start of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphSolidLine_2">endWidth</a></td>
<td>The width of the line at the end of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphSolidLine_3">endColor</a></td>
<td>The colour applied to the line at the end of the morphing process.</td>
</tr>
</table>

<p>The FSDefineMorphShape object support transparent colours so alpha channel information must be specified in the colour objects.</p>

<h1 class="datasheet">History</h1>

<p>The FSMorphSolidLine class represents the MorphLineStyle structure from the Macromedia Flash (SWF) File Format Specification. Shape morphing was introduced in Flash 3.</P>

 */  
    class DLL_DECL FSMorphSolidLine : public FSLineStyle
    {
public:
        FSMorphSolidLine(FSInputStream* aStream);
        
        /** Constructs an FSMorphSolidLine object specifying the starting and ending widths and colors.
        
            @param aStartWidth the width of the line at the start of the morphing process.
            @param anEndWidth the width of the line at the end of the morphing process.
            @param aStartColor the colour of the line at the start of the morphing process.
            @param anEndColor the colour of the line at the end of the morphing process.
            */
        FSMorphSolidLine(int aStartWidth, int anEndWidth, const FSColor& aStartColor, const FSColor& anEndColor) : startWidth(aStartWidth), endWidth(anEndWidth), startColor(aStartColor), endColor(anEndColor) {}

        FSMorphSolidLine* clone() const { return new FSMorphSolidLine(*this); }

        const char* className() const;
         
        /** Gets the width of the line at the start of the morphing process.

            @return the starting width of the line.
            */
        int getStartWidth() { return startWidth; }
        
        /** Gets the width of the line at the end of the morphing process. 
            
            @return the ending width of the line.
            */
        int getEndWidth() { return endWidth; }

        /** Gets the colour of the line at the start of the morphing process.

            @return the starting colour of the line.
            */
        FSColor& getStartColor() { return startColor; }

        /** Gets the colour of the line at the end of the morphing process.

            @return the ending colour of the line.
            */
        FSColor& getEndColor() { return endColor; }

        /** Sets the width of the line at the start of the morphing process. 

            @param aNumber the starting width of the line.
            */
        void setStartWidth(int aNumber) { startWidth = aNumber; }

        /** Sets the width of the line at the end of the morphing process.
        
            @param aNumber the ending width of the line.
            */
        void setEndWidth(int aNumber) { endWidth = aNumber; }

        /** Gets the colour of the line at the start of the morphing process.

            @param aColor the starting colour of the line.
            */
        void setStartColor(const FSColor& aColor) { startColor = aColor; }

        /** Sets the colour of the line at the end of the morphing process.

            @param aColor the ending colour of the line.
            */
        void setEndColor(const FSColor& aColor) { endColor = aColor; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int startWidth;
        int endWidth;
        
        FSColor startColor;
        FSColor endColor;        
    };
}

#endif
