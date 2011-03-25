/*
 *  FSPush.h
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

#ifndef __FSPush_h__
#define __FSPush_h__ 1

#include "FSVector.h"

#include "FSActionObject.h"
#include "FSBoolean.h"
#include "FSInteger.h"
#include "FSDouble.h"
#include "FSNull.h"
#include "FSVoid.h"
#include "FSString.h"
#include "FSRegisterIndex.h"
#include "FSTableIndex.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSValue*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{    
/**
 * %FSPush is used to push values on the Flash Player's internal stack.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSPush_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSPush_1">values</a></td>
<td>An array of values that will be pushed onto the Flash Player's Stack and used when executing actions.</td>
</tr>
</table>

<p>The FSPush action supports the full range of data types supported by Flash:</p>

<table class="datasheet">
<tr><th align="left">Data Type</th><th align="left">Description</th></tr>
<tr><td nowrap width="20%">Boolean</td><td>A boolean value, 1 (true) or 0 (false).</td></tr>
<tr><td nowrap width="20%">Integer</td><td>A signed 32-bit integer, range -2,147,483,648 to 2,147,483,647.</td></tr>
<tr><td nowrap width="20%">Double</td><td>A double-precision (64-bit) floating-point number, range approximately +/- 1.79769313486231570E+308.</td></tr>
<tr><td nowrap width="20%">String</td><td>A String. The string is encoded as using the UTF-8 encoding which is backward compatible with ASCII encoding supported in Flash 5.</td></tr>
<tr><td nowrap width="20%">Register Index</td><td>The number (0,..3) of one of the Flash player's internal registers.</td></tr>
<tr><td nowrap width="20%">Table Index</td><td>An index into a table of string literals defined using the FSTable action.</td></tr>
<tr><td nowrap width="20%">Null</td><td>A null value.</td></tr>
<tr><td nowrap width="20%">Void</td><td>A void value.</td></tr>
<tr><td nowrap width="20%">Movie Clip Property</td><td>A reserved number used to identify a specific property of a movie clip.</td></tr>
<tr><td nowrap width="20%">Player Property</td><td>A reserved number used to identify a specific property of the Flash Player.</td></tr>
</table>

<p>Movie Clip properties are used to access the attributes of the specified movie clip. To simplify using movie clip properties the values are defined as constants in the FSPush class:</p>

<table class="datasheet">
<tr><th nowrap align="left">Name</th><th align="left">Description</th></tr>
<tr><td>_x</td><td>The x-coordinate of the current drawing point.</td></tr>
<tr><td>_y</td><td>The y-coordinate of the current drawing point.</td></tr>
<tr><td>_xscale</td><td>The scale of the player window in the x-axis.</td></tr>
<tr><td>_yscale</td><td>The scale of the player window in the y-axis.</td></tr>
<tr><td>_currentframe</td><td>The number of the frame currently being displayed</td></tr>
<tr><td>_totalframes</td><td>The total number of frames in the current movie clip being played.</td></tr>
<tr><td>_alpha</td><td>Whether the player supports alpha channel transparency in colours.</td></tr>
<tr><td>_visible</td><td>Whether the player is currently visible.</td></tr>
<tr><td>_width</td><td>The width of the player, in pixels, on the screen.</td></tr>
<tr><td>_height</td><td>The height of the player, in pixels, on the screen.</td></tr>
<tr><td>_rotation</td><td>The rotation of the movie clip in degrees</td></tr>
<tr><td>_target</td><td>The current target or context for actions.</td></tr>
<tr><td>_framesloaded</td><td>The number of frames from the movie clip that are currently loaded</td></tr>
<tr><td>_name</td><td>The name of a movie clip.</td></tr>
<tr><td>_droptarget</td><td>Then name of the movie clip currently being dragged.</td></tr>
<tr><td>_url</td><td>The URL of the current movie clip being played.</td></tr>
</table>

<p>Player properties are used to access the attributes of the Player showing the movie clips. To simplify using player properties the values are defined as constants in the FSPush class:</p>

<table class="datasheet">
<tr><th nowrap align="left">Name</th><th align="left">Description</th></tr>
<tr><td>_quality</td><td>Whether the player is set to display movie clips at high quality.</td></tr>
<tr><td>_highquality</td><td>Whether the player is set to display movie clips at high quality.</td></tr>
<tr><td>_focusrect</td><td>Whether a bounding yellow rectangle is drawn around the current object (a sprite or button) has the keyboard and mouse focus.</td></tr>
<tr><td>_soundbuftime</td><td>The number of seconds to buffer streaming sound before playing</td></tr>
<tr><td>_xmouse</td><td>The current x-coordinate of the mouse location.</td></tr>
<tr><td>_ymouse</td><td>The current y-coordinate of the mouse location.</td></tr>
</table>

<p>The FSPush class maintains an array of values that will be pushed onto the stack. Any basic data types: boolean, int and double passed in the class constructors or using the add() methods are wrapped internally, in an Boolean, Integer and Double class respectively - simplifying how the class is used. Wrapper classes are only used explicitly when parsing a Flash files and manipulating the values stored in the array.</p>

<h1 class="datasheet">Examples</h1>

<p>Push each of the different types value onto the stack:</p>

<pre>
FSPush boolean        = new FSPush(true);
FSPush integer        = new FSPush(123);
FSPush double         = new FSPush(123.0);
FSPush string         = new FSPush("123");
FSPush null           = new FSPush(new FSNull());
FSPush void           = new FSPush(new FSVoid());
FSPush registerIndex  = new FSPush(new FSRegisterIndex(0));
FSPush tableIndex     = new FSPush(new FSTableIndex(0));
FSPush movieProperty  = new FSPush(FSPush._x);
FSPush playerProperty = new FSPush(FSPush._xmouse);
</pre>

<p>For efficiency a single FSPush action can push several values onto the stack in a single operation. The order in which values are added to the FSPush action is the same order in which the values are pushed onto the stack.</p>

<pre>
FSPush push = new FSPush();

push.add(123);
push.add(123.0);
push.add("123");
</pre>

<p>If an array of values are added to a FSPush object then boolean, int and double values must be wrapped using the Boolean, Integer and Double classes respectively.</p>

<h1 class="datasheet">History</h1>

<p>FSPush is a class for representing the Push action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 4 and contained either an integer or string argument. It was extended in Flash 5 to support a number of different data types and allow more than one value to be added in a single action.</p>

 */  
    class DLL_DECL FSPush : public FSActionObject
    {
public:
        /** Definition of the different types of properties defined in Flash. */
        enum propertyType { X = 0, Y = 1, XScale = 2, YScale = 3, CurrentFrame = 4, TotalFrames = 5, Alpha = 6, Visible = 7, Width = 8, Height = 9, Rotation = 10, Target = 11, FramesLoaded = 12, Name = 13, DropTarget = 14, Url = 15, HighQuality = 16, FocusRect = 17, SoundBufTime = 18, Quality = 19, XMouse = 20, YMouse = 21
        };

        FSPush(FSInputStream* aStream);

        /** Constructs an FSPush action object with no values added. */
        FSPush() : FSActionObject(Push), values() {}

        /** Constructs an FSPush action object initialized with a bool value.

            @param aBool a bool value.
            */
        FSPush(bool aBool) : FSActionObject(Push), values() { add(aBool); }

        /** Constructs an FSPush action object initialized with an integer value.

            @param anInt an integer (int) value.
            */
        FSPush(int anInt) : FSActionObject(Push), values() { add(anInt); }

        /** Constructs an FSPush action object initialized with a double value.

            @param aDouble a double-precision floating-point value.
            */
        FSPush(double aDouble) : FSActionObject(Push), values() { add(aDouble); }

        /** Constructs an FSPush action object initialized with a Null value.

            @param aNull a lightweight FSNull object.
            */
        FSPush(const FSNull& aNull) : FSActionObject(Push), values() { add(aNull); }

        /** Constructs an FSPush action object with the array of values that will be pushed onto the stack initialized with a Void value.

            @param aVoid a lightweight FSVoid object.
            */
        FSPush(const FSVoid& aVoid) : FSActionObject(Push), values() { add(aVoid); }

        /** Constructs an FSPush action object initialized with a string.

            @param aString a C string.
            */
        FSPush(const char* aString) : FSActionObject(Push), values() { add(aString); }

        /** Constructs an FSPush action object initialized with a table index.

            @param anIndex a FSTableIndex referencing an entry in a table of literals.
            */
        FSPush(const FSTableIndex& anIndex) : FSActionObject(Push), values() { add(anIndex); }

        /** Constructs an FSPush action object initialised with a register index.

            @param anIndex a FSRegisterIndex referencing one of the Flash Player's internal registers.
            */
        FSPush(const FSRegisterIndex& anIndex) : FSActionObject(Push), values() { add(anIndex); }

        /** Constructs an FSPush action object initialized with an array of integer values.

            @param anArray an array of integer (int) values.
            @param size the number of elements in the array.
            */
        FSPush(int anArray[], int size) : FSActionObject(Push), values(size)
        {
            for (int i=0; i<size; i++)
            {
                FSInteger* aValue = new FSInteger(anArray[i]);

                if (aValue == 0)
                    throw FSAllocationException();
                else
                    values[i] = aValue;
            }
        }

        /** Constructs an FSPush action object initialized with an array of strings.

            @param anArray an array of strings.
            @param size the number of elements in the array.
            */
        FSPush(char* anArray[], int size) : FSActionObject(Push), values(size)
        {
            for (int i=0; i<size; i++)
            {
                FSString* aValue = new FSString(anArray[i]);

                if (aValue == 0)
                    throw FSAllocationException();
                else
                    values[i] = aValue;
            }
        }

        /** Constructs an FSPush action that will push the values in the array onto the stack. All the objects (derived from the FSValue class) are owned by the FSPush object and will be deleted when the FSPush object is deleted.

            @param anArray an array values to be pushed onto the stack.
            */
        FSPush(const FSVector<FSValue*>& anArray);

        FSPush(const FSPush& rhs);

        ~FSPush();

        FSPush& operator= (const FSPush& rhs);
        
        FSPush* clone() const;

        const char* className() const;

        /** Adds a bool value to the array of values that will be pushed onto the stack.

            @param aBool a bool value.
            */
        void add(bool aBool) { values.push_back(new FSBoolean(aBool)); }

        /** Adds an integer value to the array of values that will be pushed onto the stack.

            @param anInt an integer (int) value.
            */
        void add(int anInt) { values.push_back(new FSInteger(anInt)); } 

        /** Adds a double value to the array of values that will be pushed onto the stack.

            @param aDouble a double-precision floating-point value.
            */
        void add(double aDouble) { values.push_back(new FSDouble(aDouble)); }

        /** Adds a NULL value to the array of values that will be pushed onto the stack.

            @param aNull a lightweight FSNull object.
            */
        void add(const FSNull& aNull) { values.push_back(new FSNull(aNull)); }

        /** Adds a void value to the array of values that will be pushed onto the stack.

            @param aVoid a lightweight FSVoid object.
            */
        void add(const FSVoid& aVoid) { values.push_back(new FSVoid(aVoid)); }

        /** Adds a String to the array of values that will be pushed onto the stack.

            @param aString a String.
            */
        void add(const char* aString) { values.push_back(new FSString(aString)); }

        /** Adds an FSTableIndex to the array of values that will be pushed onto the stack.

            @param anIndex a FSTableIndex referencing an entry in a table of literals.
            */
        void add(const FSTableIndex& anIndex) { values.push_back(new FSTableIndex(anIndex)); }

        /** Adds an FSRegisterIndex to the array of values that will be pushed onto the stack.

            @param anIndex a FSRegisterIndex referencing one of the Flash Player's internal registers.
            */
        void add(const FSRegisterIndex& anIndex) { values.push_back(new FSRegisterIndex(anIndex)); }

        /** Adds an array of integer values to the array values that will be pushed onto the stack.

            @param anArray an array of integer (int) values.
            @param size the number of elements in the array.
            */
        void add(int anArray[], int size)
        {
            for (int i=0; i<size; i++)
            {
                FSInteger* aValue = new FSInteger(anArray[i]);

                if (aValue == 0)
                    throw FSAllocationException();
                else
                    values.push_back(aValue);
            }
        }

        /** Adds an array of strings to the array values that will be pushed onto the stack.

            @param anArray an array of strings.
            @param size the number of elements in the array.
            */
        void add(char* anArray[], int size)
        {
            for (int i=0; i<size; i++)
            {
                FSString* aValue = new FSString(anArray[i]);

                if (aValue == 0)
                    throw FSAllocationException();
                else
                    values[i] = aValue;
            }
       }

        /** Adds the values in the array to the array values that will be pushed onto the stack. All the objects (derived from the FSValue class) are owned by the FSPush object and will be deleted when the FSPush object is deleted.

            @param anArray an array of objects.
            */
        void add(const FSVector<FSValue*>& anArray);

        /** Gets the array of values.

            @return the array of values that will be pushed onto the stack.
            */
        FSVector<FSValue*>& getValues() { return values; }

        /** Sets the array of values.

            @param anArray the array of values that will be pushed onto the stack.
            */
        void setValues(const FSVector<FSValue*>& anArray) { values = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSVector<FSValue*> values;
    };
} 

#endif
