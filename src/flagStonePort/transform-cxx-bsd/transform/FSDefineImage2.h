/*
 *  FSDefineImage2.h
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

#pragma warning( disable : 4290 )

#ifndef __FSDefineImage2_h__
#define __FSDefineImage2_h__ 1

#include "FSDefineObject.h"

namespace transform
{
/**
 * %FSDefineImage2 is used to define a transparent image compressed using the lossless 
 * zlib compression algorithm. 
 * 
<p>The class supports colour-mapped images where the image data contains an index into a colour table or images where the image data specifies the colour directly. It extends FSDefineImage by including alpha channel information for the colour table and pixels in the image.</p>

<p>For colour-mapped images the colour table contains up to 256, 32-bit colours. The image contains one byte for each pixel which is an index into the table to specify the colour for that pixel. The colour table and the image data are compressed as a single block, with the colour table placed before the image.</p>

<p>For images where the colour is specified directly, the image data contains 32 bit colour values.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSDefineImage2_0">type</a></td>
<td>Identifies the data structure when it is encoded. The type attribute is read-only and may be used when iterating through the objects in an FSMovie object to identify the object class without using run-time type checking.</td>
</tr>

<tr>
<td><a name="FSDefineImage2_1">identifier</a></td>
<td>A unique identifier, in the range 1..65535, that is used to reference the image from other objects.</td>
</tr>

<tr>
<td><a name="FSDefineImage2_2">width</a></td>
<td>Width of the image in pixels, NOT twips. 1 pixel = 20 twips.</td>
</tr>

<tr>
<td><a name="FSDefineImage2_3">height</a></td>
<td>Height of the image in pixels, NOT twips.  1 pixel = 20 twips.</td>
</tr>

<tr>
<td><a name="FSDefineImage2_4">pixelSize</a></td>
<td>The number of bits per pixel, either 8 or 32. 8-bit pixels are used for indexed images where the colour table contains the colours for each pixel. 32-bit pixels are used to specify the colour and transparency directly.</td>
</tr>

<tr>
<td><a name="FSDefineImage2_5">tableSize</a></td>
<td>The number of entries in the colour table - which is compressed as part of the image. Each entry in the colour table contains one byte each for the red, green and blue colour channels. The colour table is only used for indexed colour images. The table is not used when the colour is specified directly in each pixel.</td>
</tr>

<tr>
<td><a name="FSDefineImage2_5">compressedData</a></td>
<td>An array of bytes containing the zlib compressed colour table and image.</td>
</tr>

</table>

<p>The image data is stored in zlib compressed form within the object. For colour-mapped images the compressed data contains the colour table followed by the image data.</p>

<h1 class="datasheet">History</h1>

<p>The FSDefineImage2 class represents the DefineBitsLossless2 tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSDefineImage2 : public FSDefineObject
    {
public:
        FSDefineImage2(FSInputStream* aStream);

        /** Constructs an FSDefineImage2 object defining a colour-mapped image. The object assumes ownership for the data added.
        
            @param anIdentifier    the unique identifier for this object
            @param aWidth the width of the image.
            @param aHeight the height of the image.
            @param aTableSize the number of entries in the colour table in the compressed image. Each entry takes 4 bytes.
            @param bytes the zlib compressed colour table and image data.
            @param numberOfBytes length of the zlib compressed image data.
            */
        FSDefineImage2(int anIdentifier, int aWidth, int aHeight, int aTableSize, byte* bytes, size_t numberOfBytes);

        /** Constructs an FSDefineImage2 object defining an image that specifies the colour directly. Each pixel in the image is 32 bits - 8 bits for the red, green, blue and alpha colour channels. The object assumes ownership for the data added.

            @param anIdentifier    the unique identifier for this object
            @param aWidth the width of the image.
            @param aHeight the height of the image.
            @param bytes the zlib compressed image data.
            @param numberOfBytes length of the zlib compressed image data.
            */
        FSDefineImage2(int anIdentifier, int aWidth, int aHeight, byte* bytes, size_t numberOfBytes);

        FSDefineImage2(const FSDefineImage2& rhs);

        FSDefineImage2& operator= (const FSDefineImage2& rhs);

        FSDefineImage2* clone() const { return new FSDefineImage2(*this); }

        const char* className() const;
        
        /** Gets the width of the image in pixels.

            @return the width of the image.
            */
        int getWidth() const { return width; }

        /** Gets the height of the image in pixels.

            @return the height of the image in pixels.
            */
        int getHeight() const { return height; }

        /** Gets the number of bits used to represent each pixel. Either 8 bits for colour-mapped image or 32 bits for images where the colour is specified directly in the image.

            @return the number of bits per pixel: 8 or 32.
            */
        int getPixelSize() const { return pixelSize; }

        /** Gets the number of entries in the colour table encoded the compressed image. Returns 0 for images where the colour is specified directly.

            @return the number of entries in the colour table.
            */
        int getTableSize() const { return tableSize; }

        /** Gets the compressed image data,

            @return the compressed image data.
            */
        byte* getImage() const { return image; }

        /** Gets the number of bytes in the compressed image data.

            @return the length of the compressed image.
            */
        size_t getImageLength() const { return imageLength; }

        /** Sets the width of the image in pixels.

            @param aNumber the width of the image. 
            */
        void setWidth(int aNumber) { width = aNumber; }

        /** Sets the height of the image in pixels.

            @param aNumber the height of the image in pixels.
            */
        void setHeight(int aNumber) { height = aNumber; }

        /** Sets the size of the pixel in bits: 8 for colour-mapped images, 32 for direct images.

            @param aNumber the size of each pixel in bits: 8 or 32.
            */
        void setPixelSize(int aNumber) { pixelSize = aNumber; }

        /** Sets the number of entries in the colour table in the compressed image.

            @param aNumber the number of entries in the colour table in the compressed image.
            */
        void setTableSize(int aNumber) { tableSize = aNumber; }

        /** Sets the compressed image data.

            @param bytes byte array containing zlib compressed colour table and image.
            @param numberOfBytes the number of bytes in the zlib compressed colour table and image.
            */
        void setImage(byte* bytes, size_t numberOfBytes)
        {
            delete [] image;
                
            image = bytes;
            imageLength = numberOfBytes;
        }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int width;
        int height;

        int pixelSize;
        int tableSize;

        byte* image;
        size_t imageLength;
    };
}

#endif
