/*
 *  FSDefineImage.h
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

#ifndef __FSDefineImage_h__
#define __FSDefineImage_h__ 1

#include "FSDefineObject.h"

namespace transform
{
/**
 * %FSDefineImage is used to define an image compressed using the lossless zlib compression algorithm. 
 * 
<p>The class supports colour-mapped images where the image data contains an index into a colour table or images where the image data specifies the colour directly.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSDefineImage_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineImage_1">identifier</a></td>
<td>A unique identifier, in the range 1..65535, that is used to reference the image from other objects.</td>
</tr>

<tr>
<td><a name="FSDefineImage_2">width</a></td>
<td>Width of the image in pixels, NOT twips. 1 pixel = 20 twips.</td>
</tr>

<tr>
<td><a name="FSDefineImage_3">height</a></td>
<td>Height of the image in pixels, NOT twips.  1 pixel = 20 twips.</td>
</tr>

<tr>
<td><a name="FSDefineImage_4">pixelSize</a></td>
<td>The number of bits per pixel, either 16 or 24.</td>
</tr>

<tr>
<td><a name="FSDefineImage_4">tableSize</a></td>
<td>The number of entries in the colour table - which is compressed as part of the image. Each entry in the colour table contains one byte each for the red, green and blue colour channels. The colour table is only used for indexed colour images. The table is not used when the colour is specified directly in each pixel.</td>
</tr>

<tr>
<td><a name="FSDefineImage_5">compressedData</a></td>
<td>An array of bytes containing the zlib compressed colour table and image.</td>
</tr>

</table>

<p>For colour-mapped images the colour table contains up to 256, 24-bit colours. The image contains one byte for each pixel which is an index into the table to specify the colour for that pixel. The colour table and the image data are compressed as a single block, with the colour table placed before the image.</p>

<p>For images where the colour is specified directly, the image data contains either 16 or 24 bit colour values. For 16-bit colour values the most significant bit is zero followed by three, 5-bit fields for the red, green and blue channels:</p>

<pre>
            +-+--------+--------+--------+
            |0|   Red  |  Green |  Blue  |
            +-+--------+--------+--------+
           15                            0
</pre>

<p>Four bytes are used to represent 24-bit colours. The first byte is always set to zero and the following bytes contain the colour values for the red, green and blue colour channels.</p>

<p>The number of bytes in each row of an image must be aligned to a 32-bit word boundary. For example if an image if an icon is 25 pixels wide, then for an 8-bit colour mapped image an additional three bytes (0x00) must be used to pad each row; for a 16-bit direct mapped colour image an additional two bytes must be used as padding.</p>

<p>The image data is stored in zlib compressed form within the object. For colour-mapped images the compressed data contains the colour table followed by the image data. The colour table is omitted for direct-mapped images.</p>

<h1 class="datasheet">History</h1>

<p>The FSDefineImage class represents the DefineBitsLossless tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 2.</p>

 */
    class DLL_DECL FSDefineImage : public FSDefineObject
    {
public:
        FSDefineImage(FSInputStream* aStream);

        /** Constructs an FSDefineImage object defining a colour-mapped image. The object assumes ownership for the data added.
    
            @param anIdentifier    the unique identifier for this object
            @param aWidth the width of the image.
            @param aHeight the height of the image.
            @param aTableSize the number of entries in the colour table in the compressed data. Each entry is 24 bits.
            @param bytes the zlib compressed colour table and image data.
            @param numberOfBytes the number of bytes in the compressed data.
            */
        FSDefineImage(int anIdentifier, int aWidth, int aHeight, int aTableSize, byte* bytes, size_t numberOfBytes);

        /** Constructs an FSDefineImage object defining an image that specifies the colour directly. The object assumes ownership for the data added.

            @param anIdentifier    the unique identifier for this object
            @param aWidth the width of the image.
            @param aHeight the height of the image.
            @param bytes the zlib compressed image data.
            @param numberOfBytes length of the zlib compressed image data.
            @param aPixelSize the size of each pixel, either 16 or 24 bits.
            */
        FSDefineImage(int anIdentifier, int aWidth, int aHeight, byte* bytes, size_t numberOfBytes, int aPixelSize);

        FSDefineImage(const FSDefineImage& rhs);

        ~FSDefineImage();

        FSDefineImage& operator= (const FSDefineImage& rhs);

        FSDefineImage* clone() const { return new FSDefineImage(*this); }

        const char* className() const;

        /** Gets the width of the image in pixels.

            @return the width of the image.
            */
        int getWidth() const { return width; }

        /** Gets the height of the image in pixels.

            @return the height of the image in pixels.
            */
        int getHeight() const { return height; }

        /** Gets the number of bits used to represent each pixel. Either 8, 16 or 24 bits. The pixel size is 8-bits for colour-mapped images and 16 or 24 bits for images where the colour is specified directly.

            @return the number of bits per pixel: 8, 16 or 24.
            */
        int getPixelSize() const { return pixelSize; }

        /** Gets the number of entries in the colour table encoded the compressed image. For images where the colour is specified directly in the image then the table size is zero.

            @return the number of entries in the colour table.
            */
        int getTableSize() const { return tableSize; }

        /** Gets the compressed colour table and image

            @return the compressed image data.
            */
        byte* getImage() const { return image; }

        /** Gets the number of bytes in the compressed image data.

            @return the length of the compressed image.
            */
        size_t getImageLength() const { return imageLength; }

        /** Sets the width of the image in pixels

            @param aNumber the width of the image. 
            */
        void setWidth(int aNumber) { width = aNumber; }

        /** Sets the height of the image in pixels.

            @param aNumber the height of the image in pixels.
            */
        void setHeight(int aNumber) { height = aNumber; }

        /** Sets the size of the pixel in bits: 8, 16 or 32. The pixel size is 8-bits for colour-mapped images and 16 or 24 bits for images where the colour is specified directly.

            @param aNumber the size of each pixel in bits: 8, 16 or 24.
            */
        void setPixelSize(int aNumber) { pixelSize = aNumber; }

        /** Sets the number of entries in the colour table in the compressed image. For images where the colour is specified directly in the image then the table size should be zero.

            @param aNumber the number of entries in the colour table in the compressed image.
            */
        void setTableSize(int aNumber) { tableSize = aNumber; }

        /** Sets the compressed image data using compressed data. The object assumes ownership for the data added. Any existing data is deleted.

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
