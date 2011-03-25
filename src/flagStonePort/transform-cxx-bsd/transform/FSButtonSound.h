/*
 *  FSButtonSound.h
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

#ifndef __FSButtonSound_h__
#define __FSButtonSound_h__ 1

#include "FSMovieObject.h"

#include "FSSound.h"

namespace transform
{
    /**
     * %FSButtonSound defines the sounds that are played when an event occurs in a button. 
     * 
<p>A sound is played for only a subset of the events that a button responds to:</p>

<table>
<tr><td>rollOver</td><td>The cursor enters the active area of the button.</td></tr> 
<tr><td>rollOut</td><td>The cursor exits the active area of the button.</td></tr> 
<tr><td>press</td><td>The mouse button is clicked and the cursor is inside the active area of the button.</td></tr> 
<tr><td>release</td><td>The mouse button is released while the cursor is inside the active area of the button.</td></tr>
</table>

<table>

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSButtonSound_0">type</a></td>
<td>Identifies the data structure when it is encoded. The type attribute is read-only and may be used when iterating through the objects in an FSMovie object to identify the object class without using run-time type checking.</td>
</tr>

<tr>
<td><a name="FSButtonSound_1">identifier</a></td>
<td>the identifier of an FSDefineButton or FSDefineButton2 object that define the button.</td>
</tr>

<tr>
<td><a name="FSButtonSound_2">sound[rollOver]</a></td>
<td>An FSSound object that describes how the sound will be played for a rollOver event.</td>
</tr>

<tr>
<td><a name="FSButtonSound_3">sound[rollOut]</a></td>
<td>An FSSound object that describes how the sound will be played for a rollOver event.</td>
</tr>

<tr>
<td><a name="FSButtonSound_4">sound[press]</a></td>
<td>An FSSound object that describes how the sound will be played for a press event.</td>
</tr>

<tr>
<td><a name="FSButtonSound_5">sound[release]</a></td>
<td>An FSSound object that describes how the sound will be played for a release event.</td>
</tr>

</table>

<p><b>Important:</b> If the identifier in the FSSound object for an event is set to zero then the corresponding FSSound object will not be encoded when the object is encoded to a Flash file. This compresses the object when the sounds for only a sub-set of the events are defined.</p>

 <h1 class="datasheet">History</h1>

<p>The FSButtonSound class represents the DefineButtonSound structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 2.</p>

     */ 
    class DLL_DECL FSButtonSound : public FSMovieObject
    {
public:
        FSButtonSound(FSInputStream* aStream);

        /**  Constructs an FSButtonSound object that defines the sound played for a single button event.

            @param anIdentifier the identifier of the FSDefineButton or FSDefineButton2 object that defines the button.
            @param eventCode the event that identifies when the sound id played, must be either FSButtonEvent::rollOver, FSButtonEvent::rollOut, FSButtonEvent::press or FSButtonEvent::release.
            @param aSound an FSSound object that controls how the sound is played.
            */
        FSButtonSound(int anIdentifier, int eventCode, const FSSound& aSound);

        FSButtonSound* clone() const { return new FSButtonSound(*this); }

        const char* className() const;

        /** Gets the identifier of the button that this object applies to.

            @return the identifier of the button.
            */
        int getIdentifier() const { return identifier; }

        /** Gets the sound for the specified event.

            @param eventCode the code representing the button event. must be either FSButtonEvent::rollOver, FSButtonEvent::rollOut, FSButtonEvent::press or FSButtonEvent::release.
            @return the FSSound that identifies and controls the sound that will be played for the event.
            */
        FSSound& getSoundForEvent(int eventCode);

        /** Sets the identifier of the button that this object applies to.

            @param anIdentifier the identifier of the button which this object applies to.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the FSSound object for the specified button event.

            @param eventCode the code representing the button event, must be either FSButtonEvent::rollOver, FSButtonEvent::rollOut, FSButtonEvent::press or FSButtonEvent::release.
            @param aSound an FSSound object that identifies and controls how the sound is played.
            */
        void setSoundForEvent(int eventCode, const FSSound& aSound);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    
    private:
        int identifier;

        FSSound sound[4];
    };
}

#endif
