/*
 *  FSClipEvent.h
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

#ifndef __FSClipEvent_h__
#define __FSClipEvent_h__ 1

#include "FSVector.h"

#include "FSTransformObject.h"
#include "FSActionObject.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSActionObject*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSClipEvent is used to define the actions that a movie clip will execute in response 
 * to a particular event.
 * 
<p>FSClipEvent objects are added to an FSPlaceObject2 object and the actions are registered with the Flash Player when the movie clip is added to the display list.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSClipEvent_0">event</a></td><td>A code representing one or more events that the movie clip will respond to.</td></tr>
<tr><td><a name="FSClipEvent_1">actions</a></td><td>An array of actions that will be executed when one or more of the specified events occur.</td></tr>

<tr><td><a name="FSClipEvent_2">encodedActions</a></td>
<td>An array of bytes containing encoded actions can also be set. The encoded actions are typically generated by the parser in the Translate framework. The actions array and encodedActions cannot both be valid at the same time. Accessor methods used to set either of the attributes will set the other to null.</td>
</tr>

</table>

<p>The events that a movie clip responds to are:</p>

<table class="datasheet">
<tr bgcolor="#CCCCFF" valign="top"><th align="left">Event</th>
<th align="left">Description</th></tr>
<tr><td>Load</td><td>occurs when the movie clip is finished loading.</td></tr>
<tr><td>Unload</td><td>occurs when the movie clip is unloaded from the parent movie.</td></tr>
<tr><td>EnterFrame</td><td>occurs when each frame in the movie clip is played.</td></tr>
<tr><td>MouseMove</td><td>occurs when the mouse pointer is moved.</td></tr>
<tr><td>MouseDown</td><td>occurs when the left mouse button is pressed while the cursor is outside of the bounding rectangle of the movie clip.</td></tr>
<tr><td>MouseUp</td><td>occurs when the left mouse button is pressed  and released while the cursor is outside of the bounding rectangle of the movie clip.</td></tr>
<tr><td>KeyDown</td><td>occurs when any key is pressed on the keyboard. From Flash 6  a key code can be specified to identify a specific key rather than testing for the value inside the actions that are executed in response to the event.</td></tr>
<tr><td>KeyUp</td><td>occurs when any key being pressed on the keyboard is released.</td></tr>
<tr><td>Data</td><td>occurs when an FSGetUrl2 action is executed with the movie clip specified as a target.</td></tr>
</table>

<p>Starting with Flash 6 movie clips also respond to the same set of events that buttons do:</p>

<table class="datasheet">
<tr><td>RollOver</td><td>occurs when the mouse cursor moves over the movie clip.</td></tr>
<tr><td>RollOut</td><td>occurs when the mouse cursor moves out of the bounding rectangle  of the movie clip.</td></tr>
<tr><td>Press</td><td>occurs when the mouse button is clicked while the mouse cursor is inside bounding rectangle of the movie clip.</td></tr>
<tr><td>Release</td><td>occurs when the mouse button is clicked and released while the mouse cursor is inside bounding rectangle of the movie clip.</td></tr>
<tr><td>ReleaseOut</td><td>occurs when the mouse button is clicked and the mouse cursor is released outside of the bounding rectangle of the movie clip.</td></tr>
<tr><td>DragOut</td><td>occurs when the mouse button is clicked and the mouse cursor is dragged out of the bounding rectangle of the movie clip.</td></tr>
<tr><td>DragOver</td><td>occurs when the mouse button is clicked, the mouse cursor is dragged into the bounding rectangle of the movie clip and the mouse button is released.</td></tr>
<tr><td>Initialize</td><td>occurs when a movie clip is initialized using the FSInitialize class.</td></tr>
</td></tr>
</table>

<p>Movie clips now also respond to keys being pressed on the keyboard. Keyboard events are defined by the character key being pressed, e.g. "t", "T", "$", etc. The ASCII code for the key is used to identify which key was pressed. Note that while multiple mouse events can be defined for a button only one keyboard event can be defined.</p>

<p>In Flash 7 a new construct event was added.</p>
    
<table class="datasheet">
<tr><td>Construct</a></td><td>The function of this event is undocumented.</td></tr>
</td></tr>
</table>

<p>IMPORTANT: The FSClipEvent object supports both the Flash 5, Flash 6 and Flash 7 event models. The events that are encoded to a file are determined by the version of the FSMovie in which the object is contained. The codes assigned to the different types of event ensure that the same value can be used to encode the object for each version of Flash.</p>

<p>For the KeyDown and KeyUp events, Flash ActionScript provides the Key object which contains the getCode() and isDown() functions that allow code to be written to test which key was pressed. Note that ActionScript is a high-level interpreted language similar to JavaScript. Transform supports actions that represent the compiled version of the ActionScript code. To create and compile ActionScript code then use Transform's sister product, Translate.</p>

<p>Each type of event is defined by a constant, for example, Load, EnterFrame, etc. An FSClipEvent object can define the actions that will be executed in response to multiple events. There are two ways to respond to multiple events. If the same set of actions should be executed then the event code that flags which events should be responded to can be generated by bitwise OR-ing together the individual constants:</p>

<pre>
int loadAndMouseMove = FSClipEvent.Load | FSClipEvent.MouseMove;
</pre>

<p>If different actions should be executed then an FSClipEvent object is created for each different set of events. The FSPlaceObject2 object that is used to register the actions for a movie clip with the Flash Player supports an array of FSClipEvent objects.</p>

<p>The array of actions may be empty. Although this situation does not perform any useful operation it is valid and may be encountered when parsing Flash files generated by a third party.</p>

<h1 class="datasheet">Examples</h1>

<p>The following simplified code fragments illustrate how the FSClipEvent class can be used.</p>

<p>1. Defining the actions for a single event.</p>

<pre>
FSDefineMovieClip movieClip = new FSDefineMovieClip(movie.newIdentifier(), commands);

FSClipEvent clipEvent(FSClipEvent.MouseDown);

clipEvent.add(anAction);
...

FSPlaceObject2 placeClip = new FSPlaceObject2(movieClip.getIdentifier(), 1, events, 400, 400);

placeClip.add(clipEvent);

movie.add(movieClip);
movie.add(placeClip);
</pre>

<p>2. Defining the actions for a compound event.<br/>
If a movie clip should execute the same set of actions for different types of event then the code for the compound event can be created by bitwise-OR'ing individual event codes.</p>

<pre>
FSDefineMovieClip movieClip = new FSDefineMovieClip(movie.newIdentifier(), commands);

FSClipEvent clipEvent(FSClipEvent.MouseDown | FSClipEvent.KeyDown, actions);
...
FSPlaceObject2* placeClip = new FSPlaceObject2(movieClip.getIdentifier(), 1, events, 400, 400)

placeClip.add(clipEvent);

movie.add(movieClip);
movie.add(placeClip);
</pre>

<p>3. Defining different sets of actions for events.<br/>
An FSClipEvent object is created for each set of events that a movie clip must respond to.</p>

<pre>
FSDefineMovieClip* movieClip = new FSDefineMovieClip(movie.newIdentifier(), commands);
FSPlaceObject2* placeClip = new FSPlaceObject2(movieClip.getIdentifier(), 1, events, 400, 400)

FSClipEvent mouseEvent(FSClipEvent.MouseDown, mouseActions);
...
placeClip.add(clipEvent);

FSClipEvent keyEvent(FSClipEvent.KeyDown, keyActions);
...
placeClip.add(keyEvent);

movie.add(movieClip);
movie.add(placeClip);
</pre>

<h1 class="datasheet">History</h1>

<p>The FSClipEvent class represents the ClipEvent data structure tag from the 
Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 5. 
The event model was extended in Flash 6 to support the set of events that Buttons 
respond to. In Flash 7 the Construct event was added.</p>

 */  
    class DLL_DECL FSClipEvent : public FSTransformObject
    {
public:
        /** Definition of the different types of movie clip event. */
        enum eventType { 
            Load = 1, 
            EnterFrame = 2, 
            Unload = 4, 
            MouseMove = 8, 
            MouseDown = 16, 
            MouseUp = 32, 
            KeyDown = 64, 
            KeyUp = 128, 
            Data = 256,
// Flash 6
            Initialize = 512,
            Press = 1024,
            Release = 2048,
            ReleaseOut = 4096,
            RollOver = 8192,
            RollOut = 16384,
            DragOver = 32768,
            DragOut = 65536,
            KeyPress = 131072,
// Flash 7
            Construct = 262144
        };

        FSClipEvent(FSInputStream* aStream);

        /** Constructs an FSClipEvent object for an event with an empty array of actions.

            @param eventCode the code representing one or more events.
            */
        FSClipEvent(int eventCode = 0)
            : event(eventCode) 
            , keyCode(0) 
            , actions()
            , encodedActions(0)
            , encodedLength(0)
        {}

        /** Constructs an FSClipEvent object that defines the array of actions that will be executed when a particular event occurs. The FSClipEvent object assumes ownership of all the action objects in the array.

            @param eventCode the code representing one or more events.
            @param anArray the array of pointer to actions that will be executed when the specified event occurs.
            */
        FSClipEvent(int eventCode, const FSVector<FSActionObject*>& anArray) 
            : event(eventCode)
            , keyCode(0)
            , actions(anArray)
            , encodedActions(0)
            , encodedLength(0)
            {}

        /** 
         * Constructs an FSClipEvent object that defines the array of actions that 
         * will be executed when a particular event occurs.
         * 
         * @param eventCode the event code.
         * @param bytes an array of encoded action objects.
         * @param size the number of bytes in the encoded actions.
         */
        FSClipEvent(int eventCode, byte* bytes, size_t size) 
            : event(eventCode)
            , keyCode(0)
            , actions()
            , encodedActions(bytes)
            , encodedLength(size)
            {}

        /** Constructs an FSClipEvent object that defines the array of actions that will be executed when a particular event occurs or when the specified key is pressed. 

            @param eventCode the code representing one or more events.
            @param key the ASCII code for the key pressed on the keyboard.
            @param anArray the array of actions that will be executed when the specified event occurs.
            */
        FSClipEvent(int eventCode, int key, const FSVector<FSActionObject*>& anArray) 
            : event(eventCode)
            , keyCode(key)
            , actions(anArray) 
        {}

        /** 
         * Constructs an FSClipEvent object that defines the array of actions that will be 
         * executed when a particular event occurs or when the specified key is pressed.
         * The array of bytes contained the encoded actions and is typically generated
         * using the classes in the Translate framework.
         * 
         * @param eventCode the code representing one or more events.
         * @param key the ASCII code for the key pressed on the keyboard.
         * @param bytes an array of encoded action objects.
         * @param size the number of bytes in the encoded actions.
         */
        FSClipEvent(int eventCode, int key, byte* bytes, size_t size) 
            : event(eventCode)
            , keyCode(key)
            , actions() 
            , encodedActions(bytes)
            , encodedLength(size)
        {}
        
        FSClipEvent(const FSClipEvent& rhs);

        ~FSClipEvent();

        FSClipEvent& operator= (const FSClipEvent& rhs);

        FSClipEvent* clone() const { return new FSClipEvent(*this); }

        const char* className() const;

        /** Adds an action to the array of actions. The FSClipEvent object assumes ownership of the action object.

            @param anAction a pointer to an action object.
            */
        void add(FSActionObject* anAction) { actions.push_back(anAction); }

        /** Adds all the actions in an array to the array of actions. The FSClipEvent object assumes ownership of all the action objects in the array.

            @param anArray an array of pointers to action objects.
            */
        void add(const FSVector<FSActionObject*>& anArray);

        /** Gets the event code that this FSClipEvent defines actions for.

            @return the eventCode representing the events that the FSClipEvent object will respond to.
            */
        int getEvent() const { return event; }

        /**
         * Gets the code for the key that triggers the event when pressed. The code is typically the 
         * ASCII code for standard western keyboards.
         *
         * @return the code for the key that triggers the event.
         */
        int getKeyCode() { return keyCode; }

        /** Gets the array of actions that are executed by the movie clip in response to specified event(s).

            @return the array of actions that will be executed when the specified event occurs.
            */
        FSVector<FSActionObject*>& getActions() { return actions; }

        /** Sets the event code that this FSClipEvent defines actions for.

            @param eventCode the code representing one or more events.
            */
        void setEvent(int eventCode) { event = eventCode; }

        /**
         * Sets the code for the key that triggers the event when pressed. The code is typically the 
         * ASCII code for standard western keyboards.
         *
         * @param code the ASCII code for the key that triggers the event.
         */
        void setKeyCode(int code) {    keyCode = code; }

        /** Sets the array of actions that are executed by the movie clip in response to specified event(s).

            @param anArray the array of actions that will be executed when the specified event occurs.
            */
        void setActions(const FSVector<FSActionObject*>& anArray);

        /** 
         * Set the array of encoded actions generated by the classes in the Translate
         * framework. If the object already contains an array of actions then they 
         * will be deleted.
         * 
         * @param bytes the array of encoded actions.
         * @param size the number of bytes in the encoded actions.
         */
        void setEncodedActions(byte* bytes, size_t size);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int event;
        int keyCode;
        FSVector<FSActionObject*> actions;
        byte* encodedActions;
        size_t encodedLength;
    };
} 

#endif
