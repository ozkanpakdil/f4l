/*
 *  FSGotoFrame.java
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

#ifndef __FSGotoFrame_h__
#define __FSGotoFrame_h__

#include "FSActionObject.h"

namespace transform
{
/**
 * The %FSGotoFrame action instructs the player to move to the specified frame in the current 
 * movie's main time-line.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSGotoFrame_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr><td><a name="FSGotoFrame_1">frameNumber</a></td>
<td>The number of the frame in the movie's main time-line, in the range 1..65535, to move to.</td>
</tr>

</table>

<p>The movie will start playing immediately from the specified frame.</p>

<h1 class="datasheet">Examples</h1>

<pre>
FSGotoFrame gotoFrame(12);
</pre>

<p>FSGotoFrame is only used to control the main time-line of a movie. Controlling how an individual movie clip is played is handled by a different mechanism. From Flash 5 onward movie clips are defined as objects. The ExecuteMethod action is used to execute the gotoAndPlay() or gotoAndStop() methods that control a movie clip's time-line:</p>

<pre>
// Push the arguments followed by the number of arguments onto the stack

frameAction.add(new FSPush("frameName"));
frameAction.add(new FSPush(1));

// Get a reference to the object.

frameAction.add(new FSPush("_root"));
frameAction.add(new FSPush("movieClip"));
frameAction.add(new FSAction(FSAction::GetAttribute));

// Place the name of the method on the stack then execute it.

frameAction.add(new FSPush("gotoAndPlay"));
frameAction.add(new FSAction(FSAction::ExecuteMethod));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSGotoFrame represents the ActionGotoFrame action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3. This class is now superceded by the FSGotoFrame2 action which allows either the name of a frame or a number of be specified.</p>
 */
    class DLL_DECL FSGotoFrame : public FSActionObject
    {
public:
        FSGotoFrame(FSInputStream* aStream);

        /** Constructs an FSGotoFrame with the specified frame number. The frame number must be in the range 1..65535.

        @param aNumber the frame number.
        */
        FSGotoFrame(int aNumber) : FSActionObject(GotoFrame), frameNumber(aNumber) {}

        FSGotoFrame* clone() const { return new FSGotoFrame(*this); }

        const char* className() const;

        /** Gets the number of the frame to move the main time-line to.

            @return the frame number.
            */
        int getFrameNumber() { return frameNumber; }

        /** Sets the number of the frame to move the main time-line to. The frame number must be in the range 1..65535.

            @param aNumber the frame number.
            */
        void setFrameNumber(int aNumber) { frameNumber = aNumber; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int frameNumber;
    };
}

#endif
