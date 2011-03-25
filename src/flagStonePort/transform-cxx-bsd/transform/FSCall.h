/*
 *  FSCall.h
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

#ifndef __FSCall_h__
#define __FSCall_h__

#include "FSActionObject.h"

namespace transform
{
/**
 * %FSCall is used to execute the actions previously assigned to a given frame with an %FSDoAction object.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSCall_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

</table>

<p>FSCall is a stack-based action, the value for the <i>frame name</i> or <i>frame number</i> is retrieved from the top of the stack when it is executed.</p>

<p>The following code fragment show how to execute the actions associated with a given frame number from a Flash movie:</p>

<pre>
actions.add(new FSPush(12));
actions.add(new FSCall());
</pre>

<p>Alternatively if the frame has been assigned a name using an FSFrameLabel object then the associated actions may be executed by using the name as a reference:</p>

<pre>
movie.add(new FSFrameLabel("FirstFrame"));
...
actions.add(new FSPush("FirstFrame"));
actions.add(new FSCall());
</pre>

<h1 class="datasheet">History</h1>

<p>The FSCall class represents the ActionCall action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 4.</p>

 */  
    class DLL_DECL FSCall : public FSActionObject
    {
public:
        FSCall(FSInputStream* aStream);
    
        /** Constructs an FSCall object. */
        FSCall() : FSActionObject(Call) {}

        FSCall* clone() const { return new FSCall(*this); }

        const char* className() const;

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    };
}

#endif
