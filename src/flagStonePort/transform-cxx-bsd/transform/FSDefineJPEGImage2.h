/*
 *  FSDefineJPEGImage2.h
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

#ifndef __FSDefineJPEGImage2_h__
#define __FSDefineJPEGImage2_h__ 1

#include "FSDefineObject.h"

namespace transform
{
/**
 * %FSDefineJPEGImage2 is used to define a JPEG encoded image with an integrated encoding table. 
 *  
<p>It extends the FSDefineJPEGImage class by including a separate encoding table, rather than using an FSJPEGEncodingTable object to store the encoding table. This allows multiple JPEG images with different amounts of compression to be included within a Flash file.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSDefineJPEGImage2_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineJPEGImage2_1">identifier</a></td>
<td>A unique identifier, in the range 1..65535, that is used to reference the image from other objects.</td>
</tr>

<tr>
<td><a name="FSDefineJPEGImage2_2">image</a></td>
<td>An array of bytes containing the JPEG compressed image.</td>
</tr>

<tr>
<td><a name="FSDefineJPEGImage2_3">encodingTable</a></td>
<td>An array of bytes containing the encoding table. May be set to null.</td>
</tr>
</table>

<p>Although the encoding table defines how the image is compressed it is not essential. If an FSDefineJPEGImage2 object is created with an empty encoding table then the Flash Player will still display the JPEG image correctly. The empty encoding table is not a null object. It contains four bytes: 0xFF, 0xD9, 0xFF, 0xD8. Note however that this is reversed from StartOfImage (SOI, 0xFFD8) and EndOfImage (EOI, 0xFFD9) tags defined in the JPEG file format specification. This appears to be a bug in Flash. However the order is preserved to ensure compatibility although code has been tested with the normal order for the tags and the images were displayed correctly.</p>

<h1 class="datasheet">Examples</h1>

<p>The simplest way to use the FSDefineJPEGImage2 class is to use the constructor that specifies the JPEG file to initialise the object:</p>

<pre>
FILE* input = 0;
char* buffer = 0;
long length = 0;
unsigned int numberOfBytes = 0;

try {
    if ((input = fopen(fileName, "rb")) == 0)
        throw FSFileOpenException("Cannot Open File");
    
    if (fseek(input, 0, SEEK_END) != 0)
        throw FSAccessException("Cannot Read File");
    
    if ((length = ftell(input)) == -1L)
        throw FSAccessException("Cannot Read File");
    else
        numberOfBytes = (unsigned int)length;
    
    rewind(input);
    
    buffer = new char[numberOfBytes];
    
    if (numberOfBytes &gt; 0 && buffer == 0)
        throw FSAccessException("Cannot Read File");
    
    if (fread(buffer, 1, numberOfBytes, input) != numberOfBytes)
        throw FSAccessException("Cannot Read File");
    
    if (fclose(input) != 0)
        throw FSAccessException("Cannot Read File");
    
    movie.add(new FSDefineJPEGImage2(movie.newIdentifier(), buffer, numberOfBytes));
}
catch (FSFileOpenException e) {
    ... Process Exception ...
}
catch (FSAccessException e) {
    ... Process Exception ...
}
</pre>

<p>This generates an object with an empty encoding table, however the image will still be displayed correctly.</p>

<h1 class="datasheet">History</h1>

<p>The FSDefineJPEGImage2 class represents the DefineBitsJPEG2 tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 2.</p>

 */
    class DLL_DECL FSDefineJPEGImage2 : public FSDefineObject
    {
public:
        FSDefineJPEGImage2(FSInputStream* aStream);

        /** Constructs an FSDefineJPEGImage2 object with the identifier, JPEG image data and JPEG encoding table data. The object assumes ownership of the data added.

            @param anIdentifier    the unique identifier for this object
            @param imageBytes the JPEG encoded image data.
            @param imageLength the number of bytes in the image data.
            @param encodingBytes the JPEG encoded encoding table.
            @param encodingLength the number of bytes in the encoding data.
            */
        FSDefineJPEGImage2(int anIdentifier, byte* imageBytes, size_t imageLength, byte* encodingBytes, size_t encodingLength);
        
        /** Constructs an FSDefineJPEGImage2 object with the identifier and JPEG image data. The JPEG encoding table is set to empty. The object assumes ownership of the data added.

            @param anIdentifier    the unique identifier for this object
            @param imageBytes the JPEG encoded image data.
            @param imageLength the number of bytes in the image data.
            */
        FSDefineJPEGImage2(int anIdentifier, byte* imageBytes, size_t imageLength);

        FSDefineJPEGImage2(const FSDefineJPEGImage2& rhs);

        ~FSDefineJPEGImage2();

        FSDefineJPEGImage2& operator= (const FSDefineJPEGImage2& rhs);

        FSDefineJPEGImage2* clone() const { return new FSDefineJPEGImage2(*this); }

        const char* className() const;

        /** Gets the image width in pixels.

            @return the width of the image.
            */

        int getWidth() const { return width; }

        /** Gets the image height in pixels.

            @return the height of the image.
            */
        int getHeight() const { return height; }

        /** Gets the image data.

            @return the array of bytes containing the image data.
            */
        byte* getImage() const { return image; }

        /** Gets the number of bytes in the image data.

            @return the length of the image data.
            */
        size_t getImageLength() const { return imageLength; }

        /** Gets the encoding table.

            @return the array of bytes containing the encoding table.
            */
        byte* getEncodingTable() const { return encodingTable; }

        /** Gets the number of bytes in the encoding data.

            @return the length of the encoding data.
            */
        size_t getEncodingLength() const { return encodingLength; }

        /** Sets the image data. The object assumes ownership of the data added, any existing data will be deleted.

            @param bytes an array of bytes containing the image data.
            @param numberOfBytes the number of bytes in the image.
            */
        void setImage(byte* bytes, size_t numberOfBytes);

        /** Sets the encoding table data. The object assumes ownership of the data added, any existing data will be deleted.

            @param bytes an array of bytes containing the encoding table.
            @param numberOfBytes the number of bytes in the encoding table.
            */
        void setEncodingTable(byte* bytes, size_t numberOfBytes);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int width;
        int height;

        byte* image;
        size_t imageLength;

        byte* encodingTable;
        size_t encodingLength;
    };
}

#endif
