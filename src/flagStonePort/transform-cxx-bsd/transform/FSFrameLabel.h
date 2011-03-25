/*
 *  FSFrameLabel.h
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

#ifndef __FSFrameLabel_h__
#define __FSFrameLabel_h__

#include "FSMovieObject.h"

#include "FSString.h"

namespace transform
{
/**
 * %FSFrameLabel defines a name for the current frame in a movie or movie clip. 
 *  
<p>The name can be referenced from other objects such as FSGotoFrame2 to simplify the creation of scripts to control movies by using a predefined name rather than the frame number. The label assigned to a particular frame should be unique. Frames may also be reference externally when specifying the movie to play using a URL - similar to the way names links are used in HTML. When the Flash Player loaded a movie it will begin playing at the frame specified in the URL.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSFrameLabel_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSFrameLabel_1">label</a></td>
<td>The name that will be assigned to the current frame.</td>
</tr>

<tr>
<td><a name="FSFrameLabel_2">isAnchor</a></td>
<td>Will the label be used as an anchor.</td>
</tr>

</table>

<p>The name is assigned to a particular frame when the FSFrameLabel object is defined prior to the FSShowFrame object that displays all the objects on the display list. The frame can then be referenced by its name once it has been defined. A frame cannot be referenced before the Player has loaded and displayed the frame that contains the corresponding FSFrameLabel object.</p>

<h1 class="datasheet">Examples</h1>

<p>The following simplified code samples illustrate how to use the FSFrameLabel class to refer to a frame by its name rather than a number.</P>

<p>1. Using the FSFrameLabel object.<br/>
This examples uses the FSFrameLabel object to allow the movie to loop back and replay an animation starting at a named frame.</p>

<pre>
movie.add(new FSFrameLabel("Frame Name"));
movie.add(new FSShowFrame());

...

FSDoAction* frameAction = new FSDoAction();

frameAction.add(new FSPush("FirstFrame"));
frameAction.add(new FSGotoFrame2(false));

movie.add(frameAction);
</pre>

<p>2. Controlling a movie clip.<br/>
The FSFrameLabel object can also be used to control the time-line of a movie clip. In this case though the mechanism is slightly different. From Flash 5 onward movie clips are defined as objects. The ExecuteMethod action is used to execute the gotoAndPlay() or gotoAndStop() methods that control a movie clip's time-line:</p>

<pre>
// First define the commands that animate the movie clip.
FSVector<FSMovieObject*> commands;
...
commands.push_back(new FSFrameLabel("Frame Name"));
commands.push_back(new FSShowFrame());

FSDefineMovieClip* movieClip = new FSDefineMovieClip(movie.newIdentifier(), commands);

// Add the movie clip to the display list on layer 1 at (400, 400). Give it the name
// "movieClip" to allow it to be referenced later.

movie.add(movieClip);
movie.add(new FSPlaceObject2(movieClip.getIdentifier(), 1, events, "movieClip", 400, 400));

// Create the FSDoAction object that will start the movie clip playing.

FSDoAction* clipActions = new FSDoAction();

// Movie clips objects can be controlled by executing pre-defined methods.

// Define the arguments followed by their number for the gotoAndPlay method.

clipActions.add(new FSPush("Frame Name"));
clipActions.add(new FSPush(1));

// Get the movie clip object using its name. It's location is specified relative to the "_root"
// level which represents the main time-line of the movie.

clipActions.add(new FSPush("_root"));
clipActions.add(new FSPush("movieClip"));
clipActions.add(new FSAction(FSAction.GetAttribute));

actions.add(new FSPush("gotoAndPlay"));
actions.add(new FSAction(FSAction.ExecuteMethod));

movie.add(clipActions);
movie.add(new FSShowFrame());
</pre>

<p>3. Defining an anchored frame.<br/>
Specifying a frame name as an anchor allows a movie start playing from any frame.</p>

<pre>
// Define the anchored frame in a movie.
movie.add(new FSFrameLabel("StartHere", true));
movie.add(new FSShowFrame());
....
movie.encodeToFile("movie.swf");
</pre>

<p>To start playing the movie at the frame labeled "StartHere" specify the label using the same format a HTML anchors:</p>

<pre>
http://www.flagstonesoftware.com/flash/movie.swf#StartHere
</pre>

<p>This may be used either in a browser window to load a file or form within a movie using the FSGetUrl or FSGetUrl2 actions.</p>

<h1 class="datasheet">History</h1>

<p>The FSFrameLabel class represents the FrameLabel tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3. In Flash 6 the label can support named anchors which allows a frame to be specified as the starting point when displaying a Flash movie in a web browser.</p>

 */  
    class DLL_DECL FSFrameLabel : public FSMovieObject
    {
public:
        FSFrameLabel(FSInputStream* aStream);

        FSFrameLabel() 
            : FSMovieObject(FrameLabel)
            , label()
            , anchor(false)
        {}

        /** Constructs an FSFrameLabel object with the specified name that will be assigned to the current frame. 

            @param aString a c-string defines the label name.
            */
        FSFrameLabel(const char* aString) 
            : FSMovieObject(FrameLabel)
            , label(aString)
            , anchor(false) 
        {}

        /** 
         * Constructs an FSFrameLabel object with the specified name. If the isAnchor flag is true 
         * then the frame will be directly selectable by a URL and the Flash Player will begin playing
         * the movie at the specified frame.

            @param aString the string that defines the label that will be assigned to the current frame.
            @param isAnchor if true the name will be used as an anchor when referencing the frame in a URL.
            */
        FSFrameLabel(const char* aString, bool isAnchor) : FSMovieObject(FrameLabel), label(aString), anchor(isAnchor) {}

        FSFrameLabel* clone() const { return new FSFrameLabel(*this); }

        const char* className() const;

        /** Gets the label string

            @return a c-string representing the label name.
            */
        const char* getLabel() const { return label.c_str(); }

        /** Sets the label that will be assigned to the current frame.

            @param aString the c-string that defines the label.
            */
        void setLabel(const char* aString) { label = aString; }

        /** Sets the label defining whether it will be referenced as an anchor or not.

            @param aString the string that defines the label that will be assigned to the current frame.
            @param isAnchor if true the name will be used as an anchor when referencing the frame in a URL.
            */
        void setLabel(const char* aString, bool isAnchor)
        {
            label = aString;
            anchor = isAnchor;
        }

        /** Gets the flag indicating whether the frame name is also used as an anchor so the frame can be referenced from outside of the movie.

            @return true if the frame is an anchor frame, false otherwise.
            */
        bool getAnchor() { return anchor; }

        /** Sets the flag indicating whether the frame name is also used as an anchor so the frame can be referenced from outside of the movie.

            @return isAnchor true if the frame is an anchor frame, false otherwise.
            */
        void setAnchor(bool isAnchor) { anchor = isAnchor; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString label;
        bool anchor;
    };
}

#endif
