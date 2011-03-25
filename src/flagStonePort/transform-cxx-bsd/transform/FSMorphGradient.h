/*
 *  FSMorphGradient.h
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

#ifndef __FSMorphGradient_h__
#define __FSMorphGradient_h__

#include "FSTransformObject.h"

#include "FSColor.h"

namespace transform
{
/**
 * %FSMorphGradient defines the control points that is used to specify how a gradient fill is 
 * displayed at the start and end of the shape morphing process. 
 * 
<p>Two or more control points are used to define how the colour changes across the gradient square.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSMorphGradient_0">startRatio</a></td>
<td>The location of the control point across the gradient square at the start of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphGradient_1">endRatio</a></td>
<td>The location of the control point across the gradient square at the end of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphGradient_2">startColor</a></td>
<td>The colour at the control point at the start of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphGradient_3">startColor</a></td>
<td>The colour at the control point at the end of the morphing process.</td>
</tr>
</table>

<p>The location of the control point is defined by a ratio - a number between 0 and 255 that specifies the relative location in the square. For Linear Gradient Fills a ratio of zero is mapped to the left side of the gradient square and 255 is mapped to the right side of the square. For Radial Gradient Fills a ratio of zero is mapped to the centre of the gradient square and 255 is mapped to the edge of the largest circle that fits inside the gradient square.</p>

<p>FSMorphGradients are only used in FSDefineMorphShape objects which support transparent colours so values for all the colour channels must be specified in the FSColor objects.</p>

<p>When the Flash Player displays the gradient control points they are sorted by the ratio with the FSGradient object with the smallest ratio value displayed first.</p>

<h1 class="datasheet">History</h1>

<p>The FSMorphGradient class represents the MorphGradientRecord structure from the Macromedia Flash (SWF) File Format Specification. Shape morphing was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSMorphGradient : public FSTransformObject
    {
public:
        FSMorphGradient(FSInputStream* aStream);

        FSMorphGradient() : startRatio(0), endRatio(0), startColor(), endColor() {}

        /**
        Constructs an FSMorphGradient object specifying the starting and ending ratios and colors.

         @param aStartRatio the ratio along the gradient square at the start of the morphing process.
         @param anEndRatio the ratio along the gradient square at the end of the morphing process.
         @param aStartColor the colour at the starting control point.
         @param anEndColor the colour at the ending control point.
         */
        FSMorphGradient(int aStartRatio, int anEndRatio, const FSColor& aStartColor, const FSColor& anEndColor) : startRatio(aStartRatio), endRatio(anEndRatio), startColor(aStartColor), endColor(anEndColor) {}

        FSMorphGradient* clone() const { return new FSMorphGradient(*this); }

        const char* className() const;

        /** Gets the ratio at the start of the morphing process.

            @return the start ratio.
            */
        int getStartRatio() { return startRatio; }

        /** Gets the ratio at the end of the morphing process.

            @return the end ratio.
            */
        int getEndRatio() { return endRatio; }

        /** Gets the colour at the start of the morphing process.

            @return the starting colour.
            */
        FSColor& getStartColor() { return startColor; }

        /** Gets the colour at the end of the morphing process.

            @return the ending colour.
            */
        FSColor& getEndColor() { return endColor; }

        /** Sets the ratio along the gradient square at the start of the morphing process.

         @param aNumber the starting ratio.
         */
        void setStartRatio(int aNumber) { startRatio = aNumber; }

        /** Sets the ratio along the gradient square at the end of the morphing process.

         @param aNumber the ending ratio.
         */
        void setEndRatio(int aNumber) { endRatio = aNumber; }

        /** Sets the colour at the start of the morphing process.

            @param aColor the starting colour.
            */
        void setStartColor(const FSColor& aColor) { startColor = aColor; }

        /** Sets the colour at the end of the morphing process.

            @param aColor the ending colour.
            */
        void setEndColor(const FSColor& aColor) { endColor = aColor; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int startRatio;
        int endRatio;
        
        FSColor startColor;
        FSColor endColor;        
    };
}

#endif
