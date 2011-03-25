/*
 *  FSMorphBitmapFill.h
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

#ifndef __FSMorphBitmapFill_h__
#define __FSMorphBitmapFill_h__

#include "FSFillStyle.h"

#include "FSCoordTransform.h"

namespace transform
{
/**
 * %FSMorphBitmapFil uses a bitmap image to fill an area of a morphing shape. 
 * 
<p>Two types of bitmap fill are supported:</p>

<ul>
<li>Clipped - the image is placed in the middle of the area to be filled. If the area to be filled is larger
than the image then the colour at the edge of the image is used to fill the remaining area.</li>
<li>Tiled - the image is tiled across the area to be filled.</li>
</ul>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSMorphBitmapFill_0">type</a></td>
<td>The type of bitmap fill, either FSFillStyle.Tiled or FSFillStyle.Clipped.</td>
</tr>

<tr>
<td><a name="FSMorphBitmapFill_1">identifier</a></td>
<td>The identifier of the image that will be displayed.</td>
</tr>

<tr>
<td><a name="FSMorphBitmapFill_2">startTransform</a></td>
<td>An optional FSCoordTransform object that will be applied to the image, to change its origin, orientation, etc., at the start of the morphing process.</td>
</tr>

<tr>
<td><a name="FSMorphBitmapFill_3">endTransform</a></td>
<td>An optional FSCoordTransform object that will be applied to the image, to change its origin, orientation, etc., at the end of the morphing process.</td>
</tr>

</table>

<p>The bitmap is referenced using the identifier obtains from an instance of an FSDefineJPEGImage, FSDefineJPEGImage2, FSDefineJPEGImage3, FSDefineImage or FSDefineImage2 object. Only one image can be displayed throughout the morphing process.</p>

<p>When an image is loaded its width and height default to twips rather than pixels. An image 300 x 200 pixels will be displayed as 300 x 200 twips (15 x 10 pixels). Scaling the image by 20 (20 twips = 1 pixel) would restore it to its original size. The FSCoordTransform attribute in the FSBitmapFill object can be used to scale the image to its original size.</p>

<p>The image is drawn with the top left corner at the origin of the shape being filled so the scaling transform must be composited with the translation transform that places the image at the desired location within the shape.</p>

<h1 class="datasheet">History</h1>

<p>The FSMorphBitmapFill class represents the MorphFillStyle structure from the Macromedia Flash (SWF) File Format Specification. Shape morphing was introduced in Flash 3.</P>

 */  
    class DLL_DECL FSMorphBitmapFill : public FSFillStyle
    {
public:
        FSMorphBitmapFill(FSInputStream* aStream);

        /** Constructs an FSMorphBitmapFill specifying the type, bitmap image and coordinated transforms for the image at the start and end of the morphing process.
    
            @param aType the type of fill either TiledBitmap or ClippedBitmap.
            @param anIdentifier the identifier for the bitmap image.
            @param aStartTransform the transform applied to the image at the start of the morphing process.
            @param anEndTransform the transform applied to the image at the end of the morphing process.
            */
        FSMorphBitmapFill(int aType, int anIdentifier, const FSCoordTransform& aStartTransform, const FSCoordTransform& anEndTransform) : FSFillStyle(aType), identifier(anIdentifier), startTransform(aStartTransform), endTransform(anEndTransform) {}

        FSMorphBitmapFill* clone() const { return new FSMorphBitmapFill(*this); }

        const char* className() const;

        /**  Gets the identifier of the bitmap image.

            @return the image's identifier.
            */
        int getIdentifier() { return identifier; }

        /** Gets the starting coordinate transform for the image.

            @return the starting coordinate transform.
            */
        FSCoordTransform& getStartTransform() { return startTransform; }

        /** Gets the ending coordinate transform for the image.

            @return the ending coordinate transform.
            */
        FSCoordTransform& getEndTransform() { return endTransform; }

        /** Sets the identifier of the bitmap image to be used in the morphing process.

            @param anIdentifier the identifier of the bitmap image.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the coordinate transform for the image at the start of the morphing process.

            @param aTransform the starting coordinate transform.
            */
        void setStartTransform(const FSCoordTransform& aTransform) { startTransform = aTransform; } 

        /** Sets the coordinate transform for the image at the end of the morphing process.

            @param aTransform the ending coordinate transform.
            */
        void setEndTransform(const FSCoordTransform& aTransform) { endTransform = aTransform; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
        FSCoordTransform startTransform;
        FSCoordTransform endTransform;
    };
}

#endif

