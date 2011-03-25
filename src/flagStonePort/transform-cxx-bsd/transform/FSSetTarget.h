/*
 *  FSSetTarget.h
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

#ifndef __FSSetTarget_h__
#define __FSSetTarget_h__

#include "FSActionObject.h"

#include "FSString.h"

namespace transform
{
/**
 * %FSSetTarget is used to control the time-line of a particular movie clip. 
 * 
<p>The action performs a "context switch". All following actions such as GotoFrame, Play, etc. will be applied to the specified object until another <b>FSSetTarget</b> action is executed. Setting the target to be the empty string ("") returns the target to the movie's main timeline.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSSetTarget_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSSetTarget_1">target</a></td>
<td>The name assigned to a movie clip. Names are assigned using the FSPlaceObject2 class when the movie clip is placed on the Flash Player's Display List.</td>
</tr>

</table>

<h1 class="datasheet">Example</h1>

<pre>
// Direct all subsequent actions to this movie clip

actions->add(new FSSetTarget("/MovieClip:3"));
...
&lt;movie clip actions&gt;
...

// Restore the actions to the main movie timeline

actions->add(new FSSetTarget(""));
</pre>


<h1 class="datasheet">History</h1>

<p>The FSSetTarget class represents the SetTarget action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */ 
    class DLL_DECL FSSetTarget : public FSActionObject
    {
public:
        FSSetTarget(FSInputStream* aStream);

        /** Constructs an FSSetTarget action that changes the context to the specified target.

            @param aString the name of a movie clip.
            */
        FSSetTarget(const char* aString) : FSActionObject(SetTarget), target(aString) {}

        FSSetTarget* clone() const { return new FSSetTarget(*this); }

        const char* className() const;

        /** Gets the name of the target movie clip.

            @return the name of the target movie clip.
            */
        const char* getTarget() { return target.c_str(); }

        /** Sets the name of the target movie clip.

            @param aString the name of a movie clip.
            */
        void setTarget(const char* aString) { target = aString; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString target;
    };
}

#endif
