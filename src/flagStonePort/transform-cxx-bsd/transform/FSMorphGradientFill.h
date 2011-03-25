/*
 *  FSMorphGradientFill.h
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

#ifndef __FSMorphGradientFill_h__
#define __FSMorphGradientFill_h__ 1

#include "FSVector.h"

#include "FSFillStyle.h"

#include "FSCoordTransform.h"
#include "FSMorphGradient.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSMorphGradient>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSMorphGradientFill defines how a colour changes across an area filled in a morphing shape. 
 * 
<p>Two type of gradient fill are supported:</p>

<table class="datasheet">

<tr>
<td>Linear</td>
<td>The gradient changes in one direction across the area to be filled.</td>
</tr>

<tr>
<td>Radial</td>
<td>The gradient changes radially from the centre of the area to be filled.</td>
</tr>

</table>

<p>Gradients are defined in terms of a  standard space called the gradient square, centred at (0,0) and extending from (-16384, -16384) to (16384, 16384).</p>

<img src="gradientSquare.gif">

<p>A coordinate transform is required to map the gradient square to the coordinates of the filled area. The transformation is applied in two steps. First the gradient square is scaled so the colour covers the shape followed by a translation to map the gradient square coordinates to the coordinate range of the shape.</p>

<img src="gradientMapping.gif">

<p>A series of control points is used to control how the colour displayed changes across the gradient. At least two control points are required to define a gradient - one for the starting colour and one for the final colour. Up to eight control points may be specified to generate complex colour transitions. When the Flash Player displays the control points they are sorted by the ratio defined in each FSGradient object, with the smallest ratio value displayed first.
</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSMorphGradientFill_0">type</a></td>
<td>The type of gradient fill, either FSFillStyle.Linear or FSFillStyle.Radial.</td>
</tr>

<tr>
<td><a name="FSMorphGradientFill_1">startTransform</a></td>
<td>The coordinate transform used to map the logical coordinates of the gradient square on to a set of physical coordinates at the start of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphGradientFill_1">endTransform</a></td>
<td>The coordinate transform used to map the logical coordinates of the gradient square on to a set of physical coordinates at the end of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphGradientFill_2">gradients</a></td>
<td>An array of up to eight FSGradient objects that define the control points across the gradient square that control the colour transitions. The Flash Player performs the interpolation of the colour values between the control points. Alpha channel (defining transparency) must be defined for the colour in each control point.</td>
</tr>
</table>

<p>In addition to specifying the type of gradient fill that will be displayed the type attribute may be used when iterating through an array of fill style objects to identify the type of fill style without using run-time type checking.</p>

<h1 class="datasheet">Example</h1>

<p>For the coordinate transformation, the scaling factor is calculated by diving the width of the gradient square by the width of the shape:</p>

<pre>
float gradientSquareWidth = 32768.0f;
float scale = gradientSquareWidth / shapeWidth; 
</pre>

<p>The translation is defined by calculating the difference between the minimum coordinates of the <em>scaled</em> gradient square and the minimum coordinates of the shape:

<pre>
int gradientX = -16384; // minimum x coordinate of the gradient square.
int gradientY = -16384; // minimum y coordinate of the gradient square.

// Get the minimum coordinates of the shape being filled;
int shapeX = shape.getBounds().getMinX();
int shapeY = shape.getBounds().getMinY();

// Now calculate the translation
int translateX = shapeX - (gradientX / scale);
int translateY = shapeY - (gradientY / scale);
</pre>

<p>The FSCoordTransform has a convenient constructor to create the two-step transformation:</p>

<pre>
FSCoordTransform composite(translateX, translateY, scale, scale);
</pre>

<p>The transform is independent of any transformation defined for the parent shape in which the gradient is displayed. The gradient will be displayed correctly if the shape is scaled, rotated, etc. when it is added to the display list.</p>

<p>The above process is repeated to calculate the transform for the gradient fill at the end of the morphing process. The transforms are independent of any transformation defined for the parent morphing shape in which the gradients are displayed.

<h1 class="datasheet">History</h1>

<p>The FSMorphGradientFill class represents the MorphFillStyle structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSMorphGradientFill : public FSFillStyle
    {
public:
        FSMorphGradientFill(FSInputStream* aStream);

        /** Constructs an FSMorphGradientFill object specifying the type of fill, starting and ending coordinate transforms and the array of gradient control points.

            @param aType the type of gradient fill, either FSFillStyle::LinearGradient or FSFillStyle::RadialGradient.
            @param aStartTransform the coordinate transform mapping the gradient square onto physical coordinates at the start of the morphing process.
            @param anEndTransform the coordinate transform mapping the gradient square onto physical coordinates at the end of the morphing process.
            @param anArray an array of up to eight FSMorphGradient objects defining the control points for the gradient.
            */
        FSMorphGradientFill(int aType, const FSCoordTransform& aStartTransform, const FSCoordTransform& anEndTransform, const FSVector<FSMorphGradient>& anArray) : FSFillStyle(aType), startTransform(aStartTransform), endTransform(anEndTransform), gradients(anArray) {}

        FSMorphGradientFill* clone() const { return new FSMorphGradientFill(*this); }

        const char* className() const;

        /** Add an FSMorphGradient object to the end of the gradients array.

            @param anObject an FSMorphGradient.
            */
        void add(const FSMorphGradient& anObject) { gradients.push_back(anObject); }

        /** Add all the FSMorphGradient objects from the array to the end of the gradients array.

            @param anArray an array of FSMorphGradient objects.
            */
        void add(const FSVector<FSMorphGradient>& anArray);

        /** Gets the coordinate transform mapping the gradient square onto physical coordinates at the start of the morphing process.

         @return the starting coordinate transform.
         */
        FSCoordTransform& getStartTransform() { return startTransform; }

        /** Gets the coordinate transform mapping the gradient square onto physical coordinates at the end of the morphing process.

         @return the ending coordinate transform.
         */
        FSCoordTransform& getEndTransform() { return endTransform; }

        /** Gets the array of up to eight FSMorphGradient objects defining the control points for the gradient.

            @return the array of control points.
            */
        FSVector<FSMorphGradient>& getGradients() { return gradients; }

        /** Sets the initial coordinate transform mapping the gradient square onto physical coordinates.

            @param aTransform the starting coordinate transform.
            */
        void setStartTransform(const FSCoordTransform& aTransform) { startTransform = aTransform; }

        /** Sets the final coordinate transform mapping the gradient square onto physical coordinates.

            @param aTransform the ending coordinate transform.
            */
        void setEndTransform(const FSCoordTransform& aTransform) { endTransform = aTransform; }

        /** Sets the array of control points that define the gradient.

            @param anArray an array of up to eight FSMorphGradient objects.
            */
        void setGradients(const FSVector<FSMorphGradient>& anArray) { gradients = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    
    private:
        FSCoordTransform startTransform;
        FSCoordTransform endTransform;
        FSVector<FSMorphGradient> gradients;

    };
} 

#endif
