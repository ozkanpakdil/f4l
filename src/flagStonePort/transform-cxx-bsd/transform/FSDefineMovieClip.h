/*
 *  FSDefineMovieClip.java
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

#ifndef __FSDefineMovieClip_h__
#define __FSDefineMovieClip_h__

#include "FSDefineObject.h"

#include "FSVector.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSMovieObject*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSDefineMovieClip defines a movie clip that animates shapes within a movie. 
 * 
<p>It contains an array of movie objects that define the placement of shapes, buttons, text and images and the order in which they are displayed through a time-line that is separate from the parent movie.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSDefineMovieClip_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineMovieClip_1">identifier</a></td>
<td>A unique identifier, in the range 1..65535, for the movie clip.</td>
</tr>

<tr>
<td><a name="FSDefineMovieClip_2">objects</a></td>
<td>An array of FSMovieObject objects that define the commands that are executed by the Flash Player to animate the movie clip.</td>
</tr>
</table>

<p>Although a movie clip contains the commands that instructs the Flash Player on how to animate the clip it cannot contain any new definitions of objects. All definitions must be in the main movie. All objects referred to by the movie clip must be also defined in the main movie before they can be used.</p>

<p>When using the FSDefineMovieClip object can only contain objects from the following classes: FSShowFrame, FSPlaceObject, FSPlaceObject2, FSRemoveObject, FSRemoveObject2, FSDoAction, FSStartSound, FSFrameLabel, FSSoundStreamHead, FSSoundStreamHead2 or FSSoundStreamBlock. Other objects are not allowed.</p>

<h1 class="datasheet">History</h1>

<p>The FSDefineMovieClip class represents the DefineSprite tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */  
    class DLL_DECL FSDefineMovieClip : public FSDefineObject
    {
public:
        FSDefineMovieClip(FSInputStream* aStream);

        /** Constructs an FSDefineMovieClip object with the unique identifier and array of pointers to movie objects. The FSDefineMovieClip object assumes ownership of all the objects in the array.

            @param anIdentifier a unique identifier for the movie clip.
            @param anArray an array of movie objects.
            */
        FSDefineMovieClip(int anIdentifier, FSVector<FSMovieObject*>anArray) : FSDefineObject(DefineMovieClip, anIdentifier), objects(anArray) {}

        FSDefineMovieClip(const FSDefineMovieClip& rhs);

        ~FSDefineMovieClip();

        FSDefineMovieClip& operator= (const FSDefineMovieClip& rhs);

        FSDefineMovieClip* clone() const { return new FSDefineMovieClip(*this); }

        const char* className() const;

        /** Adds an object to the array of movie objects. The FSDefineMovieClip object assumes ownership of the object. 

            @param anObject a pointer to an object.
            */
        void add(FSMovieObject* anObject) { objects.push_back(anObject); }

        /** Adds all the objects in an array to the array of movie objects. The FSDefineMovieClip object assumes ownership of all the objects in the array.

            @param anArray an array of pointers to movie objects.
            */
        void add(const FSVector<FSMovieObject*>& anArray);

        /** Gets the array of movie objects.

            @return the array of movie objects.
            */
        FSVector<FSMovieObject*>& getObjects() { return objects; }

        /** Sets the array of movie tag objects. All the objects added are owned by the FSDefineMovieClip object.

            @param anArray the array of movie objects.
            */
        void setObjects(FSVector<FSMovieObject*> anArray) { objects = anArray; }
     
        /** Gets the total number of frames in the movie clip.
    
            @return the number of frames.
            */
        int getFrameCount();

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
        
private:
        FSVector<FSMovieObject*>objects;
    };
}

#endif
