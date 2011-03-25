/*
 *  FSGradient.h
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

#ifndef __FSGradient_h__
#define __FSGradient_h__ 1

#include "FSTransformObject.h"

#include "FSColor.h"

namespace transform
{
/**
 * %FSGradient defines a control point that is used to specify how a gradient colour is displayed. 
 * 
<p>Two or more control points are used to define how the colour changes across the gradient square. Each control point specifies:</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSGradient_0">ratio</a></td>
<td>The location of the control point across the gradient square.</td>
</tr>

<tr><td><a name="FSGradient_1">color</a></td>
<td>The colour displayed at the control point.</td>
</tr>
</table>

<p>The location of the control point is defined by a ratio - a number between 0 and 255 - that specifies the relative location in the square. For Linear Gradient Fills a ratio of zero is mapped to the left side of the gradient square and 255 is mapped to the right side of the square. For Radial Gradient Fills a ratio of zero is mapped to the centre of the gradient square and 255 is mapped to the edge of the largest circle that fits inside the gradient square. A ratio is used rather than specifying coordinates within the gradient square as the coordinate space is transformed to fit the shape that the gradient is being displayed in.</p>

<p>Note that the object used to create the shape definition determines whether the alpha channel is encoded in the gradient colours. Simply specifying the level of transparency in the FSColor object is not sufficient.</p>

<h1 class="datasheet">History</h1>

<p>The FSGradient class represents the GradientRecord structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSGradient : public FSTransformObject
    {
public:
        FSGradient(FSInputStream* aStream);

        FSGradient() : ratio(0), color() {}

        /** Constructs an FSGradient object with the specified ratio and color.

            @param aRatio the ratio along the gradient square.
            @param aColor the color at the control point.
            */
        FSGradient(int aRatio, const FSColor& aColor) : ratio(aRatio), color(aColor) {}

        FSGradient* clone() const { return new FSGradient(*this); }

        const char* className() const;

        /** Gets the ratio that defines the relative point across the gradient square.

            @return the ratio where the control point is located.
            */
        int getRatio() const { return ratio; }

        /** Gets the colour that is displayed at the control point across the gradient square defined by the ratio.

            @return the color at the control point.
            */
        FSColor& getColor() { return color; }

        /** Sets the ratio that defines the control point across the gradient square.

            @param aNumber the ratio along the gradient square.
            */
        void setRatio(int aNumber) { ratio = aNumber; }

        /** Sets the colour that is displayed at the control point across the gradient square.

            @param aColor the color at the control point.
            */
        void setColor(const FSColor& aColor) { color = aColor; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int ratio;
        
        FSColor color;
    };
}

#endif

