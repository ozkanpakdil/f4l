/*
 *  FSWaitForFrame.java
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

#ifndef __FSWaitForFrame_h__
#define __FSWaitForFrame_h__

#include "FSActionObject.h"

namespace transform
{
/**
 * The %FSWaitForFrame action instructs the player to wait until the specified frame 
 * number has been loaded. 
 * 
<p>If the frame has been loaded then the actions in the following <i>n</i> actions are executed. This action is most often used to execute a short animation loop that plays until the main part of a movie has been loaded.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSWaitForFrame_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSWaitForFrame_1">frameNumber</a></td>
<td>The number of the frame to check to see whether it has been loaded.</td>
</tr>

<tr>
<td><a name="FSWaitForFrame_2">actionCount</a></td>
<td>The number of actions, following the FSWaitForFrame action that will be executed when the frame has been loaded.</td>
</tr>
</table>

<h1 class="datasheet">Examples</h1>
The following example instructs the Flash Player to wait until the eighth frame of a movie clip has been loaded then to move the time-line to the loaded frame:

<pre>
actions->add(new FSWaitForFrame(8, 1));
actions->add(new FSGotoFrame(8));
</pre>

<p>This method of waiting until a frame has been loaded is considered obsolete. Determining the number of frames loaded using the FramesLoaded property of the Flash player in combination with an FSIf action is now the preferred mechanism:</p>

<pre>
FSDoAction* actions = new FSDoAction();

actions->add(new FSPush("_root"));
actions->add(new FSAction(FSAction::GetVariable));
actions->add(new FSPush(FSPush::FramesLoaded));
actions->add(new FSAction(FSAction::GetProperty));
actions->add(new FSPush(8));
actions->add(new FSAction(FSAction::Less));
actions->add(new FSIf(-29));

actions->add(new FSGotoFrame(8));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSWaitForFrame class represents the ActionWaitForFrame action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 3.</p>

 */
    class DLL_DECL FSWaitForFrame : public FSActionObject
    {
public:
        FSWaitForFrame(FSInputStream* aStream);

        /** Constructs an FSWaitForFrame object with the specified frame number and the number of actions that will be executed when the frame is loaded.

         @param aFrameNumber the number of the frame to wait for.
         @param anActionCount the number of actions to execute.
         */
        FSWaitForFrame(int aFrameNumber, int anActionCount) : FSActionObject(WaitForFrame), frameNumber(aFrameNumber), actionCount(anActionCount) {}

        FSWaitForFrame* clone() const { return new FSWaitForFrame(*this); }

        const char* className() const;

        /** Gets the frame number.

            @return the number of the frame to wait for.
            */
        int getFrameNumber() { return frameNumber; }

        /** Gets the number of actions that will be executed when the specified frame is loaded.

            @return the number of actions.
            */
        int getActionCount() { return actionCount; }

        /** Sets the frame number. The frame number must be in the range 1..65535.

            @param aNumber the number of the frame.
            */
        void setFrameNumber(int aNumber) { frameNumber = aNumber; }

        /** Sets the number of actions to execute if the frame has been loaded, in the range 0..255. Unlike other actions it is the number of actions that are specified not the number of bytes in memory they occupy.

            @param aNumber the number of actions to execute.
            */
        void setActionCount(int aNumber) { actionCount = aNumber; }
        
        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int frameNumber;
        int actionCount;
    };
}

#endif
