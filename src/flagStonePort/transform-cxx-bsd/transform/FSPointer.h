/*
 *  FSPointer.java
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

#ifndef __FSPointer_h__
#define __FSPointer_h__

#include "FSMovieObject.h"

namespace transform
{
/**
 * %FSPointer defines an unsigned 32-bit pointer. 
 * 
<p>It is thought that this class was used by Macromedia's Generator product and 
its exact function is not known. It is included in the framework for completeness.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSPointer_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSPointer_1">pointer</a></td>
<td>The pointer value.</td>
</tr>
</table>

<h1 class="datasheet">History</h1>

<p>The FSPointer class represents the DefineBitsPtr tag from the Macromedia Flash 
(SWF) File Format Specification. It is not documented in later editions of the 
specification. It is not known when this tag was added.</p>

 */  
    class DLL_DECL FSPointer : public FSMovieObject
    {
public:
        FSPointer(FSInputStream* aStream);

        /** Constructs an FSPointer object.

        @param aNumber the pointer.
        */
        FSPointer(unsigned int aNumber) : FSMovieObject(Pointer), value(aNumber) {}

        FSPointer* clone() const { return new FSPointer(*this); }

        const char* className() const;

        /** Gets the value for the pointer.

            @return the pointer value.
            */
        unsigned int getValue() { return value; }

        /** Sets the pointer.

            @param aNumber the pointer.
            */
        void setValue(unsigned int aNumber) { value = aNumber; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        unsigned int value;
    };
}

#endif
