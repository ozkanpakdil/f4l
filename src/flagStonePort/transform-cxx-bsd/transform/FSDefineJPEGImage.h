/*
 *  FSDefineJPEGImage.h
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

#ifndef __FSDefineJPEGImage_h__
#define __FSDefineJPEGImage_h__ 1

#include "FSDefineObject.h"

namespace transform
{
/**
 * %FSDefineJPEGImage is used to define a JPEG encoded image. 
 * 
<p>FSDefineJPEGImage objects only contain the image data, the encoding table for the image is defined in a FSJPEGEncodingTable object. All images using a shared FSJPEGEncodingTable object to represent the encoding table have the same compression ratio.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSDefineJPEGImage_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineJPEGImage_1">identifier</a></td>
<td>A unique identifier, in the range 1..65535, that is used to reference the image from other objects.</td>
</tr>

<tr>
<td><a name="FSDefineJPEGImage_2">image</a></td>
<td>An array of bytes containing the JPEG compressed image.</td>
</tr>
</table>

<p>Images can only be displayed inside a shape using the FSBitmapFill class.</p>

<p>The image data may be taken directly from a JPEG image file. No further decoding is necessary.</p>

<p>Although the FSDefineJPEGImage class is supposed to be used with the FSJPEGEncodingTable class which defines the encoding table for the images it is not essential. If an FSJPEGEncodingTable object is created with an empty encoding table then the Flash Player will still display the JPEG image correctly.</p>

<h1 class="datasheet">Example</h1>

<p>The simplest way to use the FSJPEGEncodingTable and FSDefineJPEGImage classes to define JPEG encoded images is to create an empty encoding table then construct the FSDefineJPEGImage object with the image data from a file:</p>

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
        throw FSAccessException("Cannot Allocate Memory");
    
    if (fread(buffer, 1, numberOfBytes, input) != numberOfBytes)
        throw FSAccessException("Cannot Read File");
    
    if (fclose(input) != 0)
        throw FSAccessException("Cannot Read File");
    
    movie.add(new FSJPEGEncodingTable());
    movie.add(new FSDefineJPEGImage(movie.newIdentifier(), buffer, numberOfBytes));
}
catch (FSFileOpenException e) {
    ... Process Exception ...
}
catch (FSAccessException e) {
    ... Process Exception ...
}
</pre>

<h1 class="datasheet">History</h1>

<p>The FSDefineJPEGImage class represents the DefineBits data structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSDefineJPEGImage : public FSDefineObject
    {
public:
        FSDefineJPEGImage(FSInputStream* aStream);

        /** Constructs an FSDefineJPEGImage object with the identifier and JPEG data. The object assumes ownership of the image data. 

            @param anIdentifier    the unique identifier for this object
            @param bytes the JPEG encoded image data.
            @param numberOfBytes the number of bytes in the image.
        */
        FSDefineJPEGImage(int anIdentifier, byte* bytes, size_t numberOfBytes);

        FSDefineJPEGImage(const FSDefineJPEGImage& rhs);

        ~FSDefineJPEGImage();

        FSDefineJPEGImage& operator= (const FSDefineJPEGImage& rhs);

        FSDefineJPEGImage* clone() const { return new FSDefineJPEGImage(*this); }

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

        /** Gets the length of the image data.

            @return the number of bytes in the image data.
            */
        size_t getImageLength() const { return imageLength; }

        /** Sets the image data. The object assumes ownership of the image data, any existing data will be deleted.

            @param bytes an array of bytes containing the image data.
            @param numberOfBytes the number of bytes in the image.
            */
        void setImage(byte* bytes, size_t numberOfBytes);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int width;
        int height;

        byte* image;
        size_t imageLength;
    };
}

#endif
