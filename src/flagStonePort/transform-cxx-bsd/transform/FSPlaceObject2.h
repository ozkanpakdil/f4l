/*
 *  FSPlaceObject2.h
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

#ifndef __FSPlaceObject2_h__
#define __FSPlaceObject2_h__

#include "FSMovieObject.h"

#include "FSString.h"
#include "FSVector.h"
#include "FSCoordTransform.h"
#include "FSColorTransform.h"
#include "FSClipEvent.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSClipEvent>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSPlaceObject2 is used to add and manipulate objects (shape, button, etc.) on the Flash 
 * Player's display list. 
 *  
<p>FSPlaceObject2 supersedes the FSPlaceObject class providing more functionality and easier manipulation of  objects in the display list through the following operations:</p>

<ul>
<li>Place a new shape on the display list.</li>
<li>Change an existing shape by moving it to new location or changing its appearance.</li>
<li>Replace an existing shape with a another.</li>
<li>Define clipping layers to mask objects displayed in front of a shape.</li>
<li>Control the morphing process that changes one shape into another.</li>
<li>Assign names to objects rather than using their identifiers.</li>
<li>Define the sequence of actions that are executed when an event occurs in movie clip.</li>
</ul>

<p><b>Clipping Depth</b><br/>
With the introduction of Flash 3 the display list supported a clipping layer. This allowed the outline of an object to define a clipping path that is used to mask other objects placed in front of it. The clipping depth can be set to mask objects between the layer containing the clipping path and a specified layer.</p>

<p<b>Shape Morphing</b><br/>
Shapes that will be morphed are defined using the FSDefineMorphShape class which defines a start and end shape. The Flash Player performs the interpolation that transforms one shape into another. The progress of the morphing process is controlled by a ratio which ranges from 0.0 to 1.0, where 0 generates a shape identical to the starting shape in the FSDefineMorphShape object and 1.0 generates the shape at the end of the morphing process.</p>

<p<b>Movie Clip Events</b><br/>
With the introduction of Flash 5, movie clips (defined using the FSDefineMovieClip class) could specify sequences of actions that would be performed in response to mouse or keyboard events. The actions are specified using FSClipEvent objects and the FSPlaceObject2 class is used to register the actions in response to a particular event with the Flash player. Multiple events can be handled by defining an FSClipEvent for each type of event. For more information see the FSClipEvent class.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSPlaceObject2_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_1">place</a></td>
<td>Indicates whether a new object is being placed in the display list or an existing object is being modified or replaced.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_2">identifier</a></td>
<td>The identifier of the object to added to the display list.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_3">layer</a></td>
<td>Defines the order in which objects are displayed.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_4">transform</a></td>
<td>Optional. A coordinate transform defines the position, scale and rotation of the object.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_5">colorTransform</a></td>
<td>Optional. A colour transform defines any colour changes such as transparency effects.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_6">depth</a></td>
<td>Optional. The layer number up to which objects will be clipped by this object's outline.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_7">ratio</a></td>
<td>Optional. The point for the morphing process of a shape.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_8">name</a></td>
<td>Optional. A name to assign to the object.</td>
</tr>

<tr>
<td><a name="FSPlaceObject2_9">events</a></td>
<td>Optional. An array of FSClipEvent objects that define the actions that are performed when a specific movie clip event occurs.</td>
</tr>

<tr><td><a name="FSPlaceObject2_10">encodedEvents</a></td>
<td>An array of bytes containing encoded clip events can also be set. The encoded objects are typically generated by the parser in the Translate framework. The events array and encodedEvents cannot both be valid at the same time. Accessor methods used to set either of the attributes will set the other to null.</td>
</tr>

</table>

<p>Since only one object can be placed on a given layer an existing object on the display list can be identified by the layer it is displayed on rather than its identifier. Therefore Layer is the only required attribute. The remaining attributes are optional according to the different operation being performed:</p>

<ul>
<li>If an existing object on the display list is being modified then only the layer number is required. Previously in the FSPlaceObject class both the identifier and the layer number were required.</li>
<li>If no coordinate transform is applied to the shape (the default is a unity transform that does not change the shape) then it is not encoded.</li>
<li>Similarly if no colour transform is applied to the shape (the default is a unity transform that does not change the shape's colour) then it is not encoded.</li>
<li>If a shape is not being morphed then the ratio attribute may be left at its default value (-1.0).</li>
<li>If a shape is not used to define a clipping area then the depth attribute may be left at its default value (0).</li>
<li>If a name is net assigned to an object the name attribute may be left its default value (an empty string).</li>
<li>If no events are being defined for a movie clip then the array of FSClipEvent object may be left empty.</li>
</ul>

<p>The class provides a range of constructors which define different subsets of the attributes according to the type of operation that will be performed on an object in the Flash Player's display list. If an attribute is not specified in a constructor then it will be assigned a default value and will be omitted when the object is encoded.</p>

<h1 class="datasheet">Examples</h1>

<p>The following code samples illustrate how to use the FSPlaceObject2 class to manipulate objects on the display list. These examples use constructors with the most convenient (simplest) arguments. To define more complex place operations constructors are provided that take larger numbers of arguments and allow more complex transformations to be specified.</p>

<p>1. Display an object.<br/>
To display an object at a given location the placeType, identifier, layer number and x,y coordinates are required.</p>

<pre>
// Add the shape to the display list - on layer 1 at coordinates (400, 400)
// The constructor allows just the x and y coordinate to be defined, the
// FSCoordTransform object is constructed internally.

FSDefineShape shape = new FSDefineShape(movie.newIdentifier(), ......);

movie.add(new FSPlaceObject2(shape.getIdentifier(), 1, 400, 400));
movie.add(new FSShowFrame());
</pre>

<p>2. Move an object.<br/>
To move an object only the layer number is required. This simplifies the code required to manipulate existing objects when compared to the original FSPlaceObject class.</p>

<pre>
// Add the shape to the display list.
movie.add(new FSPlaceObject2(shape.getIdentifier(), 1, 400, 400));
movie.add(new FSShowFrame());

// Move shape to a new location.
movie.add(new FSPlaceObject2(1, 250, 300));
movie.add(new FSShowFrame());
</pre>

<p>3. Replace an existing object with another.<br/>
To move an object only the layer number is required. This simplifies the code required to manipulate existing objects when compared to the original FSPlaceObject class.</p>

<pre>
// Add the shape to the display list.
movie.add(new FSPlaceObject2(shape.getIdentifier(), 1, 400, 400));
movie.add(new FSShowFrame());

// Replace the shape.
movie.add(new FSPlaceObject2(newShape.getIdentifier(), 1));
movie.add(new FSShowFrame());
</pre>

<p>4. Defining a clipping layer.<br/>
The number of layers to clip using the outline of the shape as a path can be specified when placing the shape on the display list.</p>

<pre>
// Add the shape to the display list and clip objects on the next two layers

currentLayer = 1;
clipTo = currentLayer + 2;

movie.add(new FSPlaceObject2(shape.getIdentifier(), currentLayer, clipTo, 400, 400));
movie.add(new FSShowFrame());
</pre>

<p>5. Controlling the morphing process.<br/>
The ratio attribute controls the progress as an FSDefineMorphShape object changes from one shape into another.</p>

<pre>
FSShape triangle = new FSShape(....);
FSShape hexagon = new FSShape(....);

FSDefineMorphShape shape = new FSDefineMorphShape(movie.newIdentifier(), ...., triangle, hexagon);

movie.add(new FSPlaceObject2(shape.getIdentifier(), 1, 0.0, 400, 400));

// Morph the shapes over 10 frames

for (float i=0.1; i&lt;1.0; i+= 0.1)
{
    movie.add(new FSPlaceObject(1, i));
    movie.add(new FSShowFrame());
}
</pre>

<p>6. Defining a movie clip event.<br/>
FSClipEvent objects are ONLY used to define the sequence of actions executed when a particular event occurs in a movie clip.</p>

<pre>
// Define an array of clip events that will contain one event that defines the
// behaviour of the movie clip in response to a mouse down event.

FSVector<FSClipEvent> events;

FSClipEvent clipEvent(FSClipEvent.MouseDown);

// Add one or more actions for the mouse down event.

clipEvent.add(...);
...

// Add the clip event to the array of events for the movie clip.

events.push_back(clipEvent);

// Create the commands to animate the movie clip.

FSVector<FSActionObject*> commands;

commands.push_back(...);

FSDefineMovieClip* movieClip = new FSDefineMovieClip(movie.newIdentifier(), commands);

// Now place the movie clip on the screen on layer 1 at (400, 400).

movie.add(new FSPlaceObject2(movieClip.getIdentifier(), 1, events, 400, 400));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSPlaceObject2 class represents the PlaceObject2 tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSPlaceObject2 : public FSMovieObject
    {
public:
        /** Definition of the different ways to place an object on the Flash Player's, display list using the FSPlaceObject2 class.
            */
        enum placeType { Modify = 1, New = 2, Replace = 3 };

        FSPlaceObject2(FSInputStream* aStream);

        /** Constructs an FSPlaceObject2 object to place a new object or replace an existing object on the display list.
        
            @param type the type of place operation to be performed, either New or Replace.
            @param anIdentifier the identifier of a new object to be displayed.
            @param aLayer the layer number on which an object is being displayed.
            @param aTransform an FSCoordTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(placeType type, int anIdentifier, int aLayer, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform()) 
            : FSMovieObject(PlaceObject2)
            , place(type)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(aTransform)
            , colorTransform(aColorTransform)
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object to place new morphing shape on the display list either placing the shape for the first time or replacing an existing object.
            
            @param type the type of place operation to be performed, either New or Replace.
            @param anIdentifier the identifier of a new object to be displayed.
            @param aLayer the layer number on which an object is being displayed.
            @param aRatio the ratio of the progress in morphing the shape.
            @param aTransform an FSCoordTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(placeType type, int anIdentifier, int aLayer, float aRatio, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform()) 
            : FSMovieObject(PlaceObject2)
            , place(type)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(aTransform)
            , colorTransform(aColorTransform)
            , ratio(aRatio)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0)
        {}

        /** Constructs an FSPlaceObject2 object to place a shape on the display list that defines a clipping path that will clip objects for the specified number of layers. 

            @param type the type of place operation to be performed, either New or Replace.
            @param anIdentifier the identifier of a new object to be displayed.
            @param aLayer the layer number on which an object is being displayed.
            @param aDepth the layer number up to which objects will be clipped by this object's outline.
            @param aTransform an FSCoordTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(placeType type, int anIdentifier, int aLayer, int aDepth, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform()) 
            : FSMovieObject(PlaceObject2)
            , place(type)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(aTransform)
            , colorTransform(aColorTransform)
            , ratio(-1.0f)
            , depth(aDepth)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object that places a movie clip on the display list.

            @param type the type of place operation to be performed, either New or Replace.
            @param anIdentifier the identifier of a new movie clip to be displayed.
            @param aLayer the layer number on which the clip is being displayed.
            @param anArray an array of FSClipEvent objects that define the events responded to by the movie clip.
            @param aTransform an FSCoordTransform object that will be applied to the movie displayed in the display list at layer, aLayer.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(placeType type, int anIdentifier, int aLayer, const FSVector<FSClipEvent>& anArray, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform()) 
            : FSMovieObject(PlaceObject2)
            , place(type)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(aTransform)
            , colorTransform(aColorTransform)
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events(anArray)
            , encodedEvents(0)
            , encodedLength(0)
        {}

        /** Constructs an FSPlaceObject2 object that places a named movie clip on the display list.
            
            @param type the type of place operation to be performed, either New or Replace.
            @param anIdentifier the identifier of a new movie clip to be displayed.
            @param aLayer the layer number on which the clip is being displayed.
            @param anArray an array of FSClipEvent objects that define the events responded to by the movie clip.
            @param aName a c-string that define a name for the movie clip.
            @param aTransform an FSCoordTransform object that will be applied to the movie displayed in the display list at layer, aLayer.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(placeType type, int anIdentifier, int aLayer, const FSVector<FSClipEvent>& anArray, const char* aName, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform())
            : FSMovieObject(PlaceObject2)
            , place(type), layer(aLayer)
            , identifier(anIdentifier)
            , transform(aTransform)
            , colorTransform(aColorTransform)
            , ratio(-1.0f)
            , depth(0)
            , name(aName)
            , events(anArray)
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object to place a new object on the display list at the coordinates on the screen.

            @param anIdentifier the identifier of a new object to be displayed.
            @param aLayer the layer number on which an object is being displayed.
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            */
        FSPlaceObject2(int anIdentifier, int aLayer, int x, int y) 
            : FSMovieObject(PlaceObject2)
            , place(New)
            , layer(aLayer) 
            , identifier(anIdentifier)
            , transform(FSCoordTransform(x, y))
            , colorTransform()
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0)
        {}

        /** Constructs an FSPlaceObject2 object to place new morphing shape on the display list at the coordinates on the screen.

            @param anIdentifier the identifier of a new object to be displayed.
            @param aLayer the layer number on which an object is being displayed.
            @param aRatio the ratio of the progress in morphing the shape.
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            */
        FSPlaceObject2(int anIdentifier, int aLayer, float aRatio, int x, int y) 
            : FSMovieObject(PlaceObject2)
            , place(New)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(FSCoordTransform(x, y))
            , colorTransform()
            , ratio(aRatio)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0)
        {}

        /** Constructs an FSPlaceObject2 object to place a new shape on the display list with the specified coordinate and optional colour transform.

            @param anIdentifier the identifier of a new object to be displayed.
            @param aLayer the layer number on which an object is being displayed.
            @param aTransform an FSCoordTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(int anIdentifier, int aLayer, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform()) 
            : FSMovieObject(PlaceObject2)
            , place(New)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(aTransform)
            , colorTransform(aColorTransform)
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object to place a new shape on the display list at the coordinates on the screen that defines a clipping path that will clip objects for the specified number of layers.

            @param anIdentifier the identifier of a new object to be displayed.
            @param aLayer the layer number on which an object is being displayed.
            @param aDepth the layer number up to which objects will be clipped by this object's outline.
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            */
        FSPlaceObject2(int anIdentifier, int aLayer, int aDepth, int x, int y) 
            : FSMovieObject(PlaceObject2)
            , place(New)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(FSCoordTransform(x, y))
            , colorTransform()
            , ratio(-1.0f)
            , depth(aDepth)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object that places a new movie clip on the display list at the coordinates on the screen.

            @param anIdentifier the identifier of a new movie clip to be displayed.
            @param aLayer the layer number on which the clip is being displayed.
            @param anArray an array of FSClipEvent objects that define the events responded to by the movie clip.
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            */
        FSPlaceObject2(int anIdentifier, int aLayer, const FSVector<FSClipEvent>& anArray, int x, int y) 
            : FSMovieObject(PlaceObject2)
            , place(New)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(FSCoordTransform(x, y))
            , colorTransform()
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events(anArray)
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object that places a new, named movie clip on the display list at the coordinates on the screen.

            @param anIdentifier the identifier of a new movie clip to be displayed.
            @param aLayer the layer number on which the clip is being displayed.
            @param anArray an array of FSClipEvent objects that define the events responded to by the movie clip.
            @param aName a c-string that define a name for the movie clip.
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            */
        FSPlaceObject2(int anIdentifier, int aLayer, const FSVector<FSClipEvent>& anArray, const char* aName, int x, int y) 
            : FSMovieObject(PlaceObject2)
            , place(New)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(FSCoordTransform(x, y))
            , colorTransform()
            , ratio(-1.0f)
            , depth(0)
            , name(aName)
            , events(anArray)
            , encodedEvents(0)
            , encodedLength(0)
        {}

        /** Constructs an FSPlaceObject2 object that places a new, named movie clip 
         * on the display list at the coordinates on the screen. The array of bytes
         * contains the encoded FSClipEvent objects which specify the events and 
         * actions that the movie clip will respond to. These are typically generated
         * using the classes in the Translate framework.
         * 
         * @param anIdentifier the identifier of a new movie clip to be displayed.
         * @param aLayer the layer number on which the clip is being displayed.
         * @param bytes an array of encoded clip event objects.
         * @param size the number of bytes in the encoded clip event objects.
         * @param aName a c-string that define a name for the movie clip.
         * @param x the x-coordinate where the object will be displayed.
         * @param y the y-coordinate where the object will be displayed.
         */
        FSPlaceObject2(int anIdentifier, int aLayer, byte* bytes, size_t size, const char* aName, int x, int y)
            : FSMovieObject(PlaceObject2)
            , place(New)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform(FSCoordTransform(x, y))
            , colorTransform()
            , ratio(-1.0f)
            , depth(0)
            , name(aName)
            , events()
            , encodedEvents(bytes)
            , encodedLength(size)
        {}
    
        /** Constructs an FSPlaceObject2 object to modify existing object on the display list.

            @param aLayer the layer number on which an object is being displayed.
            @param aTransform an FSCoordTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(int aLayer, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform()) 
            : FSMovieObject(PlaceObject2)
            , place(Modify)
            , layer(aLayer)
            , identifier(0)
            , transform(aTransform)
            , colorTransform(aColorTransform)
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object to change an existing morphing shape on the display list.

            @param aLayer the layer number on which an object is being displayed.
            @param aRatio the ratio of the progress in morphing the shape.
            @param aTransform an FSCoordTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(int aLayer, float aRatio, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform()) 
            : FSMovieObject(PlaceObject2)
            , place(Modify)
            , layer(aLayer)
            , identifier(0)
            , transform(aTransform)
            , colorTransform(aColorTransform)
            , ratio(aRatio)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object to change the location of an existing object on the display list.

            @param aLayer the layer number on which an object is being displayed.
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            */
        FSPlaceObject2(int aLayer, int x, int y) 
            : FSMovieObject(PlaceObject2)
            , place(Modify)
            , layer(aLayer)
            , identifier(0)
            , transform(FSCoordTransform(x, y))
            , colorTransform()
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object to change the location and morphing ratio of an existing morphing shape on the display list.

            @param aLayer the layer number on which an object is being displayed.
            @param aRatio the ratio of the progress in morphing the shape.
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            */
        FSPlaceObject2(int aLayer, float aRatio, int x, int y) 
            : FSMovieObject(PlaceObject2)
            , place(Modify)
            , layer(aLayer)
            , identifier(0)
            , transform(FSCoordTransform(x, y))
            , colorTransform()
            , ratio(aRatio)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object to change the colour of an existing shape.

            @param aLayer the layer number on which an object is being displayed.
            @param aColorTransform an FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(int aLayer, const FSColorTransform& aColorTransform) 
            : FSMovieObject(PlaceObject2)
            , place(Modify)
            , layer(aLayer)
            , identifier(0)
            , transform()
            , colorTransform(aColorTransform)
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSPlaceObject2 object to change the colour of an existing morphing shape on the display list.

            @param aLayer the layer number on which an object is being displayed.
            @param aRatio the ratio of the progress in morphing the shape.
            @param aColorTransform an optional FSColorTransform object that will be applied to the object displayed in the display list at layer, aLayer.
            */
        FSPlaceObject2(int aLayer, float aRatio, const FSColorTransform& aColorTransform) 
            : FSMovieObject(PlaceObject2)
            , place(Modify)
            , layer(aLayer)
            , identifier(0)
            , transform()
            , colorTransform(aColorTransform)
            , ratio(aRatio)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}
        
        /** Constructs an FSPlaceObject2 object that replaces an existing object on the display list.

            @param anIdentifier the identifier of the object that will replaced the one current displayed on <i>aLayer</i>.
            @param aLayer the layer number on which the object being replaced is displayed.
            */
        FSPlaceObject2(int anIdentifier, int aLayer) 
            : FSMovieObject(PlaceObject2)
            , place(Replace)
            , layer(aLayer)
            , identifier(anIdentifier)
            , transform()
            , colorTransform()
            , ratio(-1.0f)
            , depth(0)
            , name("")
            , events()
            , encodedEvents(0)
            , encodedLength(0) 
        {}
        
        FSPlaceObject2* clone() const { return new FSPlaceObject2(*this); }

        const char* className() const;

        /** Adds a clip event to the array of clip events.

            @param aClipEvent a clip event object.
            */
        void add(const FSClipEvent& aClipEvent) { events.push_back(aClipEvent); }

        /** Adds all the clip events in an array to the array of clip events.

            @param anArray an array of clip event objects.
            */
        void add(const FSVector<FSClipEvent>& anArray);

        /** Gets the type of place operation being performed.

            @return the placement type.
            */
        int getPlaceType() const { return place; }

        /** Gets the Layer on which the object will be displayed in the display list. 

            @return the display list layer number.
            */
        int getLayer() const { return layer; }

        /** Gets the identifier of the object to be placed. This is only required when placing an object for the first time. Subsequent references to the object on this layer can simply use the layer number. If the identifier is not being used zero is returned.

            @return the identifier of an object.
            */
        int getIdentifier() const { return identifier; }

        /** Gets the coordinate transform that will be applied to an object in the display list. If this is a unity transform then the shape will be unchanged and the transform is not encoded.

            @return the FSCoordTransform applied to the object.
            */
        FSCoordTransform& getTransform() { return transform; }

        /** Gets the colour transform that will be applied to an object in the display list. If this is a unity transform then the shape's colour will be unchanged and the transform is not encoded.

            @return the FSColorTransform applied to the object.
            */
        FSColorTransform& getColorTransform() { return colorTransform; }

        /** Gets the morph ratio, in the range 0.0 to 1.0 that defines the progress in the morphing process performed by the Flash Player from the defined start and end shapes. A value of 0.0 indicates the start of the process and 1.0 the end. If the ratio is not being used then a value of Transform::VALUE_NOT_SET is returned.

            @return the morph ratio, in the range 0..1.
            */
        float getRatio() const { return ratio; }

        /** Gets the number of layers that will be clipped by the object placed on the layer specified in this object.

            @return the number of layers that will be clipped.
            */
        int getClippingDepth() const { return depth; }

        /** Gets the name of the object. Returns an empty string if no name is assigned.

            @return the name assigned to an object.
            */
        const char* getName() { return name.c_str(); }

        /** Gets the array of FSClipEvent object that define the actions that will be executed in response to events that occur in the FSDefineMovieClip being placed. The array may be empty.

            @return the array of clip events
            */
        FSVector<FSClipEvent>& getClipEvents() { return events; }

        /** Sets the type of placement, either New, Modify or Replace.

            @param aType the type of operation to be performed.
            */
        void setPlaceType(int aType) { place = aType; }

        /** Sets the layer at which the object will be placed. 

            @param aNumber the layer number on which the object is being displayed.
            */
        void setLayer(int aNumber) { layer = aNumber; }

        /** Sets the identifier of the object. This attribute is not required if an existing shape is being modified.

            @param anIdentifier the identifier of a new object to be displayed.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the coordinate transform that defines the position where the object will be displayed. If the transform is a unity transform the object will not be changed and so the transform will not be encoded.
            
            @param aTransform an FSCoordTransform object that will be applied to the object displayed.
            */
        void setTransform(const FSCoordTransform& aTransform) { transform = aTransform; }

        /** Sets the colour transform that defines the colour effects applied to the object. If the transform is a unity transform the object's colour will not be changed and so the transform will not be encoded.

            @param aTransform an FSColorTransform object that will be applied to the object displayed.
            */
        void setColorTransform(const FSColorTransform& aTransform) { colorTransform = aTransform; }

        /** Sets point of the morphing process for a morph shape in the range 0.0 to 1.0. The value may be set to Transform::VALUE_NOT_SET if the shape is not being morphed.

            @param aRatio the progress in the morphing process.
            */
        void setRatio(float aRatio) { ratio = aRatio; }

        /** Sets the layer number up to which objects will be masked or clipped. May be set to zero if the shape being placed does not define a clipping path.

            @param aDepth the number of layers clipped.
            */
        void setClippingDepth(int aDepth) { depth = aDepth; }

        /** Set the name of an object to be displayed. If a shape is not being assigned a name then setting the argument to an empty string will omit the attribute when the object is encoded.

            @param aString the name assigned to the object.
            */
        void setName(const char* aString) { name = aString; }

        /** Set the array of Clip events. Clip Events are only valid for movie clips and the array should be empty when placing other types of object.

            @param anArray an array of FSClipEvent objects.
            */
        void setClipEvents(const FSVector<FSClipEvent>& anArray) { events = anArray; }

        /** 
         * Set the encoded clip event objects generated by the classes in the Translate 
         * framework. If the object already contains an array of clip events objects
         * then they will be deleted.
         * 
         * @param bytes the array of encoded clip events.
         * @param size the number of bytes in the encoded clip event data.
         */
        void setEncodedEvents(byte* bytes, size_t size);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool containsTransform() const;
        bool containsColorTransform(FSOutputStream* aStream) const;
        bool containsClipEvents() const;
        bool containsClippingDepth() const;
        bool containsName() const;
        bool containsRatio() const;

        int place;
        int layer;
        int identifier;
        
        FSCoordTransform transform;
        FSColorTransform colorTransform;
        
        float ratio;
        int depth;
        
        FSString name;
        
        FSVector<FSClipEvent> events;
        byte* encodedEvents;
        size_t encodedLength;
    };
} 

#endif
