/*
 *  FSRemoveObject.java
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

#ifndef __FSRemoveObject_h__
#define __FSRemoveObject_h__

#include "FSMovieObject.h"

namespace transform
{
/**
 * %FSRemoveObject removes an object from the Flash Player's Display List. 
 * 
<p>An object placed on the display list is displayed in every frame of a movie until it is explicitly removed. Objects must also be removed if its location or appearance is changed using either the FSPlaceObject or FSPlaceObject2 classes.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSRemoveobject_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSRemoveobject_1">identifier</a></td>
<td>The unique identifier, in the range 1..65535, of the object.</td>
</tr>

<tr>
<td><a name="FSRemoveobject_2">layer</a></td>
<td>The layer at which the object is placed in the Display List.</td>
</tr>
</table>

<p>Although only one object can be placed on any layer in the display list both the object's unique identifier and the layer number must be specified. The FSRemoveObject class is superceded in Flash 3 by the FSRemoveObject2 class which lifts this requirement allowing an object to be referenced by the layer number it occupies in the display list.</p>

<h1 class="datasheet">Examples</h1>

<p>1. Remove an object.<br/>
To remove an object from the display list the object's identifier and the layer number using when the object was placed is used.</p>

<pre>
// Place a shape to the display list for one frame.
movie.push_back(new FSPlaceObject(shape-&gt;getIdentifier(), 1, 400, 400));
movie.push_back(new FSShowFrame());

// now remove it.
movie.push_back(new FSRemoveObject(shape-&gt;getIdentifier(), 1));
movie.push_back(new FSShowFrame());
</pre>

<p>2. Move an object.<br/>
To move an object it first must be removed from the display list and repositioned at its new location. Adding the object, with a new location, on the same layer, although only one object can be displayed on a given layer, will not work. The object will be displayed twice.</p>

<pre>
// Add the shape to the display list.
movie.push_back(new FSPlaceObject(shape-&gt;getIdentifier(), 1, 400, 400));
movie.push_back(new FSShowFrame());

// Move shape to a new location, removing the original so it does not get displayed twice.
movie.push_back(new FSRemoveObject(shape-&gt;getIdentifier(), 1));
movie.push_back(new FSPlaceObject(shape-&gt;getIdentifier(), 1, 250, 300));
movie.push_back(new FSShowFrame());
</pre>

<h1 class="datasheet">History</h1>

<p>The FSRemoveObject class represents the RemoveObject tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1 and is superceded by the RemoveObject2 tag which was added in Flash 3.</p>

 */
    class DLL_DECL FSRemoveObject : public FSMovieObject
    {
public:
        FSRemoveObject(FSInputStream* aStream);

        /**  Constructs an FSRemoveObject object that will remove an object with the specified identifier from the given layer in the display list.

            @param anIdentifier the unique identifier for the object currently on the display list.
            @param aLayer the layer in the display list where the object is being displayed.
            */
        FSRemoveObject(int anIdentifier, int aLayer) : FSMovieObject(RemoveObject), identifier(anIdentifier), layer(aLayer) {}

        FSRemoveObject* clone() const { return new FSRemoveObject(*this); }

        const char* className() const;

        /** Gets the identifier of the object to be removed from the display list.

            @return the identifier of the object.
            */
        int getIdentifier() { return identifier; }

        /** Gets the layer in the display list where the object will be displayed.

            @return the layer number where the object is displayed.
            */
        int getLayer() { return layer; }

        /** Sets the identifier of the object to be removed from the display list.

            @param anIdentifier the identifier for the object.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the layer in the display list where the object will be displayed.

            @param aLayer the layer number where the object is displayed.
            */
        void setLayer(int aLayer) { layer = aLayer;}

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
        int layer;
    };
}

#endif
