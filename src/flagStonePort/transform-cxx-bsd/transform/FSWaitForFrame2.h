/*
 *  FSWaitForFrame2.h
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

#ifndef __FSWaitForFrame2_h__
#define __FSWaitForFrame2_h__

#include "FSActionObject.h"

namespace transform
{
/**
 * The %FSWaitForFrame2 action instructs the player to wait until the specified frame 
 * number or named frame has been loaded. 
 * 
<p>If the frame has been loaded then the following <i>n</i> actions are executed. The FSWaitForFrame2 action extends the FSWaitForFrame action by allowing the name of a frame to be specified.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSWaitForFrame2_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSWaitForFrame2_1">actionCount</a></td>
<td>The number of actions following that will be executed when the frame of interest has been loaded.</td>
</tr>
</table>

<p>FSWaitForFrame2 is a stack-based action. The frame number or frame name which should be loaded to trigger execution of the following actions is popped from the Flash Player's stack.</p>

<h1 class="datasheet">Examples</h1>
The following example instructs the Flash Player to wait until the frame with the name "frame" in a movie clip has been loaded:

<pre>
actions.add(new FSPush("frame"));
actions.add(new FSWaitForFrame2(1));
actions.add(new FSGotoFrame2("frame"));
</pre>

<p>This method of waiting until a frame has been loaded is considered obsolete. Determining the number of frames loaded using the FramesLoaded property of the Flash player in combination with an FSIf action is now the preferred mechanism:</p>

<pre>
FSDoAction actions = new FSDoAction();

actions.add(new FSPush("_root"));
actions.add(FSAction.GetVariable());
actions.add(new FSPush(FSPush.FramesLoaded));
actions.add(FSAction.GetProperty());
actions.add(new FSPush(8));
actions.add(FSAction.Less());
actions.add(new FSIf(-29));

actions.add(new FSGotoFrame(8));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSWaitForFrame2 class represents the ActionWaitForFrame2 action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 4.</p>

 */  
    class DLL_DECL FSWaitForFrame2 : public FSActionObject
    {
public:
        FSWaitForFrame2(FSInputStream* aStream);

        /** Constructs an FSWaitForFrame2 object with the number of actions to execute if the frame has been loaded.

            @param aNumber the number of actions to execute.
            */
        FSWaitForFrame2(int aNumber) : FSActionObject(WaitForFrame2), actionsCount(aNumber) {}

        FSWaitForFrame2* clone() const { return new FSWaitForFrame2(*this); }

        const char* className() const;

        /** Gets the number of actions to execute.

            @return the number of actions to execute.
            */
        int getActionsCount() { return actionsCount; }

        /** Sets the number of actions to execute.

            @param aNumber the number of actions to execute.
            */
        void setActionsCount(int aNumber) { actionsCount = aNumber; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int actionsCount;
    };
}

#endif
