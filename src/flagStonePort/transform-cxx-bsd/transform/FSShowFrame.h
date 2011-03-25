/*
 *  FSShowFrame.h
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

#ifndef __FSShowFrame_h__
#define __FSShowFrame_h__ 1

#include "FSMovieObject.h"

namespace transform
{
/**
 * %FSShowFrame is used to instruct the Flash Player to display a single frame in a movie or 
 * movie clip. 
 * 
<p>When a frame is displayed the Flash Player performs the following:</p>

<ul>
<li>The contents of the Flash Player's display list are drawn on the screen.</li>
<li>Any actions defined using a FSDoAction object are executed.</li>
</ul>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSShowFrame_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

</table>

<p>Objects are placed in the display list using the FSPlaceObject and FSPlaceObject2 classes and removed using the FSRemoveObject and FSRemoveObject2 classes. An object which has been added to the display list will be displayed in each frame until it is explicitly removed. There is no need to repeatedly add it to the display list.</p>

<p>The scope of a frame is delineated by successive FSShowFrame objects. All the commands that affect change the state of the display list or define actions to be executed take effect when the Flash Player displays the frame. All the objects displayed in a frame must be defined before they can be displayed. The movie is displayed as it is downloaded so displaying objects that are defined later in a movie is not allowed.</p>

<pre>
FSMovie movie;

// The scope of the first frame starts with the first object.
movie.push_back(new FSSetBackgroundColor(FSColor(255, 255, 255)));
...
movie.push_back(new FSShowFrame());

// Frame 2 - starts when the previous frame is displayed.

// All displayable objects are referenced using unique identifier.

int identifer = movie.newIdentifier();

// Define a shape to be displayed.

movie.push_back(new FSDefineShape(identifer, ......));

// Add the shape to the display list - on layer 1 at coordinates (400, 400)

movie.add(new FSPlaceObject2(FSPlaceObject2::New, identifier, 1, 400, 400));

// Add some actions

FSDoAction* frameActions = new FSDoAction(); 

frameActions-&gt;push_back(anAction);
frameActions-&gt;push_back(anotherAction);

movie.add(frameActions);

// The shape is displayed and the actions executed when the FSShowFrame command is executed.

movie.add(new FSShowFrame());
</pre>
<h1 class="datasheet">History</h1>

<p>The FSShowFrame class represents the ShowFrame data structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSShowFrame : public FSMovieObject
    {
public:
        FSShowFrame(FSInputStream* aStream);

        /** Constructs an FSShowFrame object. */
        FSShowFrame() : FSMovieObject(ShowFrame) {}

        FSShowFrame* clone() const { return new FSShowFrame(*this); }

        const char* className() const;

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    };
} 

#endif
