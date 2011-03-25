/*
 *  FSRegisterCopy.h
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

#ifndef __FSRegisterCopy_h__
#define __FSRegisterCopy_h__

#include "FSActionObject.h"

namespace transform
{
/**
 * %FSRegisterCopy is used to copy the item at the top of the stack to one of the Flash Player's
 * internal registers. 
 * 
<p>The value is not removed from the stack. The number of registers supported was 
expanded in Flash 7 to 256.</p>

<p>The Flash Player uses a stack to store values when executing the actions 
associated with a button being  pushed, frame being played, etc. If a value is 
used repeatedly in a calculation, it must be pushed onto the stack each time using 
an FSPush action. To speed up the execution of the calculation and reduce the 
amount of code required the value can be saved to one of the internal registers 
of the Flash Player using the FSRegisterCopy action. This copies the value 
currently at the top of the stack into the specified register. Pushing an 
FSRegisterIndex object onto the stack creates a reference to the register so the 
Flash Player uses the value directly rather than pushing the value onto the stack 
then immediately popping to use the value in a calculation.</p>

<p>To copy a value from the top of the stack to a register, specify the number 
of the register, 0..255, in the constructor:</p>

<pre>
// Copy a useful value into one of the Flash Player's registers

actions.add(new FSPush(3.1415296));
actions.add(new FSRegisterCopy(0));

// Use a FSRegisterIndex to look it up later

actions.add(new FSPush(FSRegisterIndex(0)));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSRegisterCopy action represents the ActionStoreRegister action in the 
Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 5 
and expanded in Flash 7 to support up to 256 registers.</p>

 */  
    class DLL_DECL FSRegisterCopy : public FSActionObject
    {
public:
        FSRegisterCopy(FSInputStream* aStream);

        /** Constructs an FSRegisterCopy object with the register number.

            @param anIndex the number of one of the Flash Player's internal registers in the range 0..3.
            */
        FSRegisterCopy(int anIndex) : FSActionObject(RegisterCopy), registerNumber(anIndex) {}

        FSRegisterCopy* clone() const { return new FSRegisterCopy(*this); }

        const char* className() const;

        /** Gets the number of the Player register that the value on the stack will be copied to.

            @return the register number in the range 0..3.
            */
        int getRegisterNumber() { return registerNumber; } 

        /** Gets the number of the Player register that the value on the stack will be copied to.

            @param anIndex the number of one of the Flash Player's internal registers in the range 0..3.
            */
        void setRegisterNumber(int anIndex) { registerNumber = anIndex; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int registerNumber;
    };
}

#endif
