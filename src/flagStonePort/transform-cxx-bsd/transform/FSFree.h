/*
 *  FSFree.h
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

#ifndef __FSFree_h__
#define __FSFree_h__

#include "FSMovieObject.h"

#include "FSString.h"

namespace transform
{
/**
 * %FSFree deletes the object with the specified identifier, freeing up resources in the Flash Player.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSFree_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSFree_1">identifier</a></td>
<td>The identifier of the object, in the range 1..65535, that will be deleted from the Flash Player's memory.</td>
</tr>

</table>

<h1 class="datasheet">History</h1>

<p>The FSFree class represents the FreeCharacter tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSFree : public FSMovieObject
    {
public:
        FSFree(FSInputStream* aStream);

        /** Constructs an FSFree object with the specified identifier.

            @param anIdentifier the identifier of the object to be deleted.
            */
        FSFree(int anIdentifier) : FSMovieObject(Free), identifier(anIdentifier) {}

        FSFree* clone() const { return new FSFree(*this); }

        const char* className() const;

        /** Gets the identifier of the object to be deleted.

            @return the object's identifier.
            */
        int getIdentifier() const { return identifier; }

        /** Sets the identifier of the object to be deleted. The identifier must be in the range 1..65535.

            @param anIdentifier the identifier of the object to be deleted.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
    };
}

#endif
