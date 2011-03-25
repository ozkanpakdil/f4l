/*
 *  FSGotoLabel.h
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

#ifndef __FSGotoLabel_h__
#define __FSGotoLabel_h__

#include "FSActionObject.h"

#include "FSString.h"

namespace transform
{
/**
 * The %FSGotoLabel action instructs the player to move to the frame in the current movie 
 * with the specified label.
 * 
<p>The label is assigned to the frame using the FSFrameLabel object.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSGotoLabel_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSGotoLabel_1">label</a></td>
<td>The name that will be assigned to the current frame.</td>
</tr>

</table>

<h1 class="datasheet">Example</h1>

<pre>
FSMovie movie;

// Assign the name to the "current" frame

movie.add(new FSFrameLabel("FirstFrame"));
movie.add(new FSShowFrame());
...

// Move the timeline back to the named frame when the actions
// associated with this frame is executed.

FSDoAction* actions = new FSDoAction();

actions->add(new FSGotoLabel("FirstFrame"));

movie.add(actions);
movie.add(new FSShowFrame());

</pre>

<p>The scope of a frame is delineated by successive FSShowFrame objects. To assign a label to a frame the FSFrameLabel object can be added at any point prior to the FSShowFrame object that marks the end of the frame.</p>

<h1 class="datasheet">History</h1>

<p>FSGotoLabel represents the ActionGotoLabel action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>
 */  
    class DLL_DECL FSGotoLabel : public FSActionObject
    {
public:
        FSGotoLabel(FSInputStream* aStream);

        /** Constructs an FSGotoLabel action with the specified frame label.

        @param aString the label assigned a particular frame in the movie.
        */
        FSGotoLabel(const char* aString) : FSActionObject(GotoLabel), label(aString) {}

        FSGotoLabel* clone() const { return new FSGotoLabel(*this); }

        const char* className() const;

        /** Gets the frame label.

            @return the label assigned to the frame.
            */
        const char* getLabel() { return label.c_str(); }

        /** Sets the frame label.

            @param aString the label assigned a particular frame in the movie.
            */
        void setLabel(const char* aString) { label = aString; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString label;
    };
}

#endif
