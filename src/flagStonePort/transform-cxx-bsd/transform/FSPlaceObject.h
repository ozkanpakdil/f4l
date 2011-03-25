/*
 *  FSPlaceObject.h
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

#ifndef __FSPlaceObject_h__
#define __FSPlaceObject_h__ 1

#include "FSMovieObject.h"

#include "FSCoordTransform.h"
#include "FSColorTransform.h"

namespace transform
{
/**
 * %FSPlaceObject is used to add an object (shape, button, etc.) to the Flash Player's display list.
 *  
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSPlaceObject_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSPlaceObject_1">identifier</a></td>
<td>The unique identifier, in the range 1..65535, of the object to be displayed.</td>
</tr>

<tr>
<td><a name="FSPlaceObject_2">layer</a></td>
<td>The Display List layer on which the object is drawn.</td>
</tr>

<tr>
<td><a name="FSPlaceObject_3">coordTransform</a></td>
<td>An FSCoordTransform which defines the location and appearance of the object.</td>
</tr>

<tr>
<td><a name="FSPlaceObject_4">colorTransform</a></td>
<td>An FSColorTransform which defines any changes to be made to the object's original colour. Optional. May be set to null if an object's colour is not being changed.</td>
</tr>

</table>

<p>Every class that defines a shape, button etc. is assigned a unique identifier. This is an integer in the range 1..65535 and is used to refer to objects when performing actions such as adding or removing them from the display list.</p>

<p>The display list contains all the objects that are currently visible on the Flash Player's screen. The display list is ordered in layers, with one (and only one) object displayed on each layer. The Layer defines the order in which objects are displayed. Objects with a higher layer number are displayed in front of objects on a lower layer.</p>

<p>The coordinate transform is principally used to specify the location of the object when it is drawn on the screen however more complex coordinate transforms can also be specified such as rotating or scaling the object without changing the original definition.</p>

<p>Similarly the color transform allows the color of the object to be changed when it is displayed without changing the original definition. The FSPlaceObject class only supports opaque colours so although the FSColorTransform supports transparent colours this information is ignored by the Flash Player. The colour transform is optional and may be set to the null object.</p>

<h1 class="datasheet">Examples</h1>

<p>The following simplified code fragments illustrate how the FSPlaceObject class can be used.</p>

<p>1. Display an object.<br/> 
Display an object on layer 1 at (400, 400). FSPlaceObject provides a constructor which specifies just the x and y coordinates, the FSCoordTransform object is constructed internally.</p>

<pre>
FSDefineShape* shape = new FSDefineShape(movie.newIdentifier(), ......)

movie.push_back(shape);
movie.push_back(new FSPlaceObject(shape-&gt;getIdentifier(), 1, 400, 400));
movie.push_back(new FSShowFrame());
</pre>

<p>2. Scale an object.<br/>
Scale an object to twice its original size by specifying a more complex coordinate transformation. Complex transforms can be created by compositing individual steps.</p>

<pre>
FSCoordTransform translate(200, 200);
FSCoordTransform scale(2.0, 2.0);
FSCoordTransform transform = FSCoordTransform::composite(location, scale);

movie.add(new FSPlaceObject(shape-&gt;getIdentifier(), 1, transform));
movie.add(new FSShowFrame());
</pre>

<p>3. Move an object.<br/>
To move an object the FSPlaceObject class must be used in conjunction with the FSRemoveObject class to first remove the object from its existing position before being placed at the new location.</p>

<pre>
// Add the shape to the display list.
movie.add(new FSPlaceObject(shape-&gt;getIdentifier(), 1, 400, 400));
movie.add(new FSShowFrame());

// Move shape to a new location, removing the original so it does not get displayed twice.
movie.add(new FSRemoveObject(shape-&gt;getIdentifier(), 1));
movie.add(new FSPlaceObject(shape-&gt;getIdentifier(), 1, 250, 300));
movie.add(new FSShowFrame());
</pre>

<h1 class="datasheet">History</h1>

<p>The FSPlaceObject class represents the PlaceObject tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1 and is superceded by the PlaceObject2 tag which was added in Flash 3.</p>

 */
    class DLL_DECL FSPlaceObject : public FSMovieObject
    {
public:
        FSPlaceObject(FSInputStream* aStream);

        /** Constructs an FSPlaceObject object that places an object with the identifier onto the display list layer at the specified coordinates (x,y). A translation coordinate transform is created from the pair of coordinates.

         @param anIdentifier the unique identifier for the object to the placed on the display list.
         @param aLayer the layer in the display list where the object will be placed.
         @param xLocation the x-coordinate where the object will be drawn.
         @param yLocation the y-coordinate where the object will be drawn.
         */
        FSPlaceObject(int anIdentifier, int aLayer, int xLocation, int yLocation) : FSMovieObject(PlaceObject), identifier(anIdentifier), layer(aLayer), transform(FSCoordTransform(xLocation, yLocation)), colorTransform() {}

        /** Constructs an FSPlaceObject object that places the object with the identifier onto the display list layer with the specified coordinate transform.

            @param anIdentifier the unique identifier for the object to the placed on the display list.
            @param aLayer the layer in the display list where the object will be placed.
            @param aTransform an FSCoordTransform object that defines the orientation, size and location of the object when it is drawn.
            */
        FSPlaceObject(int anIdentifier, int aLayer, const FSCoordTransform& aTransform) : FSMovieObject(PlaceObject), identifier(anIdentifier), layer(aLayer), transform(aTransform), colorTransform() {}

        /** Constructs an FSPlaceObject object that places the the object with the identifier onto the display list layer with the specified coordinate and colour transforms.

            @param anIdentifier the unique identifier for the object to the placed on the display list.
            @param aLayer the layer in the display list where the object will be placed.
            @param aTransform an FSCoordTransform object that defines the orientation, size and location of the object when it is drawn.
            @param aColorTransform an FSColorTransform object that defines the change applied to the color of the object when it is drawn.
            */
        FSPlaceObject(int anIdentifier, int aLayer, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform) : FSMovieObject(PlaceObject), identifier(anIdentifier), layer(aLayer), transform(aTransform), colorTransform(aColorTransform) {}

        FSPlaceObject* clone() const { return new FSPlaceObject(*this); }

        const char* className() const;

        /** Gets the identifier of the object to be added to the display list.

            @return the identifier of the object.
            */
        int getIdentifier() { return identifier; }

        /** Gets the layer in the display list where the object will be displayed.

            @return the number of the layer in the display list.
            */
        int getLayer() { return layer; }

        /** Gets the coordinate transform that will be applied to the object when it is displayed.

            @return the FSCoordTransform applied to the object.
            */
        FSCoordTransform& getTransform() { return transform; }

        /** Gets the colour transform that defines any colour changes applied to the object when it is displayed.

            @return the FSColorTransform applied to the object.
            */
        FSColorTransform& getColorTransform() { return colorTransform; }

        /** Sets the identifier of the object to be added to the display list.

            @param anIdentifier the identifier of the object.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the layer number in the display list where the object will be displayed.

            @param aLayer the layer number in the display list.
            */
        void setLayer(int aLayer) { layer = aLayer; }

        /** Sets the coordinate transform that defines the change in orientation, size and location of the object when it is displayed.

            @param aTransform the FSCoordTransform applied to the object.
            */
        void setTransform(const FSCoordTransform& aTransform) { transform = aTransform; }

        /** Sets the colour transform that defines any colour changed applied when the object is displayed.

            @param aColorTransform the FSColorTransform applied to the object.
            */
        void setColorTransform(const FSColorTransform& aColorTransform) { colorTransform = aColorTransform; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
        int layer;
        FSCoordTransform transform;
        FSColorTransform colorTransform;
    };
}

#endif
