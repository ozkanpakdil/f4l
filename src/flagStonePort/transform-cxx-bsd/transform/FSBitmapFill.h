/*
 *  FSBitmapFill.h
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

#ifndef __FSBitmapFill_h__
#define __FSBitmapFill_h__ 1

#include "FSFillStyle.h"

#include "FSCoordTransform.h"

namespace transform
{
/**
 * The %FSBitmapFill class is used to fill a shape with an image. 
 * 
<p>Two type of bitmap fill are supported:</p>

<table class="datasheet">

<tr>
<td>Clipped</td>
<td>If the area to be filled is larger than the image then the colour at the edge 
of the image is used to fill the remainder of the shape.</td>
</tr>

<tr>
<td>Tiled</td>
<td>If the area to be filled is larger than the image then the image is tiled 
across the area to be filled.</td>
</tr>

</table>

<p><!-- Blank paragraph to provide spacing between tables --></p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSBitmapFill_0">type</a></td>
<td>The type of bitmap fill, either FSFillStyle.Tiled or FSFillStyle.Clipped.</td>
</tr>

<tr>
<td><a name="FSBitmapFill_1">identifier</a></td>
<td>The identifier, in the range 1..65535, of the object that contains the image that will be displayed.</td>
</tr>

<tr>
<td><a name="FSBitmapFill_2">transform</a></td>
<td>An FSCoordTransform object that defines the coordinate transformation that will be applied to the image, to change its size, location relative to the origin of the shape, orientation, etc., when it is displayed.</td>
</tr>

</table>

<p>The type attribute may be used when iterating through an array of fill style objects to identify the type of fill style without using run-time type checking.</p>

<p>When an image is loaded its width and height default to twips rather than pixels. An image 300 x 200 pixels will be displayed as 300 x 200 twips (15 x 10 pixels). Scaling the image by 20 (20 twips = 1 pixel) using the FSCoordTransform object will restore it to its original size.</p>

<p>The image is drawn with the top left corner placed at the origin (0, 0) of the shape being filled. Depending on how the shape is drawn the coordinate transform may also need to specify a translation to place the image at the desired location.</p>

<h1 class="datasheet">When To Use</h1>

<p>In addition to filling shapes with images that represent textures or complex fill patterns the FSBitmapFill class is required to display any image in a Flash file - image can only be displayed in Flash inside a shape definition. The classes that define images only contain the image data, not how it is displayed. To simply display an image, the selected line style of a shape may be set to zero so that the image is displayed without a border.</p>

<h1 class="datasheet">Example</h1>

<p>The following code fragment centres the image in the centre of the shape - assuming  the shape is drawn with the origin at the centre. The transform constructor allows the translation and scaling transform to be specified in a single step rather than compositing the transforms.</p>

<pre>
FSCoordTransform composite(-imageWidth/2, -imageHeight/2, 20.0, 20.0);

fillStyles.push_back(new FSBitmapFill(FSFillStyle::Clipped, imageId, composite));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSBitmapFill class represents the FillStyle structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>
 
 */
    class DLL_DECL FSBitmapFill : public FSFillStyle
    {
public:
        FSBitmapFill(FSInputStream* aStream);

        /** Constructs an FSBitmapFill object of the specified type, image identifier and coordinate transform.

            @param aType the type of bitmap fill, Tiled or Clipped.
            @param anIdentifier the identifier of the image object to be displayed.
            @param aTransform an FSCoordTransform object that changes the appearance of the image.
        */
        FSBitmapFill(int aType, int anIdentifier, const FSCoordTransform& aTransform) : FSFillStyle(aType), identifier(anIdentifier), transform(aTransform) {}

        FSBitmapFill* clone() const { return new FSBitmapFill(*this); }

        const char* className() const;

        /** Gets the identifier of the image to be displayed.

            @return the identifier of the image object to be displayed.
            */
        int getIdentifier() const { return identifier; }

        /** Gets the coordinate transform applied to the image.

            @return the transform that will be applied to the image when it is displayed.
            */
        FSCoordTransform& getTransform() { return transform; }

        /** Sets the identifier of the image to be displayed. The identifier must be in the range 1..65535.

            @param anIdentifier the identifier of the image object to be displayed.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the coordinate transform applied to the image.

            @param aTransform an FSCoordTransform object that changes the appearance of the image.
            */
        void setTransform(const FSCoordTransform& aTransform) { transform = aTransform; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
        
        FSCoordTransform transform;
    };
} 

#endif

