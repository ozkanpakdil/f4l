/*
 *  FSButtonEvent.h
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

#ifndef __FSButtonEvent_h__
#define __FSButtonEvent_h__ 1

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
 * %FSButtonEvent is used to define the actions that a button will execute in response 
 * to a particular event.
 * 
<p>The events that a button responds to are:</p>

<table class="datasheet">
<tr><td>RollOver</td><td>occurs when the mouse cursor moves over the active area of a button.</td></tr>
<tr><td>RollOut</td><td>occurs when the mouse cursor moves out of the active area of a button.</td></tr>
<tr><td>Press</td><td>occurs when the mouse button is clicked while the mouse cursor is over the active area of the button.</td></tr>
<tr><td>Release</td><td>occurs when the mouse button is clicked and released while the mouse cursor is over the active area of the button.</td></tr>
<tr><td>DragOut</td><td>occurs when the mouse button is clicked and the mouse cursor is dragged out of the active area of the button.</td></tr>
<tr><td>DragOver</td><td>occurs when the mouse button is clicked, the mouse cursor is dragged into the active area of the button and the mouse button is released.</td></tr>
</td></tr>
</table>

<p>When a button is configured as a menu item (FSDefineButton2 objects only) then three additional events can occur:</p>

<table class="datasheet">
<tr><td>MenuDragOver</td><td>occurs when the mouse button is clicked and the mouse cursor is dragged into the active area of the menu item.</td></tr>
<tr><td>MenuDragOut</td><td>occurs when the mouse button is clicked and the mouse
cursor is dragged out of the active area of the menu item.</td></tr>
<tr><td>ReleaseOut</td><td>occurs when the mouse button is clicked and the mouse cursor is dragged into the active area of the menu item.</td></tr>
</table>

<p>In addition to responding to mouse events, buttons also respond to keys being pressed on the keyboard. Keyboard events are defined by the character key being pressed, e.g. "t", "T", "$", etc. For control keys a number of reserved names are supported:</p>

<table class="datasheet">
<tr><td>&lt;Left&gt;</td><td>Left arrow key.</td></tr>
<tr><td>&lt;Right&gt;</td><td>Right arrow key.</td></tr>
<tr><td>&lt;Home&gt;</td><td>Home key.</td></tr>
<tr><td>&lt;End&gt;</td><td>End key</td></tr>
<tr><td>&lt;Insert&gt;</td><td>Insert key.</td></tr>
<tr><td>&lt;Delete&gt;</td><td>Delete key.</td></tr>
<tr><td>&lt;Backspace&gt;</td><td>Backspace key.</td></tr>
<tr><td>&lt;Enter&gt;</td><td>Enter (return) key.</td></tr>
<tr><td>&lt;Up&gt;</td><td>Up arrow key.</td></tr>
<tr><td>&lt;Down&gt;</td><td>Down arrow key.</td></tr>
<tr><td>&lt;Pageup&gt;</td><td>Page up key.</td></tr>
<tr><td>&lt;Pagedown&gt;</td><td>Page down key.</td></tr>
<tr><td>&lt;Tab&gt;</td><td>Tab key.</td></tr>
<tr><td>&lt;Escape&gt;</td><td>Escape key.</td></tr>
<tr><td>&lt;Space&gt;</td><td>Space bar.</td></tr>
</table>

<p>Since the event code allows multiple events, the code for compound events can be created by performing a bit-wise Or of the individual codes:</p>

<pre>
int eventCode = FSButtonEvent::RollOver | FSButtonEvent::Press;
</pre>

<p>The class method <b>codeForKey</b> returns the event code that identifies when a specific key is pressed:</p>

<pre>
int eventCode = FSButtonEvent::codeForKey('J');
</pre>

<p>Control keys are identified using one of the reserved ButtonEvent values:</p>

<pre>
int eventCode = FSButtonEvent::Enter | FSButtonEvent::PageUp;
</pre>

<p>However while multiple mouse events can be defined for a button only one keyboard event can be defined.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSButtonEvent_0">event</a></td>
<td>a code identifying the different types of button events that the actions defined in this object will be executed in response to.</td>
</tr>

<tr><td><a name="FSButtonEvent_1">actions</a></td>
<td>An array of action objects that are executed when the events defined in the event code occur.</td>
</tr>

<tr><td><a name="FSButtonEvent_2">encodedActions</a></td>
<td>An array of bytes containing encoded actions can also be set. The encoded actions are typically generated by the parser in the Translate framework. The actions array and encodedActions cannot both be valid at the same time. Accessor methods used to set either of the attributes will set the other to null.</td>
</table>

<h1 class="datasheet">History</h1>

<p>The FSButtonEvent class represents the ButtonCondAction data structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>
 */  
    class DLL_DECL FSButtonEvent : public FSTransformObject
    {
public:
        /** Definition of the different types of event that a button can respond to. */
        enum eventType { RollOver = 1, RollOut = 2, Press = 4, Release = 8, DragOut = 16, DragOver = 32, ReleaseOut = 64, MenuDragOver = 128, MenuDragOut = 256, Left = 512, Right = 1024, Home = 1536, End = 2048, Insert = 2560, Delete = 3072, Backspace = 4096, Enter = 6656, Up = 7168, Down = 7680, PageUp = 8192, PageDown = 8704, Tab = 9216, Escape = 9728, Space = 16384 };

        /** Generates the code identifying a particular event using the name of the event.

            @param c a keyboard character.
            @return the event code corresponding to the specified event.
        */
        static int codeForKey(char c);

        FSButtonEvent(FSInputStream* aStream);

        FSButtonEvent() 
            : event(0)
            , actions()
            , encodedActions(0)
            , encodedLength(0) 
        {}

        /** Constructs an FSButtonEvent object that defines the array of actions that will be executed when a particular event occurs.

            @param aNumber the event code.
            @param anArray the array of action objects that will be executed when the specified event(s) occur.
            */
        FSButtonEvent(int aNumber, const FSVector<FSActionObject*>& anArray) 
            : event(aNumber)
            , actions(anArray)
            , encodedActions(0)
            , encodedLength(0)
        {}

        /** 
         * Constructs an FSButtonEvent object that defines the array of actions that 
         * will be executed when a particular event occurs.
         * 
         * @param aNumber the event code.
         * @param bytes an array of encoded action objects.
         * @param size the number of bytes in the encoded actions.
         */
        FSButtonEvent(int aNumber, byte* bytes, size_t size) 
            : event(aNumber)
            , actions()
            , encodedActions(bytes)
            , encodedLength(size)
        {}

        FSButtonEvent(const FSButtonEvent& rhs);

        ~FSButtonEvent();

        FSButtonEvent& operator= (const FSButtonEvent& rhs);

        FSButtonEvent* clone() const { return new FSButtonEvent(*this); }

        const char* className() const;

        /** Add an action to the end of the actions array. The FSButtonEvent object assumes ownership of the action object.

            @param anAction an FSActionObject.
            */
        void add(FSActionObject* anAction) { actions.push_back(anAction); }

        /** Adds all the action objects in the array to the end of the actions array. The FSButtonEvent object assumes ownership of all the action objects in the array.

            @param anArray of FSActionObject objects.
            */
        void add(const FSVector<FSActionObject*>& anArray);

        /** Gets the event code that this FSButtonEvent defines actions for.

            @return the compound event code.
            */
        int getEvent() const { return event; }

        /** Gets the array of actions that are executed by the button in response to specified event(s).

            @return the array of action objects that will be executed when the specified event(s) occur.
            */
        FSVector<FSActionObject*>& getActions() { return actions; }

        /** Sets the event code that this FSButtonEvent defines actions for.

            @param aNumber the event code.
            */
        void setEvent(int aNumber) { event = aNumber; }

        /** Sets the array of actions that are executed by the button in response to specified event(s). The FSButtonEvent object assumes ownership of all the action objects in the array. Any existing actions are deleted.

            @param anArray the array of action objects that will be executed when the specified event(s) occur.
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
        FSVector<FSActionObject*> actions;
        byte* encodedActions;
        size_t encodedLength;
    };
}

#endif
