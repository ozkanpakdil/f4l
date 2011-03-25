/*
 *  FSSerialNumber.h
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

#ifndef __FSSerialNumber_h__
#define __FSSerialNumber_h__

#include "FSMovieObject.h"

#include "FSString.h"

namespace transform
{
/**
 * %FSSerialNumber is used to add a user-defined serial number into a Flash file. 
 * 
<p>The serial number is simply a string and can contain arbitrary information.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSSerialNumber_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSSerialNumber_1">serialNumber</a></td>
<td>A string containing the serial number.</td>
</tr>
</table>

<h1 class="datasheet">Example</h1>

<pre>
movie.add(new FSSerialNumber("1234-DGF-2354"));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSSerialNumber represents the SerialNumber tag in the Macromedia Flash (SWF) File Format Specification. It is not known when this tag was introduced.</p>

 */  
    class DLL_DECL FSSerialNumber : public FSMovieObject
    {
public:
        FSSerialNumber(FSInputStream* aStream);

        /** Constructs an FSSerialNumber action with the specified string.

            @param aString an c-string containing the serial number.
            */
        FSSerialNumber(const char* aString) : FSMovieObject(SerialNumber), serialNumber(aString) {}

        FSSerialNumber* clone() const { return new FSSerialNumber(*this); }

        const char* className() const;

        /** Gets the serial number.

            @return the c-string containing the serial number.
            */
        const char* getSerialNumber() { return serialNumber.c_str(); }

        /** Sets the serial number.

            @param aString an c-string containing the serial number.
            */
        void setSerialNumber(const char* aString) { serialNumber = aString; } 

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString serialNumber;
    };
}

#endif
