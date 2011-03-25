/*
 *  FSJump.h
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

#ifndef __FSJump_h__
#define __FSJump_h__ 1

#include "FSActionObject.h"

namespace transform
{
/**
 * The %FSJump action performs an unconditional branch to control the actions executed by the Flash Player. 
 * 
<p>When executed the FSJump action adds an offset to the instruction pointer and execution of the stream of actions continues from that address.</p>

<p>Although the Flash Player contains an instruction pointer it does not support an explicit address space. The instruction pointer is used to reference actions within the current stream of actions being executed whether they are associated with a given frame, button or movie clip. The value contained in the instruction pointer is the address relative to the start of the current stream.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSJump_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSJump_1">offset</a></td>
<td>The offset, relative to the current instruction pointer, to jump to.</td>
</tr>
</table>

<p>The offset is a signed number allowing branches up to -32768 to 32767 bytes. The instruction pointer points to the next instruction so specifying an offset of zero will have no effect on the sequence of instructions executed.</p>

<pre>
FSDoAction actions = new FSDoAction();

actions.add(new FSJump(32));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSJump class represents the ActionJump action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 4.</p>

 */  
    class DLL_DECL FSJump : public FSActionObject
    {
public:
        FSJump(FSInputStream* aStream);

        /** Constructs an FSJump action with the specified offset. The offset must be in the range -32768..32767.

        @param anOffset the number of bytes to add to the instruction pointer.
        */
        FSJump(int anOffset) : FSActionObject(Jump), offset(anOffset) {}

        FSJump* clone() const { return new FSJump(*this); }

        const char* className() const;

        /** Gets the offset that will be added to the instruction pointer.

            @return the number of bytes representing the offset.
            */
        int getOffset() const { return offset; }

        /** Sets the offset to add to the instruction pointer. The offset must be in the range  -32768..32767.

            @param aNumber the offset in bytes to add to the instruction pointer.
            */
        void setOffset(int aNumber) { offset = aNumber; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int offset;
    };
}

#endif
