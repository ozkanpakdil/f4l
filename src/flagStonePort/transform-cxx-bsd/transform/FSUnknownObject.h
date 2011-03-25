/*
 *  FSUnknownObject.h
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

#ifndef __FSUnknownObject_h__
#define __FSUnknownObject_h__ 1

#include "FSMovieObject.h"

namespace transform
{
/**
 * %FSUnknownObject is used to represent any data structure decoded from a Flash file that 
 * is currently not supported by the framework.
 * 
<p>This allows Flash files to be parsed, processed and encoded without affecting any of the data structures not directly supported.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSUnknownObject_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSUnknownObject_1">data</a></td>
<td>The encoded bytes that make up the body of the data structure.</td>
</tr>
</table>

<p>The object provides direct access to the encoded data of the data structure offering the possibility for Transform to encode and decode tags that are not directly supported in the current release of the package. However a detailed knowledge of how the data structure is encoded and decoded is required.</p>

 */
    class DLL_DECL FSUnknownObject : public FSMovieObject
    {
public:
        FSUnknownObject(FSInputStream* aStream);
    
        /** Constructs an FSUnknownObject object of the specified type with the encoded Flash data. The object assumes ownership of the data which will be deleted when the object is deleted.

            @param aType the code identifying the tag type.
            @param bytes the encoded data for the tag.
            @param size the number of bytes in the encoded data.
            */
        FSUnknownObject(int aType, byte* bytes, size_t size);

        FSUnknownObject(const FSUnknownObject& rhs);

        ~FSUnknownObject();

        FSUnknownObject& operator= (const FSUnknownObject& rhs);
        
        FSUnknownObject* clone() const;

        const char* className() const;

        /** Gets the encoded data for the tag. Ownership is retained by the FSUnknownObject object.

            @return a pointer to the encoded binary data owned by the object.
            */
        const byte* getData() const;

        /** Sets the encoded data for the tag. The object assumes ownership of the data, deleting it when the object is deleted. Any existing data will be deleted. 

            @param bytes the encoded data for the tag.
            @param size the number of bytes in the encoded data.
            */
        void setData(byte* bytes, size_t size);

        int  lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        byte* data;
    };
} 

#endif
