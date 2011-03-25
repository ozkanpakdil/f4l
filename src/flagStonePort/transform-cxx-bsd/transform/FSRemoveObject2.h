/*
 *  FSRemoveObject2.h
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

#ifndef __FSRemoveObject2_h__
#define __FSRemoveObject2_h__

#include "FSMovieObject.h"

namespace transform
{
/**
 * %FSRemoveObject2 removes an object from the display list.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSRemoveObject2_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSRemoveObject2_1">layer</a></td>
<td>The number of the layer in the Flash Player's Display List where the object is displayed.</td>
</tr>

</table>

<p>The FSRemoveObject2 class only requires the layer number to identify a particular object, unlike the FSRemoveObject class which also requires the object's identifier although only one object can be placed on a given layer.</p>

<h1 class="datasheet">History</h1>

<p>The FSRemoveObject2 class represents the RemoveObject2 tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash in Flash 3.</p>

 */ 
    class DLL_DECL FSRemoveObject2 : public FSMovieObject
    {
public:
        FSRemoveObject2(FSInputStream* aStream);

        /** Constructs an FSRemoveObject2 object that removes the object on the display list at the specified layer.

            @param aLayer a layer number in the display list.
            */
        FSRemoveObject2(int aLayer) : FSMovieObject(RemoveObject2), layer(aLayer) {}

        FSRemoveObject2* clone() const { return new FSRemoveObject2(*this); }

        const char* className() const;

        /** Gets the layer in the display list where the object to be removed is currently displayed.

            @return the layer number where the object is currently displayed.
            */
        int getLayer() const { return layer; }

        /** Sets the layer in the display list from which the object will be removed.

            @param aLayer the layer number on which the object is displayed.
            */
        void setLayer(int aLayer) { layer = aLayer; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int layer;
    };
}

#endif
