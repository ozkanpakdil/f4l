/*
 *  FSJPEGEncodingTable.h
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

#ifndef __FSJPEGEncodingTable_h__
#define __FSJPEGEncodingTable_h__ 1

#include "FSMovieObject.h"

namespace transform
{
/**
 * %FSJPEGEncodingTable defines an encoding table for JPEG images. 
 * 
<p>The encoding table is shared between all images defined using the FSDefineJPEGImage class so there should only be one FSJPEGEncodingTable object defined in a movie.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSJPEGEncodingTable_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSJPEGEncodingTable_0">encodingTable</a></td>
<td>An array of bytes containing the encoding table data.</td>
</tr>

</table>

<p>The FSJPEGEncodingTable class is not essential to define JPEG encoded images in a movie using the FSDefineJPEGImage class. If an FSJPEGEncodingTable object is created with an empty encoding table then the Flash Player will still display JPEG images defined using FSDefineJPEGImage objects correctly. When an FSJPEGEncodingTable with an empty encoding table is encoded to a Flash file, the "end of stream" marker 0xFFD9 is encoded allowing the empty table to be decoded correctly.</p>

<h1 class="datasheet">Examples</h1>

<p>The simplest way to use the FSJPEGEncodingTable and FSDefineJPEGImage classes to define JPEG encoded images is to create an empty encoding table then construct the FSDefineJPEGImage object(s) with the image data from a file:</p>

<pre>
FILE* input = 0;
char* buffer = 0;
long length = 0;
unsigned int numberOfBytes = 0;

try {
    if ((input = fopen(fileName, "rb")) == 0)
        throw FSFileOpenException("Cannot Open File"));
    
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

<p>The FSJPEGEncodingTable class represents the JPEGEncodingTable tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSJPEGEncodingTable : public FSMovieObject
    {
public:
        FSJPEGEncodingTable(FSInputStream* aStream);

        /** Constructs an FSJPEGEncodingTable object with an empty encoding table.
            */
        FSJPEGEncodingTable() : FSMovieObject(JPEGEncodingTable), encodingTable(0) { length = 2;}

        /** Constructs an FSJPEGEncodingTable object with the encoding table data. The object assumes ownership of the table data.

            @param bytes an array of bytes contains the data for the encoding table.
            @param numberOfBytes the number of bytes in the encoding table data.
            */
        FSJPEGEncodingTable(byte* bytes, size_t numberOfBytes);

        FSJPEGEncodingTable(const FSJPEGEncodingTable& rhs);

        ~FSJPEGEncodingTable();

        FSJPEGEncodingTable& operator= (const FSJPEGEncodingTable& rhs);

        FSJPEGEncodingTable* clone() const { return new FSJPEGEncodingTable(*this); }

        const char* className() const;

        /** Gets the encoding table.

            @return the array of bytes contains the data for the encoding table.
            */
        byte* getEncodingTable() const { return encodingTable; }

        /** Sets the encoding table. The object assumes ownership of the table data, any existing table data will be deleted.

            @param bytes an array of bytes contains the data for the encoding table.
            @param size the number of bytes in the encoding table data.
            */
        void setEncodingTable(byte* bytes, size_t size);
        
        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        byte* encodingTable;
    };
}

#endif
