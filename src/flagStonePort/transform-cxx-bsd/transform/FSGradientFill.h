/*
 *  FSGradientFill.h
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

#ifndef __FSGradientFill_h__
#define __FSGradientFill_h__ 1

#include "FSVector.h"

#include "FSFillStyle.h"

#include "FSCoordTransform.h"
#include "FSGradient.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSGradient>;
#endif // _WINDLL
#endif // WIN32


namespace transform
{
/**
 * %FSGradientFill defines how a colour changes across an area to be filled with colour. 
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
<td><a name="FSGradientFill_0">type</a></td>
<td>The type of gradient fill, either FSFillStyle.Linear or FSFillStyle.Radial.</td>
</tr>

<tr><td><a name="FSGradientFill_1">transform</a></td>
<td>A coordinate transformation used to map the gradient square into the coordinates of the area to be filled.</td>
</tr>

<tr><td><a name="FSGradientFill_2">gradients</a></td>
<td>An array of up to eight FSGradient objects that define the control points across the gradient square that control the colour transitions. The Flash Player performs the interpolation of the colour values between the control points.</td>
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

<p>The transform is independent of any transformation defined for the parent shape in which the gradient is displayed. The gradient will be displayed correctly if the shape is scaled, rotated, etc., when it is added to the display list.</p>

<h1 class="datasheet">History</h1>

<p>The FSGradientFill class represents the FillStyle structure from the Macromedia Flash 
(SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSGradientFill : public FSFillStyle
    {
public:
        FSGradientFill(FSInputStream* aStream);

        /**  Constructs an FSGradientFill object specifying the type, coordinate transform and array of gradient records.

            @param aType the type of gradient fill, either FSFillStyle::LinearGradient or FSFillStyle::RadialGradient.
            @param aTransform the coordinate transform mapping the gradient square onto physical coordinates.
            @param anArray an array of up to eight FSGradient objects defining the control points for the gradient.
            */
        FSGradientFill(int aType, const FSCoordTransform& aTransform, const FSVector<FSGradient>& anArray)  : FSFillStyle(aType), transform(aTransform), gradients(anArray) {}

        FSGradientFill* clone() const { return new FSGradientFill(*this); }

        const char* className() const;

        /** Add an FSGradient object to the end of the gradients array.

            @param anObject an FSGradient.
            */
        void add(const FSGradient& anObject) { gradients.push_back(anObject); }

        /** Add all the FSGradient objects from the array to the end of the gradients array.

            @param anArray an array of FSGradient objects.
            */
        void add(const FSVector<FSGradient>& anArray);

        /** Gets the coordinate transform mapping the gradient square onto physical coordinates.

            @return the coordinate transform.
            */
        FSCoordTransform& getTransform() { return transform; }

        /** Gets the array of up to eight FSGradient objects defining the control points for the gradient.

            @return the array of control points.
            */
        FSVector<FSGradient>& getGradients() { return gradients; }

        /** Sets the coordinate transform mapping the gradient square onto physical coordinates.

            @param aTransform the coordinate transform.
            */
        void setTransform(const FSCoordTransform& aTransform) { transform = aTransform; }

        /** Sets the array of control points that define the gradient.

            @param anArray an array of up to eight FSGradient objects.
            */
        void setGradients(const FSVector<FSGradient>& anArray) { gradients = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    
    private:
        FSCoordTransform transform;
        FSVector<FSGradient> gradients;

    };
} 

#endif
